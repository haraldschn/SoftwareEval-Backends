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

// TODO: OoO Scheduler - External Model to allow OoO Issue (i.e. process from Issue Queue -> LD -> EX)

#ifndef RV32_4ISSUE_SCHEDULER_MODEL_H
#define RV32_4ISSUE_SCHEDULER_MODEL_H

#include <stdbool.h>
#include <cstdint>
#include <string>

#include "PerformanceModel.h"

namespace rv32_4issue {

enum ALU_Type {
    EMPTY,
    INT,
    MUL,
    DIV,
    BR,
    CSR
};

class Scheduler : public ConnectorModel {
   public:
    // TODO: Check if delays are matching observations!
    Scheduler(PerformanceModel* parent_) : ConnectorModel("Scheduler", parent_) {};

    uint64_t getIssue_ALU(void);
    uint64_t getLookUP_ALU(void);

    void setDec_INT(uint64_t c_);
    void setDec_MUL(uint64_t c_);
    void setDec_BR(uint64_t c_);
    void setDec_CSR(uint64_t c_);
    void setDec_DIV(uint64_t c_);

    void setEX_Alu(uint64_t c_);
    void setCOM_Alu(uint64_t c_);

    // Trace value
    uint64_t* pc_ptr;

   private:
    ALU_Type instr_type = ALU_Type::EMPTY;
    uint64_t dec_cycle = 0;
    uint64_t ex_cycle = 0;
    uint64_t com_cycle = 0;

    uint64_t earliest_scheduling = 0;

    int selected_alu = 0;

    //FU_INT_OH|FU_MUL_OH
    //FU_INT_OH|FU_BRANCH_OH|FU_MUL_OH
    //FU_INT_OH|FU_BRANCH_OH|FU_DIV_OH|FU_CSR_OH
    uint64_t alu_avail[3] = {0, 0, 0};
};

}  // namespace rv32_4issue

#endif  // RV32_4ISSUE_SCHEDULER_MODEL_H