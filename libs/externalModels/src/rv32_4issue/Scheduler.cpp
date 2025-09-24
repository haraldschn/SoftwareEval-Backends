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

#include "models/rv32_4issue/Scheduler.h"

#include <cstdint>
#include <string>
#include <sstream>

namespace rv32_4issue {


std::string getInstrString(ALU_Type type)
{
    switch (type)
    {
    case ALU_Type::INT: return "ALU_INT";
    case ALU_Type::MUL: return "ALU_MUL";
    case ALU_Type::DIV: return "ALU_DIV";
    case ALU_Type::BR: return "ALU_BRANCH";
    case ALU_Type::CSR: return "ALU_CSR";
    default:    return "???";
    }
}

uint64_t Scheduler::getIssue_ALU(void) {
    earliest_scheduling = dec_cycle+3;

    switch (instr_type)
    {
    case ALU_Type::INT:
        if (alu_avail[0] <= alu_avail[1] && alu_avail[0] <= alu_avail[2]) {
            earliest_scheduling = std::max(earliest_scheduling, alu_avail[0]);
            selected_alu = 0;
        } else if (alu_avail[1] <= alu_avail[2]) {
            earliest_scheduling = std::max(earliest_scheduling, alu_avail[1]);
            selected_alu = 1;
        } else {
            earliest_scheduling = std::max(earliest_scheduling, alu_avail[2]);
            selected_alu = 2;
        }
        break;
    case ALU_Type::MUL:
        if (alu_avail[0] <= alu_avail[1]) {
            earliest_scheduling = std::max(earliest_scheduling, alu_avail[0]);
            selected_alu = 0;
        } else {
            earliest_scheduling = std::max(earliest_scheduling, alu_avail[1]);
            selected_alu = 1;
        }
        break;
    case ALU_Type::DIV:
        earliest_scheduling = std::max(earliest_scheduling, alu_avail[2]);
        selected_alu = 2;
        break;
    case ALU_Type::BR:
        if (alu_avail[1] <= alu_avail[2]) {
            earliest_scheduling = std::max(earliest_scheduling, alu_avail[1]);
            selected_alu = 1;
        } else {
            earliest_scheduling = std::max(earliest_scheduling, alu_avail[2]);
            selected_alu = 2;
        }
        break;
    case ALU_Type::CSR:
        // CSR earliest scheduling 1 cycle after previous commit
        earliest_scheduling = std::max(com_cycle + 1, alu_avail[2]);
        selected_alu = 2;
        break;
    
    default:
        std::cout << "Scheduler.cpp Error: Not defined ALU_Type in Stage Issue_ALU";
        break;
    }

    //std::cout << earliest_scheduling << std::endl;
    return earliest_scheduling; 
};

uint64_t Scheduler::getLookUP_ALU(void) {
    return earliest_scheduling+1;
}

void Scheduler::setDec_INT(uint64_t c_) {
    dec_cycle = c_;
    instr_type = ALU_Type::INT;
};
void Scheduler::setDec_MUL(uint64_t c_) {
    dec_cycle = c_;
    instr_type = ALU_Type::MUL;
};
void Scheduler::setDec_BR(uint64_t c_) {
    dec_cycle = c_;
    instr_type = ALU_Type::BR;
};
void Scheduler::setDec_CSR(uint64_t c_) {
    dec_cycle = c_;
    instr_type = ALU_Type::CSR;
};
void Scheduler::setDec_DIV(uint64_t c_) {
    dec_cycle = c_;
    instr_type = ALU_Type::DIV;
};

void Scheduler::setEX_Alu(uint64_t c_) {
    if (instr_type != ALU_Type::EMPTY) {
        alu_avail[selected_alu] = c_-1;
    }
    ex_cycle = c_; 
};
void Scheduler::setCOM_Alu(uint64_t c_) {
    // Written at uA_WFC_alu
    com_cycle = c_ + 1;
    // if (instr_type != ALU_Type::EMPTY) {
    //     std::cout << "ALU-Instruction " << getInstrString(instr_type)
    //               << " decode finished at " << dec_cycle
    //               << " execute finished at " << ex_cycle
    //               << " in ALU_" << (selected_alu+1)
    //               << " commited at " << com_cycle << std::endl;
    // }
    instr_type = ALU_Type::EMPTY;
};

}  // namespace rv32_4issue
