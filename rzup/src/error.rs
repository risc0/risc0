use thiserror::Error;

#[derive(Debug, Error, Clone)]
pub enum RzupError {
    #[error("Component not found: {0}")]
    ComponentNotFound(String),

    #[error("Installation failed: {0}")]
    InstallationFailed(String),

    #[error("Invalid version: {0}")]
    InvalidVersion(String),

    #[error("IO error: {0}")]
    Io(String),

    #[error("Environment error: {0}")]
    Environment(String),

    #[error("{0}")]
    Other(String),

    #[error("Rate Limited: {0}")]
    RateLimited(String),
}

impl From<std::io::Error> for RzupError {
    fn from(e: std::io::Error) -> Self {
        RzupError::Io(e.to_string())
    }
}

impl From<anyhow::Error> for RzupError {
    fn from(e: anyhow::Error) -> Self {
        RzupError::Other(e.to_string())
    }
}

pub type Result<T> = std::result::Result<T, RzupError>;

