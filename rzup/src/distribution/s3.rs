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

use crate::components::Component;
use crate::distribution::{
    download_bytes, download_json,
    sha2::{Sha256Digest, Sha256Writer},
    signature::{PublicKey, Signature},
    DistributionPlatform, ProgressWriter,
};
#[cfg(feature = "publish")]
use crate::distribution::{signature::PrivateKey, upload_bytes, ProgressReader};
use crate::env::Environment;
#[cfg(feature = "publish")]
use crate::{AwsCredentials, Platform};
use crate::{BaseUrls, Result, RzupError, RzupEvent, TransferKind};

use semver::Version;
use serde::{Deserialize, Serialize};
use serde_with::{serde_as, DisplayFromStr};

use std::collections::BTreeMap;
use std::fmt;
#[cfg(feature = "publish")]
use std::{collections::btree_map::Entry, fs::File, io::Seek as _, io::SeekFrom, path::Path};

#[derive(Serialize, Deserialize, Clone, PartialEq, Eq, Hash, PartialOrd, Ord)]
#[serde(transparent)]
struct TargetTriple(String);

impl fmt::Display for TargetTriple {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        self.0.fmt(f)
    }
}

#[serde_as]
#[derive(Serialize, Deserialize)]
struct Artifact {
    #[serde_as(as = "Vec<DisplayFromStr>")]
    sha256_blobs: Vec<Sha256Digest>,
}

#[derive(Serialize, Deserialize, Default)]
struct TargetSpecificRelease {
    artifacts: BTreeMap<TargetTriple, Artifact>,
}

#[derive(Serialize, Deserialize)]
struct TargetAgnosticRelease {
    artifact: Artifact,
}

#[derive(Serialize, Deserialize)]
#[serde(rename_all = "snake_case")]
enum Release {
    TargetSpecific(TargetSpecificRelease),
    TargetAgnostic(TargetAgnosticRelease),
}

#[serde_as]
#[derive(Serialize, Deserialize)]
struct DistributionManifest {
    releases: BTreeMap<semver::Version, Release>,
    latest_version: semver::Version,
    #[serde_as(as = "Option<DisplayFromStr>")]
    #[serde(skip_serializing_if = "Option::is_none")]
    signature: Option<Signature>,
}

impl DistributionManifest {
    #[cfg(feature = "publish")]
    fn new(latest_version: Version) -> Self {
        Self {
            latest_version,
            releases: Default::default(),
            signature: None,
        }
    }

    #[cfg(feature = "install")]
    fn verify(&mut self, public_key: &PublicKey) -> Result<()> {
        let signature = self.signature.take().ok_or_else(|| {
            RzupError::Other("distribution_manifest.json missing signature".into())
        })?;

        let manifest_json =
            serde_json::to_vec(self).expect("serde_json should serialize successfully to memory");

        public_key.verify(&manifest_json, &signature)?;

        Ok(())
    }

    #[cfg(not(feature = "install"))]
    fn verify(&mut self, _public_key: &PublicKey) -> Result<()> {
        Err(RzupError::Other("install feature not enabled".into()))
    }

    #[cfg(feature = "publish")]
    fn sign(&mut self, private_key: &PrivateKey) -> Result<()> {
        let manifest_json =
            serde_json::to_vec(self).expect("serde_json should serialize successfully to memory");

        let signature = private_key.sign(&manifest_json);
        self.signature = Some(signature);
        Ok(())
    }
}

#[cfg(feature = "publish")]
fn validate_tar_xz(file: &mut File) -> Result<()> {
    use liblzma::bufread::XzDecoder;
    use std::io::BufReader;
    use tar::Archive;

    let mut ar = Archive::new(XzDecoder::new_parallel(BufReader::new(file)));
    let entries = ar
        .entries()
        .map_err(|e| RzupError::Other(format!("invalid tar.xz file: {e}")))?
        .collect::<std::io::Result<Vec<_>>>()
        .map_err(|e| RzupError::Other(format!("invalid tar.xz file: {e}")))?;
    if entries.is_empty() {
        return Err(RzupError::Other("invalid tar.xz file: empty".into()));
    }
    Ok(())
}

#[cfg(feature = "publish")]
const S3_REGION: &str = "us-west-2";

