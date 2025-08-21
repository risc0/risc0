// Copyright 2025 RISC Zero, Inc.
//
// This project is dual-licensed under either:
// - Apache License, Version 2.0 (LICENSE-APACHE or https://www.apache.org/licenses/LICENSE-2.0)
// - MIT License (LICENSE-MIT or https://opensource.org/licenses/MIT)
// at your option.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

use std::collections::HashMap;
use std::path::PathBuf;

use addr2line::{
    demangle_auto,
    gimli::{self, Reader as _},
};
use anyhow::{Result, anyhow, bail};

use super::Frame;

#[derive(Debug, Hash, PartialEq, Eq, Copy, Clone)]
pub struct InlineFunction {
    pub abstract_origin: u64,
    pub low_pc: u64,
    pub high_pc: u64,
}

#[derive(Debug, Default)]
pub struct InlineFunctionTable {
    /// abstract_origin to inline function frame
    pub frames: HashMap<u64, Frame>,
    /// low_pc to inline function
    pub starts: HashMap<u64, Vec<InlineFunction>>,
}

fn dwarf_attr_or_error<ReaderT: gimli::Reader>(
    entry: &gimli::DebuggingInformationEntry<'_, '_, ReaderT>,
    dw_at: gimli::DwAt,
) -> Result<gimli::AttributeValue<ReaderT>> {
    Ok(entry
        .attr(dw_at)?
        .ok_or_else(|| anyhow!("{dw_at} missing"))?
        .value())
}

fn get_abstract_origin_name(
    dwarf: &gimli::Dwarf<gimli::EndianRcSlice<gimli::RunTimeEndian>>,
    unit: &gimli::Unit<gimli::EndianRcSlice<gimli::RunTimeEndian>>,
    abstract_origin: &gimli::UnitOffset<usize>,
) -> Result<String> {
    let mut entries = unit.entries_raw(Some(*abstract_origin))?;
    let abbrev = if let Some(abbrev) = entries.read_abbreviation()? {
        abbrev
    } else {
        bail!("invalid abstract_origin");
    };

    for spec in abbrev.attributes() {
        let attr = entries.read_attribute(*spec)?;
        match attr.name() {
            gimli::DW_AT_linkage_name | gimli::DW_AT_MIPS_linkage_name => {
                return Ok(dwarf
                    .attr_string(unit, attr.value())?
                    .to_string_lossy()?
                    .into());
            }
            gimli::DW_AT_name => {
                return Ok(dwarf
                    .attr_string(unit, attr.value())?
                    .to_string_lossy()?
                    .into());
            }
            _ => {}
        }
    }

    bail!("invalid abstract origin")
}

fn find_unit<'a>(
    units: &'a [gimli::Unit<gimli::EndianRcSlice<gimli::RunTimeEndian>>],
    offset: &gimli::DebugInfoOffset<usize>,
) -> Result<&'a gimli::Unit<gimli::EndianRcSlice<gimli::RunTimeEndian>>> {
    match units.binary_search_by_key(&offset.0, |unit| {
        unit.header.offset().as_debug_info_offset().unwrap().0
    }) {
        Ok(_) | Err(0) => bail!("no unit for given offset"),
        Err(i) => Ok(&units[i - 1]),
    }
}

struct InlineFunctionTableBuilder<'dwarf> {
    language: Option<gimli::DwLang>,
    dwarf: &'dwarf gimli::Dwarf<gimli::EndianRcSlice<gimli::RunTimeEndian>>,
    units: &'dwarf [gimli::Unit<gimli::EndianRcSlice<gimli::RunTimeEndian>>],
    table: InlineFunctionTable,
}

impl<'dwarf> InlineFunctionTableBuilder<'dwarf> {
    fn new(
        dwarf: &'dwarf gimli::Dwarf<gimli::EndianRcSlice<gimli::RunTimeEndian>>,
        units: &'dwarf [gimli::Unit<gimli::EndianRcSlice<gimli::RunTimeEndian>>],
    ) -> Result<Self> {
        Ok(Self {
            language: None,
            dwarf,
            units,
            table: InlineFunctionTable::default(),
        })
    }

    fn build(mut self) -> Result<InlineFunctionTable> {
        for unit in self.units {
            self.build_from_unit(unit)?;
        }
        Ok(self.table)
    }

