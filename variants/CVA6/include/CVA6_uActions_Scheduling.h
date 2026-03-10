#include <algorithm>
#include <cstdint>

#include "PerformanceModel.h"

#include "CVA6_PerformanceModel.h"

namespace CVA6 {

inline void Default_Inst(PerformanceModel* perfModel_) {
    CVA6_PerformanceModel* perfModel = static_cast<CVA6_PerformanceModel*>(perfModel_);
    uint64_t enterPoint = perfModel->entrancePoint;

    uint64_t n_PC_stage_ID = perfModel->graph.add_node(F_Type::PC_stage);
    perfModel->graph.add_edge(0, n_PC_stage_ID);

    uint64_t n_IF_stage_ID = perfModel->graph.add_parent_node(F_Type::IF_stage);
    perfModel->graph.add_stage_connection(n_PC_stage_ID, n_IF_stage_ID);
    perfModel->graph.set_inorder(perfModel->nodes_IF.back(), n_IF_stage_ID);
    perfModel->graph.add_edge(perfModel->dynBranchPredModel.getPc_mp(), n_IF_stage_ID);
    perfModel->graph.add_edge(perfModel->iCacheModel.getIc_out(), n_IF_stage_ID);

    uint64_t n_IF_substage_0 = perfModel->graph.add_node(F_Type::IF_substage_0, 1, n_IF_stage_ID);
    
    uint64_t n_IF_substage_1 = perfModel->graph.add_node(F_Type::IF_substage_1, perfModel->iCacheModel.getDelay(), n_IF_stage_ID);
    perfModel->graph.add_stage_connection(n_IF_substage_0, n_IF_substage_1);
    perfModel->graph.add_edge(perfModel->dynBranchPredModel.getPc_pt(), n_IF_substage_1);
    perfModel->iCacheModel.setIc_in(n_IF_substage_1);

    uint64_t n_IF_substage_2 = perfModel->graph.add_node(F_Type::IF_substage_2, 1, n_IF_stage_ID);
    perfModel->graph.add_stage_connection(n_IF_substage_1, n_IF_substage_2);
    
    uint64_t n_IQ_stage_ID = perfModel->graph.add_node(F_Type::IQ_stage);
    perfModel->graph.add_stage_connection(n_IF_stage_ID, n_IQ_stage_ID);
    perfModel->graph.set_inorder(perfModel->nodes_IQ.back(), n_IQ_stage_ID);
    perfModel->graph.add_edge(n_IF_substage_2, n_IQ_stage_ID);

    uint64_t n_ID_stage_ID = perfModel->graph.add_node(F_Type::ID_stage);
    perfModel->graph.add_stage_connection(n_IQ_stage_ID, n_ID_stage_ID);
    perfModel->graph.set_inorder(perfModel->nodes_ID.back(), n_ID_stage_ID);

    uint64_t n_IS_stage_ID = perfModel->graph.add_node(F_Type::IS_stage);
    perfModel->graph.add_stage_connection(n_ID_stage_ID, n_IS_stage_ID);
    perfModel->graph.set_inorder(perfModel->nodes_IS.back(), n_IS_stage_ID);

    uint64_t n_EX_stage_ID = perfModel->graph.add_parent_node(F_Type::EX_stage);
    perfModel->graph.add_stage_connection(n_ID_stage_ID, n_EX_stage_ID);
    perfModel->graph.set_inorder(perfModel->nodes_EX.back(), n_EX_stage_ID);

    perfModel->graph.add_edge(perfModel->last_EX_alu, n_EX_stage_ID);
    perfModel->graph.add_edge(perfModel->last_EX_mul_o, n_EX_stage_ID);
    perfModel->graph.add_edge(perfModel->last_EX_div, n_EX_stage_ID);

    // ALU delay = 1
    uint64_t n_EX_substage_alu = perfModel->graph.add_node(F_Type::EX_substage_alu, 1, n_EX_stage_ID);
    // MUL_O / DIV blocks ALU

    uint64_t n_COM_stage_ID = perfModel->graph.add_node(F_Type::COM_stage);
    perfModel->graph.add_stage_connection(n_EX_stage_ID, n_COM_stage_ID);
    perfModel->graph.set_inorder(perfModel->nodes_COM.back(), n_COM_stage_ID);
    perfModel->graph.add_edge(n_EX_substage_alu, n_COM_stage_ID);

    // Add Nodes IDs to Stack
    perfModel->nodes_PC.push_back(n_PC_stage_ID);
    perfModel->nodes_IF.push_back(n_IF_stage_ID);
    perfModel->nodes_IQ.push_back(n_IQ_stage_ID);
    perfModel->nodes_ID.push_back(n_ID_stage_ID);
    perfModel->nodes_IS.push_back(n_IS_stage_ID);
    perfModel->nodes_EX.push_back(n_EX_stage_ID); // In-order commit EX_stage doesn't capture latency
    perfModel->nodes_COM.push_back(n_COM_stage_ID);

    perfModel->last_IF_substage = n_IF_substage_2;
    perfModel->last_EX_substage = n_EX_substage_alu;

    perfModel->last_EX_alu = n_EX_substage_alu;

    // Dump Entrance point for info print (tracing)
    perfModel->entrancePoint = enterPoint + 1;
}

inline void Arith_0(PerformanceModel* perfModel_) {
    CVA6_PerformanceModel* perfModel = static_cast<CVA6_PerformanceModel*>(perfModel_);
    uint64_t enterPoint = perfModel->entrancePoint;

    uint64_t n_PC_stage_ID = perfModel->graph.add_node(F_Type::PC_stage);
    perfModel->graph.add_edge(0, n_PC_stage_ID);

    uint64_t n_IF_stage_ID = perfModel->graph.add_parent_node(F_Type::IF_stage);
    perfModel->graph.add_stage_connection(n_PC_stage_ID, n_IF_stage_ID);
    perfModel->graph.set_inorder(perfModel->nodes_IF.back(), n_IF_stage_ID);
    perfModel->graph.add_edge(perfModel->dynBranchPredModel.getPc_mp(), n_IF_stage_ID);
    perfModel->graph.add_edge(perfModel->iCacheModel.getIc_out(), n_IF_stage_ID);

    uint64_t n_IF_substage_0 = perfModel->graph.add_node(F_Type::IF_substage_0, 1, n_IF_stage_ID);
    
    uint64_t n_IF_substage_1 = perfModel->graph.add_node(F_Type::IF_substage_1, perfModel->iCacheModel.getDelay(), n_IF_stage_ID);
    perfModel->graph.add_stage_connection(n_IF_substage_0, n_IF_substage_1);
    perfModel->graph.add_edge(perfModel->dynBranchPredModel.getPc_pt(), n_IF_substage_1);
    perfModel->iCacheModel.setIc_in(n_IF_substage_1);

    uint64_t n_IF_substage_2 = perfModel->graph.add_node(F_Type::IF_substage_2, 1, n_IF_stage_ID);
    perfModel->graph.add_stage_connection(n_IF_substage_1, n_IF_substage_2);
    
    uint64_t n_IQ_stage_ID = perfModel->graph.add_node(F_Type::IQ_stage);
    perfModel->graph.add_stage_connection(n_IF_stage_ID, n_IQ_stage_ID);
    perfModel->graph.set_inorder(perfModel->nodes_IQ.back(), n_IQ_stage_ID);
    perfModel->graph.add_edge(n_IF_substage_2, n_IQ_stage_ID);

    uint64_t n_ID_stage_ID = perfModel->graph.add_node(F_Type::ID_stage);
    perfModel->graph.add_stage_connection(n_IQ_stage_ID, n_ID_stage_ID);
    perfModel->graph.set_inorder(perfModel->nodes_ID.back(), n_ID_stage_ID);

    uint64_t n_IS_stage_ID = perfModel->graph.add_node(F_Type::IS_stage);
    perfModel->graph.add_stage_connection(n_ID_stage_ID, n_IS_stage_ID);
    perfModel->graph.set_inorder(perfModel->nodes_IS.back(), n_IS_stage_ID);

    uint64_t n_EX_stage_ID = perfModel->graph.add_parent_node(F_Type::EX_stage);
    perfModel->graph.add_stage_connection(n_ID_stage_ID, n_EX_stage_ID);
    perfModel->graph.set_inorder(perfModel->nodes_EX.back(), n_EX_stage_ID);

    perfModel->graph.add_edge(perfModel->last_EX_alu, n_EX_stage_ID);
    perfModel->graph.add_edge(perfModel->last_EX_mul_o, n_EX_stage_ID);
    perfModel->graph.add_edge(perfModel->last_EX_div, n_EX_stage_ID);

    // ALU delay = 1
    uint64_t n_EX_substage_alu = perfModel->graph.add_node(F_Type::EX_substage_alu, 1, n_EX_stage_ID);
    // MUL_O / DIV blocks ALU
    perfModel->regModel.setXd(n_EX_substage_alu);

    uint64_t n_COM_stage_ID = perfModel->graph.add_node(F_Type::COM_stage);
    perfModel->graph.add_stage_connection(n_EX_stage_ID, n_COM_stage_ID);
    perfModel->graph.add_edge(n_EX_substage_alu, n_COM_stage_ID);
    perfModel->graph.set_inorder(perfModel->nodes_COM.back(), n_COM_stage_ID);
    perfModel->clobberModel.setCb_in(n_COM_stage_ID);

    // Add Nodes IDs to Stack
    perfModel->nodes_PC.push_back(n_PC_stage_ID);
    perfModel->nodes_IF.push_back(n_IF_stage_ID);
    perfModel->nodes_IQ.push_back(n_IQ_stage_ID);
    perfModel->nodes_ID.push_back(n_ID_stage_ID);
    perfModel->nodes_IS.push_back(n_IS_stage_ID);
    perfModel->nodes_EX.push_back(n_EX_stage_ID);
    perfModel->nodes_COM.push_back(n_COM_stage_ID);

    perfModel->last_IF_substage = n_IF_substage_2;
    perfModel->last_EX_substage = n_EX_substage_alu;

    perfModel->last_EX_alu = n_EX_substage_alu;

    // Dump Entrance point for info print (tracing)
    perfModel->entrancePoint = enterPoint + 1;
}

inline void Arith_Rs1(PerformanceModel* perfModel_) {
    CVA6_PerformanceModel* perfModel = static_cast<CVA6_PerformanceModel*>(perfModel_);
    uint64_t enterPoint = perfModel->entrancePoint;

    uint64_t n_PC_stage_ID = perfModel->graph.add_node(F_Type::PC_stage);
    perfModel->graph.add_edge(0, n_PC_stage_ID);

    uint64_t n_IF_stage_ID = perfModel->graph.add_parent_node(F_Type::IF_stage);
    perfModel->graph.add_stage_connection(n_PC_stage_ID, n_IF_stage_ID);
    perfModel->graph.set_inorder(perfModel->nodes_IF.back(), n_IF_stage_ID);
    perfModel->graph.add_edge(perfModel->dynBranchPredModel.getPc_mp(), n_IF_stage_ID);
    perfModel->graph.add_edge(perfModel->iCacheModel.getIc_out(), n_IF_stage_ID);

    uint64_t n_IF_substage_0 = perfModel->graph.add_node(F_Type::IF_substage_0, 1, n_IF_stage_ID);
    
    uint64_t n_IF_substage_1 = perfModel->graph.add_node(F_Type::IF_substage_1, perfModel->iCacheModel.getDelay(), n_IF_stage_ID);
    perfModel->graph.add_stage_connection(n_IF_substage_0, n_IF_substage_1);
    perfModel->graph.add_edge(perfModel->dynBranchPredModel.getPc_pt(), n_IF_substage_1);
    perfModel->iCacheModel.setIc_in(n_IF_substage_1);

    uint64_t n_IF_substage_2 = perfModel->graph.add_node(F_Type::IF_substage_2, 1, n_IF_stage_ID);
    perfModel->graph.add_stage_connection(n_IF_substage_1, n_IF_substage_2);
    
    uint64_t n_IQ_stage_ID = perfModel->graph.add_node(F_Type::IQ_stage);
    perfModel->graph.add_stage_connection(n_IF_stage_ID, n_IQ_stage_ID);
    perfModel->graph.set_inorder(perfModel->nodes_IQ.back(), n_IQ_stage_ID);
    perfModel->graph.add_edge(n_IF_substage_2, n_IQ_stage_ID);

    uint64_t n_ID_stage_ID = perfModel->graph.add_node(F_Type::ID_stage);
    perfModel->graph.add_stage_connection(n_IQ_stage_ID, n_ID_stage_ID);
    perfModel->graph.set_inorder(perfModel->nodes_ID.back(), n_ID_stage_ID);

    uint64_t n_IS_stage_ID = perfModel->graph.add_node(F_Type::IS_stage);
    perfModel->graph.add_stage_connection(n_ID_stage_ID, n_IS_stage_ID);
    perfModel->graph.set_inorder(perfModel->nodes_IS.back(), n_IS_stage_ID);

    uint64_t n_EX_stage_ID = perfModel->graph.add_parent_node(F_Type::EX_stage);
    perfModel->graph.add_stage_connection(n_ID_stage_ID, n_EX_stage_ID);
    perfModel->graph.set_inorder(perfModel->nodes_EX.back(), n_EX_stage_ID);
    // Input requrirements from IS-Stage DEF.
    perfModel->graph.add_edge(perfModel->regModel.getXa(), n_EX_stage_ID);
    perfModel->graph.add_edge(perfModel->clobberModel.getCb_out(), n_EX_stage_ID);

    perfModel->graph.add_edge(perfModel->last_EX_alu, n_EX_stage_ID);
    perfModel->graph.add_edge(perfModel->last_EX_mul_o, n_EX_stage_ID);
    perfModel->graph.add_edge(perfModel->last_EX_div, n_EX_stage_ID);

    // ALU delay = 1
    uint64_t n_EX_substage_alu = perfModel->graph.add_node(F_Type::EX_substage_alu, 1, n_EX_stage_ID);
    // MUL_O / DIV blocks ALU
    perfModel->regModel.setXd(n_EX_substage_alu);

    uint64_t n_COM_stage_ID = perfModel->graph.add_node(F_Type::COM_stage);
    perfModel->graph.add_stage_connection(n_EX_stage_ID, n_COM_stage_ID);
    perfModel->graph.add_edge(n_EX_substage_alu, n_COM_stage_ID);
    perfModel->graph.set_inorder(perfModel->nodes_COM.back(), n_COM_stage_ID);
    perfModel->clobberModel.setCb_in(n_COM_stage_ID);

    // Add Nodes IDs to Stack
    perfModel->nodes_PC.push_back(n_PC_stage_ID);
    perfModel->nodes_IF.push_back(n_IF_stage_ID);
    perfModel->nodes_IQ.push_back(n_IQ_stage_ID);
    perfModel->nodes_ID.push_back(n_ID_stage_ID);
    perfModel->nodes_IS.push_back(n_IS_stage_ID);
    perfModel->nodes_EX.push_back(n_EX_stage_ID);
    perfModel->nodes_COM.push_back(n_COM_stage_ID);

    perfModel->last_IF_substage = n_IF_substage_2;
    perfModel->last_EX_substage = n_EX_substage_alu;

    perfModel->last_EX_alu = n_EX_substage_alu;

    // Dump Entrance point for info print (tracing)
    perfModel->entrancePoint = enterPoint + 1;
}

inline void Arith_Rs1_Rs2(PerformanceModel* perfModel_) {
    CVA6_PerformanceModel* perfModel = static_cast<CVA6_PerformanceModel*>(perfModel_);
    uint64_t enterPoint = perfModel->entrancePoint;

    uint64_t n_PC_stage_ID = perfModel->graph.add_node(F_Type::PC_stage);
    perfModel->graph.add_edge(0, n_PC_stage_ID);

    uint64_t n_IF_stage_ID = perfModel->graph.add_parent_node(F_Type::IF_stage);
    perfModel->graph.add_stage_connection(n_PC_stage_ID, n_IF_stage_ID);
    perfModel->graph.set_inorder(perfModel->nodes_IF.back(), n_IF_stage_ID);
    perfModel->graph.add_edge(perfModel->dynBranchPredModel.getPc_mp(), n_IF_stage_ID);
    perfModel->graph.add_edge(perfModel->iCacheModel.getIc_out(), n_IF_stage_ID);

    uint64_t n_IF_substage_0 = perfModel->graph.add_node(F_Type::IF_substage_0, 1, n_IF_stage_ID);
    
    uint64_t n_IF_substage_1 = perfModel->graph.add_node(F_Type::IF_substage_1, perfModel->iCacheModel.getDelay(), n_IF_stage_ID);
    perfModel->graph.add_stage_connection(n_IF_substage_0, n_IF_substage_1);
    perfModel->graph.add_edge(perfModel->dynBranchPredModel.getPc_pt(), n_IF_substage_1);
    perfModel->iCacheModel.setIc_in(n_IF_substage_1);

    uint64_t n_IF_substage_2 = perfModel->graph.add_node(F_Type::IF_substage_2, 1, n_IF_stage_ID);
    perfModel->graph.add_stage_connection(n_IF_substage_1, n_IF_substage_2);
    
    uint64_t n_IQ_stage_ID = perfModel->graph.add_node(F_Type::IQ_stage);
    perfModel->graph.add_stage_connection(n_IF_stage_ID, n_IQ_stage_ID);
    perfModel->graph.set_inorder(perfModel->nodes_IQ.back(), n_IQ_stage_ID);
    perfModel->graph.add_edge(n_IF_substage_2, n_IQ_stage_ID);

    uint64_t n_ID_stage_ID = perfModel->graph.add_node(F_Type::ID_stage);
    perfModel->graph.add_stage_connection(n_IQ_stage_ID, n_ID_stage_ID);
    perfModel->graph.set_inorder(perfModel->nodes_ID.back(), n_ID_stage_ID);

    uint64_t n_IS_stage_ID = perfModel->graph.add_node(F_Type::IS_stage);
    perfModel->graph.add_stage_connection(n_ID_stage_ID, n_IS_stage_ID);
    perfModel->graph.set_inorder(perfModel->nodes_IS.back(), n_IS_stage_ID);

    uint64_t n_EX_stage_ID = perfModel->graph.add_parent_node(F_Type::EX_stage);
    perfModel->graph.add_stage_connection(n_ID_stage_ID, n_EX_stage_ID);
    perfModel->graph.set_inorder(perfModel->nodes_EX.back(), n_EX_stage_ID);
    // Input requrirements from IS-Stage DEF.
    perfModel->graph.add_edge(perfModel->regModel.getXa(), n_EX_stage_ID);
    perfModel->graph.add_edge(perfModel->regModel.getXb(), n_EX_stage_ID);
    perfModel->graph.add_edge(perfModel->clobberModel.getCb_out(), n_EX_stage_ID);

    perfModel->graph.add_edge(perfModel->last_EX_alu, n_EX_stage_ID);
    perfModel->graph.add_edge(perfModel->last_EX_mul_o, n_EX_stage_ID);
    perfModel->graph.add_edge(perfModel->last_EX_div, n_EX_stage_ID);

    // ALU delay = 1
    uint64_t n_EX_substage_alu = perfModel->graph.add_node(F_Type::EX_substage_alu, 1, n_EX_stage_ID);
    // MUL_O / DIV blocks ALU
    perfModel->regModel.setXd(n_EX_substage_alu);

    uint64_t n_COM_stage_ID = perfModel->graph.add_node(F_Type::COM_stage);
    perfModel->graph.add_stage_connection(n_EX_stage_ID, n_COM_stage_ID);
    perfModel->graph.set_inorder(perfModel->nodes_COM.back(), n_COM_stage_ID);
    perfModel->graph.add_edge(n_EX_substage_alu, n_COM_stage_ID);
    perfModel->clobberModel.setCb_in(n_COM_stage_ID);

    // Add Nodes IDs to Stack
    perfModel->nodes_PC.push_back(n_PC_stage_ID);
    perfModel->nodes_IF.push_back(n_IF_stage_ID);
    perfModel->nodes_IQ.push_back(n_IQ_stage_ID);
    perfModel->nodes_ID.push_back(n_ID_stage_ID);
    perfModel->nodes_IS.push_back(n_IS_stage_ID);
    perfModel->nodes_EX.push_back(n_EX_stage_ID);
    perfModel->nodes_COM.push_back(n_COM_stage_ID);

    perfModel->last_IF_substage = n_IF_substage_2;
    perfModel->last_EX_substage = n_EX_substage_alu;

    perfModel->last_EX_alu = n_EX_substage_alu;

    // Dump Entrance point for info print (tracing)
    perfModel->entrancePoint = enterPoint + 1;
}

inline void Branch(PerformanceModel* perfModel_) {
    CVA6_PerformanceModel* perfModel = static_cast<CVA6_PerformanceModel*>(perfModel_);
    uint64_t enterPoint = perfModel->entrancePoint;

    uint64_t n_PC_stage_ID = perfModel->graph.add_node(F_Type::PC_stage);
    perfModel->graph.add_edge(0, n_PC_stage_ID);

    uint64_t n_IF_stage_ID = perfModel->graph.add_parent_node(F_Type::IF_stage);
    perfModel->graph.add_stage_connection(n_PC_stage_ID, n_IF_stage_ID);
    perfModel->graph.set_inorder(perfModel->nodes_IF.back(), n_IF_stage_ID);
    perfModel->graph.add_edge(perfModel->dynBranchPredModel.getPc_mp(), n_IF_stage_ID);
    perfModel->graph.add_edge(perfModel->iCacheModel.getIc_out(), n_IF_stage_ID);

    uint64_t n_IF_substage_0 = perfModel->graph.add_node(F_Type::IF_substage_0, 1, n_IF_stage_ID);
    
    uint64_t n_IF_substage_1 = perfModel->graph.add_node(F_Type::IF_substage_1, perfModel->iCacheModel.getDelay(), n_IF_stage_ID);
    perfModel->graph.add_stage_connection(n_IF_substage_0, n_IF_substage_1);
    perfModel->graph.add_edge(perfModel->dynBranchPredModel.getPc_pt(), n_IF_substage_1);
    perfModel->iCacheModel.setIc_in(n_IF_substage_1);

    uint64_t n_IF_substage_2 = perfModel->graph.add_node(F_Type::IF_substage_2, 1, n_IF_stage_ID);
    perfModel->graph.add_stage_connection(n_IF_substage_1, n_IF_substage_2);
    perfModel->dynBranchPredModel.setPc_p(n_IF_substage_2);
    
    uint64_t n_IQ_stage_ID = perfModel->graph.add_node(F_Type::IQ_stage);
    perfModel->graph.add_stage_connection(n_IF_stage_ID, n_IQ_stage_ID);
    perfModel->graph.set_inorder(perfModel->nodes_IQ.back(), n_IQ_stage_ID);
    perfModel->graph.add_edge(n_IF_substage_2, n_IQ_stage_ID);

    uint64_t n_ID_stage_ID = perfModel->graph.add_node(F_Type::ID_stage);
    perfModel->graph.add_stage_connection(n_IQ_stage_ID, n_ID_stage_ID);
    perfModel->graph.set_inorder(perfModel->nodes_ID.back(), n_ID_stage_ID);

    uint64_t n_IS_stage_ID = perfModel->graph.add_node(F_Type::IS_stage);
    perfModel->graph.add_stage_connection(n_ID_stage_ID, n_IS_stage_ID);
    perfModel->graph.set_inorder(perfModel->nodes_IS.back(), n_IS_stage_ID);

    uint64_t n_EX_stage_ID = perfModel->graph.add_parent_node(F_Type::EX_stage);
    perfModel->graph.add_stage_connection(n_ID_stage_ID, n_EX_stage_ID);
    perfModel->graph.set_inorder(perfModel->nodes_EX.back(), n_EX_stage_ID);
    // Input requrirements from IS-Stage DEF.
    perfModel->graph.add_edge(perfModel->regModel.getXa(), n_EX_stage_ID);
    perfModel->graph.add_edge(perfModel->regModel.getXb(), n_EX_stage_ID);

    perfModel->graph.add_edge(perfModel->last_EX_alu, n_EX_stage_ID);
    perfModel->graph.add_edge(perfModel->last_EX_mul_o, n_EX_stage_ID);
    perfModel->graph.add_edge(perfModel->last_EX_div, n_EX_stage_ID);

    // ALU delay = 1
    uint64_t n_EX_substage_alu = perfModel->graph.add_node(F_Type::EX_substage_alu, 1, n_EX_stage_ID);
    // MUL_O / DIV blocks ALU
    perfModel->dynBranchPredModel.setPc_c(n_EX_substage_alu);

    uint64_t n_COM_stage_ID = perfModel->graph.add_node(F_Type::COM_stage);
    perfModel->graph.add_stage_connection(n_EX_stage_ID, n_COM_stage_ID);
    perfModel->graph.set_inorder(perfModel->nodes_COM.back(), n_COM_stage_ID);
    perfModel->graph.add_edge(n_EX_substage_alu, n_COM_stage_ID);

    // Add Nodes IDs to Stack
    perfModel->nodes_PC.push_back(n_PC_stage_ID);
    perfModel->nodes_IF.push_back(n_IF_stage_ID);
    perfModel->nodes_IQ.push_back(n_IQ_stage_ID);
    perfModel->nodes_ID.push_back(n_ID_stage_ID);
    perfModel->nodes_IS.push_back(n_IS_stage_ID);
    perfModel->nodes_EX.push_back(n_EX_stage_ID);
    perfModel->nodes_COM.push_back(n_COM_stage_ID);

    perfModel->last_IF_substage = n_IF_substage_2;
    perfModel->last_EX_substage = n_EX_substage_alu;

    perfModel->last_EX_alu = n_EX_substage_alu;

    // Dump Entrance point for info print (tracing)
    perfModel->entrancePoint = enterPoint + 1;
}

inline void Jump(PerformanceModel* perfModel_) {
    CVA6_PerformanceModel* perfModel = static_cast<CVA6_PerformanceModel*>(perfModel_);
    uint64_t enterPoint = perfModel->entrancePoint;

    uint64_t n_PC_stage_ID = perfModel->graph.add_node(F_Type::PC_stage);
    perfModel->graph.add_edge(0, n_PC_stage_ID);

    uint64_t n_IF_stage_ID = perfModel->graph.add_parent_node(F_Type::IF_stage);
    perfModel->graph.add_stage_connection(n_PC_stage_ID, n_IF_stage_ID);
    perfModel->graph.set_inorder(perfModel->nodes_IF.back(), n_IF_stage_ID);
    perfModel->graph.add_edge(perfModel->dynBranchPredModel.getPc_mp(), n_IF_stage_ID);
    perfModel->graph.add_edge(perfModel->iCacheModel.getIc_out(), n_IF_stage_ID);

    uint64_t n_IF_substage_0 = perfModel->graph.add_node(F_Type::IF_substage_0, 1, n_IF_stage_ID);
    
    uint64_t n_IF_substage_1 = perfModel->graph.add_node(F_Type::IF_substage_1, perfModel->iCacheModel.getDelay(), n_IF_stage_ID);
    perfModel->graph.add_stage_connection(n_IF_substage_0, n_IF_substage_1);
    perfModel->graph.add_edge(perfModel->dynBranchPredModel.getPc_pt(), n_IF_substage_1);
    perfModel->iCacheModel.setIc_in(n_IF_substage_1);

    uint64_t n_IF_substage_2 = perfModel->graph.add_node(F_Type::IF_substage_2, 1, n_IF_stage_ID);
    perfModel->graph.add_stage_connection(n_IF_substage_1, n_IF_substage_2);
    perfModel->dynBranchPredModel.setPc_p_j(n_IF_substage_2);
    
    uint64_t n_IQ_stage_ID = perfModel->graph.add_node(F_Type::IQ_stage);
    perfModel->graph.add_stage_connection(n_IF_stage_ID, n_IQ_stage_ID);
    perfModel->graph.set_inorder(perfModel->nodes_IQ.back(), n_IQ_stage_ID);
    perfModel->graph.add_edge(n_IF_substage_2, n_IQ_stage_ID);

    uint64_t n_ID_stage_ID = perfModel->graph.add_node(F_Type::ID_stage);
    perfModel->graph.add_stage_connection(n_IQ_stage_ID, n_ID_stage_ID);
    perfModel->graph.set_inorder(perfModel->nodes_ID.back(), n_ID_stage_ID);

    uint64_t n_IS_stage_ID = perfModel->graph.add_node(F_Type::IS_stage);
    perfModel->graph.add_stage_connection(n_ID_stage_ID, n_IS_stage_ID);
    perfModel->graph.set_inorder(perfModel->nodes_IS.back(), n_IS_stage_ID);

    uint64_t n_EX_stage_ID = perfModel->graph.add_parent_node(F_Type::EX_stage);
    perfModel->graph.add_stage_connection(n_ID_stage_ID, n_EX_stage_ID);
    perfModel->graph.set_inorder(perfModel->nodes_EX.back(), n_EX_stage_ID);
    // Input requrirements from IS-Stage DEF.
    perfModel->graph.add_edge(perfModel->clobberModel.getCb_out(), n_EX_stage_ID);
    // MUL_O / DIV blocks ALU
    perfModel->graph.add_edge(perfModel->last_EX_alu, n_EX_stage_ID);
    perfModel->graph.add_edge(perfModel->last_EX_mul_o, n_EX_stage_ID);
    perfModel->graph.add_edge(perfModel->last_EX_div, n_EX_stage_ID);
    // ALU delay = 1
    uint64_t n_EX_substage_alu = perfModel->graph.add_node(F_Type::EX_substage_alu, 1, n_EX_stage_ID);
    perfModel->regModel.setXd(n_EX_substage_alu);

    uint64_t n_COM_stage_ID = perfModel->graph.add_node(F_Type::COM_stage);
    perfModel->graph.add_stage_connection(n_EX_stage_ID, n_COM_stage_ID);
    perfModel->graph.set_inorder(perfModel->nodes_COM.back(), n_COM_stage_ID);
    perfModel->clobberModel.setCb_in(n_COM_stage_ID);
    perfModel->graph.add_edge(n_EX_substage_alu, n_COM_stage_ID);

    // Add Nodes IDs to Stack
    perfModel->nodes_PC.push_back(n_PC_stage_ID);
    perfModel->nodes_IF.push_back(n_IF_stage_ID);
    perfModel->nodes_IQ.push_back(n_IQ_stage_ID);
    perfModel->nodes_ID.push_back(n_ID_stage_ID);
    perfModel->nodes_IS.push_back(n_IS_stage_ID);
    perfModel->nodes_EX.push_back(n_EX_stage_ID);
    perfModel->nodes_COM.push_back(n_COM_stage_ID);

    perfModel->last_IF_substage = n_IF_substage_2;
    perfModel->last_EX_substage = n_EX_substage_alu;

    perfModel->last_EX_alu = n_EX_substage_alu;

    // Dump Entrance point for info print (tracing)
    perfModel->entrancePoint = enterPoint + 1;
}

inline void JumpR(PerformanceModel* perfModel_) {
    CVA6_PerformanceModel* perfModel = static_cast<CVA6_PerformanceModel*>(perfModel_);
    uint64_t enterPoint = perfModel->entrancePoint;

    uint64_t n_PC_stage_ID = perfModel->graph.add_node(F_Type::PC_stage);
    perfModel->graph.add_edge(0, n_PC_stage_ID);

    uint64_t n_IF_stage_ID = perfModel->graph.add_parent_node(F_Type::IF_stage);
    perfModel->graph.add_stage_connection(n_PC_stage_ID, n_IF_stage_ID);
    perfModel->graph.set_inorder(perfModel->nodes_IF.back(), n_IF_stage_ID);
    perfModel->graph.add_edge(perfModel->dynBranchPredModel.getPc_mp(), n_IF_stage_ID);
    perfModel->graph.add_edge(perfModel->iCacheModel.getIc_out(), n_IF_stage_ID);

    uint64_t n_IF_substage_0 = perfModel->graph.add_node(F_Type::IF_substage_0, 1, n_IF_stage_ID);
    
    uint64_t n_IF_substage_1 = perfModel->graph.add_node(F_Type::IF_substage_1, perfModel->iCacheModel.getDelay(), n_IF_stage_ID);
    perfModel->graph.add_stage_connection(n_IF_substage_0, n_IF_substage_1);
    perfModel->graph.add_edge(perfModel->dynBranchPredModel.getPc_pt(), n_IF_substage_1);
    perfModel->iCacheModel.setIc_in(n_IF_substage_1);

    uint64_t n_IF_substage_2 = perfModel->graph.add_node(F_Type::IF_substage_2, 1, n_IF_stage_ID);
    perfModel->graph.add_stage_connection(n_IF_substage_1, n_IF_substage_2);
    perfModel->dynBranchPredModel.setPc_p_jr(n_IF_substage_2);
    
    uint64_t n_IQ_stage_ID = perfModel->graph.add_node(F_Type::IQ_stage);
    perfModel->graph.add_stage_connection(n_IF_stage_ID, n_IQ_stage_ID);
    perfModel->graph.set_inorder(perfModel->nodes_IQ.back(), n_IQ_stage_ID);
    perfModel->graph.add_edge(n_IF_substage_2, n_IQ_stage_ID);

    uint64_t n_ID_stage_ID = perfModel->graph.add_node(F_Type::ID_stage);
    perfModel->graph.add_stage_connection(n_IQ_stage_ID, n_ID_stage_ID);
    perfModel->graph.set_inorder(perfModel->nodes_ID.back(), n_ID_stage_ID);

    uint64_t n_IS_stage_ID = perfModel->graph.add_node(F_Type::IS_stage);
    perfModel->graph.add_stage_connection(n_ID_stage_ID, n_IS_stage_ID);
    perfModel->graph.set_inorder(perfModel->nodes_IS.back(), n_IS_stage_ID);

    uint64_t n_EX_stage_ID = perfModel->graph.add_parent_node(F_Type::EX_stage);
    perfModel->graph.add_stage_connection(n_ID_stage_ID, n_EX_stage_ID);
    perfModel->graph.set_inorder(perfModel->nodes_EX.back(), n_EX_stage_ID);
    // Input requrirements from IS-Stage DEF.
    perfModel->graph.add_edge(perfModel->regModel.getXa(), n_EX_stage_ID);
    perfModel->graph.add_edge(perfModel->clobberModel.getCb_out(), n_EX_stage_ID);
    // MUL_O / DIV blocks ALU
    perfModel->graph.add_edge(perfModel->last_EX_alu, n_EX_stage_ID);
    perfModel->graph.add_edge(perfModel->last_EX_mul_o, n_EX_stage_ID);
    perfModel->graph.add_edge(perfModel->last_EX_div, n_EX_stage_ID);
    // ALU delay = 1
    uint64_t n_EX_substage_alu = perfModel->graph.add_node(F_Type::EX_substage_alu, 1, n_EX_stage_ID);
    perfModel->regModel.setXd(n_EX_substage_alu);
    perfModel->dynBranchPredModel.setPc_c(n_EX_substage_alu);

    uint64_t n_COM_stage_ID = perfModel->graph.add_node(F_Type::COM_stage);
    perfModel->graph.add_stage_connection(n_EX_stage_ID, n_COM_stage_ID);
    perfModel->graph.set_inorder(perfModel->nodes_COM.back(), n_COM_stage_ID);
    perfModel->clobberModel.setCb_in(n_COM_stage_ID);
    perfModel->graph.add_edge(n_EX_substage_alu, n_COM_stage_ID);

    // Add Nodes IDs to Stack
    perfModel->nodes_PC.push_back(n_PC_stage_ID);
    perfModel->nodes_IF.push_back(n_IF_stage_ID);
    perfModel->nodes_IQ.push_back(n_IQ_stage_ID);
    perfModel->nodes_ID.push_back(n_ID_stage_ID);
    perfModel->nodes_IS.push_back(n_IS_stage_ID);
    perfModel->nodes_EX.push_back(n_EX_stage_ID);
    perfModel->nodes_COM.push_back(n_COM_stage_ID);

    perfModel->last_IF_substage = n_IF_substage_2;
    perfModel->last_EX_substage = n_EX_substage_alu;

    perfModel->last_EX_alu = n_EX_substage_alu;

    // Dump Entrance point for info print (tracing)
    perfModel->entrancePoint = enterPoint + 1;
}

inline void Mul(PerformanceModel* perfModel_) {
    CVA6_PerformanceModel* perfModel = static_cast<CVA6_PerformanceModel*>(perfModel_);
    uint64_t enterPoint = perfModel->entrancePoint;

    uint64_t n_PC_stage_ID = perfModel->graph.add_node(F_Type::PC_stage);
    perfModel->graph.add_edge(0, n_PC_stage_ID);

    uint64_t n_IF_stage_ID = perfModel->graph.add_parent_node(F_Type::IF_stage);
    perfModel->graph.add_stage_connection(n_PC_stage_ID, n_IF_stage_ID);
    perfModel->graph.set_inorder(perfModel->nodes_IF.back(), n_IF_stage_ID);
    perfModel->graph.add_edge(perfModel->dynBranchPredModel.getPc_mp(), n_IF_stage_ID);
    perfModel->graph.add_edge(perfModel->iCacheModel.getIc_out(), n_IF_stage_ID);

    uint64_t n_IF_substage_0 = perfModel->graph.add_node(F_Type::IF_substage_0, 1, n_IF_stage_ID);
    
    uint64_t n_IF_substage_1 = perfModel->graph.add_node(F_Type::IF_substage_1, perfModel->iCacheModel.getDelay(), n_IF_stage_ID);
    perfModel->graph.add_stage_connection(n_IF_substage_0, n_IF_substage_1);
    perfModel->graph.add_edge(perfModel->dynBranchPredModel.getPc_pt(), n_IF_substage_1);
    perfModel->iCacheModel.setIc_in(n_IF_substage_1);

    uint64_t n_IF_substage_2 = perfModel->graph.add_node(F_Type::IF_substage_2, 1, n_IF_stage_ID);
    perfModel->graph.add_stage_connection(n_IF_substage_1, n_IF_substage_2);
    
    uint64_t n_IQ_stage_ID = perfModel->graph.add_node(F_Type::IQ_stage);
    perfModel->graph.add_stage_connection(n_IF_stage_ID, n_IQ_stage_ID);
    perfModel->graph.set_inorder(perfModel->nodes_IQ.back(), n_IQ_stage_ID);
    perfModel->graph.add_edge(n_IF_substage_2, n_IQ_stage_ID);

    uint64_t n_ID_stage_ID = perfModel->graph.add_node(F_Type::ID_stage);
    perfModel->graph.add_stage_connection(n_IQ_stage_ID, n_ID_stage_ID);
    perfModel->graph.set_inorder(perfModel->nodes_ID.back(), n_ID_stage_ID);

    uint64_t n_IS_stage_ID = perfModel->graph.add_node(F_Type::IS_stage);
    perfModel->graph.add_stage_connection(n_ID_stage_ID, n_IS_stage_ID);
    perfModel->graph.set_inorder(perfModel->nodes_IS.back(), n_IS_stage_ID);

    uint64_t n_EX_stage_ID = perfModel->graph.add_parent_node(F_Type::EX_stage);
    perfModel->graph.add_stage_connection(n_ID_stage_ID, n_EX_stage_ID);
    perfModel->graph.set_inorder(perfModel->nodes_EX.back(), n_EX_stage_ID);
    // Input requrirements from IS-Stage DEF.
    perfModel->graph.add_edge(perfModel->regModel.getXa(), n_EX_stage_ID);
    perfModel->graph.add_edge(perfModel->regModel.getXb(), n_EX_stage_ID);
    perfModel->graph.add_edge(perfModel->clobberModel.getCb_out(), n_EX_stage_ID);
    // DIV blocks MUL_I
    perfModel->graph.add_edge(perfModel->last_EX_mul_i, n_EX_stage_ID);
    perfModel->graph.add_edge(perfModel->last_EX_div, n_EX_stage_ID);

    // MUL delay = 2 pipelined
    uint64_t n_EX_substage_mul_i = perfModel->graph.add_node(F_Type::EX_substage_mul_i, 1, n_EX_stage_ID);
    uint64_t n_EX_substage_mul_o = perfModel->graph.add_node(F_Type::EX_substage_mul_o, 1, n_EX_stage_ID);
    perfModel->graph.add_edge(n_EX_substage_mul_i, n_EX_substage_mul_o);
    perfModel->regModel.setXd(n_EX_substage_mul_o);

    uint64_t n_COM_stage_ID = perfModel->graph.add_node(F_Type::COM_stage);
    perfModel->graph.add_stage_connection(n_EX_stage_ID, n_COM_stage_ID);
    perfModel->graph.set_inorder(perfModel->nodes_COM.back(), n_COM_stage_ID);
    perfModel->clobberModel.setCb_in(n_COM_stage_ID);
    perfModel->graph.add_edge(n_EX_substage_mul_o, n_COM_stage_ID);

    // Add Nodes IDs to Stack
    perfModel->nodes_PC.push_back(n_PC_stage_ID);
    perfModel->nodes_IF.push_back(n_IF_stage_ID);
    perfModel->nodes_IQ.push_back(n_IQ_stage_ID);
    perfModel->nodes_ID.push_back(n_ID_stage_ID);
    perfModel->nodes_IS.push_back(n_IS_stage_ID);
    perfModel->nodes_EX.push_back(n_EX_stage_ID);
    perfModel->nodes_COM.push_back(n_COM_stage_ID);

    perfModel->last_IF_substage = n_IF_substage_2;
    perfModel->last_EX_substage = n_EX_substage_mul_o;

    perfModel->last_EX_mul_i = n_EX_substage_mul_i;
    perfModel->last_EX_mul_o = n_EX_substage_mul_o;

    // Dump Entrance point for info print (tracing)
    perfModel->entrancePoint = enterPoint + 1;
}

inline void Div(PerformanceModel* perfModel_) {
    CVA6_PerformanceModel* perfModel = static_cast<CVA6_PerformanceModel*>(perfModel_);
    uint64_t enterPoint = perfModel->entrancePoint;

    uint64_t n_PC_stage_ID = perfModel->graph.add_node(F_Type::PC_stage);
    perfModel->graph.add_edge(0, n_PC_stage_ID);

    uint64_t n_IF_stage_ID = perfModel->graph.add_parent_node(F_Type::IF_stage);
    perfModel->graph.add_stage_connection(n_PC_stage_ID, n_IF_stage_ID);
    perfModel->graph.set_inorder(perfModel->nodes_IF.back(), n_IF_stage_ID);
    perfModel->graph.add_edge(perfModel->dynBranchPredModel.getPc_mp(), n_IF_stage_ID);
    perfModel->graph.add_edge(perfModel->iCacheModel.getIc_out(), n_IF_stage_ID);

    uint64_t n_IF_substage_0 = perfModel->graph.add_node(F_Type::IF_substage_0, 1, n_IF_stage_ID);
    
    uint64_t n_IF_substage_1 = perfModel->graph.add_node(F_Type::IF_substage_1, perfModel->iCacheModel.getDelay(), n_IF_stage_ID);
    perfModel->graph.add_stage_connection(n_IF_substage_0, n_IF_substage_1);
    perfModel->graph.add_edge(perfModel->dynBranchPredModel.getPc_pt(), n_IF_substage_1);
    perfModel->iCacheModel.setIc_in(n_IF_substage_1);

    uint64_t n_IF_substage_2 = perfModel->graph.add_node(F_Type::IF_substage_2, 1, n_IF_stage_ID);
    perfModel->graph.add_stage_connection(n_IF_substage_1, n_IF_substage_2);
    
    uint64_t n_IQ_stage_ID = perfModel->graph.add_node(F_Type::IQ_stage);
    perfModel->graph.add_stage_connection(n_IF_stage_ID, n_IQ_stage_ID);
    perfModel->graph.set_inorder(perfModel->nodes_IQ.back(), n_IQ_stage_ID);
    perfModel->graph.add_edge(n_IF_substage_2, n_IQ_stage_ID);

    uint64_t n_ID_stage_ID = perfModel->graph.add_node(F_Type::ID_stage);
    perfModel->graph.add_stage_connection(n_IQ_stage_ID, n_ID_stage_ID);
    perfModel->graph.set_inorder(perfModel->nodes_ID.back(), n_ID_stage_ID);

    uint64_t n_IS_stage_ID = perfModel->graph.add_node(F_Type::IS_stage);
    perfModel->graph.add_stage_connection(n_ID_stage_ID, n_IS_stage_ID);
    perfModel->graph.set_inorder(perfModel->nodes_IS.back(), n_IS_stage_ID);

    uint64_t n_EX_stage_ID = perfModel->graph.add_parent_node(F_Type::EX_stage);
    perfModel->graph.add_stage_connection(n_ID_stage_ID, n_EX_stage_ID);
    perfModel->graph.set_inorder(perfModel->nodes_EX.back(), n_EX_stage_ID);
    // Input requrirements from IS-Stage DEF.
    perfModel->graph.add_edge(perfModel->regModel.getXa(), n_EX_stage_ID);
    perfModel->graph.add_edge(perfModel->regModel.getXb(), n_EX_stage_ID);
    perfModel->graph.add_edge(perfModel->clobberModel.getCb_out(), n_EX_stage_ID);
    perfModel->graph.add_edge(perfModel->last_EX_div, n_EX_stage_ID);

    uint64_t n_EX_substage_div = perfModel->graph.add_node(F_Type::EX_substage_div, perfModel->divider.getDelay(), n_EX_stage_ID);
    perfModel->regModel.setXd(n_EX_substage_div);

    uint64_t n_COM_stage_ID = perfModel->graph.add_node(F_Type::COM_stage);
    perfModel->graph.add_stage_connection(n_EX_stage_ID, n_COM_stage_ID);
    perfModel->graph.set_inorder(perfModel->nodes_COM.back(), n_COM_stage_ID);
    perfModel->clobberModel.setCb_in(n_COM_stage_ID);
    perfModel->graph.add_edge(n_EX_substage_div, n_COM_stage_ID);

    // Add Nodes IDs to Stack
    perfModel->nodes_PC.push_back(n_PC_stage_ID);
    perfModel->nodes_IF.push_back(n_IF_stage_ID);
    perfModel->nodes_IQ.push_back(n_IQ_stage_ID);
    perfModel->nodes_ID.push_back(n_ID_stage_ID);
    perfModel->nodes_IS.push_back(n_IS_stage_ID);
    perfModel->nodes_EX.push_back(n_EX_stage_ID);
    perfModel->nodes_COM.push_back(n_COM_stage_ID);

    perfModel->last_IF_substage = n_IF_substage_2;
    perfModel->last_EX_substage = n_EX_substage_div;

    perfModel->last_EX_div = n_EX_substage_div;

    // Dump Entrance point for info print (tracing)
    perfModel->entrancePoint = enterPoint + 1;
}

inline void DivU(PerformanceModel* perfModel_) {
    CVA6_PerformanceModel* perfModel = static_cast<CVA6_PerformanceModel*>(perfModel_);
    uint64_t enterPoint = perfModel->entrancePoint;

    uint64_t n_PC_stage_ID = perfModel->graph.add_node(F_Type::PC_stage);
    perfModel->graph.add_edge(0, n_PC_stage_ID);

    uint64_t n_IF_stage_ID = perfModel->graph.add_parent_node(F_Type::IF_stage);
    perfModel->graph.add_stage_connection(n_PC_stage_ID, n_IF_stage_ID);
    perfModel->graph.set_inorder(perfModel->nodes_IF.back(), n_IF_stage_ID);
    perfModel->graph.add_edge(perfModel->dynBranchPredModel.getPc_mp(), n_IF_stage_ID);
    perfModel->graph.add_edge(perfModel->iCacheModel.getIc_out(), n_IF_stage_ID);

    uint64_t n_IF_substage_0 = perfModel->graph.add_node(F_Type::IF_substage_0, 1, n_IF_stage_ID);
    
    uint64_t n_IF_substage_1 = perfModel->graph.add_node(F_Type::IF_substage_1, perfModel->iCacheModel.getDelay(), n_IF_stage_ID);
    perfModel->graph.add_stage_connection(n_IF_substage_0, n_IF_substage_1);
    perfModel->graph.add_edge(perfModel->dynBranchPredModel.getPc_pt(), n_IF_substage_1);
    perfModel->iCacheModel.setIc_in(n_IF_substage_1);

    uint64_t n_IF_substage_2 = perfModel->graph.add_node(F_Type::IF_substage_2, 1, n_IF_stage_ID);
    perfModel->graph.add_stage_connection(n_IF_substage_1, n_IF_substage_2);
    
    uint64_t n_IQ_stage_ID = perfModel->graph.add_node(F_Type::IQ_stage);
    perfModel->graph.add_stage_connection(n_IF_stage_ID, n_IQ_stage_ID);
    perfModel->graph.set_inorder(perfModel->nodes_IQ.back(), n_IQ_stage_ID);
    perfModel->graph.add_edge(n_IF_substage_2, n_IQ_stage_ID);

    uint64_t n_ID_stage_ID = perfModel->graph.add_node(F_Type::ID_stage);
    perfModel->graph.add_stage_connection(n_IQ_stage_ID, n_ID_stage_ID);
    perfModel->graph.set_inorder(perfModel->nodes_ID.back(), n_ID_stage_ID);

    uint64_t n_IS_stage_ID = perfModel->graph.add_node(F_Type::IS_stage);
    perfModel->graph.add_stage_connection(n_ID_stage_ID, n_IS_stage_ID);
    perfModel->graph.set_inorder(perfModel->nodes_IS.back(), n_IS_stage_ID);

    uint64_t n_EX_stage_ID = perfModel->graph.add_parent_node(F_Type::EX_stage);
    perfModel->graph.add_stage_connection(n_ID_stage_ID, n_EX_stage_ID);
    perfModel->graph.set_inorder(perfModel->nodes_EX.back(), n_EX_stage_ID);
    // Input requrirements from IS-Stage DEF.
    perfModel->graph.add_edge(perfModel->regModel.getXa(), n_EX_stage_ID);
    perfModel->graph.add_edge(perfModel->regModel.getXb(), n_EX_stage_ID);
    perfModel->graph.add_edge(perfModel->clobberModel.getCb_out(), n_EX_stage_ID);
    perfModel->graph.add_edge(perfModel->last_EX_div, n_EX_stage_ID);

    uint64_t n_EX_substage_div = perfModel->graph.add_node(F_Type::EX_substage_div, perfModel->divider_u.getDelay(), n_EX_stage_ID);
    perfModel->regModel.setXd(n_EX_substage_div);

    uint64_t n_COM_stage_ID = perfModel->graph.add_node(F_Type::COM_stage);
    perfModel->graph.add_stage_connection(n_EX_stage_ID, n_COM_stage_ID);
    perfModel->graph.set_inorder(perfModel->nodes_COM.back(), n_COM_stage_ID);
    perfModel->clobberModel.setCb_in(n_COM_stage_ID);
    perfModel->graph.add_edge(n_EX_substage_div, n_COM_stage_ID);

    // Add Nodes IDs to Stack
    perfModel->nodes_PC.push_back(n_PC_stage_ID);
    perfModel->nodes_IF.push_back(n_IF_stage_ID);
    perfModel->nodes_IQ.push_back(n_IQ_stage_ID);
    perfModel->nodes_ID.push_back(n_ID_stage_ID);
    perfModel->nodes_IS.push_back(n_IS_stage_ID);
    perfModel->nodes_EX.push_back(n_EX_stage_ID);
    perfModel->nodes_COM.push_back(n_COM_stage_ID);

    perfModel->last_IF_substage = n_IF_substage_2;
    perfModel->last_EX_substage = n_EX_substage_div;

    perfModel->last_EX_div = n_EX_substage_div;

    // Dump Entrance point for info print (tracing)
    perfModel->entrancePoint = enterPoint + 1;
}

inline void Load(PerformanceModel* perfModel_) {
    CVA6_PerformanceModel* perfModel = static_cast<CVA6_PerformanceModel*>(perfModel_);
    uint64_t enterPoint = perfModel->entrancePoint;

    uint64_t n_PC_stage_ID = perfModel->graph.add_node(F_Type::PC_stage);
    perfModel->graph.add_edge(0, n_PC_stage_ID);

    uint64_t n_IF_stage_ID = perfModel->graph.add_parent_node(F_Type::IF_stage);
    perfModel->graph.add_stage_connection(n_PC_stage_ID, n_IF_stage_ID);
    perfModel->graph.set_inorder(perfModel->nodes_IF.back(), n_IF_stage_ID);
    perfModel->graph.add_edge(perfModel->dynBranchPredModel.getPc_mp(), n_IF_stage_ID);
    perfModel->graph.add_edge(perfModel->iCacheModel.getIc_out(), n_IF_stage_ID);

    uint64_t n_IF_substage_0 = perfModel->graph.add_node(F_Type::IF_substage_0, 1, n_IF_stage_ID);
    
    uint64_t n_IF_substage_1 = perfModel->graph.add_node(F_Type::IF_substage_1, perfModel->iCacheModel.getDelay(), n_IF_stage_ID);
    perfModel->graph.add_stage_connection(n_IF_substage_0, n_IF_substage_1);
    perfModel->graph.add_edge(perfModel->dynBranchPredModel.getPc_pt(), n_IF_substage_1);
    perfModel->iCacheModel.setIc_in(n_IF_substage_1);

    uint64_t n_IF_substage_2 = perfModel->graph.add_node(F_Type::IF_substage_2, 1, n_IF_stage_ID);
    perfModel->graph.add_stage_connection(n_IF_substage_1, n_IF_substage_2);
    
    uint64_t n_IQ_stage_ID = perfModel->graph.add_node(F_Type::IQ_stage);
    perfModel->graph.add_stage_connection(n_IF_stage_ID, n_IQ_stage_ID);
    perfModel->graph.set_inorder(perfModel->nodes_IQ.back(), n_IQ_stage_ID);
    perfModel->graph.add_edge(n_IF_substage_2, n_IQ_stage_ID);

    uint64_t n_ID_stage_ID = perfModel->graph.add_node(F_Type::ID_stage);
    perfModel->graph.add_stage_connection(n_IQ_stage_ID, n_ID_stage_ID);
    perfModel->graph.set_inorder(perfModel->nodes_ID.back(), n_ID_stage_ID);

    uint64_t n_IS_stage_ID = perfModel->graph.add_node(F_Type::IS_stage);
    perfModel->graph.add_stage_connection(n_ID_stage_ID, n_IS_stage_ID);
    perfModel->graph.set_inorder(perfModel->nodes_IS.back(), n_IS_stage_ID);

    uint64_t n_EX_stage_ID = perfModel->graph.add_parent_node(F_Type::EX_stage);
    perfModel->graph.add_stage_connection(n_ID_stage_ID, n_EX_stage_ID);
    perfModel->graph.set_inorder(perfModel->nodes_EX.back(), n_EX_stage_ID);
    // Input requrirements from IS-Stage DEF.
    perfModel->graph.add_edge(perfModel->regModel.getXa(), n_EX_stage_ID);
    perfModel->graph.add_edge(perfModel->clobberModel.getCb_out(), n_EX_stage_ID);
    perfModel->graph.add_edge(perfModel->last_EX_lCtrl, n_EX_stage_ID);

    uint64_t n_EX_substage_lCtrl = perfModel->graph.add_node(F_Type::EX_substage_lCtrl, 1, n_EX_stage_ID);
    uint64_t n_EX_substage_dCache = perfModel->graph.add_node(F_Type::EX_substage_dCache, perfModel->dCacheModel.getDelay(), n_EX_stage_ID);
    perfModel->graph.add_stage_connection(n_EX_substage_lCtrl, n_EX_substage_dCache);
    uint64_t n_EX_substage_lUnit = perfModel->graph.add_node(F_Type::EX_substage_lUnit, 1, n_EX_stage_ID);
    perfModel->graph.add_stage_connection(n_EX_substage_dCache, n_EX_substage_lUnit);
    perfModel->regModel.setXd(n_EX_substage_lUnit);

    uint64_t n_COM_stage_ID = perfModel->graph.add_node(F_Type::COM_stage);
    perfModel->graph.add_stage_connection(n_EX_stage_ID, n_COM_stage_ID);
    perfModel->graph.set_inorder(perfModel->nodes_COM.back(), n_COM_stage_ID);
    perfModel->clobberModel.setCb_in(n_COM_stage_ID);
    perfModel->graph.add_edge(n_EX_substage_lUnit, n_COM_stage_ID);

    // Add Nodes IDs to Stack
    perfModel->nodes_PC.push_back(n_PC_stage_ID);
    perfModel->nodes_IF.push_back(n_IF_stage_ID);
    perfModel->nodes_IQ.push_back(n_IQ_stage_ID);
    perfModel->nodes_ID.push_back(n_ID_stage_ID);
    perfModel->nodes_IS.push_back(n_IS_stage_ID);
    perfModel->nodes_EX.push_back(n_EX_stage_ID);
    perfModel->nodes_COM.push_back(n_COM_stage_ID);

    perfModel->last_IF_substage = n_IF_substage_2;
    perfModel->last_EX_substage = n_EX_substage_lUnit;

    perfModel->last_EX_lCtrl = n_EX_substage_lCtrl;

    // Dump Entrance point for info print (tracing)
    perfModel->entrancePoint = enterPoint + 1;
}

inline void Store(PerformanceModel* perfModel_) {
    CVA6_PerformanceModel* perfModel = static_cast<CVA6_PerformanceModel*>(perfModel_);
    uint64_t enterPoint = perfModel->entrancePoint;

    uint64_t n_PC_stage_ID = perfModel->graph.add_node(F_Type::PC_stage);
    perfModel->graph.add_edge(0, n_PC_stage_ID);

    uint64_t n_IF_stage_ID = perfModel->graph.add_parent_node(F_Type::IF_stage);
    perfModel->graph.add_stage_connection(n_PC_stage_ID, n_IF_stage_ID);
    perfModel->graph.set_inorder(perfModel->nodes_IF.back(), n_IF_stage_ID);
    perfModel->graph.add_edge(perfModel->dynBranchPredModel.getPc_mp(), n_IF_stage_ID);
    perfModel->graph.add_edge(perfModel->iCacheModel.getIc_out(), n_IF_stage_ID);

    uint64_t n_IF_substage_0 = perfModel->graph.add_node(F_Type::IF_substage_0, 1, n_IF_stage_ID);
    
    uint64_t n_IF_substage_1 = perfModel->graph.add_node(F_Type::IF_substage_1, perfModel->iCacheModel.getDelay(), n_IF_stage_ID);
    perfModel->graph.add_stage_connection(n_IF_substage_0, n_IF_substage_1);
    perfModel->graph.add_edge(perfModel->dynBranchPredModel.getPc_pt(), n_IF_substage_1);
    perfModel->iCacheModel.setIc_in(n_IF_substage_1);

    uint64_t n_IF_substage_2 = perfModel->graph.add_node(F_Type::IF_substage_2, 1, n_IF_stage_ID);
    perfModel->graph.add_stage_connection(n_IF_substage_1, n_IF_substage_2);
    
    uint64_t n_IQ_stage_ID = perfModel->graph.add_node(F_Type::IQ_stage);
    perfModel->graph.add_stage_connection(n_IF_stage_ID, n_IQ_stage_ID);
    perfModel->graph.set_inorder(perfModel->nodes_IQ.back(), n_IQ_stage_ID);
    perfModel->graph.add_edge(n_IF_substage_2, n_IQ_stage_ID);

    uint64_t n_ID_stage_ID = perfModel->graph.add_node(F_Type::ID_stage);
    perfModel->graph.add_stage_connection(n_IQ_stage_ID, n_ID_stage_ID);
    perfModel->graph.set_inorder(perfModel->nodes_ID.back(), n_ID_stage_ID);

    uint64_t n_IS_stage_ID = perfModel->graph.add_node(F_Type::IS_stage);
    perfModel->graph.add_stage_connection(n_ID_stage_ID, n_IS_stage_ID);
    perfModel->graph.set_inorder(perfModel->nodes_IS.back(), n_IS_stage_ID);

    uint64_t n_EX_stage_ID = perfModel->graph.add_parent_node(F_Type::EX_stage);
    perfModel->graph.add_stage_connection(n_ID_stage_ID, n_EX_stage_ID);
    perfModel->graph.set_inorder(perfModel->nodes_EX.back(), n_EX_stage_ID);
    // Input requrirements from IS-Stage DEF.
    perfModel->graph.add_edge(perfModel->regModel.getXa(), n_EX_stage_ID);
    perfModel->graph.add_edge(perfModel->regModel.getXb(), n_EX_stage_ID);
    perfModel->graph.add_edge(perfModel->last_EX_sCtrl, n_EX_stage_ID);

    uint64_t n_EX_substage_sCtrl = perfModel->graph.add_node(F_Type::EX_substage_sCtrl, 1, n_EX_stage_ID);
    uint64_t n_EX_substage_sUnit = perfModel->graph.add_node(F_Type::EX_substage_sUnit, 1, n_EX_stage_ID);
    perfModel->graph.add_stage_connection(n_EX_substage_sCtrl, n_EX_substage_sUnit);

    uint64_t n_COM_stage_ID = perfModel->graph.add_node(F_Type::COM_stage);
    perfModel->graph.add_stage_connection(n_EX_stage_ID, n_COM_stage_ID);
    perfModel->graph.set_inorder(perfModel->nodes_COM.back(), n_COM_stage_ID);
    perfModel->graph.add_edge(n_EX_substage_sUnit, n_COM_stage_ID);

    // Add Nodes IDs to Stack
    perfModel->nodes_PC.push_back(n_PC_stage_ID);
    perfModel->nodes_IF.push_back(n_IF_stage_ID);
    perfModel->nodes_IQ.push_back(n_IQ_stage_ID);
    perfModel->nodes_ID.push_back(n_ID_stage_ID);
    perfModel->nodes_IS.push_back(n_IS_stage_ID);
    perfModel->nodes_EX.push_back(n_EX_stage_ID);
    perfModel->nodes_COM.push_back(n_COM_stage_ID);

    perfModel->last_IF_substage = n_IF_substage_2;
    perfModel->last_EX_substage = n_EX_substage_sUnit;

    perfModel->last_EX_sCtrl = n_EX_substage_sCtrl;

    // Dump Entrance point for info print (tracing)
    perfModel->entrancePoint = enterPoint + 1;
}

}  // namespace CVA6