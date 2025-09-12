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


#ifndef SWEVAL_BACKENDS_RV32_4ISSUE_PERFORMANCE_MODEL_H
#define SWEVAL_BACKENDS_RV32_4ISSUE_PERFORMANCE_MODEL_H

#include <stdbool.h>
#include <string>
#include <cstdint>

#include "PerformanceModel.h"
#include "Channel.h"

#include "models/common/StandardRegisterModel.h"
#include "models/rv32_4issue/BranchPredictionModel.h"
#include "models/rv32_4issue/ICacheModel.h"
#include "models/rv32_4issue/DCacheModel.h"
#include "models/rv32_4issue/DividerUnsignedModel.h"
#include "models/rv32_4issue/DividerModel.h"

namespace RV32_4ISSUE{

extern SchedulingFunctionSet* RV32_4ISSUE_SchedulingFunctionSet;

class RV32_4ISSUE_PerformanceModel : public PerformanceModel
{
public:

  RV32_4ISSUE_PerformanceModel() : PerformanceModel("RV32_4ISSUE", RV32_4ISSUE_SchedulingFunctionSet)
    ,IF_stage(16,0)
    ,PC_substage(4,0)
    ,IF_substage_0(4,0)
    ,IF_substage_1(4,0)
    ,IF_substage_2(4,0)
    ,DEC_stage(4,0)
    ,RN_stage(5,0)
    ,OoO_stage(64,0)
    ,IS_substage_alu(24,0)
    ,LD_substage_alu(3,0)
    ,EX_stage_alu(9,0)
    ,EX_substage_alu(3,0)
    ,EX_substage_mul_1(2,0)
    ,EX_substage_mul_2(2,0)
    ,EX_substage_mul_3(2,0)
    ,EX_substage_mul_4(2,0)
    ,EX_substage_branch(2,0)
    ,IS_substage_agu(16,0)
    ,LD_substage_agu(2,0)
    ,EX_stage_agu(2,0)
    ,EX_substage_agu(2,0)
    ,IS_substage_store(16,0)
    ,LD_substage_store(2,0)
    ,EX_stage_store(2,0)
    ,EX_substage_store(2,0)
    ,COM_stage(8,0)
    ,regModel(this)
    ,dynBranchPredModel(this)
    ,iCacheModel(this)
    ,dCacheModel(this)
    ,divider_u(this)
    ,divider(this)
  {};

  // Entrance-point "timing variable" (only used for info-stream)
  uint64_t entrancePoint = 0;

  // Single-Element Timing Variables
  uint64_t EX_substage_csr = 0;
  uint64_t EX_substage_div = 0;

  // Multi-Element Timing Variables
  MultiElementTimingVariable IF_stage;
  MultiElementTimingVariable PC_substage;
  MultiElementTimingVariable IF_substage_0;
  MultiElementTimingVariable IF_substage_1;
  MultiElementTimingVariable IF_substage_2;
  MultiElementTimingVariable DEC_stage;
  MultiElementTimingVariable RN_stage;
  MultiElementTimingVariable OoO_stage;
  MultiElementTimingVariable IS_substage_alu;
  MultiElementTimingVariable LD_substage_alu;
  MultiElementTimingVariable EX_stage_alu;
  MultiElementTimingVariable EX_substage_alu;
  MultiElementTimingVariable EX_substage_mul_1;
  MultiElementTimingVariable EX_substage_mul_2;
  MultiElementTimingVariable EX_substage_mul_3;
  MultiElementTimingVariable EX_substage_mul_4;
  MultiElementTimingVariable EX_substage_branch;
  MultiElementTimingVariable IS_substage_agu;
  MultiElementTimingVariable LD_substage_agu;
  MultiElementTimingVariable EX_stage_agu;
  MultiElementTimingVariable EX_substage_agu;
  MultiElementTimingVariable IS_substage_store;
  MultiElementTimingVariable LD_substage_store;
  MultiElementTimingVariable EX_stage_store;
  MultiElementTimingVariable EX_substage_store;
  MultiElementTimingVariable COM_stage;

  // External Resource Models
  common::StandardRegisterModel regModel;
  rv32_4issue::BranchPredictionModel dynBranchPredModel;
  rv32_4issue::ICacheModel iCacheModel;
  rv32_4issue::DCacheModel dCacheModel;
  rv32_4issue::DividerUnsignedModel divider_u;
  rv32_4issue::DividerModel divider;

  virtual void connectChannel(Channel*);
  virtual uint64_t getCycleCount(void);
  virtual std::string getPipelineStream(void);
  virtual std::string getPrintHeader(void);

};

} // namespace RV32_4ISSUE

#endif // SWEVAL_BACKENDS_RV32_4ISSUE_PERFORMANCE_MODEL_H