//===- DWARFTypeUnit.h ------------------------------------------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_DEBUGINFO_DWARF_DWARFTYPEUNIT_H
#define LLVM_DEBUGINFO_DWARF_DWARFTYPEUNIT_H

#include "llvm/ADT/StringRef.h"
#include "llvm/DebugInfo/DWARF/DWARFUnit.h"
#include "llvm/DebugInfo/DWARF/DWARFUnitIndex.h"
#include "llvm/Support/DataExtractor.h"
#include <cstdint>

namespace llvm {

class DWARFContext;
class DWARFDebugAbbrev;
struct DWARFSection;
class raw_ostream;

class DWARFTypeUnit : public DWARFUnit {
public:
  DWARFTypeUnit(DWARFContext &Context, const DWARFSection &Section,
                const DWARFUnitHeader &Header,
                const DWARFDebugAbbrev *DA, const DWARFSection *RS,
                StringRef SS, const DWARFSection &SOS, const DWARFSection *AOS,
                const DWARFSection &LS, bool LE, bool IsDWO,
                const DWARFUnitSectionBase &UnitSection)
      : DWARFUnit(Context, Section, Header, DA, RS, SS, SOS, AOS, LS, LE, IsDWO,
                  UnitSection) {}

  uint32_t getHeaderSize() const override {
    return DWARFUnit::getHeaderSize() + 12;
  }
  uint64_t getTypeHash() const { return getHeader().getTypeHash(); }
  uint32_t getTypeOffset() const { return getHeader().getTypeOffset(); }

  void dump(raw_ostream &OS, DIDumpOptions DumpOpts = {});
  static const DWARFSectionKind Section = DW_SECT_TYPES;
};

} // end namespace llvm

#endif // LLVM_DEBUGINFO_DWARF_DWARFTYPEUNIT_H
