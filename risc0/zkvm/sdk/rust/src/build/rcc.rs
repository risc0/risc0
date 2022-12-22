#![cfg(feature = "risc_cc")]

use std::{env, ffi::OsStr, path::Path};

use cc;
use cc::Error;

#[allow(missing_docs)]
pub const DEFAULT_RV_CC_INSTALL_PATH: &str = "/opt/riscv";

#[derive(Debug)]
/// A convenient wrapper around `cc::Build` with sensible defaults for building
/// to `riscv32im` targets. See `./mod.rs` for further explanation.
pub struct Build {
    inner: cc::Build,
    rv_cc_install_path: String,
    no_risc0_default_flags: bool,
    compiler_default_flags: bool,
    release: bool,
}

impl Build {
    /// Construct a new instance with the default riscv32 configuration.
    ///
    /// This builder is finished with the [`compile`] function.
    ///
    /// [`compile`]: struct.Build.html#method.compile
    pub fn new() -> Self {
        let is_riscv_env = env::var("CARGO_CFG_TARGET_ARCH").unwrap() == "riscv32";

        Self {
            inner: cc::Build::new(),
            rv_cc_install_path: DEFAULT_RV_CC_INSTALL_PATH.to_string(),
            no_risc0_default_flags: !is_riscv_env,
            compiler_default_flags: false,
            release: false,
        }
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
    /// For a convenience method for setting flags conditionally, `see
    /// flag_if_supported()`.
    ///
    /// It may return error if it’s unable to run the compiler with a test file
    /// (e.g. the compiler is missing or a write to the `out_dir` failed).
    ///
    /// Note: Once computed, the result of this call is stored in the
    /// `known_flag_support` field. If `is_flag_supported(flag)` is called
    /// again, the result will be read from the hash table.
    pub fn is_flag_supported(&self, flag: &str) -> Result<bool, Error> {
        self.inner.is_flag_supported(flag)
    }

    /// Add an arbitrary flag to the invocation of the compiler if it supports
    /// it
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
    /// When enabled on systems that support dynamic linking, this prevents
    /// linking with the shared libraries.
    pub fn static_flag(&mut self, static_flag: bool) -> &mut Self {
        self.inner.static_flag(static_flag);
        self
    }

    /// Enables the generation of default compiler flags by the inner
    /// `cc::Build`. If this option is not set, this crate disables `cc`'s
    /// default flags because they can cause issues when cross compiling.
    ///
    /// Setting the `CRATE_COMPILER_DEFAULTS` environment variable has the same
    /// effect as setting this to `true`. The presence of the environment
    /// variable and this value will be OR’d together.
    pub fn compiler_default_flags(&mut self, compiler_default_flags: bool) -> &mut Self {
        self.compiler_default_flags = compiler_default_flags;
        self
    }

    /// Disables the generation of default risc0 flags.
    ///
    /// Setting the `CRATE_NO_RISC0_DEFAULTS` environment variable has the same
    /// effect as setting this to `true`. The presence of the environment
    /// variable and this value will be OR’d together.
    pub fn no_risc0_default_flags(&mut self, no_risc0_default_flags: bool) -> &mut Self {
        self.no_risc0_default_flags = no_risc0_default_flags;
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
    /// The other `cpp_*` options will only become active if this is set to
    /// `true`.
    pub fn cpp(&mut self, cpp: bool) -> &mut Self {
        self.inner.cpp(cpp);
        self
    }

    /// Set CUDA C++ support.
    ///
    /// Enabling CUDA will pass the detected C/C++ toolchain as an argument to
    /// the CUDA compiler, NVCC. NVCC itself accepts some limited GNU-like
    /// args; any other arguments for the C/C++ toolchain will be redirected
    /// using "-Xcompiler" flags.
    pub fn cuda(&mut self, cuda: bool) -> &mut Self {
        self.inner.cuda(cuda);
        self
    }

    /// Link CUDA run-time.
    ///
    /// This option mimics the `--cudart NVCC` command-line option. Just like
    /// the original it accepts `{none|shared|static}`, with default being
    /// `static`. The method has to be invoked after `.cuda(true)`,
    ///  or not at all, if the default is right for the project.
    pub fn cudart(&mut self, cudart: &str) -> &mut Self {
        self.inner.cudart(cudart);
        self
    }

    /// Set warnings into errors flag.
    ///
    /// Disabled by default.
    ///
    /// Warning: turning warnings into errors only make sense
    /// if you are a developer of the crate using cc-rs.
    /// Some warnings only appear on some architecture or
    /// specific version of the compiler. Any user of this crate,
    /// or any other crate depending on it, could fail during
    /// compile time.
    pub fn warnings_into_errors(&mut self, warnings_into_errors: bool) -> &mut Self {
        self.inner.warnings_into_errors(warnings_into_errors);
        self
    }

    /// Set warnings flags.
    ///
    /// Adds some flags:
    /// - "-Wall" for MSVC.
    /// - "-Wall", "-Wextra" for GNU and Clang.
    ///
    /// Enabled by default.
    pub fn warnings(&mut self, warnings: bool) -> &mut Self {
        self.inner.warnings(warnings);
        self
    }

    /// Set extra warnings flags.
    ///
    /// Adds some flags:
    /// - nothing for MSVC.
    /// - "-Wextra" for GNU and Clang.
    ///
    /// Enabled by default.
    pub fn extra_warnings(&mut self, warnings: bool) -> &mut Self {
        self.inner.extra_warnings(warnings);
        self
    }

    /// Set the standard library to link against when compiling with C++
    /// support.
    ///
    /// See [`get_cpp_link_stdlib`](cc::Build::get_cpp_link_stdlib)
    /// documentation for the default value.
    /// If the `CXXSTDLIB` environment variable is set, its value will
    /// override the default value, but not the value explicitly set by calling
    /// this function.
    ///
    /// A value of `None` indicates that no automatic linking should happen,
    /// otherwise cargo will link against the specified library.
    ///
    /// The given library name must not contain the `lib` prefix.
    ///
    /// Common values:
    /// - `stdc++` for GNU
    /// - `c++` for Clang
    /// - `c++_shared` or `c++_static` for Android
    pub fn cpp_link_stdlib<'a, V: Into<Option<&'a str>>>(
        &mut self,
        cpp_link_stdlib: V,
    ) -> &mut Self {
        self.inner.cpp_link_stdlib(cpp_link_stdlib);
        self
    }

    /// Force the C++ compiler to use the specified standard library.
    ///
    /// Setting this option will automatically set `cpp_link_stdlib` to the same
    /// value.
    ///
    /// The default value of this option is always `None`.
    ///
    /// This option has no effect when compiling for a Visual Studio based
    /// target.
    ///
    /// This option sets the `-stdlib` flag, which is only supported by some
    /// compilers (clang, icc) but not by others (gcc). The library will not
    /// detect which compiler is used, as such it is the responsibility of the
    /// caller to ensure that this option is only used in conjunction with a
    /// compiler which supports the `-stdlib` flag.
    ///
    /// A value of `None` indicates that no specific C++ standard library should
    /// be used, otherwise `-stdlib` is added to the compile invocation.
    ///
    /// The given library name must not contain the `lib` prefix.
    ///
    /// Common values:
    /// - `stdc++` for GNU
    /// - `c++` for Clang
    pub fn cpp_set_stdlib<'a, V: Into<Option<&'a str>>>(&mut self, cpp_set_stdlib: V) -> &mut Self {
        self.inner.cpp_set_stdlib(cpp_set_stdlib);
        self
    }

    /// Configures the target this configuration will be compiling for.
    ///
    /// This option is automatically scraped from the `TARGET` environment
    /// variable by build scripts, so it's not required to call this function.
    pub fn target(&mut self, target: &str) -> &mut Self {
        self.inner.target(target);
        self
    }

    /// Configures the host assumed by this configuration.
    ///
    /// This option is automatically scraped from the `HOST` environment
    /// variable by build scripts, so it's not required to call this function.
    pub fn host(&mut self, host: &str) -> &mut Self {
        self.inner.host(host);
        self
    }

    /// Configures the optimization level of the generated object files.
    ///
    /// This option is automatically scraped from the `OPT_LEVEL` environment
    /// variable by build scripts, so it's not required to call this function.
    pub fn opt_level(&mut self, opt_level: u32) -> &mut Self {
        self.inner.opt_level(opt_level);
        self
    }

    /// Configures the optimization level of the generated object files.
    ///
    /// This option is automatically scraped from the `OPT_LEVEL` environment
    /// variable by build scripts, so it's not required to call this function.
    pub fn opt_level_str(&mut self, opt_level: &str) -> &mut Self {
        self.inner.opt_level_str(opt_level);
        self
    }

    /// Configures whether the compiler will emit debug information when
    /// generating object files.
    ///
    /// This option is automatically scraped from the `DEBUG` environment
    /// variable by build scripts, so it's not required to call this function.
    pub fn debug(&mut self, debug: bool) -> &mut Self {
        self.inner.debug(debug);
        self
    }

    /// Configures whether the compiler will emit instructions to store
    /// frame pointers during codegen.
    ///
    /// This option is automatically enabled when debug information is emitted.
    /// Otherwise the target platform compiler's default will be used.
    /// You can use this option to force a specific setting.
    pub fn force_frame_pointer(&mut self, force: bool) -> &mut Self {
        self.inner.force_frame_pointer(force);
        self
    }

    /// Configures the output directory where all object files and static
    /// libraries will be located.
    ///
    /// This option is automatically scraped from the `OUT_DIR` environment
    /// variable by build scripts, so it's not required to call this function.
    pub fn out_dir<P: AsRef<Path>>(&mut self, out_dir: P) -> &mut Self {
        self.inner.out_dir(out_dir);
        self
    }

    /// Configures the compiler to be used to produce output.
    ///
    /// Setting the `RCC_COMPILER` makes this method call redundant. The
    /// presence of the environment variable supersedes this value.
    ///
    /// If not set via this call or the env variable above, this option is
    /// automatically determined from the target platform or a number of
    /// environment variables.
    pub fn compiler<P: AsRef<Path>>(&mut self, compiler: P) -> &mut Self {
        self.inner.compiler(compiler);
        self
    }

    /// Configures the tool used to assemble archives.
    ///
    /// This option is automatically determined from the target platform or a
    /// number of environment variables, so it's not required to call this
    /// function.
    pub fn archiver<P: AsRef<Path>>(&mut self, archiver: P) -> &mut Self {
        self.inner.archiver(archiver);
        self
    }

    /// Define whether metadata should be emitted for cargo allowing it to
    /// automatically link the binary. Defaults to `true`.
    ///
    /// The emitted metadata is:
    ///
    ///  - `rustc-link-lib=static=`*compiled lib*
    ///  - `rustc-link-search=native=`*target folder*
    ///  - When target is MSVC, the ATL-MFC libs are added via
    ///    `rustc-link-search=native=`
    ///  - When C++ is enabled, the C++ stdlib is added via `rustc-link-lib`
    pub fn cargo_metadata(&mut self, cargo_metadata: bool) -> &mut Self {
        self.inner.cargo_metadata(cargo_metadata);
        self
    }

    /// Configures whether the compiler will emit position independent code.
    ///
    /// This option defaults to `false` for `windows-gnu` and bare metal targets
    /// and to `true` for all other targets.
    pub fn pic(&mut self, pic: bool) -> &mut Self {
        self.inner.pic(pic);
        self
    }

    /// Configures whether the Procedure Linkage Table is used for indirect
    /// calls into shared libraries.
    ///
    /// The PLT is used to provide features like lazy binding, but introduces
    /// a small performance loss due to extra pointer indirection. Setting
    /// `use_plt` to `false` can provide a small performance increase.
    ///
    /// Note that skipping the PLT requires a recent version of GCC/Clang.
    ///
    /// This only applies to ELF targets. It has no effect on other platforms.
    pub fn use_plt(&mut self, use_plt: bool) -> &mut Self {
        self.inner.use_plt(use_plt);
        self
    }

    /// Configures whether the /MT flag or the /MD flag will be passed to msvc
    /// build tools.
    ///
    /// This option defaults to `false`, and affect only msvc targets.
    pub fn static_crt(&mut self, static_crt: bool) -> &mut Self {
        self.inner.static_crt(static_crt);
        self
    }

    #[doc(hidden)]
    pub fn __set_env<A, B>(&mut self, a: A, b: B) -> &mut Self
    where
        A: AsRef<OsStr>,
        B: AsRef<OsStr>,
    {
        self.inner.__set_env(a, b);
        self
    }

    /// Configures the riscv32 cross-compiler install path. The default value is
    /// "/opt/riscv"
    ///
    /// Setting the `RV_CC_INSTALL_PATH` makes this method call redundant. The
    /// presence of the environment variable supersedes this or the default
    /// value.
    pub fn rv_cc_install_path(&mut self, rv_cc_install_path: &str) -> &mut Self {
        self.rv_cc_install_path = rv_cc_install_path.to_string();
        self
    }

    /// If enabled, removes debug information from the compiled binary. This
    /// improves performance and reduces binary size. This option is
    /// equivalent to: ```no_run
    ///  cc::Build::new()
    ///             .flag("-feliminate-unused-debug-symbols")
    ///             .flag("-feliminate-unused-debug-types")
    ///             .flag("-fvirtual-function-elimination");
    /// ```
    pub fn release(&mut self, release: bool) -> &mut Self {
        self.release = release;
        self
    }

    /// Run the compiler, generating the file `output`
    ///
    /// This will return a result instead of panicing; see compile() for the
    /// complete description.
    pub fn try_compile(&mut self, output: &str) -> Result<(), Error> {
        self.add_flags();
        self.inner.try_compile(output)
    }

    /// Run the compiler, generating the file `output`
    ///
    /// # Library name
    ///
    /// The `output` string argument determines the file name for the compiled
    /// library. The Rust compiler will create an assembly named
    /// "lib"+output+".a". MSVC will create a file named output+".lib".
    ///
    /// The choice of `output` is close to arbitrary, but:
    ///
    /// - must be nonempty,
    /// - must not contain a path separator (`/`),
    /// - must be unique across all `compile` invocations made by the same build
    ///   script.
    ///
    /// If your build script compiles a single source file, the base name of
    /// that source file would usually be reasonable:
    ///
    /// ```no_run
    /// cc::Build::new().file("blobstore.c").compile("blobstore");
    /// ```
    ///
    /// Compiling multiple source files, some people use their crate's name, or
    /// their crate's name + "-cc".
    ///
    /// Otherwise, please use your imagination.
    ///
    /// For backwards compatibility, if `output` starts with "lib" *and* ends
    /// with ".a", a second "lib" prefix and ".a" suffix do not get added on,
    /// but this usage is deprecated; please omit `lib` and `.a` in the argument
    /// that you pass.
    ///
    /// # Panics
    ///
    /// Panics if `output` is not formatted correctly or if one of the
    /// underlying compiler commands fails. It can also panic if it fails
    /// reading file names or creating directories.
    pub fn compile(&mut self, output: &str) {
        self.add_flags();
        self.inner.compile(output);
    }

    fn add_flags(&mut self) {
        // Check and add compiler default flags if necessary
        let compiler_default_flags_from_env = match env::var("CRATE_COMPILER_DEFAULTS").ok() {
            Some(s) => s.to_lowercase() == "true",
            None => false,
        };
        let compiler_default_flags = self.compiler_default_flags || compiler_default_flags_from_env;
        self.inner.no_default_flags(!compiler_default_flags);

        // Check and add no risc0 default flags if necessary
        let no_risc0_default_flags_from_env = match env::var("CRATE_NO_RISC0_DEFAULTS").ok() {
            Some(s) => s.to_lowercase() == "true",
            None => false,
        };
        self.no_risc0_default_flags =
            self.no_risc0_default_flags || no_risc0_default_flags_from_env;
        if self.no_risc0_default_flags {
            return;
        }

        // Set compiler from environment variable if it exists
        env::var("RCC_COMPILER")
            .ok()
            .filter(|s| !s.is_empty())
            .map(|s| self.inner.compiler(s));

        // Set riscv32 cross-compiler from environment variable if it exists
        env::var("RV_CC_INSTALL_PATH")
            .ok()
            .filter(|s| !s.is_empty())
            .map(|s| self.rv_cc_install_path = s);

        self.inner
            .target("riscv32im-unknown-none-elf")
            .opt_level(3)
            .flag("-O3")
            //.flag("--target=riscv32-unknown-none-elf")
            .flag("-mabi=ilp32")
            .flag("-mcmodel=medany")
            .flag("-fdata-sections")
            .flag("-ffunction-sections")
            .flag("-dead_strip")
            //.flag("-flto")
            .flag("-march=rv32im")
            .flag("-static")
            .flag(&format!(
                "--sysroot={}/riscv32-unknown-elf",
                self.rv_cc_install_path
            ))
            //.flag(&format!("--gcc-toolchain={}", self.rv_cc_install_path))
            ;

        if !self.release {
            return;
        }

        self.inner
            .flag("-feliminate-unused-debug-symbols")
            .flag("-feliminate-unused-debug-types")
            .flag("-fvirtual-function-elimination");
    }

    /// This will return a result instead of panicing; see expand() for the
    /// complete description.
    pub fn try_expand(&self) -> Result<Vec<u8>, Error> {
        self.inner.try_expand()
    }

    /// Run the compiler, returning the macro-expanded version of the input
    /// files.
    ///
    /// This is only relevant for C and C++ files.
    ///
    /// # Panics
    /// Panics if more than one file is present in the config, or if compiler
    /// path has an invalid file name.
    pub fn expand(&self) -> Vec<u8> {
        self.inner.expand()
    }

    /// Get the compiler that's in use for this configuration.
    ///
    /// This function will return a `Tool` which represents the culmination
    /// of this configuration at a snapshot in time. The returned compiler can
    /// be inspected (e.g. the path, arguments, environment) to forward along to
    /// other tools, or the `to_command` method can be used to invoke the
    /// compiler itself.
    ///
    /// This method will take into account all configuration such as debug
    /// information, optimization level, include directories, defines, etc.
    /// Additionally, the compiler binary in use follows the standard
    /// conventions for this path, e.g. looking at the explicitly set compiler,
    /// environment variables (a number of which are inspected here), and then
    /// falling back to the default configuration.
    ///
    /// # Panics
    ///
    /// Panics if an error occurred while determining the architecture.
    pub fn get_compiler(&self) -> cc::Tool {
        self.inner.get_compiler()
    }

    /// Get the compiler that's in use for this configuration.
    ///
    /// This will return a result instead of panicing; see get_compiler() for
    /// the complete description.
    pub fn try_get_compiler(&self) -> Result<cc::Tool, Error> {
        self.inner.try_get_compiler()
    }
}
