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

use std::collections::{BTreeMap, BTreeSet};
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
        IamInstanceProfileSpecification, Instance, InstanceStateName, InstanceType, ResourceType,
        Tag, TagSpecification,
    },
    Client as Ec2Client,
};
use clap::Parser;
use tokio::io::AsyncWriteExt as _;

const UBUNTU_DEEP_LEARNING_AMI: &str = "ami-05849253e8f2c10d8";
const SECURITY_GROUP: &str = "sg-0d81367b2160f98f7";
const CLUSTER_ARN: &str = "arn:aws:iam::778447792808:instance-profile/r0vm-cluster";

struct Machine {
    #[allow(dead_code)]
    ec2_client: Ec2Client,
    ssh: SshClient,
    id: String,
    ip: String,
    tag: &'static str,
}

impl Machine {
    async fn start_r0vm(&self, r0vm_args: &str) -> Result<()> {
        println!("{}: installing r0vm service", self.id);

        let service_contents = format!(
            "\
            [Service]\n\
            Environment=\
                RUST_LOG=info \
                RISC0_INFO=1 \
                OTEL_EXPORTER_OTLP_ENDPOINT=http://jaeger-poc:4318\n\
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

    #[allow(dead_code)]
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

    async fn join_tailscale(&self, tail_scale_key: &str) -> Result<()> {
        println!("{}: joining tailscale", self.id);

        ssh_execute_check(
            &self.ssh,
            "curl -fsSL https://tailscale.com/install.sh | sh",
        )
        .await?;

        ssh_execute_check(
            &self.ssh,
            &format!("sudo tailscale up --auth-key={tail_scale_key}"),
        )
        .await?;

        println!("{}: waiting for jaeger to be available", self.id);
        loop {
            let res = self.ssh.execute(&format!("nc -z jaeger-poc 4318")).await?;
            if res.exit_status == 0 {
                break;
            }

            tokio::time::sleep(Duration::from_secs(1)).await;
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
    tag: &'static str,
    key_material: &str,
    instance: Instance,
    r0vm_name: &str,
) -> Result<Machine> {
    let id = instance.instance_id().unwrap();
    let ip = instance.public_ip_address().unwrap();
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

    Ok(Machine {
        ec2_client,
        ssh,
        id: id.into(),
        ip: ip.into(),
        tag,
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

    #[arg(long)]
    tail_scale_key: String,

    #[arg(long)]
    po2: u32,
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
    let mut gpu_instances = vec![];
    while gpu_instances.len() < count as usize {
        gpu_instances.extend(
            client
                .run_instances()
                .min_count(1)
                .max_count((count as usize - gpu_instances.len()) as i32)
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
                .await?
                .instances()
                .iter()
                .map(|i| i.instance_id.clone().unwrap()),
        );
        println!("got {}/{count} gpu instances", gpu_instances.len());
    }

    let mut cpu_instances = vec![];
    for _ in 0..2 {
        cpu_instances.extend(
            client
                .run_instances()
                .min_count(1)
                .max_count(1)
                .image_id(UBUNTU_DEEP_LEARNING_AMI)
                .key_name(key_name.clone())
                .security_group_ids(SECURITY_GROUP)
                .instance_type(InstanceType::R7izMetal16xl)
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
                .await?
                .instances()
                .iter()
                .map(|i| i.instance_id.clone().unwrap()),
        );
    }
    println!("got 2/2 cpu instances");

    let all_ids: Vec<_> = cpu_instances
        .into_iter()
        .chain(gpu_instances.into_iter())
        .collect();

    let mut join_set = tokio::task::JoinSet::new();

    let mut remaining_machines: BTreeSet<_> = all_ids.clone().into_iter().collect();
    let mut retry_limits: BTreeMap<String, u32> = BTreeMap::new();
    while !remaining_machines.is_empty() {
        let describe_output = match client
            .describe_instances()
            .set_instance_ids(Some(all_ids.clone()))
            .send()
            .await
        {
            Ok(o) => o,
            Err(error) if is_not_found_error(&error) => {
                continue;
            }
            Err(error) => return Err(error.into()),
        };

        for reservation in describe_output.reservations() {
            for instance in reservation.instances() {
                let id = instance.instance_id().unwrap();
                let instance_state = instance.state().unwrap().name().unwrap();
                if instance_state == &InstanceStateName::Running {
                    if !remaining_machines.remove(id) {
                        continue;
                    }

                    println!("{id}: has started");
                    let client = client.clone();
                    let r0vm_name = r0vm_name.clone();
                    let key_material = key_material.clone();
                    let tag = match all_ids.iter().position(|id_| id_ == &id).unwrap() {
                        0 => "manager",
                        1 => "executor",
                        _ => "worker",
                    };
                    let instance = instance.clone();
                    join_set.spawn(async move {
                        set_up_instance(client, tag, &key_material, instance, &r0vm_name).await
                    });
                } else {
                    println!("{id}: state = {instance_state:?}");
                    *retry_limits.entry(id.into()).or_default() += 1;
                    if *retry_limits.entry(id.into()).or_default() > 30 {
                        println!("{id}: giving up waiting");
                        remaining_machines.remove(id);
                    }
                }
            }
        }

        tokio::time::sleep(Duration::from_secs(1)).await;
    }

    let mut remaining_machines: BTreeSet<_> = all_ids.into_iter().collect();
    let mut instances = vec![];
    while let Some(res) = join_set.join_next().await {
        let instance = res.unwrap()?;
        remaining_machines.remove(&instance.id);
        instances.push(instance);
        println!("machines still being set-up: {:?}", &remaining_machines);
    }

    let manager = instances.iter().find(|m| m.tag == "manager").unwrap();
    manager.join_tailscale(&args.tail_scale_key).await?;
    manager
        .start_r0vm("--manager --addr 0.0.0.0:9000 --api 0.0.0.0:9001")
        .await?;
    let manager_ip = manager.ip.clone();

    let executor = instances.iter().find(|m| m.tag == "executor").unwrap();
    executor
        .start_r0vm(&format!(
            "--worker=execute --addr {manager_ip}:9000 --po2={}",
            args.po2
        ))
        .await?;

    let mut join_set = tokio::task::JoinSet::new();
    for worker in instances.into_iter().filter(|i| i.tag == "worker") {
        let args = format!(
            "\
            --worker=\"prove-segment,prove-keccak,lift,join,union,resolve\" \
            --addr {manager_ip}:9000\
            "
        );
        join_set.spawn(async move { worker.start_r0vm(&args).await });
    }
    while let Some(res) = join_set.join_next().await {
        res.unwrap()?;
    }

    // println!("jaeger ui = http://{manager_ip}:16686/");
    println!("export BONSAI_API_URL=http://{manager_ip}:9001");
    println!("export BONSAI_API_KEY=anything");
    println!(
        "ssh to manager = `ssh -i {}.pem ubuntu@{manager_ip}`",
        args.cluster_name
    );

    Ok(())
}
