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

// TODO: Proof-of-concept model, taken from Robert (more or less)!

#include "models/rv32_4issue/ICacheModel.h"

#include <cstdint>
#include <string>
#include <sstream>

namespace rv32_4issue {

int ICacheModel::getDelay(void) {
    uint64_t pc = pc_ptr[getInstrIndex()];

    isMiss = !inCache(pc);

    if (!cachable(pc) | isMiss) {
        return MEMORY_DELAY;
    }

    return CACHE_DELAY;
}

bool ICacheModel::inCache(uint64_t pc_) {
    uint64_t tag = (pc_ & ICACHE_TAG_MASK) >> ICACHE_SIZE_LINES >> ICACHE_LINE_BYTES;
    uint64_t index = (pc_ & ICACHE_INDEX_MASK) >> ICACHE_LINE_BYTES;

    // Prefetch first instructions
    if (pc_ == 0x80000000) {
        // Preload first 16 (=4x4) instructions (4 byte aligned)
        updateCache(tag, index);
        return true;
    }

    for (int way_i = 0; way_i < ICACHE_WAY; way_i++) {
        if (tag_cache[way_i][index].tag == tag) {
            // Cache hit
            uint64_t tag = ((pc_ + 16) & ICACHE_TAG_MASK) >> ICACHE_SIZE_LINES >> ICACHE_LINE_BYTES;
            uint64_t index = ((pc_ + 16) & ICACHE_INDEX_MASK) >> ICACHE_LINE_BYTES;
            updateCache(tag, index);
            return true;
        }
    }

    // Cache miss + Preload next 16 (=4x4) instructions (4 byte aligned)
    updateCache(tag, index);
    return false;
}

void ICacheModel::updateCache(uint64_t tag_, uint64_t index_) {
    int way = -1;

    for (int i = 0; i < ICACHE_WAY; i++) {
        if (!tag_cache[i][index_].valid) {
            way = i;
            break;
        }
    }

    if (way == -1) {
        way = lfsr();
    }

    tag_cache[way][index_].tag = tag_;
    tag_cache[way][index_].valid = true;
}

int ICacheModel::lfsr(void) {
    static uint8_t shift_state = 0;
    uint8_t shift_in = ~(((shift_state & 0x80) >> 7) ^ ((shift_state & 0x08) >> 3) ^ ((shift_state & 0x04) >> 2) ^ ((shift_state & 0x02) >> 1));
    shift_state = (shift_state << 1) | (shift_in & 0x01);
    return (shift_state & (ICACHE_WAY - 1));
}

std::string ICacheModel::getInfoHeader() {
    std::stringstream ret_strs;
    ret_strs << "L1I:miss";
    return ret_strs.str();
}

std::string ICacheModel::getInfoStream() {
    std::stringstream ret_strs;
    ret_strs << isMiss;
    return ret_strs.str();
}

}  // namespace rv32_4issue
