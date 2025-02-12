// Copyright 2025 RISC Zero, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

use clap::Parser;
use risc0_binfmt::MemoryImage2;
use risc0_circuit_rv32im_v2::{
    execute::{platform::LOOKUP_TABLE_CYCLES, testutil, DEFAULT_SEGMENT_LIMIT_PO2},
    MAX_INSN_CYCLES,
};

/// keccak prover benchmarking tool
#[derive(Parser)]
#[command(about, version, author)]
struct Cli {
    /// Circuit PO2
    #[arg(long, default_value_t = DEFAULT_SEGMENT_LIMIT_PO2)]
    po2: usize,

    /// Number of proofs to run
    #[arg(long, default_value_t = 1)]
    count: usize,
}

const PAGING_CYCLES: usize = 1821;
const NON_LOOP_CYCLES: usize = 8;
const RESERVED_CYCLES: usize =
    LOOKUP_TABLE_CYCLES + PAGING_CYCLES + NON_LOOP_CYCLES + MAX_INSN_CYCLES;

fn main() {
    tracing_subscriber::fmt()
        .with_env_filter(tracing_subscriber::filter::EnvFilter::from_default_env())
        .init();
    //let segments = result.segments;
    //let segment = segments.first().unwrap();
    //assert_eq!(args.po2, segment.po2 as usize);
    puffin::set_scopes_on(true); // you may want to control this with a flag
                                 //let mut frame_counter = 0;
    let mut keep_repainting = true;

    // Give us something to inspect:
    let args = Cli::parse();

    let po2 = args.po2;
    let segment_cycles = 1 << po2;
    assert!(segment_cycles > RESERVED_CYCLES);
    let iterations = (segment_cycles - RESERVED_CYCLES) / 2;

    let program = testutil::kernel::simple_loop(iterations as u32);
    let image = MemoryImage2::new_kernel(program);

    //let user_cycles = result.result.user_cycles as usize;
    //let total_cycles = result.result.total_cycles as usize;

    puffin::set_scopes_on(true);

    let options = eframe::NativeOptions {
        viewport: egui::ViewportBuilder::default().with_inner_size([320.0, 240.0]),
        ..Default::default()
    };
    let _ = eframe::run_simple_native("puffin egui eframe", options, move |ctx, _frame| {
        puffin::profile_function!();
        puffin::GlobalProfiler::lock().new_frame(); // If you use the `puffin` feature of `eframe` you don't need to call this

        egui::CentralPanel::default().show(ctx, |ui| {
            let mut profile = puffin::are_scopes_on();
            ui.checkbox(&mut profile, "Show profiler window");
            puffin::set_scopes_on(profile); // controls both the profile capturing, and the displaying of it

            ui.horizontal(|ui| {
                ui.checkbox(&mut keep_repainting, "Keep repainting this window");
                if keep_repainting {
                    ui.spinner();
                    ui.ctx().request_repaint();
                }
            });

            if ui.button("Quit").clicked() {
                ui.ctx().send_viewport_cmd(egui::ViewportCommand::Close);
            }
        });
        let image = image.clone();

        let result = testutil::execute(
            image,
            args.po2,
            MAX_INSN_CYCLES,
            testutil::DEFAULT_SESSION_LIMIT,
            &testutil::NullSyscall,
            None,
        )
        .unwrap();

        // This call does nothing if profiling is disabled
        puffin_egui::show_viewport_if_enabled(ctx);

        // ----------------------------------------------------------------

        result.segments.first().unwrap().preflight_test().unwrap();

        //frame_counter += 1;
        std::thread::sleep(std::time::Duration::from_millis(1000));
    });
}
