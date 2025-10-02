/*
 * Copyright 2022 Chair of EDA, Technical University of Munich
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

// TODO: Proof-of-concept model, taken from Robert (more or less)!

#include "models/rv32_4issue/DCacheModel.h"

#include <cstdint>
#include <string>
#include <sstream>

namespace rv32_4issue {

int DCacheModel::getDelay(void) {
    uint64_t addr = addr_ptr[getInstrIndex()];

    // printf("addr=%lx", (uint32_t)addr);

    // TODO: Robert's model calculates an additional delay here if address is blocked by a preceding store!

    if (!cachable(addr)) {
        isMiss = true;
        // printf(", DELAY=%d\n", NOT_CACHABLE_DELAY);
        return NOT_CACHABLE_DELAY;
    }
    if (inCache(addr)) {
        isMiss = false;
        // printf(", DELAY=%d\n", CACHE_DELAY);
        return CACHE_DELAY;
    }
    isMiss = true;
    // printf(", DELAY=%d\n", MEMORY_DELAY);
    return MEMORY_DELAY;
}

bool DCacheModel::inCache(uint64_t addr_) {
    uint64_t tag = (addr_ & DCACHE_TAG_MASK) >> DCACHE_SIZE_LINES >> DCACHE_LINE_BYTES;
    uint64_t index = (addr_ & DCACHE_INDEX_MASK) >> DCACHE_LINE_BYTES;

    for (int way_i = 0; way_i < DCACHE_WAY; way_i++) {
        if (tag_cache[way_i][index].tag == tag) {
            // Cache hit
            return true;
        }
    }

    // Cache miss
    updateCache(tag, index);

    return false;
}

void DCacheModel::updateCache(uint64_t tag_, uint64_t index_) {
    int way = -1;

    for (int way_i = 0; way_i < DCACHE_WAY; way_i++) {
        if (!tag_cache[way_i][index_].valid) {
            way = way_i;
            break;
        }
    }

    if (way == -1) {
        way = lfsr();
    }

    tag_cache[way][index_].tag = tag_;
    tag_cache[way][index_].valid = true;
}

int DCacheModel::lfsr(void) {
    static uint8_t shift_state = 0;
    uint8_t shift_in = ~(((shift_state & 0x80) >> 7) ^ ((shift_state & 0x08) >> 3) ^ ((shift_state & 0x04) >> 2) ^ ((shift_state & 0x02) >> 1));
    shift_state = (shift_state << 1) | (shift_in & 0x01);
    return (shift_state & (DCACHE_WAY - 1));
}

std::string DCacheModel::getInfoHeader() {
    std::stringstream ret_strs;
    ret_strs << "L1D:miss";
    return ret_strs.str();
}

std::string DCacheModel::getInfoStream() {
    std::stringstream ret_strs;
    ret_strs << isMiss;
    return ret_strs.str();
}

}  // namespace rv32_4issue
