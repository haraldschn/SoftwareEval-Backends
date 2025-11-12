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

#ifndef SOOMRV_I_CACHE_MODEL_H
#define SOOMRV_I_CACHE_MODEL_H

#include <stdbool.h>
#include <cstdint>
#include <string>

#include "PerformanceModel.h"

// Parameters to customize Cache layout
#define ICACHE_WAY 4
#define ICACHE_SIZE_LINES 8 // 2^8 = 256 lines

#define ICACHE_LINE_BYTES 4

#define ICACHE_SIZE (2 << ICACHE_SIZE_LINES)  // 2 << 8 = 256
#define ICACHE_LINE_SIZE ((2 << ICACHE_LINE_BYTES) * 8)

namespace soomrv {

struct ICacheEntry {
    uint64_t tag = 0;
    bool valid = false;
};

class ICacheModel : public ResourceModel {
   public:
    ICacheModel(PerformanceModel* parent_) : ResourceModel("ICacheModel", parent_), CACHE_DELAY(1), MEMORY_DELAY(12) {};
    virtual int getDelay(void);

    void setIc_in(uint64_t c_) { t_ic = isMiss ? c_ : 0; };
    uint64_t getIc_out(void) { return t_ic; };

    // Tracing API
    std::string getInfoHeader();
    std::string getInfoStream();

    // Trace value
    uint64_t* pc_ptr;

   private:
    // Cache state
    ICacheEntry tag_cache[ICACHE_WAY][ICACHE_SIZE];

    bool isMiss = false;
    uint64_t pc_prev = 0x80000000 - 4;

    // Time when ICache releases block on miss
    uint64_t t_ic = 0;

    // Constants
    const int CACHE_DELAY;
    const int MEMORY_DELAY;

    const uint64_t ICACHE_INDEX_MASK = (ICACHE_SIZE - 1) << ICACHE_LINE_BYTES;
    const uint64_t ICACHE_TAG_MASK = (~((ICACHE_SIZE * (2 << ICACHE_LINE_BYTES)) - 1));

    // Support functions
    bool inCache(uint64_t);
    bool cachable(uint64_t pc_) { return ((0x80000000 <= pc_) && (pc_ < 0xC0000000)) ? true : false; };
    void updateCache(uint64_t, uint64_t);
    int lfsr(void);
};

}  // namespace soomrv

#endif  // CVA6_I_CACHE_MODEL_H
