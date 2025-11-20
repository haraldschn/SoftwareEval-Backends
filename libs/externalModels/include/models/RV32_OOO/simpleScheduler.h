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

namespace RV32_OOO {

// Functional Unit set at Decode stage
enum F_Type {
    EMPTY,
    DIV,
    MUL,
    BR,
    ALU,
    ST,
    LD
};

class Scheduler : public ConnectorModel {
   public:
    Scheduler(PerformanceModel* parent_) : ConnectorModel("RV32_OOO_Scheduler", parent_) {};

    uint64_t* pc_ptr;
    uint64_t* rs1_ptr;
    uint64_t* rs2_ptr;
    uint64_t* rd_ptr;

    void setDec_div(uint64_t x_);
    void setDec_mul(uint64_t x_);
    void setDec_br(uint64_t x_);
    void setDec_alu(uint64_t x_);
    void setDec_st(uint64_t x_);
    void setDec_ld(uint64_t x_);
    void setT_wb(uint64_t x_);

    uint64_t getT_issue(void);

   private:
    F_Type instr_type = F_Type::EMPTY;

    uint64_t issue_time = 0;
    // Stores previous wb_time
    uint64_t wb_time = 0;

    uint64_t div_avail = 0;
    uint64_t mul_avail = 0;
    uint64_t br_avail = 0;
    uint64_t alu_avail = 0;
    uint64_t lsu_avail = 0;
    uint64_t lu_avail = 0;
    
};

}  // namespace RV32_OOO

#endif  // RV32_OOO_SCHEDULER_H