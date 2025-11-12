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


#ifndef SWEVAL_BACKENDS_SOOMRV_PERFORMANCE_MODEL_H
#define SWEVAL_BACKENDS_SOOMRV_PERFORMANCE_MODEL_H

#include <stdbool.h>
#include <string>
#include <cstdint>

#include "PerformanceModel.h"
#include "Channel.h"

#include "models/soomrv/RegisterModel.h"
#include "models/soomrv/BranchPredictionModel.h"
#include "models/soomrv/ICacheModel.h"
#include "models/soomrv/DCacheModel.h"
#include "models/soomrv/FetchAligner.h"
#include "models/soomrv/Scheduler.h"

namespace SOOMRV{

extern SchedulingFunctionSet* SOOMRV_SchedulingFunctionSet;

class SOOMRV_PerformanceModel : public PerformanceModel
{
public:

  SOOMRV_PerformanceModel() : PerformanceModel("SOOMRV", SOOMRV_SchedulingFunctionSet)
    ,IF_stage(16,0)
    ,PC_substage(4,0)
    ,IF_substage_0(4,0)
    ,IF_substage_1(4,0)
    ,IF_substage_2(4,0)
    ,DEC_stage(4,0)
    ,RN_stage(4,0)
    ,IS_substage_alu_OoO(24,0)
    ,LD_substage_alu_OoO(64,0)
    ,EX_stage_alu_OoO(64,0)
    ,WFC_stage_alu(64,0)
    ,IS_substage_agu(16,0)
    ,LD_substage_agu(2,0)
    ,EX_stage_agu(64,0)
    ,WFC_stage_agu(64,0)
    ,COM_stage(4,0)
    ,regModel(this)
    ,dynBranchPredModel(this)
    ,iCacheModel(this)
    ,dCacheModel(this)
    ,fetchAligner(this)
    ,schedModel(this)
  {};

  // Entrance-point "timing variable" (only used for info-stream)
  uint64_t entrancePoint = 0;


  // Multi-Element Timing Variables
  MultiElementTimingVariable IF_stage;
  MultiElementTimingVariable PC_substage;
  MultiElementTimingVariable IF_substage_0;
  MultiElementTimingVariable IF_substage_1;
  MultiElementTimingVariable IF_substage_2;
  MultiElementTimingVariable DEC_stage;
  MultiElementTimingVariable RN_stage;
  MultiElementTimingVariable IS_substage_alu_OoO;
  MultiElementTimingVariable LD_substage_alu_OoO;
  MultiElementTimingVariable EX_stage_alu_OoO;
  MultiElementTimingVariable WFC_stage_alu;
  MultiElementTimingVariable IS_substage_agu;
  MultiElementTimingVariable LD_substage_agu;
  MultiElementTimingVariable EX_stage_agu;
  MultiElementTimingVariable WFC_stage_agu;
  MultiElementTimingVariable COM_stage;

  // External Resource Models
  soomrv::RegisterModel regModel;
  soomrv::BranchPredictionModel dynBranchPredModel;
  soomrv::ICacheModel iCacheModel;
  soomrv::DCacheModel dCacheModel;
  soomrv::FetchAligner fetchAligner;
  soomrv::Scheduler schedModel;

  virtual void connectChannel(Channel*);
  virtual uint64_t getCycleCount(void);
  virtual std::string getPipelineStream(void);
  virtual std::string getPrintHeader(void);

};

} // namespace SOOMRV

#endif // SWEVAL_BACKENDS_SOOMRV_PERFORMANCE_MODEL_H