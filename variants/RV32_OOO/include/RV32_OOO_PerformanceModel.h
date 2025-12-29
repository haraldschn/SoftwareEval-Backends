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

namespace RV32_OOO{

#define ISSUE_LENGTH 1

// Node Types for Scheduling function
// currently only Stages
enum F_Type {
    EMPTY,
    // Order matters (Stage -> Substage -> Resource)
    PC_stage,
    IF_stage,
    IS_stage,
    IB_stage,
    EX_stage,
    WB_stage,
    EX_div,
    EX_mul,
    Ex_br,
    EX_alu,
    EX_lsu,
    F_SIZE
};

extern SchedulingFunctionSet* RV32_OOO_SchedulingFunctionSet;

class RV32_OOO_PerformanceModel : public PerformanceModel
{
public:

  RV32_OOO_PerformanceModel() : PerformanceModel("RV32_OOO", RV32_OOO_SchedulingFunctionSet)
    ,regModel(this)
    ,noBranchPredModel(this)
    ,clobberModel(this)
  {};

  // Entrance-point "timing variable" (only used for info-stream)
  uint64_t entrancePoint = 0;

  std::vector<uint64_t> nodes_PC;
  std::vector<uint64_t> nodes_IF;
  std::vector<uint64_t> nodes_IS;
  std::vector<uint64_t> nodes_IB;
  std::vector<uint64_t> nodes_EX; // Get Node type from individual Node
  std::vector<uint64_t> nodes_WB;

  std::vector<std::string> staBranchPredModel_trace;

  // External Resource Models
  RV32_OOO::OoORegisterModel regModel;
  RV32_OOO::NoBranchPredictModel noBranchPredModel;
  RV32_OOO::ClobberModel clobberModel;

  virtual void connectChannel(Channel*);
  virtual uint64_t getCycleCount(void);
  virtual std::string getPipelineStream(void);
  virtual std::string getPrintHeader(void);

  virtual uint64_t getLastEntryNode(void);

};

} // namespace RV32_OOO

#endif // SWEVAL_BACKENDS_RV32_OOO_PERFORMANCE_MODEL_H