use std::{
    collections::{BTreeMap, BTreeSet},
    iter::Chain,
    vec::IntoIter,
};

use anyhow::{ensure, Result};
use semver::Version;
use serde_valid::{
    validation::{Error as ValidationError, Errors as ValidationErrors},
    Validate,
};

pub mod aliases;
pub mod profile;
pub mod profile_settings;
pub mod repo;
pub mod traits;

pub use aliases::*;
pub use profile::*;
pub use profile_settings::*;
pub use repo::*;
pub use traits::*;










