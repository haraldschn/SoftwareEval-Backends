/*
 * Copyright 2025 Chair of EDA, Technical University of Munich
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *	 http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/********************* AUTO GENERATE FILE (create by M2-ISA-R-Perf) *********************/

#include <algorithm>
#include <cstdint>

#include "PerformanceModel.h"

#include "RV32_OOO_PerformanceModel.h"
#include "RV32_OOO_uActions_Scheduling.h"

namespace RV32_OOO {

SchedulingFunctionSet* RV32_OOO_SchedulingFunctionSet = new SchedulingFunctionSet("RV32_OOO_SchedulingFunctionSet");

static SchedulingFunction* schedulingFunction_add = new SchedulingFunction(
    RV32_OOO_SchedulingFunctionSet,
    "add",
    0,
    [](PerformanceModel* perfModel_) {
        Arith_Ra_Rb(perfModel_);
    });

static SchedulingFunction* schedulingFunction_sub = new SchedulingFunction(
    RV32_OOO_SchedulingFunctionSet,
    "sub",
    1,
    [](PerformanceModel* perfModel_) {
        Arith_Ra_Rb(perfModel_);
    });

static SchedulingFunction* schedulingFunction_xor = new SchedulingFunction(
    RV32_OOO_SchedulingFunctionSet,
    "xor",
    2,
    [](PerformanceModel* perfModel_) {
        Arith_Ra_Rb(perfModel_);
    });

static SchedulingFunction* schedulingFunction_or = new SchedulingFunction(
    RV32_OOO_SchedulingFunctionSet,
    "or",
    3,
    [](PerformanceModel* perfModel_) {
        Arith_Ra_Rb(perfModel_);
    });

static SchedulingFunction* schedulingFunction_and = new SchedulingFunction(
    RV32_OOO_SchedulingFunctionSet,
    "and",
    4,
    [](PerformanceModel* perfModel_) {
        Arith_Ra_Rb(perfModel_);
    });

static SchedulingFunction* schedulingFunction_slt = new SchedulingFunction(
    RV32_OOO_SchedulingFunctionSet,
    "slt",
    5,
    [](PerformanceModel* perfModel_) {
        Arith_Ra_Rb(perfModel_);
    });

static SchedulingFunction* schedulingFunction_sltu = new SchedulingFunction(
    RV32_OOO_SchedulingFunctionSet,
    "sltu",
    6,
    [](PerformanceModel* perfModel_) {
        Arith_Ra_Rb(perfModel_);
    });

static SchedulingFunction* schedulingFunction_sll = new SchedulingFunction(
    RV32_OOO_SchedulingFunctionSet,
    "sll",
    7,
    [](PerformanceModel* perfModel_) {
        Arith_Ra_Rb(perfModel_);
    });

static SchedulingFunction* schedulingFunction_srl = new SchedulingFunction(
    RV32_OOO_SchedulingFunctionSet,
    "srl",
    8,
    [](PerformanceModel* perfModel_) {
        Arith_Ra_Rb(perfModel_);
    });

static SchedulingFunction* schedulingFunction_sra = new SchedulingFunction(
    RV32_OOO_SchedulingFunctionSet,
    "sra",
    9,
    [](PerformanceModel* perfModel_) {
        Arith_Ra_Rb(perfModel_);
    });

static SchedulingFunction* schedulingFunction_addi = new SchedulingFunction(
    RV32_OOO_SchedulingFunctionSet,
    "addi",
    10,
    [](PerformanceModel* perfModel_) {
      Arith_Ra(perfModel_);
    });

static SchedulingFunction* schedulingFunction_xori = new SchedulingFunction(
    RV32_OOO_SchedulingFunctionSet,
    "xori",
    11,
    [](PerformanceModel* perfModel_) {
      Arith_Ra(perfModel_);
    });

static SchedulingFunction* schedulingFunction_ori = new SchedulingFunction(
    RV32_OOO_SchedulingFunctionSet,
    "ori",
    12,
    [](PerformanceModel* perfModel_) {
      Arith_Ra(perfModel_);
    });

static SchedulingFunction* schedulingFunction_andi = new SchedulingFunction(
    RV32_OOO_SchedulingFunctionSet,
    "andi",
    13,
    [](PerformanceModel* perfModel_) {
      Arith_Ra(perfModel_);
    });

static SchedulingFunction* schedulingFunction_slti = new SchedulingFunction(
    RV32_OOO_SchedulingFunctionSet,
    "slti",
    14,
    [](PerformanceModel* perfModel_) {
      Arith_Ra(perfModel_);
    });

static SchedulingFunction* schedulingFunction_sltiu = new SchedulingFunction(
    RV32_OOO_SchedulingFunctionSet,
    "sltiu",
    15,
    [](PerformanceModel* perfModel_) {
      Arith_Ra(perfModel_);
    });

static SchedulingFunction* schedulingFunction_slli = new SchedulingFunction(
    RV32_OOO_SchedulingFunctionSet,
    "slli",
    16,
    [](PerformanceModel* perfModel_) {
      Arith_Ra(perfModel_);
    });

static SchedulingFunction* schedulingFunction_srli = new SchedulingFunction(
    RV32_OOO_SchedulingFunctionSet,
    "srli",
    17,
    [](PerformanceModel* perfModel_) {
      Arith_Ra(perfModel_);
    });

static SchedulingFunction* schedulingFunction_srai = new SchedulingFunction(
    RV32_OOO_SchedulingFunctionSet,
    "srai",
    18,
    [](PerformanceModel* perfModel_) {
      Arith_Ra(perfModel_);
    });

static SchedulingFunction* schedulingFunction_auipc = new SchedulingFunction(
    RV32_OOO_SchedulingFunctionSet,
    "auipc",
    19,
    [](PerformanceModel* perfModel_) {
      Arith_X(perfModel_);
    });

static SchedulingFunction* schedulingFunction_lui = new SchedulingFunction(
    RV32_OOO_SchedulingFunctionSet,
    "lui",
    20,
    [](PerformanceModel* perfModel_) {
      Arith_X(perfModel_);
    });

static SchedulingFunction* schedulingFunction_mul = new SchedulingFunction(
    RV32_OOO_SchedulingFunctionSet,
    "mul",
    21,
    [](PerformanceModel* perfModel_) {
      Mul_Ra_Rb(perfModel_);
    });

static SchedulingFunction* schedulingFunction_mulh = new SchedulingFunction(
    RV32_OOO_SchedulingFunctionSet,
    "mulh",
    22,
    [](PerformanceModel* perfModel_) {
      MulH_Ra_Rb(perfModel_);
    });

static SchedulingFunction* schedulingFunction_mulhu = new SchedulingFunction(
    RV32_OOO_SchedulingFunctionSet,
    "mulhu",
    23,
    [](PerformanceModel* perfModel_) {
      MulH_Ra_Rb(perfModel_);
    });

static SchedulingFunction* schedulingFunction_mulhsu = new SchedulingFunction(
    RV32_OOO_SchedulingFunctionSet,
    "mulhsu",
    24,
    [](PerformanceModel* perfModel_) {
      MulH_Ra_Rb(perfModel_);
    });

static SchedulingFunction* schedulingFunction_div = new SchedulingFunction(
    RV32_OOO_SchedulingFunctionSet,
    "div",
    25,
    [](PerformanceModel* perfModel_) {
      Div_Ra_Rb(perfModel_);
    });

static SchedulingFunction* schedulingFunction_rem = new SchedulingFunction(
    RV32_OOO_SchedulingFunctionSet,
    "rem",
    26,
    [](PerformanceModel* perfModel_) {
      Div_Ra_Rb(perfModel_);
    });

static SchedulingFunction* schedulingFunction_divu = new SchedulingFunction(
    RV32_OOO_SchedulingFunctionSet,
    "divu",
    27,
    [](PerformanceModel* perfModel_) {
      DivU_Ra_Rb(perfModel_);
    });

static SchedulingFunction* schedulingFunction_remu = new SchedulingFunction(
    RV32_OOO_SchedulingFunctionSet,
    "remu",
    28,
    [](PerformanceModel* perfModel_) {
      DivU_Ra_Rb(perfModel_);
    });

static SchedulingFunction* schedulingFunction_csrrw = new SchedulingFunction(
    RV32_OOO_SchedulingFunctionSet,
    "csrrw",
    29,
    [](PerformanceModel* perfModel_) {
      Csr_Ra(perfModel_);
    });

static SchedulingFunction* schedulingFunction_csrrs = new SchedulingFunction(
    RV32_OOO_SchedulingFunctionSet,
    "csrrs",
    30,
    [](PerformanceModel* perfModel_) {
      Csr_Ra(perfModel_);
    });

static SchedulingFunction* schedulingFunction_csrrc = new SchedulingFunction(
    RV32_OOO_SchedulingFunctionSet,
    "csrrc",
    31,
    [](PerformanceModel* perfModel_) {
      Csr_Ra(perfModel_);
    });

static SchedulingFunction* schedulingFunction_csrrwi = new SchedulingFunction(
    RV32_OOO_SchedulingFunctionSet,
    "csrrwi",
    32,
    [](PerformanceModel* perfModel_) {
      Csr_X(perfModel_);
    });

static SchedulingFunction* schedulingFunction_csrrsi = new SchedulingFunction(
    RV32_OOO_SchedulingFunctionSet,
    "csrrsi",
    33,
    [](PerformanceModel* perfModel_) {
      Csr_X(perfModel_);
    });

static SchedulingFunction* schedulingFunction_csrrci = new SchedulingFunction(
    RV32_OOO_SchedulingFunctionSet,
    "csrrci",
    34,
    [](PerformanceModel* perfModel_) {
      Csr_X(perfModel_);
    });

static SchedulingFunction* schedulingFunction_sb = new SchedulingFunction(
    RV32_OOO_SchedulingFunctionSet,
    "sb",
    35,
    [](PerformanceModel* perfModel_) {
      Store(perfModel_);
    });

static SchedulingFunction* schedulingFunction_sh = new SchedulingFunction(
    RV32_OOO_SchedulingFunctionSet,
    "sh",
    36,
    [](PerformanceModel* perfModel_) {
      Store(perfModel_);
    });

static SchedulingFunction* schedulingFunction_sw = new SchedulingFunction(
    RV32_OOO_SchedulingFunctionSet,
    "sw",
    37,
    [](PerformanceModel* perfModel_) {
      Store(perfModel_);
    });

static SchedulingFunction* schedulingFunction_lw = new SchedulingFunction(
    RV32_OOO_SchedulingFunctionSet,
    "lw",
    38,
    [](PerformanceModel* perfModel_) {
      Load(perfModel_);
    });

static SchedulingFunction* schedulingFunction_lh = new SchedulingFunction(
    RV32_OOO_SchedulingFunctionSet,
    "lh",
    39,
    [](PerformanceModel* perfModel_) {
      Load(perfModel_);
    });

static SchedulingFunction* schedulingFunction_lhu = new SchedulingFunction(
    RV32_OOO_SchedulingFunctionSet,
    "lhu",
    40,
    [](PerformanceModel* perfModel_) {
      Load(perfModel_);
    });

static SchedulingFunction* schedulingFunction_lb = new SchedulingFunction(
    RV32_OOO_SchedulingFunctionSet,
    "lb",
    41,
    [](PerformanceModel* perfModel_) {
      Load(perfModel_);
    });

static SchedulingFunction* schedulingFunction_lbu = new SchedulingFunction(
    RV32_OOO_SchedulingFunctionSet,
    "lbu",
    42,
    [](PerformanceModel* perfModel_) {
      Load(perfModel_);
    });

static SchedulingFunction* schedulingFunction_beq = new SchedulingFunction(
    RV32_OOO_SchedulingFunctionSet,
    "beq",
    43,
    [](PerformanceModel* perfModel_) {
      Branch_Ra_Rb(perfModel_);
    });

static SchedulingFunction* schedulingFunction_bne = new SchedulingFunction(
    RV32_OOO_SchedulingFunctionSet,
    "bne",
    44,
    [](PerformanceModel* perfModel_) {
      Branch_Ra_Rb(perfModel_);
    });

static SchedulingFunction* schedulingFunction_blt = new SchedulingFunction(
    RV32_OOO_SchedulingFunctionSet,
    "blt",
    45,
    [](PerformanceModel* perfModel_) {
      Branch_Ra_Rb(perfModel_);
    });

static SchedulingFunction* schedulingFunction_bge = new SchedulingFunction(
    RV32_OOO_SchedulingFunctionSet,
    "bge",
    46,
    [](PerformanceModel* perfModel_) {
      Branch_Ra_Rb(perfModel_);
    });

static SchedulingFunction* schedulingFunction_bltu = new SchedulingFunction(
    RV32_OOO_SchedulingFunctionSet,
    "bltu",
    47,
    [](PerformanceModel* perfModel_) {
      Branch_Ra_Rb(perfModel_);
    });

static SchedulingFunction* schedulingFunction_bgeu = new SchedulingFunction(
    RV32_OOO_SchedulingFunctionSet,
    "bgeu",
    48,
    [](PerformanceModel* perfModel_) {
      Branch_Ra_Rb(perfModel_);
    });

static SchedulingFunction* schedulingFunction__def = new SchedulingFunction(
    RV32_OOO_SchedulingFunctionSet,
    "_def",
    49,
    [](PerformanceModel* perfModel_) {
      Default_Inst(perfModel_);
    });

static SchedulingFunction* schedulingFunction_jal = new SchedulingFunction(
    RV32_OOO_SchedulingFunctionSet,
    "jal",
    50,
    [](PerformanceModel* perfModel_) {
      JAL(perfModel_);
    });

static SchedulingFunction* schedulingFunction_jalr = new SchedulingFunction(
    RV32_OOO_SchedulingFunctionSet,
    "jalr",
    51,
    [](PerformanceModel* perfModel_) {
      JALR(perfModel_);
    });

}  // namespace RV32_OOO