use crate::components::Component;

#[derive(Debug)]
pub(crate) struct R0Vm;

impl Component for R0Vm {
    fn id(&self) -> &'static str {
        "r0vm"
    }

    fn is_virtual(&self) -> bool {
        true
    }

    fn parent_component(&self) -> Option<&'static str> {
        Some("cargo-risczero")
    }
}
