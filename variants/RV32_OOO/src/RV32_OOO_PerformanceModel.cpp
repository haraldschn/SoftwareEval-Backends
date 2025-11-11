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

#include "models/rv32_ooo/NoBranchPredictModel.h"
#include "models/rv32_ooo/ClobberModel.h"
#include "models/rv32_ooo/Scheduler.h"

namespace RV32_OOO{

void RV32_OOO_PerformanceModel::connectChannel(Channel* channel_)
{
  RV32_OOO_Channel* channel = static_cast<RV32_OOO_Channel*>(channel_);


  clobberModel.rs1_ptr = channel->rs1;
  clobberModel.rs2_ptr = channel->rs2;
  clobberModel.rd_ptr = channel->rd;

  scheduleModel.pc_ptr = channel->pc;
  scheduleModel.rs1_ptr = channel->rs1;
  scheduleModel.rs2_ptr = channel->rs2;
  scheduleModel.rd_ptr = channel->rd;
  scheduleModel.addr_ptr = channel->addr;

}

uint64_t RV32_OOO_PerformanceModel::getCycleCount(void)
{
  
  return std::max({
    PC_stage 
    ,IF_stage
    ,IS_stage
    ,IB_stage_OoO.get(1)
    ,EX_stage_div_NoB
    ,EX_stage_mul_NoB.get(1)
    ,EX_stage_mul0v_NoB
    ,EX_stage_mul1v_NoB
    ,EX_stage_br_NoB
    ,EX_stage_alu_NoB
    ,EX_stage_lsu_NoB.get(1)
    ,EX_stage_lu0v_NoB
    ,EX_stage_lu1v_NoB
    ,EX_stage_suv_NoB
    ,WB_stage_NoB.get(1)
  });
}

std::string RV32_OOO_PerformanceModel::getPipelineStream(void)
{
  std::stringstream ret_strs;
  ret_strs << entrancePoint;
  ret_strs << "," << PC_stage;
  ret_strs << "," << IF_stage;
  ret_strs << "," << IS_stage;
  ret_strs << "," << IB_stage_OoO.get(1);
  ret_strs << "," << EX_stage_div_NoB;
  ret_strs << "," << EX_stage_mul_NoB.get(1);
  ret_strs << "," << EX_stage_br_NoB;
  ret_strs << "," << EX_stage_alu_NoB;
  ret_strs << "," << EX_stage_lsu_NoB.get(1);
  ret_strs << "," << WB_stage_NoB.get(1);
  ret_strs << "," << noBranchPredModel.getInfoStream();
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

} // namespace RV32_OOO