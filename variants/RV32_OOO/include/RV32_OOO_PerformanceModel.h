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


#ifndef SWEVAL_BACKENDS_RV32_OOO_PERFORMANCE_MODEL_H
#define SWEVAL_BACKENDS_RV32_OOO_PERFORMANCE_MODEL_H

#include <stdbool.h>
#include <string>
#include <cstdint>

#include "PerformanceModel.h"
#include "Channel.h"

#include "models/RV32_OOO/OoORegisterModel.h"
#include "models/RV32_OOO/NoBranchPredictModel.h"
#include "models/RV32_OOO/ClobberModel.h"
#include "models/RV32_OOO/Scheduler.h"

namespace RV32_OOO{

extern SchedulingFunctionSet* RV32_OOO_SchedulingFunctionSet;

class RV32_OOO_PerformanceModel : public PerformanceModel
{
public:

  RV32_OOO_PerformanceModel() : PerformanceModel("RV32_OOO", RV32_OOO_SchedulingFunctionSet)
    ,IB_stage_OoO(4,0)
    ,EX_stage_mul_NoB(2,0)
    ,EX_stage_lsu_NoB(2,0)
    ,WB_stage_NoB(4,0)
    ,regModel(this)
    ,noBranchPredModel(this)
    ,clobberModel(this)
    ,scheduleModel(this)
  {};

  // Entrance-point "timing variable" (only used for info-stream)
  uint64_t entrancePoint = 0;

  // Single-Element Timing Variables
  uint64_t PC_stage = 0;
  uint64_t IF_stage = 0;
  uint64_t IS_stage = 0;
  uint64_t EX_stage_div_NoB = 0;
  uint64_t EX_stage_mul0v_NoB = 0;
  uint64_t EX_stage_mul1v_NoB = 0;
  uint64_t EX_stage_br_NoB = 0;
  uint64_t EX_stage_alu_NoB = 0;
  uint64_t EX_stage_lu0v_NoB = 0;
  uint64_t EX_stage_lu1v_NoB = 0;
  uint64_t EX_stage_suv_NoB = 0;

  // Multi-Element Timing Variables
  MultiElementTimingVariable IB_stage_OoO;
  MultiElementTimingVariable EX_stage_mul_NoB;
  MultiElementTimingVariable EX_stage_lsu_NoB;
  MultiElementTimingVariable WB_stage_NoB;

  // External Resource Models
  RV32_OOO::OoORegisterModel regModel;
  RV32_OOO::NoBranchPredictModel noBranchPredModel;
  RV32_OOO::ClobberModel clobberModel;
  RV32_OOO::Scheduler scheduleModel;

  virtual void connectChannel(Channel*);
  virtual uint64_t getCycleCount(void);
  virtual std::string getPipelineStream(void);
  virtual std::string getPrintHeader(void);

};

} // namespace RV32_OOO

#endif // SWEVAL_BACKENDS_RV32_OOO_PERFORMANCE_MODEL_H