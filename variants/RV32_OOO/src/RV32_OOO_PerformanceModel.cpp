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

/********************* AUTO GENERATE FILE (create by M2-ISA-R-Perf) *********************/


#include "RV32_OOO_PerformanceModel.h"

#include <stdbool.h>
#include <string>
#include <sstream>
#include <algorithm>

#include "Channel.h"

#include "RV32_OOO_Channel.h"

#include "models/RV32_OOO/OoORegisterModel.h"
#include "models/RV32_OOO/NoBranchPredictModel.h"
#include "models/RV32_OOO/ClobberModel.h"

namespace RV32_OOO{

void RV32_OOO_PerformanceModel::connectChannel(Channel* channel_)
{
  RV32_OOO_Channel* channel = static_cast<RV32_OOO_Channel*>(channel_);

  regModel.rs1_ptr = channel->rs1;
  regModel.rs2_ptr = channel->rs2;
  regModel.rd_ptr = channel->rd;

  clobberModel.rs1_ptr = channel->rs1;
  clobberModel.rs2_ptr = channel->rs2;
  clobberModel.rd_ptr = channel->rd;

}

uint64_t RV32_OOO_PerformanceModel::getCycleCount(void)
{
  
  return 0;
}

std::string RV32_OOO_PerformanceModel::getPipelineStream(void)
{
  std::stringstream ret_strs;
  ret_strs << entrancePoint;
  // ret_strs << "," << PC_stage;
  // ret_strs << "," << IF_stage;
  // ret_strs << "," << IS_stage;
  // ret_strs << "," << IB_stage_OoO.get(1);
  // ret_strs << "," << EX_stage_div_NoB;
  // ret_strs << "," << EX_stage_mul_NoB.get(1);
  // ret_strs << "," << EX_stage_br_NoB;
  // ret_strs << "," << EX_stage_alu_NoB;
  // ret_strs << "," << EX_stage_lsu_NoB.get(1);
  // ret_strs << "," << WB_stage_NoB.get(1);
  // ret_strs << "," << noBranchPredModel.getInfoStream();
  ret_strs << std::endl;
  return ret_strs.str();
}

std::string RV32_OOO_PerformanceModel::getPrintHeader(void)
{
  std::stringstream ret_strs;
  ret_strs << "Enter";
  ret_strs << "," << "PC_stage";
  ret_strs << "," << "IF_stage";
  ret_strs << "," << "IS_stage";
  ret_strs << "," << "IB_stage_OoO";
  ret_strs << "," << "EX_stage_div_NoB";
  ret_strs << "," << "EX_stage_mul_NoB";
  ret_strs << "," << "EX_stage_br_NoB";
  ret_strs << "," << "EX_stage_alu_NoB";
  ret_strs << "," << "EX_stage_lsu_NoB";
  ret_strs << "," << "WB_stage_NoB";
  ret_strs << "," << noBranchPredModel.getInfoHeader();
  ret_strs << std::endl;
  return ret_strs.str();
}

uint64_t RV32_OOO_PerformanceModel::getLastEntryNode(void) {
    return nodes_PC.back();
}

} // namespace RV32_OOO