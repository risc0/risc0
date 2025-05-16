// Copyright 2025 RISC Zero, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

use std::path::{Path, PathBuf};
use std::time::Duration;

use anyhow::{bail, Context as _, Result};
use async_ssh2_tokio::{AuthMethod, Client as SshClient, ServerCheckMethod};
use aws_config::SdkConfig;
use aws_sdk_ec2::config::http::HttpResponse;
use aws_sdk_ec2::operation::describe_instances::DescribeInstancesError;
use aws_sdk_ec2::{
    error::SdkError,
    types::{
        IamInstanceProfileSpecification, InstanceStateName, InstanceType, ResourceType, Tag,
        TagSpecification,
    },
    Client as Ec2Client,
};
use clap::Parser;
use tokio::io::AsyncWriteExt as _;

const UBUNTU_DEEP_LEARNING_AMI: &str = "ami-05849253e8f2c10d8";
const SECURITY_GROUP: &str = "sg-0d81367b2160f98f7";
const CLUSTER_ARN: &str = "arn:aws:iam::778447792808:instance-profile/r0vm-cluster";

struct Instance {
    #[allow(dead_code)]
    ec2_client: Ec2Client,
    ssh: SshClient,
    id: String,
    ip: String,
}

impl Instance {
    async fn start_r0vm(&self, r0vm_args: &str) -> Result<()> {
        println!("{}: installing r0vm service", self.id);

        let service_contents = format!(
            "\
            [Service]\n\
            ExecStart=/home/ubuntu/r0vm {r0vm_args}\n\
            \n\
            [Install]\n\
            WantedBy=multi-user.target\n\
        "
        );
        ssh_execute_check(&self.ssh,
            &format!(
                "sudo bash -c \"echo \\\"{service_contents}\\\" > /etc/systemd/system/r0vm.service\""
            ))
            .await?;

        ssh_execute_check(&self.ssh, "sudo systemctl daemon-reload").await?;
        ssh_execute_check(&self.ssh, "sudo systemctl start r0vm").await?;

        Ok(())
    }

    async fn start_jaeger(&self) -> Result<()> {
        println!("{}: starting jaeger container", self.id);

        let cmd = format!(
            "\
              docker run -d --name jaeger \
                  -p 16686:16686 \
                  -p 4317:4317 \
                  -p 4318:4318 \
                  -p 5778:5778 \
                  -p 9411:9411 \
                  jaegertracing/jaeger:2.6.0\
        "
        );
        ssh_execute_check(&self.ssh, &cmd).await?;

        println!("{}: waiting for jaeger to be listening", self.id);
        for tcp_port in [16686, 4317, 4318, 5778, 9411] {
            loop {
                let res = self
                    .ssh
                    .execute(&format!("nc -z 127.0.0.1 {tcp_port}"))
                    .await?;
                if res.exit_status == 0 {
                    break;
                }

                tokio::time::sleep(Duration::from_secs(1)).await;
            }
        }

        Ok(())
    }
}

async fn ssh_execute_check(ssh: &SshClient, cmd: &str) -> Result<()> {
    let res = ssh.execute(cmd).await?;

    if res.exit_status != 0 {
        bail!(
            "ssh command {cmd:?} failed with: {}. stderr = {}",
            res.exit_status,
            res.stderr
        );
    }

    Ok(())
}

fn is_not_found_error(error: &SdkError<DescribeInstancesError, HttpResponse>) -> bool {
    error
        .as_service_error()
        .is_some_and(|e| e.meta().code() == Some("InvalidInstanceID.NotFound"))
}

