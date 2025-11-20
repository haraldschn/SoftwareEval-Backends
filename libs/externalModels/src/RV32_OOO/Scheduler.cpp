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

#include "models/RV32_OOO/Scheduler.h"
#include "RV32_OOO_PerformanceModel.h"

#include <cstdint>

namespace RV32_OOO {

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

// Test scheduler with list-scheduling (implemented in class DependencyGraph)
uint64_t Scheduler::getT_issue(void) {
    RV32_OOO_PerformanceModel* perfModel = static_cast<RV32_OOO_PerformanceModel*>(perfModel_);

    if (rs1_ptr[getInstrIndex()] > 0 && rs1_ptr[getInstrIndex()] < 32) {
        // RAW edge
        if (last_reg_write[rs1_ptr[getInstrIndex()]] > 0) {
            dpg.add_edge_RAW(last_reg_write[rs1_ptr[getInstrIndex()]], node_number);
        }

        last_reg_reads[rs1_ptr[getInstrIndex()]].insert(node_number);
        earliest_issue = std::max(earliest_issue, perfModel->regModel.getXa());
    }

    if (rs2_ptr[getInstrIndex()] > 0 && rs2_ptr[getInstrIndex()] < 32) {
        // RAW edge
        if (last_reg_write[rs2_ptr[getInstrIndex()]] > 0) {
            dpg.add_edge_RAW(last_reg_write[rs2_ptr[getInstrIndex()]], node_number);
        }

        last_reg_reads[rs2_ptr[getInstrIndex()]].insert(node_number);
        earliest_issue = std::max(earliest_issue, perfModel->regModel.getXb());
    }

    uint64_t update_register[32] = {0};

    next_issue = dpg.schedule(node_number, earliest_issue, update_register);

    for (uint64_t i = 1; i < 32; i++) {
        if (update_register[i] != 0) {
            std::cout << "update rd: " << i << " with t:" << update_register[i] << "\n";
            perfModel->regModel.updateXd(update_register[i], i);
        }
    }

    return earliest_issue;
}

void Scheduler::setT_wb(uint64_t x_) {
    if (rd_ptr[getInstrIndex()] > 0 && rd_ptr[getInstrIndex()] < 32) {
        // Ignore WAR and WAW hazards (i.e. using RegisterRenaming with always enough register available)
        /*
        // WAR
        if(last_reg_reads[rd_ptr[getInstrIndex()]].empty()) {
            for (int rline : last_reg_reads[rd_ptr[getInstrIndex()]]) {
                dpg.add_edge_WAR(last_reg_write[rd_ptr[getInstrIndex()]], node_number);
            }
        }

        // WAW
        if(last_reg_write[rd_ptr[getInstrIndex()]] > 0) {
            dpg.add_edge_WAW(last_reg_write[rd_ptr[getInstrIndex()]], node_number);
        }
        */

        last_reg_write[rd_ptr[getInstrIndex()]] = node_number;
        last_reg_reads[rd_ptr[getInstrIndex()]].clear();

        dpg.set_node_rd(node_number, rd_ptr[getInstrIndex()]);
    }

    dpg.get_WB_time(node_number, x_);

    instr_type = F_Type::EMPTY;
}

}  // namespace RV32_OOO