#[cfg(feature = "publish")]
fn sign_s3_request(
    creds: &AwsCredentials,
    req: &mut http::Request<reqwest::blocking::Body>,
) -> Result<()> {
    use aws_sigv4::http_request::{sign, SignableBody, SignableRequest, SigningSettings};
    use aws_sigv4::sign::v4;

    let identity = creds.clone().into();
    let signing_settings = SigningSettings::default();
    let signing_params = v4::SigningParams::builder()
        .identity(&identity)
        .region(S3_REGION)
        .name("s3")
        .time(std::time::SystemTime::now())
        .settings(signing_settings)
        .build()
        .unwrap()
        .into();

    let mut headers = vec![];
    for (k, v) in req.headers() {
        headers.push((
            k.as_str(),
            v.to_str()
                .map_err(|e| RzupError::Other(format!("unsignable request header {k}: {e}")))?,
        ));
    }

    let signable_request = SignableRequest::new(
        req.method().as_str(),
        req.uri().to_string(),
        headers.into_iter(),
        SignableBody::UnsignedPayload,
    )
    .map_err(|e| RzupError::Other(format!("error signing HTTP request: {e}")))?;

    let (signing_instructions, _signature) = sign(signable_request, &signing_params)
        .map_err(|e| RzupError::Other(format!("error signing HTTP request: {e}")))?
        .into_parts();
    signing_instructions.apply_to_request_http1x(req);

    req.headers_mut().insert(
        "x-amz-content-sha256",
        http::HeaderValue::from_static("UNSIGNED-PAYLOAD"),
    );

    Ok(())
}

#[cfg(feature = "publish")]
fn is_object_not_found_error(error: &RzupError) -> bool {
    let error_str = error.to_string();

    error_str.contains("<Code>AccessDenied</Code>") || error_str.contains("<Code>NoSuchKey</Code>")
}

pub struct S3Bucket<'a> {
    base_urls: &'a BaseUrls,
}

impl<'a> S3Bucket<'a> {
    pub fn new(base_urls: &'a BaseUrls) -> Self {
        Self { base_urls }
    }

    fn get_distribution_manifest(
        &self,
        env: &Environment,
        component: &Component,
    ) -> Result<DistributionManifest> {
        env.emit(RzupEvent::Debug {
            message: format!("Fetching distribution information for {component}"),
        });

        let base_url = &self.base_urls.s3_base_url;
        let url = format!("{base_url}/rzup/components/{component}/distribution_manifest.json");
        let mut manifest: DistributionManifest = download_json(&url, &None)?;
        manifest.verify(env.public_key())?;

        Ok(manifest)
    }

    #[cfg(feature = "publish")]
    fn validate_upload(
        &self,
        version: &Version,
        platform: Option<Platform>,
        manifest: &DistributionManifest,
    ) -> Result<()> {
        if let Some(release) = manifest.releases.get(version) {
            match (release, platform) {
                (Release::TargetAgnostic(_), Some(_)) => {
                    return Err(RzupError::Other(
                        "target-agnostic artifact already exists for this release version, \
                                add --force flag to overwrite"
                            .into(),
                    ));
                }
                (Release::TargetSpecific(_), None) => {
                    return Err(RzupError::Other(
                        "target-specific artifact already exists for this release version, \
                                add --force flag to overwrite"
                            .into(),
                    ));
                }
                (Release::TargetAgnostic(_), None) => {
                    return Err(RzupError::Other(
                        "artifact already exists for this release, add --force flag to \
                                overwrite"
                            .into(),
                    ));
                }
                (Release::TargetSpecific(TargetSpecificRelease { artifacts }), Some(platform))
                    if artifacts.contains_key(&TargetTriple(platform.target_triple())) =>
                {
                    return Err(RzupError::Other(
                        "artifact already exists for this release and target, \
                                add --force flag to overwrite"
                            .into(),
                    ));
                }
                _ => {}
            }
        }
        Ok(())
    }

    #[cfg(feature = "publish")]
    fn update_manifest_with_artifact(
        &self,
        version: &Version,
        platform: Option<Platform>,
        sha256: Sha256Digest,
        manifest: &mut DistributionManifest,
    ) {
        let artifact = Artifact {
            sha256_blobs: vec![sha256],
        };
        match manifest.releases.entry(version.clone()) {
            Entry::Occupied(mut entry) => {
                let existing_release = entry.get_mut();
                match (existing_release, platform) {
                    (
                        Release::TargetSpecific(TargetSpecificRelease { artifacts }),
                        Some(platform),
                    ) => {
                        artifacts.insert(TargetTriple(platform.target_triple()), artifact);
                    }
                    (existing_release @ Release::TargetAgnostic(_), Some(platform)) => {
                        let mut artifacts = BTreeMap::new();
                        artifacts.insert(TargetTriple(platform.target_triple()), artifact);
                        *existing_release =
                            Release::TargetSpecific(TargetSpecificRelease { artifacts });
                    }
                    (existing_release @ Release::TargetSpecific(_), None)
                    | (existing_release @ Release::TargetAgnostic(_), None) => {
                        *existing_release =
                            Release::TargetAgnostic(TargetAgnosticRelease { artifact });
                    }
                }
            }
            Entry::Vacant(entry) => {
                entry.insert(if let Some(platform) = platform {
                    let mut artifacts = BTreeMap::new();
                    artifacts.insert(TargetTriple(platform.target_triple()), artifact);
                    Release::TargetSpecific(TargetSpecificRelease { artifacts })
                } else {
                    Release::TargetAgnostic(TargetAgnosticRelease { artifact })
                });
            }
        }
    }

