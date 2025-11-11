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

namespace RV32_OOO{

SchedulingFunctionSet* RV32_OOO_SchedulingFunctionSet = new SchedulingFunctionSet("RV32_OOO_SchedulingFunctionSet");

static SchedulingFunction *schedulingFunction_add = new SchedulingFunction(
  RV32_OOO_SchedulingFunctionSet,
  "add",
  0,
  [](PerformanceModel* perfModel_){
  RV32_OOO_PerformanceModel* perfModel = static_cast<RV32_OOO_PerformanceModel*>(perfModel_);
  // Enter
uint64_t n_Enter = perfModel->PC_stage;
// PCGen
uint64_t n_PCGen;
uint64_t n_PCGen_max;
n_PCGen_max = std::max({n_Enter, perfModel->noBranchPredModel.getPc()});
n_PCGen = n_PCGen_max + 1;
perfModel->noBranchPredModel.setPc_p(n_PCGen);
// PC_stage
uint64_t n_PC_stage;
n_PC_stage = std::max({n_PCGen, perfModel->IF_stage});
perfModel->PC_stage = n_PC_stage;
// IPort_R
uint64_t n_IPort_R;
n_IPort_R = n_PC_stage + 1;
// uA_Clobber
uint64_t n_uA_Clobber;
n_uA_Clobber = std::max({n_PC_stage, perfModel->clobberModel.getCb_out()});
// IF_stage
uint64_t n_IF_stage;
n_IF_stage = std::max({n_IPort_R, n_uA_Clobber, perfModel->IS_stage});
perfModel->IF_stage = n_IF_stage;
// Decoder
uint64_t n_Decoder;
n_Decoder = n_IF_stage + 1;
perfModel->scheduleModel.setDec_alu(n_Decoder);
// IS_stage
uint64_t n_IS_stage;
n_IS_stage = std::max({n_Decoder, perfModel->IB_stage_OoO.get_min()});
perfModel->IS_stage = n_IS_stage;
// uA_OF_A
uint64_t n_uA_OF_A;
n_uA_OF_A = std::max({n_IS_stage, perfModel->scheduleModel.getXa()});
// uA_OF_B
uint64_t n_uA_OF_B;
n_uA_OF_B = std::max({n_IS_stage, perfModel->scheduleModel.getXb()});
// uA_Issue
uint64_t n_uA_Issue;
n_uA_Issue = std::max({n_IS_stage, perfModel->scheduleModel.getT_issue()});
// IB_stage_OoO
uint64_t n_IB_stage_OoO;
n_IB_stage_OoO = std::max({n_uA_OF_A, n_uA_OF_B, n_uA_Issue});
perfModel->IB_stage_OoO.replace_min(n_IB_stage_OoO);
// ALU
uint64_t n_ALU;
n_ALU = n_IB_stage_OoO + 1;
perfModel->scheduleModel.setXd(n_ALU);
perfModel->clobberModel.setCb_inRd(n_ALU);
perfModel->clobberModel.setCb_inR1(n_ALU);
perfModel->clobberModel.setCb_inR2(n_ALU);
// EX_stage_alu_NoB
uint64_t n_EX_stage_alu_NoB = n_ALU;
perfModel->EX_stage_alu_NoB = n_EX_stage_alu_NoB;
// WB
uint64_t n_WB;
n_WB = n_EX_stage_alu_NoB + 1;
perfModel->scheduleModel.setT_wb(n_WB);
// WB_stage_NoB
uint64_t n_WB_stage_NoB = n_WB;
perfModel->WB_stage_NoB.set(n_WB_stage_NoB);

  // Dump Entrance point for info print (tracing)
  perfModel->entrancePoint = n_Enter;
  }
);

static SchedulingFunction *schedulingFunction_sub = new SchedulingFunction(
  RV32_OOO_SchedulingFunctionSet,
  "sub",
  1,
  [](PerformanceModel* perfModel_){
  RV32_OOO_PerformanceModel* perfModel = static_cast<RV32_OOO_PerformanceModel*>(perfModel_);
  // Enter
uint64_t n_Enter = perfModel->PC_stage;
// PCGen
uint64_t n_PCGen;
uint64_t n_PCGen_max;
n_PCGen_max = std::max({n_Enter, perfModel->noBranchPredModel.getPc()});
n_PCGen = n_PCGen_max + 1;
perfModel->noBranchPredModel.setPc_p(n_PCGen);
// PC_stage
uint64_t n_PC_stage;
n_PC_stage = std::max({n_PCGen, perfModel->IF_stage});
perfModel->PC_stage = n_PC_stage;
// IPort_R
uint64_t n_IPort_R;
n_IPort_R = n_PC_stage + 1;
// uA_Clobber
uint64_t n_uA_Clobber;
n_uA_Clobber = std::max({n_PC_stage, perfModel->clobberModel.getCb_out()});
// IF_stage
uint64_t n_IF_stage;
n_IF_stage = std::max({n_IPort_R, n_uA_Clobber, perfModel->IS_stage});
perfModel->IF_stage = n_IF_stage;
// Decoder
uint64_t n_Decoder;
n_Decoder = n_IF_stage + 1;
perfModel->scheduleModel.setDec_alu(n_Decoder);
// IS_stage
uint64_t n_IS_stage;
n_IS_stage = std::max({n_Decoder, perfModel->IB_stage_OoO.get_min()});
perfModel->IS_stage = n_IS_stage;
// uA_OF_A
uint64_t n_uA_OF_A;
n_uA_OF_A = std::max({n_IS_stage, perfModel->scheduleModel.getXa()});
// uA_OF_B
uint64_t n_uA_OF_B;
n_uA_OF_B = std::max({n_IS_stage, perfModel->scheduleModel.getXb()});
// uA_Issue
uint64_t n_uA_Issue;
n_uA_Issue = std::max({n_IS_stage, perfModel->scheduleModel.getT_issue()});
// IB_stage_OoO
uint64_t n_IB_stage_OoO;
n_IB_stage_OoO = std::max({n_uA_OF_A, n_uA_OF_B, n_uA_Issue});
perfModel->IB_stage_OoO.replace_min(n_IB_stage_OoO);
// ALU
uint64_t n_ALU;
n_ALU = n_IB_stage_OoO + 1;
perfModel->scheduleModel.setXd(n_ALU);
perfModel->clobberModel.setCb_inRd(n_ALU);
perfModel->clobberModel.setCb_inR1(n_ALU);
perfModel->clobberModel.setCb_inR2(n_ALU);
// EX_stage_alu_NoB
uint64_t n_EX_stage_alu_NoB = n_ALU;
perfModel->EX_stage_alu_NoB = n_EX_stage_alu_NoB;
// WB
uint64_t n_WB;
n_WB = n_EX_stage_alu_NoB + 1;
perfModel->scheduleModel.setT_wb(n_WB);
// WB_stage_NoB
uint64_t n_WB_stage_NoB = n_WB;
perfModel->WB_stage_NoB.set(n_WB_stage_NoB);

  // Dump Entrance point for info print (tracing)
  perfModel->entrancePoint = n_Enter;
  }
);

static SchedulingFunction *schedulingFunction_xor = new SchedulingFunction(
  RV32_OOO_SchedulingFunctionSet,
  "xor",
  2,
  [](PerformanceModel* perfModel_){
  RV32_OOO_PerformanceModel* perfModel = static_cast<RV32_OOO_PerformanceModel*>(perfModel_);
  // Enter
uint64_t n_Enter = perfModel->PC_stage;
// PCGen
uint64_t n_PCGen;
uint64_t n_PCGen_max;
n_PCGen_max = std::max({n_Enter, perfModel->noBranchPredModel.getPc()});
n_PCGen = n_PCGen_max + 1;
perfModel->noBranchPredModel.setPc_p(n_PCGen);
// PC_stage
uint64_t n_PC_stage;
n_PC_stage = std::max({n_PCGen, perfModel->IF_stage});
perfModel->PC_stage = n_PC_stage;
// IPort_R
uint64_t n_IPort_R;
n_IPort_R = n_PC_stage + 1;
// uA_Clobber
uint64_t n_uA_Clobber;
n_uA_Clobber = std::max({n_PC_stage, perfModel->clobberModel.getCb_out()});
// IF_stage
uint64_t n_IF_stage;
n_IF_stage = std::max({n_IPort_R, n_uA_Clobber, perfModel->IS_stage});
perfModel->IF_stage = n_IF_stage;
// Decoder
uint64_t n_Decoder;
n_Decoder = n_IF_stage + 1;
perfModel->scheduleModel.setDec_alu(n_Decoder);
// IS_stage
uint64_t n_IS_stage;
n_IS_stage = std::max({n_Decoder, perfModel->IB_stage_OoO.get_min()});
perfModel->IS_stage = n_IS_stage;
// uA_OF_A
uint64_t n_uA_OF_A;
n_uA_OF_A = std::max({n_IS_stage, perfModel->scheduleModel.getXa()});
// uA_OF_B
uint64_t n_uA_OF_B;
n_uA_OF_B = std::max({n_IS_stage, perfModel->scheduleModel.getXb()});
// uA_Issue
uint64_t n_uA_Issue;
n_uA_Issue = std::max({n_IS_stage, perfModel->scheduleModel.getT_issue()});
// IB_stage_OoO
uint64_t n_IB_stage_OoO;
n_IB_stage_OoO = std::max({n_uA_OF_A, n_uA_OF_B, n_uA_Issue});
perfModel->IB_stage_OoO.replace_min(n_IB_stage_OoO);
// ALU
uint64_t n_ALU;
n_ALU = n_IB_stage_OoO + 1;
perfModel->scheduleModel.setXd(n_ALU);
perfModel->clobberModel.setCb_inRd(n_ALU);
perfModel->clobberModel.setCb_inR1(n_ALU);
perfModel->clobberModel.setCb_inR2(n_ALU);
// EX_stage_alu_NoB
uint64_t n_EX_stage_alu_NoB = n_ALU;
perfModel->EX_stage_alu_NoB = n_EX_stage_alu_NoB;
// WB
uint64_t n_WB;
n_WB = n_EX_stage_alu_NoB + 1;
perfModel->scheduleModel.setT_wb(n_WB);
// WB_stage_NoB
uint64_t n_WB_stage_NoB = n_WB;
perfModel->WB_stage_NoB.set(n_WB_stage_NoB);

  // Dump Entrance point for info print (tracing)
  perfModel->entrancePoint = n_Enter;
  }
);

static SchedulingFunction *schedulingFunction_or = new SchedulingFunction(
  RV32_OOO_SchedulingFunctionSet,
  "or",
  3,
  [](PerformanceModel* perfModel_){
  RV32_OOO_PerformanceModel* perfModel = static_cast<RV32_OOO_PerformanceModel*>(perfModel_);
  // Enter
uint64_t n_Enter = perfModel->PC_stage;
// PCGen
uint64_t n_PCGen;
uint64_t n_PCGen_max;
n_PCGen_max = std::max({n_Enter, perfModel->noBranchPredModel.getPc()});
n_PCGen = n_PCGen_max + 1;
perfModel->noBranchPredModel.setPc_p(n_PCGen);
// PC_stage
uint64_t n_PC_stage;
n_PC_stage = std::max({n_PCGen, perfModel->IF_stage});
perfModel->PC_stage = n_PC_stage;
// IPort_R
uint64_t n_IPort_R;
n_IPort_R = n_PC_stage + 1;
// uA_Clobber
uint64_t n_uA_Clobber;
n_uA_Clobber = std::max({n_PC_stage, perfModel->clobberModel.getCb_out()});
// IF_stage
uint64_t n_IF_stage;
n_IF_stage = std::max({n_IPort_R, n_uA_Clobber, perfModel->IS_stage});
perfModel->IF_stage = n_IF_stage;
// Decoder
uint64_t n_Decoder;
n_Decoder = n_IF_stage + 1;
perfModel->scheduleModel.setDec_alu(n_Decoder);
// IS_stage
uint64_t n_IS_stage;
n_IS_stage = std::max({n_Decoder, perfModel->IB_stage_OoO.get_min()});
perfModel->IS_stage = n_IS_stage;
// uA_OF_A
uint64_t n_uA_OF_A;
n_uA_OF_A = std::max({n_IS_stage, perfModel->scheduleModel.getXa()});
// uA_OF_B
uint64_t n_uA_OF_B;
n_uA_OF_B = std::max({n_IS_stage, perfModel->scheduleModel.getXb()});
// uA_Issue
uint64_t n_uA_Issue;
n_uA_Issue = std::max({n_IS_stage, perfModel->scheduleModel.getT_issue()});
// IB_stage_OoO
uint64_t n_IB_stage_OoO;
n_IB_stage_OoO = std::max({n_uA_OF_A, n_uA_OF_B, n_uA_Issue});
perfModel->IB_stage_OoO.replace_min(n_IB_stage_OoO);
// ALU
uint64_t n_ALU;
n_ALU = n_IB_stage_OoO + 1;
perfModel->scheduleModel.setXd(n_ALU);
perfModel->clobberModel.setCb_inRd(n_ALU);
perfModel->clobberModel.setCb_inR1(n_ALU);
perfModel->clobberModel.setCb_inR2(n_ALU);
// EX_stage_alu_NoB
uint64_t n_EX_stage_alu_NoB = n_ALU;
perfModel->EX_stage_alu_NoB = n_EX_stage_alu_NoB;
// WB
uint64_t n_WB;
n_WB = n_EX_stage_alu_NoB + 1;
perfModel->scheduleModel.setT_wb(n_WB);
// WB_stage_NoB
uint64_t n_WB_stage_NoB = n_WB;
perfModel->WB_stage_NoB.set(n_WB_stage_NoB);

  // Dump Entrance point for info print (tracing)
  perfModel->entrancePoint = n_Enter;
  }
);

static SchedulingFunction *schedulingFunction_and = new SchedulingFunction(
  RV32_OOO_SchedulingFunctionSet,
  "and",
  4,
  [](PerformanceModel* perfModel_){
  RV32_OOO_PerformanceModel* perfModel = static_cast<RV32_OOO_PerformanceModel*>(perfModel_);
  // Enter
uint64_t n_Enter = perfModel->PC_stage;
// PCGen
uint64_t n_PCGen;
uint64_t n_PCGen_max;
n_PCGen_max = std::max({n_Enter, perfModel->noBranchPredModel.getPc()});
n_PCGen = n_PCGen_max + 1;
perfModel->noBranchPredModel.setPc_p(n_PCGen);
// PC_stage
uint64_t n_PC_stage;
n_PC_stage = std::max({n_PCGen, perfModel->IF_stage});
perfModel->PC_stage = n_PC_stage;
// IPort_R
uint64_t n_IPort_R;
n_IPort_R = n_PC_stage + 1;
// uA_Clobber
uint64_t n_uA_Clobber;
n_uA_Clobber = std::max({n_PC_stage, perfModel->clobberModel.getCb_out()});
// IF_stage
uint64_t n_IF_stage;
n_IF_stage = std::max({n_IPort_R, n_uA_Clobber, perfModel->IS_stage});
perfModel->IF_stage = n_IF_stage;
// Decoder
uint64_t n_Decoder;
n_Decoder = n_IF_stage + 1;
perfModel->scheduleModel.setDec_alu(n_Decoder);
// IS_stage
uint64_t n_IS_stage;
n_IS_stage = std::max({n_Decoder, perfModel->IB_stage_OoO.get_min()});
perfModel->IS_stage = n_IS_stage;
// uA_OF_A
uint64_t n_uA_OF_A;
n_uA_OF_A = std::max({n_IS_stage, perfModel->scheduleModel.getXa()});
// uA_OF_B
uint64_t n_uA_OF_B;
n_uA_OF_B = std::max({n_IS_stage, perfModel->scheduleModel.getXb()});
// uA_Issue
uint64_t n_uA_Issue;
n_uA_Issue = std::max({n_IS_stage, perfModel->scheduleModel.getT_issue()});
// IB_stage_OoO
uint64_t n_IB_stage_OoO;
n_IB_stage_OoO = std::max({n_uA_OF_A, n_uA_OF_B, n_uA_Issue});
perfModel->IB_stage_OoO.replace_min(n_IB_stage_OoO);
// ALU
uint64_t n_ALU;
n_ALU = n_IB_stage_OoO + 1;
perfModel->scheduleModel.setXd(n_ALU);
perfModel->clobberModel.setCb_inRd(n_ALU);
perfModel->clobberModel.setCb_inR1(n_ALU);
perfModel->clobberModel.setCb_inR2(n_ALU);
// EX_stage_alu_NoB
uint64_t n_EX_stage_alu_NoB = n_ALU;
perfModel->EX_stage_alu_NoB = n_EX_stage_alu_NoB;
// WB
uint64_t n_WB;
n_WB = n_EX_stage_alu_NoB + 1;
perfModel->scheduleModel.setT_wb(n_WB);
// WB_stage_NoB
uint64_t n_WB_stage_NoB = n_WB;
perfModel->WB_stage_NoB.set(n_WB_stage_NoB);

  // Dump Entrance point for info print (tracing)
  perfModel->entrancePoint = n_Enter;
  }
);

static SchedulingFunction *schedulingFunction_slt = new SchedulingFunction(
  RV32_OOO_SchedulingFunctionSet,
  "slt",
  5,
  [](PerformanceModel* perfModel_){
  RV32_OOO_PerformanceModel* perfModel = static_cast<RV32_OOO_PerformanceModel*>(perfModel_);
  // Enter
uint64_t n_Enter = perfModel->PC_stage;
// PCGen
uint64_t n_PCGen;
uint64_t n_PCGen_max;
n_PCGen_max = std::max({n_Enter, perfModel->noBranchPredModel.getPc()});
n_PCGen = n_PCGen_max + 1;
perfModel->noBranchPredModel.setPc_p(n_PCGen);
// PC_stage
uint64_t n_PC_stage;
n_PC_stage = std::max({n_PCGen, perfModel->IF_stage});
perfModel->PC_stage = n_PC_stage;
// IPort_R
uint64_t n_IPort_R;
n_IPort_R = n_PC_stage + 1;
// uA_Clobber
uint64_t n_uA_Clobber;
n_uA_Clobber = std::max({n_PC_stage, perfModel->clobberModel.getCb_out()});
// IF_stage
uint64_t n_IF_stage;
n_IF_stage = std::max({n_IPort_R, n_uA_Clobber, perfModel->IS_stage});
perfModel->IF_stage = n_IF_stage;
// Decoder
uint64_t n_Decoder;
n_Decoder = n_IF_stage + 1;
perfModel->scheduleModel.setDec_alu(n_Decoder);
// IS_stage
uint64_t n_IS_stage;
n_IS_stage = std::max({n_Decoder, perfModel->IB_stage_OoO.get_min()});
perfModel->IS_stage = n_IS_stage;
// uA_OF_A
uint64_t n_uA_OF_A;
n_uA_OF_A = std::max({n_IS_stage, perfModel->scheduleModel.getXa()});
// uA_OF_B
uint64_t n_uA_OF_B;
n_uA_OF_B = std::max({n_IS_stage, perfModel->scheduleModel.getXb()});
// uA_Issue
uint64_t n_uA_Issue;
n_uA_Issue = std::max({n_IS_stage, perfModel->scheduleModel.getT_issue()});
// IB_stage_OoO
uint64_t n_IB_stage_OoO;
n_IB_stage_OoO = std::max({n_uA_OF_A, n_uA_OF_B, n_uA_Issue});
perfModel->IB_stage_OoO.replace_min(n_IB_stage_OoO);
// ALU
uint64_t n_ALU;
n_ALU = n_IB_stage_OoO + 1;
perfModel->scheduleModel.setXd(n_ALU);
perfModel->clobberModel.setCb_inRd(n_ALU);
perfModel->clobberModel.setCb_inR1(n_ALU);
perfModel->clobberModel.setCb_inR2(n_ALU);
// EX_stage_alu_NoB
uint64_t n_EX_stage_alu_NoB = n_ALU;
perfModel->EX_stage_alu_NoB = n_EX_stage_alu_NoB;
// WB
uint64_t n_WB;
n_WB = n_EX_stage_alu_NoB + 1;
perfModel->scheduleModel.setT_wb(n_WB);
// WB_stage_NoB
uint64_t n_WB_stage_NoB = n_WB;
perfModel->WB_stage_NoB.set(n_WB_stage_NoB);

  // Dump Entrance point for info print (tracing)
  perfModel->entrancePoint = n_Enter;
  }
);

static SchedulingFunction *schedulingFunction_sltu = new SchedulingFunction(
  RV32_OOO_SchedulingFunctionSet,
  "sltu",
  6,
  [](PerformanceModel* perfModel_){
  RV32_OOO_PerformanceModel* perfModel = static_cast<RV32_OOO_PerformanceModel*>(perfModel_);
  // Enter
uint64_t n_Enter = perfModel->PC_stage;
// PCGen
uint64_t n_PCGen;
uint64_t n_PCGen_max;
n_PCGen_max = std::max({n_Enter, perfModel->noBranchPredModel.getPc()});
n_PCGen = n_PCGen_max + 1;
perfModel->noBranchPredModel.setPc_p(n_PCGen);
// PC_stage
uint64_t n_PC_stage;
n_PC_stage = std::max({n_PCGen, perfModel->IF_stage});
perfModel->PC_stage = n_PC_stage;
// IPort_R
uint64_t n_IPort_R;
n_IPort_R = n_PC_stage + 1;
// uA_Clobber
uint64_t n_uA_Clobber;
n_uA_Clobber = std::max({n_PC_stage, perfModel->clobberModel.getCb_out()});
// IF_stage
uint64_t n_IF_stage;
n_IF_stage = std::max({n_IPort_R, n_uA_Clobber, perfModel->IS_stage});
perfModel->IF_stage = n_IF_stage;
// Decoder
uint64_t n_Decoder;
n_Decoder = n_IF_stage + 1;
perfModel->scheduleModel.setDec_alu(n_Decoder);
// IS_stage
uint64_t n_IS_stage;
n_IS_stage = std::max({n_Decoder, perfModel->IB_stage_OoO.get_min()});
perfModel->IS_stage = n_IS_stage;
// uA_OF_A
uint64_t n_uA_OF_A;
n_uA_OF_A = std::max({n_IS_stage, perfModel->scheduleModel.getXa()});
// uA_OF_B
uint64_t n_uA_OF_B;
n_uA_OF_B = std::max({n_IS_stage, perfModel->scheduleModel.getXb()});
// uA_Issue
uint64_t n_uA_Issue;
n_uA_Issue = std::max({n_IS_stage, perfModel->scheduleModel.getT_issue()});
// IB_stage_OoO
uint64_t n_IB_stage_OoO;
n_IB_stage_OoO = std::max({n_uA_OF_A, n_uA_OF_B, n_uA_Issue});
perfModel->IB_stage_OoO.replace_min(n_IB_stage_OoO);
// ALU
uint64_t n_ALU;
n_ALU = n_IB_stage_OoO + 1;
perfModel->scheduleModel.setXd(n_ALU);
perfModel->clobberModel.setCb_inRd(n_ALU);
perfModel->clobberModel.setCb_inR1(n_ALU);
perfModel->clobberModel.setCb_inR2(n_ALU);
// EX_stage_alu_NoB
uint64_t n_EX_stage_alu_NoB = n_ALU;
perfModel->EX_stage_alu_NoB = n_EX_stage_alu_NoB;
// WB
uint64_t n_WB;
n_WB = n_EX_stage_alu_NoB + 1;
perfModel->scheduleModel.setT_wb(n_WB);
// WB_stage_NoB
uint64_t n_WB_stage_NoB = n_WB;
perfModel->WB_stage_NoB.set(n_WB_stage_NoB);

  // Dump Entrance point for info print (tracing)
  perfModel->entrancePoint = n_Enter;
  }
);

static SchedulingFunction *schedulingFunction_sll = new SchedulingFunction(
  RV32_OOO_SchedulingFunctionSet,
  "sll",
  7,
  [](PerformanceModel* perfModel_){
  RV32_OOO_PerformanceModel* perfModel = static_cast<RV32_OOO_PerformanceModel*>(perfModel_);
  // Enter
uint64_t n_Enter = perfModel->PC_stage;
// PCGen
uint64_t n_PCGen;
uint64_t n_PCGen_max;
n_PCGen_max = std::max({n_Enter, perfModel->noBranchPredModel.getPc()});
n_PCGen = n_PCGen_max + 1;
perfModel->noBranchPredModel.setPc_p(n_PCGen);
// PC_stage
uint64_t n_PC_stage;
n_PC_stage = std::max({n_PCGen, perfModel->IF_stage});
perfModel->PC_stage = n_PC_stage;
// IPort_R
uint64_t n_IPort_R;
n_IPort_R = n_PC_stage + 1;
// uA_Clobber
uint64_t n_uA_Clobber;
n_uA_Clobber = std::max({n_PC_stage, perfModel->clobberModel.getCb_out()});
// IF_stage
uint64_t n_IF_stage;
n_IF_stage = std::max({n_IPort_R, n_uA_Clobber, perfModel->IS_stage});
perfModel->IF_stage = n_IF_stage;
// Decoder
uint64_t n_Decoder;
n_Decoder = n_IF_stage + 1;
perfModel->scheduleModel.setDec_alu(n_Decoder);
// IS_stage
uint64_t n_IS_stage;
n_IS_stage = std::max({n_Decoder, perfModel->IB_stage_OoO.get_min()});
perfModel->IS_stage = n_IS_stage;
// uA_OF_A
uint64_t n_uA_OF_A;
n_uA_OF_A = std::max({n_IS_stage, perfModel->scheduleModel.getXa()});
// uA_OF_B
uint64_t n_uA_OF_B;
n_uA_OF_B = std::max({n_IS_stage, perfModel->scheduleModel.getXb()});
// uA_Issue
uint64_t n_uA_Issue;
n_uA_Issue = std::max({n_IS_stage, perfModel->scheduleModel.getT_issue()});
// IB_stage_OoO
uint64_t n_IB_stage_OoO;
n_IB_stage_OoO = std::max({n_uA_OF_A, n_uA_OF_B, n_uA_Issue});
perfModel->IB_stage_OoO.replace_min(n_IB_stage_OoO);
// ALU
uint64_t n_ALU;
n_ALU = n_IB_stage_OoO + 1;
perfModel->scheduleModel.setXd(n_ALU);
perfModel->clobberModel.setCb_inRd(n_ALU);
perfModel->clobberModel.setCb_inR1(n_ALU);
perfModel->clobberModel.setCb_inR2(n_ALU);
// EX_stage_alu_NoB
uint64_t n_EX_stage_alu_NoB = n_ALU;
perfModel->EX_stage_alu_NoB = n_EX_stage_alu_NoB;
// WB
uint64_t n_WB;
n_WB = n_EX_stage_alu_NoB + 1;
perfModel->scheduleModel.setT_wb(n_WB);
// WB_stage_NoB
uint64_t n_WB_stage_NoB = n_WB;
perfModel->WB_stage_NoB.set(n_WB_stage_NoB);

  // Dump Entrance point for info print (tracing)
  perfModel->entrancePoint = n_Enter;
  }
);

static SchedulingFunction *schedulingFunction_srl = new SchedulingFunction(
  RV32_OOO_SchedulingFunctionSet,
  "srl",
  8,
  [](PerformanceModel* perfModel_){
  RV32_OOO_PerformanceModel* perfModel = static_cast<RV32_OOO_PerformanceModel*>(perfModel_);
  // Enter
uint64_t n_Enter = perfModel->PC_stage;
// PCGen
uint64_t n_PCGen;
uint64_t n_PCGen_max;
n_PCGen_max = std::max({n_Enter, perfModel->noBranchPredModel.getPc()});
n_PCGen = n_PCGen_max + 1;
perfModel->noBranchPredModel.setPc_p(n_PCGen);
// PC_stage
uint64_t n_PC_stage;
n_PC_stage = std::max({n_PCGen, perfModel->IF_stage});
perfModel->PC_stage = n_PC_stage;
// IPort_R
uint64_t n_IPort_R;
n_IPort_R = n_PC_stage + 1;
// uA_Clobber
uint64_t n_uA_Clobber;
n_uA_Clobber = std::max({n_PC_stage, perfModel->clobberModel.getCb_out()});
// IF_stage
uint64_t n_IF_stage;
n_IF_stage = std::max({n_IPort_R, n_uA_Clobber, perfModel->IS_stage});
perfModel->IF_stage = n_IF_stage;
// Decoder
uint64_t n_Decoder;
n_Decoder = n_IF_stage + 1;
perfModel->scheduleModel.setDec_alu(n_Decoder);
// IS_stage
uint64_t n_IS_stage;
n_IS_stage = std::max({n_Decoder, perfModel->IB_stage_OoO.get_min()});
perfModel->IS_stage = n_IS_stage;
// uA_OF_A
uint64_t n_uA_OF_A;
n_uA_OF_A = std::max({n_IS_stage, perfModel->scheduleModel.getXa()});
// uA_OF_B
uint64_t n_uA_OF_B;
n_uA_OF_B = std::max({n_IS_stage, perfModel->scheduleModel.getXb()});
// uA_Issue
uint64_t n_uA_Issue;
n_uA_Issue = std::max({n_IS_stage, perfModel->scheduleModel.getT_issue()});
// IB_stage_OoO
uint64_t n_IB_stage_OoO;
n_IB_stage_OoO = std::max({n_uA_OF_A, n_uA_OF_B, n_uA_Issue});
perfModel->IB_stage_OoO.replace_min(n_IB_stage_OoO);
// ALU
uint64_t n_ALU;
n_ALU = n_IB_stage_OoO + 1;
perfModel->scheduleModel.setXd(n_ALU);
perfModel->clobberModel.setCb_inRd(n_ALU);
perfModel->clobberModel.setCb_inR1(n_ALU);
perfModel->clobberModel.setCb_inR2(n_ALU);
// EX_stage_alu_NoB
uint64_t n_EX_stage_alu_NoB = n_ALU;
perfModel->EX_stage_alu_NoB = n_EX_stage_alu_NoB;
// WB
uint64_t n_WB;
n_WB = n_EX_stage_alu_NoB + 1;
perfModel->scheduleModel.setT_wb(n_WB);
// WB_stage_NoB
uint64_t n_WB_stage_NoB = n_WB;
perfModel->WB_stage_NoB.set(n_WB_stage_NoB);

  // Dump Entrance point for info print (tracing)
  perfModel->entrancePoint = n_Enter;
  }
);

static SchedulingFunction *schedulingFunction_sra = new SchedulingFunction(
  RV32_OOO_SchedulingFunctionSet,
  "sra",
  9,
  [](PerformanceModel* perfModel_){
  RV32_OOO_PerformanceModel* perfModel = static_cast<RV32_OOO_PerformanceModel*>(perfModel_);
  // Enter
uint64_t n_Enter = perfModel->PC_stage;
// PCGen
uint64_t n_PCGen;
uint64_t n_PCGen_max;
n_PCGen_max = std::max({n_Enter, perfModel->noBranchPredModel.getPc()});
n_PCGen = n_PCGen_max + 1;
perfModel->noBranchPredModel.setPc_p(n_PCGen);
// PC_stage
uint64_t n_PC_stage;
n_PC_stage = std::max({n_PCGen, perfModel->IF_stage});
perfModel->PC_stage = n_PC_stage;
// IPort_R
uint64_t n_IPort_R;
n_IPort_R = n_PC_stage + 1;
// uA_Clobber
uint64_t n_uA_Clobber;
n_uA_Clobber = std::max({n_PC_stage, perfModel->clobberModel.getCb_out()});
// IF_stage
uint64_t n_IF_stage;
n_IF_stage = std::max({n_IPort_R, n_uA_Clobber, perfModel->IS_stage});
perfModel->IF_stage = n_IF_stage;
// Decoder
uint64_t n_Decoder;
n_Decoder = n_IF_stage + 1;
perfModel->scheduleModel.setDec_alu(n_Decoder);
// IS_stage
uint64_t n_IS_stage;
n_IS_stage = std::max({n_Decoder, perfModel->IB_stage_OoO.get_min()});
perfModel->IS_stage = n_IS_stage;
// uA_OF_A
uint64_t n_uA_OF_A;
n_uA_OF_A = std::max({n_IS_stage, perfModel->scheduleModel.getXa()});
// uA_OF_B
uint64_t n_uA_OF_B;
n_uA_OF_B = std::max({n_IS_stage, perfModel->scheduleModel.getXb()});
// uA_Issue
uint64_t n_uA_Issue;
n_uA_Issue = std::max({n_IS_stage, perfModel->scheduleModel.getT_issue()});
// IB_stage_OoO
uint64_t n_IB_stage_OoO;
n_IB_stage_OoO = std::max({n_uA_OF_A, n_uA_OF_B, n_uA_Issue});
perfModel->IB_stage_OoO.replace_min(n_IB_stage_OoO);
// ALU
uint64_t n_ALU;
n_ALU = n_IB_stage_OoO + 1;
perfModel->scheduleModel.setXd(n_ALU);
perfModel->clobberModel.setCb_inRd(n_ALU);
perfModel->clobberModel.setCb_inR1(n_ALU);
perfModel->clobberModel.setCb_inR2(n_ALU);
// EX_stage_alu_NoB
uint64_t n_EX_stage_alu_NoB = n_ALU;
perfModel->EX_stage_alu_NoB = n_EX_stage_alu_NoB;
// WB
uint64_t n_WB;
n_WB = n_EX_stage_alu_NoB + 1;
perfModel->scheduleModel.setT_wb(n_WB);
// WB_stage_NoB
uint64_t n_WB_stage_NoB = n_WB;
perfModel->WB_stage_NoB.set(n_WB_stage_NoB);

  // Dump Entrance point for info print (tracing)
  perfModel->entrancePoint = n_Enter;
  }
);

static SchedulingFunction *schedulingFunction_addi = new SchedulingFunction(
  RV32_OOO_SchedulingFunctionSet,
  "addi",
  10,
  [](PerformanceModel* perfModel_){
  RV32_OOO_PerformanceModel* perfModel = static_cast<RV32_OOO_PerformanceModel*>(perfModel_);
  // Enter
uint64_t n_Enter = perfModel->PC_stage;
// PCGen
uint64_t n_PCGen;
uint64_t n_PCGen_max;
n_PCGen_max = std::max({n_Enter, perfModel->noBranchPredModel.getPc()});
n_PCGen = n_PCGen_max + 1;
perfModel->noBranchPredModel.setPc_p(n_PCGen);
// PC_stage
uint64_t n_PC_stage;
n_PC_stage = std::max({n_PCGen, perfModel->IF_stage});
perfModel->PC_stage = n_PC_stage;
// IPort_R
uint64_t n_IPort_R;
n_IPort_R = n_PC_stage + 1;
// uA_Clobber
uint64_t n_uA_Clobber;
n_uA_Clobber = std::max({n_PC_stage, perfModel->clobberModel.getCb_out()});
// IF_stage
uint64_t n_IF_stage;
n_IF_stage = std::max({n_IPort_R, n_uA_Clobber, perfModel->IS_stage});
perfModel->IF_stage = n_IF_stage;
// Decoder
uint64_t n_Decoder;
n_Decoder = n_IF_stage + 1;
perfModel->scheduleModel.setDec_alu(n_Decoder);
// IS_stage
uint64_t n_IS_stage;
n_IS_stage = std::max({n_Decoder, perfModel->IB_stage_OoO.get_min()});
perfModel->IS_stage = n_IS_stage;
// uA_OF_A
uint64_t n_uA_OF_A;
n_uA_OF_A = std::max({n_IS_stage, perfModel->scheduleModel.getXa()});
// uA_Issue
uint64_t n_uA_Issue;
n_uA_Issue = std::max({n_IS_stage, perfModel->scheduleModel.getT_issue()});
// IB_stage_OoO
uint64_t n_IB_stage_OoO;
n_IB_stage_OoO = std::max({n_uA_OF_A, n_uA_Issue});
perfModel->IB_stage_OoO.replace_min(n_IB_stage_OoO);
// ALU
uint64_t n_ALU;
n_ALU = n_IB_stage_OoO + 1;
perfModel->scheduleModel.setXd(n_ALU);
perfModel->clobberModel.setCb_inRd(n_ALU);
perfModel->clobberModel.setCb_inR1(n_ALU);
// EX_stage_alu_NoB
uint64_t n_EX_stage_alu_NoB = n_ALU;
perfModel->EX_stage_alu_NoB = n_EX_stage_alu_NoB;
// WB
uint64_t n_WB;
n_WB = n_EX_stage_alu_NoB + 1;
perfModel->scheduleModel.setT_wb(n_WB);
// WB_stage_NoB
uint64_t n_WB_stage_NoB = n_WB;
perfModel->WB_stage_NoB.set(n_WB_stage_NoB);

  // Dump Entrance point for info print (tracing)
  perfModel->entrancePoint = n_Enter;
  }
);

static SchedulingFunction *schedulingFunction_xori = new SchedulingFunction(
  RV32_OOO_SchedulingFunctionSet,
  "xori",
  11,
  [](PerformanceModel* perfModel_){
  RV32_OOO_PerformanceModel* perfModel = static_cast<RV32_OOO_PerformanceModel*>(perfModel_);
  // Enter
uint64_t n_Enter = perfModel->PC_stage;
// PCGen
uint64_t n_PCGen;
uint64_t n_PCGen_max;
n_PCGen_max = std::max({n_Enter, perfModel->noBranchPredModel.getPc()});
n_PCGen = n_PCGen_max + 1;
perfModel->noBranchPredModel.setPc_p(n_PCGen);
// PC_stage
uint64_t n_PC_stage;
n_PC_stage = std::max({n_PCGen, perfModel->IF_stage});
perfModel->PC_stage = n_PC_stage;
// IPort_R
uint64_t n_IPort_R;
n_IPort_R = n_PC_stage + 1;
// uA_Clobber
uint64_t n_uA_Clobber;
n_uA_Clobber = std::max({n_PC_stage, perfModel->clobberModel.getCb_out()});
// IF_stage
uint64_t n_IF_stage;
n_IF_stage = std::max({n_IPort_R, n_uA_Clobber, perfModel->IS_stage});
perfModel->IF_stage = n_IF_stage;
// Decoder
uint64_t n_Decoder;
n_Decoder = n_IF_stage + 1;
perfModel->scheduleModel.setDec_alu(n_Decoder);
// IS_stage
uint64_t n_IS_stage;
n_IS_stage = std::max({n_Decoder, perfModel->IB_stage_OoO.get_min()});
perfModel->IS_stage = n_IS_stage;
// uA_OF_A
uint64_t n_uA_OF_A;
n_uA_OF_A = std::max({n_IS_stage, perfModel->scheduleModel.getXa()});
// uA_Issue
uint64_t n_uA_Issue;
n_uA_Issue = std::max({n_IS_stage, perfModel->scheduleModel.getT_issue()});
// IB_stage_OoO
uint64_t n_IB_stage_OoO;
n_IB_stage_OoO = std::max({n_uA_OF_A, n_uA_Issue});
perfModel->IB_stage_OoO.replace_min(n_IB_stage_OoO);
// ALU
uint64_t n_ALU;
n_ALU = n_IB_stage_OoO + 1;
perfModel->scheduleModel.setXd(n_ALU);
perfModel->clobberModel.setCb_inRd(n_ALU);
perfModel->clobberModel.setCb_inR1(n_ALU);
// EX_stage_alu_NoB
uint64_t n_EX_stage_alu_NoB = n_ALU;
perfModel->EX_stage_alu_NoB = n_EX_stage_alu_NoB;
// WB
uint64_t n_WB;
n_WB = n_EX_stage_alu_NoB + 1;
perfModel->scheduleModel.setT_wb(n_WB);
// WB_stage_NoB
uint64_t n_WB_stage_NoB = n_WB;
perfModel->WB_stage_NoB.set(n_WB_stage_NoB);

  // Dump Entrance point for info print (tracing)
  perfModel->entrancePoint = n_Enter;
  }
);

static SchedulingFunction *schedulingFunction_ori = new SchedulingFunction(
  RV32_OOO_SchedulingFunctionSet,
  "ori",
  12,
  [](PerformanceModel* perfModel_){
  RV32_OOO_PerformanceModel* perfModel = static_cast<RV32_OOO_PerformanceModel*>(perfModel_);
  // Enter
uint64_t n_Enter = perfModel->PC_stage;
// PCGen
uint64_t n_PCGen;
uint64_t n_PCGen_max;
n_PCGen_max = std::max({n_Enter, perfModel->noBranchPredModel.getPc()});
n_PCGen = n_PCGen_max + 1;
perfModel->noBranchPredModel.setPc_p(n_PCGen);
// PC_stage
uint64_t n_PC_stage;
n_PC_stage = std::max({n_PCGen, perfModel->IF_stage});
perfModel->PC_stage = n_PC_stage;
// IPort_R
uint64_t n_IPort_R;
n_IPort_R = n_PC_stage + 1;
// uA_Clobber
uint64_t n_uA_Clobber;
n_uA_Clobber = std::max({n_PC_stage, perfModel->clobberModel.getCb_out()});
// IF_stage
uint64_t n_IF_stage;
n_IF_stage = std::max({n_IPort_R, n_uA_Clobber, perfModel->IS_stage});
perfModel->IF_stage = n_IF_stage;
// Decoder
uint64_t n_Decoder;
n_Decoder = n_IF_stage + 1;
perfModel->scheduleModel.setDec_alu(n_Decoder);
// IS_stage
uint64_t n_IS_stage;
n_IS_stage = std::max({n_Decoder, perfModel->IB_stage_OoO.get_min()});
perfModel->IS_stage = n_IS_stage;
// uA_OF_A
uint64_t n_uA_OF_A;
n_uA_OF_A = std::max({n_IS_stage, perfModel->scheduleModel.getXa()});
// uA_Issue
uint64_t n_uA_Issue;
n_uA_Issue = std::max({n_IS_stage, perfModel->scheduleModel.getT_issue()});
// IB_stage_OoO
uint64_t n_IB_stage_OoO;
n_IB_stage_OoO = std::max({n_uA_OF_A, n_uA_Issue});
perfModel->IB_stage_OoO.replace_min(n_IB_stage_OoO);
// ALU
uint64_t n_ALU;
n_ALU = n_IB_stage_OoO + 1;
perfModel->scheduleModel.setXd(n_ALU);
perfModel->clobberModel.setCb_inRd(n_ALU);
perfModel->clobberModel.setCb_inR1(n_ALU);
// EX_stage_alu_NoB
uint64_t n_EX_stage_alu_NoB = n_ALU;
perfModel->EX_stage_alu_NoB = n_EX_stage_alu_NoB;
// WB
uint64_t n_WB;
n_WB = n_EX_stage_alu_NoB + 1;
perfModel->scheduleModel.setT_wb(n_WB);
// WB_stage_NoB
uint64_t n_WB_stage_NoB = n_WB;
perfModel->WB_stage_NoB.set(n_WB_stage_NoB);

  // Dump Entrance point for info print (tracing)
  perfModel->entrancePoint = n_Enter;
  }
);

static SchedulingFunction *schedulingFunction_andi = new SchedulingFunction(
  RV32_OOO_SchedulingFunctionSet,
  "andi",
  13,
  [](PerformanceModel* perfModel_){
  RV32_OOO_PerformanceModel* perfModel = static_cast<RV32_OOO_PerformanceModel*>(perfModel_);
  // Enter
uint64_t n_Enter = perfModel->PC_stage;
// PCGen
uint64_t n_PCGen;
uint64_t n_PCGen_max;
n_PCGen_max = std::max({n_Enter, perfModel->noBranchPredModel.getPc()});
n_PCGen = n_PCGen_max + 1;
perfModel->noBranchPredModel.setPc_p(n_PCGen);
// PC_stage
uint64_t n_PC_stage;
n_PC_stage = std::max({n_PCGen, perfModel->IF_stage});
perfModel->PC_stage = n_PC_stage;
// IPort_R
uint64_t n_IPort_R;
n_IPort_R = n_PC_stage + 1;
// uA_Clobber
uint64_t n_uA_Clobber;
n_uA_Clobber = std::max({n_PC_stage, perfModel->clobberModel.getCb_out()});
// IF_stage
uint64_t n_IF_stage;
n_IF_stage = std::max({n_IPort_R, n_uA_Clobber, perfModel->IS_stage});
perfModel->IF_stage = n_IF_stage;
// Decoder
uint64_t n_Decoder;
n_Decoder = n_IF_stage + 1;
perfModel->scheduleModel.setDec_alu(n_Decoder);
// IS_stage
uint64_t n_IS_stage;
n_IS_stage = std::max({n_Decoder, perfModel->IB_stage_OoO.get_min()});
perfModel->IS_stage = n_IS_stage;
// uA_OF_A
uint64_t n_uA_OF_A;
n_uA_OF_A = std::max({n_IS_stage, perfModel->scheduleModel.getXa()});
// uA_Issue
uint64_t n_uA_Issue;
n_uA_Issue = std::max({n_IS_stage, perfModel->scheduleModel.getT_issue()});
// IB_stage_OoO
uint64_t n_IB_stage_OoO;
n_IB_stage_OoO = std::max({n_uA_OF_A, n_uA_Issue});
perfModel->IB_stage_OoO.replace_min(n_IB_stage_OoO);
// ALU
uint64_t n_ALU;
n_ALU = n_IB_stage_OoO + 1;
perfModel->scheduleModel.setXd(n_ALU);
perfModel->clobberModel.setCb_inRd(n_ALU);
perfModel->clobberModel.setCb_inR1(n_ALU);
// EX_stage_alu_NoB
uint64_t n_EX_stage_alu_NoB = n_ALU;
perfModel->EX_stage_alu_NoB = n_EX_stage_alu_NoB;
// WB
uint64_t n_WB;
n_WB = n_EX_stage_alu_NoB + 1;
perfModel->scheduleModel.setT_wb(n_WB);
// WB_stage_NoB
uint64_t n_WB_stage_NoB = n_WB;
perfModel->WB_stage_NoB.set(n_WB_stage_NoB);

  // Dump Entrance point for info print (tracing)
  perfModel->entrancePoint = n_Enter;
  }
);

static SchedulingFunction *schedulingFunction_slti = new SchedulingFunction(
  RV32_OOO_SchedulingFunctionSet,
  "slti",
  14,
  [](PerformanceModel* perfModel_){
  RV32_OOO_PerformanceModel* perfModel = static_cast<RV32_OOO_PerformanceModel*>(perfModel_);
  // Enter
uint64_t n_Enter = perfModel->PC_stage;
// PCGen
uint64_t n_PCGen;
uint64_t n_PCGen_max;
n_PCGen_max = std::max({n_Enter, perfModel->noBranchPredModel.getPc()});
n_PCGen = n_PCGen_max + 1;
perfModel->noBranchPredModel.setPc_p(n_PCGen);
// PC_stage
uint64_t n_PC_stage;
n_PC_stage = std::max({n_PCGen, perfModel->IF_stage});
perfModel->PC_stage = n_PC_stage;
// IPort_R
uint64_t n_IPort_R;
n_IPort_R = n_PC_stage + 1;
// uA_Clobber
uint64_t n_uA_Clobber;
n_uA_Clobber = std::max({n_PC_stage, perfModel->clobberModel.getCb_out()});
// IF_stage
uint64_t n_IF_stage;
n_IF_stage = std::max({n_IPort_R, n_uA_Clobber, perfModel->IS_stage});
perfModel->IF_stage = n_IF_stage;
// Decoder
uint64_t n_Decoder;
n_Decoder = n_IF_stage + 1;
perfModel->scheduleModel.setDec_alu(n_Decoder);
// IS_stage
uint64_t n_IS_stage;
n_IS_stage = std::max({n_Decoder, perfModel->IB_stage_OoO.get_min()});
perfModel->IS_stage = n_IS_stage;
// uA_OF_A
uint64_t n_uA_OF_A;
n_uA_OF_A = std::max({n_IS_stage, perfModel->scheduleModel.getXa()});
// uA_Issue
uint64_t n_uA_Issue;
n_uA_Issue = std::max({n_IS_stage, perfModel->scheduleModel.getT_issue()});
// IB_stage_OoO
uint64_t n_IB_stage_OoO;
n_IB_stage_OoO = std::max({n_uA_OF_A, n_uA_Issue});
perfModel->IB_stage_OoO.replace_min(n_IB_stage_OoO);
// ALU
uint64_t n_ALU;
n_ALU = n_IB_stage_OoO + 1;
perfModel->scheduleModel.setXd(n_ALU);
perfModel->clobberModel.setCb_inRd(n_ALU);
perfModel->clobberModel.setCb_inR1(n_ALU);
// EX_stage_alu_NoB
uint64_t n_EX_stage_alu_NoB = n_ALU;
perfModel->EX_stage_alu_NoB = n_EX_stage_alu_NoB;
// WB
uint64_t n_WB;
n_WB = n_EX_stage_alu_NoB + 1;
perfModel->scheduleModel.setT_wb(n_WB);
// WB_stage_NoB
uint64_t n_WB_stage_NoB = n_WB;
perfModel->WB_stage_NoB.set(n_WB_stage_NoB);

  // Dump Entrance point for info print (tracing)
  perfModel->entrancePoint = n_Enter;
  }
);

static SchedulingFunction *schedulingFunction_sltiu = new SchedulingFunction(
  RV32_OOO_SchedulingFunctionSet,
  "sltiu",
  15,
  [](PerformanceModel* perfModel_){
  RV32_OOO_PerformanceModel* perfModel = static_cast<RV32_OOO_PerformanceModel*>(perfModel_);
  // Enter
uint64_t n_Enter = perfModel->PC_stage;
// PCGen
uint64_t n_PCGen;
uint64_t n_PCGen_max;
n_PCGen_max = std::max({n_Enter, perfModel->noBranchPredModel.getPc()});
n_PCGen = n_PCGen_max + 1;
perfModel->noBranchPredModel.setPc_p(n_PCGen);
// PC_stage
uint64_t n_PC_stage;
n_PC_stage = std::max({n_PCGen, perfModel->IF_stage});
perfModel->PC_stage = n_PC_stage;
// IPort_R
uint64_t n_IPort_R;
n_IPort_R = n_PC_stage + 1;
// uA_Clobber
uint64_t n_uA_Clobber;
n_uA_Clobber = std::max({n_PC_stage, perfModel->clobberModel.getCb_out()});
// IF_stage
uint64_t n_IF_stage;
n_IF_stage = std::max({n_IPort_R, n_uA_Clobber, perfModel->IS_stage});
perfModel->IF_stage = n_IF_stage;
// Decoder
uint64_t n_Decoder;
n_Decoder = n_IF_stage + 1;
perfModel->scheduleModel.setDec_alu(n_Decoder);
// IS_stage
uint64_t n_IS_stage;
n_IS_stage = std::max({n_Decoder, perfModel->IB_stage_OoO.get_min()});
perfModel->IS_stage = n_IS_stage;
// uA_OF_A
uint64_t n_uA_OF_A;
n_uA_OF_A = std::max({n_IS_stage, perfModel->scheduleModel.getXa()});
// uA_Issue
uint64_t n_uA_Issue;
n_uA_Issue = std::max({n_IS_stage, perfModel->scheduleModel.getT_issue()});
// IB_stage_OoO
uint64_t n_IB_stage_OoO;
n_IB_stage_OoO = std::max({n_uA_OF_A, n_uA_Issue});
perfModel->IB_stage_OoO.replace_min(n_IB_stage_OoO);
// ALU
uint64_t n_ALU;
n_ALU = n_IB_stage_OoO + 1;
perfModel->scheduleModel.setXd(n_ALU);
perfModel->clobberModel.setCb_inRd(n_ALU);
perfModel->clobberModel.setCb_inR1(n_ALU);
// EX_stage_alu_NoB
uint64_t n_EX_stage_alu_NoB = n_ALU;
perfModel->EX_stage_alu_NoB = n_EX_stage_alu_NoB;
// WB
uint64_t n_WB;
n_WB = n_EX_stage_alu_NoB + 1;
perfModel->scheduleModel.setT_wb(n_WB);
// WB_stage_NoB
uint64_t n_WB_stage_NoB = n_WB;
perfModel->WB_stage_NoB.set(n_WB_stage_NoB);

  // Dump Entrance point for info print (tracing)
  perfModel->entrancePoint = n_Enter;
  }
);

static SchedulingFunction *schedulingFunction_slli = new SchedulingFunction(
  RV32_OOO_SchedulingFunctionSet,
  "slli",
  16,
  [](PerformanceModel* perfModel_){
  RV32_OOO_PerformanceModel* perfModel = static_cast<RV32_OOO_PerformanceModel*>(perfModel_);
  // Enter
uint64_t n_Enter = perfModel->PC_stage;
// PCGen
uint64_t n_PCGen;
uint64_t n_PCGen_max;
n_PCGen_max = std::max({n_Enter, perfModel->noBranchPredModel.getPc()});
n_PCGen = n_PCGen_max + 1;
perfModel->noBranchPredModel.setPc_p(n_PCGen);
// PC_stage
uint64_t n_PC_stage;
n_PC_stage = std::max({n_PCGen, perfModel->IF_stage});
perfModel->PC_stage = n_PC_stage;
// IPort_R
uint64_t n_IPort_R;
n_IPort_R = n_PC_stage + 1;
// uA_Clobber
uint64_t n_uA_Clobber;
n_uA_Clobber = std::max({n_PC_stage, perfModel->clobberModel.getCb_out()});
// IF_stage
uint64_t n_IF_stage;
n_IF_stage = std::max({n_IPort_R, n_uA_Clobber, perfModel->IS_stage});
perfModel->IF_stage = n_IF_stage;
// Decoder
uint64_t n_Decoder;
n_Decoder = n_IF_stage + 1;
perfModel->scheduleModel.setDec_alu(n_Decoder);
// IS_stage
uint64_t n_IS_stage;
n_IS_stage = std::max({n_Decoder, perfModel->IB_stage_OoO.get_min()});
perfModel->IS_stage = n_IS_stage;
// uA_OF_A
uint64_t n_uA_OF_A;
n_uA_OF_A = std::max({n_IS_stage, perfModel->scheduleModel.getXa()});
// uA_Issue
uint64_t n_uA_Issue;
n_uA_Issue = std::max({n_IS_stage, perfModel->scheduleModel.getT_issue()});
// IB_stage_OoO
uint64_t n_IB_stage_OoO;
n_IB_stage_OoO = std::max({n_uA_OF_A, n_uA_Issue});
perfModel->IB_stage_OoO.replace_min(n_IB_stage_OoO);
// ALU
uint64_t n_ALU;
n_ALU = n_IB_stage_OoO + 1;
perfModel->scheduleModel.setXd(n_ALU);
perfModel->clobberModel.setCb_inRd(n_ALU);
perfModel->clobberModel.setCb_inR1(n_ALU);
// EX_stage_alu_NoB
uint64_t n_EX_stage_alu_NoB = n_ALU;
perfModel->EX_stage_alu_NoB = n_EX_stage_alu_NoB;
// WB
uint64_t n_WB;
n_WB = n_EX_stage_alu_NoB + 1;
perfModel->scheduleModel.setT_wb(n_WB);
// WB_stage_NoB
uint64_t n_WB_stage_NoB = n_WB;
perfModel->WB_stage_NoB.set(n_WB_stage_NoB);

  // Dump Entrance point for info print (tracing)
  perfModel->entrancePoint = n_Enter;
  }
);

static SchedulingFunction *schedulingFunction_srli = new SchedulingFunction(
  RV32_OOO_SchedulingFunctionSet,
  "srli",
  17,
  [](PerformanceModel* perfModel_){
  RV32_OOO_PerformanceModel* perfModel = static_cast<RV32_OOO_PerformanceModel*>(perfModel_);
  // Enter
uint64_t n_Enter = perfModel->PC_stage;
// PCGen
uint64_t n_PCGen;
uint64_t n_PCGen_max;
n_PCGen_max = std::max({n_Enter, perfModel->noBranchPredModel.getPc()});
n_PCGen = n_PCGen_max + 1;
perfModel->noBranchPredModel.setPc_p(n_PCGen);
// PC_stage
uint64_t n_PC_stage;
n_PC_stage = std::max({n_PCGen, perfModel->IF_stage});
perfModel->PC_stage = n_PC_stage;
// IPort_R
uint64_t n_IPort_R;
n_IPort_R = n_PC_stage + 1;
// uA_Clobber
uint64_t n_uA_Clobber;
n_uA_Clobber = std::max({n_PC_stage, perfModel->clobberModel.getCb_out()});
// IF_stage
uint64_t n_IF_stage;
n_IF_stage = std::max({n_IPort_R, n_uA_Clobber, perfModel->IS_stage});
perfModel->IF_stage = n_IF_stage;
// Decoder
uint64_t n_Decoder;
n_Decoder = n_IF_stage + 1;
perfModel->scheduleModel.setDec_alu(n_Decoder);
// IS_stage
uint64_t n_IS_stage;
n_IS_stage = std::max({n_Decoder, perfModel->IB_stage_OoO.get_min()});
perfModel->IS_stage = n_IS_stage;
// uA_OF_A
uint64_t n_uA_OF_A;
n_uA_OF_A = std::max({n_IS_stage, perfModel->scheduleModel.getXa()});
// uA_Issue
uint64_t n_uA_Issue;
n_uA_Issue = std::max({n_IS_stage, perfModel->scheduleModel.getT_issue()});
// IB_stage_OoO
uint64_t n_IB_stage_OoO;
n_IB_stage_OoO = std::max({n_uA_OF_A, n_uA_Issue});
perfModel->IB_stage_OoO.replace_min(n_IB_stage_OoO);
// ALU
uint64_t n_ALU;
n_ALU = n_IB_stage_OoO + 1;
perfModel->scheduleModel.setXd(n_ALU);
perfModel->clobberModel.setCb_inRd(n_ALU);
perfModel->clobberModel.setCb_inR1(n_ALU);
// EX_stage_alu_NoB
uint64_t n_EX_stage_alu_NoB = n_ALU;
perfModel->EX_stage_alu_NoB = n_EX_stage_alu_NoB;
// WB
uint64_t n_WB;
n_WB = n_EX_stage_alu_NoB + 1;
perfModel->scheduleModel.setT_wb(n_WB);
// WB_stage_NoB
uint64_t n_WB_stage_NoB = n_WB;
perfModel->WB_stage_NoB.set(n_WB_stage_NoB);

  // Dump Entrance point for info print (tracing)
  perfModel->entrancePoint = n_Enter;
  }
);

static SchedulingFunction *schedulingFunction_srai = new SchedulingFunction(
  RV32_OOO_SchedulingFunctionSet,
  "srai",
  18,
  [](PerformanceModel* perfModel_){
  RV32_OOO_PerformanceModel* perfModel = static_cast<RV32_OOO_PerformanceModel*>(perfModel_);
  // Enter
uint64_t n_Enter = perfModel->PC_stage;
// PCGen
uint64_t n_PCGen;
uint64_t n_PCGen_max;
n_PCGen_max = std::max({n_Enter, perfModel->noBranchPredModel.getPc()});
n_PCGen = n_PCGen_max + 1;
perfModel->noBranchPredModel.setPc_p(n_PCGen);
// PC_stage
uint64_t n_PC_stage;
n_PC_stage = std::max({n_PCGen, perfModel->IF_stage});
perfModel->PC_stage = n_PC_stage;
// IPort_R
uint64_t n_IPort_R;
n_IPort_R = n_PC_stage + 1;
// uA_Clobber
uint64_t n_uA_Clobber;
n_uA_Clobber = std::max({n_PC_stage, perfModel->clobberModel.getCb_out()});
// IF_stage
uint64_t n_IF_stage;
n_IF_stage = std::max({n_IPort_R, n_uA_Clobber, perfModel->IS_stage});
perfModel->IF_stage = n_IF_stage;
// Decoder
uint64_t n_Decoder;
n_Decoder = n_IF_stage + 1;
perfModel->scheduleModel.setDec_alu(n_Decoder);
// IS_stage
uint64_t n_IS_stage;
n_IS_stage = std::max({n_Decoder, perfModel->IB_stage_OoO.get_min()});
perfModel->IS_stage = n_IS_stage;
// uA_OF_A
uint64_t n_uA_OF_A;
n_uA_OF_A = std::max({n_IS_stage, perfModel->scheduleModel.getXa()});
// uA_Issue
uint64_t n_uA_Issue;
n_uA_Issue = std::max({n_IS_stage, perfModel->scheduleModel.getT_issue()});
// IB_stage_OoO
uint64_t n_IB_stage_OoO;
n_IB_stage_OoO = std::max({n_uA_OF_A, n_uA_Issue});
perfModel->IB_stage_OoO.replace_min(n_IB_stage_OoO);
// ALU
uint64_t n_ALU;
n_ALU = n_IB_stage_OoO + 1;
perfModel->scheduleModel.setXd(n_ALU);
perfModel->clobberModel.setCb_inRd(n_ALU);
perfModel->clobberModel.setCb_inR1(n_ALU);
// EX_stage_alu_NoB
uint64_t n_EX_stage_alu_NoB = n_ALU;
perfModel->EX_stage_alu_NoB = n_EX_stage_alu_NoB;
// WB
uint64_t n_WB;
n_WB = n_EX_stage_alu_NoB + 1;
perfModel->scheduleModel.setT_wb(n_WB);
// WB_stage_NoB
uint64_t n_WB_stage_NoB = n_WB;
perfModel->WB_stage_NoB.set(n_WB_stage_NoB);

  // Dump Entrance point for info print (tracing)
  perfModel->entrancePoint = n_Enter;
  }
);

static SchedulingFunction *schedulingFunction_auipc = new SchedulingFunction(
  RV32_OOO_SchedulingFunctionSet,
  "auipc",
  19,
  [](PerformanceModel* perfModel_){
  RV32_OOO_PerformanceModel* perfModel = static_cast<RV32_OOO_PerformanceModel*>(perfModel_);
  // Enter
uint64_t n_Enter = perfModel->PC_stage;
// PCGen
uint64_t n_PCGen;
uint64_t n_PCGen_max;
n_PCGen_max = std::max({n_Enter, perfModel->noBranchPredModel.getPc()});
n_PCGen = n_PCGen_max + 1;
perfModel->noBranchPredModel.setPc_p(n_PCGen);
// PC_stage
uint64_t n_PC_stage;
n_PC_stage = std::max({n_PCGen, perfModel->IF_stage});
perfModel->PC_stage = n_PC_stage;
// IPort_R
uint64_t n_IPort_R;
n_IPort_R = n_PC_stage + 1;
// uA_Clobber
uint64_t n_uA_Clobber;
n_uA_Clobber = std::max({n_PC_stage, perfModel->clobberModel.getCb_out()});
// IF_stage
uint64_t n_IF_stage;
n_IF_stage = std::max({n_IPort_R, n_uA_Clobber, perfModel->IS_stage});
perfModel->IF_stage = n_IF_stage;
// Decoder
uint64_t n_Decoder;
n_Decoder = n_IF_stage + 1;
perfModel->scheduleModel.setDec_alu(n_Decoder);
// IS_stage
uint64_t n_IS_stage;
n_IS_stage = std::max({n_Decoder, perfModel->IB_stage_OoO.get_min()});
perfModel->IS_stage = n_IS_stage;
// uA_Issue
uint64_t n_uA_Issue;
n_uA_Issue = std::max({n_IS_stage, perfModel->scheduleModel.getT_issue()});
// IB_stage_OoO
uint64_t n_IB_stage_OoO = n_uA_Issue;
perfModel->IB_stage_OoO.replace_min(n_IB_stage_OoO);
// ALU
uint64_t n_ALU;
n_ALU = n_IB_stage_OoO + 1;
perfModel->scheduleModel.setXd(n_ALU);
perfModel->clobberModel.setCb_inRd(n_ALU);
// EX_stage_alu_NoB
uint64_t n_EX_stage_alu_NoB = n_ALU;
perfModel->EX_stage_alu_NoB = n_EX_stage_alu_NoB;
// WB
uint64_t n_WB;
n_WB = n_EX_stage_alu_NoB + 1;
perfModel->scheduleModel.setT_wb(n_WB);
// WB_stage_NoB
uint64_t n_WB_stage_NoB = n_WB;
perfModel->WB_stage_NoB.set(n_WB_stage_NoB);

  // Dump Entrance point for info print (tracing)
  perfModel->entrancePoint = n_Enter;
  }
);

static SchedulingFunction *schedulingFunction_lui = new SchedulingFunction(
  RV32_OOO_SchedulingFunctionSet,
  "lui",
  20,
  [](PerformanceModel* perfModel_){
  RV32_OOO_PerformanceModel* perfModel = static_cast<RV32_OOO_PerformanceModel*>(perfModel_);
  // Enter
uint64_t n_Enter = perfModel->PC_stage;
// PCGen
uint64_t n_PCGen;
uint64_t n_PCGen_max;
n_PCGen_max = std::max({n_Enter, perfModel->noBranchPredModel.getPc()});
n_PCGen = n_PCGen_max + 1;
perfModel->noBranchPredModel.setPc_p(n_PCGen);
// PC_stage
uint64_t n_PC_stage;
n_PC_stage = std::max({n_PCGen, perfModel->IF_stage});
perfModel->PC_stage = n_PC_stage;
// IPort_R
uint64_t n_IPort_R;
n_IPort_R = n_PC_stage + 1;
// uA_Clobber
uint64_t n_uA_Clobber;
n_uA_Clobber = std::max({n_PC_stage, perfModel->clobberModel.getCb_out()});
// IF_stage
uint64_t n_IF_stage;
n_IF_stage = std::max({n_IPort_R, n_uA_Clobber, perfModel->IS_stage});
perfModel->IF_stage = n_IF_stage;
// Decoder
uint64_t n_Decoder;
n_Decoder = n_IF_stage + 1;
perfModel->scheduleModel.setDec_alu(n_Decoder);
// IS_stage
uint64_t n_IS_stage;
n_IS_stage = std::max({n_Decoder, perfModel->IB_stage_OoO.get_min()});
perfModel->IS_stage = n_IS_stage;
// uA_Issue
uint64_t n_uA_Issue;
n_uA_Issue = std::max({n_IS_stage, perfModel->scheduleModel.getT_issue()});
// IB_stage_OoO
uint64_t n_IB_stage_OoO = n_uA_Issue;
perfModel->IB_stage_OoO.replace_min(n_IB_stage_OoO);
// ALU
uint64_t n_ALU;
n_ALU = n_IB_stage_OoO + 1;
perfModel->scheduleModel.setXd(n_ALU);
perfModel->clobberModel.setCb_inRd(n_ALU);
// EX_stage_alu_NoB
uint64_t n_EX_stage_alu_NoB = n_ALU;
perfModel->EX_stage_alu_NoB = n_EX_stage_alu_NoB;
// WB
uint64_t n_WB;
n_WB = n_EX_stage_alu_NoB + 1;
perfModel->scheduleModel.setT_wb(n_WB);
// WB_stage_NoB
uint64_t n_WB_stage_NoB = n_WB;
perfModel->WB_stage_NoB.set(n_WB_stage_NoB);

  // Dump Entrance point for info print (tracing)
  perfModel->entrancePoint = n_Enter;
  }
);

static SchedulingFunction *schedulingFunction_mul = new SchedulingFunction(
  RV32_OOO_SchedulingFunctionSet,
  "mul",
  21,
  [](PerformanceModel* perfModel_){
  RV32_OOO_PerformanceModel* perfModel = static_cast<RV32_OOO_PerformanceModel*>(perfModel_);
  // Enter
uint64_t n_Enter = perfModel->PC_stage;
// PCGen
uint64_t n_PCGen;
uint64_t n_PCGen_max;
n_PCGen_max = std::max({n_Enter, perfModel->noBranchPredModel.getPc()});
n_PCGen = n_PCGen_max + 1;
perfModel->noBranchPredModel.setPc_p(n_PCGen);
// PC_stage
uint64_t n_PC_stage;
n_PC_stage = std::max({n_PCGen, perfModel->IF_stage});
perfModel->PC_stage = n_PC_stage;
// IPort_R
uint64_t n_IPort_R;
n_IPort_R = n_PC_stage + 1;
// uA_Clobber
uint64_t n_uA_Clobber;
n_uA_Clobber = std::max({n_PC_stage, perfModel->clobberModel.getCb_out()});
// IF_stage
uint64_t n_IF_stage;
n_IF_stage = std::max({n_IPort_R, n_uA_Clobber, perfModel->IS_stage});
perfModel->IF_stage = n_IF_stage;
// Decoder
uint64_t n_Decoder;
n_Decoder = n_IF_stage + 1;
perfModel->scheduleModel.setDec_mul(n_Decoder);
// IS_stage
uint64_t n_IS_stage;
n_IS_stage = std::max({n_Decoder, perfModel->IB_stage_OoO.get_min()});
perfModel->IS_stage = n_IS_stage;
// uA_OF_A
uint64_t n_uA_OF_A;
n_uA_OF_A = std::max({n_IS_stage, perfModel->scheduleModel.getXa()});
// uA_OF_B
uint64_t n_uA_OF_B;
n_uA_OF_B = std::max({n_IS_stage, perfModel->scheduleModel.getXb()});
// uA_Issue
uint64_t n_uA_Issue;
n_uA_Issue = std::max({n_IS_stage, perfModel->scheduleModel.getT_issue()});
// IB_stage_OoO
uint64_t n_IB_stage_OoO;
n_IB_stage_OoO = std::max({n_uA_OF_A, n_uA_OF_B, n_uA_Issue});
perfModel->IB_stage_OoO.replace_min(n_IB_stage_OoO);
// MUL0
uint64_t n_MUL0;
n_MUL0 = n_IB_stage_OoO + 1;
// EX_stage_mul0v_NoB
uint64_t n_EX_stage_mul0v_NoB = n_MUL0;
perfModel->EX_stage_mul0v_NoB = n_EX_stage_mul0v_NoB;
// MUL1
uint64_t n_MUL1;
n_MUL1 = n_EX_stage_mul0v_NoB + 1;
perfModel->scheduleModel.setXd(n_MUL1);
perfModel->clobberModel.setCb_inRd(n_MUL1);
perfModel->clobberModel.setCb_inR1(n_MUL1);
perfModel->clobberModel.setCb_inR2(n_MUL1);
// EX_stage_mul_NoB
uint64_t n_EX_stage_mul_NoB = n_MUL1;
perfModel->EX_stage_mul_NoB.set(n_EX_stage_mul_NoB);
perfModel->EX_stage_mul1v_NoB = n_EX_stage_mul_NoB;
// WB
uint64_t n_WB;
n_WB = n_EX_stage_mul_NoB + 1;
perfModel->scheduleModel.setT_wb(n_WB);
// WB_stage_NoB
uint64_t n_WB_stage_NoB = n_WB;
perfModel->WB_stage_NoB.set(n_WB_stage_NoB);

  // Dump Entrance point for info print (tracing)
  perfModel->entrancePoint = n_Enter;
  }
);

static SchedulingFunction *schedulingFunction_mulh = new SchedulingFunction(
  RV32_OOO_SchedulingFunctionSet,
  "mulh",
  22,
  [](PerformanceModel* perfModel_){
  RV32_OOO_PerformanceModel* perfModel = static_cast<RV32_OOO_PerformanceModel*>(perfModel_);
  // Enter
uint64_t n_Enter = perfModel->PC_stage;
// PCGen
uint64_t n_PCGen;
uint64_t n_PCGen_max;
n_PCGen_max = std::max({n_Enter, perfModel->noBranchPredModel.getPc()});
n_PCGen = n_PCGen_max + 1;
perfModel->noBranchPredModel.setPc_p(n_PCGen);
// PC_stage
uint64_t n_PC_stage;
n_PC_stage = std::max({n_PCGen, perfModel->IF_stage});
perfModel->PC_stage = n_PC_stage;
// IPort_R
uint64_t n_IPort_R;
n_IPort_R = n_PC_stage + 1;
// uA_Clobber
uint64_t n_uA_Clobber;
n_uA_Clobber = std::max({n_PC_stage, perfModel->clobberModel.getCb_out()});
// IF_stage
uint64_t n_IF_stage;
n_IF_stage = std::max({n_IPort_R, n_uA_Clobber, perfModel->IS_stage});
perfModel->IF_stage = n_IF_stage;
// Decoder
uint64_t n_Decoder;
n_Decoder = n_IF_stage + 1;
perfModel->scheduleModel.setDec_mul(n_Decoder);
// IS_stage
uint64_t n_IS_stage;
n_IS_stage = std::max({n_Decoder, perfModel->IB_stage_OoO.get_min()});
perfModel->IS_stage = n_IS_stage;
// uA_OF_A
uint64_t n_uA_OF_A;
n_uA_OF_A = std::max({n_IS_stage, perfModel->scheduleModel.getXa()});
// uA_OF_B
uint64_t n_uA_OF_B;
n_uA_OF_B = std::max({n_IS_stage, perfModel->scheduleModel.getXb()});
// uA_Issue
uint64_t n_uA_Issue;
n_uA_Issue = std::max({n_IS_stage, perfModel->scheduleModel.getT_issue()});
// IB_stage_OoO
uint64_t n_IB_stage_OoO;
n_IB_stage_OoO = std::max({n_uA_OF_A, n_uA_OF_B, n_uA_Issue});
perfModel->IB_stage_OoO.replace_min(n_IB_stage_OoO);
// MUL0
uint64_t n_MUL0;
n_MUL0 = n_IB_stage_OoO + 1;
// EX_stage_mul0v_NoB
uint64_t n_EX_stage_mul0v_NoB = n_MUL0;
perfModel->EX_stage_mul0v_NoB = n_EX_stage_mul0v_NoB;
// MUL1
uint64_t n_MUL1;
n_MUL1 = n_EX_stage_mul0v_NoB + 1;
perfModel->scheduleModel.setXd(n_MUL1);
perfModel->clobberModel.setCb_inRd(n_MUL1);
perfModel->clobberModel.setCb_inR1(n_MUL1);
perfModel->clobberModel.setCb_inR2(n_MUL1);
// EX_stage_mul_NoB
uint64_t n_EX_stage_mul_NoB = n_MUL1;
perfModel->EX_stage_mul_NoB.set(n_EX_stage_mul_NoB);
perfModel->EX_stage_mul1v_NoB = n_EX_stage_mul_NoB;
// WB
uint64_t n_WB;
n_WB = n_EX_stage_mul_NoB + 1;
perfModel->scheduleModel.setT_wb(n_WB);
// WB_stage_NoB
uint64_t n_WB_stage_NoB = n_WB;
perfModel->WB_stage_NoB.set(n_WB_stage_NoB);

  // Dump Entrance point for info print (tracing)
  perfModel->entrancePoint = n_Enter;
  }
);

static SchedulingFunction *schedulingFunction_mulhu = new SchedulingFunction(
  RV32_OOO_SchedulingFunctionSet,
  "mulhu",
  23,
  [](PerformanceModel* perfModel_){
  RV32_OOO_PerformanceModel* perfModel = static_cast<RV32_OOO_PerformanceModel*>(perfModel_);
  // Enter
uint64_t n_Enter = perfModel->PC_stage;
// PCGen
uint64_t n_PCGen;
uint64_t n_PCGen_max;
n_PCGen_max = std::max({n_Enter, perfModel->noBranchPredModel.getPc()});
n_PCGen = n_PCGen_max + 1;
perfModel->noBranchPredModel.setPc_p(n_PCGen);
// PC_stage
uint64_t n_PC_stage;
n_PC_stage = std::max({n_PCGen, perfModel->IF_stage});
perfModel->PC_stage = n_PC_stage;
// IPort_R
uint64_t n_IPort_R;
n_IPort_R = n_PC_stage + 1;
// uA_Clobber
uint64_t n_uA_Clobber;
n_uA_Clobber = std::max({n_PC_stage, perfModel->clobberModel.getCb_out()});
// IF_stage
uint64_t n_IF_stage;
n_IF_stage = std::max({n_IPort_R, n_uA_Clobber, perfModel->IS_stage});
perfModel->IF_stage = n_IF_stage;
// Decoder
uint64_t n_Decoder;
n_Decoder = n_IF_stage + 1;
perfModel->scheduleModel.setDec_mul(n_Decoder);
// IS_stage
uint64_t n_IS_stage;
n_IS_stage = std::max({n_Decoder, perfModel->IB_stage_OoO.get_min()});
perfModel->IS_stage = n_IS_stage;
// uA_OF_A
uint64_t n_uA_OF_A;
n_uA_OF_A = std::max({n_IS_stage, perfModel->scheduleModel.getXa()});
// uA_OF_B
uint64_t n_uA_OF_B;
n_uA_OF_B = std::max({n_IS_stage, perfModel->scheduleModel.getXb()});
// uA_Issue
uint64_t n_uA_Issue;
n_uA_Issue = std::max({n_IS_stage, perfModel->scheduleModel.getT_issue()});
// IB_stage_OoO
uint64_t n_IB_stage_OoO;
n_IB_stage_OoO = std::max({n_uA_OF_A, n_uA_OF_B, n_uA_Issue});
perfModel->IB_stage_OoO.replace_min(n_IB_stage_OoO);
// MUL0
uint64_t n_MUL0;
n_MUL0 = n_IB_stage_OoO + 1;
// EX_stage_mul0v_NoB
uint64_t n_EX_stage_mul0v_NoB = n_MUL0;
perfModel->EX_stage_mul0v_NoB = n_EX_stage_mul0v_NoB;
// MUL1
uint64_t n_MUL1;
n_MUL1 = n_EX_stage_mul0v_NoB + 1;
perfModel->scheduleModel.setXd(n_MUL1);
perfModel->clobberModel.setCb_inRd(n_MUL1);
perfModel->clobberModel.setCb_inR1(n_MUL1);
perfModel->clobberModel.setCb_inR2(n_MUL1);
// EX_stage_mul_NoB
uint64_t n_EX_stage_mul_NoB = n_MUL1;
perfModel->EX_stage_mul_NoB.set(n_EX_stage_mul_NoB);
perfModel->EX_stage_mul1v_NoB = n_EX_stage_mul_NoB;
// WB
uint64_t n_WB;
n_WB = n_EX_stage_mul_NoB + 1;
perfModel->scheduleModel.setT_wb(n_WB);
// WB_stage_NoB
uint64_t n_WB_stage_NoB = n_WB;
perfModel->WB_stage_NoB.set(n_WB_stage_NoB);

  // Dump Entrance point for info print (tracing)
  perfModel->entrancePoint = n_Enter;
  }
);

static SchedulingFunction *schedulingFunction_mulhsu = new SchedulingFunction(
  RV32_OOO_SchedulingFunctionSet,
  "mulhsu",
  24,
  [](PerformanceModel* perfModel_){
  RV32_OOO_PerformanceModel* perfModel = static_cast<RV32_OOO_PerformanceModel*>(perfModel_);
  // Enter
uint64_t n_Enter = perfModel->PC_stage;
// PCGen
uint64_t n_PCGen;
uint64_t n_PCGen_max;
n_PCGen_max = std::max({n_Enter, perfModel->noBranchPredModel.getPc()});
n_PCGen = n_PCGen_max + 1;
perfModel->noBranchPredModel.setPc_p(n_PCGen);
// PC_stage
uint64_t n_PC_stage;
n_PC_stage = std::max({n_PCGen, perfModel->IF_stage});
perfModel->PC_stage = n_PC_stage;
// IPort_R
uint64_t n_IPort_R;
n_IPort_R = n_PC_stage + 1;
// uA_Clobber
uint64_t n_uA_Clobber;
n_uA_Clobber = std::max({n_PC_stage, perfModel->clobberModel.getCb_out()});
// IF_stage
uint64_t n_IF_stage;
n_IF_stage = std::max({n_IPort_R, n_uA_Clobber, perfModel->IS_stage});
perfModel->IF_stage = n_IF_stage;
// Decoder
uint64_t n_Decoder;
n_Decoder = n_IF_stage + 1;
perfModel->scheduleModel.setDec_mul(n_Decoder);
// IS_stage
uint64_t n_IS_stage;
n_IS_stage = std::max({n_Decoder, perfModel->IB_stage_OoO.get_min()});
perfModel->IS_stage = n_IS_stage;
// uA_OF_A
uint64_t n_uA_OF_A;
n_uA_OF_A = std::max({n_IS_stage, perfModel->scheduleModel.getXa()});
// uA_OF_B
uint64_t n_uA_OF_B;
n_uA_OF_B = std::max({n_IS_stage, perfModel->scheduleModel.getXb()});
// uA_Issue
uint64_t n_uA_Issue;
n_uA_Issue = std::max({n_IS_stage, perfModel->scheduleModel.getT_issue()});
// IB_stage_OoO
uint64_t n_IB_stage_OoO;
n_IB_stage_OoO = std::max({n_uA_OF_A, n_uA_OF_B, n_uA_Issue});
perfModel->IB_stage_OoO.replace_min(n_IB_stage_OoO);
// MUL0
uint64_t n_MUL0;
n_MUL0 = n_IB_stage_OoO + 1;
// EX_stage_mul0v_NoB
uint64_t n_EX_stage_mul0v_NoB = n_MUL0;
perfModel->EX_stage_mul0v_NoB = n_EX_stage_mul0v_NoB;
// MUL1
uint64_t n_MUL1;
n_MUL1 = n_EX_stage_mul0v_NoB + 1;
perfModel->scheduleModel.setXd(n_MUL1);
perfModel->clobberModel.setCb_inRd(n_MUL1);
perfModel->clobberModel.setCb_inR1(n_MUL1);
perfModel->clobberModel.setCb_inR2(n_MUL1);
// EX_stage_mul_NoB
uint64_t n_EX_stage_mul_NoB = n_MUL1;
perfModel->EX_stage_mul_NoB.set(n_EX_stage_mul_NoB);
perfModel->EX_stage_mul1v_NoB = n_EX_stage_mul_NoB;
// WB
uint64_t n_WB;
n_WB = n_EX_stage_mul_NoB + 1;
perfModel->scheduleModel.setT_wb(n_WB);
// WB_stage_NoB
uint64_t n_WB_stage_NoB = n_WB;
perfModel->WB_stage_NoB.set(n_WB_stage_NoB);

  // Dump Entrance point for info print (tracing)
  perfModel->entrancePoint = n_Enter;
  }
);

static SchedulingFunction *schedulingFunction_div = new SchedulingFunction(
  RV32_OOO_SchedulingFunctionSet,
  "div",
  25,
  [](PerformanceModel* perfModel_){
  RV32_OOO_PerformanceModel* perfModel = static_cast<RV32_OOO_PerformanceModel*>(perfModel_);
  // Enter
uint64_t n_Enter = perfModel->PC_stage;
// PCGen
uint64_t n_PCGen;
uint64_t n_PCGen_max;
n_PCGen_max = std::max({n_Enter, perfModel->noBranchPredModel.getPc()});
n_PCGen = n_PCGen_max + 1;
perfModel->noBranchPredModel.setPc_p(n_PCGen);
// PC_stage
uint64_t n_PC_stage;
n_PC_stage = std::max({n_PCGen, perfModel->IF_stage});
perfModel->PC_stage = n_PC_stage;
// IPort_R
uint64_t n_IPort_R;
n_IPort_R = n_PC_stage + 1;
// uA_Clobber
uint64_t n_uA_Clobber;
n_uA_Clobber = std::max({n_PC_stage, perfModel->clobberModel.getCb_out()});
// IF_stage
uint64_t n_IF_stage;
n_IF_stage = std::max({n_IPort_R, n_uA_Clobber, perfModel->IS_stage});
perfModel->IF_stage = n_IF_stage;
// Decoder
uint64_t n_Decoder;
n_Decoder = n_IF_stage + 1;
perfModel->scheduleModel.setDec_div(n_Decoder);
// IS_stage
uint64_t n_IS_stage;
n_IS_stage = std::max({n_Decoder, perfModel->IB_stage_OoO.get_min()});
perfModel->IS_stage = n_IS_stage;
// uA_OF_A
uint64_t n_uA_OF_A;
n_uA_OF_A = std::max({n_IS_stage, perfModel->scheduleModel.getXa()});
// uA_OF_B
uint64_t n_uA_OF_B;
n_uA_OF_B = std::max({n_IS_stage, perfModel->scheduleModel.getXb()});
// uA_Issue
uint64_t n_uA_Issue;
n_uA_Issue = std::max({n_IS_stage, perfModel->scheduleModel.getT_issue()});
// IB_stage_OoO
uint64_t n_IB_stage_OoO;
n_IB_stage_OoO = std::max({n_uA_OF_A, n_uA_OF_B, n_uA_Issue});
perfModel->IB_stage_OoO.replace_min(n_IB_stage_OoO);
// DIV
uint64_t n_DIV;
n_DIV = n_IB_stage_OoO + 4;
perfModel->scheduleModel.setXd(n_DIV);
perfModel->clobberModel.setCb_inRd(n_DIV);
perfModel->clobberModel.setCb_inR1(n_DIV);
perfModel->clobberModel.setCb_inR2(n_DIV);
// EX_stage_div_NoB
uint64_t n_EX_stage_div_NoB = n_DIV;
perfModel->EX_stage_div_NoB = n_EX_stage_div_NoB;
// WB
uint64_t n_WB;
n_WB = n_EX_stage_div_NoB + 1;
perfModel->scheduleModel.setT_wb(n_WB);
// WB_stage_NoB
uint64_t n_WB_stage_NoB = n_WB;
perfModel->WB_stage_NoB.set(n_WB_stage_NoB);

  // Dump Entrance point for info print (tracing)
  perfModel->entrancePoint = n_Enter;
  }
);

static SchedulingFunction *schedulingFunction_rem = new SchedulingFunction(
  RV32_OOO_SchedulingFunctionSet,
  "rem",
  26,
  [](PerformanceModel* perfModel_){
  RV32_OOO_PerformanceModel* perfModel = static_cast<RV32_OOO_PerformanceModel*>(perfModel_);
  // Enter
uint64_t n_Enter = perfModel->PC_stage;
// PCGen
uint64_t n_PCGen;
uint64_t n_PCGen_max;
n_PCGen_max = std::max({n_Enter, perfModel->noBranchPredModel.getPc()});
n_PCGen = n_PCGen_max + 1;
perfModel->noBranchPredModel.setPc_p(n_PCGen);
// PC_stage
uint64_t n_PC_stage;
n_PC_stage = std::max({n_PCGen, perfModel->IF_stage});
perfModel->PC_stage = n_PC_stage;
// IPort_R
uint64_t n_IPort_R;
n_IPort_R = n_PC_stage + 1;
// uA_Clobber
uint64_t n_uA_Clobber;
n_uA_Clobber = std::max({n_PC_stage, perfModel->clobberModel.getCb_out()});
// IF_stage
uint64_t n_IF_stage;
n_IF_stage = std::max({n_IPort_R, n_uA_Clobber, perfModel->IS_stage});
perfModel->IF_stage = n_IF_stage;
// Decoder
uint64_t n_Decoder;
n_Decoder = n_IF_stage + 1;
perfModel->scheduleModel.setDec_div(n_Decoder);
// IS_stage
uint64_t n_IS_stage;
n_IS_stage = std::max({n_Decoder, perfModel->IB_stage_OoO.get_min()});
perfModel->IS_stage = n_IS_stage;
// uA_OF_A
uint64_t n_uA_OF_A;
n_uA_OF_A = std::max({n_IS_stage, perfModel->scheduleModel.getXa()});
// uA_OF_B
uint64_t n_uA_OF_B;
n_uA_OF_B = std::max({n_IS_stage, perfModel->scheduleModel.getXb()});
// uA_Issue
uint64_t n_uA_Issue;
n_uA_Issue = std::max({n_IS_stage, perfModel->scheduleModel.getT_issue()});
// IB_stage_OoO
uint64_t n_IB_stage_OoO;
n_IB_stage_OoO = std::max({n_uA_OF_A, n_uA_OF_B, n_uA_Issue});
perfModel->IB_stage_OoO.replace_min(n_IB_stage_OoO);
// DIV
uint64_t n_DIV;
n_DIV = n_IB_stage_OoO + 4;
perfModel->scheduleModel.setXd(n_DIV);
perfModel->clobberModel.setCb_inRd(n_DIV);
perfModel->clobberModel.setCb_inR1(n_DIV);
perfModel->clobberModel.setCb_inR2(n_DIV);
// EX_stage_div_NoB
uint64_t n_EX_stage_div_NoB = n_DIV;
perfModel->EX_stage_div_NoB = n_EX_stage_div_NoB;
// WB
uint64_t n_WB;
n_WB = n_EX_stage_div_NoB + 1;
perfModel->scheduleModel.setT_wb(n_WB);
// WB_stage_NoB
uint64_t n_WB_stage_NoB = n_WB;
perfModel->WB_stage_NoB.set(n_WB_stage_NoB);

  // Dump Entrance point for info print (tracing)
  perfModel->entrancePoint = n_Enter;
  }
);

static SchedulingFunction *schedulingFunction_divu = new SchedulingFunction(
  RV32_OOO_SchedulingFunctionSet,
  "divu",
  27,
  [](PerformanceModel* perfModel_){
  RV32_OOO_PerformanceModel* perfModel = static_cast<RV32_OOO_PerformanceModel*>(perfModel_);
  // Enter
uint64_t n_Enter = perfModel->PC_stage;
// PCGen
uint64_t n_PCGen;
uint64_t n_PCGen_max;
n_PCGen_max = std::max({n_Enter, perfModel->noBranchPredModel.getPc()});
n_PCGen = n_PCGen_max + 1;
perfModel->noBranchPredModel.setPc_p(n_PCGen);
// PC_stage
uint64_t n_PC_stage;
n_PC_stage = std::max({n_PCGen, perfModel->IF_stage});
perfModel->PC_stage = n_PC_stage;
// IPort_R
uint64_t n_IPort_R;
n_IPort_R = n_PC_stage + 1;
// uA_Clobber
uint64_t n_uA_Clobber;
n_uA_Clobber = std::max({n_PC_stage, perfModel->clobberModel.getCb_out()});
// IF_stage
uint64_t n_IF_stage;
n_IF_stage = std::max({n_IPort_R, n_uA_Clobber, perfModel->IS_stage});
perfModel->IF_stage = n_IF_stage;
// Decoder
uint64_t n_Decoder;
n_Decoder = n_IF_stage + 1;
perfModel->scheduleModel.setDec_div(n_Decoder);
// IS_stage
uint64_t n_IS_stage;
n_IS_stage = std::max({n_Decoder, perfModel->IB_stage_OoO.get_min()});
perfModel->IS_stage = n_IS_stage;
// uA_OF_A
uint64_t n_uA_OF_A;
n_uA_OF_A = std::max({n_IS_stage, perfModel->scheduleModel.getXa()});
// uA_OF_B
uint64_t n_uA_OF_B;
n_uA_OF_B = std::max({n_IS_stage, perfModel->scheduleModel.getXb()});
// uA_Issue
uint64_t n_uA_Issue;
n_uA_Issue = std::max({n_IS_stage, perfModel->scheduleModel.getT_issue()});
// IB_stage_OoO
uint64_t n_IB_stage_OoO;
n_IB_stage_OoO = std::max({n_uA_OF_A, n_uA_OF_B, n_uA_Issue});
perfModel->IB_stage_OoO.replace_min(n_IB_stage_OoO);
// DIV
uint64_t n_DIV;
n_DIV = n_IB_stage_OoO + 4;
perfModel->scheduleModel.setXd(n_DIV);
perfModel->clobberModel.setCb_inRd(n_DIV);
perfModel->clobberModel.setCb_inR1(n_DIV);
perfModel->clobberModel.setCb_inR2(n_DIV);
// EX_stage_div_NoB
uint64_t n_EX_stage_div_NoB = n_DIV;
perfModel->EX_stage_div_NoB = n_EX_stage_div_NoB;
// WB
uint64_t n_WB;
n_WB = n_EX_stage_div_NoB + 1;
perfModel->scheduleModel.setT_wb(n_WB);
// WB_stage_NoB
uint64_t n_WB_stage_NoB = n_WB;
perfModel->WB_stage_NoB.set(n_WB_stage_NoB);

  // Dump Entrance point for info print (tracing)
  perfModel->entrancePoint = n_Enter;
  }
);

static SchedulingFunction *schedulingFunction_remu = new SchedulingFunction(
  RV32_OOO_SchedulingFunctionSet,
  "remu",
  28,
  [](PerformanceModel* perfModel_){
  RV32_OOO_PerformanceModel* perfModel = static_cast<RV32_OOO_PerformanceModel*>(perfModel_);
  // Enter
uint64_t n_Enter = perfModel->PC_stage;
// PCGen
uint64_t n_PCGen;
uint64_t n_PCGen_max;
n_PCGen_max = std::max({n_Enter, perfModel->noBranchPredModel.getPc()});
n_PCGen = n_PCGen_max + 1;
perfModel->noBranchPredModel.setPc_p(n_PCGen);
// PC_stage
uint64_t n_PC_stage;
n_PC_stage = std::max({n_PCGen, perfModel->IF_stage});
perfModel->PC_stage = n_PC_stage;
// IPort_R
uint64_t n_IPort_R;
n_IPort_R = n_PC_stage + 1;
// uA_Clobber
uint64_t n_uA_Clobber;
n_uA_Clobber = std::max({n_PC_stage, perfModel->clobberModel.getCb_out()});
// IF_stage
uint64_t n_IF_stage;
n_IF_stage = std::max({n_IPort_R, n_uA_Clobber, perfModel->IS_stage});
perfModel->IF_stage = n_IF_stage;
// Decoder
uint64_t n_Decoder;
n_Decoder = n_IF_stage + 1;
perfModel->scheduleModel.setDec_div(n_Decoder);
// IS_stage
uint64_t n_IS_stage;
n_IS_stage = std::max({n_Decoder, perfModel->IB_stage_OoO.get_min()});
perfModel->IS_stage = n_IS_stage;
// uA_OF_A
uint64_t n_uA_OF_A;
n_uA_OF_A = std::max({n_IS_stage, perfModel->scheduleModel.getXa()});
// uA_OF_B
uint64_t n_uA_OF_B;
n_uA_OF_B = std::max({n_IS_stage, perfModel->scheduleModel.getXb()});
// uA_Issue
uint64_t n_uA_Issue;
n_uA_Issue = std::max({n_IS_stage, perfModel->scheduleModel.getT_issue()});
// IB_stage_OoO
uint64_t n_IB_stage_OoO;
n_IB_stage_OoO = std::max({n_uA_OF_A, n_uA_OF_B, n_uA_Issue});
perfModel->IB_stage_OoO.replace_min(n_IB_stage_OoO);
// DIV
uint64_t n_DIV;
n_DIV = n_IB_stage_OoO + 4;
perfModel->scheduleModel.setXd(n_DIV);
perfModel->clobberModel.setCb_inRd(n_DIV);
perfModel->clobberModel.setCb_inR1(n_DIV);
perfModel->clobberModel.setCb_inR2(n_DIV);
// EX_stage_div_NoB
uint64_t n_EX_stage_div_NoB = n_DIV;
perfModel->EX_stage_div_NoB = n_EX_stage_div_NoB;
// WB
uint64_t n_WB;
n_WB = n_EX_stage_div_NoB + 1;
perfModel->scheduleModel.setT_wb(n_WB);
// WB_stage_NoB
uint64_t n_WB_stage_NoB = n_WB;
perfModel->WB_stage_NoB.set(n_WB_stage_NoB);

  // Dump Entrance point for info print (tracing)
  perfModel->entrancePoint = n_Enter;
  }
);

static SchedulingFunction *schedulingFunction_csrrw = new SchedulingFunction(
  RV32_OOO_SchedulingFunctionSet,
  "csrrw",
  29,
  [](PerformanceModel* perfModel_){
  RV32_OOO_PerformanceModel* perfModel = static_cast<RV32_OOO_PerformanceModel*>(perfModel_);
  // Enter
uint64_t n_Enter = perfModel->PC_stage;
// PCGen
uint64_t n_PCGen;
uint64_t n_PCGen_max;
n_PCGen_max = std::max({n_Enter, perfModel->noBranchPredModel.getPc()});
n_PCGen = n_PCGen_max + 1;
perfModel->noBranchPredModel.setPc_p(n_PCGen);
// PC_stage
uint64_t n_PC_stage;
n_PC_stage = std::max({n_PCGen, perfModel->IF_stage});
perfModel->PC_stage = n_PC_stage;
// IPort_R
uint64_t n_IPort_R;
n_IPort_R = n_PC_stage + 1;
// uA_Clobber
uint64_t n_uA_Clobber;
n_uA_Clobber = std::max({n_PC_stage, perfModel->clobberModel.getCb_out()});
// IF_stage
uint64_t n_IF_stage;
n_IF_stage = std::max({n_IPort_R, n_uA_Clobber, perfModel->IS_stage});
perfModel->IF_stage = n_IF_stage;
// Decoder
uint64_t n_Decoder;
n_Decoder = n_IF_stage + 1;
perfModel->scheduleModel.setDec_alu(n_Decoder);
// IS_stage
uint64_t n_IS_stage;
n_IS_stage = std::max({n_Decoder, perfModel->IB_stage_OoO.get_min()});
perfModel->IS_stage = n_IS_stage;
// uA_OF_A
uint64_t n_uA_OF_A;
n_uA_OF_A = std::max({n_IS_stage, perfModel->scheduleModel.getXa()});
// uA_Issue
uint64_t n_uA_Issue;
n_uA_Issue = std::max({n_IS_stage, perfModel->scheduleModel.getT_issue()});
// IB_stage_OoO
uint64_t n_IB_stage_OoO;
n_IB_stage_OoO = std::max({n_uA_OF_A, n_uA_Issue});
perfModel->IB_stage_OoO.replace_min(n_IB_stage_OoO);
// CSR
uint64_t n_CSR;
n_CSR = n_IB_stage_OoO + 1;
perfModel->scheduleModel.setXd(n_CSR);
perfModel->clobberModel.setCb_inRd(n_CSR);
// EX_stage_alu_NoB
uint64_t n_EX_stage_alu_NoB = n_CSR;
perfModel->EX_stage_alu_NoB = n_EX_stage_alu_NoB;
// WB
uint64_t n_WB;
n_WB = n_EX_stage_alu_NoB + 1;
perfModel->scheduleModel.setT_wb(n_WB);
// WB_stage_NoB
uint64_t n_WB_stage_NoB = n_WB;
perfModel->WB_stage_NoB.set(n_WB_stage_NoB);

  // Dump Entrance point for info print (tracing)
  perfModel->entrancePoint = n_Enter;
  }
);

static SchedulingFunction *schedulingFunction_csrrs = new SchedulingFunction(
  RV32_OOO_SchedulingFunctionSet,
  "csrrs",
  30,
  [](PerformanceModel* perfModel_){
  RV32_OOO_PerformanceModel* perfModel = static_cast<RV32_OOO_PerformanceModel*>(perfModel_);
  // Enter
uint64_t n_Enter = perfModel->PC_stage;
// PCGen
uint64_t n_PCGen;
uint64_t n_PCGen_max;
n_PCGen_max = std::max({n_Enter, perfModel->noBranchPredModel.getPc()});
n_PCGen = n_PCGen_max + 1;
perfModel->noBranchPredModel.setPc_p(n_PCGen);
// PC_stage
uint64_t n_PC_stage;
n_PC_stage = std::max({n_PCGen, perfModel->IF_stage});
perfModel->PC_stage = n_PC_stage;
// IPort_R
uint64_t n_IPort_R;
n_IPort_R = n_PC_stage + 1;
// uA_Clobber
uint64_t n_uA_Clobber;
n_uA_Clobber = std::max({n_PC_stage, perfModel->clobberModel.getCb_out()});
// IF_stage
uint64_t n_IF_stage;
n_IF_stage = std::max({n_IPort_R, n_uA_Clobber, perfModel->IS_stage});
perfModel->IF_stage = n_IF_stage;
// Decoder
uint64_t n_Decoder;
n_Decoder = n_IF_stage + 1;
perfModel->scheduleModel.setDec_alu(n_Decoder);
// IS_stage
uint64_t n_IS_stage;
n_IS_stage = std::max({n_Decoder, perfModel->IB_stage_OoO.get_min()});
perfModel->IS_stage = n_IS_stage;
// uA_OF_A
uint64_t n_uA_OF_A;
n_uA_OF_A = std::max({n_IS_stage, perfModel->scheduleModel.getXa()});
// uA_Issue
uint64_t n_uA_Issue;
n_uA_Issue = std::max({n_IS_stage, perfModel->scheduleModel.getT_issue()});
// IB_stage_OoO
uint64_t n_IB_stage_OoO;
n_IB_stage_OoO = std::max({n_uA_OF_A, n_uA_Issue});
perfModel->IB_stage_OoO.replace_min(n_IB_stage_OoO);
// CSR
uint64_t n_CSR;
n_CSR = n_IB_stage_OoO + 1;
perfModel->scheduleModel.setXd(n_CSR);
perfModel->clobberModel.setCb_inRd(n_CSR);
// EX_stage_alu_NoB
uint64_t n_EX_stage_alu_NoB = n_CSR;
perfModel->EX_stage_alu_NoB = n_EX_stage_alu_NoB;
// WB
uint64_t n_WB;
n_WB = n_EX_stage_alu_NoB + 1;
perfModel->scheduleModel.setT_wb(n_WB);
// WB_stage_NoB
uint64_t n_WB_stage_NoB = n_WB;
perfModel->WB_stage_NoB.set(n_WB_stage_NoB);

  // Dump Entrance point for info print (tracing)
  perfModel->entrancePoint = n_Enter;
  }
);

static SchedulingFunction *schedulingFunction_csrrc = new SchedulingFunction(
  RV32_OOO_SchedulingFunctionSet,
  "csrrc",
  31,
  [](PerformanceModel* perfModel_){
  RV32_OOO_PerformanceModel* perfModel = static_cast<RV32_OOO_PerformanceModel*>(perfModel_);
  // Enter
uint64_t n_Enter = perfModel->PC_stage;
// PCGen
uint64_t n_PCGen;
uint64_t n_PCGen_max;
n_PCGen_max = std::max({n_Enter, perfModel->noBranchPredModel.getPc()});
n_PCGen = n_PCGen_max + 1;
perfModel->noBranchPredModel.setPc_p(n_PCGen);
// PC_stage
uint64_t n_PC_stage;
n_PC_stage = std::max({n_PCGen, perfModel->IF_stage});
perfModel->PC_stage = n_PC_stage;
// IPort_R
uint64_t n_IPort_R;
n_IPort_R = n_PC_stage + 1;
// uA_Clobber
uint64_t n_uA_Clobber;
n_uA_Clobber = std::max({n_PC_stage, perfModel->clobberModel.getCb_out()});
// IF_stage
uint64_t n_IF_stage;
n_IF_stage = std::max({n_IPort_R, n_uA_Clobber, perfModel->IS_stage});
perfModel->IF_stage = n_IF_stage;
// Decoder
uint64_t n_Decoder;
n_Decoder = n_IF_stage + 1;
perfModel->scheduleModel.setDec_alu(n_Decoder);
// IS_stage
uint64_t n_IS_stage;
n_IS_stage = std::max({n_Decoder, perfModel->IB_stage_OoO.get_min()});
perfModel->IS_stage = n_IS_stage;
// uA_OF_A
uint64_t n_uA_OF_A;
n_uA_OF_A = std::max({n_IS_stage, perfModel->scheduleModel.getXa()});
// uA_Issue
uint64_t n_uA_Issue;
n_uA_Issue = std::max({n_IS_stage, perfModel->scheduleModel.getT_issue()});
// IB_stage_OoO
uint64_t n_IB_stage_OoO;
n_IB_stage_OoO = std::max({n_uA_OF_A, n_uA_Issue});
perfModel->IB_stage_OoO.replace_min(n_IB_stage_OoO);
// CSR
uint64_t n_CSR;
n_CSR = n_IB_stage_OoO + 1;
perfModel->scheduleModel.setXd(n_CSR);
perfModel->clobberModel.setCb_inRd(n_CSR);
// EX_stage_alu_NoB
uint64_t n_EX_stage_alu_NoB = n_CSR;
perfModel->EX_stage_alu_NoB = n_EX_stage_alu_NoB;
// WB
uint64_t n_WB;
n_WB = n_EX_stage_alu_NoB + 1;
perfModel->scheduleModel.setT_wb(n_WB);
// WB_stage_NoB
uint64_t n_WB_stage_NoB = n_WB;
perfModel->WB_stage_NoB.set(n_WB_stage_NoB);

  // Dump Entrance point for info print (tracing)
  perfModel->entrancePoint = n_Enter;
  }
);

static SchedulingFunction *schedulingFunction_csrrwi = new SchedulingFunction(
  RV32_OOO_SchedulingFunctionSet,
  "csrrwi",
  32,
  [](PerformanceModel* perfModel_){
  RV32_OOO_PerformanceModel* perfModel = static_cast<RV32_OOO_PerformanceModel*>(perfModel_);
  // Enter
uint64_t n_Enter = perfModel->PC_stage;
// PCGen
uint64_t n_PCGen;
uint64_t n_PCGen_max;
n_PCGen_max = std::max({n_Enter, perfModel->noBranchPredModel.getPc()});
n_PCGen = n_PCGen_max + 1;
perfModel->noBranchPredModel.setPc_p(n_PCGen);
// PC_stage
uint64_t n_PC_stage;
n_PC_stage = std::max({n_PCGen, perfModel->IF_stage});
perfModel->PC_stage = n_PC_stage;
// IPort_R
uint64_t n_IPort_R;
n_IPort_R = n_PC_stage + 1;
// uA_Clobber
uint64_t n_uA_Clobber;
n_uA_Clobber = std::max({n_PC_stage, perfModel->clobberModel.getCb_out()});
// IF_stage
uint64_t n_IF_stage;
n_IF_stage = std::max({n_IPort_R, n_uA_Clobber, perfModel->IS_stage});
perfModel->IF_stage = n_IF_stage;
// Decoder
uint64_t n_Decoder;
n_Decoder = n_IF_stage + 1;
perfModel->scheduleModel.setDec_alu(n_Decoder);
// IS_stage
uint64_t n_IS_stage;
n_IS_stage = std::max({n_Decoder, perfModel->IB_stage_OoO.get_min()});
perfModel->IS_stage = n_IS_stage;
// uA_Issue
uint64_t n_uA_Issue;
n_uA_Issue = std::max({n_IS_stage, perfModel->scheduleModel.getT_issue()});
// IB_stage_OoO
uint64_t n_IB_stage_OoO = n_uA_Issue;
perfModel->IB_stage_OoO.replace_min(n_IB_stage_OoO);
// CSR
uint64_t n_CSR;
n_CSR = n_IB_stage_OoO + 1;
perfModel->scheduleModel.setXd(n_CSR);
perfModel->clobberModel.setCb_inRd(n_CSR);
// EX_stage_alu_NoB
uint64_t n_EX_stage_alu_NoB = n_CSR;
perfModel->EX_stage_alu_NoB = n_EX_stage_alu_NoB;
// WB
uint64_t n_WB;
n_WB = n_EX_stage_alu_NoB + 1;
perfModel->scheduleModel.setT_wb(n_WB);
// WB_stage_NoB
uint64_t n_WB_stage_NoB = n_WB;
perfModel->WB_stage_NoB.set(n_WB_stage_NoB);

  // Dump Entrance point for info print (tracing)
  perfModel->entrancePoint = n_Enter;
  }
);

static SchedulingFunction *schedulingFunction_csrrsi = new SchedulingFunction(
  RV32_OOO_SchedulingFunctionSet,
  "csrrsi",
  33,
  [](PerformanceModel* perfModel_){
  RV32_OOO_PerformanceModel* perfModel = static_cast<RV32_OOO_PerformanceModel*>(perfModel_);
  // Enter
uint64_t n_Enter = perfModel->PC_stage;
// PCGen
uint64_t n_PCGen;
uint64_t n_PCGen_max;
n_PCGen_max = std::max({n_Enter, perfModel->noBranchPredModel.getPc()});
n_PCGen = n_PCGen_max + 1;
perfModel->noBranchPredModel.setPc_p(n_PCGen);
// PC_stage
uint64_t n_PC_stage;
n_PC_stage = std::max({n_PCGen, perfModel->IF_stage});
perfModel->PC_stage = n_PC_stage;
// IPort_R
uint64_t n_IPort_R;
n_IPort_R = n_PC_stage + 1;
// uA_Clobber
uint64_t n_uA_Clobber;
n_uA_Clobber = std::max({n_PC_stage, perfModel->clobberModel.getCb_out()});
// IF_stage
uint64_t n_IF_stage;
n_IF_stage = std::max({n_IPort_R, n_uA_Clobber, perfModel->IS_stage});
perfModel->IF_stage = n_IF_stage;
// Decoder
uint64_t n_Decoder;
n_Decoder = n_IF_stage + 1;
perfModel->scheduleModel.setDec_alu(n_Decoder);
// IS_stage
uint64_t n_IS_stage;
n_IS_stage = std::max({n_Decoder, perfModel->IB_stage_OoO.get_min()});
perfModel->IS_stage = n_IS_stage;
// uA_Issue
uint64_t n_uA_Issue;
n_uA_Issue = std::max({n_IS_stage, perfModel->scheduleModel.getT_issue()});
// IB_stage_OoO
uint64_t n_IB_stage_OoO = n_uA_Issue;
perfModel->IB_stage_OoO.replace_min(n_IB_stage_OoO);
// CSR
uint64_t n_CSR;
n_CSR = n_IB_stage_OoO + 1;
perfModel->scheduleModel.setXd(n_CSR);
perfModel->clobberModel.setCb_inRd(n_CSR);
// EX_stage_alu_NoB
uint64_t n_EX_stage_alu_NoB = n_CSR;
perfModel->EX_stage_alu_NoB = n_EX_stage_alu_NoB;
// WB
uint64_t n_WB;
n_WB = n_EX_stage_alu_NoB + 1;
perfModel->scheduleModel.setT_wb(n_WB);
// WB_stage_NoB
uint64_t n_WB_stage_NoB = n_WB;
perfModel->WB_stage_NoB.set(n_WB_stage_NoB);

  // Dump Entrance point for info print (tracing)
  perfModel->entrancePoint = n_Enter;
  }
);

static SchedulingFunction *schedulingFunction_csrrci = new SchedulingFunction(
  RV32_OOO_SchedulingFunctionSet,
  "csrrci",
  34,
  [](PerformanceModel* perfModel_){
  RV32_OOO_PerformanceModel* perfModel = static_cast<RV32_OOO_PerformanceModel*>(perfModel_);
  // Enter
uint64_t n_Enter = perfModel->PC_stage;
// PCGen
uint64_t n_PCGen;
uint64_t n_PCGen_max;
n_PCGen_max = std::max({n_Enter, perfModel->noBranchPredModel.getPc()});
n_PCGen = n_PCGen_max + 1;
perfModel->noBranchPredModel.setPc_p(n_PCGen);
// PC_stage
uint64_t n_PC_stage;
n_PC_stage = std::max({n_PCGen, perfModel->IF_stage});
perfModel->PC_stage = n_PC_stage;
// IPort_R
uint64_t n_IPort_R;
n_IPort_R = n_PC_stage + 1;
// uA_Clobber
uint64_t n_uA_Clobber;
n_uA_Clobber = std::max({n_PC_stage, perfModel->clobberModel.getCb_out()});
// IF_stage
uint64_t n_IF_stage;
n_IF_stage = std::max({n_IPort_R, n_uA_Clobber, perfModel->IS_stage});
perfModel->IF_stage = n_IF_stage;
// Decoder
uint64_t n_Decoder;
n_Decoder = n_IF_stage + 1;
perfModel->scheduleModel.setDec_alu(n_Decoder);
// IS_stage
uint64_t n_IS_stage;
n_IS_stage = std::max({n_Decoder, perfModel->IB_stage_OoO.get_min()});
perfModel->IS_stage = n_IS_stage;
// uA_Issue
uint64_t n_uA_Issue;
n_uA_Issue = std::max({n_IS_stage, perfModel->scheduleModel.getT_issue()});
// IB_stage_OoO
uint64_t n_IB_stage_OoO = n_uA_Issue;
perfModel->IB_stage_OoO.replace_min(n_IB_stage_OoO);
// CSR
uint64_t n_CSR;
n_CSR = n_IB_stage_OoO + 1;
perfModel->scheduleModel.setXd(n_CSR);
perfModel->clobberModel.setCb_inRd(n_CSR);
// EX_stage_alu_NoB
uint64_t n_EX_stage_alu_NoB = n_CSR;
perfModel->EX_stage_alu_NoB = n_EX_stage_alu_NoB;
// WB
uint64_t n_WB;
n_WB = n_EX_stage_alu_NoB + 1;
perfModel->scheduleModel.setT_wb(n_WB);
// WB_stage_NoB
uint64_t n_WB_stage_NoB = n_WB;
perfModel->WB_stage_NoB.set(n_WB_stage_NoB);

  // Dump Entrance point for info print (tracing)
  perfModel->entrancePoint = n_Enter;
  }
);

static SchedulingFunction *schedulingFunction_sb = new SchedulingFunction(
  RV32_OOO_SchedulingFunctionSet,
  "sb",
  35,
  [](PerformanceModel* perfModel_){
  RV32_OOO_PerformanceModel* perfModel = static_cast<RV32_OOO_PerformanceModel*>(perfModel_);
  // Enter
uint64_t n_Enter = perfModel->PC_stage;
// PCGen
uint64_t n_PCGen;
uint64_t n_PCGen_max;
n_PCGen_max = std::max({n_Enter, perfModel->noBranchPredModel.getPc()});
n_PCGen = n_PCGen_max + 1;
perfModel->noBranchPredModel.setPc_p(n_PCGen);
// PC_stage
uint64_t n_PC_stage;
n_PC_stage = std::max({n_PCGen, perfModel->IF_stage});
perfModel->PC_stage = n_PC_stage;
// IPort_R
uint64_t n_IPort_R;
n_IPort_R = n_PC_stage + 1;
// IF_stage
uint64_t n_IF_stage;
n_IF_stage = std::max({n_IPort_R, perfModel->IS_stage});
perfModel->IF_stage = n_IF_stage;
// Decoder
uint64_t n_Decoder;
n_Decoder = n_IF_stage + 1;
perfModel->scheduleModel.setDec_st(n_Decoder);
// IS_stage
uint64_t n_IS_stage;
n_IS_stage = std::max({n_Decoder, perfModel->IB_stage_OoO.get_min()});
perfModel->IS_stage = n_IS_stage;
// uA_OF_A
uint64_t n_uA_OF_A;
n_uA_OF_A = std::max({n_IS_stage, perfModel->scheduleModel.getXa()});
// uA_OF_B
uint64_t n_uA_OF_B;
n_uA_OF_B = std::max({n_IS_stage, perfModel->scheduleModel.getXb()});
// uA_Issue
uint64_t n_uA_Issue;
n_uA_Issue = std::max({n_IS_stage, perfModel->scheduleModel.getT_issue()});
// IB_stage_OoO
uint64_t n_IB_stage_OoO;
n_IB_stage_OoO = std::max({n_uA_OF_A, n_uA_OF_B, n_uA_Issue});
perfModel->IB_stage_OoO.replace_min(n_IB_stage_OoO);
// DPort_W
uint64_t n_DPort_W;
n_DPort_W = n_IB_stage_OoO + 1;
perfModel->clobberModel.setCb_inR1(n_DPort_W);
perfModel->clobberModel.setCb_inR2(n_DPort_W);
// EX_stage_lsu_NoB
uint64_t n_EX_stage_lsu_NoB = n_DPort_W;
perfModel->EX_stage_lsu_NoB.set(n_EX_stage_lsu_NoB);
perfModel->EX_stage_suv_NoB = n_EX_stage_lsu_NoB;
// WB
uint64_t n_WB;
n_WB = n_EX_stage_lsu_NoB + 1;
perfModel->scheduleModel.setT_wb(n_WB);
// WB_stage_NoB
uint64_t n_WB_stage_NoB = n_WB;
perfModel->WB_stage_NoB.set(n_WB_stage_NoB);

  // Dump Entrance point for info print (tracing)
  perfModel->entrancePoint = n_Enter;
  }
);

static SchedulingFunction *schedulingFunction_sh = new SchedulingFunction(
  RV32_OOO_SchedulingFunctionSet,
  "sh",
  36,
  [](PerformanceModel* perfModel_){
  RV32_OOO_PerformanceModel* perfModel = static_cast<RV32_OOO_PerformanceModel*>(perfModel_);
  // Enter
uint64_t n_Enter = perfModel->PC_stage;
// PCGen
uint64_t n_PCGen;
uint64_t n_PCGen_max;
n_PCGen_max = std::max({n_Enter, perfModel->noBranchPredModel.getPc()});
n_PCGen = n_PCGen_max + 1;
perfModel->noBranchPredModel.setPc_p(n_PCGen);
// PC_stage
uint64_t n_PC_stage;
n_PC_stage = std::max({n_PCGen, perfModel->IF_stage});
perfModel->PC_stage = n_PC_stage;
// IPort_R
uint64_t n_IPort_R;
n_IPort_R = n_PC_stage + 1;
// IF_stage
uint64_t n_IF_stage;
n_IF_stage = std::max({n_IPort_R, perfModel->IS_stage});
perfModel->IF_stage = n_IF_stage;
// Decoder
uint64_t n_Decoder;
n_Decoder = n_IF_stage + 1;
perfModel->scheduleModel.setDec_st(n_Decoder);
// IS_stage
uint64_t n_IS_stage;
n_IS_stage = std::max({n_Decoder, perfModel->IB_stage_OoO.get_min()});
perfModel->IS_stage = n_IS_stage;
// uA_OF_A
uint64_t n_uA_OF_A;
n_uA_OF_A = std::max({n_IS_stage, perfModel->scheduleModel.getXa()});
// uA_OF_B
uint64_t n_uA_OF_B;
n_uA_OF_B = std::max({n_IS_stage, perfModel->scheduleModel.getXb()});
// uA_Issue
uint64_t n_uA_Issue;
n_uA_Issue = std::max({n_IS_stage, perfModel->scheduleModel.getT_issue()});
// IB_stage_OoO
uint64_t n_IB_stage_OoO;
n_IB_stage_OoO = std::max({n_uA_OF_A, n_uA_OF_B, n_uA_Issue});
perfModel->IB_stage_OoO.replace_min(n_IB_stage_OoO);
// DPort_W
uint64_t n_DPort_W;
n_DPort_W = n_IB_stage_OoO + 1;
perfModel->clobberModel.setCb_inR1(n_DPort_W);
perfModel->clobberModel.setCb_inR2(n_DPort_W);
// EX_stage_lsu_NoB
uint64_t n_EX_stage_lsu_NoB = n_DPort_W;
perfModel->EX_stage_lsu_NoB.set(n_EX_stage_lsu_NoB);
perfModel->EX_stage_suv_NoB = n_EX_stage_lsu_NoB;
// WB
uint64_t n_WB;
n_WB = n_EX_stage_lsu_NoB + 1;
perfModel->scheduleModel.setT_wb(n_WB);
// WB_stage_NoB
uint64_t n_WB_stage_NoB = n_WB;
perfModel->WB_stage_NoB.set(n_WB_stage_NoB);

  // Dump Entrance point for info print (tracing)
  perfModel->entrancePoint = n_Enter;
  }
);

static SchedulingFunction *schedulingFunction_sw = new SchedulingFunction(
  RV32_OOO_SchedulingFunctionSet,
  "sw",
  37,
  [](PerformanceModel* perfModel_){
  RV32_OOO_PerformanceModel* perfModel = static_cast<RV32_OOO_PerformanceModel*>(perfModel_);
  // Enter
uint64_t n_Enter = perfModel->PC_stage;
// PCGen
uint64_t n_PCGen;
uint64_t n_PCGen_max;
n_PCGen_max = std::max({n_Enter, perfModel->noBranchPredModel.getPc()});
n_PCGen = n_PCGen_max + 1;
perfModel->noBranchPredModel.setPc_p(n_PCGen);
// PC_stage
uint64_t n_PC_stage;
n_PC_stage = std::max({n_PCGen, perfModel->IF_stage});
perfModel->PC_stage = n_PC_stage;
// IPort_R
uint64_t n_IPort_R;
n_IPort_R = n_PC_stage + 1;
// IF_stage
uint64_t n_IF_stage;
n_IF_stage = std::max({n_IPort_R, perfModel->IS_stage});
perfModel->IF_stage = n_IF_stage;
// Decoder
uint64_t n_Decoder;
n_Decoder = n_IF_stage + 1;
perfModel->scheduleModel.setDec_st(n_Decoder);
// IS_stage
uint64_t n_IS_stage;
n_IS_stage = std::max({n_Decoder, perfModel->IB_stage_OoO.get_min()});
perfModel->IS_stage = n_IS_stage;
// uA_OF_A
uint64_t n_uA_OF_A;
n_uA_OF_A = std::max({n_IS_stage, perfModel->scheduleModel.getXa()});
// uA_OF_B
uint64_t n_uA_OF_B;
n_uA_OF_B = std::max({n_IS_stage, perfModel->scheduleModel.getXb()});
// uA_Issue
uint64_t n_uA_Issue;
n_uA_Issue = std::max({n_IS_stage, perfModel->scheduleModel.getT_issue()});
// IB_stage_OoO
uint64_t n_IB_stage_OoO;
n_IB_stage_OoO = std::max({n_uA_OF_A, n_uA_OF_B, n_uA_Issue});
perfModel->IB_stage_OoO.replace_min(n_IB_stage_OoO);
// DPort_W
uint64_t n_DPort_W;
n_DPort_W = n_IB_stage_OoO + 1;
perfModel->clobberModel.setCb_inR1(n_DPort_W);
perfModel->clobberModel.setCb_inR2(n_DPort_W);
// EX_stage_lsu_NoB
uint64_t n_EX_stage_lsu_NoB = n_DPort_W;
perfModel->EX_stage_lsu_NoB.set(n_EX_stage_lsu_NoB);
perfModel->EX_stage_suv_NoB = n_EX_stage_lsu_NoB;
// WB
uint64_t n_WB;
n_WB = n_EX_stage_lsu_NoB + 1;
perfModel->scheduleModel.setT_wb(n_WB);
// WB_stage_NoB
uint64_t n_WB_stage_NoB = n_WB;
perfModel->WB_stage_NoB.set(n_WB_stage_NoB);

  // Dump Entrance point for info print (tracing)
  perfModel->entrancePoint = n_Enter;
  }
);

static SchedulingFunction *schedulingFunction_lw = new SchedulingFunction(
  RV32_OOO_SchedulingFunctionSet,
  "lw",
  38,
  [](PerformanceModel* perfModel_){
  RV32_OOO_PerformanceModel* perfModel = static_cast<RV32_OOO_PerformanceModel*>(perfModel_);
  // Enter
uint64_t n_Enter = perfModel->PC_stage;
// PCGen
uint64_t n_PCGen;
uint64_t n_PCGen_max;
n_PCGen_max = std::max({n_Enter, perfModel->noBranchPredModel.getPc()});
n_PCGen = n_PCGen_max + 1;
perfModel->noBranchPredModel.setPc_p(n_PCGen);
// PC_stage
uint64_t n_PC_stage;
n_PC_stage = std::max({n_PCGen, perfModel->IF_stage});
perfModel->PC_stage = n_PC_stage;
// IPort_R
uint64_t n_IPort_R;
n_IPort_R = n_PC_stage + 1;
// uA_Clobber
uint64_t n_uA_Clobber;
n_uA_Clobber = std::max({n_PC_stage, perfModel->clobberModel.getCb_out()});
// IF_stage
uint64_t n_IF_stage;
n_IF_stage = std::max({n_IPort_R, n_uA_Clobber, perfModel->IS_stage});
perfModel->IF_stage = n_IF_stage;
// Decoder
uint64_t n_Decoder;
n_Decoder = n_IF_stage + 1;
perfModel->scheduleModel.setDec_ld(n_Decoder);
// IS_stage
uint64_t n_IS_stage;
n_IS_stage = std::max({n_Decoder, perfModel->IB_stage_OoO.get_min()});
perfModel->IS_stage = n_IS_stage;
// uA_OF_A
uint64_t n_uA_OF_A;
n_uA_OF_A = std::max({n_IS_stage, perfModel->scheduleModel.getXa()});
// uA_Issue
uint64_t n_uA_Issue;
n_uA_Issue = std::max({n_IS_stage, perfModel->scheduleModel.getT_issue()});
// IB_stage_OoO
uint64_t n_IB_stage_OoO;
n_IB_stage_OoO = std::max({n_uA_OF_A, n_uA_Issue});
perfModel->IB_stage_OoO.replace_min(n_IB_stage_OoO);
// LSU
uint64_t n_LSU;
n_LSU = n_IB_stage_OoO + 1;
// EX_stage_lu0v_NoB
uint64_t n_EX_stage_lu0v_NoB = n_LSU;
perfModel->EX_stage_lu0v_NoB = n_EX_stage_lu0v_NoB;
// DPort_R
uint64_t n_DPort_R;
n_DPort_R = n_EX_stage_lu0v_NoB + 1;
perfModel->scheduleModel.setXd(n_DPort_R);
perfModel->clobberModel.setCb_inRd(n_DPort_R);
// EX_stage_lsu_NoB
uint64_t n_EX_stage_lsu_NoB = n_DPort_R;
perfModel->EX_stage_lsu_NoB.set(n_EX_stage_lsu_NoB);
perfModel->EX_stage_lu1v_NoB = n_EX_stage_lsu_NoB;
// WB
uint64_t n_WB;
n_WB = n_EX_stage_lsu_NoB + 1;
perfModel->scheduleModel.setT_wb(n_WB);
// WB_stage_NoB
uint64_t n_WB_stage_NoB = n_WB;
perfModel->WB_stage_NoB.set(n_WB_stage_NoB);

  // Dump Entrance point for info print (tracing)
  perfModel->entrancePoint = n_Enter;
  }
);

static SchedulingFunction *schedulingFunction_lh = new SchedulingFunction(
  RV32_OOO_SchedulingFunctionSet,
  "lh",
  39,
  [](PerformanceModel* perfModel_){
  RV32_OOO_PerformanceModel* perfModel = static_cast<RV32_OOO_PerformanceModel*>(perfModel_);
  // Enter
uint64_t n_Enter = perfModel->PC_stage;
// PCGen
uint64_t n_PCGen;
uint64_t n_PCGen_max;
n_PCGen_max = std::max({n_Enter, perfModel->noBranchPredModel.getPc()});
n_PCGen = n_PCGen_max + 1;
perfModel->noBranchPredModel.setPc_p(n_PCGen);
// PC_stage
uint64_t n_PC_stage;
n_PC_stage = std::max({n_PCGen, perfModel->IF_stage});
perfModel->PC_stage = n_PC_stage;
// IPort_R
uint64_t n_IPort_R;
n_IPort_R = n_PC_stage + 1;
// uA_Clobber
uint64_t n_uA_Clobber;
n_uA_Clobber = std::max({n_PC_stage, perfModel->clobberModel.getCb_out()});
// IF_stage
uint64_t n_IF_stage;
n_IF_stage = std::max({n_IPort_R, n_uA_Clobber, perfModel->IS_stage});
perfModel->IF_stage = n_IF_stage;
// Decoder
uint64_t n_Decoder;
n_Decoder = n_IF_stage + 1;
perfModel->scheduleModel.setDec_ld(n_Decoder);
// IS_stage
uint64_t n_IS_stage;
n_IS_stage = std::max({n_Decoder, perfModel->IB_stage_OoO.get_min()});
perfModel->IS_stage = n_IS_stage;
// uA_OF_A
uint64_t n_uA_OF_A;
n_uA_OF_A = std::max({n_IS_stage, perfModel->scheduleModel.getXa()});
// uA_Issue
uint64_t n_uA_Issue;
n_uA_Issue = std::max({n_IS_stage, perfModel->scheduleModel.getT_issue()});
// IB_stage_OoO
uint64_t n_IB_stage_OoO;
n_IB_stage_OoO = std::max({n_uA_OF_A, n_uA_Issue});
perfModel->IB_stage_OoO.replace_min(n_IB_stage_OoO);
// LSU
uint64_t n_LSU;
n_LSU = n_IB_stage_OoO + 1;
// EX_stage_lu0v_NoB
uint64_t n_EX_stage_lu0v_NoB = n_LSU;
perfModel->EX_stage_lu0v_NoB = n_EX_stage_lu0v_NoB;
// DPort_R
uint64_t n_DPort_R;
n_DPort_R = n_EX_stage_lu0v_NoB + 1;
perfModel->scheduleModel.setXd(n_DPort_R);
perfModel->clobberModel.setCb_inRd(n_DPort_R);
// EX_stage_lsu_NoB
uint64_t n_EX_stage_lsu_NoB = n_DPort_R;
perfModel->EX_stage_lsu_NoB.set(n_EX_stage_lsu_NoB);
perfModel->EX_stage_lu1v_NoB = n_EX_stage_lsu_NoB;
// WB
uint64_t n_WB;
n_WB = n_EX_stage_lsu_NoB + 1;
perfModel->scheduleModel.setT_wb(n_WB);
// WB_stage_NoB
uint64_t n_WB_stage_NoB = n_WB;
perfModel->WB_stage_NoB.set(n_WB_stage_NoB);

  // Dump Entrance point for info print (tracing)
  perfModel->entrancePoint = n_Enter;
  }
);

static SchedulingFunction *schedulingFunction_lhu = new SchedulingFunction(
  RV32_OOO_SchedulingFunctionSet,
  "lhu",
  40,
  [](PerformanceModel* perfModel_){
  RV32_OOO_PerformanceModel* perfModel = static_cast<RV32_OOO_PerformanceModel*>(perfModel_);
  // Enter
uint64_t n_Enter = perfModel->PC_stage;
// PCGen
uint64_t n_PCGen;
uint64_t n_PCGen_max;
n_PCGen_max = std::max({n_Enter, perfModel->noBranchPredModel.getPc()});
n_PCGen = n_PCGen_max + 1;
perfModel->noBranchPredModel.setPc_p(n_PCGen);
// PC_stage
uint64_t n_PC_stage;
n_PC_stage = std::max({n_PCGen, perfModel->IF_stage});
perfModel->PC_stage = n_PC_stage;
// IPort_R
uint64_t n_IPort_R;
n_IPort_R = n_PC_stage + 1;
// uA_Clobber
uint64_t n_uA_Clobber;
n_uA_Clobber = std::max({n_PC_stage, perfModel->clobberModel.getCb_out()});
// IF_stage
uint64_t n_IF_stage;
n_IF_stage = std::max({n_IPort_R, n_uA_Clobber, perfModel->IS_stage});
perfModel->IF_stage = n_IF_stage;
// Decoder
uint64_t n_Decoder;
n_Decoder = n_IF_stage + 1;
perfModel->scheduleModel.setDec_ld(n_Decoder);
// IS_stage
uint64_t n_IS_stage;
n_IS_stage = std::max({n_Decoder, perfModel->IB_stage_OoO.get_min()});
perfModel->IS_stage = n_IS_stage;
// uA_OF_A
uint64_t n_uA_OF_A;
n_uA_OF_A = std::max({n_IS_stage, perfModel->scheduleModel.getXa()});
// uA_Issue
uint64_t n_uA_Issue;
n_uA_Issue = std::max({n_IS_stage, perfModel->scheduleModel.getT_issue()});
// IB_stage_OoO
uint64_t n_IB_stage_OoO;
n_IB_stage_OoO = std::max({n_uA_OF_A, n_uA_Issue});
perfModel->IB_stage_OoO.replace_min(n_IB_stage_OoO);
// LSU
uint64_t n_LSU;
n_LSU = n_IB_stage_OoO + 1;
// EX_stage_lu0v_NoB
uint64_t n_EX_stage_lu0v_NoB = n_LSU;
perfModel->EX_stage_lu0v_NoB = n_EX_stage_lu0v_NoB;
// DPort_R
uint64_t n_DPort_R;
n_DPort_R = n_EX_stage_lu0v_NoB + 1;
perfModel->scheduleModel.setXd(n_DPort_R);
perfModel->clobberModel.setCb_inRd(n_DPort_R);
// EX_stage_lsu_NoB
uint64_t n_EX_stage_lsu_NoB = n_DPort_R;
perfModel->EX_stage_lsu_NoB.set(n_EX_stage_lsu_NoB);
perfModel->EX_stage_lu1v_NoB = n_EX_stage_lsu_NoB;
// WB
uint64_t n_WB;
n_WB = n_EX_stage_lsu_NoB + 1;
perfModel->scheduleModel.setT_wb(n_WB);
// WB_stage_NoB
uint64_t n_WB_stage_NoB = n_WB;
perfModel->WB_stage_NoB.set(n_WB_stage_NoB);

  // Dump Entrance point for info print (tracing)
  perfModel->entrancePoint = n_Enter;
  }
);

static SchedulingFunction *schedulingFunction_lb = new SchedulingFunction(
  RV32_OOO_SchedulingFunctionSet,
  "lb",
  41,
  [](PerformanceModel* perfModel_){
  RV32_OOO_PerformanceModel* perfModel = static_cast<RV32_OOO_PerformanceModel*>(perfModel_);
  // Enter
uint64_t n_Enter = perfModel->PC_stage;
// PCGen
uint64_t n_PCGen;
uint64_t n_PCGen_max;
n_PCGen_max = std::max({n_Enter, perfModel->noBranchPredModel.getPc()});
n_PCGen = n_PCGen_max + 1;
perfModel->noBranchPredModel.setPc_p(n_PCGen);
// PC_stage
uint64_t n_PC_stage;
n_PC_stage = std::max({n_PCGen, perfModel->IF_stage});
perfModel->PC_stage = n_PC_stage;
// IPort_R
uint64_t n_IPort_R;
n_IPort_R = n_PC_stage + 1;
// uA_Clobber
uint64_t n_uA_Clobber;
n_uA_Clobber = std::max({n_PC_stage, perfModel->clobberModel.getCb_out()});
// IF_stage
uint64_t n_IF_stage;
n_IF_stage = std::max({n_IPort_R, n_uA_Clobber, perfModel->IS_stage});
perfModel->IF_stage = n_IF_stage;
// Decoder
uint64_t n_Decoder;
n_Decoder = n_IF_stage + 1;
perfModel->scheduleModel.setDec_ld(n_Decoder);
// IS_stage
uint64_t n_IS_stage;
n_IS_stage = std::max({n_Decoder, perfModel->IB_stage_OoO.get_min()});
perfModel->IS_stage = n_IS_stage;
// uA_OF_A
uint64_t n_uA_OF_A;
n_uA_OF_A = std::max({n_IS_stage, perfModel->scheduleModel.getXa()});
// uA_Issue
uint64_t n_uA_Issue;
n_uA_Issue = std::max({n_IS_stage, perfModel->scheduleModel.getT_issue()});
// IB_stage_OoO
uint64_t n_IB_stage_OoO;
n_IB_stage_OoO = std::max({n_uA_OF_A, n_uA_Issue});
perfModel->IB_stage_OoO.replace_min(n_IB_stage_OoO);
// LSU
uint64_t n_LSU;
n_LSU = n_IB_stage_OoO + 1;
// EX_stage_lu0v_NoB
uint64_t n_EX_stage_lu0v_NoB = n_LSU;
perfModel->EX_stage_lu0v_NoB = n_EX_stage_lu0v_NoB;
// DPort_R
uint64_t n_DPort_R;
n_DPort_R = n_EX_stage_lu0v_NoB + 1;
perfModel->scheduleModel.setXd(n_DPort_R);
perfModel->clobberModel.setCb_inRd(n_DPort_R);
// EX_stage_lsu_NoB
uint64_t n_EX_stage_lsu_NoB = n_DPort_R;
perfModel->EX_stage_lsu_NoB.set(n_EX_stage_lsu_NoB);
perfModel->EX_stage_lu1v_NoB = n_EX_stage_lsu_NoB;
// WB
uint64_t n_WB;
n_WB = n_EX_stage_lsu_NoB + 1;
perfModel->scheduleModel.setT_wb(n_WB);
// WB_stage_NoB
uint64_t n_WB_stage_NoB = n_WB;
perfModel->WB_stage_NoB.set(n_WB_stage_NoB);

  // Dump Entrance point for info print (tracing)
  perfModel->entrancePoint = n_Enter;
  }
);

static SchedulingFunction *schedulingFunction_lbu = new SchedulingFunction(
  RV32_OOO_SchedulingFunctionSet,
  "lbu",
  42,
  [](PerformanceModel* perfModel_){
  RV32_OOO_PerformanceModel* perfModel = static_cast<RV32_OOO_PerformanceModel*>(perfModel_);
  // Enter
uint64_t n_Enter = perfModel->PC_stage;
// PCGen
uint64_t n_PCGen;
uint64_t n_PCGen_max;
n_PCGen_max = std::max({n_Enter, perfModel->noBranchPredModel.getPc()});
n_PCGen = n_PCGen_max + 1;
perfModel->noBranchPredModel.setPc_p(n_PCGen);
// PC_stage
uint64_t n_PC_stage;
n_PC_stage = std::max({n_PCGen, perfModel->IF_stage});
perfModel->PC_stage = n_PC_stage;
// IPort_R
uint64_t n_IPort_R;
n_IPort_R = n_PC_stage + 1;
// uA_Clobber
uint64_t n_uA_Clobber;
n_uA_Clobber = std::max({n_PC_stage, perfModel->clobberModel.getCb_out()});
// IF_stage
uint64_t n_IF_stage;
n_IF_stage = std::max({n_IPort_R, n_uA_Clobber, perfModel->IS_stage});
perfModel->IF_stage = n_IF_stage;
// Decoder
uint64_t n_Decoder;
n_Decoder = n_IF_stage + 1;
perfModel->scheduleModel.setDec_ld(n_Decoder);
// IS_stage
uint64_t n_IS_stage;
n_IS_stage = std::max({n_Decoder, perfModel->IB_stage_OoO.get_min()});
perfModel->IS_stage = n_IS_stage;
// uA_OF_A
uint64_t n_uA_OF_A;
n_uA_OF_A = std::max({n_IS_stage, perfModel->scheduleModel.getXa()});
// uA_Issue
uint64_t n_uA_Issue;
n_uA_Issue = std::max({n_IS_stage, perfModel->scheduleModel.getT_issue()});
// IB_stage_OoO
uint64_t n_IB_stage_OoO;
n_IB_stage_OoO = std::max({n_uA_OF_A, n_uA_Issue});
perfModel->IB_stage_OoO.replace_min(n_IB_stage_OoO);
// LSU
uint64_t n_LSU;
n_LSU = n_IB_stage_OoO + 1;
// EX_stage_lu0v_NoB
uint64_t n_EX_stage_lu0v_NoB = n_LSU;
perfModel->EX_stage_lu0v_NoB = n_EX_stage_lu0v_NoB;
// DPort_R
uint64_t n_DPort_R;
n_DPort_R = n_EX_stage_lu0v_NoB + 1;
perfModel->scheduleModel.setXd(n_DPort_R);
perfModel->clobberModel.setCb_inRd(n_DPort_R);
// EX_stage_lsu_NoB
uint64_t n_EX_stage_lsu_NoB = n_DPort_R;
perfModel->EX_stage_lsu_NoB.set(n_EX_stage_lsu_NoB);
perfModel->EX_stage_lu1v_NoB = n_EX_stage_lsu_NoB;
// WB
uint64_t n_WB;
n_WB = n_EX_stage_lsu_NoB + 1;
perfModel->scheduleModel.setT_wb(n_WB);
// WB_stage_NoB
uint64_t n_WB_stage_NoB = n_WB;
perfModel->WB_stage_NoB.set(n_WB_stage_NoB);

  // Dump Entrance point for info print (tracing)
  perfModel->entrancePoint = n_Enter;
  }
);

static SchedulingFunction *schedulingFunction_beq = new SchedulingFunction(
  RV32_OOO_SchedulingFunctionSet,
  "beq",
  43,
  [](PerformanceModel* perfModel_){
  RV32_OOO_PerformanceModel* perfModel = static_cast<RV32_OOO_PerformanceModel*>(perfModel_);
  // Enter
uint64_t n_Enter = perfModel->PC_stage;
// PCGen
uint64_t n_PCGen;
uint64_t n_PCGen_max;
n_PCGen_max = std::max({n_Enter, perfModel->noBranchPredModel.getPc()});
n_PCGen = n_PCGen_max + 1;
perfModel->noBranchPredModel.setPc_p(n_PCGen);
// PC_stage
uint64_t n_PC_stage;
n_PC_stage = std::max({n_PCGen, perfModel->IF_stage});
perfModel->PC_stage = n_PC_stage;
// IPort_R
uint64_t n_IPort_R;
n_IPort_R = n_PC_stage + 1;
// IF_stage
uint64_t n_IF_stage;
n_IF_stage = std::max({n_IPort_R, perfModel->IS_stage});
perfModel->IF_stage = n_IF_stage;
// Decoder
uint64_t n_Decoder;
n_Decoder = n_IF_stage + 1;
perfModel->scheduleModel.setDec_br(n_Decoder);
// IS_stage
uint64_t n_IS_stage;
n_IS_stage = std::max({n_Decoder, perfModel->IB_stage_OoO.get_min()});
perfModel->IS_stage = n_IS_stage;
// uA_OF_A
uint64_t n_uA_OF_A;
n_uA_OF_A = std::max({n_IS_stage, perfModel->scheduleModel.getXa()});
// uA_OF_B
uint64_t n_uA_OF_B;
n_uA_OF_B = std::max({n_IS_stage, perfModel->scheduleModel.getXb()});
// uA_Issue
uint64_t n_uA_Issue;
n_uA_Issue = std::max({n_IS_stage, perfModel->scheduleModel.getT_issue()});
// IB_stage_OoO
uint64_t n_IB_stage_OoO;
n_IB_stage_OoO = std::max({n_uA_OF_A, n_uA_OF_B, n_uA_Issue});
perfModel->IB_stage_OoO.replace_min(n_IB_stage_OoO);
// ADD
uint64_t n_ADD;
n_ADD = n_IB_stage_OoO + 1;
perfModel->noBranchPredModel.setPc_np(n_ADD);
perfModel->clobberModel.setCb_inR1(n_ADD);
perfModel->clobberModel.setCb_inR2(n_ADD);
// EX_stage_br_NoB
uint64_t n_EX_stage_br_NoB = n_ADD;
perfModel->EX_stage_br_NoB = n_EX_stage_br_NoB;
// WB
uint64_t n_WB;
n_WB = n_EX_stage_br_NoB + 1;
perfModel->scheduleModel.setT_wb(n_WB);
// WB_stage_NoB
uint64_t n_WB_stage_NoB = n_WB;
perfModel->WB_stage_NoB.set(n_WB_stage_NoB);

  // Dump Entrance point for info print (tracing)
  perfModel->entrancePoint = n_Enter;
  }
);

static SchedulingFunction *schedulingFunction_bne = new SchedulingFunction(
  RV32_OOO_SchedulingFunctionSet,
  "bne",
  44,
  [](PerformanceModel* perfModel_){
  RV32_OOO_PerformanceModel* perfModel = static_cast<RV32_OOO_PerformanceModel*>(perfModel_);
  // Enter
uint64_t n_Enter = perfModel->PC_stage;
// PCGen
uint64_t n_PCGen;
uint64_t n_PCGen_max;
n_PCGen_max = std::max({n_Enter, perfModel->noBranchPredModel.getPc()});
n_PCGen = n_PCGen_max + 1;
perfModel->noBranchPredModel.setPc_p(n_PCGen);
// PC_stage
uint64_t n_PC_stage;
n_PC_stage = std::max({n_PCGen, perfModel->IF_stage});
perfModel->PC_stage = n_PC_stage;
// IPort_R
uint64_t n_IPort_R;
n_IPort_R = n_PC_stage + 1;
// IF_stage
uint64_t n_IF_stage;
n_IF_stage = std::max({n_IPort_R, perfModel->IS_stage});
perfModel->IF_stage = n_IF_stage;
// Decoder
uint64_t n_Decoder;
n_Decoder = n_IF_stage + 1;
perfModel->scheduleModel.setDec_br(n_Decoder);
// IS_stage
uint64_t n_IS_stage;
n_IS_stage = std::max({n_Decoder, perfModel->IB_stage_OoO.get_min()});
perfModel->IS_stage = n_IS_stage;
// uA_OF_A
uint64_t n_uA_OF_A;
n_uA_OF_A = std::max({n_IS_stage, perfModel->scheduleModel.getXa()});
// uA_OF_B
uint64_t n_uA_OF_B;
n_uA_OF_B = std::max({n_IS_stage, perfModel->scheduleModel.getXb()});
// uA_Issue
uint64_t n_uA_Issue;
n_uA_Issue = std::max({n_IS_stage, perfModel->scheduleModel.getT_issue()});
// IB_stage_OoO
uint64_t n_IB_stage_OoO;
n_IB_stage_OoO = std::max({n_uA_OF_A, n_uA_OF_B, n_uA_Issue});
perfModel->IB_stage_OoO.replace_min(n_IB_stage_OoO);
// ADD
uint64_t n_ADD;
n_ADD = n_IB_stage_OoO + 1;
perfModel->noBranchPredModel.setPc_np(n_ADD);
perfModel->clobberModel.setCb_inR1(n_ADD);
perfModel->clobberModel.setCb_inR2(n_ADD);
// EX_stage_br_NoB
uint64_t n_EX_stage_br_NoB = n_ADD;
perfModel->EX_stage_br_NoB = n_EX_stage_br_NoB;
// WB
uint64_t n_WB;
n_WB = n_EX_stage_br_NoB + 1;
perfModel->scheduleModel.setT_wb(n_WB);
// WB_stage_NoB
uint64_t n_WB_stage_NoB = n_WB;
perfModel->WB_stage_NoB.set(n_WB_stage_NoB);

  // Dump Entrance point for info print (tracing)
  perfModel->entrancePoint = n_Enter;
  }
);

static SchedulingFunction *schedulingFunction_blt = new SchedulingFunction(
  RV32_OOO_SchedulingFunctionSet,
  "blt",
  45,
  [](PerformanceModel* perfModel_){
  RV32_OOO_PerformanceModel* perfModel = static_cast<RV32_OOO_PerformanceModel*>(perfModel_);
  // Enter
uint64_t n_Enter = perfModel->PC_stage;
// PCGen
uint64_t n_PCGen;
uint64_t n_PCGen_max;
n_PCGen_max = std::max({n_Enter, perfModel->noBranchPredModel.getPc()});
n_PCGen = n_PCGen_max + 1;
perfModel->noBranchPredModel.setPc_p(n_PCGen);
// PC_stage
uint64_t n_PC_stage;
n_PC_stage = std::max({n_PCGen, perfModel->IF_stage});
perfModel->PC_stage = n_PC_stage;
// IPort_R
uint64_t n_IPort_R;
n_IPort_R = n_PC_stage + 1;
// IF_stage
uint64_t n_IF_stage;
n_IF_stage = std::max({n_IPort_R, perfModel->IS_stage});
perfModel->IF_stage = n_IF_stage;
// Decoder
uint64_t n_Decoder;
n_Decoder = n_IF_stage + 1;
perfModel->scheduleModel.setDec_br(n_Decoder);
// IS_stage
uint64_t n_IS_stage;
n_IS_stage = std::max({n_Decoder, perfModel->IB_stage_OoO.get_min()});
perfModel->IS_stage = n_IS_stage;
// uA_OF_A
uint64_t n_uA_OF_A;
n_uA_OF_A = std::max({n_IS_stage, perfModel->scheduleModel.getXa()});
// uA_OF_B
uint64_t n_uA_OF_B;
n_uA_OF_B = std::max({n_IS_stage, perfModel->scheduleModel.getXb()});
// uA_Issue
uint64_t n_uA_Issue;
n_uA_Issue = std::max({n_IS_stage, perfModel->scheduleModel.getT_issue()});
// IB_stage_OoO
uint64_t n_IB_stage_OoO;
n_IB_stage_OoO = std::max({n_uA_OF_A, n_uA_OF_B, n_uA_Issue});
perfModel->IB_stage_OoO.replace_min(n_IB_stage_OoO);
// ADD
uint64_t n_ADD;
n_ADD = n_IB_stage_OoO + 1;
perfModel->noBranchPredModel.setPc_np(n_ADD);
perfModel->clobberModel.setCb_inR1(n_ADD);
perfModel->clobberModel.setCb_inR2(n_ADD);
// EX_stage_br_NoB
uint64_t n_EX_stage_br_NoB = n_ADD;
perfModel->EX_stage_br_NoB = n_EX_stage_br_NoB;
// WB
uint64_t n_WB;
n_WB = n_EX_stage_br_NoB + 1;
perfModel->scheduleModel.setT_wb(n_WB);
// WB_stage_NoB
uint64_t n_WB_stage_NoB = n_WB;
perfModel->WB_stage_NoB.set(n_WB_stage_NoB);

  // Dump Entrance point for info print (tracing)
  perfModel->entrancePoint = n_Enter;
  }
);

static SchedulingFunction *schedulingFunction_bge = new SchedulingFunction(
  RV32_OOO_SchedulingFunctionSet,
  "bge",
  46,
  [](PerformanceModel* perfModel_){
  RV32_OOO_PerformanceModel* perfModel = static_cast<RV32_OOO_PerformanceModel*>(perfModel_);
  // Enter
uint64_t n_Enter = perfModel->PC_stage;
// PCGen
uint64_t n_PCGen;
uint64_t n_PCGen_max;
n_PCGen_max = std::max({n_Enter, perfModel->noBranchPredModel.getPc()});
n_PCGen = n_PCGen_max + 1;
perfModel->noBranchPredModel.setPc_p(n_PCGen);
// PC_stage
uint64_t n_PC_stage;
n_PC_stage = std::max({n_PCGen, perfModel->IF_stage});
perfModel->PC_stage = n_PC_stage;
// IPort_R
uint64_t n_IPort_R;
n_IPort_R = n_PC_stage + 1;
// IF_stage
uint64_t n_IF_stage;
n_IF_stage = std::max({n_IPort_R, perfModel->IS_stage});
perfModel->IF_stage = n_IF_stage;
// Decoder
uint64_t n_Decoder;
n_Decoder = n_IF_stage + 1;
perfModel->scheduleModel.setDec_br(n_Decoder);
// IS_stage
uint64_t n_IS_stage;
n_IS_stage = std::max({n_Decoder, perfModel->IB_stage_OoO.get_min()});
perfModel->IS_stage = n_IS_stage;
// uA_OF_A
uint64_t n_uA_OF_A;
n_uA_OF_A = std::max({n_IS_stage, perfModel->scheduleModel.getXa()});
// uA_OF_B
uint64_t n_uA_OF_B;
n_uA_OF_B = std::max({n_IS_stage, perfModel->scheduleModel.getXb()});
// uA_Issue
uint64_t n_uA_Issue;
n_uA_Issue = std::max({n_IS_stage, perfModel->scheduleModel.getT_issue()});
// IB_stage_OoO
uint64_t n_IB_stage_OoO;
n_IB_stage_OoO = std::max({n_uA_OF_A, n_uA_OF_B, n_uA_Issue});
perfModel->IB_stage_OoO.replace_min(n_IB_stage_OoO);
// ADD
uint64_t n_ADD;
n_ADD = n_IB_stage_OoO + 1;
perfModel->noBranchPredModel.setPc_np(n_ADD);
perfModel->clobberModel.setCb_inR1(n_ADD);
perfModel->clobberModel.setCb_inR2(n_ADD);
// EX_stage_br_NoB
uint64_t n_EX_stage_br_NoB = n_ADD;
perfModel->EX_stage_br_NoB = n_EX_stage_br_NoB;
// WB
uint64_t n_WB;
n_WB = n_EX_stage_br_NoB + 1;
perfModel->scheduleModel.setT_wb(n_WB);
// WB_stage_NoB
uint64_t n_WB_stage_NoB = n_WB;
perfModel->WB_stage_NoB.set(n_WB_stage_NoB);

  // Dump Entrance point for info print (tracing)
  perfModel->entrancePoint = n_Enter;
  }
);

static SchedulingFunction *schedulingFunction_bltu = new SchedulingFunction(
  RV32_OOO_SchedulingFunctionSet,
  "bltu",
  47,
  [](PerformanceModel* perfModel_){
  RV32_OOO_PerformanceModel* perfModel = static_cast<RV32_OOO_PerformanceModel*>(perfModel_);
  // Enter
uint64_t n_Enter = perfModel->PC_stage;
// PCGen
uint64_t n_PCGen;
uint64_t n_PCGen_max;
n_PCGen_max = std::max({n_Enter, perfModel->noBranchPredModel.getPc()});
n_PCGen = n_PCGen_max + 1;
perfModel->noBranchPredModel.setPc_p(n_PCGen);
// PC_stage
uint64_t n_PC_stage;
n_PC_stage = std::max({n_PCGen, perfModel->IF_stage});
perfModel->PC_stage = n_PC_stage;
// IPort_R
uint64_t n_IPort_R;
n_IPort_R = n_PC_stage + 1;
// IF_stage
uint64_t n_IF_stage;
n_IF_stage = std::max({n_IPort_R, perfModel->IS_stage});
perfModel->IF_stage = n_IF_stage;
// Decoder
uint64_t n_Decoder;
n_Decoder = n_IF_stage + 1;
perfModel->scheduleModel.setDec_br(n_Decoder);
// IS_stage
uint64_t n_IS_stage;
n_IS_stage = std::max({n_Decoder, perfModel->IB_stage_OoO.get_min()});
perfModel->IS_stage = n_IS_stage;
// uA_OF_A
uint64_t n_uA_OF_A;
n_uA_OF_A = std::max({n_IS_stage, perfModel->scheduleModel.getXa()});
// uA_OF_B
uint64_t n_uA_OF_B;
n_uA_OF_B = std::max({n_IS_stage, perfModel->scheduleModel.getXb()});
// uA_Issue
uint64_t n_uA_Issue;
n_uA_Issue = std::max({n_IS_stage, perfModel->scheduleModel.getT_issue()});
// IB_stage_OoO
uint64_t n_IB_stage_OoO;
n_IB_stage_OoO = std::max({n_uA_OF_A, n_uA_OF_B, n_uA_Issue});
perfModel->IB_stage_OoO.replace_min(n_IB_stage_OoO);
// ADD
uint64_t n_ADD;
n_ADD = n_IB_stage_OoO + 1;
perfModel->noBranchPredModel.setPc_np(n_ADD);
perfModel->clobberModel.setCb_inR1(n_ADD);
perfModel->clobberModel.setCb_inR2(n_ADD);
// EX_stage_br_NoB
uint64_t n_EX_stage_br_NoB = n_ADD;
perfModel->EX_stage_br_NoB = n_EX_stage_br_NoB;
// WB
uint64_t n_WB;
n_WB = n_EX_stage_br_NoB + 1;
perfModel->scheduleModel.setT_wb(n_WB);
// WB_stage_NoB
uint64_t n_WB_stage_NoB = n_WB;
perfModel->WB_stage_NoB.set(n_WB_stage_NoB);

  // Dump Entrance point for info print (tracing)
  perfModel->entrancePoint = n_Enter;
  }
);

static SchedulingFunction *schedulingFunction_bgeu = new SchedulingFunction(
  RV32_OOO_SchedulingFunctionSet,
  "bgeu",
  48,
  [](PerformanceModel* perfModel_){
  RV32_OOO_PerformanceModel* perfModel = static_cast<RV32_OOO_PerformanceModel*>(perfModel_);
  // Enter
uint64_t n_Enter = perfModel->PC_stage;
// PCGen
uint64_t n_PCGen;
uint64_t n_PCGen_max;
n_PCGen_max = std::max({n_Enter, perfModel->noBranchPredModel.getPc()});
n_PCGen = n_PCGen_max + 1;
perfModel->noBranchPredModel.setPc_p(n_PCGen);
// PC_stage
uint64_t n_PC_stage;
n_PC_stage = std::max({n_PCGen, perfModel->IF_stage});
perfModel->PC_stage = n_PC_stage;
// IPort_R
uint64_t n_IPort_R;
n_IPort_R = n_PC_stage + 1;
// IF_stage
uint64_t n_IF_stage;
n_IF_stage = std::max({n_IPort_R, perfModel->IS_stage});
perfModel->IF_stage = n_IF_stage;
// Decoder
uint64_t n_Decoder;
n_Decoder = n_IF_stage + 1;
perfModel->scheduleModel.setDec_br(n_Decoder);
// IS_stage
uint64_t n_IS_stage;
n_IS_stage = std::max({n_Decoder, perfModel->IB_stage_OoO.get_min()});
perfModel->IS_stage = n_IS_stage;
// uA_OF_A
uint64_t n_uA_OF_A;
n_uA_OF_A = std::max({n_IS_stage, perfModel->scheduleModel.getXa()});
// uA_OF_B
uint64_t n_uA_OF_B;
n_uA_OF_B = std::max({n_IS_stage, perfModel->scheduleModel.getXb()});
// uA_Issue
uint64_t n_uA_Issue;
n_uA_Issue = std::max({n_IS_stage, perfModel->scheduleModel.getT_issue()});
// IB_stage_OoO
uint64_t n_IB_stage_OoO;
n_IB_stage_OoO = std::max({n_uA_OF_A, n_uA_OF_B, n_uA_Issue});
perfModel->IB_stage_OoO.replace_min(n_IB_stage_OoO);
// ADD
uint64_t n_ADD;
n_ADD = n_IB_stage_OoO + 1;
perfModel->noBranchPredModel.setPc_np(n_ADD);
perfModel->clobberModel.setCb_inR1(n_ADD);
perfModel->clobberModel.setCb_inR2(n_ADD);
// EX_stage_br_NoB
uint64_t n_EX_stage_br_NoB = n_ADD;
perfModel->EX_stage_br_NoB = n_EX_stage_br_NoB;
// WB
uint64_t n_WB;
n_WB = n_EX_stage_br_NoB + 1;
perfModel->scheduleModel.setT_wb(n_WB);
// WB_stage_NoB
uint64_t n_WB_stage_NoB = n_WB;
perfModel->WB_stage_NoB.set(n_WB_stage_NoB);

  // Dump Entrance point for info print (tracing)
  perfModel->entrancePoint = n_Enter;
  }
);

static SchedulingFunction *schedulingFunction__def = new SchedulingFunction(
  RV32_OOO_SchedulingFunctionSet,
  "_def",
  49,
  [](PerformanceModel* perfModel_){
  RV32_OOO_PerformanceModel* perfModel = static_cast<RV32_OOO_PerformanceModel*>(perfModel_);
  // Enter
uint64_t n_Enter = perfModel->PC_stage;
// PCGen
uint64_t n_PCGen;
uint64_t n_PCGen_max;
n_PCGen_max = std::max({n_Enter, perfModel->noBranchPredModel.getPc()});
n_PCGen = n_PCGen_max + 1;
perfModel->noBranchPredModel.setPc_p(n_PCGen);
// PC_stage
uint64_t n_PC_stage;
n_PC_stage = std::max({n_PCGen, perfModel->IF_stage});
perfModel->PC_stage = n_PC_stage;
// IPort_R
uint64_t n_IPort_R;
n_IPort_R = n_PC_stage + 1;
// IF_stage
uint64_t n_IF_stage = n_IPort_R;
perfModel->IF_stage = n_IF_stage;

  // Dump Entrance point for info print (tracing)
  perfModel->entrancePoint = n_Enter;
  }
);

static SchedulingFunction *schedulingFunction_jal = new SchedulingFunction(
  RV32_OOO_SchedulingFunctionSet,
  "jal",
  50,
  [](PerformanceModel* perfModel_){
  RV32_OOO_PerformanceModel* perfModel = static_cast<RV32_OOO_PerformanceModel*>(perfModel_);
  // Enter
uint64_t n_Enter = perfModel->PC_stage;
// PCGen
uint64_t n_PCGen;
uint64_t n_PCGen_max;
n_PCGen_max = std::max({n_Enter, perfModel->noBranchPredModel.getPc()});
n_PCGen = n_PCGen_max + 1;
perfModel->noBranchPredModel.setPc_p(n_PCGen);
// PC_stage
uint64_t n_PC_stage;
n_PC_stage = std::max({n_PCGen, perfModel->IF_stage});
perfModel->PC_stage = n_PC_stage;
// IPort_R
uint64_t n_IPort_R;
n_IPort_R = n_PC_stage + 1;
// uA_Clobber
uint64_t n_uA_Clobber;
n_uA_Clobber = std::max({n_PC_stage, perfModel->clobberModel.getCb_out()});
// IF_stage
uint64_t n_IF_stage;
n_IF_stage = std::max({n_IPort_R, n_uA_Clobber, perfModel->IS_stage});
perfModel->IF_stage = n_IF_stage;
// JumpDecoder
uint64_t n_JumpDecoder;
n_JumpDecoder = n_IF_stage + 1;
perfModel->noBranchPredModel.setPc_np(n_JumpDecoder);
perfModel->scheduleModel.setDec_br(n_JumpDecoder);
// IS_stage
uint64_t n_IS_stage;
n_IS_stage = std::max({n_JumpDecoder, perfModel->IB_stage_OoO.get_min()});
perfModel->IS_stage = n_IS_stage;
// uA_Issue
uint64_t n_uA_Issue;
n_uA_Issue = std::max({n_IS_stage, perfModel->scheduleModel.getT_issue()});
// IB_stage_OoO
uint64_t n_IB_stage_OoO = n_uA_Issue;
perfModel->IB_stage_OoO.replace_min(n_IB_stage_OoO);
// ADD
uint64_t n_ADD;
n_ADD = n_IB_stage_OoO + 1;
perfModel->scheduleModel.setXd(n_ADD);
perfModel->clobberModel.setCb_inRd(n_ADD);
// EX_stage_br_NoB
uint64_t n_EX_stage_br_NoB = n_ADD;
perfModel->EX_stage_br_NoB = n_EX_stage_br_NoB;
// WB
uint64_t n_WB;
n_WB = n_EX_stage_br_NoB + 1;
perfModel->scheduleModel.setT_wb(n_WB);
// WB_stage_NoB
uint64_t n_WB_stage_NoB = n_WB;
perfModel->WB_stage_NoB.set(n_WB_stage_NoB);

  // Dump Entrance point for info print (tracing)
  perfModel->entrancePoint = n_Enter;
  }
);

static SchedulingFunction *schedulingFunction_jalr = new SchedulingFunction(
  RV32_OOO_SchedulingFunctionSet,
  "jalr",
  51,
  [](PerformanceModel* perfModel_){
  RV32_OOO_PerformanceModel* perfModel = static_cast<RV32_OOO_PerformanceModel*>(perfModel_);
  // Enter
uint64_t n_Enter = perfModel->PC_stage;
// PCGen
uint64_t n_PCGen;
uint64_t n_PCGen_max;
n_PCGen_max = std::max({n_Enter, perfModel->noBranchPredModel.getPc()});
n_PCGen = n_PCGen_max + 1;
perfModel->noBranchPredModel.setPc_p(n_PCGen);
// PC_stage
uint64_t n_PC_stage;
n_PC_stage = std::max({n_PCGen, perfModel->IF_stage});
perfModel->PC_stage = n_PC_stage;
// IPort_R
uint64_t n_IPort_R;
n_IPort_R = n_PC_stage + 1;
// uA_Clobber
uint64_t n_uA_Clobber;
n_uA_Clobber = std::max({n_PC_stage, perfModel->clobberModel.getCb_out()});
// IF_stage
uint64_t n_IF_stage;
n_IF_stage = std::max({n_IPort_R, n_uA_Clobber, perfModel->IS_stage});
perfModel->IF_stage = n_IF_stage;
// JumpDecoder
uint64_t n_JumpDecoder;
uint64_t n_JumpDecoder_max;
n_JumpDecoder_max = std::max({n_IF_stage, perfModel->scheduleModel.getXa()});
n_JumpDecoder = n_JumpDecoder_max + 1;
perfModel->noBranchPredModel.setPc_np(n_JumpDecoder);
perfModel->scheduleModel.setDec_br(n_JumpDecoder);
// IS_stage
uint64_t n_IS_stage;
n_IS_stage = std::max({n_JumpDecoder, perfModel->IB_stage_OoO.get_min()});
perfModel->IS_stage = n_IS_stage;
// uA_Issue
uint64_t n_uA_Issue;
n_uA_Issue = std::max({n_IS_stage, perfModel->scheduleModel.getT_issue()});
// IB_stage_OoO
uint64_t n_IB_stage_OoO = n_uA_Issue;
perfModel->IB_stage_OoO.replace_min(n_IB_stage_OoO);
// ADD
uint64_t n_ADD;
n_ADD = n_IB_stage_OoO + 1;
perfModel->scheduleModel.setXd(n_ADD);
perfModel->clobberModel.setCb_inRd(n_ADD);
perfModel->clobberModel.setCb_inR1(n_ADD);
// EX_stage_br_NoB
uint64_t n_EX_stage_br_NoB = n_ADD;
perfModel->EX_stage_br_NoB = n_EX_stage_br_NoB;
// WB
uint64_t n_WB;
n_WB = n_EX_stage_br_NoB + 1;
perfModel->scheduleModel.setT_wb(n_WB);
// WB_stage_NoB
uint64_t n_WB_stage_NoB = n_WB;
perfModel->WB_stage_NoB.set(n_WB_stage_NoB);

  // Dump Entrance point for info print (tracing)
  perfModel->entrancePoint = n_Enter;
  }
);


} // namespace RV32_OOO