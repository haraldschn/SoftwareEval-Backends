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

#include "RV32_4ISSUE_PerformanceModel.h"

namespace RV32_4ISSUE{

SchedulingFunctionSet* RV32_4ISSUE_SchedulingFunctionSet = new SchedulingFunctionSet("RV32_4ISSUE_SchedulingFunctionSet");

static SchedulingFunction *schedulingFunction_add = new SchedulingFunction(
  RV32_4ISSUE_SchedulingFunctionSet,
  "add",
  0,
  [](PerformanceModel* perfModel_){
  RV32_4ISSUE_PerformanceModel* perfModel = static_cast<RV32_4ISSUE_PerformanceModel*>(perfModel_);
  // Enter
uint64_t n_Enter;
n_Enter = std::max({perfModel->IF_stage.get(16), perfModel->PC_substage.get(4)});
// PCGen
uint64_t n_PCGen;
n_PCGen = n_Enter + 1;
// uA_PcCorrect
uint64_t n_uA_PcCorrect;
n_uA_PcCorrect = std::max({n_Enter, perfModel->dynBranchPredModel.getPc_mp()});
// uA_CacheBlock
uint64_t n_uA_CacheBlock;
n_uA_CacheBlock = std::max({n_Enter, perfModel->iCacheModel.getIc_out()});
// PC_substage
uint64_t n_PC_substage;
n_PC_substage = std::max({n_PCGen, n_uA_PcCorrect, n_uA_CacheBlock, perfModel->PC_substage.get(1), perfModel->IF_substage_0.get(4)});
perfModel->PC_substage.set(n_PC_substage);
// ICacheCtrl
uint64_t n_ICacheCtrl;
n_ICacheCtrl = n_PC_substage + 1;
// IF_substage_0
uint64_t n_IF_substage_0;
n_IF_substage_0 = std::max({n_ICacheCtrl, perfModel->IF_substage_0.get(1), perfModel->IF_substage_1.get(4)});
perfModel->IF_substage_0.set(n_IF_substage_0);
// ICache
uint64_t n_ICache;
n_ICache = n_IF_substage_0 + perfModel->iCacheModel.getDelay();
perfModel->iCacheModel.setIc_in(n_ICache);
// uA_PcPredict
uint64_t n_uA_PcPredict;
n_uA_PcPredict = std::max({n_IF_substage_0, perfModel->dynBranchPredModel.getPc_pt()});
// IF_substage_1
uint64_t n_IF_substage_1;
n_IF_substage_1 = std::max({n_ICache, n_uA_PcPredict, perfModel->IF_substage_1.get(1), perfModel->IF_substage_2.get(4)});
perfModel->IF_substage_1.set(n_IF_substage_1);
// IScan
uint64_t n_IScan;
n_IScan = n_IF_substage_1 + 1;
// IF_stage
uint64_t n_IF_stage;
n_IF_stage = std::max({n_IScan, perfModel->IF_stage.get(1), perfModel->IF_substage_2.get(1), perfModel->DEC_stage.get(4)});
perfModel->IF_stage.set(n_IF_stage);
perfModel->IF_substage_2.set(n_IF_stage);
// Decoder
uint64_t n_Decoder;
n_Decoder = n_IF_stage + 1;
// DEC_stage
uint64_t n_DEC_stage;
n_DEC_stage = std::max({n_Decoder, perfModel->DEC_stage.get(1), perfModel->RN_stage.get(5)});
perfModel->DEC_stage.set(n_DEC_stage);
// Rename
uint64_t n_Rename;
n_Rename = n_DEC_stage + 1;
// RN_stage
uint64_t n_RN_stage;
n_RN_stage = std::max({n_Rename, perfModel->RN_stage.get(1), perfModel->OoO_stage.get(64), perfModel->IS_substage_alu.get(24)});
perfModel->RN_stage.set(n_RN_stage);
// Issue
uint64_t n_Issue;
n_Issue = n_RN_stage + 2;
// IS_substage_alu
uint64_t n_IS_substage_alu;
n_IS_substage_alu = std::max({n_Issue, perfModel->IS_substage_alu.get(1), perfModel->LD_substage_alu.get(3)});
perfModel->IS_substage_alu.set(n_IS_substage_alu);
// OperandLookup
uint64_t n_OperandLookup;
n_OperandLookup = n_IS_substage_alu + 1;
// uA_OF_A_alu
uint64_t n_uA_OF_A_alu;
n_uA_OF_A_alu = std::max({n_IS_substage_alu, perfModel->regModel.getXa()});
// uA_OF_B_alu
uint64_t n_uA_OF_B_alu;
n_uA_OF_B_alu = std::max({n_IS_substage_alu, perfModel->regModel.getXb()});
// LD_substage_alu
uint64_t n_LD_substage_alu;
n_LD_substage_alu = std::max({n_OperandLookup, n_uA_OF_A_alu, n_uA_OF_B_alu, perfModel->LD_substage_alu.get(1), perfModel->EX_stage_alu.get(9), perfModel->EX_substage_alu.get(3)});
perfModel->LD_substage_alu.set(n_LD_substage_alu);
// ALU
uint64_t n_ALU;
n_ALU = n_LD_substage_alu + 1;
perfModel->regModel.setXd(n_ALU);
// EX_stage_alu
uint64_t n_EX_stage_alu;
n_EX_stage_alu = std::max({n_ALU, perfModel->EX_stage_alu.get(1), perfModel->EX_substage_alu.get(1)});
perfModel->EX_stage_alu.set(n_EX_stage_alu);
perfModel->EX_substage_alu.set(n_EX_stage_alu);
// OoO_stage
uint64_t n_OoO_stage;
n_OoO_stage = std::max({n_EX_stage_alu, perfModel->OoO_stage.get(1), perfModel->COM_stage.get(8)});
perfModel->OoO_stage.set(n_OoO_stage);
// Commit
uint64_t n_Commit;
n_Commit = n_OoO_stage + 2;
// COM_stage
uint64_t n_COM_stage;
n_COM_stage = std::max({n_Commit, perfModel->COM_stage.get(1)});
perfModel->COM_stage.set(n_COM_stage);

  // Dump Entrance point for info print (tracing)
  perfModel->entrancePoint = n_Enter;
  }
);

static SchedulingFunction *schedulingFunction_sub = new SchedulingFunction(
  RV32_4ISSUE_SchedulingFunctionSet,
  "sub",
  1,
  [](PerformanceModel* perfModel_){
  RV32_4ISSUE_PerformanceModel* perfModel = static_cast<RV32_4ISSUE_PerformanceModel*>(perfModel_);
  // Enter
uint64_t n_Enter;
n_Enter = std::max({perfModel->IF_stage.get(16), perfModel->PC_substage.get(4)});
// PCGen
uint64_t n_PCGen;
n_PCGen = n_Enter + 1;
// uA_PcCorrect
uint64_t n_uA_PcCorrect;
n_uA_PcCorrect = std::max({n_Enter, perfModel->dynBranchPredModel.getPc_mp()});
// uA_CacheBlock
uint64_t n_uA_CacheBlock;
n_uA_CacheBlock = std::max({n_Enter, perfModel->iCacheModel.getIc_out()});
// PC_substage
uint64_t n_PC_substage;
n_PC_substage = std::max({n_PCGen, n_uA_PcCorrect, n_uA_CacheBlock, perfModel->PC_substage.get(1), perfModel->IF_substage_0.get(4)});
perfModel->PC_substage.set(n_PC_substage);
// ICacheCtrl
uint64_t n_ICacheCtrl;
n_ICacheCtrl = n_PC_substage + 1;
// IF_substage_0
uint64_t n_IF_substage_0;
n_IF_substage_0 = std::max({n_ICacheCtrl, perfModel->IF_substage_0.get(1), perfModel->IF_substage_1.get(4)});
perfModel->IF_substage_0.set(n_IF_substage_0);
// ICache
uint64_t n_ICache;
n_ICache = n_IF_substage_0 + perfModel->iCacheModel.getDelay();
perfModel->iCacheModel.setIc_in(n_ICache);
// uA_PcPredict
uint64_t n_uA_PcPredict;
n_uA_PcPredict = std::max({n_IF_substage_0, perfModel->dynBranchPredModel.getPc_pt()});
// IF_substage_1
uint64_t n_IF_substage_1;
n_IF_substage_1 = std::max({n_ICache, n_uA_PcPredict, perfModel->IF_substage_1.get(1), perfModel->IF_substage_2.get(4)});
perfModel->IF_substage_1.set(n_IF_substage_1);
// IScan
uint64_t n_IScan;
n_IScan = n_IF_substage_1 + 1;
// IF_stage
uint64_t n_IF_stage;
n_IF_stage = std::max({n_IScan, perfModel->IF_stage.get(1), perfModel->IF_substage_2.get(1), perfModel->DEC_stage.get(4)});
perfModel->IF_stage.set(n_IF_stage);
perfModel->IF_substage_2.set(n_IF_stage);
// Decoder
uint64_t n_Decoder;
n_Decoder = n_IF_stage + 1;
// DEC_stage
uint64_t n_DEC_stage;
n_DEC_stage = std::max({n_Decoder, perfModel->DEC_stage.get(1), perfModel->RN_stage.get(5)});
perfModel->DEC_stage.set(n_DEC_stage);
// Rename
uint64_t n_Rename;
n_Rename = n_DEC_stage + 1;
// RN_stage
uint64_t n_RN_stage;
n_RN_stage = std::max({n_Rename, perfModel->RN_stage.get(1), perfModel->OoO_stage.get(64), perfModel->IS_substage_alu.get(24)});
perfModel->RN_stage.set(n_RN_stage);
// Issue
uint64_t n_Issue;
n_Issue = n_RN_stage + 2;
// IS_substage_alu
uint64_t n_IS_substage_alu;
n_IS_substage_alu = std::max({n_Issue, perfModel->IS_substage_alu.get(1), perfModel->LD_substage_alu.get(3)});
perfModel->IS_substage_alu.set(n_IS_substage_alu);
// OperandLookup
uint64_t n_OperandLookup;
n_OperandLookup = n_IS_substage_alu + 1;
// uA_OF_A_alu
uint64_t n_uA_OF_A_alu;
n_uA_OF_A_alu = std::max({n_IS_substage_alu, perfModel->regModel.getXa()});
// uA_OF_B_alu
uint64_t n_uA_OF_B_alu;
n_uA_OF_B_alu = std::max({n_IS_substage_alu, perfModel->regModel.getXb()});
// LD_substage_alu
uint64_t n_LD_substage_alu;
n_LD_substage_alu = std::max({n_OperandLookup, n_uA_OF_A_alu, n_uA_OF_B_alu, perfModel->LD_substage_alu.get(1), perfModel->EX_stage_alu.get(9), perfModel->EX_substage_alu.get(3)});
perfModel->LD_substage_alu.set(n_LD_substage_alu);
// ALU
uint64_t n_ALU;
n_ALU = n_LD_substage_alu + 1;
perfModel->regModel.setXd(n_ALU);
// EX_stage_alu
uint64_t n_EX_stage_alu;
n_EX_stage_alu = std::max({n_ALU, perfModel->EX_stage_alu.get(1), perfModel->EX_substage_alu.get(1)});
perfModel->EX_stage_alu.set(n_EX_stage_alu);
perfModel->EX_substage_alu.set(n_EX_stage_alu);
// OoO_stage
uint64_t n_OoO_stage;
n_OoO_stage = std::max({n_EX_stage_alu, perfModel->OoO_stage.get(1), perfModel->COM_stage.get(8)});
perfModel->OoO_stage.set(n_OoO_stage);
// Commit
uint64_t n_Commit;
n_Commit = n_OoO_stage + 2;
// COM_stage
uint64_t n_COM_stage;
n_COM_stage = std::max({n_Commit, perfModel->COM_stage.get(1)});
perfModel->COM_stage.set(n_COM_stage);

  // Dump Entrance point for info print (tracing)
  perfModel->entrancePoint = n_Enter;
  }
);

static SchedulingFunction *schedulingFunction_xor = new SchedulingFunction(
  RV32_4ISSUE_SchedulingFunctionSet,
  "xor",
  2,
  [](PerformanceModel* perfModel_){
  RV32_4ISSUE_PerformanceModel* perfModel = static_cast<RV32_4ISSUE_PerformanceModel*>(perfModel_);
  // Enter
uint64_t n_Enter;
n_Enter = std::max({perfModel->IF_stage.get(16), perfModel->PC_substage.get(4)});
// PCGen
uint64_t n_PCGen;
n_PCGen = n_Enter + 1;
// uA_PcCorrect
uint64_t n_uA_PcCorrect;
n_uA_PcCorrect = std::max({n_Enter, perfModel->dynBranchPredModel.getPc_mp()});
// uA_CacheBlock
uint64_t n_uA_CacheBlock;
n_uA_CacheBlock = std::max({n_Enter, perfModel->iCacheModel.getIc_out()});
// PC_substage
uint64_t n_PC_substage;
n_PC_substage = std::max({n_PCGen, n_uA_PcCorrect, n_uA_CacheBlock, perfModel->PC_substage.get(1), perfModel->IF_substage_0.get(4)});
perfModel->PC_substage.set(n_PC_substage);
// ICacheCtrl
uint64_t n_ICacheCtrl;
n_ICacheCtrl = n_PC_substage + 1;
// IF_substage_0
uint64_t n_IF_substage_0;
n_IF_substage_0 = std::max({n_ICacheCtrl, perfModel->IF_substage_0.get(1), perfModel->IF_substage_1.get(4)});
perfModel->IF_substage_0.set(n_IF_substage_0);
// ICache
uint64_t n_ICache;
n_ICache = n_IF_substage_0 + perfModel->iCacheModel.getDelay();
perfModel->iCacheModel.setIc_in(n_ICache);
// uA_PcPredict
uint64_t n_uA_PcPredict;
n_uA_PcPredict = std::max({n_IF_substage_0, perfModel->dynBranchPredModel.getPc_pt()});
// IF_substage_1
uint64_t n_IF_substage_1;
n_IF_substage_1 = std::max({n_ICache, n_uA_PcPredict, perfModel->IF_substage_1.get(1), perfModel->IF_substage_2.get(4)});
perfModel->IF_substage_1.set(n_IF_substage_1);
// IScan
uint64_t n_IScan;
n_IScan = n_IF_substage_1 + 1;
// IF_stage
uint64_t n_IF_stage;
n_IF_stage = std::max({n_IScan, perfModel->IF_stage.get(1), perfModel->IF_substage_2.get(1), perfModel->DEC_stage.get(4)});
perfModel->IF_stage.set(n_IF_stage);
perfModel->IF_substage_2.set(n_IF_stage);
// Decoder
uint64_t n_Decoder;
n_Decoder = n_IF_stage + 1;
// DEC_stage
uint64_t n_DEC_stage;
n_DEC_stage = std::max({n_Decoder, perfModel->DEC_stage.get(1), perfModel->RN_stage.get(5)});
perfModel->DEC_stage.set(n_DEC_stage);
// Rename
uint64_t n_Rename;
n_Rename = n_DEC_stage + 1;
// RN_stage
uint64_t n_RN_stage;
n_RN_stage = std::max({n_Rename, perfModel->RN_stage.get(1), perfModel->OoO_stage.get(64), perfModel->IS_substage_alu.get(24)});
perfModel->RN_stage.set(n_RN_stage);
// Issue
uint64_t n_Issue;
n_Issue = n_RN_stage + 2;
// IS_substage_alu
uint64_t n_IS_substage_alu;
n_IS_substage_alu = std::max({n_Issue, perfModel->IS_substage_alu.get(1), perfModel->LD_substage_alu.get(3)});
perfModel->IS_substage_alu.set(n_IS_substage_alu);
// OperandLookup
uint64_t n_OperandLookup;
n_OperandLookup = n_IS_substage_alu + 1;
// uA_OF_A_alu
uint64_t n_uA_OF_A_alu;
n_uA_OF_A_alu = std::max({n_IS_substage_alu, perfModel->regModel.getXa()});
// uA_OF_B_alu
uint64_t n_uA_OF_B_alu;
n_uA_OF_B_alu = std::max({n_IS_substage_alu, perfModel->regModel.getXb()});
// LD_substage_alu
uint64_t n_LD_substage_alu;
n_LD_substage_alu = std::max({n_OperandLookup, n_uA_OF_A_alu, n_uA_OF_B_alu, perfModel->LD_substage_alu.get(1), perfModel->EX_stage_alu.get(9), perfModel->EX_substage_alu.get(3)});
perfModel->LD_substage_alu.set(n_LD_substage_alu);
// ALU
uint64_t n_ALU;
n_ALU = n_LD_substage_alu + 1;
perfModel->regModel.setXd(n_ALU);
// EX_stage_alu
uint64_t n_EX_stage_alu;
n_EX_stage_alu = std::max({n_ALU, perfModel->EX_stage_alu.get(1), perfModel->EX_substage_alu.get(1)});
perfModel->EX_stage_alu.set(n_EX_stage_alu);
perfModel->EX_substage_alu.set(n_EX_stage_alu);
// OoO_stage
uint64_t n_OoO_stage;
n_OoO_stage = std::max({n_EX_stage_alu, perfModel->OoO_stage.get(1), perfModel->COM_stage.get(8)});
perfModel->OoO_stage.set(n_OoO_stage);
// Commit
uint64_t n_Commit;
n_Commit = n_OoO_stage + 2;
// COM_stage
uint64_t n_COM_stage;
n_COM_stage = std::max({n_Commit, perfModel->COM_stage.get(1)});
perfModel->COM_stage.set(n_COM_stage);

  // Dump Entrance point for info print (tracing)
  perfModel->entrancePoint = n_Enter;
  }
);

static SchedulingFunction *schedulingFunction_or = new SchedulingFunction(
  RV32_4ISSUE_SchedulingFunctionSet,
  "or",
  3,
  [](PerformanceModel* perfModel_){
  RV32_4ISSUE_PerformanceModel* perfModel = static_cast<RV32_4ISSUE_PerformanceModel*>(perfModel_);
  // Enter
uint64_t n_Enter;
n_Enter = std::max({perfModel->IF_stage.get(16), perfModel->PC_substage.get(4)});
// PCGen
uint64_t n_PCGen;
n_PCGen = n_Enter + 1;
// uA_PcCorrect
uint64_t n_uA_PcCorrect;
n_uA_PcCorrect = std::max({n_Enter, perfModel->dynBranchPredModel.getPc_mp()});
// uA_CacheBlock
uint64_t n_uA_CacheBlock;
n_uA_CacheBlock = std::max({n_Enter, perfModel->iCacheModel.getIc_out()});
// PC_substage
uint64_t n_PC_substage;
n_PC_substage = std::max({n_PCGen, n_uA_PcCorrect, n_uA_CacheBlock, perfModel->PC_substage.get(1), perfModel->IF_substage_0.get(4)});
perfModel->PC_substage.set(n_PC_substage);
// ICacheCtrl
uint64_t n_ICacheCtrl;
n_ICacheCtrl = n_PC_substage + 1;
// IF_substage_0
uint64_t n_IF_substage_0;
n_IF_substage_0 = std::max({n_ICacheCtrl, perfModel->IF_substage_0.get(1), perfModel->IF_substage_1.get(4)});
perfModel->IF_substage_0.set(n_IF_substage_0);
// ICache
uint64_t n_ICache;
n_ICache = n_IF_substage_0 + perfModel->iCacheModel.getDelay();
perfModel->iCacheModel.setIc_in(n_ICache);
// uA_PcPredict
uint64_t n_uA_PcPredict;
n_uA_PcPredict = std::max({n_IF_substage_0, perfModel->dynBranchPredModel.getPc_pt()});
// IF_substage_1
uint64_t n_IF_substage_1;
n_IF_substage_1 = std::max({n_ICache, n_uA_PcPredict, perfModel->IF_substage_1.get(1), perfModel->IF_substage_2.get(4)});
perfModel->IF_substage_1.set(n_IF_substage_1);
// IScan
uint64_t n_IScan;
n_IScan = n_IF_substage_1 + 1;
// IF_stage
uint64_t n_IF_stage;
n_IF_stage = std::max({n_IScan, perfModel->IF_stage.get(1), perfModel->IF_substage_2.get(1), perfModel->DEC_stage.get(4)});
perfModel->IF_stage.set(n_IF_stage);
perfModel->IF_substage_2.set(n_IF_stage);
// Decoder
uint64_t n_Decoder;
n_Decoder = n_IF_stage + 1;
// DEC_stage
uint64_t n_DEC_stage;
n_DEC_stage = std::max({n_Decoder, perfModel->DEC_stage.get(1), perfModel->RN_stage.get(5)});
perfModel->DEC_stage.set(n_DEC_stage);
// Rename
uint64_t n_Rename;
n_Rename = n_DEC_stage + 1;
// RN_stage
uint64_t n_RN_stage;
n_RN_stage = std::max({n_Rename, perfModel->RN_stage.get(1), perfModel->OoO_stage.get(64), perfModel->IS_substage_alu.get(24)});
perfModel->RN_stage.set(n_RN_stage);
// Issue
uint64_t n_Issue;
n_Issue = n_RN_stage + 2;
// IS_substage_alu
uint64_t n_IS_substage_alu;
n_IS_substage_alu = std::max({n_Issue, perfModel->IS_substage_alu.get(1), perfModel->LD_substage_alu.get(3)});
perfModel->IS_substage_alu.set(n_IS_substage_alu);
// OperandLookup
uint64_t n_OperandLookup;
n_OperandLookup = n_IS_substage_alu + 1;
// uA_OF_A_alu
uint64_t n_uA_OF_A_alu;
n_uA_OF_A_alu = std::max({n_IS_substage_alu, perfModel->regModel.getXa()});
// uA_OF_B_alu
uint64_t n_uA_OF_B_alu;
n_uA_OF_B_alu = std::max({n_IS_substage_alu, perfModel->regModel.getXb()});
// LD_substage_alu
uint64_t n_LD_substage_alu;
n_LD_substage_alu = std::max({n_OperandLookup, n_uA_OF_A_alu, n_uA_OF_B_alu, perfModel->LD_substage_alu.get(1), perfModel->EX_stage_alu.get(9), perfModel->EX_substage_alu.get(3)});
perfModel->LD_substage_alu.set(n_LD_substage_alu);
// ALU
uint64_t n_ALU;
n_ALU = n_LD_substage_alu + 1;
perfModel->regModel.setXd(n_ALU);
// EX_stage_alu
uint64_t n_EX_stage_alu;
n_EX_stage_alu = std::max({n_ALU, perfModel->EX_stage_alu.get(1), perfModel->EX_substage_alu.get(1)});
perfModel->EX_stage_alu.set(n_EX_stage_alu);
perfModel->EX_substage_alu.set(n_EX_stage_alu);
// OoO_stage
uint64_t n_OoO_stage;
n_OoO_stage = std::max({n_EX_stage_alu, perfModel->OoO_stage.get(1), perfModel->COM_stage.get(8)});
perfModel->OoO_stage.set(n_OoO_stage);
// Commit
uint64_t n_Commit;
n_Commit = n_OoO_stage + 2;
// COM_stage
uint64_t n_COM_stage;
n_COM_stage = std::max({n_Commit, perfModel->COM_stage.get(1)});
perfModel->COM_stage.set(n_COM_stage);

  // Dump Entrance point for info print (tracing)
  perfModel->entrancePoint = n_Enter;
  }
);

static SchedulingFunction *schedulingFunction_and = new SchedulingFunction(
  RV32_4ISSUE_SchedulingFunctionSet,
  "and",
  4,
  [](PerformanceModel* perfModel_){
  RV32_4ISSUE_PerformanceModel* perfModel = static_cast<RV32_4ISSUE_PerformanceModel*>(perfModel_);
  // Enter
uint64_t n_Enter;
n_Enter = std::max({perfModel->IF_stage.get(16), perfModel->PC_substage.get(4)});
// PCGen
uint64_t n_PCGen;
n_PCGen = n_Enter + 1;
// uA_PcCorrect
uint64_t n_uA_PcCorrect;
n_uA_PcCorrect = std::max({n_Enter, perfModel->dynBranchPredModel.getPc_mp()});
// uA_CacheBlock
uint64_t n_uA_CacheBlock;
n_uA_CacheBlock = std::max({n_Enter, perfModel->iCacheModel.getIc_out()});
// PC_substage
uint64_t n_PC_substage;
n_PC_substage = std::max({n_PCGen, n_uA_PcCorrect, n_uA_CacheBlock, perfModel->PC_substage.get(1), perfModel->IF_substage_0.get(4)});
perfModel->PC_substage.set(n_PC_substage);
// ICacheCtrl
uint64_t n_ICacheCtrl;
n_ICacheCtrl = n_PC_substage + 1;
// IF_substage_0
uint64_t n_IF_substage_0;
n_IF_substage_0 = std::max({n_ICacheCtrl, perfModel->IF_substage_0.get(1), perfModel->IF_substage_1.get(4)});
perfModel->IF_substage_0.set(n_IF_substage_0);
// ICache
uint64_t n_ICache;
n_ICache = n_IF_substage_0 + perfModel->iCacheModel.getDelay();
perfModel->iCacheModel.setIc_in(n_ICache);
// uA_PcPredict
uint64_t n_uA_PcPredict;
n_uA_PcPredict = std::max({n_IF_substage_0, perfModel->dynBranchPredModel.getPc_pt()});
// IF_substage_1
uint64_t n_IF_substage_1;
n_IF_substage_1 = std::max({n_ICache, n_uA_PcPredict, perfModel->IF_substage_1.get(1), perfModel->IF_substage_2.get(4)});
perfModel->IF_substage_1.set(n_IF_substage_1);
// IScan
uint64_t n_IScan;
n_IScan = n_IF_substage_1 + 1;
// IF_stage
uint64_t n_IF_stage;
n_IF_stage = std::max({n_IScan, perfModel->IF_stage.get(1), perfModel->IF_substage_2.get(1), perfModel->DEC_stage.get(4)});
perfModel->IF_stage.set(n_IF_stage);
perfModel->IF_substage_2.set(n_IF_stage);
// Decoder
uint64_t n_Decoder;
n_Decoder = n_IF_stage + 1;
// DEC_stage
uint64_t n_DEC_stage;
n_DEC_stage = std::max({n_Decoder, perfModel->DEC_stage.get(1), perfModel->RN_stage.get(5)});
perfModel->DEC_stage.set(n_DEC_stage);
// Rename
uint64_t n_Rename;
n_Rename = n_DEC_stage + 1;
// RN_stage
uint64_t n_RN_stage;
n_RN_stage = std::max({n_Rename, perfModel->RN_stage.get(1), perfModel->OoO_stage.get(64), perfModel->IS_substage_alu.get(24)});
perfModel->RN_stage.set(n_RN_stage);
// Issue
uint64_t n_Issue;
n_Issue = n_RN_stage + 2;
// IS_substage_alu
uint64_t n_IS_substage_alu;
n_IS_substage_alu = std::max({n_Issue, perfModel->IS_substage_alu.get(1), perfModel->LD_substage_alu.get(3)});
perfModel->IS_substage_alu.set(n_IS_substage_alu);
// OperandLookup
uint64_t n_OperandLookup;
n_OperandLookup = n_IS_substage_alu + 1;
// uA_OF_A_alu
uint64_t n_uA_OF_A_alu;
n_uA_OF_A_alu = std::max({n_IS_substage_alu, perfModel->regModel.getXa()});
// uA_OF_B_alu
uint64_t n_uA_OF_B_alu;
n_uA_OF_B_alu = std::max({n_IS_substage_alu, perfModel->regModel.getXb()});
// LD_substage_alu
uint64_t n_LD_substage_alu;
n_LD_substage_alu = std::max({n_OperandLookup, n_uA_OF_A_alu, n_uA_OF_B_alu, perfModel->LD_substage_alu.get(1), perfModel->EX_stage_alu.get(9), perfModel->EX_substage_alu.get(3)});
perfModel->LD_substage_alu.set(n_LD_substage_alu);
// ALU
uint64_t n_ALU;
n_ALU = n_LD_substage_alu + 1;
perfModel->regModel.setXd(n_ALU);
// EX_stage_alu
uint64_t n_EX_stage_alu;
n_EX_stage_alu = std::max({n_ALU, perfModel->EX_stage_alu.get(1), perfModel->EX_substage_alu.get(1)});
perfModel->EX_stage_alu.set(n_EX_stage_alu);
perfModel->EX_substage_alu.set(n_EX_stage_alu);
// OoO_stage
uint64_t n_OoO_stage;
n_OoO_stage = std::max({n_EX_stage_alu, perfModel->OoO_stage.get(1), perfModel->COM_stage.get(8)});
perfModel->OoO_stage.set(n_OoO_stage);
// Commit
uint64_t n_Commit;
n_Commit = n_OoO_stage + 2;
// COM_stage
uint64_t n_COM_stage;
n_COM_stage = std::max({n_Commit, perfModel->COM_stage.get(1)});
perfModel->COM_stage.set(n_COM_stage);

  // Dump Entrance point for info print (tracing)
  perfModel->entrancePoint = n_Enter;
  }
);

static SchedulingFunction *schedulingFunction_slt = new SchedulingFunction(
  RV32_4ISSUE_SchedulingFunctionSet,
  "slt",
  5,
  [](PerformanceModel* perfModel_){
  RV32_4ISSUE_PerformanceModel* perfModel = static_cast<RV32_4ISSUE_PerformanceModel*>(perfModel_);
  // Enter
uint64_t n_Enter;
n_Enter = std::max({perfModel->IF_stage.get(16), perfModel->PC_substage.get(4)});
// PCGen
uint64_t n_PCGen;
n_PCGen = n_Enter + 1;
// uA_PcCorrect
uint64_t n_uA_PcCorrect;
n_uA_PcCorrect = std::max({n_Enter, perfModel->dynBranchPredModel.getPc_mp()});
// uA_CacheBlock
uint64_t n_uA_CacheBlock;
n_uA_CacheBlock = std::max({n_Enter, perfModel->iCacheModel.getIc_out()});
// PC_substage
uint64_t n_PC_substage;
n_PC_substage = std::max({n_PCGen, n_uA_PcCorrect, n_uA_CacheBlock, perfModel->PC_substage.get(1), perfModel->IF_substage_0.get(4)});
perfModel->PC_substage.set(n_PC_substage);
// ICacheCtrl
uint64_t n_ICacheCtrl;
n_ICacheCtrl = n_PC_substage + 1;
// IF_substage_0
uint64_t n_IF_substage_0;
n_IF_substage_0 = std::max({n_ICacheCtrl, perfModel->IF_substage_0.get(1), perfModel->IF_substage_1.get(4)});
perfModel->IF_substage_0.set(n_IF_substage_0);
// ICache
uint64_t n_ICache;
n_ICache = n_IF_substage_0 + perfModel->iCacheModel.getDelay();
perfModel->iCacheModel.setIc_in(n_ICache);
// uA_PcPredict
uint64_t n_uA_PcPredict;
n_uA_PcPredict = std::max({n_IF_substage_0, perfModel->dynBranchPredModel.getPc_pt()});
// IF_substage_1
uint64_t n_IF_substage_1;
n_IF_substage_1 = std::max({n_ICache, n_uA_PcPredict, perfModel->IF_substage_1.get(1), perfModel->IF_substage_2.get(4)});
perfModel->IF_substage_1.set(n_IF_substage_1);
// IScan
uint64_t n_IScan;
n_IScan = n_IF_substage_1 + 1;
// IF_stage
uint64_t n_IF_stage;
n_IF_stage = std::max({n_IScan, perfModel->IF_stage.get(1), perfModel->IF_substage_2.get(1), perfModel->DEC_stage.get(4)});
perfModel->IF_stage.set(n_IF_stage);
perfModel->IF_substage_2.set(n_IF_stage);
// Decoder
uint64_t n_Decoder;
n_Decoder = n_IF_stage + 1;
// DEC_stage
uint64_t n_DEC_stage;
n_DEC_stage = std::max({n_Decoder, perfModel->DEC_stage.get(1), perfModel->RN_stage.get(5)});
perfModel->DEC_stage.set(n_DEC_stage);
// Rename
uint64_t n_Rename;
n_Rename = n_DEC_stage + 1;
// RN_stage
uint64_t n_RN_stage;
n_RN_stage = std::max({n_Rename, perfModel->RN_stage.get(1), perfModel->OoO_stage.get(64), perfModel->IS_substage_alu.get(24)});
perfModel->RN_stage.set(n_RN_stage);
// Issue
uint64_t n_Issue;
n_Issue = n_RN_stage + 2;
// IS_substage_alu
uint64_t n_IS_substage_alu;
n_IS_substage_alu = std::max({n_Issue, perfModel->IS_substage_alu.get(1), perfModel->LD_substage_alu.get(3)});
perfModel->IS_substage_alu.set(n_IS_substage_alu);
// OperandLookup
uint64_t n_OperandLookup;
n_OperandLookup = n_IS_substage_alu + 1;
// uA_OF_A_alu
uint64_t n_uA_OF_A_alu;
n_uA_OF_A_alu = std::max({n_IS_substage_alu, perfModel->regModel.getXa()});
// uA_OF_B_alu
uint64_t n_uA_OF_B_alu;
n_uA_OF_B_alu = std::max({n_IS_substage_alu, perfModel->regModel.getXb()});
// LD_substage_alu
uint64_t n_LD_substage_alu;
n_LD_substage_alu = std::max({n_OperandLookup, n_uA_OF_A_alu, n_uA_OF_B_alu, perfModel->LD_substage_alu.get(1), perfModel->EX_stage_alu.get(9), perfModel->EX_substage_alu.get(3)});
perfModel->LD_substage_alu.set(n_LD_substage_alu);
// ALU
uint64_t n_ALU;
n_ALU = n_LD_substage_alu + 1;
perfModel->regModel.setXd(n_ALU);
// EX_stage_alu
uint64_t n_EX_stage_alu;
n_EX_stage_alu = std::max({n_ALU, perfModel->EX_stage_alu.get(1), perfModel->EX_substage_alu.get(1)});
perfModel->EX_stage_alu.set(n_EX_stage_alu);
perfModel->EX_substage_alu.set(n_EX_stage_alu);
// OoO_stage
uint64_t n_OoO_stage;
n_OoO_stage = std::max({n_EX_stage_alu, perfModel->OoO_stage.get(1), perfModel->COM_stage.get(8)});
perfModel->OoO_stage.set(n_OoO_stage);
// Commit
uint64_t n_Commit;
n_Commit = n_OoO_stage + 2;
// COM_stage
uint64_t n_COM_stage;
n_COM_stage = std::max({n_Commit, perfModel->COM_stage.get(1)});
perfModel->COM_stage.set(n_COM_stage);

  // Dump Entrance point for info print (tracing)
  perfModel->entrancePoint = n_Enter;
  }
);

static SchedulingFunction *schedulingFunction_sltu = new SchedulingFunction(
  RV32_4ISSUE_SchedulingFunctionSet,
  "sltu",
  6,
  [](PerformanceModel* perfModel_){
  RV32_4ISSUE_PerformanceModel* perfModel = static_cast<RV32_4ISSUE_PerformanceModel*>(perfModel_);
  // Enter
uint64_t n_Enter;
n_Enter = std::max({perfModel->IF_stage.get(16), perfModel->PC_substage.get(4)});
// PCGen
uint64_t n_PCGen;
n_PCGen = n_Enter + 1;
// uA_PcCorrect
uint64_t n_uA_PcCorrect;
n_uA_PcCorrect = std::max({n_Enter, perfModel->dynBranchPredModel.getPc_mp()});
// uA_CacheBlock
uint64_t n_uA_CacheBlock;
n_uA_CacheBlock = std::max({n_Enter, perfModel->iCacheModel.getIc_out()});
// PC_substage
uint64_t n_PC_substage;
n_PC_substage = std::max({n_PCGen, n_uA_PcCorrect, n_uA_CacheBlock, perfModel->PC_substage.get(1), perfModel->IF_substage_0.get(4)});
perfModel->PC_substage.set(n_PC_substage);
// ICacheCtrl
uint64_t n_ICacheCtrl;
n_ICacheCtrl = n_PC_substage + 1;
// IF_substage_0
uint64_t n_IF_substage_0;
n_IF_substage_0 = std::max({n_ICacheCtrl, perfModel->IF_substage_0.get(1), perfModel->IF_substage_1.get(4)});
perfModel->IF_substage_0.set(n_IF_substage_0);
// ICache
uint64_t n_ICache;
n_ICache = n_IF_substage_0 + perfModel->iCacheModel.getDelay();
perfModel->iCacheModel.setIc_in(n_ICache);
// uA_PcPredict
uint64_t n_uA_PcPredict;
n_uA_PcPredict = std::max({n_IF_substage_0, perfModel->dynBranchPredModel.getPc_pt()});
// IF_substage_1
uint64_t n_IF_substage_1;
n_IF_substage_1 = std::max({n_ICache, n_uA_PcPredict, perfModel->IF_substage_1.get(1), perfModel->IF_substage_2.get(4)});
perfModel->IF_substage_1.set(n_IF_substage_1);
// IScan
uint64_t n_IScan;
n_IScan = n_IF_substage_1 + 1;
// IF_stage
uint64_t n_IF_stage;
n_IF_stage = std::max({n_IScan, perfModel->IF_stage.get(1), perfModel->IF_substage_2.get(1), perfModel->DEC_stage.get(4)});
perfModel->IF_stage.set(n_IF_stage);
perfModel->IF_substage_2.set(n_IF_stage);
// Decoder
uint64_t n_Decoder;
n_Decoder = n_IF_stage + 1;
// DEC_stage
uint64_t n_DEC_stage;
n_DEC_stage = std::max({n_Decoder, perfModel->DEC_stage.get(1), perfModel->RN_stage.get(5)});
perfModel->DEC_stage.set(n_DEC_stage);
// Rename
uint64_t n_Rename;
n_Rename = n_DEC_stage + 1;
// RN_stage
uint64_t n_RN_stage;
n_RN_stage = std::max({n_Rename, perfModel->RN_stage.get(1), perfModel->OoO_stage.get(64), perfModel->IS_substage_alu.get(24)});
perfModel->RN_stage.set(n_RN_stage);
// Issue
uint64_t n_Issue;
n_Issue = n_RN_stage + 2;
// IS_substage_alu
uint64_t n_IS_substage_alu;
n_IS_substage_alu = std::max({n_Issue, perfModel->IS_substage_alu.get(1), perfModel->LD_substage_alu.get(3)});
perfModel->IS_substage_alu.set(n_IS_substage_alu);
// OperandLookup
uint64_t n_OperandLookup;
n_OperandLookup = n_IS_substage_alu + 1;
// uA_OF_A_alu
uint64_t n_uA_OF_A_alu;
n_uA_OF_A_alu = std::max({n_IS_substage_alu, perfModel->regModel.getXa()});
// uA_OF_B_alu
uint64_t n_uA_OF_B_alu;
n_uA_OF_B_alu = std::max({n_IS_substage_alu, perfModel->regModel.getXb()});
// LD_substage_alu
uint64_t n_LD_substage_alu;
n_LD_substage_alu = std::max({n_OperandLookup, n_uA_OF_A_alu, n_uA_OF_B_alu, perfModel->LD_substage_alu.get(1), perfModel->EX_stage_alu.get(9), perfModel->EX_substage_alu.get(3)});
perfModel->LD_substage_alu.set(n_LD_substage_alu);
// ALU
uint64_t n_ALU;
n_ALU = n_LD_substage_alu + 1;
perfModel->regModel.setXd(n_ALU);
// EX_stage_alu
uint64_t n_EX_stage_alu;
n_EX_stage_alu = std::max({n_ALU, perfModel->EX_stage_alu.get(1), perfModel->EX_substage_alu.get(1)});
perfModel->EX_stage_alu.set(n_EX_stage_alu);
perfModel->EX_substage_alu.set(n_EX_stage_alu);
// OoO_stage
uint64_t n_OoO_stage;
n_OoO_stage = std::max({n_EX_stage_alu, perfModel->OoO_stage.get(1), perfModel->COM_stage.get(8)});
perfModel->OoO_stage.set(n_OoO_stage);
// Commit
uint64_t n_Commit;
n_Commit = n_OoO_stage + 2;
// COM_stage
uint64_t n_COM_stage;
n_COM_stage = std::max({n_Commit, perfModel->COM_stage.get(1)});
perfModel->COM_stage.set(n_COM_stage);

  // Dump Entrance point for info print (tracing)
  perfModel->entrancePoint = n_Enter;
  }
);

static SchedulingFunction *schedulingFunction_sll = new SchedulingFunction(
  RV32_4ISSUE_SchedulingFunctionSet,
  "sll",
  7,
  [](PerformanceModel* perfModel_){
  RV32_4ISSUE_PerformanceModel* perfModel = static_cast<RV32_4ISSUE_PerformanceModel*>(perfModel_);
  // Enter
uint64_t n_Enter;
n_Enter = std::max({perfModel->IF_stage.get(16), perfModel->PC_substage.get(4)});
// PCGen
uint64_t n_PCGen;
n_PCGen = n_Enter + 1;
// uA_PcCorrect
uint64_t n_uA_PcCorrect;
n_uA_PcCorrect = std::max({n_Enter, perfModel->dynBranchPredModel.getPc_mp()});
// uA_CacheBlock
uint64_t n_uA_CacheBlock;
n_uA_CacheBlock = std::max({n_Enter, perfModel->iCacheModel.getIc_out()});
// PC_substage
uint64_t n_PC_substage;
n_PC_substage = std::max({n_PCGen, n_uA_PcCorrect, n_uA_CacheBlock, perfModel->PC_substage.get(1), perfModel->IF_substage_0.get(4)});
perfModel->PC_substage.set(n_PC_substage);
// ICacheCtrl
uint64_t n_ICacheCtrl;
n_ICacheCtrl = n_PC_substage + 1;
// IF_substage_0
uint64_t n_IF_substage_0;
n_IF_substage_0 = std::max({n_ICacheCtrl, perfModel->IF_substage_0.get(1), perfModel->IF_substage_1.get(4)});
perfModel->IF_substage_0.set(n_IF_substage_0);
// ICache
uint64_t n_ICache;
n_ICache = n_IF_substage_0 + perfModel->iCacheModel.getDelay();
perfModel->iCacheModel.setIc_in(n_ICache);
// uA_PcPredict
uint64_t n_uA_PcPredict;
n_uA_PcPredict = std::max({n_IF_substage_0, perfModel->dynBranchPredModel.getPc_pt()});
// IF_substage_1
uint64_t n_IF_substage_1;
n_IF_substage_1 = std::max({n_ICache, n_uA_PcPredict, perfModel->IF_substage_1.get(1), perfModel->IF_substage_2.get(4)});
perfModel->IF_substage_1.set(n_IF_substage_1);
// IScan
uint64_t n_IScan;
n_IScan = n_IF_substage_1 + 1;
// IF_stage
uint64_t n_IF_stage;
n_IF_stage = std::max({n_IScan, perfModel->IF_stage.get(1), perfModel->IF_substage_2.get(1), perfModel->DEC_stage.get(4)});
perfModel->IF_stage.set(n_IF_stage);
perfModel->IF_substage_2.set(n_IF_stage);
// Decoder
uint64_t n_Decoder;
n_Decoder = n_IF_stage + 1;
// DEC_stage
uint64_t n_DEC_stage;
n_DEC_stage = std::max({n_Decoder, perfModel->DEC_stage.get(1), perfModel->RN_stage.get(5)});
perfModel->DEC_stage.set(n_DEC_stage);
// Rename
uint64_t n_Rename;
n_Rename = n_DEC_stage + 1;
// RN_stage
uint64_t n_RN_stage;
n_RN_stage = std::max({n_Rename, perfModel->RN_stage.get(1), perfModel->OoO_stage.get(64), perfModel->IS_substage_alu.get(24)});
perfModel->RN_stage.set(n_RN_stage);
// Issue
uint64_t n_Issue;
n_Issue = n_RN_stage + 2;
// IS_substage_alu
uint64_t n_IS_substage_alu;
n_IS_substage_alu = std::max({n_Issue, perfModel->IS_substage_alu.get(1), perfModel->LD_substage_alu.get(3)});
perfModel->IS_substage_alu.set(n_IS_substage_alu);
// OperandLookup
uint64_t n_OperandLookup;
n_OperandLookup = n_IS_substage_alu + 1;
// uA_OF_A_alu
uint64_t n_uA_OF_A_alu;
n_uA_OF_A_alu = std::max({n_IS_substage_alu, perfModel->regModel.getXa()});
// uA_OF_B_alu
uint64_t n_uA_OF_B_alu;
n_uA_OF_B_alu = std::max({n_IS_substage_alu, perfModel->regModel.getXb()});
// LD_substage_alu
uint64_t n_LD_substage_alu;
n_LD_substage_alu = std::max({n_OperandLookup, n_uA_OF_A_alu, n_uA_OF_B_alu, perfModel->LD_substage_alu.get(1), perfModel->EX_stage_alu.get(9), perfModel->EX_substage_alu.get(3)});
perfModel->LD_substage_alu.set(n_LD_substage_alu);
// ALU
uint64_t n_ALU;
n_ALU = n_LD_substage_alu + 1;
perfModel->regModel.setXd(n_ALU);
// EX_stage_alu
uint64_t n_EX_stage_alu;
n_EX_stage_alu = std::max({n_ALU, perfModel->EX_stage_alu.get(1), perfModel->EX_substage_alu.get(1)});
perfModel->EX_stage_alu.set(n_EX_stage_alu);
perfModel->EX_substage_alu.set(n_EX_stage_alu);
// OoO_stage
uint64_t n_OoO_stage;
n_OoO_stage = std::max({n_EX_stage_alu, perfModel->OoO_stage.get(1), perfModel->COM_stage.get(8)});
perfModel->OoO_stage.set(n_OoO_stage);
// Commit
uint64_t n_Commit;
n_Commit = n_OoO_stage + 2;
// COM_stage
uint64_t n_COM_stage;
n_COM_stage = std::max({n_Commit, perfModel->COM_stage.get(1)});
perfModel->COM_stage.set(n_COM_stage);

  // Dump Entrance point for info print (tracing)
  perfModel->entrancePoint = n_Enter;
  }
);

static SchedulingFunction *schedulingFunction_srl = new SchedulingFunction(
  RV32_4ISSUE_SchedulingFunctionSet,
  "srl",
  8,
  [](PerformanceModel* perfModel_){
  RV32_4ISSUE_PerformanceModel* perfModel = static_cast<RV32_4ISSUE_PerformanceModel*>(perfModel_);
  // Enter
uint64_t n_Enter;
n_Enter = std::max({perfModel->IF_stage.get(16), perfModel->PC_substage.get(4)});
// PCGen
uint64_t n_PCGen;
n_PCGen = n_Enter + 1;
// uA_PcCorrect
uint64_t n_uA_PcCorrect;
n_uA_PcCorrect = std::max({n_Enter, perfModel->dynBranchPredModel.getPc_mp()});
// uA_CacheBlock
uint64_t n_uA_CacheBlock;
n_uA_CacheBlock = std::max({n_Enter, perfModel->iCacheModel.getIc_out()});
// PC_substage
uint64_t n_PC_substage;
n_PC_substage = std::max({n_PCGen, n_uA_PcCorrect, n_uA_CacheBlock, perfModel->PC_substage.get(1), perfModel->IF_substage_0.get(4)});
perfModel->PC_substage.set(n_PC_substage);
// ICacheCtrl
uint64_t n_ICacheCtrl;
n_ICacheCtrl = n_PC_substage + 1;
// IF_substage_0
uint64_t n_IF_substage_0;
n_IF_substage_0 = std::max({n_ICacheCtrl, perfModel->IF_substage_0.get(1), perfModel->IF_substage_1.get(4)});
perfModel->IF_substage_0.set(n_IF_substage_0);
// ICache
uint64_t n_ICache;
n_ICache = n_IF_substage_0 + perfModel->iCacheModel.getDelay();
perfModel->iCacheModel.setIc_in(n_ICache);
// uA_PcPredict
uint64_t n_uA_PcPredict;
n_uA_PcPredict = std::max({n_IF_substage_0, perfModel->dynBranchPredModel.getPc_pt()});
// IF_substage_1
uint64_t n_IF_substage_1;
n_IF_substage_1 = std::max({n_ICache, n_uA_PcPredict, perfModel->IF_substage_1.get(1), perfModel->IF_substage_2.get(4)});
perfModel->IF_substage_1.set(n_IF_substage_1);
// IScan
uint64_t n_IScan;
n_IScan = n_IF_substage_1 + 1;
// IF_stage
uint64_t n_IF_stage;
n_IF_stage = std::max({n_IScan, perfModel->IF_stage.get(1), perfModel->IF_substage_2.get(1), perfModel->DEC_stage.get(4)});
perfModel->IF_stage.set(n_IF_stage);
perfModel->IF_substage_2.set(n_IF_stage);
// Decoder
uint64_t n_Decoder;
n_Decoder = n_IF_stage + 1;
// DEC_stage
uint64_t n_DEC_stage;
n_DEC_stage = std::max({n_Decoder, perfModel->DEC_stage.get(1), perfModel->RN_stage.get(5)});
perfModel->DEC_stage.set(n_DEC_stage);
// Rename
uint64_t n_Rename;
n_Rename = n_DEC_stage + 1;
// RN_stage
uint64_t n_RN_stage;
n_RN_stage = std::max({n_Rename, perfModel->RN_stage.get(1), perfModel->OoO_stage.get(64), perfModel->IS_substage_alu.get(24)});
perfModel->RN_stage.set(n_RN_stage);
// Issue
uint64_t n_Issue;
n_Issue = n_RN_stage + 2;
// IS_substage_alu
uint64_t n_IS_substage_alu;
n_IS_substage_alu = std::max({n_Issue, perfModel->IS_substage_alu.get(1), perfModel->LD_substage_alu.get(3)});
perfModel->IS_substage_alu.set(n_IS_substage_alu);
// OperandLookup
uint64_t n_OperandLookup;
n_OperandLookup = n_IS_substage_alu + 1;
// uA_OF_A_alu
uint64_t n_uA_OF_A_alu;
n_uA_OF_A_alu = std::max({n_IS_substage_alu, perfModel->regModel.getXa()});
// uA_OF_B_alu
uint64_t n_uA_OF_B_alu;
n_uA_OF_B_alu = std::max({n_IS_substage_alu, perfModel->regModel.getXb()});
// LD_substage_alu
uint64_t n_LD_substage_alu;
n_LD_substage_alu = std::max({n_OperandLookup, n_uA_OF_A_alu, n_uA_OF_B_alu, perfModel->LD_substage_alu.get(1), perfModel->EX_stage_alu.get(9), perfModel->EX_substage_alu.get(3)});
perfModel->LD_substage_alu.set(n_LD_substage_alu);
// ALU
uint64_t n_ALU;
n_ALU = n_LD_substage_alu + 1;
perfModel->regModel.setXd(n_ALU);
// EX_stage_alu
uint64_t n_EX_stage_alu;
n_EX_stage_alu = std::max({n_ALU, perfModel->EX_stage_alu.get(1), perfModel->EX_substage_alu.get(1)});
perfModel->EX_stage_alu.set(n_EX_stage_alu);
perfModel->EX_substage_alu.set(n_EX_stage_alu);
// OoO_stage
uint64_t n_OoO_stage;
n_OoO_stage = std::max({n_EX_stage_alu, perfModel->OoO_stage.get(1), perfModel->COM_stage.get(8)});
perfModel->OoO_stage.set(n_OoO_stage);
// Commit
uint64_t n_Commit;
n_Commit = n_OoO_stage + 2;
// COM_stage
uint64_t n_COM_stage;
n_COM_stage = std::max({n_Commit, perfModel->COM_stage.get(1)});
perfModel->COM_stage.set(n_COM_stage);

  // Dump Entrance point for info print (tracing)
  perfModel->entrancePoint = n_Enter;
  }
);

static SchedulingFunction *schedulingFunction_sra = new SchedulingFunction(
  RV32_4ISSUE_SchedulingFunctionSet,
  "sra",
  9,
  [](PerformanceModel* perfModel_){
  RV32_4ISSUE_PerformanceModel* perfModel = static_cast<RV32_4ISSUE_PerformanceModel*>(perfModel_);
  // Enter
uint64_t n_Enter;
n_Enter = std::max({perfModel->IF_stage.get(16), perfModel->PC_substage.get(4)});
// PCGen
uint64_t n_PCGen;
n_PCGen = n_Enter + 1;
// uA_PcCorrect
uint64_t n_uA_PcCorrect;
n_uA_PcCorrect = std::max({n_Enter, perfModel->dynBranchPredModel.getPc_mp()});
// uA_CacheBlock
uint64_t n_uA_CacheBlock;
n_uA_CacheBlock = std::max({n_Enter, perfModel->iCacheModel.getIc_out()});
// PC_substage
uint64_t n_PC_substage;
n_PC_substage = std::max({n_PCGen, n_uA_PcCorrect, n_uA_CacheBlock, perfModel->PC_substage.get(1), perfModel->IF_substage_0.get(4)});
perfModel->PC_substage.set(n_PC_substage);
// ICacheCtrl
uint64_t n_ICacheCtrl;
n_ICacheCtrl = n_PC_substage + 1;
// IF_substage_0
uint64_t n_IF_substage_0;
n_IF_substage_0 = std::max({n_ICacheCtrl, perfModel->IF_substage_0.get(1), perfModel->IF_substage_1.get(4)});
perfModel->IF_substage_0.set(n_IF_substage_0);
// ICache
uint64_t n_ICache;
n_ICache = n_IF_substage_0 + perfModel->iCacheModel.getDelay();
perfModel->iCacheModel.setIc_in(n_ICache);
// uA_PcPredict
uint64_t n_uA_PcPredict;
n_uA_PcPredict = std::max({n_IF_substage_0, perfModel->dynBranchPredModel.getPc_pt()});
// IF_substage_1
uint64_t n_IF_substage_1;
n_IF_substage_1 = std::max({n_ICache, n_uA_PcPredict, perfModel->IF_substage_1.get(1), perfModel->IF_substage_2.get(4)});
perfModel->IF_substage_1.set(n_IF_substage_1);
// IScan
uint64_t n_IScan;
n_IScan = n_IF_substage_1 + 1;
// IF_stage
uint64_t n_IF_stage;
n_IF_stage = std::max({n_IScan, perfModel->IF_stage.get(1), perfModel->IF_substage_2.get(1), perfModel->DEC_stage.get(4)});
perfModel->IF_stage.set(n_IF_stage);
perfModel->IF_substage_2.set(n_IF_stage);
// Decoder
uint64_t n_Decoder;
n_Decoder = n_IF_stage + 1;
// DEC_stage
uint64_t n_DEC_stage;
n_DEC_stage = std::max({n_Decoder, perfModel->DEC_stage.get(1), perfModel->RN_stage.get(5)});
perfModel->DEC_stage.set(n_DEC_stage);
// Rename
uint64_t n_Rename;
n_Rename = n_DEC_stage + 1;
// RN_stage
uint64_t n_RN_stage;
n_RN_stage = std::max({n_Rename, perfModel->RN_stage.get(1), perfModel->OoO_stage.get(64), perfModel->IS_substage_alu.get(24)});
perfModel->RN_stage.set(n_RN_stage);
// Issue
uint64_t n_Issue;
n_Issue = n_RN_stage + 2;
// IS_substage_alu
uint64_t n_IS_substage_alu;
n_IS_substage_alu = std::max({n_Issue, perfModel->IS_substage_alu.get(1), perfModel->LD_substage_alu.get(3)});
perfModel->IS_substage_alu.set(n_IS_substage_alu);
// OperandLookup
uint64_t n_OperandLookup;
n_OperandLookup = n_IS_substage_alu + 1;
// uA_OF_A_alu
uint64_t n_uA_OF_A_alu;
n_uA_OF_A_alu = std::max({n_IS_substage_alu, perfModel->regModel.getXa()});
// uA_OF_B_alu
uint64_t n_uA_OF_B_alu;
n_uA_OF_B_alu = std::max({n_IS_substage_alu, perfModel->regModel.getXb()});
// LD_substage_alu
uint64_t n_LD_substage_alu;
n_LD_substage_alu = std::max({n_OperandLookup, n_uA_OF_A_alu, n_uA_OF_B_alu, perfModel->LD_substage_alu.get(1), perfModel->EX_stage_alu.get(9), perfModel->EX_substage_alu.get(3)});
perfModel->LD_substage_alu.set(n_LD_substage_alu);
// ALU
uint64_t n_ALU;
n_ALU = n_LD_substage_alu + 1;
perfModel->regModel.setXd(n_ALU);
// EX_stage_alu
uint64_t n_EX_stage_alu;
n_EX_stage_alu = std::max({n_ALU, perfModel->EX_stage_alu.get(1), perfModel->EX_substage_alu.get(1)});
perfModel->EX_stage_alu.set(n_EX_stage_alu);
perfModel->EX_substage_alu.set(n_EX_stage_alu);
// OoO_stage
uint64_t n_OoO_stage;
n_OoO_stage = std::max({n_EX_stage_alu, perfModel->OoO_stage.get(1), perfModel->COM_stage.get(8)});
perfModel->OoO_stage.set(n_OoO_stage);
// Commit
uint64_t n_Commit;
n_Commit = n_OoO_stage + 2;
// COM_stage
uint64_t n_COM_stage;
n_COM_stage = std::max({n_Commit, perfModel->COM_stage.get(1)});
perfModel->COM_stage.set(n_COM_stage);

  // Dump Entrance point for info print (tracing)
  perfModel->entrancePoint = n_Enter;
  }
);

static SchedulingFunction *schedulingFunction_addi = new SchedulingFunction(
  RV32_4ISSUE_SchedulingFunctionSet,
  "addi",
  10,
  [](PerformanceModel* perfModel_){
  RV32_4ISSUE_PerformanceModel* perfModel = static_cast<RV32_4ISSUE_PerformanceModel*>(perfModel_);
  // Enter
uint64_t n_Enter;
n_Enter = std::max({perfModel->IF_stage.get(16), perfModel->PC_substage.get(4)});
// PCGen
uint64_t n_PCGen;
n_PCGen = n_Enter + 1;
// uA_PcCorrect
uint64_t n_uA_PcCorrect;
n_uA_PcCorrect = std::max({n_Enter, perfModel->dynBranchPredModel.getPc_mp()});
// uA_CacheBlock
uint64_t n_uA_CacheBlock;
n_uA_CacheBlock = std::max({n_Enter, perfModel->iCacheModel.getIc_out()});
// PC_substage
uint64_t n_PC_substage;
n_PC_substage = std::max({n_PCGen, n_uA_PcCorrect, n_uA_CacheBlock, perfModel->PC_substage.get(1), perfModel->IF_substage_0.get(4)});
perfModel->PC_substage.set(n_PC_substage);
// ICacheCtrl
uint64_t n_ICacheCtrl;
n_ICacheCtrl = n_PC_substage + 1;
// IF_substage_0
uint64_t n_IF_substage_0;
n_IF_substage_0 = std::max({n_ICacheCtrl, perfModel->IF_substage_0.get(1), perfModel->IF_substage_1.get(4)});
perfModel->IF_substage_0.set(n_IF_substage_0);
// ICache
uint64_t n_ICache;
n_ICache = n_IF_substage_0 + perfModel->iCacheModel.getDelay();
perfModel->iCacheModel.setIc_in(n_ICache);
// uA_PcPredict
uint64_t n_uA_PcPredict;
n_uA_PcPredict = std::max({n_IF_substage_0, perfModel->dynBranchPredModel.getPc_pt()});
// IF_substage_1
uint64_t n_IF_substage_1;
n_IF_substage_1 = std::max({n_ICache, n_uA_PcPredict, perfModel->IF_substage_1.get(1), perfModel->IF_substage_2.get(4)});
perfModel->IF_substage_1.set(n_IF_substage_1);
// IScan
uint64_t n_IScan;
n_IScan = n_IF_substage_1 + 1;
// IF_stage
uint64_t n_IF_stage;
n_IF_stage = std::max({n_IScan, perfModel->IF_stage.get(1), perfModel->IF_substage_2.get(1), perfModel->DEC_stage.get(4)});
perfModel->IF_stage.set(n_IF_stage);
perfModel->IF_substage_2.set(n_IF_stage);
// Decoder
uint64_t n_Decoder;
n_Decoder = n_IF_stage + 1;
// DEC_stage
uint64_t n_DEC_stage;
n_DEC_stage = std::max({n_Decoder, perfModel->DEC_stage.get(1), perfModel->RN_stage.get(5)});
perfModel->DEC_stage.set(n_DEC_stage);
// Rename
uint64_t n_Rename;
n_Rename = n_DEC_stage + 1;
// RN_stage
uint64_t n_RN_stage;
n_RN_stage = std::max({n_Rename, perfModel->RN_stage.get(1), perfModel->OoO_stage.get(64), perfModel->IS_substage_alu.get(24)});
perfModel->RN_stage.set(n_RN_stage);
// Issue
uint64_t n_Issue;
n_Issue = n_RN_stage + 2;
// IS_substage_alu
uint64_t n_IS_substage_alu;
n_IS_substage_alu = std::max({n_Issue, perfModel->IS_substage_alu.get(1), perfModel->LD_substage_alu.get(3)});
perfModel->IS_substage_alu.set(n_IS_substage_alu);
// OperandLookup
uint64_t n_OperandLookup;
n_OperandLookup = n_IS_substage_alu + 1;
// uA_OF_A_alu
uint64_t n_uA_OF_A_alu;
n_uA_OF_A_alu = std::max({n_IS_substage_alu, perfModel->regModel.getXa()});
// LD_substage_alu
uint64_t n_LD_substage_alu;
n_LD_substage_alu = std::max({n_OperandLookup, n_uA_OF_A_alu, perfModel->LD_substage_alu.get(1), perfModel->EX_stage_alu.get(9), perfModel->EX_substage_alu.get(3)});
perfModel->LD_substage_alu.set(n_LD_substage_alu);
// ALU
uint64_t n_ALU;
n_ALU = n_LD_substage_alu + 1;
perfModel->regModel.setXd(n_ALU);
// EX_stage_alu
uint64_t n_EX_stage_alu;
n_EX_stage_alu = std::max({n_ALU, perfModel->EX_stage_alu.get(1), perfModel->EX_substage_alu.get(1)});
perfModel->EX_stage_alu.set(n_EX_stage_alu);
perfModel->EX_substage_alu.set(n_EX_stage_alu);
// OoO_stage
uint64_t n_OoO_stage;
n_OoO_stage = std::max({n_EX_stage_alu, perfModel->OoO_stage.get(1), perfModel->COM_stage.get(8)});
perfModel->OoO_stage.set(n_OoO_stage);
// Commit
uint64_t n_Commit;
n_Commit = n_OoO_stage + 2;
// COM_stage
uint64_t n_COM_stage;
n_COM_stage = std::max({n_Commit, perfModel->COM_stage.get(1)});
perfModel->COM_stage.set(n_COM_stage);

  // Dump Entrance point for info print (tracing)
  perfModel->entrancePoint = n_Enter;
  }
);

static SchedulingFunction *schedulingFunction_xori = new SchedulingFunction(
  RV32_4ISSUE_SchedulingFunctionSet,
  "xori",
  11,
  [](PerformanceModel* perfModel_){
  RV32_4ISSUE_PerformanceModel* perfModel = static_cast<RV32_4ISSUE_PerformanceModel*>(perfModel_);
  // Enter
uint64_t n_Enter;
n_Enter = std::max({perfModel->IF_stage.get(16), perfModel->PC_substage.get(4)});
// PCGen
uint64_t n_PCGen;
n_PCGen = n_Enter + 1;
// uA_PcCorrect
uint64_t n_uA_PcCorrect;
n_uA_PcCorrect = std::max({n_Enter, perfModel->dynBranchPredModel.getPc_mp()});
// uA_CacheBlock
uint64_t n_uA_CacheBlock;
n_uA_CacheBlock = std::max({n_Enter, perfModel->iCacheModel.getIc_out()});
// PC_substage
uint64_t n_PC_substage;
n_PC_substage = std::max({n_PCGen, n_uA_PcCorrect, n_uA_CacheBlock, perfModel->PC_substage.get(1), perfModel->IF_substage_0.get(4)});
perfModel->PC_substage.set(n_PC_substage);
// ICacheCtrl
uint64_t n_ICacheCtrl;
n_ICacheCtrl = n_PC_substage + 1;
// IF_substage_0
uint64_t n_IF_substage_0;
n_IF_substage_0 = std::max({n_ICacheCtrl, perfModel->IF_substage_0.get(1), perfModel->IF_substage_1.get(4)});
perfModel->IF_substage_0.set(n_IF_substage_0);
// ICache
uint64_t n_ICache;
n_ICache = n_IF_substage_0 + perfModel->iCacheModel.getDelay();
perfModel->iCacheModel.setIc_in(n_ICache);
// uA_PcPredict
uint64_t n_uA_PcPredict;
n_uA_PcPredict = std::max({n_IF_substage_0, perfModel->dynBranchPredModel.getPc_pt()});
// IF_substage_1
uint64_t n_IF_substage_1;
n_IF_substage_1 = std::max({n_ICache, n_uA_PcPredict, perfModel->IF_substage_1.get(1), perfModel->IF_substage_2.get(4)});
perfModel->IF_substage_1.set(n_IF_substage_1);
// IScan
uint64_t n_IScan;
n_IScan = n_IF_substage_1 + 1;
// IF_stage
uint64_t n_IF_stage;
n_IF_stage = std::max({n_IScan, perfModel->IF_stage.get(1), perfModel->IF_substage_2.get(1), perfModel->DEC_stage.get(4)});
perfModel->IF_stage.set(n_IF_stage);
perfModel->IF_substage_2.set(n_IF_stage);
// Decoder
uint64_t n_Decoder;
n_Decoder = n_IF_stage + 1;
// DEC_stage
uint64_t n_DEC_stage;
n_DEC_stage = std::max({n_Decoder, perfModel->DEC_stage.get(1), perfModel->RN_stage.get(5)});
perfModel->DEC_stage.set(n_DEC_stage);
// Rename
uint64_t n_Rename;
n_Rename = n_DEC_stage + 1;
// RN_stage
uint64_t n_RN_stage;
n_RN_stage = std::max({n_Rename, perfModel->RN_stage.get(1), perfModel->OoO_stage.get(64), perfModel->IS_substage_alu.get(24)});
perfModel->RN_stage.set(n_RN_stage);
// Issue
uint64_t n_Issue;
n_Issue = n_RN_stage + 2;
// IS_substage_alu
uint64_t n_IS_substage_alu;
n_IS_substage_alu = std::max({n_Issue, perfModel->IS_substage_alu.get(1), perfModel->LD_substage_alu.get(3)});
perfModel->IS_substage_alu.set(n_IS_substage_alu);
// OperandLookup
uint64_t n_OperandLookup;
n_OperandLookup = n_IS_substage_alu + 1;
// uA_OF_A_alu
uint64_t n_uA_OF_A_alu;
n_uA_OF_A_alu = std::max({n_IS_substage_alu, perfModel->regModel.getXa()});
// LD_substage_alu
uint64_t n_LD_substage_alu;
n_LD_substage_alu = std::max({n_OperandLookup, n_uA_OF_A_alu, perfModel->LD_substage_alu.get(1), perfModel->EX_stage_alu.get(9), perfModel->EX_substage_alu.get(3)});
perfModel->LD_substage_alu.set(n_LD_substage_alu);
// ALU
uint64_t n_ALU;
n_ALU = n_LD_substage_alu + 1;
perfModel->regModel.setXd(n_ALU);
// EX_stage_alu
uint64_t n_EX_stage_alu;
n_EX_stage_alu = std::max({n_ALU, perfModel->EX_stage_alu.get(1), perfModel->EX_substage_alu.get(1)});
perfModel->EX_stage_alu.set(n_EX_stage_alu);
perfModel->EX_substage_alu.set(n_EX_stage_alu);
// OoO_stage
uint64_t n_OoO_stage;
n_OoO_stage = std::max({n_EX_stage_alu, perfModel->OoO_stage.get(1), perfModel->COM_stage.get(8)});
perfModel->OoO_stage.set(n_OoO_stage);
// Commit
uint64_t n_Commit;
n_Commit = n_OoO_stage + 2;
// COM_stage
uint64_t n_COM_stage;
n_COM_stage = std::max({n_Commit, perfModel->COM_stage.get(1)});
perfModel->COM_stage.set(n_COM_stage);

  // Dump Entrance point for info print (tracing)
  perfModel->entrancePoint = n_Enter;
  }
);

static SchedulingFunction *schedulingFunction_ori = new SchedulingFunction(
  RV32_4ISSUE_SchedulingFunctionSet,
  "ori",
  12,
  [](PerformanceModel* perfModel_){
  RV32_4ISSUE_PerformanceModel* perfModel = static_cast<RV32_4ISSUE_PerformanceModel*>(perfModel_);
  // Enter
uint64_t n_Enter;
n_Enter = std::max({perfModel->IF_stage.get(16), perfModel->PC_substage.get(4)});
// PCGen
uint64_t n_PCGen;
n_PCGen = n_Enter + 1;
// uA_PcCorrect
uint64_t n_uA_PcCorrect;
n_uA_PcCorrect = std::max({n_Enter, perfModel->dynBranchPredModel.getPc_mp()});
// uA_CacheBlock
uint64_t n_uA_CacheBlock;
n_uA_CacheBlock = std::max({n_Enter, perfModel->iCacheModel.getIc_out()});
// PC_substage
uint64_t n_PC_substage;
n_PC_substage = std::max({n_PCGen, n_uA_PcCorrect, n_uA_CacheBlock, perfModel->PC_substage.get(1), perfModel->IF_substage_0.get(4)});
perfModel->PC_substage.set(n_PC_substage);
// ICacheCtrl
uint64_t n_ICacheCtrl;
n_ICacheCtrl = n_PC_substage + 1;
// IF_substage_0
uint64_t n_IF_substage_0;
n_IF_substage_0 = std::max({n_ICacheCtrl, perfModel->IF_substage_0.get(1), perfModel->IF_substage_1.get(4)});
perfModel->IF_substage_0.set(n_IF_substage_0);
// ICache
uint64_t n_ICache;
n_ICache = n_IF_substage_0 + perfModel->iCacheModel.getDelay();
perfModel->iCacheModel.setIc_in(n_ICache);
// uA_PcPredict
uint64_t n_uA_PcPredict;
n_uA_PcPredict = std::max({n_IF_substage_0, perfModel->dynBranchPredModel.getPc_pt()});
// IF_substage_1
uint64_t n_IF_substage_1;
n_IF_substage_1 = std::max({n_ICache, n_uA_PcPredict, perfModel->IF_substage_1.get(1), perfModel->IF_substage_2.get(4)});
perfModel->IF_substage_1.set(n_IF_substage_1);
// IScan
uint64_t n_IScan;
n_IScan = n_IF_substage_1 + 1;
// IF_stage
uint64_t n_IF_stage;
n_IF_stage = std::max({n_IScan, perfModel->IF_stage.get(1), perfModel->IF_substage_2.get(1), perfModel->DEC_stage.get(4)});
perfModel->IF_stage.set(n_IF_stage);
perfModel->IF_substage_2.set(n_IF_stage);
// Decoder
uint64_t n_Decoder;
n_Decoder = n_IF_stage + 1;
// DEC_stage
uint64_t n_DEC_stage;
n_DEC_stage = std::max({n_Decoder, perfModel->DEC_stage.get(1), perfModel->RN_stage.get(5)});
perfModel->DEC_stage.set(n_DEC_stage);
// Rename
uint64_t n_Rename;
n_Rename = n_DEC_stage + 1;
// RN_stage
uint64_t n_RN_stage;
n_RN_stage = std::max({n_Rename, perfModel->RN_stage.get(1), perfModel->OoO_stage.get(64), perfModel->IS_substage_alu.get(24)});
perfModel->RN_stage.set(n_RN_stage);
// Issue
uint64_t n_Issue;
n_Issue = n_RN_stage + 2;
// IS_substage_alu
uint64_t n_IS_substage_alu;
n_IS_substage_alu = std::max({n_Issue, perfModel->IS_substage_alu.get(1), perfModel->LD_substage_alu.get(3)});
perfModel->IS_substage_alu.set(n_IS_substage_alu);
// OperandLookup
uint64_t n_OperandLookup;
n_OperandLookup = n_IS_substage_alu + 1;
// uA_OF_A_alu
uint64_t n_uA_OF_A_alu;
n_uA_OF_A_alu = std::max({n_IS_substage_alu, perfModel->regModel.getXa()});
// LD_substage_alu
uint64_t n_LD_substage_alu;
n_LD_substage_alu = std::max({n_OperandLookup, n_uA_OF_A_alu, perfModel->LD_substage_alu.get(1), perfModel->EX_stage_alu.get(9), perfModel->EX_substage_alu.get(3)});
perfModel->LD_substage_alu.set(n_LD_substage_alu);
// ALU
uint64_t n_ALU;
n_ALU = n_LD_substage_alu + 1;
perfModel->regModel.setXd(n_ALU);
// EX_stage_alu
uint64_t n_EX_stage_alu;
n_EX_stage_alu = std::max({n_ALU, perfModel->EX_stage_alu.get(1), perfModel->EX_substage_alu.get(1)});
perfModel->EX_stage_alu.set(n_EX_stage_alu);
perfModel->EX_substage_alu.set(n_EX_stage_alu);
// OoO_stage
uint64_t n_OoO_stage;
n_OoO_stage = std::max({n_EX_stage_alu, perfModel->OoO_stage.get(1), perfModel->COM_stage.get(8)});
perfModel->OoO_stage.set(n_OoO_stage);
// Commit
uint64_t n_Commit;
n_Commit = n_OoO_stage + 2;
// COM_stage
uint64_t n_COM_stage;
n_COM_stage = std::max({n_Commit, perfModel->COM_stage.get(1)});
perfModel->COM_stage.set(n_COM_stage);

  // Dump Entrance point for info print (tracing)
  perfModel->entrancePoint = n_Enter;
  }
);

static SchedulingFunction *schedulingFunction_andi = new SchedulingFunction(
  RV32_4ISSUE_SchedulingFunctionSet,
  "andi",
  13,
  [](PerformanceModel* perfModel_){
  RV32_4ISSUE_PerformanceModel* perfModel = static_cast<RV32_4ISSUE_PerformanceModel*>(perfModel_);
  // Enter
uint64_t n_Enter;
n_Enter = std::max({perfModel->IF_stage.get(16), perfModel->PC_substage.get(4)});
// PCGen
uint64_t n_PCGen;
n_PCGen = n_Enter + 1;
// uA_PcCorrect
uint64_t n_uA_PcCorrect;
n_uA_PcCorrect = std::max({n_Enter, perfModel->dynBranchPredModel.getPc_mp()});
// uA_CacheBlock
uint64_t n_uA_CacheBlock;
n_uA_CacheBlock = std::max({n_Enter, perfModel->iCacheModel.getIc_out()});
// PC_substage
uint64_t n_PC_substage;
n_PC_substage = std::max({n_PCGen, n_uA_PcCorrect, n_uA_CacheBlock, perfModel->PC_substage.get(1), perfModel->IF_substage_0.get(4)});
perfModel->PC_substage.set(n_PC_substage);
// ICacheCtrl
uint64_t n_ICacheCtrl;
n_ICacheCtrl = n_PC_substage + 1;
// IF_substage_0
uint64_t n_IF_substage_0;
n_IF_substage_0 = std::max({n_ICacheCtrl, perfModel->IF_substage_0.get(1), perfModel->IF_substage_1.get(4)});
perfModel->IF_substage_0.set(n_IF_substage_0);
// ICache
uint64_t n_ICache;
n_ICache = n_IF_substage_0 + perfModel->iCacheModel.getDelay();
perfModel->iCacheModel.setIc_in(n_ICache);
// uA_PcPredict
uint64_t n_uA_PcPredict;
n_uA_PcPredict = std::max({n_IF_substage_0, perfModel->dynBranchPredModel.getPc_pt()});
// IF_substage_1
uint64_t n_IF_substage_1;
n_IF_substage_1 = std::max({n_ICache, n_uA_PcPredict, perfModel->IF_substage_1.get(1), perfModel->IF_substage_2.get(4)});
perfModel->IF_substage_1.set(n_IF_substage_1);
// IScan
uint64_t n_IScan;
n_IScan = n_IF_substage_1 + 1;
// IF_stage
uint64_t n_IF_stage;
n_IF_stage = std::max({n_IScan, perfModel->IF_stage.get(1), perfModel->IF_substage_2.get(1), perfModel->DEC_stage.get(4)});
perfModel->IF_stage.set(n_IF_stage);
perfModel->IF_substage_2.set(n_IF_stage);
// Decoder
uint64_t n_Decoder;
n_Decoder = n_IF_stage + 1;
// DEC_stage
uint64_t n_DEC_stage;
n_DEC_stage = std::max({n_Decoder, perfModel->DEC_stage.get(1), perfModel->RN_stage.get(5)});
perfModel->DEC_stage.set(n_DEC_stage);
// Rename
uint64_t n_Rename;
n_Rename = n_DEC_stage + 1;
// RN_stage
uint64_t n_RN_stage;
n_RN_stage = std::max({n_Rename, perfModel->RN_stage.get(1), perfModel->OoO_stage.get(64), perfModel->IS_substage_alu.get(24)});
perfModel->RN_stage.set(n_RN_stage);
// Issue
uint64_t n_Issue;
n_Issue = n_RN_stage + 2;
// IS_substage_alu
uint64_t n_IS_substage_alu;
n_IS_substage_alu = std::max({n_Issue, perfModel->IS_substage_alu.get(1), perfModel->LD_substage_alu.get(3)});
perfModel->IS_substage_alu.set(n_IS_substage_alu);
// OperandLookup
uint64_t n_OperandLookup;
n_OperandLookup = n_IS_substage_alu + 1;
// uA_OF_A_alu
uint64_t n_uA_OF_A_alu;
n_uA_OF_A_alu = std::max({n_IS_substage_alu, perfModel->regModel.getXa()});
// LD_substage_alu
uint64_t n_LD_substage_alu;
n_LD_substage_alu = std::max({n_OperandLookup, n_uA_OF_A_alu, perfModel->LD_substage_alu.get(1), perfModel->EX_stage_alu.get(9), perfModel->EX_substage_alu.get(3)});
perfModel->LD_substage_alu.set(n_LD_substage_alu);
// ALU
uint64_t n_ALU;
n_ALU = n_LD_substage_alu + 1;
perfModel->regModel.setXd(n_ALU);
// EX_stage_alu
uint64_t n_EX_stage_alu;
n_EX_stage_alu = std::max({n_ALU, perfModel->EX_stage_alu.get(1), perfModel->EX_substage_alu.get(1)});
perfModel->EX_stage_alu.set(n_EX_stage_alu);
perfModel->EX_substage_alu.set(n_EX_stage_alu);
// OoO_stage
uint64_t n_OoO_stage;
n_OoO_stage = std::max({n_EX_stage_alu, perfModel->OoO_stage.get(1), perfModel->COM_stage.get(8)});
perfModel->OoO_stage.set(n_OoO_stage);
// Commit
uint64_t n_Commit;
n_Commit = n_OoO_stage + 2;
// COM_stage
uint64_t n_COM_stage;
n_COM_stage = std::max({n_Commit, perfModel->COM_stage.get(1)});
perfModel->COM_stage.set(n_COM_stage);

  // Dump Entrance point for info print (tracing)
  perfModel->entrancePoint = n_Enter;
  }
);

static SchedulingFunction *schedulingFunction_slti = new SchedulingFunction(
  RV32_4ISSUE_SchedulingFunctionSet,
  "slti",
  14,
  [](PerformanceModel* perfModel_){
  RV32_4ISSUE_PerformanceModel* perfModel = static_cast<RV32_4ISSUE_PerformanceModel*>(perfModel_);
  // Enter
uint64_t n_Enter;
n_Enter = std::max({perfModel->IF_stage.get(16), perfModel->PC_substage.get(4)});
// PCGen
uint64_t n_PCGen;
n_PCGen = n_Enter + 1;
// uA_PcCorrect
uint64_t n_uA_PcCorrect;
n_uA_PcCorrect = std::max({n_Enter, perfModel->dynBranchPredModel.getPc_mp()});
// uA_CacheBlock
uint64_t n_uA_CacheBlock;
n_uA_CacheBlock = std::max({n_Enter, perfModel->iCacheModel.getIc_out()});
// PC_substage
uint64_t n_PC_substage;
n_PC_substage = std::max({n_PCGen, n_uA_PcCorrect, n_uA_CacheBlock, perfModel->PC_substage.get(1), perfModel->IF_substage_0.get(4)});
perfModel->PC_substage.set(n_PC_substage);
// ICacheCtrl
uint64_t n_ICacheCtrl;
n_ICacheCtrl = n_PC_substage + 1;
// IF_substage_0
uint64_t n_IF_substage_0;
n_IF_substage_0 = std::max({n_ICacheCtrl, perfModel->IF_substage_0.get(1), perfModel->IF_substage_1.get(4)});
perfModel->IF_substage_0.set(n_IF_substage_0);
// ICache
uint64_t n_ICache;
n_ICache = n_IF_substage_0 + perfModel->iCacheModel.getDelay();
perfModel->iCacheModel.setIc_in(n_ICache);
// uA_PcPredict
uint64_t n_uA_PcPredict;
n_uA_PcPredict = std::max({n_IF_substage_0, perfModel->dynBranchPredModel.getPc_pt()});
// IF_substage_1
uint64_t n_IF_substage_1;
n_IF_substage_1 = std::max({n_ICache, n_uA_PcPredict, perfModel->IF_substage_1.get(1), perfModel->IF_substage_2.get(4)});
perfModel->IF_substage_1.set(n_IF_substage_1);
// IScan
uint64_t n_IScan;
n_IScan = n_IF_substage_1 + 1;
// IF_stage
uint64_t n_IF_stage;
n_IF_stage = std::max({n_IScan, perfModel->IF_stage.get(1), perfModel->IF_substage_2.get(1), perfModel->DEC_stage.get(4)});
perfModel->IF_stage.set(n_IF_stage);
perfModel->IF_substage_2.set(n_IF_stage);
// Decoder
uint64_t n_Decoder;
n_Decoder = n_IF_stage + 1;
// DEC_stage
uint64_t n_DEC_stage;
n_DEC_stage = std::max({n_Decoder, perfModel->DEC_stage.get(1), perfModel->RN_stage.get(5)});
perfModel->DEC_stage.set(n_DEC_stage);
// Rename
uint64_t n_Rename;
n_Rename = n_DEC_stage + 1;
// RN_stage
uint64_t n_RN_stage;
n_RN_stage = std::max({n_Rename, perfModel->RN_stage.get(1), perfModel->OoO_stage.get(64), perfModel->IS_substage_alu.get(24)});
perfModel->RN_stage.set(n_RN_stage);
// Issue
uint64_t n_Issue;
n_Issue = n_RN_stage + 2;
// IS_substage_alu
uint64_t n_IS_substage_alu;
n_IS_substage_alu = std::max({n_Issue, perfModel->IS_substage_alu.get(1), perfModel->LD_substage_alu.get(3)});
perfModel->IS_substage_alu.set(n_IS_substage_alu);
// OperandLookup
uint64_t n_OperandLookup;
n_OperandLookup = n_IS_substage_alu + 1;
// uA_OF_A_alu
uint64_t n_uA_OF_A_alu;
n_uA_OF_A_alu = std::max({n_IS_substage_alu, perfModel->regModel.getXa()});
// LD_substage_alu
uint64_t n_LD_substage_alu;
n_LD_substage_alu = std::max({n_OperandLookup, n_uA_OF_A_alu, perfModel->LD_substage_alu.get(1), perfModel->EX_stage_alu.get(9), perfModel->EX_substage_alu.get(3)});
perfModel->LD_substage_alu.set(n_LD_substage_alu);
// ALU
uint64_t n_ALU;
n_ALU = n_LD_substage_alu + 1;
perfModel->regModel.setXd(n_ALU);
// EX_stage_alu
uint64_t n_EX_stage_alu;
n_EX_stage_alu = std::max({n_ALU, perfModel->EX_stage_alu.get(1), perfModel->EX_substage_alu.get(1)});
perfModel->EX_stage_alu.set(n_EX_stage_alu);
perfModel->EX_substage_alu.set(n_EX_stage_alu);
// OoO_stage
uint64_t n_OoO_stage;
n_OoO_stage = std::max({n_EX_stage_alu, perfModel->OoO_stage.get(1), perfModel->COM_stage.get(8)});
perfModel->OoO_stage.set(n_OoO_stage);
// Commit
uint64_t n_Commit;
n_Commit = n_OoO_stage + 2;
// COM_stage
uint64_t n_COM_stage;
n_COM_stage = std::max({n_Commit, perfModel->COM_stage.get(1)});
perfModel->COM_stage.set(n_COM_stage);

  // Dump Entrance point for info print (tracing)
  perfModel->entrancePoint = n_Enter;
  }
);

static SchedulingFunction *schedulingFunction_sltiu = new SchedulingFunction(
  RV32_4ISSUE_SchedulingFunctionSet,
  "sltiu",
  15,
  [](PerformanceModel* perfModel_){
  RV32_4ISSUE_PerformanceModel* perfModel = static_cast<RV32_4ISSUE_PerformanceModel*>(perfModel_);
  // Enter
uint64_t n_Enter;
n_Enter = std::max({perfModel->IF_stage.get(16), perfModel->PC_substage.get(4)});
// PCGen
uint64_t n_PCGen;
n_PCGen = n_Enter + 1;
// uA_PcCorrect
uint64_t n_uA_PcCorrect;
n_uA_PcCorrect = std::max({n_Enter, perfModel->dynBranchPredModel.getPc_mp()});
// uA_CacheBlock
uint64_t n_uA_CacheBlock;
n_uA_CacheBlock = std::max({n_Enter, perfModel->iCacheModel.getIc_out()});
// PC_substage
uint64_t n_PC_substage;
n_PC_substage = std::max({n_PCGen, n_uA_PcCorrect, n_uA_CacheBlock, perfModel->PC_substage.get(1), perfModel->IF_substage_0.get(4)});
perfModel->PC_substage.set(n_PC_substage);
// ICacheCtrl
uint64_t n_ICacheCtrl;
n_ICacheCtrl = n_PC_substage + 1;
// IF_substage_0
uint64_t n_IF_substage_0;
n_IF_substage_0 = std::max({n_ICacheCtrl, perfModel->IF_substage_0.get(1), perfModel->IF_substage_1.get(4)});
perfModel->IF_substage_0.set(n_IF_substage_0);
// ICache
uint64_t n_ICache;
n_ICache = n_IF_substage_0 + perfModel->iCacheModel.getDelay();
perfModel->iCacheModel.setIc_in(n_ICache);
// uA_PcPredict
uint64_t n_uA_PcPredict;
n_uA_PcPredict = std::max({n_IF_substage_0, perfModel->dynBranchPredModel.getPc_pt()});
// IF_substage_1
uint64_t n_IF_substage_1;
n_IF_substage_1 = std::max({n_ICache, n_uA_PcPredict, perfModel->IF_substage_1.get(1), perfModel->IF_substage_2.get(4)});
perfModel->IF_substage_1.set(n_IF_substage_1);
// IScan
uint64_t n_IScan;
n_IScan = n_IF_substage_1 + 1;
// IF_stage
uint64_t n_IF_stage;
n_IF_stage = std::max({n_IScan, perfModel->IF_stage.get(1), perfModel->IF_substage_2.get(1), perfModel->DEC_stage.get(4)});
perfModel->IF_stage.set(n_IF_stage);
perfModel->IF_substage_2.set(n_IF_stage);
// Decoder
uint64_t n_Decoder;
n_Decoder = n_IF_stage + 1;
// DEC_stage
uint64_t n_DEC_stage;
n_DEC_stage = std::max({n_Decoder, perfModel->DEC_stage.get(1), perfModel->RN_stage.get(5)});
perfModel->DEC_stage.set(n_DEC_stage);
// Rename
uint64_t n_Rename;
n_Rename = n_DEC_stage + 1;
// RN_stage
uint64_t n_RN_stage;
n_RN_stage = std::max({n_Rename, perfModel->RN_stage.get(1), perfModel->OoO_stage.get(64), perfModel->IS_substage_alu.get(24)});
perfModel->RN_stage.set(n_RN_stage);
// Issue
uint64_t n_Issue;
n_Issue = n_RN_stage + 2;
// IS_substage_alu
uint64_t n_IS_substage_alu;
n_IS_substage_alu = std::max({n_Issue, perfModel->IS_substage_alu.get(1), perfModel->LD_substage_alu.get(3)});
perfModel->IS_substage_alu.set(n_IS_substage_alu);
// OperandLookup
uint64_t n_OperandLookup;
n_OperandLookup = n_IS_substage_alu + 1;
// uA_OF_A_alu
uint64_t n_uA_OF_A_alu;
n_uA_OF_A_alu = std::max({n_IS_substage_alu, perfModel->regModel.getXa()});
// LD_substage_alu
uint64_t n_LD_substage_alu;
n_LD_substage_alu = std::max({n_OperandLookup, n_uA_OF_A_alu, perfModel->LD_substage_alu.get(1), perfModel->EX_stage_alu.get(9), perfModel->EX_substage_alu.get(3)});
perfModel->LD_substage_alu.set(n_LD_substage_alu);
// ALU
uint64_t n_ALU;
n_ALU = n_LD_substage_alu + 1;
perfModel->regModel.setXd(n_ALU);
// EX_stage_alu
uint64_t n_EX_stage_alu;
n_EX_stage_alu = std::max({n_ALU, perfModel->EX_stage_alu.get(1), perfModel->EX_substage_alu.get(1)});
perfModel->EX_stage_alu.set(n_EX_stage_alu);
perfModel->EX_substage_alu.set(n_EX_stage_alu);
// OoO_stage
uint64_t n_OoO_stage;
n_OoO_stage = std::max({n_EX_stage_alu, perfModel->OoO_stage.get(1), perfModel->COM_stage.get(8)});
perfModel->OoO_stage.set(n_OoO_stage);
// Commit
uint64_t n_Commit;
n_Commit = n_OoO_stage + 2;
// COM_stage
uint64_t n_COM_stage;
n_COM_stage = std::max({n_Commit, perfModel->COM_stage.get(1)});
perfModel->COM_stage.set(n_COM_stage);

  // Dump Entrance point for info print (tracing)
  perfModel->entrancePoint = n_Enter;
  }
);

static SchedulingFunction *schedulingFunction_slli = new SchedulingFunction(
  RV32_4ISSUE_SchedulingFunctionSet,
  "slli",
  16,
  [](PerformanceModel* perfModel_){
  RV32_4ISSUE_PerformanceModel* perfModel = static_cast<RV32_4ISSUE_PerformanceModel*>(perfModel_);
  // Enter
uint64_t n_Enter;
n_Enter = std::max({perfModel->IF_stage.get(16), perfModel->PC_substage.get(4)});
// PCGen
uint64_t n_PCGen;
n_PCGen = n_Enter + 1;
// uA_PcCorrect
uint64_t n_uA_PcCorrect;
n_uA_PcCorrect = std::max({n_Enter, perfModel->dynBranchPredModel.getPc_mp()});
// uA_CacheBlock
uint64_t n_uA_CacheBlock;
n_uA_CacheBlock = std::max({n_Enter, perfModel->iCacheModel.getIc_out()});
// PC_substage
uint64_t n_PC_substage;
n_PC_substage = std::max({n_PCGen, n_uA_PcCorrect, n_uA_CacheBlock, perfModel->PC_substage.get(1), perfModel->IF_substage_0.get(4)});
perfModel->PC_substage.set(n_PC_substage);
// ICacheCtrl
uint64_t n_ICacheCtrl;
n_ICacheCtrl = n_PC_substage + 1;
// IF_substage_0
uint64_t n_IF_substage_0;
n_IF_substage_0 = std::max({n_ICacheCtrl, perfModel->IF_substage_0.get(1), perfModel->IF_substage_1.get(4)});
perfModel->IF_substage_0.set(n_IF_substage_0);
// ICache
uint64_t n_ICache;
n_ICache = n_IF_substage_0 + perfModel->iCacheModel.getDelay();
perfModel->iCacheModel.setIc_in(n_ICache);
// uA_PcPredict
uint64_t n_uA_PcPredict;
n_uA_PcPredict = std::max({n_IF_substage_0, perfModel->dynBranchPredModel.getPc_pt()});
// IF_substage_1
uint64_t n_IF_substage_1;
n_IF_substage_1 = std::max({n_ICache, n_uA_PcPredict, perfModel->IF_substage_1.get(1), perfModel->IF_substage_2.get(4)});
perfModel->IF_substage_1.set(n_IF_substage_1);
// IScan
uint64_t n_IScan;
n_IScan = n_IF_substage_1 + 1;
// IF_stage
uint64_t n_IF_stage;
n_IF_stage = std::max({n_IScan, perfModel->IF_stage.get(1), perfModel->IF_substage_2.get(1), perfModel->DEC_stage.get(4)});
perfModel->IF_stage.set(n_IF_stage);
perfModel->IF_substage_2.set(n_IF_stage);
// Decoder
uint64_t n_Decoder;
n_Decoder = n_IF_stage + 1;
// DEC_stage
uint64_t n_DEC_stage;
n_DEC_stage = std::max({n_Decoder, perfModel->DEC_stage.get(1), perfModel->RN_stage.get(5)});
perfModel->DEC_stage.set(n_DEC_stage);
// Rename
uint64_t n_Rename;
n_Rename = n_DEC_stage + 1;
// RN_stage
uint64_t n_RN_stage;
n_RN_stage = std::max({n_Rename, perfModel->RN_stage.get(1), perfModel->OoO_stage.get(64), perfModel->IS_substage_alu.get(24)});
perfModel->RN_stage.set(n_RN_stage);
// Issue
uint64_t n_Issue;
n_Issue = n_RN_stage + 2;
// IS_substage_alu
uint64_t n_IS_substage_alu;
n_IS_substage_alu = std::max({n_Issue, perfModel->IS_substage_alu.get(1), perfModel->LD_substage_alu.get(3)});
perfModel->IS_substage_alu.set(n_IS_substage_alu);
// OperandLookup
uint64_t n_OperandLookup;
n_OperandLookup = n_IS_substage_alu + 1;
// uA_OF_A_alu
uint64_t n_uA_OF_A_alu;
n_uA_OF_A_alu = std::max({n_IS_substage_alu, perfModel->regModel.getXa()});
// LD_substage_alu
uint64_t n_LD_substage_alu;
n_LD_substage_alu = std::max({n_OperandLookup, n_uA_OF_A_alu, perfModel->LD_substage_alu.get(1), perfModel->EX_stage_alu.get(9), perfModel->EX_substage_alu.get(3)});
perfModel->LD_substage_alu.set(n_LD_substage_alu);
// ALU
uint64_t n_ALU;
n_ALU = n_LD_substage_alu + 1;
perfModel->regModel.setXd(n_ALU);
// EX_stage_alu
uint64_t n_EX_stage_alu;
n_EX_stage_alu = std::max({n_ALU, perfModel->EX_stage_alu.get(1), perfModel->EX_substage_alu.get(1)});
perfModel->EX_stage_alu.set(n_EX_stage_alu);
perfModel->EX_substage_alu.set(n_EX_stage_alu);
// OoO_stage
uint64_t n_OoO_stage;
n_OoO_stage = std::max({n_EX_stage_alu, perfModel->OoO_stage.get(1), perfModel->COM_stage.get(8)});
perfModel->OoO_stage.set(n_OoO_stage);
// Commit
uint64_t n_Commit;
n_Commit = n_OoO_stage + 2;
// COM_stage
uint64_t n_COM_stage;
n_COM_stage = std::max({n_Commit, perfModel->COM_stage.get(1)});
perfModel->COM_stage.set(n_COM_stage);

  // Dump Entrance point for info print (tracing)
  perfModel->entrancePoint = n_Enter;
  }
);

static SchedulingFunction *schedulingFunction_srli = new SchedulingFunction(
  RV32_4ISSUE_SchedulingFunctionSet,
  "srli",
  17,
  [](PerformanceModel* perfModel_){
  RV32_4ISSUE_PerformanceModel* perfModel = static_cast<RV32_4ISSUE_PerformanceModel*>(perfModel_);
  // Enter
uint64_t n_Enter;
n_Enter = std::max({perfModel->IF_stage.get(16), perfModel->PC_substage.get(4)});
// PCGen
uint64_t n_PCGen;
n_PCGen = n_Enter + 1;
// uA_PcCorrect
uint64_t n_uA_PcCorrect;
n_uA_PcCorrect = std::max({n_Enter, perfModel->dynBranchPredModel.getPc_mp()});
// uA_CacheBlock
uint64_t n_uA_CacheBlock;
n_uA_CacheBlock = std::max({n_Enter, perfModel->iCacheModel.getIc_out()});
// PC_substage
uint64_t n_PC_substage;
n_PC_substage = std::max({n_PCGen, n_uA_PcCorrect, n_uA_CacheBlock, perfModel->PC_substage.get(1), perfModel->IF_substage_0.get(4)});
perfModel->PC_substage.set(n_PC_substage);
// ICacheCtrl
uint64_t n_ICacheCtrl;
n_ICacheCtrl = n_PC_substage + 1;
// IF_substage_0
uint64_t n_IF_substage_0;
n_IF_substage_0 = std::max({n_ICacheCtrl, perfModel->IF_substage_0.get(1), perfModel->IF_substage_1.get(4)});
perfModel->IF_substage_0.set(n_IF_substage_0);
// ICache
uint64_t n_ICache;
n_ICache = n_IF_substage_0 + perfModel->iCacheModel.getDelay();
perfModel->iCacheModel.setIc_in(n_ICache);
// uA_PcPredict
uint64_t n_uA_PcPredict;
n_uA_PcPredict = std::max({n_IF_substage_0, perfModel->dynBranchPredModel.getPc_pt()});
// IF_substage_1
uint64_t n_IF_substage_1;
n_IF_substage_1 = std::max({n_ICache, n_uA_PcPredict, perfModel->IF_substage_1.get(1), perfModel->IF_substage_2.get(4)});
perfModel->IF_substage_1.set(n_IF_substage_1);
// IScan
uint64_t n_IScan;
n_IScan = n_IF_substage_1 + 1;
// IF_stage
uint64_t n_IF_stage;
n_IF_stage = std::max({n_IScan, perfModel->IF_stage.get(1), perfModel->IF_substage_2.get(1), perfModel->DEC_stage.get(4)});
perfModel->IF_stage.set(n_IF_stage);
perfModel->IF_substage_2.set(n_IF_stage);
// Decoder
uint64_t n_Decoder;
n_Decoder = n_IF_stage + 1;
// DEC_stage
uint64_t n_DEC_stage;
n_DEC_stage = std::max({n_Decoder, perfModel->DEC_stage.get(1), perfModel->RN_stage.get(5)});
perfModel->DEC_stage.set(n_DEC_stage);
// Rename
uint64_t n_Rename;
n_Rename = n_DEC_stage + 1;
// RN_stage
uint64_t n_RN_stage;
n_RN_stage = std::max({n_Rename, perfModel->RN_stage.get(1), perfModel->OoO_stage.get(64), perfModel->IS_substage_alu.get(24)});
perfModel->RN_stage.set(n_RN_stage);
// Issue
uint64_t n_Issue;
n_Issue = n_RN_stage + 2;
// IS_substage_alu
uint64_t n_IS_substage_alu;
n_IS_substage_alu = std::max({n_Issue, perfModel->IS_substage_alu.get(1), perfModel->LD_substage_alu.get(3)});
perfModel->IS_substage_alu.set(n_IS_substage_alu);
// OperandLookup
uint64_t n_OperandLookup;
n_OperandLookup = n_IS_substage_alu + 1;
// uA_OF_A_alu
uint64_t n_uA_OF_A_alu;
n_uA_OF_A_alu = std::max({n_IS_substage_alu, perfModel->regModel.getXa()});
// LD_substage_alu
uint64_t n_LD_substage_alu;
n_LD_substage_alu = std::max({n_OperandLookup, n_uA_OF_A_alu, perfModel->LD_substage_alu.get(1), perfModel->EX_stage_alu.get(9), perfModel->EX_substage_alu.get(3)});
perfModel->LD_substage_alu.set(n_LD_substage_alu);
// ALU
uint64_t n_ALU;
n_ALU = n_LD_substage_alu + 1;
perfModel->regModel.setXd(n_ALU);
// EX_stage_alu
uint64_t n_EX_stage_alu;
n_EX_stage_alu = std::max({n_ALU, perfModel->EX_stage_alu.get(1), perfModel->EX_substage_alu.get(1)});
perfModel->EX_stage_alu.set(n_EX_stage_alu);
perfModel->EX_substage_alu.set(n_EX_stage_alu);
// OoO_stage
uint64_t n_OoO_stage;
n_OoO_stage = std::max({n_EX_stage_alu, perfModel->OoO_stage.get(1), perfModel->COM_stage.get(8)});
perfModel->OoO_stage.set(n_OoO_stage);
// Commit
uint64_t n_Commit;
n_Commit = n_OoO_stage + 2;
// COM_stage
uint64_t n_COM_stage;
n_COM_stage = std::max({n_Commit, perfModel->COM_stage.get(1)});
perfModel->COM_stage.set(n_COM_stage);

  // Dump Entrance point for info print (tracing)
  perfModel->entrancePoint = n_Enter;
  }
);

static SchedulingFunction *schedulingFunction_srai = new SchedulingFunction(
  RV32_4ISSUE_SchedulingFunctionSet,
  "srai",
  18,
  [](PerformanceModel* perfModel_){
  RV32_4ISSUE_PerformanceModel* perfModel = static_cast<RV32_4ISSUE_PerformanceModel*>(perfModel_);
  // Enter
uint64_t n_Enter;
n_Enter = std::max({perfModel->IF_stage.get(16), perfModel->PC_substage.get(4)});
// PCGen
uint64_t n_PCGen;
n_PCGen = n_Enter + 1;
// uA_PcCorrect
uint64_t n_uA_PcCorrect;
n_uA_PcCorrect = std::max({n_Enter, perfModel->dynBranchPredModel.getPc_mp()});
// uA_CacheBlock
uint64_t n_uA_CacheBlock;
n_uA_CacheBlock = std::max({n_Enter, perfModel->iCacheModel.getIc_out()});
// PC_substage
uint64_t n_PC_substage;
n_PC_substage = std::max({n_PCGen, n_uA_PcCorrect, n_uA_CacheBlock, perfModel->PC_substage.get(1), perfModel->IF_substage_0.get(4)});
perfModel->PC_substage.set(n_PC_substage);
// ICacheCtrl
uint64_t n_ICacheCtrl;
n_ICacheCtrl = n_PC_substage + 1;
// IF_substage_0
uint64_t n_IF_substage_0;
n_IF_substage_0 = std::max({n_ICacheCtrl, perfModel->IF_substage_0.get(1), perfModel->IF_substage_1.get(4)});
perfModel->IF_substage_0.set(n_IF_substage_0);
// ICache
uint64_t n_ICache;
n_ICache = n_IF_substage_0 + perfModel->iCacheModel.getDelay();
perfModel->iCacheModel.setIc_in(n_ICache);
// uA_PcPredict
uint64_t n_uA_PcPredict;
n_uA_PcPredict = std::max({n_IF_substage_0, perfModel->dynBranchPredModel.getPc_pt()});
// IF_substage_1
uint64_t n_IF_substage_1;
n_IF_substage_1 = std::max({n_ICache, n_uA_PcPredict, perfModel->IF_substage_1.get(1), perfModel->IF_substage_2.get(4)});
perfModel->IF_substage_1.set(n_IF_substage_1);
// IScan
uint64_t n_IScan;
n_IScan = n_IF_substage_1 + 1;
// IF_stage
uint64_t n_IF_stage;
n_IF_stage = std::max({n_IScan, perfModel->IF_stage.get(1), perfModel->IF_substage_2.get(1), perfModel->DEC_stage.get(4)});
perfModel->IF_stage.set(n_IF_stage);
perfModel->IF_substage_2.set(n_IF_stage);
// Decoder
uint64_t n_Decoder;
n_Decoder = n_IF_stage + 1;
// DEC_stage
uint64_t n_DEC_stage;
n_DEC_stage = std::max({n_Decoder, perfModel->DEC_stage.get(1), perfModel->RN_stage.get(5)});
perfModel->DEC_stage.set(n_DEC_stage);
// Rename
uint64_t n_Rename;
n_Rename = n_DEC_stage + 1;
// RN_stage
uint64_t n_RN_stage;
n_RN_stage = std::max({n_Rename, perfModel->RN_stage.get(1), perfModel->OoO_stage.get(64), perfModel->IS_substage_alu.get(24)});
perfModel->RN_stage.set(n_RN_stage);
// Issue
uint64_t n_Issue;
n_Issue = n_RN_stage + 2;
// IS_substage_alu
uint64_t n_IS_substage_alu;
n_IS_substage_alu = std::max({n_Issue, perfModel->IS_substage_alu.get(1), perfModel->LD_substage_alu.get(3)});
perfModel->IS_substage_alu.set(n_IS_substage_alu);
// OperandLookup
uint64_t n_OperandLookup;
n_OperandLookup = n_IS_substage_alu + 1;
// uA_OF_A_alu
uint64_t n_uA_OF_A_alu;
n_uA_OF_A_alu = std::max({n_IS_substage_alu, perfModel->regModel.getXa()});
// LD_substage_alu
uint64_t n_LD_substage_alu;
n_LD_substage_alu = std::max({n_OperandLookup, n_uA_OF_A_alu, perfModel->LD_substage_alu.get(1), perfModel->EX_stage_alu.get(9), perfModel->EX_substage_alu.get(3)});
perfModel->LD_substage_alu.set(n_LD_substage_alu);
// ALU
uint64_t n_ALU;
n_ALU = n_LD_substage_alu + 1;
perfModel->regModel.setXd(n_ALU);
// EX_stage_alu
uint64_t n_EX_stage_alu;
n_EX_stage_alu = std::max({n_ALU, perfModel->EX_stage_alu.get(1), perfModel->EX_substage_alu.get(1)});
perfModel->EX_stage_alu.set(n_EX_stage_alu);
perfModel->EX_substage_alu.set(n_EX_stage_alu);
// OoO_stage
uint64_t n_OoO_stage;
n_OoO_stage = std::max({n_EX_stage_alu, perfModel->OoO_stage.get(1), perfModel->COM_stage.get(8)});
perfModel->OoO_stage.set(n_OoO_stage);
// Commit
uint64_t n_Commit;
n_Commit = n_OoO_stage + 2;
// COM_stage
uint64_t n_COM_stage;
n_COM_stage = std::max({n_Commit, perfModel->COM_stage.get(1)});
perfModel->COM_stage.set(n_COM_stage);

  // Dump Entrance point for info print (tracing)
  perfModel->entrancePoint = n_Enter;
  }
);

static SchedulingFunction *schedulingFunction_auipc = new SchedulingFunction(
  RV32_4ISSUE_SchedulingFunctionSet,
  "auipc",
  19,
  [](PerformanceModel* perfModel_){
  RV32_4ISSUE_PerformanceModel* perfModel = static_cast<RV32_4ISSUE_PerformanceModel*>(perfModel_);
  // Enter
uint64_t n_Enter;
n_Enter = std::max({perfModel->IF_stage.get(16), perfModel->PC_substage.get(4)});
// PCGen
uint64_t n_PCGen;
n_PCGen = n_Enter + 1;
// uA_PcCorrect
uint64_t n_uA_PcCorrect;
n_uA_PcCorrect = std::max({n_Enter, perfModel->dynBranchPredModel.getPc_mp()});
// uA_CacheBlock
uint64_t n_uA_CacheBlock;
n_uA_CacheBlock = std::max({n_Enter, perfModel->iCacheModel.getIc_out()});
// PC_substage
uint64_t n_PC_substage;
n_PC_substage = std::max({n_PCGen, n_uA_PcCorrect, n_uA_CacheBlock, perfModel->PC_substage.get(1), perfModel->IF_substage_0.get(4)});
perfModel->PC_substage.set(n_PC_substage);
// ICacheCtrl
uint64_t n_ICacheCtrl;
n_ICacheCtrl = n_PC_substage + 1;
// IF_substage_0
uint64_t n_IF_substage_0;
n_IF_substage_0 = std::max({n_ICacheCtrl, perfModel->IF_substage_0.get(1), perfModel->IF_substage_1.get(4)});
perfModel->IF_substage_0.set(n_IF_substage_0);
// ICache
uint64_t n_ICache;
n_ICache = n_IF_substage_0 + perfModel->iCacheModel.getDelay();
perfModel->iCacheModel.setIc_in(n_ICache);
// uA_PcPredict
uint64_t n_uA_PcPredict;
n_uA_PcPredict = std::max({n_IF_substage_0, perfModel->dynBranchPredModel.getPc_pt()});
// IF_substage_1
uint64_t n_IF_substage_1;
n_IF_substage_1 = std::max({n_ICache, n_uA_PcPredict, perfModel->IF_substage_1.get(1), perfModel->IF_substage_2.get(4)});
perfModel->IF_substage_1.set(n_IF_substage_1);
// IScan
uint64_t n_IScan;
n_IScan = n_IF_substage_1 + 1;
// IF_stage
uint64_t n_IF_stage;
n_IF_stage = std::max({n_IScan, perfModel->IF_stage.get(1), perfModel->IF_substage_2.get(1), perfModel->DEC_stage.get(4)});
perfModel->IF_stage.set(n_IF_stage);
perfModel->IF_substage_2.set(n_IF_stage);
// Decoder
uint64_t n_Decoder;
n_Decoder = n_IF_stage + 1;
// DEC_stage
uint64_t n_DEC_stage;
n_DEC_stage = std::max({n_Decoder, perfModel->DEC_stage.get(1), perfModel->RN_stage.get(5)});
perfModel->DEC_stage.set(n_DEC_stage);
// Rename
uint64_t n_Rename;
n_Rename = n_DEC_stage + 1;
// RN_stage
uint64_t n_RN_stage;
n_RN_stage = std::max({n_Rename, perfModel->RN_stage.get(1), perfModel->OoO_stage.get(64), perfModel->IS_substage_alu.get(24)});
perfModel->RN_stage.set(n_RN_stage);
// Issue
uint64_t n_Issue;
n_Issue = n_RN_stage + 2;
// IS_substage_alu
uint64_t n_IS_substage_alu;
n_IS_substage_alu = std::max({n_Issue, perfModel->IS_substage_alu.get(1), perfModel->LD_substage_alu.get(3)});
perfModel->IS_substage_alu.set(n_IS_substage_alu);
// OperandLookup
uint64_t n_OperandLookup;
n_OperandLookup = n_IS_substage_alu + 1;
// LD_substage_alu
uint64_t n_LD_substage_alu;
n_LD_substage_alu = std::max({n_OperandLookup, perfModel->LD_substage_alu.get(1), perfModel->EX_stage_alu.get(9), perfModel->EX_substage_alu.get(3)});
perfModel->LD_substage_alu.set(n_LD_substage_alu);
// ALU
uint64_t n_ALU;
n_ALU = n_LD_substage_alu + 1;
perfModel->regModel.setXd(n_ALU);
// EX_stage_alu
uint64_t n_EX_stage_alu;
n_EX_stage_alu = std::max({n_ALU, perfModel->EX_stage_alu.get(1), perfModel->EX_substage_alu.get(1)});
perfModel->EX_stage_alu.set(n_EX_stage_alu);
perfModel->EX_substage_alu.set(n_EX_stage_alu);
// OoO_stage
uint64_t n_OoO_stage;
n_OoO_stage = std::max({n_EX_stage_alu, perfModel->OoO_stage.get(1), perfModel->COM_stage.get(8)});
perfModel->OoO_stage.set(n_OoO_stage);
// Commit
uint64_t n_Commit;
n_Commit = n_OoO_stage + 2;
// COM_stage
uint64_t n_COM_stage;
n_COM_stage = std::max({n_Commit, perfModel->COM_stage.get(1)});
perfModel->COM_stage.set(n_COM_stage);

  // Dump Entrance point for info print (tracing)
  perfModel->entrancePoint = n_Enter;
  }
);

static SchedulingFunction *schedulingFunction_lui = new SchedulingFunction(
  RV32_4ISSUE_SchedulingFunctionSet,
  "lui",
  20,
  [](PerformanceModel* perfModel_){
  RV32_4ISSUE_PerformanceModel* perfModel = static_cast<RV32_4ISSUE_PerformanceModel*>(perfModel_);
  // Enter
uint64_t n_Enter;
n_Enter = std::max({perfModel->IF_stage.get(16), perfModel->PC_substage.get(4)});
// PCGen
uint64_t n_PCGen;
n_PCGen = n_Enter + 1;
// uA_PcCorrect
uint64_t n_uA_PcCorrect;
n_uA_PcCorrect = std::max({n_Enter, perfModel->dynBranchPredModel.getPc_mp()});
// uA_CacheBlock
uint64_t n_uA_CacheBlock;
n_uA_CacheBlock = std::max({n_Enter, perfModel->iCacheModel.getIc_out()});
// PC_substage
uint64_t n_PC_substage;
n_PC_substage = std::max({n_PCGen, n_uA_PcCorrect, n_uA_CacheBlock, perfModel->PC_substage.get(1), perfModel->IF_substage_0.get(4)});
perfModel->PC_substage.set(n_PC_substage);
// ICacheCtrl
uint64_t n_ICacheCtrl;
n_ICacheCtrl = n_PC_substage + 1;
// IF_substage_0
uint64_t n_IF_substage_0;
n_IF_substage_0 = std::max({n_ICacheCtrl, perfModel->IF_substage_0.get(1), perfModel->IF_substage_1.get(4)});
perfModel->IF_substage_0.set(n_IF_substage_0);
// ICache
uint64_t n_ICache;
n_ICache = n_IF_substage_0 + perfModel->iCacheModel.getDelay();
perfModel->iCacheModel.setIc_in(n_ICache);
// uA_PcPredict
uint64_t n_uA_PcPredict;
n_uA_PcPredict = std::max({n_IF_substage_0, perfModel->dynBranchPredModel.getPc_pt()});
// IF_substage_1
uint64_t n_IF_substage_1;
n_IF_substage_1 = std::max({n_ICache, n_uA_PcPredict, perfModel->IF_substage_1.get(1), perfModel->IF_substage_2.get(4)});
perfModel->IF_substage_1.set(n_IF_substage_1);
// IScan
uint64_t n_IScan;
n_IScan = n_IF_substage_1 + 1;
// IF_stage
uint64_t n_IF_stage;
n_IF_stage = std::max({n_IScan, perfModel->IF_stage.get(1), perfModel->IF_substage_2.get(1), perfModel->DEC_stage.get(4)});
perfModel->IF_stage.set(n_IF_stage);
perfModel->IF_substage_2.set(n_IF_stage);
// Decoder
uint64_t n_Decoder;
n_Decoder = n_IF_stage + 1;
// DEC_stage
uint64_t n_DEC_stage;
n_DEC_stage = std::max({n_Decoder, perfModel->DEC_stage.get(1), perfModel->RN_stage.get(5)});
perfModel->DEC_stage.set(n_DEC_stage);
// Rename
uint64_t n_Rename;
n_Rename = n_DEC_stage + 1;
// RN_stage
uint64_t n_RN_stage;
n_RN_stage = std::max({n_Rename, perfModel->RN_stage.get(1), perfModel->OoO_stage.get(64), perfModel->IS_substage_alu.get(24)});
perfModel->RN_stage.set(n_RN_stage);
// Issue
uint64_t n_Issue;
n_Issue = n_RN_stage + 2;
// IS_substage_alu
uint64_t n_IS_substage_alu;
n_IS_substage_alu = std::max({n_Issue, perfModel->IS_substage_alu.get(1), perfModel->LD_substage_alu.get(3)});
perfModel->IS_substage_alu.set(n_IS_substage_alu);
// OperandLookup
uint64_t n_OperandLookup;
n_OperandLookup = n_IS_substage_alu + 1;
// LD_substage_alu
uint64_t n_LD_substage_alu;
n_LD_substage_alu = std::max({n_OperandLookup, perfModel->LD_substage_alu.get(1), perfModel->EX_stage_alu.get(9), perfModel->EX_substage_alu.get(3)});
perfModel->LD_substage_alu.set(n_LD_substage_alu);
// ALU
uint64_t n_ALU;
n_ALU = n_LD_substage_alu + 1;
perfModel->regModel.setXd(n_ALU);
// EX_stage_alu
uint64_t n_EX_stage_alu;
n_EX_stage_alu = std::max({n_ALU, perfModel->EX_stage_alu.get(1), perfModel->EX_substage_alu.get(1)});
perfModel->EX_stage_alu.set(n_EX_stage_alu);
perfModel->EX_substage_alu.set(n_EX_stage_alu);
// OoO_stage
uint64_t n_OoO_stage;
n_OoO_stage = std::max({n_EX_stage_alu, perfModel->OoO_stage.get(1), perfModel->COM_stage.get(8)});
perfModel->OoO_stage.set(n_OoO_stage);
// Commit
uint64_t n_Commit;
n_Commit = n_OoO_stage + 2;
// COM_stage
uint64_t n_COM_stage;
n_COM_stage = std::max({n_Commit, perfModel->COM_stage.get(1)});
perfModel->COM_stage.set(n_COM_stage);

  // Dump Entrance point for info print (tracing)
  perfModel->entrancePoint = n_Enter;
  }
);

static SchedulingFunction *schedulingFunction_mul = new SchedulingFunction(
  RV32_4ISSUE_SchedulingFunctionSet,
  "mul",
  21,
  [](PerformanceModel* perfModel_){
  RV32_4ISSUE_PerformanceModel* perfModel = static_cast<RV32_4ISSUE_PerformanceModel*>(perfModel_);
  // Enter
uint64_t n_Enter;
n_Enter = std::max({perfModel->IF_stage.get(16), perfModel->PC_substage.get(4)});
// PCGen
uint64_t n_PCGen;
n_PCGen = n_Enter + 1;
// uA_PcCorrect
uint64_t n_uA_PcCorrect;
n_uA_PcCorrect = std::max({n_Enter, perfModel->dynBranchPredModel.getPc_mp()});
// uA_CacheBlock
uint64_t n_uA_CacheBlock;
n_uA_CacheBlock = std::max({n_Enter, perfModel->iCacheModel.getIc_out()});
// PC_substage
uint64_t n_PC_substage;
n_PC_substage = std::max({n_PCGen, n_uA_PcCorrect, n_uA_CacheBlock, perfModel->PC_substage.get(1), perfModel->IF_substage_0.get(4)});
perfModel->PC_substage.set(n_PC_substage);
// ICacheCtrl
uint64_t n_ICacheCtrl;
n_ICacheCtrl = n_PC_substage + 1;
// IF_substage_0
uint64_t n_IF_substage_0;
n_IF_substage_0 = std::max({n_ICacheCtrl, perfModel->IF_substage_0.get(1), perfModel->IF_substage_1.get(4)});
perfModel->IF_substage_0.set(n_IF_substage_0);
// ICache
uint64_t n_ICache;
n_ICache = n_IF_substage_0 + perfModel->iCacheModel.getDelay();
perfModel->iCacheModel.setIc_in(n_ICache);
// uA_PcPredict
uint64_t n_uA_PcPredict;
n_uA_PcPredict = std::max({n_IF_substage_0, perfModel->dynBranchPredModel.getPc_pt()});
// IF_substage_1
uint64_t n_IF_substage_1;
n_IF_substage_1 = std::max({n_ICache, n_uA_PcPredict, perfModel->IF_substage_1.get(1), perfModel->IF_substage_2.get(4)});
perfModel->IF_substage_1.set(n_IF_substage_1);
// IScan
uint64_t n_IScan;
n_IScan = n_IF_substage_1 + 1;
// IF_stage
uint64_t n_IF_stage;
n_IF_stage = std::max({n_IScan, perfModel->IF_stage.get(1), perfModel->IF_substage_2.get(1), perfModel->DEC_stage.get(4)});
perfModel->IF_stage.set(n_IF_stage);
perfModel->IF_substage_2.set(n_IF_stage);
// Decoder
uint64_t n_Decoder;
n_Decoder = n_IF_stage + 1;
// DEC_stage
uint64_t n_DEC_stage;
n_DEC_stage = std::max({n_Decoder, perfModel->DEC_stage.get(1), perfModel->RN_stage.get(5)});
perfModel->DEC_stage.set(n_DEC_stage);
// Rename
uint64_t n_Rename;
n_Rename = n_DEC_stage + 1;
// RN_stage
uint64_t n_RN_stage;
n_RN_stage = std::max({n_Rename, perfModel->RN_stage.get(1), perfModel->OoO_stage.get(64), perfModel->IS_substage_alu.get(24)});
perfModel->RN_stage.set(n_RN_stage);
// Issue
uint64_t n_Issue;
n_Issue = n_RN_stage + 2;
// IS_substage_alu
uint64_t n_IS_substage_alu;
n_IS_substage_alu = std::max({n_Issue, perfModel->IS_substage_alu.get(1), perfModel->LD_substage_alu.get(3)});
perfModel->IS_substage_alu.set(n_IS_substage_alu);
// OperandLookup
uint64_t n_OperandLookup;
n_OperandLookup = n_IS_substage_alu + 1;
// uA_OF_A_alu
uint64_t n_uA_OF_A_alu;
n_uA_OF_A_alu = std::max({n_IS_substage_alu, perfModel->regModel.getXa()});
// uA_OF_B_alu
uint64_t n_uA_OF_B_alu;
n_uA_OF_B_alu = std::max({n_IS_substage_alu, perfModel->regModel.getXb()});
// LD_substage_alu
uint64_t n_LD_substage_alu;
n_LD_substage_alu = std::max({n_OperandLookup, n_uA_OF_A_alu, n_uA_OF_B_alu, perfModel->LD_substage_alu.get(1), perfModel->EX_stage_alu.get(9), perfModel->EX_substage_mul_1.get(2)});
perfModel->LD_substage_alu.set(n_LD_substage_alu);
// MUL1
uint64_t n_MUL1;
n_MUL1 = n_LD_substage_alu + 1;
// EX_substage_mul_1
uint64_t n_EX_substage_mul_1;
n_EX_substage_mul_1 = std::max({n_MUL1, perfModel->EX_substage_mul_1.get(1), perfModel->EX_substage_mul_2.get(2)});
perfModel->EX_substage_mul_1.set(n_EX_substage_mul_1);
// MUL2
uint64_t n_MUL2;
n_MUL2 = n_EX_substage_mul_1 + 1;
// EX_substage_mul_2
uint64_t n_EX_substage_mul_2;
n_EX_substage_mul_2 = std::max({n_MUL2, perfModel->EX_substage_mul_2.get(1), perfModel->EX_substage_mul_3.get(2)});
perfModel->EX_substage_mul_2.set(n_EX_substage_mul_2);
// MUL3
uint64_t n_MUL3;
n_MUL3 = n_EX_substage_mul_2 + 1;
// EX_substage_mul_3
uint64_t n_EX_substage_mul_3;
n_EX_substage_mul_3 = std::max({n_MUL3, perfModel->EX_substage_mul_3.get(1), perfModel->EX_substage_mul_4.get(2)});
perfModel->EX_substage_mul_3.set(n_EX_substage_mul_3);
// MUL4
uint64_t n_MUL4;
n_MUL4 = n_EX_substage_mul_3 + 1;
perfModel->regModel.setXd(n_MUL4);
// EX_stage_alu
uint64_t n_EX_stage_alu;
n_EX_stage_alu = std::max({n_MUL4, perfModel->EX_stage_alu.get(1), perfModel->EX_substage_mul_4.get(1)});
perfModel->EX_stage_alu.set(n_EX_stage_alu);
perfModel->EX_substage_mul_4.set(n_EX_stage_alu);
// OoO_stage
uint64_t n_OoO_stage;
n_OoO_stage = std::max({n_EX_stage_alu, perfModel->OoO_stage.get(1), perfModel->COM_stage.get(8)});
perfModel->OoO_stage.set(n_OoO_stage);
// Commit
uint64_t n_Commit;
n_Commit = n_OoO_stage + 2;
// COM_stage
uint64_t n_COM_stage;
n_COM_stage = std::max({n_Commit, perfModel->COM_stage.get(1)});
perfModel->COM_stage.set(n_COM_stage);

  // Dump Entrance point for info print (tracing)
  perfModel->entrancePoint = n_Enter;
  }
);

static SchedulingFunction *schedulingFunction_mulh = new SchedulingFunction(
  RV32_4ISSUE_SchedulingFunctionSet,
  "mulh",
  22,
  [](PerformanceModel* perfModel_){
  RV32_4ISSUE_PerformanceModel* perfModel = static_cast<RV32_4ISSUE_PerformanceModel*>(perfModel_);
  // Enter
uint64_t n_Enter;
n_Enter = std::max({perfModel->IF_stage.get(16), perfModel->PC_substage.get(4)});
// PCGen
uint64_t n_PCGen;
n_PCGen = n_Enter + 1;
// uA_PcCorrect
uint64_t n_uA_PcCorrect;
n_uA_PcCorrect = std::max({n_Enter, perfModel->dynBranchPredModel.getPc_mp()});
// uA_CacheBlock
uint64_t n_uA_CacheBlock;
n_uA_CacheBlock = std::max({n_Enter, perfModel->iCacheModel.getIc_out()});
// PC_substage
uint64_t n_PC_substage;
n_PC_substage = std::max({n_PCGen, n_uA_PcCorrect, n_uA_CacheBlock, perfModel->PC_substage.get(1), perfModel->IF_substage_0.get(4)});
perfModel->PC_substage.set(n_PC_substage);
// ICacheCtrl
uint64_t n_ICacheCtrl;
n_ICacheCtrl = n_PC_substage + 1;
// IF_substage_0
uint64_t n_IF_substage_0;
n_IF_substage_0 = std::max({n_ICacheCtrl, perfModel->IF_substage_0.get(1), perfModel->IF_substage_1.get(4)});
perfModel->IF_substage_0.set(n_IF_substage_0);
// ICache
uint64_t n_ICache;
n_ICache = n_IF_substage_0 + perfModel->iCacheModel.getDelay();
perfModel->iCacheModel.setIc_in(n_ICache);
// uA_PcPredict
uint64_t n_uA_PcPredict;
n_uA_PcPredict = std::max({n_IF_substage_0, perfModel->dynBranchPredModel.getPc_pt()});
// IF_substage_1
uint64_t n_IF_substage_1;
n_IF_substage_1 = std::max({n_ICache, n_uA_PcPredict, perfModel->IF_substage_1.get(1), perfModel->IF_substage_2.get(4)});
perfModel->IF_substage_1.set(n_IF_substage_1);
// IScan
uint64_t n_IScan;
n_IScan = n_IF_substage_1 + 1;
// IF_stage
uint64_t n_IF_stage;
n_IF_stage = std::max({n_IScan, perfModel->IF_stage.get(1), perfModel->IF_substage_2.get(1), perfModel->DEC_stage.get(4)});
perfModel->IF_stage.set(n_IF_stage);
perfModel->IF_substage_2.set(n_IF_stage);
// Decoder
uint64_t n_Decoder;
n_Decoder = n_IF_stage + 1;
// DEC_stage
uint64_t n_DEC_stage;
n_DEC_stage = std::max({n_Decoder, perfModel->DEC_stage.get(1), perfModel->RN_stage.get(5)});
perfModel->DEC_stage.set(n_DEC_stage);
// Rename
uint64_t n_Rename;
n_Rename = n_DEC_stage + 1;
// RN_stage
uint64_t n_RN_stage;
n_RN_stage = std::max({n_Rename, perfModel->RN_stage.get(1), perfModel->OoO_stage.get(64), perfModel->IS_substage_alu.get(24)});
perfModel->RN_stage.set(n_RN_stage);
// Issue
uint64_t n_Issue;
n_Issue = n_RN_stage + 2;
// IS_substage_alu
uint64_t n_IS_substage_alu;
n_IS_substage_alu = std::max({n_Issue, perfModel->IS_substage_alu.get(1), perfModel->LD_substage_alu.get(3)});
perfModel->IS_substage_alu.set(n_IS_substage_alu);
// OperandLookup
uint64_t n_OperandLookup;
n_OperandLookup = n_IS_substage_alu + 1;
// uA_OF_A_alu
uint64_t n_uA_OF_A_alu;
n_uA_OF_A_alu = std::max({n_IS_substage_alu, perfModel->regModel.getXa()});
// uA_OF_B_alu
uint64_t n_uA_OF_B_alu;
n_uA_OF_B_alu = std::max({n_IS_substage_alu, perfModel->regModel.getXb()});
// LD_substage_alu
uint64_t n_LD_substage_alu;
n_LD_substage_alu = std::max({n_OperandLookup, n_uA_OF_A_alu, n_uA_OF_B_alu, perfModel->LD_substage_alu.get(1), perfModel->EX_stage_alu.get(9), perfModel->EX_substage_mul_1.get(2)});
perfModel->LD_substage_alu.set(n_LD_substage_alu);
// MUL1
uint64_t n_MUL1;
n_MUL1 = n_LD_substage_alu + 1;
// EX_substage_mul_1
uint64_t n_EX_substage_mul_1;
n_EX_substage_mul_1 = std::max({n_MUL1, perfModel->EX_substage_mul_1.get(1), perfModel->EX_substage_mul_2.get(2)});
perfModel->EX_substage_mul_1.set(n_EX_substage_mul_1);
// MUL2
uint64_t n_MUL2;
n_MUL2 = n_EX_substage_mul_1 + 1;
// EX_substage_mul_2
uint64_t n_EX_substage_mul_2;
n_EX_substage_mul_2 = std::max({n_MUL2, perfModel->EX_substage_mul_2.get(1), perfModel->EX_substage_mul_3.get(2)});
perfModel->EX_substage_mul_2.set(n_EX_substage_mul_2);
// MUL3
uint64_t n_MUL3;
n_MUL3 = n_EX_substage_mul_2 + 1;
// EX_substage_mul_3
uint64_t n_EX_substage_mul_3;
n_EX_substage_mul_3 = std::max({n_MUL3, perfModel->EX_substage_mul_3.get(1), perfModel->EX_substage_mul_4.get(2)});
perfModel->EX_substage_mul_3.set(n_EX_substage_mul_3);
// MUL4
uint64_t n_MUL4;
n_MUL4 = n_EX_substage_mul_3 + 1;
perfModel->regModel.setXd(n_MUL4);
// EX_stage_alu
uint64_t n_EX_stage_alu;
n_EX_stage_alu = std::max({n_MUL4, perfModel->EX_stage_alu.get(1), perfModel->EX_substage_mul_4.get(1)});
perfModel->EX_stage_alu.set(n_EX_stage_alu);
perfModel->EX_substage_mul_4.set(n_EX_stage_alu);
// OoO_stage
uint64_t n_OoO_stage;
n_OoO_stage = std::max({n_EX_stage_alu, perfModel->OoO_stage.get(1), perfModel->COM_stage.get(8)});
perfModel->OoO_stage.set(n_OoO_stage);
// Commit
uint64_t n_Commit;
n_Commit = n_OoO_stage + 2;
// COM_stage
uint64_t n_COM_stage;
n_COM_stage = std::max({n_Commit, perfModel->COM_stage.get(1)});
perfModel->COM_stage.set(n_COM_stage);

  // Dump Entrance point for info print (tracing)
  perfModel->entrancePoint = n_Enter;
  }
);

static SchedulingFunction *schedulingFunction_mulhu = new SchedulingFunction(
  RV32_4ISSUE_SchedulingFunctionSet,
  "mulhu",
  23,
  [](PerformanceModel* perfModel_){
  RV32_4ISSUE_PerformanceModel* perfModel = static_cast<RV32_4ISSUE_PerformanceModel*>(perfModel_);
  // Enter
uint64_t n_Enter;
n_Enter = std::max({perfModel->IF_stage.get(16), perfModel->PC_substage.get(4)});
// PCGen
uint64_t n_PCGen;
n_PCGen = n_Enter + 1;
// uA_PcCorrect
uint64_t n_uA_PcCorrect;
n_uA_PcCorrect = std::max({n_Enter, perfModel->dynBranchPredModel.getPc_mp()});
// uA_CacheBlock
uint64_t n_uA_CacheBlock;
n_uA_CacheBlock = std::max({n_Enter, perfModel->iCacheModel.getIc_out()});
// PC_substage
uint64_t n_PC_substage;
n_PC_substage = std::max({n_PCGen, n_uA_PcCorrect, n_uA_CacheBlock, perfModel->PC_substage.get(1), perfModel->IF_substage_0.get(4)});
perfModel->PC_substage.set(n_PC_substage);
// ICacheCtrl
uint64_t n_ICacheCtrl;
n_ICacheCtrl = n_PC_substage + 1;
// IF_substage_0
uint64_t n_IF_substage_0;
n_IF_substage_0 = std::max({n_ICacheCtrl, perfModel->IF_substage_0.get(1), perfModel->IF_substage_1.get(4)});
perfModel->IF_substage_0.set(n_IF_substage_0);
// ICache
uint64_t n_ICache;
n_ICache = n_IF_substage_0 + perfModel->iCacheModel.getDelay();
perfModel->iCacheModel.setIc_in(n_ICache);
// uA_PcPredict
uint64_t n_uA_PcPredict;
n_uA_PcPredict = std::max({n_IF_substage_0, perfModel->dynBranchPredModel.getPc_pt()});
// IF_substage_1
uint64_t n_IF_substage_1;
n_IF_substage_1 = std::max({n_ICache, n_uA_PcPredict, perfModel->IF_substage_1.get(1), perfModel->IF_substage_2.get(4)});
perfModel->IF_substage_1.set(n_IF_substage_1);
// IScan
uint64_t n_IScan;
n_IScan = n_IF_substage_1 + 1;
// IF_stage
uint64_t n_IF_stage;
n_IF_stage = std::max({n_IScan, perfModel->IF_stage.get(1), perfModel->IF_substage_2.get(1), perfModel->DEC_stage.get(4)});
perfModel->IF_stage.set(n_IF_stage);
perfModel->IF_substage_2.set(n_IF_stage);
// Decoder
uint64_t n_Decoder;
n_Decoder = n_IF_stage + 1;
// DEC_stage
uint64_t n_DEC_stage;
n_DEC_stage = std::max({n_Decoder, perfModel->DEC_stage.get(1), perfModel->RN_stage.get(5)});
perfModel->DEC_stage.set(n_DEC_stage);
// Rename
uint64_t n_Rename;
n_Rename = n_DEC_stage + 1;
// RN_stage
uint64_t n_RN_stage;
n_RN_stage = std::max({n_Rename, perfModel->RN_stage.get(1), perfModel->OoO_stage.get(64), perfModel->IS_substage_alu.get(24)});
perfModel->RN_stage.set(n_RN_stage);
// Issue
uint64_t n_Issue;
n_Issue = n_RN_stage + 2;
// IS_substage_alu
uint64_t n_IS_substage_alu;
n_IS_substage_alu = std::max({n_Issue, perfModel->IS_substage_alu.get(1), perfModel->LD_substage_alu.get(3)});
perfModel->IS_substage_alu.set(n_IS_substage_alu);
// OperandLookup
uint64_t n_OperandLookup;
n_OperandLookup = n_IS_substage_alu + 1;
// uA_OF_A_alu
uint64_t n_uA_OF_A_alu;
n_uA_OF_A_alu = std::max({n_IS_substage_alu, perfModel->regModel.getXa()});
// uA_OF_B_alu
uint64_t n_uA_OF_B_alu;
n_uA_OF_B_alu = std::max({n_IS_substage_alu, perfModel->regModel.getXb()});
// LD_substage_alu
uint64_t n_LD_substage_alu;
n_LD_substage_alu = std::max({n_OperandLookup, n_uA_OF_A_alu, n_uA_OF_B_alu, perfModel->LD_substage_alu.get(1), perfModel->EX_stage_alu.get(9), perfModel->EX_substage_mul_1.get(2)});
perfModel->LD_substage_alu.set(n_LD_substage_alu);
// MUL1
uint64_t n_MUL1;
n_MUL1 = n_LD_substage_alu + 1;
// EX_substage_mul_1
uint64_t n_EX_substage_mul_1;
n_EX_substage_mul_1 = std::max({n_MUL1, perfModel->EX_substage_mul_1.get(1), perfModel->EX_substage_mul_2.get(2)});
perfModel->EX_substage_mul_1.set(n_EX_substage_mul_1);
// MUL2
uint64_t n_MUL2;
n_MUL2 = n_EX_substage_mul_1 + 1;
// EX_substage_mul_2
uint64_t n_EX_substage_mul_2;
n_EX_substage_mul_2 = std::max({n_MUL2, perfModel->EX_substage_mul_2.get(1), perfModel->EX_substage_mul_3.get(2)});
perfModel->EX_substage_mul_2.set(n_EX_substage_mul_2);
// MUL3
uint64_t n_MUL3;
n_MUL3 = n_EX_substage_mul_2 + 1;
// EX_substage_mul_3
uint64_t n_EX_substage_mul_3;
n_EX_substage_mul_3 = std::max({n_MUL3, perfModel->EX_substage_mul_3.get(1), perfModel->EX_substage_mul_4.get(2)});
perfModel->EX_substage_mul_3.set(n_EX_substage_mul_3);
// MUL4
uint64_t n_MUL4;
n_MUL4 = n_EX_substage_mul_3 + 1;
perfModel->regModel.setXd(n_MUL4);
// EX_stage_alu
uint64_t n_EX_stage_alu;
n_EX_stage_alu = std::max({n_MUL4, perfModel->EX_stage_alu.get(1), perfModel->EX_substage_mul_4.get(1)});
perfModel->EX_stage_alu.set(n_EX_stage_alu);
perfModel->EX_substage_mul_4.set(n_EX_stage_alu);
// OoO_stage
uint64_t n_OoO_stage;
n_OoO_stage = std::max({n_EX_stage_alu, perfModel->OoO_stage.get(1), perfModel->COM_stage.get(8)});
perfModel->OoO_stage.set(n_OoO_stage);
// Commit
uint64_t n_Commit;
n_Commit = n_OoO_stage + 2;
// COM_stage
uint64_t n_COM_stage;
n_COM_stage = std::max({n_Commit, perfModel->COM_stage.get(1)});
perfModel->COM_stage.set(n_COM_stage);

  // Dump Entrance point for info print (tracing)
  perfModel->entrancePoint = n_Enter;
  }
);

static SchedulingFunction *schedulingFunction_mulhsu = new SchedulingFunction(
  RV32_4ISSUE_SchedulingFunctionSet,
  "mulhsu",
  24,
  [](PerformanceModel* perfModel_){
  RV32_4ISSUE_PerformanceModel* perfModel = static_cast<RV32_4ISSUE_PerformanceModel*>(perfModel_);
  // Enter
uint64_t n_Enter;
n_Enter = std::max({perfModel->IF_stage.get(16), perfModel->PC_substage.get(4)});
// PCGen
uint64_t n_PCGen;
n_PCGen = n_Enter + 1;
// uA_PcCorrect
uint64_t n_uA_PcCorrect;
n_uA_PcCorrect = std::max({n_Enter, perfModel->dynBranchPredModel.getPc_mp()});
// uA_CacheBlock
uint64_t n_uA_CacheBlock;
n_uA_CacheBlock = std::max({n_Enter, perfModel->iCacheModel.getIc_out()});
// PC_substage
uint64_t n_PC_substage;
n_PC_substage = std::max({n_PCGen, n_uA_PcCorrect, n_uA_CacheBlock, perfModel->PC_substage.get(1), perfModel->IF_substage_0.get(4)});
perfModel->PC_substage.set(n_PC_substage);
// ICacheCtrl
uint64_t n_ICacheCtrl;
n_ICacheCtrl = n_PC_substage + 1;
// IF_substage_0
uint64_t n_IF_substage_0;
n_IF_substage_0 = std::max({n_ICacheCtrl, perfModel->IF_substage_0.get(1), perfModel->IF_substage_1.get(4)});
perfModel->IF_substage_0.set(n_IF_substage_0);
// ICache
uint64_t n_ICache;
n_ICache = n_IF_substage_0 + perfModel->iCacheModel.getDelay();
perfModel->iCacheModel.setIc_in(n_ICache);
// uA_PcPredict
uint64_t n_uA_PcPredict;
n_uA_PcPredict = std::max({n_IF_substage_0, perfModel->dynBranchPredModel.getPc_pt()});
// IF_substage_1
uint64_t n_IF_substage_1;
n_IF_substage_1 = std::max({n_ICache, n_uA_PcPredict, perfModel->IF_substage_1.get(1), perfModel->IF_substage_2.get(4)});
perfModel->IF_substage_1.set(n_IF_substage_1);
// IScan
uint64_t n_IScan;
n_IScan = n_IF_substage_1 + 1;
// IF_stage
uint64_t n_IF_stage;
n_IF_stage = std::max({n_IScan, perfModel->IF_stage.get(1), perfModel->IF_substage_2.get(1), perfModel->DEC_stage.get(4)});
perfModel->IF_stage.set(n_IF_stage);
perfModel->IF_substage_2.set(n_IF_stage);
// Decoder
uint64_t n_Decoder;
n_Decoder = n_IF_stage + 1;
// DEC_stage
uint64_t n_DEC_stage;
n_DEC_stage = std::max({n_Decoder, perfModel->DEC_stage.get(1), perfModel->RN_stage.get(5)});
perfModel->DEC_stage.set(n_DEC_stage);
// Rename
uint64_t n_Rename;
n_Rename = n_DEC_stage + 1;
// RN_stage
uint64_t n_RN_stage;
n_RN_stage = std::max({n_Rename, perfModel->RN_stage.get(1), perfModel->OoO_stage.get(64), perfModel->IS_substage_alu.get(24)});
perfModel->RN_stage.set(n_RN_stage);
// Issue
uint64_t n_Issue;
n_Issue = n_RN_stage + 2;
// IS_substage_alu
uint64_t n_IS_substage_alu;
n_IS_substage_alu = std::max({n_Issue, perfModel->IS_substage_alu.get(1), perfModel->LD_substage_alu.get(3)});
perfModel->IS_substage_alu.set(n_IS_substage_alu);
// OperandLookup
uint64_t n_OperandLookup;
n_OperandLookup = n_IS_substage_alu + 1;
// uA_OF_A_alu
uint64_t n_uA_OF_A_alu;
n_uA_OF_A_alu = std::max({n_IS_substage_alu, perfModel->regModel.getXa()});
// uA_OF_B_alu
uint64_t n_uA_OF_B_alu;
n_uA_OF_B_alu = std::max({n_IS_substage_alu, perfModel->regModel.getXb()});
// LD_substage_alu
uint64_t n_LD_substage_alu;
n_LD_substage_alu = std::max({n_OperandLookup, n_uA_OF_A_alu, n_uA_OF_B_alu, perfModel->LD_substage_alu.get(1), perfModel->EX_stage_alu.get(9), perfModel->EX_substage_mul_1.get(2)});
perfModel->LD_substage_alu.set(n_LD_substage_alu);
// MUL1
uint64_t n_MUL1;
n_MUL1 = n_LD_substage_alu + 1;
// EX_substage_mul_1
uint64_t n_EX_substage_mul_1;
n_EX_substage_mul_1 = std::max({n_MUL1, perfModel->EX_substage_mul_1.get(1), perfModel->EX_substage_mul_2.get(2)});
perfModel->EX_substage_mul_1.set(n_EX_substage_mul_1);
// MUL2
uint64_t n_MUL2;
n_MUL2 = n_EX_substage_mul_1 + 1;
// EX_substage_mul_2
uint64_t n_EX_substage_mul_2;
n_EX_substage_mul_2 = std::max({n_MUL2, perfModel->EX_substage_mul_2.get(1), perfModel->EX_substage_mul_3.get(2)});
perfModel->EX_substage_mul_2.set(n_EX_substage_mul_2);
// MUL3
uint64_t n_MUL3;
n_MUL3 = n_EX_substage_mul_2 + 1;
// EX_substage_mul_3
uint64_t n_EX_substage_mul_3;
n_EX_substage_mul_3 = std::max({n_MUL3, perfModel->EX_substage_mul_3.get(1), perfModel->EX_substage_mul_4.get(2)});
perfModel->EX_substage_mul_3.set(n_EX_substage_mul_3);
// MUL4
uint64_t n_MUL4;
n_MUL4 = n_EX_substage_mul_3 + 1;
perfModel->regModel.setXd(n_MUL4);
// EX_stage_alu
uint64_t n_EX_stage_alu;
n_EX_stage_alu = std::max({n_MUL4, perfModel->EX_stage_alu.get(1), perfModel->EX_substage_mul_4.get(1)});
perfModel->EX_stage_alu.set(n_EX_stage_alu);
perfModel->EX_substage_mul_4.set(n_EX_stage_alu);
// OoO_stage
uint64_t n_OoO_stage;
n_OoO_stage = std::max({n_EX_stage_alu, perfModel->OoO_stage.get(1), perfModel->COM_stage.get(8)});
perfModel->OoO_stage.set(n_OoO_stage);
// Commit
uint64_t n_Commit;
n_Commit = n_OoO_stage + 2;
// COM_stage
uint64_t n_COM_stage;
n_COM_stage = std::max({n_Commit, perfModel->COM_stage.get(1)});
perfModel->COM_stage.set(n_COM_stage);

  // Dump Entrance point for info print (tracing)
  perfModel->entrancePoint = n_Enter;
  }
);

static SchedulingFunction *schedulingFunction_div = new SchedulingFunction(
  RV32_4ISSUE_SchedulingFunctionSet,
  "div",
  25,
  [](PerformanceModel* perfModel_){
  RV32_4ISSUE_PerformanceModel* perfModel = static_cast<RV32_4ISSUE_PerformanceModel*>(perfModel_);
  // Enter
uint64_t n_Enter;
n_Enter = std::max({perfModel->IF_stage.get(16), perfModel->PC_substage.get(4)});
// PCGen
uint64_t n_PCGen;
n_PCGen = n_Enter + 1;
// uA_PcCorrect
uint64_t n_uA_PcCorrect;
n_uA_PcCorrect = std::max({n_Enter, perfModel->dynBranchPredModel.getPc_mp()});
// uA_CacheBlock
uint64_t n_uA_CacheBlock;
n_uA_CacheBlock = std::max({n_Enter, perfModel->iCacheModel.getIc_out()});
// PC_substage
uint64_t n_PC_substage;
n_PC_substage = std::max({n_PCGen, n_uA_PcCorrect, n_uA_CacheBlock, perfModel->PC_substage.get(1), perfModel->IF_substage_0.get(4)});
perfModel->PC_substage.set(n_PC_substage);
// ICacheCtrl
uint64_t n_ICacheCtrl;
n_ICacheCtrl = n_PC_substage + 1;
// IF_substage_0
uint64_t n_IF_substage_0;
n_IF_substage_0 = std::max({n_ICacheCtrl, perfModel->IF_substage_0.get(1), perfModel->IF_substage_1.get(4)});
perfModel->IF_substage_0.set(n_IF_substage_0);
// ICache
uint64_t n_ICache;
n_ICache = n_IF_substage_0 + perfModel->iCacheModel.getDelay();
perfModel->iCacheModel.setIc_in(n_ICache);
// uA_PcPredict
uint64_t n_uA_PcPredict;
n_uA_PcPredict = std::max({n_IF_substage_0, perfModel->dynBranchPredModel.getPc_pt()});
// IF_substage_1
uint64_t n_IF_substage_1;
n_IF_substage_1 = std::max({n_ICache, n_uA_PcPredict, perfModel->IF_substage_1.get(1), perfModel->IF_substage_2.get(4)});
perfModel->IF_substage_1.set(n_IF_substage_1);
// IScan
uint64_t n_IScan;
n_IScan = n_IF_substage_1 + 1;
// IF_stage
uint64_t n_IF_stage;
n_IF_stage = std::max({n_IScan, perfModel->IF_stage.get(1), perfModel->IF_substage_2.get(1), perfModel->DEC_stage.get(4)});
perfModel->IF_stage.set(n_IF_stage);
perfModel->IF_substage_2.set(n_IF_stage);
// Decoder
uint64_t n_Decoder;
n_Decoder = n_IF_stage + 1;
// DEC_stage
uint64_t n_DEC_stage;
n_DEC_stage = std::max({n_Decoder, perfModel->DEC_stage.get(1), perfModel->RN_stage.get(5)});
perfModel->DEC_stage.set(n_DEC_stage);
// Rename
uint64_t n_Rename;
n_Rename = n_DEC_stage + 1;
// RN_stage
uint64_t n_RN_stage;
n_RN_stage = std::max({n_Rename, perfModel->RN_stage.get(1), perfModel->OoO_stage.get(64), perfModel->IS_substage_alu.get(24)});
perfModel->RN_stage.set(n_RN_stage);
// Issue
uint64_t n_Issue;
n_Issue = n_RN_stage + 2;
// IS_substage_alu
uint64_t n_IS_substage_alu;
n_IS_substage_alu = std::max({n_Issue, perfModel->IS_substage_alu.get(1), perfModel->LD_substage_alu.get(3)});
perfModel->IS_substage_alu.set(n_IS_substage_alu);
// OperandLookup
uint64_t n_OperandLookup;
n_OperandLookup = n_IS_substage_alu + 1;
// uA_OF_A_alu
uint64_t n_uA_OF_A_alu;
n_uA_OF_A_alu = std::max({n_IS_substage_alu, perfModel->regModel.getXa()});
// uA_OF_B_alu
uint64_t n_uA_OF_B_alu;
n_uA_OF_B_alu = std::max({n_IS_substage_alu, perfModel->regModel.getXb()});
// LD_substage_alu
uint64_t n_LD_substage_alu;
n_LD_substage_alu = std::max({n_OperandLookup, n_uA_OF_A_alu, n_uA_OF_B_alu, perfModel->LD_substage_alu.get(1), perfModel->EX_stage_alu.get(9), perfModel->EX_substage_div});
perfModel->LD_substage_alu.set(n_LD_substage_alu);
// DIV
uint64_t n_DIV;
n_DIV = n_LD_substage_alu + perfModel->divider.getDelay();
perfModel->regModel.setXd(n_DIV);
// EX_stage_alu
uint64_t n_EX_stage_alu;
n_EX_stage_alu = std::max({n_DIV, perfModel->EX_stage_alu.get(1)});
perfModel->EX_stage_alu.set(n_EX_stage_alu);
perfModel->EX_substage_div = n_EX_stage_alu;
// OoO_stage
uint64_t n_OoO_stage;
n_OoO_stage = std::max({n_EX_stage_alu, perfModel->OoO_stage.get(1), perfModel->COM_stage.get(8)});
perfModel->OoO_stage.set(n_OoO_stage);
// Commit
uint64_t n_Commit;
n_Commit = n_OoO_stage + 2;
// COM_stage
uint64_t n_COM_stage;
n_COM_stage = std::max({n_Commit, perfModel->COM_stage.get(1)});
perfModel->COM_stage.set(n_COM_stage);

  // Dump Entrance point for info print (tracing)
  perfModel->entrancePoint = n_Enter;
  }
);

static SchedulingFunction *schedulingFunction_rem = new SchedulingFunction(
  RV32_4ISSUE_SchedulingFunctionSet,
  "rem",
  26,
  [](PerformanceModel* perfModel_){
  RV32_4ISSUE_PerformanceModel* perfModel = static_cast<RV32_4ISSUE_PerformanceModel*>(perfModel_);
  // Enter
uint64_t n_Enter;
n_Enter = std::max({perfModel->IF_stage.get(16), perfModel->PC_substage.get(4)});
// PCGen
uint64_t n_PCGen;
n_PCGen = n_Enter + 1;
// uA_PcCorrect
uint64_t n_uA_PcCorrect;
n_uA_PcCorrect = std::max({n_Enter, perfModel->dynBranchPredModel.getPc_mp()});
// uA_CacheBlock
uint64_t n_uA_CacheBlock;
n_uA_CacheBlock = std::max({n_Enter, perfModel->iCacheModel.getIc_out()});
// PC_substage
uint64_t n_PC_substage;
n_PC_substage = std::max({n_PCGen, n_uA_PcCorrect, n_uA_CacheBlock, perfModel->PC_substage.get(1), perfModel->IF_substage_0.get(4)});
perfModel->PC_substage.set(n_PC_substage);
// ICacheCtrl
uint64_t n_ICacheCtrl;
n_ICacheCtrl = n_PC_substage + 1;
// IF_substage_0
uint64_t n_IF_substage_0;
n_IF_substage_0 = std::max({n_ICacheCtrl, perfModel->IF_substage_0.get(1), perfModel->IF_substage_1.get(4)});
perfModel->IF_substage_0.set(n_IF_substage_0);
// ICache
uint64_t n_ICache;
n_ICache = n_IF_substage_0 + perfModel->iCacheModel.getDelay();
perfModel->iCacheModel.setIc_in(n_ICache);
// uA_PcPredict
uint64_t n_uA_PcPredict;
n_uA_PcPredict = std::max({n_IF_substage_0, perfModel->dynBranchPredModel.getPc_pt()});
// IF_substage_1
uint64_t n_IF_substage_1;
n_IF_substage_1 = std::max({n_ICache, n_uA_PcPredict, perfModel->IF_substage_1.get(1), perfModel->IF_substage_2.get(4)});
perfModel->IF_substage_1.set(n_IF_substage_1);
// IScan
uint64_t n_IScan;
n_IScan = n_IF_substage_1 + 1;
// IF_stage
uint64_t n_IF_stage;
n_IF_stage = std::max({n_IScan, perfModel->IF_stage.get(1), perfModel->IF_substage_2.get(1), perfModel->DEC_stage.get(4)});
perfModel->IF_stage.set(n_IF_stage);
perfModel->IF_substage_2.set(n_IF_stage);
// Decoder
uint64_t n_Decoder;
n_Decoder = n_IF_stage + 1;
// DEC_stage
uint64_t n_DEC_stage;
n_DEC_stage = std::max({n_Decoder, perfModel->DEC_stage.get(1), perfModel->RN_stage.get(5)});
perfModel->DEC_stage.set(n_DEC_stage);
// Rename
uint64_t n_Rename;
n_Rename = n_DEC_stage + 1;
// RN_stage
uint64_t n_RN_stage;
n_RN_stage = std::max({n_Rename, perfModel->RN_stage.get(1), perfModel->OoO_stage.get(64), perfModel->IS_substage_alu.get(24)});
perfModel->RN_stage.set(n_RN_stage);
// Issue
uint64_t n_Issue;
n_Issue = n_RN_stage + 2;
// IS_substage_alu
uint64_t n_IS_substage_alu;
n_IS_substage_alu = std::max({n_Issue, perfModel->IS_substage_alu.get(1), perfModel->LD_substage_alu.get(3)});
perfModel->IS_substage_alu.set(n_IS_substage_alu);
// OperandLookup
uint64_t n_OperandLookup;
n_OperandLookup = n_IS_substage_alu + 1;
// uA_OF_A_alu
uint64_t n_uA_OF_A_alu;
n_uA_OF_A_alu = std::max({n_IS_substage_alu, perfModel->regModel.getXa()});
// uA_OF_B_alu
uint64_t n_uA_OF_B_alu;
n_uA_OF_B_alu = std::max({n_IS_substage_alu, perfModel->regModel.getXb()});
// LD_substage_alu
uint64_t n_LD_substage_alu;
n_LD_substage_alu = std::max({n_OperandLookup, n_uA_OF_A_alu, n_uA_OF_B_alu, perfModel->LD_substage_alu.get(1), perfModel->EX_stage_alu.get(9), perfModel->EX_substage_div});
perfModel->LD_substage_alu.set(n_LD_substage_alu);
// DIV
uint64_t n_DIV;
n_DIV = n_LD_substage_alu + perfModel->divider.getDelay();
perfModel->regModel.setXd(n_DIV);
// EX_stage_alu
uint64_t n_EX_stage_alu;
n_EX_stage_alu = std::max({n_DIV, perfModel->EX_stage_alu.get(1)});
perfModel->EX_stage_alu.set(n_EX_stage_alu);
perfModel->EX_substage_div = n_EX_stage_alu;
// OoO_stage
uint64_t n_OoO_stage;
n_OoO_stage = std::max({n_EX_stage_alu, perfModel->OoO_stage.get(1), perfModel->COM_stage.get(8)});
perfModel->OoO_stage.set(n_OoO_stage);
// Commit
uint64_t n_Commit;
n_Commit = n_OoO_stage + 2;
// COM_stage
uint64_t n_COM_stage;
n_COM_stage = std::max({n_Commit, perfModel->COM_stage.get(1)});
perfModel->COM_stage.set(n_COM_stage);

  // Dump Entrance point for info print (tracing)
  perfModel->entrancePoint = n_Enter;
  }
);

static SchedulingFunction *schedulingFunction_divu = new SchedulingFunction(
  RV32_4ISSUE_SchedulingFunctionSet,
  "divu",
  27,
  [](PerformanceModel* perfModel_){
  RV32_4ISSUE_PerformanceModel* perfModel = static_cast<RV32_4ISSUE_PerformanceModel*>(perfModel_);
  // Enter
uint64_t n_Enter;
n_Enter = std::max({perfModel->IF_stage.get(16), perfModel->PC_substage.get(4)});
// PCGen
uint64_t n_PCGen;
n_PCGen = n_Enter + 1;
// uA_PcCorrect
uint64_t n_uA_PcCorrect;
n_uA_PcCorrect = std::max({n_Enter, perfModel->dynBranchPredModel.getPc_mp()});
// uA_CacheBlock
uint64_t n_uA_CacheBlock;
n_uA_CacheBlock = std::max({n_Enter, perfModel->iCacheModel.getIc_out()});
// PC_substage
uint64_t n_PC_substage;
n_PC_substage = std::max({n_PCGen, n_uA_PcCorrect, n_uA_CacheBlock, perfModel->PC_substage.get(1), perfModel->IF_substage_0.get(4)});
perfModel->PC_substage.set(n_PC_substage);
// ICacheCtrl
uint64_t n_ICacheCtrl;
n_ICacheCtrl = n_PC_substage + 1;
// IF_substage_0
uint64_t n_IF_substage_0;
n_IF_substage_0 = std::max({n_ICacheCtrl, perfModel->IF_substage_0.get(1), perfModel->IF_substage_1.get(4)});
perfModel->IF_substage_0.set(n_IF_substage_0);
// ICache
uint64_t n_ICache;
n_ICache = n_IF_substage_0 + perfModel->iCacheModel.getDelay();
perfModel->iCacheModel.setIc_in(n_ICache);
// uA_PcPredict
uint64_t n_uA_PcPredict;
n_uA_PcPredict = std::max({n_IF_substage_0, perfModel->dynBranchPredModel.getPc_pt()});
// IF_substage_1
uint64_t n_IF_substage_1;
n_IF_substage_1 = std::max({n_ICache, n_uA_PcPredict, perfModel->IF_substage_1.get(1), perfModel->IF_substage_2.get(4)});
perfModel->IF_substage_1.set(n_IF_substage_1);
// IScan
uint64_t n_IScan;
n_IScan = n_IF_substage_1 + 1;
// IF_stage
uint64_t n_IF_stage;
n_IF_stage = std::max({n_IScan, perfModel->IF_stage.get(1), perfModel->IF_substage_2.get(1), perfModel->DEC_stage.get(4)});
perfModel->IF_stage.set(n_IF_stage);
perfModel->IF_substage_2.set(n_IF_stage);
// Decoder
uint64_t n_Decoder;
n_Decoder = n_IF_stage + 1;
// DEC_stage
uint64_t n_DEC_stage;
n_DEC_stage = std::max({n_Decoder, perfModel->DEC_stage.get(1), perfModel->RN_stage.get(5)});
perfModel->DEC_stage.set(n_DEC_stage);
// Rename
uint64_t n_Rename;
n_Rename = n_DEC_stage + 1;
// RN_stage
uint64_t n_RN_stage;
n_RN_stage = std::max({n_Rename, perfModel->RN_stage.get(1), perfModel->OoO_stage.get(64), perfModel->IS_substage_alu.get(24)});
perfModel->RN_stage.set(n_RN_stage);
// Issue
uint64_t n_Issue;
n_Issue = n_RN_stage + 2;
// IS_substage_alu
uint64_t n_IS_substage_alu;
n_IS_substage_alu = std::max({n_Issue, perfModel->IS_substage_alu.get(1), perfModel->LD_substage_alu.get(3)});
perfModel->IS_substage_alu.set(n_IS_substage_alu);
// OperandLookup
uint64_t n_OperandLookup;
n_OperandLookup = n_IS_substage_alu + 1;
// uA_OF_A_alu
uint64_t n_uA_OF_A_alu;
n_uA_OF_A_alu = std::max({n_IS_substage_alu, perfModel->regModel.getXa()});
// uA_OF_B_alu
uint64_t n_uA_OF_B_alu;
n_uA_OF_B_alu = std::max({n_IS_substage_alu, perfModel->regModel.getXb()});
// LD_substage_alu
uint64_t n_LD_substage_alu;
n_LD_substage_alu = std::max({n_OperandLookup, n_uA_OF_A_alu, n_uA_OF_B_alu, perfModel->LD_substage_alu.get(1), perfModel->EX_stage_alu.get(9), perfModel->EX_substage_div});
perfModel->LD_substage_alu.set(n_LD_substage_alu);
// DIVU
uint64_t n_DIVU;
n_DIVU = n_LD_substage_alu + perfModel->divider_u.getDelay();
perfModel->regModel.setXd(n_DIVU);
// EX_stage_alu
uint64_t n_EX_stage_alu;
n_EX_stage_alu = std::max({n_DIVU, perfModel->EX_stage_alu.get(1)});
perfModel->EX_stage_alu.set(n_EX_stage_alu);
perfModel->EX_substage_div = n_EX_stage_alu;
// OoO_stage
uint64_t n_OoO_stage;
n_OoO_stage = std::max({n_EX_stage_alu, perfModel->OoO_stage.get(1), perfModel->COM_stage.get(8)});
perfModel->OoO_stage.set(n_OoO_stage);
// Commit
uint64_t n_Commit;
n_Commit = n_OoO_stage + 2;
// COM_stage
uint64_t n_COM_stage;
n_COM_stage = std::max({n_Commit, perfModel->COM_stage.get(1)});
perfModel->COM_stage.set(n_COM_stage);

  // Dump Entrance point for info print (tracing)
  perfModel->entrancePoint = n_Enter;
  }
);

static SchedulingFunction *schedulingFunction_remu = new SchedulingFunction(
  RV32_4ISSUE_SchedulingFunctionSet,
  "remu",
  28,
  [](PerformanceModel* perfModel_){
  RV32_4ISSUE_PerformanceModel* perfModel = static_cast<RV32_4ISSUE_PerformanceModel*>(perfModel_);
  // Enter
uint64_t n_Enter;
n_Enter = std::max({perfModel->IF_stage.get(16), perfModel->PC_substage.get(4)});
// PCGen
uint64_t n_PCGen;
n_PCGen = n_Enter + 1;
// uA_PcCorrect
uint64_t n_uA_PcCorrect;
n_uA_PcCorrect = std::max({n_Enter, perfModel->dynBranchPredModel.getPc_mp()});
// uA_CacheBlock
uint64_t n_uA_CacheBlock;
n_uA_CacheBlock = std::max({n_Enter, perfModel->iCacheModel.getIc_out()});
// PC_substage
uint64_t n_PC_substage;
n_PC_substage = std::max({n_PCGen, n_uA_PcCorrect, n_uA_CacheBlock, perfModel->PC_substage.get(1), perfModel->IF_substage_0.get(4)});
perfModel->PC_substage.set(n_PC_substage);
// ICacheCtrl
uint64_t n_ICacheCtrl;
n_ICacheCtrl = n_PC_substage + 1;
// IF_substage_0
uint64_t n_IF_substage_0;
n_IF_substage_0 = std::max({n_ICacheCtrl, perfModel->IF_substage_0.get(1), perfModel->IF_substage_1.get(4)});
perfModel->IF_substage_0.set(n_IF_substage_0);
// ICache
uint64_t n_ICache;
n_ICache = n_IF_substage_0 + perfModel->iCacheModel.getDelay();
perfModel->iCacheModel.setIc_in(n_ICache);
// uA_PcPredict
uint64_t n_uA_PcPredict;
n_uA_PcPredict = std::max({n_IF_substage_0, perfModel->dynBranchPredModel.getPc_pt()});
// IF_substage_1
uint64_t n_IF_substage_1;
n_IF_substage_1 = std::max({n_ICache, n_uA_PcPredict, perfModel->IF_substage_1.get(1), perfModel->IF_substage_2.get(4)});
perfModel->IF_substage_1.set(n_IF_substage_1);
// IScan
uint64_t n_IScan;
n_IScan = n_IF_substage_1 + 1;
// IF_stage
uint64_t n_IF_stage;
n_IF_stage = std::max({n_IScan, perfModel->IF_stage.get(1), perfModel->IF_substage_2.get(1), perfModel->DEC_stage.get(4)});
perfModel->IF_stage.set(n_IF_stage);
perfModel->IF_substage_2.set(n_IF_stage);
// Decoder
uint64_t n_Decoder;
n_Decoder = n_IF_stage + 1;
// DEC_stage
uint64_t n_DEC_stage;
n_DEC_stage = std::max({n_Decoder, perfModel->DEC_stage.get(1), perfModel->RN_stage.get(5)});
perfModel->DEC_stage.set(n_DEC_stage);
// Rename
uint64_t n_Rename;
n_Rename = n_DEC_stage + 1;
// RN_stage
uint64_t n_RN_stage;
n_RN_stage = std::max({n_Rename, perfModel->RN_stage.get(1), perfModel->OoO_stage.get(64), perfModel->IS_substage_alu.get(24)});
perfModel->RN_stage.set(n_RN_stage);
// Issue
uint64_t n_Issue;
n_Issue = n_RN_stage + 2;
// IS_substage_alu
uint64_t n_IS_substage_alu;
n_IS_substage_alu = std::max({n_Issue, perfModel->IS_substage_alu.get(1), perfModel->LD_substage_alu.get(3)});
perfModel->IS_substage_alu.set(n_IS_substage_alu);
// OperandLookup
uint64_t n_OperandLookup;
n_OperandLookup = n_IS_substage_alu + 1;
// uA_OF_A_alu
uint64_t n_uA_OF_A_alu;
n_uA_OF_A_alu = std::max({n_IS_substage_alu, perfModel->regModel.getXa()});
// uA_OF_B_alu
uint64_t n_uA_OF_B_alu;
n_uA_OF_B_alu = std::max({n_IS_substage_alu, perfModel->regModel.getXb()});
// LD_substage_alu
uint64_t n_LD_substage_alu;
n_LD_substage_alu = std::max({n_OperandLookup, n_uA_OF_A_alu, n_uA_OF_B_alu, perfModel->LD_substage_alu.get(1), perfModel->EX_stage_alu.get(9), perfModel->EX_substage_div});
perfModel->LD_substage_alu.set(n_LD_substage_alu);
// DIVU
uint64_t n_DIVU;
n_DIVU = n_LD_substage_alu + perfModel->divider_u.getDelay();
perfModel->regModel.setXd(n_DIVU);
// EX_stage_alu
uint64_t n_EX_stage_alu;
n_EX_stage_alu = std::max({n_DIVU, perfModel->EX_stage_alu.get(1)});
perfModel->EX_stage_alu.set(n_EX_stage_alu);
perfModel->EX_substage_div = n_EX_stage_alu;
// OoO_stage
uint64_t n_OoO_stage;
n_OoO_stage = std::max({n_EX_stage_alu, perfModel->OoO_stage.get(1), perfModel->COM_stage.get(8)});
perfModel->OoO_stage.set(n_OoO_stage);
// Commit
uint64_t n_Commit;
n_Commit = n_OoO_stage + 2;
// COM_stage
uint64_t n_COM_stage;
n_COM_stage = std::max({n_Commit, perfModel->COM_stage.get(1)});
perfModel->COM_stage.set(n_COM_stage);

  // Dump Entrance point for info print (tracing)
  perfModel->entrancePoint = n_Enter;
  }
);

static SchedulingFunction *schedulingFunction_csrrw = new SchedulingFunction(
  RV32_4ISSUE_SchedulingFunctionSet,
  "csrrw",
  29,
  [](PerformanceModel* perfModel_){
  RV32_4ISSUE_PerformanceModel* perfModel = static_cast<RV32_4ISSUE_PerformanceModel*>(perfModel_);
  // Enter
uint64_t n_Enter;
n_Enter = std::max({perfModel->IF_stage.get(16), perfModel->PC_substage.get(4)});
// PCGen
uint64_t n_PCGen;
n_PCGen = n_Enter + 1;
// uA_PcCorrect
uint64_t n_uA_PcCorrect;
n_uA_PcCorrect = std::max({n_Enter, perfModel->dynBranchPredModel.getPc_mp()});
// uA_CacheBlock
uint64_t n_uA_CacheBlock;
n_uA_CacheBlock = std::max({n_Enter, perfModel->iCacheModel.getIc_out()});
// PC_substage
uint64_t n_PC_substage;
n_PC_substage = std::max({n_PCGen, n_uA_PcCorrect, n_uA_CacheBlock, perfModel->PC_substage.get(1), perfModel->IF_substage_0.get(4)});
perfModel->PC_substage.set(n_PC_substage);
// ICacheCtrl
uint64_t n_ICacheCtrl;
n_ICacheCtrl = n_PC_substage + 1;
// IF_substage_0
uint64_t n_IF_substage_0;
n_IF_substage_0 = std::max({n_ICacheCtrl, perfModel->IF_substage_0.get(1), perfModel->IF_substage_1.get(4)});
perfModel->IF_substage_0.set(n_IF_substage_0);
// ICache
uint64_t n_ICache;
n_ICache = n_IF_substage_0 + perfModel->iCacheModel.getDelay();
perfModel->iCacheModel.setIc_in(n_ICache);
// uA_PcPredict
uint64_t n_uA_PcPredict;
n_uA_PcPredict = std::max({n_IF_substage_0, perfModel->dynBranchPredModel.getPc_pt()});
// IF_substage_1
uint64_t n_IF_substage_1;
n_IF_substage_1 = std::max({n_ICache, n_uA_PcPredict, perfModel->IF_substage_1.get(1), perfModel->IF_substage_2.get(4)});
perfModel->IF_substage_1.set(n_IF_substage_1);
// IScan
uint64_t n_IScan;
n_IScan = n_IF_substage_1 + 1;
// IF_stage
uint64_t n_IF_stage;
n_IF_stage = std::max({n_IScan, perfModel->IF_stage.get(1), perfModel->IF_substage_2.get(1), perfModel->DEC_stage.get(4)});
perfModel->IF_stage.set(n_IF_stage);
perfModel->IF_substage_2.set(n_IF_stage);
// Decoder
uint64_t n_Decoder;
n_Decoder = n_IF_stage + 1;
// DEC_stage
uint64_t n_DEC_stage;
n_DEC_stage = std::max({n_Decoder, perfModel->DEC_stage.get(1), perfModel->RN_stage.get(5)});
perfModel->DEC_stage.set(n_DEC_stage);
// Rename
uint64_t n_Rename;
n_Rename = n_DEC_stage + 1;
// RN_stage
uint64_t n_RN_stage;
n_RN_stage = std::max({n_Rename, perfModel->RN_stage.get(1), perfModel->OoO_stage.get(64), perfModel->IS_substage_alu.get(24)});
perfModel->RN_stage.set(n_RN_stage);
// Issue
uint64_t n_Issue;
n_Issue = n_RN_stage + 2;
// IS_substage_alu
uint64_t n_IS_substage_alu;
n_IS_substage_alu = std::max({n_Issue, perfModel->IS_substage_alu.get(1), perfModel->LD_substage_alu.get(3)});
perfModel->IS_substage_alu.set(n_IS_substage_alu);
// OperandLookup
uint64_t n_OperandLookup;
n_OperandLookup = n_IS_substage_alu + 1;
// uA_OF_A_alu
uint64_t n_uA_OF_A_alu;
n_uA_OF_A_alu = std::max({n_IS_substage_alu, perfModel->regModel.getXa()});
// LD_substage_alu
uint64_t n_LD_substage_alu;
n_LD_substage_alu = std::max({n_OperandLookup, n_uA_OF_A_alu, perfModel->LD_substage_alu.get(1), perfModel->EX_stage_alu.get(9), perfModel->EX_substage_csr});
perfModel->LD_substage_alu.set(n_LD_substage_alu);
// CSR
uint64_t n_CSR;
n_CSR = n_LD_substage_alu + 1;
perfModel->regModel.setXd(n_CSR);
// EX_stage_alu
uint64_t n_EX_stage_alu;
n_EX_stage_alu = std::max({n_CSR, perfModel->EX_stage_alu.get(1)});
perfModel->EX_stage_alu.set(n_EX_stage_alu);
perfModel->EX_substage_csr = n_EX_stage_alu;
// OoO_stage
uint64_t n_OoO_stage;
n_OoO_stage = std::max({n_EX_stage_alu, perfModel->OoO_stage.get(1), perfModel->COM_stage.get(8)});
perfModel->OoO_stage.set(n_OoO_stage);
// Commit
uint64_t n_Commit;
n_Commit = n_OoO_stage + 2;
// COM_stage
uint64_t n_COM_stage;
n_COM_stage = std::max({n_Commit, perfModel->COM_stage.get(1)});
perfModel->COM_stage.set(n_COM_stage);

  // Dump Entrance point for info print (tracing)
  perfModel->entrancePoint = n_Enter;
  }
);

static SchedulingFunction *schedulingFunction_csrrs = new SchedulingFunction(
  RV32_4ISSUE_SchedulingFunctionSet,
  "csrrs",
  30,
  [](PerformanceModel* perfModel_){
  RV32_4ISSUE_PerformanceModel* perfModel = static_cast<RV32_4ISSUE_PerformanceModel*>(perfModel_);
  // Enter
uint64_t n_Enter;
n_Enter = std::max({perfModel->IF_stage.get(16), perfModel->PC_substage.get(4)});
// PCGen
uint64_t n_PCGen;
n_PCGen = n_Enter + 1;
// uA_PcCorrect
uint64_t n_uA_PcCorrect;
n_uA_PcCorrect = std::max({n_Enter, perfModel->dynBranchPredModel.getPc_mp()});
// uA_CacheBlock
uint64_t n_uA_CacheBlock;
n_uA_CacheBlock = std::max({n_Enter, perfModel->iCacheModel.getIc_out()});
// PC_substage
uint64_t n_PC_substage;
n_PC_substage = std::max({n_PCGen, n_uA_PcCorrect, n_uA_CacheBlock, perfModel->PC_substage.get(1), perfModel->IF_substage_0.get(4)});
perfModel->PC_substage.set(n_PC_substage);
// ICacheCtrl
uint64_t n_ICacheCtrl;
n_ICacheCtrl = n_PC_substage + 1;
// IF_substage_0
uint64_t n_IF_substage_0;
n_IF_substage_0 = std::max({n_ICacheCtrl, perfModel->IF_substage_0.get(1), perfModel->IF_substage_1.get(4)});
perfModel->IF_substage_0.set(n_IF_substage_0);
// ICache
uint64_t n_ICache;
n_ICache = n_IF_substage_0 + perfModel->iCacheModel.getDelay();
perfModel->iCacheModel.setIc_in(n_ICache);
// uA_PcPredict
uint64_t n_uA_PcPredict;
n_uA_PcPredict = std::max({n_IF_substage_0, perfModel->dynBranchPredModel.getPc_pt()});
// IF_substage_1
uint64_t n_IF_substage_1;
n_IF_substage_1 = std::max({n_ICache, n_uA_PcPredict, perfModel->IF_substage_1.get(1), perfModel->IF_substage_2.get(4)});
perfModel->IF_substage_1.set(n_IF_substage_1);
// IScan
uint64_t n_IScan;
n_IScan = n_IF_substage_1 + 1;
// IF_stage
uint64_t n_IF_stage;
n_IF_stage = std::max({n_IScan, perfModel->IF_stage.get(1), perfModel->IF_substage_2.get(1), perfModel->DEC_stage.get(4)});
perfModel->IF_stage.set(n_IF_stage);
perfModel->IF_substage_2.set(n_IF_stage);
// Decoder
uint64_t n_Decoder;
n_Decoder = n_IF_stage + 1;
// DEC_stage
uint64_t n_DEC_stage;
n_DEC_stage = std::max({n_Decoder, perfModel->DEC_stage.get(1), perfModel->RN_stage.get(5)});
perfModel->DEC_stage.set(n_DEC_stage);
// Rename
uint64_t n_Rename;
n_Rename = n_DEC_stage + 1;
// RN_stage
uint64_t n_RN_stage;
n_RN_stage = std::max({n_Rename, perfModel->RN_stage.get(1), perfModel->OoO_stage.get(64), perfModel->IS_substage_alu.get(24)});
perfModel->RN_stage.set(n_RN_stage);
// Issue
uint64_t n_Issue;
n_Issue = n_RN_stage + 2;
// IS_substage_alu
uint64_t n_IS_substage_alu;
n_IS_substage_alu = std::max({n_Issue, perfModel->IS_substage_alu.get(1), perfModel->LD_substage_alu.get(3)});
perfModel->IS_substage_alu.set(n_IS_substage_alu);
// OperandLookup
uint64_t n_OperandLookup;
n_OperandLookup = n_IS_substage_alu + 1;
// uA_OF_A_alu
uint64_t n_uA_OF_A_alu;
n_uA_OF_A_alu = std::max({n_IS_substage_alu, perfModel->regModel.getXa()});
// LD_substage_alu
uint64_t n_LD_substage_alu;
n_LD_substage_alu = std::max({n_OperandLookup, n_uA_OF_A_alu, perfModel->LD_substage_alu.get(1), perfModel->EX_stage_alu.get(9), perfModel->EX_substage_csr});
perfModel->LD_substage_alu.set(n_LD_substage_alu);
// CSR
uint64_t n_CSR;
n_CSR = n_LD_substage_alu + 1;
perfModel->regModel.setXd(n_CSR);
// EX_stage_alu
uint64_t n_EX_stage_alu;
n_EX_stage_alu = std::max({n_CSR, perfModel->EX_stage_alu.get(1)});
perfModel->EX_stage_alu.set(n_EX_stage_alu);
perfModel->EX_substage_csr = n_EX_stage_alu;
// OoO_stage
uint64_t n_OoO_stage;
n_OoO_stage = std::max({n_EX_stage_alu, perfModel->OoO_stage.get(1), perfModel->COM_stage.get(8)});
perfModel->OoO_stage.set(n_OoO_stage);
// Commit
uint64_t n_Commit;
n_Commit = n_OoO_stage + 2;
// COM_stage
uint64_t n_COM_stage;
n_COM_stage = std::max({n_Commit, perfModel->COM_stage.get(1)});
perfModel->COM_stage.set(n_COM_stage);

  // Dump Entrance point for info print (tracing)
  perfModel->entrancePoint = n_Enter;
  }
);

static SchedulingFunction *schedulingFunction_csrrc = new SchedulingFunction(
  RV32_4ISSUE_SchedulingFunctionSet,
  "csrrc",
  31,
  [](PerformanceModel* perfModel_){
  RV32_4ISSUE_PerformanceModel* perfModel = static_cast<RV32_4ISSUE_PerformanceModel*>(perfModel_);
  // Enter
uint64_t n_Enter;
n_Enter = std::max({perfModel->IF_stage.get(16), perfModel->PC_substage.get(4)});
// PCGen
uint64_t n_PCGen;
n_PCGen = n_Enter + 1;
// uA_PcCorrect
uint64_t n_uA_PcCorrect;
n_uA_PcCorrect = std::max({n_Enter, perfModel->dynBranchPredModel.getPc_mp()});
// uA_CacheBlock
uint64_t n_uA_CacheBlock;
n_uA_CacheBlock = std::max({n_Enter, perfModel->iCacheModel.getIc_out()});
// PC_substage
uint64_t n_PC_substage;
n_PC_substage = std::max({n_PCGen, n_uA_PcCorrect, n_uA_CacheBlock, perfModel->PC_substage.get(1), perfModel->IF_substage_0.get(4)});
perfModel->PC_substage.set(n_PC_substage);
// ICacheCtrl
uint64_t n_ICacheCtrl;
n_ICacheCtrl = n_PC_substage + 1;
// IF_substage_0
uint64_t n_IF_substage_0;
n_IF_substage_0 = std::max({n_ICacheCtrl, perfModel->IF_substage_0.get(1), perfModel->IF_substage_1.get(4)});
perfModel->IF_substage_0.set(n_IF_substage_0);
// ICache
uint64_t n_ICache;
n_ICache = n_IF_substage_0 + perfModel->iCacheModel.getDelay();
perfModel->iCacheModel.setIc_in(n_ICache);
// uA_PcPredict
uint64_t n_uA_PcPredict;
n_uA_PcPredict = std::max({n_IF_substage_0, perfModel->dynBranchPredModel.getPc_pt()});
// IF_substage_1
uint64_t n_IF_substage_1;
n_IF_substage_1 = std::max({n_ICache, n_uA_PcPredict, perfModel->IF_substage_1.get(1), perfModel->IF_substage_2.get(4)});
perfModel->IF_substage_1.set(n_IF_substage_1);
// IScan
uint64_t n_IScan;
n_IScan = n_IF_substage_1 + 1;
// IF_stage
uint64_t n_IF_stage;
n_IF_stage = std::max({n_IScan, perfModel->IF_stage.get(1), perfModel->IF_substage_2.get(1), perfModel->DEC_stage.get(4)});
perfModel->IF_stage.set(n_IF_stage);
perfModel->IF_substage_2.set(n_IF_stage);
// Decoder
uint64_t n_Decoder;
n_Decoder = n_IF_stage + 1;
// DEC_stage
uint64_t n_DEC_stage;
n_DEC_stage = std::max({n_Decoder, perfModel->DEC_stage.get(1), perfModel->RN_stage.get(5)});
perfModel->DEC_stage.set(n_DEC_stage);
// Rename
uint64_t n_Rename;
n_Rename = n_DEC_stage + 1;
// RN_stage
uint64_t n_RN_stage;
n_RN_stage = std::max({n_Rename, perfModel->RN_stage.get(1), perfModel->OoO_stage.get(64), perfModel->IS_substage_alu.get(24)});
perfModel->RN_stage.set(n_RN_stage);
// Issue
uint64_t n_Issue;
n_Issue = n_RN_stage + 2;
// IS_substage_alu
uint64_t n_IS_substage_alu;
n_IS_substage_alu = std::max({n_Issue, perfModel->IS_substage_alu.get(1), perfModel->LD_substage_alu.get(3)});
perfModel->IS_substage_alu.set(n_IS_substage_alu);
// OperandLookup
uint64_t n_OperandLookup;
n_OperandLookup = n_IS_substage_alu + 1;
// uA_OF_A_alu
uint64_t n_uA_OF_A_alu;
n_uA_OF_A_alu = std::max({n_IS_substage_alu, perfModel->regModel.getXa()});
// LD_substage_alu
uint64_t n_LD_substage_alu;
n_LD_substage_alu = std::max({n_OperandLookup, n_uA_OF_A_alu, perfModel->LD_substage_alu.get(1), perfModel->EX_stage_alu.get(9), perfModel->EX_substage_csr});
perfModel->LD_substage_alu.set(n_LD_substage_alu);
// CSR
uint64_t n_CSR;
n_CSR = n_LD_substage_alu + 1;
perfModel->regModel.setXd(n_CSR);
// EX_stage_alu
uint64_t n_EX_stage_alu;
n_EX_stage_alu = std::max({n_CSR, perfModel->EX_stage_alu.get(1)});
perfModel->EX_stage_alu.set(n_EX_stage_alu);
perfModel->EX_substage_csr = n_EX_stage_alu;
// OoO_stage
uint64_t n_OoO_stage;
n_OoO_stage = std::max({n_EX_stage_alu, perfModel->OoO_stage.get(1), perfModel->COM_stage.get(8)});
perfModel->OoO_stage.set(n_OoO_stage);
// Commit
uint64_t n_Commit;
n_Commit = n_OoO_stage + 2;
// COM_stage
uint64_t n_COM_stage;
n_COM_stage = std::max({n_Commit, perfModel->COM_stage.get(1)});
perfModel->COM_stage.set(n_COM_stage);

  // Dump Entrance point for info print (tracing)
  perfModel->entrancePoint = n_Enter;
  }
);

static SchedulingFunction *schedulingFunction_csrrwi = new SchedulingFunction(
  RV32_4ISSUE_SchedulingFunctionSet,
  "csrrwi",
  32,
  [](PerformanceModel* perfModel_){
  RV32_4ISSUE_PerformanceModel* perfModel = static_cast<RV32_4ISSUE_PerformanceModel*>(perfModel_);
  // Enter
uint64_t n_Enter;
n_Enter = std::max({perfModel->IF_stage.get(16), perfModel->PC_substage.get(4)});
// PCGen
uint64_t n_PCGen;
n_PCGen = n_Enter + 1;
// uA_PcCorrect
uint64_t n_uA_PcCorrect;
n_uA_PcCorrect = std::max({n_Enter, perfModel->dynBranchPredModel.getPc_mp()});
// uA_CacheBlock
uint64_t n_uA_CacheBlock;
n_uA_CacheBlock = std::max({n_Enter, perfModel->iCacheModel.getIc_out()});
// PC_substage
uint64_t n_PC_substage;
n_PC_substage = std::max({n_PCGen, n_uA_PcCorrect, n_uA_CacheBlock, perfModel->PC_substage.get(1), perfModel->IF_substage_0.get(4)});
perfModel->PC_substage.set(n_PC_substage);
// ICacheCtrl
uint64_t n_ICacheCtrl;
n_ICacheCtrl = n_PC_substage + 1;
// IF_substage_0
uint64_t n_IF_substage_0;
n_IF_substage_0 = std::max({n_ICacheCtrl, perfModel->IF_substage_0.get(1), perfModel->IF_substage_1.get(4)});
perfModel->IF_substage_0.set(n_IF_substage_0);
// ICache
uint64_t n_ICache;
n_ICache = n_IF_substage_0 + perfModel->iCacheModel.getDelay();
perfModel->iCacheModel.setIc_in(n_ICache);
// uA_PcPredict
uint64_t n_uA_PcPredict;
n_uA_PcPredict = std::max({n_IF_substage_0, perfModel->dynBranchPredModel.getPc_pt()});
// IF_substage_1
uint64_t n_IF_substage_1;
n_IF_substage_1 = std::max({n_ICache, n_uA_PcPredict, perfModel->IF_substage_1.get(1), perfModel->IF_substage_2.get(4)});
perfModel->IF_substage_1.set(n_IF_substage_1);
// IScan
uint64_t n_IScan;
n_IScan = n_IF_substage_1 + 1;
// IF_stage
uint64_t n_IF_stage;
n_IF_stage = std::max({n_IScan, perfModel->IF_stage.get(1), perfModel->IF_substage_2.get(1), perfModel->DEC_stage.get(4)});
perfModel->IF_stage.set(n_IF_stage);
perfModel->IF_substage_2.set(n_IF_stage);
// Decoder
uint64_t n_Decoder;
n_Decoder = n_IF_stage + 1;
// DEC_stage
uint64_t n_DEC_stage;
n_DEC_stage = std::max({n_Decoder, perfModel->DEC_stage.get(1), perfModel->RN_stage.get(5)});
perfModel->DEC_stage.set(n_DEC_stage);
// Rename
uint64_t n_Rename;
n_Rename = n_DEC_stage + 1;
// RN_stage
uint64_t n_RN_stage;
n_RN_stage = std::max({n_Rename, perfModel->RN_stage.get(1), perfModel->OoO_stage.get(64), perfModel->IS_substage_alu.get(24)});
perfModel->RN_stage.set(n_RN_stage);
// Issue
uint64_t n_Issue;
n_Issue = n_RN_stage + 2;
// IS_substage_alu
uint64_t n_IS_substage_alu;
n_IS_substage_alu = std::max({n_Issue, perfModel->IS_substage_alu.get(1), perfModel->LD_substage_alu.get(3)});
perfModel->IS_substage_alu.set(n_IS_substage_alu);
// OperandLookup
uint64_t n_OperandLookup;
n_OperandLookup = n_IS_substage_alu + 1;
// LD_substage_alu
uint64_t n_LD_substage_alu;
n_LD_substage_alu = std::max({n_OperandLookup, perfModel->LD_substage_alu.get(1), perfModel->EX_stage_alu.get(9), perfModel->EX_substage_csr});
perfModel->LD_substage_alu.set(n_LD_substage_alu);
// CSR
uint64_t n_CSR;
n_CSR = n_LD_substage_alu + 1;
perfModel->regModel.setXd(n_CSR);
// EX_stage_alu
uint64_t n_EX_stage_alu;
n_EX_stage_alu = std::max({n_CSR, perfModel->EX_stage_alu.get(1)});
perfModel->EX_stage_alu.set(n_EX_stage_alu);
perfModel->EX_substage_csr = n_EX_stage_alu;
// OoO_stage
uint64_t n_OoO_stage;
n_OoO_stage = std::max({n_EX_stage_alu, perfModel->OoO_stage.get(1), perfModel->COM_stage.get(8)});
perfModel->OoO_stage.set(n_OoO_stage);
// Commit
uint64_t n_Commit;
n_Commit = n_OoO_stage + 2;
// COM_stage
uint64_t n_COM_stage;
n_COM_stage = std::max({n_Commit, perfModel->COM_stage.get(1)});
perfModel->COM_stage.set(n_COM_stage);

  // Dump Entrance point for info print (tracing)
  perfModel->entrancePoint = n_Enter;
  }
);

static SchedulingFunction *schedulingFunction_csrrsi = new SchedulingFunction(
  RV32_4ISSUE_SchedulingFunctionSet,
  "csrrsi",
  33,
  [](PerformanceModel* perfModel_){
  RV32_4ISSUE_PerformanceModel* perfModel = static_cast<RV32_4ISSUE_PerformanceModel*>(perfModel_);
  // Enter
uint64_t n_Enter;
n_Enter = std::max({perfModel->IF_stage.get(16), perfModel->PC_substage.get(4)});
// PCGen
uint64_t n_PCGen;
n_PCGen = n_Enter + 1;
// uA_PcCorrect
uint64_t n_uA_PcCorrect;
n_uA_PcCorrect = std::max({n_Enter, perfModel->dynBranchPredModel.getPc_mp()});
// uA_CacheBlock
uint64_t n_uA_CacheBlock;
n_uA_CacheBlock = std::max({n_Enter, perfModel->iCacheModel.getIc_out()});
// PC_substage
uint64_t n_PC_substage;
n_PC_substage = std::max({n_PCGen, n_uA_PcCorrect, n_uA_CacheBlock, perfModel->PC_substage.get(1), perfModel->IF_substage_0.get(4)});
perfModel->PC_substage.set(n_PC_substage);
// ICacheCtrl
uint64_t n_ICacheCtrl;
n_ICacheCtrl = n_PC_substage + 1;
// IF_substage_0
uint64_t n_IF_substage_0;
n_IF_substage_0 = std::max({n_ICacheCtrl, perfModel->IF_substage_0.get(1), perfModel->IF_substage_1.get(4)});
perfModel->IF_substage_0.set(n_IF_substage_0);
// ICache
uint64_t n_ICache;
n_ICache = n_IF_substage_0 + perfModel->iCacheModel.getDelay();
perfModel->iCacheModel.setIc_in(n_ICache);
// uA_PcPredict
uint64_t n_uA_PcPredict;
n_uA_PcPredict = std::max({n_IF_substage_0, perfModel->dynBranchPredModel.getPc_pt()});
// IF_substage_1
uint64_t n_IF_substage_1;
n_IF_substage_1 = std::max({n_ICache, n_uA_PcPredict, perfModel->IF_substage_1.get(1), perfModel->IF_substage_2.get(4)});
perfModel->IF_substage_1.set(n_IF_substage_1);
// IScan
uint64_t n_IScan;
n_IScan = n_IF_substage_1 + 1;
// IF_stage
uint64_t n_IF_stage;
n_IF_stage = std::max({n_IScan, perfModel->IF_stage.get(1), perfModel->IF_substage_2.get(1), perfModel->DEC_stage.get(4)});
perfModel->IF_stage.set(n_IF_stage);
perfModel->IF_substage_2.set(n_IF_stage);
// Decoder
uint64_t n_Decoder;
n_Decoder = n_IF_stage + 1;
// DEC_stage
uint64_t n_DEC_stage;
n_DEC_stage = std::max({n_Decoder, perfModel->DEC_stage.get(1), perfModel->RN_stage.get(5)});
perfModel->DEC_stage.set(n_DEC_stage);
// Rename
uint64_t n_Rename;
n_Rename = n_DEC_stage + 1;
// RN_stage
uint64_t n_RN_stage;
n_RN_stage = std::max({n_Rename, perfModel->RN_stage.get(1), perfModel->OoO_stage.get(64), perfModel->IS_substage_alu.get(24)});
perfModel->RN_stage.set(n_RN_stage);
// Issue
uint64_t n_Issue;
n_Issue = n_RN_stage + 2;
// IS_substage_alu
uint64_t n_IS_substage_alu;
n_IS_substage_alu = std::max({n_Issue, perfModel->IS_substage_alu.get(1), perfModel->LD_substage_alu.get(3)});
perfModel->IS_substage_alu.set(n_IS_substage_alu);
// OperandLookup
uint64_t n_OperandLookup;
n_OperandLookup = n_IS_substage_alu + 1;
// LD_substage_alu
uint64_t n_LD_substage_alu;
n_LD_substage_alu = std::max({n_OperandLookup, perfModel->LD_substage_alu.get(1), perfModel->EX_stage_alu.get(9), perfModel->EX_substage_csr});
perfModel->LD_substage_alu.set(n_LD_substage_alu);
// CSR
uint64_t n_CSR;
n_CSR = n_LD_substage_alu + 1;
perfModel->regModel.setXd(n_CSR);
// EX_stage_alu
uint64_t n_EX_stage_alu;
n_EX_stage_alu = std::max({n_CSR, perfModel->EX_stage_alu.get(1)});
perfModel->EX_stage_alu.set(n_EX_stage_alu);
perfModel->EX_substage_csr = n_EX_stage_alu;
// OoO_stage
uint64_t n_OoO_stage;
n_OoO_stage = std::max({n_EX_stage_alu, perfModel->OoO_stage.get(1), perfModel->COM_stage.get(8)});
perfModel->OoO_stage.set(n_OoO_stage);
// Commit
uint64_t n_Commit;
n_Commit = n_OoO_stage + 2;
// COM_stage
uint64_t n_COM_stage;
n_COM_stage = std::max({n_Commit, perfModel->COM_stage.get(1)});
perfModel->COM_stage.set(n_COM_stage);

  // Dump Entrance point for info print (tracing)
  perfModel->entrancePoint = n_Enter;
  }
);

static SchedulingFunction *schedulingFunction_csrrci = new SchedulingFunction(
  RV32_4ISSUE_SchedulingFunctionSet,
  "csrrci",
  34,
  [](PerformanceModel* perfModel_){
  RV32_4ISSUE_PerformanceModel* perfModel = static_cast<RV32_4ISSUE_PerformanceModel*>(perfModel_);
  // Enter
uint64_t n_Enter;
n_Enter = std::max({perfModel->IF_stage.get(16), perfModel->PC_substage.get(4)});
// PCGen
uint64_t n_PCGen;
n_PCGen = n_Enter + 1;
// uA_PcCorrect
uint64_t n_uA_PcCorrect;
n_uA_PcCorrect = std::max({n_Enter, perfModel->dynBranchPredModel.getPc_mp()});
// uA_CacheBlock
uint64_t n_uA_CacheBlock;
n_uA_CacheBlock = std::max({n_Enter, perfModel->iCacheModel.getIc_out()});
// PC_substage
uint64_t n_PC_substage;
n_PC_substage = std::max({n_PCGen, n_uA_PcCorrect, n_uA_CacheBlock, perfModel->PC_substage.get(1), perfModel->IF_substage_0.get(4)});
perfModel->PC_substage.set(n_PC_substage);
// ICacheCtrl
uint64_t n_ICacheCtrl;
n_ICacheCtrl = n_PC_substage + 1;
// IF_substage_0
uint64_t n_IF_substage_0;
n_IF_substage_0 = std::max({n_ICacheCtrl, perfModel->IF_substage_0.get(1), perfModel->IF_substage_1.get(4)});
perfModel->IF_substage_0.set(n_IF_substage_0);
// ICache
uint64_t n_ICache;
n_ICache = n_IF_substage_0 + perfModel->iCacheModel.getDelay();
perfModel->iCacheModel.setIc_in(n_ICache);
// uA_PcPredict
uint64_t n_uA_PcPredict;
n_uA_PcPredict = std::max({n_IF_substage_0, perfModel->dynBranchPredModel.getPc_pt()});
// IF_substage_1
uint64_t n_IF_substage_1;
n_IF_substage_1 = std::max({n_ICache, n_uA_PcPredict, perfModel->IF_substage_1.get(1), perfModel->IF_substage_2.get(4)});
perfModel->IF_substage_1.set(n_IF_substage_1);
// IScan
uint64_t n_IScan;
n_IScan = n_IF_substage_1 + 1;
// IF_stage
uint64_t n_IF_stage;
n_IF_stage = std::max({n_IScan, perfModel->IF_stage.get(1), perfModel->IF_substage_2.get(1), perfModel->DEC_stage.get(4)});
perfModel->IF_stage.set(n_IF_stage);
perfModel->IF_substage_2.set(n_IF_stage);
// Decoder
uint64_t n_Decoder;
n_Decoder = n_IF_stage + 1;
// DEC_stage
uint64_t n_DEC_stage;
n_DEC_stage = std::max({n_Decoder, perfModel->DEC_stage.get(1), perfModel->RN_stage.get(5)});
perfModel->DEC_stage.set(n_DEC_stage);
// Rename
uint64_t n_Rename;
n_Rename = n_DEC_stage + 1;
// RN_stage
uint64_t n_RN_stage;
n_RN_stage = std::max({n_Rename, perfModel->RN_stage.get(1), perfModel->OoO_stage.get(64), perfModel->IS_substage_alu.get(24)});
perfModel->RN_stage.set(n_RN_stage);
// Issue
uint64_t n_Issue;
n_Issue = n_RN_stage + 2;
// IS_substage_alu
uint64_t n_IS_substage_alu;
n_IS_substage_alu = std::max({n_Issue, perfModel->IS_substage_alu.get(1), perfModel->LD_substage_alu.get(3)});
perfModel->IS_substage_alu.set(n_IS_substage_alu);
// OperandLookup
uint64_t n_OperandLookup;
n_OperandLookup = n_IS_substage_alu + 1;
// LD_substage_alu
uint64_t n_LD_substage_alu;
n_LD_substage_alu = std::max({n_OperandLookup, perfModel->LD_substage_alu.get(1), perfModel->EX_stage_alu.get(9), perfModel->EX_substage_csr});
perfModel->LD_substage_alu.set(n_LD_substage_alu);
// CSR
uint64_t n_CSR;
n_CSR = n_LD_substage_alu + 1;
perfModel->regModel.setXd(n_CSR);
// EX_stage_alu
uint64_t n_EX_stage_alu;
n_EX_stage_alu = std::max({n_CSR, perfModel->EX_stage_alu.get(1)});
perfModel->EX_stage_alu.set(n_EX_stage_alu);
perfModel->EX_substage_csr = n_EX_stage_alu;
// OoO_stage
uint64_t n_OoO_stage;
n_OoO_stage = std::max({n_EX_stage_alu, perfModel->OoO_stage.get(1), perfModel->COM_stage.get(8)});
perfModel->OoO_stage.set(n_OoO_stage);
// Commit
uint64_t n_Commit;
n_Commit = n_OoO_stage + 2;
// COM_stage
uint64_t n_COM_stage;
n_COM_stage = std::max({n_Commit, perfModel->COM_stage.get(1)});
perfModel->COM_stage.set(n_COM_stage);

  // Dump Entrance point for info print (tracing)
  perfModel->entrancePoint = n_Enter;
  }
);

static SchedulingFunction *schedulingFunction_sb = new SchedulingFunction(
  RV32_4ISSUE_SchedulingFunctionSet,
  "sb",
  35,
  [](PerformanceModel* perfModel_){
  RV32_4ISSUE_PerformanceModel* perfModel = static_cast<RV32_4ISSUE_PerformanceModel*>(perfModel_);
  // Enter
uint64_t n_Enter;
n_Enter = std::max({perfModel->IF_stage.get(16), perfModel->PC_substage.get(4)});
// PCGen
uint64_t n_PCGen;
n_PCGen = n_Enter + 1;
// uA_PcCorrect
uint64_t n_uA_PcCorrect;
n_uA_PcCorrect = std::max({n_Enter, perfModel->dynBranchPredModel.getPc_mp()});
// uA_CacheBlock
uint64_t n_uA_CacheBlock;
n_uA_CacheBlock = std::max({n_Enter, perfModel->iCacheModel.getIc_out()});
// PC_substage
uint64_t n_PC_substage;
n_PC_substage = std::max({n_PCGen, n_uA_PcCorrect, n_uA_CacheBlock, perfModel->PC_substage.get(1), perfModel->IF_substage_0.get(4)});
perfModel->PC_substage.set(n_PC_substage);
// ICacheCtrl
uint64_t n_ICacheCtrl;
n_ICacheCtrl = n_PC_substage + 1;
// IF_substage_0
uint64_t n_IF_substage_0;
n_IF_substage_0 = std::max({n_ICacheCtrl, perfModel->IF_substage_0.get(1), perfModel->IF_substage_1.get(4)});
perfModel->IF_substage_0.set(n_IF_substage_0);
// ICache
uint64_t n_ICache;
n_ICache = n_IF_substage_0 + perfModel->iCacheModel.getDelay();
perfModel->iCacheModel.setIc_in(n_ICache);
// uA_PcPredict
uint64_t n_uA_PcPredict;
n_uA_PcPredict = std::max({n_IF_substage_0, perfModel->dynBranchPredModel.getPc_pt()});
// IF_substage_1
uint64_t n_IF_substage_1;
n_IF_substage_1 = std::max({n_ICache, n_uA_PcPredict, perfModel->IF_substage_1.get(1), perfModel->IF_substage_2.get(4)});
perfModel->IF_substage_1.set(n_IF_substage_1);
// IScan
uint64_t n_IScan;
n_IScan = n_IF_substage_1 + 1;
// IF_stage
uint64_t n_IF_stage;
n_IF_stage = std::max({n_IScan, perfModel->IF_stage.get(1), perfModel->IF_substage_2.get(1), perfModel->DEC_stage.get(4)});
perfModel->IF_stage.set(n_IF_stage);
perfModel->IF_substage_2.set(n_IF_stage);
// Decoder
uint64_t n_Decoder;
n_Decoder = n_IF_stage + 1;
// DEC_stage
uint64_t n_DEC_stage;
n_DEC_stage = std::max({n_Decoder, perfModel->DEC_stage.get(1), perfModel->RN_stage.get(5)});
perfModel->DEC_stage.set(n_DEC_stage);
// Rename
uint64_t n_Rename;
n_Rename = n_DEC_stage + 1;
// RN_stage
uint64_t n_RN_stage;
n_RN_stage = std::max({n_Rename, perfModel->RN_stage.get(1), perfModel->OoO_stage.get(64), perfModel->IS_substage_store.get(16)});
perfModel->RN_stage.set(n_RN_stage);
// Issue
uint64_t n_Issue;
n_Issue = n_RN_stage + 2;
// IS_substage_store
uint64_t n_IS_substage_store;
n_IS_substage_store = std::max({n_Issue, perfModel->IS_substage_store.get(1), perfModel->LD_substage_store.get(2)});
perfModel->IS_substage_store.set(n_IS_substage_store);
// OperandLookup
uint64_t n_OperandLookup;
n_OperandLookup = n_IS_substage_store + 1;
// uA_OF_A_store
uint64_t n_uA_OF_A_store;
n_uA_OF_A_store = std::max({n_IS_substage_store, perfModel->regModel.getXa()});
// uA_OF_B_store
uint64_t n_uA_OF_B_store;
n_uA_OF_B_store = std::max({n_IS_substage_store, perfModel->regModel.getXb()});
// LD_substage_store
uint64_t n_LD_substage_store;
n_LD_substage_store = std::max({n_OperandLookup, n_uA_OF_A_store, n_uA_OF_B_store, perfModel->LD_substage_store.get(1), perfModel->EX_stage_store.get(2), perfModel->EX_substage_store.get(2)});
perfModel->LD_substage_store.set(n_LD_substage_store);
// STORE
uint64_t n_STORE;
n_STORE = n_LD_substage_store + 1;
perfModel->dCacheModel.setDc_in(n_STORE);
// EX_stage_store
uint64_t n_EX_stage_store;
n_EX_stage_store = std::max({n_STORE, perfModel->EX_stage_store.get(1), perfModel->EX_substage_store.get(1)});
perfModel->EX_stage_store.set(n_EX_stage_store);
perfModel->EX_substage_store.set(n_EX_stage_store);
// OoO_stage
uint64_t n_OoO_stage;
n_OoO_stage = std::max({n_EX_stage_store, perfModel->OoO_stage.get(1), perfModel->COM_stage.get(8)});
perfModel->OoO_stage.set(n_OoO_stage);
// Commit
uint64_t n_Commit;
n_Commit = n_OoO_stage + 2;
// DCache_Store
uint64_t n_DCache_Store;
n_DCache_Store = n_OoO_stage + 3;
// COM_stage
uint64_t n_COM_stage;
n_COM_stage = std::max({n_Commit, n_DCache_Store, perfModel->COM_stage.get(1)});
perfModel->COM_stage.set(n_COM_stage);

  // Dump Entrance point for info print (tracing)
  perfModel->entrancePoint = n_Enter;
  }
);

static SchedulingFunction *schedulingFunction_sh = new SchedulingFunction(
  RV32_4ISSUE_SchedulingFunctionSet,
  "sh",
  36,
  [](PerformanceModel* perfModel_){
  RV32_4ISSUE_PerformanceModel* perfModel = static_cast<RV32_4ISSUE_PerformanceModel*>(perfModel_);
  // Enter
uint64_t n_Enter;
n_Enter = std::max({perfModel->IF_stage.get(16), perfModel->PC_substage.get(4)});
// PCGen
uint64_t n_PCGen;
n_PCGen = n_Enter + 1;
// uA_PcCorrect
uint64_t n_uA_PcCorrect;
n_uA_PcCorrect = std::max({n_Enter, perfModel->dynBranchPredModel.getPc_mp()});
// uA_CacheBlock
uint64_t n_uA_CacheBlock;
n_uA_CacheBlock = std::max({n_Enter, perfModel->iCacheModel.getIc_out()});
// PC_substage
uint64_t n_PC_substage;
n_PC_substage = std::max({n_PCGen, n_uA_PcCorrect, n_uA_CacheBlock, perfModel->PC_substage.get(1), perfModel->IF_substage_0.get(4)});
perfModel->PC_substage.set(n_PC_substage);
// ICacheCtrl
uint64_t n_ICacheCtrl;
n_ICacheCtrl = n_PC_substage + 1;
// IF_substage_0
uint64_t n_IF_substage_0;
n_IF_substage_0 = std::max({n_ICacheCtrl, perfModel->IF_substage_0.get(1), perfModel->IF_substage_1.get(4)});
perfModel->IF_substage_0.set(n_IF_substage_0);
// ICache
uint64_t n_ICache;
n_ICache = n_IF_substage_0 + perfModel->iCacheModel.getDelay();
perfModel->iCacheModel.setIc_in(n_ICache);
// uA_PcPredict
uint64_t n_uA_PcPredict;
n_uA_PcPredict = std::max({n_IF_substage_0, perfModel->dynBranchPredModel.getPc_pt()});
// IF_substage_1
uint64_t n_IF_substage_1;
n_IF_substage_1 = std::max({n_ICache, n_uA_PcPredict, perfModel->IF_substage_1.get(1), perfModel->IF_substage_2.get(4)});
perfModel->IF_substage_1.set(n_IF_substage_1);
// IScan
uint64_t n_IScan;
n_IScan = n_IF_substage_1 + 1;
// IF_stage
uint64_t n_IF_stage;
n_IF_stage = std::max({n_IScan, perfModel->IF_stage.get(1), perfModel->IF_substage_2.get(1), perfModel->DEC_stage.get(4)});
perfModel->IF_stage.set(n_IF_stage);
perfModel->IF_substage_2.set(n_IF_stage);
// Decoder
uint64_t n_Decoder;
n_Decoder = n_IF_stage + 1;
// DEC_stage
uint64_t n_DEC_stage;
n_DEC_stage = std::max({n_Decoder, perfModel->DEC_stage.get(1), perfModel->RN_stage.get(5)});
perfModel->DEC_stage.set(n_DEC_stage);
// Rename
uint64_t n_Rename;
n_Rename = n_DEC_stage + 1;
// RN_stage
uint64_t n_RN_stage;
n_RN_stage = std::max({n_Rename, perfModel->RN_stage.get(1), perfModel->OoO_stage.get(64), perfModel->IS_substage_store.get(16)});
perfModel->RN_stage.set(n_RN_stage);
// Issue
uint64_t n_Issue;
n_Issue = n_RN_stage + 2;
// IS_substage_store
uint64_t n_IS_substage_store;
n_IS_substage_store = std::max({n_Issue, perfModel->IS_substage_store.get(1), perfModel->LD_substage_store.get(2)});
perfModel->IS_substage_store.set(n_IS_substage_store);
// OperandLookup
uint64_t n_OperandLookup;
n_OperandLookup = n_IS_substage_store + 1;
// uA_OF_A_store
uint64_t n_uA_OF_A_store;
n_uA_OF_A_store = std::max({n_IS_substage_store, perfModel->regModel.getXa()});
// uA_OF_B_store
uint64_t n_uA_OF_B_store;
n_uA_OF_B_store = std::max({n_IS_substage_store, perfModel->regModel.getXb()});
// LD_substage_store
uint64_t n_LD_substage_store;
n_LD_substage_store = std::max({n_OperandLookup, n_uA_OF_A_store, n_uA_OF_B_store, perfModel->LD_substage_store.get(1), perfModel->EX_stage_store.get(2), perfModel->EX_substage_store.get(2)});
perfModel->LD_substage_store.set(n_LD_substage_store);
// STORE
uint64_t n_STORE;
n_STORE = n_LD_substage_store + 1;
perfModel->dCacheModel.setDc_in(n_STORE);
// EX_stage_store
uint64_t n_EX_stage_store;
n_EX_stage_store = std::max({n_STORE, perfModel->EX_stage_store.get(1), perfModel->EX_substage_store.get(1)});
perfModel->EX_stage_store.set(n_EX_stage_store);
perfModel->EX_substage_store.set(n_EX_stage_store);
// OoO_stage
uint64_t n_OoO_stage;
n_OoO_stage = std::max({n_EX_stage_store, perfModel->OoO_stage.get(1), perfModel->COM_stage.get(8)});
perfModel->OoO_stage.set(n_OoO_stage);
// Commit
uint64_t n_Commit;
n_Commit = n_OoO_stage + 2;
// DCache_Store
uint64_t n_DCache_Store;
n_DCache_Store = n_OoO_stage + 3;
// COM_stage
uint64_t n_COM_stage;
n_COM_stage = std::max({n_Commit, n_DCache_Store, perfModel->COM_stage.get(1)});
perfModel->COM_stage.set(n_COM_stage);

  // Dump Entrance point for info print (tracing)
  perfModel->entrancePoint = n_Enter;
  }
);

static SchedulingFunction *schedulingFunction_sw = new SchedulingFunction(
  RV32_4ISSUE_SchedulingFunctionSet,
  "sw",
  37,
  [](PerformanceModel* perfModel_){
  RV32_4ISSUE_PerformanceModel* perfModel = static_cast<RV32_4ISSUE_PerformanceModel*>(perfModel_);
  // Enter
uint64_t n_Enter;
n_Enter = std::max({perfModel->IF_stage.get(16), perfModel->PC_substage.get(4)});
// PCGen
uint64_t n_PCGen;
n_PCGen = n_Enter + 1;
// uA_PcCorrect
uint64_t n_uA_PcCorrect;
n_uA_PcCorrect = std::max({n_Enter, perfModel->dynBranchPredModel.getPc_mp()});
// uA_CacheBlock
uint64_t n_uA_CacheBlock;
n_uA_CacheBlock = std::max({n_Enter, perfModel->iCacheModel.getIc_out()});
// PC_substage
uint64_t n_PC_substage;
n_PC_substage = std::max({n_PCGen, n_uA_PcCorrect, n_uA_CacheBlock, perfModel->PC_substage.get(1), perfModel->IF_substage_0.get(4)});
perfModel->PC_substage.set(n_PC_substage);
// ICacheCtrl
uint64_t n_ICacheCtrl;
n_ICacheCtrl = n_PC_substage + 1;
// IF_substage_0
uint64_t n_IF_substage_0;
n_IF_substage_0 = std::max({n_ICacheCtrl, perfModel->IF_substage_0.get(1), perfModel->IF_substage_1.get(4)});
perfModel->IF_substage_0.set(n_IF_substage_0);
// ICache
uint64_t n_ICache;
n_ICache = n_IF_substage_0 + perfModel->iCacheModel.getDelay();
perfModel->iCacheModel.setIc_in(n_ICache);
// uA_PcPredict
uint64_t n_uA_PcPredict;
n_uA_PcPredict = std::max({n_IF_substage_0, perfModel->dynBranchPredModel.getPc_pt()});
// IF_substage_1
uint64_t n_IF_substage_1;
n_IF_substage_1 = std::max({n_ICache, n_uA_PcPredict, perfModel->IF_substage_1.get(1), perfModel->IF_substage_2.get(4)});
perfModel->IF_substage_1.set(n_IF_substage_1);
// IScan
uint64_t n_IScan;
n_IScan = n_IF_substage_1 + 1;
// IF_stage
uint64_t n_IF_stage;
n_IF_stage = std::max({n_IScan, perfModel->IF_stage.get(1), perfModel->IF_substage_2.get(1), perfModel->DEC_stage.get(4)});
perfModel->IF_stage.set(n_IF_stage);
perfModel->IF_substage_2.set(n_IF_stage);
// Decoder
uint64_t n_Decoder;
n_Decoder = n_IF_stage + 1;
// DEC_stage
uint64_t n_DEC_stage;
n_DEC_stage = std::max({n_Decoder, perfModel->DEC_stage.get(1), perfModel->RN_stage.get(5)});
perfModel->DEC_stage.set(n_DEC_stage);
// Rename
uint64_t n_Rename;
n_Rename = n_DEC_stage + 1;
// RN_stage
uint64_t n_RN_stage;
n_RN_stage = std::max({n_Rename, perfModel->RN_stage.get(1), perfModel->OoO_stage.get(64), perfModel->IS_substage_store.get(16)});
perfModel->RN_stage.set(n_RN_stage);
// Issue
uint64_t n_Issue;
n_Issue = n_RN_stage + 2;
// IS_substage_store
uint64_t n_IS_substage_store;
n_IS_substage_store = std::max({n_Issue, perfModel->IS_substage_store.get(1), perfModel->LD_substage_store.get(2)});
perfModel->IS_substage_store.set(n_IS_substage_store);
// OperandLookup
uint64_t n_OperandLookup;
n_OperandLookup = n_IS_substage_store + 1;
// uA_OF_A_store
uint64_t n_uA_OF_A_store;
n_uA_OF_A_store = std::max({n_IS_substage_store, perfModel->regModel.getXa()});
// uA_OF_B_store
uint64_t n_uA_OF_B_store;
n_uA_OF_B_store = std::max({n_IS_substage_store, perfModel->regModel.getXb()});
// LD_substage_store
uint64_t n_LD_substage_store;
n_LD_substage_store = std::max({n_OperandLookup, n_uA_OF_A_store, n_uA_OF_B_store, perfModel->LD_substage_store.get(1), perfModel->EX_stage_store.get(2), perfModel->EX_substage_store.get(2)});
perfModel->LD_substage_store.set(n_LD_substage_store);
// STORE
uint64_t n_STORE;
n_STORE = n_LD_substage_store + 1;
perfModel->dCacheModel.setDc_in(n_STORE);
// EX_stage_store
uint64_t n_EX_stage_store;
n_EX_stage_store = std::max({n_STORE, perfModel->EX_stage_store.get(1), perfModel->EX_substage_store.get(1)});
perfModel->EX_stage_store.set(n_EX_stage_store);
perfModel->EX_substage_store.set(n_EX_stage_store);
// OoO_stage
uint64_t n_OoO_stage;
n_OoO_stage = std::max({n_EX_stage_store, perfModel->OoO_stage.get(1), perfModel->COM_stage.get(8)});
perfModel->OoO_stage.set(n_OoO_stage);
// Commit
uint64_t n_Commit;
n_Commit = n_OoO_stage + 2;
// DCache_Store
uint64_t n_DCache_Store;
n_DCache_Store = n_OoO_stage + 3;
// COM_stage
uint64_t n_COM_stage;
n_COM_stage = std::max({n_Commit, n_DCache_Store, perfModel->COM_stage.get(1)});
perfModel->COM_stage.set(n_COM_stage);

  // Dump Entrance point for info print (tracing)
  perfModel->entrancePoint = n_Enter;
  }
);

static SchedulingFunction *schedulingFunction_lw = new SchedulingFunction(
  RV32_4ISSUE_SchedulingFunctionSet,
  "lw",
  38,
  [](PerformanceModel* perfModel_){
  RV32_4ISSUE_PerformanceModel* perfModel = static_cast<RV32_4ISSUE_PerformanceModel*>(perfModel_);
  // Enter
uint64_t n_Enter;
n_Enter = std::max({perfModel->IF_stage.get(16), perfModel->PC_substage.get(4)});
// PCGen
uint64_t n_PCGen;
n_PCGen = n_Enter + 1;
// uA_PcCorrect
uint64_t n_uA_PcCorrect;
n_uA_PcCorrect = std::max({n_Enter, perfModel->dynBranchPredModel.getPc_mp()});
// uA_CacheBlock
uint64_t n_uA_CacheBlock;
n_uA_CacheBlock = std::max({n_Enter, perfModel->iCacheModel.getIc_out()});
// PC_substage
uint64_t n_PC_substage;
n_PC_substage = std::max({n_PCGen, n_uA_PcCorrect, n_uA_CacheBlock, perfModel->PC_substage.get(1), perfModel->IF_substage_0.get(4)});
perfModel->PC_substage.set(n_PC_substage);
// ICacheCtrl
uint64_t n_ICacheCtrl;
n_ICacheCtrl = n_PC_substage + 1;
// IF_substage_0
uint64_t n_IF_substage_0;
n_IF_substage_0 = std::max({n_ICacheCtrl, perfModel->IF_substage_0.get(1), perfModel->IF_substage_1.get(4)});
perfModel->IF_substage_0.set(n_IF_substage_0);
// ICache
uint64_t n_ICache;
n_ICache = n_IF_substage_0 + perfModel->iCacheModel.getDelay();
perfModel->iCacheModel.setIc_in(n_ICache);
// uA_PcPredict
uint64_t n_uA_PcPredict;
n_uA_PcPredict = std::max({n_IF_substage_0, perfModel->dynBranchPredModel.getPc_pt()});
// IF_substage_1
uint64_t n_IF_substage_1;
n_IF_substage_1 = std::max({n_ICache, n_uA_PcPredict, perfModel->IF_substage_1.get(1), perfModel->IF_substage_2.get(4)});
perfModel->IF_substage_1.set(n_IF_substage_1);
// IScan
uint64_t n_IScan;
n_IScan = n_IF_substage_1 + 1;
// IF_stage
uint64_t n_IF_stage;
n_IF_stage = std::max({n_IScan, perfModel->IF_stage.get(1), perfModel->IF_substage_2.get(1), perfModel->DEC_stage.get(4)});
perfModel->IF_stage.set(n_IF_stage);
perfModel->IF_substage_2.set(n_IF_stage);
// Decoder
uint64_t n_Decoder;
n_Decoder = n_IF_stage + 1;
// DEC_stage
uint64_t n_DEC_stage;
n_DEC_stage = std::max({n_Decoder, perfModel->DEC_stage.get(1), perfModel->RN_stage.get(5)});
perfModel->DEC_stage.set(n_DEC_stage);
// Rename
uint64_t n_Rename;
n_Rename = n_DEC_stage + 1;
// RN_stage
uint64_t n_RN_stage;
n_RN_stage = std::max({n_Rename, perfModel->RN_stage.get(1), perfModel->OoO_stage.get(64), perfModel->IS_substage_agu.get(16)});
perfModel->RN_stage.set(n_RN_stage);
// Issue
uint64_t n_Issue;
n_Issue = n_RN_stage + 2;
// IS_substage_agu
uint64_t n_IS_substage_agu;
n_IS_substage_agu = std::max({n_Issue, perfModel->IS_substage_agu.get(1), perfModel->LD_substage_agu.get(2)});
perfModel->IS_substage_agu.set(n_IS_substage_agu);
// OperandLookup
uint64_t n_OperandLookup;
n_OperandLookup = n_IS_substage_agu + 1;
// uA_OF_A_agu
uint64_t n_uA_OF_A_agu;
n_uA_OF_A_agu = std::max({n_IS_substage_agu, perfModel->regModel.getXa()});
// LD_substage_agu
uint64_t n_LD_substage_agu;
n_LD_substage_agu = std::max({n_OperandLookup, n_uA_OF_A_agu, perfModel->LD_substage_agu.get(1), perfModel->EX_stage_agu.get(2), perfModel->EX_substage_agu.get(2)});
perfModel->LD_substage_agu.set(n_LD_substage_agu);
// LOAD
uint64_t n_LOAD;
n_LOAD = n_LD_substage_agu + 1;
// DCache
uint64_t n_DCache;
n_DCache = n_LD_substage_agu + perfModel->dCacheModel.getDelay();
perfModel->regModel.setXd(n_DCache);
// EX_stage_agu
uint64_t n_EX_stage_agu;
n_EX_stage_agu = std::max({n_LOAD, n_DCache, perfModel->EX_stage_agu.get(1), perfModel->EX_substage_agu.get(1)});
perfModel->EX_stage_agu.set(n_EX_stage_agu);
perfModel->EX_substage_agu.set(n_EX_stage_agu);
// EX_substage_agu
uint64_t n_EX_substage_agu;
n_EX_substage_agu = std::max({n_DCache, perfModel->EX_substage_agu.get(1)});
perfModel->EX_substage_agu.set(n_EX_substage_agu);
// OoO_stage
uint64_t n_OoO_stage;
n_OoO_stage = std::max({n_EX_stage_agu, perfModel->OoO_stage.get(1), perfModel->COM_stage.get(8)});
perfModel->OoO_stage.set(n_OoO_stage);
// Commit
uint64_t n_Commit;
n_Commit = n_OoO_stage + 2;
// COM_stage
uint64_t n_COM_stage;
n_COM_stage = std::max({n_Commit, perfModel->COM_stage.get(1)});
perfModel->COM_stage.set(n_COM_stage);

  // Dump Entrance point for info print (tracing)
  perfModel->entrancePoint = n_Enter;
  }
);

static SchedulingFunction *schedulingFunction_lh = new SchedulingFunction(
  RV32_4ISSUE_SchedulingFunctionSet,
  "lh",
  39,
  [](PerformanceModel* perfModel_){
  RV32_4ISSUE_PerformanceModel* perfModel = static_cast<RV32_4ISSUE_PerformanceModel*>(perfModel_);
  // Enter
uint64_t n_Enter;
n_Enter = std::max({perfModel->IF_stage.get(16), perfModel->PC_substage.get(4)});
// PCGen
uint64_t n_PCGen;
n_PCGen = n_Enter + 1;
// uA_PcCorrect
uint64_t n_uA_PcCorrect;
n_uA_PcCorrect = std::max({n_Enter, perfModel->dynBranchPredModel.getPc_mp()});
// uA_CacheBlock
uint64_t n_uA_CacheBlock;
n_uA_CacheBlock = std::max({n_Enter, perfModel->iCacheModel.getIc_out()});
// PC_substage
uint64_t n_PC_substage;
n_PC_substage = std::max({n_PCGen, n_uA_PcCorrect, n_uA_CacheBlock, perfModel->PC_substage.get(1), perfModel->IF_substage_0.get(4)});
perfModel->PC_substage.set(n_PC_substage);
// ICacheCtrl
uint64_t n_ICacheCtrl;
n_ICacheCtrl = n_PC_substage + 1;
// IF_substage_0
uint64_t n_IF_substage_0;
n_IF_substage_0 = std::max({n_ICacheCtrl, perfModel->IF_substage_0.get(1), perfModel->IF_substage_1.get(4)});
perfModel->IF_substage_0.set(n_IF_substage_0);
// ICache
uint64_t n_ICache;
n_ICache = n_IF_substage_0 + perfModel->iCacheModel.getDelay();
perfModel->iCacheModel.setIc_in(n_ICache);
// uA_PcPredict
uint64_t n_uA_PcPredict;
n_uA_PcPredict = std::max({n_IF_substage_0, perfModel->dynBranchPredModel.getPc_pt()});
// IF_substage_1
uint64_t n_IF_substage_1;
n_IF_substage_1 = std::max({n_ICache, n_uA_PcPredict, perfModel->IF_substage_1.get(1), perfModel->IF_substage_2.get(4)});
perfModel->IF_substage_1.set(n_IF_substage_1);
// IScan
uint64_t n_IScan;
n_IScan = n_IF_substage_1 + 1;
// IF_stage
uint64_t n_IF_stage;
n_IF_stage = std::max({n_IScan, perfModel->IF_stage.get(1), perfModel->IF_substage_2.get(1), perfModel->DEC_stage.get(4)});
perfModel->IF_stage.set(n_IF_stage);
perfModel->IF_substage_2.set(n_IF_stage);
// Decoder
uint64_t n_Decoder;
n_Decoder = n_IF_stage + 1;
// DEC_stage
uint64_t n_DEC_stage;
n_DEC_stage = std::max({n_Decoder, perfModel->DEC_stage.get(1), perfModel->RN_stage.get(5)});
perfModel->DEC_stage.set(n_DEC_stage);
// Rename
uint64_t n_Rename;
n_Rename = n_DEC_stage + 1;
// RN_stage
uint64_t n_RN_stage;
n_RN_stage = std::max({n_Rename, perfModel->RN_stage.get(1), perfModel->OoO_stage.get(64), perfModel->IS_substage_agu.get(16)});
perfModel->RN_stage.set(n_RN_stage);
// Issue
uint64_t n_Issue;
n_Issue = n_RN_stage + 2;
// IS_substage_agu
uint64_t n_IS_substage_agu;
n_IS_substage_agu = std::max({n_Issue, perfModel->IS_substage_agu.get(1), perfModel->LD_substage_agu.get(2)});
perfModel->IS_substage_agu.set(n_IS_substage_agu);
// OperandLookup
uint64_t n_OperandLookup;
n_OperandLookup = n_IS_substage_agu + 1;
// uA_OF_A_agu
uint64_t n_uA_OF_A_agu;
n_uA_OF_A_agu = std::max({n_IS_substage_agu, perfModel->regModel.getXa()});
// LD_substage_agu
uint64_t n_LD_substage_agu;
n_LD_substage_agu = std::max({n_OperandLookup, n_uA_OF_A_agu, perfModel->LD_substage_agu.get(1), perfModel->EX_stage_agu.get(2), perfModel->EX_substage_agu.get(2)});
perfModel->LD_substage_agu.set(n_LD_substage_agu);
// LOAD
uint64_t n_LOAD;
n_LOAD = n_LD_substage_agu + 1;
// DCache
uint64_t n_DCache;
n_DCache = n_LD_substage_agu + perfModel->dCacheModel.getDelay();
perfModel->regModel.setXd(n_DCache);
// EX_stage_agu
uint64_t n_EX_stage_agu;
n_EX_stage_agu = std::max({n_LOAD, n_DCache, perfModel->EX_stage_agu.get(1), perfModel->EX_substage_agu.get(1)});
perfModel->EX_stage_agu.set(n_EX_stage_agu);
perfModel->EX_substage_agu.set(n_EX_stage_agu);
// EX_substage_agu
uint64_t n_EX_substage_agu;
n_EX_substage_agu = std::max({n_DCache, perfModel->EX_substage_agu.get(1)});
perfModel->EX_substage_agu.set(n_EX_substage_agu);
// OoO_stage
uint64_t n_OoO_stage;
n_OoO_stage = std::max({n_EX_stage_agu, perfModel->OoO_stage.get(1), perfModel->COM_stage.get(8)});
perfModel->OoO_stage.set(n_OoO_stage);
// Commit
uint64_t n_Commit;
n_Commit = n_OoO_stage + 2;
// COM_stage
uint64_t n_COM_stage;
n_COM_stage = std::max({n_Commit, perfModel->COM_stage.get(1)});
perfModel->COM_stage.set(n_COM_stage);

  // Dump Entrance point for info print (tracing)
  perfModel->entrancePoint = n_Enter;
  }
);

static SchedulingFunction *schedulingFunction_lhu = new SchedulingFunction(
  RV32_4ISSUE_SchedulingFunctionSet,
  "lhu",
  40,
  [](PerformanceModel* perfModel_){
  RV32_4ISSUE_PerformanceModel* perfModel = static_cast<RV32_4ISSUE_PerformanceModel*>(perfModel_);
  // Enter
uint64_t n_Enter;
n_Enter = std::max({perfModel->IF_stage.get(16), perfModel->PC_substage.get(4)});
// PCGen
uint64_t n_PCGen;
n_PCGen = n_Enter + 1;
// uA_PcCorrect
uint64_t n_uA_PcCorrect;
n_uA_PcCorrect = std::max({n_Enter, perfModel->dynBranchPredModel.getPc_mp()});
// uA_CacheBlock
uint64_t n_uA_CacheBlock;
n_uA_CacheBlock = std::max({n_Enter, perfModel->iCacheModel.getIc_out()});
// PC_substage
uint64_t n_PC_substage;
n_PC_substage = std::max({n_PCGen, n_uA_PcCorrect, n_uA_CacheBlock, perfModel->PC_substage.get(1), perfModel->IF_substage_0.get(4)});
perfModel->PC_substage.set(n_PC_substage);
// ICacheCtrl
uint64_t n_ICacheCtrl;
n_ICacheCtrl = n_PC_substage + 1;
// IF_substage_0
uint64_t n_IF_substage_0;
n_IF_substage_0 = std::max({n_ICacheCtrl, perfModel->IF_substage_0.get(1), perfModel->IF_substage_1.get(4)});
perfModel->IF_substage_0.set(n_IF_substage_0);
// ICache
uint64_t n_ICache;
n_ICache = n_IF_substage_0 + perfModel->iCacheModel.getDelay();
perfModel->iCacheModel.setIc_in(n_ICache);
// uA_PcPredict
uint64_t n_uA_PcPredict;
n_uA_PcPredict = std::max({n_IF_substage_0, perfModel->dynBranchPredModel.getPc_pt()});
// IF_substage_1
uint64_t n_IF_substage_1;
n_IF_substage_1 = std::max({n_ICache, n_uA_PcPredict, perfModel->IF_substage_1.get(1), perfModel->IF_substage_2.get(4)});
perfModel->IF_substage_1.set(n_IF_substage_1);
// IScan
uint64_t n_IScan;
n_IScan = n_IF_substage_1 + 1;
// IF_stage
uint64_t n_IF_stage;
n_IF_stage = std::max({n_IScan, perfModel->IF_stage.get(1), perfModel->IF_substage_2.get(1), perfModel->DEC_stage.get(4)});
perfModel->IF_stage.set(n_IF_stage);
perfModel->IF_substage_2.set(n_IF_stage);
// Decoder
uint64_t n_Decoder;
n_Decoder = n_IF_stage + 1;
// DEC_stage
uint64_t n_DEC_stage;
n_DEC_stage = std::max({n_Decoder, perfModel->DEC_stage.get(1), perfModel->RN_stage.get(5)});
perfModel->DEC_stage.set(n_DEC_stage);
// Rename
uint64_t n_Rename;
n_Rename = n_DEC_stage + 1;
// RN_stage
uint64_t n_RN_stage;
n_RN_stage = std::max({n_Rename, perfModel->RN_stage.get(1), perfModel->OoO_stage.get(64), perfModel->IS_substage_agu.get(16)});
perfModel->RN_stage.set(n_RN_stage);
// Issue
uint64_t n_Issue;
n_Issue = n_RN_stage + 2;
// IS_substage_agu
uint64_t n_IS_substage_agu;
n_IS_substage_agu = std::max({n_Issue, perfModel->IS_substage_agu.get(1), perfModel->LD_substage_agu.get(2)});
perfModel->IS_substage_agu.set(n_IS_substage_agu);
// OperandLookup
uint64_t n_OperandLookup;
n_OperandLookup = n_IS_substage_agu + 1;
// uA_OF_A_agu
uint64_t n_uA_OF_A_agu;
n_uA_OF_A_agu = std::max({n_IS_substage_agu, perfModel->regModel.getXa()});
// LD_substage_agu
uint64_t n_LD_substage_agu;
n_LD_substage_agu = std::max({n_OperandLookup, n_uA_OF_A_agu, perfModel->LD_substage_agu.get(1), perfModel->EX_stage_agu.get(2), perfModel->EX_substage_agu.get(2)});
perfModel->LD_substage_agu.set(n_LD_substage_agu);
// LOAD
uint64_t n_LOAD;
n_LOAD = n_LD_substage_agu + 1;
// DCache
uint64_t n_DCache;
n_DCache = n_LD_substage_agu + perfModel->dCacheModel.getDelay();
perfModel->regModel.setXd(n_DCache);
// EX_stage_agu
uint64_t n_EX_stage_agu;
n_EX_stage_agu = std::max({n_LOAD, n_DCache, perfModel->EX_stage_agu.get(1), perfModel->EX_substage_agu.get(1)});
perfModel->EX_stage_agu.set(n_EX_stage_agu);
perfModel->EX_substage_agu.set(n_EX_stage_agu);
// EX_substage_agu
uint64_t n_EX_substage_agu;
n_EX_substage_agu = std::max({n_DCache, perfModel->EX_substage_agu.get(1)});
perfModel->EX_substage_agu.set(n_EX_substage_agu);
// OoO_stage
uint64_t n_OoO_stage;
n_OoO_stage = std::max({n_EX_stage_agu, perfModel->OoO_stage.get(1), perfModel->COM_stage.get(8)});
perfModel->OoO_stage.set(n_OoO_stage);
// Commit
uint64_t n_Commit;
n_Commit = n_OoO_stage + 2;
// COM_stage
uint64_t n_COM_stage;
n_COM_stage = std::max({n_Commit, perfModel->COM_stage.get(1)});
perfModel->COM_stage.set(n_COM_stage);

  // Dump Entrance point for info print (tracing)
  perfModel->entrancePoint = n_Enter;
  }
);

static SchedulingFunction *schedulingFunction_lb = new SchedulingFunction(
  RV32_4ISSUE_SchedulingFunctionSet,
  "lb",
  41,
  [](PerformanceModel* perfModel_){
  RV32_4ISSUE_PerformanceModel* perfModel = static_cast<RV32_4ISSUE_PerformanceModel*>(perfModel_);
  // Enter
uint64_t n_Enter;
n_Enter = std::max({perfModel->IF_stage.get(16), perfModel->PC_substage.get(4)});
// PCGen
uint64_t n_PCGen;
n_PCGen = n_Enter + 1;
// uA_PcCorrect
uint64_t n_uA_PcCorrect;
n_uA_PcCorrect = std::max({n_Enter, perfModel->dynBranchPredModel.getPc_mp()});
// uA_CacheBlock
uint64_t n_uA_CacheBlock;
n_uA_CacheBlock = std::max({n_Enter, perfModel->iCacheModel.getIc_out()});
// PC_substage
uint64_t n_PC_substage;
n_PC_substage = std::max({n_PCGen, n_uA_PcCorrect, n_uA_CacheBlock, perfModel->PC_substage.get(1), perfModel->IF_substage_0.get(4)});
perfModel->PC_substage.set(n_PC_substage);
// ICacheCtrl
uint64_t n_ICacheCtrl;
n_ICacheCtrl = n_PC_substage + 1;
// IF_substage_0
uint64_t n_IF_substage_0;
n_IF_substage_0 = std::max({n_ICacheCtrl, perfModel->IF_substage_0.get(1), perfModel->IF_substage_1.get(4)});
perfModel->IF_substage_0.set(n_IF_substage_0);
// ICache
uint64_t n_ICache;
n_ICache = n_IF_substage_0 + perfModel->iCacheModel.getDelay();
perfModel->iCacheModel.setIc_in(n_ICache);
// uA_PcPredict
uint64_t n_uA_PcPredict;
n_uA_PcPredict = std::max({n_IF_substage_0, perfModel->dynBranchPredModel.getPc_pt()});
// IF_substage_1
uint64_t n_IF_substage_1;
n_IF_substage_1 = std::max({n_ICache, n_uA_PcPredict, perfModel->IF_substage_1.get(1), perfModel->IF_substage_2.get(4)});
perfModel->IF_substage_1.set(n_IF_substage_1);
// IScan
uint64_t n_IScan;
n_IScan = n_IF_substage_1 + 1;
// IF_stage
uint64_t n_IF_stage;
n_IF_stage = std::max({n_IScan, perfModel->IF_stage.get(1), perfModel->IF_substage_2.get(1), perfModel->DEC_stage.get(4)});
perfModel->IF_stage.set(n_IF_stage);
perfModel->IF_substage_2.set(n_IF_stage);
// Decoder
uint64_t n_Decoder;
n_Decoder = n_IF_stage + 1;
// DEC_stage
uint64_t n_DEC_stage;
n_DEC_stage = std::max({n_Decoder, perfModel->DEC_stage.get(1), perfModel->RN_stage.get(5)});
perfModel->DEC_stage.set(n_DEC_stage);
// Rename
uint64_t n_Rename;
n_Rename = n_DEC_stage + 1;
// RN_stage
uint64_t n_RN_stage;
n_RN_stage = std::max({n_Rename, perfModel->RN_stage.get(1), perfModel->OoO_stage.get(64), perfModel->IS_substage_agu.get(16)});
perfModel->RN_stage.set(n_RN_stage);
// Issue
uint64_t n_Issue;
n_Issue = n_RN_stage + 2;
// IS_substage_agu
uint64_t n_IS_substage_agu;
n_IS_substage_agu = std::max({n_Issue, perfModel->IS_substage_agu.get(1), perfModel->LD_substage_agu.get(2)});
perfModel->IS_substage_agu.set(n_IS_substage_agu);
// OperandLookup
uint64_t n_OperandLookup;
n_OperandLookup = n_IS_substage_agu + 1;
// uA_OF_A_agu
uint64_t n_uA_OF_A_agu;
n_uA_OF_A_agu = std::max({n_IS_substage_agu, perfModel->regModel.getXa()});
// LD_substage_agu
uint64_t n_LD_substage_agu;
n_LD_substage_agu = std::max({n_OperandLookup, n_uA_OF_A_agu, perfModel->LD_substage_agu.get(1), perfModel->EX_stage_agu.get(2), perfModel->EX_substage_agu.get(2)});
perfModel->LD_substage_agu.set(n_LD_substage_agu);
// LOAD
uint64_t n_LOAD;
n_LOAD = n_LD_substage_agu + 1;
// DCache
uint64_t n_DCache;
n_DCache = n_LD_substage_agu + perfModel->dCacheModel.getDelay();
perfModel->regModel.setXd(n_DCache);
// EX_stage_agu
uint64_t n_EX_stage_agu;
n_EX_stage_agu = std::max({n_LOAD, n_DCache, perfModel->EX_stage_agu.get(1), perfModel->EX_substage_agu.get(1)});
perfModel->EX_stage_agu.set(n_EX_stage_agu);
perfModel->EX_substage_agu.set(n_EX_stage_agu);
// EX_substage_agu
uint64_t n_EX_substage_agu;
n_EX_substage_agu = std::max({n_DCache, perfModel->EX_substage_agu.get(1)});
perfModel->EX_substage_agu.set(n_EX_substage_agu);
// OoO_stage
uint64_t n_OoO_stage;
n_OoO_stage = std::max({n_EX_stage_agu, perfModel->OoO_stage.get(1), perfModel->COM_stage.get(8)});
perfModel->OoO_stage.set(n_OoO_stage);
// Commit
uint64_t n_Commit;
n_Commit = n_OoO_stage + 2;
// COM_stage
uint64_t n_COM_stage;
n_COM_stage = std::max({n_Commit, perfModel->COM_stage.get(1)});
perfModel->COM_stage.set(n_COM_stage);

  // Dump Entrance point for info print (tracing)
  perfModel->entrancePoint = n_Enter;
  }
);

static SchedulingFunction *schedulingFunction_lbu = new SchedulingFunction(
  RV32_4ISSUE_SchedulingFunctionSet,
  "lbu",
  42,
  [](PerformanceModel* perfModel_){
  RV32_4ISSUE_PerformanceModel* perfModel = static_cast<RV32_4ISSUE_PerformanceModel*>(perfModel_);
  // Enter
uint64_t n_Enter;
n_Enter = std::max({perfModel->IF_stage.get(16), perfModel->PC_substage.get(4)});
// PCGen
uint64_t n_PCGen;
n_PCGen = n_Enter + 1;
// uA_PcCorrect
uint64_t n_uA_PcCorrect;
n_uA_PcCorrect = std::max({n_Enter, perfModel->dynBranchPredModel.getPc_mp()});
// uA_CacheBlock
uint64_t n_uA_CacheBlock;
n_uA_CacheBlock = std::max({n_Enter, perfModel->iCacheModel.getIc_out()});
// PC_substage
uint64_t n_PC_substage;
n_PC_substage = std::max({n_PCGen, n_uA_PcCorrect, n_uA_CacheBlock, perfModel->PC_substage.get(1), perfModel->IF_substage_0.get(4)});
perfModel->PC_substage.set(n_PC_substage);
// ICacheCtrl
uint64_t n_ICacheCtrl;
n_ICacheCtrl = n_PC_substage + 1;
// IF_substage_0
uint64_t n_IF_substage_0;
n_IF_substage_0 = std::max({n_ICacheCtrl, perfModel->IF_substage_0.get(1), perfModel->IF_substage_1.get(4)});
perfModel->IF_substage_0.set(n_IF_substage_0);
// ICache
uint64_t n_ICache;
n_ICache = n_IF_substage_0 + perfModel->iCacheModel.getDelay();
perfModel->iCacheModel.setIc_in(n_ICache);
// uA_PcPredict
uint64_t n_uA_PcPredict;
n_uA_PcPredict = std::max({n_IF_substage_0, perfModel->dynBranchPredModel.getPc_pt()});
// IF_substage_1
uint64_t n_IF_substage_1;
n_IF_substage_1 = std::max({n_ICache, n_uA_PcPredict, perfModel->IF_substage_1.get(1), perfModel->IF_substage_2.get(4)});
perfModel->IF_substage_1.set(n_IF_substage_1);
// IScan
uint64_t n_IScan;
n_IScan = n_IF_substage_1 + 1;
// IF_stage
uint64_t n_IF_stage;
n_IF_stage = std::max({n_IScan, perfModel->IF_stage.get(1), perfModel->IF_substage_2.get(1), perfModel->DEC_stage.get(4)});
perfModel->IF_stage.set(n_IF_stage);
perfModel->IF_substage_2.set(n_IF_stage);
// Decoder
uint64_t n_Decoder;
n_Decoder = n_IF_stage + 1;
// DEC_stage
uint64_t n_DEC_stage;
n_DEC_stage = std::max({n_Decoder, perfModel->DEC_stage.get(1), perfModel->RN_stage.get(5)});
perfModel->DEC_stage.set(n_DEC_stage);
// Rename
uint64_t n_Rename;
n_Rename = n_DEC_stage + 1;
// RN_stage
uint64_t n_RN_stage;
n_RN_stage = std::max({n_Rename, perfModel->RN_stage.get(1), perfModel->OoO_stage.get(64), perfModel->IS_substage_agu.get(16)});
perfModel->RN_stage.set(n_RN_stage);
// Issue
uint64_t n_Issue;
n_Issue = n_RN_stage + 2;
// IS_substage_agu
uint64_t n_IS_substage_agu;
n_IS_substage_agu = std::max({n_Issue, perfModel->IS_substage_agu.get(1), perfModel->LD_substage_agu.get(2)});
perfModel->IS_substage_agu.set(n_IS_substage_agu);
// OperandLookup
uint64_t n_OperandLookup;
n_OperandLookup = n_IS_substage_agu + 1;
// uA_OF_A_agu
uint64_t n_uA_OF_A_agu;
n_uA_OF_A_agu = std::max({n_IS_substage_agu, perfModel->regModel.getXa()});
// LD_substage_agu
uint64_t n_LD_substage_agu;
n_LD_substage_agu = std::max({n_OperandLookup, n_uA_OF_A_agu, perfModel->LD_substage_agu.get(1), perfModel->EX_stage_agu.get(2), perfModel->EX_substage_agu.get(2)});
perfModel->LD_substage_agu.set(n_LD_substage_agu);
// LOAD
uint64_t n_LOAD;
n_LOAD = n_LD_substage_agu + 1;
// DCache
uint64_t n_DCache;
n_DCache = n_LD_substage_agu + perfModel->dCacheModel.getDelay();
perfModel->regModel.setXd(n_DCache);
// EX_stage_agu
uint64_t n_EX_stage_agu;
n_EX_stage_agu = std::max({n_LOAD, n_DCache, perfModel->EX_stage_agu.get(1), perfModel->EX_substage_agu.get(1)});
perfModel->EX_stage_agu.set(n_EX_stage_agu);
perfModel->EX_substage_agu.set(n_EX_stage_agu);
// EX_substage_agu
uint64_t n_EX_substage_agu;
n_EX_substage_agu = std::max({n_DCache, perfModel->EX_substage_agu.get(1)});
perfModel->EX_substage_agu.set(n_EX_substage_agu);
// OoO_stage
uint64_t n_OoO_stage;
n_OoO_stage = std::max({n_EX_stage_agu, perfModel->OoO_stage.get(1), perfModel->COM_stage.get(8)});
perfModel->OoO_stage.set(n_OoO_stage);
// Commit
uint64_t n_Commit;
n_Commit = n_OoO_stage + 2;
// COM_stage
uint64_t n_COM_stage;
n_COM_stage = std::max({n_Commit, perfModel->COM_stage.get(1)});
perfModel->COM_stage.set(n_COM_stage);

  // Dump Entrance point for info print (tracing)
  perfModel->entrancePoint = n_Enter;
  }
);

static SchedulingFunction *schedulingFunction_beq = new SchedulingFunction(
  RV32_4ISSUE_SchedulingFunctionSet,
  "beq",
  43,
  [](PerformanceModel* perfModel_){
  RV32_4ISSUE_PerformanceModel* perfModel = static_cast<RV32_4ISSUE_PerformanceModel*>(perfModel_);
  // Enter
uint64_t n_Enter;
n_Enter = std::max({perfModel->IF_stage.get(16), perfModel->PC_substage.get(4)});
// PCGen
uint64_t n_PCGen;
n_PCGen = n_Enter + 1;
// uA_PcCorrect
uint64_t n_uA_PcCorrect;
n_uA_PcCorrect = std::max({n_Enter, perfModel->dynBranchPredModel.getPc_mp()});
// uA_CacheBlock
uint64_t n_uA_CacheBlock;
n_uA_CacheBlock = std::max({n_Enter, perfModel->iCacheModel.getIc_out()});
// PC_substage
uint64_t n_PC_substage;
n_PC_substage = std::max({n_PCGen, n_uA_PcCorrect, n_uA_CacheBlock, perfModel->PC_substage.get(1), perfModel->IF_substage_0.get(4)});
perfModel->PC_substage.set(n_PC_substage);
// ICacheCtrl
uint64_t n_ICacheCtrl;
n_ICacheCtrl = n_PC_substage + 1;
// IF_substage_0
uint64_t n_IF_substage_0;
n_IF_substage_0 = std::max({n_ICacheCtrl, perfModel->IF_substage_0.get(1), perfModel->IF_substage_1.get(4)});
perfModel->IF_substage_0.set(n_IF_substage_0);
// ICache
uint64_t n_ICache;
n_ICache = n_IF_substage_0 + perfModel->iCacheModel.getDelay();
perfModel->iCacheModel.setIc_in(n_ICache);
// uA_PcPredict
uint64_t n_uA_PcPredict;
n_uA_PcPredict = std::max({n_IF_substage_0, perfModel->dynBranchPredModel.getPc_pt()});
// IF_substage_1
uint64_t n_IF_substage_1;
n_IF_substage_1 = std::max({n_ICache, n_uA_PcPredict, perfModel->IF_substage_1.get(1), perfModel->IF_substage_2.get(4)});
perfModel->IF_substage_1.set(n_IF_substage_1);
// IScan
uint64_t n_IScan;
n_IScan = n_IF_substage_1 + 1;
perfModel->dynBranchPredModel.setPc_p(n_IScan);
// IF_stage
uint64_t n_IF_stage;
n_IF_stage = std::max({n_IScan, perfModel->IF_stage.get(1), perfModel->IF_substage_2.get(1), perfModel->DEC_stage.get(4)});
perfModel->IF_stage.set(n_IF_stage);
perfModel->IF_substage_2.set(n_IF_stage);
// Decoder
uint64_t n_Decoder;
n_Decoder = n_IF_stage + 1;
// DEC_stage
uint64_t n_DEC_stage;
n_DEC_stage = std::max({n_Decoder, perfModel->DEC_stage.get(1), perfModel->RN_stage.get(5)});
perfModel->DEC_stage.set(n_DEC_stage);
// Rename
uint64_t n_Rename;
n_Rename = n_DEC_stage + 1;
// RN_stage
uint64_t n_RN_stage;
n_RN_stage = std::max({n_Rename, perfModel->RN_stage.get(1), perfModel->OoO_stage.get(64), perfModel->IS_substage_alu.get(24)});
perfModel->RN_stage.set(n_RN_stage);
// Issue
uint64_t n_Issue;
n_Issue = n_RN_stage + 2;
// IS_substage_alu
uint64_t n_IS_substage_alu;
n_IS_substage_alu = std::max({n_Issue, perfModel->IS_substage_alu.get(1), perfModel->LD_substage_alu.get(3)});
perfModel->IS_substage_alu.set(n_IS_substage_alu);
// OperandLookup
uint64_t n_OperandLookup;
n_OperandLookup = n_IS_substage_alu + 1;
// uA_OF_A_alu
uint64_t n_uA_OF_A_alu;
n_uA_OF_A_alu = std::max({n_IS_substage_alu, perfModel->regModel.getXa()});
// uA_OF_B_alu
uint64_t n_uA_OF_B_alu;
n_uA_OF_B_alu = std::max({n_IS_substage_alu, perfModel->regModel.getXb()});
// LD_substage_alu
uint64_t n_LD_substage_alu;
n_LD_substage_alu = std::max({n_OperandLookup, n_uA_OF_A_alu, n_uA_OF_B_alu, perfModel->LD_substage_alu.get(1), perfModel->EX_stage_alu.get(9), perfModel->EX_substage_branch.get(2)});
perfModel->LD_substage_alu.set(n_LD_substage_alu);
// ALU
uint64_t n_ALU;
n_ALU = n_LD_substage_alu + 1;
// EX_stage_alu
uint64_t n_EX_stage_alu;
n_EX_stage_alu = std::max({n_ALU, perfModel->EX_stage_alu.get(1), perfModel->EX_substage_branch.get(1)});
perfModel->EX_stage_alu.set(n_EX_stage_alu);
perfModel->EX_substage_branch.set(n_EX_stage_alu);
// OoO_stage
uint64_t n_OoO_stage;
n_OoO_stage = std::max({n_EX_stage_alu, perfModel->OoO_stage.get(1), perfModel->COM_stage.get(8)});
perfModel->OoO_stage.set(n_OoO_stage);
// Commit
uint64_t n_Commit;
n_Commit = n_OoO_stage + 2;
perfModel->dynBranchPredModel.setPc_c(n_Commit);
// COM_stage
uint64_t n_COM_stage;
n_COM_stage = std::max({n_Commit, perfModel->COM_stage.get(1)});
perfModel->COM_stage.set(n_COM_stage);

  // Dump Entrance point for info print (tracing)
  perfModel->entrancePoint = n_Enter;
  }
);

static SchedulingFunction *schedulingFunction_bne = new SchedulingFunction(
  RV32_4ISSUE_SchedulingFunctionSet,
  "bne",
  44,
  [](PerformanceModel* perfModel_){
  RV32_4ISSUE_PerformanceModel* perfModel = static_cast<RV32_4ISSUE_PerformanceModel*>(perfModel_);
  // Enter
uint64_t n_Enter;
n_Enter = std::max({perfModel->IF_stage.get(16), perfModel->PC_substage.get(4)});
// PCGen
uint64_t n_PCGen;
n_PCGen = n_Enter + 1;
// uA_PcCorrect
uint64_t n_uA_PcCorrect;
n_uA_PcCorrect = std::max({n_Enter, perfModel->dynBranchPredModel.getPc_mp()});
// uA_CacheBlock
uint64_t n_uA_CacheBlock;
n_uA_CacheBlock = std::max({n_Enter, perfModel->iCacheModel.getIc_out()});
// PC_substage
uint64_t n_PC_substage;
n_PC_substage = std::max({n_PCGen, n_uA_PcCorrect, n_uA_CacheBlock, perfModel->PC_substage.get(1), perfModel->IF_substage_0.get(4)});
perfModel->PC_substage.set(n_PC_substage);
// ICacheCtrl
uint64_t n_ICacheCtrl;
n_ICacheCtrl = n_PC_substage + 1;
// IF_substage_0
uint64_t n_IF_substage_0;
n_IF_substage_0 = std::max({n_ICacheCtrl, perfModel->IF_substage_0.get(1), perfModel->IF_substage_1.get(4)});
perfModel->IF_substage_0.set(n_IF_substage_0);
// ICache
uint64_t n_ICache;
n_ICache = n_IF_substage_0 + perfModel->iCacheModel.getDelay();
perfModel->iCacheModel.setIc_in(n_ICache);
// uA_PcPredict
uint64_t n_uA_PcPredict;
n_uA_PcPredict = std::max({n_IF_substage_0, perfModel->dynBranchPredModel.getPc_pt()});
// IF_substage_1
uint64_t n_IF_substage_1;
n_IF_substage_1 = std::max({n_ICache, n_uA_PcPredict, perfModel->IF_substage_1.get(1), perfModel->IF_substage_2.get(4)});
perfModel->IF_substage_1.set(n_IF_substage_1);
// IScan
uint64_t n_IScan;
n_IScan = n_IF_substage_1 + 1;
perfModel->dynBranchPredModel.setPc_p(n_IScan);
// IF_stage
uint64_t n_IF_stage;
n_IF_stage = std::max({n_IScan, perfModel->IF_stage.get(1), perfModel->IF_substage_2.get(1), perfModel->DEC_stage.get(4)});
perfModel->IF_stage.set(n_IF_stage);
perfModel->IF_substage_2.set(n_IF_stage);
// Decoder
uint64_t n_Decoder;
n_Decoder = n_IF_stage + 1;
// DEC_stage
uint64_t n_DEC_stage;
n_DEC_stage = std::max({n_Decoder, perfModel->DEC_stage.get(1), perfModel->RN_stage.get(5)});
perfModel->DEC_stage.set(n_DEC_stage);
// Rename
uint64_t n_Rename;
n_Rename = n_DEC_stage + 1;
// RN_stage
uint64_t n_RN_stage;
n_RN_stage = std::max({n_Rename, perfModel->RN_stage.get(1), perfModel->OoO_stage.get(64), perfModel->IS_substage_alu.get(24)});
perfModel->RN_stage.set(n_RN_stage);
// Issue
uint64_t n_Issue;
n_Issue = n_RN_stage + 2;
// IS_substage_alu
uint64_t n_IS_substage_alu;
n_IS_substage_alu = std::max({n_Issue, perfModel->IS_substage_alu.get(1), perfModel->LD_substage_alu.get(3)});
perfModel->IS_substage_alu.set(n_IS_substage_alu);
// OperandLookup
uint64_t n_OperandLookup;
n_OperandLookup = n_IS_substage_alu + 1;
// uA_OF_A_alu
uint64_t n_uA_OF_A_alu;
n_uA_OF_A_alu = std::max({n_IS_substage_alu, perfModel->regModel.getXa()});
// uA_OF_B_alu
uint64_t n_uA_OF_B_alu;
n_uA_OF_B_alu = std::max({n_IS_substage_alu, perfModel->regModel.getXb()});
// LD_substage_alu
uint64_t n_LD_substage_alu;
n_LD_substage_alu = std::max({n_OperandLookup, n_uA_OF_A_alu, n_uA_OF_B_alu, perfModel->LD_substage_alu.get(1), perfModel->EX_stage_alu.get(9), perfModel->EX_substage_branch.get(2)});
perfModel->LD_substage_alu.set(n_LD_substage_alu);
// ALU
uint64_t n_ALU;
n_ALU = n_LD_substage_alu + 1;
// EX_stage_alu
uint64_t n_EX_stage_alu;
n_EX_stage_alu = std::max({n_ALU, perfModel->EX_stage_alu.get(1), perfModel->EX_substage_branch.get(1)});
perfModel->EX_stage_alu.set(n_EX_stage_alu);
perfModel->EX_substage_branch.set(n_EX_stage_alu);
// OoO_stage
uint64_t n_OoO_stage;
n_OoO_stage = std::max({n_EX_stage_alu, perfModel->OoO_stage.get(1), perfModel->COM_stage.get(8)});
perfModel->OoO_stage.set(n_OoO_stage);
// Commit
uint64_t n_Commit;
n_Commit = n_OoO_stage + 2;
perfModel->dynBranchPredModel.setPc_c(n_Commit);
// COM_stage
uint64_t n_COM_stage;
n_COM_stage = std::max({n_Commit, perfModel->COM_stage.get(1)});
perfModel->COM_stage.set(n_COM_stage);

  // Dump Entrance point for info print (tracing)
  perfModel->entrancePoint = n_Enter;
  }
);

static SchedulingFunction *schedulingFunction_blt = new SchedulingFunction(
  RV32_4ISSUE_SchedulingFunctionSet,
  "blt",
  45,
  [](PerformanceModel* perfModel_){
  RV32_4ISSUE_PerformanceModel* perfModel = static_cast<RV32_4ISSUE_PerformanceModel*>(perfModel_);
  // Enter
uint64_t n_Enter;
n_Enter = std::max({perfModel->IF_stage.get(16), perfModel->PC_substage.get(4)});
// PCGen
uint64_t n_PCGen;
n_PCGen = n_Enter + 1;
// uA_PcCorrect
uint64_t n_uA_PcCorrect;
n_uA_PcCorrect = std::max({n_Enter, perfModel->dynBranchPredModel.getPc_mp()});
// uA_CacheBlock
uint64_t n_uA_CacheBlock;
n_uA_CacheBlock = std::max({n_Enter, perfModel->iCacheModel.getIc_out()});
// PC_substage
uint64_t n_PC_substage;
n_PC_substage = std::max({n_PCGen, n_uA_PcCorrect, n_uA_CacheBlock, perfModel->PC_substage.get(1), perfModel->IF_substage_0.get(4)});
perfModel->PC_substage.set(n_PC_substage);
// ICacheCtrl
uint64_t n_ICacheCtrl;
n_ICacheCtrl = n_PC_substage + 1;
// IF_substage_0
uint64_t n_IF_substage_0;
n_IF_substage_0 = std::max({n_ICacheCtrl, perfModel->IF_substage_0.get(1), perfModel->IF_substage_1.get(4)});
perfModel->IF_substage_0.set(n_IF_substage_0);
// ICache
uint64_t n_ICache;
n_ICache = n_IF_substage_0 + perfModel->iCacheModel.getDelay();
perfModel->iCacheModel.setIc_in(n_ICache);
// uA_PcPredict
uint64_t n_uA_PcPredict;
n_uA_PcPredict = std::max({n_IF_substage_0, perfModel->dynBranchPredModel.getPc_pt()});
// IF_substage_1
uint64_t n_IF_substage_1;
n_IF_substage_1 = std::max({n_ICache, n_uA_PcPredict, perfModel->IF_substage_1.get(1), perfModel->IF_substage_2.get(4)});
perfModel->IF_substage_1.set(n_IF_substage_1);
// IScan
uint64_t n_IScan;
n_IScan = n_IF_substage_1 + 1;
perfModel->dynBranchPredModel.setPc_p(n_IScan);
// IF_stage
uint64_t n_IF_stage;
n_IF_stage = std::max({n_IScan, perfModel->IF_stage.get(1), perfModel->IF_substage_2.get(1), perfModel->DEC_stage.get(4)});
perfModel->IF_stage.set(n_IF_stage);
perfModel->IF_substage_2.set(n_IF_stage);
// Decoder
uint64_t n_Decoder;
n_Decoder = n_IF_stage + 1;
// DEC_stage
uint64_t n_DEC_stage;
n_DEC_stage = std::max({n_Decoder, perfModel->DEC_stage.get(1), perfModel->RN_stage.get(5)});
perfModel->DEC_stage.set(n_DEC_stage);
// Rename
uint64_t n_Rename;
n_Rename = n_DEC_stage + 1;
// RN_stage
uint64_t n_RN_stage;
n_RN_stage = std::max({n_Rename, perfModel->RN_stage.get(1), perfModel->OoO_stage.get(64), perfModel->IS_substage_alu.get(24)});
perfModel->RN_stage.set(n_RN_stage);
// Issue
uint64_t n_Issue;
n_Issue = n_RN_stage + 2;
// IS_substage_alu
uint64_t n_IS_substage_alu;
n_IS_substage_alu = std::max({n_Issue, perfModel->IS_substage_alu.get(1), perfModel->LD_substage_alu.get(3)});
perfModel->IS_substage_alu.set(n_IS_substage_alu);
// OperandLookup
uint64_t n_OperandLookup;
n_OperandLookup = n_IS_substage_alu + 1;
// uA_OF_A_alu
uint64_t n_uA_OF_A_alu;
n_uA_OF_A_alu = std::max({n_IS_substage_alu, perfModel->regModel.getXa()});
// uA_OF_B_alu
uint64_t n_uA_OF_B_alu;
n_uA_OF_B_alu = std::max({n_IS_substage_alu, perfModel->regModel.getXb()});
// LD_substage_alu
uint64_t n_LD_substage_alu;
n_LD_substage_alu = std::max({n_OperandLookup, n_uA_OF_A_alu, n_uA_OF_B_alu, perfModel->LD_substage_alu.get(1), perfModel->EX_stage_alu.get(9), perfModel->EX_substage_branch.get(2)});
perfModel->LD_substage_alu.set(n_LD_substage_alu);
// ALU
uint64_t n_ALU;
n_ALU = n_LD_substage_alu + 1;
// EX_stage_alu
uint64_t n_EX_stage_alu;
n_EX_stage_alu = std::max({n_ALU, perfModel->EX_stage_alu.get(1), perfModel->EX_substage_branch.get(1)});
perfModel->EX_stage_alu.set(n_EX_stage_alu);
perfModel->EX_substage_branch.set(n_EX_stage_alu);
// OoO_stage
uint64_t n_OoO_stage;
n_OoO_stage = std::max({n_EX_stage_alu, perfModel->OoO_stage.get(1), perfModel->COM_stage.get(8)});
perfModel->OoO_stage.set(n_OoO_stage);
// Commit
uint64_t n_Commit;
n_Commit = n_OoO_stage + 2;
perfModel->dynBranchPredModel.setPc_c(n_Commit);
// COM_stage
uint64_t n_COM_stage;
n_COM_stage = std::max({n_Commit, perfModel->COM_stage.get(1)});
perfModel->COM_stage.set(n_COM_stage);

  // Dump Entrance point for info print (tracing)
  perfModel->entrancePoint = n_Enter;
  }
);

static SchedulingFunction *schedulingFunction_bge = new SchedulingFunction(
  RV32_4ISSUE_SchedulingFunctionSet,
  "bge",
  46,
  [](PerformanceModel* perfModel_){
  RV32_4ISSUE_PerformanceModel* perfModel = static_cast<RV32_4ISSUE_PerformanceModel*>(perfModel_);
  // Enter
uint64_t n_Enter;
n_Enter = std::max({perfModel->IF_stage.get(16), perfModel->PC_substage.get(4)});
// PCGen
uint64_t n_PCGen;
n_PCGen = n_Enter + 1;
// uA_PcCorrect
uint64_t n_uA_PcCorrect;
n_uA_PcCorrect = std::max({n_Enter, perfModel->dynBranchPredModel.getPc_mp()});
// uA_CacheBlock
uint64_t n_uA_CacheBlock;
n_uA_CacheBlock = std::max({n_Enter, perfModel->iCacheModel.getIc_out()});
// PC_substage
uint64_t n_PC_substage;
n_PC_substage = std::max({n_PCGen, n_uA_PcCorrect, n_uA_CacheBlock, perfModel->PC_substage.get(1), perfModel->IF_substage_0.get(4)});
perfModel->PC_substage.set(n_PC_substage);
// ICacheCtrl
uint64_t n_ICacheCtrl;
n_ICacheCtrl = n_PC_substage + 1;
// IF_substage_0
uint64_t n_IF_substage_0;
n_IF_substage_0 = std::max({n_ICacheCtrl, perfModel->IF_substage_0.get(1), perfModel->IF_substage_1.get(4)});
perfModel->IF_substage_0.set(n_IF_substage_0);
// ICache
uint64_t n_ICache;
n_ICache = n_IF_substage_0 + perfModel->iCacheModel.getDelay();
perfModel->iCacheModel.setIc_in(n_ICache);
// uA_PcPredict
uint64_t n_uA_PcPredict;
n_uA_PcPredict = std::max({n_IF_substage_0, perfModel->dynBranchPredModel.getPc_pt()});
// IF_substage_1
uint64_t n_IF_substage_1;
n_IF_substage_1 = std::max({n_ICache, n_uA_PcPredict, perfModel->IF_substage_1.get(1), perfModel->IF_substage_2.get(4)});
perfModel->IF_substage_1.set(n_IF_substage_1);
// IScan
uint64_t n_IScan;
n_IScan = n_IF_substage_1 + 1;
perfModel->dynBranchPredModel.setPc_p(n_IScan);
// IF_stage
uint64_t n_IF_stage;
n_IF_stage = std::max({n_IScan, perfModel->IF_stage.get(1), perfModel->IF_substage_2.get(1), perfModel->DEC_stage.get(4)});
perfModel->IF_stage.set(n_IF_stage);
perfModel->IF_substage_2.set(n_IF_stage);
// Decoder
uint64_t n_Decoder;
n_Decoder = n_IF_stage + 1;
// DEC_stage
uint64_t n_DEC_stage;
n_DEC_stage = std::max({n_Decoder, perfModel->DEC_stage.get(1), perfModel->RN_stage.get(5)});
perfModel->DEC_stage.set(n_DEC_stage);
// Rename
uint64_t n_Rename;
n_Rename = n_DEC_stage + 1;
// RN_stage
uint64_t n_RN_stage;
n_RN_stage = std::max({n_Rename, perfModel->RN_stage.get(1), perfModel->OoO_stage.get(64), perfModel->IS_substage_alu.get(24)});
perfModel->RN_stage.set(n_RN_stage);
// Issue
uint64_t n_Issue;
n_Issue = n_RN_stage + 2;
// IS_substage_alu
uint64_t n_IS_substage_alu;
n_IS_substage_alu = std::max({n_Issue, perfModel->IS_substage_alu.get(1), perfModel->LD_substage_alu.get(3)});
perfModel->IS_substage_alu.set(n_IS_substage_alu);
// OperandLookup
uint64_t n_OperandLookup;
n_OperandLookup = n_IS_substage_alu + 1;
// uA_OF_A_alu
uint64_t n_uA_OF_A_alu;
n_uA_OF_A_alu = std::max({n_IS_substage_alu, perfModel->regModel.getXa()});
// uA_OF_B_alu
uint64_t n_uA_OF_B_alu;
n_uA_OF_B_alu = std::max({n_IS_substage_alu, perfModel->regModel.getXb()});
// LD_substage_alu
uint64_t n_LD_substage_alu;
n_LD_substage_alu = std::max({n_OperandLookup, n_uA_OF_A_alu, n_uA_OF_B_alu, perfModel->LD_substage_alu.get(1), perfModel->EX_stage_alu.get(9), perfModel->EX_substage_branch.get(2)});
perfModel->LD_substage_alu.set(n_LD_substage_alu);
// ALU
uint64_t n_ALU;
n_ALU = n_LD_substage_alu + 1;
// EX_stage_alu
uint64_t n_EX_stage_alu;
n_EX_stage_alu = std::max({n_ALU, perfModel->EX_stage_alu.get(1), perfModel->EX_substage_branch.get(1)});
perfModel->EX_stage_alu.set(n_EX_stage_alu);
perfModel->EX_substage_branch.set(n_EX_stage_alu);
// OoO_stage
uint64_t n_OoO_stage;
n_OoO_stage = std::max({n_EX_stage_alu, perfModel->OoO_stage.get(1), perfModel->COM_stage.get(8)});
perfModel->OoO_stage.set(n_OoO_stage);
// Commit
uint64_t n_Commit;
n_Commit = n_OoO_stage + 2;
perfModel->dynBranchPredModel.setPc_c(n_Commit);
// COM_stage
uint64_t n_COM_stage;
n_COM_stage = std::max({n_Commit, perfModel->COM_stage.get(1)});
perfModel->COM_stage.set(n_COM_stage);

  // Dump Entrance point for info print (tracing)
  perfModel->entrancePoint = n_Enter;
  }
);

static SchedulingFunction *schedulingFunction_bltu = new SchedulingFunction(
  RV32_4ISSUE_SchedulingFunctionSet,
  "bltu",
  47,
  [](PerformanceModel* perfModel_){
  RV32_4ISSUE_PerformanceModel* perfModel = static_cast<RV32_4ISSUE_PerformanceModel*>(perfModel_);
  // Enter
uint64_t n_Enter;
n_Enter = std::max({perfModel->IF_stage.get(16), perfModel->PC_substage.get(4)});
// PCGen
uint64_t n_PCGen;
n_PCGen = n_Enter + 1;
// uA_PcCorrect
uint64_t n_uA_PcCorrect;
n_uA_PcCorrect = std::max({n_Enter, perfModel->dynBranchPredModel.getPc_mp()});
// uA_CacheBlock
uint64_t n_uA_CacheBlock;
n_uA_CacheBlock = std::max({n_Enter, perfModel->iCacheModel.getIc_out()});
// PC_substage
uint64_t n_PC_substage;
n_PC_substage = std::max({n_PCGen, n_uA_PcCorrect, n_uA_CacheBlock, perfModel->PC_substage.get(1), perfModel->IF_substage_0.get(4)});
perfModel->PC_substage.set(n_PC_substage);
// ICacheCtrl
uint64_t n_ICacheCtrl;
n_ICacheCtrl = n_PC_substage + 1;
// IF_substage_0
uint64_t n_IF_substage_0;
n_IF_substage_0 = std::max({n_ICacheCtrl, perfModel->IF_substage_0.get(1), perfModel->IF_substage_1.get(4)});
perfModel->IF_substage_0.set(n_IF_substage_0);
// ICache
uint64_t n_ICache;
n_ICache = n_IF_substage_0 + perfModel->iCacheModel.getDelay();
perfModel->iCacheModel.setIc_in(n_ICache);
// uA_PcPredict
uint64_t n_uA_PcPredict;
n_uA_PcPredict = std::max({n_IF_substage_0, perfModel->dynBranchPredModel.getPc_pt()});
// IF_substage_1
uint64_t n_IF_substage_1;
n_IF_substage_1 = std::max({n_ICache, n_uA_PcPredict, perfModel->IF_substage_1.get(1), perfModel->IF_substage_2.get(4)});
perfModel->IF_substage_1.set(n_IF_substage_1);
// IScan
uint64_t n_IScan;
n_IScan = n_IF_substage_1 + 1;
perfModel->dynBranchPredModel.setPc_p(n_IScan);
// IF_stage
uint64_t n_IF_stage;
n_IF_stage = std::max({n_IScan, perfModel->IF_stage.get(1), perfModel->IF_substage_2.get(1), perfModel->DEC_stage.get(4)});
perfModel->IF_stage.set(n_IF_stage);
perfModel->IF_substage_2.set(n_IF_stage);
// Decoder
uint64_t n_Decoder;
n_Decoder = n_IF_stage + 1;
// DEC_stage
uint64_t n_DEC_stage;
n_DEC_stage = std::max({n_Decoder, perfModel->DEC_stage.get(1), perfModel->RN_stage.get(5)});
perfModel->DEC_stage.set(n_DEC_stage);
// Rename
uint64_t n_Rename;
n_Rename = n_DEC_stage + 1;
// RN_stage
uint64_t n_RN_stage;
n_RN_stage = std::max({n_Rename, perfModel->RN_stage.get(1), perfModel->OoO_stage.get(64), perfModel->IS_substage_alu.get(24)});
perfModel->RN_stage.set(n_RN_stage);
// Issue
uint64_t n_Issue;
n_Issue = n_RN_stage + 2;
// IS_substage_alu
uint64_t n_IS_substage_alu;
n_IS_substage_alu = std::max({n_Issue, perfModel->IS_substage_alu.get(1), perfModel->LD_substage_alu.get(3)});
perfModel->IS_substage_alu.set(n_IS_substage_alu);
// OperandLookup
uint64_t n_OperandLookup;
n_OperandLookup = n_IS_substage_alu + 1;
// uA_OF_A_alu
uint64_t n_uA_OF_A_alu;
n_uA_OF_A_alu = std::max({n_IS_substage_alu, perfModel->regModel.getXa()});
// uA_OF_B_alu
uint64_t n_uA_OF_B_alu;
n_uA_OF_B_alu = std::max({n_IS_substage_alu, perfModel->regModel.getXb()});
// LD_substage_alu
uint64_t n_LD_substage_alu;
n_LD_substage_alu = std::max({n_OperandLookup, n_uA_OF_A_alu, n_uA_OF_B_alu, perfModel->LD_substage_alu.get(1), perfModel->EX_stage_alu.get(9), perfModel->EX_substage_branch.get(2)});
perfModel->LD_substage_alu.set(n_LD_substage_alu);
// ALU
uint64_t n_ALU;
n_ALU = n_LD_substage_alu + 1;
// EX_stage_alu
uint64_t n_EX_stage_alu;
n_EX_stage_alu = std::max({n_ALU, perfModel->EX_stage_alu.get(1), perfModel->EX_substage_branch.get(1)});
perfModel->EX_stage_alu.set(n_EX_stage_alu);
perfModel->EX_substage_branch.set(n_EX_stage_alu);
// OoO_stage
uint64_t n_OoO_stage;
n_OoO_stage = std::max({n_EX_stage_alu, perfModel->OoO_stage.get(1), perfModel->COM_stage.get(8)});
perfModel->OoO_stage.set(n_OoO_stage);
// Commit
uint64_t n_Commit;
n_Commit = n_OoO_stage + 2;
perfModel->dynBranchPredModel.setPc_c(n_Commit);
// COM_stage
uint64_t n_COM_stage;
n_COM_stage = std::max({n_Commit, perfModel->COM_stage.get(1)});
perfModel->COM_stage.set(n_COM_stage);

  // Dump Entrance point for info print (tracing)
  perfModel->entrancePoint = n_Enter;
  }
);

static SchedulingFunction *schedulingFunction_bgeu = new SchedulingFunction(
  RV32_4ISSUE_SchedulingFunctionSet,
  "bgeu",
  48,
  [](PerformanceModel* perfModel_){
  RV32_4ISSUE_PerformanceModel* perfModel = static_cast<RV32_4ISSUE_PerformanceModel*>(perfModel_);
  // Enter
uint64_t n_Enter;
n_Enter = std::max({perfModel->IF_stage.get(16), perfModel->PC_substage.get(4)});
// PCGen
uint64_t n_PCGen;
n_PCGen = n_Enter + 1;
// uA_PcCorrect
uint64_t n_uA_PcCorrect;
n_uA_PcCorrect = std::max({n_Enter, perfModel->dynBranchPredModel.getPc_mp()});
// uA_CacheBlock
uint64_t n_uA_CacheBlock;
n_uA_CacheBlock = std::max({n_Enter, perfModel->iCacheModel.getIc_out()});
// PC_substage
uint64_t n_PC_substage;
n_PC_substage = std::max({n_PCGen, n_uA_PcCorrect, n_uA_CacheBlock, perfModel->PC_substage.get(1), perfModel->IF_substage_0.get(4)});
perfModel->PC_substage.set(n_PC_substage);
// ICacheCtrl
uint64_t n_ICacheCtrl;
n_ICacheCtrl = n_PC_substage + 1;
// IF_substage_0
uint64_t n_IF_substage_0;
n_IF_substage_0 = std::max({n_ICacheCtrl, perfModel->IF_substage_0.get(1), perfModel->IF_substage_1.get(4)});
perfModel->IF_substage_0.set(n_IF_substage_0);
// ICache
uint64_t n_ICache;
n_ICache = n_IF_substage_0 + perfModel->iCacheModel.getDelay();
perfModel->iCacheModel.setIc_in(n_ICache);
// uA_PcPredict
uint64_t n_uA_PcPredict;
n_uA_PcPredict = std::max({n_IF_substage_0, perfModel->dynBranchPredModel.getPc_pt()});
// IF_substage_1
uint64_t n_IF_substage_1;
n_IF_substage_1 = std::max({n_ICache, n_uA_PcPredict, perfModel->IF_substage_1.get(1), perfModel->IF_substage_2.get(4)});
perfModel->IF_substage_1.set(n_IF_substage_1);
// IScan
uint64_t n_IScan;
n_IScan = n_IF_substage_1 + 1;
perfModel->dynBranchPredModel.setPc_p(n_IScan);
// IF_stage
uint64_t n_IF_stage;
n_IF_stage = std::max({n_IScan, perfModel->IF_stage.get(1), perfModel->IF_substage_2.get(1), perfModel->DEC_stage.get(4)});
perfModel->IF_stage.set(n_IF_stage);
perfModel->IF_substage_2.set(n_IF_stage);
// Decoder
uint64_t n_Decoder;
n_Decoder = n_IF_stage + 1;
// DEC_stage
uint64_t n_DEC_stage;
n_DEC_stage = std::max({n_Decoder, perfModel->DEC_stage.get(1), perfModel->RN_stage.get(5)});
perfModel->DEC_stage.set(n_DEC_stage);
// Rename
uint64_t n_Rename;
n_Rename = n_DEC_stage + 1;
// RN_stage
uint64_t n_RN_stage;
n_RN_stage = std::max({n_Rename, perfModel->RN_stage.get(1), perfModel->OoO_stage.get(64), perfModel->IS_substage_alu.get(24)});
perfModel->RN_stage.set(n_RN_stage);
// Issue
uint64_t n_Issue;
n_Issue = n_RN_stage + 2;
// IS_substage_alu
uint64_t n_IS_substage_alu;
n_IS_substage_alu = std::max({n_Issue, perfModel->IS_substage_alu.get(1), perfModel->LD_substage_alu.get(3)});
perfModel->IS_substage_alu.set(n_IS_substage_alu);
// OperandLookup
uint64_t n_OperandLookup;
n_OperandLookup = n_IS_substage_alu + 1;
// uA_OF_A_alu
uint64_t n_uA_OF_A_alu;
n_uA_OF_A_alu = std::max({n_IS_substage_alu, perfModel->regModel.getXa()});
// uA_OF_B_alu
uint64_t n_uA_OF_B_alu;
n_uA_OF_B_alu = std::max({n_IS_substage_alu, perfModel->regModel.getXb()});
// LD_substage_alu
uint64_t n_LD_substage_alu;
n_LD_substage_alu = std::max({n_OperandLookup, n_uA_OF_A_alu, n_uA_OF_B_alu, perfModel->LD_substage_alu.get(1), perfModel->EX_stage_alu.get(9), perfModel->EX_substage_branch.get(2)});
perfModel->LD_substage_alu.set(n_LD_substage_alu);
// ALU
uint64_t n_ALU;
n_ALU = n_LD_substage_alu + 1;
// EX_stage_alu
uint64_t n_EX_stage_alu;
n_EX_stage_alu = std::max({n_ALU, perfModel->EX_stage_alu.get(1), perfModel->EX_substage_branch.get(1)});
perfModel->EX_stage_alu.set(n_EX_stage_alu);
perfModel->EX_substage_branch.set(n_EX_stage_alu);
// OoO_stage
uint64_t n_OoO_stage;
n_OoO_stage = std::max({n_EX_stage_alu, perfModel->OoO_stage.get(1), perfModel->COM_stage.get(8)});
perfModel->OoO_stage.set(n_OoO_stage);
// Commit
uint64_t n_Commit;
n_Commit = n_OoO_stage + 2;
perfModel->dynBranchPredModel.setPc_c(n_Commit);
// COM_stage
uint64_t n_COM_stage;
n_COM_stage = std::max({n_Commit, perfModel->COM_stage.get(1)});
perfModel->COM_stage.set(n_COM_stage);

  // Dump Entrance point for info print (tracing)
  perfModel->entrancePoint = n_Enter;
  }
);

static SchedulingFunction *schedulingFunction_jal = new SchedulingFunction(
  RV32_4ISSUE_SchedulingFunctionSet,
  "jal",
  49,
  [](PerformanceModel* perfModel_){
  RV32_4ISSUE_PerformanceModel* perfModel = static_cast<RV32_4ISSUE_PerformanceModel*>(perfModel_);
  // Enter
uint64_t n_Enter;
n_Enter = std::max({perfModel->IF_stage.get(16), perfModel->PC_substage.get(4)});
// PCGen
uint64_t n_PCGen;
n_PCGen = n_Enter + 1;
// uA_PcCorrect
uint64_t n_uA_PcCorrect;
n_uA_PcCorrect = std::max({n_Enter, perfModel->dynBranchPredModel.getPc_mp()});
// uA_CacheBlock
uint64_t n_uA_CacheBlock;
n_uA_CacheBlock = std::max({n_Enter, perfModel->iCacheModel.getIc_out()});
// PC_substage
uint64_t n_PC_substage;
n_PC_substage = std::max({n_PCGen, n_uA_PcCorrect, n_uA_CacheBlock, perfModel->PC_substage.get(1), perfModel->IF_substage_0.get(4)});
perfModel->PC_substage.set(n_PC_substage);
// ICacheCtrl
uint64_t n_ICacheCtrl;
n_ICacheCtrl = n_PC_substage + 1;
// IF_substage_0
uint64_t n_IF_substage_0;
n_IF_substage_0 = std::max({n_ICacheCtrl, perfModel->IF_substage_0.get(1), perfModel->IF_substage_1.get(4)});
perfModel->IF_substage_0.set(n_IF_substage_0);
// ICache
uint64_t n_ICache;
n_ICache = n_IF_substage_0 + perfModel->iCacheModel.getDelay();
perfModel->iCacheModel.setIc_in(n_ICache);
// uA_PcPredict
uint64_t n_uA_PcPredict;
n_uA_PcPredict = std::max({n_IF_substage_0, perfModel->dynBranchPredModel.getPc_pt()});
// IF_substage_1
uint64_t n_IF_substage_1;
n_IF_substage_1 = std::max({n_ICache, n_uA_PcPredict, perfModel->IF_substage_1.get(1), perfModel->IF_substage_2.get(4)});
perfModel->IF_substage_1.set(n_IF_substage_1);
// IScan
uint64_t n_IScan;
n_IScan = n_IF_substage_1 + 1;
perfModel->dynBranchPredModel.setPc_p_j(n_IScan);
// IF_stage
uint64_t n_IF_stage;
n_IF_stage = std::max({n_IScan, perfModel->IF_stage.get(1), perfModel->IF_substage_2.get(1), perfModel->DEC_stage.get(4)});
perfModel->IF_stage.set(n_IF_stage);
perfModel->IF_substage_2.set(n_IF_stage);
// Decoder
uint64_t n_Decoder;
n_Decoder = n_IF_stage + 1;
// DEC_stage
uint64_t n_DEC_stage;
n_DEC_stage = std::max({n_Decoder, perfModel->DEC_stage.get(1), perfModel->RN_stage.get(5)});
perfModel->DEC_stage.set(n_DEC_stage);
// Rename
uint64_t n_Rename;
n_Rename = n_DEC_stage + 1;
// RN_stage
uint64_t n_RN_stage;
n_RN_stage = std::max({n_Rename, perfModel->RN_stage.get(1), perfModel->OoO_stage.get(64), perfModel->IS_substage_alu.get(24)});
perfModel->RN_stage.set(n_RN_stage);
// Issue
uint64_t n_Issue;
n_Issue = n_RN_stage + 2;
// IS_substage_alu
uint64_t n_IS_substage_alu;
n_IS_substage_alu = std::max({n_Issue, perfModel->IS_substage_alu.get(1), perfModel->LD_substage_alu.get(3)});
perfModel->IS_substage_alu.set(n_IS_substage_alu);
// OperandLookup
uint64_t n_OperandLookup;
n_OperandLookup = n_IS_substage_alu + 1;
// LD_substage_alu
uint64_t n_LD_substage_alu;
n_LD_substage_alu = std::max({n_OperandLookup, perfModel->LD_substage_alu.get(1), perfModel->EX_stage_alu.get(9), perfModel->EX_substage_branch.get(2)});
perfModel->LD_substage_alu.set(n_LD_substage_alu);
// ALU
uint64_t n_ALU;
n_ALU = n_LD_substage_alu + 1;
perfModel->regModel.setXd(n_ALU);
// EX_stage_alu
uint64_t n_EX_stage_alu;
n_EX_stage_alu = std::max({n_ALU, perfModel->EX_stage_alu.get(1), perfModel->EX_substage_branch.get(1)});
perfModel->EX_stage_alu.set(n_EX_stage_alu);
perfModel->EX_substage_branch.set(n_EX_stage_alu);
// OoO_stage
uint64_t n_OoO_stage;
n_OoO_stage = std::max({n_EX_stage_alu, perfModel->OoO_stage.get(1), perfModel->COM_stage.get(8)});
perfModel->OoO_stage.set(n_OoO_stage);
// Commit
uint64_t n_Commit;
n_Commit = n_OoO_stage + 2;
perfModel->dynBranchPredModel.setPc_c(n_Commit);
// COM_stage
uint64_t n_COM_stage;
n_COM_stage = std::max({n_Commit, perfModel->COM_stage.get(1)});
perfModel->COM_stage.set(n_COM_stage);

  // Dump Entrance point for info print (tracing)
  perfModel->entrancePoint = n_Enter;
  }
);

static SchedulingFunction *schedulingFunction_jalr = new SchedulingFunction(
  RV32_4ISSUE_SchedulingFunctionSet,
  "jalr",
  50,
  [](PerformanceModel* perfModel_){
  RV32_4ISSUE_PerformanceModel* perfModel = static_cast<RV32_4ISSUE_PerformanceModel*>(perfModel_);
  // Enter
uint64_t n_Enter;
n_Enter = std::max({perfModel->IF_stage.get(16), perfModel->PC_substage.get(4)});
// PCGen
uint64_t n_PCGen;
n_PCGen = n_Enter + 1;
// uA_PcCorrect
uint64_t n_uA_PcCorrect;
n_uA_PcCorrect = std::max({n_Enter, perfModel->dynBranchPredModel.getPc_mp()});
// uA_CacheBlock
uint64_t n_uA_CacheBlock;
n_uA_CacheBlock = std::max({n_Enter, perfModel->iCacheModel.getIc_out()});
// PC_substage
uint64_t n_PC_substage;
n_PC_substage = std::max({n_PCGen, n_uA_PcCorrect, n_uA_CacheBlock, perfModel->PC_substage.get(1), perfModel->IF_substage_0.get(4)});
perfModel->PC_substage.set(n_PC_substage);
// ICacheCtrl
uint64_t n_ICacheCtrl;
n_ICacheCtrl = n_PC_substage + 1;
// IF_substage_0
uint64_t n_IF_substage_0;
n_IF_substage_0 = std::max({n_ICacheCtrl, perfModel->IF_substage_0.get(1), perfModel->IF_substage_1.get(4)});
perfModel->IF_substage_0.set(n_IF_substage_0);
// ICache
uint64_t n_ICache;
n_ICache = n_IF_substage_0 + perfModel->iCacheModel.getDelay();
perfModel->iCacheModel.setIc_in(n_ICache);
// uA_PcPredict
uint64_t n_uA_PcPredict;
n_uA_PcPredict = std::max({n_IF_substage_0, perfModel->dynBranchPredModel.getPc_pt()});
// IF_substage_1
uint64_t n_IF_substage_1;
n_IF_substage_1 = std::max({n_ICache, n_uA_PcPredict, perfModel->IF_substage_1.get(1), perfModel->IF_substage_2.get(4)});
perfModel->IF_substage_1.set(n_IF_substage_1);
// IScan
uint64_t n_IScan;
n_IScan = n_IF_substage_1 + 1;
perfModel->dynBranchPredModel.setPc_p_jr(n_IScan);
// IF_stage
uint64_t n_IF_stage;
n_IF_stage = std::max({n_IScan, perfModel->IF_stage.get(1), perfModel->IF_substage_2.get(1), perfModel->DEC_stage.get(4)});
perfModel->IF_stage.set(n_IF_stage);
perfModel->IF_substage_2.set(n_IF_stage);
// Decoder
uint64_t n_Decoder;
n_Decoder = n_IF_stage + 1;
// DEC_stage
uint64_t n_DEC_stage;
n_DEC_stage = std::max({n_Decoder, perfModel->DEC_stage.get(1), perfModel->RN_stage.get(5)});
perfModel->DEC_stage.set(n_DEC_stage);
// Rename
uint64_t n_Rename;
n_Rename = n_DEC_stage + 1;
// RN_stage
uint64_t n_RN_stage;
n_RN_stage = std::max({n_Rename, perfModel->RN_stage.get(1), perfModel->OoO_stage.get(64), perfModel->IS_substage_alu.get(24)});
perfModel->RN_stage.set(n_RN_stage);
// Issue
uint64_t n_Issue;
n_Issue = n_RN_stage + 2;
// IS_substage_alu
uint64_t n_IS_substage_alu;
n_IS_substage_alu = std::max({n_Issue, perfModel->IS_substage_alu.get(1), perfModel->LD_substage_alu.get(3)});
perfModel->IS_substage_alu.set(n_IS_substage_alu);
// OperandLookup
uint64_t n_OperandLookup;
n_OperandLookup = n_IS_substage_alu + 1;
// uA_OF_A_alu
uint64_t n_uA_OF_A_alu;
n_uA_OF_A_alu = std::max({n_IS_substage_alu, perfModel->regModel.getXa()});
// LD_substage_alu
uint64_t n_LD_substage_alu;
n_LD_substage_alu = std::max({n_OperandLookup, n_uA_OF_A_alu, perfModel->LD_substage_alu.get(1), perfModel->EX_stage_alu.get(9), perfModel->EX_substage_branch.get(2)});
perfModel->LD_substage_alu.set(n_LD_substage_alu);
// ALU
uint64_t n_ALU;
n_ALU = n_LD_substage_alu + 1;
perfModel->regModel.setXd(n_ALU);
// EX_stage_alu
uint64_t n_EX_stage_alu;
n_EX_stage_alu = std::max({n_ALU, perfModel->EX_stage_alu.get(1), perfModel->EX_substage_branch.get(1)});
perfModel->EX_stage_alu.set(n_EX_stage_alu);
perfModel->EX_substage_branch.set(n_EX_stage_alu);
// OoO_stage
uint64_t n_OoO_stage;
n_OoO_stage = std::max({n_EX_stage_alu, perfModel->OoO_stage.get(1), perfModel->COM_stage.get(8)});
perfModel->OoO_stage.set(n_OoO_stage);
// Commit
uint64_t n_Commit;
n_Commit = n_OoO_stage + 2;
perfModel->dynBranchPredModel.setPc_c(n_Commit);
// COM_stage
uint64_t n_COM_stage;
n_COM_stage = std::max({n_Commit, perfModel->COM_stage.get(1)});
perfModel->COM_stage.set(n_COM_stage);

  // Dump Entrance point for info print (tracing)
  perfModel->entrancePoint = n_Enter;
  }
);

static SchedulingFunction *schedulingFunction__def = new SchedulingFunction(
  RV32_4ISSUE_SchedulingFunctionSet,
  "_def",
  51,
  [](PerformanceModel* perfModel_){
  RV32_4ISSUE_PerformanceModel* perfModel = static_cast<RV32_4ISSUE_PerformanceModel*>(perfModel_);
  // Enter
uint64_t n_Enter;
n_Enter = std::max({perfModel->IF_stage.get(16), perfModel->PC_substage.get(4)});
// PCGen
uint64_t n_PCGen;
n_PCGen = n_Enter + 1;
// uA_PcCorrect
uint64_t n_uA_PcCorrect;
n_uA_PcCorrect = std::max({n_Enter, perfModel->dynBranchPredModel.getPc_mp()});
// uA_CacheBlock
uint64_t n_uA_CacheBlock;
n_uA_CacheBlock = std::max({n_Enter, perfModel->iCacheModel.getIc_out()});
// PC_substage
uint64_t n_PC_substage;
n_PC_substage = std::max({n_PCGen, n_uA_PcCorrect, n_uA_CacheBlock, perfModel->PC_substage.get(1), perfModel->IF_substage_0.get(4)});
perfModel->PC_substage.set(n_PC_substage);
// ICacheCtrl
uint64_t n_ICacheCtrl;
n_ICacheCtrl = n_PC_substage + 1;
// IF_substage_0
uint64_t n_IF_substage_0;
n_IF_substage_0 = std::max({n_ICacheCtrl, perfModel->IF_substage_0.get(1), perfModel->IF_substage_1.get(4)});
perfModel->IF_substage_0.set(n_IF_substage_0);
// ICache
uint64_t n_ICache;
n_ICache = n_IF_substage_0 + perfModel->iCacheModel.getDelay();
perfModel->iCacheModel.setIc_in(n_ICache);
// uA_PcPredict
uint64_t n_uA_PcPredict;
n_uA_PcPredict = std::max({n_IF_substage_0, perfModel->dynBranchPredModel.getPc_pt()});
// IF_substage_1
uint64_t n_IF_substage_1;
n_IF_substage_1 = std::max({n_ICache, n_uA_PcPredict, perfModel->IF_substage_1.get(1)});
perfModel->IF_substage_1.set(n_IF_substage_1);

  // Dump Entrance point for info print (tracing)
  perfModel->entrancePoint = n_Enter;
  }
);


} // namespace RV32_4ISSUE