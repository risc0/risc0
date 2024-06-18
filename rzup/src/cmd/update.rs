use crate::{
    extension::install::InstallCargoRisczero,
    toolchain::{
        dist::ToolchainRepo,
        install::{InstallToolchain, Installable},
    },
    utils::get_updatable_items,
};

pub fn handle_update() {
    let updateable = get_updatable_items().expect("Error getting updatable items");

    for item in updateable {
        match item.installable {
            Installable::Extension => {
                InstallCargoRisczero {
                    version: Some("latest".to_string()),
                }
                .run()
                .expect("Error during cargo-risczero update");
            }
            Installable::Rust => InstallToolchain {
                toolchain: Some("latest".to_string()),
                repo: ToolchainRepo::Rust,
            }
            .run()
            .expect("Error updating Rust toolchain"),
            Installable::Cpp => InstallToolchain {
                toolchain: Some("latest".to_string()),
                repo: ToolchainRepo::Cpp,
            }
            .run()
            .expect("Error updating C++ toolchain"),
        }
    }
}
