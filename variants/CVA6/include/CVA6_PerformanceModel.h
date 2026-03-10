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


#ifndef SWEVAL_BACKENDS_CVA6_PERFORMANCE_MODEL_H
#define SWEVAL_BACKENDS_CVA6_PERFORMANCE_MODEL_H

#include <stdbool.h>
#include <string>
#include <cstdint>

#include "PerformanceModel.h"
#include "Channel.h"

#include "models/common/StandardRegisterModel.h"
#include "models/cva6/BranchPredictionModel.h"
#include "models/cva6/ClobberModel.h"
#include "models/cva6/ICacheModel.h"
#include "models/cva6/DividerModel.h"
#include "models/cva6/DividerUnsignedModel.h"
#include "models/cva6/DCacheModel.h"

namespace CVA6{

// Node Types for Scheduling function
// currently only Stages
enum F_Type {
    EMPTY,
    // Order matters (Stage -> Substage -> Resource)
    COM_stage,
    EX_stage,
    IS_stage,
    ID_stage,
    IQ_stage,
    IF_stage,
    PC_stage,
    
    EX_substage_sUnit,
    EX_substage_sCtrl,
    EX_substage_lUnit,
    EX_substage_dCache,
    EX_substage_lCtrl,
    EX_substage_div,
    EX_substage_mul_o,
    EX_substage_mul_i,
    EX_substage_alu,
    
    IF_substage_2,
    IF_substage_1,
    IF_substage_0,

    F_SIZE
};

const uint32_t F_Capacities[]{
    1, //EMPTY,
    // Order matters (Stage -> Substage -> Resource)
    2, //COM_stage,
    8, //EX_stage,
    1, //IS_stage,
    1, //ID_stage,
    7, //IQ_stage,
    3, //IF_stage,
    1, //PC_stage,
    
    1, //EX_substage_sUnit,
    1, //EX_substage_sCtrl,
    1, //EX_substage_lUnit,
    1, //EX_substage_dCache,
    1, //EX_substage_lCtrl,
    1, //EX_substage_div,
    1, //EX_substage_mul_o,
    1, //EX_substage_mul_i,
    1, //EX_substage_alu,

    1, //IF_substage_2,
    1, //IF_substage_1,
    1, //IF_substage_0,
    
    1 //F_SIZE
};

extern SchedulingFunctionSet* CVA6_SchedulingFunctionSet;

class CVA6_PerformanceModel : public PerformanceModel
{
public:

  CVA6_PerformanceModel() : PerformanceModel("CVA6", CVA6_SchedulingFunctionSet, F_Type::F_SIZE)
    ,regModel(this)
    ,dynBranchPredModel(this)
    ,clobberModel(this)
    ,iCacheModel(this)
    ,divider(this)
    ,divider_u(this)
    ,dCacheModel(this)
  {
    graph.init_capacity(F_Capacities);

    nodes_PC.push_back(0);
    nodes_IF.push_back(0);
    nodes_IQ.push_back(0);
    nodes_ID.push_back(0);
    nodes_IS.push_back(0);
    nodes_EX.push_back(0);
    nodes_COM.push_back(0);
  };

  // Entrance-point "timing variable" (only used for info-stream)
  uint64_t entrancePoint = 0;

  // Result Node IDs
  std::vector<uint64_t> nodes_PC;
  std::vector<uint64_t> nodes_IF;
  std::vector<uint64_t> nodes_IQ;
  std::vector<uint64_t> nodes_ID;
  std::vector<uint64_t> nodes_IS;
  std::vector<uint64_t> nodes_EX;
  std::vector<uint64_t> nodes_COM;

  uint64_t last_IF_substage = 0;
  uint64_t last_EX_substage = 0;

  uint64_t last_EX_alu = 0;
  uint64_t last_EX_mul_i = 0;
  uint64_t last_EX_mul_o = 0;
  uint64_t last_EX_div = 0;
  uint64_t last_EX_sCtrl = 0;
  uint64_t last_EX_lCtrl = 0;

  uint64_t current_print = 1;

  // External Resource Models
  common::StandardRegisterModel regModel;
  cva6::BranchPredictionModel dynBranchPredModel;
  cva6::ClobberModel clobberModel;
  cva6::ICacheModel iCacheModel;
  cva6::DividerModel divider;
  cva6::DividerUnsignedModel divider_u;
  cva6::DCacheModel dCacheModel;

  virtual void connectChannel(Channel*);
  virtual uint64_t getCycleCount(void);
  virtual std::string getPipelineStream(void);
  virtual std::string getPrintHeader(void);
  virtual uint64_t getLastEntryNode(void);

};

} // namespace CVA6

#endif // SWEVAL_BACKENDS_CVA6_PERFORMANCE_MODEL_H