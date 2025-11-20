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

#ifndef RV32_OOO_DEPEND_MODEL_H
#define RV32_OOO_DEPEND_MODEL_H

#include "PerformanceModel.h"
#include <cstdint>

namespace RV32_OOO {

class DependModel : public ConnectorModel {
   public:
    DependModel(PerformanceModel* parent_) : ConnectorModel("RV32_OOO_DependModel", parent_) {};

    uint64_t* pc_ptr;
    uint64_t* rs1_ptr;
    uint64_t* rs2_ptr;
    uint64_t* rd_ptr;

    void setDecodeTime(uint64_t x_);

    uint64_t getIssueTime(void);

   private:
    uint64_t dec_time = 0;

    uint64_t register_depency[64] = {0};
};

}  // namespace RV32_OOO

#endif  // RV32_OOO_DEPEND_MODEL_H