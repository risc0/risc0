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

use std::io::Write;

use termcolor::{Color, ColorChoice, ColorSpec, StandardStream, WriteColor};

use crate::errors::RzupError;

pub fn info_msg(msg: &str) -> Result<(), RzupError> {
    let mut stdout = StandardStream::stdout(ColorChoice::Always);
    let mut color_spec = ColorSpec::new();
    color_spec.set_bold(true);
    stdout.set_color(&color_spec)?;
    write!(stdout, "info: ")?;
    stdout.reset()?;
    writeln!(stdout, "{}", msg)?;
    stdout.flush()?;
    Ok(())
}

pub fn pretty_msg(
    stdout: &mut StandardStream,
    bold: bool,
    color: Option<Color>,
    message: &str,
) -> Result<(), RzupError> {
    let mut color_spec = ColorSpec::new();
    color_spec.set_bold(bold).set_fg(color);
    stdout.set_color(&color_spec)?;
    write!(stdout, "{}", message)?;
    stdout.flush()?;
    Ok(())
}

pub fn pretty_msgln(
    stdout: &mut StandardStream,
    bold: bool,
    color: Option<Color>,
    message: &str,
) -> Result<(), RzupError> {
    pretty_msg(stdout, bold, color, message)?;
    writeln!(stdout)?;
    stdout.flush()?;
    Ok(())
}

pub fn pretty_header(stdout: &mut StandardStream, header: &str) -> Result<(), RzupError> {
    pretty_msgln(stdout, true, None, header)?;
    pretty_msgln(stdout, true, None, &"-".repeat(header.len()))?;
    pretty_msgln(stdout, false, None, "")?;
    Ok(())
}