    fn build_from_unit(
        &mut self,
        unit: &'dwarf gimli::Unit<gimli::EndianRcSlice<gimli::RunTimeEndian>>,
    ) -> Result<()> {
        let mut entries = unit.entries();
        while let Some((_, entry)) = entries.next_dfs()? {
            if entry.tag() == gimli::DW_TAG_compile_unit
                && let Ok(gimli::AttributeValue::Language(unit_language)) =
                    dwarf_attr_or_error(entry, gimli::DW_AT_language)
            {
                self.language = Some(unit_language);
            }
            if entry.tag() == gimli::DW_TAG_inlined_subroutine
                && let Err(error) = self.build_from_inline_subroutine(unit, entry)
            {
                tracing::warn!("Error decoding DWARF for DW_TAG_inlined_subroutine: {error}");
            }
        }

        Ok(())
    }

    fn read_pc_ranges_from_entry(
        &self,
        unit: &'dwarf gimli::Unit<gimli::EndianRcSlice<gimli::RunTimeEndian>>,
        entry: &gimli::DebuggingInformationEntry<
            '_,
            '_,
            gimli::EndianRcSlice<gimli::RunTimeEndian>,
        >,
    ) -> Result<Vec<(u64, u64)>> {
        let Ok(value) = dwarf_attr_or_error(entry, gimli::DW_AT_ranges) else {
            return Ok(vec![]);
        };

        let Some(ranges_offset) = self.dwarf.attr_ranges_offset(unit, value)? else {
            return Ok(vec![]);
        };

        let mut ranges = vec![];
        let mut range_iter = self.dwarf.ranges(unit, ranges_offset)?;
        while let Some(gimli::Range { begin, end }) = range_iter.next()? {
            if begin < end && begin != 0 {
                ranges.push((begin, end));
            }
        }
        Ok(ranges)
    }

    fn read_low_pc_from_entry(
        &self,
        unit: &'dwarf gimli::Unit<gimli::EndianRcSlice<gimli::RunTimeEndian>>,
        entry: &gimli::DebuggingInformationEntry<
            '_,
            '_,
            gimli::EndianRcSlice<gimli::RunTimeEndian>,
        >,
    ) -> Result<Option<u64>> {
        let Ok(value) = dwarf_attr_or_error(entry, gimli::DW_AT_low_pc) else {
            return Ok(None);
        };
        let low_pc = match value {
            gimli::AttributeValue::Addr(val) => val,
            gimli::AttributeValue::DebugAddrIndex(index) => self.dwarf.address(unit, index)?,
            _ => bail!("DW_AT_low_pc not as expected"),
        };
        Ok((low_pc != 0).then_some(low_pc))
    }

    fn read_high_pc_from_entry(
        &self,
        unit: &'dwarf gimli::Unit<gimli::EndianRcSlice<gimli::RunTimeEndian>>,
        entry: &gimli::DebuggingInformationEntry<
            '_,
            '_,
            gimli::EndianRcSlice<gimli::RunTimeEndian>,
        >,
        low_pc: u64,
    ) -> Result<u64> {
        Ok(match dwarf_attr_or_error(entry, gimli::DW_AT_high_pc)? {
            gimli::AttributeValue::Addr(val) => val,
            gimli::AttributeValue::DebugAddrIndex(index) => self.dwarf.address(unit, index)?,
            gimli::AttributeValue::Udata(val) => low_pc + val,
            _ => bail!("DW_AT_high_pc not as expected"),
        })
    }

    fn read_low_pc_and_high_pc_from_entry(
        &self,
        unit: &'dwarf gimli::Unit<gimli::EndianRcSlice<gimli::RunTimeEndian>>,
        entry: &gimli::DebuggingInformationEntry<
            '_,
            '_,
            gimli::EndianRcSlice<gimli::RunTimeEndian>,
        >,
    ) -> Result<Option<(u64, u64)>> {
        let Some(low_pc) = self.read_low_pc_from_entry(unit, entry)? else {
            return Ok(None);
        };
        let high_pc = self.read_high_pc_from_entry(unit, entry, low_pc)?;

        Ok(Some((low_pc, high_pc)))
    }

    fn read_abstract_origin_from_entry(
        &self,
        unit: &'dwarf gimli::Unit<gimli::EndianRcSlice<gimli::RunTimeEndian>>,
        entry: &gimli::DebuggingInformationEntry<
            '_,
            '_,
            gimli::EndianRcSlice<gimli::RunTimeEndian>,
        >,
    ) -> Result<(String, gimli::DebugInfoOffset)> {
        match dwarf_attr_or_error(entry, gimli::DW_AT_abstract_origin)? {
            gimli::AttributeValue::UnitRef(unit_offset) => Ok((
                get_abstract_origin_name(self.dwarf, unit, &unit_offset)?,
                unit_offset
                    .to_debug_info_offset(&unit.header)
                    .ok_or_else(|| anyhow!("invalid attribute abstract_origin"))?,
            )),
            gimli::AttributeValue::DebugInfoRef(debug_info_offset) => {
                let unit = find_unit(self.units, &debug_info_offset)?;
                let unit_offset = debug_info_offset
                    .to_unit_offset(&unit.header)
                    .ok_or_else(|| anyhow!("invalid attribute abstract_origin"))?;
                Ok((
                    get_abstract_origin_name(self.dwarf, unit, &unit_offset)?,
                    debug_info_offset,
                ))
            }
            _ => bail!("DW_AT_abstract_origin not as expected"),
        }
    }

