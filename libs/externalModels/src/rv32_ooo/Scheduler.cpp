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

#include "models/rv32_ooo/Scheduler.h"

#include <cstdint>

namespace rv32_ooo {

void Scheduler::setDec_div(uint64_t x_) {
    instr_type = F_Type::DIV;
    earliest_issue = x_;

    node_number = dpg.add_node(F_Type::DIV, earliest_issue);
}

void Scheduler::setDec_mul(uint64_t x_) {
    instr_type = F_Type::MUL;
    earliest_issue = x_;

    node_number = dpg.add_node(F_Type::MUL, earliest_issue, 2);
}

void Scheduler::setDec_br(uint64_t x_) {
    instr_type = F_Type::BR;
    earliest_issue = x_;

    node_number = dpg.add_node(F_Type::BR, earliest_issue);
}

void Scheduler::setDec_alu(uint64_t x_) {
    instr_type = F_Type::ALU;
    earliest_issue = x_;

    node_number = dpg.add_node(F_Type::ALU, earliest_issue);
}

void Scheduler::setDec_st(uint64_t x_) {
    instr_type = F_Type::LSU;
    earliest_issue = x_;

    node_number = dpg.add_node(F_Type::LSU, earliest_issue, 1);

    last_mem_write[addr_ptr[getInstrIndex()]] = node_number;
    last_mem_reads[addr_ptr[getInstrIndex()]].clear();
}

void Scheduler::setDec_ld(uint64_t x_) {
    instr_type = F_Type::LSU;
    earliest_issue = x_;

    node_number = dpg.add_node(F_Type::LSU, earliest_issue, 2);

    last_mem_reads[addr_ptr[getInstrIndex()]].insert(node_number);
}

void Scheduler::setT_wb(uint64_t x_) {
    dpg.get_WB_time(node_number, x_);

    instr_type = F_Type::EMPTY;
}

// Test scheduler with list-scheduling (implemented in class DependencyGraph)
uint64_t Scheduler::getT_issue(void) {
    next_issue = dpg.schedule(node_number, earliest_issue);

    return earliest_issue;
}

}  // namespace rv32_ooo