async fn set_up_instance(
    ec2_client: Ec2Client,
    key_material: &str,
    id: &str,
    r0vm_name: &str,
) -> Result<Instance> {
    println!("{id}: waiting for running");

    let instance_description = loop {
        let describe_output = match ec2_client
            .describe_instances()
            .instance_ids(id)
            .send()
            .await
        {
            Ok(o) => o,
            Err(error) if is_not_found_error(&error) => continue,
            Err(error) => return Err(error.into()),
        };

        let instance_description = &describe_output.reservations()[0].instances()[0];
        if instance_description.state().unwrap().name().unwrap() == &InstanceStateName::Running {
            break instance_description.clone();
        }

        tokio::time::sleep(Duration::from_secs(1)).await;
    };

    let ip = instance_description.public_ip_address().unwrap();
    println!("{id}: got ip = {ip}, waiting for ssh to come up");

    let ssh = loop {
        let res = SshClient::connect(
            (ip, 22),
            "ubuntu",
            AuthMethod::PrivateKey {
                key_data: key_material.into(),
                key_pass: None,
            },
            ServerCheckMethod::NoCheck,
        )
        .await;
        match res {
            Ok(ssh) => break ssh,
            Err(error) => {
                println!("{id}: got ssh error: {error}, retrying...");
                tokio::time::sleep(Duration::from_secs(1)).await;
            }
        }
    };
    println!("{id}: established ssh connection");

    println!("{id}: downloading and extracting r0vm binary");
    ssh_execute_check(
        &ssh,
        &format!("aws s3 cp s3://r0vm-cache/{r0vm_name} /home/ubuntu/"),
    )
    .await?;
    ssh_execute_check(&ssh, &format!("tar -xJf /home/ubuntu/{r0vm_name}")).await?;

    let storage_root = "/home/flaub/src/risc0/tmp/bucket";
    for sub_dir in ["images", "inputs", "receipts"] {
        ssh_execute_check(&ssh, &format!("sudo mkdir -p {storage_root}/{sub_dir}")).await?;
    }

    Ok(Instance {
        ec2_client,
        ssh,
        id: id.into(),
        ip: ip.into(),
    })
}

#[derive(Parser)]
struct Cli {
    #[arg(long)]
    num_workers: i32,

    #[arg(long)]
    r0vm_path: PathBuf,

    #[arg(long)]
    cluster_name: String,

    #[arg(long)]
    aws_profile: String,
}

async fn create_key(client: &Ec2Client, cluster_name: &str) -> Result<(String, String)> {
    client
        .delete_key_pair()
        .key_name(format!("r0vm-cluster-{cluster_name}"))
        .send()
        .await?;

    let key = client
        .create_key_pair()
        .key_name(format!("r0vm-cluster-{cluster_name}"))
        .send()
        .await?;

    let key_path = format!("{cluster_name}.pem");
    let _ = tokio::fs::remove_file(&key_path).await;

    let mut key_file = tokio::fs::OpenOptions::new()
        .write(true)
        .create(true)
        .mode(0o700)
        .open(&key_path)
        .await?;

    let mut key_contents = key.key_material.as_ref().unwrap().as_bytes();
    tokio::io::copy(&mut key_contents, &mut key_file).await?;
    key_file.flush().await?;
    drop(key_file);

    Ok((key.key_name.unwrap(), key.key_material.unwrap()))
}

async fn compress_r0vm(r0vm_path: &Path) -> Result<PathBuf> {
    let digest = sha256::try_async_digest(r0vm_path).await?;

    let r0vm_xz_path = r0vm_path.with_extension(&format!("{digest}.tar.xz"));
    if tokio::fs::try_exists(&r0vm_xz_path).await? {
        return Ok(r0vm_xz_path);
    }

    let mut r0vm_file = tokio::fs::OpenOptions::new()
        .read(true)
        .open(&r0vm_path)
        .await
        .with_context(|| format!("failed to open {}", r0vm_path.display()))?;

    let r0vm_xz_file = tokio::fs::OpenOptions::new()
        .write(true)
        .create(true)
        .open(&r0vm_xz_path)
        .await
        .with_context(|| format!("failed to open {}", r0vm_xz_path.display()))?;
    let xz_stream = async_compression::tokio::write::LzmaEncoder::with_quality(
        r0vm_xz_file,
        async_compression::Level::Fastest,
    );

    let mut tar_file = tokio_tar::Builder::new(xz_stream);
    tar_file.append_file("r0vm", &mut r0vm_file).await?;
    tar_file.finish().await?;

    let mut xz_stream = tar_file.into_inner().await?;
    xz_stream.flush().await?;
    xz_stream.shutdown().await?;
    xz_stream.into_inner().flush().await?;

    Ok(r0vm_xz_path)
}

