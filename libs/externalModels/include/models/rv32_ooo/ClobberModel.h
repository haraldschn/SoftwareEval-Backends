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

#ifndef RV32_OOO_CLOBBER_MODEL_H
#define RV32_OOO_CLOBBER_MODEL_H

#include "PerformanceModel.h"
#include <cstdint>

namespace rv32_ooo {

class ClobberModel : public ConnectorModel {
   public:
    ClobberModel(PerformanceModel* parent_) : ConnectorModel("RV32_OOO_ClobberModel", parent_), RENAMING(true) {
        for (int i = 0; i < 64; i++) {
            registerModel[i] = 0;
        }
    };

    uint64_t* rs1_ptr;
    uint64_t* rs2_ptr;
    uint64_t* rd_ptr;

    // TODO: Consider corner-case rd = 0?

    uint64_t getCb_out(void) { 
        //printf("%ld\n",(rd_ptr[getInstrIndex()] != 0) ? registerModel[rd_ptr[getInstrIndex()]] : 0);
        return (rd_ptr[getInstrIndex()] != 0) ? registerModel[rd_ptr[getInstrIndex()]] : 0; 
    };

    void setCb_inRd(uint64_t xd_) { registerModel[rd_ptr[getInstrIndex()]] = RENAMING ? 0 : xd_; };
    void setCb_inR1(uint64_t xd_) { registerModel[rs1_ptr[getInstrIndex()]] = RENAMING ? 0 : xd_; };
    void setCb_inR2(uint64_t xd_) { registerModel[rs2_ptr[getInstrIndex()]] = RENAMING ? 0 : xd_; };

   private:
    uint64_t registerModel[64] = {0};

    const bool RENAMING = true;
};

}  // namespace rv32_ooo

#endif  // RV32_OOO_CLOBBER_MODEL_H
