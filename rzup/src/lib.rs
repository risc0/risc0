#[cfg(feature = "cli")]
pub mod cli;
mod components;
mod distribution;
mod env;
pub mod error;
mod settings;

use crate::components::registry::ComponentRegistry;
use crate::env::Environment;
use crate::settings::Settings;
pub use error::{Result, RzupError};
use semver::Version;
use std::collections::HashMap;
use std::path::PathBuf;

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
    SettingsCreated {
        path: PathBuf,
    },
    Uninstalled {
        id: String,
        version: String,
    },
    Debug {
        message: String,
    },
}

pub struct Rzup {
    environment: Environment,
    registry: ComponentRegistry,
}

impl Rzup {
    pub fn new() -> Result<Self> {
        let environment = Environment::new()?;
        let mut registry = ComponentRegistry::new(&environment)?;
        Self::initialize_settings(&environment, &mut registry)?;
        registry.scan_environment(&environment)?;

        Ok(Self {
            environment,
            registry,
        })
    }

    pub fn with_root<P: Into<PathBuf>>(root: P) -> Result<Self> {
        let environment = Environment::with_root(root)?;
        let mut registry = ComponentRegistry::new(&environment)?;
        Self::initialize_settings(&environment, &mut registry)?;
        registry.scan_environment(&environment)?;

        Ok(Self {
            environment,
            registry,
        })
    }

    fn initialize_settings(
        environment: &Environment,
        registry: &mut ComponentRegistry,
    ) -> Result<()> {
        if !environment.settings_path().exists() {
            environment.emit(RzupEvent::SettingsCreated {
                path: environment.settings_path().to_path_buf(),
            });
            registry.settings().save(environment.settings_path())?;
        }
        Ok(())
    }

    pub fn set_event_handler<F>(&mut self, handler: F)
    where
        F: Fn(RzupEvent) + Send + Sync + 'static,
    {
        self.environment.set_event_handler(handler);
    }

    pub fn install_all(&mut self, force: bool) -> Result<()> {
        self.registry.install_all(&self.environment, force)?;
        self.registry.scan_environment(&self.environment)?;
        Ok(())
    }

    pub fn install_component(
        &mut self,
        component: &str,
        version: Option<Version>,
        force: bool,
    ) -> Result<()> {
        self.registry
            .install_component(&self.environment, component, version, force)?;
        self.registry.scan_environment(&self.environment)?;
        Ok(())
    }

    pub fn uninstall_component(&mut self, component: &str, version: Version) -> Result<()> {
        self.registry
            .uninstall_component(&self.environment, component, version)?;
        self.registry.scan_environment(&self.environment)?;
        Ok(())
    }

    pub fn environment(&self) -> &Environment {
        &self.environment
    }

    pub fn settings(&self) -> &Settings {
        self.registry.settings()
    }

    pub fn latest_version(&self, component_id: &str) -> Result<Version> {
        let component = self.registry.components.get(component_id).unwrap();
        component.get_latest_version(self.environment())
    }

    pub fn installed_versions(&self, component_id: &str) -> HashMap<Version, PathBuf> {
        self.registry
            .get_component_versions(component_id)
            .unwrap()
            .versions
            .clone()
    }

    pub fn is_installed(&self, component_id: &str, version: &Version) -> bool {
        self.installed_versions(component_id).contains_key(version)
    }
}
