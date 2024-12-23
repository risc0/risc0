#[derive(Debug)]
pub enum RzupEvent {
    DownloadStarted {
        id: String,
        version: String,
        url: String,
    },
    DownloadCompleted {
        id: String,
        version: String,
    },
    InstallationStarted {
        id: String,
        version: String,
    },
    InstallationCompleted {
        id: String,
        version: String,
    },
    ComponentAlreadyInstalled {
        id: String,
        version: String,
    },
    InstallationFailed {
        id: String,
        version: String,
    },
    Uninstalled {
        id: String,
        version: String,
    },
    CheckUpdates {
        id: Option<String>, // none means finished checking
    },
    Debug {
        message: String,
    },
}
