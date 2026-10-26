// Copyright 2026 RISC Zero, Inc.
//
// Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
// http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
// http://opensource.org/licenses/MIT>, at your option. This file may not be
// copied, modified, or distributed except according to those terms.
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

use crate::error::{Result, RzupError};
use reqwest::{IntoUrl, Url, blocking::Client};
use std::time::Duration;

/// 3 hour HTTP timeout, internet can be slow and components can be up to 5gb.
const HTTP_TIMEOUT_SECS: u64 = 3 * 60 * 60;

/// How many times a broken transfer is resumed before giving up.
const MAX_RESUMES: u32 = 5;

fn http_client_get(
    url: &Url,
    bearer_token: &Option<String>,
) -> Result<reqwest::blocking::Response> {
    http_client_get_from(url, bearer_token, None)
}

/// GET `url`, asking for the body from byte `offset` on when one is given.
fn http_client_get_from(
    url: &Url,
    bearer_token: &Option<String>,
    offset: Option<u64>,
) -> Result<reqwest::blocking::Response> {
    let client = Client::builder()
        .timeout(Duration::from_secs(HTTP_TIMEOUT_SECS))
        .build()
        .map_err(|e| RzupError::Other(format!("Failed to create HTTP client: {e}")))?;

    let mut builder = client.get(url.clone()).header("User-Agent", "rzup");

    if let Some(token) = bearer_token {
        builder = builder.header("Authorization", format!("Bearer {token}"));
    }

    if let Some(offset) = offset {
        builder = builder.header("Range", format!("bytes={offset}-"));
    }

    builder
        .send()
        .map_err(|e| RzupError::Other(format!("{e:?}: {url}")))
}

/// Copies the body of `response`, which came from GET `url`, into `writer`. When the transfer
/// breaks, the rest is requested again from `url` with an HTTP Range request and the copy
/// continues, up to `MAX_RESUMES` times. The original URL is used rather than the response's
/// final one so that a redirect to a signed URL, as GitHub release assets use, is followed afresh
/// and the bearer token never reaches the redirect target. Before each resume, `on_resume` gets
/// the number of bytes received so far and the error that interrupted the transfer. Returns the
/// number of bytes copied.
pub fn copy_with_resume(
    response: reqwest::blocking::Response,
    url: impl IntoUrl,
    bearer_token: &Option<String>,
    writer: &mut impl std::io::Write,
    mut on_resume: impl FnMut(u64, &std::io::Error),
) -> Result<u64> {
    let url = url
        .into_url()
        .map_err(|e| RzupError::Other(e.to_string()))?;
    let mut reader: Box<dyn std::io::Read> = Box::new(response);
    let mut received = 0u64;
    let mut resumes = 0u32;
    let mut buf = vec![0u8; 64 * 1024];

    loop {
        match reader.read(&mut buf) {
            Ok(0) => return Ok(received),
            Ok(n) => {
                writer.write_all(&buf[..n])?;
                received += n as u64;
            }
            Err(e) => {
                if resumes >= MAX_RESUMES {
                    return Err(RzupError::Other(format!(
                        "Failed to download file after {resumes} resumes: {e:?}: {url}"
                    )));
                }
                resumes += 1;
                on_resume(received, &e);

                let response = http_client_get_from(&url, bearer_token, Some(received))?;
                let status = response.status();
                if status != reqwest::StatusCode::PARTIAL_CONTENT {
                    let host = response.url().host_str().unwrap_or("").to_owned();
                    return Err(RzupError::Other(format!(
                        "Remote error: {host}: expected 206 Partial Content when resuming at \
                        byte {received}, got {status}: {url}"
                    )));
                }
                reader = Box::new(response);
            }
        }
    }
}

fn error_on_status(
    response: reqwest::blocking::Response,
    url: &Url,
) -> Result<reqwest::blocking::Response> {
    let status = response.status();

    if !status.is_success() {
        let host = response.url().host_str().expect("URL has a host");
        let host = host.to_owned();
        let body = response.text().ok();

        Err(RzupError::Other(format!(
            "Remote error: {host}: {status}: {body:?}: {url}"
        )))
    } else {
        Ok(response)
    }
}

pub fn check_for_not_found(url: impl IntoUrl, bearer_token: &Option<String>) -> Result<bool> {
    let url = url
        .into_url()
        .map_err(|e| RzupError::Other(e.to_string()))?;
    let response = http_client_get(&url, bearer_token)?;
    let status = response.status();
    if status == reqwest::StatusCode::NOT_FOUND {
        return Ok(false);
    }
    error_on_status(response, &url)?;
    Ok(true)
}

pub fn download_json<RetT: serde::de::DeserializeOwned>(
    url: impl IntoUrl,
    bearer_token: &Option<String>,
) -> Result<RetT> {
    let url = url
        .into_url()
        .map_err(|e| RzupError::Other(e.to_string()))?;
    let response = http_client_get(&url, bearer_token)?;
    let response = error_on_status(response, &url)?;
    response
        .json()
        .map_err(|e| RzupError::Other(format!("{e:?}: {url}")))
}

pub fn download_text(url: impl IntoUrl, bearer_token: &Option<String>) -> Result<String> {
    let url = url
        .into_url()
        .map_err(|e| RzupError::Other(e.to_string()))?;
    let response = http_client_get(&url, bearer_token)?;
    let response = error_on_status(response, &url)?;
    response
        .text()
        .map_err(|e| RzupError::Other(format!("{e:?}: {url}")))
}

pub fn download_bytes(
    url: impl IntoUrl,
    bearer_token: &Option<String>,
) -> Result<reqwest::blocking::Response> {
    let url = url
        .into_url()
        .map_err(|e| RzupError::Other(e.to_string()))?;
    let response = http_client_get(&url, bearer_token)?;
    let response = error_on_status(response, &url)?;
    Ok(response)
}

