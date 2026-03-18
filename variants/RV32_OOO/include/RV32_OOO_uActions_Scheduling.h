#include <algorithm>
#include <cstdint>

#include "PerformanceModel.h"

#include "RV32_OOO_PerformanceModel.h"

namespace RV32_OOO {

inline void Arith_Ra_Rb(PerformanceModel* perfModel_) {
    RV32_OOO_PerformanceModel* perfModel = static_cast<RV32_OOO_PerformanceModel*>(perfModel_);
    uint64_t enterPoint = perfModel->entrancePoint;

    uint64_t n_PC_stage_ID = perfModel->graph.add_node(F_Type::PC_stage);
    perfModel->graph.add_edge(0, n_PC_stage_ID); // Needed to put first node into ready_nodes TODO: make less verbose
    perfModel->graph.set_inorder(perfModel->nodes_PC.back(), n_PC_stage_ID);
    perfModel->graph.add_edge(perfModel->noBranchPredModel.getPc(), n_PC_stage_ID);
    perfModel->noBranchPredModel.setPc_p(n_PC_stage_ID);

    uint64_t n_IF_stage_ID = perfModel->graph.add_node(F_Type::IF_stage);
    perfModel->graph.add_stage_connection(n_PC_stage_ID, n_IF_stage_ID);
    perfModel->graph.set_inorder(perfModel->nodes_IF.back(), n_IF_stage_ID);

    uint64_t n_IS_stage_ID = perfModel->graph.add_node(F_Type::IS_stage);
    perfModel->graph.add_stage_connection(n_IF_stage_ID, n_IS_stage_ID);
    perfModel->graph.set_inorder(perfModel->nodes_IS.back(), n_IS_stage_ID);
    perfModel->graph.add_edge(perfModel->clobberModel.getCb_out(), n_IS_stage_ID);

    uint64_t n_IB_stage_ID = perfModel->graph.add_parent_node(F_Type::IB_stage);
    perfModel->graph.add_stage_connection(n_IS_stage_ID, n_IB_stage_ID);
    perfModel->graph.set_inorder(perfModel->nodes_IB.back(), n_IB_stage_ID);

    uint64_t n_EX_stage_ID = perfModel->graph.add_node(F_Type::EX_alu, 1, n_IB_stage_ID);
    perfModel->graph.add_edge(n_IS_stage_ID, n_EX_stage_ID);
    perfModel->graph.add_edge(perfModel->regModel.getXa(), n_EX_stage_ID);
    perfModel->graph.add_edge(perfModel->regModel.getXb(), n_EX_stage_ID);
    perfModel->clobberModel.setCb_inRd(n_EX_stage_ID);
    perfModel->clobberModel.setCb_inR1(n_EX_stage_ID);
    perfModel->clobberModel.setCb_inR2(n_EX_stage_ID);
    perfModel->regModel.setXd(n_EX_stage_ID);

    uint64_t n_WB_stage_ID = perfModel->graph.add_node(F_Type::WB_stage);
    perfModel->graph.add_stage_connection(n_IB_stage_ID, n_WB_stage_ID);
    perfModel->graph.add_edge(n_EX_stage_ID,n_WB_stage_ID);

    // Add Nodes IDs to Stack
    perfModel->nodes_PC.push_back(n_PC_stage_ID);
    perfModel->nodes_IF.push_back(n_IF_stage_ID);
    perfModel->nodes_IS.push_back(n_IS_stage_ID);
    perfModel->nodes_IB.push_back(n_IB_stage_ID);
    perfModel->nodes_EX.push_back(n_EX_stage_ID);
    perfModel->nodes_WB.push_back(n_WB_stage_ID);
    //perfModel->noBranchPredModel_trace.push_back(perfModel->noBranchPredModel.getInfoStream());

    // Dump Entrance point for info print (tracing)
    perfModel->entrancePoint = enterPoint + 1;
}

inline void Arith_Ra(PerformanceModel* perfModel_) {
    RV32_OOO_PerformanceModel* perfModel = static_cast<RV32_OOO_PerformanceModel*>(perfModel_);
    uint64_t enterPoint = perfModel->entrancePoint;

    uint64_t n_PC_stage_ID = perfModel->graph.add_node(F_Type::PC_stage);
    perfModel->graph.add_edge(0, n_PC_stage_ID); // Needed to put first node into ready_nodes TODO: make less verbose
    perfModel->graph.set_inorder(perfModel->nodes_PC.back(), n_PC_stage_ID);
    perfModel->graph.add_edge(perfModel->noBranchPredModel.getPc(), n_PC_stage_ID);
    perfModel->noBranchPredModel.setPc_p(n_PC_stage_ID);

    uint64_t n_IF_stage_ID = perfModel->graph.add_node(F_Type::IF_stage);
    perfModel->graph.add_stage_connection(n_PC_stage_ID, n_IF_stage_ID);
    perfModel->graph.set_inorder(perfModel->nodes_IF.back(), n_IF_stage_ID);

    uint64_t n_IS_stage_ID = perfModel->graph.add_node(F_Type::IS_stage);
    perfModel->graph.add_stage_connection(n_IF_stage_ID, n_IS_stage_ID);
    perfModel->graph.set_inorder(perfModel->nodes_IS.back(), n_IS_stage_ID);
    perfModel->graph.add_edge(perfModel->clobberModel.getCb_out(), n_IS_stage_ID);

    uint64_t n_IB_stage_ID = perfModel->graph.add_parent_node(F_Type::IB_stage);
    perfModel->graph.add_stage_connection(n_IS_stage_ID, n_IB_stage_ID);
    perfModel->graph.set_inorder(perfModel->nodes_IB.back(), n_IB_stage_ID);

    uint64_t n_EX_stage_ID = perfModel->graph.add_node(F_Type::EX_alu, 1, n_IB_stage_ID);
    perfModel->graph.add_edge(n_IS_stage_ID, n_EX_stage_ID);
    perfModel->graph.add_edge(perfModel->regModel.getXa(), n_EX_stage_ID);
    perfModel->clobberModel.setCb_inRd(n_EX_stage_ID);
    perfModel->clobberModel.setCb_inR1(n_EX_stage_ID);
    perfModel->regModel.setXd(n_EX_stage_ID);

    uint64_t n_WB_stage_ID = perfModel->graph.add_node(F_Type::WB_stage);
    perfModel->graph.add_stage_connection(n_IB_stage_ID, n_WB_stage_ID);
    perfModel->graph.add_edge(n_EX_stage_ID,n_WB_stage_ID);

    // Add Nodes IDs to Stack
    perfModel->nodes_PC.push_back(n_PC_stage_ID);
    perfModel->nodes_IF.push_back(n_IF_stage_ID);
    perfModel->nodes_IS.push_back(n_IS_stage_ID);
    perfModel->nodes_IB.push_back(n_IB_stage_ID);
    perfModel->nodes_EX.push_back(n_EX_stage_ID);
    perfModel->nodes_WB.push_back(n_WB_stage_ID);
    //perfModel->noBranchPredModel_trace.push_back(perfModel->noBranchPredModel.getInfoStream());

    // Dump Entrance point for info print (tracing)
    perfModel->entrancePoint = enterPoint + 1;
}

inline void Arith_X(PerformanceModel* perfModel_) {
    RV32_OOO_PerformanceModel* perfModel = static_cast<RV32_OOO_PerformanceModel*>(perfModel_);
    uint64_t enterPoint = perfModel->entrancePoint;

    uint64_t n_PC_stage_ID = perfModel->graph.add_node(F_Type::PC_stage);
    perfModel->graph.add_edge(0, n_PC_stage_ID); // Needed to put first node into ready_nodes TODO: make less verbose
    perfModel->graph.set_inorder(perfModel->nodes_PC.back(), n_PC_stage_ID);
    perfModel->graph.add_edge(perfModel->noBranchPredModel.getPc(), n_PC_stage_ID);
    perfModel->noBranchPredModel.setPc_p(n_PC_stage_ID);

    uint64_t n_IF_stage_ID = perfModel->graph.add_node(F_Type::IF_stage);
    perfModel->graph.add_stage_connection(n_PC_stage_ID, n_IF_stage_ID);
    perfModel->graph.set_inorder(perfModel->nodes_IF.back(), n_IF_stage_ID);

    uint64_t n_IS_stage_ID = perfModel->graph.add_node(F_Type::IS_stage);
    perfModel->graph.add_stage_connection(n_IF_stage_ID, n_IS_stage_ID);
    perfModel->graph.set_inorder(perfModel->nodes_IS.back(), n_IS_stage_ID);
    perfModel->graph.add_edge(perfModel->clobberModel.getCb_out(), n_IS_stage_ID);

    uint64_t n_IB_stage_ID = perfModel->graph.add_parent_node(F_Type::IB_stage);
    perfModel->graph.add_stage_connection(n_IS_stage_ID, n_IB_stage_ID);
    perfModel->graph.set_inorder(perfModel->nodes_IB.back(), n_IB_stage_ID);

    uint64_t n_EX_stage_ID = perfModel->graph.add_node(F_Type::EX_alu, 1, n_IB_stage_ID);
    perfModel->graph.add_edge(n_IS_stage_ID, n_EX_stage_ID);
    perfModel->clobberModel.setCb_inRd(n_EX_stage_ID);
    perfModel->regModel.setXd(n_EX_stage_ID);

    uint64_t n_WB_stage_ID = perfModel->graph.add_node(F_Type::WB_stage);
    perfModel->graph.add_stage_connection(n_IB_stage_ID, n_WB_stage_ID);
    perfModel->graph.add_edge(n_EX_stage_ID,n_WB_stage_ID);

    // Add Nodes IDs to Stack
    perfModel->nodes_PC.push_back(n_PC_stage_ID);
    perfModel->nodes_IF.push_back(n_IF_stage_ID);
    perfModel->nodes_IS.push_back(n_IS_stage_ID);
    perfModel->nodes_IB.push_back(n_IB_stage_ID);
    perfModel->nodes_EX.push_back(n_EX_stage_ID);
    perfModel->nodes_WB.push_back(n_WB_stage_ID);
    //perfModel->noBranchPredModel_trace.push_back(perfModel->noBranchPredModel.getInfoStream());

    // Dump Entrance point for info print (tracing)
    perfModel->entrancePoint = enterPoint + 1;
}

inline void Mul_Ra_Rb(PerformanceModel* perfModel_) {
    RV32_OOO_PerformanceModel* perfModel = static_cast<RV32_OOO_PerformanceModel*>(perfModel_);
    uint64_t enterPoint = perfModel->entrancePoint;

    uint64_t n_PC_stage_ID = perfModel->graph.add_node(F_Type::PC_stage);
    perfModel->graph.add_edge(0, n_PC_stage_ID); // Needed to put first node into ready_nodes TODO: make less verbose
    perfModel->graph.set_inorder(perfModel->nodes_PC.back(), n_PC_stage_ID);
    perfModel->graph.add_edge(perfModel->noBranchPredModel.getPc(), n_PC_stage_ID);
    perfModel->noBranchPredModel.setPc_p(n_PC_stage_ID);

    uint64_t n_IF_stage_ID = perfModel->graph.add_node(F_Type::IF_stage);
    perfModel->graph.add_stage_connection(n_PC_stage_ID, n_IF_stage_ID);
    perfModel->graph.set_inorder(perfModel->nodes_IF.back(), n_IF_stage_ID);

    uint64_t n_IS_stage_ID = perfModel->graph.add_node(F_Type::IS_stage);
    perfModel->graph.add_stage_connection(n_IF_stage_ID, n_IS_stage_ID);
    perfModel->graph.set_inorder(perfModel->nodes_IS.back(), n_IS_stage_ID);
    perfModel->graph.add_edge(perfModel->clobberModel.getCb_out(), n_IS_stage_ID);

    uint64_t n_IB_stage_ID = perfModel->graph.add_parent_node(F_Type::IB_stage);
    perfModel->graph.add_stage_connection(n_IS_stage_ID, n_IB_stage_ID);
    perfModel->graph.set_inorder(perfModel->nodes_IB.back(), n_IB_stage_ID);

    uint64_t n_EX_stage_ID_1 = perfModel->graph.add_node(F_Type::EX_mul_i, 1, n_IB_stage_ID);
    perfModel->graph.add_edge(n_IS_stage_ID, n_EX_stage_ID_1);
    perfModel->graph.add_edge(perfModel->regModel.getXa(), n_EX_stage_ID_1);
    perfModel->graph.add_edge(perfModel->regModel.getXb(), n_EX_stage_ID_1);

    uint64_t n_EX_stage_ID_2 = perfModel->graph.add_node(F_Type::EX_mul_o, 1, n_IB_stage_ID);
    perfModel->graph.add_edge(n_EX_stage_ID_1, n_EX_stage_ID_2);
    perfModel->clobberModel.setCb_inRd(n_EX_stage_ID_2);
    perfModel->clobberModel.setCb_inR1(n_EX_stage_ID_2);
    perfModel->clobberModel.setCb_inR2(n_EX_stage_ID_2);  
    perfModel->regModel.setXd(n_EX_stage_ID_2);

    uint64_t n_WB_stage_ID = perfModel->graph.add_node(F_Type::WB_stage);
    perfModel->graph.add_stage_connection(n_IB_stage_ID, n_WB_stage_ID);

    // Add Nodes IDs to Stack
    perfModel->nodes_PC.push_back(n_PC_stage_ID);
    perfModel->nodes_IF.push_back(n_IF_stage_ID);
    perfModel->nodes_IS.push_back(n_IS_stage_ID);
    perfModel->nodes_IB.push_back(n_IB_stage_ID);
    perfModel->nodes_EX.push_back(n_EX_stage_ID_1);
    perfModel->nodes_WB.push_back(n_WB_stage_ID);
    //perfModel->noBranchPredModel_trace.push_back(perfModel->noBranchPredModel.getInfoStream());

    // Dump Entrance point for info print (tracing)
    perfModel->entrancePoint = enterPoint + 1;
}

inline void MulH_Ra_Rb(PerformanceModel* perfModel_) {
    RV32_OOO_PerformanceModel* perfModel = static_cast<RV32_OOO_PerformanceModel*>(perfModel_);
    uint64_t enterPoint = perfModel->entrancePoint;

    uint64_t n_PC_stage_ID = perfModel->graph.add_node(F_Type::PC_stage);
    perfModel->graph.add_edge(0, n_PC_stage_ID); // Needed to put first node into ready_nodes TODO: make less verbose
    perfModel->graph.set_inorder(perfModel->nodes_PC.back(), n_PC_stage_ID);
    perfModel->graph.add_edge(perfModel->noBranchPredModel.getPc(), n_PC_stage_ID);
    perfModel->noBranchPredModel.setPc_p(n_PC_stage_ID);

    uint64_t n_IF_stage_ID = perfModel->graph.add_node(F_Type::IF_stage);
    perfModel->graph.add_stage_connection(n_PC_stage_ID, n_IF_stage_ID);
    perfModel->graph.set_inorder(perfModel->nodes_IF.back(), n_IF_stage_ID);

    uint64_t n_IS_stage_ID = perfModel->graph.add_node(F_Type::IS_stage);
    perfModel->graph.add_stage_connection(n_IF_stage_ID, n_IS_stage_ID);
    perfModel->graph.set_inorder(perfModel->nodes_IS.back(), n_IS_stage_ID);
    perfModel->graph.add_edge(perfModel->clobberModel.getCb_out(), n_IS_stage_ID);

    uint64_t n_IB_stage_ID = perfModel->graph.add_parent_node(F_Type::IB_stage);
    perfModel->graph.add_stage_connection(n_IS_stage_ID, n_IB_stage_ID);
    perfModel->graph.set_inorder(perfModel->nodes_IB.back(), n_IB_stage_ID);

    uint64_t n_EX_stage_ID_1 = perfModel->graph.add_node(F_Type::EX_mul_i, 1, n_IB_stage_ID);
    perfModel->graph.add_edge(n_IS_stage_ID, n_EX_stage_ID_1);
    perfModel->graph.add_edge(perfModel->regModel.getXa(), n_EX_stage_ID_1);
    perfModel->graph.add_edge(perfModel->regModel.getXb(), n_EX_stage_ID_1);

    uint64_t n_EX_stage_ID_2 = perfModel->graph.add_node(F_Type::EX_mul_o, 1, n_IB_stage_ID);
    perfModel->graph.add_edge(n_EX_stage_ID_1, n_EX_stage_ID_2);
    perfModel->clobberModel.setCb_inRd(n_EX_stage_ID_2);
    perfModel->clobberModel.setCb_inR1(n_EX_stage_ID_2);
    perfModel->clobberModel.setCb_inR2(n_EX_stage_ID_2);  
    perfModel->regModel.setXd(n_EX_stage_ID_2);

    uint64_t n_WB_stage_ID = perfModel->graph.add_node(F_Type::WB_stage);
    perfModel->graph.add_stage_connection(n_IB_stage_ID, n_WB_stage_ID);
    perfModel->graph.add_edge(n_EX_stage_ID_2,n_WB_stage_ID);

    // Add Nodes IDs to Stack
    perfModel->nodes_PC.push_back(n_PC_stage_ID);
    perfModel->nodes_IF.push_back(n_IF_stage_ID);
    perfModel->nodes_IS.push_back(n_IS_stage_ID);
    perfModel->nodes_IB.push_back(n_IB_stage_ID);
    perfModel->nodes_EX.push_back(n_EX_stage_ID_1);
    perfModel->nodes_WB.push_back(n_WB_stage_ID);
    //perfModel->noBranchPredModel_trace.push_back(perfModel->noBranchPredModel.getInfoStream());

    // Dump Entrance point for info print (tracing)
    perfModel->entrancePoint = enterPoint + 1;
}

inline void Div_Ra_Rb(PerformanceModel* perfModel_) {
    RV32_OOO_PerformanceModel* perfModel = static_cast<RV32_OOO_PerformanceModel*>(perfModel_);
    uint64_t enterPoint = perfModel->entrancePoint;

    uint64_t n_PC_stage_ID = perfModel->graph.add_node(F_Type::PC_stage);
    perfModel->graph.add_edge(0, n_PC_stage_ID); // Needed to put first node into ready_nodes TODO: make less verbose
    perfModel->graph.set_inorder(perfModel->nodes_PC.back(), n_PC_stage_ID);
    perfModel->graph.add_edge(perfModel->noBranchPredModel.getPc(), n_PC_stage_ID);
    perfModel->noBranchPredModel.setPc_p(n_PC_stage_ID);

    uint64_t n_IF_stage_ID = perfModel->graph.add_node(F_Type::IF_stage);
    perfModel->graph.add_stage_connection(n_PC_stage_ID, n_IF_stage_ID);
    perfModel->graph.set_inorder(perfModel->nodes_IF.back(), n_IF_stage_ID);

    uint64_t n_IS_stage_ID = perfModel->graph.add_node(F_Type::IS_stage);
    perfModel->graph.add_stage_connection(n_IF_stage_ID, n_IS_stage_ID);
    perfModel->graph.set_inorder(perfModel->nodes_IS.back(), n_IS_stage_ID);
    perfModel->graph.add_edge(perfModel->clobberModel.getCb_out(), n_IS_stage_ID);

    uint64_t n_IB_stage_ID = perfModel->graph.add_parent_node(F_Type::IB_stage);
    perfModel->graph.add_stage_connection(n_IS_stage_ID, n_IB_stage_ID);
    perfModel->graph.set_inorder(perfModel->nodes_IB.back(), n_IB_stage_ID);

    uint64_t n_EX_stage_ID = perfModel->graph.add_node(F_Type::EX_div, 4, n_IB_stage_ID);
    perfModel->graph.add_edge(n_IS_stage_ID, n_EX_stage_ID);
    perfModel->graph.add_edge(perfModel->regModel.getXa(), n_EX_stage_ID);
    perfModel->graph.add_edge(perfModel->regModel.getXb(), n_EX_stage_ID);
    perfModel->clobberModel.setCb_inRd(n_EX_stage_ID);
    perfModel->clobberModel.setCb_inR1(n_EX_stage_ID);
    perfModel->clobberModel.setCb_inR2(n_EX_stage_ID);
    perfModel->regModel.setXd(n_EX_stage_ID);

    uint64_t n_WB_stage_ID = perfModel->graph.add_node(F_Type::WB_stage);
    perfModel->graph.add_stage_connection(n_IB_stage_ID, n_WB_stage_ID);
    perfModel->graph.add_edge(n_EX_stage_ID,n_WB_stage_ID);

    // Add Nodes IDs to Stack
    perfModel->nodes_PC.push_back(n_PC_stage_ID);
    perfModel->nodes_IF.push_back(n_IF_stage_ID);
    perfModel->nodes_IS.push_back(n_IS_stage_ID);
    perfModel->nodes_IB.push_back(n_IB_stage_ID);
    perfModel->nodes_EX.push_back(n_EX_stage_ID);
    perfModel->nodes_WB.push_back(n_WB_stage_ID);
    //perfModel->noBranchPredModel_trace.push_back(perfModel->noBranchPredModel.getInfoStream());

    // Dump Entrance point for info print (tracing)
    perfModel->entrancePoint = enterPoint + 1;
}

inline void DivU_Ra_Rb(PerformanceModel* perfModel_) {
    RV32_OOO_PerformanceModel* perfModel = static_cast<RV32_OOO_PerformanceModel*>(perfModel_);
    uint64_t enterPoint = perfModel->entrancePoint;

    uint64_t n_PC_stage_ID = perfModel->graph.add_node(F_Type::PC_stage);
    perfModel->graph.add_edge(0, n_PC_stage_ID); // Needed to put first node into ready_nodes TODO: make less verbose
    perfModel->graph.set_inorder(perfModel->nodes_PC.back(), n_PC_stage_ID);
    perfModel->graph.add_edge(perfModel->noBranchPredModel.getPc(), n_PC_stage_ID);
    perfModel->noBranchPredModel.setPc_p(n_PC_stage_ID);

    uint64_t n_IF_stage_ID = perfModel->graph.add_node(F_Type::IF_stage);
    perfModel->graph.add_stage_connection(n_PC_stage_ID, n_IF_stage_ID);
    perfModel->graph.set_inorder(perfModel->nodes_IF.back(), n_IF_stage_ID);

    uint64_t n_IS_stage_ID = perfModel->graph.add_node(F_Type::IS_stage);
    perfModel->graph.add_stage_connection(n_IF_stage_ID, n_IS_stage_ID);
    perfModel->graph.set_inorder(perfModel->nodes_IS.back(), n_IS_stage_ID);
    perfModel->graph.add_edge(perfModel->clobberModel.getCb_out(), n_IS_stage_ID);

    uint64_t n_IB_stage_ID = perfModel->graph.add_parent_node(F_Type::IB_stage);
    perfModel->graph.add_stage_connection(n_IS_stage_ID, n_IB_stage_ID);
    perfModel->graph.set_inorder(perfModel->nodes_IB.back(), n_IB_stage_ID);

    uint64_t n_EX_stage_ID = perfModel->graph.add_node(F_Type::EX_div, 4, n_IB_stage_ID);
    perfModel->graph.add_edge(n_IS_stage_ID, n_EX_stage_ID);
    perfModel->graph.add_edge(perfModel->regModel.getXa(), n_EX_stage_ID);
    perfModel->graph.add_edge(perfModel->regModel.getXb(), n_EX_stage_ID);
    perfModel->clobberModel.setCb_inRd(n_EX_stage_ID);
    perfModel->clobberModel.setCb_inR1(n_EX_stage_ID);
    perfModel->clobberModel.setCb_inR2(n_EX_stage_ID);
    perfModel->regModel.setXd(n_EX_stage_ID);

    uint64_t n_WB_stage_ID = perfModel->graph.add_node(F_Type::WB_stage);
    perfModel->graph.add_stage_connection(n_IB_stage_ID, n_WB_stage_ID);
    perfModel->graph.add_edge(n_EX_stage_ID,n_WB_stage_ID);

    // Add Nodes IDs to Stack
    perfModel->nodes_PC.push_back(n_PC_stage_ID);
    perfModel->nodes_IF.push_back(n_IF_stage_ID);
    perfModel->nodes_IS.push_back(n_IS_stage_ID);
    perfModel->nodes_IB.push_back(n_IB_stage_ID);
    perfModel->nodes_EX.push_back(n_EX_stage_ID);
    perfModel->nodes_WB.push_back(n_WB_stage_ID);
    //perfModel->noBranchPredModel_trace.push_back(perfModel->noBranchPredModel.getInfoStream());

    // Dump Entrance point for info print (tracing)
    perfModel->entrancePoint = enterPoint + 1;
}

inline void Csr_Ra(PerformanceModel* perfModel_) {
    RV32_OOO_PerformanceModel* perfModel = static_cast<RV32_OOO_PerformanceModel*>(perfModel_);
    uint64_t enterPoint = perfModel->entrancePoint;

    uint64_t n_PC_stage_ID = perfModel->graph.add_node(F_Type::PC_stage);
    perfModel->graph.add_edge(0, n_PC_stage_ID); // Needed to put first node into ready_nodes TODO: make less verbose
    perfModel->graph.set_inorder(perfModel->nodes_PC.back(), n_PC_stage_ID);
    perfModel->graph.add_edge(perfModel->noBranchPredModel.getPc(), n_PC_stage_ID);
    perfModel->noBranchPredModel.setPc_p(n_PC_stage_ID);

    uint64_t n_IF_stage_ID = perfModel->graph.add_node(F_Type::IF_stage);
    perfModel->graph.add_stage_connection(n_PC_stage_ID, n_IF_stage_ID);
    perfModel->graph.set_inorder(perfModel->nodes_IF.back(), n_IF_stage_ID);

    uint64_t n_IS_stage_ID = perfModel->graph.add_node(F_Type::IS_stage);
    perfModel->graph.add_stage_connection(n_IF_stage_ID, n_IS_stage_ID);
    perfModel->graph.set_inorder(perfModel->nodes_IS.back(), n_IS_stage_ID);
    perfModel->graph.add_edge(perfModel->clobberModel.getCb_out(), n_IS_stage_ID);

    uint64_t n_IB_stage_ID = perfModel->graph.add_parent_node(F_Type::IB_stage);
    perfModel->graph.add_stage_connection(n_IS_stage_ID, n_IB_stage_ID);
    perfModel->graph.set_inorder(perfModel->nodes_IB.back(), n_IB_stage_ID);

    uint64_t n_EX_stage_ID = perfModel->graph.add_node(F_Type::EX_alu, 1, n_IB_stage_ID);
    perfModel->graph.add_edge(n_IS_stage_ID, n_EX_stage_ID);
    perfModel->graph.add_edge(perfModel->regModel.getXa(), n_EX_stage_ID);
    perfModel->clobberModel.setCb_inRd(n_EX_stage_ID);
    perfModel->regModel.setXd(n_EX_stage_ID);

    uint64_t n_WB_stage_ID = perfModel->graph.add_node(F_Type::WB_stage);
    perfModel->graph.add_stage_connection(n_IB_stage_ID, n_WB_stage_ID);
    perfModel->graph.add_edge(n_EX_stage_ID,n_WB_stage_ID);

    // Add Nodes IDs to Stack
    perfModel->nodes_PC.push_back(n_PC_stage_ID);
    perfModel->nodes_IF.push_back(n_IF_stage_ID);
    perfModel->nodes_IS.push_back(n_IS_stage_ID);
    perfModel->nodes_IB.push_back(n_IB_stage_ID);
    perfModel->nodes_EX.push_back(n_EX_stage_ID);
    perfModel->nodes_WB.push_back(n_WB_stage_ID);
    //perfModel->noBranchPredModel_trace.push_back(perfModel->noBranchPredModel.getInfoStream());

    // Dump Entrance point for info print (tracing)
    perfModel->entrancePoint = enterPoint + 1;
}

inline void Csr_X(PerformanceModel* perfModel_) {
    RV32_OOO_PerformanceModel* perfModel = static_cast<RV32_OOO_PerformanceModel*>(perfModel_);
    uint64_t enterPoint = perfModel->entrancePoint;

    uint64_t n_PC_stage_ID = perfModel->graph.add_node(F_Type::PC_stage);
    perfModel->graph.add_edge(0, n_PC_stage_ID); // Needed to put first node into ready_nodes TODO: make less verbose
    perfModel->graph.set_inorder(perfModel->nodes_PC.back(), n_PC_stage_ID);
    perfModel->graph.add_edge(perfModel->noBranchPredModel.getPc(), n_PC_stage_ID);
    perfModel->noBranchPredModel.setPc_p(n_PC_stage_ID);

    uint64_t n_IF_stage_ID = perfModel->graph.add_node(F_Type::IF_stage);
    perfModel->graph.add_stage_connection(n_PC_stage_ID, n_IF_stage_ID);
    perfModel->graph.set_inorder(perfModel->nodes_IF.back(), n_IF_stage_ID);

    uint64_t n_IS_stage_ID = perfModel->graph.add_node(F_Type::IS_stage);
    perfModel->graph.add_stage_connection(n_IF_stage_ID, n_IS_stage_ID);
    perfModel->graph.set_inorder(perfModel->nodes_IS.back(), n_IS_stage_ID);
    perfModel->graph.add_edge(perfModel->clobberModel.getCb_out(), n_IS_stage_ID);

    uint64_t n_IB_stage_ID = perfModel->graph.add_parent_node(F_Type::IB_stage);
    perfModel->graph.add_stage_connection(n_IS_stage_ID, n_IB_stage_ID);
    perfModel->graph.set_inorder(perfModel->nodes_IB.back(), n_IB_stage_ID);

    uint64_t n_EX_stage_ID = perfModel->graph.add_node(F_Type::EX_alu, 1, n_IB_stage_ID);
    perfModel->graph.add_edge(n_IS_stage_ID, n_EX_stage_ID);
    perfModel->clobberModel.setCb_inRd(n_EX_stage_ID);
    perfModel->regModel.setXd(n_EX_stage_ID);

    uint64_t n_WB_stage_ID = perfModel->graph.add_node(F_Type::WB_stage);
    perfModel->graph.add_stage_connection(n_IB_stage_ID, n_WB_stage_ID);
    perfModel->graph.add_edge(n_EX_stage_ID,n_WB_stage_ID);

    // Add Nodes IDs to Stack
    perfModel->nodes_PC.push_back(n_PC_stage_ID);
    perfModel->nodes_IF.push_back(n_IF_stage_ID);
    perfModel->nodes_IS.push_back(n_IS_stage_ID);
    perfModel->nodes_IB.push_back(n_IB_stage_ID);
    perfModel->nodes_EX.push_back(n_EX_stage_ID);
    perfModel->nodes_WB.push_back(n_WB_stage_ID);
    //perfModel->noBranchPredModel_trace.push_back(perfModel->noBranchPredModel.getInfoStream());

    // Dump Entrance point for info print (tracing)
    perfModel->entrancePoint = enterPoint + 1;
}

inline void Store(PerformanceModel* perfModel_) {
    RV32_OOO_PerformanceModel* perfModel = static_cast<RV32_OOO_PerformanceModel*>(perfModel_);
    uint64_t enterPoint = perfModel->entrancePoint;

    uint64_t n_PC_stage_ID = perfModel->graph.add_node(F_Type::PC_stage);
    perfModel->graph.add_edge(0, n_PC_stage_ID); // Needed to put first node into ready_nodes TODO: make less verbose
    perfModel->graph.set_inorder(perfModel->nodes_PC.back(), n_PC_stage_ID);
    perfModel->graph.add_edge(perfModel->noBranchPredModel.getPc(), n_PC_stage_ID);
    perfModel->noBranchPredModel.setPc_p(n_PC_stage_ID);

    uint64_t n_IF_stage_ID = perfModel->graph.add_node(F_Type::IF_stage);
    perfModel->graph.add_stage_connection(n_PC_stage_ID, n_IF_stage_ID);
    perfModel->graph.set_inorder(perfModel->nodes_IF.back(), n_IF_stage_ID);

    uint64_t n_IS_stage_ID = perfModel->graph.add_node(F_Type::IS_stage);
    perfModel->graph.add_stage_connection(n_IF_stage_ID, n_IS_stage_ID);
    perfModel->graph.set_inorder(perfModel->nodes_IS.back(), n_IS_stage_ID);

    uint64_t n_IB_stage_ID = perfModel->graph.add_parent_node(F_Type::IB_stage);
    perfModel->graph.add_stage_connection(n_IS_stage_ID, n_IB_stage_ID);
    perfModel->graph.set_inorder(perfModel->nodes_IB.back(), n_IB_stage_ID);

    uint64_t n_EX_stage_ID = perfModel->graph.add_node(F_Type::EX_lsu, 1, n_IB_stage_ID);
    perfModel->graph.add_edge(n_IS_stage_ID, n_EX_stage_ID);
    perfModel->graph.add_edge(perfModel->regModel.getXa(), n_EX_stage_ID);
    perfModel->graph.add_edge(perfModel->regModel.getXb(), n_EX_stage_ID);
    perfModel->clobberModel.setCb_inR1(n_EX_stage_ID);
    perfModel->clobberModel.setCb_inR2(n_EX_stage_ID);

    uint64_t n_WB_stage_ID = perfModel->graph.add_node(F_Type::WB_stage);
    perfModel->graph.add_stage_connection(n_IB_stage_ID, n_WB_stage_ID);
    perfModel->graph.add_edge(n_EX_stage_ID,n_WB_stage_ID);

    // Add Nodes IDs to Stack
    perfModel->nodes_PC.push_back(n_PC_stage_ID);
    perfModel->nodes_IF.push_back(n_IF_stage_ID);
    perfModel->nodes_IS.push_back(n_IS_stage_ID);
    perfModel->nodes_IB.push_back(n_IB_stage_ID);
    perfModel->nodes_EX.push_back(n_EX_stage_ID);
    perfModel->nodes_WB.push_back(n_WB_stage_ID);
    //perfModel->noBranchPredModel_trace.push_back(perfModel->noBranchPredModel.getInfoStream());

    // Dump Entrance point for info print (tracing)
    perfModel->entrancePoint = enterPoint + 1;
}

inline void Load(PerformanceModel* perfModel_) {
    RV32_OOO_PerformanceModel* perfModel = static_cast<RV32_OOO_PerformanceModel*>(perfModel_);
    uint64_t enterPoint = perfModel->entrancePoint;

    uint64_t n_PC_stage_ID = perfModel->graph.add_node(F_Type::PC_stage);
    perfModel->graph.add_edge(0, n_PC_stage_ID); // Needed to put first node into ready_nodes TODO: make less verbose
    perfModel->graph.set_inorder(perfModel->nodes_PC.back(), n_PC_stage_ID);
    perfModel->graph.add_edge(perfModel->noBranchPredModel.getPc(), n_PC_stage_ID);
    perfModel->noBranchPredModel.setPc_p(n_PC_stage_ID);

    uint64_t n_IF_stage_ID = perfModel->graph.add_node(F_Type::IF_stage);
    perfModel->graph.add_stage_connection(n_PC_stage_ID, n_IF_stage_ID);
    perfModel->graph.set_inorder(perfModel->nodes_IF.back(), n_IF_stage_ID);

    uint64_t n_IS_stage_ID = perfModel->graph.add_node(F_Type::IS_stage);
    perfModel->graph.add_stage_connection(n_IF_stage_ID, n_IS_stage_ID);
    perfModel->graph.set_inorder(perfModel->nodes_IS.back(), n_IS_stage_ID);
    perfModel->graph.add_edge(perfModel->clobberModel.getCb_out(), n_IS_stage_ID);

    uint64_t n_IB_stage_ID = perfModel->graph.add_parent_node(F_Type::IB_stage);
    perfModel->graph.add_stage_connection(n_IS_stage_ID, n_IB_stage_ID);
    perfModel->graph.set_inorder(perfModel->nodes_IB.back(), n_IB_stage_ID);

    uint64_t n_LSU1_stage_ID = perfModel->graph.add_node(F_Type::EX_lsu, 1, n_IB_stage_ID);
    perfModel->graph.add_edge(n_IS_stage_ID, n_LSU1_stage_ID);
    perfModel->graph.add_edge(perfModel->regModel.getXa(), n_LSU1_stage_ID);

    uint64_t n_LSU2_stage_ID = perfModel->graph.add_node(F_Type::EX_lsu2, 1, n_IB_stage_ID);
    perfModel->graph.add_edge(n_LSU1_stage_ID, n_LSU2_stage_ID);
    perfModel->clobberModel.setCb_inRd(n_LSU2_stage_ID);
    perfModel->regModel.setXd(n_LSU2_stage_ID);

    // uint64_t n_LSU3_stage_ID = perfModel->graph.add_node(F_Type::EX_lsu3, 1, n_IB_stage_ID);
    // perfModel->graph.add_edge(n_LSU2_stage_ID, n_LSU3_stage_ID);
    // perfModel->clobberModel.setCb_inRd(n_LSU3_stage_ID);
    // perfModel->regModel.setXd(n_LSU3_stage_ID);

    uint64_t n_WB_stage_ID = perfModel->graph.add_node(F_Type::WB_stage);
    perfModel->graph.add_stage_connection(n_IB_stage_ID, n_WB_stage_ID);
    perfModel->graph.add_edge(n_LSU2_stage_ID,n_WB_stage_ID);
    //perfModel->graph.add_edge(n_LSU3_stage_ID,n_WB_stage_ID);

    // Add Nodes IDs to Stack
    perfModel->nodes_PC.push_back(n_PC_stage_ID);
    perfModel->nodes_IF.push_back(n_IF_stage_ID);
    perfModel->nodes_IS.push_back(n_IS_stage_ID);
    perfModel->nodes_IB.push_back(n_IB_stage_ID);
    perfModel->nodes_EX.push_back(n_LSU1_stage_ID);
    perfModel->nodes_WB.push_back(n_WB_stage_ID);
    //perfModel->noBranchPredModel_trace.push_back(perfModel->noBranchPredModel.getInfoStream());

    // Dump Entrance point for info print (tracing)
    perfModel->entrancePoint = enterPoint + 1;
}

inline void Branch_Ra_Rb(PerformanceModel* perfModel_) {
    RV32_OOO_PerformanceModel* perfModel = static_cast<RV32_OOO_PerformanceModel*>(perfModel_);
    uint64_t enterPoint = perfModel->entrancePoint;

    uint64_t n_PC_stage_ID = perfModel->graph.add_node(F_Type::PC_stage);
    perfModel->graph.add_edge(0, n_PC_stage_ID); // Needed to put first node into ready_nodes TODO: make less verbose
    perfModel->graph.set_inorder(perfModel->nodes_PC.back(), n_PC_stage_ID);
    perfModel->graph.add_edge(perfModel->noBranchPredModel.getPc(), n_PC_stage_ID);
    perfModel->noBranchPredModel.setPc_p(n_PC_stage_ID);

    uint64_t n_IF_stage_ID = perfModel->graph.add_node(F_Type::IF_stage);
    perfModel->graph.add_stage_connection(n_PC_stage_ID, n_IF_stage_ID);
    perfModel->graph.set_inorder(perfModel->nodes_IF.back(), n_IF_stage_ID);

    uint64_t n_IS_stage_ID = perfModel->graph.add_node(F_Type::IS_stage);
    perfModel->graph.add_stage_connection(n_IF_stage_ID, n_IS_stage_ID);
    perfModel->graph.set_inorder(perfModel->nodes_IS.back(), n_IS_stage_ID);

    uint64_t n_IB_stage_ID = perfModel->graph.add_parent_node(F_Type::IB_stage);
    perfModel->graph.add_stage_connection(n_IS_stage_ID, n_IB_stage_ID);
    perfModel->graph.set_inorder(perfModel->nodes_IB.back(), n_IB_stage_ID);

    uint64_t n_EX_stage_ID = perfModel->graph.add_node(F_Type::EX_add, 1, n_IB_stage_ID);
    perfModel->graph.add_edge(n_IS_stage_ID, n_EX_stage_ID);
    perfModel->graph.add_edge(perfModel->regModel.getXa(), n_EX_stage_ID);
    perfModel->graph.add_edge(perfModel->regModel.getXb(), n_EX_stage_ID);
    perfModel->noBranchPredModel.setPc_np(n_EX_stage_ID);
    perfModel->clobberModel.setCb_inR1(n_EX_stage_ID);
    perfModel->clobberModel.setCb_inR2(n_EX_stage_ID);

    uint64_t n_WB_stage_ID = perfModel->graph.add_node(F_Type::WB_stage);
    perfModel->graph.add_stage_connection(n_IB_stage_ID, n_WB_stage_ID);
    perfModel->graph.add_edge(n_EX_stage_ID,n_WB_stage_ID);

    // Add Nodes IDs to Stack
    perfModel->nodes_PC.push_back(n_PC_stage_ID);
    perfModel->nodes_IF.push_back(n_IF_stage_ID);
    perfModel->nodes_IS.push_back(n_IS_stage_ID);
    perfModel->nodes_IB.push_back(n_IB_stage_ID);
    perfModel->nodes_EX.push_back(n_EX_stage_ID);
    perfModel->nodes_WB.push_back(n_WB_stage_ID);
    //perfModel->noBranchPredModel_trace.push_back(perfModel->noBranchPredModel.getInfoStream());

    // Dump Entrance point for info print (tracing)
    perfModel->entrancePoint = enterPoint + 1;
}

inline void Default_Inst(PerformanceModel* perfModel_) {
    RV32_OOO_PerformanceModel* perfModel = static_cast<RV32_OOO_PerformanceModel*>(perfModel_);
    uint64_t enterPoint = perfModel->entrancePoint;

    uint64_t n_PC_stage_ID = perfModel->graph.add_node(F_Type::PC_stage);
    perfModel->graph.add_edge(0, n_PC_stage_ID); // Needed to put first node into ready_nodes TODO: make less verbose
    perfModel->graph.set_inorder(perfModel->nodes_PC.back(), n_PC_stage_ID);
    perfModel->graph.add_edge(perfModel->noBranchPredModel.getPc(), n_PC_stage_ID);
    perfModel->noBranchPredModel.setPc_p(n_PC_stage_ID);

    uint64_t n_IF_stage_ID = perfModel->graph.add_node(F_Type::IF_stage);
    perfModel->graph.add_stage_connection(n_PC_stage_ID, n_IF_stage_ID);
    perfModel->graph.set_inorder(perfModel->nodes_IF.back(), n_IF_stage_ID);

    // Add Nodes IDs to Stack
    perfModel->nodes_PC.push_back(n_PC_stage_ID);
    perfModel->nodes_IF.push_back(n_IF_stage_ID);
    perfModel->nodes_IS.push_back(back_or_zero(perfModel->nodes_IS));
    perfModel->nodes_IB.push_back(back_or_zero(perfModel->nodes_IB));
    perfModel->nodes_EX.push_back(back_or_zero(perfModel->nodes_EX));
    perfModel->nodes_WB.push_back(back_or_zero(perfModel->nodes_WB));
    //perfModel->noBranchPredModel_trace.push_back(perfModel->noBranchPredModel.getInfoStream());

    // Dump Entrance point for info print (tracing)
    perfModel->entrancePoint = enterPoint + 1;
}

inline void JAL(PerformanceModel* perfModel_) {
    RV32_OOO_PerformanceModel* perfModel = static_cast<RV32_OOO_PerformanceModel*>(perfModel_);
    uint64_t enterPoint = perfModel->entrancePoint;

    uint64_t n_PC_stage_ID = perfModel->graph.add_node(F_Type::PC_stage);
    perfModel->graph.add_edge(0, n_PC_stage_ID); // Needed to put first node into ready_nodes TODO: make less verbose
    perfModel->graph.set_inorder(perfModel->nodes_PC.back(), n_PC_stage_ID);
    perfModel->graph.add_edge(perfModel->noBranchPredModel.getPc(), n_PC_stage_ID);
    perfModel->noBranchPredModel.setPc_p(n_PC_stage_ID);

    uint64_t n_IF_stage_ID = perfModel->graph.add_node(F_Type::IF_stage);
    perfModel->graph.add_stage_connection(n_PC_stage_ID, n_IF_stage_ID);
    perfModel->graph.set_inorder(perfModel->nodes_IF.back(), n_IF_stage_ID);

    uint64_t n_IS_stage_ID = perfModel->graph.add_node(F_Type::IS_stage);
    perfModel->graph.add_stage_connection(n_IF_stage_ID, n_IS_stage_ID);
    perfModel->graph.set_inorder(perfModel->nodes_IS.back(), n_IS_stage_ID);
    perfModel->graph.add_edge(perfModel->clobberModel.getCb_out(), n_IS_stage_ID);
    perfModel->noBranchPredModel.setPc_np(n_IS_stage_ID);

    uint64_t n_IB_stage_ID = perfModel->graph.add_parent_node(F_Type::IB_stage);
    perfModel->graph.add_stage_connection(n_IS_stage_ID, n_IB_stage_ID);
    perfModel->graph.set_inorder(perfModel->nodes_IB.back(), n_IB_stage_ID);

    uint64_t n_EX_stage_ID = perfModel->graph.add_node(F_Type::EX_add, 1, n_IB_stage_ID);
    perfModel->graph.add_edge(n_IS_stage_ID, n_EX_stage_ID);
    perfModel->regModel.setXd(n_EX_stage_ID);
    perfModel->clobberModel.setCb_inRd(n_EX_stage_ID);

    uint64_t n_WB_stage_ID = perfModel->graph.add_node(F_Type::WB_stage);
    perfModel->graph.add_stage_connection(n_IB_stage_ID, n_WB_stage_ID);
    perfModel->graph.add_edge(n_EX_stage_ID,n_WB_stage_ID);

    // Add Nodes IDs to Stack
    perfModel->nodes_PC.push_back(n_PC_stage_ID);
    perfModel->nodes_IF.push_back(n_IF_stage_ID);
    perfModel->nodes_IS.push_back(n_IS_stage_ID);
    perfModel->nodes_IB.push_back(n_IB_stage_ID);
    perfModel->nodes_EX.push_back(n_EX_stage_ID);
    perfModel->nodes_WB.push_back(n_WB_stage_ID);
    //perfModel->noBranchPredModel_trace.push_back(perfModel->noBranchPredModel.getInfoStream());

    // Dump Entrance point for info print (tracing)
    perfModel->entrancePoint = enterPoint + 1;
}

inline void JALR(PerformanceModel* perfModel_) {
    RV32_OOO_PerformanceModel* perfModel = static_cast<RV32_OOO_PerformanceModel*>(perfModel_);
    uint64_t enterPoint = perfModel->entrancePoint;

    uint64_t n_PC_stage_ID = perfModel->graph.add_node(F_Type::PC_stage);
    perfModel->graph.add_edge(0, n_PC_stage_ID); // Needed to put first node into ready_nodes TODO: make less verbose
    perfModel->graph.set_inorder(perfModel->nodes_PC.back(), n_PC_stage_ID);
    perfModel->graph.add_edge(perfModel->noBranchPredModel.getPc(), n_PC_stage_ID);
    perfModel->noBranchPredModel.setPc_p(n_PC_stage_ID);

    uint64_t n_IF_stage_ID = perfModel->graph.add_node(F_Type::IF_stage);
    perfModel->graph.add_stage_connection(n_PC_stage_ID, n_IF_stage_ID);
    perfModel->graph.set_inorder(perfModel->nodes_IF.back(), n_IF_stage_ID);

    uint64_t n_IS_stage_ID = perfModel->graph.add_node(F_Type::IS_stage);
    perfModel->graph.add_stage_connection(n_IF_stage_ID, n_IS_stage_ID);
    perfModel->graph.set_inorder(perfModel->nodes_IS.back(), n_IS_stage_ID);
    perfModel->graph.add_edge(perfModel->clobberModel.getCb_out(), n_IS_stage_ID);
    perfModel->noBranchPredModel.setPc_np(n_IS_stage_ID);

    uint64_t n_IB_stage_ID = perfModel->graph.add_parent_node(F_Type::IB_stage);
    perfModel->graph.add_stage_connection(n_IS_stage_ID, n_IB_stage_ID);
    perfModel->graph.set_inorder(perfModel->nodes_IB.back(), n_IB_stage_ID);
    perfModel->graph.add_edge(perfModel->clobberModel.getCb_out(), n_IB_stage_ID);
    perfModel->noBranchPredModel.setPc_np(n_IB_stage_ID);

    uint64_t n_EX_stage_ID = perfModel->graph.add_node(F_Type::EX_add, 1, n_IB_stage_ID);
    perfModel->graph.add_edge(n_IS_stage_ID, n_EX_stage_ID);
    perfModel->regModel.setXd(n_EX_stage_ID);
    perfModel->clobberModel.setCb_inRd(n_EX_stage_ID);
    perfModel->clobberModel.setCb_inR1(n_EX_stage_ID);

    uint64_t n_WB_stage_ID = perfModel->graph.add_node(F_Type::WB_stage);
    perfModel->graph.add_stage_connection(n_IB_stage_ID, n_WB_stage_ID);
    perfModel->graph.add_edge(n_EX_stage_ID,n_WB_stage_ID);

    // Add Nodes IDs to Stack
    perfModel->nodes_PC.push_back(n_PC_stage_ID);
    perfModel->nodes_IF.push_back(n_IF_stage_ID);
    perfModel->nodes_IS.push_back(n_IS_stage_ID);
    perfModel->nodes_IB.push_back(n_IB_stage_ID);
    perfModel->nodes_EX.push_back(n_EX_stage_ID);
    perfModel->nodes_WB.push_back(n_WB_stage_ID);
    //perfModel->noBranchPredModel_trace.push_back(perfModel->noBranchPredModel.getInfoStream());

    // Dump Entrance point for info print (tracing)
    perfModel->entrancePoint = enterPoint + 1;
}

}  // namespace RV32_OOO