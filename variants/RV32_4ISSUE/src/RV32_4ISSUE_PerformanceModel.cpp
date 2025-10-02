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


#include "RV32_4ISSUE_PerformanceModel.h"

#include <stdbool.h>
#include <string>
#include <sstream>
#include <algorithm>

#include "Channel.h"

#include "RV32_4ISSUE_Channel.h"

#include "models/rv32_4issue/RegisterModel.h"
#include "models/rv32_4issue/BranchPredictionModel.h"
#include "models/rv32_4issue/ICacheModel.h"
#include "models/rv32_4issue/DCacheModel.h"
#include "models/rv32_4issue/FetchAligner.h"
#include "models/rv32_4issue/Scheduler.h"
#include "models/rv32_4issue/DividerUnsignedModel.h"
#include "models/rv32_4issue/DividerModel.h"

namespace RV32_4ISSUE{

void RV32_4ISSUE_PerformanceModel::connectChannel(Channel* channel_)
{
  RV32_4ISSUE_Channel* channel = static_cast<RV32_4ISSUE_Channel*>(channel_);

  regModel.rs1_ptr = channel->rs1;
  regModel.rs2_ptr = channel->rs2;
  regModel.rd_ptr = channel->rd;

  dynBranchPredModel.pc_ptr = channel->pc;
  dynBranchPredModel.brTarget_ptr = channel->brTarget;
  dynBranchPredModel.rs1_ptr = channel->rs1;
  dynBranchPredModel.rd_ptr = channel->rd;
  dynBranchPredModel.imm_ptr = channel->imm;

  iCacheModel.pc_ptr = channel->pc;

  dCacheModel.pc_ptr = channel->pc;
  dCacheModel.addr_ptr = channel->addr;

  fetchAligner.pc_ptr = channel->pc;

  schedModel.pc_ptr = channel->pc;
  schedModel.rs1_ptr = channel->rs1;
  schedModel.rd_ptr = channel->rd;

  divider_u.rs2_data_ptr = channel->rs2_data;

  divider.rs2_data_ptr = channel->rs2_data;

}

uint64_t RV32_4ISSUE_PerformanceModel::getCycleCount(void)
{
  
  return std::max({
    IF_stage.get(1) 
    ,PC_substage.get(1)
    ,IF_substage_0.get(1)
    ,IF_substage_1.get(1)
    ,IF_substage_2.get(1)
    ,DEC_stage.get(1)
    ,RN_stage.get(1)
    ,IS_substage_alu_OoO.get(1)
    ,LD_substage_alu_OoO.get(1)
    ,EX_stage_alu_OoO.get(1)
    ,WFC_stage_alu.get(1)
    ,IS_substage_agu.get(1)
    ,LD_substage_agu.get(1)
    ,EX_stage_agu.get(1)
    ,WFC_stage_agu.get(1)
    ,COM_stage.get(1)
  });
}

std::string RV32_4ISSUE_PerformanceModel::getPipelineStream(void)
{
  std::stringstream ret_strs;
  ret_strs << entrancePoint;
  ret_strs << "," << IF_stage.get(1);
  ret_strs << "," << DEC_stage.get(1);
  ret_strs << "," << RN_stage.get(1);
  ret_strs << "," << IS_substage_alu_OoO.get(1);
  ret_strs << "," << LD_substage_alu_OoO.get(1);
  ret_strs << "," << EX_stage_alu_OoO.get(1);
  ret_strs << "," << WFC_stage_alu.get(1);
  ret_strs << "," << IS_substage_agu.get(1);
  ret_strs << "," << LD_substage_agu.get(1);
  ret_strs << "," << EX_stage_agu.get(1);
  ret_strs << "," << WFC_stage_agu.get(1);
  ret_strs << "," << COM_stage.get(1);
  ret_strs << "," << dynBranchPredModel.getInfoStream();
  ret_strs << "," << iCacheModel.getInfoStream();
  ret_strs << "," << dCacheModel.getInfoStream();
  ret_strs << std::endl;
  return ret_strs.str();
}

std::string RV32_4ISSUE_PerformanceModel::getPrintHeader(void)
{
  std::stringstream ret_strs;
  ret_strs << "Enter";
  ret_strs << "," << "IF_stage";
  ret_strs << "," << "DEC_stage";
  ret_strs << "," << "RN_stage";
  ret_strs << "," << "IS_substage_alu_OoO";
  ret_strs << "," << "LD_substage_alu_OoO";
  ret_strs << "," << "EX_stage_alu_OoO";
  ret_strs << "," << "WFC_stage_alu";
  ret_strs << "," << "IS_substage_agu";
  ret_strs << "," << "LD_substage_agu";
  ret_strs << "," << "EX_stage_agu";
  ret_strs << "," << "WFC_stage_agu";
  ret_strs << "," << "COM_stage";
  ret_strs << "," << dynBranchPredModel.getInfoHeader();
  ret_strs << "," << iCacheModel.getInfoHeader();
  ret_strs << "," << dCacheModel.getInfoHeader();
  ret_strs << std::endl;
  return ret_strs.str();
}

} // namespace RV32_4ISSUE