#[cfg_attr(not(feature = "publish"), allow(dead_code))]
pub fn upload_bytes<BodyT: std::io::Read + Send + 'static>(
    url: impl IntoUrl,
    signer: impl FnOnce(&mut http::Request<reqwest::blocking::Body>) -> Result<()>,
    body_stream: BodyT,
    content_length: u64,
) -> Result<()> {
    let url = url
        .into_url()
        .map_err(|e| RzupError::Other(e.to_string()))?;

    let client = Client::builder()
        .timeout(Duration::from_secs(HTTP_TIMEOUT_SECS))
        .build()
        .map_err(|e| RzupError::Other(format!("Failed to create HTTP client: {e:?}")))?;

    let mut request = http::Request::builder()
        .method("PUT")
        .uri(url.as_str())
        .header("user-agent", "rzup")
        .header("content-type", "application/octet-stream")
        .header("content-length", content_length.to_string())
        .body(reqwest::blocking::Body::sized(body_stream, content_length))
        .map_err(|e| RzupError::Other(format!("failed to build HTTP request: {e:?}")))?;

    signer(&mut request)?;

    let request = reqwest::blocking::Request::try_from(request).map_err(|e| {
        RzupError::Other(format!(
            "failed to convert to reqwest::blocking::Request: {e:?}"
        ))
    })?;

    let response = client
        .execute(request)
        .map_err(|e| RzupError::Other(format!("{e:?}: {url}")))?;

    error_on_status(response, &url)?;

    Ok(())
}

#[cfg(test)]
mod tests {
    use super::*;
    use std::io::{Read as _, Write as _};
    use std::net::{TcpListener, TcpStream};

    const BODY_LEN: usize = 300_000;
    const CUT_AT: usize = 123_456;

    fn body() -> Vec<u8> {
        (0..BODY_LEN).map(|i| (i % 251) as u8).collect()
    }

    fn read_request(stream: &mut TcpStream) -> String {
        let mut req = Vec::new();
        let mut chunk = [0u8; 1024];
        while !req.windows(4).any(|w| w == b"\r\n\r\n") {
            let n = stream.read(&mut chunk).unwrap();
            assert!(n > 0, "client closed before sending a request");
            req.extend_from_slice(&chunk[..n]);
        }
        String::from_utf8(req).unwrap()
    }

    fn range_offset(request: &str) -> Option<usize> {
        request.lines().find_map(|line| {
            let (name, value) = line.split_once(':')?;
            if !name.eq_ignore_ascii_case("range") {
                return None;
            }
            value
                .trim()
                .strip_prefix("bytes=")?
                .strip_suffix('-')?
                .parse()
                .ok()
        })
    }

    /// Serves `/blob`: the first response claims the whole body but stops after `CUT_AT` bytes and
    /// closes the connection. The second response honours the Range header when `honor_range` is
    /// set, otherwise it is a plain 200 with the whole body.
    fn flaky_server(honor_range: bool) -> String {
        let listener = TcpListener::bind("127.0.0.1:0").unwrap();
        let url = format!("http://{}/blob", listener.local_addr().unwrap());
        std::thread::spawn(move || {
            let body = body();

            let mut stream = listener.accept().unwrap().0;
            let request = read_request(&mut stream);
            assert_eq!(range_offset(&request), None);
            stream
                .write_all(
                    format!(
                        "HTTP/1.1 200 OK\r\nContent-Length: {BODY_LEN}\r\nConnection: close\r\n\r\n"
                    )
                    .as_bytes(),
                )
                .unwrap();
            stream.write_all(&body[..CUT_AT]).unwrap();
            drop(stream);

            let mut stream = listener.accept().unwrap().0;
            let request = read_request(&mut stream);
            let offset = range_offset(&request).expect("second request carries a Range header");
            assert_eq!(offset, CUT_AT);
            if honor_range {
                let rest = &body[offset..];
                stream
                    .write_all(
                        format!(
                            "HTTP/1.1 206 Partial Content\r\nContent-Length: {}\r\n\
                            Content-Range: bytes {offset}-{}/{BODY_LEN}\r\nConnection: close\r\n\r\n",
                            rest.len(),
                            BODY_LEN - 1
                        )
                        .as_bytes(),
                    )
                    .unwrap();
                stream.write_all(rest).unwrap();
            } else {
                stream
                    .write_all(
                        format!(
                            "HTTP/1.1 200 OK\r\nContent-Length: {BODY_LEN}\r\nConnection: close\r\n\r\n"
                        )
                        .as_bytes(),
                    )
                    .unwrap();
                stream.write_all(&body).unwrap();
            }
        });
        url
    }

    #[test]
    fn copy_with_resume_resumes_after_broken_transfer() {
        let url = flaky_server(true);
        let response = download_bytes(&url, &None).unwrap();

        let mut out = Vec::new();
        let mut resumes = Vec::new();
        let copied = copy_with_resume(response, &url, &None, &mut out, |received, _err| {
            resumes.push(received)
        })
        .unwrap();

        assert_eq!(copied, BODY_LEN as u64);
        assert_eq!(out, body());
        assert_eq!(resumes, vec![CUT_AT as u64]);
    }

    #[test]
    fn copy_with_resume_rejects_server_that_ignores_range() {
        let url = flaky_server(false);
        let response = download_bytes(&url, &None).unwrap();

        let mut out = Vec::new();
        let err = copy_with_resume(response, &url, &None, &mut out, |_, _| {}).unwrap_err();

        assert!(
            err.to_string().contains("expected 206 Partial Content"),
            "{err}"
        );
        assert_eq!(out.len(), CUT_AT);
    }
}
