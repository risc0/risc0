// Copyright 2024 RISC Zero, Inc.
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

#[macro_export]
macro_rules! info_msg {
    ($msg:expr) => {{
        use std::io::Write;
        use termcolor::{ColorChoice, ColorSpec, StandardStream, WriteColor};

        let mut stdout = StandardStream::stdout(ColorChoice::Always);
        let mut color_spec = ColorSpec::new();
        color_spec.set_bold(true);
        stdout.set_color(&color_spec).expect("Failed to set color");
        write!(stdout, "info: ").expect("Failed to write info label");
        stdout.reset().expect("Failed to reset color");
        writeln!(stdout, "{}", $msg).expect("Failed to write message");
        stdout.flush().expect("Failed to flush stdout");
    }};
}

#[macro_export]
macro_rules! verbose_msg {
    ($msg:expr) => {{
        use std::io::Write;
        use termcolor::{Color, ColorChoice, ColorSpec, StandardStream, WriteColor};
        use $crate::utils::is_verbose;

        if is_verbose() {
            let mut stdout = StandardStream::stdout(ColorChoice::Always);
            let mut color_spec = ColorSpec::new();
            color_spec.set_bold(true).set_fg(Some(Color::Yellow));
            stdout.set_color(&color_spec).expect("Failed to set color");
            write!(stdout, "verbose: ").expect("Failed to write verbose label");
            stdout.reset().expect("Failed to reset color");
            writeln!(stdout, "{}", $msg).expect("Failed to write message");
            stdout.flush().expect("Failed to flush stdout");
        }
    }};
}

#[macro_export]
macro_rules! pretty_msg {
    ($stdout:expr, $bold:expr, $color:expr, $message:expr) => {{
        use std::io::Write;
        use termcolor::{ColorSpec, WriteColor};

        let mut color_spec = ColorSpec::new();
        color_spec.set_bold($bold).set_fg($color);
        $stdout.set_color(&color_spec).expect("Failed to set color");
        write!($stdout, "{}", $message).expect("Failed to write message");
        $stdout.flush().expect("Failed to flush stdout");
    }};
}

#[macro_export]
macro_rules! pretty_msgln {
    ($stdout:expr, $bold:expr, $color:expr, $message:expr) => {{
        use std::io::Write;
        pretty_msg!($stdout, $bold, $color, $message);
        writeln!($stdout).expect("Failed to write newline");
        $stdout.flush().expect("Failed to flush stdout");
    }};
}

#[macro_export]
macro_rules! pretty_header {
    ($stdout:expr, $header:expr) => {{
        pretty_msgln!($stdout, true, None, $header);
        pretty_msgln!($stdout, true, None, &"-".repeat($header.len()));
        pretty_msgln!($stdout, false, None, "");
    }};
}
