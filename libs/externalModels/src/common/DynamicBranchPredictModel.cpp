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

#include "models/common/DynamicBranchPredictModel.h"

#include <stdbool.h>

namespace common{

bool PredictFsm::getPrediction()
{
  if(state == STRONG_NOT_TAKEN || state == WEAK_NOT_TAKEN)
  {
    return false;
  }
  return true;
}

void PredictFsm::update(bool taken)
{
  switch(state)
  {

  case STRONG_NOT_TAKEN: state = taken ? WEAK_NOT_TAKEN : STRONG_NOT_TAKEN;
    break;

  case WEAK_NOT_TAKEN: state = taken ? STRONG_TAKEN : STRONG_NOT_TAKEN;
    break;

  case WEAK_TAKEN: state = taken ? STRONG_TAKEN : STRONG_NOT_TAKEN;
    break;

  case STRONG_TAKEN: state = taken ? STRONG_TAKEN : WEAK_TAKEN;
    break;

  default: state = RESET_STATE;
  }
  
}
  
bool BranchHistoryTable::getPrediction(uint64_t pc)
{
  auto entry = table.find(pc);

  // Look up prediction
  if(entry != table.end())
  {
    return entry->second->getPrediction();
  }
  else
  {
    std::cout << "ERROR: BHT_1. THIS SHOULD NEVER HAPPEN\n";  // TODO: Remove this error message
  }

  return false;

}

void BranchHistoryTable::update(uint64_t pc, bool taken)
{
  auto entry = table.find(pc);
  if(entry != table.end())
  {
    entry->second->update(taken);
  }
  else
  {
    std::cout << "ERROR: BHT_2. THIS SHOULD NEVER HAPPEN\n"; // TODO: Remove this error message
  }
}

void BranchHistoryTable::createEntry(uint64_t pc)
{
  table[pc] = new PredictFsm();
}

void BranchHistoryTable::replaceEntry(uint64_t new_pc, uint64_t old_pc)
{
  auto entry = table.find(old_pc);
  if(entry == table.end())
  {
    std::cout << "ERROR: BHT_3. THIS SHOULD NEVER HAPPEN\n"; // TODO: Remove this error message
  }    
  entry->second->reset();
  table[new_pc] = entry->second;
  table.erase(entry);
}   

uint64_t BranchTargetBuffer::getPrediction(uint64_t pc)
{
  auto entry = table.find(pc);

  if(entry != table.end())
  {
    return entry->second;
  }
  else
  {
    std::cout << "ERROR: BTB_1. THIS SHOULD NEVER HAPPEN\n";  // TODO: Remove this error message
  }

  return 0;
}

void BranchTargetBuffer::update(uint64_t pc, uint64_t branch_addr)
{
  auto entry = table.find(pc);
  if(entry != table.end())
  {
    entry->second = branch_addr;
  }
  else
  {
    std::cout << "ERROR: BTB_2. THIS SHOULD NEVER HAPPEN\n"; // TODO: Remove this error message
  }
}

void BranchTargetBuffer::createEntry(uint64_t pc)
{
  table[pc] = 0;
}

void BranchTargetBuffer::replaceEntry(uint64_t new_pc, uint64_t old_pc)
{
  auto entry = table.find(old_pc);
  if(entry == table.end())
  {
    std::cout << "ERROR: BHT_3. THIS SHOULD NEVER HAPPEN\n"; // TODO: Remove this error message
  }    
  table.erase(entry);

  table[new_pc] = 0;
}

void DynamicBranchPredictModel::setPc_p(uint64_t pc_p_)
{
  pc_p = pc_p_;
}

void DynamicBranchPredictModel::setPc_np(uint64_t pc_np_)
{
  branchInstr = true;
  branchInstrPc = pc_ptr[getInstrIndex()];
  comp_branchAddr = brTarget_ptr[getInstrIndex()];

  bool entryExists = false;
  for(const uint64_t & entry : pcFifo)
  {
    if(entry == branchInstrPc)
    {
      entryExists = true;
      break;
    }
  }

  if(!entryExists)
  {
	
    if(pcFifo.size() < BUFFER_DEPTH)
    {
      bht.createEntry(branchInstrPc);
      btb.createEntry(branchInstrPc);      
    }
    else
    {
      uint64_t removePc = pcFifo.front();
      pcFifo.pop_front();
      bht.replaceEntry(branchInstrPc, removePc);
      btb.replaceEntry(branchInstrPc, removePc);
    }
    pcFifo.push_back(branchInstrPc);
  }
  
  pred_taken = bht.getPrediction(branchInstrPc);
  pred_branchAddr = btb.getPrediction(branchInstrPc);
  
}

uint64_t DynamicBranchPredictModel::getPc()
{
  if(!branchInstr)
  {
    return pc_p;
  }

  branchInstr = false;
  
  uint64_t curPc = pc_ptr[getInstrIndex()];
  bool taken = (curPc == pred_branchAddr) | (curPc == comp_branchAddr);

  bht.update(branchInstrPc, taken);
  if(curPc == comp_branchAddr)
  {
    btb.update(branchInstrPc, comp_branchAddr);
  }
  
  if(pred_taken & (curPc == pred_branchAddr ))
  {
    return pc_p;
  }
  if(!pred_taken & !taken)
  {
    return pc_p;
  }

  return pc_np;
  
}

} // namespace common
