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

#ifndef RV32_4ISSUE_D_CACHE_MODEL_H
#define RV32_4ISSUE_D_CACHE_MODEL_H

#include <stdbool.h>
#include <cstdint>
#include <string>

#include "PerformanceModel.h"

// Parameters to customize Cache layout
#define DCACHE_WAY 4
#define DCACHE_SIZE_LINES 8 // 2^8 = 256 lines

#define DCACHE_LINE_BYTES 4 // (2^4)*8 = 128 bits

#define DCACHE_SIZE (2 << DCACHE_SIZE_LINES)  // 2 << 8 = 256
#define DCACHE_LINE_SIZE ((2 << DCACHE_LINE_BYTES) * 8)

namespace rv32_4issue {

struct DCacheEntry {
    uint64_t tag = 0;
    bool valid = false;
};

class DCacheModel : public ResourceModel {
   public:
    DCacheModel(PerformanceModel* parent_) : ResourceModel("DCacheModel", parent_), CACHE_DELAY(2), MEMORY_DELAY(8), NOT_CACHABLE_DELAY(12) {};
    virtual int getDelay(void);

    void setDc_in(uint64_t c_) {
        uint64_t addr = addr_ptr[getInstrIndex()];
        inCache(addr);
    };
    uint64_t getDc_out(void) { return 0; };

    // Tracing API
    std::string getInfoHeader();
    std::string getInfoStream();

    // Trace value
    uint64_t* addr_ptr;
    uint64_t* pc_ptr;

   private:
    // Cache state
    DCacheEntry tag_cache[DCACHE_WAY][DCACHE_SIZE];

    // Support functions
    bool inCache(uint64_t);
    bool cachable(uint64_t addr_) { return ((0x80000000 <= addr_) && (addr_ < 0xC0000000)) ? true : false; };
    void updateCache(uint64_t, uint64_t);
    int lfsr(void);

    // Miss flag. Currently only used for info print
    bool isMiss = false;

    // Constants
    const int CACHE_DELAY;
    const int MEMORY_DELAY;
    const int NOT_CACHABLE_DELAY;

    const uint64_t DCACHE_INDEX_MASK = (DCACHE_SIZE - 1) << DCACHE_LINE_BYTES;  // 255 << 4 = 0xFF0
    const uint64_t DCACHE_TAG_MASK = (~((DCACHE_SIZE * (2 << DCACHE_LINE_BYTES)) - 1)); // ~0xFFFF = 0xFFFF0000
};

}  // namespace rv32_4issue

#endif  // RV32_4ISSUE_D_CACHE_MODEL_H
