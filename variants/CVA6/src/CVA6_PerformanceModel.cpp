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

#include "CVA6_PerformanceModel.h"

#include <stdbool.h>
#include <string>
#include <sstream>
#include <algorithm>

#include "Channel.h"

#include "CVA6_Channel.h"

#include "models/common/StandardRegisterModel.h"
#include "models/cva6/BranchPredictionModel.h"
#include "models/cva6/ClobberModel.h"
#include "models/cva6/ICacheModel.h"
#include "models/cva6/DividerModel.h"
#include "models/cva6/DividerUnsignedModel.h"
#include "models/cva6/DCacheModel.h"

namespace CVA6 {

void CVA6_PerformanceModel::connectChannel(Channel* channel_) {
    CVA6_Channel* channel = static_cast<CVA6_Channel*>(channel_);

    regModel.rs1_ptr = channel->rs1;
    regModel.rs2_ptr = channel->rs2;
    regModel.rd_ptr = channel->rd;

    dynBranchPredModel.pc_ptr = channel->pc;
    dynBranchPredModel.brTarget_ptr = channel->brTarget;
    dynBranchPredModel.rs1_ptr = channel->rs1;
    dynBranchPredModel.rd_ptr = channel->rd;
    dynBranchPredModel.imm_ptr = channel->imm;

    clobberModel.rd_ptr = channel->rd;

    iCacheModel.pc_ptr = channel->pc;

    divider.rs1_data_ptr = channel->rs1_data;
    divider.rs2_data_ptr = channel->rs2_data;

    divider_u.rs1_data_ptr = channel->rs1_data;
    divider_u.rs2_data_ptr = channel->rs2_data;

    dCacheModel.addr_ptr = channel->addr;
}

uint64_t CVA6_PerformanceModel::getCycleCount(void) {
    uint64_t enter = graph.get_node_t_start(nodes_PC.back());
    uint64_t PC_stage = graph.get_node_t_start(nodes_IF.back());
    uint64_t IF_stage = graph.get_node_t_start(nodes_IQ.back());
    uint64_t IQ_stage = graph.get_node_t_start(nodes_ID.back());
    uint64_t ID_stage = graph.get_node_t_start(nodes_IS.back());
    uint64_t IS_stage = graph.get_node_t_start(nodes_EX.back());
    uint64_t EX_stage = graph.get_node_t_start(nodes_COM.back());
    uint64_t COM_stage = graph.get_node_t_end(nodes_COM.back());

    return std::max({enter, PC_stage, IF_stage, IQ_stage, ID_stage, IS_stage, EX_stage, COM_stage});
}

std::string CVA6_PerformanceModel::getPipelineStream(void) {
    uint64_t min_len = std::min({nodes_PC.size(),
                                 nodes_IF.size(),
                                 nodes_IQ.size(),
                                 nodes_ID.size(),
                                 nodes_IS.size(),
                                 nodes_EX.size(),
                                 nodes_COM.size()});

    std::stringstream ret_strs;
    if (min_len > current_print) {
        ret_strs << graph.get_node_t_start(nodes_IF[current_print-1]);
        ret_strs << "," << graph.get_node_t_start(nodes_IF[current_print]);
        ret_strs << "," << graph.get_node_t_start(nodes_IQ[current_print]);
        ret_strs << "," << graph.get_node_t_start(nodes_ID[current_print]);
        ret_strs << "," << graph.get_node_t_start(nodes_IS[current_print]);
        ret_strs << "," << graph.get_node_t_start(nodes_EX[current_print]);
        ret_strs << "," << graph.get_node_t_start(nodes_COM[current_print]);
        ret_strs << "," << graph.get_node_t_end(nodes_COM[current_print]);
        // ret_strs << "," << dynBranchPredModel.getInfoStream();
        // ret_strs << "," << iCacheModel.getInfoStream();
        // ret_strs << "," << dCacheModel.getInfoStream();
        ret_strs << std::endl;
        current_print += 1;
    }

    return ret_strs.str();
}

std::string CVA6_PerformanceModel::getPrintHeader(void) {
    std::stringstream ret_strs;
    ret_strs << "Enter";
    ret_strs << "," << "PC_stage";
    ret_strs << "," << "IF_stage";
    ret_strs << "," << "IQ_stage";
    ret_strs << "," << "ID_stage";
    ret_strs << "," << "IS_stage";
    ret_strs << "," << "EX_stage";
    ret_strs << "," << "COM_stage";
    // ret_strs << "," << dynBranchPredModel.getInfoHeader();
    // ret_strs << "," << iCacheModel.getInfoHeader();
    // ret_strs << "," << dCacheModel.getInfoHeader();
    ret_strs << std::endl;
    return ret_strs.str();
}

uint64_t CVA6_PerformanceModel::getLastEntryNode(void) {
    return nodes_PC.back();
}

}  // namespace CVA6