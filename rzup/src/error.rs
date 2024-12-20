use thiserror::Error;

#[derive(Debug, Error)]
pub enum RzupError {
    #[error("Component not found: {0}")]
    ComponentNotFound(String),

    #[error("Installation failed: {0}")]
    InstallationFailed(String),

    #[error("Invalid version: {0}")]
    InvalidVersion(String),

    #[error("IO error: {0}")]
    Io(#[from] std::io::Error),

    #[error("Environment error: {0}")]
    Environment(String),

    #[error(transparent)]
    Other(#[from] anyhow::Error),
}

pub type Result<T> = std::result::Result<T, RzupError>;