    #[cfg(feature = "publish")]
    fn upload_manifest(
        &self,
        component: &Component,
        creds: &AwsCredentials,
        private_key: &PrivateKey,
        mut manifest: DistributionManifest,
    ) -> Result<()> {
        manifest.sign(private_key)?;

        let manifest_json = serde_json::to_vec(&manifest)
            .expect("serde_json should serialize successfully to memory");

        let manifest_json_len = manifest_json.len() as u64;
        let base_url = &self.base_urls.s3_base_url;
        let upload_url =
            format!("{base_url}/rzup/components/{component}/distribution_manifest.json");
        upload_bytes(
            &upload_url,
            |req| sign_s3_request(creds, req),
            std::io::Cursor::new(manifest_json),
            manifest_json_len,
        )?;
        Ok(())
    }

    #[cfg(feature = "publish")]
    #[allow(clippy::too_many_arguments)]
    fn upload_artifact(
        &self,
        env: &Environment,
        component: &Component,
        version: &Version,
        creds: &AwsCredentials,
        data_stream: File,
        data_length: u64,
        sha256: &Sha256Digest,
    ) -> Result<()> {
        let base_url = &self.base_urls.s3_base_url;
        let upload_url = format!("{base_url}/rzup/components/{component}/sha256/{sha256}");
        let upload_id = format!("{component}/{sha256}");

        env.emit(RzupEvent::TransferStarted {
            kind: TransferKind::Upload,
            id: upload_id.clone(),
            version: Some(version.to_string()),
            url: Some(upload_url.clone()),
            len: Some(data_length),
        });
        let (send, recv) = std::sync::mpsc::channel();
        let data_stream = ProgressReader::new(upload_id.clone(), send, data_stream);
        std::thread::scope(move |scope| -> Result<()> {
            scope.spawn(move || {
                while let Ok(r) = recv.recv() {
                    env.emit(r);
                }
            });

            upload_bytes(
                &upload_url,
                |req| sign_s3_request(creds, req),
                data_stream,
                data_length,
            )?;

            Ok(())
        })?;

        env.emit(RzupEvent::TransferCompleted {
            kind: TransferKind::Upload,
            id: upload_id,
            version: Some(version.to_string()),
        });

        Ok(())
    }

    #[cfg(feature = "publish")]
    pub fn publish_upload(
        &self,
        env: &Environment,
        component: &Component,
        version: &Version,
        platform: Option<Platform>,
        payload: &Path,
        force: bool,
    ) -> Result<()> {
        let creds = env
            .get_aws_creds()
            .ok_or_else(|| RzupError::Other("missing AWS S3 credentials".into()))?;

        env.emit(RzupEvent::Print {
            message: "Getting private key from AWS".into(),
        });
        let private_key = env.get_private_key()?;

        env.emit(RzupEvent::Print {
            message: "Reading distribution_manifest.json".into(),
        });
        let mut manifest = match self.get_distribution_manifest(env, component) {
            Ok(manifest) => manifest,
            Err(error) => {
                if is_object_not_found_error(&error) {
                    DistributionManifest::new(version.clone())
                } else {
                    return Err(error);
                }
            }
        };

        // Check if we are going to replace something by uploading
        if !force {
            self.validate_upload(version, platform, &manifest)?;
        }

        env.emit(RzupEvent::Print {
            message: "Validating artifact".into(),
        });
        let mut data_stream = File::open(payload)?;
        validate_tar_xz(&mut data_stream)?;
        data_stream.seek(SeekFrom::Start(0))?;

        // Calculate the sha256
        env.emit(RzupEvent::Print {
            message: format!("Calculating sha256 for {component} {version}"),
        });

        let data_length = data_stream.metadata()?.len();
        let sha256 = Sha256Digest::calculate_for_file(&mut data_stream)?;
        data_stream.seek(SeekFrom::Start(0))?;

        // Upload the artifact to S3
        self.upload_artifact(
            env,
            component,
            version,
            &creds,
            data_stream,
            data_length,
            &sha256,
        )?;

        // Update the manifest
        self.update_manifest_with_artifact(version, platform, sha256, &mut manifest);

        env.emit(RzupEvent::Print {
            message: format!("Updating distribution_manifest.json for {component} {version}"),
        });
        self.upload_manifest(component, &creds, &private_key, manifest)?;

        Ok(())
    }

