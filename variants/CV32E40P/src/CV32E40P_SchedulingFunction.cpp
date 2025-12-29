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

#include "CV32E40P_PerformanceModel.h"
#include "CV32E40P_uActions_Scheduling.h"

namespace CV32E40P {

SchedulingFunctionSet* CV32E40P_SchedulingFunctionSet = new SchedulingFunctionSet("CV32E40P_SchedulingFunctionSet");

static SchedulingFunction* schedulingFunction_add = new SchedulingFunction(
    CV32E40P_SchedulingFunctionSet,
    "add",
    0,
    [](PerformanceModel* perfModel_) {
        Arith_Ra_Rb(perfModel_);
    });

static SchedulingFunction* schedulingFunction_sub = new SchedulingFunction(
    CV32E40P_SchedulingFunctionSet,
    "sub",
    1,
    [](PerformanceModel* perfModel_) {
        Arith_Ra_Rb(perfModel_);
    });

static SchedulingFunction* schedulingFunction_xor = new SchedulingFunction(
    CV32E40P_SchedulingFunctionSet,
    "xor",
    2,
    [](PerformanceModel* perfModel_) {
        Arith_Ra_Rb(perfModel_);
    });

static SchedulingFunction* schedulingFunction_or = new SchedulingFunction(
    CV32E40P_SchedulingFunctionSet,
    "or",
    3,
    [](PerformanceModel* perfModel_) {
        Arith_Ra_Rb(perfModel_);
    });

static SchedulingFunction* schedulingFunction_and = new SchedulingFunction(
    CV32E40P_SchedulingFunctionSet,
    "and",
    4,
    [](PerformanceModel* perfModel_) {
        Arith_Ra_Rb(perfModel_);
    });

static SchedulingFunction* schedulingFunction_slt = new SchedulingFunction(
    CV32E40P_SchedulingFunctionSet,
    "slt",
    5,
    [](PerformanceModel* perfModel_) {
        Arith_Ra_Rb(perfModel_);
    });

static SchedulingFunction* schedulingFunction_sltu = new SchedulingFunction(
    CV32E40P_SchedulingFunctionSet,
    "sltu",
    6,
    [](PerformanceModel* perfModel_) {
        Arith_Ra_Rb(perfModel_);
    });

static SchedulingFunction* schedulingFunction_sll = new SchedulingFunction(
    CV32E40P_SchedulingFunctionSet,
    "sll",
    7,
    [](PerformanceModel* perfModel_) {
        Arith_Ra_Rb(perfModel_);
    });

static SchedulingFunction* schedulingFunction_srl = new SchedulingFunction(
    CV32E40P_SchedulingFunctionSet,
    "srl",
    8,
    [](PerformanceModel* perfModel_) {
        Arith_Ra_Rb(perfModel_);
    });

static SchedulingFunction* schedulingFunction_sra = new SchedulingFunction(
    CV32E40P_SchedulingFunctionSet,
    "sra",
    9,
    [](PerformanceModel* perfModel_) {
        Arith_Ra_Rb(perfModel_);
    });

static SchedulingFunction* schedulingFunction_addi = new SchedulingFunction(
    CV32E40P_SchedulingFunctionSet,
    "addi",
    10,
    [](PerformanceModel* perfModel_) {
        Arith_Ra(perfModel_);
    });

static SchedulingFunction* schedulingFunction_xori = new SchedulingFunction(
    CV32E40P_SchedulingFunctionSet,
    "xori",
    11,
    [](PerformanceModel* perfModel_) {
        Arith_Ra(perfModel_);
    });

static SchedulingFunction* schedulingFunction_ori = new SchedulingFunction(
    CV32E40P_SchedulingFunctionSet,
    "ori",
    12,
    [](PerformanceModel* perfModel_) {
        Arith_Ra(perfModel_);
    });

static SchedulingFunction* schedulingFunction_andi = new SchedulingFunction(
    CV32E40P_SchedulingFunctionSet,
    "andi",
    13,
    [](PerformanceModel* perfModel_) {
        Arith_Ra(perfModel_);
    });

static SchedulingFunction* schedulingFunction_slti = new SchedulingFunction(
    CV32E40P_SchedulingFunctionSet,
    "slti",
    14,
    [](PerformanceModel* perfModel_) {
        Arith_Ra(perfModel_);
    });

static SchedulingFunction* schedulingFunction_sltiu = new SchedulingFunction(
    CV32E40P_SchedulingFunctionSet,
    "sltiu",
    15,
    [](PerformanceModel* perfModel_) {
        Arith_Ra(perfModel_);
    });

static SchedulingFunction* schedulingFunction_slli = new SchedulingFunction(
    CV32E40P_SchedulingFunctionSet,
    "slli",
    16,
    [](PerformanceModel* perfModel_) {
        Arith_Ra(perfModel_);
    });

static SchedulingFunction* schedulingFunction_srli = new SchedulingFunction(
    CV32E40P_SchedulingFunctionSet,
    "srli",
    17,
    [](PerformanceModel* perfModel_) {
        Arith_Ra(perfModel_);
    });

static SchedulingFunction* schedulingFunction_srai = new SchedulingFunction(
    CV32E40P_SchedulingFunctionSet,
    "srai",
    18,
    [](PerformanceModel* perfModel_) {
        Arith_Ra(perfModel_);
    });

static SchedulingFunction* schedulingFunction_auipc = new SchedulingFunction(
    CV32E40P_SchedulingFunctionSet,
    "auipc",
    19,
    [](PerformanceModel* perfModel_) {
        Arith_X(perfModel_);
    });

static SchedulingFunction* schedulingFunction_lui = new SchedulingFunction(
    CV32E40P_SchedulingFunctionSet,
    "lui",
    20,
    [](PerformanceModel* perfModel_) {
        Arith_X(perfModel_);
    });

static SchedulingFunction* schedulingFunction_mul = new SchedulingFunction(
    CV32E40P_SchedulingFunctionSet,
    "mul",
    21,
    [](PerformanceModel* perfModel_) {
        Mul_Ra_Rb(perfModel_);
    });

static SchedulingFunction* schedulingFunction_mulh = new SchedulingFunction(
    CV32E40P_SchedulingFunctionSet,
    "mulh",
    22,
    [](PerformanceModel* perfModel_) {
        MulH_Ra_Rb(perfModel_);
    });

static SchedulingFunction* schedulingFunction_mulhu = new SchedulingFunction(
    CV32E40P_SchedulingFunctionSet,
    "mulhu",
    23,
    [](PerformanceModel* perfModel_) {
        MulH_Ra_Rb(perfModel_);
    });

static SchedulingFunction* schedulingFunction_mulhsu = new SchedulingFunction(
    CV32E40P_SchedulingFunctionSet,
    "mulhsu",
    24,
    [](PerformanceModel* perfModel_) {
        MulH_Ra_Rb(perfModel_);
    });

static SchedulingFunction* schedulingFunction_div = new SchedulingFunction(
    CV32E40P_SchedulingFunctionSet,
    "div",
    25,
    [](PerformanceModel* perfModel_) {
        Div_Ra_Rb(perfModel_);
    });

static SchedulingFunction* schedulingFunction_rem = new SchedulingFunction(
    CV32E40P_SchedulingFunctionSet,
    "rem",
    26,
    [](PerformanceModel* perfModel_) {
        Div_Ra_Rb(perfModel_);
    });

static SchedulingFunction* schedulingFunction_divu = new SchedulingFunction(
    CV32E40P_SchedulingFunctionSet,
    "divu",
    27,
    [](PerformanceModel* perfModel_) {
        DivU_Ra_Rb(perfModel_);
    });

static SchedulingFunction* schedulingFunction_remu = new SchedulingFunction(
    CV32E40P_SchedulingFunctionSet,
    "remu",
    28,
    [](PerformanceModel* perfModel_) {
        DivU_Ra_Rb(perfModel_);
    });

static SchedulingFunction* schedulingFunction_csrrw = new SchedulingFunction(
    CV32E40P_SchedulingFunctionSet,
    "csrrw",
    29,
    [](PerformanceModel* perfModel_) {
        Csr_Ra(perfModel_);
    });

static SchedulingFunction* schedulingFunction_csrrs = new SchedulingFunction(
    CV32E40P_SchedulingFunctionSet,
    "csrrs",
    30,
    [](PerformanceModel* perfModel_) {
        Csr_Ra(perfModel_);
    });

static SchedulingFunction* schedulingFunction_csrrc = new SchedulingFunction(
    CV32E40P_SchedulingFunctionSet,
    "csrrc",
    31,
    [](PerformanceModel* perfModel_) {
        Csr_Ra(perfModel_);
    });

static SchedulingFunction* schedulingFunction_csrrwi = new SchedulingFunction(
    CV32E40P_SchedulingFunctionSet,
    "csrrwi",
    32,
    [](PerformanceModel* perfModel_) {
        Csr_X(perfModel_);
    });

static SchedulingFunction* schedulingFunction_csrrsi = new SchedulingFunction(
    CV32E40P_SchedulingFunctionSet,
    "csrrsi",
    33,
    [](PerformanceModel* perfModel_) {
        Csr_X(perfModel_);
    });

static SchedulingFunction* schedulingFunction_csrrci = new SchedulingFunction(
    CV32E40P_SchedulingFunctionSet,
    "csrrci",
    34,
    [](PerformanceModel* perfModel_) {
        Csr_X(perfModel_);
    });

static SchedulingFunction* schedulingFunction_sb = new SchedulingFunction(
    CV32E40P_SchedulingFunctionSet,
    "sb",
    35,
    [](PerformanceModel* perfModel_) {
        Store(perfModel_);
    });

static SchedulingFunction* schedulingFunction_sh = new SchedulingFunction(
    CV32E40P_SchedulingFunctionSet,
    "sh",
    36,
    [](PerformanceModel* perfModel_) {
        Store(perfModel_);
    });

static SchedulingFunction* schedulingFunction_sw = new SchedulingFunction(
    CV32E40P_SchedulingFunctionSet,
    "sw",
    37,
    [](PerformanceModel* perfModel_) {
        Store(perfModel_);
    });

static SchedulingFunction* schedulingFunction_lw = new SchedulingFunction(
    CV32E40P_SchedulingFunctionSet,
    "lw",
    38,
    [](PerformanceModel* perfModel_) {
        Load(perfModel_);
    });

static SchedulingFunction* schedulingFunction_lh = new SchedulingFunction(
    CV32E40P_SchedulingFunctionSet,
    "lh",
    39,
    [](PerformanceModel* perfModel_) {
        Load(perfModel_);
    });

static SchedulingFunction* schedulingFunction_lhu = new SchedulingFunction(
    CV32E40P_SchedulingFunctionSet,
    "lhu",
    40,
    [](PerformanceModel* perfModel_) {
        Load(perfModel_);
    });

static SchedulingFunction* schedulingFunction_lb = new SchedulingFunction(
    CV32E40P_SchedulingFunctionSet,
    "lb",
    41,
    [](PerformanceModel* perfModel_) {
        Load(perfModel_);
    });

static SchedulingFunction* schedulingFunction_lbu = new SchedulingFunction(
    CV32E40P_SchedulingFunctionSet,
    "lbu",
    42,
    [](PerformanceModel* perfModel_) {
        Load(perfModel_);
    });

static SchedulingFunction* schedulingFunction_beq = new SchedulingFunction(
    CV32E40P_SchedulingFunctionSet,
    "beq",
    43,
    [](PerformanceModel* perfModel_) {
        Branch_Ra_Rb(perfModel_);
    });

static SchedulingFunction* schedulingFunction_bne = new SchedulingFunction(
    CV32E40P_SchedulingFunctionSet,
    "bne",
    44,
    [](PerformanceModel* perfModel_) {
        Branch_Ra_Rb(perfModel_);
    });

static SchedulingFunction* schedulingFunction_blt = new SchedulingFunction(
    CV32E40P_SchedulingFunctionSet,
    "blt",
    45,
    [](PerformanceModel* perfModel_) {
        Branch_Ra_Rb(perfModel_);
    });

static SchedulingFunction* schedulingFunction_bge = new SchedulingFunction(
    CV32E40P_SchedulingFunctionSet,
    "bge",
    46,
    [](PerformanceModel* perfModel_) {
        Branch_Ra_Rb(perfModel_);
    });

static SchedulingFunction* schedulingFunction_bltu = new SchedulingFunction(
    CV32E40P_SchedulingFunctionSet,
    "bltu",
    47,
    [](PerformanceModel* perfModel_) {
        Branch_Ra_Rb(perfModel_);
    });

static SchedulingFunction* schedulingFunction_bgeu = new SchedulingFunction(
    CV32E40P_SchedulingFunctionSet,
    "bgeu",
    48,
    [](PerformanceModel* perfModel_) {
        Branch_Ra_Rb(perfModel_);
    });

static SchedulingFunction* schedulingFunction__def = new SchedulingFunction(
    CV32E40P_SchedulingFunctionSet,
    "_def",
    49,
    [](PerformanceModel* perfModel_) {
        Default_Inst(perfModel_);
    });

static SchedulingFunction* schedulingFunction_jal = new SchedulingFunction(
    CV32E40P_SchedulingFunctionSet,
    "jal",
    50,
    [](PerformanceModel* perfModel_) {
        JAL(perfModel_);
    });

static SchedulingFunction* schedulingFunction_jalr = new SchedulingFunction(
    CV32E40P_SchedulingFunctionSet,
    "jalr",
    51,
    [](PerformanceModel* perfModel_) {
        JALR(perfModel_);
    });

}  // namespace CV32E40P