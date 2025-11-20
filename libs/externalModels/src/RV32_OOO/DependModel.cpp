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

#include "models/RV32_OOO/DependModel.h"

#include <cstdint>
#include <string>
#include <sstream>

namespace RV32_OOO{

void DependModel::setDecodeTime(uint64_t x_) {
    dec_time = x_;
}

uint64_t DependModel::getIssueTime(void) {
    // Test: Finding Register dependecies between instructions in external modul
    //      - What happens if RS1, RS2 or RD are not used by current instruction (one of the previous values ?)
    //      - This would lead to incorrectly determining dependencies (with this approach)

    /*
    std::cout << "instr at pc: " << std::hex << pc_ptr[getInstrIndex()] << " dependency " << std::endl;
    std::cout << rs1_ptr[getInstrIndex()] << std::endl;
    std::cout << rs2_ptr[getInstrIndex()] << std::endl;
    std::cout << rd_ptr[getInstrIndex()] << std::endl;

    if(rs1_ptr[getInstrIndex()] > 32 || rs2_ptr[getInstrIndex()] > 32 || rd_ptr[getInstrIndex()] > 32) {
        exit(1);
    }

    if (rs1_ptr[getInstrIndex()] > 0 && rs1_ptr[getInstrIndex()] < 32) {
        std::cout << "\trs1 on pc:" << register_depency[rs1_ptr[getInstrIndex()]] << std::endl;
    }
    if (rs2_ptr[getInstrIndex()] > 0 && rs2_ptr[getInstrIndex()] < 32) {
        std::cout << "\trs2 on pc:" << register_depency[rs2_ptr[getInstrIndex()]] << std::endl;
    }

    if (rd_ptr[getInstrIndex()] > 0 && rd_ptr[getInstrIndex()] < 32) {
        register_depency[rd_ptr[getInstrIndex()]] = pc_ptr[getInstrIndex()];
    }
    */

    return 0;
}

    
} // namespace RV32_OOO