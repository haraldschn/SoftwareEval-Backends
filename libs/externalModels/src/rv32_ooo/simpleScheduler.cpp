/*
 * Copyright 2024 Chair of EDA, Technical University of Munich
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

#include "models/rv32_ooo/simpleScheduler.h"

#include <cstdint>
#include <string>
#include <sstream>

namespace rv32_ooo{

void Scheduler::setDec_div(uint64_t x_) {
    instr_type = F_Type::DIV;
    issue_time = x_;
}

void Scheduler::setDec_mul(uint64_t x_) {
    instr_type = F_Type::MUL;
    issue_time = x_;
}

void Scheduler::setDec_br(uint64_t x_) {
    instr_type = F_Type::BR;
    issue_time = x_;
}

void Scheduler::setDec_alu(uint64_t x_) {
    instr_type = F_Type::ALU;
    issue_time = x_;
}

void Scheduler::setDec_st(uint64_t x_) {
    instr_type = F_Type::ST;
    issue_time = x_;
}

void Scheduler::setDec_ld(uint64_t x_) {
    instr_type = F_Type::LD;
    issue_time = x_;
}

void Scheduler::setT_wb(uint64_t x_) {
    wb_time = x_;

    // WB times < 2 would lead to error
    if (x_ < 2) {
        exit(1);
    } 

    switch (instr_type)
    {
    case F_Type::DIV:
        div_avail = x_ - 1;
        break;
    case F_Type::MUL:
        // MUL pipelined (Latency: 2, II: 1)
        mul_avail = x_ - 2; 
        break;
    case F_Type::BR:
        br_avail = x_ - 1;
        break;
    case F_Type::ALU:
        alu_avail = x_ - 1;
        break;
    case F_Type::ST:
        lsu_avail = x_ - 1;
        break;
    case F_Type::LD:
        // LSU pipelined (Latency: 2, II: 1)
        // Blocks store (LSU for all available after at WB, else pipelining possible)
        lsu_avail = x_ - 1;
        lu_avail = x_ - 2; 
        break;

    default:
        break;
    }

    instr_type = F_Type::EMPTY;
}

// Test scheduler with ASAP scheduling along individual functional units
uint64_t Scheduler::getT_issue(void) {

    switch (instr_type)
    {
    case F_Type::DIV:
        wb_time = div_avail;
        break;
    case F_Type::MUL:
        wb_time = mul_avail;
        break;
    case F_Type::BR:
        wb_time = br_avail;
        break;
    case F_Type::ALU:
        wb_time = alu_avail;
        break;
    case F_Type::ST:
        wb_time = lsu_avail;
        break;
    case F_Type::LD:
        if ((lsu_avail - lu_avail) == 1) {
            wb_time = lu_avail;
        } else {
            wb_time = lsu_avail;
        }
        break;

    default:
        break;
    }

    return wb_time;
}

/* 
// Test scheduler with simple in-order scheduling along all functional units
uint64_t Scheduler::getT_issue(void) {
    std::cout << std::hex << pc_ptr[getInstrIndex()] << std::dec;

    switch (instr_type)
    {
    case F_Type::DIV:
        std::cout << ": issue DIV" << std::endl;
        break;
    case F_Type::MUL:
        std::cout << ": issue MUL" << std::endl;
        break;
    case F_Type::BR:
        std::cout << ": issue ADD (i.e. BR)" << std::endl;
        break;
    case F_Type::ALU:
        std::cout << ": issue ALU" << std::endl;
        break;
    case F_Type::ST:
        std::cout << ": issue LSU (ST)" << std::endl;
        break;
    case F_Type::LD:
        std::cout << ": issue LSU (LD)" << std::endl;
        break;

    default:
        break;
    }

    if (wb_time > 0) {
        return wb_time-1;
    }
    return 0;
} 
*/

    
} // namespace common