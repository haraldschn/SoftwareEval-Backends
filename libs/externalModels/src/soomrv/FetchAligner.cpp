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

// TODO: Proof-of-concept model!
// Only considers non-compressed instructions

#include "models/soomrv/FetchAligner.h"

#include <cstdint>
#include <string>
#include <sstream>

namespace soomrv {

// int FetchAligner::getDelay(void) {
//     return 1;
// }

void FetchAligner::setPCGen_in(uint64_t c_) {
    uint64_t pc = pc_ptr[getInstrIndex()];
    
    //printf("%x:", (uint32_t)pc);

    //printf("\t%d", c_);
    IF_start_next = c_-1;
    //printf("\n");
}

uint64_t FetchAligner::getPCGen_out(void) { 

    uint64_t pc = pc_ptr[getInstrIndex()];
    
    int fetch_delay = ALIGNED_DELAY;
    if (pc == INITIAL_PC) {
        pc_prev = pc;
        return 1;
    } else if ((pc - pc_prev) != 4) {
        fetch_delay = UNALIGNED_DELAY;
    } else if ((pc & 0xF) == 0x0) {
        fetch_delay = UNALIGNED_DELAY;
    }

    pc_prev = pc;
    
    return IF_start_next + fetch_delay; 
}

}  // namespace soomrv
