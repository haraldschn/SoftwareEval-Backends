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
#include "models/RV32_OOO/BranchPredictionModel.h"

#include "models/RV32_OOO/ClobberModel.h"

namespace RV32_OOO {

#define ISSUE_LENGTH 1

// Node Types for Scheduling function
// currently only Stages
enum F_Type {
    EMPTY,
    // Order matters (Parent Stage -> Substage -> Resource)

    // Parent - Stages
    WB_stage,
    IB_stage,
    IS_stage,
    IF_stage,
    PC_stage,

    // Child - Stages
    EX_stage,

    // Execute Substages
    EX_div,
    EX_mul_o,
    EX_mul_i,
    EX_add,
    EX_alu,
    EX_lsu3,
    EX_lsu2,
    EX_lsu,

    F_SIZE
};

const uint32_t F_Capacities[]{
    2, // EMPTY,
    // Order matters (Parent Stage -> Substage -> Resource)

    // Parent - Stages
    4, // WB_stage,
    4, // IB_stage,
    2, // IS_stage,
    2, // IF_stage,
    2, // PC_stage,
    
    // Child - Stages
    1, // EX_stage,

    // Execute Substages
    1, // EX_div,
    1, // EX_mul_o,
    1, // EX_mul_i,
    1, // EX_add,
    1, // EX_alu,
    1, // EX_lsu3,
    1, // EX_lsu2,
    1, // EX_lsu,

    1 // F_SIZE
};

extern SchedulingFunctionSet* RV32_OOO_SchedulingFunctionSet;

class RV32_OOO_PerformanceModel : public PerformanceModel {
   public:
    RV32_OOO_PerformanceModel() : PerformanceModel("RV32_OOO", RV32_OOO_SchedulingFunctionSet, F_Type::F_SIZE), regModel(this), noBranchPredModel(this), clobberModel(this) {
        graph.init_capacity(F_Capacities);

        nodes_PC.push_back(0);
        nodes_IF.push_back(0);
        nodes_IS.push_back(0);
        nodes_IB.push_back(0);
        nodes_EX.push_back(0);
        nodes_WB.push_back(0);
    };

    // Entrance-point "timing variable" (only used for info-stream)
    uint64_t entrancePoint = 0;

    std::vector<uint64_t> nodes_PC;
    std::vector<uint64_t> nodes_IF;
    std::vector<uint64_t> nodes_IS;
    std::vector<uint64_t> nodes_IB;
    std::vector<uint64_t> nodes_EX;  // Get Node type from individual Node
    std::vector<uint64_t> nodes_WB;

    std::vector<std::string> noBranchPredModel_trace;

    uint64_t current_print = 1;

    // External Resource Models
    RV32_OOO::OoORegisterModel regModel;

    // Trying different Branch Predictor Models
    //RV32_OOO::NoBranchPredictModel noBranchPredModel;
    RV32_OOO::BranchPredictModel noBranchPredModel;

    RV32_OOO::ClobberModel clobberModel;

    virtual void connectChannel(Channel*);
    virtual uint64_t getCycleCount(void);
    virtual std::string getPipelineStream(void);
    virtual std::string getPrintHeader(void);

    virtual uint64_t getLastEntryNode(void);
};

}  // namespace RV32_OOO

#endif  // SWEVAL_BACKENDS_RV32_OOO_PERFORMANCE_MODEL_H