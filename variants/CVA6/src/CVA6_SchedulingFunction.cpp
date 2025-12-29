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

#include "CVA6_PerformanceModel.h"
#include "CVA6_uActions_Scheduling.h"
namespace CVA6 {

SchedulingFunctionSet* CVA6_SchedulingFunctionSet = new SchedulingFunctionSet("CVA6_SchedulingFunctionSet");

static SchedulingFunction* schedulingFunction__def = new SchedulingFunction(
    CVA6_SchedulingFunctionSet,
    "_def",
    0,
    [](PerformanceModel* perfModel_) {
        Default_Inst(perfModel_);
    });

static SchedulingFunction* schedulingFunction_auipc = new SchedulingFunction(
    CVA6_SchedulingFunctionSet,
    "auipc",
    1,
    [](PerformanceModel* perfModel_) {
        Arith_0(perfModel_);
    });

static SchedulingFunction* schedulingFunction_lui = new SchedulingFunction(
    CVA6_SchedulingFunctionSet,
    "lui",
    2,
    [](PerformanceModel* perfModel_) {
        Arith_0(perfModel_);
    });

static SchedulingFunction* schedulingFunction_csrrwi = new SchedulingFunction(
    CVA6_SchedulingFunctionSet,
    "csrrwi",
    3,
    [](PerformanceModel* perfModel_) {
        Arith_0(perfModel_);
    });

static SchedulingFunction* schedulingFunction_csrrsi = new SchedulingFunction(
    CVA6_SchedulingFunctionSet,
    "csrrsi",
    4,
    [](PerformanceModel* perfModel_) {
        Arith_0(perfModel_);
    });

static SchedulingFunction* schedulingFunction_csrrci = new SchedulingFunction(
    CVA6_SchedulingFunctionSet,
    "csrrci",
    5,
    [](PerformanceModel* perfModel_) {
        Arith_0(perfModel_);
    });

static SchedulingFunction* schedulingFunction_addi = new SchedulingFunction(
    CVA6_SchedulingFunctionSet,
    "addi",
    6,
    [](PerformanceModel* perfModel_) {
        Arith_Rs1(perfModel_);
    });

static SchedulingFunction* schedulingFunction_xori = new SchedulingFunction(
    CVA6_SchedulingFunctionSet,
    "xori",
    7,
    [](PerformanceModel* perfModel_) {
        Arith_Rs1(perfModel_);
    });

static SchedulingFunction* schedulingFunction_ori = new SchedulingFunction(
    CVA6_SchedulingFunctionSet,
    "ori",
    8,
    [](PerformanceModel* perfModel_) {
        Arith_Rs1(perfModel_);
    });

static SchedulingFunction* schedulingFunction_andi = new SchedulingFunction(
    CVA6_SchedulingFunctionSet,
    "andi",
    9,
    [](PerformanceModel* perfModel_) {
        Arith_Rs1(perfModel_);
    });

static SchedulingFunction* schedulingFunction_slti = new SchedulingFunction(
    CVA6_SchedulingFunctionSet,
    "slti",
    10,
    [](PerformanceModel* perfModel_) {
        Arith_Rs1(perfModel_);
    });

static SchedulingFunction* schedulingFunction_sltiu = new SchedulingFunction(
    CVA6_SchedulingFunctionSet,
    "sltiu",
    11,
    [](PerformanceModel* perfModel_) {
        Arith_Rs1(perfModel_);
    });

static SchedulingFunction* schedulingFunction_slli = new SchedulingFunction(
    CVA6_SchedulingFunctionSet,
    "slli",
    12,
    [](PerformanceModel* perfModel_) {
        Arith_Rs1(perfModel_);
    });

static SchedulingFunction* schedulingFunction_srli = new SchedulingFunction(
    CVA6_SchedulingFunctionSet,
    "srli",
    13,
    [](PerformanceModel* perfModel_) {
        Arith_Rs1(perfModel_);
    });

static SchedulingFunction* schedulingFunction_srai = new SchedulingFunction(
    CVA6_SchedulingFunctionSet,
    "srai",
    14,
    [](PerformanceModel* perfModel_) {
        Arith_Rs1(perfModel_);
    });

static SchedulingFunction* schedulingFunction_csrrw = new SchedulingFunction(
    CVA6_SchedulingFunctionSet,
    "csrrw",
    15,
    [](PerformanceModel* perfModel_) {
        Arith_Rs1(perfModel_);
    });

static SchedulingFunction* schedulingFunction_csrrs = new SchedulingFunction(
    CVA6_SchedulingFunctionSet,
    "csrrs",
    16,
    [](PerformanceModel* perfModel_) {
        Arith_Rs1(perfModel_);
    });

static SchedulingFunction* schedulingFunction_csrrc = new SchedulingFunction(
    CVA6_SchedulingFunctionSet,
    "csrrc",
    17,
    [](PerformanceModel* perfModel_) {
        Arith_Rs1(perfModel_);
    });

static SchedulingFunction* schedulingFunction_addiw = new SchedulingFunction(
    CVA6_SchedulingFunctionSet,
    "addiw",
    18,
    [](PerformanceModel* perfModel_) {
        Arith_Rs1(perfModel_);
    });

static SchedulingFunction* schedulingFunction_slliw = new SchedulingFunction(
    CVA6_SchedulingFunctionSet,
    "slliw",
    19,
    [](PerformanceModel* perfModel_) {
        Arith_Rs1(perfModel_);
    });

static SchedulingFunction* schedulingFunction_sraiw = new SchedulingFunction(
    CVA6_SchedulingFunctionSet,
    "sraiw",
    20,
    [](PerformanceModel* perfModel_) {
        Arith_Rs1(perfModel_);
    });

static SchedulingFunction* schedulingFunction_srliw = new SchedulingFunction(
    CVA6_SchedulingFunctionSet,
    "srliw",
    21,
    [](PerformanceModel* perfModel_) {
        Arith_Rs1(perfModel_);
    });

static SchedulingFunction* schedulingFunction_add = new SchedulingFunction(
    CVA6_SchedulingFunctionSet,
    "add",
    22,
    [](PerformanceModel* perfModel_) {
        Arith_Rs1_Rs2(perfModel_);
    });

static SchedulingFunction* schedulingFunction_sub = new SchedulingFunction(
    CVA6_SchedulingFunctionSet,
    "sub",
    23,
    [](PerformanceModel* perfModel_) {
        Arith_Rs1_Rs2(perfModel_);
    });

static SchedulingFunction* schedulingFunction_xor = new SchedulingFunction(
    CVA6_SchedulingFunctionSet,
    "xor",
    24,
    [](PerformanceModel* perfModel_) {
        Arith_Rs1_Rs2(perfModel_);
    });

static SchedulingFunction* schedulingFunction_or = new SchedulingFunction(
    CVA6_SchedulingFunctionSet,
    "or",
    25,
    [](PerformanceModel* perfModel_) {
        Arith_Rs1_Rs2(perfModel_);
    });

static SchedulingFunction* schedulingFunction_and = new SchedulingFunction(
    CVA6_SchedulingFunctionSet,
    "and",
    26,
    [](PerformanceModel* perfModel_) {
        Arith_Rs1_Rs2(perfModel_);
    });

static SchedulingFunction* schedulingFunction_slt = new SchedulingFunction(
    CVA6_SchedulingFunctionSet,
    "slt",
    27,
    [](PerformanceModel* perfModel_) {
        Arith_Rs1_Rs2(perfModel_);
    });

static SchedulingFunction* schedulingFunction_sltu = new SchedulingFunction(
    CVA6_SchedulingFunctionSet,
    "sltu",
    28,
    [](PerformanceModel* perfModel_) {
        Arith_Rs1_Rs2(perfModel_);
    });

static SchedulingFunction* schedulingFunction_sll = new SchedulingFunction(
    CVA6_SchedulingFunctionSet,
    "sll",
    29,
    [](PerformanceModel* perfModel_) {
        Arith_Rs1_Rs2(perfModel_);
    });

static SchedulingFunction* schedulingFunction_srl = new SchedulingFunction(
    CVA6_SchedulingFunctionSet,
    "srl",
    30,
    [](PerformanceModel* perfModel_) {
        Arith_Rs1_Rs2(perfModel_);
    });

static SchedulingFunction* schedulingFunction_sra = new SchedulingFunction(
    CVA6_SchedulingFunctionSet,
    "sra",
    31,
    [](PerformanceModel* perfModel_) {
        Arith_Rs1_Rs2(perfModel_);
    });

static SchedulingFunction* schedulingFunction_subw = new SchedulingFunction(
    CVA6_SchedulingFunctionSet,
    "subw",
    32,
    [](PerformanceModel* perfModel_) {
        Arith_Rs1_Rs2(perfModel_);
    });

static SchedulingFunction* schedulingFunction_addw = new SchedulingFunction(
    CVA6_SchedulingFunctionSet,
    "addw",
    33,
    [](PerformanceModel* perfModel_) {
        Arith_Rs1_Rs2(perfModel_);
    });

static SchedulingFunction* schedulingFunction_beq = new SchedulingFunction(
    CVA6_SchedulingFunctionSet,
    "beq",
    34,
    [](PerformanceModel* perfModel_) {
        Branch(perfModel_);
    });

static SchedulingFunction* schedulingFunction_bne = new SchedulingFunction(
    CVA6_SchedulingFunctionSet,
    "bne",
    35,
    [](PerformanceModel* perfModel_) {
        Branch(perfModel_);
    });

static SchedulingFunction* schedulingFunction_blt = new SchedulingFunction(
    CVA6_SchedulingFunctionSet,
    "blt",
    36,
    [](PerformanceModel* perfModel_) {
        Branch(perfModel_);
    });

static SchedulingFunction* schedulingFunction_bge = new SchedulingFunction(
    CVA6_SchedulingFunctionSet,
    "bge",
    37,
    [](PerformanceModel* perfModel_) {
        Branch(perfModel_);
    });

static SchedulingFunction* schedulingFunction_bltu = new SchedulingFunction(
    CVA6_SchedulingFunctionSet,
    "bltu",
    38,
    [](PerformanceModel* perfModel_) {
        Branch(perfModel_);
    });

static SchedulingFunction* schedulingFunction_bgeu = new SchedulingFunction(
    CVA6_SchedulingFunctionSet,
    "bgeu",
    39,
    [](PerformanceModel* perfModel_) {
        Branch(perfModel_);
    });

static SchedulingFunction* schedulingFunction_jal = new SchedulingFunction(
    CVA6_SchedulingFunctionSet,
    "jal",
    40,
    [](PerformanceModel* perfModel_) {
        Jump(perfModel_);
    });

static SchedulingFunction* schedulingFunction_jalr = new SchedulingFunction(
    CVA6_SchedulingFunctionSet,
    "jalr",
    41,
    [](PerformanceModel* perfModel_) {
        JumpR(perfModel_);
    });

static SchedulingFunction* schedulingFunction_mul = new SchedulingFunction(
    CVA6_SchedulingFunctionSet,
    "mul",
    42,
    [](PerformanceModel* perfModel_) {
        Mul(perfModel_);
    });

static SchedulingFunction* schedulingFunction_mulh = new SchedulingFunction(
    CVA6_SchedulingFunctionSet,
    "mulh",
    43,
    [](PerformanceModel* perfModel_) {
        Mul(perfModel_);
    });

static SchedulingFunction* schedulingFunction_mulhu = new SchedulingFunction(
    CVA6_SchedulingFunctionSet,
    "mulhu",
    44,
    [](PerformanceModel* perfModel_) {
        Mul(perfModel_);
    });

static SchedulingFunction* schedulingFunction_mulhsu = new SchedulingFunction(
    CVA6_SchedulingFunctionSet,
    "mulhsu",
    45,
    [](PerformanceModel* perfModel_) {
        Mul(perfModel_);
    });

static SchedulingFunction* schedulingFunction_mulw = new SchedulingFunction(
    CVA6_SchedulingFunctionSet,
    "mulw",
    46,
    [](PerformanceModel* perfModel_) {
        Mul(perfModel_);
    });

static SchedulingFunction* schedulingFunction_div = new SchedulingFunction(
    CVA6_SchedulingFunctionSet,
    "div",
    47,
    [](PerformanceModel* perfModel_) {
        Div(perfModel_);
    });

static SchedulingFunction* schedulingFunction_rem = new SchedulingFunction(
    CVA6_SchedulingFunctionSet,
    "rem",
    48,
    [](PerformanceModel* perfModel_) {
        Div(perfModel_);
    });

static SchedulingFunction* schedulingFunction_divw = new SchedulingFunction(
    CVA6_SchedulingFunctionSet,
    "divw",
    49,
    [](PerformanceModel* perfModel_) {
        Div(perfModel_);
    });

static SchedulingFunction* schedulingFunction_remw = new SchedulingFunction(
    CVA6_SchedulingFunctionSet,
    "remw",
    50,
    [](PerformanceModel* perfModel_) {
        Div(perfModel_);
    });

static SchedulingFunction* schedulingFunction_divu = new SchedulingFunction(
    CVA6_SchedulingFunctionSet,
    "divu",
    51,
    [](PerformanceModel* perfModel_) {
        DivU(perfModel_);
    });

static SchedulingFunction* schedulingFunction_remu = new SchedulingFunction(
    CVA6_SchedulingFunctionSet,
    "remu",
    52,
    [](PerformanceModel* perfModel_) {
        DivU(perfModel_);
    });

static SchedulingFunction* schedulingFunction_divuw = new SchedulingFunction(
    CVA6_SchedulingFunctionSet,
    "divuw",
    53,
    [](PerformanceModel* perfModel_) {
        DivU(perfModel_);
    });

static SchedulingFunction* schedulingFunction_remuw = new SchedulingFunction(
    CVA6_SchedulingFunctionSet,
    "remuw",
    54,
    [](PerformanceModel* perfModel_) {
        DivU(perfModel_);
    });

static SchedulingFunction* schedulingFunction_lw = new SchedulingFunction(
    CVA6_SchedulingFunctionSet,
    "lw",
    55,
    [](PerformanceModel* perfModel_) {
        Load(perfModel_);
    });

static SchedulingFunction* schedulingFunction_lh = new SchedulingFunction(
    CVA6_SchedulingFunctionSet,
    "lh",
    56,
    [](PerformanceModel* perfModel_) {
        Load(perfModel_);
    });

static SchedulingFunction* schedulingFunction_lhu = new SchedulingFunction(
    CVA6_SchedulingFunctionSet,
    "lhu",
    57,
    [](PerformanceModel* perfModel_) {
        Load(perfModel_);
    });

static SchedulingFunction* schedulingFunction_lb = new SchedulingFunction(
    CVA6_SchedulingFunctionSet,
    "lb",
    58,
    [](PerformanceModel* perfModel_) {
        Load(perfModel_);
    });

static SchedulingFunction* schedulingFunction_lbu = new SchedulingFunction(
    CVA6_SchedulingFunctionSet,
    "lbu",
    59,
    [](PerformanceModel* perfModel_) {
        Load(perfModel_);
    });

static SchedulingFunction* schedulingFunction_ld = new SchedulingFunction(
    CVA6_SchedulingFunctionSet,
    "ld",
    60,
    [](PerformanceModel* perfModel_) {
        Load(perfModel_);
    });

static SchedulingFunction* schedulingFunction_lwu = new SchedulingFunction(
    CVA6_SchedulingFunctionSet,
    "lwu",
    61,
    [](PerformanceModel* perfModel_) {
        Load(perfModel_);
    });

static SchedulingFunction* schedulingFunction_sb = new SchedulingFunction(
    CVA6_SchedulingFunctionSet,
    "sb",
    62,
    [](PerformanceModel* perfModel_) {
        Store(perfModel_);
    });

static SchedulingFunction* schedulingFunction_sh = new SchedulingFunction(
    CVA6_SchedulingFunctionSet,
    "sh",
    63,
    [](PerformanceModel* perfModel_) {
        Store(perfModel_);
    });

static SchedulingFunction* schedulingFunction_sw = new SchedulingFunction(
    CVA6_SchedulingFunctionSet,
    "sw",
    64,
    [](PerformanceModel* perfModel_) {
        Store(perfModel_);
    });

static SchedulingFunction* schedulingFunction_sd = new SchedulingFunction(
    CVA6_SchedulingFunctionSet,
    "sd",
    65,
    [](PerformanceModel* perfModel_) {
        Store(perfModel_);
    });

}  // namespace CVA6