async fn upload_r0vm(config: &SdkConfig, path: &Path) -> Result<String> {
    let client = aws_sdk_s3::Client::new(config);

    let name = path.file_name().unwrap();
    let object_key = name.to_str().unwrap();

    let got_object = client
        .get_object()
        .bucket("r0vm-cache")
        .key(object_key)
        .send()
        .await
        .is_ok();

    if !got_object {
        let body = aws_sdk_s3::primitives::ByteStream::from_path(path).await;
        client
            .put_object()
            .bucket("r0vm-cache")
            .key(object_key)
            .body(body.unwrap())
            .send()
            .await?;
    }

    Ok(object_key.into())
}

#[tokio::main(flavor = "current_thread")]
async fn main() -> Result<()> {
    let args = Cli::parse();

    let config = aws_config::from_env()
        .profile_name(&args.aws_profile)
        .load()
        .await;
    let client = Ec2Client::new(&config);

    println!("creating key pair");
    let (key_name, key_material) = create_key(&client, &args.cluster_name).await?;

    println!("compressing r0vm");
    let r0vm_xz_path = compress_r0vm(&args.r0vm_path).await?;

    println!("uploading r0vm");
    let r0vm_name = upload_r0vm(&config, &r0vm_xz_path).await?;

    println!("requesting AWS EC2 machines");
    let count = args.num_workers;
    let gpu_instances = client
        .run_instances()
        .min_count(count)
        .max_count(count)
        .image_id(UBUNTU_DEEP_LEARNING_AMI)
        .key_name(key_name.clone())
        .security_group_ids(SECURITY_GROUP)
        .instance_type(InstanceType::G6eXlarge)
        .iam_instance_profile(
            IamInstanceProfileSpecification::builder()
                .arn(CLUSTER_ARN)
                .build(),
        )
        .tag_specifications(
            TagSpecification::builder()
                .resource_type(ResourceType::Instance)
                .tags(Tag::builder().key("name").value(&args.cluster_name).build())
                .build(),
        )
        .send()
        .await?;

    let count = 2;
    let cpu_instances = client
        .run_instances()
        .min_count(count)
        .max_count(count)
        .image_id(UBUNTU_DEEP_LEARNING_AMI)
        .key_name(key_name.clone())
        .security_group_ids(SECURITY_GROUP)
        .instance_type(InstanceType::C5n2xlarge)
        .iam_instance_profile(
            IamInstanceProfileSpecification::builder()
                .arn(CLUSTER_ARN)
                .build(),
        )
        .tag_specifications(
            TagSpecification::builder()
                .resource_type(ResourceType::Instance)
                .tags(Tag::builder().key("name").value(&args.cluster_name).build())
                .build(),
        )
        .send()
        .await?;

    let mut handles = vec![];
    for i in cpu_instances
        .instances()
        .iter()
        .chain(gpu_instances.instances().iter())
    {
        let client = client.clone();
        let id = i.instance_id().unwrap().to_owned();
        let r0vm_name = r0vm_name.clone();
        let key_material = key_material.clone();
        let handle = tokio::task::spawn(async move {
            set_up_instance(client, &key_material, &id, &r0vm_name).await
        });
        handles.push(handle);
    }

    let mut instances = vec![];
    for handle in handles {
        instances.push(handle.await.unwrap()?);
    }

    let manager = &instances[0];
    manager.start_jaeger().await?;
    manager
        .start_r0vm("--manager --addr 0.0.0.0:9000 --api 0.0.0.0:9001")
        .await?;
    let manager_ip = &manager.ip;

    let executor = &instances[1];
    executor
        .start_r0vm(&format!("--worker=execute --addr {manager_ip}:9000"))
        .await?;

    println!("jaeger ui = http://{manager_ip}:16686/");
    println!("export BONSAI_API_URL=http://{manager_ip}:9001");
    println!("export BONSAI_API_KEY=anything");
    println!(
        "ssh to manager = `ssh -i {}.pem ubuntu@{manager_ip}`",
        args.cluster_name
    );

    for worker in &instances[2..] {
        let args = format!(
            "\
            --worker=\"prove-segment,prove-keccak,lift,join,union,resolve\" \
            --addr {manager_ip}:9000\
            "
        );
        worker.start_r0vm(&args).await?;
    }

    Ok(())
}
