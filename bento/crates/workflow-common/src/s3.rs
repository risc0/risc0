// Copyright (c) 2025 RISC Zero, Inc.
//
// All rights reserved.

use anyhow::{bail, Context, Result};
use aws_sdk_s3::{
    config::{Builder, Credentials, Region},
    operation::{create_bucket::CreateBucketError, head_object::HeadObjectError},
    primitives::ByteStream,
    types::CreateBucketConfiguration,
    Client,
};
use std::path::Path;

/// Object store elf dir
pub const ELF_BUCKET_DIR: &str = "elfs";

/// Object store input dir
pub const INPUT_BUCKET_DIR: &str = "inputs";

/// Guest executor logs dir
pub const EXEC_LOGS_BUCKET_DIR: &str = "exec_logs";

/// Object store receipts dir
pub const RECEIPT_BUCKET_DIR: &str = "receipts";

/// Object store preflight journals dir
pub const PREFLIGHT_JOURNALS_BUCKET_DIR: &str = "preflight_journals";

/// Object store stark receipt dir
pub const STARK_BUCKET_DIR: &str = "stark";

/// Object store receipts groth15 dir
pub const GROTH16_BUCKET_DIR: &str = "groth16";

const MOCK_REGION: &str = "us-west-2";

/// S3 client object
pub struct S3Client {
    bucket: String,
    client: Client,
}

impl S3Client {
    /// Initialize a s3 client from a minio config
    pub async fn from_minio(
        url: &str,
        bucket: &str,
        access_key: &str,
        secret_key: &str,
    ) -> Result<Self> {
        let cred = Credentials::new(access_key, secret_key, None, None, "loaded-from-custom-env");

        let s3_config = Builder::new()
            .endpoint_url(url)
            .credentials_provider(cred)
            .behavior_version_latest()
            .region(Region::new(MOCK_REGION))
            .force_path_style(true)
            .build();

        let client = aws_sdk_s3::Client::from_conf(s3_config);

        // Attempt to provision the bucket if it does not exist
        let cfg = CreateBucketConfiguration::builder().build();
        let res = client
            .create_bucket()
            .create_bucket_configuration(cfg)
            .bucket(bucket)
            .send()
            .await;

        if let Err(err) = res {
            let Some(service_err) = err.as_service_error() else {
                bail!(format!("Minio SDK error: {err:?}"));
            };
            match service_err {
                CreateBucketError::BucketAlreadyOwnedByYou(_) => {}
                _ => bail!(format!("Failed to create bucket: {err:?}")),
            }
        }

        Ok(Self {
            bucket: bucket.to_string(),
            client,
        })
    }

    /// Reads a s3 object encoded with bincode
    pub async fn read_from_s3<T>(&self, key: &str) -> Result<T>
    where
        T: serde::de::DeserializeOwned,
    {
        let result = self
            .client
            .get_object()
            .bucket(&self.bucket)
            .key(key)
            .send()
            .await?;

        let encoded = result.body.collect().await?.to_vec();
        bincode::deserialize(&encoded).context("Failed to deserialize s3 object")
    }

    /// Reads a s3 object to byte buffer
    pub async fn read_buf_from_s3(&self, key: &str) -> Result<Vec<u8>> {
        let result = self
            .client
            .get_object()
            .bucket(&self.bucket)
            .key(key)
            .send()
            .await?;

        Ok(result.body.collect().await?.to_vec())
    }

    /// Write a bincode serializable object to S3
    pub async fn write_to_s3<T>(&self, key: &str, obj: T) -> Result<()>
    where
        T: serde::Serialize,
    {
        let bytes = bincode::serialize(&obj)?;
        let data_stream = ByteStream::from(bytes);
        self.client
            .put_object()
            .bucket(&self.bucket)
            .key(key)
            .body(data_stream)
            .send()
            .await?;
        Ok(())
    }

    /// Write a buffer to S3
    pub async fn write_buf_to_s3(&self, key: &str, bytes: Vec<u8>) -> Result<()> {
        let data_stream = ByteStream::from(bytes);
        self.client
            .put_object()
            .bucket(&self.bucket)
            .key(key)
            .body(data_stream)
            .send()
            .await?;
        Ok(())
    }

    pub async fn write_file_to_s3(&self, key: &str, in_path: &Path) -> Result<()> {
        let data_stream = ByteStream::read_from().path(in_path).build().await?;
        self.client
            .put_object()
            .bucket(&self.bucket)
            .key(key)
            .body(data_stream)
            .send()
            .await?;
        Ok(())
    }

    pub async fn object_exists(&self, key: &str) -> Result<bool> {
        match self.client.head_bucket().bucket(&self.bucket).send().await {
            Ok(_) => match self
                .client
                .head_object()
                .bucket(&self.bucket)
                .key(key)
                .send()
                .await
            {
                Ok(_) => Ok(true),
                Err(err) => match err.into_service_error() {
                    HeadObjectError::NotFound(_) => Ok(false),
                    err => Err(err.into()),
                },
            },
            Err(err) => Err(err.into()),
        }
    }
}
