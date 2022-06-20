#![cfg(feature = "risc_cc")]

use std::path::Path;

use cc::Error;
#[derive(Debug)]
/// A convenient wrapper around cc::Build with sensible defaults for building
/// to riscv32im targets.
pub struct Build {
    inner: cc::Build,
    riscv_default_features: bool,
}

impl Default for Build {
    fn default() -> Self {
        Self {
            inner: cc::Build::new(),
            riscv_default_features: true,
        }
    }
}

impl Build {
    /// Construct a new instance with a default configuration for riscv32im.
    /// This builder is finished with the compile function
    pub fn new() -> Self {
        Self::default()
    }

    /// Add a directory to the `-I` or include path for headers
    pub fn include<P: AsRef<Path>>(&mut self, dir: P) -> &mut Self {
        self.inner.include(dir);
        self
    }

    /// Add multiple directories to the `-I` include path.
    pub fn includes<P>(&mut self, dirs: P) -> &mut Self
    where
        P: IntoIterator,
        P::Item: AsRef<Path>,
    {
        self.inner.includes(dirs);
        self
    }

    /// Specify a `-D` variable with an optional value.
    pub fn define<'a, V: Into<Option<&'a str>>>(&mut self, var: &str, val: V) -> &mut Self {
        self.inner.define(var, val);
        self
    }

    /// Add an arbitrary object file to link in
    pub fn object<P: AsRef<Path>>(&mut self, obj: P) -> &mut Self {
        self.inner.object(obj);
        self
    }

    /// Add an arbitrary flag to the invocation of the compiler
    pub fn flag(&mut self, flag: &str) -> &mut Self {
        self.inner.flag(flag);
        self
    }

    /// Add a flag to the invocation of the `ar`
    pub fn ar_flag(&mut self, flag: &str) -> &mut Self {
        self.inner.ar_flag(flag);
        self
    }

    /// Run the compiler to test if it accepts the given flag.
    ///
    /// For a convenience method for setting flags conditionally, see flag_if_supported().
    ///
    /// It may return error if it’s unable to run the compiler with a test file
    /// (e.g. the compiler is missing or a write to the out_dir failed).
    ///
    /// Note: Once computed, the result of this call is stored in the known_flag_support field.
    /// If is_flag_supported(flag) is called again, the result will be read from the hash table.
    pub fn is_flag_supported(&self, flag: &str) -> Result<bool, Error> {
        self.inner.is_flag_supported(flag)
    }

    /// Add an arbitrary flag to the invocation of the compiler if it supports it
    pub fn flag_if_supported(&mut self, flag: &str) -> &mut Self {
        self.inner.flag_if_supported(flag);
        self
    }

    /// Set the `-shared` flag.
    ///
    /// When enabled, the compiler will produce a shared object which can then
    /// be linked with other objects to form an executable.
    pub fn shared_flag(&mut self, shared_flag: bool) -> &mut Self {
        self.inner.shared_flag(shared_flag);
        self
    }

    /// Set the `-static` flag.
    ///
    /// When enabled on systems that support dynamic linking, this prevents linking with the shared libraries.
    pub fn static_flag(&mut self, static_flag: bool) -> &mut Self {
        self.inner.static_flag(static_flag);
        self
    }

    /// Enables the generation of default compiler flags by the inner `cc::Build`.
    /// If this option is not set, this crate disables `cc`'s default flags
    /// because they can cause issues when cross compiling.
    ///
    /// Setting the `CRATE_CC_DEFAULTS` environment variable has the same effect as setting this to `true`.
    /// The presence of the environment variable and this value will be OR’d together.
    pub fn cc_default_flags(&mut self, default_flags: bool) -> &mut Self {
        let default_flags_from_env = match option_env!("CRATE_CC_DEFAULTS") {
            Some(str) => str.to_lowercase() == "true",
            None => false,
        };
        let flags = default_flags || default_flags_from_env;
        self.inner.no_default_flags(!flags);
        self
    }

    /// Add a file which will be compiled
    pub fn file<P: AsRef<Path>>(&mut self, p: P) -> &mut Self {
        self.inner.file(p);
        self
    }

    /// Add files which will be compiled
    pub fn files<P>(&mut self, p: P) -> &mut Self
    where
        P: IntoIterator,
        P::Item: AsRef<Path>,
    {
        self.inner.files(p);
        self
    }

    /// Set C++ support.
    ///
    /// The other `cpp_*` options will only become active if this is set to `true`.
    pub fn cpp(&mut self, cpp: bool) -> &mut Self {
        self.inner.cpp(cpp);
        self
    }

    /// Set CUDA C++ support.
    ///
    /// Enabling CUDA will pass the detected C/C++ toolchain as an argument to the CUDA compiler, NVCC.
    /// NVCC itself accepts some limited GNU-like args; any other arguments for the C/C++ toolchain
    /// will be redirected using “-Xcompiler” flags.
    pub fn cuda(&mut self, cuda: bool) -> &mut Self {
        self.inner.cuda(cuda);
        self
    }

    /// Link CUDA run-time.
    ///
    /// This option mimics the `--cudart NVCC` command-line option. Just like the original it
    /// accepts `{none|shared|static}`, with default being `static`. The method has to be invoked after `.cuda(true)`,
    ///  or not at all, if the default is right for the project.
    pub fn cudart(&mut self, cudart: &str) -> &mut Self {
        self.inner.cudart(cudart);
        self
    }
}
