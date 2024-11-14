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
pub type NondetRegLayout23LayoutArray = [&'static NondetRegLayout; 23];
pub struct OneHot_23_Layout {
    pub _super: &'static NondetRegLayout23LayoutArray,
}
impl risc0_zkp::layout::Component for OneHot_23_Layout {
    fn ty_name(&self) -> &'static str {
        "OneHot_23_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        Ok(())
    }
}
pub type NondetRegLayout24LayoutArray = [&'static NondetRegLayout; 24];
pub type NondetRegLayout22LayoutArray = [&'static NondetRegLayout; 22];
pub struct RetTupleLayout {
    pub minor: &'static NondetRegLayout,
    pub arr_d: &'static NondetRegLayout24LayoutArray,
    pub arr_f: &'static NondetRegLayout22LayoutArray,
    pub arr_e: &'static NondetRegLayout22LayoutArray,
    pub arr_c: &'static NondetRegLayout22LayoutArray,
    pub arr_b: &'static NondetRegLayout22LayoutArray,
    pub arr_a: &'static NondetRegLayout22LayoutArray,
    pub major: &'static NondetRegLayout,
    pub rnd: &'static NondetRegLayout,
    pub blk: &'static NondetRegLayout,
    pub midx: &'static NondetRegLayout,
}
impl risc0_zkp::layout::Component for RetTupleLayout {
    fn ty_name(&self) -> &'static str {
        "RetTupleLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("minor", self.minor)?;
        v.visit_component("arr_d", self.arr_d)?;
        v.visit_component("arr_f", self.arr_f)?;
        v.visit_component("arr_e", self.arr_e)?;
        v.visit_component("arr_c", self.arr_c)?;
        v.visit_component("arr_b", self.arr_b)?;
        v.visit_component("arr_a", self.arr_a)?;
        v.visit_component("major", self.major)?;
        v.visit_component("rnd", self.rnd)?;
        v.visit_component("blk", self.blk)?;
        v.visit_component("midx", self.midx)?;
        Ok(())
    }
}
pub struct ToBits_22_Layout {
    pub _super: &'static NondetRegLayout22LayoutArray,
}
impl risc0_zkp::layout::Component for ToBits_22_Layout {
    fn ty_name(&self) -> &'static str {
        "ToBits_22_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        Ok(())
    }
}
pub struct Xor5wordsResult_0__0_Layout {
    pub xor_abc: &'static NondetRegLayout22LayoutArray,
    pub unpack_a: &'static ToBits_22_Layout,
    pub unpack_b: &'static ToBits_22_Layout,
    pub unpack_c: &'static ToBits_22_Layout,
    pub unpack_d: &'static ToBits_22_Layout,
    pub unpack_e: &'static ToBits_22_Layout,
}
impl risc0_zkp::layout::Component for Xor5wordsResult_0__0_Layout {
    fn ty_name(&self) -> &'static str {
        "Xor5wordsResult_0__0_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("xor_abc", self.xor_abc)?;
        v.visit_component("unpack_a", self.unpack_a)?;
        v.visit_component("unpack_b", self.unpack_b)?;
        v.visit_component("unpack_c", self.unpack_c)?;
        v.visit_component("unpack_d", self.unpack_d)?;
        v.visit_component("unpack_e", self.unpack_e)?;
        Ok(())
    }
}
pub struct Xor5wordsMinor0_0_Layout {
    pub _super: &'static RetTupleLayout,
    pub result: &'static NondetRegLayout,
    pub _0: &'static Xor5wordsResult_0__0_Layout,
}
impl risc0_zkp::layout::Component for Xor5wordsMinor0_0_Layout {
    fn ty_name(&self) -> &'static str {
        "Xor5wordsMinor0_0_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("result", self.result)?;
        v.visit_component("_0", self._0)?;
        Ok(())
    }
}
pub type NondetRegLayout21LayoutArray = [&'static NondetRegLayout; 21];
pub struct ToBits_21_Layout {
    pub _super: &'static NondetRegLayout21LayoutArray,
}
impl risc0_zkp::layout::Component for ToBits_21_Layout {
    fn ty_name(&self) -> &'static str {
        "ToBits_21_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        Ok(())
    }
}
pub struct Xor5wordsResult_0__1_Layout {
    pub unpack_a: &'static ToBits_21_Layout,
    pub xor_abc: &'static NondetRegLayout21LayoutArray,
    pub unpack_b: &'static ToBits_21_Layout,
    pub unpack_c: &'static ToBits_21_Layout,
    pub unpack_d: &'static ToBits_21_Layout,
    pub unpack_e: &'static ToBits_21_Layout,
}
impl risc0_zkp::layout::Component for Xor5wordsResult_0__1_Layout {
    fn ty_name(&self) -> &'static str {
        "Xor5wordsResult_0__1_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("unpack_a", self.unpack_a)?;
        v.visit_component("xor_abc", self.xor_abc)?;
        v.visit_component("unpack_b", self.unpack_b)?;
        v.visit_component("unpack_c", self.unpack_c)?;
        v.visit_component("unpack_d", self.unpack_d)?;
        v.visit_component("unpack_e", self.unpack_e)?;
        Ok(())
    }
}
pub struct Xor5wordsMinor1_0_Layout {
    pub _super: &'static RetTupleLayout,
    pub result: &'static NondetRegLayout,
    pub _0: &'static Xor5wordsResult_0__1_Layout,
}
impl risc0_zkp::layout::Component for Xor5wordsMinor1_0_Layout {
    fn ty_name(&self) -> &'static str {
        "Xor5wordsMinor1_0_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("result", self.result)?;
        v.visit_component("_0", self._0)?;
        Ok(())
    }
}
pub struct Xor5wordsResult_0__2_Layout {
    pub unpack_a: &'static ToBits_21_Layout,
    pub xor_abc: &'static NondetRegLayout21LayoutArray,
    pub unpack_b: &'static ToBits_21_Layout,
    pub unpack_c: &'static ToBits_21_Layout,
    pub unpack_d: &'static ToBits_21_Layout,
    pub unpack_e: &'static ToBits_21_Layout,
}
impl risc0_zkp::layout::Component for Xor5wordsResult_0__2_Layout {
    fn ty_name(&self) -> &'static str {
        "Xor5wordsResult_0__2_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("unpack_a", self.unpack_a)?;
        v.visit_component("xor_abc", self.xor_abc)?;
        v.visit_component("unpack_b", self.unpack_b)?;
        v.visit_component("unpack_c", self.unpack_c)?;
        v.visit_component("unpack_d", self.unpack_d)?;
        v.visit_component("unpack_e", self.unpack_e)?;
        Ok(())
    }
}
pub struct Xor5wordsMinor2_0_Layout {
    pub _super: &'static RetTupleLayout,
    pub result: &'static NondetRegLayout,
    pub _0: &'static Xor5wordsResult_0__2_Layout,
}
impl risc0_zkp::layout::Component for Xor5wordsMinor2_0_Layout {
    fn ty_name(&self) -> &'static str {
        "Xor5wordsMinor2_0_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("result", self.result)?;
        v.visit_component("_0", self._0)?;
        Ok(())
    }
}
pub type NondetRegLayout9LayoutArray = [&'static NondetRegLayout; 9];
pub struct Xor5wordsMinor3_0_Layout {
    pub _super: &'static RetTupleLayout,
    pub _0: &'static NondetRegLayout,
    pub inp_c: &'static NondetRegLayout22LayoutArray,
    pub inp_b: &'static NondetRegLayout22LayoutArray,
    pub inp_a: &'static NondetRegLayout22LayoutArray,
    pub tmp_1: &'static NondetRegLayout9LayoutArray,
    pub _1: &'static NondetRegLayout,
    pub _2: &'static NondetRegLayout,
}
impl risc0_zkp::layout::Component for Xor5wordsMinor3_0_Layout {
    fn ty_name(&self) -> &'static str {
        "Xor5wordsMinor3_0_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("_0", self._0)?;
        v.visit_component("inp_c", self.inp_c)?;
        v.visit_component("inp_b", self.inp_b)?;
        v.visit_component("inp_a", self.inp_a)?;
        v.visit_component("tmp_1", self.tmp_1)?;
        v.visit_component("_1", self._1)?;
        v.visit_component("_2", self._2)?;
        Ok(())
    }
}
pub struct Xor5wordsMajor_0__SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static Xor5wordsMinor0_0_Layout,
    pub arm1: &'static Xor5wordsMinor1_0_Layout,
    pub arm2: &'static Xor5wordsMinor2_0_Layout,
    pub arm3: &'static Xor5wordsMinor3_0_Layout,
}
impl risc0_zkp::layout::Component for Xor5wordsMajor_0__SuperLayout {
    fn ty_name(&self) -> &'static str {
        "Xor5wordsMajor_0__SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        v.visit_component("arm2", self.arm2)?;
        v.visit_component("arm3", self.arm3)?;
        Ok(())
    }
}
pub type NondetRegLayout4LayoutArray = [&'static NondetRegLayout; 4];
pub struct OneHot_4_Layout {
    pub _super: &'static NondetRegLayout4LayoutArray,
}
impl risc0_zkp::layout::Component for OneHot_4_Layout {
    fn ty_name(&self) -> &'static str {
        "OneHot_4_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        Ok(())
    }
}
pub struct Xor5wordsMajor_0_Layout {
    pub _super: &'static Xor5wordsMajor_0__SuperLayout,
    pub minor_onehot: &'static OneHot_4_Layout,
}
impl risc0_zkp::layout::Component for Xor5wordsMajor_0_Layout {
    fn ty_name(&self) -> &'static str {
        "Xor5wordsMajor_0_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("minor_onehot", self.minor_onehot)?;
        Ok(())
    }
}
pub struct Xor5wordsResult_1__0_Layout {
    pub xor_abc: &'static NondetRegLayout22LayoutArray,
    pub unpack_a: &'static ToBits_22_Layout,
    pub unpack_b: &'static ToBits_22_Layout,
    pub unpack_c: &'static ToBits_22_Layout,
    pub unpack_d: &'static ToBits_22_Layout,
    pub unpack_e: &'static ToBits_22_Layout,
}
impl risc0_zkp::layout::Component for Xor5wordsResult_1__0_Layout {
    fn ty_name(&self) -> &'static str {
        "Xor5wordsResult_1__0_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("xor_abc", self.xor_abc)?;
        v.visit_component("unpack_a", self.unpack_a)?;
        v.visit_component("unpack_b", self.unpack_b)?;
        v.visit_component("unpack_c", self.unpack_c)?;
        v.visit_component("unpack_d", self.unpack_d)?;
        v.visit_component("unpack_e", self.unpack_e)?;
        Ok(())
    }
}
pub struct Xor5wordsMinor0_1_Layout {
    pub _super: &'static RetTupleLayout,
    pub result: &'static NondetRegLayout,
    pub _0: &'static Xor5wordsResult_1__0_Layout,
}
impl risc0_zkp::layout::Component for Xor5wordsMinor0_1_Layout {
    fn ty_name(&self) -> &'static str {
        "Xor5wordsMinor0_1_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("result", self.result)?;
        v.visit_component("_0", self._0)?;
        Ok(())
    }
}
pub struct Xor5wordsResult_1__1_Layout {
    pub unpack_a: &'static ToBits_21_Layout,
    pub xor_abc: &'static NondetRegLayout21LayoutArray,
    pub unpack_b: &'static ToBits_21_Layout,
    pub unpack_c: &'static ToBits_21_Layout,
    pub unpack_d: &'static ToBits_21_Layout,
    pub unpack_e: &'static ToBits_21_Layout,
}
impl risc0_zkp::layout::Component for Xor5wordsResult_1__1_Layout {
    fn ty_name(&self) -> &'static str {
        "Xor5wordsResult_1__1_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("unpack_a", self.unpack_a)?;
        v.visit_component("xor_abc", self.xor_abc)?;
        v.visit_component("unpack_b", self.unpack_b)?;
        v.visit_component("unpack_c", self.unpack_c)?;
        v.visit_component("unpack_d", self.unpack_d)?;
        v.visit_component("unpack_e", self.unpack_e)?;
        Ok(())
    }
}
pub struct Xor5wordsMinor1_1_Layout {
    pub _super: &'static RetTupleLayout,
    pub result: &'static NondetRegLayout,
    pub _0: &'static Xor5wordsResult_1__1_Layout,
}
impl risc0_zkp::layout::Component for Xor5wordsMinor1_1_Layout {
    fn ty_name(&self) -> &'static str {
        "Xor5wordsMinor1_1_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("result", self.result)?;
        v.visit_component("_0", self._0)?;
        Ok(())
    }
}
pub struct Xor5wordsResult_1__2_Layout {
    pub unpack_a: &'static ToBits_21_Layout,
    pub xor_abc: &'static NondetRegLayout21LayoutArray,
    pub unpack_b: &'static ToBits_21_Layout,
    pub unpack_c: &'static ToBits_21_Layout,
    pub unpack_d: &'static ToBits_21_Layout,
    pub unpack_e: &'static ToBits_21_Layout,
}
impl risc0_zkp::layout::Component for Xor5wordsResult_1__2_Layout {
    fn ty_name(&self) -> &'static str {
        "Xor5wordsResult_1__2_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("unpack_a", self.unpack_a)?;
        v.visit_component("xor_abc", self.xor_abc)?;
        v.visit_component("unpack_b", self.unpack_b)?;
        v.visit_component("unpack_c", self.unpack_c)?;
        v.visit_component("unpack_d", self.unpack_d)?;
        v.visit_component("unpack_e", self.unpack_e)?;
        Ok(())
    }
}
pub struct Xor5wordsMinor2_1_Layout {
    pub _super: &'static RetTupleLayout,
    pub result: &'static NondetRegLayout,
    pub _0: &'static Xor5wordsResult_1__2_Layout,
}
impl risc0_zkp::layout::Component for Xor5wordsMinor2_1_Layout {
    fn ty_name(&self) -> &'static str {
        "Xor5wordsMinor2_1_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("result", self.result)?;
        v.visit_component("_0", self._0)?;
        Ok(())
    }
}
pub type NondetRegLayout12LayoutArray = [&'static NondetRegLayout; 12];
pub struct Xor5wordsMinor3_1_Layout {
    pub _super: &'static RetTupleLayout,
    pub _0: &'static NondetRegLayout,
    pub inp_c: &'static NondetRegLayout22LayoutArray,
    pub inp_b: &'static NondetRegLayout22LayoutArray,
    pub inp_a: &'static NondetRegLayout22LayoutArray,
    pub tmp_1: &'static NondetRegLayout12LayoutArray,
    pub _1: &'static NondetRegLayout,
    pub _2: &'static NondetRegLayout,
}
impl risc0_zkp::layout::Component for Xor5wordsMinor3_1_Layout {
    fn ty_name(&self) -> &'static str {
        "Xor5wordsMinor3_1_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("_0", self._0)?;
        v.visit_component("inp_c", self.inp_c)?;
        v.visit_component("inp_b", self.inp_b)?;
        v.visit_component("inp_a", self.inp_a)?;
        v.visit_component("tmp_1", self.tmp_1)?;
        v.visit_component("_1", self._1)?;
        v.visit_component("_2", self._2)?;
        Ok(())
    }
}
pub struct Xor5wordsMajor_1__SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static Xor5wordsMinor0_1_Layout,
    pub arm1: &'static Xor5wordsMinor1_1_Layout,
    pub arm2: &'static Xor5wordsMinor2_1_Layout,
    pub arm3: &'static Xor5wordsMinor3_1_Layout,
}
impl risc0_zkp::layout::Component for Xor5wordsMajor_1__SuperLayout {
    fn ty_name(&self) -> &'static str {
        "Xor5wordsMajor_1__SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        v.visit_component("arm2", self.arm2)?;
        v.visit_component("arm3", self.arm3)?;
        Ok(())
    }
}
pub struct Xor5wordsMajor_1_Layout {
    pub _super: &'static Xor5wordsMajor_1__SuperLayout,
    pub minor_onehot: &'static OneHot_4_Layout,
}
impl risc0_zkp::layout::Component for Xor5wordsMajor_1_Layout {
    fn ty_name(&self) -> &'static str {
        "Xor5wordsMajor_1_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("minor_onehot", self.minor_onehot)?;
        Ok(())
    }
}
pub struct Xor5wordsResult_2__0_Layout {
    pub xor_abc: &'static NondetRegLayout22LayoutArray,
    pub unpack_a: &'static ToBits_22_Layout,
    pub unpack_b: &'static ToBits_22_Layout,
    pub unpack_c: &'static ToBits_22_Layout,
    pub unpack_d: &'static ToBits_22_Layout,
    pub unpack_e: &'static ToBits_22_Layout,
}
impl risc0_zkp::layout::Component for Xor5wordsResult_2__0_Layout {
    fn ty_name(&self) -> &'static str {
        "Xor5wordsResult_2__0_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("xor_abc", self.xor_abc)?;
        v.visit_component("unpack_a", self.unpack_a)?;
        v.visit_component("unpack_b", self.unpack_b)?;
        v.visit_component("unpack_c", self.unpack_c)?;
        v.visit_component("unpack_d", self.unpack_d)?;
        v.visit_component("unpack_e", self.unpack_e)?;
        Ok(())
    }
}
pub struct Xor5wordsMinor0_2_Layout {
    pub _super: &'static RetTupleLayout,
    pub result: &'static NondetRegLayout,
    pub _0: &'static Xor5wordsResult_2__0_Layout,
}
impl risc0_zkp::layout::Component for Xor5wordsMinor0_2_Layout {
    fn ty_name(&self) -> &'static str {
        "Xor5wordsMinor0_2_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("result", self.result)?;
        v.visit_component("_0", self._0)?;
        Ok(())
    }
}
pub struct Xor5wordsResult_2__1_Layout {
    pub unpack_a: &'static ToBits_21_Layout,
    pub xor_abc: &'static NondetRegLayout21LayoutArray,
    pub unpack_b: &'static ToBits_21_Layout,
    pub unpack_c: &'static ToBits_21_Layout,
    pub unpack_d: &'static ToBits_21_Layout,
    pub unpack_e: &'static ToBits_21_Layout,
}
impl risc0_zkp::layout::Component for Xor5wordsResult_2__1_Layout {
    fn ty_name(&self) -> &'static str {
        "Xor5wordsResult_2__1_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("unpack_a", self.unpack_a)?;
        v.visit_component("xor_abc", self.xor_abc)?;
        v.visit_component("unpack_b", self.unpack_b)?;
        v.visit_component("unpack_c", self.unpack_c)?;
        v.visit_component("unpack_d", self.unpack_d)?;
        v.visit_component("unpack_e", self.unpack_e)?;
        Ok(())
    }
}
pub struct Xor5wordsMinor1_2_Layout {
    pub _super: &'static RetTupleLayout,
    pub result: &'static NondetRegLayout,
    pub _0: &'static Xor5wordsResult_2__1_Layout,
}
impl risc0_zkp::layout::Component for Xor5wordsMinor1_2_Layout {
    fn ty_name(&self) -> &'static str {
        "Xor5wordsMinor1_2_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("result", self.result)?;
        v.visit_component("_0", self._0)?;
        Ok(())
    }
}
pub struct Xor5wordsResult_2__2_Layout {
    pub unpack_a: &'static ToBits_21_Layout,
    pub xor_abc: &'static NondetRegLayout21LayoutArray,
    pub unpack_b: &'static ToBits_21_Layout,
    pub unpack_c: &'static ToBits_21_Layout,
    pub unpack_d: &'static ToBits_21_Layout,
    pub unpack_e: &'static ToBits_21_Layout,
}
impl risc0_zkp::layout::Component for Xor5wordsResult_2__2_Layout {
    fn ty_name(&self) -> &'static str {
        "Xor5wordsResult_2__2_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("unpack_a", self.unpack_a)?;
        v.visit_component("xor_abc", self.xor_abc)?;
        v.visit_component("unpack_b", self.unpack_b)?;
        v.visit_component("unpack_c", self.unpack_c)?;
        v.visit_component("unpack_d", self.unpack_d)?;
        v.visit_component("unpack_e", self.unpack_e)?;
        Ok(())
    }
}
pub struct Xor5wordsMinor2_2_Layout {
    pub _super: &'static RetTupleLayout,
    pub result: &'static NondetRegLayout,
    pub _0: &'static Xor5wordsResult_2__2_Layout,
}
impl risc0_zkp::layout::Component for Xor5wordsMinor2_2_Layout {
    fn ty_name(&self) -> &'static str {
        "Xor5wordsMinor2_2_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("result", self.result)?;
        v.visit_component("_0", self._0)?;
        Ok(())
    }
}
pub type NondetRegLayout15LayoutArray = [&'static NondetRegLayout; 15];
pub struct Xor5wordsMinor3_2_Layout {
    pub _super: &'static RetTupleLayout,
    pub _0: &'static NondetRegLayout,
    pub inp_c: &'static NondetRegLayout22LayoutArray,
    pub inp_b: &'static NondetRegLayout22LayoutArray,
    pub inp_a: &'static NondetRegLayout22LayoutArray,
    pub tmp_1: &'static NondetRegLayout15LayoutArray,
    pub _1: &'static NondetRegLayout,
    pub _2: &'static NondetRegLayout,
}
impl risc0_zkp::layout::Component for Xor5wordsMinor3_2_Layout {
    fn ty_name(&self) -> &'static str {
        "Xor5wordsMinor3_2_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("_0", self._0)?;
        v.visit_component("inp_c", self.inp_c)?;
        v.visit_component("inp_b", self.inp_b)?;
        v.visit_component("inp_a", self.inp_a)?;
        v.visit_component("tmp_1", self.tmp_1)?;
        v.visit_component("_1", self._1)?;
        v.visit_component("_2", self._2)?;
        Ok(())
    }
}
pub struct Xor5wordsMajor_2__SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static Xor5wordsMinor0_2_Layout,
    pub arm1: &'static Xor5wordsMinor1_2_Layout,
    pub arm2: &'static Xor5wordsMinor2_2_Layout,
    pub arm3: &'static Xor5wordsMinor3_2_Layout,
}
impl risc0_zkp::layout::Component for Xor5wordsMajor_2__SuperLayout {
    fn ty_name(&self) -> &'static str {
        "Xor5wordsMajor_2__SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        v.visit_component("arm2", self.arm2)?;
        v.visit_component("arm3", self.arm3)?;
        Ok(())
    }
}
pub struct Xor5wordsMajor_2_Layout {
    pub _super: &'static Xor5wordsMajor_2__SuperLayout,
    pub minor_onehot: &'static OneHot_4_Layout,
}
impl risc0_zkp::layout::Component for Xor5wordsMajor_2_Layout {
    fn ty_name(&self) -> &'static str {
        "Xor5wordsMajor_2_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("minor_onehot", self.minor_onehot)?;
        Ok(())
    }
}
pub struct Xor5wordsResult_3__0_Layout {
    pub xor_abc: &'static NondetRegLayout22LayoutArray,
    pub unpack_a: &'static ToBits_22_Layout,
    pub unpack_b: &'static ToBits_22_Layout,
    pub unpack_c: &'static ToBits_22_Layout,
    pub unpack_d: &'static ToBits_22_Layout,
    pub unpack_e: &'static ToBits_22_Layout,
}
impl risc0_zkp::layout::Component for Xor5wordsResult_3__0_Layout {
    fn ty_name(&self) -> &'static str {
        "Xor5wordsResult_3__0_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("xor_abc", self.xor_abc)?;
        v.visit_component("unpack_a", self.unpack_a)?;
        v.visit_component("unpack_b", self.unpack_b)?;
        v.visit_component("unpack_c", self.unpack_c)?;
        v.visit_component("unpack_d", self.unpack_d)?;
        v.visit_component("unpack_e", self.unpack_e)?;
        Ok(())
    }
}
pub struct Xor5wordsMinor0_3_Layout {
    pub _super: &'static RetTupleLayout,
    pub result: &'static NondetRegLayout,
    pub _0: &'static Xor5wordsResult_3__0_Layout,
}
impl risc0_zkp::layout::Component for Xor5wordsMinor0_3_Layout {
    fn ty_name(&self) -> &'static str {
        "Xor5wordsMinor0_3_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("result", self.result)?;
        v.visit_component("_0", self._0)?;
        Ok(())
    }
}
pub struct Xor5wordsResult_3__1_Layout {
    pub unpack_a: &'static ToBits_21_Layout,
    pub xor_abc: &'static NondetRegLayout21LayoutArray,
    pub unpack_b: &'static ToBits_21_Layout,
    pub unpack_c: &'static ToBits_21_Layout,
    pub unpack_d: &'static ToBits_21_Layout,
    pub unpack_e: &'static ToBits_21_Layout,
}
impl risc0_zkp::layout::Component for Xor5wordsResult_3__1_Layout {
    fn ty_name(&self) -> &'static str {
        "Xor5wordsResult_3__1_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("unpack_a", self.unpack_a)?;
        v.visit_component("xor_abc", self.xor_abc)?;
        v.visit_component("unpack_b", self.unpack_b)?;
        v.visit_component("unpack_c", self.unpack_c)?;
        v.visit_component("unpack_d", self.unpack_d)?;
        v.visit_component("unpack_e", self.unpack_e)?;
        Ok(())
    }
}
pub struct Xor5wordsMinor1_3_Layout {
    pub _super: &'static RetTupleLayout,
    pub result: &'static NondetRegLayout,
    pub _0: &'static Xor5wordsResult_3__1_Layout,
}
impl risc0_zkp::layout::Component for Xor5wordsMinor1_3_Layout {
    fn ty_name(&self) -> &'static str {
        "Xor5wordsMinor1_3_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("result", self.result)?;
        v.visit_component("_0", self._0)?;
        Ok(())
    }
}
pub struct Xor5wordsResult_3__2_Layout {
    pub unpack_a: &'static ToBits_21_Layout,
    pub xor_abc: &'static NondetRegLayout21LayoutArray,
    pub unpack_b: &'static ToBits_21_Layout,
    pub unpack_c: &'static ToBits_21_Layout,
    pub unpack_d: &'static ToBits_21_Layout,
    pub unpack_e: &'static ToBits_21_Layout,
}
impl risc0_zkp::layout::Component for Xor5wordsResult_3__2_Layout {
    fn ty_name(&self) -> &'static str {
        "Xor5wordsResult_3__2_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("unpack_a", self.unpack_a)?;
        v.visit_component("xor_abc", self.xor_abc)?;
        v.visit_component("unpack_b", self.unpack_b)?;
        v.visit_component("unpack_c", self.unpack_c)?;
        v.visit_component("unpack_d", self.unpack_d)?;
        v.visit_component("unpack_e", self.unpack_e)?;
        Ok(())
    }
}
pub struct Xor5wordsMinor2_3_Layout {
    pub _super: &'static RetTupleLayout,
    pub result: &'static NondetRegLayout,
    pub _0: &'static Xor5wordsResult_3__2_Layout,
}
impl risc0_zkp::layout::Component for Xor5wordsMinor2_3_Layout {
    fn ty_name(&self) -> &'static str {
        "Xor5wordsMinor2_3_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("result", self.result)?;
        v.visit_component("_0", self._0)?;
        Ok(())
    }
}
pub type NondetRegLayout18LayoutArray = [&'static NondetRegLayout; 18];
pub struct Xor5wordsMinor3_3_Layout {
    pub _super: &'static RetTupleLayout,
    pub _0: &'static NondetRegLayout,
    pub inp_c: &'static NondetRegLayout22LayoutArray,
    pub inp_b: &'static NondetRegLayout22LayoutArray,
    pub inp_a: &'static NondetRegLayout22LayoutArray,
    pub tmp_1: &'static NondetRegLayout18LayoutArray,
    pub _1: &'static NondetRegLayout,
    pub _2: &'static NondetRegLayout,
}
impl risc0_zkp::layout::Component for Xor5wordsMinor3_3_Layout {
    fn ty_name(&self) -> &'static str {
        "Xor5wordsMinor3_3_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("_0", self._0)?;
        v.visit_component("inp_c", self.inp_c)?;
        v.visit_component("inp_b", self.inp_b)?;
        v.visit_component("inp_a", self.inp_a)?;
        v.visit_component("tmp_1", self.tmp_1)?;
        v.visit_component("_1", self._1)?;
        v.visit_component("_2", self._2)?;
        Ok(())
    }
}
pub struct Xor5wordsMajor_3__SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static Xor5wordsMinor0_3_Layout,
    pub arm1: &'static Xor5wordsMinor1_3_Layout,
    pub arm2: &'static Xor5wordsMinor2_3_Layout,
    pub arm3: &'static Xor5wordsMinor3_3_Layout,
}
impl risc0_zkp::layout::Component for Xor5wordsMajor_3__SuperLayout {
    fn ty_name(&self) -> &'static str {
        "Xor5wordsMajor_3__SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        v.visit_component("arm2", self.arm2)?;
        v.visit_component("arm3", self.arm3)?;
        Ok(())
    }
}
pub struct Xor5wordsMajor_3_Layout {
    pub _super: &'static Xor5wordsMajor_3__SuperLayout,
    pub minor_onehot: &'static OneHot_4_Layout,
}
impl risc0_zkp::layout::Component for Xor5wordsMajor_3_Layout {
    fn ty_name(&self) -> &'static str {
        "Xor5wordsMajor_3_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("minor_onehot", self.minor_onehot)?;
        Ok(())
    }
}
pub struct Xor5wordsResult_4__0_Layout {
    pub xor_abc: &'static NondetRegLayout22LayoutArray,
    pub unpack_a: &'static ToBits_22_Layout,
    pub unpack_b: &'static ToBits_22_Layout,
    pub unpack_c: &'static ToBits_22_Layout,
    pub unpack_d: &'static ToBits_22_Layout,
    pub unpack_e: &'static ToBits_22_Layout,
}
impl risc0_zkp::layout::Component for Xor5wordsResult_4__0_Layout {
    fn ty_name(&self) -> &'static str {
        "Xor5wordsResult_4__0_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("xor_abc", self.xor_abc)?;
        v.visit_component("unpack_a", self.unpack_a)?;
        v.visit_component("unpack_b", self.unpack_b)?;
        v.visit_component("unpack_c", self.unpack_c)?;
        v.visit_component("unpack_d", self.unpack_d)?;
        v.visit_component("unpack_e", self.unpack_e)?;
        Ok(())
    }
}
pub struct Xor5wordsMinor0_4_Layout {
    pub _super: &'static RetTupleLayout,
    pub result: &'static NondetRegLayout,
    pub _0: &'static Xor5wordsResult_4__0_Layout,
}
impl risc0_zkp::layout::Component for Xor5wordsMinor0_4_Layout {
    fn ty_name(&self) -> &'static str {
        "Xor5wordsMinor0_4_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("result", self.result)?;
        v.visit_component("_0", self._0)?;
        Ok(())
    }
}
pub struct Xor5wordsResult_4__1_Layout {
    pub unpack_a: &'static ToBits_21_Layout,
    pub xor_abc: &'static NondetRegLayout21LayoutArray,
    pub unpack_b: &'static ToBits_21_Layout,
    pub unpack_c: &'static ToBits_21_Layout,
    pub unpack_d: &'static ToBits_21_Layout,
    pub unpack_e: &'static ToBits_21_Layout,
}
impl risc0_zkp::layout::Component for Xor5wordsResult_4__1_Layout {
    fn ty_name(&self) -> &'static str {
        "Xor5wordsResult_4__1_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("unpack_a", self.unpack_a)?;
        v.visit_component("xor_abc", self.xor_abc)?;
        v.visit_component("unpack_b", self.unpack_b)?;
        v.visit_component("unpack_c", self.unpack_c)?;
        v.visit_component("unpack_d", self.unpack_d)?;
        v.visit_component("unpack_e", self.unpack_e)?;
        Ok(())
    }
}
pub struct Xor5wordsMinor1_4_Layout {
    pub _super: &'static RetTupleLayout,
    pub result: &'static NondetRegLayout,
    pub _0: &'static Xor5wordsResult_4__1_Layout,
}
impl risc0_zkp::layout::Component for Xor5wordsMinor1_4_Layout {
    fn ty_name(&self) -> &'static str {
        "Xor5wordsMinor1_4_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("result", self.result)?;
        v.visit_component("_0", self._0)?;
        Ok(())
    }
}
pub struct Xor5wordsResult_4__2_Layout {
    pub unpack_a: &'static ToBits_21_Layout,
    pub xor_abc: &'static NondetRegLayout21LayoutArray,
    pub unpack_b: &'static ToBits_21_Layout,
    pub unpack_c: &'static ToBits_21_Layout,
    pub unpack_d: &'static ToBits_21_Layout,
    pub unpack_e: &'static ToBits_21_Layout,
}
impl risc0_zkp::layout::Component for Xor5wordsResult_4__2_Layout {
    fn ty_name(&self) -> &'static str {
        "Xor5wordsResult_4__2_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("unpack_a", self.unpack_a)?;
        v.visit_component("xor_abc", self.xor_abc)?;
        v.visit_component("unpack_b", self.unpack_b)?;
        v.visit_component("unpack_c", self.unpack_c)?;
        v.visit_component("unpack_d", self.unpack_d)?;
        v.visit_component("unpack_e", self.unpack_e)?;
        Ok(())
    }
}
pub struct Xor5wordsMinor2_4_Layout {
    pub _super: &'static RetTupleLayout,
    pub result: &'static NondetRegLayout,
    pub _0: &'static Xor5wordsResult_4__2_Layout,
}
impl risc0_zkp::layout::Component for Xor5wordsMinor2_4_Layout {
    fn ty_name(&self) -> &'static str {
        "Xor5wordsMinor2_4_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("result", self.result)?;
        v.visit_component("_0", self._0)?;
        Ok(())
    }
}
pub struct Xor5wordsMinor3_4_Layout {
    pub _super: &'static RetTupleLayout,
    pub _0: &'static NondetRegLayout,
    pub inp_c: &'static NondetRegLayout22LayoutArray,
    pub inp_b: &'static NondetRegLayout22LayoutArray,
    pub inp_a: &'static NondetRegLayout22LayoutArray,
    pub tmp_1: &'static NondetRegLayout21LayoutArray,
    pub _1: &'static NondetRegLayout,
    pub _2: &'static NondetRegLayout,
}
impl risc0_zkp::layout::Component for Xor5wordsMinor3_4_Layout {
    fn ty_name(&self) -> &'static str {
        "Xor5wordsMinor3_4_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("_0", self._0)?;
        v.visit_component("inp_c", self.inp_c)?;
        v.visit_component("inp_b", self.inp_b)?;
        v.visit_component("inp_a", self.inp_a)?;
        v.visit_component("tmp_1", self.tmp_1)?;
        v.visit_component("_1", self._1)?;
        v.visit_component("_2", self._2)?;
        Ok(())
    }
}
pub struct Xor5wordsMajor_4__SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static Xor5wordsMinor0_4_Layout,
    pub arm1: &'static Xor5wordsMinor1_4_Layout,
    pub arm2: &'static Xor5wordsMinor2_4_Layout,
    pub arm3: &'static Xor5wordsMinor3_4_Layout,
}
impl risc0_zkp::layout::Component for Xor5wordsMajor_4__SuperLayout {
    fn ty_name(&self) -> &'static str {
        "Xor5wordsMajor_4__SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        v.visit_component("arm2", self.arm2)?;
        v.visit_component("arm3", self.arm3)?;
        Ok(())
    }
}
pub struct Xor5wordsMajor_4_Layout {
    pub _super: &'static Xor5wordsMajor_4__SuperLayout,
    pub minor_onehot: &'static OneHot_4_Layout,
}
impl risc0_zkp::layout::Component for Xor5wordsMajor_4_Layout {
    fn ty_name(&self) -> &'static str {
        "Xor5wordsMajor_4_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("minor_onehot", self.minor_onehot)?;
        Ok(())
    }
}
pub struct RhoMinor0_0__0_Layout {
    pub _super: &'static RetTupleLayout,
    pub unpack_m1: &'static ToBits_22_Layout,
    pub unpack_m2: &'static ToBits_21_Layout,
    pub unpack_m3: &'static ToBits_21_Layout,
    pub unpack_p1: &'static ToBits_22_Layout,
    pub unpack_p2: &'static ToBits_21_Layout,
    pub unpack_p3: &'static ToBits_21_Layout,
}
impl risc0_zkp::layout::Component for RhoMinor0_0__0_Layout {
    fn ty_name(&self) -> &'static str {
        "RhoMinor0_0__0_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("unpack_m1", self.unpack_m1)?;
        v.visit_component("unpack_m2", self.unpack_m2)?;
        v.visit_component("unpack_m3", self.unpack_m3)?;
        v.visit_component("unpack_p1", self.unpack_p1)?;
        v.visit_component("unpack_p2", self.unpack_p2)?;
        v.visit_component("unpack_p3", self.unpack_p3)?;
        Ok(())
    }
}
pub struct RhoMinor1_0__0_Arm1_SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub unpack_m1: &'static ToBits_22_Layout,
    pub unpack_m2: &'static ToBits_21_Layout,
    pub unpack_m3: &'static ToBits_21_Layout,
}
impl risc0_zkp::layout::Component for RhoMinor1_0__0_Arm1_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "RhoMinor1_0__0_Arm1_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("unpack_m1", self.unpack_m1)?;
        v.visit_component("unpack_m2", self.unpack_m2)?;
        v.visit_component("unpack_m3", self.unpack_m3)?;
        Ok(())
    }
}
pub struct RhoMinor1_0__0__SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static RhoMinor1_0__0_Arm1_SuperLayout,
}
impl risc0_zkp::layout::Component for RhoMinor1_0__0__SuperLayout {
    fn ty_name(&self) -> &'static str {
        "RhoMinor1_0__0__SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct RhoMinor1_0__0_Layout {
    pub _super: &'static RhoMinor1_0__0__SuperLayout,
    pub unpack_xy1: &'static ToBits_22_Layout,
    pub unpack_xy2: &'static ToBits_21_Layout,
    pub unpack_xy3: &'static ToBits_21_Layout,
    pub _0: &'static NondetRegLayout,
    pub _1: &'static NondetRegLayout,
    pub _2: &'static NondetRegLayout,
}
impl risc0_zkp::layout::Component for RhoMinor1_0__0_Layout {
    fn ty_name(&self) -> &'static str {
        "RhoMinor1_0__0_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("unpack_xy1", self.unpack_xy1)?;
        v.visit_component("unpack_xy2", self.unpack_xy2)?;
        v.visit_component("unpack_xy3", self.unpack_xy3)?;
        v.visit_component("_0", self._0)?;
        v.visit_component("_1", self._1)?;
        v.visit_component("_2", self._2)?;
        Ok(())
    }
}
pub struct RhoMinor2_0__0_Layout {
    pub _super: &'static RetTupleLayout,
    pub unpack_p1: &'static ToBits_22_Layout,
    pub unpack_p2: &'static ToBits_21_Layout,
    pub unpack_p3: &'static ToBits_21_Layout,
    pub unpack_xy1: &'static ToBits_22_Layout,
    pub unpack_xy2: &'static ToBits_21_Layout,
    pub unpack_xy3: &'static ToBits_21_Layout,
    pub _0: &'static NondetRegLayout,
    pub _1: &'static NondetRegLayout,
    pub _2: &'static NondetRegLayout,
}
impl risc0_zkp::layout::Component for RhoMinor2_0__0_Layout {
    fn ty_name(&self) -> &'static str {
        "RhoMinor2_0__0_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("unpack_p1", self.unpack_p1)?;
        v.visit_component("unpack_p2", self.unpack_p2)?;
        v.visit_component("unpack_p3", self.unpack_p3)?;
        v.visit_component("unpack_xy1", self.unpack_xy1)?;
        v.visit_component("unpack_xy2", self.unpack_xy2)?;
        v.visit_component("unpack_xy3", self.unpack_xy3)?;
        v.visit_component("_0", self._0)?;
        v.visit_component("_1", self._1)?;
        v.visit_component("_2", self._2)?;
        Ok(())
    }
}
pub struct RhoMinor0_2__0_Layout {
    pub _super: &'static RetTupleLayout,
    pub unpack_m1: &'static ToBits_22_Layout,
    pub unpack_m2: &'static ToBits_21_Layout,
    pub unpack_m3: &'static ToBits_21_Layout,
    pub unpack_p1: &'static ToBits_22_Layout,
    pub unpack_p2: &'static ToBits_21_Layout,
    pub unpack_p3: &'static ToBits_21_Layout,
}
impl risc0_zkp::layout::Component for RhoMinor0_2__0_Layout {
    fn ty_name(&self) -> &'static str {
        "RhoMinor0_2__0_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("unpack_m1", self.unpack_m1)?;
        v.visit_component("unpack_m2", self.unpack_m2)?;
        v.visit_component("unpack_m3", self.unpack_m3)?;
        v.visit_component("unpack_p1", self.unpack_p1)?;
        v.visit_component("unpack_p2", self.unpack_p2)?;
        v.visit_component("unpack_p3", self.unpack_p3)?;
        Ok(())
    }
}
pub struct RhoMinor1_2__0_Arm1_SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub unpack_m1: &'static ToBits_22_Layout,
    pub unpack_m2: &'static ToBits_21_Layout,
    pub unpack_m3: &'static ToBits_21_Layout,
}
impl risc0_zkp::layout::Component for RhoMinor1_2__0_Arm1_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "RhoMinor1_2__0_Arm1_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("unpack_m1", self.unpack_m1)?;
        v.visit_component("unpack_m2", self.unpack_m2)?;
        v.visit_component("unpack_m3", self.unpack_m3)?;
        Ok(())
    }
}
pub struct RhoMinor1_2__0__SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static RhoMinor1_2__0_Arm1_SuperLayout,
}
impl risc0_zkp::layout::Component for RhoMinor1_2__0__SuperLayout {
    fn ty_name(&self) -> &'static str {
        "RhoMinor1_2__0__SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct RhoMinor1_2__0_Layout {
    pub _super: &'static RhoMinor1_2__0__SuperLayout,
    pub unpack_xy1: &'static ToBits_22_Layout,
    pub unpack_xy2: &'static ToBits_21_Layout,
    pub unpack_xy3: &'static ToBits_21_Layout,
    pub _0: &'static NondetRegLayout,
    pub _1: &'static NondetRegLayout,
    pub _2: &'static NondetRegLayout,
}
impl risc0_zkp::layout::Component for RhoMinor1_2__0_Layout {
    fn ty_name(&self) -> &'static str {
        "RhoMinor1_2__0_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("unpack_xy1", self.unpack_xy1)?;
        v.visit_component("unpack_xy2", self.unpack_xy2)?;
        v.visit_component("unpack_xy3", self.unpack_xy3)?;
        v.visit_component("_0", self._0)?;
        v.visit_component("_1", self._1)?;
        v.visit_component("_2", self._2)?;
        Ok(())
    }
}
pub struct RhoMinor2_2__0_Layout {
    pub _super: &'static RetTupleLayout,
    pub unpack_p1: &'static ToBits_22_Layout,
    pub unpack_p2: &'static ToBits_21_Layout,
    pub unpack_p3: &'static ToBits_21_Layout,
    pub unpack_xy1: &'static ToBits_22_Layout,
    pub unpack_xy2: &'static ToBits_21_Layout,
    pub unpack_xy3: &'static ToBits_21_Layout,
    pub _0: &'static NondetRegLayout,
    pub _1: &'static NondetRegLayout,
    pub _2: &'static NondetRegLayout,
}
impl risc0_zkp::layout::Component for RhoMinor2_2__0_Layout {
    fn ty_name(&self) -> &'static str {
        "RhoMinor2_2__0_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("unpack_p1", self.unpack_p1)?;
        v.visit_component("unpack_p2", self.unpack_p2)?;
        v.visit_component("unpack_p3", self.unpack_p3)?;
        v.visit_component("unpack_xy1", self.unpack_xy1)?;
        v.visit_component("unpack_xy2", self.unpack_xy2)?;
        v.visit_component("unpack_xy3", self.unpack_xy3)?;
        v.visit_component("_0", self._0)?;
        v.visit_component("_1", self._1)?;
        v.visit_component("_2", self._2)?;
        Ok(())
    }
}
pub struct RhoMinor0_4__0_Layout {
    pub _super: &'static RetTupleLayout,
    pub unpack_m1: &'static ToBits_22_Layout,
    pub unpack_m2: &'static ToBits_21_Layout,
    pub unpack_m3: &'static ToBits_21_Layout,
    pub unpack_p1: &'static ToBits_22_Layout,
    pub unpack_p2: &'static ToBits_21_Layout,
    pub unpack_p3: &'static ToBits_21_Layout,
}
impl risc0_zkp::layout::Component for RhoMinor0_4__0_Layout {
    fn ty_name(&self) -> &'static str {
        "RhoMinor0_4__0_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("unpack_m1", self.unpack_m1)?;
        v.visit_component("unpack_m2", self.unpack_m2)?;
        v.visit_component("unpack_m3", self.unpack_m3)?;
        v.visit_component("unpack_p1", self.unpack_p1)?;
        v.visit_component("unpack_p2", self.unpack_p2)?;
        v.visit_component("unpack_p3", self.unpack_p3)?;
        Ok(())
    }
}
pub struct RhoMinor1_4__0_Arm1_SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub unpack_m1: &'static ToBits_22_Layout,
    pub unpack_m2: &'static ToBits_21_Layout,
    pub unpack_m3: &'static ToBits_21_Layout,
}
impl risc0_zkp::layout::Component for RhoMinor1_4__0_Arm1_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "RhoMinor1_4__0_Arm1_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("unpack_m1", self.unpack_m1)?;
        v.visit_component("unpack_m2", self.unpack_m2)?;
        v.visit_component("unpack_m3", self.unpack_m3)?;
        Ok(())
    }
}
pub struct RhoMinor1_4__0__SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static RhoMinor1_4__0_Arm1_SuperLayout,
}
impl risc0_zkp::layout::Component for RhoMinor1_4__0__SuperLayout {
    fn ty_name(&self) -> &'static str {
        "RhoMinor1_4__0__SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct RhoMinor1_4__0_Layout {
    pub _super: &'static RhoMinor1_4__0__SuperLayout,
    pub unpack_xy1: &'static ToBits_22_Layout,
    pub unpack_xy2: &'static ToBits_21_Layout,
    pub unpack_xy3: &'static ToBits_21_Layout,
    pub _0: &'static NondetRegLayout,
    pub _1: &'static NondetRegLayout,
    pub _2: &'static NondetRegLayout,
}
impl risc0_zkp::layout::Component for RhoMinor1_4__0_Layout {
    fn ty_name(&self) -> &'static str {
        "RhoMinor1_4__0_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("unpack_xy1", self.unpack_xy1)?;
        v.visit_component("unpack_xy2", self.unpack_xy2)?;
        v.visit_component("unpack_xy3", self.unpack_xy3)?;
        v.visit_component("_0", self._0)?;
        v.visit_component("_1", self._1)?;
        v.visit_component("_2", self._2)?;
        Ok(())
    }
}
pub struct RhoMinor3_0_Arm1Arm1Arm1_SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static RetTupleLayout,
}
impl risc0_zkp::layout::Component for RhoMinor3_0_Arm1Arm1Arm1_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "RhoMinor3_0_Arm1Arm1Arm1_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct RhoMinor3_0_Arm1Arm1_SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static RhoMinor3_0_Arm1Arm1Arm1_SuperLayout,
}
impl risc0_zkp::layout::Component for RhoMinor3_0_Arm1Arm1_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "RhoMinor3_0_Arm1Arm1_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct RhoMinor3_0_Arm1_SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static RhoMinor3_0_Arm1Arm1_SuperLayout,
}
impl risc0_zkp::layout::Component for RhoMinor3_0_Arm1_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "RhoMinor3_0_Arm1_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct RhoMinor3_0__SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static RhoMinor3_0_Arm1_SuperLayout,
}
impl risc0_zkp::layout::Component for RhoMinor3_0__SuperLayout {
    fn ty_name(&self) -> &'static str {
        "RhoMinor3_0__SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct RhoMajor_0__SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RhoMinor0_0__0_Layout,
    pub arm1: &'static RhoMinor1_0__0_Layout,
    pub arm2: &'static RhoMinor2_0__0_Layout,
    pub arm3: &'static RhoMinor0_2__0_Layout,
    pub arm4: &'static RhoMinor1_2__0_Layout,
    pub arm5: &'static RhoMinor2_2__0_Layout,
    pub arm6: &'static RhoMinor0_4__0_Layout,
    pub arm7: &'static RhoMinor1_4__0_Layout,
    pub arm8: &'static RhoMinor3_0__SuperLayout,
}
impl risc0_zkp::layout::Component for RhoMajor_0__SuperLayout {
    fn ty_name(&self) -> &'static str {
        "RhoMajor_0__SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        v.visit_component("arm2", self.arm2)?;
        v.visit_component("arm3", self.arm3)?;
        v.visit_component("arm4", self.arm4)?;
        v.visit_component("arm5", self.arm5)?;
        v.visit_component("arm6", self.arm6)?;
        v.visit_component("arm7", self.arm7)?;
        v.visit_component("arm8", self.arm8)?;
        Ok(())
    }
}
pub struct OneHot_9_Layout {
    pub _super: &'static NondetRegLayout9LayoutArray,
}
impl risc0_zkp::layout::Component for OneHot_9_Layout {
    fn ty_name(&self) -> &'static str {
        "OneHot_9_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        Ok(())
    }
}
pub struct RhoMajor_0_Layout {
    pub _super: &'static RhoMajor_0__SuperLayout,
    pub minor_onehot: &'static OneHot_9_Layout,
}
impl risc0_zkp::layout::Component for RhoMajor_0_Layout {
    fn ty_name(&self) -> &'static str {
        "RhoMajor_0_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("minor_onehot", self.minor_onehot)?;
        Ok(())
    }
}
pub struct RhoMinor0_0__1_Layout {
    pub _super: &'static RetTupleLayout,
    pub unpack_m1: &'static ToBits_22_Layout,
    pub unpack_m2: &'static ToBits_21_Layout,
    pub unpack_m3: &'static ToBits_21_Layout,
    pub unpack_p1: &'static ToBits_22_Layout,
    pub unpack_p2: &'static ToBits_21_Layout,
    pub unpack_p3: &'static ToBits_21_Layout,
}
impl risc0_zkp::layout::Component for RhoMinor0_0__1_Layout {
    fn ty_name(&self) -> &'static str {
        "RhoMinor0_0__1_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("unpack_m1", self.unpack_m1)?;
        v.visit_component("unpack_m2", self.unpack_m2)?;
        v.visit_component("unpack_m3", self.unpack_m3)?;
        v.visit_component("unpack_p1", self.unpack_p1)?;
        v.visit_component("unpack_p2", self.unpack_p2)?;
        v.visit_component("unpack_p3", self.unpack_p3)?;
        Ok(())
    }
}
pub struct RhoMinor1_0__1_Arm1_SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub unpack_m1: &'static ToBits_22_Layout,
    pub unpack_m2: &'static ToBits_21_Layout,
    pub unpack_m3: &'static ToBits_21_Layout,
}
impl risc0_zkp::layout::Component for RhoMinor1_0__1_Arm1_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "RhoMinor1_0__1_Arm1_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("unpack_m1", self.unpack_m1)?;
        v.visit_component("unpack_m2", self.unpack_m2)?;
        v.visit_component("unpack_m3", self.unpack_m3)?;
        Ok(())
    }
}
pub struct RhoMinor1_0__1__SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static RhoMinor1_0__1_Arm1_SuperLayout,
}
impl risc0_zkp::layout::Component for RhoMinor1_0__1__SuperLayout {
    fn ty_name(&self) -> &'static str {
        "RhoMinor1_0__1__SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct RhoMinor1_0__1_Layout {
    pub _super: &'static RhoMinor1_0__1__SuperLayout,
    pub unpack_xy1: &'static ToBits_22_Layout,
    pub unpack_xy2: &'static ToBits_21_Layout,
    pub unpack_xy3: &'static ToBits_21_Layout,
    pub _0: &'static NondetRegLayout,
    pub _1: &'static NondetRegLayout,
    pub _2: &'static NondetRegLayout,
}
impl risc0_zkp::layout::Component for RhoMinor1_0__1_Layout {
    fn ty_name(&self) -> &'static str {
        "RhoMinor1_0__1_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("unpack_xy1", self.unpack_xy1)?;
        v.visit_component("unpack_xy2", self.unpack_xy2)?;
        v.visit_component("unpack_xy3", self.unpack_xy3)?;
        v.visit_component("_0", self._0)?;
        v.visit_component("_1", self._1)?;
        v.visit_component("_2", self._2)?;
        Ok(())
    }
}
pub struct RhoMinor2_0__1_Layout {
    pub _super: &'static RetTupleLayout,
    pub unpack_p1: &'static ToBits_22_Layout,
    pub unpack_p2: &'static ToBits_21_Layout,
    pub unpack_p3: &'static ToBits_21_Layout,
    pub unpack_xy1: &'static ToBits_22_Layout,
    pub unpack_xy2: &'static ToBits_21_Layout,
    pub unpack_xy3: &'static ToBits_21_Layout,
    pub _0: &'static NondetRegLayout,
    pub _1: &'static NondetRegLayout,
    pub _2: &'static NondetRegLayout,
}
impl risc0_zkp::layout::Component for RhoMinor2_0__1_Layout {
    fn ty_name(&self) -> &'static str {
        "RhoMinor2_0__1_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("unpack_p1", self.unpack_p1)?;
        v.visit_component("unpack_p2", self.unpack_p2)?;
        v.visit_component("unpack_p3", self.unpack_p3)?;
        v.visit_component("unpack_xy1", self.unpack_xy1)?;
        v.visit_component("unpack_xy2", self.unpack_xy2)?;
        v.visit_component("unpack_xy3", self.unpack_xy3)?;
        v.visit_component("_0", self._0)?;
        v.visit_component("_1", self._1)?;
        v.visit_component("_2", self._2)?;
        Ok(())
    }
}
pub struct RhoMinor0_2__1_Layout {
    pub _super: &'static RetTupleLayout,
    pub unpack_m1: &'static ToBits_22_Layout,
    pub unpack_m2: &'static ToBits_21_Layout,
    pub unpack_m3: &'static ToBits_21_Layout,
    pub unpack_p1: &'static ToBits_22_Layout,
    pub unpack_p2: &'static ToBits_21_Layout,
    pub unpack_p3: &'static ToBits_21_Layout,
}
impl risc0_zkp::layout::Component for RhoMinor0_2__1_Layout {
    fn ty_name(&self) -> &'static str {
        "RhoMinor0_2__1_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("unpack_m1", self.unpack_m1)?;
        v.visit_component("unpack_m2", self.unpack_m2)?;
        v.visit_component("unpack_m3", self.unpack_m3)?;
        v.visit_component("unpack_p1", self.unpack_p1)?;
        v.visit_component("unpack_p2", self.unpack_p2)?;
        v.visit_component("unpack_p3", self.unpack_p3)?;
        Ok(())
    }
}
pub struct RhoMinor1_2__1_Arm1_SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub unpack_m1: &'static ToBits_22_Layout,
    pub unpack_m2: &'static ToBits_21_Layout,
    pub unpack_m3: &'static ToBits_21_Layout,
}
impl risc0_zkp::layout::Component for RhoMinor1_2__1_Arm1_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "RhoMinor1_2__1_Arm1_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("unpack_m1", self.unpack_m1)?;
        v.visit_component("unpack_m2", self.unpack_m2)?;
        v.visit_component("unpack_m3", self.unpack_m3)?;
        Ok(())
    }
}
pub struct RhoMinor1_2__1__SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static RhoMinor1_2__1_Arm1_SuperLayout,
}
impl risc0_zkp::layout::Component for RhoMinor1_2__1__SuperLayout {
    fn ty_name(&self) -> &'static str {
        "RhoMinor1_2__1__SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct RhoMinor1_2__1_Layout {
    pub _super: &'static RhoMinor1_2__1__SuperLayout,
    pub unpack_xy1: &'static ToBits_22_Layout,
    pub unpack_xy2: &'static ToBits_21_Layout,
    pub unpack_xy3: &'static ToBits_21_Layout,
    pub _0: &'static NondetRegLayout,
    pub _1: &'static NondetRegLayout,
    pub _2: &'static NondetRegLayout,
}
impl risc0_zkp::layout::Component for RhoMinor1_2__1_Layout {
    fn ty_name(&self) -> &'static str {
        "RhoMinor1_2__1_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("unpack_xy1", self.unpack_xy1)?;
        v.visit_component("unpack_xy2", self.unpack_xy2)?;
        v.visit_component("unpack_xy3", self.unpack_xy3)?;
        v.visit_component("_0", self._0)?;
        v.visit_component("_1", self._1)?;
        v.visit_component("_2", self._2)?;
        Ok(())
    }
}
pub struct RhoMinor2_2__1_Layout {
    pub _super: &'static RetTupleLayout,
    pub unpack_p1: &'static ToBits_22_Layout,
    pub unpack_p2: &'static ToBits_21_Layout,
    pub unpack_p3: &'static ToBits_21_Layout,
    pub unpack_xy1: &'static ToBits_22_Layout,
    pub unpack_xy2: &'static ToBits_21_Layout,
    pub unpack_xy3: &'static ToBits_21_Layout,
    pub _0: &'static NondetRegLayout,
    pub _1: &'static NondetRegLayout,
    pub _2: &'static NondetRegLayout,
}
impl risc0_zkp::layout::Component for RhoMinor2_2__1_Layout {
    fn ty_name(&self) -> &'static str {
        "RhoMinor2_2__1_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("unpack_p1", self.unpack_p1)?;
        v.visit_component("unpack_p2", self.unpack_p2)?;
        v.visit_component("unpack_p3", self.unpack_p3)?;
        v.visit_component("unpack_xy1", self.unpack_xy1)?;
        v.visit_component("unpack_xy2", self.unpack_xy2)?;
        v.visit_component("unpack_xy3", self.unpack_xy3)?;
        v.visit_component("_0", self._0)?;
        v.visit_component("_1", self._1)?;
        v.visit_component("_2", self._2)?;
        Ok(())
    }
}
pub struct RhoMinor0_4__1_Layout {
    pub _super: &'static RetTupleLayout,
    pub unpack_m1: &'static ToBits_22_Layout,
    pub unpack_m2: &'static ToBits_21_Layout,
    pub unpack_m3: &'static ToBits_21_Layout,
    pub unpack_p1: &'static ToBits_22_Layout,
    pub unpack_p2: &'static ToBits_21_Layout,
    pub unpack_p3: &'static ToBits_21_Layout,
}
impl risc0_zkp::layout::Component for RhoMinor0_4__1_Layout {
    fn ty_name(&self) -> &'static str {
        "RhoMinor0_4__1_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("unpack_m1", self.unpack_m1)?;
        v.visit_component("unpack_m2", self.unpack_m2)?;
        v.visit_component("unpack_m3", self.unpack_m3)?;
        v.visit_component("unpack_p1", self.unpack_p1)?;
        v.visit_component("unpack_p2", self.unpack_p2)?;
        v.visit_component("unpack_p3", self.unpack_p3)?;
        Ok(())
    }
}
pub struct RhoMinor1_4__1_Arm1_SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub unpack_m1: &'static ToBits_22_Layout,
    pub unpack_m2: &'static ToBits_21_Layout,
    pub unpack_m3: &'static ToBits_21_Layout,
}
impl risc0_zkp::layout::Component for RhoMinor1_4__1_Arm1_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "RhoMinor1_4__1_Arm1_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("unpack_m1", self.unpack_m1)?;
        v.visit_component("unpack_m2", self.unpack_m2)?;
        v.visit_component("unpack_m3", self.unpack_m3)?;
        Ok(())
    }
}
pub struct RhoMinor1_4__1__SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static RhoMinor1_4__1_Arm1_SuperLayout,
}
impl risc0_zkp::layout::Component for RhoMinor1_4__1__SuperLayout {
    fn ty_name(&self) -> &'static str {
        "RhoMinor1_4__1__SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct RhoMinor1_4__1_Layout {
    pub _super: &'static RhoMinor1_4__1__SuperLayout,
    pub unpack_xy1: &'static ToBits_22_Layout,
    pub unpack_xy2: &'static ToBits_21_Layout,
    pub unpack_xy3: &'static ToBits_21_Layout,
    pub _0: &'static NondetRegLayout,
    pub _1: &'static NondetRegLayout,
    pub _2: &'static NondetRegLayout,
}
impl risc0_zkp::layout::Component for RhoMinor1_4__1_Layout {
    fn ty_name(&self) -> &'static str {
        "RhoMinor1_4__1_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("unpack_xy1", self.unpack_xy1)?;
        v.visit_component("unpack_xy2", self.unpack_xy2)?;
        v.visit_component("unpack_xy3", self.unpack_xy3)?;
        v.visit_component("_0", self._0)?;
        v.visit_component("_1", self._1)?;
        v.visit_component("_2", self._2)?;
        Ok(())
    }
}
pub struct RhoMinor3_1_Arm1Arm1Arm1_SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static RetTupleLayout,
}
impl risc0_zkp::layout::Component for RhoMinor3_1_Arm1Arm1Arm1_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "RhoMinor3_1_Arm1Arm1Arm1_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct RhoMinor3_1_Arm1Arm1_SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static RhoMinor3_1_Arm1Arm1Arm1_SuperLayout,
}
impl risc0_zkp::layout::Component for RhoMinor3_1_Arm1Arm1_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "RhoMinor3_1_Arm1Arm1_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct RhoMinor3_1_Arm1_SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static RhoMinor3_1_Arm1Arm1_SuperLayout,
}
impl risc0_zkp::layout::Component for RhoMinor3_1_Arm1_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "RhoMinor3_1_Arm1_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct RhoMinor3_1__SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static RhoMinor3_1_Arm1_SuperLayout,
}
impl risc0_zkp::layout::Component for RhoMinor3_1__SuperLayout {
    fn ty_name(&self) -> &'static str {
        "RhoMinor3_1__SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct RhoMajor_1__SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RhoMinor0_0__1_Layout,
    pub arm1: &'static RhoMinor1_0__1_Layout,
    pub arm2: &'static RhoMinor2_0__1_Layout,
    pub arm3: &'static RhoMinor0_2__1_Layout,
    pub arm4: &'static RhoMinor1_2__1_Layout,
    pub arm5: &'static RhoMinor2_2__1_Layout,
    pub arm6: &'static RhoMinor0_4__1_Layout,
    pub arm7: &'static RhoMinor1_4__1_Layout,
    pub arm8: &'static RhoMinor3_1__SuperLayout,
}
impl risc0_zkp::layout::Component for RhoMajor_1__SuperLayout {
    fn ty_name(&self) -> &'static str {
        "RhoMajor_1__SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        v.visit_component("arm2", self.arm2)?;
        v.visit_component("arm3", self.arm3)?;
        v.visit_component("arm4", self.arm4)?;
        v.visit_component("arm5", self.arm5)?;
        v.visit_component("arm6", self.arm6)?;
        v.visit_component("arm7", self.arm7)?;
        v.visit_component("arm8", self.arm8)?;
        Ok(())
    }
}
pub struct RhoMajor_1_Layout {
    pub _super: &'static RhoMajor_1__SuperLayout,
    pub minor_onehot: &'static OneHot_9_Layout,
}
impl risc0_zkp::layout::Component for RhoMajor_1_Layout {
    fn ty_name(&self) -> &'static str {
        "RhoMajor_1_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("minor_onehot", self.minor_onehot)?;
        Ok(())
    }
}
pub struct RhoMinor0_0__2_Layout {
    pub _super: &'static RetTupleLayout,
    pub unpack_m1: &'static ToBits_22_Layout,
    pub unpack_m2: &'static ToBits_21_Layout,
    pub unpack_m3: &'static ToBits_21_Layout,
    pub unpack_p1: &'static ToBits_22_Layout,
    pub unpack_p2: &'static ToBits_21_Layout,
    pub unpack_p3: &'static ToBits_21_Layout,
}
impl risc0_zkp::layout::Component for RhoMinor0_0__2_Layout {
    fn ty_name(&self) -> &'static str {
        "RhoMinor0_0__2_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("unpack_m1", self.unpack_m1)?;
        v.visit_component("unpack_m2", self.unpack_m2)?;
        v.visit_component("unpack_m3", self.unpack_m3)?;
        v.visit_component("unpack_p1", self.unpack_p1)?;
        v.visit_component("unpack_p2", self.unpack_p2)?;
        v.visit_component("unpack_p3", self.unpack_p3)?;
        Ok(())
    }
}
pub struct RhoMinor1_0__2_Arm1_SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub unpack_m1: &'static ToBits_22_Layout,
    pub unpack_m2: &'static ToBits_21_Layout,
    pub unpack_m3: &'static ToBits_21_Layout,
}
impl risc0_zkp::layout::Component for RhoMinor1_0__2_Arm1_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "RhoMinor1_0__2_Arm1_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("unpack_m1", self.unpack_m1)?;
        v.visit_component("unpack_m2", self.unpack_m2)?;
        v.visit_component("unpack_m3", self.unpack_m3)?;
        Ok(())
    }
}
pub struct RhoMinor1_0__2__SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static RhoMinor1_0__2_Arm1_SuperLayout,
}
impl risc0_zkp::layout::Component for RhoMinor1_0__2__SuperLayout {
    fn ty_name(&self) -> &'static str {
        "RhoMinor1_0__2__SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct RhoMinor1_0__2_Layout {
    pub _super: &'static RhoMinor1_0__2__SuperLayout,
    pub unpack_xy1: &'static ToBits_22_Layout,
    pub unpack_xy2: &'static ToBits_21_Layout,
    pub unpack_xy3: &'static ToBits_21_Layout,
    pub _0: &'static NondetRegLayout,
    pub _1: &'static NondetRegLayout,
    pub _2: &'static NondetRegLayout,
}
impl risc0_zkp::layout::Component for RhoMinor1_0__2_Layout {
    fn ty_name(&self) -> &'static str {
        "RhoMinor1_0__2_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("unpack_xy1", self.unpack_xy1)?;
        v.visit_component("unpack_xy2", self.unpack_xy2)?;
        v.visit_component("unpack_xy3", self.unpack_xy3)?;
        v.visit_component("_0", self._0)?;
        v.visit_component("_1", self._1)?;
        v.visit_component("_2", self._2)?;
        Ok(())
    }
}
pub struct RhoMinor2_0__2_Layout {
    pub _super: &'static RetTupleLayout,
    pub unpack_p1: &'static ToBits_22_Layout,
    pub unpack_p2: &'static ToBits_21_Layout,
    pub unpack_p3: &'static ToBits_21_Layout,
    pub unpack_xy1: &'static ToBits_22_Layout,
    pub unpack_xy2: &'static ToBits_21_Layout,
    pub unpack_xy3: &'static ToBits_21_Layout,
    pub _0: &'static NondetRegLayout,
    pub _1: &'static NondetRegLayout,
    pub _2: &'static NondetRegLayout,
}
impl risc0_zkp::layout::Component for RhoMinor2_0__2_Layout {
    fn ty_name(&self) -> &'static str {
        "RhoMinor2_0__2_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("unpack_p1", self.unpack_p1)?;
        v.visit_component("unpack_p2", self.unpack_p2)?;
        v.visit_component("unpack_p3", self.unpack_p3)?;
        v.visit_component("unpack_xy1", self.unpack_xy1)?;
        v.visit_component("unpack_xy2", self.unpack_xy2)?;
        v.visit_component("unpack_xy3", self.unpack_xy3)?;
        v.visit_component("_0", self._0)?;
        v.visit_component("_1", self._1)?;
        v.visit_component("_2", self._2)?;
        Ok(())
    }
}
pub struct RhoMinor0_2__2_Layout {
    pub _super: &'static RetTupleLayout,
    pub unpack_m1: &'static ToBits_22_Layout,
    pub unpack_m2: &'static ToBits_21_Layout,
    pub unpack_m3: &'static ToBits_21_Layout,
    pub unpack_p1: &'static ToBits_22_Layout,
    pub unpack_p2: &'static ToBits_21_Layout,
    pub unpack_p3: &'static ToBits_21_Layout,
}
impl risc0_zkp::layout::Component for RhoMinor0_2__2_Layout {
    fn ty_name(&self) -> &'static str {
        "RhoMinor0_2__2_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("unpack_m1", self.unpack_m1)?;
        v.visit_component("unpack_m2", self.unpack_m2)?;
        v.visit_component("unpack_m3", self.unpack_m3)?;
        v.visit_component("unpack_p1", self.unpack_p1)?;
        v.visit_component("unpack_p2", self.unpack_p2)?;
        v.visit_component("unpack_p3", self.unpack_p3)?;
        Ok(())
    }
}
pub struct RhoMinor1_2__2_Arm1_SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub unpack_m1: &'static ToBits_22_Layout,
    pub unpack_m2: &'static ToBits_21_Layout,
    pub unpack_m3: &'static ToBits_21_Layout,
}
impl risc0_zkp::layout::Component for RhoMinor1_2__2_Arm1_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "RhoMinor1_2__2_Arm1_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("unpack_m1", self.unpack_m1)?;
        v.visit_component("unpack_m2", self.unpack_m2)?;
        v.visit_component("unpack_m3", self.unpack_m3)?;
        Ok(())
    }
}
pub struct RhoMinor1_2__2__SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static RhoMinor1_2__2_Arm1_SuperLayout,
}
impl risc0_zkp::layout::Component for RhoMinor1_2__2__SuperLayout {
    fn ty_name(&self) -> &'static str {
        "RhoMinor1_2__2__SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct RhoMinor1_2__2_Layout {
    pub _super: &'static RhoMinor1_2__2__SuperLayout,
    pub unpack_xy1: &'static ToBits_22_Layout,
    pub unpack_xy2: &'static ToBits_21_Layout,
    pub unpack_xy3: &'static ToBits_21_Layout,
    pub _0: &'static NondetRegLayout,
    pub _1: &'static NondetRegLayout,
    pub _2: &'static NondetRegLayout,
}
impl risc0_zkp::layout::Component for RhoMinor1_2__2_Layout {
    fn ty_name(&self) -> &'static str {
        "RhoMinor1_2__2_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("unpack_xy1", self.unpack_xy1)?;
        v.visit_component("unpack_xy2", self.unpack_xy2)?;
        v.visit_component("unpack_xy3", self.unpack_xy3)?;
        v.visit_component("_0", self._0)?;
        v.visit_component("_1", self._1)?;
        v.visit_component("_2", self._2)?;
        Ok(())
    }
}
pub struct RhoMinor2_2__2_Layout {
    pub _super: &'static RetTupleLayout,
    pub unpack_p1: &'static ToBits_22_Layout,
    pub unpack_p2: &'static ToBits_21_Layout,
    pub unpack_p3: &'static ToBits_21_Layout,
    pub unpack_xy1: &'static ToBits_22_Layout,
    pub unpack_xy2: &'static ToBits_21_Layout,
    pub unpack_xy3: &'static ToBits_21_Layout,
    pub _0: &'static NondetRegLayout,
    pub _1: &'static NondetRegLayout,
    pub _2: &'static NondetRegLayout,
}
impl risc0_zkp::layout::Component for RhoMinor2_2__2_Layout {
    fn ty_name(&self) -> &'static str {
        "RhoMinor2_2__2_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("unpack_p1", self.unpack_p1)?;
        v.visit_component("unpack_p2", self.unpack_p2)?;
        v.visit_component("unpack_p3", self.unpack_p3)?;
        v.visit_component("unpack_xy1", self.unpack_xy1)?;
        v.visit_component("unpack_xy2", self.unpack_xy2)?;
        v.visit_component("unpack_xy3", self.unpack_xy3)?;
        v.visit_component("_0", self._0)?;
        v.visit_component("_1", self._1)?;
        v.visit_component("_2", self._2)?;
        Ok(())
    }
}
pub struct RhoMinor0_4__2_Layout {
    pub _super: &'static RetTupleLayout,
    pub unpack_m1: &'static ToBits_22_Layout,
    pub unpack_m2: &'static ToBits_21_Layout,
    pub unpack_m3: &'static ToBits_21_Layout,
    pub unpack_p1: &'static ToBits_22_Layout,
    pub unpack_p2: &'static ToBits_21_Layout,
    pub unpack_p3: &'static ToBits_21_Layout,
}
impl risc0_zkp::layout::Component for RhoMinor0_4__2_Layout {
    fn ty_name(&self) -> &'static str {
        "RhoMinor0_4__2_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("unpack_m1", self.unpack_m1)?;
        v.visit_component("unpack_m2", self.unpack_m2)?;
        v.visit_component("unpack_m3", self.unpack_m3)?;
        v.visit_component("unpack_p1", self.unpack_p1)?;
        v.visit_component("unpack_p2", self.unpack_p2)?;
        v.visit_component("unpack_p3", self.unpack_p3)?;
        Ok(())
    }
}
pub struct RhoMinor1_4__2_Arm1_SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub unpack_m1: &'static ToBits_22_Layout,
    pub unpack_m2: &'static ToBits_21_Layout,
    pub unpack_m3: &'static ToBits_21_Layout,
}
impl risc0_zkp::layout::Component for RhoMinor1_4__2_Arm1_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "RhoMinor1_4__2_Arm1_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("unpack_m1", self.unpack_m1)?;
        v.visit_component("unpack_m2", self.unpack_m2)?;
        v.visit_component("unpack_m3", self.unpack_m3)?;
        Ok(())
    }
}
pub struct RhoMinor1_4__2__SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static RhoMinor1_4__2_Arm1_SuperLayout,
}
impl risc0_zkp::layout::Component for RhoMinor1_4__2__SuperLayout {
    fn ty_name(&self) -> &'static str {
        "RhoMinor1_4__2__SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct RhoMinor1_4__2_Layout {
    pub _super: &'static RhoMinor1_4__2__SuperLayout,
    pub unpack_xy1: &'static ToBits_22_Layout,
    pub unpack_xy2: &'static ToBits_21_Layout,
    pub unpack_xy3: &'static ToBits_21_Layout,
    pub _0: &'static NondetRegLayout,
    pub _1: &'static NondetRegLayout,
    pub _2: &'static NondetRegLayout,
}
impl risc0_zkp::layout::Component for RhoMinor1_4__2_Layout {
    fn ty_name(&self) -> &'static str {
        "RhoMinor1_4__2_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("unpack_xy1", self.unpack_xy1)?;
        v.visit_component("unpack_xy2", self.unpack_xy2)?;
        v.visit_component("unpack_xy3", self.unpack_xy3)?;
        v.visit_component("_0", self._0)?;
        v.visit_component("_1", self._1)?;
        v.visit_component("_2", self._2)?;
        Ok(())
    }
}
pub struct RhoMinor3_2_Arm1Arm1Arm1_SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static RetTupleLayout,
}
impl risc0_zkp::layout::Component for RhoMinor3_2_Arm1Arm1Arm1_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "RhoMinor3_2_Arm1Arm1Arm1_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct RhoMinor3_2_Arm1Arm1_SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static RhoMinor3_2_Arm1Arm1Arm1_SuperLayout,
}
impl risc0_zkp::layout::Component for RhoMinor3_2_Arm1Arm1_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "RhoMinor3_2_Arm1Arm1_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct RhoMinor3_2_Arm1_SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static RhoMinor3_2_Arm1Arm1_SuperLayout,
}
impl risc0_zkp::layout::Component for RhoMinor3_2_Arm1_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "RhoMinor3_2_Arm1_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct RhoMinor3_2__SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static RhoMinor3_2_Arm1_SuperLayout,
}
impl risc0_zkp::layout::Component for RhoMinor3_2__SuperLayout {
    fn ty_name(&self) -> &'static str {
        "RhoMinor3_2__SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct RhoMajor_2__SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RhoMinor0_0__2_Layout,
    pub arm1: &'static RhoMinor1_0__2_Layout,
    pub arm2: &'static RhoMinor2_0__2_Layout,
    pub arm3: &'static RhoMinor0_2__2_Layout,
    pub arm4: &'static RhoMinor1_2__2_Layout,
    pub arm5: &'static RhoMinor2_2__2_Layout,
    pub arm6: &'static RhoMinor0_4__2_Layout,
    pub arm7: &'static RhoMinor1_4__2_Layout,
    pub arm8: &'static RhoMinor3_2__SuperLayout,
}
impl risc0_zkp::layout::Component for RhoMajor_2__SuperLayout {
    fn ty_name(&self) -> &'static str {
        "RhoMajor_2__SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        v.visit_component("arm2", self.arm2)?;
        v.visit_component("arm3", self.arm3)?;
        v.visit_component("arm4", self.arm4)?;
        v.visit_component("arm5", self.arm5)?;
        v.visit_component("arm6", self.arm6)?;
        v.visit_component("arm7", self.arm7)?;
        v.visit_component("arm8", self.arm8)?;
        Ok(())
    }
}
pub struct RhoMajor_2_Layout {
    pub _super: &'static RhoMajor_2__SuperLayout,
    pub minor_onehot: &'static OneHot_9_Layout,
}
impl risc0_zkp::layout::Component for RhoMajor_2_Layout {
    fn ty_name(&self) -> &'static str {
        "RhoMajor_2_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("minor_onehot", self.minor_onehot)?;
        Ok(())
    }
}
pub struct RhoMinor0_0__3_Layout {
    pub _super: &'static RetTupleLayout,
    pub unpack_m1: &'static ToBits_22_Layout,
    pub unpack_m2: &'static ToBits_21_Layout,
    pub unpack_m3: &'static ToBits_21_Layout,
    pub unpack_p1: &'static ToBits_22_Layout,
    pub unpack_p2: &'static ToBits_21_Layout,
    pub unpack_p3: &'static ToBits_21_Layout,
}
impl risc0_zkp::layout::Component for RhoMinor0_0__3_Layout {
    fn ty_name(&self) -> &'static str {
        "RhoMinor0_0__3_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("unpack_m1", self.unpack_m1)?;
        v.visit_component("unpack_m2", self.unpack_m2)?;
        v.visit_component("unpack_m3", self.unpack_m3)?;
        v.visit_component("unpack_p1", self.unpack_p1)?;
        v.visit_component("unpack_p2", self.unpack_p2)?;
        v.visit_component("unpack_p3", self.unpack_p3)?;
        Ok(())
    }
}
pub struct RhoMinor1_0__3_Arm1_SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub unpack_m1: &'static ToBits_22_Layout,
    pub unpack_m2: &'static ToBits_21_Layout,
    pub unpack_m3: &'static ToBits_21_Layout,
}
impl risc0_zkp::layout::Component for RhoMinor1_0__3_Arm1_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "RhoMinor1_0__3_Arm1_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("unpack_m1", self.unpack_m1)?;
        v.visit_component("unpack_m2", self.unpack_m2)?;
        v.visit_component("unpack_m3", self.unpack_m3)?;
        Ok(())
    }
}
pub struct RhoMinor1_0__3__SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static RhoMinor1_0__3_Arm1_SuperLayout,
}
impl risc0_zkp::layout::Component for RhoMinor1_0__3__SuperLayout {
    fn ty_name(&self) -> &'static str {
        "RhoMinor1_0__3__SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct RhoMinor1_0__3_Layout {
    pub _super: &'static RhoMinor1_0__3__SuperLayout,
    pub unpack_xy1: &'static ToBits_22_Layout,
    pub unpack_xy2: &'static ToBits_21_Layout,
    pub unpack_xy3: &'static ToBits_21_Layout,
    pub _0: &'static NondetRegLayout,
    pub _1: &'static NondetRegLayout,
    pub _2: &'static NondetRegLayout,
}
impl risc0_zkp::layout::Component for RhoMinor1_0__3_Layout {
    fn ty_name(&self) -> &'static str {
        "RhoMinor1_0__3_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("unpack_xy1", self.unpack_xy1)?;
        v.visit_component("unpack_xy2", self.unpack_xy2)?;
        v.visit_component("unpack_xy3", self.unpack_xy3)?;
        v.visit_component("_0", self._0)?;
        v.visit_component("_1", self._1)?;
        v.visit_component("_2", self._2)?;
        Ok(())
    }
}
pub struct RhoMinor2_0__3_Layout {
    pub _super: &'static RetTupleLayout,
    pub unpack_p1: &'static ToBits_22_Layout,
    pub unpack_p2: &'static ToBits_21_Layout,
    pub unpack_p3: &'static ToBits_21_Layout,
    pub unpack_xy1: &'static ToBits_22_Layout,
    pub unpack_xy2: &'static ToBits_21_Layout,
    pub unpack_xy3: &'static ToBits_21_Layout,
    pub _0: &'static NondetRegLayout,
    pub _1: &'static NondetRegLayout,
    pub _2: &'static NondetRegLayout,
}
impl risc0_zkp::layout::Component for RhoMinor2_0__3_Layout {
    fn ty_name(&self) -> &'static str {
        "RhoMinor2_0__3_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("unpack_p1", self.unpack_p1)?;
        v.visit_component("unpack_p2", self.unpack_p2)?;
        v.visit_component("unpack_p3", self.unpack_p3)?;
        v.visit_component("unpack_xy1", self.unpack_xy1)?;
        v.visit_component("unpack_xy2", self.unpack_xy2)?;
        v.visit_component("unpack_xy3", self.unpack_xy3)?;
        v.visit_component("_0", self._0)?;
        v.visit_component("_1", self._1)?;
        v.visit_component("_2", self._2)?;
        Ok(())
    }
}
pub struct RhoMinor0_2__3_Layout {
    pub _super: &'static RetTupleLayout,
    pub unpack_m1: &'static ToBits_22_Layout,
    pub unpack_m2: &'static ToBits_21_Layout,
    pub unpack_m3: &'static ToBits_21_Layout,
    pub unpack_p1: &'static ToBits_22_Layout,
    pub unpack_p2: &'static ToBits_21_Layout,
    pub unpack_p3: &'static ToBits_21_Layout,
}
impl risc0_zkp::layout::Component for RhoMinor0_2__3_Layout {
    fn ty_name(&self) -> &'static str {
        "RhoMinor0_2__3_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("unpack_m1", self.unpack_m1)?;
        v.visit_component("unpack_m2", self.unpack_m2)?;
        v.visit_component("unpack_m3", self.unpack_m3)?;
        v.visit_component("unpack_p1", self.unpack_p1)?;
        v.visit_component("unpack_p2", self.unpack_p2)?;
        v.visit_component("unpack_p3", self.unpack_p3)?;
        Ok(())
    }
}
pub struct RhoMinor1_2__3_Arm1_SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub unpack_m1: &'static ToBits_22_Layout,
    pub unpack_m2: &'static ToBits_21_Layout,
    pub unpack_m3: &'static ToBits_21_Layout,
}
impl risc0_zkp::layout::Component for RhoMinor1_2__3_Arm1_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "RhoMinor1_2__3_Arm1_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("unpack_m1", self.unpack_m1)?;
        v.visit_component("unpack_m2", self.unpack_m2)?;
        v.visit_component("unpack_m3", self.unpack_m3)?;
        Ok(())
    }
}
pub struct RhoMinor1_2__3__SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static RhoMinor1_2__3_Arm1_SuperLayout,
}
impl risc0_zkp::layout::Component for RhoMinor1_2__3__SuperLayout {
    fn ty_name(&self) -> &'static str {
        "RhoMinor1_2__3__SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct RhoMinor1_2__3_Layout {
    pub _super: &'static RhoMinor1_2__3__SuperLayout,
    pub unpack_xy1: &'static ToBits_22_Layout,
    pub unpack_xy2: &'static ToBits_21_Layout,
    pub unpack_xy3: &'static ToBits_21_Layout,
    pub _0: &'static NondetRegLayout,
    pub _1: &'static NondetRegLayout,
    pub _2: &'static NondetRegLayout,
}
impl risc0_zkp::layout::Component for RhoMinor1_2__3_Layout {
    fn ty_name(&self) -> &'static str {
        "RhoMinor1_2__3_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("unpack_xy1", self.unpack_xy1)?;
        v.visit_component("unpack_xy2", self.unpack_xy2)?;
        v.visit_component("unpack_xy3", self.unpack_xy3)?;
        v.visit_component("_0", self._0)?;
        v.visit_component("_1", self._1)?;
        v.visit_component("_2", self._2)?;
        Ok(())
    }
}
pub struct RhoMinor2_2__3_Layout {
    pub _super: &'static RetTupleLayout,
    pub unpack_p1: &'static ToBits_22_Layout,
    pub unpack_p2: &'static ToBits_21_Layout,
    pub unpack_p3: &'static ToBits_21_Layout,
    pub unpack_xy1: &'static ToBits_22_Layout,
    pub unpack_xy2: &'static ToBits_21_Layout,
    pub unpack_xy3: &'static ToBits_21_Layout,
    pub _0: &'static NondetRegLayout,
    pub _1: &'static NondetRegLayout,
    pub _2: &'static NondetRegLayout,
}
impl risc0_zkp::layout::Component for RhoMinor2_2__3_Layout {
    fn ty_name(&self) -> &'static str {
        "RhoMinor2_2__3_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("unpack_p1", self.unpack_p1)?;
        v.visit_component("unpack_p2", self.unpack_p2)?;
        v.visit_component("unpack_p3", self.unpack_p3)?;
        v.visit_component("unpack_xy1", self.unpack_xy1)?;
        v.visit_component("unpack_xy2", self.unpack_xy2)?;
        v.visit_component("unpack_xy3", self.unpack_xy3)?;
        v.visit_component("_0", self._0)?;
        v.visit_component("_1", self._1)?;
        v.visit_component("_2", self._2)?;
        Ok(())
    }
}
pub struct RhoMinor0_4__3_Layout {
    pub _super: &'static RetTupleLayout,
    pub unpack_m1: &'static ToBits_22_Layout,
    pub unpack_m2: &'static ToBits_21_Layout,
    pub unpack_m3: &'static ToBits_21_Layout,
    pub unpack_p1: &'static ToBits_22_Layout,
    pub unpack_p2: &'static ToBits_21_Layout,
    pub unpack_p3: &'static ToBits_21_Layout,
}
impl risc0_zkp::layout::Component for RhoMinor0_4__3_Layout {
    fn ty_name(&self) -> &'static str {
        "RhoMinor0_4__3_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("unpack_m1", self.unpack_m1)?;
        v.visit_component("unpack_m2", self.unpack_m2)?;
        v.visit_component("unpack_m3", self.unpack_m3)?;
        v.visit_component("unpack_p1", self.unpack_p1)?;
        v.visit_component("unpack_p2", self.unpack_p2)?;
        v.visit_component("unpack_p3", self.unpack_p3)?;
        Ok(())
    }
}
pub struct RhoMinor1_4__3_Arm1_SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub unpack_m1: &'static ToBits_22_Layout,
    pub unpack_m2: &'static ToBits_21_Layout,
    pub unpack_m3: &'static ToBits_21_Layout,
}
impl risc0_zkp::layout::Component for RhoMinor1_4__3_Arm1_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "RhoMinor1_4__3_Arm1_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("unpack_m1", self.unpack_m1)?;
        v.visit_component("unpack_m2", self.unpack_m2)?;
        v.visit_component("unpack_m3", self.unpack_m3)?;
        Ok(())
    }
}
pub struct RhoMinor1_4__3__SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static RhoMinor1_4__3_Arm1_SuperLayout,
}
impl risc0_zkp::layout::Component for RhoMinor1_4__3__SuperLayout {
    fn ty_name(&self) -> &'static str {
        "RhoMinor1_4__3__SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct RhoMinor1_4__3_Layout {
    pub _super: &'static RhoMinor1_4__3__SuperLayout,
    pub unpack_xy1: &'static ToBits_22_Layout,
    pub unpack_xy2: &'static ToBits_21_Layout,
    pub unpack_xy3: &'static ToBits_21_Layout,
    pub _0: &'static NondetRegLayout,
    pub _1: &'static NondetRegLayout,
    pub _2: &'static NondetRegLayout,
}
impl risc0_zkp::layout::Component for RhoMinor1_4__3_Layout {
    fn ty_name(&self) -> &'static str {
        "RhoMinor1_4__3_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("unpack_xy1", self.unpack_xy1)?;
        v.visit_component("unpack_xy2", self.unpack_xy2)?;
        v.visit_component("unpack_xy3", self.unpack_xy3)?;
        v.visit_component("_0", self._0)?;
        v.visit_component("_1", self._1)?;
        v.visit_component("_2", self._2)?;
        Ok(())
    }
}
pub struct RhoMinor3_3_Arm1Arm1Arm1_SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static RetTupleLayout,
}
impl risc0_zkp::layout::Component for RhoMinor3_3_Arm1Arm1Arm1_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "RhoMinor3_3_Arm1Arm1Arm1_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct RhoMinor3_3_Arm1Arm1_SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static RhoMinor3_3_Arm1Arm1Arm1_SuperLayout,
}
impl risc0_zkp::layout::Component for RhoMinor3_3_Arm1Arm1_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "RhoMinor3_3_Arm1Arm1_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct RhoMinor3_3_Arm1_SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static RhoMinor3_3_Arm1Arm1_SuperLayout,
}
impl risc0_zkp::layout::Component for RhoMinor3_3_Arm1_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "RhoMinor3_3_Arm1_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct RhoMinor3_3__SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static RhoMinor3_3_Arm1_SuperLayout,
}
impl risc0_zkp::layout::Component for RhoMinor3_3__SuperLayout {
    fn ty_name(&self) -> &'static str {
        "RhoMinor3_3__SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct RhoMajor_3__SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RhoMinor0_0__3_Layout,
    pub arm1: &'static RhoMinor1_0__3_Layout,
    pub arm2: &'static RhoMinor2_0__3_Layout,
    pub arm3: &'static RhoMinor0_2__3_Layout,
    pub arm4: &'static RhoMinor1_2__3_Layout,
    pub arm5: &'static RhoMinor2_2__3_Layout,
    pub arm6: &'static RhoMinor0_4__3_Layout,
    pub arm7: &'static RhoMinor1_4__3_Layout,
    pub arm8: &'static RhoMinor3_3__SuperLayout,
}
impl risc0_zkp::layout::Component for RhoMajor_3__SuperLayout {
    fn ty_name(&self) -> &'static str {
        "RhoMajor_3__SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        v.visit_component("arm2", self.arm2)?;
        v.visit_component("arm3", self.arm3)?;
        v.visit_component("arm4", self.arm4)?;
        v.visit_component("arm5", self.arm5)?;
        v.visit_component("arm6", self.arm6)?;
        v.visit_component("arm7", self.arm7)?;
        v.visit_component("arm8", self.arm8)?;
        Ok(())
    }
}
pub struct RhoMajor_3_Layout {
    pub _super: &'static RhoMajor_3__SuperLayout,
    pub minor_onehot: &'static OneHot_9_Layout,
}
impl risc0_zkp::layout::Component for RhoMajor_3_Layout {
    fn ty_name(&self) -> &'static str {
        "RhoMajor_3_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("minor_onehot", self.minor_onehot)?;
        Ok(())
    }
}
pub struct RhoMinor0_0__4_Layout {
    pub _super: &'static RetTupleLayout,
    pub unpack_m1: &'static ToBits_22_Layout,
    pub unpack_m2: &'static ToBits_21_Layout,
    pub unpack_m3: &'static ToBits_21_Layout,
    pub unpack_p1: &'static ToBits_22_Layout,
    pub unpack_p2: &'static ToBits_21_Layout,
    pub unpack_p3: &'static ToBits_21_Layout,
}
impl risc0_zkp::layout::Component for RhoMinor0_0__4_Layout {
    fn ty_name(&self) -> &'static str {
        "RhoMinor0_0__4_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("unpack_m1", self.unpack_m1)?;
        v.visit_component("unpack_m2", self.unpack_m2)?;
        v.visit_component("unpack_m3", self.unpack_m3)?;
        v.visit_component("unpack_p1", self.unpack_p1)?;
        v.visit_component("unpack_p2", self.unpack_p2)?;
        v.visit_component("unpack_p3", self.unpack_p3)?;
        Ok(())
    }
}
pub struct RhoMinor1_0__4_Arm1_SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub unpack_m1: &'static ToBits_22_Layout,
    pub unpack_m2: &'static ToBits_21_Layout,
    pub unpack_m3: &'static ToBits_21_Layout,
}
impl risc0_zkp::layout::Component for RhoMinor1_0__4_Arm1_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "RhoMinor1_0__4_Arm1_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("unpack_m1", self.unpack_m1)?;
        v.visit_component("unpack_m2", self.unpack_m2)?;
        v.visit_component("unpack_m3", self.unpack_m3)?;
        Ok(())
    }
}
pub struct RhoMinor1_0__4__SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static RhoMinor1_0__4_Arm1_SuperLayout,
}
impl risc0_zkp::layout::Component for RhoMinor1_0__4__SuperLayout {
    fn ty_name(&self) -> &'static str {
        "RhoMinor1_0__4__SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct RhoMinor1_0__4_Layout {
    pub _super: &'static RhoMinor1_0__4__SuperLayout,
    pub unpack_xy1: &'static ToBits_22_Layout,
    pub unpack_xy2: &'static ToBits_21_Layout,
    pub unpack_xy3: &'static ToBits_21_Layout,
    pub _0: &'static NondetRegLayout,
    pub _1: &'static NondetRegLayout,
    pub _2: &'static NondetRegLayout,
}
impl risc0_zkp::layout::Component for RhoMinor1_0__4_Layout {
    fn ty_name(&self) -> &'static str {
        "RhoMinor1_0__4_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("unpack_xy1", self.unpack_xy1)?;
        v.visit_component("unpack_xy2", self.unpack_xy2)?;
        v.visit_component("unpack_xy3", self.unpack_xy3)?;
        v.visit_component("_0", self._0)?;
        v.visit_component("_1", self._1)?;
        v.visit_component("_2", self._2)?;
        Ok(())
    }
}
pub struct RhoMinor2_0__4_Layout {
    pub _super: &'static RetTupleLayout,
    pub unpack_p1: &'static ToBits_22_Layout,
    pub unpack_p2: &'static ToBits_21_Layout,
    pub unpack_p3: &'static ToBits_21_Layout,
    pub unpack_xy1: &'static ToBits_22_Layout,
    pub unpack_xy2: &'static ToBits_21_Layout,
    pub unpack_xy3: &'static ToBits_21_Layout,
    pub _0: &'static NondetRegLayout,
    pub _1: &'static NondetRegLayout,
    pub _2: &'static NondetRegLayout,
}
impl risc0_zkp::layout::Component for RhoMinor2_0__4_Layout {
    fn ty_name(&self) -> &'static str {
        "RhoMinor2_0__4_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("unpack_p1", self.unpack_p1)?;
        v.visit_component("unpack_p2", self.unpack_p2)?;
        v.visit_component("unpack_p3", self.unpack_p3)?;
        v.visit_component("unpack_xy1", self.unpack_xy1)?;
        v.visit_component("unpack_xy2", self.unpack_xy2)?;
        v.visit_component("unpack_xy3", self.unpack_xy3)?;
        v.visit_component("_0", self._0)?;
        v.visit_component("_1", self._1)?;
        v.visit_component("_2", self._2)?;
        Ok(())
    }
}
pub struct RhoMinor0_2__4_Layout {
    pub _super: &'static RetTupleLayout,
    pub unpack_m1: &'static ToBits_22_Layout,
    pub unpack_m2: &'static ToBits_21_Layout,
    pub unpack_m3: &'static ToBits_21_Layout,
    pub unpack_p1: &'static ToBits_22_Layout,
    pub unpack_p2: &'static ToBits_21_Layout,
    pub unpack_p3: &'static ToBits_21_Layout,
}
impl risc0_zkp::layout::Component for RhoMinor0_2__4_Layout {
    fn ty_name(&self) -> &'static str {
        "RhoMinor0_2__4_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("unpack_m1", self.unpack_m1)?;
        v.visit_component("unpack_m2", self.unpack_m2)?;
        v.visit_component("unpack_m3", self.unpack_m3)?;
        v.visit_component("unpack_p1", self.unpack_p1)?;
        v.visit_component("unpack_p2", self.unpack_p2)?;
        v.visit_component("unpack_p3", self.unpack_p3)?;
        Ok(())
    }
}
pub struct RhoMinor1_2__4_Arm1_SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub unpack_m1: &'static ToBits_22_Layout,
    pub unpack_m2: &'static ToBits_21_Layout,
    pub unpack_m3: &'static ToBits_21_Layout,
}
impl risc0_zkp::layout::Component for RhoMinor1_2__4_Arm1_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "RhoMinor1_2__4_Arm1_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("unpack_m1", self.unpack_m1)?;
        v.visit_component("unpack_m2", self.unpack_m2)?;
        v.visit_component("unpack_m3", self.unpack_m3)?;
        Ok(())
    }
}
pub struct RhoMinor1_2__4__SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static RhoMinor1_2__4_Arm1_SuperLayout,
}
impl risc0_zkp::layout::Component for RhoMinor1_2__4__SuperLayout {
    fn ty_name(&self) -> &'static str {
        "RhoMinor1_2__4__SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct RhoMinor1_2__4_Layout {
    pub _super: &'static RhoMinor1_2__4__SuperLayout,
    pub unpack_xy1: &'static ToBits_22_Layout,
    pub unpack_xy2: &'static ToBits_21_Layout,
    pub unpack_xy3: &'static ToBits_21_Layout,
    pub _0: &'static NondetRegLayout,
    pub _1: &'static NondetRegLayout,
    pub _2: &'static NondetRegLayout,
}
impl risc0_zkp::layout::Component for RhoMinor1_2__4_Layout {
    fn ty_name(&self) -> &'static str {
        "RhoMinor1_2__4_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("unpack_xy1", self.unpack_xy1)?;
        v.visit_component("unpack_xy2", self.unpack_xy2)?;
        v.visit_component("unpack_xy3", self.unpack_xy3)?;
        v.visit_component("_0", self._0)?;
        v.visit_component("_1", self._1)?;
        v.visit_component("_2", self._2)?;
        Ok(())
    }
}
pub struct RhoMinor2_2__4_Layout {
    pub _super: &'static RetTupleLayout,
    pub unpack_p1: &'static ToBits_22_Layout,
    pub unpack_p2: &'static ToBits_21_Layout,
    pub unpack_p3: &'static ToBits_21_Layout,
    pub unpack_xy1: &'static ToBits_22_Layout,
    pub unpack_xy2: &'static ToBits_21_Layout,
    pub unpack_xy3: &'static ToBits_21_Layout,
    pub _0: &'static NondetRegLayout,
    pub _1: &'static NondetRegLayout,
    pub _2: &'static NondetRegLayout,
}
impl risc0_zkp::layout::Component for RhoMinor2_2__4_Layout {
    fn ty_name(&self) -> &'static str {
        "RhoMinor2_2__4_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("unpack_p1", self.unpack_p1)?;
        v.visit_component("unpack_p2", self.unpack_p2)?;
        v.visit_component("unpack_p3", self.unpack_p3)?;
        v.visit_component("unpack_xy1", self.unpack_xy1)?;
        v.visit_component("unpack_xy2", self.unpack_xy2)?;
        v.visit_component("unpack_xy3", self.unpack_xy3)?;
        v.visit_component("_0", self._0)?;
        v.visit_component("_1", self._1)?;
        v.visit_component("_2", self._2)?;
        Ok(())
    }
}
pub struct RhoMinor0_4__4_Layout {
    pub _super: &'static RetTupleLayout,
    pub unpack_m1: &'static ToBits_22_Layout,
    pub unpack_m2: &'static ToBits_21_Layout,
    pub unpack_m3: &'static ToBits_21_Layout,
    pub unpack_p1: &'static ToBits_22_Layout,
    pub unpack_p2: &'static ToBits_21_Layout,
    pub unpack_p3: &'static ToBits_21_Layout,
}
impl risc0_zkp::layout::Component for RhoMinor0_4__4_Layout {
    fn ty_name(&self) -> &'static str {
        "RhoMinor0_4__4_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("unpack_m1", self.unpack_m1)?;
        v.visit_component("unpack_m2", self.unpack_m2)?;
        v.visit_component("unpack_m3", self.unpack_m3)?;
        v.visit_component("unpack_p1", self.unpack_p1)?;
        v.visit_component("unpack_p2", self.unpack_p2)?;
        v.visit_component("unpack_p3", self.unpack_p3)?;
        Ok(())
    }
}
pub struct RhoMinor1_4__4_Arm1_SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub unpack_m1: &'static ToBits_22_Layout,
    pub unpack_m2: &'static ToBits_21_Layout,
    pub unpack_m3: &'static ToBits_21_Layout,
}
impl risc0_zkp::layout::Component for RhoMinor1_4__4_Arm1_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "RhoMinor1_4__4_Arm1_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("unpack_m1", self.unpack_m1)?;
        v.visit_component("unpack_m2", self.unpack_m2)?;
        v.visit_component("unpack_m3", self.unpack_m3)?;
        Ok(())
    }
}
pub struct RhoMinor1_4__4__SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static RhoMinor1_4__4_Arm1_SuperLayout,
}
impl risc0_zkp::layout::Component for RhoMinor1_4__4__SuperLayout {
    fn ty_name(&self) -> &'static str {
        "RhoMinor1_4__4__SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct RhoMinor1_4__4_Layout {
    pub _super: &'static RhoMinor1_4__4__SuperLayout,
    pub unpack_xy1: &'static ToBits_22_Layout,
    pub unpack_xy2: &'static ToBits_21_Layout,
    pub unpack_xy3: &'static ToBits_21_Layout,
    pub _0: &'static NondetRegLayout,
    pub _1: &'static NondetRegLayout,
    pub _2: &'static NondetRegLayout,
}
impl risc0_zkp::layout::Component for RhoMinor1_4__4_Layout {
    fn ty_name(&self) -> &'static str {
        "RhoMinor1_4__4_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("unpack_xy1", self.unpack_xy1)?;
        v.visit_component("unpack_xy2", self.unpack_xy2)?;
        v.visit_component("unpack_xy3", self.unpack_xy3)?;
        v.visit_component("_0", self._0)?;
        v.visit_component("_1", self._1)?;
        v.visit_component("_2", self._2)?;
        Ok(())
    }
}
pub struct RhoMinor3_4_Arm1Arm1Arm1_SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static RetTupleLayout,
}
impl risc0_zkp::layout::Component for RhoMinor3_4_Arm1Arm1Arm1_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "RhoMinor3_4_Arm1Arm1Arm1_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct RhoMinor3_4_Arm1Arm1_SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static RhoMinor3_4_Arm1Arm1Arm1_SuperLayout,
}
impl risc0_zkp::layout::Component for RhoMinor3_4_Arm1Arm1_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "RhoMinor3_4_Arm1Arm1_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct RhoMinor3_4_Arm1_SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static RhoMinor3_4_Arm1Arm1_SuperLayout,
}
impl risc0_zkp::layout::Component for RhoMinor3_4_Arm1_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "RhoMinor3_4_Arm1_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct RhoMinor3_4__SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static RhoMinor3_4_Arm1_SuperLayout,
}
impl risc0_zkp::layout::Component for RhoMinor3_4__SuperLayout {
    fn ty_name(&self) -> &'static str {
        "RhoMinor3_4__SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct RhoMajor_4__SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RhoMinor0_0__4_Layout,
    pub arm1: &'static RhoMinor1_0__4_Layout,
    pub arm2: &'static RhoMinor2_0__4_Layout,
    pub arm3: &'static RhoMinor0_2__4_Layout,
    pub arm4: &'static RhoMinor1_2__4_Layout,
    pub arm5: &'static RhoMinor2_2__4_Layout,
    pub arm6: &'static RhoMinor0_4__4_Layout,
    pub arm7: &'static RhoMinor1_4__4_Layout,
    pub arm8: &'static RhoMinor3_4__SuperLayout,
}
impl risc0_zkp::layout::Component for RhoMajor_4__SuperLayout {
    fn ty_name(&self) -> &'static str {
        "RhoMajor_4__SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        v.visit_component("arm2", self.arm2)?;
        v.visit_component("arm3", self.arm3)?;
        v.visit_component("arm4", self.arm4)?;
        v.visit_component("arm5", self.arm5)?;
        v.visit_component("arm6", self.arm6)?;
        v.visit_component("arm7", self.arm7)?;
        v.visit_component("arm8", self.arm8)?;
        Ok(())
    }
}
pub struct RhoMajor_4_Layout {
    pub _super: &'static RhoMajor_4__SuperLayout,
    pub minor_onehot: &'static OneHot_9_Layout,
}
impl risc0_zkp::layout::Component for RhoMajor_4_Layout {
    fn ty_name(&self) -> &'static str {
        "RhoMajor_4_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("minor_onehot", self.minor_onehot)?;
        Ok(())
    }
}
pub struct ChiMinor0_0__0_Layout {
    pub _super: &'static RetTupleLayout,
    pub unpack_1xp1: &'static ToBits_21_Layout,
    pub unpack_1xp2: &'static ToBits_21_Layout,
    pub unpack_1x: &'static ToBits_21_Layout,
    pub _0: &'static NondetRegLayout,
    pub unpack_0xp1: &'static ToBits_22_Layout,
    pub unpack_0xp2: &'static ToBits_22_Layout,
    pub unpack_0x: &'static ToBits_22_Layout,
    pub _1: &'static NondetRegLayout,
}
impl risc0_zkp::layout::Component for ChiMinor0_0__0_Layout {
    fn ty_name(&self) -> &'static str {
        "ChiMinor0_0__0_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("unpack_1xp1", self.unpack_1xp1)?;
        v.visit_component("unpack_1xp2", self.unpack_1xp2)?;
        v.visit_component("unpack_1x", self.unpack_1x)?;
        v.visit_component("_0", self._0)?;
        v.visit_component("unpack_0xp1", self.unpack_0xp1)?;
        v.visit_component("unpack_0xp2", self.unpack_0xp2)?;
        v.visit_component("unpack_0x", self.unpack_0x)?;
        v.visit_component("_1", self._1)?;
        Ok(())
    }
}
pub struct ChiMinor1_0__0_Arm1_SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub res3n: &'static NondetRegLayout,
    pub unpack_2nx: &'static ToBits_21_Layout,
    pub unpack_2nxp1: &'static ToBits_21_Layout,
    pub unpack_2nxp2: &'static ToBits_21_Layout,
}
impl risc0_zkp::layout::Component for ChiMinor1_0__0_Arm1_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "ChiMinor1_0__0_Arm1_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("res3n", self.res3n)?;
        v.visit_component("unpack_2nx", self.unpack_2nx)?;
        v.visit_component("unpack_2nxp1", self.unpack_2nxp1)?;
        v.visit_component("unpack_2nxp2", self.unpack_2nxp2)?;
        Ok(())
    }
}
pub struct ChiMinor1_0__0__SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static ChiMinor1_0__0_Arm1_SuperLayout,
}
impl risc0_zkp::layout::Component for ChiMinor1_0__0__SuperLayout {
    fn ty_name(&self) -> &'static str {
        "ChiMinor1_0__0__SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct ChiMinor1_0__0_Layout {
    pub _super: &'static ChiMinor1_0__0__SuperLayout,
    pub unpack_2x: &'static ToBits_21_Layout,
    pub unpack_2xp1: &'static ToBits_21_Layout,
    pub unpack_2xp2: &'static ToBits_21_Layout,
    pub res3: &'static NondetRegLayout,
}
impl risc0_zkp::layout::Component for ChiMinor1_0__0_Layout {
    fn ty_name(&self) -> &'static str {
        "ChiMinor1_0__0_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("unpack_2x", self.unpack_2x)?;
        v.visit_component("unpack_2xp1", self.unpack_2xp1)?;
        v.visit_component("unpack_2xp2", self.unpack_2xp2)?;
        v.visit_component("res3", self.res3)?;
        Ok(())
    }
}
pub struct ChiMinor0_1__0_Layout {
    pub _super: &'static RetTupleLayout,
    pub unpack_1xp1: &'static ToBits_21_Layout,
    pub unpack_1xp2: &'static ToBits_21_Layout,
    pub unpack_1x: &'static ToBits_21_Layout,
    pub _0: &'static NondetRegLayout,
    pub unpack_0xp1: &'static ToBits_22_Layout,
    pub unpack_0xp2: &'static ToBits_22_Layout,
    pub unpack_0x: &'static ToBits_22_Layout,
    pub _1: &'static NondetRegLayout,
}
impl risc0_zkp::layout::Component for ChiMinor0_1__0_Layout {
    fn ty_name(&self) -> &'static str {
        "ChiMinor0_1__0_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("unpack_1xp1", self.unpack_1xp1)?;
        v.visit_component("unpack_1xp2", self.unpack_1xp2)?;
        v.visit_component("unpack_1x", self.unpack_1x)?;
        v.visit_component("_0", self._0)?;
        v.visit_component("unpack_0xp1", self.unpack_0xp1)?;
        v.visit_component("unpack_0xp2", self.unpack_0xp2)?;
        v.visit_component("unpack_0x", self.unpack_0x)?;
        v.visit_component("_1", self._1)?;
        Ok(())
    }
}
pub struct ChiMinor0_2__0_Layout {
    pub _super: &'static RetTupleLayout,
    pub unpack_1xp1: &'static ToBits_21_Layout,
    pub unpack_1xp2: &'static ToBits_21_Layout,
    pub unpack_1x: &'static ToBits_21_Layout,
    pub _0: &'static NondetRegLayout,
    pub unpack_0xp1: &'static ToBits_22_Layout,
    pub unpack_0xp2: &'static ToBits_22_Layout,
    pub unpack_0x: &'static ToBits_22_Layout,
    pub _1: &'static NondetRegLayout,
}
impl risc0_zkp::layout::Component for ChiMinor0_2__0_Layout {
    fn ty_name(&self) -> &'static str {
        "ChiMinor0_2__0_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("unpack_1xp1", self.unpack_1xp1)?;
        v.visit_component("unpack_1xp2", self.unpack_1xp2)?;
        v.visit_component("unpack_1x", self.unpack_1x)?;
        v.visit_component("_0", self._0)?;
        v.visit_component("unpack_0xp1", self.unpack_0xp1)?;
        v.visit_component("unpack_0xp2", self.unpack_0xp2)?;
        v.visit_component("unpack_0x", self.unpack_0x)?;
        v.visit_component("_1", self._1)?;
        Ok(())
    }
}
pub struct ChiMinor1_2__0_Arm1_SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub res3n: &'static NondetRegLayout,
    pub unpack_2nx: &'static ToBits_21_Layout,
    pub unpack_2nxp1: &'static ToBits_21_Layout,
    pub unpack_2nxp2: &'static ToBits_21_Layout,
}
impl risc0_zkp::layout::Component for ChiMinor1_2__0_Arm1_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "ChiMinor1_2__0_Arm1_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("res3n", self.res3n)?;
        v.visit_component("unpack_2nx", self.unpack_2nx)?;
        v.visit_component("unpack_2nxp1", self.unpack_2nxp1)?;
        v.visit_component("unpack_2nxp2", self.unpack_2nxp2)?;
        Ok(())
    }
}
pub struct ChiMinor1_2__0__SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static ChiMinor1_2__0_Arm1_SuperLayout,
}
impl risc0_zkp::layout::Component for ChiMinor1_2__0__SuperLayout {
    fn ty_name(&self) -> &'static str {
        "ChiMinor1_2__0__SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct ChiMinor1_2__0_Layout {
    pub _super: &'static ChiMinor1_2__0__SuperLayout,
    pub unpack_2x: &'static ToBits_21_Layout,
    pub unpack_2xp1: &'static ToBits_21_Layout,
    pub unpack_2xp2: &'static ToBits_21_Layout,
    pub res3: &'static NondetRegLayout,
}
impl risc0_zkp::layout::Component for ChiMinor1_2__0_Layout {
    fn ty_name(&self) -> &'static str {
        "ChiMinor1_2__0_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("unpack_2x", self.unpack_2x)?;
        v.visit_component("unpack_2xp1", self.unpack_2xp1)?;
        v.visit_component("unpack_2xp2", self.unpack_2xp2)?;
        v.visit_component("res3", self.res3)?;
        Ok(())
    }
}
pub struct ChiMinor0_3__0_Layout {
    pub _super: &'static RetTupleLayout,
    pub unpack_1xp1: &'static ToBits_21_Layout,
    pub unpack_1xp2: &'static ToBits_21_Layout,
    pub unpack_1x: &'static ToBits_21_Layout,
    pub _0: &'static NondetRegLayout,
    pub unpack_0xp1: &'static ToBits_22_Layout,
    pub unpack_0xp2: &'static ToBits_22_Layout,
    pub unpack_0x: &'static ToBits_22_Layout,
    pub _1: &'static NondetRegLayout,
}
impl risc0_zkp::layout::Component for ChiMinor0_3__0_Layout {
    fn ty_name(&self) -> &'static str {
        "ChiMinor0_3__0_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("unpack_1xp1", self.unpack_1xp1)?;
        v.visit_component("unpack_1xp2", self.unpack_1xp2)?;
        v.visit_component("unpack_1x", self.unpack_1x)?;
        v.visit_component("_0", self._0)?;
        v.visit_component("unpack_0xp1", self.unpack_0xp1)?;
        v.visit_component("unpack_0xp2", self.unpack_0xp2)?;
        v.visit_component("unpack_0x", self.unpack_0x)?;
        v.visit_component("_1", self._1)?;
        Ok(())
    }
}
pub struct ChiMinor0_4__0_Layout {
    pub _super: &'static RetTupleLayout,
    pub unpack_1xp1: &'static ToBits_21_Layout,
    pub unpack_1xp2: &'static ToBits_21_Layout,
    pub unpack_1x: &'static ToBits_21_Layout,
    pub _0: &'static NondetRegLayout,
    pub unpack_0xp1: &'static ToBits_22_Layout,
    pub unpack_0xp2: &'static ToBits_22_Layout,
    pub unpack_0x: &'static ToBits_22_Layout,
    pub _1: &'static NondetRegLayout,
}
impl risc0_zkp::layout::Component for ChiMinor0_4__0_Layout {
    fn ty_name(&self) -> &'static str {
        "ChiMinor0_4__0_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("unpack_1xp1", self.unpack_1xp1)?;
        v.visit_component("unpack_1xp2", self.unpack_1xp2)?;
        v.visit_component("unpack_1x", self.unpack_1x)?;
        v.visit_component("_0", self._0)?;
        v.visit_component("unpack_0xp1", self.unpack_0xp1)?;
        v.visit_component("unpack_0xp2", self.unpack_0xp2)?;
        v.visit_component("unpack_0x", self.unpack_0x)?;
        v.visit_component("_1", self._1)?;
        Ok(())
    }
}
pub struct ChiMinor1_4__0_Arm1_SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub res3n: &'static NondetRegLayout,
    pub unpack_2nx: &'static ToBits_21_Layout,
    pub unpack_2nxp1: &'static ToBits_21_Layout,
    pub unpack_2nxp2: &'static ToBits_21_Layout,
}
impl risc0_zkp::layout::Component for ChiMinor1_4__0_Arm1_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "ChiMinor1_4__0_Arm1_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("res3n", self.res3n)?;
        v.visit_component("unpack_2nx", self.unpack_2nx)?;
        v.visit_component("unpack_2nxp1", self.unpack_2nxp1)?;
        v.visit_component("unpack_2nxp2", self.unpack_2nxp2)?;
        Ok(())
    }
}
pub struct ChiMinor1_4__0__SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static ChiMinor1_4__0_Arm1_SuperLayout,
}
impl risc0_zkp::layout::Component for ChiMinor1_4__0__SuperLayout {
    fn ty_name(&self) -> &'static str {
        "ChiMinor1_4__0__SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct ChiMinor1_4__0_Layout {
    pub _super: &'static ChiMinor1_4__0__SuperLayout,
    pub unpack_2x: &'static ToBits_21_Layout,
    pub unpack_2xp1: &'static ToBits_21_Layout,
    pub unpack_2xp2: &'static ToBits_21_Layout,
    pub res3: &'static NondetRegLayout,
}
impl risc0_zkp::layout::Component for ChiMinor1_4__0_Layout {
    fn ty_name(&self) -> &'static str {
        "ChiMinor1_4__0_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("unpack_2x", self.unpack_2x)?;
        v.visit_component("unpack_2xp1", self.unpack_2xp1)?;
        v.visit_component("unpack_2xp2", self.unpack_2xp2)?;
        v.visit_component("res3", self.res3)?;
        Ok(())
    }
}
pub struct OneHot_24_Layout {
    pub _super: &'static NondetRegLayout24LayoutArray,
}
impl risc0_zkp::layout::Component for OneHot_24_Layout {
    fn ty_name(&self) -> &'static str {
        "OneHot_24_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        Ok(())
    }
}
pub struct ChiMinor2_0_Arm1Arm1Arm1Arm1_SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub unpack_rnd: &'static OneHot_24_Layout,
    pub unpack_a002: &'static ToBits_22_Layout,
}
impl risc0_zkp::layout::Component for ChiMinor2_0_Arm1Arm1Arm1Arm1_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "ChiMinor2_0_Arm1Arm1Arm1Arm1_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("unpack_rnd", self.unpack_rnd)?;
        v.visit_component("unpack_a002", self.unpack_a002)?;
        Ok(())
    }
}
pub struct ChiMinor2_0_Arm1Arm1Arm1_SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static ChiMinor2_0_Arm1Arm1Arm1Arm1_SuperLayout,
}
impl risc0_zkp::layout::Component for ChiMinor2_0_Arm1Arm1Arm1_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "ChiMinor2_0_Arm1Arm1Arm1_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct ChiMinor2_0_Arm1Arm1_SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static ChiMinor2_0_Arm1Arm1Arm1_SuperLayout,
}
impl risc0_zkp::layout::Component for ChiMinor2_0_Arm1Arm1_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "ChiMinor2_0_Arm1Arm1_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct ChiMinor2_0_Arm1_SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static ChiMinor2_0_Arm1Arm1_SuperLayout,
}
impl risc0_zkp::layout::Component for ChiMinor2_0_Arm1_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "ChiMinor2_0_Arm1_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct ChiMinor2_0__SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static ChiMinor2_0_Arm1_SuperLayout,
}
impl risc0_zkp::layout::Component for ChiMinor2_0__SuperLayout {
    fn ty_name(&self) -> &'static str {
        "ChiMinor2_0__SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct IotaXorRcArm23_SuperLayout {
    pub inv_new_blk: &'static NondetRegLayout,
    pub prod: &'static NondetRegLayout,
}
impl risc0_zkp::layout::Component for IotaXorRcArm23_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "IotaXorRcArm23_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("inv_new_blk", self.inv_new_blk)?;
        v.visit_component("prod", self.prod)?;
        Ok(())
    }
}
pub struct IotaXorRcNxtLayout {
    pub arm23: &'static IotaXorRcArm23_SuperLayout,
}
impl risc0_zkp::layout::Component for IotaXorRcNxtLayout {
    fn ty_name(&self) -> &'static str {
        "IotaXorRcNxtLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("arm23", self.arm23)?;
        Ok(())
    }
}
pub struct IotaXorRcLayout {
    pub _super: &'static RetTupleLayout,
    pub unpack_a001: &'static ToBits_21_Layout,
    pub nxt: &'static IotaXorRcNxtLayout,
    pub unpack_a000: &'static ToBits_22_Layout,
}
impl risc0_zkp::layout::Component for IotaXorRcLayout {
    fn ty_name(&self) -> &'static str {
        "IotaXorRcLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("unpack_a001", self.unpack_a001)?;
        v.visit_component("nxt", self.nxt)?;
        v.visit_component("unpack_a000", self.unpack_a000)?;
        Ok(())
    }
}
pub struct ChiMajor_0__SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static ChiMinor0_0__0_Layout,
    pub arm1: &'static ChiMinor1_0__0_Layout,
    pub arm2: &'static ChiMinor0_1__0_Layout,
    pub arm3: &'static ChiMinor0_2__0_Layout,
    pub arm4: &'static ChiMinor1_2__0_Layout,
    pub arm5: &'static ChiMinor0_3__0_Layout,
    pub arm6: &'static ChiMinor0_4__0_Layout,
    pub arm7: &'static ChiMinor1_4__0_Layout,
    pub arm8: &'static ChiMinor2_0__SuperLayout,
    pub arm9: &'static IotaXorRcLayout,
}
impl risc0_zkp::layout::Component for ChiMajor_0__SuperLayout {
    fn ty_name(&self) -> &'static str {
        "ChiMajor_0__SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        v.visit_component("arm2", self.arm2)?;
        v.visit_component("arm3", self.arm3)?;
        v.visit_component("arm4", self.arm4)?;
        v.visit_component("arm5", self.arm5)?;
        v.visit_component("arm6", self.arm6)?;
        v.visit_component("arm7", self.arm7)?;
        v.visit_component("arm8", self.arm8)?;
        v.visit_component("arm9", self.arm9)?;
        Ok(())
    }
}
pub type NondetRegLayout10LayoutArray = [&'static NondetRegLayout; 10];
pub struct OneHot_10_Layout {
    pub _super: &'static NondetRegLayout10LayoutArray,
}
impl risc0_zkp::layout::Component for OneHot_10_Layout {
    fn ty_name(&self) -> &'static str {
        "OneHot_10_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        Ok(())
    }
}
pub struct ChiMajor_0_Layout {
    pub _super: &'static ChiMajor_0__SuperLayout,
    pub minor_onehot: &'static OneHot_10_Layout,
}
impl risc0_zkp::layout::Component for ChiMajor_0_Layout {
    fn ty_name(&self) -> &'static str {
        "ChiMajor_0_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("minor_onehot", self.minor_onehot)?;
        Ok(())
    }
}
pub struct ChiMinor0_0__1_Layout {
    pub _super: &'static RetTupleLayout,
    pub unpack_1xp1: &'static ToBits_21_Layout,
    pub unpack_1xp2: &'static ToBits_21_Layout,
    pub unpack_1x: &'static ToBits_21_Layout,
    pub _0: &'static NondetRegLayout,
    pub unpack_0xp1: &'static ToBits_22_Layout,
    pub unpack_0xp2: &'static ToBits_22_Layout,
    pub unpack_0x: &'static ToBits_22_Layout,
    pub _1: &'static NondetRegLayout,
}
impl risc0_zkp::layout::Component for ChiMinor0_0__1_Layout {
    fn ty_name(&self) -> &'static str {
        "ChiMinor0_0__1_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("unpack_1xp1", self.unpack_1xp1)?;
        v.visit_component("unpack_1xp2", self.unpack_1xp2)?;
        v.visit_component("unpack_1x", self.unpack_1x)?;
        v.visit_component("_0", self._0)?;
        v.visit_component("unpack_0xp1", self.unpack_0xp1)?;
        v.visit_component("unpack_0xp2", self.unpack_0xp2)?;
        v.visit_component("unpack_0x", self.unpack_0x)?;
        v.visit_component("_1", self._1)?;
        Ok(())
    }
}
pub struct ChiMinor1_0__1_Arm1_SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub res3n: &'static NondetRegLayout,
    pub unpack_2nx: &'static ToBits_21_Layout,
    pub unpack_2nxp1: &'static ToBits_21_Layout,
    pub unpack_2nxp2: &'static ToBits_21_Layout,
}
impl risc0_zkp::layout::Component for ChiMinor1_0__1_Arm1_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "ChiMinor1_0__1_Arm1_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("res3n", self.res3n)?;
        v.visit_component("unpack_2nx", self.unpack_2nx)?;
        v.visit_component("unpack_2nxp1", self.unpack_2nxp1)?;
        v.visit_component("unpack_2nxp2", self.unpack_2nxp2)?;
        Ok(())
    }
}
pub struct ChiMinor1_0__1__SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static ChiMinor1_0__1_Arm1_SuperLayout,
}
impl risc0_zkp::layout::Component for ChiMinor1_0__1__SuperLayout {
    fn ty_name(&self) -> &'static str {
        "ChiMinor1_0__1__SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct ChiMinor1_0__1_Layout {
    pub _super: &'static ChiMinor1_0__1__SuperLayout,
    pub unpack_2x: &'static ToBits_21_Layout,
    pub unpack_2xp1: &'static ToBits_21_Layout,
    pub unpack_2xp2: &'static ToBits_21_Layout,
    pub res3: &'static NondetRegLayout,
}
impl risc0_zkp::layout::Component for ChiMinor1_0__1_Layout {
    fn ty_name(&self) -> &'static str {
        "ChiMinor1_0__1_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("unpack_2x", self.unpack_2x)?;
        v.visit_component("unpack_2xp1", self.unpack_2xp1)?;
        v.visit_component("unpack_2xp2", self.unpack_2xp2)?;
        v.visit_component("res3", self.res3)?;
        Ok(())
    }
}
pub struct ChiMinor0_1__1_Layout {
    pub _super: &'static RetTupleLayout,
    pub unpack_1xp1: &'static ToBits_21_Layout,
    pub unpack_1xp2: &'static ToBits_21_Layout,
    pub unpack_1x: &'static ToBits_21_Layout,
    pub _0: &'static NondetRegLayout,
    pub unpack_0xp1: &'static ToBits_22_Layout,
    pub unpack_0xp2: &'static ToBits_22_Layout,
    pub unpack_0x: &'static ToBits_22_Layout,
    pub _1: &'static NondetRegLayout,
}
impl risc0_zkp::layout::Component for ChiMinor0_1__1_Layout {
    fn ty_name(&self) -> &'static str {
        "ChiMinor0_1__1_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("unpack_1xp1", self.unpack_1xp1)?;
        v.visit_component("unpack_1xp2", self.unpack_1xp2)?;
        v.visit_component("unpack_1x", self.unpack_1x)?;
        v.visit_component("_0", self._0)?;
        v.visit_component("unpack_0xp1", self.unpack_0xp1)?;
        v.visit_component("unpack_0xp2", self.unpack_0xp2)?;
        v.visit_component("unpack_0x", self.unpack_0x)?;
        v.visit_component("_1", self._1)?;
        Ok(())
    }
}
pub struct ChiMinor0_2__1_Layout {
    pub _super: &'static RetTupleLayout,
    pub unpack_1xp1: &'static ToBits_21_Layout,
    pub unpack_1xp2: &'static ToBits_21_Layout,
    pub unpack_1x: &'static ToBits_21_Layout,
    pub _0: &'static NondetRegLayout,
    pub unpack_0xp1: &'static ToBits_22_Layout,
    pub unpack_0xp2: &'static ToBits_22_Layout,
    pub unpack_0x: &'static ToBits_22_Layout,
    pub _1: &'static NondetRegLayout,
}
impl risc0_zkp::layout::Component for ChiMinor0_2__1_Layout {
    fn ty_name(&self) -> &'static str {
        "ChiMinor0_2__1_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("unpack_1xp1", self.unpack_1xp1)?;
        v.visit_component("unpack_1xp2", self.unpack_1xp2)?;
        v.visit_component("unpack_1x", self.unpack_1x)?;
        v.visit_component("_0", self._0)?;
        v.visit_component("unpack_0xp1", self.unpack_0xp1)?;
        v.visit_component("unpack_0xp2", self.unpack_0xp2)?;
        v.visit_component("unpack_0x", self.unpack_0x)?;
        v.visit_component("_1", self._1)?;
        Ok(())
    }
}
pub struct ChiMinor1_2__1_Arm1_SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub res3n: &'static NondetRegLayout,
    pub unpack_2nx: &'static ToBits_21_Layout,
    pub unpack_2nxp1: &'static ToBits_21_Layout,
    pub unpack_2nxp2: &'static ToBits_21_Layout,
}
impl risc0_zkp::layout::Component for ChiMinor1_2__1_Arm1_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "ChiMinor1_2__1_Arm1_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("res3n", self.res3n)?;
        v.visit_component("unpack_2nx", self.unpack_2nx)?;
        v.visit_component("unpack_2nxp1", self.unpack_2nxp1)?;
        v.visit_component("unpack_2nxp2", self.unpack_2nxp2)?;
        Ok(())
    }
}
pub struct ChiMinor1_2__1__SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static ChiMinor1_2__1_Arm1_SuperLayout,
}
impl risc0_zkp::layout::Component for ChiMinor1_2__1__SuperLayout {
    fn ty_name(&self) -> &'static str {
        "ChiMinor1_2__1__SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct ChiMinor1_2__1_Layout {
    pub _super: &'static ChiMinor1_2__1__SuperLayout,
    pub unpack_2x: &'static ToBits_21_Layout,
    pub unpack_2xp1: &'static ToBits_21_Layout,
    pub unpack_2xp2: &'static ToBits_21_Layout,
    pub res3: &'static NondetRegLayout,
}
impl risc0_zkp::layout::Component for ChiMinor1_2__1_Layout {
    fn ty_name(&self) -> &'static str {
        "ChiMinor1_2__1_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("unpack_2x", self.unpack_2x)?;
        v.visit_component("unpack_2xp1", self.unpack_2xp1)?;
        v.visit_component("unpack_2xp2", self.unpack_2xp2)?;
        v.visit_component("res3", self.res3)?;
        Ok(())
    }
}
pub struct ChiMinor0_3__1_Layout {
    pub _super: &'static RetTupleLayout,
    pub unpack_1xp1: &'static ToBits_21_Layout,
    pub unpack_1xp2: &'static ToBits_21_Layout,
    pub unpack_1x: &'static ToBits_21_Layout,
    pub _0: &'static NondetRegLayout,
    pub unpack_0xp1: &'static ToBits_22_Layout,
    pub unpack_0xp2: &'static ToBits_22_Layout,
    pub unpack_0x: &'static ToBits_22_Layout,
    pub _1: &'static NondetRegLayout,
}
impl risc0_zkp::layout::Component for ChiMinor0_3__1_Layout {
    fn ty_name(&self) -> &'static str {
        "ChiMinor0_3__1_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("unpack_1xp1", self.unpack_1xp1)?;
        v.visit_component("unpack_1xp2", self.unpack_1xp2)?;
        v.visit_component("unpack_1x", self.unpack_1x)?;
        v.visit_component("_0", self._0)?;
        v.visit_component("unpack_0xp1", self.unpack_0xp1)?;
        v.visit_component("unpack_0xp2", self.unpack_0xp2)?;
        v.visit_component("unpack_0x", self.unpack_0x)?;
        v.visit_component("_1", self._1)?;
        Ok(())
    }
}
pub struct ChiMinor0_4__1_Layout {
    pub _super: &'static RetTupleLayout,
    pub unpack_1xp1: &'static ToBits_21_Layout,
    pub unpack_1xp2: &'static ToBits_21_Layout,
    pub unpack_1x: &'static ToBits_21_Layout,
    pub _0: &'static NondetRegLayout,
    pub unpack_0xp1: &'static ToBits_22_Layout,
    pub unpack_0xp2: &'static ToBits_22_Layout,
    pub unpack_0x: &'static ToBits_22_Layout,
    pub _1: &'static NondetRegLayout,
}
impl risc0_zkp::layout::Component for ChiMinor0_4__1_Layout {
    fn ty_name(&self) -> &'static str {
        "ChiMinor0_4__1_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("unpack_1xp1", self.unpack_1xp1)?;
        v.visit_component("unpack_1xp2", self.unpack_1xp2)?;
        v.visit_component("unpack_1x", self.unpack_1x)?;
        v.visit_component("_0", self._0)?;
        v.visit_component("unpack_0xp1", self.unpack_0xp1)?;
        v.visit_component("unpack_0xp2", self.unpack_0xp2)?;
        v.visit_component("unpack_0x", self.unpack_0x)?;
        v.visit_component("_1", self._1)?;
        Ok(())
    }
}
pub struct ChiMinor1_4__1_Arm1_SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub res3n: &'static NondetRegLayout,
    pub unpack_2nx: &'static ToBits_21_Layout,
    pub unpack_2nxp1: &'static ToBits_21_Layout,
    pub unpack_2nxp2: &'static ToBits_21_Layout,
}
impl risc0_zkp::layout::Component for ChiMinor1_4__1_Arm1_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "ChiMinor1_4__1_Arm1_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("res3n", self.res3n)?;
        v.visit_component("unpack_2nx", self.unpack_2nx)?;
        v.visit_component("unpack_2nxp1", self.unpack_2nxp1)?;
        v.visit_component("unpack_2nxp2", self.unpack_2nxp2)?;
        Ok(())
    }
}
pub struct ChiMinor1_4__1__SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static ChiMinor1_4__1_Arm1_SuperLayout,
}
impl risc0_zkp::layout::Component for ChiMinor1_4__1__SuperLayout {
    fn ty_name(&self) -> &'static str {
        "ChiMinor1_4__1__SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct ChiMinor1_4__1_Layout {
    pub _super: &'static ChiMinor1_4__1__SuperLayout,
    pub unpack_2x: &'static ToBits_21_Layout,
    pub unpack_2xp1: &'static ToBits_21_Layout,
    pub unpack_2xp2: &'static ToBits_21_Layout,
    pub res3: &'static NondetRegLayout,
}
impl risc0_zkp::layout::Component for ChiMinor1_4__1_Layout {
    fn ty_name(&self) -> &'static str {
        "ChiMinor1_4__1_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("unpack_2x", self.unpack_2x)?;
        v.visit_component("unpack_2xp1", self.unpack_2xp1)?;
        v.visit_component("unpack_2xp2", self.unpack_2xp2)?;
        v.visit_component("res3", self.res3)?;
        Ok(())
    }
}
pub struct ChiMinor2_1_Arm1Arm1Arm1Arm1_SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub unpack_rnd: &'static OneHot_24_Layout,
    pub unpack_a002: &'static ToBits_22_Layout,
}
impl risc0_zkp::layout::Component for ChiMinor2_1_Arm1Arm1Arm1Arm1_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "ChiMinor2_1_Arm1Arm1Arm1Arm1_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("unpack_rnd", self.unpack_rnd)?;
        v.visit_component("unpack_a002", self.unpack_a002)?;
        Ok(())
    }
}
pub struct ChiMinor2_1_Arm1Arm1Arm1_SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static ChiMinor2_1_Arm1Arm1Arm1Arm1_SuperLayout,
}
impl risc0_zkp::layout::Component for ChiMinor2_1_Arm1Arm1Arm1_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "ChiMinor2_1_Arm1Arm1Arm1_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct ChiMinor2_1_Arm1Arm1_SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static ChiMinor2_1_Arm1Arm1Arm1_SuperLayout,
}
impl risc0_zkp::layout::Component for ChiMinor2_1_Arm1Arm1_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "ChiMinor2_1_Arm1Arm1_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct ChiMinor2_1_Arm1_SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static ChiMinor2_1_Arm1Arm1_SuperLayout,
}
impl risc0_zkp::layout::Component for ChiMinor2_1_Arm1_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "ChiMinor2_1_Arm1_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct ChiMinor2_1__SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static ChiMinor2_1_Arm1_SuperLayout,
}
impl risc0_zkp::layout::Component for ChiMinor2_1__SuperLayout {
    fn ty_name(&self) -> &'static str {
        "ChiMinor2_1__SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct ChiMajor_1__SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static ChiMinor0_0__1_Layout,
    pub arm1: &'static ChiMinor1_0__1_Layout,
    pub arm2: &'static ChiMinor0_1__1_Layout,
    pub arm3: &'static ChiMinor0_2__1_Layout,
    pub arm4: &'static ChiMinor1_2__1_Layout,
    pub arm5: &'static ChiMinor0_3__1_Layout,
    pub arm6: &'static ChiMinor0_4__1_Layout,
    pub arm7: &'static ChiMinor1_4__1_Layout,
    pub arm8: &'static ChiMinor2_1__SuperLayout,
    pub arm9: &'static IotaXorRcLayout,
}
impl risc0_zkp::layout::Component for ChiMajor_1__SuperLayout {
    fn ty_name(&self) -> &'static str {
        "ChiMajor_1__SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        v.visit_component("arm2", self.arm2)?;
        v.visit_component("arm3", self.arm3)?;
        v.visit_component("arm4", self.arm4)?;
        v.visit_component("arm5", self.arm5)?;
        v.visit_component("arm6", self.arm6)?;
        v.visit_component("arm7", self.arm7)?;
        v.visit_component("arm8", self.arm8)?;
        v.visit_component("arm9", self.arm9)?;
        Ok(())
    }
}
pub struct ChiMajor_1_Layout {
    pub _super: &'static ChiMajor_1__SuperLayout,
    pub minor_onehot: &'static OneHot_10_Layout,
}
impl risc0_zkp::layout::Component for ChiMajor_1_Layout {
    fn ty_name(&self) -> &'static str {
        "ChiMajor_1_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("minor_onehot", self.minor_onehot)?;
        Ok(())
    }
}
pub struct ChiMinor0_0__2_Layout {
    pub _super: &'static RetTupleLayout,
    pub unpack_1xp1: &'static ToBits_21_Layout,
    pub unpack_1xp2: &'static ToBits_21_Layout,
    pub unpack_1x: &'static ToBits_21_Layout,
    pub _0: &'static NondetRegLayout,
    pub unpack_0xp1: &'static ToBits_22_Layout,
    pub unpack_0xp2: &'static ToBits_22_Layout,
    pub unpack_0x: &'static ToBits_22_Layout,
    pub _1: &'static NondetRegLayout,
}
impl risc0_zkp::layout::Component for ChiMinor0_0__2_Layout {
    fn ty_name(&self) -> &'static str {
        "ChiMinor0_0__2_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("unpack_1xp1", self.unpack_1xp1)?;
        v.visit_component("unpack_1xp2", self.unpack_1xp2)?;
        v.visit_component("unpack_1x", self.unpack_1x)?;
        v.visit_component("_0", self._0)?;
        v.visit_component("unpack_0xp1", self.unpack_0xp1)?;
        v.visit_component("unpack_0xp2", self.unpack_0xp2)?;
        v.visit_component("unpack_0x", self.unpack_0x)?;
        v.visit_component("_1", self._1)?;
        Ok(())
    }
}
pub struct ChiMinor1_0__2_Arm1_SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub res3n: &'static NondetRegLayout,
    pub unpack_2nx: &'static ToBits_21_Layout,
    pub unpack_2nxp1: &'static ToBits_21_Layout,
    pub unpack_2nxp2: &'static ToBits_21_Layout,
}
impl risc0_zkp::layout::Component for ChiMinor1_0__2_Arm1_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "ChiMinor1_0__2_Arm1_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("res3n", self.res3n)?;
        v.visit_component("unpack_2nx", self.unpack_2nx)?;
        v.visit_component("unpack_2nxp1", self.unpack_2nxp1)?;
        v.visit_component("unpack_2nxp2", self.unpack_2nxp2)?;
        Ok(())
    }
}
pub struct ChiMinor1_0__2__SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static ChiMinor1_0__2_Arm1_SuperLayout,
}
impl risc0_zkp::layout::Component for ChiMinor1_0__2__SuperLayout {
    fn ty_name(&self) -> &'static str {
        "ChiMinor1_0__2__SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct ChiMinor1_0__2_Layout {
    pub _super: &'static ChiMinor1_0__2__SuperLayout,
    pub unpack_2x: &'static ToBits_21_Layout,
    pub unpack_2xp1: &'static ToBits_21_Layout,
    pub unpack_2xp2: &'static ToBits_21_Layout,
    pub res3: &'static NondetRegLayout,
}
impl risc0_zkp::layout::Component for ChiMinor1_0__2_Layout {
    fn ty_name(&self) -> &'static str {
        "ChiMinor1_0__2_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("unpack_2x", self.unpack_2x)?;
        v.visit_component("unpack_2xp1", self.unpack_2xp1)?;
        v.visit_component("unpack_2xp2", self.unpack_2xp2)?;
        v.visit_component("res3", self.res3)?;
        Ok(())
    }
}
pub struct ChiMinor0_1__2_Layout {
    pub _super: &'static RetTupleLayout,
    pub unpack_1xp1: &'static ToBits_21_Layout,
    pub unpack_1xp2: &'static ToBits_21_Layout,
    pub unpack_1x: &'static ToBits_21_Layout,
    pub _0: &'static NondetRegLayout,
    pub unpack_0xp1: &'static ToBits_22_Layout,
    pub unpack_0xp2: &'static ToBits_22_Layout,
    pub unpack_0x: &'static ToBits_22_Layout,
    pub _1: &'static NondetRegLayout,
}
impl risc0_zkp::layout::Component for ChiMinor0_1__2_Layout {
    fn ty_name(&self) -> &'static str {
        "ChiMinor0_1__2_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("unpack_1xp1", self.unpack_1xp1)?;
        v.visit_component("unpack_1xp2", self.unpack_1xp2)?;
        v.visit_component("unpack_1x", self.unpack_1x)?;
        v.visit_component("_0", self._0)?;
        v.visit_component("unpack_0xp1", self.unpack_0xp1)?;
        v.visit_component("unpack_0xp2", self.unpack_0xp2)?;
        v.visit_component("unpack_0x", self.unpack_0x)?;
        v.visit_component("_1", self._1)?;
        Ok(())
    }
}
pub struct ChiMinor0_2__2_Layout {
    pub _super: &'static RetTupleLayout,
    pub unpack_1xp1: &'static ToBits_21_Layout,
    pub unpack_1xp2: &'static ToBits_21_Layout,
    pub unpack_1x: &'static ToBits_21_Layout,
    pub _0: &'static NondetRegLayout,
    pub unpack_0xp1: &'static ToBits_22_Layout,
    pub unpack_0xp2: &'static ToBits_22_Layout,
    pub unpack_0x: &'static ToBits_22_Layout,
    pub _1: &'static NondetRegLayout,
}
impl risc0_zkp::layout::Component for ChiMinor0_2__2_Layout {
    fn ty_name(&self) -> &'static str {
        "ChiMinor0_2__2_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("unpack_1xp1", self.unpack_1xp1)?;
        v.visit_component("unpack_1xp2", self.unpack_1xp2)?;
        v.visit_component("unpack_1x", self.unpack_1x)?;
        v.visit_component("_0", self._0)?;
        v.visit_component("unpack_0xp1", self.unpack_0xp1)?;
        v.visit_component("unpack_0xp2", self.unpack_0xp2)?;
        v.visit_component("unpack_0x", self.unpack_0x)?;
        v.visit_component("_1", self._1)?;
        Ok(())
    }
}
pub struct ChiMinor1_2__2_Arm1_SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub res3n: &'static NondetRegLayout,
    pub unpack_2nx: &'static ToBits_21_Layout,
    pub unpack_2nxp1: &'static ToBits_21_Layout,
    pub unpack_2nxp2: &'static ToBits_21_Layout,
}
impl risc0_zkp::layout::Component for ChiMinor1_2__2_Arm1_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "ChiMinor1_2__2_Arm1_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("res3n", self.res3n)?;
        v.visit_component("unpack_2nx", self.unpack_2nx)?;
        v.visit_component("unpack_2nxp1", self.unpack_2nxp1)?;
        v.visit_component("unpack_2nxp2", self.unpack_2nxp2)?;
        Ok(())
    }
}
pub struct ChiMinor1_2__2__SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static ChiMinor1_2__2_Arm1_SuperLayout,
}
impl risc0_zkp::layout::Component for ChiMinor1_2__2__SuperLayout {
    fn ty_name(&self) -> &'static str {
        "ChiMinor1_2__2__SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct ChiMinor1_2__2_Layout {
    pub _super: &'static ChiMinor1_2__2__SuperLayout,
    pub unpack_2x: &'static ToBits_21_Layout,
    pub unpack_2xp1: &'static ToBits_21_Layout,
    pub unpack_2xp2: &'static ToBits_21_Layout,
    pub res3: &'static NondetRegLayout,
}
impl risc0_zkp::layout::Component for ChiMinor1_2__2_Layout {
    fn ty_name(&self) -> &'static str {
        "ChiMinor1_2__2_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("unpack_2x", self.unpack_2x)?;
        v.visit_component("unpack_2xp1", self.unpack_2xp1)?;
        v.visit_component("unpack_2xp2", self.unpack_2xp2)?;
        v.visit_component("res3", self.res3)?;
        Ok(())
    }
}
pub struct ChiMinor0_3__2_Layout {
    pub _super: &'static RetTupleLayout,
    pub unpack_1xp1: &'static ToBits_21_Layout,
    pub unpack_1xp2: &'static ToBits_21_Layout,
    pub unpack_1x: &'static ToBits_21_Layout,
    pub _0: &'static NondetRegLayout,
    pub unpack_0xp1: &'static ToBits_22_Layout,
    pub unpack_0xp2: &'static ToBits_22_Layout,
    pub unpack_0x: &'static ToBits_22_Layout,
    pub _1: &'static NondetRegLayout,
}
impl risc0_zkp::layout::Component for ChiMinor0_3__2_Layout {
    fn ty_name(&self) -> &'static str {
        "ChiMinor0_3__2_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("unpack_1xp1", self.unpack_1xp1)?;
        v.visit_component("unpack_1xp2", self.unpack_1xp2)?;
        v.visit_component("unpack_1x", self.unpack_1x)?;
        v.visit_component("_0", self._0)?;
        v.visit_component("unpack_0xp1", self.unpack_0xp1)?;
        v.visit_component("unpack_0xp2", self.unpack_0xp2)?;
        v.visit_component("unpack_0x", self.unpack_0x)?;
        v.visit_component("_1", self._1)?;
        Ok(())
    }
}
pub struct ChiMinor0_4__2_Layout {
    pub _super: &'static RetTupleLayout,
    pub unpack_1xp1: &'static ToBits_21_Layout,
    pub unpack_1xp2: &'static ToBits_21_Layout,
    pub unpack_1x: &'static ToBits_21_Layout,
    pub _0: &'static NondetRegLayout,
    pub unpack_0xp1: &'static ToBits_22_Layout,
    pub unpack_0xp2: &'static ToBits_22_Layout,
    pub unpack_0x: &'static ToBits_22_Layout,
    pub _1: &'static NondetRegLayout,
}
impl risc0_zkp::layout::Component for ChiMinor0_4__2_Layout {
    fn ty_name(&self) -> &'static str {
        "ChiMinor0_4__2_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("unpack_1xp1", self.unpack_1xp1)?;
        v.visit_component("unpack_1xp2", self.unpack_1xp2)?;
        v.visit_component("unpack_1x", self.unpack_1x)?;
        v.visit_component("_0", self._0)?;
        v.visit_component("unpack_0xp1", self.unpack_0xp1)?;
        v.visit_component("unpack_0xp2", self.unpack_0xp2)?;
        v.visit_component("unpack_0x", self.unpack_0x)?;
        v.visit_component("_1", self._1)?;
        Ok(())
    }
}
pub struct ChiMinor1_4__2_Arm1_SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub res3n: &'static NondetRegLayout,
    pub unpack_2nx: &'static ToBits_21_Layout,
    pub unpack_2nxp1: &'static ToBits_21_Layout,
    pub unpack_2nxp2: &'static ToBits_21_Layout,
}
impl risc0_zkp::layout::Component for ChiMinor1_4__2_Arm1_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "ChiMinor1_4__2_Arm1_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("res3n", self.res3n)?;
        v.visit_component("unpack_2nx", self.unpack_2nx)?;
        v.visit_component("unpack_2nxp1", self.unpack_2nxp1)?;
        v.visit_component("unpack_2nxp2", self.unpack_2nxp2)?;
        Ok(())
    }
}
pub struct ChiMinor1_4__2__SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static ChiMinor1_4__2_Arm1_SuperLayout,
}
impl risc0_zkp::layout::Component for ChiMinor1_4__2__SuperLayout {
    fn ty_name(&self) -> &'static str {
        "ChiMinor1_4__2__SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct ChiMinor1_4__2_Layout {
    pub _super: &'static ChiMinor1_4__2__SuperLayout,
    pub unpack_2x: &'static ToBits_21_Layout,
    pub unpack_2xp1: &'static ToBits_21_Layout,
    pub unpack_2xp2: &'static ToBits_21_Layout,
    pub res3: &'static NondetRegLayout,
}
impl risc0_zkp::layout::Component for ChiMinor1_4__2_Layout {
    fn ty_name(&self) -> &'static str {
        "ChiMinor1_4__2_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("unpack_2x", self.unpack_2x)?;
        v.visit_component("unpack_2xp1", self.unpack_2xp1)?;
        v.visit_component("unpack_2xp2", self.unpack_2xp2)?;
        v.visit_component("res3", self.res3)?;
        Ok(())
    }
}
pub struct ChiMinor2_2_Arm1Arm1Arm1Arm1_SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub unpack_rnd: &'static OneHot_24_Layout,
    pub unpack_a002: &'static ToBits_22_Layout,
}
impl risc0_zkp::layout::Component for ChiMinor2_2_Arm1Arm1Arm1Arm1_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "ChiMinor2_2_Arm1Arm1Arm1Arm1_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("unpack_rnd", self.unpack_rnd)?;
        v.visit_component("unpack_a002", self.unpack_a002)?;
        Ok(())
    }
}
pub struct ChiMinor2_2_Arm1Arm1Arm1_SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static ChiMinor2_2_Arm1Arm1Arm1Arm1_SuperLayout,
}
impl risc0_zkp::layout::Component for ChiMinor2_2_Arm1Arm1Arm1_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "ChiMinor2_2_Arm1Arm1Arm1_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct ChiMinor2_2_Arm1Arm1_SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static ChiMinor2_2_Arm1Arm1Arm1_SuperLayout,
}
impl risc0_zkp::layout::Component for ChiMinor2_2_Arm1Arm1_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "ChiMinor2_2_Arm1Arm1_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct ChiMinor2_2_Arm1_SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static ChiMinor2_2_Arm1Arm1_SuperLayout,
}
impl risc0_zkp::layout::Component for ChiMinor2_2_Arm1_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "ChiMinor2_2_Arm1_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct ChiMinor2_2__SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static ChiMinor2_2_Arm1_SuperLayout,
}
impl risc0_zkp::layout::Component for ChiMinor2_2__SuperLayout {
    fn ty_name(&self) -> &'static str {
        "ChiMinor2_2__SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct ChiMajor_2__SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static ChiMinor0_0__2_Layout,
    pub arm1: &'static ChiMinor1_0__2_Layout,
    pub arm2: &'static ChiMinor0_1__2_Layout,
    pub arm3: &'static ChiMinor0_2__2_Layout,
    pub arm4: &'static ChiMinor1_2__2_Layout,
    pub arm5: &'static ChiMinor0_3__2_Layout,
    pub arm6: &'static ChiMinor0_4__2_Layout,
    pub arm7: &'static ChiMinor1_4__2_Layout,
    pub arm8: &'static ChiMinor2_2__SuperLayout,
    pub arm9: &'static IotaXorRcLayout,
}
impl risc0_zkp::layout::Component for ChiMajor_2__SuperLayout {
    fn ty_name(&self) -> &'static str {
        "ChiMajor_2__SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        v.visit_component("arm2", self.arm2)?;
        v.visit_component("arm3", self.arm3)?;
        v.visit_component("arm4", self.arm4)?;
        v.visit_component("arm5", self.arm5)?;
        v.visit_component("arm6", self.arm6)?;
        v.visit_component("arm7", self.arm7)?;
        v.visit_component("arm8", self.arm8)?;
        v.visit_component("arm9", self.arm9)?;
        Ok(())
    }
}
pub struct ChiMajor_2_Layout {
    pub _super: &'static ChiMajor_2__SuperLayout,
    pub minor_onehot: &'static OneHot_10_Layout,
}
impl risc0_zkp::layout::Component for ChiMajor_2_Layout {
    fn ty_name(&self) -> &'static str {
        "ChiMajor_2_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("minor_onehot", self.minor_onehot)?;
        Ok(())
    }
}
pub struct ChiMinor0_0__3_Layout {
    pub _super: &'static RetTupleLayout,
    pub unpack_1xp1: &'static ToBits_21_Layout,
    pub unpack_1xp2: &'static ToBits_21_Layout,
    pub unpack_1x: &'static ToBits_21_Layout,
    pub _0: &'static NondetRegLayout,
    pub unpack_0xp1: &'static ToBits_22_Layout,
    pub unpack_0xp2: &'static ToBits_22_Layout,
    pub unpack_0x: &'static ToBits_22_Layout,
    pub _1: &'static NondetRegLayout,
}
impl risc0_zkp::layout::Component for ChiMinor0_0__3_Layout {
    fn ty_name(&self) -> &'static str {
        "ChiMinor0_0__3_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("unpack_1xp1", self.unpack_1xp1)?;
        v.visit_component("unpack_1xp2", self.unpack_1xp2)?;
        v.visit_component("unpack_1x", self.unpack_1x)?;
        v.visit_component("_0", self._0)?;
        v.visit_component("unpack_0xp1", self.unpack_0xp1)?;
        v.visit_component("unpack_0xp2", self.unpack_0xp2)?;
        v.visit_component("unpack_0x", self.unpack_0x)?;
        v.visit_component("_1", self._1)?;
        Ok(())
    }
}
pub struct ChiMinor1_0__3_Arm1_SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub res3n: &'static NondetRegLayout,
    pub unpack_2nx: &'static ToBits_21_Layout,
    pub unpack_2nxp1: &'static ToBits_21_Layout,
    pub unpack_2nxp2: &'static ToBits_21_Layout,
}
impl risc0_zkp::layout::Component for ChiMinor1_0__3_Arm1_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "ChiMinor1_0__3_Arm1_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("res3n", self.res3n)?;
        v.visit_component("unpack_2nx", self.unpack_2nx)?;
        v.visit_component("unpack_2nxp1", self.unpack_2nxp1)?;
        v.visit_component("unpack_2nxp2", self.unpack_2nxp2)?;
        Ok(())
    }
}
pub struct ChiMinor1_0__3__SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static ChiMinor1_0__3_Arm1_SuperLayout,
}
impl risc0_zkp::layout::Component for ChiMinor1_0__3__SuperLayout {
    fn ty_name(&self) -> &'static str {
        "ChiMinor1_0__3__SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct ChiMinor1_0__3_Layout {
    pub _super: &'static ChiMinor1_0__3__SuperLayout,
    pub unpack_2x: &'static ToBits_21_Layout,
    pub unpack_2xp1: &'static ToBits_21_Layout,
    pub unpack_2xp2: &'static ToBits_21_Layout,
    pub res3: &'static NondetRegLayout,
}
impl risc0_zkp::layout::Component for ChiMinor1_0__3_Layout {
    fn ty_name(&self) -> &'static str {
        "ChiMinor1_0__3_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("unpack_2x", self.unpack_2x)?;
        v.visit_component("unpack_2xp1", self.unpack_2xp1)?;
        v.visit_component("unpack_2xp2", self.unpack_2xp2)?;
        v.visit_component("res3", self.res3)?;
        Ok(())
    }
}
pub struct ChiMinor0_1__3_Layout {
    pub _super: &'static RetTupleLayout,
    pub unpack_1xp1: &'static ToBits_21_Layout,
    pub unpack_1xp2: &'static ToBits_21_Layout,
    pub unpack_1x: &'static ToBits_21_Layout,
    pub _0: &'static NondetRegLayout,
    pub unpack_0xp1: &'static ToBits_22_Layout,
    pub unpack_0xp2: &'static ToBits_22_Layout,
    pub unpack_0x: &'static ToBits_22_Layout,
    pub _1: &'static NondetRegLayout,
}
impl risc0_zkp::layout::Component for ChiMinor0_1__3_Layout {
    fn ty_name(&self) -> &'static str {
        "ChiMinor0_1__3_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("unpack_1xp1", self.unpack_1xp1)?;
        v.visit_component("unpack_1xp2", self.unpack_1xp2)?;
        v.visit_component("unpack_1x", self.unpack_1x)?;
        v.visit_component("_0", self._0)?;
        v.visit_component("unpack_0xp1", self.unpack_0xp1)?;
        v.visit_component("unpack_0xp2", self.unpack_0xp2)?;
        v.visit_component("unpack_0x", self.unpack_0x)?;
        v.visit_component("_1", self._1)?;
        Ok(())
    }
}
pub struct ChiMinor0_2__3_Layout {
    pub _super: &'static RetTupleLayout,
    pub unpack_1xp1: &'static ToBits_21_Layout,
    pub unpack_1xp2: &'static ToBits_21_Layout,
    pub unpack_1x: &'static ToBits_21_Layout,
    pub _0: &'static NondetRegLayout,
    pub unpack_0xp1: &'static ToBits_22_Layout,
    pub unpack_0xp2: &'static ToBits_22_Layout,
    pub unpack_0x: &'static ToBits_22_Layout,
    pub _1: &'static NondetRegLayout,
}
impl risc0_zkp::layout::Component for ChiMinor0_2__3_Layout {
    fn ty_name(&self) -> &'static str {
        "ChiMinor0_2__3_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("unpack_1xp1", self.unpack_1xp1)?;
        v.visit_component("unpack_1xp2", self.unpack_1xp2)?;
        v.visit_component("unpack_1x", self.unpack_1x)?;
        v.visit_component("_0", self._0)?;
        v.visit_component("unpack_0xp1", self.unpack_0xp1)?;
        v.visit_component("unpack_0xp2", self.unpack_0xp2)?;
        v.visit_component("unpack_0x", self.unpack_0x)?;
        v.visit_component("_1", self._1)?;
        Ok(())
    }
}
pub struct ChiMinor1_2__3_Arm1_SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub res3n: &'static NondetRegLayout,
    pub unpack_2nx: &'static ToBits_21_Layout,
    pub unpack_2nxp1: &'static ToBits_21_Layout,
    pub unpack_2nxp2: &'static ToBits_21_Layout,
}
impl risc0_zkp::layout::Component for ChiMinor1_2__3_Arm1_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "ChiMinor1_2__3_Arm1_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("res3n", self.res3n)?;
        v.visit_component("unpack_2nx", self.unpack_2nx)?;
        v.visit_component("unpack_2nxp1", self.unpack_2nxp1)?;
        v.visit_component("unpack_2nxp2", self.unpack_2nxp2)?;
        Ok(())
    }
}
pub struct ChiMinor1_2__3__SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static ChiMinor1_2__3_Arm1_SuperLayout,
}
impl risc0_zkp::layout::Component for ChiMinor1_2__3__SuperLayout {
    fn ty_name(&self) -> &'static str {
        "ChiMinor1_2__3__SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct ChiMinor1_2__3_Layout {
    pub _super: &'static ChiMinor1_2__3__SuperLayout,
    pub unpack_2x: &'static ToBits_21_Layout,
    pub unpack_2xp1: &'static ToBits_21_Layout,
    pub unpack_2xp2: &'static ToBits_21_Layout,
    pub res3: &'static NondetRegLayout,
}
impl risc0_zkp::layout::Component for ChiMinor1_2__3_Layout {
    fn ty_name(&self) -> &'static str {
        "ChiMinor1_2__3_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("unpack_2x", self.unpack_2x)?;
        v.visit_component("unpack_2xp1", self.unpack_2xp1)?;
        v.visit_component("unpack_2xp2", self.unpack_2xp2)?;
        v.visit_component("res3", self.res3)?;
        Ok(())
    }
}
pub struct ChiMinor0_3__3_Layout {
    pub _super: &'static RetTupleLayout,
    pub unpack_1xp1: &'static ToBits_21_Layout,
    pub unpack_1xp2: &'static ToBits_21_Layout,
    pub unpack_1x: &'static ToBits_21_Layout,
    pub _0: &'static NondetRegLayout,
    pub unpack_0xp1: &'static ToBits_22_Layout,
    pub unpack_0xp2: &'static ToBits_22_Layout,
    pub unpack_0x: &'static ToBits_22_Layout,
    pub _1: &'static NondetRegLayout,
}
impl risc0_zkp::layout::Component for ChiMinor0_3__3_Layout {
    fn ty_name(&self) -> &'static str {
        "ChiMinor0_3__3_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("unpack_1xp1", self.unpack_1xp1)?;
        v.visit_component("unpack_1xp2", self.unpack_1xp2)?;
        v.visit_component("unpack_1x", self.unpack_1x)?;
        v.visit_component("_0", self._0)?;
        v.visit_component("unpack_0xp1", self.unpack_0xp1)?;
        v.visit_component("unpack_0xp2", self.unpack_0xp2)?;
        v.visit_component("unpack_0x", self.unpack_0x)?;
        v.visit_component("_1", self._1)?;
        Ok(())
    }
}
pub struct ChiMinor0_4__3_Layout {
    pub _super: &'static RetTupleLayout,
    pub unpack_1xp1: &'static ToBits_21_Layout,
    pub unpack_1xp2: &'static ToBits_21_Layout,
    pub unpack_1x: &'static ToBits_21_Layout,
    pub _0: &'static NondetRegLayout,
    pub unpack_0xp1: &'static ToBits_22_Layout,
    pub unpack_0xp2: &'static ToBits_22_Layout,
    pub unpack_0x: &'static ToBits_22_Layout,
    pub _1: &'static NondetRegLayout,
}
impl risc0_zkp::layout::Component for ChiMinor0_4__3_Layout {
    fn ty_name(&self) -> &'static str {
        "ChiMinor0_4__3_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("unpack_1xp1", self.unpack_1xp1)?;
        v.visit_component("unpack_1xp2", self.unpack_1xp2)?;
        v.visit_component("unpack_1x", self.unpack_1x)?;
        v.visit_component("_0", self._0)?;
        v.visit_component("unpack_0xp1", self.unpack_0xp1)?;
        v.visit_component("unpack_0xp2", self.unpack_0xp2)?;
        v.visit_component("unpack_0x", self.unpack_0x)?;
        v.visit_component("_1", self._1)?;
        Ok(())
    }
}
pub struct ChiMinor1_4__3_Arm1_SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub res3n: &'static NondetRegLayout,
    pub unpack_2nx: &'static ToBits_21_Layout,
    pub unpack_2nxp1: &'static ToBits_21_Layout,
    pub unpack_2nxp2: &'static ToBits_21_Layout,
}
impl risc0_zkp::layout::Component for ChiMinor1_4__3_Arm1_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "ChiMinor1_4__3_Arm1_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("res3n", self.res3n)?;
        v.visit_component("unpack_2nx", self.unpack_2nx)?;
        v.visit_component("unpack_2nxp1", self.unpack_2nxp1)?;
        v.visit_component("unpack_2nxp2", self.unpack_2nxp2)?;
        Ok(())
    }
}
pub struct ChiMinor1_4__3__SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static ChiMinor1_4__3_Arm1_SuperLayout,
}
impl risc0_zkp::layout::Component for ChiMinor1_4__3__SuperLayout {
    fn ty_name(&self) -> &'static str {
        "ChiMinor1_4__3__SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct ChiMinor1_4__3_Layout {
    pub _super: &'static ChiMinor1_4__3__SuperLayout,
    pub unpack_2x: &'static ToBits_21_Layout,
    pub unpack_2xp1: &'static ToBits_21_Layout,
    pub unpack_2xp2: &'static ToBits_21_Layout,
    pub res3: &'static NondetRegLayout,
}
impl risc0_zkp::layout::Component for ChiMinor1_4__3_Layout {
    fn ty_name(&self) -> &'static str {
        "ChiMinor1_4__3_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("unpack_2x", self.unpack_2x)?;
        v.visit_component("unpack_2xp1", self.unpack_2xp1)?;
        v.visit_component("unpack_2xp2", self.unpack_2xp2)?;
        v.visit_component("res3", self.res3)?;
        Ok(())
    }
}
pub struct ChiMinor2_3_Arm1Arm1Arm1Arm1_SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub unpack_rnd: &'static OneHot_24_Layout,
    pub unpack_a002: &'static ToBits_22_Layout,
}
impl risc0_zkp::layout::Component for ChiMinor2_3_Arm1Arm1Arm1Arm1_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "ChiMinor2_3_Arm1Arm1Arm1Arm1_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("unpack_rnd", self.unpack_rnd)?;
        v.visit_component("unpack_a002", self.unpack_a002)?;
        Ok(())
    }
}
pub struct ChiMinor2_3_Arm1Arm1Arm1_SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static ChiMinor2_3_Arm1Arm1Arm1Arm1_SuperLayout,
}
impl risc0_zkp::layout::Component for ChiMinor2_3_Arm1Arm1Arm1_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "ChiMinor2_3_Arm1Arm1Arm1_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct ChiMinor2_3_Arm1Arm1_SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static ChiMinor2_3_Arm1Arm1Arm1_SuperLayout,
}
impl risc0_zkp::layout::Component for ChiMinor2_3_Arm1Arm1_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "ChiMinor2_3_Arm1Arm1_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct ChiMinor2_3_Arm1_SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static ChiMinor2_3_Arm1Arm1_SuperLayout,
}
impl risc0_zkp::layout::Component for ChiMinor2_3_Arm1_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "ChiMinor2_3_Arm1_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct ChiMinor2_3__SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static ChiMinor2_3_Arm1_SuperLayout,
}
impl risc0_zkp::layout::Component for ChiMinor2_3__SuperLayout {
    fn ty_name(&self) -> &'static str {
        "ChiMinor2_3__SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct ChiMajor_3__SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static ChiMinor0_0__3_Layout,
    pub arm1: &'static ChiMinor1_0__3_Layout,
    pub arm2: &'static ChiMinor0_1__3_Layout,
    pub arm3: &'static ChiMinor0_2__3_Layout,
    pub arm4: &'static ChiMinor1_2__3_Layout,
    pub arm5: &'static ChiMinor0_3__3_Layout,
    pub arm6: &'static ChiMinor0_4__3_Layout,
    pub arm7: &'static ChiMinor1_4__3_Layout,
    pub arm8: &'static ChiMinor2_3__SuperLayout,
    pub arm9: &'static IotaXorRcLayout,
}
impl risc0_zkp::layout::Component for ChiMajor_3__SuperLayout {
    fn ty_name(&self) -> &'static str {
        "ChiMajor_3__SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        v.visit_component("arm2", self.arm2)?;
        v.visit_component("arm3", self.arm3)?;
        v.visit_component("arm4", self.arm4)?;
        v.visit_component("arm5", self.arm5)?;
        v.visit_component("arm6", self.arm6)?;
        v.visit_component("arm7", self.arm7)?;
        v.visit_component("arm8", self.arm8)?;
        v.visit_component("arm9", self.arm9)?;
        Ok(())
    }
}
pub struct ChiMajor_3_Layout {
    pub _super: &'static ChiMajor_3__SuperLayout,
    pub minor_onehot: &'static OneHot_10_Layout,
}
impl risc0_zkp::layout::Component for ChiMajor_3_Layout {
    fn ty_name(&self) -> &'static str {
        "ChiMajor_3_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("minor_onehot", self.minor_onehot)?;
        Ok(())
    }
}
pub struct ChiMinor0_0__4_Layout {
    pub _super: &'static RetTupleLayout,
    pub unpack_1xp1: &'static ToBits_21_Layout,
    pub unpack_1xp2: &'static ToBits_21_Layout,
    pub unpack_1x: &'static ToBits_21_Layout,
    pub _0: &'static NondetRegLayout,
    pub unpack_0xp1: &'static ToBits_22_Layout,
    pub unpack_0xp2: &'static ToBits_22_Layout,
    pub unpack_0x: &'static ToBits_22_Layout,
    pub _1: &'static NondetRegLayout,
}
impl risc0_zkp::layout::Component for ChiMinor0_0__4_Layout {
    fn ty_name(&self) -> &'static str {
        "ChiMinor0_0__4_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("unpack_1xp1", self.unpack_1xp1)?;
        v.visit_component("unpack_1xp2", self.unpack_1xp2)?;
        v.visit_component("unpack_1x", self.unpack_1x)?;
        v.visit_component("_0", self._0)?;
        v.visit_component("unpack_0xp1", self.unpack_0xp1)?;
        v.visit_component("unpack_0xp2", self.unpack_0xp2)?;
        v.visit_component("unpack_0x", self.unpack_0x)?;
        v.visit_component("_1", self._1)?;
        Ok(())
    }
}
pub struct ChiMinor1_0__4_Arm1_SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub res3n: &'static NondetRegLayout,
    pub unpack_2nx: &'static ToBits_21_Layout,
    pub unpack_2nxp1: &'static ToBits_21_Layout,
    pub unpack_2nxp2: &'static ToBits_21_Layout,
}
impl risc0_zkp::layout::Component for ChiMinor1_0__4_Arm1_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "ChiMinor1_0__4_Arm1_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("res3n", self.res3n)?;
        v.visit_component("unpack_2nx", self.unpack_2nx)?;
        v.visit_component("unpack_2nxp1", self.unpack_2nxp1)?;
        v.visit_component("unpack_2nxp2", self.unpack_2nxp2)?;
        Ok(())
    }
}
pub struct ChiMinor1_0__4__SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static ChiMinor1_0__4_Arm1_SuperLayout,
}
impl risc0_zkp::layout::Component for ChiMinor1_0__4__SuperLayout {
    fn ty_name(&self) -> &'static str {
        "ChiMinor1_0__4__SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct ChiMinor1_0__4_Layout {
    pub _super: &'static ChiMinor1_0__4__SuperLayout,
    pub unpack_2x: &'static ToBits_21_Layout,
    pub unpack_2xp1: &'static ToBits_21_Layout,
    pub unpack_2xp2: &'static ToBits_21_Layout,
    pub res3: &'static NondetRegLayout,
}
impl risc0_zkp::layout::Component for ChiMinor1_0__4_Layout {
    fn ty_name(&self) -> &'static str {
        "ChiMinor1_0__4_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("unpack_2x", self.unpack_2x)?;
        v.visit_component("unpack_2xp1", self.unpack_2xp1)?;
        v.visit_component("unpack_2xp2", self.unpack_2xp2)?;
        v.visit_component("res3", self.res3)?;
        Ok(())
    }
}
pub struct ChiMinor0_1__4_Layout {
    pub _super: &'static RetTupleLayout,
    pub unpack_1xp1: &'static ToBits_21_Layout,
    pub unpack_1xp2: &'static ToBits_21_Layout,
    pub unpack_1x: &'static ToBits_21_Layout,
    pub _0: &'static NondetRegLayout,
    pub unpack_0xp1: &'static ToBits_22_Layout,
    pub unpack_0xp2: &'static ToBits_22_Layout,
    pub unpack_0x: &'static ToBits_22_Layout,
    pub _1: &'static NondetRegLayout,
}
impl risc0_zkp::layout::Component for ChiMinor0_1__4_Layout {
    fn ty_name(&self) -> &'static str {
        "ChiMinor0_1__4_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("unpack_1xp1", self.unpack_1xp1)?;
        v.visit_component("unpack_1xp2", self.unpack_1xp2)?;
        v.visit_component("unpack_1x", self.unpack_1x)?;
        v.visit_component("_0", self._0)?;
        v.visit_component("unpack_0xp1", self.unpack_0xp1)?;
        v.visit_component("unpack_0xp2", self.unpack_0xp2)?;
        v.visit_component("unpack_0x", self.unpack_0x)?;
        v.visit_component("_1", self._1)?;
        Ok(())
    }
}
pub struct ChiMinor0_2__4_Layout {
    pub _super: &'static RetTupleLayout,
    pub unpack_1xp1: &'static ToBits_21_Layout,
    pub unpack_1xp2: &'static ToBits_21_Layout,
    pub unpack_1x: &'static ToBits_21_Layout,
    pub _0: &'static NondetRegLayout,
    pub unpack_0xp1: &'static ToBits_22_Layout,
    pub unpack_0xp2: &'static ToBits_22_Layout,
    pub unpack_0x: &'static ToBits_22_Layout,
    pub _1: &'static NondetRegLayout,
}
impl risc0_zkp::layout::Component for ChiMinor0_2__4_Layout {
    fn ty_name(&self) -> &'static str {
        "ChiMinor0_2__4_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("unpack_1xp1", self.unpack_1xp1)?;
        v.visit_component("unpack_1xp2", self.unpack_1xp2)?;
        v.visit_component("unpack_1x", self.unpack_1x)?;
        v.visit_component("_0", self._0)?;
        v.visit_component("unpack_0xp1", self.unpack_0xp1)?;
        v.visit_component("unpack_0xp2", self.unpack_0xp2)?;
        v.visit_component("unpack_0x", self.unpack_0x)?;
        v.visit_component("_1", self._1)?;
        Ok(())
    }
}
pub struct ChiMinor1_2__4_Arm1_SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub res3n: &'static NondetRegLayout,
    pub unpack_2nx: &'static ToBits_21_Layout,
    pub unpack_2nxp1: &'static ToBits_21_Layout,
    pub unpack_2nxp2: &'static ToBits_21_Layout,
}
impl risc0_zkp::layout::Component for ChiMinor1_2__4_Arm1_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "ChiMinor1_2__4_Arm1_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("res3n", self.res3n)?;
        v.visit_component("unpack_2nx", self.unpack_2nx)?;
        v.visit_component("unpack_2nxp1", self.unpack_2nxp1)?;
        v.visit_component("unpack_2nxp2", self.unpack_2nxp2)?;
        Ok(())
    }
}
pub struct ChiMinor1_2__4__SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static ChiMinor1_2__4_Arm1_SuperLayout,
}
impl risc0_zkp::layout::Component for ChiMinor1_2__4__SuperLayout {
    fn ty_name(&self) -> &'static str {
        "ChiMinor1_2__4__SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct ChiMinor1_2__4_Layout {
    pub _super: &'static ChiMinor1_2__4__SuperLayout,
    pub unpack_2x: &'static ToBits_21_Layout,
    pub unpack_2xp1: &'static ToBits_21_Layout,
    pub unpack_2xp2: &'static ToBits_21_Layout,
    pub res3: &'static NondetRegLayout,
}
impl risc0_zkp::layout::Component for ChiMinor1_2__4_Layout {
    fn ty_name(&self) -> &'static str {
        "ChiMinor1_2__4_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("unpack_2x", self.unpack_2x)?;
        v.visit_component("unpack_2xp1", self.unpack_2xp1)?;
        v.visit_component("unpack_2xp2", self.unpack_2xp2)?;
        v.visit_component("res3", self.res3)?;
        Ok(())
    }
}
pub struct ChiMinor0_3__4_Layout {
    pub _super: &'static RetTupleLayout,
    pub unpack_1xp1: &'static ToBits_21_Layout,
    pub unpack_1xp2: &'static ToBits_21_Layout,
    pub unpack_1x: &'static ToBits_21_Layout,
    pub _0: &'static NondetRegLayout,
    pub unpack_0xp1: &'static ToBits_22_Layout,
    pub unpack_0xp2: &'static ToBits_22_Layout,
    pub unpack_0x: &'static ToBits_22_Layout,
    pub _1: &'static NondetRegLayout,
}
impl risc0_zkp::layout::Component for ChiMinor0_3__4_Layout {
    fn ty_name(&self) -> &'static str {
        "ChiMinor0_3__4_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("unpack_1xp1", self.unpack_1xp1)?;
        v.visit_component("unpack_1xp2", self.unpack_1xp2)?;
        v.visit_component("unpack_1x", self.unpack_1x)?;
        v.visit_component("_0", self._0)?;
        v.visit_component("unpack_0xp1", self.unpack_0xp1)?;
        v.visit_component("unpack_0xp2", self.unpack_0xp2)?;
        v.visit_component("unpack_0x", self.unpack_0x)?;
        v.visit_component("_1", self._1)?;
        Ok(())
    }
}
pub struct ChiMinor0_4__4_Layout {
    pub _super: &'static RetTupleLayout,
    pub unpack_1xp1: &'static ToBits_21_Layout,
    pub unpack_1xp2: &'static ToBits_21_Layout,
    pub unpack_1x: &'static ToBits_21_Layout,
    pub _0: &'static NondetRegLayout,
    pub unpack_0xp1: &'static ToBits_22_Layout,
    pub unpack_0xp2: &'static ToBits_22_Layout,
    pub unpack_0x: &'static ToBits_22_Layout,
    pub _1: &'static NondetRegLayout,
}
impl risc0_zkp::layout::Component for ChiMinor0_4__4_Layout {
    fn ty_name(&self) -> &'static str {
        "ChiMinor0_4__4_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("unpack_1xp1", self.unpack_1xp1)?;
        v.visit_component("unpack_1xp2", self.unpack_1xp2)?;
        v.visit_component("unpack_1x", self.unpack_1x)?;
        v.visit_component("_0", self._0)?;
        v.visit_component("unpack_0xp1", self.unpack_0xp1)?;
        v.visit_component("unpack_0xp2", self.unpack_0xp2)?;
        v.visit_component("unpack_0x", self.unpack_0x)?;
        v.visit_component("_1", self._1)?;
        Ok(())
    }
}
pub struct ChiMinor1_4__4_Arm1_SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub res3n: &'static NondetRegLayout,
    pub unpack_2nx: &'static ToBits_21_Layout,
    pub unpack_2nxp1: &'static ToBits_21_Layout,
    pub unpack_2nxp2: &'static ToBits_21_Layout,
}
impl risc0_zkp::layout::Component for ChiMinor1_4__4_Arm1_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "ChiMinor1_4__4_Arm1_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("res3n", self.res3n)?;
        v.visit_component("unpack_2nx", self.unpack_2nx)?;
        v.visit_component("unpack_2nxp1", self.unpack_2nxp1)?;
        v.visit_component("unpack_2nxp2", self.unpack_2nxp2)?;
        Ok(())
    }
}
pub struct ChiMinor1_4__4__SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static ChiMinor1_4__4_Arm1_SuperLayout,
}
impl risc0_zkp::layout::Component for ChiMinor1_4__4__SuperLayout {
    fn ty_name(&self) -> &'static str {
        "ChiMinor1_4__4__SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct ChiMinor1_4__4_Layout {
    pub _super: &'static ChiMinor1_4__4__SuperLayout,
    pub unpack_2x: &'static ToBits_21_Layout,
    pub unpack_2xp1: &'static ToBits_21_Layout,
    pub unpack_2xp2: &'static ToBits_21_Layout,
    pub res3: &'static NondetRegLayout,
}
impl risc0_zkp::layout::Component for ChiMinor1_4__4_Layout {
    fn ty_name(&self) -> &'static str {
        "ChiMinor1_4__4_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("unpack_2x", self.unpack_2x)?;
        v.visit_component("unpack_2xp1", self.unpack_2xp1)?;
        v.visit_component("unpack_2xp2", self.unpack_2xp2)?;
        v.visit_component("res3", self.res3)?;
        Ok(())
    }
}
pub struct ChiMinor2_4_Arm1Arm1Arm1Arm1_SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub unpack_rnd: &'static OneHot_24_Layout,
    pub unpack_a002: &'static ToBits_22_Layout,
}
impl risc0_zkp::layout::Component for ChiMinor2_4_Arm1Arm1Arm1Arm1_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "ChiMinor2_4_Arm1Arm1Arm1Arm1_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("unpack_rnd", self.unpack_rnd)?;
        v.visit_component("unpack_a002", self.unpack_a002)?;
        Ok(())
    }
}
pub struct ChiMinor2_4_Arm1Arm1Arm1_SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static ChiMinor2_4_Arm1Arm1Arm1Arm1_SuperLayout,
}
impl risc0_zkp::layout::Component for ChiMinor2_4_Arm1Arm1Arm1_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "ChiMinor2_4_Arm1Arm1Arm1_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct ChiMinor2_4_Arm1Arm1_SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static ChiMinor2_4_Arm1Arm1Arm1_SuperLayout,
}
impl risc0_zkp::layout::Component for ChiMinor2_4_Arm1Arm1_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "ChiMinor2_4_Arm1Arm1_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct ChiMinor2_4_Arm1_SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static ChiMinor2_4_Arm1Arm1_SuperLayout,
}
impl risc0_zkp::layout::Component for ChiMinor2_4_Arm1_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "ChiMinor2_4_Arm1_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct ChiMinor2_4__SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static ChiMinor2_4_Arm1_SuperLayout,
}
impl risc0_zkp::layout::Component for ChiMinor2_4__SuperLayout {
    fn ty_name(&self) -> &'static str {
        "ChiMinor2_4__SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct ChiMajor_4__SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static ChiMinor0_0__4_Layout,
    pub arm1: &'static ChiMinor1_0__4_Layout,
    pub arm2: &'static ChiMinor0_1__4_Layout,
    pub arm3: &'static ChiMinor0_2__4_Layout,
    pub arm4: &'static ChiMinor1_2__4_Layout,
    pub arm5: &'static ChiMinor0_3__4_Layout,
    pub arm6: &'static ChiMinor0_4__4_Layout,
    pub arm7: &'static ChiMinor1_4__4_Layout,
    pub arm8: &'static ChiMinor2_4__SuperLayout,
    pub arm9: &'static IotaXorRcLayout,
}
impl risc0_zkp::layout::Component for ChiMajor_4__SuperLayout {
    fn ty_name(&self) -> &'static str {
        "ChiMajor_4__SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        v.visit_component("arm2", self.arm2)?;
        v.visit_component("arm3", self.arm3)?;
        v.visit_component("arm4", self.arm4)?;
        v.visit_component("arm5", self.arm5)?;
        v.visit_component("arm6", self.arm6)?;
        v.visit_component("arm7", self.arm7)?;
        v.visit_component("arm8", self.arm8)?;
        v.visit_component("arm9", self.arm9)?;
        Ok(())
    }
}
pub struct ChiMajor_4_Layout {
    pub _super: &'static ChiMajor_4__SuperLayout,
    pub minor_onehot: &'static OneHot_10_Layout,
}
impl risc0_zkp::layout::Component for ChiMajor_4_Layout {
    fn ty_name(&self) -> &'static str {
        "ChiMajor_4_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("minor_onehot", self.minor_onehot)?;
        Ok(())
    }
}
pub type NondetRegLayout16LayoutArray = [&'static NondetRegLayout; 16];
pub struct ToBits_16_Layout {
    pub _super: &'static NondetRegLayout16LayoutArray,
}
impl risc0_zkp::layout::Component for ToBits_16_Layout {
    fn ty_name(&self) -> &'static str {
        "ToBits_16_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        Ok(())
    }
}
pub struct UseOnceMemoryElementLayout {
    pub count: &'static NondetRegLayout,
    pub index: &'static NondetRegLayout,
    pub _0: &'static NondetRegLayout,
    pub _1: &'static NondetRegLayout,
    pub _2: &'static NondetRegLayout,
    pub _3: &'static NondetRegLayout,
}
impl risc0_zkp::layout::Component for UseOnceMemoryElementLayout {
    fn ty_name(&self) -> &'static str {
        "UseOnceMemoryElementLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("count", self.count)?;
        v.visit_component("index", self.index)?;
        v.visit_component("_0", self._0)?;
        v.visit_component("_1", self._1)?;
        v.visit_component("_2", self._2)?;
        v.visit_component("_3", self._3)?;
        Ok(())
    }
}
pub struct WriteMemoryLayout {
    pub elem: &'static UseOnceMemoryElementLayout,
}
impl risc0_zkp::layout::Component for WriteMemoryLayout {
    fn ty_name(&self) -> &'static str {
        "WriteMemoryLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("elem", self.elem)?;
        Ok(())
    }
}
pub struct AbsorbWord_0__0_Layout {
    pub _super: &'static RetTupleLayout,
    pub unpack_a: &'static ToBits_22_Layout,
    pub unpack_e: &'static ToBits_22_Layout,
    pub unpack_f: &'static ToBits_22_Layout,
    pub unpack_1: &'static ToBits_16_Layout,
    pub unpack_2: &'static ToBits_16_Layout,
    pub unpack_3: &'static ToBits_16_Layout,
    pub unpack_4: &'static ToBits_16_Layout,
    pub _0: &'static WriteMemoryLayout,
    pub invmidx: &'static NondetRegLayout,
}
impl risc0_zkp::layout::Component for AbsorbWord_0__0_Layout {
    fn ty_name(&self) -> &'static str {
        "AbsorbWord_0__0_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("unpack_a", self.unpack_a)?;
        v.visit_component("unpack_e", self.unpack_e)?;
        v.visit_component("unpack_f", self.unpack_f)?;
        v.visit_component("unpack_1", self.unpack_1)?;
        v.visit_component("unpack_2", self.unpack_2)?;
        v.visit_component("unpack_3", self.unpack_3)?;
        v.visit_component("unpack_4", self.unpack_4)?;
        v.visit_component("_0", self._0)?;
        v.visit_component("invmidx", self.invmidx)?;
        Ok(())
    }
}
pub struct AbsorbWord_1__0_Layout {
    pub _super: &'static RetTupleLayout,
    pub unpack_a: &'static ToBits_22_Layout,
    pub unpack_e: &'static ToBits_22_Layout,
    pub unpack_f: &'static ToBits_22_Layout,
    pub unpack_1: &'static ToBits_16_Layout,
    pub unpack_2: &'static ToBits_16_Layout,
    pub unpack_3: &'static ToBits_16_Layout,
    pub unpack_4: &'static ToBits_16_Layout,
    pub _0: &'static WriteMemoryLayout,
    pub invmidx: &'static NondetRegLayout,
}
impl risc0_zkp::layout::Component for AbsorbWord_1__0_Layout {
    fn ty_name(&self) -> &'static str {
        "AbsorbWord_1__0_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("unpack_a", self.unpack_a)?;
        v.visit_component("unpack_e", self.unpack_e)?;
        v.visit_component("unpack_f", self.unpack_f)?;
        v.visit_component("unpack_1", self.unpack_1)?;
        v.visit_component("unpack_2", self.unpack_2)?;
        v.visit_component("unpack_3", self.unpack_3)?;
        v.visit_component("unpack_4", self.unpack_4)?;
        v.visit_component("_0", self._0)?;
        v.visit_component("invmidx", self.invmidx)?;
        Ok(())
    }
}
pub struct AbsorbWord_2__0_Layout {
    pub _super: &'static RetTupleLayout,
    pub unpack_a: &'static ToBits_22_Layout,
    pub unpack_e: &'static ToBits_22_Layout,
    pub unpack_f: &'static ToBits_22_Layout,
    pub unpack_1: &'static ToBits_16_Layout,
    pub unpack_2: &'static ToBits_16_Layout,
    pub unpack_3: &'static ToBits_16_Layout,
    pub unpack_4: &'static ToBits_16_Layout,
    pub _0: &'static WriteMemoryLayout,
    pub invmidx: &'static NondetRegLayout,
}
impl risc0_zkp::layout::Component for AbsorbWord_2__0_Layout {
    fn ty_name(&self) -> &'static str {
        "AbsorbWord_2__0_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("unpack_a", self.unpack_a)?;
        v.visit_component("unpack_e", self.unpack_e)?;
        v.visit_component("unpack_f", self.unpack_f)?;
        v.visit_component("unpack_1", self.unpack_1)?;
        v.visit_component("unpack_2", self.unpack_2)?;
        v.visit_component("unpack_3", self.unpack_3)?;
        v.visit_component("unpack_4", self.unpack_4)?;
        v.visit_component("_0", self._0)?;
        v.visit_component("invmidx", self.invmidx)?;
        Ok(())
    }
}
pub struct AbsorbWord_3__0_Layout {
    pub _super: &'static RetTupleLayout,
    pub unpack_a: &'static ToBits_22_Layout,
    pub unpack_e: &'static ToBits_22_Layout,
    pub unpack_f: &'static ToBits_22_Layout,
    pub unpack_1: &'static ToBits_16_Layout,
    pub unpack_2: &'static ToBits_16_Layout,
    pub unpack_3: &'static ToBits_16_Layout,
    pub unpack_4: &'static ToBits_16_Layout,
    pub _0: &'static WriteMemoryLayout,
    pub invmidx: &'static NondetRegLayout,
}
impl risc0_zkp::layout::Component for AbsorbWord_3__0_Layout {
    fn ty_name(&self) -> &'static str {
        "AbsorbWord_3__0_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("unpack_a", self.unpack_a)?;
        v.visit_component("unpack_e", self.unpack_e)?;
        v.visit_component("unpack_f", self.unpack_f)?;
        v.visit_component("unpack_1", self.unpack_1)?;
        v.visit_component("unpack_2", self.unpack_2)?;
        v.visit_component("unpack_3", self.unpack_3)?;
        v.visit_component("unpack_4", self.unpack_4)?;
        v.visit_component("_0", self._0)?;
        v.visit_component("invmidx", self.invmidx)?;
        Ok(())
    }
}
pub struct AbsorbWord_4__0_Layout {
    pub _super: &'static RetTupleLayout,
    pub unpack_a: &'static ToBits_22_Layout,
    pub unpack_e: &'static ToBits_22_Layout,
    pub unpack_f: &'static ToBits_22_Layout,
    pub unpack_1: &'static ToBits_16_Layout,
    pub unpack_2: &'static ToBits_16_Layout,
    pub unpack_3: &'static ToBits_16_Layout,
    pub unpack_4: &'static ToBits_16_Layout,
    pub _0: &'static WriteMemoryLayout,
    pub invmidx: &'static NondetRegLayout,
}
impl risc0_zkp::layout::Component for AbsorbWord_4__0_Layout {
    fn ty_name(&self) -> &'static str {
        "AbsorbWord_4__0_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("unpack_a", self.unpack_a)?;
        v.visit_component("unpack_e", self.unpack_e)?;
        v.visit_component("unpack_f", self.unpack_f)?;
        v.visit_component("unpack_1", self.unpack_1)?;
        v.visit_component("unpack_2", self.unpack_2)?;
        v.visit_component("unpack_3", self.unpack_3)?;
        v.visit_component("unpack_4", self.unpack_4)?;
        v.visit_component("_0", self._0)?;
        v.visit_component("invmidx", self.invmidx)?;
        Ok(())
    }
}
pub struct AbsorbWord_0__1_Layout {
    pub _super: &'static RetTupleLayout,
    pub unpack_a: &'static ToBits_22_Layout,
    pub unpack_e: &'static ToBits_22_Layout,
    pub unpack_f: &'static ToBits_22_Layout,
    pub unpack_1: &'static ToBits_16_Layout,
    pub unpack_2: &'static ToBits_16_Layout,
    pub unpack_3: &'static ToBits_16_Layout,
    pub unpack_4: &'static ToBits_16_Layout,
    pub _0: &'static WriteMemoryLayout,
    pub invmidx: &'static NondetRegLayout,
}
impl risc0_zkp::layout::Component for AbsorbWord_0__1_Layout {
    fn ty_name(&self) -> &'static str {
        "AbsorbWord_0__1_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("unpack_a", self.unpack_a)?;
        v.visit_component("unpack_e", self.unpack_e)?;
        v.visit_component("unpack_f", self.unpack_f)?;
        v.visit_component("unpack_1", self.unpack_1)?;
        v.visit_component("unpack_2", self.unpack_2)?;
        v.visit_component("unpack_3", self.unpack_3)?;
        v.visit_component("unpack_4", self.unpack_4)?;
        v.visit_component("_0", self._0)?;
        v.visit_component("invmidx", self.invmidx)?;
        Ok(())
    }
}
pub struct AbsorbWord_1__1_Layout {
    pub _super: &'static RetTupleLayout,
    pub unpack_a: &'static ToBits_22_Layout,
    pub unpack_e: &'static ToBits_22_Layout,
    pub unpack_f: &'static ToBits_22_Layout,
    pub unpack_1: &'static ToBits_16_Layout,
    pub unpack_2: &'static ToBits_16_Layout,
    pub unpack_3: &'static ToBits_16_Layout,
    pub unpack_4: &'static ToBits_16_Layout,
    pub _0: &'static WriteMemoryLayout,
    pub invmidx: &'static NondetRegLayout,
}
impl risc0_zkp::layout::Component for AbsorbWord_1__1_Layout {
    fn ty_name(&self) -> &'static str {
        "AbsorbWord_1__1_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("unpack_a", self.unpack_a)?;
        v.visit_component("unpack_e", self.unpack_e)?;
        v.visit_component("unpack_f", self.unpack_f)?;
        v.visit_component("unpack_1", self.unpack_1)?;
        v.visit_component("unpack_2", self.unpack_2)?;
        v.visit_component("unpack_3", self.unpack_3)?;
        v.visit_component("unpack_4", self.unpack_4)?;
        v.visit_component("_0", self._0)?;
        v.visit_component("invmidx", self.invmidx)?;
        Ok(())
    }
}
pub struct AbsorbWord_2__1_Layout {
    pub _super: &'static RetTupleLayout,
    pub unpack_a: &'static ToBits_22_Layout,
    pub unpack_e: &'static ToBits_22_Layout,
    pub unpack_f: &'static ToBits_22_Layout,
    pub unpack_1: &'static ToBits_16_Layout,
    pub unpack_2: &'static ToBits_16_Layout,
    pub unpack_3: &'static ToBits_16_Layout,
    pub unpack_4: &'static ToBits_16_Layout,
    pub _0: &'static WriteMemoryLayout,
    pub invmidx: &'static NondetRegLayout,
}
impl risc0_zkp::layout::Component for AbsorbWord_2__1_Layout {
    fn ty_name(&self) -> &'static str {
        "AbsorbWord_2__1_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("unpack_a", self.unpack_a)?;
        v.visit_component("unpack_e", self.unpack_e)?;
        v.visit_component("unpack_f", self.unpack_f)?;
        v.visit_component("unpack_1", self.unpack_1)?;
        v.visit_component("unpack_2", self.unpack_2)?;
        v.visit_component("unpack_3", self.unpack_3)?;
        v.visit_component("unpack_4", self.unpack_4)?;
        v.visit_component("_0", self._0)?;
        v.visit_component("invmidx", self.invmidx)?;
        Ok(())
    }
}
pub struct AbsorbWord_3__1_Layout {
    pub _super: &'static RetTupleLayout,
    pub unpack_a: &'static ToBits_22_Layout,
    pub unpack_e: &'static ToBits_22_Layout,
    pub unpack_f: &'static ToBits_22_Layout,
    pub unpack_1: &'static ToBits_16_Layout,
    pub unpack_2: &'static ToBits_16_Layout,
    pub unpack_3: &'static ToBits_16_Layout,
    pub unpack_4: &'static ToBits_16_Layout,
    pub _0: &'static WriteMemoryLayout,
    pub invmidx: &'static NondetRegLayout,
}
impl risc0_zkp::layout::Component for AbsorbWord_3__1_Layout {
    fn ty_name(&self) -> &'static str {
        "AbsorbWord_3__1_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("unpack_a", self.unpack_a)?;
        v.visit_component("unpack_e", self.unpack_e)?;
        v.visit_component("unpack_f", self.unpack_f)?;
        v.visit_component("unpack_1", self.unpack_1)?;
        v.visit_component("unpack_2", self.unpack_2)?;
        v.visit_component("unpack_3", self.unpack_3)?;
        v.visit_component("unpack_4", self.unpack_4)?;
        v.visit_component("_0", self._0)?;
        v.visit_component("invmidx", self.invmidx)?;
        Ok(())
    }
}
pub struct AbsorbMajor1Arm9Layout {
    pub _super: &'static RetTupleLayout,
    pub _extra0: &'static UseOnceMemoryElementLayout,
}
impl risc0_zkp::layout::Component for AbsorbMajor1Arm9Layout {
    fn ty_name(&self) -> &'static str {
        "AbsorbMajor1Arm9Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("_extra0", self._extra0)?;
        Ok(())
    }
}
pub struct AbsorbMajor1_SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static AbsorbWord_0__0_Layout,
    pub arm1: &'static AbsorbWord_1__0_Layout,
    pub arm2: &'static AbsorbWord_2__0_Layout,
    pub arm3: &'static AbsorbWord_3__0_Layout,
    pub arm4: &'static AbsorbWord_4__0_Layout,
    pub arm5: &'static AbsorbWord_0__1_Layout,
    pub arm6: &'static AbsorbWord_1__1_Layout,
    pub arm7: &'static AbsorbWord_2__1_Layout,
    pub arm8: &'static AbsorbWord_3__1_Layout,
    pub arm9: &'static AbsorbMajor1Arm9Layout,
}
impl risc0_zkp::layout::Component for AbsorbMajor1_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "AbsorbMajor1_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        v.visit_component("arm2", self.arm2)?;
        v.visit_component("arm3", self.arm3)?;
        v.visit_component("arm4", self.arm4)?;
        v.visit_component("arm5", self.arm5)?;
        v.visit_component("arm6", self.arm6)?;
        v.visit_component("arm7", self.arm7)?;
        v.visit_component("arm8", self.arm8)?;
        v.visit_component("arm9", self.arm9)?;
        Ok(())
    }
}
pub type UseOnceMemoryElementLayout1LayoutArray = [&'static UseOnceMemoryElementLayout; 1];
pub struct _ArgumentsAbsorbMajor1_SuperLayout {
    pub use_once_memory_element: &'static UseOnceMemoryElementLayout1LayoutArray,
}
impl risc0_zkp::layout::Component for _ArgumentsAbsorbMajor1_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "_ArgumentsAbsorbMajor1_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("use_once_memory_element", self.use_once_memory_element)?;
        Ok(())
    }
}
pub struct AbsorbMajor1Layout {
    pub _super: &'static AbsorbMajor1_SuperLayout,
    pub minor_onehot: &'static OneHot_10_Layout,
    pub _arguments__super: &'static _ArgumentsAbsorbMajor1_SuperLayout,
}
impl risc0_zkp::layout::Component for AbsorbMajor1Layout {
    fn ty_name(&self) -> &'static str {
        "AbsorbMajor1Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("minor_onehot", self.minor_onehot)?;
        v.visit_component("_arguments__super", self._arguments__super)?;
        Ok(())
    }
}
pub struct AbsorbWord_4__1_Layout {
    pub _super: &'static RetTupleLayout,
    pub unpack_a: &'static ToBits_22_Layout,
    pub unpack_e: &'static ToBits_22_Layout,
    pub unpack_f: &'static ToBits_22_Layout,
    pub unpack_1: &'static ToBits_16_Layout,
    pub unpack_2: &'static ToBits_16_Layout,
    pub unpack_3: &'static ToBits_16_Layout,
    pub unpack_4: &'static ToBits_16_Layout,
    pub _0: &'static WriteMemoryLayout,
    pub invmidx: &'static NondetRegLayout,
}
impl risc0_zkp::layout::Component for AbsorbWord_4__1_Layout {
    fn ty_name(&self) -> &'static str {
        "AbsorbWord_4__1_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("unpack_a", self.unpack_a)?;
        v.visit_component("unpack_e", self.unpack_e)?;
        v.visit_component("unpack_f", self.unpack_f)?;
        v.visit_component("unpack_1", self.unpack_1)?;
        v.visit_component("unpack_2", self.unpack_2)?;
        v.visit_component("unpack_3", self.unpack_3)?;
        v.visit_component("unpack_4", self.unpack_4)?;
        v.visit_component("_0", self._0)?;
        v.visit_component("invmidx", self.invmidx)?;
        Ok(())
    }
}
pub struct AbsorbWord_0__2_Layout {
    pub _super: &'static RetTupleLayout,
    pub unpack_a: &'static ToBits_22_Layout,
    pub unpack_e: &'static ToBits_22_Layout,
    pub unpack_f: &'static ToBits_22_Layout,
    pub unpack_1: &'static ToBits_16_Layout,
    pub unpack_2: &'static ToBits_16_Layout,
    pub unpack_3: &'static ToBits_16_Layout,
    pub unpack_4: &'static ToBits_16_Layout,
    pub _0: &'static WriteMemoryLayout,
    pub invmidx: &'static NondetRegLayout,
}
impl risc0_zkp::layout::Component for AbsorbWord_0__2_Layout {
    fn ty_name(&self) -> &'static str {
        "AbsorbWord_0__2_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("unpack_a", self.unpack_a)?;
        v.visit_component("unpack_e", self.unpack_e)?;
        v.visit_component("unpack_f", self.unpack_f)?;
        v.visit_component("unpack_1", self.unpack_1)?;
        v.visit_component("unpack_2", self.unpack_2)?;
        v.visit_component("unpack_3", self.unpack_3)?;
        v.visit_component("unpack_4", self.unpack_4)?;
        v.visit_component("_0", self._0)?;
        v.visit_component("invmidx", self.invmidx)?;
        Ok(())
    }
}
pub struct AbsorbWord_1__2_Layout {
    pub _super: &'static RetTupleLayout,
    pub unpack_a: &'static ToBits_22_Layout,
    pub unpack_e: &'static ToBits_22_Layout,
    pub unpack_f: &'static ToBits_22_Layout,
    pub unpack_1: &'static ToBits_16_Layout,
    pub unpack_2: &'static ToBits_16_Layout,
    pub unpack_3: &'static ToBits_16_Layout,
    pub unpack_4: &'static ToBits_16_Layout,
    pub _0: &'static WriteMemoryLayout,
    pub invmidx: &'static NondetRegLayout,
}
impl risc0_zkp::layout::Component for AbsorbWord_1__2_Layout {
    fn ty_name(&self) -> &'static str {
        "AbsorbWord_1__2_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("unpack_a", self.unpack_a)?;
        v.visit_component("unpack_e", self.unpack_e)?;
        v.visit_component("unpack_f", self.unpack_f)?;
        v.visit_component("unpack_1", self.unpack_1)?;
        v.visit_component("unpack_2", self.unpack_2)?;
        v.visit_component("unpack_3", self.unpack_3)?;
        v.visit_component("unpack_4", self.unpack_4)?;
        v.visit_component("_0", self._0)?;
        v.visit_component("invmidx", self.invmidx)?;
        Ok(())
    }
}
pub struct AbsorbWord_2__2_Layout {
    pub _super: &'static RetTupleLayout,
    pub unpack_a: &'static ToBits_22_Layout,
    pub unpack_e: &'static ToBits_22_Layout,
    pub unpack_f: &'static ToBits_22_Layout,
    pub unpack_1: &'static ToBits_16_Layout,
    pub unpack_2: &'static ToBits_16_Layout,
    pub unpack_3: &'static ToBits_16_Layout,
    pub unpack_4: &'static ToBits_16_Layout,
    pub _0: &'static WriteMemoryLayout,
    pub invmidx: &'static NondetRegLayout,
}
impl risc0_zkp::layout::Component for AbsorbWord_2__2_Layout {
    fn ty_name(&self) -> &'static str {
        "AbsorbWord_2__2_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("unpack_a", self.unpack_a)?;
        v.visit_component("unpack_e", self.unpack_e)?;
        v.visit_component("unpack_f", self.unpack_f)?;
        v.visit_component("unpack_1", self.unpack_1)?;
        v.visit_component("unpack_2", self.unpack_2)?;
        v.visit_component("unpack_3", self.unpack_3)?;
        v.visit_component("unpack_4", self.unpack_4)?;
        v.visit_component("_0", self._0)?;
        v.visit_component("invmidx", self.invmidx)?;
        Ok(())
    }
}
pub struct AbsorbWord_3__2_Layout {
    pub _super: &'static RetTupleLayout,
    pub unpack_a: &'static ToBits_22_Layout,
    pub unpack_e: &'static ToBits_22_Layout,
    pub unpack_f: &'static ToBits_22_Layout,
    pub unpack_1: &'static ToBits_16_Layout,
    pub unpack_2: &'static ToBits_16_Layout,
    pub unpack_3: &'static ToBits_16_Layout,
    pub unpack_4: &'static ToBits_16_Layout,
    pub _0: &'static WriteMemoryLayout,
    pub invmidx: &'static NondetRegLayout,
}
impl risc0_zkp::layout::Component for AbsorbWord_3__2_Layout {
    fn ty_name(&self) -> &'static str {
        "AbsorbWord_3__2_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("unpack_a", self.unpack_a)?;
        v.visit_component("unpack_e", self.unpack_e)?;
        v.visit_component("unpack_f", self.unpack_f)?;
        v.visit_component("unpack_1", self.unpack_1)?;
        v.visit_component("unpack_2", self.unpack_2)?;
        v.visit_component("unpack_3", self.unpack_3)?;
        v.visit_component("unpack_4", self.unpack_4)?;
        v.visit_component("_0", self._0)?;
        v.visit_component("invmidx", self.invmidx)?;
        Ok(())
    }
}
pub struct AbsorbWord_4__2_Layout {
    pub _super: &'static RetTupleLayout,
    pub unpack_a: &'static ToBits_22_Layout,
    pub unpack_e: &'static ToBits_22_Layout,
    pub unpack_f: &'static ToBits_22_Layout,
    pub unpack_1: &'static ToBits_16_Layout,
    pub unpack_2: &'static ToBits_16_Layout,
    pub unpack_3: &'static ToBits_16_Layout,
    pub unpack_4: &'static ToBits_16_Layout,
    pub _0: &'static WriteMemoryLayout,
    pub invmidx: &'static NondetRegLayout,
}
impl risc0_zkp::layout::Component for AbsorbWord_4__2_Layout {
    fn ty_name(&self) -> &'static str {
        "AbsorbWord_4__2_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("unpack_a", self.unpack_a)?;
        v.visit_component("unpack_e", self.unpack_e)?;
        v.visit_component("unpack_f", self.unpack_f)?;
        v.visit_component("unpack_1", self.unpack_1)?;
        v.visit_component("unpack_2", self.unpack_2)?;
        v.visit_component("unpack_3", self.unpack_3)?;
        v.visit_component("unpack_4", self.unpack_4)?;
        v.visit_component("_0", self._0)?;
        v.visit_component("invmidx", self.invmidx)?;
        Ok(())
    }
}
pub struct AbsorbWord_0__3_Layout {
    pub _super: &'static RetTupleLayout,
    pub unpack_a: &'static ToBits_22_Layout,
    pub unpack_e: &'static ToBits_22_Layout,
    pub unpack_f: &'static ToBits_22_Layout,
    pub unpack_1: &'static ToBits_16_Layout,
    pub unpack_2: &'static ToBits_16_Layout,
    pub unpack_3: &'static ToBits_16_Layout,
    pub unpack_4: &'static ToBits_16_Layout,
    pub _0: &'static WriteMemoryLayout,
    pub invmidx: &'static NondetRegLayout,
}
impl risc0_zkp::layout::Component for AbsorbWord_0__3_Layout {
    fn ty_name(&self) -> &'static str {
        "AbsorbWord_0__3_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("unpack_a", self.unpack_a)?;
        v.visit_component("unpack_e", self.unpack_e)?;
        v.visit_component("unpack_f", self.unpack_f)?;
        v.visit_component("unpack_1", self.unpack_1)?;
        v.visit_component("unpack_2", self.unpack_2)?;
        v.visit_component("unpack_3", self.unpack_3)?;
        v.visit_component("unpack_4", self.unpack_4)?;
        v.visit_component("_0", self._0)?;
        v.visit_component("invmidx", self.invmidx)?;
        Ok(())
    }
}
pub struct AbsorbWord_1__3_Layout {
    pub _super: &'static RetTupleLayout,
    pub unpack_a: &'static ToBits_22_Layout,
    pub unpack_e: &'static ToBits_22_Layout,
    pub unpack_f: &'static ToBits_22_Layout,
    pub unpack_1: &'static ToBits_16_Layout,
    pub unpack_2: &'static ToBits_16_Layout,
    pub unpack_3: &'static ToBits_16_Layout,
    pub unpack_4: &'static ToBits_16_Layout,
    pub _0: &'static WriteMemoryLayout,
    pub invmidx: &'static NondetRegLayout,
}
impl risc0_zkp::layout::Component for AbsorbWord_1__3_Layout {
    fn ty_name(&self) -> &'static str {
        "AbsorbWord_1__3_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("unpack_a", self.unpack_a)?;
        v.visit_component("unpack_e", self.unpack_e)?;
        v.visit_component("unpack_f", self.unpack_f)?;
        v.visit_component("unpack_1", self.unpack_1)?;
        v.visit_component("unpack_2", self.unpack_2)?;
        v.visit_component("unpack_3", self.unpack_3)?;
        v.visit_component("unpack_4", self.unpack_4)?;
        v.visit_component("_0", self._0)?;
        v.visit_component("invmidx", self.invmidx)?;
        Ok(())
    }
}
pub struct AbsorbMajor2Arm8Layout {
    pub _super: &'static RetTupleLayout,
    pub _extra0: &'static UseOnceMemoryElementLayout,
}
impl risc0_zkp::layout::Component for AbsorbMajor2Arm8Layout {
    fn ty_name(&self) -> &'static str {
        "AbsorbMajor2Arm8Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("_extra0", self._extra0)?;
        Ok(())
    }
}
pub struct AbsorbMajor2_SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static AbsorbWord_4__1_Layout,
    pub arm1: &'static AbsorbWord_0__2_Layout,
    pub arm2: &'static AbsorbWord_1__2_Layout,
    pub arm3: &'static AbsorbWord_2__2_Layout,
    pub arm4: &'static AbsorbWord_3__2_Layout,
    pub arm5: &'static AbsorbWord_4__2_Layout,
    pub arm6: &'static AbsorbWord_0__3_Layout,
    pub arm7: &'static AbsorbWord_1__3_Layout,
    pub arm8: &'static AbsorbMajor2Arm8Layout,
}
impl risc0_zkp::layout::Component for AbsorbMajor2_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "AbsorbMajor2_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        v.visit_component("arm2", self.arm2)?;
        v.visit_component("arm3", self.arm3)?;
        v.visit_component("arm4", self.arm4)?;
        v.visit_component("arm5", self.arm5)?;
        v.visit_component("arm6", self.arm6)?;
        v.visit_component("arm7", self.arm7)?;
        v.visit_component("arm8", self.arm8)?;
        Ok(())
    }
}
pub struct _ArgumentsAbsorbMajor2_SuperLayout {
    pub use_once_memory_element: &'static UseOnceMemoryElementLayout1LayoutArray,
}
impl risc0_zkp::layout::Component for _ArgumentsAbsorbMajor2_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "_ArgumentsAbsorbMajor2_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("use_once_memory_element", self.use_once_memory_element)?;
        Ok(())
    }
}
pub struct AbsorbMajor2Layout {
    pub _super: &'static AbsorbMajor2_SuperLayout,
    pub minor_onehot: &'static OneHot_9_Layout,
    pub _arguments__super: &'static _ArgumentsAbsorbMajor2_SuperLayout,
}
impl risc0_zkp::layout::Component for AbsorbMajor2Layout {
    fn ty_name(&self) -> &'static str {
        "AbsorbMajor2Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("minor_onehot", self.minor_onehot)?;
        v.visit_component("_arguments__super", self._arguments__super)?;
        Ok(())
    }
}
pub struct EqualWord_0_Arm0Layout {
    pub _extra0: &'static UseOnceMemoryElementLayout,
    pub _extra1: &'static UseOnceMemoryElementLayout,
}
impl risc0_zkp::layout::Component for EqualWord_0_Arm0Layout {
    fn ty_name(&self) -> &'static str {
        "EqualWord_0_Arm0Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_extra0", self._extra0)?;
        v.visit_component("_extra1", self._extra1)?;
        Ok(())
    }
}
pub struct EqualWord_0_Arm1_SuperArm0Layout {
    pub _extra0: &'static UseOnceMemoryElementLayout,
}
impl risc0_zkp::layout::Component for EqualWord_0_Arm1_SuperArm0Layout {
    fn ty_name(&self) -> &'static str {
        "EqualWord_0_Arm1_SuperArm0Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_extra0", self._extra0)?;
        Ok(())
    }
}
pub type NondetRegLayout3LayoutArray = [&'static NondetRegLayout; 3];
pub struct ToBits_3_Layout {
    pub _super: &'static NondetRegLayout3LayoutArray,
}
impl risc0_zkp::layout::Component for ToBits_3_Layout {
    fn ty_name(&self) -> &'static str {
        "ToBits_3_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        Ok(())
    }
}
pub struct EqualWord_0_Arm1_SuperArm1_SuperLayout {
    pub invmidx_nn: &'static NondetRegLayout,
    pub nskip: &'static NondetRegLayout,
    pub _0: &'static WriteMemoryLayout,
    pub unpack_nskip: &'static ToBits_3_Layout,
}
impl risc0_zkp::layout::Component for EqualWord_0_Arm1_SuperArm1_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "EqualWord_0_Arm1_SuperArm1_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("invmidx_nn", self.invmidx_nn)?;
        v.visit_component("nskip", self.nskip)?;
        v.visit_component("_0", self._0)?;
        v.visit_component("unpack_nskip", self.unpack_nskip)?;
        Ok(())
    }
}
pub struct EqualWord_0_Arm1_Super_SuperLayout {
    pub arm0: &'static EqualWord_0_Arm1_SuperArm0Layout,
    pub arm1: &'static EqualWord_0_Arm1_SuperArm1_SuperLayout,
}
impl risc0_zkp::layout::Component for EqualWord_0_Arm1_Super_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "EqualWord_0_Arm1_Super_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct _ArgumentsEqualWord_0_Arm1_Super_SuperLayout {
    pub use_once_memory_element: &'static UseOnceMemoryElementLayout1LayoutArray,
}
impl risc0_zkp::layout::Component for _ArgumentsEqualWord_0_Arm1_Super_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "_ArgumentsEqualWord_0_Arm1_Super_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("use_once_memory_element", self.use_once_memory_element)?;
        Ok(())
    }
}
pub struct EqualWord_0_Arm1_SuperLayout {
    pub _super: &'static EqualWord_0_Arm1_Super_SuperLayout,
    pub blk: &'static NondetRegLayout,
    pub inv_blk: &'static NondetRegLayout,
    pub invmidxnxt: &'static NondetRegLayout,
    pub _0: &'static WriteMemoryLayout,
    pub _arguments__super: &'static _ArgumentsEqualWord_0_Arm1_Super_SuperLayout,
    pub prod: &'static NondetRegLayout,
}
impl risc0_zkp::layout::Component for EqualWord_0_Arm1_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "EqualWord_0_Arm1_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("blk", self.blk)?;
        v.visit_component("inv_blk", self.inv_blk)?;
        v.visit_component("invmidxnxt", self.invmidxnxt)?;
        v.visit_component("_0", self._0)?;
        v.visit_component("_arguments__super", self._arguments__super)?;
        v.visit_component("prod", self.prod)?;
        Ok(())
    }
}
pub struct EqualWord_0_NxtLayout {
    pub arm0: &'static EqualWord_0_Arm0Layout,
    pub arm1: &'static EqualWord_0_Arm1_SuperLayout,
}
impl risc0_zkp::layout::Component for EqualWord_0_NxtLayout {
    fn ty_name(&self) -> &'static str {
        "EqualWord_0_NxtLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub type UseOnceMemoryElementLayout2LayoutArray = [&'static UseOnceMemoryElementLayout; 2];
pub struct _ArgumentsEqualWord_0_NxtLayout {
    pub use_once_memory_element: &'static UseOnceMemoryElementLayout2LayoutArray,
}
impl risc0_zkp::layout::Component for _ArgumentsEqualWord_0_NxtLayout {
    fn ty_name(&self) -> &'static str {
        "_ArgumentsEqualWord_0_NxtLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("use_once_memory_element", self.use_once_memory_element)?;
        Ok(())
    }
}
pub struct EqualWord_0_Layout {
    pub _super: &'static RetTupleLayout,
    pub unpack_1: &'static ToBits_16_Layout,
    pub nxt: &'static EqualWord_0_NxtLayout,
    pub _arguments_nxt: &'static _ArgumentsEqualWord_0_NxtLayout,
    pub unpack_2: &'static ToBits_16_Layout,
    pub unpack_3: &'static ToBits_16_Layout,
    pub unpack_4: &'static ToBits_16_Layout,
    pub invmidx: &'static NondetRegLayout,
    pub unpack_a: &'static ToBits_22_Layout,
    pub unpack_e: &'static ToBits_21_Layout,
    pub unpack_f: &'static ToBits_21_Layout,
    pub _0: &'static WriteMemoryLayout,
}
impl risc0_zkp::layout::Component for EqualWord_0_Layout {
    fn ty_name(&self) -> &'static str {
        "EqualWord_0_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("unpack_1", self.unpack_1)?;
        v.visit_component("nxt", self.nxt)?;
        v.visit_component("_arguments_nxt", self._arguments_nxt)?;
        v.visit_component("unpack_2", self.unpack_2)?;
        v.visit_component("unpack_3", self.unpack_3)?;
        v.visit_component("unpack_4", self.unpack_4)?;
        v.visit_component("invmidx", self.invmidx)?;
        v.visit_component("unpack_a", self.unpack_a)?;
        v.visit_component("unpack_e", self.unpack_e)?;
        v.visit_component("unpack_f", self.unpack_f)?;
        v.visit_component("_0", self._0)?;
        Ok(())
    }
}
pub struct EqualWord_1_Arm0Layout {
    pub _extra0: &'static UseOnceMemoryElementLayout,
    pub _extra1: &'static UseOnceMemoryElementLayout,
}
impl risc0_zkp::layout::Component for EqualWord_1_Arm0Layout {
    fn ty_name(&self) -> &'static str {
        "EqualWord_1_Arm0Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_extra0", self._extra0)?;
        v.visit_component("_extra1", self._extra1)?;
        Ok(())
    }
}
pub struct EqualWord_1_Arm1_SuperArm0Layout {
    pub _extra0: &'static UseOnceMemoryElementLayout,
}
impl risc0_zkp::layout::Component for EqualWord_1_Arm1_SuperArm0Layout {
    fn ty_name(&self) -> &'static str {
        "EqualWord_1_Arm1_SuperArm0Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_extra0", self._extra0)?;
        Ok(())
    }
}
pub struct EqualWord_1_Arm1_SuperArm1_SuperLayout {
    pub invmidx_nn: &'static NondetRegLayout,
    pub nskip: &'static NondetRegLayout,
    pub _0: &'static WriteMemoryLayout,
    pub unpack_nskip: &'static ToBits_3_Layout,
}
impl risc0_zkp::layout::Component for EqualWord_1_Arm1_SuperArm1_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "EqualWord_1_Arm1_SuperArm1_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("invmidx_nn", self.invmidx_nn)?;
        v.visit_component("nskip", self.nskip)?;
        v.visit_component("_0", self._0)?;
        v.visit_component("unpack_nskip", self.unpack_nskip)?;
        Ok(())
    }
}
pub struct EqualWord_1_Arm1_Super_SuperLayout {
    pub arm0: &'static EqualWord_1_Arm1_SuperArm0Layout,
    pub arm1: &'static EqualWord_1_Arm1_SuperArm1_SuperLayout,
}
impl risc0_zkp::layout::Component for EqualWord_1_Arm1_Super_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "EqualWord_1_Arm1_Super_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct _ArgumentsEqualWord_1_Arm1_Super_SuperLayout {
    pub use_once_memory_element: &'static UseOnceMemoryElementLayout1LayoutArray,
}
impl risc0_zkp::layout::Component for _ArgumentsEqualWord_1_Arm1_Super_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "_ArgumentsEqualWord_1_Arm1_Super_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("use_once_memory_element", self.use_once_memory_element)?;
        Ok(())
    }
}
pub struct EqualWord_1_Arm1_SuperLayout {
    pub _super: &'static EqualWord_1_Arm1_Super_SuperLayout,
    pub blk: &'static NondetRegLayout,
    pub inv_blk: &'static NondetRegLayout,
    pub invmidxnxt: &'static NondetRegLayout,
    pub _0: &'static WriteMemoryLayout,
    pub _arguments__super: &'static _ArgumentsEqualWord_1_Arm1_Super_SuperLayout,
    pub prod: &'static NondetRegLayout,
}
impl risc0_zkp::layout::Component for EqualWord_1_Arm1_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "EqualWord_1_Arm1_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("blk", self.blk)?;
        v.visit_component("inv_blk", self.inv_blk)?;
        v.visit_component("invmidxnxt", self.invmidxnxt)?;
        v.visit_component("_0", self._0)?;
        v.visit_component("_arguments__super", self._arguments__super)?;
        v.visit_component("prod", self.prod)?;
        Ok(())
    }
}
pub struct EqualWord_1_NxtLayout {
    pub arm0: &'static EqualWord_1_Arm0Layout,
    pub arm1: &'static EqualWord_1_Arm1_SuperLayout,
}
impl risc0_zkp::layout::Component for EqualWord_1_NxtLayout {
    fn ty_name(&self) -> &'static str {
        "EqualWord_1_NxtLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct _ArgumentsEqualWord_1_NxtLayout {
    pub use_once_memory_element: &'static UseOnceMemoryElementLayout2LayoutArray,
}
impl risc0_zkp::layout::Component for _ArgumentsEqualWord_1_NxtLayout {
    fn ty_name(&self) -> &'static str {
        "_ArgumentsEqualWord_1_NxtLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("use_once_memory_element", self.use_once_memory_element)?;
        Ok(())
    }
}
pub struct EqualWord_1_Layout {
    pub _super: &'static RetTupleLayout,
    pub unpack_1: &'static ToBits_16_Layout,
    pub nxt: &'static EqualWord_1_NxtLayout,
    pub _arguments_nxt: &'static _ArgumentsEqualWord_1_NxtLayout,
    pub unpack_2: &'static ToBits_16_Layout,
    pub unpack_3: &'static ToBits_16_Layout,
    pub unpack_4: &'static ToBits_16_Layout,
    pub invmidx: &'static NondetRegLayout,
    pub unpack_a: &'static ToBits_22_Layout,
    pub unpack_e: &'static ToBits_21_Layout,
    pub unpack_f: &'static ToBits_21_Layout,
    pub _0: &'static WriteMemoryLayout,
}
impl risc0_zkp::layout::Component for EqualWord_1_Layout {
    fn ty_name(&self) -> &'static str {
        "EqualWord_1_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("unpack_1", self.unpack_1)?;
        v.visit_component("nxt", self.nxt)?;
        v.visit_component("_arguments_nxt", self._arguments_nxt)?;
        v.visit_component("unpack_2", self.unpack_2)?;
        v.visit_component("unpack_3", self.unpack_3)?;
        v.visit_component("unpack_4", self.unpack_4)?;
        v.visit_component("invmidx", self.invmidx)?;
        v.visit_component("unpack_a", self.unpack_a)?;
        v.visit_component("unpack_e", self.unpack_e)?;
        v.visit_component("unpack_f", self.unpack_f)?;
        v.visit_component("_0", self._0)?;
        Ok(())
    }
}
pub struct EqualWord_2_Arm0Layout {
    pub _extra0: &'static UseOnceMemoryElementLayout,
    pub _extra1: &'static UseOnceMemoryElementLayout,
}
impl risc0_zkp::layout::Component for EqualWord_2_Arm0Layout {
    fn ty_name(&self) -> &'static str {
        "EqualWord_2_Arm0Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_extra0", self._extra0)?;
        v.visit_component("_extra1", self._extra1)?;
        Ok(())
    }
}
pub struct EqualWord_2_Arm1_SuperArm0Layout {
    pub _extra0: &'static UseOnceMemoryElementLayout,
}
impl risc0_zkp::layout::Component for EqualWord_2_Arm1_SuperArm0Layout {
    fn ty_name(&self) -> &'static str {
        "EqualWord_2_Arm1_SuperArm0Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_extra0", self._extra0)?;
        Ok(())
    }
}
pub struct EqualWord_2_Arm1_SuperArm1_SuperLayout {
    pub invmidx_nn: &'static NondetRegLayout,
    pub nskip: &'static NondetRegLayout,
    pub _0: &'static WriteMemoryLayout,
    pub unpack_nskip: &'static ToBits_3_Layout,
}
impl risc0_zkp::layout::Component for EqualWord_2_Arm1_SuperArm1_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "EqualWord_2_Arm1_SuperArm1_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("invmidx_nn", self.invmidx_nn)?;
        v.visit_component("nskip", self.nskip)?;
        v.visit_component("_0", self._0)?;
        v.visit_component("unpack_nskip", self.unpack_nskip)?;
        Ok(())
    }
}
pub struct EqualWord_2_Arm1_Super_SuperLayout {
    pub arm0: &'static EqualWord_2_Arm1_SuperArm0Layout,
    pub arm1: &'static EqualWord_2_Arm1_SuperArm1_SuperLayout,
}
impl risc0_zkp::layout::Component for EqualWord_2_Arm1_Super_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "EqualWord_2_Arm1_Super_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct _ArgumentsEqualWord_2_Arm1_Super_SuperLayout {
    pub use_once_memory_element: &'static UseOnceMemoryElementLayout1LayoutArray,
}
impl risc0_zkp::layout::Component for _ArgumentsEqualWord_2_Arm1_Super_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "_ArgumentsEqualWord_2_Arm1_Super_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("use_once_memory_element", self.use_once_memory_element)?;
        Ok(())
    }
}
pub struct EqualWord_2_Arm1_SuperLayout {
    pub _super: &'static EqualWord_2_Arm1_Super_SuperLayout,
    pub blk: &'static NondetRegLayout,
    pub inv_blk: &'static NondetRegLayout,
    pub invmidxnxt: &'static NondetRegLayout,
    pub _0: &'static WriteMemoryLayout,
    pub _arguments__super: &'static _ArgumentsEqualWord_2_Arm1_Super_SuperLayout,
    pub prod: &'static NondetRegLayout,
}
impl risc0_zkp::layout::Component for EqualWord_2_Arm1_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "EqualWord_2_Arm1_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("blk", self.blk)?;
        v.visit_component("inv_blk", self.inv_blk)?;
        v.visit_component("invmidxnxt", self.invmidxnxt)?;
        v.visit_component("_0", self._0)?;
        v.visit_component("_arguments__super", self._arguments__super)?;
        v.visit_component("prod", self.prod)?;
        Ok(())
    }
}
pub struct EqualWord_2_NxtLayout {
    pub arm0: &'static EqualWord_2_Arm0Layout,
    pub arm1: &'static EqualWord_2_Arm1_SuperLayout,
}
impl risc0_zkp::layout::Component for EqualWord_2_NxtLayout {
    fn ty_name(&self) -> &'static str {
        "EqualWord_2_NxtLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct _ArgumentsEqualWord_2_NxtLayout {
    pub use_once_memory_element: &'static UseOnceMemoryElementLayout2LayoutArray,
}
impl risc0_zkp::layout::Component for _ArgumentsEqualWord_2_NxtLayout {
    fn ty_name(&self) -> &'static str {
        "_ArgumentsEqualWord_2_NxtLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("use_once_memory_element", self.use_once_memory_element)?;
        Ok(())
    }
}
pub struct EqualWord_2_Layout {
    pub _super: &'static RetTupleLayout,
    pub unpack_1: &'static ToBits_16_Layout,
    pub nxt: &'static EqualWord_2_NxtLayout,
    pub _arguments_nxt: &'static _ArgumentsEqualWord_2_NxtLayout,
    pub unpack_2: &'static ToBits_16_Layout,
    pub unpack_3: &'static ToBits_16_Layout,
    pub unpack_4: &'static ToBits_16_Layout,
    pub invmidx: &'static NondetRegLayout,
    pub unpack_a: &'static ToBits_22_Layout,
    pub unpack_e: &'static ToBits_21_Layout,
    pub unpack_f: &'static ToBits_21_Layout,
    pub _0: &'static WriteMemoryLayout,
}
impl risc0_zkp::layout::Component for EqualWord_2_Layout {
    fn ty_name(&self) -> &'static str {
        "EqualWord_2_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("unpack_1", self.unpack_1)?;
        v.visit_component("nxt", self.nxt)?;
        v.visit_component("_arguments_nxt", self._arguments_nxt)?;
        v.visit_component("unpack_2", self.unpack_2)?;
        v.visit_component("unpack_3", self.unpack_3)?;
        v.visit_component("unpack_4", self.unpack_4)?;
        v.visit_component("invmidx", self.invmidx)?;
        v.visit_component("unpack_a", self.unpack_a)?;
        v.visit_component("unpack_e", self.unpack_e)?;
        v.visit_component("unpack_f", self.unpack_f)?;
        v.visit_component("_0", self._0)?;
        Ok(())
    }
}
pub struct EqualWord_3_Arm0Layout {
    pub _extra0: &'static UseOnceMemoryElementLayout,
    pub _extra1: &'static UseOnceMemoryElementLayout,
}
impl risc0_zkp::layout::Component for EqualWord_3_Arm0Layout {
    fn ty_name(&self) -> &'static str {
        "EqualWord_3_Arm0Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_extra0", self._extra0)?;
        v.visit_component("_extra1", self._extra1)?;
        Ok(())
    }
}
pub struct EqualWord_3_Arm1_SuperArm0Layout {
    pub _extra0: &'static UseOnceMemoryElementLayout,
}
impl risc0_zkp::layout::Component for EqualWord_3_Arm1_SuperArm0Layout {
    fn ty_name(&self) -> &'static str {
        "EqualWord_3_Arm1_SuperArm0Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_extra0", self._extra0)?;
        Ok(())
    }
}
pub struct EqualWord_3_Arm1_SuperArm1_SuperLayout {
    pub invmidx_nn: &'static NondetRegLayout,
    pub nskip: &'static NondetRegLayout,
    pub _0: &'static WriteMemoryLayout,
    pub unpack_nskip: &'static ToBits_3_Layout,
}
impl risc0_zkp::layout::Component for EqualWord_3_Arm1_SuperArm1_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "EqualWord_3_Arm1_SuperArm1_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("invmidx_nn", self.invmidx_nn)?;
        v.visit_component("nskip", self.nskip)?;
        v.visit_component("_0", self._0)?;
        v.visit_component("unpack_nskip", self.unpack_nskip)?;
        Ok(())
    }
}
pub struct EqualWord_3_Arm1_Super_SuperLayout {
    pub arm0: &'static EqualWord_3_Arm1_SuperArm0Layout,
    pub arm1: &'static EqualWord_3_Arm1_SuperArm1_SuperLayout,
}
impl risc0_zkp::layout::Component for EqualWord_3_Arm1_Super_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "EqualWord_3_Arm1_Super_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct _ArgumentsEqualWord_3_Arm1_Super_SuperLayout {
    pub use_once_memory_element: &'static UseOnceMemoryElementLayout1LayoutArray,
}
impl risc0_zkp::layout::Component for _ArgumentsEqualWord_3_Arm1_Super_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "_ArgumentsEqualWord_3_Arm1_Super_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("use_once_memory_element", self.use_once_memory_element)?;
        Ok(())
    }
}
pub struct EqualWord_3_Arm1_SuperLayout {
    pub _super: &'static EqualWord_3_Arm1_Super_SuperLayout,
    pub blk: &'static NondetRegLayout,
    pub inv_blk: &'static NondetRegLayout,
    pub invmidxnxt: &'static NondetRegLayout,
    pub _0: &'static WriteMemoryLayout,
    pub _arguments__super: &'static _ArgumentsEqualWord_3_Arm1_Super_SuperLayout,
    pub prod: &'static NondetRegLayout,
}
impl risc0_zkp::layout::Component for EqualWord_3_Arm1_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "EqualWord_3_Arm1_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("blk", self.blk)?;
        v.visit_component("inv_blk", self.inv_blk)?;
        v.visit_component("invmidxnxt", self.invmidxnxt)?;
        v.visit_component("_0", self._0)?;
        v.visit_component("_arguments__super", self._arguments__super)?;
        v.visit_component("prod", self.prod)?;
        Ok(())
    }
}
pub struct EqualWord_3_NxtLayout {
    pub arm0: &'static EqualWord_3_Arm0Layout,
    pub arm1: &'static EqualWord_3_Arm1_SuperLayout,
}
impl risc0_zkp::layout::Component for EqualWord_3_NxtLayout {
    fn ty_name(&self) -> &'static str {
        "EqualWord_3_NxtLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct _ArgumentsEqualWord_3_NxtLayout {
    pub use_once_memory_element: &'static UseOnceMemoryElementLayout2LayoutArray,
}
impl risc0_zkp::layout::Component for _ArgumentsEqualWord_3_NxtLayout {
    fn ty_name(&self) -> &'static str {
        "_ArgumentsEqualWord_3_NxtLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("use_once_memory_element", self.use_once_memory_element)?;
        Ok(())
    }
}
pub struct EqualWord_3_Layout {
    pub _super: &'static RetTupleLayout,
    pub unpack_1: &'static ToBits_16_Layout,
    pub nxt: &'static EqualWord_3_NxtLayout,
    pub _arguments_nxt: &'static _ArgumentsEqualWord_3_NxtLayout,
    pub unpack_2: &'static ToBits_16_Layout,
    pub unpack_3: &'static ToBits_16_Layout,
    pub unpack_4: &'static ToBits_16_Layout,
    pub invmidx: &'static NondetRegLayout,
    pub unpack_a: &'static ToBits_22_Layout,
    pub unpack_e: &'static ToBits_21_Layout,
    pub unpack_f: &'static ToBits_21_Layout,
    pub _0: &'static WriteMemoryLayout,
}
impl risc0_zkp::layout::Component for EqualWord_3_Layout {
    fn ty_name(&self) -> &'static str {
        "EqualWord_3_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("unpack_1", self.unpack_1)?;
        v.visit_component("nxt", self.nxt)?;
        v.visit_component("_arguments_nxt", self._arguments_nxt)?;
        v.visit_component("unpack_2", self.unpack_2)?;
        v.visit_component("unpack_3", self.unpack_3)?;
        v.visit_component("unpack_4", self.unpack_4)?;
        v.visit_component("invmidx", self.invmidx)?;
        v.visit_component("unpack_a", self.unpack_a)?;
        v.visit_component("unpack_e", self.unpack_e)?;
        v.visit_component("unpack_f", self.unpack_f)?;
        v.visit_component("_0", self._0)?;
        Ok(())
    }
}
pub struct MemPaddingSha256Arm0_SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub _0: &'static WriteMemoryLayout,
}
impl risc0_zkp::layout::Component for MemPaddingSha256Arm0_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "MemPaddingSha256Arm0_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("_0", self._0)?;
        Ok(())
    }
}
pub struct MemPaddingSha256Arm0Layout {
    pub _super: &'static MemPaddingSha256Arm0_SuperLayout,
    pub _extra0: &'static UseOnceMemoryElementLayout,
}
impl risc0_zkp::layout::Component for MemPaddingSha256Arm0Layout {
    fn ty_name(&self) -> &'static str {
        "MemPaddingSha256Arm0Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("_extra0", self._extra0)?;
        Ok(())
    }
}
pub struct MemPaddingSha256Arm1_SuperArm0_SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub _0: &'static WriteMemoryLayout,
}
impl risc0_zkp::layout::Component for MemPaddingSha256Arm1_SuperArm0_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "MemPaddingSha256Arm1_SuperArm0_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("_0", self._0)?;
        Ok(())
    }
}
pub struct MemPaddingSha256Arm1_SuperArm1_SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub _0: &'static WriteMemoryLayout,
}
impl risc0_zkp::layout::Component for MemPaddingSha256Arm1_SuperArm1_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "MemPaddingSha256Arm1_SuperArm1_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("_0", self._0)?;
        Ok(())
    }
}
pub struct MemPaddingSha256Arm1_Super_SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static MemPaddingSha256Arm1_SuperArm0_SuperLayout,
    pub arm1: &'static MemPaddingSha256Arm1_SuperArm1_SuperLayout,
}
impl risc0_zkp::layout::Component for MemPaddingSha256Arm1_Super_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "MemPaddingSha256Arm1_Super_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct _ArgumentsMemPaddingSha256Arm1_Super_SuperLayout {
    pub use_once_memory_element: &'static UseOnceMemoryElementLayout1LayoutArray,
}
impl risc0_zkp::layout::Component for _ArgumentsMemPaddingSha256Arm1_Super_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "_ArgumentsMemPaddingSha256Arm1_Super_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("use_once_memory_element", self.use_once_memory_element)?;
        Ok(())
    }
}
pub struct MemPaddingSha256Arm1_SuperLayout {
    pub _super: &'static MemPaddingSha256Arm1_Super_SuperLayout,
    pub _0: &'static WriteMemoryLayout,
    pub _arguments__super: &'static _ArgumentsMemPaddingSha256Arm1_Super_SuperLayout,
}
impl risc0_zkp::layout::Component for MemPaddingSha256Arm1_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "MemPaddingSha256Arm1_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("_0", self._0)?;
        v.visit_component("_arguments__super", self._arguments__super)?;
        Ok(())
    }
}
pub struct MemPaddingSha256_SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static MemPaddingSha256Arm0Layout,
    pub arm1: &'static MemPaddingSha256Arm1_SuperLayout,
}
impl risc0_zkp::layout::Component for MemPaddingSha256_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "MemPaddingSha256_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct _ArgumentsMemPaddingSha256_SuperLayout {
    pub use_once_memory_element: &'static UseOnceMemoryElementLayout2LayoutArray,
}
impl risc0_zkp::layout::Component for _ArgumentsMemPaddingSha256_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "_ArgumentsMemPaddingSha256_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("use_once_memory_element", self.use_once_memory_element)?;
        Ok(())
    }
}
pub type NondetRegLayout30LayoutArray = [&'static NondetRegLayout; 30];
pub struct ToBits_30_Layout {
    pub _super: &'static NondetRegLayout30LayoutArray,
}
impl risc0_zkp::layout::Component for ToBits_30_Layout {
    fn ty_name(&self) -> &'static str {
        "ToBits_30_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        Ok(())
    }
}
pub struct MemPaddingSha256Layout {
    pub _super: &'static MemPaddingSha256_SuperLayout,
    pub _arguments__super: &'static _ArgumentsMemPaddingSha256_SuperLayout,
    pub prod: &'static NondetRegLayout,
    pub prod_nxt: &'static NondetRegLayout,
    pub invn: &'static NondetRegLayout,
    pub unpack_bitlen: &'static ToBits_30_Layout,
    pub invn_nxt: &'static NondetRegLayout,
}
impl risc0_zkp::layout::Component for MemPaddingSha256Layout {
    fn ty_name(&self) -> &'static str {
        "MemPaddingSha256Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("_arguments__super", self._arguments__super)?;
        v.visit_component("prod", self.prod)?;
        v.visit_component("prod_nxt", self.prod_nxt)?;
        v.visit_component("invn", self.invn)?;
        v.visit_component("unpack_bitlen", self.unpack_bitlen)?;
        v.visit_component("invn_nxt", self.invn_nxt)?;
        Ok(())
    }
}
pub struct SetupMajorArm4Layout {
    pub _super: &'static MemPaddingSha256Layout,
    pub _extra0: &'static UseOnceMemoryElementLayout,
}
impl risc0_zkp::layout::Component for SetupMajorArm4Layout {
    fn ty_name(&self) -> &'static str {
        "SetupMajorArm4Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("_extra0", self._extra0)?;
        Ok(())
    }
}
pub struct Sha256init_1__SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static RetTupleLayout,
}
impl risc0_zkp::layout::Component for Sha256init_1__SuperLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256init_1__SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct Sha256init_1_Layout {
    pub _super: &'static Sha256init_1__SuperLayout,
    pub low_a: &'static ToBits_16_Layout,
    pub high_a: &'static ToBits_16_Layout,
    pub low_e: &'static ToBits_16_Layout,
    pub high_e: &'static ToBits_16_Layout,
}
impl risc0_zkp::layout::Component for Sha256init_1_Layout {
    fn ty_name(&self) -> &'static str {
        "Sha256init_1_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("low_a", self.low_a)?;
        v.visit_component("high_a", self.high_a)?;
        v.visit_component("low_e", self.low_e)?;
        v.visit_component("high_e", self.high_e)?;
        Ok(())
    }
}
pub struct SetupMajorArm5Layout {
    pub _super: &'static Sha256init_1_Layout,
    pub _extra0: &'static UseOnceMemoryElementLayout,
    pub _extra1: &'static UseOnceMemoryElementLayout,
    pub _extra2: &'static UseOnceMemoryElementLayout,
}
impl risc0_zkp::layout::Component for SetupMajorArm5Layout {
    fn ty_name(&self) -> &'static str {
        "SetupMajorArm5Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("_extra0", self._extra0)?;
        v.visit_component("_extra1", self._extra1)?;
        v.visit_component("_extra2", self._extra2)?;
        Ok(())
    }
}
pub struct Sha256init_2__SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static RetTupleLayout,
}
impl risc0_zkp::layout::Component for Sha256init_2__SuperLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256init_2__SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct Sha256init_2_Layout {
    pub _super: &'static Sha256init_2__SuperLayout,
    pub low_a: &'static ToBits_16_Layout,
    pub high_a: &'static ToBits_16_Layout,
    pub low_e: &'static ToBits_16_Layout,
    pub high_e: &'static ToBits_16_Layout,
}
impl risc0_zkp::layout::Component for Sha256init_2_Layout {
    fn ty_name(&self) -> &'static str {
        "Sha256init_2_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("low_a", self.low_a)?;
        v.visit_component("high_a", self.high_a)?;
        v.visit_component("low_e", self.low_e)?;
        v.visit_component("high_e", self.high_e)?;
        Ok(())
    }
}
pub struct SetupMajorArm6Layout {
    pub _super: &'static Sha256init_2_Layout,
    pub _extra0: &'static UseOnceMemoryElementLayout,
    pub _extra1: &'static UseOnceMemoryElementLayout,
    pub _extra2: &'static UseOnceMemoryElementLayout,
}
impl risc0_zkp::layout::Component for SetupMajorArm6Layout {
    fn ty_name(&self) -> &'static str {
        "SetupMajorArm6Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("_extra0", self._extra0)?;
        v.visit_component("_extra1", self._extra1)?;
        v.visit_component("_extra2", self._extra2)?;
        Ok(())
    }
}
pub struct Sha256init_3__SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static RetTupleLayout,
}
impl risc0_zkp::layout::Component for Sha256init_3__SuperLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256init_3__SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct Sha256init_3_Layout {
    pub _super: &'static Sha256init_3__SuperLayout,
    pub low_a: &'static ToBits_16_Layout,
    pub high_a: &'static ToBits_16_Layout,
    pub low_e: &'static ToBits_16_Layout,
    pub high_e: &'static ToBits_16_Layout,
}
impl risc0_zkp::layout::Component for Sha256init_3_Layout {
    fn ty_name(&self) -> &'static str {
        "Sha256init_3_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("low_a", self.low_a)?;
        v.visit_component("high_a", self.high_a)?;
        v.visit_component("low_e", self.low_e)?;
        v.visit_component("high_e", self.high_e)?;
        Ok(())
    }
}
pub struct SetupMajorArm7Layout {
    pub _super: &'static Sha256init_3_Layout,
    pub _extra0: &'static UseOnceMemoryElementLayout,
    pub _extra1: &'static UseOnceMemoryElementLayout,
    pub _extra2: &'static UseOnceMemoryElementLayout,
}
impl risc0_zkp::layout::Component for SetupMajorArm7Layout {
    fn ty_name(&self) -> &'static str {
        "SetupMajorArm7Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("_extra0", self._extra0)?;
        v.visit_component("_extra1", self._extra1)?;
        v.visit_component("_extra2", self._extra2)?;
        Ok(())
    }
}
pub struct Sha256init_4__SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static RetTupleLayout,
}
impl risc0_zkp::layout::Component for Sha256init_4__SuperLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256init_4__SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct Sha256init_4_Layout {
    pub _super: &'static Sha256init_4__SuperLayout,
    pub low_a: &'static ToBits_16_Layout,
    pub high_a: &'static ToBits_16_Layout,
    pub low_e: &'static ToBits_16_Layout,
    pub high_e: &'static ToBits_16_Layout,
}
impl risc0_zkp::layout::Component for Sha256init_4_Layout {
    fn ty_name(&self) -> &'static str {
        "Sha256init_4_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("low_a", self.low_a)?;
        v.visit_component("high_a", self.high_a)?;
        v.visit_component("low_e", self.low_e)?;
        v.visit_component("high_e", self.high_e)?;
        Ok(())
    }
}
pub struct SetupMajorArm8Layout {
    pub _super: &'static Sha256init_4_Layout,
    pub _extra0: &'static UseOnceMemoryElementLayout,
    pub _extra1: &'static UseOnceMemoryElementLayout,
    pub _extra2: &'static UseOnceMemoryElementLayout,
}
impl risc0_zkp::layout::Component for SetupMajorArm8Layout {
    fn ty_name(&self) -> &'static str {
        "SetupMajorArm8Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("_extra0", self._extra0)?;
        v.visit_component("_extra1", self._extra1)?;
        v.visit_component("_extra2", self._extra2)?;
        Ok(())
    }
}
pub struct Pack2Layout {
    pub low: &'static NondetRegLayout,
    pub high: &'static NondetRegLayout,
}
impl risc0_zkp::layout::Component for Pack2Layout {
    fn ty_name(&self) -> &'static str {
        "Pack2Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("low", self.low)?;
        v.visit_component("high", self.high)?;
        Ok(())
    }
}
pub struct Sha256fini_5_Arm1_SuperArm1_SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub fa: &'static Pack2Layout,
    pub fb: &'static Pack2Layout,
    pub fc: &'static Pack2Layout,
    pub fd: &'static Pack2Layout,
    pub fe: &'static Pack2Layout,
    pub ff: &'static Pack2Layout,
    pub fg: &'static Pack2Layout,
    pub fh: &'static Pack2Layout,
}
impl risc0_zkp::layout::Component for Sha256fini_5_Arm1_SuperArm1_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256fini_5_Arm1_SuperArm1_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("fa", self.fa)?;
        v.visit_component("fb", self.fb)?;
        v.visit_component("fc", self.fc)?;
        v.visit_component("fd", self.fd)?;
        v.visit_component("fe", self.fe)?;
        v.visit_component("ff", self.ff)?;
        v.visit_component("fg", self.fg)?;
        v.visit_component("fh", self.fh)?;
        Ok(())
    }
}
pub struct Sha256fini_5_Arm1_Super_SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static Sha256fini_5_Arm1_SuperArm1_SuperLayout,
}
impl risc0_zkp::layout::Component for Sha256fini_5_Arm1_Super_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256fini_5_Arm1_Super_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct Sha256fini_5_Arm1_SuperLayout {
    pub _super: &'static Sha256fini_5_Arm1_Super_SuperLayout,
    pub inv_more_input: &'static NondetRegLayout,
}
impl risc0_zkp::layout::Component for Sha256fini_5_Arm1_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256fini_5_Arm1_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("inv_more_input", self.inv_more_input)?;
        Ok(())
    }
}
pub struct Sha256fini_5__SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static Sha256fini_5_Arm1_SuperLayout,
}
impl risc0_zkp::layout::Component for Sha256fini_5__SuperLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256fini_5__SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub type NondetRegLayout20LayoutArray = [&'static NondetRegLayout; 20];
pub struct ToBits_20_Layout {
    pub _super: &'static NondetRegLayout20LayoutArray,
}
impl risc0_zkp::layout::Component for ToBits_20_Layout {
    fn ty_name(&self) -> &'static str {
        "ToBits_20_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        Ok(())
    }
}
pub type NondetRegLayout19LayoutArray = [&'static NondetRegLayout; 19];
pub struct ToBits_19_Layout {
    pub _super: &'static NondetRegLayout19LayoutArray,
}
impl risc0_zkp::layout::Component for ToBits_19_Layout {
    fn ty_name(&self) -> &'static str {
        "ToBits_19_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        Ok(())
    }
}
pub struct UnpackWithCarryLayout {
    pub high_bits: &'static ToBits_20_Layout,
    pub low_bits: &'static ToBits_19_Layout,
}
impl risc0_zkp::layout::Component for UnpackWithCarryLayout {
    fn ty_name(&self) -> &'static str {
        "UnpackWithCarryLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("high_bits", self.high_bits)?;
        v.visit_component("low_bits", self.low_bits)?;
        Ok(())
    }
}
pub struct Sha256fini_5_Layout {
    pub _super: &'static Sha256fini_5__SuperLayout,
    pub _0: &'static Pack2Layout,
    pub _1: &'static Pack2Layout,
    pub _2: &'static Pack2Layout,
    pub _3: &'static Pack2Layout,
    pub new_a: &'static UnpackWithCarryLayout,
    pub new_e: &'static UnpackWithCarryLayout,
}
impl risc0_zkp::layout::Component for Sha256fini_5_Layout {
    fn ty_name(&self) -> &'static str {
        "Sha256fini_5_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("_0", self._0)?;
        v.visit_component("_1", self._1)?;
        v.visit_component("_2", self._2)?;
        v.visit_component("_3", self._3)?;
        v.visit_component("new_a", self.new_a)?;
        v.visit_component("new_e", self.new_e)?;
        Ok(())
    }
}
pub struct SetupMajorArm9Layout {
    pub _super: &'static Sha256fini_5_Layout,
    pub _extra0: &'static UseOnceMemoryElementLayout,
    pub _extra1: &'static UseOnceMemoryElementLayout,
    pub _extra2: &'static UseOnceMemoryElementLayout,
}
impl risc0_zkp::layout::Component for SetupMajorArm9Layout {
    fn ty_name(&self) -> &'static str {
        "SetupMajorArm9Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("_extra0", self._extra0)?;
        v.visit_component("_extra1", self._extra1)?;
        v.visit_component("_extra2", self._extra2)?;
        Ok(())
    }
}
pub struct Sha256fini_6_Arm1_SuperArm1_SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub fa: &'static Pack2Layout,
    pub fb: &'static Pack2Layout,
    pub fc: &'static Pack2Layout,
    pub fd: &'static Pack2Layout,
    pub fe: &'static Pack2Layout,
    pub ff: &'static Pack2Layout,
    pub fg: &'static Pack2Layout,
    pub fh: &'static Pack2Layout,
}
impl risc0_zkp::layout::Component for Sha256fini_6_Arm1_SuperArm1_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256fini_6_Arm1_SuperArm1_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("fa", self.fa)?;
        v.visit_component("fb", self.fb)?;
        v.visit_component("fc", self.fc)?;
        v.visit_component("fd", self.fd)?;
        v.visit_component("fe", self.fe)?;
        v.visit_component("ff", self.ff)?;
        v.visit_component("fg", self.fg)?;
        v.visit_component("fh", self.fh)?;
        Ok(())
    }
}
pub struct Sha256fini_6_Arm1_Super_SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static Sha256fini_6_Arm1_SuperArm1_SuperLayout,
}
impl risc0_zkp::layout::Component for Sha256fini_6_Arm1_Super_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256fini_6_Arm1_Super_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct Sha256fini_6_Arm1_SuperLayout {
    pub _super: &'static Sha256fini_6_Arm1_Super_SuperLayout,
    pub inv_more_input: &'static NondetRegLayout,
}
impl risc0_zkp::layout::Component for Sha256fini_6_Arm1_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256fini_6_Arm1_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("inv_more_input", self.inv_more_input)?;
        Ok(())
    }
}
pub struct Sha256fini_6__SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static Sha256fini_6_Arm1_SuperLayout,
}
impl risc0_zkp::layout::Component for Sha256fini_6__SuperLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256fini_6__SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct Sha256fini_6_Layout {
    pub _super: &'static Sha256fini_6__SuperLayout,
    pub _0: &'static Pack2Layout,
    pub _1: &'static Pack2Layout,
    pub _2: &'static Pack2Layout,
    pub _3: &'static Pack2Layout,
    pub new_a: &'static UnpackWithCarryLayout,
    pub new_e: &'static UnpackWithCarryLayout,
}
impl risc0_zkp::layout::Component for Sha256fini_6_Layout {
    fn ty_name(&self) -> &'static str {
        "Sha256fini_6_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("_0", self._0)?;
        v.visit_component("_1", self._1)?;
        v.visit_component("_2", self._2)?;
        v.visit_component("_3", self._3)?;
        v.visit_component("new_a", self.new_a)?;
        v.visit_component("new_e", self.new_e)?;
        Ok(())
    }
}
pub struct SetupMajorArm10Layout {
    pub _super: &'static Sha256fini_6_Layout,
    pub _extra0: &'static UseOnceMemoryElementLayout,
    pub _extra1: &'static UseOnceMemoryElementLayout,
    pub _extra2: &'static UseOnceMemoryElementLayout,
}
impl risc0_zkp::layout::Component for SetupMajorArm10Layout {
    fn ty_name(&self) -> &'static str {
        "SetupMajorArm10Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("_extra0", self._extra0)?;
        v.visit_component("_extra1", self._extra1)?;
        v.visit_component("_extra2", self._extra2)?;
        Ok(())
    }
}
pub struct Sha256fini_7_Arm1_SuperArm1_SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub fa: &'static Pack2Layout,
    pub fb: &'static Pack2Layout,
    pub fc: &'static Pack2Layout,
    pub fd: &'static Pack2Layout,
    pub fe: &'static Pack2Layout,
    pub ff: &'static Pack2Layout,
    pub fg: &'static Pack2Layout,
    pub fh: &'static Pack2Layout,
}
impl risc0_zkp::layout::Component for Sha256fini_7_Arm1_SuperArm1_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256fini_7_Arm1_SuperArm1_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("fa", self.fa)?;
        v.visit_component("fb", self.fb)?;
        v.visit_component("fc", self.fc)?;
        v.visit_component("fd", self.fd)?;
        v.visit_component("fe", self.fe)?;
        v.visit_component("ff", self.ff)?;
        v.visit_component("fg", self.fg)?;
        v.visit_component("fh", self.fh)?;
        Ok(())
    }
}
pub struct Sha256fini_7_Arm1_Super_SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static Sha256fini_7_Arm1_SuperArm1_SuperLayout,
}
impl risc0_zkp::layout::Component for Sha256fini_7_Arm1_Super_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256fini_7_Arm1_Super_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct Sha256fini_7_Arm1_SuperLayout {
    pub _super: &'static Sha256fini_7_Arm1_Super_SuperLayout,
    pub inv_more_input: &'static NondetRegLayout,
}
impl risc0_zkp::layout::Component for Sha256fini_7_Arm1_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256fini_7_Arm1_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("inv_more_input", self.inv_more_input)?;
        Ok(())
    }
}
pub struct Sha256fini_7__SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static Sha256fini_7_Arm1_SuperLayout,
}
impl risc0_zkp::layout::Component for Sha256fini_7__SuperLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256fini_7__SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct Sha256fini_7_Layout {
    pub _super: &'static Sha256fini_7__SuperLayout,
    pub _0: &'static Pack2Layout,
    pub _1: &'static Pack2Layout,
    pub _2: &'static Pack2Layout,
    pub _3: &'static Pack2Layout,
    pub new_a: &'static UnpackWithCarryLayout,
    pub new_e: &'static UnpackWithCarryLayout,
}
impl risc0_zkp::layout::Component for Sha256fini_7_Layout {
    fn ty_name(&self) -> &'static str {
        "Sha256fini_7_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("_0", self._0)?;
        v.visit_component("_1", self._1)?;
        v.visit_component("_2", self._2)?;
        v.visit_component("_3", self._3)?;
        v.visit_component("new_a", self.new_a)?;
        v.visit_component("new_e", self.new_e)?;
        Ok(())
    }
}
pub struct SetupMajorArm11Layout {
    pub _super: &'static Sha256fini_7_Layout,
    pub _extra0: &'static UseOnceMemoryElementLayout,
    pub _extra1: &'static UseOnceMemoryElementLayout,
    pub _extra2: &'static UseOnceMemoryElementLayout,
}
impl risc0_zkp::layout::Component for SetupMajorArm11Layout {
    fn ty_name(&self) -> &'static str {
        "SetupMajorArm11Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("_extra0", self._extra0)?;
        v.visit_component("_extra1", self._extra1)?;
        v.visit_component("_extra2", self._extra2)?;
        Ok(())
    }
}
pub struct Sha256fini_8_Arm1_SuperArm1_SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub fa: &'static Pack2Layout,
    pub fb: &'static Pack2Layout,
    pub fc: &'static Pack2Layout,
    pub fd: &'static Pack2Layout,
    pub fe: &'static Pack2Layout,
    pub ff: &'static Pack2Layout,
    pub fg: &'static Pack2Layout,
    pub fh: &'static Pack2Layout,
}
impl risc0_zkp::layout::Component for Sha256fini_8_Arm1_SuperArm1_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256fini_8_Arm1_SuperArm1_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("fa", self.fa)?;
        v.visit_component("fb", self.fb)?;
        v.visit_component("fc", self.fc)?;
        v.visit_component("fd", self.fd)?;
        v.visit_component("fe", self.fe)?;
        v.visit_component("ff", self.ff)?;
        v.visit_component("fg", self.fg)?;
        v.visit_component("fh", self.fh)?;
        Ok(())
    }
}
pub struct Sha256fini_8_Arm1_Super_SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static Sha256fini_8_Arm1_SuperArm1_SuperLayout,
}
impl risc0_zkp::layout::Component for Sha256fini_8_Arm1_Super_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256fini_8_Arm1_Super_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct Sha256fini_8_Arm1_SuperLayout {
    pub _super: &'static Sha256fini_8_Arm1_Super_SuperLayout,
    pub inv_more_input: &'static NondetRegLayout,
}
impl risc0_zkp::layout::Component for Sha256fini_8_Arm1_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256fini_8_Arm1_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("inv_more_input", self.inv_more_input)?;
        Ok(())
    }
}
pub struct Sha256fini_8__SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static Sha256fini_8_Arm1_SuperLayout,
}
impl risc0_zkp::layout::Component for Sha256fini_8__SuperLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256fini_8__SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct Sha256fini_8_Layout {
    pub _super: &'static Sha256fini_8__SuperLayout,
    pub _0: &'static Pack2Layout,
    pub _1: &'static Pack2Layout,
    pub _2: &'static Pack2Layout,
    pub _3: &'static Pack2Layout,
    pub new_a: &'static UnpackWithCarryLayout,
    pub new_e: &'static UnpackWithCarryLayout,
}
impl risc0_zkp::layout::Component for Sha256fini_8_Layout {
    fn ty_name(&self) -> &'static str {
        "Sha256fini_8_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("_0", self._0)?;
        v.visit_component("_1", self._1)?;
        v.visit_component("_2", self._2)?;
        v.visit_component("_3", self._3)?;
        v.visit_component("new_a", self.new_a)?;
        v.visit_component("new_e", self.new_e)?;
        Ok(())
    }
}
pub struct SetupMajorArm12Layout {
    pub _super: &'static Sha256fini_8_Layout,
    pub _extra0: &'static UseOnceMemoryElementLayout,
    pub _extra1: &'static UseOnceMemoryElementLayout,
    pub _extra2: &'static UseOnceMemoryElementLayout,
}
impl risc0_zkp::layout::Component for SetupMajorArm12Layout {
    fn ty_name(&self) -> &'static str {
        "SetupMajorArm12Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("_extra0", self._extra0)?;
        v.visit_component("_extra1", self._extra1)?;
        v.visit_component("_extra2", self._extra2)?;
        Ok(())
    }
}
pub struct SetupMajorArm13Layout {
    pub _super: &'static RetTupleLayout,
    pub _extra0: &'static UseOnceMemoryElementLayout,
    pub _extra1: &'static UseOnceMemoryElementLayout,
    pub _extra2: &'static UseOnceMemoryElementLayout,
}
impl risc0_zkp::layout::Component for SetupMajorArm13Layout {
    fn ty_name(&self) -> &'static str {
        "SetupMajorArm13Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("_extra0", self._extra0)?;
        v.visit_component("_extra1", self._extra1)?;
        v.visit_component("_extra2", self._extra2)?;
        Ok(())
    }
}
pub struct SetupMajor_SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static EqualWord_0_Layout,
    pub arm1: &'static EqualWord_1_Layout,
    pub arm2: &'static EqualWord_2_Layout,
    pub arm3: &'static EqualWord_3_Layout,
    pub arm4: &'static SetupMajorArm4Layout,
    pub arm5: &'static SetupMajorArm5Layout,
    pub arm6: &'static SetupMajorArm6Layout,
    pub arm7: &'static SetupMajorArm7Layout,
    pub arm8: &'static SetupMajorArm8Layout,
    pub arm9: &'static SetupMajorArm9Layout,
    pub arm10: &'static SetupMajorArm10Layout,
    pub arm11: &'static SetupMajorArm11Layout,
    pub arm12: &'static SetupMajorArm12Layout,
    pub arm13: &'static SetupMajorArm13Layout,
}
impl risc0_zkp::layout::Component for SetupMajor_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "SetupMajor_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        v.visit_component("arm2", self.arm2)?;
        v.visit_component("arm3", self.arm3)?;
        v.visit_component("arm4", self.arm4)?;
        v.visit_component("arm5", self.arm5)?;
        v.visit_component("arm6", self.arm6)?;
        v.visit_component("arm7", self.arm7)?;
        v.visit_component("arm8", self.arm8)?;
        v.visit_component("arm9", self.arm9)?;
        v.visit_component("arm10", self.arm10)?;
        v.visit_component("arm11", self.arm11)?;
        v.visit_component("arm12", self.arm12)?;
        v.visit_component("arm13", self.arm13)?;
        Ok(())
    }
}
pub type NondetRegLayout14LayoutArray = [&'static NondetRegLayout; 14];
pub struct OneHot_14_Layout {
    pub _super: &'static NondetRegLayout14LayoutArray,
}
impl risc0_zkp::layout::Component for OneHot_14_Layout {
    fn ty_name(&self) -> &'static str {
        "OneHot_14_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        Ok(())
    }
}
pub type UseOnceMemoryElementLayout3LayoutArray = [&'static UseOnceMemoryElementLayout; 3];
pub struct _ArgumentsSetupMajor_SuperLayout {
    pub use_once_memory_element: &'static UseOnceMemoryElementLayout3LayoutArray,
}
impl risc0_zkp::layout::Component for _ArgumentsSetupMajor_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "_ArgumentsSetupMajor_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("use_once_memory_element", self.use_once_memory_element)?;
        Ok(())
    }
}
pub struct SetupMajorLayout {
    pub _super: &'static SetupMajor_SuperLayout,
    pub minor_onehot: &'static OneHot_14_Layout,
    pub _arguments__super: &'static _ArgumentsSetupMajor_SuperLayout,
}
impl risc0_zkp::layout::Component for SetupMajorLayout {
    fn ty_name(&self) -> &'static str {
        "SetupMajorLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("minor_onehot", self.minor_onehot)?;
        v.visit_component("_arguments__super", self._arguments__super)?;
        Ok(())
    }
}
pub struct TopArm18_SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub _0: &'static WriteMemoryLayout,
    pub blk: &'static NondetRegLayout,
}
impl risc0_zkp::layout::Component for TopArm18_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "TopArm18_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("_0", self._0)?;
        v.visit_component("blk", self.blk)?;
        Ok(())
    }
}
pub struct Sha256load_0__SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static RetTupleLayout,
}
impl risc0_zkp::layout::Component for Sha256load_0__SuperLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256load_0__SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct ComputeAELayout {
    pub pack_ch: &'static Pack2Layout,
    pub _0: &'static Pack2Layout,
    pub _1: &'static Pack2Layout,
    pub _2: &'static Pack2Layout,
    pub pack_maj: &'static Pack2Layout,
    pub _3: &'static Pack2Layout,
    pub _4: &'static Pack2Layout,
}
impl risc0_zkp::layout::Component for ComputeAELayout {
    fn ty_name(&self) -> &'static str {
        "ComputeAELayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("pack_ch", self.pack_ch)?;
        v.visit_component("_0", self._0)?;
        v.visit_component("_1", self._1)?;
        v.visit_component("_2", self._2)?;
        v.visit_component("pack_maj", self.pack_maj)?;
        v.visit_component("_3", self._3)?;
        v.visit_component("_4", self._4)?;
        Ok(())
    }
}
pub struct ReadMemoryLayout {
    pub elem: &'static UseOnceMemoryElementLayout,
}
impl risc0_zkp::layout::Component for ReadMemoryLayout {
    fn ty_name(&self) -> &'static str {
        "ReadMemoryLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("elem", self.elem)?;
        Ok(())
    }
}
pub struct Sha256load_0_Arm0_SuperLayout {
    pub mem: &'static ReadMemoryLayout,
}
impl risc0_zkp::layout::Component for Sha256load_0_Arm0_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256load_0_Arm0_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("mem", self.mem)?;
        Ok(())
    }
}
pub struct Sha256load_0_Arm1Layout {
    pub _extra0: &'static UseOnceMemoryElementLayout,
}
impl risc0_zkp::layout::Component for Sha256load_0_Arm1Layout {
    fn ty_name(&self) -> &'static str {
        "Sha256load_0_Arm1Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_extra0", self._extra0)?;
        Ok(())
    }
}
pub struct Sha256load_0_ValsLayout {
    pub arm0: &'static Sha256load_0_Arm0_SuperLayout,
    pub arm1: &'static Sha256load_0_Arm1Layout,
}
impl risc0_zkp::layout::Component for Sha256load_0_ValsLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256load_0_ValsLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct _ArgumentsSha256load_0_ValsLayout {
    pub use_once_memory_element: &'static UseOnceMemoryElementLayout1LayoutArray,
}
impl risc0_zkp::layout::Component for _ArgumentsSha256load_0_ValsLayout {
    fn ty_name(&self) -> &'static str {
        "_ArgumentsSha256load_0_ValsLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("use_once_memory_element", self.use_once_memory_element)?;
        Ok(())
    }
}
pub struct Sha256load_0_Layout {
    pub _super: &'static Sha256load_0__SuperLayout,
    pub new_a: &'static UnpackWithCarryLayout,
    pub new_e: &'static UnpackWithCarryLayout,
    pub high_w: &'static ToBits_16_Layout,
    pub low_w: &'static ToBits_16_Layout,
    pub ae: &'static ComputeAELayout,
    pub inv_within: &'static NondetRegLayout,
    pub vals: &'static Sha256load_0_ValsLayout,
    pub _arguments_vals: &'static _ArgumentsSha256load_0_ValsLayout,
}
impl risc0_zkp::layout::Component for Sha256load_0_Layout {
    fn ty_name(&self) -> &'static str {
        "Sha256load_0_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("new_a", self.new_a)?;
        v.visit_component("new_e", self.new_e)?;
        v.visit_component("high_w", self.high_w)?;
        v.visit_component("low_w", self.low_w)?;
        v.visit_component("ae", self.ae)?;
        v.visit_component("inv_within", self.inv_within)?;
        v.visit_component("vals", self.vals)?;
        v.visit_component("_arguments_vals", self._arguments_vals)?;
        Ok(())
    }
}
pub struct Sha256load_1__SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static RetTupleLayout,
}
impl risc0_zkp::layout::Component for Sha256load_1__SuperLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256load_1__SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct Sha256load_1_Arm0_SuperLayout {
    pub mem: &'static ReadMemoryLayout,
}
impl risc0_zkp::layout::Component for Sha256load_1_Arm0_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256load_1_Arm0_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("mem", self.mem)?;
        Ok(())
    }
}
pub struct Sha256load_1_Arm1Layout {
    pub _extra0: &'static UseOnceMemoryElementLayout,
}
impl risc0_zkp::layout::Component for Sha256load_1_Arm1Layout {
    fn ty_name(&self) -> &'static str {
        "Sha256load_1_Arm1Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_extra0", self._extra0)?;
        Ok(())
    }
}
pub struct Sha256load_1_ValsLayout {
    pub arm0: &'static Sha256load_1_Arm0_SuperLayout,
    pub arm1: &'static Sha256load_1_Arm1Layout,
}
impl risc0_zkp::layout::Component for Sha256load_1_ValsLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256load_1_ValsLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct _ArgumentsSha256load_1_ValsLayout {
    pub use_once_memory_element: &'static UseOnceMemoryElementLayout1LayoutArray,
}
impl risc0_zkp::layout::Component for _ArgumentsSha256load_1_ValsLayout {
    fn ty_name(&self) -> &'static str {
        "_ArgumentsSha256load_1_ValsLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("use_once_memory_element", self.use_once_memory_element)?;
        Ok(())
    }
}
pub struct Sha256load_1_Layout {
    pub _super: &'static Sha256load_1__SuperLayout,
    pub new_a: &'static UnpackWithCarryLayout,
    pub new_e: &'static UnpackWithCarryLayout,
    pub high_w: &'static ToBits_16_Layout,
    pub low_w: &'static ToBits_16_Layout,
    pub ae: &'static ComputeAELayout,
    pub inv_within: &'static NondetRegLayout,
    pub vals: &'static Sha256load_1_ValsLayout,
    pub _arguments_vals: &'static _ArgumentsSha256load_1_ValsLayout,
}
impl risc0_zkp::layout::Component for Sha256load_1_Layout {
    fn ty_name(&self) -> &'static str {
        "Sha256load_1_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("new_a", self.new_a)?;
        v.visit_component("new_e", self.new_e)?;
        v.visit_component("high_w", self.high_w)?;
        v.visit_component("low_w", self.low_w)?;
        v.visit_component("ae", self.ae)?;
        v.visit_component("inv_within", self.inv_within)?;
        v.visit_component("vals", self.vals)?;
        v.visit_component("_arguments_vals", self._arguments_vals)?;
        Ok(())
    }
}
pub struct Sha256load_2__SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static RetTupleLayout,
}
impl risc0_zkp::layout::Component for Sha256load_2__SuperLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256load_2__SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct Sha256load_2_Arm0_SuperLayout {
    pub mem: &'static ReadMemoryLayout,
}
impl risc0_zkp::layout::Component for Sha256load_2_Arm0_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256load_2_Arm0_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("mem", self.mem)?;
        Ok(())
    }
}
pub struct Sha256load_2_Arm1Layout {
    pub _extra0: &'static UseOnceMemoryElementLayout,
}
impl risc0_zkp::layout::Component for Sha256load_2_Arm1Layout {
    fn ty_name(&self) -> &'static str {
        "Sha256load_2_Arm1Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_extra0", self._extra0)?;
        Ok(())
    }
}
pub struct Sha256load_2_ValsLayout {
    pub arm0: &'static Sha256load_2_Arm0_SuperLayout,
    pub arm1: &'static Sha256load_2_Arm1Layout,
}
impl risc0_zkp::layout::Component for Sha256load_2_ValsLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256load_2_ValsLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct _ArgumentsSha256load_2_ValsLayout {
    pub use_once_memory_element: &'static UseOnceMemoryElementLayout1LayoutArray,
}
impl risc0_zkp::layout::Component for _ArgumentsSha256load_2_ValsLayout {
    fn ty_name(&self) -> &'static str {
        "_ArgumentsSha256load_2_ValsLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("use_once_memory_element", self.use_once_memory_element)?;
        Ok(())
    }
}
pub struct Sha256load_2_Layout {
    pub _super: &'static Sha256load_2__SuperLayout,
    pub new_a: &'static UnpackWithCarryLayout,
    pub new_e: &'static UnpackWithCarryLayout,
    pub high_w: &'static ToBits_16_Layout,
    pub low_w: &'static ToBits_16_Layout,
    pub ae: &'static ComputeAELayout,
    pub inv_within: &'static NondetRegLayout,
    pub vals: &'static Sha256load_2_ValsLayout,
    pub _arguments_vals: &'static _ArgumentsSha256load_2_ValsLayout,
}
impl risc0_zkp::layout::Component for Sha256load_2_Layout {
    fn ty_name(&self) -> &'static str {
        "Sha256load_2_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("new_a", self.new_a)?;
        v.visit_component("new_e", self.new_e)?;
        v.visit_component("high_w", self.high_w)?;
        v.visit_component("low_w", self.low_w)?;
        v.visit_component("ae", self.ae)?;
        v.visit_component("inv_within", self.inv_within)?;
        v.visit_component("vals", self.vals)?;
        v.visit_component("_arguments_vals", self._arguments_vals)?;
        Ok(())
    }
}
pub struct Sha256load_3__SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static RetTupleLayout,
}
impl risc0_zkp::layout::Component for Sha256load_3__SuperLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256load_3__SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct Sha256load_3_Arm0_SuperLayout {
    pub mem: &'static ReadMemoryLayout,
}
impl risc0_zkp::layout::Component for Sha256load_3_Arm0_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256load_3_Arm0_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("mem", self.mem)?;
        Ok(())
    }
}
pub struct Sha256load_3_Arm1Layout {
    pub _extra0: &'static UseOnceMemoryElementLayout,
}
impl risc0_zkp::layout::Component for Sha256load_3_Arm1Layout {
    fn ty_name(&self) -> &'static str {
        "Sha256load_3_Arm1Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_extra0", self._extra0)?;
        Ok(())
    }
}
pub struct Sha256load_3_ValsLayout {
    pub arm0: &'static Sha256load_3_Arm0_SuperLayout,
    pub arm1: &'static Sha256load_3_Arm1Layout,
}
impl risc0_zkp::layout::Component for Sha256load_3_ValsLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256load_3_ValsLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct _ArgumentsSha256load_3_ValsLayout {
    pub use_once_memory_element: &'static UseOnceMemoryElementLayout1LayoutArray,
}
impl risc0_zkp::layout::Component for _ArgumentsSha256load_3_ValsLayout {
    fn ty_name(&self) -> &'static str {
        "_ArgumentsSha256load_3_ValsLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("use_once_memory_element", self.use_once_memory_element)?;
        Ok(())
    }
}
pub struct Sha256load_3_Layout {
    pub _super: &'static Sha256load_3__SuperLayout,
    pub new_a: &'static UnpackWithCarryLayout,
    pub new_e: &'static UnpackWithCarryLayout,
    pub high_w: &'static ToBits_16_Layout,
    pub low_w: &'static ToBits_16_Layout,
    pub ae: &'static ComputeAELayout,
    pub inv_within: &'static NondetRegLayout,
    pub vals: &'static Sha256load_3_ValsLayout,
    pub _arguments_vals: &'static _ArgumentsSha256load_3_ValsLayout,
}
impl risc0_zkp::layout::Component for Sha256load_3_Layout {
    fn ty_name(&self) -> &'static str {
        "Sha256load_3_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("new_a", self.new_a)?;
        v.visit_component("new_e", self.new_e)?;
        v.visit_component("high_w", self.high_w)?;
        v.visit_component("low_w", self.low_w)?;
        v.visit_component("ae", self.ae)?;
        v.visit_component("inv_within", self.inv_within)?;
        v.visit_component("vals", self.vals)?;
        v.visit_component("_arguments_vals", self._arguments_vals)?;
        Ok(())
    }
}
pub struct Sha256load_4__SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static RetTupleLayout,
}
impl risc0_zkp::layout::Component for Sha256load_4__SuperLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256load_4__SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct Sha256load_4_Arm0_SuperLayout {
    pub mem: &'static ReadMemoryLayout,
}
impl risc0_zkp::layout::Component for Sha256load_4_Arm0_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256load_4_Arm0_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("mem", self.mem)?;
        Ok(())
    }
}
pub struct Sha256load_4_Arm1Layout {
    pub _extra0: &'static UseOnceMemoryElementLayout,
}
impl risc0_zkp::layout::Component for Sha256load_4_Arm1Layout {
    fn ty_name(&self) -> &'static str {
        "Sha256load_4_Arm1Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_extra0", self._extra0)?;
        Ok(())
    }
}
pub struct Sha256load_4_ValsLayout {
    pub arm0: &'static Sha256load_4_Arm0_SuperLayout,
    pub arm1: &'static Sha256load_4_Arm1Layout,
}
impl risc0_zkp::layout::Component for Sha256load_4_ValsLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256load_4_ValsLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct _ArgumentsSha256load_4_ValsLayout {
    pub use_once_memory_element: &'static UseOnceMemoryElementLayout1LayoutArray,
}
impl risc0_zkp::layout::Component for _ArgumentsSha256load_4_ValsLayout {
    fn ty_name(&self) -> &'static str {
        "_ArgumentsSha256load_4_ValsLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("use_once_memory_element", self.use_once_memory_element)?;
        Ok(())
    }
}
pub struct Sha256load_4_Layout {
    pub _super: &'static Sha256load_4__SuperLayout,
    pub new_a: &'static UnpackWithCarryLayout,
    pub new_e: &'static UnpackWithCarryLayout,
    pub high_w: &'static ToBits_16_Layout,
    pub low_w: &'static ToBits_16_Layout,
    pub ae: &'static ComputeAELayout,
    pub inv_within: &'static NondetRegLayout,
    pub vals: &'static Sha256load_4_ValsLayout,
    pub _arguments_vals: &'static _ArgumentsSha256load_4_ValsLayout,
}
impl risc0_zkp::layout::Component for Sha256load_4_Layout {
    fn ty_name(&self) -> &'static str {
        "Sha256load_4_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("new_a", self.new_a)?;
        v.visit_component("new_e", self.new_e)?;
        v.visit_component("high_w", self.high_w)?;
        v.visit_component("low_w", self.low_w)?;
        v.visit_component("ae", self.ae)?;
        v.visit_component("inv_within", self.inv_within)?;
        v.visit_component("vals", self.vals)?;
        v.visit_component("_arguments_vals", self._arguments_vals)?;
        Ok(())
    }
}
pub struct Sha256load_5__SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static RetTupleLayout,
}
impl risc0_zkp::layout::Component for Sha256load_5__SuperLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256load_5__SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct Sha256load_5_Arm0_SuperLayout {
    pub mem: &'static ReadMemoryLayout,
}
impl risc0_zkp::layout::Component for Sha256load_5_Arm0_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256load_5_Arm0_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("mem", self.mem)?;
        Ok(())
    }
}
pub struct Sha256load_5_Arm1Layout {
    pub _extra0: &'static UseOnceMemoryElementLayout,
}
impl risc0_zkp::layout::Component for Sha256load_5_Arm1Layout {
    fn ty_name(&self) -> &'static str {
        "Sha256load_5_Arm1Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_extra0", self._extra0)?;
        Ok(())
    }
}
pub struct Sha256load_5_ValsLayout {
    pub arm0: &'static Sha256load_5_Arm0_SuperLayout,
    pub arm1: &'static Sha256load_5_Arm1Layout,
}
impl risc0_zkp::layout::Component for Sha256load_5_ValsLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256load_5_ValsLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct _ArgumentsSha256load_5_ValsLayout {
    pub use_once_memory_element: &'static UseOnceMemoryElementLayout1LayoutArray,
}
impl risc0_zkp::layout::Component for _ArgumentsSha256load_5_ValsLayout {
    fn ty_name(&self) -> &'static str {
        "_ArgumentsSha256load_5_ValsLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("use_once_memory_element", self.use_once_memory_element)?;
        Ok(())
    }
}
pub struct Sha256load_5_Layout {
    pub _super: &'static Sha256load_5__SuperLayout,
    pub new_a: &'static UnpackWithCarryLayout,
    pub new_e: &'static UnpackWithCarryLayout,
    pub high_w: &'static ToBits_16_Layout,
    pub low_w: &'static ToBits_16_Layout,
    pub ae: &'static ComputeAELayout,
    pub inv_within: &'static NondetRegLayout,
    pub vals: &'static Sha256load_5_ValsLayout,
    pub _arguments_vals: &'static _ArgumentsSha256load_5_ValsLayout,
}
impl risc0_zkp::layout::Component for Sha256load_5_Layout {
    fn ty_name(&self) -> &'static str {
        "Sha256load_5_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("new_a", self.new_a)?;
        v.visit_component("new_e", self.new_e)?;
        v.visit_component("high_w", self.high_w)?;
        v.visit_component("low_w", self.low_w)?;
        v.visit_component("ae", self.ae)?;
        v.visit_component("inv_within", self.inv_within)?;
        v.visit_component("vals", self.vals)?;
        v.visit_component("_arguments_vals", self._arguments_vals)?;
        Ok(())
    }
}
pub struct Sha256load_6__SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static RetTupleLayout,
}
impl risc0_zkp::layout::Component for Sha256load_6__SuperLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256load_6__SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct Sha256load_6_Arm0_SuperLayout {
    pub mem: &'static ReadMemoryLayout,
}
impl risc0_zkp::layout::Component for Sha256load_6_Arm0_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256load_6_Arm0_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("mem", self.mem)?;
        Ok(())
    }
}
pub struct Sha256load_6_Arm1Layout {
    pub _extra0: &'static UseOnceMemoryElementLayout,
}
impl risc0_zkp::layout::Component for Sha256load_6_Arm1Layout {
    fn ty_name(&self) -> &'static str {
        "Sha256load_6_Arm1Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_extra0", self._extra0)?;
        Ok(())
    }
}
pub struct Sha256load_6_ValsLayout {
    pub arm0: &'static Sha256load_6_Arm0_SuperLayout,
    pub arm1: &'static Sha256load_6_Arm1Layout,
}
impl risc0_zkp::layout::Component for Sha256load_6_ValsLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256load_6_ValsLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct _ArgumentsSha256load_6_ValsLayout {
    pub use_once_memory_element: &'static UseOnceMemoryElementLayout1LayoutArray,
}
impl risc0_zkp::layout::Component for _ArgumentsSha256load_6_ValsLayout {
    fn ty_name(&self) -> &'static str {
        "_ArgumentsSha256load_6_ValsLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("use_once_memory_element", self.use_once_memory_element)?;
        Ok(())
    }
}
pub struct Sha256load_6_Layout {
    pub _super: &'static Sha256load_6__SuperLayout,
    pub new_a: &'static UnpackWithCarryLayout,
    pub new_e: &'static UnpackWithCarryLayout,
    pub high_w: &'static ToBits_16_Layout,
    pub low_w: &'static ToBits_16_Layout,
    pub ae: &'static ComputeAELayout,
    pub inv_within: &'static NondetRegLayout,
    pub vals: &'static Sha256load_6_ValsLayout,
    pub _arguments_vals: &'static _ArgumentsSha256load_6_ValsLayout,
}
impl risc0_zkp::layout::Component for Sha256load_6_Layout {
    fn ty_name(&self) -> &'static str {
        "Sha256load_6_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("new_a", self.new_a)?;
        v.visit_component("new_e", self.new_e)?;
        v.visit_component("high_w", self.high_w)?;
        v.visit_component("low_w", self.low_w)?;
        v.visit_component("ae", self.ae)?;
        v.visit_component("inv_within", self.inv_within)?;
        v.visit_component("vals", self.vals)?;
        v.visit_component("_arguments_vals", self._arguments_vals)?;
        Ok(())
    }
}
pub struct Sha256load_7__SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static RetTupleLayout,
}
impl risc0_zkp::layout::Component for Sha256load_7__SuperLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256load_7__SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct Sha256load_7_Arm0_SuperLayout {
    pub mem: &'static ReadMemoryLayout,
}
impl risc0_zkp::layout::Component for Sha256load_7_Arm0_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256load_7_Arm0_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("mem", self.mem)?;
        Ok(())
    }
}
pub struct Sha256load_7_Arm1Layout {
    pub _extra0: &'static UseOnceMemoryElementLayout,
}
impl risc0_zkp::layout::Component for Sha256load_7_Arm1Layout {
    fn ty_name(&self) -> &'static str {
        "Sha256load_7_Arm1Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_extra0", self._extra0)?;
        Ok(())
    }
}
pub struct Sha256load_7_ValsLayout {
    pub arm0: &'static Sha256load_7_Arm0_SuperLayout,
    pub arm1: &'static Sha256load_7_Arm1Layout,
}
impl risc0_zkp::layout::Component for Sha256load_7_ValsLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256load_7_ValsLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct _ArgumentsSha256load_7_ValsLayout {
    pub use_once_memory_element: &'static UseOnceMemoryElementLayout1LayoutArray,
}
impl risc0_zkp::layout::Component for _ArgumentsSha256load_7_ValsLayout {
    fn ty_name(&self) -> &'static str {
        "_ArgumentsSha256load_7_ValsLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("use_once_memory_element", self.use_once_memory_element)?;
        Ok(())
    }
}
pub struct Sha256load_7_Layout {
    pub _super: &'static Sha256load_7__SuperLayout,
    pub new_a: &'static UnpackWithCarryLayout,
    pub new_e: &'static UnpackWithCarryLayout,
    pub high_w: &'static ToBits_16_Layout,
    pub low_w: &'static ToBits_16_Layout,
    pub ae: &'static ComputeAELayout,
    pub inv_within: &'static NondetRegLayout,
    pub vals: &'static Sha256load_7_ValsLayout,
    pub _arguments_vals: &'static _ArgumentsSha256load_7_ValsLayout,
}
impl risc0_zkp::layout::Component for Sha256load_7_Layout {
    fn ty_name(&self) -> &'static str {
        "Sha256load_7_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("new_a", self.new_a)?;
        v.visit_component("new_e", self.new_e)?;
        v.visit_component("high_w", self.high_w)?;
        v.visit_component("low_w", self.low_w)?;
        v.visit_component("ae", self.ae)?;
        v.visit_component("inv_within", self.inv_within)?;
        v.visit_component("vals", self.vals)?;
        v.visit_component("_arguments_vals", self._arguments_vals)?;
        Ok(())
    }
}
pub struct Sha256load_8__SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static RetTupleLayout,
}
impl risc0_zkp::layout::Component for Sha256load_8__SuperLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256load_8__SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct Sha256load_8_Arm0_SuperLayout {
    pub mem: &'static ReadMemoryLayout,
}
impl risc0_zkp::layout::Component for Sha256load_8_Arm0_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256load_8_Arm0_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("mem", self.mem)?;
        Ok(())
    }
}
pub struct Sha256load_8_Arm1Layout {
    pub _extra0: &'static UseOnceMemoryElementLayout,
}
impl risc0_zkp::layout::Component for Sha256load_8_Arm1Layout {
    fn ty_name(&self) -> &'static str {
        "Sha256load_8_Arm1Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_extra0", self._extra0)?;
        Ok(())
    }
}
pub struct Sha256load_8_ValsLayout {
    pub arm0: &'static Sha256load_8_Arm0_SuperLayout,
    pub arm1: &'static Sha256load_8_Arm1Layout,
}
impl risc0_zkp::layout::Component for Sha256load_8_ValsLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256load_8_ValsLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct _ArgumentsSha256load_8_ValsLayout {
    pub use_once_memory_element: &'static UseOnceMemoryElementLayout1LayoutArray,
}
impl risc0_zkp::layout::Component for _ArgumentsSha256load_8_ValsLayout {
    fn ty_name(&self) -> &'static str {
        "_ArgumentsSha256load_8_ValsLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("use_once_memory_element", self.use_once_memory_element)?;
        Ok(())
    }
}
pub struct Sha256load_8_Layout {
    pub _super: &'static Sha256load_8__SuperLayout,
    pub new_a: &'static UnpackWithCarryLayout,
    pub new_e: &'static UnpackWithCarryLayout,
    pub high_w: &'static ToBits_16_Layout,
    pub low_w: &'static ToBits_16_Layout,
    pub ae: &'static ComputeAELayout,
    pub inv_within: &'static NondetRegLayout,
    pub vals: &'static Sha256load_8_ValsLayout,
    pub _arguments_vals: &'static _ArgumentsSha256load_8_ValsLayout,
}
impl risc0_zkp::layout::Component for Sha256load_8_Layout {
    fn ty_name(&self) -> &'static str {
        "Sha256load_8_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("new_a", self.new_a)?;
        v.visit_component("new_e", self.new_e)?;
        v.visit_component("high_w", self.high_w)?;
        v.visit_component("low_w", self.low_w)?;
        v.visit_component("ae", self.ae)?;
        v.visit_component("inv_within", self.inv_within)?;
        v.visit_component("vals", self.vals)?;
        v.visit_component("_arguments_vals", self._arguments_vals)?;
        Ok(())
    }
}
pub struct Sha256load_9__SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static RetTupleLayout,
}
impl risc0_zkp::layout::Component for Sha256load_9__SuperLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256load_9__SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct Sha256load_9_Arm0_SuperLayout {
    pub mem: &'static ReadMemoryLayout,
}
impl risc0_zkp::layout::Component for Sha256load_9_Arm0_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256load_9_Arm0_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("mem", self.mem)?;
        Ok(())
    }
}
pub struct Sha256load_9_Arm1Layout {
    pub _extra0: &'static UseOnceMemoryElementLayout,
}
impl risc0_zkp::layout::Component for Sha256load_9_Arm1Layout {
    fn ty_name(&self) -> &'static str {
        "Sha256load_9_Arm1Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_extra0", self._extra0)?;
        Ok(())
    }
}
pub struct Sha256load_9_ValsLayout {
    pub arm0: &'static Sha256load_9_Arm0_SuperLayout,
    pub arm1: &'static Sha256load_9_Arm1Layout,
}
impl risc0_zkp::layout::Component for Sha256load_9_ValsLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256load_9_ValsLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct _ArgumentsSha256load_9_ValsLayout {
    pub use_once_memory_element: &'static UseOnceMemoryElementLayout1LayoutArray,
}
impl risc0_zkp::layout::Component for _ArgumentsSha256load_9_ValsLayout {
    fn ty_name(&self) -> &'static str {
        "_ArgumentsSha256load_9_ValsLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("use_once_memory_element", self.use_once_memory_element)?;
        Ok(())
    }
}
pub struct Sha256load_9_Layout {
    pub _super: &'static Sha256load_9__SuperLayout,
    pub new_a: &'static UnpackWithCarryLayout,
    pub new_e: &'static UnpackWithCarryLayout,
    pub high_w: &'static ToBits_16_Layout,
    pub low_w: &'static ToBits_16_Layout,
    pub ae: &'static ComputeAELayout,
    pub inv_within: &'static NondetRegLayout,
    pub vals: &'static Sha256load_9_ValsLayout,
    pub _arguments_vals: &'static _ArgumentsSha256load_9_ValsLayout,
}
impl risc0_zkp::layout::Component for Sha256load_9_Layout {
    fn ty_name(&self) -> &'static str {
        "Sha256load_9_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("new_a", self.new_a)?;
        v.visit_component("new_e", self.new_e)?;
        v.visit_component("high_w", self.high_w)?;
        v.visit_component("low_w", self.low_w)?;
        v.visit_component("ae", self.ae)?;
        v.visit_component("inv_within", self.inv_within)?;
        v.visit_component("vals", self.vals)?;
        v.visit_component("_arguments_vals", self._arguments_vals)?;
        Ok(())
    }
}
pub struct Sha256load_10__SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static RetTupleLayout,
}
impl risc0_zkp::layout::Component for Sha256load_10__SuperLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256load_10__SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct Sha256load_10_Arm0_SuperLayout {
    pub mem: &'static ReadMemoryLayout,
}
impl risc0_zkp::layout::Component for Sha256load_10_Arm0_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256load_10_Arm0_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("mem", self.mem)?;
        Ok(())
    }
}
pub struct Sha256load_10_Arm1Layout {
    pub _extra0: &'static UseOnceMemoryElementLayout,
}
impl risc0_zkp::layout::Component for Sha256load_10_Arm1Layout {
    fn ty_name(&self) -> &'static str {
        "Sha256load_10_Arm1Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_extra0", self._extra0)?;
        Ok(())
    }
}
pub struct Sha256load_10_ValsLayout {
    pub arm0: &'static Sha256load_10_Arm0_SuperLayout,
    pub arm1: &'static Sha256load_10_Arm1Layout,
}
impl risc0_zkp::layout::Component for Sha256load_10_ValsLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256load_10_ValsLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct _ArgumentsSha256load_10_ValsLayout {
    pub use_once_memory_element: &'static UseOnceMemoryElementLayout1LayoutArray,
}
impl risc0_zkp::layout::Component for _ArgumentsSha256load_10_ValsLayout {
    fn ty_name(&self) -> &'static str {
        "_ArgumentsSha256load_10_ValsLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("use_once_memory_element", self.use_once_memory_element)?;
        Ok(())
    }
}
pub struct Sha256load_10_Layout {
    pub _super: &'static Sha256load_10__SuperLayout,
    pub new_a: &'static UnpackWithCarryLayout,
    pub new_e: &'static UnpackWithCarryLayout,
    pub high_w: &'static ToBits_16_Layout,
    pub low_w: &'static ToBits_16_Layout,
    pub ae: &'static ComputeAELayout,
    pub inv_within: &'static NondetRegLayout,
    pub vals: &'static Sha256load_10_ValsLayout,
    pub _arguments_vals: &'static _ArgumentsSha256load_10_ValsLayout,
}
impl risc0_zkp::layout::Component for Sha256load_10_Layout {
    fn ty_name(&self) -> &'static str {
        "Sha256load_10_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("new_a", self.new_a)?;
        v.visit_component("new_e", self.new_e)?;
        v.visit_component("high_w", self.high_w)?;
        v.visit_component("low_w", self.low_w)?;
        v.visit_component("ae", self.ae)?;
        v.visit_component("inv_within", self.inv_within)?;
        v.visit_component("vals", self.vals)?;
        v.visit_component("_arguments_vals", self._arguments_vals)?;
        Ok(())
    }
}
pub struct Sha256load_11__SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static RetTupleLayout,
}
impl risc0_zkp::layout::Component for Sha256load_11__SuperLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256load_11__SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct Sha256load_11_Arm0_SuperLayout {
    pub mem: &'static ReadMemoryLayout,
}
impl risc0_zkp::layout::Component for Sha256load_11_Arm0_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256load_11_Arm0_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("mem", self.mem)?;
        Ok(())
    }
}
pub struct Sha256load_11_Arm1Layout {
    pub _extra0: &'static UseOnceMemoryElementLayout,
}
impl risc0_zkp::layout::Component for Sha256load_11_Arm1Layout {
    fn ty_name(&self) -> &'static str {
        "Sha256load_11_Arm1Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_extra0", self._extra0)?;
        Ok(())
    }
}
pub struct Sha256load_11_ValsLayout {
    pub arm0: &'static Sha256load_11_Arm0_SuperLayout,
    pub arm1: &'static Sha256load_11_Arm1Layout,
}
impl risc0_zkp::layout::Component for Sha256load_11_ValsLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256load_11_ValsLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct _ArgumentsSha256load_11_ValsLayout {
    pub use_once_memory_element: &'static UseOnceMemoryElementLayout1LayoutArray,
}
impl risc0_zkp::layout::Component for _ArgumentsSha256load_11_ValsLayout {
    fn ty_name(&self) -> &'static str {
        "_ArgumentsSha256load_11_ValsLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("use_once_memory_element", self.use_once_memory_element)?;
        Ok(())
    }
}
pub struct Sha256load_11_Layout {
    pub _super: &'static Sha256load_11__SuperLayout,
    pub new_a: &'static UnpackWithCarryLayout,
    pub new_e: &'static UnpackWithCarryLayout,
    pub high_w: &'static ToBits_16_Layout,
    pub low_w: &'static ToBits_16_Layout,
    pub ae: &'static ComputeAELayout,
    pub inv_within: &'static NondetRegLayout,
    pub vals: &'static Sha256load_11_ValsLayout,
    pub _arguments_vals: &'static _ArgumentsSha256load_11_ValsLayout,
}
impl risc0_zkp::layout::Component for Sha256load_11_Layout {
    fn ty_name(&self) -> &'static str {
        "Sha256load_11_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("new_a", self.new_a)?;
        v.visit_component("new_e", self.new_e)?;
        v.visit_component("high_w", self.high_w)?;
        v.visit_component("low_w", self.low_w)?;
        v.visit_component("ae", self.ae)?;
        v.visit_component("inv_within", self.inv_within)?;
        v.visit_component("vals", self.vals)?;
        v.visit_component("_arguments_vals", self._arguments_vals)?;
        Ok(())
    }
}
pub struct Sha256load_12__SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static RetTupleLayout,
}
impl risc0_zkp::layout::Component for Sha256load_12__SuperLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256load_12__SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct Sha256load_12_Arm0_SuperLayout {
    pub mem: &'static ReadMemoryLayout,
}
impl risc0_zkp::layout::Component for Sha256load_12_Arm0_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256load_12_Arm0_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("mem", self.mem)?;
        Ok(())
    }
}
pub struct Sha256load_12_Arm1Layout {
    pub _extra0: &'static UseOnceMemoryElementLayout,
}
impl risc0_zkp::layout::Component for Sha256load_12_Arm1Layout {
    fn ty_name(&self) -> &'static str {
        "Sha256load_12_Arm1Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_extra0", self._extra0)?;
        Ok(())
    }
}
pub struct Sha256load_12_ValsLayout {
    pub arm0: &'static Sha256load_12_Arm0_SuperLayout,
    pub arm1: &'static Sha256load_12_Arm1Layout,
}
impl risc0_zkp::layout::Component for Sha256load_12_ValsLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256load_12_ValsLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct _ArgumentsSha256load_12_ValsLayout {
    pub use_once_memory_element: &'static UseOnceMemoryElementLayout1LayoutArray,
}
impl risc0_zkp::layout::Component for _ArgumentsSha256load_12_ValsLayout {
    fn ty_name(&self) -> &'static str {
        "_ArgumentsSha256load_12_ValsLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("use_once_memory_element", self.use_once_memory_element)?;
        Ok(())
    }
}
pub struct Sha256load_12_Layout {
    pub _super: &'static Sha256load_12__SuperLayout,
    pub new_a: &'static UnpackWithCarryLayout,
    pub new_e: &'static UnpackWithCarryLayout,
    pub high_w: &'static ToBits_16_Layout,
    pub low_w: &'static ToBits_16_Layout,
    pub ae: &'static ComputeAELayout,
    pub inv_within: &'static NondetRegLayout,
    pub vals: &'static Sha256load_12_ValsLayout,
    pub _arguments_vals: &'static _ArgumentsSha256load_12_ValsLayout,
}
impl risc0_zkp::layout::Component for Sha256load_12_Layout {
    fn ty_name(&self) -> &'static str {
        "Sha256load_12_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("new_a", self.new_a)?;
        v.visit_component("new_e", self.new_e)?;
        v.visit_component("high_w", self.high_w)?;
        v.visit_component("low_w", self.low_w)?;
        v.visit_component("ae", self.ae)?;
        v.visit_component("inv_within", self.inv_within)?;
        v.visit_component("vals", self.vals)?;
        v.visit_component("_arguments_vals", self._arguments_vals)?;
        Ok(())
    }
}
pub struct Sha256load_13__SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static RetTupleLayout,
}
impl risc0_zkp::layout::Component for Sha256load_13__SuperLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256load_13__SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct Sha256load_13_Arm0_SuperLayout {
    pub mem: &'static ReadMemoryLayout,
}
impl risc0_zkp::layout::Component for Sha256load_13_Arm0_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256load_13_Arm0_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("mem", self.mem)?;
        Ok(())
    }
}
pub struct Sha256load_13_Arm1Layout {
    pub _extra0: &'static UseOnceMemoryElementLayout,
}
impl risc0_zkp::layout::Component for Sha256load_13_Arm1Layout {
    fn ty_name(&self) -> &'static str {
        "Sha256load_13_Arm1Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_extra0", self._extra0)?;
        Ok(())
    }
}
pub struct Sha256load_13_ValsLayout {
    pub arm0: &'static Sha256load_13_Arm0_SuperLayout,
    pub arm1: &'static Sha256load_13_Arm1Layout,
}
impl risc0_zkp::layout::Component for Sha256load_13_ValsLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256load_13_ValsLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct _ArgumentsSha256load_13_ValsLayout {
    pub use_once_memory_element: &'static UseOnceMemoryElementLayout1LayoutArray,
}
impl risc0_zkp::layout::Component for _ArgumentsSha256load_13_ValsLayout {
    fn ty_name(&self) -> &'static str {
        "_ArgumentsSha256load_13_ValsLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("use_once_memory_element", self.use_once_memory_element)?;
        Ok(())
    }
}
pub struct Sha256load_13_Layout {
    pub _super: &'static Sha256load_13__SuperLayout,
    pub new_a: &'static UnpackWithCarryLayout,
    pub new_e: &'static UnpackWithCarryLayout,
    pub high_w: &'static ToBits_16_Layout,
    pub low_w: &'static ToBits_16_Layout,
    pub ae: &'static ComputeAELayout,
    pub inv_within: &'static NondetRegLayout,
    pub vals: &'static Sha256load_13_ValsLayout,
    pub _arguments_vals: &'static _ArgumentsSha256load_13_ValsLayout,
}
impl risc0_zkp::layout::Component for Sha256load_13_Layout {
    fn ty_name(&self) -> &'static str {
        "Sha256load_13_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("new_a", self.new_a)?;
        v.visit_component("new_e", self.new_e)?;
        v.visit_component("high_w", self.high_w)?;
        v.visit_component("low_w", self.low_w)?;
        v.visit_component("ae", self.ae)?;
        v.visit_component("inv_within", self.inv_within)?;
        v.visit_component("vals", self.vals)?;
        v.visit_component("_arguments_vals", self._arguments_vals)?;
        Ok(())
    }
}
pub struct Sha256load_14__SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static RetTupleLayout,
}
impl risc0_zkp::layout::Component for Sha256load_14__SuperLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256load_14__SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct Sha256load_14_Arm0_SuperLayout {
    pub mem: &'static ReadMemoryLayout,
}
impl risc0_zkp::layout::Component for Sha256load_14_Arm0_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256load_14_Arm0_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("mem", self.mem)?;
        Ok(())
    }
}
pub struct Sha256load_14_Arm1Layout {
    pub _extra0: &'static UseOnceMemoryElementLayout,
}
impl risc0_zkp::layout::Component for Sha256load_14_Arm1Layout {
    fn ty_name(&self) -> &'static str {
        "Sha256load_14_Arm1Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_extra0", self._extra0)?;
        Ok(())
    }
}
pub struct Sha256load_14_ValsLayout {
    pub arm0: &'static Sha256load_14_Arm0_SuperLayout,
    pub arm1: &'static Sha256load_14_Arm1Layout,
}
impl risc0_zkp::layout::Component for Sha256load_14_ValsLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256load_14_ValsLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct _ArgumentsSha256load_14_ValsLayout {
    pub use_once_memory_element: &'static UseOnceMemoryElementLayout1LayoutArray,
}
impl risc0_zkp::layout::Component for _ArgumentsSha256load_14_ValsLayout {
    fn ty_name(&self) -> &'static str {
        "_ArgumentsSha256load_14_ValsLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("use_once_memory_element", self.use_once_memory_element)?;
        Ok(())
    }
}
pub struct Sha256load_14_Layout {
    pub _super: &'static Sha256load_14__SuperLayout,
    pub new_a: &'static UnpackWithCarryLayout,
    pub new_e: &'static UnpackWithCarryLayout,
    pub high_w: &'static ToBits_16_Layout,
    pub low_w: &'static ToBits_16_Layout,
    pub ae: &'static ComputeAELayout,
    pub inv_within: &'static NondetRegLayout,
    pub vals: &'static Sha256load_14_ValsLayout,
    pub _arguments_vals: &'static _ArgumentsSha256load_14_ValsLayout,
}
impl risc0_zkp::layout::Component for Sha256load_14_Layout {
    fn ty_name(&self) -> &'static str {
        "Sha256load_14_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("new_a", self.new_a)?;
        v.visit_component("new_e", self.new_e)?;
        v.visit_component("high_w", self.high_w)?;
        v.visit_component("low_w", self.low_w)?;
        v.visit_component("ae", self.ae)?;
        v.visit_component("inv_within", self.inv_within)?;
        v.visit_component("vals", self.vals)?;
        v.visit_component("_arguments_vals", self._arguments_vals)?;
        Ok(())
    }
}
pub struct Sha256load_15__SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static RetTupleLayout,
}
impl risc0_zkp::layout::Component for Sha256load_15__SuperLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256load_15__SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct Sha256load_15_Arm0_SuperLayout {
    pub mem: &'static ReadMemoryLayout,
}
impl risc0_zkp::layout::Component for Sha256load_15_Arm0_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256load_15_Arm0_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("mem", self.mem)?;
        Ok(())
    }
}
pub struct Sha256load_15_Arm1Layout {
    pub _extra0: &'static UseOnceMemoryElementLayout,
}
impl risc0_zkp::layout::Component for Sha256load_15_Arm1Layout {
    fn ty_name(&self) -> &'static str {
        "Sha256load_15_Arm1Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_extra0", self._extra0)?;
        Ok(())
    }
}
pub struct Sha256load_15_ValsLayout {
    pub arm0: &'static Sha256load_15_Arm0_SuperLayout,
    pub arm1: &'static Sha256load_15_Arm1Layout,
}
impl risc0_zkp::layout::Component for Sha256load_15_ValsLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256load_15_ValsLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct _ArgumentsSha256load_15_ValsLayout {
    pub use_once_memory_element: &'static UseOnceMemoryElementLayout1LayoutArray,
}
impl risc0_zkp::layout::Component for _ArgumentsSha256load_15_ValsLayout {
    fn ty_name(&self) -> &'static str {
        "_ArgumentsSha256load_15_ValsLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("use_once_memory_element", self.use_once_memory_element)?;
        Ok(())
    }
}
pub struct Sha256load_15_Layout {
    pub _super: &'static Sha256load_15__SuperLayout,
    pub new_a: &'static UnpackWithCarryLayout,
    pub new_e: &'static UnpackWithCarryLayout,
    pub high_w: &'static ToBits_16_Layout,
    pub low_w: &'static ToBits_16_Layout,
    pub ae: &'static ComputeAELayout,
    pub inv_within: &'static NondetRegLayout,
    pub vals: &'static Sha256load_15_ValsLayout,
    pub _arguments_vals: &'static _ArgumentsSha256load_15_ValsLayout,
}
impl risc0_zkp::layout::Component for Sha256load_15_Layout {
    fn ty_name(&self) -> &'static str {
        "Sha256load_15_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("new_a", self.new_a)?;
        v.visit_component("new_e", self.new_e)?;
        v.visit_component("high_w", self.high_w)?;
        v.visit_component("low_w", self.low_w)?;
        v.visit_component("ae", self.ae)?;
        v.visit_component("inv_within", self.inv_within)?;
        v.visit_component("vals", self.vals)?;
        v.visit_component("_arguments_vals", self._arguments_vals)?;
        Ok(())
    }
}
pub struct Sha256loadAll_SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static Sha256load_0_Layout,
    pub arm1: &'static Sha256load_1_Layout,
    pub arm2: &'static Sha256load_2_Layout,
    pub arm3: &'static Sha256load_3_Layout,
    pub arm4: &'static Sha256load_4_Layout,
    pub arm5: &'static Sha256load_5_Layout,
    pub arm6: &'static Sha256load_6_Layout,
    pub arm7: &'static Sha256load_7_Layout,
    pub arm8: &'static Sha256load_8_Layout,
    pub arm9: &'static Sha256load_9_Layout,
    pub arm10: &'static Sha256load_10_Layout,
    pub arm11: &'static Sha256load_11_Layout,
    pub arm12: &'static Sha256load_12_Layout,
    pub arm13: &'static Sha256load_13_Layout,
    pub arm14: &'static Sha256load_14_Layout,
    pub arm15: &'static Sha256load_15_Layout,
}
impl risc0_zkp::layout::Component for Sha256loadAll_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256loadAll_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        v.visit_component("arm2", self.arm2)?;
        v.visit_component("arm3", self.arm3)?;
        v.visit_component("arm4", self.arm4)?;
        v.visit_component("arm5", self.arm5)?;
        v.visit_component("arm6", self.arm6)?;
        v.visit_component("arm7", self.arm7)?;
        v.visit_component("arm8", self.arm8)?;
        v.visit_component("arm9", self.arm9)?;
        v.visit_component("arm10", self.arm10)?;
        v.visit_component("arm11", self.arm11)?;
        v.visit_component("arm12", self.arm12)?;
        v.visit_component("arm13", self.arm13)?;
        v.visit_component("arm14", self.arm14)?;
        v.visit_component("arm15", self.arm15)?;
        Ok(())
    }
}
pub struct _ArgumentsSha256loadAll_SuperLayout {
    pub use_once_memory_element: &'static UseOnceMemoryElementLayout1LayoutArray,
}
impl risc0_zkp::layout::Component for _ArgumentsSha256loadAll_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "_ArgumentsSha256loadAll_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("use_once_memory_element", self.use_once_memory_element)?;
        Ok(())
    }
}
pub struct OneHot_16_Layout {
    pub _super: &'static NondetRegLayout16LayoutArray,
}
impl risc0_zkp::layout::Component for OneHot_16_Layout {
    fn ty_name(&self) -> &'static str {
        "OneHot_16_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        Ok(())
    }
}
pub struct Sha256loadAllLayout {
    pub _super: &'static Sha256loadAll_SuperLayout,
    pub _arguments__super: &'static _ArgumentsSha256loadAll_SuperLayout,
    pub minor_onehot: &'static OneHot_16_Layout,
}
impl risc0_zkp::layout::Component for Sha256loadAllLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256loadAllLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("_arguments__super", self._arguments__super)?;
        v.visit_component("minor_onehot", self.minor_onehot)?;
        Ok(())
    }
}
pub struct Sha256mix_0__0_Arm1_Super_SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static RetTupleLayout,
}
impl risc0_zkp::layout::Component for Sha256mix_0__0_Arm1_Super_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256mix_0__0_Arm1_Super_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct Sha256mix_0__0__SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static Sha256mix_0__0_Arm1_Super_SuperLayout,
}
impl risc0_zkp::layout::Component for Sha256mix_0__0__SuperLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256mix_0__0__SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct ComputeWLayout {
    pub pack_s0: &'static Pack2Layout,
    pub pack_s1: &'static Pack2Layout,
    pub _0: &'static Pack2Layout,
    pub _1: &'static Pack2Layout,
}
impl risc0_zkp::layout::Component for ComputeWLayout {
    fn ty_name(&self) -> &'static str {
        "ComputeWLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("pack_s0", self.pack_s0)?;
        v.visit_component("pack_s1", self.pack_s1)?;
        v.visit_component("_0", self._0)?;
        v.visit_component("_1", self._1)?;
        Ok(())
    }
}
pub struct Sha256mix_0__0_Layout {
    pub _super: &'static Sha256mix_0__0__SuperLayout,
    pub new_w: &'static UnpackWithCarryLayout,
    pub new_a: &'static UnpackWithCarryLayout,
    pub new_e: &'static UnpackWithCarryLayout,
    pub ae: &'static ComputeAELayout,
    pub packed_w: &'static ComputeWLayout,
}
impl risc0_zkp::layout::Component for Sha256mix_0__0_Layout {
    fn ty_name(&self) -> &'static str {
        "Sha256mix_0__0_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("new_w", self.new_w)?;
        v.visit_component("new_a", self.new_a)?;
        v.visit_component("new_e", self.new_e)?;
        v.visit_component("ae", self.ae)?;
        v.visit_component("packed_w", self.packed_w)?;
        Ok(())
    }
}
pub struct Sha256mix_0__1_Arm1_Super_SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static RetTupleLayout,
}
impl risc0_zkp::layout::Component for Sha256mix_0__1_Arm1_Super_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256mix_0__1_Arm1_Super_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct Sha256mix_0__1__SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static Sha256mix_0__1_Arm1_Super_SuperLayout,
}
impl risc0_zkp::layout::Component for Sha256mix_0__1__SuperLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256mix_0__1__SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct Sha256mix_0__1_Layout {
    pub _super: &'static Sha256mix_0__1__SuperLayout,
    pub new_w: &'static UnpackWithCarryLayout,
    pub new_a: &'static UnpackWithCarryLayout,
    pub new_e: &'static UnpackWithCarryLayout,
    pub ae: &'static ComputeAELayout,
    pub packed_w: &'static ComputeWLayout,
}
impl risc0_zkp::layout::Component for Sha256mix_0__1_Layout {
    fn ty_name(&self) -> &'static str {
        "Sha256mix_0__1_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("new_w", self.new_w)?;
        v.visit_component("new_a", self.new_a)?;
        v.visit_component("new_e", self.new_e)?;
        v.visit_component("ae", self.ae)?;
        v.visit_component("packed_w", self.packed_w)?;
        Ok(())
    }
}
pub struct Sha256mix_0__2_Arm1_Super_SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static RetTupleLayout,
}
impl risc0_zkp::layout::Component for Sha256mix_0__2_Arm1_Super_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256mix_0__2_Arm1_Super_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct Sha256mix_0__2__SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static Sha256mix_0__2_Arm1_Super_SuperLayout,
}
impl risc0_zkp::layout::Component for Sha256mix_0__2__SuperLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256mix_0__2__SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct Sha256mix_0__2_Layout {
    pub _super: &'static Sha256mix_0__2__SuperLayout,
    pub new_w: &'static UnpackWithCarryLayout,
    pub new_a: &'static UnpackWithCarryLayout,
    pub new_e: &'static UnpackWithCarryLayout,
    pub ae: &'static ComputeAELayout,
    pub packed_w: &'static ComputeWLayout,
}
impl risc0_zkp::layout::Component for Sha256mix_0__2_Layout {
    fn ty_name(&self) -> &'static str {
        "Sha256mix_0__2_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("new_w", self.new_w)?;
        v.visit_component("new_a", self.new_a)?;
        v.visit_component("new_e", self.new_e)?;
        v.visit_component("ae", self.ae)?;
        v.visit_component("packed_w", self.packed_w)?;
        Ok(())
    }
}
pub struct Sha256mix_0__3_Arm1_Super_SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static RetTupleLayout,
}
impl risc0_zkp::layout::Component for Sha256mix_0__3_Arm1_Super_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256mix_0__3_Arm1_Super_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct Sha256mix_0__3__SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static Sha256mix_0__3_Arm1_Super_SuperLayout,
}
impl risc0_zkp::layout::Component for Sha256mix_0__3__SuperLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256mix_0__3__SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct Sha256mix_0__3_Layout {
    pub _super: &'static Sha256mix_0__3__SuperLayout,
    pub new_w: &'static UnpackWithCarryLayout,
    pub new_a: &'static UnpackWithCarryLayout,
    pub new_e: &'static UnpackWithCarryLayout,
    pub ae: &'static ComputeAELayout,
    pub packed_w: &'static ComputeWLayout,
}
impl risc0_zkp::layout::Component for Sha256mix_0__3_Layout {
    fn ty_name(&self) -> &'static str {
        "Sha256mix_0__3_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("new_w", self.new_w)?;
        v.visit_component("new_a", self.new_a)?;
        v.visit_component("new_e", self.new_e)?;
        v.visit_component("ae", self.ae)?;
        v.visit_component("packed_w", self.packed_w)?;
        Ok(())
    }
}
pub struct Sha256mix_0__4_Arm1_Super_SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static RetTupleLayout,
}
impl risc0_zkp::layout::Component for Sha256mix_0__4_Arm1_Super_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256mix_0__4_Arm1_Super_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct Sha256mix_0__4__SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static Sha256mix_0__4_Arm1_Super_SuperLayout,
}
impl risc0_zkp::layout::Component for Sha256mix_0__4__SuperLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256mix_0__4__SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct Sha256mix_0__4_Layout {
    pub _super: &'static Sha256mix_0__4__SuperLayout,
    pub new_w: &'static UnpackWithCarryLayout,
    pub new_a: &'static UnpackWithCarryLayout,
    pub new_e: &'static UnpackWithCarryLayout,
    pub ae: &'static ComputeAELayout,
    pub packed_w: &'static ComputeWLayout,
}
impl risc0_zkp::layout::Component for Sha256mix_0__4_Layout {
    fn ty_name(&self) -> &'static str {
        "Sha256mix_0__4_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("new_w", self.new_w)?;
        v.visit_component("new_a", self.new_a)?;
        v.visit_component("new_e", self.new_e)?;
        v.visit_component("ae", self.ae)?;
        v.visit_component("packed_w", self.packed_w)?;
        Ok(())
    }
}
pub struct Sha256mix_0__5_Arm1_Super_SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static RetTupleLayout,
}
impl risc0_zkp::layout::Component for Sha256mix_0__5_Arm1_Super_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256mix_0__5_Arm1_Super_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct Sha256mix_0__5__SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static Sha256mix_0__5_Arm1_Super_SuperLayout,
}
impl risc0_zkp::layout::Component for Sha256mix_0__5__SuperLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256mix_0__5__SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct Sha256mix_0__5_Layout {
    pub _super: &'static Sha256mix_0__5__SuperLayout,
    pub new_w: &'static UnpackWithCarryLayout,
    pub new_a: &'static UnpackWithCarryLayout,
    pub new_e: &'static UnpackWithCarryLayout,
    pub ae: &'static ComputeAELayout,
    pub packed_w: &'static ComputeWLayout,
}
impl risc0_zkp::layout::Component for Sha256mix_0__5_Layout {
    fn ty_name(&self) -> &'static str {
        "Sha256mix_0__5_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("new_w", self.new_w)?;
        v.visit_component("new_a", self.new_a)?;
        v.visit_component("new_e", self.new_e)?;
        v.visit_component("ae", self.ae)?;
        v.visit_component("packed_w", self.packed_w)?;
        Ok(())
    }
}
pub struct Sha256mix_0__6_Arm1_Super_SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static RetTupleLayout,
}
impl risc0_zkp::layout::Component for Sha256mix_0__6_Arm1_Super_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256mix_0__6_Arm1_Super_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct Sha256mix_0__6__SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static Sha256mix_0__6_Arm1_Super_SuperLayout,
}
impl risc0_zkp::layout::Component for Sha256mix_0__6__SuperLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256mix_0__6__SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct Sha256mix_0__6_Layout {
    pub _super: &'static Sha256mix_0__6__SuperLayout,
    pub new_w: &'static UnpackWithCarryLayout,
    pub new_a: &'static UnpackWithCarryLayout,
    pub new_e: &'static UnpackWithCarryLayout,
    pub ae: &'static ComputeAELayout,
    pub packed_w: &'static ComputeWLayout,
}
impl risc0_zkp::layout::Component for Sha256mix_0__6_Layout {
    fn ty_name(&self) -> &'static str {
        "Sha256mix_0__6_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("new_w", self.new_w)?;
        v.visit_component("new_a", self.new_a)?;
        v.visit_component("new_e", self.new_e)?;
        v.visit_component("ae", self.ae)?;
        v.visit_component("packed_w", self.packed_w)?;
        Ok(())
    }
}
pub struct Sha256mix_0__7_Arm1_Super_SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static RetTupleLayout,
}
impl risc0_zkp::layout::Component for Sha256mix_0__7_Arm1_Super_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256mix_0__7_Arm1_Super_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct Sha256mix_0__7__SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static Sha256mix_0__7_Arm1_Super_SuperLayout,
}
impl risc0_zkp::layout::Component for Sha256mix_0__7__SuperLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256mix_0__7__SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct Sha256mix_0__7_Layout {
    pub _super: &'static Sha256mix_0__7__SuperLayout,
    pub new_w: &'static UnpackWithCarryLayout,
    pub new_a: &'static UnpackWithCarryLayout,
    pub new_e: &'static UnpackWithCarryLayout,
    pub ae: &'static ComputeAELayout,
    pub packed_w: &'static ComputeWLayout,
}
impl risc0_zkp::layout::Component for Sha256mix_0__7_Layout {
    fn ty_name(&self) -> &'static str {
        "Sha256mix_0__7_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("new_w", self.new_w)?;
        v.visit_component("new_a", self.new_a)?;
        v.visit_component("new_e", self.new_e)?;
        v.visit_component("ae", self.ae)?;
        v.visit_component("packed_w", self.packed_w)?;
        Ok(())
    }
}
pub struct Sha256mix_0__8_Arm1_Super_SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static RetTupleLayout,
}
impl risc0_zkp::layout::Component for Sha256mix_0__8_Arm1_Super_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256mix_0__8_Arm1_Super_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct Sha256mix_0__8__SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static Sha256mix_0__8_Arm1_Super_SuperLayout,
}
impl risc0_zkp::layout::Component for Sha256mix_0__8__SuperLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256mix_0__8__SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct Sha256mix_0__8_Layout {
    pub _super: &'static Sha256mix_0__8__SuperLayout,
    pub new_w: &'static UnpackWithCarryLayout,
    pub new_a: &'static UnpackWithCarryLayout,
    pub new_e: &'static UnpackWithCarryLayout,
    pub ae: &'static ComputeAELayout,
    pub packed_w: &'static ComputeWLayout,
}
impl risc0_zkp::layout::Component for Sha256mix_0__8_Layout {
    fn ty_name(&self) -> &'static str {
        "Sha256mix_0__8_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("new_w", self.new_w)?;
        v.visit_component("new_a", self.new_a)?;
        v.visit_component("new_e", self.new_e)?;
        v.visit_component("ae", self.ae)?;
        v.visit_component("packed_w", self.packed_w)?;
        Ok(())
    }
}
pub struct Sha256mix_0__9_Arm1_Super_SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static RetTupleLayout,
}
impl risc0_zkp::layout::Component for Sha256mix_0__9_Arm1_Super_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256mix_0__9_Arm1_Super_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct Sha256mix_0__9__SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static Sha256mix_0__9_Arm1_Super_SuperLayout,
}
impl risc0_zkp::layout::Component for Sha256mix_0__9__SuperLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256mix_0__9__SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct Sha256mix_0__9_Layout {
    pub _super: &'static Sha256mix_0__9__SuperLayout,
    pub new_w: &'static UnpackWithCarryLayout,
    pub new_a: &'static UnpackWithCarryLayout,
    pub new_e: &'static UnpackWithCarryLayout,
    pub ae: &'static ComputeAELayout,
    pub packed_w: &'static ComputeWLayout,
}
impl risc0_zkp::layout::Component for Sha256mix_0__9_Layout {
    fn ty_name(&self) -> &'static str {
        "Sha256mix_0__9_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("new_w", self.new_w)?;
        v.visit_component("new_a", self.new_a)?;
        v.visit_component("new_e", self.new_e)?;
        v.visit_component("ae", self.ae)?;
        v.visit_component("packed_w", self.packed_w)?;
        Ok(())
    }
}
pub struct Sha256mix_0__10_Arm1_Super_SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static RetTupleLayout,
}
impl risc0_zkp::layout::Component for Sha256mix_0__10_Arm1_Super_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256mix_0__10_Arm1_Super_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct Sha256mix_0__10__SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static Sha256mix_0__10_Arm1_Super_SuperLayout,
}
impl risc0_zkp::layout::Component for Sha256mix_0__10__SuperLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256mix_0__10__SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct Sha256mix_0__10_Layout {
    pub _super: &'static Sha256mix_0__10__SuperLayout,
    pub new_w: &'static UnpackWithCarryLayout,
    pub new_a: &'static UnpackWithCarryLayout,
    pub new_e: &'static UnpackWithCarryLayout,
    pub ae: &'static ComputeAELayout,
    pub packed_w: &'static ComputeWLayout,
}
impl risc0_zkp::layout::Component for Sha256mix_0__10_Layout {
    fn ty_name(&self) -> &'static str {
        "Sha256mix_0__10_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("new_w", self.new_w)?;
        v.visit_component("new_a", self.new_a)?;
        v.visit_component("new_e", self.new_e)?;
        v.visit_component("ae", self.ae)?;
        v.visit_component("packed_w", self.packed_w)?;
        Ok(())
    }
}
pub struct Sha256mix_0__11_Arm1_Super_SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static RetTupleLayout,
}
impl risc0_zkp::layout::Component for Sha256mix_0__11_Arm1_Super_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256mix_0__11_Arm1_Super_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct Sha256mix_0__11__SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static Sha256mix_0__11_Arm1_Super_SuperLayout,
}
impl risc0_zkp::layout::Component for Sha256mix_0__11__SuperLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256mix_0__11__SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct Sha256mix_0__11_Layout {
    pub _super: &'static Sha256mix_0__11__SuperLayout,
    pub new_w: &'static UnpackWithCarryLayout,
    pub new_a: &'static UnpackWithCarryLayout,
    pub new_e: &'static UnpackWithCarryLayout,
    pub ae: &'static ComputeAELayout,
    pub packed_w: &'static ComputeWLayout,
}
impl risc0_zkp::layout::Component for Sha256mix_0__11_Layout {
    fn ty_name(&self) -> &'static str {
        "Sha256mix_0__11_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("new_w", self.new_w)?;
        v.visit_component("new_a", self.new_a)?;
        v.visit_component("new_e", self.new_e)?;
        v.visit_component("ae", self.ae)?;
        v.visit_component("packed_w", self.packed_w)?;
        Ok(())
    }
}
pub struct Sha256mix_0__12_Arm1_Super_SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static RetTupleLayout,
}
impl risc0_zkp::layout::Component for Sha256mix_0__12_Arm1_Super_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256mix_0__12_Arm1_Super_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct Sha256mix_0__12__SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static Sha256mix_0__12_Arm1_Super_SuperLayout,
}
impl risc0_zkp::layout::Component for Sha256mix_0__12__SuperLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256mix_0__12__SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct Sha256mix_0__12_Layout {
    pub _super: &'static Sha256mix_0__12__SuperLayout,
    pub new_w: &'static UnpackWithCarryLayout,
    pub new_a: &'static UnpackWithCarryLayout,
    pub new_e: &'static UnpackWithCarryLayout,
    pub ae: &'static ComputeAELayout,
    pub packed_w: &'static ComputeWLayout,
}
impl risc0_zkp::layout::Component for Sha256mix_0__12_Layout {
    fn ty_name(&self) -> &'static str {
        "Sha256mix_0__12_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("new_w", self.new_w)?;
        v.visit_component("new_a", self.new_a)?;
        v.visit_component("new_e", self.new_e)?;
        v.visit_component("ae", self.ae)?;
        v.visit_component("packed_w", self.packed_w)?;
        Ok(())
    }
}
pub struct Sha256mix_0__13_Arm1_Super_SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static RetTupleLayout,
}
impl risc0_zkp::layout::Component for Sha256mix_0__13_Arm1_Super_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256mix_0__13_Arm1_Super_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct Sha256mix_0__13__SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static Sha256mix_0__13_Arm1_Super_SuperLayout,
}
impl risc0_zkp::layout::Component for Sha256mix_0__13__SuperLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256mix_0__13__SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct Sha256mix_0__13_Layout {
    pub _super: &'static Sha256mix_0__13__SuperLayout,
    pub new_w: &'static UnpackWithCarryLayout,
    pub new_a: &'static UnpackWithCarryLayout,
    pub new_e: &'static UnpackWithCarryLayout,
    pub ae: &'static ComputeAELayout,
    pub packed_w: &'static ComputeWLayout,
}
impl risc0_zkp::layout::Component for Sha256mix_0__13_Layout {
    fn ty_name(&self) -> &'static str {
        "Sha256mix_0__13_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("new_w", self.new_w)?;
        v.visit_component("new_a", self.new_a)?;
        v.visit_component("new_e", self.new_e)?;
        v.visit_component("ae", self.ae)?;
        v.visit_component("packed_w", self.packed_w)?;
        Ok(())
    }
}
pub struct Sha256mix_0__14_Arm1_Super_SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static RetTupleLayout,
}
impl risc0_zkp::layout::Component for Sha256mix_0__14_Arm1_Super_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256mix_0__14_Arm1_Super_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct Sha256mix_0__14__SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static Sha256mix_0__14_Arm1_Super_SuperLayout,
}
impl risc0_zkp::layout::Component for Sha256mix_0__14__SuperLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256mix_0__14__SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct Sha256mix_0__14_Layout {
    pub _super: &'static Sha256mix_0__14__SuperLayout,
    pub new_w: &'static UnpackWithCarryLayout,
    pub new_a: &'static UnpackWithCarryLayout,
    pub new_e: &'static UnpackWithCarryLayout,
    pub ae: &'static ComputeAELayout,
    pub packed_w: &'static ComputeWLayout,
}
impl risc0_zkp::layout::Component for Sha256mix_0__14_Layout {
    fn ty_name(&self) -> &'static str {
        "Sha256mix_0__14_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("new_w", self.new_w)?;
        v.visit_component("new_a", self.new_a)?;
        v.visit_component("new_e", self.new_e)?;
        v.visit_component("ae", self.ae)?;
        v.visit_component("packed_w", self.packed_w)?;
        Ok(())
    }
}
pub struct Sha256mix_0__15_Arm1_Super_SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static RetTupleLayout,
}
impl risc0_zkp::layout::Component for Sha256mix_0__15_Arm1_Super_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256mix_0__15_Arm1_Super_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct Sha256mix_0__15__SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static Sha256mix_0__15_Arm1_Super_SuperLayout,
}
impl risc0_zkp::layout::Component for Sha256mix_0__15__SuperLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256mix_0__15__SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct Sha256mix_0__15_Layout {
    pub _super: &'static Sha256mix_0__15__SuperLayout,
    pub new_w: &'static UnpackWithCarryLayout,
    pub new_a: &'static UnpackWithCarryLayout,
    pub new_e: &'static UnpackWithCarryLayout,
    pub ae: &'static ComputeAELayout,
    pub packed_w: &'static ComputeWLayout,
}
impl risc0_zkp::layout::Component for Sha256mix_0__15_Layout {
    fn ty_name(&self) -> &'static str {
        "Sha256mix_0__15_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("new_w", self.new_w)?;
        v.visit_component("new_a", self.new_a)?;
        v.visit_component("new_e", self.new_e)?;
        v.visit_component("ae", self.ae)?;
        v.visit_component("packed_w", self.packed_w)?;
        Ok(())
    }
}
pub struct Sha256mixAll_0__SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static Sha256mix_0__0_Layout,
    pub arm1: &'static Sha256mix_0__1_Layout,
    pub arm2: &'static Sha256mix_0__2_Layout,
    pub arm3: &'static Sha256mix_0__3_Layout,
    pub arm4: &'static Sha256mix_0__4_Layout,
    pub arm5: &'static Sha256mix_0__5_Layout,
    pub arm6: &'static Sha256mix_0__6_Layout,
    pub arm7: &'static Sha256mix_0__7_Layout,
    pub arm8: &'static Sha256mix_0__8_Layout,
    pub arm9: &'static Sha256mix_0__9_Layout,
    pub arm10: &'static Sha256mix_0__10_Layout,
    pub arm11: &'static Sha256mix_0__11_Layout,
    pub arm12: &'static Sha256mix_0__12_Layout,
    pub arm13: &'static Sha256mix_0__13_Layout,
    pub arm14: &'static Sha256mix_0__14_Layout,
    pub arm15: &'static Sha256mix_0__15_Layout,
}
impl risc0_zkp::layout::Component for Sha256mixAll_0__SuperLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256mixAll_0__SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        v.visit_component("arm2", self.arm2)?;
        v.visit_component("arm3", self.arm3)?;
        v.visit_component("arm4", self.arm4)?;
        v.visit_component("arm5", self.arm5)?;
        v.visit_component("arm6", self.arm6)?;
        v.visit_component("arm7", self.arm7)?;
        v.visit_component("arm8", self.arm8)?;
        v.visit_component("arm9", self.arm9)?;
        v.visit_component("arm10", self.arm10)?;
        v.visit_component("arm11", self.arm11)?;
        v.visit_component("arm12", self.arm12)?;
        v.visit_component("arm13", self.arm13)?;
        v.visit_component("arm14", self.arm14)?;
        v.visit_component("arm15", self.arm15)?;
        Ok(())
    }
}
pub struct Sha256mixAll_0_Layout {
    pub _super: &'static Sha256mixAll_0__SuperLayout,
    pub minor_onehot: &'static OneHot_16_Layout,
}
impl risc0_zkp::layout::Component for Sha256mixAll_0_Layout {
    fn ty_name(&self) -> &'static str {
        "Sha256mixAll_0_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("minor_onehot", self.minor_onehot)?;
        Ok(())
    }
}
pub struct Sha256mix_1__0_Arm1_Super_SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static RetTupleLayout,
}
impl risc0_zkp::layout::Component for Sha256mix_1__0_Arm1_Super_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256mix_1__0_Arm1_Super_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct Sha256mix_1__0__SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static Sha256mix_1__0_Arm1_Super_SuperLayout,
}
impl risc0_zkp::layout::Component for Sha256mix_1__0__SuperLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256mix_1__0__SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct Sha256mix_1__0_Layout {
    pub _super: &'static Sha256mix_1__0__SuperLayout,
    pub new_w: &'static UnpackWithCarryLayout,
    pub new_a: &'static UnpackWithCarryLayout,
    pub new_e: &'static UnpackWithCarryLayout,
    pub ae: &'static ComputeAELayout,
    pub packed_w: &'static ComputeWLayout,
}
impl risc0_zkp::layout::Component for Sha256mix_1__0_Layout {
    fn ty_name(&self) -> &'static str {
        "Sha256mix_1__0_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("new_w", self.new_w)?;
        v.visit_component("new_a", self.new_a)?;
        v.visit_component("new_e", self.new_e)?;
        v.visit_component("ae", self.ae)?;
        v.visit_component("packed_w", self.packed_w)?;
        Ok(())
    }
}
pub struct Sha256mix_1__1_Arm1_Super_SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static RetTupleLayout,
}
impl risc0_zkp::layout::Component for Sha256mix_1__1_Arm1_Super_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256mix_1__1_Arm1_Super_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct Sha256mix_1__1__SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static Sha256mix_1__1_Arm1_Super_SuperLayout,
}
impl risc0_zkp::layout::Component for Sha256mix_1__1__SuperLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256mix_1__1__SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct Sha256mix_1__1_Layout {
    pub _super: &'static Sha256mix_1__1__SuperLayout,
    pub new_w: &'static UnpackWithCarryLayout,
    pub new_a: &'static UnpackWithCarryLayout,
    pub new_e: &'static UnpackWithCarryLayout,
    pub ae: &'static ComputeAELayout,
    pub packed_w: &'static ComputeWLayout,
}
impl risc0_zkp::layout::Component for Sha256mix_1__1_Layout {
    fn ty_name(&self) -> &'static str {
        "Sha256mix_1__1_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("new_w", self.new_w)?;
        v.visit_component("new_a", self.new_a)?;
        v.visit_component("new_e", self.new_e)?;
        v.visit_component("ae", self.ae)?;
        v.visit_component("packed_w", self.packed_w)?;
        Ok(())
    }
}
pub struct Sha256mix_1__2_Arm1_Super_SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static RetTupleLayout,
}
impl risc0_zkp::layout::Component for Sha256mix_1__2_Arm1_Super_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256mix_1__2_Arm1_Super_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct Sha256mix_1__2__SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static Sha256mix_1__2_Arm1_Super_SuperLayout,
}
impl risc0_zkp::layout::Component for Sha256mix_1__2__SuperLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256mix_1__2__SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct Sha256mix_1__2_Layout {
    pub _super: &'static Sha256mix_1__2__SuperLayout,
    pub new_w: &'static UnpackWithCarryLayout,
    pub new_a: &'static UnpackWithCarryLayout,
    pub new_e: &'static UnpackWithCarryLayout,
    pub ae: &'static ComputeAELayout,
    pub packed_w: &'static ComputeWLayout,
}
impl risc0_zkp::layout::Component for Sha256mix_1__2_Layout {
    fn ty_name(&self) -> &'static str {
        "Sha256mix_1__2_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("new_w", self.new_w)?;
        v.visit_component("new_a", self.new_a)?;
        v.visit_component("new_e", self.new_e)?;
        v.visit_component("ae", self.ae)?;
        v.visit_component("packed_w", self.packed_w)?;
        Ok(())
    }
}
pub struct Sha256mix_1__3_Arm1_Super_SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static RetTupleLayout,
}
impl risc0_zkp::layout::Component for Sha256mix_1__3_Arm1_Super_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256mix_1__3_Arm1_Super_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct Sha256mix_1__3__SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static Sha256mix_1__3_Arm1_Super_SuperLayout,
}
impl risc0_zkp::layout::Component for Sha256mix_1__3__SuperLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256mix_1__3__SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct Sha256mix_1__3_Layout {
    pub _super: &'static Sha256mix_1__3__SuperLayout,
    pub new_w: &'static UnpackWithCarryLayout,
    pub new_a: &'static UnpackWithCarryLayout,
    pub new_e: &'static UnpackWithCarryLayout,
    pub ae: &'static ComputeAELayout,
    pub packed_w: &'static ComputeWLayout,
}
impl risc0_zkp::layout::Component for Sha256mix_1__3_Layout {
    fn ty_name(&self) -> &'static str {
        "Sha256mix_1__3_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("new_w", self.new_w)?;
        v.visit_component("new_a", self.new_a)?;
        v.visit_component("new_e", self.new_e)?;
        v.visit_component("ae", self.ae)?;
        v.visit_component("packed_w", self.packed_w)?;
        Ok(())
    }
}
pub struct Sha256mix_1__4_Arm1_Super_SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static RetTupleLayout,
}
impl risc0_zkp::layout::Component for Sha256mix_1__4_Arm1_Super_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256mix_1__4_Arm1_Super_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct Sha256mix_1__4__SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static Sha256mix_1__4_Arm1_Super_SuperLayout,
}
impl risc0_zkp::layout::Component for Sha256mix_1__4__SuperLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256mix_1__4__SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct Sha256mix_1__4_Layout {
    pub _super: &'static Sha256mix_1__4__SuperLayout,
    pub new_w: &'static UnpackWithCarryLayout,
    pub new_a: &'static UnpackWithCarryLayout,
    pub new_e: &'static UnpackWithCarryLayout,
    pub ae: &'static ComputeAELayout,
    pub packed_w: &'static ComputeWLayout,
}
impl risc0_zkp::layout::Component for Sha256mix_1__4_Layout {
    fn ty_name(&self) -> &'static str {
        "Sha256mix_1__4_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("new_w", self.new_w)?;
        v.visit_component("new_a", self.new_a)?;
        v.visit_component("new_e", self.new_e)?;
        v.visit_component("ae", self.ae)?;
        v.visit_component("packed_w", self.packed_w)?;
        Ok(())
    }
}
pub struct Sha256mix_1__5_Arm1_Super_SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static RetTupleLayout,
}
impl risc0_zkp::layout::Component for Sha256mix_1__5_Arm1_Super_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256mix_1__5_Arm1_Super_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct Sha256mix_1__5__SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static Sha256mix_1__5_Arm1_Super_SuperLayout,
}
impl risc0_zkp::layout::Component for Sha256mix_1__5__SuperLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256mix_1__5__SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct Sha256mix_1__5_Layout {
    pub _super: &'static Sha256mix_1__5__SuperLayout,
    pub new_w: &'static UnpackWithCarryLayout,
    pub new_a: &'static UnpackWithCarryLayout,
    pub new_e: &'static UnpackWithCarryLayout,
    pub ae: &'static ComputeAELayout,
    pub packed_w: &'static ComputeWLayout,
}
impl risc0_zkp::layout::Component for Sha256mix_1__5_Layout {
    fn ty_name(&self) -> &'static str {
        "Sha256mix_1__5_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("new_w", self.new_w)?;
        v.visit_component("new_a", self.new_a)?;
        v.visit_component("new_e", self.new_e)?;
        v.visit_component("ae", self.ae)?;
        v.visit_component("packed_w", self.packed_w)?;
        Ok(())
    }
}
pub struct Sha256mix_1__6_Arm1_Super_SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static RetTupleLayout,
}
impl risc0_zkp::layout::Component for Sha256mix_1__6_Arm1_Super_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256mix_1__6_Arm1_Super_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct Sha256mix_1__6__SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static Sha256mix_1__6_Arm1_Super_SuperLayout,
}
impl risc0_zkp::layout::Component for Sha256mix_1__6__SuperLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256mix_1__6__SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct Sha256mix_1__6_Layout {
    pub _super: &'static Sha256mix_1__6__SuperLayout,
    pub new_w: &'static UnpackWithCarryLayout,
    pub new_a: &'static UnpackWithCarryLayout,
    pub new_e: &'static UnpackWithCarryLayout,
    pub ae: &'static ComputeAELayout,
    pub packed_w: &'static ComputeWLayout,
}
impl risc0_zkp::layout::Component for Sha256mix_1__6_Layout {
    fn ty_name(&self) -> &'static str {
        "Sha256mix_1__6_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("new_w", self.new_w)?;
        v.visit_component("new_a", self.new_a)?;
        v.visit_component("new_e", self.new_e)?;
        v.visit_component("ae", self.ae)?;
        v.visit_component("packed_w", self.packed_w)?;
        Ok(())
    }
}
pub struct Sha256mix_1__7_Arm1_Super_SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static RetTupleLayout,
}
impl risc0_zkp::layout::Component for Sha256mix_1__7_Arm1_Super_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256mix_1__7_Arm1_Super_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct Sha256mix_1__7__SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static Sha256mix_1__7_Arm1_Super_SuperLayout,
}
impl risc0_zkp::layout::Component for Sha256mix_1__7__SuperLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256mix_1__7__SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct Sha256mix_1__7_Layout {
    pub _super: &'static Sha256mix_1__7__SuperLayout,
    pub new_w: &'static UnpackWithCarryLayout,
    pub new_a: &'static UnpackWithCarryLayout,
    pub new_e: &'static UnpackWithCarryLayout,
    pub ae: &'static ComputeAELayout,
    pub packed_w: &'static ComputeWLayout,
}
impl risc0_zkp::layout::Component for Sha256mix_1__7_Layout {
    fn ty_name(&self) -> &'static str {
        "Sha256mix_1__7_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("new_w", self.new_w)?;
        v.visit_component("new_a", self.new_a)?;
        v.visit_component("new_e", self.new_e)?;
        v.visit_component("ae", self.ae)?;
        v.visit_component("packed_w", self.packed_w)?;
        Ok(())
    }
}
pub struct Sha256mix_1__8_Arm1_Super_SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static RetTupleLayout,
}
impl risc0_zkp::layout::Component for Sha256mix_1__8_Arm1_Super_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256mix_1__8_Arm1_Super_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct Sha256mix_1__8__SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static Sha256mix_1__8_Arm1_Super_SuperLayout,
}
impl risc0_zkp::layout::Component for Sha256mix_1__8__SuperLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256mix_1__8__SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct Sha256mix_1__8_Layout {
    pub _super: &'static Sha256mix_1__8__SuperLayout,
    pub new_w: &'static UnpackWithCarryLayout,
    pub new_a: &'static UnpackWithCarryLayout,
    pub new_e: &'static UnpackWithCarryLayout,
    pub ae: &'static ComputeAELayout,
    pub packed_w: &'static ComputeWLayout,
}
impl risc0_zkp::layout::Component for Sha256mix_1__8_Layout {
    fn ty_name(&self) -> &'static str {
        "Sha256mix_1__8_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("new_w", self.new_w)?;
        v.visit_component("new_a", self.new_a)?;
        v.visit_component("new_e", self.new_e)?;
        v.visit_component("ae", self.ae)?;
        v.visit_component("packed_w", self.packed_w)?;
        Ok(())
    }
}
pub struct Sha256mix_1__9_Arm1_Super_SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static RetTupleLayout,
}
impl risc0_zkp::layout::Component for Sha256mix_1__9_Arm1_Super_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256mix_1__9_Arm1_Super_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct Sha256mix_1__9__SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static Sha256mix_1__9_Arm1_Super_SuperLayout,
}
impl risc0_zkp::layout::Component for Sha256mix_1__9__SuperLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256mix_1__9__SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct Sha256mix_1__9_Layout {
    pub _super: &'static Sha256mix_1__9__SuperLayout,
    pub new_w: &'static UnpackWithCarryLayout,
    pub new_a: &'static UnpackWithCarryLayout,
    pub new_e: &'static UnpackWithCarryLayout,
    pub ae: &'static ComputeAELayout,
    pub packed_w: &'static ComputeWLayout,
}
impl risc0_zkp::layout::Component for Sha256mix_1__9_Layout {
    fn ty_name(&self) -> &'static str {
        "Sha256mix_1__9_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("new_w", self.new_w)?;
        v.visit_component("new_a", self.new_a)?;
        v.visit_component("new_e", self.new_e)?;
        v.visit_component("ae", self.ae)?;
        v.visit_component("packed_w", self.packed_w)?;
        Ok(())
    }
}
pub struct Sha256mix_1__10_Arm1_Super_SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static RetTupleLayout,
}
impl risc0_zkp::layout::Component for Sha256mix_1__10_Arm1_Super_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256mix_1__10_Arm1_Super_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct Sha256mix_1__10__SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static Sha256mix_1__10_Arm1_Super_SuperLayout,
}
impl risc0_zkp::layout::Component for Sha256mix_1__10__SuperLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256mix_1__10__SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct Sha256mix_1__10_Layout {
    pub _super: &'static Sha256mix_1__10__SuperLayout,
    pub new_w: &'static UnpackWithCarryLayout,
    pub new_a: &'static UnpackWithCarryLayout,
    pub new_e: &'static UnpackWithCarryLayout,
    pub ae: &'static ComputeAELayout,
    pub packed_w: &'static ComputeWLayout,
}
impl risc0_zkp::layout::Component for Sha256mix_1__10_Layout {
    fn ty_name(&self) -> &'static str {
        "Sha256mix_1__10_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("new_w", self.new_w)?;
        v.visit_component("new_a", self.new_a)?;
        v.visit_component("new_e", self.new_e)?;
        v.visit_component("ae", self.ae)?;
        v.visit_component("packed_w", self.packed_w)?;
        Ok(())
    }
}
pub struct Sha256mix_1__11_Arm1_Super_SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static RetTupleLayout,
}
impl risc0_zkp::layout::Component for Sha256mix_1__11_Arm1_Super_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256mix_1__11_Arm1_Super_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct Sha256mix_1__11__SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static Sha256mix_1__11_Arm1_Super_SuperLayout,
}
impl risc0_zkp::layout::Component for Sha256mix_1__11__SuperLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256mix_1__11__SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct Sha256mix_1__11_Layout {
    pub _super: &'static Sha256mix_1__11__SuperLayout,
    pub new_w: &'static UnpackWithCarryLayout,
    pub new_a: &'static UnpackWithCarryLayout,
    pub new_e: &'static UnpackWithCarryLayout,
    pub ae: &'static ComputeAELayout,
    pub packed_w: &'static ComputeWLayout,
}
impl risc0_zkp::layout::Component for Sha256mix_1__11_Layout {
    fn ty_name(&self) -> &'static str {
        "Sha256mix_1__11_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("new_w", self.new_w)?;
        v.visit_component("new_a", self.new_a)?;
        v.visit_component("new_e", self.new_e)?;
        v.visit_component("ae", self.ae)?;
        v.visit_component("packed_w", self.packed_w)?;
        Ok(())
    }
}
pub struct Sha256mix_1__12_Arm1_Super_SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static RetTupleLayout,
}
impl risc0_zkp::layout::Component for Sha256mix_1__12_Arm1_Super_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256mix_1__12_Arm1_Super_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct Sha256mix_1__12__SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static Sha256mix_1__12_Arm1_Super_SuperLayout,
}
impl risc0_zkp::layout::Component for Sha256mix_1__12__SuperLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256mix_1__12__SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct Sha256mix_1__12_Layout {
    pub _super: &'static Sha256mix_1__12__SuperLayout,
    pub new_w: &'static UnpackWithCarryLayout,
    pub new_a: &'static UnpackWithCarryLayout,
    pub new_e: &'static UnpackWithCarryLayout,
    pub ae: &'static ComputeAELayout,
    pub packed_w: &'static ComputeWLayout,
}
impl risc0_zkp::layout::Component for Sha256mix_1__12_Layout {
    fn ty_name(&self) -> &'static str {
        "Sha256mix_1__12_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("new_w", self.new_w)?;
        v.visit_component("new_a", self.new_a)?;
        v.visit_component("new_e", self.new_e)?;
        v.visit_component("ae", self.ae)?;
        v.visit_component("packed_w", self.packed_w)?;
        Ok(())
    }
}
pub struct Sha256mix_1__13_Arm1_Super_SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static RetTupleLayout,
}
impl risc0_zkp::layout::Component for Sha256mix_1__13_Arm1_Super_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256mix_1__13_Arm1_Super_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct Sha256mix_1__13__SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static Sha256mix_1__13_Arm1_Super_SuperLayout,
}
impl risc0_zkp::layout::Component for Sha256mix_1__13__SuperLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256mix_1__13__SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct Sha256mix_1__13_Layout {
    pub _super: &'static Sha256mix_1__13__SuperLayout,
    pub new_w: &'static UnpackWithCarryLayout,
    pub new_a: &'static UnpackWithCarryLayout,
    pub new_e: &'static UnpackWithCarryLayout,
    pub ae: &'static ComputeAELayout,
    pub packed_w: &'static ComputeWLayout,
}
impl risc0_zkp::layout::Component for Sha256mix_1__13_Layout {
    fn ty_name(&self) -> &'static str {
        "Sha256mix_1__13_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("new_w", self.new_w)?;
        v.visit_component("new_a", self.new_a)?;
        v.visit_component("new_e", self.new_e)?;
        v.visit_component("ae", self.ae)?;
        v.visit_component("packed_w", self.packed_w)?;
        Ok(())
    }
}
pub struct Sha256mix_1__14_Arm1_Super_SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static RetTupleLayout,
}
impl risc0_zkp::layout::Component for Sha256mix_1__14_Arm1_Super_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256mix_1__14_Arm1_Super_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct Sha256mix_1__14__SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static Sha256mix_1__14_Arm1_Super_SuperLayout,
}
impl risc0_zkp::layout::Component for Sha256mix_1__14__SuperLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256mix_1__14__SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct Sha256mix_1__14_Layout {
    pub _super: &'static Sha256mix_1__14__SuperLayout,
    pub new_w: &'static UnpackWithCarryLayout,
    pub new_a: &'static UnpackWithCarryLayout,
    pub new_e: &'static UnpackWithCarryLayout,
    pub ae: &'static ComputeAELayout,
    pub packed_w: &'static ComputeWLayout,
}
impl risc0_zkp::layout::Component for Sha256mix_1__14_Layout {
    fn ty_name(&self) -> &'static str {
        "Sha256mix_1__14_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("new_w", self.new_w)?;
        v.visit_component("new_a", self.new_a)?;
        v.visit_component("new_e", self.new_e)?;
        v.visit_component("ae", self.ae)?;
        v.visit_component("packed_w", self.packed_w)?;
        Ok(())
    }
}
pub struct Sha256mix_1__15_Arm1_Super_SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static RetTupleLayout,
}
impl risc0_zkp::layout::Component for Sha256mix_1__15_Arm1_Super_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256mix_1__15_Arm1_Super_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct Sha256mix_1__15__SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static Sha256mix_1__15_Arm1_Super_SuperLayout,
}
impl risc0_zkp::layout::Component for Sha256mix_1__15__SuperLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256mix_1__15__SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct Sha256mix_1__15_Layout {
    pub _super: &'static Sha256mix_1__15__SuperLayout,
    pub new_w: &'static UnpackWithCarryLayout,
    pub new_a: &'static UnpackWithCarryLayout,
    pub new_e: &'static UnpackWithCarryLayout,
    pub ae: &'static ComputeAELayout,
    pub packed_w: &'static ComputeWLayout,
}
impl risc0_zkp::layout::Component for Sha256mix_1__15_Layout {
    fn ty_name(&self) -> &'static str {
        "Sha256mix_1__15_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("new_w", self.new_w)?;
        v.visit_component("new_a", self.new_a)?;
        v.visit_component("new_e", self.new_e)?;
        v.visit_component("ae", self.ae)?;
        v.visit_component("packed_w", self.packed_w)?;
        Ok(())
    }
}
pub struct Sha256mixAll_1__SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static Sha256mix_1__0_Layout,
    pub arm1: &'static Sha256mix_1__1_Layout,
    pub arm2: &'static Sha256mix_1__2_Layout,
    pub arm3: &'static Sha256mix_1__3_Layout,
    pub arm4: &'static Sha256mix_1__4_Layout,
    pub arm5: &'static Sha256mix_1__5_Layout,
    pub arm6: &'static Sha256mix_1__6_Layout,
    pub arm7: &'static Sha256mix_1__7_Layout,
    pub arm8: &'static Sha256mix_1__8_Layout,
    pub arm9: &'static Sha256mix_1__9_Layout,
    pub arm10: &'static Sha256mix_1__10_Layout,
    pub arm11: &'static Sha256mix_1__11_Layout,
    pub arm12: &'static Sha256mix_1__12_Layout,
    pub arm13: &'static Sha256mix_1__13_Layout,
    pub arm14: &'static Sha256mix_1__14_Layout,
    pub arm15: &'static Sha256mix_1__15_Layout,
}
impl risc0_zkp::layout::Component for Sha256mixAll_1__SuperLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256mixAll_1__SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        v.visit_component("arm2", self.arm2)?;
        v.visit_component("arm3", self.arm3)?;
        v.visit_component("arm4", self.arm4)?;
        v.visit_component("arm5", self.arm5)?;
        v.visit_component("arm6", self.arm6)?;
        v.visit_component("arm7", self.arm7)?;
        v.visit_component("arm8", self.arm8)?;
        v.visit_component("arm9", self.arm9)?;
        v.visit_component("arm10", self.arm10)?;
        v.visit_component("arm11", self.arm11)?;
        v.visit_component("arm12", self.arm12)?;
        v.visit_component("arm13", self.arm13)?;
        v.visit_component("arm14", self.arm14)?;
        v.visit_component("arm15", self.arm15)?;
        Ok(())
    }
}
pub struct Sha256mixAll_1_Layout {
    pub _super: &'static Sha256mixAll_1__SuperLayout,
    pub minor_onehot: &'static OneHot_16_Layout,
}
impl risc0_zkp::layout::Component for Sha256mixAll_1_Layout {
    fn ty_name(&self) -> &'static str {
        "Sha256mixAll_1_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("minor_onehot", self.minor_onehot)?;
        Ok(())
    }
}
pub struct Sha256mix_2__0_Arm1_Super_SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static RetTupleLayout,
}
impl risc0_zkp::layout::Component for Sha256mix_2__0_Arm1_Super_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256mix_2__0_Arm1_Super_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct Sha256mix_2__0__SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static Sha256mix_2__0_Arm1_Super_SuperLayout,
}
impl risc0_zkp::layout::Component for Sha256mix_2__0__SuperLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256mix_2__0__SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct Sha256mix_2__0_Layout {
    pub _super: &'static Sha256mix_2__0__SuperLayout,
    pub new_w: &'static UnpackWithCarryLayout,
    pub new_a: &'static UnpackWithCarryLayout,
    pub new_e: &'static UnpackWithCarryLayout,
    pub ae: &'static ComputeAELayout,
    pub packed_w: &'static ComputeWLayout,
}
impl risc0_zkp::layout::Component for Sha256mix_2__0_Layout {
    fn ty_name(&self) -> &'static str {
        "Sha256mix_2__0_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("new_w", self.new_w)?;
        v.visit_component("new_a", self.new_a)?;
        v.visit_component("new_e", self.new_e)?;
        v.visit_component("ae", self.ae)?;
        v.visit_component("packed_w", self.packed_w)?;
        Ok(())
    }
}
pub struct Sha256mix_2__1_Arm1_Super_SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static RetTupleLayout,
}
impl risc0_zkp::layout::Component for Sha256mix_2__1_Arm1_Super_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256mix_2__1_Arm1_Super_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct Sha256mix_2__1__SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static Sha256mix_2__1_Arm1_Super_SuperLayout,
}
impl risc0_zkp::layout::Component for Sha256mix_2__1__SuperLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256mix_2__1__SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct Sha256mix_2__1_Layout {
    pub _super: &'static Sha256mix_2__1__SuperLayout,
    pub new_w: &'static UnpackWithCarryLayout,
    pub new_a: &'static UnpackWithCarryLayout,
    pub new_e: &'static UnpackWithCarryLayout,
    pub ae: &'static ComputeAELayout,
    pub packed_w: &'static ComputeWLayout,
}
impl risc0_zkp::layout::Component for Sha256mix_2__1_Layout {
    fn ty_name(&self) -> &'static str {
        "Sha256mix_2__1_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("new_w", self.new_w)?;
        v.visit_component("new_a", self.new_a)?;
        v.visit_component("new_e", self.new_e)?;
        v.visit_component("ae", self.ae)?;
        v.visit_component("packed_w", self.packed_w)?;
        Ok(())
    }
}
pub struct Sha256mix_2__2_Arm1_Super_SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static RetTupleLayout,
}
impl risc0_zkp::layout::Component for Sha256mix_2__2_Arm1_Super_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256mix_2__2_Arm1_Super_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct Sha256mix_2__2__SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static Sha256mix_2__2_Arm1_Super_SuperLayout,
}
impl risc0_zkp::layout::Component for Sha256mix_2__2__SuperLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256mix_2__2__SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct Sha256mix_2__2_Layout {
    pub _super: &'static Sha256mix_2__2__SuperLayout,
    pub new_w: &'static UnpackWithCarryLayout,
    pub new_a: &'static UnpackWithCarryLayout,
    pub new_e: &'static UnpackWithCarryLayout,
    pub ae: &'static ComputeAELayout,
    pub packed_w: &'static ComputeWLayout,
}
impl risc0_zkp::layout::Component for Sha256mix_2__2_Layout {
    fn ty_name(&self) -> &'static str {
        "Sha256mix_2__2_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("new_w", self.new_w)?;
        v.visit_component("new_a", self.new_a)?;
        v.visit_component("new_e", self.new_e)?;
        v.visit_component("ae", self.ae)?;
        v.visit_component("packed_w", self.packed_w)?;
        Ok(())
    }
}
pub struct Sha256mix_2__3_Arm1_Super_SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static RetTupleLayout,
}
impl risc0_zkp::layout::Component for Sha256mix_2__3_Arm1_Super_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256mix_2__3_Arm1_Super_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct Sha256mix_2__3__SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static Sha256mix_2__3_Arm1_Super_SuperLayout,
}
impl risc0_zkp::layout::Component for Sha256mix_2__3__SuperLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256mix_2__3__SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct Sha256mix_2__3_Layout {
    pub _super: &'static Sha256mix_2__3__SuperLayout,
    pub new_w: &'static UnpackWithCarryLayout,
    pub new_a: &'static UnpackWithCarryLayout,
    pub new_e: &'static UnpackWithCarryLayout,
    pub ae: &'static ComputeAELayout,
    pub packed_w: &'static ComputeWLayout,
}
impl risc0_zkp::layout::Component for Sha256mix_2__3_Layout {
    fn ty_name(&self) -> &'static str {
        "Sha256mix_2__3_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("new_w", self.new_w)?;
        v.visit_component("new_a", self.new_a)?;
        v.visit_component("new_e", self.new_e)?;
        v.visit_component("ae", self.ae)?;
        v.visit_component("packed_w", self.packed_w)?;
        Ok(())
    }
}
pub struct Sha256mix_2__4_Arm1_Super_SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static RetTupleLayout,
}
impl risc0_zkp::layout::Component for Sha256mix_2__4_Arm1_Super_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256mix_2__4_Arm1_Super_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct Sha256mix_2__4__SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static Sha256mix_2__4_Arm1_Super_SuperLayout,
}
impl risc0_zkp::layout::Component for Sha256mix_2__4__SuperLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256mix_2__4__SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct Sha256mix_2__4_Layout {
    pub _super: &'static Sha256mix_2__4__SuperLayout,
    pub new_w: &'static UnpackWithCarryLayout,
    pub new_a: &'static UnpackWithCarryLayout,
    pub new_e: &'static UnpackWithCarryLayout,
    pub ae: &'static ComputeAELayout,
    pub packed_w: &'static ComputeWLayout,
}
impl risc0_zkp::layout::Component for Sha256mix_2__4_Layout {
    fn ty_name(&self) -> &'static str {
        "Sha256mix_2__4_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("new_w", self.new_w)?;
        v.visit_component("new_a", self.new_a)?;
        v.visit_component("new_e", self.new_e)?;
        v.visit_component("ae", self.ae)?;
        v.visit_component("packed_w", self.packed_w)?;
        Ok(())
    }
}
pub struct Sha256mix_2__5_Arm1_Super_SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static RetTupleLayout,
}
impl risc0_zkp::layout::Component for Sha256mix_2__5_Arm1_Super_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256mix_2__5_Arm1_Super_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct Sha256mix_2__5__SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static Sha256mix_2__5_Arm1_Super_SuperLayout,
}
impl risc0_zkp::layout::Component for Sha256mix_2__5__SuperLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256mix_2__5__SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct Sha256mix_2__5_Layout {
    pub _super: &'static Sha256mix_2__5__SuperLayout,
    pub new_w: &'static UnpackWithCarryLayout,
    pub new_a: &'static UnpackWithCarryLayout,
    pub new_e: &'static UnpackWithCarryLayout,
    pub ae: &'static ComputeAELayout,
    pub packed_w: &'static ComputeWLayout,
}
impl risc0_zkp::layout::Component for Sha256mix_2__5_Layout {
    fn ty_name(&self) -> &'static str {
        "Sha256mix_2__5_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("new_w", self.new_w)?;
        v.visit_component("new_a", self.new_a)?;
        v.visit_component("new_e", self.new_e)?;
        v.visit_component("ae", self.ae)?;
        v.visit_component("packed_w", self.packed_w)?;
        Ok(())
    }
}
pub struct Sha256mix_2__6_Arm1_Super_SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static RetTupleLayout,
}
impl risc0_zkp::layout::Component for Sha256mix_2__6_Arm1_Super_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256mix_2__6_Arm1_Super_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct Sha256mix_2__6__SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static Sha256mix_2__6_Arm1_Super_SuperLayout,
}
impl risc0_zkp::layout::Component for Sha256mix_2__6__SuperLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256mix_2__6__SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct Sha256mix_2__6_Layout {
    pub _super: &'static Sha256mix_2__6__SuperLayout,
    pub new_w: &'static UnpackWithCarryLayout,
    pub new_a: &'static UnpackWithCarryLayout,
    pub new_e: &'static UnpackWithCarryLayout,
    pub ae: &'static ComputeAELayout,
    pub packed_w: &'static ComputeWLayout,
}
impl risc0_zkp::layout::Component for Sha256mix_2__6_Layout {
    fn ty_name(&self) -> &'static str {
        "Sha256mix_2__6_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("new_w", self.new_w)?;
        v.visit_component("new_a", self.new_a)?;
        v.visit_component("new_e", self.new_e)?;
        v.visit_component("ae", self.ae)?;
        v.visit_component("packed_w", self.packed_w)?;
        Ok(())
    }
}
pub struct Sha256mix_2__7_Arm1_Super_SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static RetTupleLayout,
}
impl risc0_zkp::layout::Component for Sha256mix_2__7_Arm1_Super_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256mix_2__7_Arm1_Super_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct Sha256mix_2__7__SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static Sha256mix_2__7_Arm1_Super_SuperLayout,
}
impl risc0_zkp::layout::Component for Sha256mix_2__7__SuperLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256mix_2__7__SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct Sha256mix_2__7_Layout {
    pub _super: &'static Sha256mix_2__7__SuperLayout,
    pub new_w: &'static UnpackWithCarryLayout,
    pub new_a: &'static UnpackWithCarryLayout,
    pub new_e: &'static UnpackWithCarryLayout,
    pub ae: &'static ComputeAELayout,
    pub packed_w: &'static ComputeWLayout,
}
impl risc0_zkp::layout::Component for Sha256mix_2__7_Layout {
    fn ty_name(&self) -> &'static str {
        "Sha256mix_2__7_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("new_w", self.new_w)?;
        v.visit_component("new_a", self.new_a)?;
        v.visit_component("new_e", self.new_e)?;
        v.visit_component("ae", self.ae)?;
        v.visit_component("packed_w", self.packed_w)?;
        Ok(())
    }
}
pub struct Sha256mix_2__8_Arm1_Super_SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static RetTupleLayout,
}
impl risc0_zkp::layout::Component for Sha256mix_2__8_Arm1_Super_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256mix_2__8_Arm1_Super_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct Sha256mix_2__8__SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static Sha256mix_2__8_Arm1_Super_SuperLayout,
}
impl risc0_zkp::layout::Component for Sha256mix_2__8__SuperLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256mix_2__8__SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct Sha256mix_2__8_Layout {
    pub _super: &'static Sha256mix_2__8__SuperLayout,
    pub new_w: &'static UnpackWithCarryLayout,
    pub new_a: &'static UnpackWithCarryLayout,
    pub new_e: &'static UnpackWithCarryLayout,
    pub ae: &'static ComputeAELayout,
    pub packed_w: &'static ComputeWLayout,
}
impl risc0_zkp::layout::Component for Sha256mix_2__8_Layout {
    fn ty_name(&self) -> &'static str {
        "Sha256mix_2__8_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("new_w", self.new_w)?;
        v.visit_component("new_a", self.new_a)?;
        v.visit_component("new_e", self.new_e)?;
        v.visit_component("ae", self.ae)?;
        v.visit_component("packed_w", self.packed_w)?;
        Ok(())
    }
}
pub struct Sha256mix_2__9_Arm1_Super_SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static RetTupleLayout,
}
impl risc0_zkp::layout::Component for Sha256mix_2__9_Arm1_Super_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256mix_2__9_Arm1_Super_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct Sha256mix_2__9__SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static Sha256mix_2__9_Arm1_Super_SuperLayout,
}
impl risc0_zkp::layout::Component for Sha256mix_2__9__SuperLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256mix_2__9__SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct Sha256mix_2__9_Layout {
    pub _super: &'static Sha256mix_2__9__SuperLayout,
    pub new_w: &'static UnpackWithCarryLayout,
    pub new_a: &'static UnpackWithCarryLayout,
    pub new_e: &'static UnpackWithCarryLayout,
    pub ae: &'static ComputeAELayout,
    pub packed_w: &'static ComputeWLayout,
}
impl risc0_zkp::layout::Component for Sha256mix_2__9_Layout {
    fn ty_name(&self) -> &'static str {
        "Sha256mix_2__9_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("new_w", self.new_w)?;
        v.visit_component("new_a", self.new_a)?;
        v.visit_component("new_e", self.new_e)?;
        v.visit_component("ae", self.ae)?;
        v.visit_component("packed_w", self.packed_w)?;
        Ok(())
    }
}
pub struct Sha256mix_2__10_Arm1_Super_SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static RetTupleLayout,
}
impl risc0_zkp::layout::Component for Sha256mix_2__10_Arm1_Super_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256mix_2__10_Arm1_Super_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct Sha256mix_2__10__SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static Sha256mix_2__10_Arm1_Super_SuperLayout,
}
impl risc0_zkp::layout::Component for Sha256mix_2__10__SuperLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256mix_2__10__SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct Sha256mix_2__10_Layout {
    pub _super: &'static Sha256mix_2__10__SuperLayout,
    pub new_w: &'static UnpackWithCarryLayout,
    pub new_a: &'static UnpackWithCarryLayout,
    pub new_e: &'static UnpackWithCarryLayout,
    pub ae: &'static ComputeAELayout,
    pub packed_w: &'static ComputeWLayout,
}
impl risc0_zkp::layout::Component for Sha256mix_2__10_Layout {
    fn ty_name(&self) -> &'static str {
        "Sha256mix_2__10_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("new_w", self.new_w)?;
        v.visit_component("new_a", self.new_a)?;
        v.visit_component("new_e", self.new_e)?;
        v.visit_component("ae", self.ae)?;
        v.visit_component("packed_w", self.packed_w)?;
        Ok(())
    }
}
pub struct Sha256mix_2__11_Arm1_Super_SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static RetTupleLayout,
}
impl risc0_zkp::layout::Component for Sha256mix_2__11_Arm1_Super_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256mix_2__11_Arm1_Super_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct Sha256mix_2__11__SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static Sha256mix_2__11_Arm1_Super_SuperLayout,
}
impl risc0_zkp::layout::Component for Sha256mix_2__11__SuperLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256mix_2__11__SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct Sha256mix_2__11_Layout {
    pub _super: &'static Sha256mix_2__11__SuperLayout,
    pub new_w: &'static UnpackWithCarryLayout,
    pub new_a: &'static UnpackWithCarryLayout,
    pub new_e: &'static UnpackWithCarryLayout,
    pub ae: &'static ComputeAELayout,
    pub packed_w: &'static ComputeWLayout,
}
impl risc0_zkp::layout::Component for Sha256mix_2__11_Layout {
    fn ty_name(&self) -> &'static str {
        "Sha256mix_2__11_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("new_w", self.new_w)?;
        v.visit_component("new_a", self.new_a)?;
        v.visit_component("new_e", self.new_e)?;
        v.visit_component("ae", self.ae)?;
        v.visit_component("packed_w", self.packed_w)?;
        Ok(())
    }
}
pub struct Sha256mix_2__12_Arm1_Super_SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static RetTupleLayout,
}
impl risc0_zkp::layout::Component for Sha256mix_2__12_Arm1_Super_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256mix_2__12_Arm1_Super_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct Sha256mix_2__12__SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static Sha256mix_2__12_Arm1_Super_SuperLayout,
}
impl risc0_zkp::layout::Component for Sha256mix_2__12__SuperLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256mix_2__12__SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct Sha256mix_2__12_Layout {
    pub _super: &'static Sha256mix_2__12__SuperLayout,
    pub new_w: &'static UnpackWithCarryLayout,
    pub new_a: &'static UnpackWithCarryLayout,
    pub new_e: &'static UnpackWithCarryLayout,
    pub ae: &'static ComputeAELayout,
    pub packed_w: &'static ComputeWLayout,
}
impl risc0_zkp::layout::Component for Sha256mix_2__12_Layout {
    fn ty_name(&self) -> &'static str {
        "Sha256mix_2__12_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("new_w", self.new_w)?;
        v.visit_component("new_a", self.new_a)?;
        v.visit_component("new_e", self.new_e)?;
        v.visit_component("ae", self.ae)?;
        v.visit_component("packed_w", self.packed_w)?;
        Ok(())
    }
}
pub struct Sha256mix_2__13_Arm1_Super_SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static RetTupleLayout,
}
impl risc0_zkp::layout::Component for Sha256mix_2__13_Arm1_Super_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256mix_2__13_Arm1_Super_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct Sha256mix_2__13__SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static Sha256mix_2__13_Arm1_Super_SuperLayout,
}
impl risc0_zkp::layout::Component for Sha256mix_2__13__SuperLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256mix_2__13__SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct Sha256mix_2__13_Layout {
    pub _super: &'static Sha256mix_2__13__SuperLayout,
    pub new_w: &'static UnpackWithCarryLayout,
    pub new_a: &'static UnpackWithCarryLayout,
    pub new_e: &'static UnpackWithCarryLayout,
    pub ae: &'static ComputeAELayout,
    pub packed_w: &'static ComputeWLayout,
}
impl risc0_zkp::layout::Component for Sha256mix_2__13_Layout {
    fn ty_name(&self) -> &'static str {
        "Sha256mix_2__13_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("new_w", self.new_w)?;
        v.visit_component("new_a", self.new_a)?;
        v.visit_component("new_e", self.new_e)?;
        v.visit_component("ae", self.ae)?;
        v.visit_component("packed_w", self.packed_w)?;
        Ok(())
    }
}
pub struct Sha256mix_2__14_Arm1_Super_SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static RetTupleLayout,
}
impl risc0_zkp::layout::Component for Sha256mix_2__14_Arm1_Super_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256mix_2__14_Arm1_Super_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct Sha256mix_2__14__SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static Sha256mix_2__14_Arm1_Super_SuperLayout,
}
impl risc0_zkp::layout::Component for Sha256mix_2__14__SuperLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256mix_2__14__SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct Sha256mix_2__14_Layout {
    pub _super: &'static Sha256mix_2__14__SuperLayout,
    pub new_w: &'static UnpackWithCarryLayout,
    pub new_a: &'static UnpackWithCarryLayout,
    pub new_e: &'static UnpackWithCarryLayout,
    pub ae: &'static ComputeAELayout,
    pub packed_w: &'static ComputeWLayout,
}
impl risc0_zkp::layout::Component for Sha256mix_2__14_Layout {
    fn ty_name(&self) -> &'static str {
        "Sha256mix_2__14_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("new_w", self.new_w)?;
        v.visit_component("new_a", self.new_a)?;
        v.visit_component("new_e", self.new_e)?;
        v.visit_component("ae", self.ae)?;
        v.visit_component("packed_w", self.packed_w)?;
        Ok(())
    }
}
pub struct Sha256mix_2__15_Arm1_Super_SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static RetTupleLayout,
}
impl risc0_zkp::layout::Component for Sha256mix_2__15_Arm1_Super_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256mix_2__15_Arm1_Super_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct Sha256mix_2__15__SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static RetTupleLayout,
    pub arm1: &'static Sha256mix_2__15_Arm1_Super_SuperLayout,
}
impl risc0_zkp::layout::Component for Sha256mix_2__15__SuperLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256mix_2__15__SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct Sha256mix_2__15_Layout {
    pub _super: &'static Sha256mix_2__15__SuperLayout,
    pub new_w: &'static UnpackWithCarryLayout,
    pub new_a: &'static UnpackWithCarryLayout,
    pub new_e: &'static UnpackWithCarryLayout,
    pub ae: &'static ComputeAELayout,
    pub packed_w: &'static ComputeWLayout,
}
impl risc0_zkp::layout::Component for Sha256mix_2__15_Layout {
    fn ty_name(&self) -> &'static str {
        "Sha256mix_2__15_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("new_w", self.new_w)?;
        v.visit_component("new_a", self.new_a)?;
        v.visit_component("new_e", self.new_e)?;
        v.visit_component("ae", self.ae)?;
        v.visit_component("packed_w", self.packed_w)?;
        Ok(())
    }
}
pub struct Sha256mixAll_2__SuperLayout {
    pub _super: &'static RetTupleLayout,
    pub arm0: &'static Sha256mix_2__0_Layout,
    pub arm1: &'static Sha256mix_2__1_Layout,
    pub arm2: &'static Sha256mix_2__2_Layout,
    pub arm3: &'static Sha256mix_2__3_Layout,
    pub arm4: &'static Sha256mix_2__4_Layout,
    pub arm5: &'static Sha256mix_2__5_Layout,
    pub arm6: &'static Sha256mix_2__6_Layout,
    pub arm7: &'static Sha256mix_2__7_Layout,
    pub arm8: &'static Sha256mix_2__8_Layout,
    pub arm9: &'static Sha256mix_2__9_Layout,
    pub arm10: &'static Sha256mix_2__10_Layout,
    pub arm11: &'static Sha256mix_2__11_Layout,
    pub arm12: &'static Sha256mix_2__12_Layout,
    pub arm13: &'static Sha256mix_2__13_Layout,
    pub arm14: &'static Sha256mix_2__14_Layout,
    pub arm15: &'static Sha256mix_2__15_Layout,
}
impl risc0_zkp::layout::Component for Sha256mixAll_2__SuperLayout {
    fn ty_name(&self) -> &'static str {
        "Sha256mixAll_2__SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        v.visit_component("arm2", self.arm2)?;
        v.visit_component("arm3", self.arm3)?;
        v.visit_component("arm4", self.arm4)?;
        v.visit_component("arm5", self.arm5)?;
        v.visit_component("arm6", self.arm6)?;
        v.visit_component("arm7", self.arm7)?;
        v.visit_component("arm8", self.arm8)?;
        v.visit_component("arm9", self.arm9)?;
        v.visit_component("arm10", self.arm10)?;
        v.visit_component("arm11", self.arm11)?;
        v.visit_component("arm12", self.arm12)?;
        v.visit_component("arm13", self.arm13)?;
        v.visit_component("arm14", self.arm14)?;
        v.visit_component("arm15", self.arm15)?;
        Ok(())
    }
}
pub struct Sha256mixAll_2_Layout {
    pub _super: &'static Sha256mixAll_2__SuperLayout,
    pub minor_onehot: &'static OneHot_16_Layout,
}
impl risc0_zkp::layout::Component for Sha256mixAll_2_Layout {
    fn ty_name(&self) -> &'static str {
        "Sha256mixAll_2_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("minor_onehot", self.minor_onehot)?;
        Ok(())
    }
}
pub struct TopRetvalsLayout {
    pub _super: &'static RetTupleLayout,
    pub _selector: &'static NondetRegLayout23LayoutArray,
    pub arm0: &'static Xor5wordsMajor_0_Layout,
    pub arm1: &'static Xor5wordsMajor_1_Layout,
    pub arm2: &'static Xor5wordsMajor_2_Layout,
    pub arm3: &'static Xor5wordsMajor_3_Layout,
    pub arm4: &'static Xor5wordsMajor_4_Layout,
    pub arm5: &'static RhoMajor_0_Layout,
    pub arm6: &'static RhoMajor_1_Layout,
    pub arm7: &'static RhoMajor_2_Layout,
    pub arm8: &'static RhoMajor_3_Layout,
    pub arm9: &'static RhoMajor_4_Layout,
    pub arm10: &'static ChiMajor_0_Layout,
    pub arm11: &'static ChiMajor_1_Layout,
    pub arm12: &'static ChiMajor_2_Layout,
    pub arm13: &'static ChiMajor_3_Layout,
    pub arm14: &'static ChiMajor_4_Layout,
    pub arm15: &'static AbsorbMajor1Layout,
    pub arm16: &'static AbsorbMajor2Layout,
    pub arm17: &'static SetupMajorLayout,
    pub arm18: &'static TopArm18_SuperLayout,
    pub arm19: &'static Sha256loadAllLayout,
    pub arm20: &'static Sha256mixAll_0_Layout,
    pub arm21: &'static Sha256mixAll_1_Layout,
    pub arm22: &'static Sha256mixAll_2_Layout,
}
impl risc0_zkp::layout::Component for TopRetvalsLayout {
    fn ty_name(&self) -> &'static str {
        "TopRetvalsLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("_selector", self._selector)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        v.visit_component("arm2", self.arm2)?;
        v.visit_component("arm3", self.arm3)?;
        v.visit_component("arm4", self.arm4)?;
        v.visit_component("arm5", self.arm5)?;
        v.visit_component("arm6", self.arm6)?;
        v.visit_component("arm7", self.arm7)?;
        v.visit_component("arm8", self.arm8)?;
        v.visit_component("arm9", self.arm9)?;
        v.visit_component("arm10", self.arm10)?;
        v.visit_component("arm11", self.arm11)?;
        v.visit_component("arm12", self.arm12)?;
        v.visit_component("arm13", self.arm13)?;
        v.visit_component("arm14", self.arm14)?;
        v.visit_component("arm15", self.arm15)?;
        v.visit_component("arm16", self.arm16)?;
        v.visit_component("arm17", self.arm17)?;
        v.visit_component("arm18", self.arm18)?;
        v.visit_component("arm19", self.arm19)?;
        v.visit_component("arm20", self.arm20)?;
        v.visit_component("arm21", self.arm21)?;
        v.visit_component("arm22", self.arm22)?;
        Ok(())
    }
}
pub struct TopLayout {
    pub pc: &'static NondetRegLayout,
    pub inv_pc: &'static NondetRegLayout,
    pub major_onehot: &'static OneHot_23_Layout,
    pub retvals: &'static TopRetvalsLayout,
}
impl risc0_zkp::layout::Component for TopLayout {
    fn ty_name(&self) -> &'static str {
        "TopLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("pc", self.pc)?;
        v.visit_component("inv_pc", self.inv_pc)?;
        v.visit_component("major_onehot", self.major_onehot)?;
        v.visit_component("retvals", self.retvals)?;
        Ok(())
    }
}
pub struct ShaOutputLayout {
    pub vals: &'static NondetRegLayout16LayoutArray,
}
impl risc0_zkp::layout::Component for ShaOutputLayout {
    fn ty_name(&self) -> &'static str {
        "ShaOutputLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("vals", self.vals)?;
        Ok(())
    }
}
pub type Reg1LayoutArray = [&'static Reg; 1];
pub struct TestEqzLayout {
    pub _0: &'static NondetRegLayout,
}
impl risc0_zkp::layout::Component for TestEqzLayout {
    fn ty_name(&self) -> &'static str {
        "TestEqzLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_0", self._0)?;
        Ok(())
    }
}
pub struct TestSucc_TestKeccak01Layout {
    pub x: &'static TopLayout,
    pub _0: &'static TestEqzLayout,
    pub _1: &'static TestEqzLayout,
    pub _2: &'static TestEqzLayout,
    pub _3: &'static TestEqzLayout,
    pub _4: &'static TestEqzLayout,
    pub _5: &'static TestEqzLayout,
    pub _6: &'static TestEqzLayout,
    pub _7: &'static TestEqzLayout,
    pub _8: &'static TestEqzLayout,
    pub _9: &'static TestEqzLayout,
    pub _10: &'static TestEqzLayout,
    pub _11: &'static TestEqzLayout,
    pub _12: &'static TestEqzLayout,
    pub _13: &'static TestEqzLayout,
    pub _14: &'static TestEqzLayout,
    pub _15: &'static TestEqzLayout,
}
impl risc0_zkp::layout::Component for TestSucc_TestKeccak01Layout {
    fn ty_name(&self) -> &'static str {
        "TestSucc_TestKeccak01Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("x", self.x)?;
        v.visit_component("_0", self._0)?;
        v.visit_component("_1", self._1)?;
        v.visit_component("_2", self._2)?;
        v.visit_component("_3", self._3)?;
        v.visit_component("_4", self._4)?;
        v.visit_component("_5", self._5)?;
        v.visit_component("_6", self._6)?;
        v.visit_component("_7", self._7)?;
        v.visit_component("_8", self._8)?;
        v.visit_component("_9", self._9)?;
        v.visit_component("_10", self._10)?;
        v.visit_component("_11", self._11)?;
        v.visit_component("_12", self._12)?;
        v.visit_component("_13", self._13)?;
        v.visit_component("_14", self._14)?;
        v.visit_component("_15", self._15)?;
        Ok(())
    }
}
pub struct _globalLayout {
    pub output: &'static ShaOutputLayout,
}
impl risc0_zkp::layout::Component for _globalLayout {
    fn ty_name(&self) -> &'static str {
        "_globalLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("output", self.output)?;
        Ok(())
    }
}
pub struct Arg_UseOnceMemoryElementLayout {
    pub index: &'static Reg,
    pub _0: &'static Reg,
    pub _1: &'static Reg,
    pub _2: &'static Reg,
    pub _3: &'static Reg,
}
impl risc0_zkp::layout::Component for Arg_UseOnceMemoryElementLayout {
    fn ty_name(&self) -> &'static str {
        "Arg_UseOnceMemoryElementLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("index", self.index)?;
        v.visit_component("_0", self._0)?;
        v.visit_component("_1", self._1)?;
        v.visit_component("_2", self._2)?;
        v.visit_component("_3", self._3)?;
        Ok(())
    }
}
pub struct _accumLayout {
    pub use_once_memory_element: &'static Arg_UseOnceMemoryElementLayout,
    pub _offset: &'static Reg,
}
impl risc0_zkp::layout::Component for _accumLayout {
    fn ty_name(&self) -> &'static str {
        "_accumLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("use_once_memory_element", self.use_once_memory_element)?;
        v.visit_component("_offset", self._offset)?;
        Ok(())
    }
}
pub struct _mixLayout {
    pub randomness: &'static _accumLayout,
}
impl risc0_zkp::layout::Component for _mixLayout {
    fn ty_name(&self) -> &'static str {
        "_mixLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("randomness", self.randomness)?;
        Ok(())
    }
}
#[derive(Copy, Clone, Debug)]
pub struct NondetRegStruct {
    pub _super: Val,
}
pub type Val4Array = [Val; 4];
#[derive(Copy, Clone, Debug)]
pub struct MemDigestStruct {
    pub _super: Val4Array,
}
pub type NondetRegStruct4Array = [NondetRegStruct; 4];
#[derive(Copy, Clone, Debug)]
pub struct UseOnceMemoryElementStruct {
    pub count: NondetRegStruct,
    pub index: NondetRegStruct,
    pub digest: NondetRegStruct4Array,
}
#[derive(Copy, Clone, Debug)]
pub struct ReadMemoryStruct {
    pub _super: NondetRegStruct4Array,
}
#[derive(Copy, Clone, Debug)]
pub struct WriteMemoryStruct {}
pub type Val22Array = [Val; 22];
pub type NondetRegStruct22Array = [NondetRegStruct; 22];
pub type Val24Array = [Val; 24];
pub type NondetRegStruct24Array = [NondetRegStruct; 24];
#[derive(Copy, Clone, Debug)]
pub struct RetTupleStruct {
    pub arr_a: NondetRegStruct22Array,
    pub arr_b: NondetRegStruct22Array,
    pub arr_c: NondetRegStruct22Array,
    pub arr_d: NondetRegStruct24Array,
    pub arr_e: NondetRegStruct22Array,
    pub arr_f: NondetRegStruct22Array,
    pub minor: NondetRegStruct,
    pub major: NondetRegStruct,
    pub rnd: NondetRegStruct,
    pub blk: NondetRegStruct,
    pub midx: NondetRegStruct,
}
pub type Val32Array = [Val; 32];
#[derive(Copy, Clone, Debug)]
pub struct TwoShortsStruct {
    pub low: Val,
    pub high: Val,
}
#[derive(Copy, Clone, Debug)]
pub struct Pack2Struct {
    pub _super: TwoShortsStruct,
    pub low: NondetRegStruct,
    pub high: NondetRegStruct,
}
#[derive(Copy, Clone, Debug)]
pub struct ComputeAEStruct {
    pub a_out: TwoShortsStruct,
    pub e_out: TwoShortsStruct,
}
pub type Val19Array = [Val; 19];
pub type Val31Array = [Val; 31];
pub type NondetRegStruct19Array = [NondetRegStruct; 19];
#[derive(Copy, Clone, Debug)]
pub struct ToBits_19_Struct {
    pub _super: NondetRegStruct19Array,
}
pub type Val20Array = [Val; 20];
pub type NondetRegStruct20Array = [NondetRegStruct; 20];
#[derive(Copy, Clone, Debug)]
pub struct ToBits_20_Struct {
    pub _super: NondetRegStruct20Array,
}
#[derive(Copy, Clone, Debug)]
pub struct Concatenate_NondetReg__16__16__Super_SuperStruct {
    pub _super: Val,
}
pub type Concatenate_NondetReg__16__16__Super_SuperStruct32Array =
    [Concatenate_NondetReg__16__16__Super_SuperStruct; 32];
#[derive(Copy, Clone, Debug)]
pub struct Concatenate_NondetReg__16__16_Struct {
    pub _super: Concatenate_NondetReg__16__16__Super_SuperStruct32Array,
}
pub type Val16Array = [Val; 16];
pub type NondetRegStruct16Array = [NondetRegStruct; 16];
#[derive(Copy, Clone, Debug)]
pub struct OneHot_16_Struct {
    pub _super: NondetRegStruct16Array,
}
#[derive(Copy, Clone, Debug)]
pub struct ToBits_16_Struct {
    pub _super: NondetRegStruct16Array,
}
pub type Val6Array = [Val; 6];
#[derive(Copy, Clone, Debug)]
pub struct ToBits_22_Struct {
    pub _super: NondetRegStruct22Array,
}
pub type Val21Array = [Val; 21];
pub type NondetRegStruct21Array = [NondetRegStruct; 21];
#[derive(Copy, Clone, Debug)]
pub struct ToBits_21_Struct {
    pub _super: NondetRegStruct21Array,
}
pub type Val22Array3Array = [Val22Array; 3];
#[derive(Copy, Clone, Debug)]
pub struct RctableStruct {
    pub _super: Val22Array3Array,
}
pub type Val3Array = [Val; 3];
pub type Val10Array = [Val; 10];
pub type NondetRegStruct10Array = [NondetRegStruct; 10];
#[derive(Copy, Clone, Debug)]
pub struct OneHot_10_Struct {
    pub _super: NondetRegStruct10Array,
}
pub type Val9Array = [Val; 9];
pub type NondetRegStruct9Array = [NondetRegStruct; 9];
#[derive(Copy, Clone, Debug)]
pub struct OneHot_9_Struct {
    pub _super: NondetRegStruct9Array,
}
pub type Val30Array = [Val; 30];
pub type NondetRegStruct30Array = [NondetRegStruct; 30];
#[derive(Copy, Clone, Debug)]
pub struct ToBits_30_Struct {
    pub _super: NondetRegStruct30Array,
}
#[derive(Copy, Clone, Debug)]
pub struct ShaOutputValsStruct {}
pub type ShaOutputValsStruct16Array = [ShaOutputValsStruct; 16];
#[derive(Copy, Clone, Debug)]
pub struct ShaOutputStruct {}
pub type Val14Array = [Val; 14];
pub type NondetRegStruct14Array = [NondetRegStruct; 14];
#[derive(Copy, Clone, Debug)]
pub struct OneHot_14_Struct {
    pub _super: NondetRegStruct14Array,
}
pub type NondetRegStruct3Array = [NondetRegStruct; 3];
#[derive(Copy, Clone, Debug)]
pub struct ToBits_3_Struct {
    pub _super: NondetRegStruct3Array,
}
pub type Val5Array = [Val; 5];
pub type Val23Array = [Val; 23];
pub type NondetRegStruct23Array = [NondetRegStruct; 23];
#[derive(Copy, Clone, Debug)]
pub struct OneHot_23_Struct {
    pub _super: NondetRegStruct23Array,
}
#[derive(Copy, Clone, Debug)]
pub struct OneHot_4_Struct {
    pub _super: NondetRegStruct4Array,
}
#[derive(Copy, Clone, Debug)]
pub struct FromBits_22_Struct {
    pub _super: Val,
}
#[derive(Copy, Clone, Debug)]
pub struct FromBits_21_Struct {
    pub _super: Val,
}
pub type Val12Array = [Val; 12];
pub type NondetRegStruct12Array = [NondetRegStruct; 12];
pub type Val15Array = [Val; 15];
pub type NondetRegStruct15Array = [NondetRegStruct; 15];
pub type Val18Array = [Val; 18];
pub type NondetRegStruct18Array = [NondetRegStruct; 18];
#[derive(Copy, Clone, Debug)]
pub struct OneHot_24_Struct {
    pub _super: NondetRegStruct24Array,
}
#[derive(Copy, Clone, Debug)]
pub struct TopStruct {}
#[derive(Copy, Clone, Debug)]
pub struct ComponentStruct {}
