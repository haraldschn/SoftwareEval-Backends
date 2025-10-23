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

#ifndef RV32_OOO_SCHEDULER_H
#define RV32_OOO_SCHEDULER_H

#include "PerformanceModel.h"
#include <cstdint>
#include <queue>
#include <stack>

namespace rv32_ooo {

// Functional Unit set at Decode stage
enum F_Type {
    EMPTY,
    DIV,
    MUL,
    BR,
    ALU,
    ST,
    LD,
    F_SIZE
};

class Scheduler : public ConnectorModel {
   public:
    Scheduler(PerformanceModel* parent_) : ConnectorModel("RV32_OOO_Scheduler", parent_) {};

    uint64_t* pc_ptr;
    uint64_t* rs1_ptr;
    uint64_t* rs2_ptr;
    uint64_t* rd_ptr;

    // included RegisterModel in this scheduler (need for gettign issue time)
    uint64_t getXa(void) {
        earliest_issue = std::max(earliest_issue, registerModel[rs1_ptr[getInstrIndex()]]);
        return registerModel[rs1_ptr[getInstrIndex()]];
    };
    uint64_t getXb(void) {
        earliest_issue = std::max(earliest_issue, registerModel[rs2_ptr[getInstrIndex()]]);
        return registerModel[rs2_ptr[getInstrIndex()]];
    };
    void setXd(uint64_t xd_) { 
        registerModel[rd_ptr[getInstrIndex()]] = xd_; 
    };

    void setDec_div(uint64_t x_);
    void setDec_mul(uint64_t x_);
    void setDec_br(uint64_t x_);
    void setDec_alu(uint64_t x_);
    void setDec_st(uint64_t x_);
    void setDec_ld(uint64_t x_);
    void setT_wb(uint64_t x_);

    uint64_t getT_issue(void);


   private:
    uint64_t registerModel[64] = {0};

    F_Type instr_type = F_Type::EMPTY;

    uint64_t issue_time = 0;
    // Issue time considering max(DEC, OF_A, OF_B) (op_fetch are only considered if microactions available)
    uint64_t earliest_issue = 0;
    // Stores initially previous wb_time
    uint64_t next_issue = 0;

    std::priority_queue<uint64_t> fu_avail[F_Type::F_SIZE];
    void find_possible_issue(int II_delay, F_Type instr);
};

}  // namespace rv32_ooo

#endif  // RV32_OOO_SCHEDULER_H