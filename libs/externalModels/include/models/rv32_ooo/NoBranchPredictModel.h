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

#ifndef RV32_OOO_NO_BRANCH_PREDICT_MODEL_H
#define RV32_OOO_NO_BRANCH_PREDICT_MODEL_H

#include "PerformanceModel.h"

#include <stdbool.h>
#include <cstdint>

namespace rv32_ooo {

class NoBranchPredictModel : public ConnectorModel {
   public:
    NoBranchPredictModel(PerformanceModel* parent_) : ConnectorModel("RV32_OOO_NoBranchPredictModel", parent_) {};

    void setPc_p(uint64_t pc_p_) {};
    void setPc_np(uint64_t pc_np_) { pc = pc_np_; };
    uint64_t getPc(void) { return pc; };

    // Tracing API
    std::string getInfoHeader();
    std::string getInfoStream();

   private:
    uint64_t pc = 0;
    // Status variables for info-print (tracing)
    bool mispredicted_info = false;
    uint64_t pc_info = 0;
};

}  // namespace rv32_ooo

#endif  // RV32_OOO_NO_BRANCH_PREDICT_MODEL_H