    #[cfg(feature = "publish")]
    pub fn publish_set_latest(
        &self,
        env: &Environment,
        component: &Component,
        version: &Version,
    ) -> Result<()> {
        let creds = env
            .get_aws_creds()
            .ok_or_else(|| RzupError::Other("missing AWS S3 credentials".into()))?;
        let private_key = env.get_private_key()?;

        let mut manifest = self.get_distribution_manifest(env, component)?;
        if !manifest.releases.contains_key(version) {
            return Err(RzupError::Other(format!(
                "release for {component} at version {version} not found"
            )));
        }
        manifest.latest_version = version.clone();

        env.emit(RzupEvent::Print {
            message: format!(
                "Updating distribution_manifest.json for {component}, \
                setting latest-version to {version}"
            ),
        });
        self.upload_manifest(component, &creds, &private_key, manifest)?;

        Ok(())
    }
}

impl<'a> DistributionPlatform for S3Bucket<'a> {
    fn latest_version(&self, env: &Environment, component: &Component) -> Result<Version> {
        env.emit(RzupEvent::Debug {
            message: format!("Fetching latest version for {component}"),
        });

        let manifest = self.get_distribution_manifest(env, component)?;

        Ok(manifest.latest_version)
    }

    fn download_version(
        &self,
        env: &Environment,
        component: &Component,
        version: &Version,
    ) -> Result<()> {
        let manifest = self.get_distribution_manifest(env, component)?;

        let Some(release) = manifest.releases.get(version) else {
            env.emit(RzupEvent::InstallationFailed {
                id: component.to_string(),
                version: version.to_string(),
            });
            return Err(RzupError::InvalidVersion(format!(
                "{version} is not available for {component}",
            )));
        };

        let platform = env.platform();
        let artifact = match release {
            Release::TargetSpecific(release) => {
                let target_triple = TargetTriple(platform.target_triple());

                let Some(artifact) = release.artifacts.get(&target_triple) else {
                    env.emit(RzupEvent::InstallationFailed {
                        id: component.to_string(),
                        version: version.to_string(),
                    });
                    return Err(RzupError::UnsupportedPlatform(format!(
                        "{component} is not available for platform {target_triple}",
                    )));
                };
                artifact
            }
            Release::TargetAgnostic(release) => &release.artifact,
        };

        let archive_name = component.archive_name(platform)?;
        if artifact.sha256_blobs.is_empty() {
            return Err(RzupError::Other("release contains no artifacts".into()));
        }
        if artifact.sha256_blobs.len() > 1 {
            return Err(RzupError::Other(
                "release contains multiple artifacts, update rzup".into(),
            ));
        }
        let artifact_sha256 = &artifact.sha256_blobs[0];

        let download_path = env.tmp_dir().join(archive_name);
        let mut download_file = std::fs::OpenOptions::new()
            .write(true)
            .create(true)
            .truncate(true)
            .open(&download_path)?;

        let base_url = &self.base_urls.s3_base_url;
        let download_url =
            format!("{base_url}/rzup/components/{component}/sha256/{artifact_sha256}");
        let mut resp = download_bytes(&download_url, &None)?;

        env.emit(RzupEvent::TransferStarted {
            kind: TransferKind::Download,
            id: component.to_string(),
            version: Some(version.to_string()),
            url: Some(download_url.clone()),
            len: resp.content_length(),
        });

        let mut writer = Sha256Writer::new(ProgressWriter::new(
            component.to_string(),
            env,
            &mut download_file,
        ));
        resp.copy_to(&mut writer)
            .map_err(|e| RzupError::Other(format!("Failed to download file: {e}")))?;

        let download_sha = writer.finish();

        if &download_sha != artifact_sha256 {
            env.emit(RzupEvent::InstallationFailed {
                id: component.to_string(),
                version: version.to_string(),
            });
            return Err(RzupError::Sha256Mismatch {
                expected: artifact_sha256.to_string(),
                actual: download_sha.to_string(),
            });
        }

        env.emit(RzupEvent::TransferCompleted {
            kind: TransferKind::Download,
            id: component.to_string(),
            version: Some(version.to_string()),
        });

        Ok(())
    }
}
