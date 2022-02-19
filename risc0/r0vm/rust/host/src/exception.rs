use std::fmt::{self, Display};

#[derive(Debug)]
pub struct Exception {
    pub(crate) what: String,
}

impl Display for Exception {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        f.write_str(&self.what)
    }
}

impl std::error::Error for Exception {}

impl Exception {
    pub fn new(what: &str) -> Self {
        Exception {
            what: what.to_string(),
        }
    }

    pub fn what(&self) -> &str {
        &self.what
    }
}
