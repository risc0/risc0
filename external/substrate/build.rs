fn main() {
    #[cfg(feature = "std")]
    {
        substrate_wasm_builder::WasmBuilder::new()
            .with_current_project()
            .export_heap_base()
            .disable_runtime_version_section_check()
            .import_memory()
            .build();
    }
}
