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

#include "models/rv32_ooo/Scheduler.h"

#include <cstdint>
#include <string>
#include <sstream>

namespace rv32_ooo {

void Scheduler::setDec_div(uint64_t x_) {
    instr_type = F_Type::DIV;
    issue_time = x_;
    earliest_issue = issue_time;
}

void Scheduler::setDec_mul(uint64_t x_) {
    instr_type = F_Type::MUL;
    issue_time = x_;
    earliest_issue = issue_time;
}

void Scheduler::setDec_br(uint64_t x_) {
    instr_type = F_Type::BR;
    issue_time = x_;
    earliest_issue = issue_time;
}

void Scheduler::setDec_alu(uint64_t x_) {
    instr_type = F_Type::ALU;
    issue_time = x_;
    earliest_issue = issue_time;
}

void Scheduler::setDec_st(uint64_t x_) {
    instr_type = F_Type::ST;
    issue_time = x_;
    earliest_issue = issue_time;
}

void Scheduler::setDec_ld(uint64_t x_) {
    instr_type = F_Type::LD;
    issue_time = x_;
    earliest_issue = issue_time;
}

void Scheduler::setT_wb(uint64_t x_) {
    next_issue = x_;

    // WB times < 2 would lead to error
    if (x_ < 2) {
        exit(1);
    }

    switch (instr_type) {
        case F_Type::DIV:
            fu_avail[instr_type].push(x_ - 1);
            break;
        case F_Type::MUL:
            // MUL pipelined (Latency: 2, II: 1)
            fu_avail[instr_type].push(x_ - 2);
            break;
        case F_Type::BR:
            fu_avail[instr_type].push(x_ - 1);
            break;
        case F_Type::ALU:
            fu_avail[instr_type].push(x_ - 1);
            break;
        case F_Type::ST:
            fu_avail[F_Type::ST].push(x_ - 1);
            fu_avail[F_Type::LD].push(x_ - 1);
            break;
        case F_Type::LD:
            // LSU pipelined (Latency: 2, II: 1)
            // Blocks store (LSU for all available after at WB, else pipelining possible)
            fu_avail[F_Type::ST].push(x_ - 1);
            fu_avail[F_Type::LD].push(x_ - 2);
            break;
        default:
            break;
    }

    instr_type = F_Type::EMPTY;
}

// Test scheduler with ASAP scheduling along individual functional units
uint64_t Scheduler::getT_issue(void) {
    switch (instr_type) {
        case F_Type::DIV:
            next_issue = earliest_issue;
            find_possible_issue(4, instr_type);
            break;
        case F_Type::MUL:
            next_issue = earliest_issue;
            find_possible_issue(1, instr_type);
            break;
        case F_Type::BR: {
            for (int i = 0; i < F_SIZE; i++) {
                next_issue = fu_avail[i].empty() ? next_issue : std::max(next_issue, fu_avail[i].top());
            }
            }
            // next_issue = earliest_issue;
            // find_possible_issue(1, instr_type);
            break;  
        case F_Type::ALU:
            next_issue = earliest_issue;
            find_possible_issue(1, instr_type);
            break;
        case F_Type::ST:
            next_issue = earliest_issue;
            find_possible_issue(1, instr_type);
            break;
        case F_Type::LD:
            if (fu_avail[F_Type::ST].empty() || fu_avail[F_Type::LD].empty()) {
                next_issue = 0;
            } else if ((fu_avail[F_Type::ST].top() - fu_avail[F_Type::LD].top()) == 1) {
                next_issue = earliest_issue;
                find_possible_issue(1, F_Type::LD);
            } else {
                next_issue = earliest_issue;
                find_possible_issue(1, F_Type::ST);
            }
            break;

        default:
            break;
    }

    std::cout << std::hex << pc_ptr[getInstrIndex()] << std::dec << " issued at: " << std::max(next_issue, earliest_issue) << std::endl;
    ;
    return std::max(next_issue, earliest_issue);
    // return earliest_issue;
}

void Scheduler::find_possible_issue(int II_delay, F_Type instr) {
    std::stack<uint64_t> temp_stack;

    uint64_t issue_possible = 0;
    if (!fu_avail[instr].empty()) {
        issue_possible = fu_avail[instr].top();
    }

    while (!fu_avail[instr].empty() && (fu_avail[instr].top() - II_delay) > earliest_issue) {
        uint64_t temp = fu_avail[instr].top();
        fu_avail[instr].pop();
        temp_stack.push(temp);

        if (!fu_avail[instr].empty() && (temp - fu_avail[instr].top()) > II_delay) {
            issue_possible = fu_avail[instr].top();
        }
    }
    // FU can be used earliest at this available time
    while (!temp_stack.empty()) {
        uint64_t temp = temp_stack.top();
        temp_stack.pop();
        fu_avail[instr].push(temp);
    }

    next_issue = issue_possible;
}

}  // namespace rv32_ooo