pub struct NondetRegLayout {
    pub _super: &'static Reg,
}
impl risc0_zkp::layout::Component for NondetRegLayout {
    fn ty_name(&self) -> &'static str {
        "NondetRegLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        Ok(())
    }
}
pub type NondetRegLayout2LayoutArray = [&'static NondetRegLayout; 2];
pub struct OneHotLayout {
    pub _super: &'static NondetRegLayout2LayoutArray,
}
impl risc0_zkp::layout::Component for OneHotLayout {
    fn ty_name(&self) -> &'static str {
        "OneHotLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        Ok(())
    }
}
pub struct TopResultLayout {
    pub _super: &'static NondetRegLayout,
    pub arm0: &'static NondetRegLayout,
    pub arm1: &'static NondetRegLayout,
}
impl risc0_zkp::layout::Component for TopResultLayout {
    fn ty_name(&self) -> &'static str {
        "TopResultLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct TopLayout {
    pub op: &'static NondetRegLayout,
    pub arg1: &'static NondetRegLayout,
    pub arg2: &'static NondetRegLayout,
    pub expected: &'static NondetRegLayout,
    pub _0: &'static OneHotLayout,
    pub result: &'static TopResultLayout,
}
impl risc0_zkp::layout::Component for TopLayout {
    fn ty_name(&self) -> &'static str {
        "TopLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("op", self.op)?;
        v.visit_component("arg1", self.arg1)?;
        v.visit_component("arg2", self.arg2)?;
        v.visit_component("expected", self.expected)?;
        v.visit_component("_0", self._0)?;
        v.visit_component("result", self.result)?;
        Ok(())
    }
}
pub struct _globalLayout {
    pub result: &'static NondetRegLayout,
}
impl risc0_zkp::layout::Component for _globalLayout {
    fn ty_name(&self) -> &'static str {
        "_globalLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("result", self.result)?;
        Ok(())
    }
}
#[derive(Copy, Clone, Debug)]
pub struct NondetRegStruct {
    pub _super: Val,
}
pub type Val2Array = [Val; 2];
pub type NondetRegStruct2Array = [NondetRegStruct; 2];
#[derive(Copy, Clone, Debug)]
pub struct OneHotStruct {
    pub _super: NondetRegStruct2Array,
}
#[derive(Copy, Clone, Debug)]
pub struct TopStruct {}
