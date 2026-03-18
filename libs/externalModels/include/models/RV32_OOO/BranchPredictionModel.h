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

#ifndef RV32_OOO_DYNAMIC_BRANCH_PREDICT_MODEL_H
#define RV32_OOO_DYNAMIC_BRANCH_PREDICT_MODEL_H

#include "PerformanceModel.h"

#include <stdbool.h>
#include <map>
#include <list>

// TODO: Check where unsigned int should be used instead of int!

namespace RV32_OOO{

class PredictFsm
{
public:
  bool getPrediction();
  void update(bool);
  void reset() { state = RESET_STATE; };
private:
  enum state_t {STRONG_NOT_TAKEN, WEAK_NOT_TAKEN, WEAK_TAKEN, STRONG_TAKEN};
  state_t RESET_STATE = WEAK_TAKEN;
  state_t state = RESET_STATE;
};

class BranchHistoryTable
{
public:
  bool getPrediction(uint64_t);
  void update(uint64_t, bool);
  void createEntry(uint64_t);
  void replaceEntry(uint64_t, uint64_t);

private:
  std::map<uint64_t, PredictFsm*> table;
};

class BranchTargetBuffer
{
public:
  uint64_t getPrediction(uint64_t);
  void update(uint64_t, uint64_t);
  void createEntry(uint64_t);
  void replaceEntry(uint64_t, uint64_t);

private:
  std::map<uint64_t, uint64_t> table;
};
 
class BranchPredictModel : public ConnectorModel
{
public:
    // TODO: Make BUFFER_SIZE configurable! 
    BranchPredictModel(PerformanceModel* parent_) : ConnectorModel("RV32_OOO_BranchPredictModel", parent_), btb(), bht(), BUFFER_DEPTH(5) {};

    uint64_t* pc_ptr;
    uint64_t* brTarget_ptr;

    void setPc_p(uint64_t pc_p_) {};
    void setPc_np(uint64_t);
    uint64_t getPc(void);

    // Tracing API
    std::string getInfoHeader();
    std::string getInfoStream();
    
private:
    uint64_t pc_p = 0;
    uint64_t pc_np = 0;

    bool branchInstr = false;
    uint64_t branchInstrPc = 0;

    bool pred_taken = false;
    uint64_t pred_branchAddr = 0;
    uint64_t comp_branchAddr = 0;

    BranchTargetBuffer btb;
    BranchHistoryTable bht;
    
    const uint64_t BUFFER_DEPTH;
    std::list<uint64_t> pcFifo;

};

} // namespace RV32_OOO
  
#endif //RV32_OOO_DYNAMIC_BRANCH_PREDICT_MODEL_H
