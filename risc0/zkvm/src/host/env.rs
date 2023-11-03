use anyhow::anyhow;
use std::path::PathBuf;

/// Return the requested pprof profile path, set via the RISC0_PPROF_OUT environment variable.
pub(crate) fn pprof_path() -> Option<PathBuf> {
    match std::env::var("RISC0_PPROF_OUT") {
        Ok(path) => {
            log::debug!("pprof output path set to: {path}");
            Some(PathBuf::from(path))
        }
        Err(std::env::VarError::NotPresent) => None,
        Err(std::env::VarError::NotUnicode(_)) => {
            log::warn!("Environment variable RISC0_PPROF_OUT is malformed");
            None
        }
    }
}

/// Write the pprof profile
pub(crate) fn write_pprof_file(profile: &[u8]) -> anyhow::Result<()> {
    let path = pprof_path().ok_or(anyhow!("no path set to write pprof profile"))?;
    log::debug!("writing profile to: {}", path.display());
    std::fs::write(path, profile)?;
    Ok(())
}
