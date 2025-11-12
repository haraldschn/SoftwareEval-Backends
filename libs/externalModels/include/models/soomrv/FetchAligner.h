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

// TODO: Proof-of-concept model, align Fetches with 0x???????0, ..4 , ..8, ..C in same PC!

#ifndef SOOMRV_FALIGN_MODEL_H
#define SOOMRV_FALIGN_MODEL_H

#include <stdbool.h>
#include <cstdint>
#include <string>

#include "PerformanceModel.h"

#define INITIAL_PC 0x80000000

namespace soomrv {

class FetchAligner : public ConnectorModel {
   public:
    // TODO: Check if delays are matching observations!
    FetchAligner(PerformanceModel* parent_) : ConnectorModel("FetchAligner", parent_), ALIGNED_DELAY(0), UNALIGNED_DELAY(1) {};
    //virtual int getDelay(void);

    void setPCGen_in(uint64_t c_);
    uint64_t getPCGen_out(void);

    // Trace value
    uint64_t* pc_ptr;
    
   private:

    uint64_t pc_prev = INITIAL_PC-4;

    uint64_t IF_start_next = 0;

    // Constants
    const int ALIGNED_DELAY;
    const int UNALIGNED_DELAY;
};

}  // namespace soomrv

#endif  // SOOMRV_FALIGN_MODEL_H