    fn read_file_name_from_entry(
        &self,
        unit: &'dwarf gimli::Unit<gimli::EndianRcSlice<gimli::RunTimeEndian>>,
        entry: &gimli::DebuggingInformationEntry<
            '_,
            '_,
            gimli::EndianRcSlice<gimli::RunTimeEndian>,
        >,
    ) -> Result<Option<String>> {
        let Ok(value) = dwarf_attr_or_error(entry, gimli::DW_AT_call_file) else {
            return Ok(None);
        };
        let gimli::AttributeValue::FileIndex(idx) = value else {
            return Ok(None);
        };

        let line_program = unit
            .line_program
            .as_ref()
            .ok_or_else(|| anyhow!("line_program missing"))?;

        let header = line_program.header();
        let file = header
            .file(idx)
            .ok_or_else(|| anyhow!("file index {idx} missing"))?;

        let mut file_path = PathBuf::new();
        if let Some(comp_dir) = unit.comp_dir.as_ref() {
            file_path.push(comp_dir.to_string_lossy()?.as_ref());
        }

        if file.directory_index() != 0 {
            let directory = file
                .directory(header)
                .ok_or_else(|| anyhow!("file directory missing"))?;
            let value = self.dwarf.attr_string(unit, directory)?;
            file_path.push(value.to_string_lossy()?.as_ref());
        }

        let s = self.dwarf.attr_string(unit, file.path_name())?;
        file_path.push(s.to_string_lossy()?.as_ref());
        Ok(Some(file_path.to_string_lossy().into()))
    }

    fn read_line_number_from_entry(
        &self,
        entry: &gimli::DebuggingInformationEntry<
            '_,
            '_,
            gimli::EndianRcSlice<gimli::RunTimeEndian>,
        >,
    ) -> Option<i64> {
        if let Ok(gimli::AttributeValue::Udata(val)) =
            dwarf_attr_or_error(entry, gimli::DW_AT_call_line)
        {
            Some(val as i64)
        } else {
            None
        }
    }

    fn build_from_inline_subroutine(
        &mut self,
        unit: &'dwarf gimli::Unit<gimli::EndianRcSlice<gimli::RunTimeEndian>>,
        entry: &gimli::DebuggingInformationEntry<
            '_,
            '_,
            gimli::EndianRcSlice<gimli::RunTimeEndian>,
        >,
    ) -> Result<()> {
        let mut ranges = vec![];

        if let Some(range) = self.read_low_pc_and_high_pc_from_entry(unit, entry)? {
            ranges.push(range);
        } else {
            ranges.extend(self.read_pc_ranges_from_entry(unit, entry)?);
        }

        let (name, abstract_origin) = self.read_abstract_origin_from_entry(unit, entry)?;

        for (low_pc, high_pc) in ranges {
            let starts = self.table.starts.entry(low_pc).or_default();
            starts.push(InlineFunction {
                abstract_origin: abstract_origin.0 as u64,
                low_pc,
                high_pc,
            });
        }

        #[allow(clippy::map_entry)]
        if !self.table.frames.contains_key(&(abstract_origin.0 as u64)) {
            let filename = self.read_file_name_from_entry(unit, entry)?;
            let lineno = self.read_line_number_from_entry(entry);

            let frame = Frame {
                name: demangle_auto(std::borrow::Cow::Borrowed(&name), self.language).into(),
                lineno: lineno.unwrap_or_default(),
                filename: filename.unwrap_or_default(),
            };
            self.table.frames.insert(abstract_origin.0 as u64, frame);
        }

        Ok(())
    }
}

impl InlineFunctionTable {
    pub fn build_from_dwarf(
        dwarf: &gimli::Dwarf<gimli::EndianRcSlice<gimli::RunTimeEndian>>,
    ) -> Result<Self> {
        let mut units = vec![];
        let mut iter = dwarf.units();
        while let Some(header) = iter.next()? {
            units.push(dwarf.unit(header)?);
        }

        let builder = InlineFunctionTableBuilder::new(dwarf, &units)?;
        builder.build()
    }
}
