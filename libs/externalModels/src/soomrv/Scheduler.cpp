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

#include "models/soomrv/Scheduler.h"

#include <cstdint>
#include <string>
#include <sstream>

namespace soomrv {

int Scheduler::getDelay(void) {
    // DELAY for LD and ALU Stages
    int delay = 1;

    if (instr_type == ALU_Type::LUI || instr_type == ALU_Type::JAL) {
        delay = 0;
    }

    return delay;
}

std::string getInstrString(ALU_Type type) {
    switch (type) {
        case ALU_Type::LUI:
            return "ALU_INT (ADDI / LUI)";
        case ALU_Type::INT:
            return "ALU_INT";
        case ALU_Type::MUL:
            return "ALU_MUL";
        case ALU_Type::DIV:
            return "ALU_DIV";
        case ALU_Type::BR:
            return "ALU_BRANCH";
        case ALU_Type::JAL:
            return "ALU_JAL";
        case ALU_Type::CSR:
            return "ALU_CSR";
        default:
            return "???";
    }
}

uint64_t Scheduler::getIssue_ALU(void) {
    earliest_scheduling = rn_cycle + 2;

    switch (instr_type) {
        case ALU_Type::LUI:
            // LUI (pseudo ADDI with rs1/rs2 == 0)
            // only RN -> Commit
            earliest_scheduling = rn_cycle;
            break;
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
        case ALU_Type::JAL:
            // JAL with RD==0
            // only RN -> Commit
            earliest_scheduling = rn_cycle;
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

    // std::cout << earliest_scheduling << std::endl;
    return earliest_scheduling;
};

void Scheduler::setRn_ADDI(uint64_t c_) {
    rn_cycle = c_;
    if (rs1_ptr[getInstrIndex()] == 0) {
        instr_type = ALU_Type::LUI;
    } else {
        instr_type = ALU_Type::INT;
    }
};
void Scheduler::setRn_INT(uint64_t c_) {
    rn_cycle = c_;
    instr_type = ALU_Type::INT;
};
void Scheduler::setRn_MUL(uint64_t c_) {
    rn_cycle = c_;
    instr_type = ALU_Type::MUL;
};
void Scheduler::setRn_BR(uint64_t c_) {
    rn_cycle = c_;
    instr_type = ALU_Type::BR;
};
void Scheduler::setRn_JAL(uint64_t c_) {
    rn_cycle = c_;
    if (rd_ptr[getInstrIndex()] == 0) {
        instr_type = ALU_Type::JAL;
    } else {
        instr_type = ALU_Type::BR;
    }
};
void Scheduler::setRn_CSR(uint64_t c_) {
    rn_cycle = c_;
    instr_type = ALU_Type::CSR;
};
void Scheduler::setRn_DIV(uint64_t c_) {
    rn_cycle = c_;
    instr_type = ALU_Type::DIV;
};

void Scheduler::setEX_Alu(uint64_t c_) {
    if (instr_type == ALU_Type::MUL) {
        alu_avail[selected_alu] = c_ - 1 - 3; // Correction for pipelined multiply
    } else if (instr_type != ALU_Type::EMPTY || instr_type != ALU_Type::LUI || instr_type != ALU_Type::JAL) {
        alu_avail[selected_alu] = c_ - 1;
    }
    ex_cycle = c_;
};
void Scheduler::setCOM_Alu(uint64_t c_) {
    // Written at uA_WFC_alu
    com_cycle = c_ + 1;
    // if (instr_type != ALU_Type::EMPTY) {
    //     std::cout << "ALU-Instruction " << getInstrString(instr_type)
    //               << " rename finished at " << rn_cycle
    //               << " execute finished at " << ex_cycle
    //               << " in ALU_" << (selected_alu+1)
    //               << " commited at " << com_cycle << std::endl;
    // }
    instr_type = ALU_Type::EMPTY;
};

}  // namespace soomrv
