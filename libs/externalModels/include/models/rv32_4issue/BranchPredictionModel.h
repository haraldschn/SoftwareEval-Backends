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

#ifndef RV32_4ISSUE_DYNAMIC_BRANCH_PREDICT_MODEL_H
#define RV32_4ISSUE_DYNAMIC_BRANCH_PREDICT_MODEL_H

#include <stdbool.h>
#include <array>
#include <stack>
#include <cstdint>

#include "PerformanceModel.h"

namespace rv32_4issue{

class PredictFsm
{
public:
  PredictFsm(){};
  bool getPrediction(void);
  void update(bool);
private:
  enum state_t {STRONG_NOT_TAKEN, WEAK_NOT_TAKEN, WEAK_TAKEN, STRONG_TAKEN};
  state_t RESET_STATE = STRONG_NOT_TAKEN;
  state_t FLUSH_STATE = WEAK_TAKEN; 
  state_t state = RESET_STATE;
};


struct BranchHistoryEntry
{
  bool valid = false;
  PredictFsm state;
};


class BranchHistoryTable
{
public:
  BranchHistoryTable(){};
  bool getPrediction(uint64_t, uint64_t);
  void update(uint64_t, bool);
private:
  std::array<BranchHistoryEntry, 4096> tab;
  int getIndex(uint64_t pc_) { return ((pc_ & 0x00001FFE) >> 1); };
};


struct ReturnAddressEntry
{
  bool valid = false;
  uint64_t addr = 0;
};


class ReturnAddressStack
{
public:
  ReturnAddressStack(){};
  void push(uint64_t);
  uint64_t pop(void);
private:
  const long unsigned int MAX_STACK_SIZE = 32;
  std::stack<ReturnAddressEntry> stack;
};


struct TargetBufferEntry
{
  bool valid = false;
  uint64_t addr = 0;
};

class BranchTargetBuffer
{
public:
  BranchTargetBuffer(){};
  uint64_t getPrediction(uint64_t);
  void update(uint64_t, uint64_t);
private:
  std::array<TargetBufferEntry, 4096> tab;
  int getIndex(uint64_t pc_) { return ((pc_ & 0x00001FFE) >> 1); };
};

  
class BranchPredictionModel : public ConnectorModel
{
public:
  BranchPredictionModel(PerformanceModel* parent_) : ConnectorModel("RV32_4ISSUE_BranchPredictionModel", parent_), bht(), btb(), ras() {};
   
  // API
  void setPc_p(uint64_t);
  void setPc_p_j(uint64_t);
  void setPc_p_jr(uint64_t);
  void setPc_c(uint64_t pc_c_) { t_pc_mp = pc_c_; };
  uint64_t getPc_mp(void);
  uint64_t getPc_pt(void);

  // Tracing API
  std::string getInfoHeader();
  std::string getInfoStream();
  
  // Trace values
  uint64_t* pc_ptr;
  uint64_t* brTarget_ptr;
  uint64_t* imm_ptr;
  uint64_t* rs1_ptr;
  uint64_t* rd_ptr;
  
private:
  BranchHistoryTable bht;
  BranchTargetBuffer btb;
  ReturnAddressStack ras;

  bool branch_flag = false;
  uint64_t branchPc = 0; 
  uint64_t branchTarget = 0;
  bool branchPredictedTaken = false;

  bool jump_flag = false;

  bool jumpR_flag = false;
  bool return_flag = false;
  
  uint64_t t_pc_pt = 0; // predicted and taken
  uint64_t t_pc_mp = 0; // mispredicted

  bool isMispredict = false;
  bool isTaken = false;
  
  bool isCall(void) { return ( (rd_ptr[getInstrIndex()] == 1) | (rd_ptr[getInstrIndex()] == 5) ); };
  bool isReturn(void) {return ( (rs1_ptr[getInstrIndex()] != rd_ptr[getInstrIndex()]) & ((rs1_ptr[getInstrIndex()] == 1) | (rs1_ptr[getInstrIndex()] == 5)) ); };
  
  // TODO: Use for model evaluation. DELETE!
  uint64_t pc_info = 0;
  
};

} // namespace rv32_4issue
  
#endif //RV32_4ISSUE_DYNAMIC_BRANCH_PREDICT_MODEL_H