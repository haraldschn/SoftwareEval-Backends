#include <algorithm>
#include <cstdint>

#include "PerformanceModel.h"
#include "PerformanceScheduler.h"

#include "CV32E40P_PerformanceModel.h"

namespace CV32E40P {

inline void Arith_Ra_Rb(PerformanceModel* perfModel_) {
    CV32E40P_PerformanceModel* perfModel = static_cast<CV32E40P_PerformanceModel*>(perfModel_);
    uint64_t enterPoint = perfModel->entrancePoint;

    uint64_t n_IF_stage_ID = perfModel->graph.add_node(F_Type::IF_stage);
    perfModel->graph.add_edge(0, n_IF_stage_ID);
    perfModel->graph.set_inorder(perfModel->nodes_IF.back(), n_IF_stage_ID);
    perfModel->graph.add_edge(perfModel->staBranchPredModel.getPc(), n_IF_stage_ID);
    perfModel->staBranchPredModel.setPc_p(n_IF_stage_ID);
    
    uint64_t n_ID_stage_ID = perfModel->graph.add_node(F_Type::ID_stage);
    perfModel->graph.add_stage_connection(n_IF_stage_ID, n_ID_stage_ID);
    perfModel->graph.set_inorder(perfModel->nodes_ID.back(), n_ID_stage_ID);

    // ALU delay = 1
    uint64_t n_EX_stage_ID = perfModel->graph.add_node(F_Type::EX_stage);
    perfModel->graph.add_stage_connection(n_ID_stage_ID, n_EX_stage_ID);
    perfModel->graph.set_inorder(perfModel->nodes_EX.back(), n_EX_stage_ID);
    perfModel->graph.add_edge(perfModel->regModel.getXa(), n_EX_stage_ID);
    perfModel->graph.add_edge(perfModel->regModel.getXb(), n_EX_stage_ID);
    perfModel->regModel.setXd(n_EX_stage_ID);
    
    uint64_t n_WB_stage_ID = perfModel->nodes_WB.back();

    // Add Nodes IDs to Stack
    perfModel->nodes_IF.push_back(n_IF_stage_ID);
    perfModel->nodes_ID.push_back(n_ID_stage_ID);
    perfModel->nodes_EX.push_back(n_EX_stage_ID);
    perfModel->nodes_WB.push_back(n_WB_stage_ID);
    perfModel->staBranchPredModel_trace.push_back(perfModel->staBranchPredModel.getInfoStream());

    // Dump Entrance point for info print (tracing)
    perfModel->entrancePoint = enterPoint + 1;
}

inline void Arith_Ra(PerformanceModel* perfModel_) {
    CV32E40P_PerformanceModel* perfModel = static_cast<CV32E40P_PerformanceModel*>(perfModel_);
    uint64_t enterPoint = perfModel->entrancePoint;

    uint64_t n_IF_stage_ID = perfModel->graph.add_node(F_Type::IF_stage);
    perfModel->graph.add_edge(0, n_IF_stage_ID);
    perfModel->graph.set_inorder(perfModel->nodes_IF.back(), n_IF_stage_ID);
    perfModel->graph.add_edge(perfModel->staBranchPredModel.getPc(), n_IF_stage_ID);
    perfModel->staBranchPredModel.setPc_p(n_IF_stage_ID);
    
    uint64_t n_ID_stage_ID = perfModel->graph.add_node(F_Type::ID_stage);
    perfModel->graph.add_stage_connection(n_IF_stage_ID, n_ID_stage_ID);
    perfModel->graph.set_inorder(perfModel->nodes_ID.back(), n_ID_stage_ID);

    // ALU delay = 1
    uint64_t n_EX_stage_ID = perfModel->graph.add_node(F_Type::EX_stage);
    perfModel->graph.add_stage_connection(n_ID_stage_ID, n_EX_stage_ID);
    perfModel->graph.set_inorder(perfModel->nodes_EX.back(), n_EX_stage_ID);
    perfModel->graph.add_edge(perfModel->regModel.getXa(), n_EX_stage_ID);
    perfModel->regModel.setXd(n_EX_stage_ID);

    uint64_t n_WB_stage_ID = perfModel->nodes_WB.back();

    // Add Nodes IDs to Stack
    perfModel->nodes_IF.push_back(n_IF_stage_ID);
    perfModel->nodes_ID.push_back(n_ID_stage_ID);
    perfModel->nodes_EX.push_back(n_EX_stage_ID);
    perfModel->nodes_WB.push_back(n_WB_stage_ID);
    perfModel->staBranchPredModel_trace.push_back(perfModel->staBranchPredModel.getInfoStream());

    // Dump Entrance point for info print (tracing)
    perfModel->entrancePoint = enterPoint + 1;
}

inline void Arith_X(PerformanceModel* perfModel_) {
    CV32E40P_PerformanceModel* perfModel = static_cast<CV32E40P_PerformanceModel*>(perfModel_);
    uint64_t enterPoint = perfModel->entrancePoint;

    uint64_t n_IF_stage_ID = perfModel->graph.add_node(F_Type::IF_stage);
    perfModel->graph.add_edge(0, n_IF_stage_ID);
    perfModel->graph.set_inorder(perfModel->nodes_IF.back(), n_IF_stage_ID);
    perfModel->graph.add_edge(perfModel->staBranchPredModel.getPc(), n_IF_stage_ID);
    perfModel->staBranchPredModel.setPc_p(n_IF_stage_ID);
    
    uint64_t n_ID_stage_ID = perfModel->graph.add_node(F_Type::ID_stage);
    perfModel->graph.add_stage_connection(n_IF_stage_ID, n_ID_stage_ID);
    perfModel->graph.set_inorder(perfModel->nodes_ID.back(), n_ID_stage_ID);

    // ALU delay = 1
    uint64_t n_EX_stage_ID = perfModel->graph.add_node(F_Type::EX_stage);
    perfModel->graph.add_stage_connection(n_ID_stage_ID, n_EX_stage_ID);
    perfModel->graph.set_inorder(perfModel->nodes_EX.back(), n_EX_stage_ID);
    perfModel->regModel.setXd(n_EX_stage_ID);
    
    uint64_t n_WB_stage_ID = perfModel->nodes_WB.back();

    // Add Nodes IDs to Stack
    perfModel->nodes_IF.push_back(n_IF_stage_ID);
    perfModel->nodes_ID.push_back(n_ID_stage_ID);
    perfModel->nodes_EX.push_back(n_EX_stage_ID);
    perfModel->nodes_WB.push_back(n_WB_stage_ID);
    perfModel->staBranchPredModel_trace.push_back(perfModel->staBranchPredModel.getInfoStream());

    // Dump Entrance point for info print (tracing)
    perfModel->entrancePoint = enterPoint + 1;
}

inline void Mul_Ra_Rb(PerformanceModel* perfModel_) {
    CV32E40P_PerformanceModel* perfModel = static_cast<CV32E40P_PerformanceModel*>(perfModel_);
    uint64_t enterPoint = perfModel->entrancePoint;

    uint64_t n_IF_stage_ID = perfModel->graph.add_node(F_Type::IF_stage);
    perfModel->graph.add_edge(0, n_IF_stage_ID);
    perfModel->graph.set_inorder(perfModel->nodes_IF.back(), n_IF_stage_ID);
    perfModel->graph.add_edge(perfModel->staBranchPredModel.getPc(), n_IF_stage_ID);
    perfModel->staBranchPredModel.setPc_p(n_IF_stage_ID);
    
    uint64_t n_ID_stage_ID = perfModel->graph.add_node(F_Type::ID_stage);
    perfModel->graph.add_stage_connection(n_IF_stage_ID, n_ID_stage_ID);
    perfModel->graph.set_inorder(perfModel->nodes_ID.back(), n_ID_stage_ID);

    // MUL delay = 1
    uint64_t n_EX_stage_ID = perfModel->graph.add_node(F_Type::EX_stage);
    perfModel->graph.add_stage_connection(n_ID_stage_ID, n_EX_stage_ID);
    perfModel->graph.set_inorder(perfModel->nodes_EX.back(), n_EX_stage_ID);
    perfModel->graph.add_edge(perfModel->regModel.getXa(), n_EX_stage_ID);
    perfModel->graph.add_edge(perfModel->regModel.getXb(), n_EX_stage_ID);
    perfModel->regModel.setXd(n_EX_stage_ID);
    
    uint64_t n_WB_stage_ID = perfModel->nodes_WB.back();

    // Add Nodes IDs to Stack
    perfModel->nodes_IF.push_back(n_IF_stage_ID);
    perfModel->nodes_ID.push_back(n_ID_stage_ID);
    perfModel->nodes_EX.push_back(n_EX_stage_ID);
    perfModel->nodes_WB.push_back(n_WB_stage_ID);
    perfModel->staBranchPredModel_trace.push_back(perfModel->staBranchPredModel.getInfoStream());

    // Dump Entrance point for info print (tracing)
    perfModel->entrancePoint = enterPoint + 1;
}

inline void MulH_Ra_Rb(PerformanceModel* perfModel_) {
    CV32E40P_PerformanceModel* perfModel = static_cast<CV32E40P_PerformanceModel*>(perfModel_);
    uint64_t enterPoint = perfModel->entrancePoint;

    uint64_t n_IF_stage_ID = perfModel->graph.add_node(F_Type::IF_stage);
    perfModel->graph.add_edge(0, n_IF_stage_ID);
    perfModel->graph.set_inorder(perfModel->nodes_IF.back(), n_IF_stage_ID);
    perfModel->graph.add_edge(perfModel->staBranchPredModel.getPc(), n_IF_stage_ID);
    perfModel->staBranchPredModel.setPc_p(n_IF_stage_ID);
    
    uint64_t n_ID_stage_ID = perfModel->graph.add_node(F_Type::ID_stage);
    perfModel->graph.add_stage_connection(n_IF_stage_ID, n_ID_stage_ID);
    perfModel->graph.set_inorder(perfModel->nodes_ID.back(), n_ID_stage_ID);

    // MULH delay = 5
    uint64_t n_EX_stage_ID = perfModel->graph.add_node(F_Type::EX_stage, 5);
    perfModel->graph.add_stage_connection(n_ID_stage_ID, n_EX_stage_ID);
    perfModel->graph.set_inorder(perfModel->nodes_EX.back(), n_EX_stage_ID);
    perfModel->graph.add_edge(perfModel->regModel.getXa(), n_EX_stage_ID);
    perfModel->graph.add_edge(perfModel->regModel.getXb(), n_EX_stage_ID);
    perfModel->regModel.setXd(n_EX_stage_ID);
    
    uint64_t n_WB_stage_ID = perfModel->nodes_WB.back();

    // Add Nodes IDs to Stack
    perfModel->nodes_IF.push_back(n_IF_stage_ID);
    perfModel->nodes_ID.push_back(n_ID_stage_ID);
    perfModel->nodes_EX.push_back(n_EX_stage_ID);
    perfModel->nodes_WB.push_back(n_WB_stage_ID);
    perfModel->staBranchPredModel_trace.push_back(perfModel->staBranchPredModel.getInfoStream());

    // Dump Entrance point for info print (tracing)
    perfModel->entrancePoint = enterPoint + 1;
}

inline void Div_Ra_Rb(PerformanceModel* perfModel_) {
    CV32E40P_PerformanceModel* perfModel = static_cast<CV32E40P_PerformanceModel*>(perfModel_);
    uint64_t enterPoint = perfModel->entrancePoint;

    uint64_t n_IF_stage_ID = perfModel->graph.add_node(F_Type::IF_stage);
    perfModel->graph.add_edge(0, n_IF_stage_ID);
    perfModel->graph.set_inorder(perfModel->nodes_IF.back(), n_IF_stage_ID);
    perfModel->graph.add_edge(perfModel->staBranchPredModel.getPc(), n_IF_stage_ID);
    perfModel->staBranchPredModel.setPc_p(n_IF_stage_ID);
    
    uint64_t n_ID_stage_ID = perfModel->graph.add_node(F_Type::ID_stage);
    perfModel->graph.add_stage_connection(n_IF_stage_ID, n_ID_stage_ID);
    perfModel->graph.set_inorder(perfModel->nodes_ID.back(), n_ID_stage_ID);

    // DIV delay = Resource model Divider
    uint64_t n_EX_stage_ID = perfModel->graph.add_node(F_Type::EX_stage, perfModel->divider.getDelay());
    perfModel->graph.add_stage_connection(n_ID_stage_ID, n_EX_stage_ID);
    perfModel->graph.set_inorder(perfModel->nodes_EX.back(), n_EX_stage_ID);
    perfModel->graph.add_edge(perfModel->regModel.getXa(), n_EX_stage_ID);
    perfModel->graph.add_edge(perfModel->regModel.getXb(), n_EX_stage_ID);
    perfModel->regModel.setXd(n_EX_stage_ID);
    
    uint64_t n_WB_stage_ID = perfModel->nodes_WB.back();

    // Add Nodes IDs to Stack
    perfModel->nodes_IF.push_back(n_IF_stage_ID);
    perfModel->nodes_ID.push_back(n_ID_stage_ID);
    perfModel->nodes_EX.push_back(n_EX_stage_ID);
    perfModel->nodes_WB.push_back(n_WB_stage_ID);
    perfModel->staBranchPredModel_trace.push_back(perfModel->staBranchPredModel.getInfoStream());

    // Dump Entrance point for info print (tracing)
    perfModel->entrancePoint = enterPoint + 1;
}

inline void DivU_Ra_Rb(PerformanceModel* perfModel_) {
    CV32E40P_PerformanceModel* perfModel = static_cast<CV32E40P_PerformanceModel*>(perfModel_);
    uint64_t enterPoint = perfModel->entrancePoint;

    uint64_t n_IF_stage_ID = perfModel->graph.add_node(F_Type::IF_stage);
    perfModel->graph.add_edge(0, n_IF_stage_ID);
    perfModel->graph.set_inorder(perfModel->nodes_IF.back(), n_IF_stage_ID);
    perfModel->graph.add_edge(perfModel->staBranchPredModel.getPc(), n_IF_stage_ID);
    perfModel->staBranchPredModel.setPc_p(n_IF_stage_ID);
    
    uint64_t n_ID_stage_ID = perfModel->graph.add_node(F_Type::ID_stage);
    perfModel->graph.add_stage_connection(n_IF_stage_ID, n_ID_stage_ID);
    perfModel->graph.set_inorder(perfModel->nodes_ID.back(), n_ID_stage_ID);

    // DIVU delay = Resource model DividerU
    uint64_t n_EX_stage_ID = perfModel->graph.add_node(F_Type::EX_stage, perfModel->divider_u.getDelay());
    perfModel->graph.add_stage_connection(n_ID_stage_ID, n_EX_stage_ID);
    perfModel->graph.set_inorder(perfModel->nodes_EX.back(), n_EX_stage_ID);
    perfModel->graph.add_edge(perfModel->regModel.getXa(), n_EX_stage_ID);
    perfModel->graph.add_edge(perfModel->regModel.getXb(), n_EX_stage_ID);
    perfModel->regModel.setXd(n_EX_stage_ID);
    
    uint64_t n_WB_stage_ID = perfModel->nodes_WB.back();

    // Add Nodes IDs to Stack
    perfModel->nodes_IF.push_back(n_IF_stage_ID);
    perfModel->nodes_ID.push_back(n_ID_stage_ID);
    perfModel->nodes_EX.push_back(n_EX_stage_ID);
    perfModel->nodes_WB.push_back(n_WB_stage_ID);
    perfModel->staBranchPredModel_trace.push_back(perfModel->staBranchPredModel.getInfoStream());

    // Dump Entrance point for info print (tracing)
    perfModel->entrancePoint = enterPoint + 1;
}

inline void Csr_Ra(PerformanceModel* perfModel_) {
    CV32E40P_PerformanceModel* perfModel = static_cast<CV32E40P_PerformanceModel*>(perfModel_);
    uint64_t enterPoint = perfModel->entrancePoint;

    uint64_t n_IF_stage_ID = perfModel->graph.add_node(F_Type::IF_stage);
    perfModel->graph.add_edge(0, n_IF_stage_ID);
    perfModel->graph.set_inorder(perfModel->nodes_IF.back(), n_IF_stage_ID);
    perfModel->graph.add_edge(perfModel->staBranchPredModel.getPc(), n_IF_stage_ID);
    perfModel->staBranchPredModel.setPc_p(n_IF_stage_ID);
    
    uint64_t n_ID_stage_ID = perfModel->graph.add_node(F_Type::ID_stage);
    perfModel->graph.add_stage_connection(n_IF_stage_ID, n_ID_stage_ID);
    perfModel->graph.set_inorder(perfModel->nodes_ID.back(), n_ID_stage_ID);

    // ALU delay = 1
    uint64_t n_EX_stage_ID = perfModel->graph.add_node(F_Type::EX_stage);
    perfModel->graph.add_stage_connection(n_ID_stage_ID, n_EX_stage_ID);
    perfModel->graph.set_inorder(perfModel->nodes_EX.back(), n_EX_stage_ID);
    perfModel->graph.add_edge(perfModel->regModel.getXa(), n_EX_stage_ID);
    perfModel->regModel.setXd(n_EX_stage_ID);

    uint64_t n_WB_stage_ID = perfModel->nodes_WB.back();

    // Add Nodes IDs to Stack
    perfModel->nodes_IF.push_back(n_IF_stage_ID);
    perfModel->nodes_ID.push_back(n_ID_stage_ID);
    perfModel->nodes_EX.push_back(n_EX_stage_ID);
    perfModel->nodes_WB.push_back(n_WB_stage_ID);
    perfModel->staBranchPredModel_trace.push_back(perfModel->staBranchPredModel.getInfoStream());

    // Dump Entrance point for info print (tracing)
    perfModel->entrancePoint = enterPoint + 1;
}

inline void Csr_X(PerformanceModel* perfModel_) {
    CV32E40P_PerformanceModel* perfModel = static_cast<CV32E40P_PerformanceModel*>(perfModel_);
    uint64_t enterPoint = perfModel->entrancePoint;

    uint64_t n_IF_stage_ID = perfModel->graph.add_node(F_Type::IF_stage);
    perfModel->graph.add_edge(0, n_IF_stage_ID);
    perfModel->graph.set_inorder(perfModel->nodes_IF.back(), n_IF_stage_ID);
    perfModel->graph.add_edge(perfModel->staBranchPredModel.getPc(), n_IF_stage_ID);
    perfModel->staBranchPredModel.setPc_p(n_IF_stage_ID);
    
    uint64_t n_ID_stage_ID = perfModel->graph.add_node(F_Type::ID_stage);
    perfModel->graph.add_stage_connection(n_IF_stage_ID, n_ID_stage_ID);
    perfModel->graph.set_inorder(perfModel->nodes_ID.back(), n_ID_stage_ID);

    // ALU delay = 1
    uint64_t n_EX_stage_ID = perfModel->graph.add_node(F_Type::EX_stage);
    perfModel->graph.add_stage_connection(n_ID_stage_ID, n_EX_stage_ID);
    perfModel->graph.set_inorder(perfModel->nodes_EX.back(), n_EX_stage_ID);
    perfModel->regModel.setXd(n_EX_stage_ID);
    
    uint64_t n_WB_stage_ID = perfModel->nodes_WB.back();

    // Add Nodes IDs to Stack
    perfModel->nodes_IF.push_back(n_IF_stage_ID);
    perfModel->nodes_ID.push_back(n_ID_stage_ID);
    perfModel->nodes_EX.push_back(n_EX_stage_ID);
    perfModel->nodes_WB.push_back(n_WB_stage_ID);
    perfModel->staBranchPredModel_trace.push_back(perfModel->staBranchPredModel.getInfoStream());

    // Dump Entrance point for info print (tracing)
    perfModel->entrancePoint = enterPoint + 1;
}

inline void Store(PerformanceModel* perfModel_) {
    CV32E40P_PerformanceModel* perfModel = static_cast<CV32E40P_PerformanceModel*>(perfModel_);
    uint64_t enterPoint = perfModel->entrancePoint;

    uint64_t n_IF_stage_ID = perfModel->graph.add_node(F_Type::IF_stage);
    perfModel->graph.add_edge(0, n_IF_stage_ID);
    perfModel->graph.set_inorder(perfModel->nodes_IF.back(), n_IF_stage_ID);
    perfModel->graph.add_edge(perfModel->staBranchPredModel.getPc(), n_IF_stage_ID);
    perfModel->staBranchPredModel.setPc_p(n_IF_stage_ID);

    uint64_t n_ID_stage_ID = perfModel->graph.add_node(F_Type::ID_stage);
    perfModel->graph.add_stage_connection(n_IF_stage_ID, n_ID_stage_ID);
    perfModel->graph.set_inorder(perfModel->nodes_ID.back(), n_ID_stage_ID);

    uint64_t n_EX_stage_ID = perfModel->graph.add_node(F_Type::EX_stage);
    perfModel->graph.add_stage_connection(n_ID_stage_ID, n_EX_stage_ID);
    perfModel->graph.set_inorder(perfModel->nodes_EX.back(), n_EX_stage_ID);
    perfModel->graph.add_edge(perfModel->regModel.getXa(), n_EX_stage_ID);
    perfModel->graph.add_edge(perfModel->regModel.getXb(), n_EX_stage_ID);

    // DPort_W delay = 1
    uint64_t n_WB_stage_ID = perfModel->graph.add_node(F_Type::WB_stage);
    perfModel->graph.add_stage_connection(n_EX_stage_ID, n_WB_stage_ID);
    perfModel->graph.set_inorder(perfModel->nodes_WB.back(), n_WB_stage_ID);

    // Add Nodes IDs to Stack
    perfModel->nodes_IF.push_back(n_IF_stage_ID);
    perfModel->nodes_ID.push_back(n_ID_stage_ID);
    perfModel->nodes_EX.push_back(n_EX_stage_ID);
    perfModel->nodes_WB.push_back(n_WB_stage_ID);
    perfModel->staBranchPredModel_trace.push_back(perfModel->staBranchPredModel.getInfoStream());

    // Dump Entrance point for info print (tracing)
    perfModel->entrancePoint = enterPoint + 1;
}

inline void Load(PerformanceModel* perfModel_) {
    CV32E40P_PerformanceModel* perfModel = static_cast<CV32E40P_PerformanceModel*>(perfModel_);
    uint64_t enterPoint = perfModel->entrancePoint;

    uint64_t n_IF_stage_ID = perfModel->graph.add_node(F_Type::IF_stage);
    perfModel->graph.add_edge(0, n_IF_stage_ID);
    perfModel->graph.set_inorder(perfModel->nodes_IF.back(), n_IF_stage_ID);
    perfModel->graph.add_edge(perfModel->staBranchPredModel.getPc(), n_IF_stage_ID);
    perfModel->staBranchPredModel.setPc_p(n_IF_stage_ID);

    uint64_t n_ID_stage_ID = perfModel->graph.add_node(F_Type::ID_stage);
    perfModel->graph.add_stage_connection(n_IF_stage_ID, n_ID_stage_ID);
    perfModel->graph.set_inorder(perfModel->nodes_ID.back(), n_ID_stage_ID);

    uint64_t n_EX_stage_ID = perfModel->graph.add_node(F_Type::EX_stage);
    perfModel->graph.add_stage_connection(n_ID_stage_ID, n_EX_stage_ID);
    perfModel->graph.set_inorder(perfModel->nodes_EX.back(), n_EX_stage_ID);
    perfModel->graph.add_edge(perfModel->regModel.getXa(), n_EX_stage_ID);

    // DPort_W delay = 1
    uint64_t n_WB_stage_ID = perfModel->graph.add_node(F_Type::WB_stage);
    perfModel->graph.add_stage_connection(n_EX_stage_ID, n_WB_stage_ID);
    perfModel->graph.set_inorder(perfModel->nodes_WB.back(), n_WB_stage_ID);
    perfModel->regModel.setXd(n_WB_stage_ID);

    // Add Nodes IDs to Stack
    perfModel->nodes_IF.push_back(n_IF_stage_ID);
    perfModel->nodes_ID.push_back(n_ID_stage_ID);
    perfModel->nodes_EX.push_back(n_EX_stage_ID);
    perfModel->nodes_WB.push_back(n_WB_stage_ID);
    perfModel->staBranchPredModel_trace.push_back(perfModel->staBranchPredModel.getInfoStream());

    // Dump Entrance point for info print (tracing)
    perfModel->entrancePoint = enterPoint + 1;
}

inline void Branch_Ra_Rb(PerformanceModel* perfModel_) {
    CV32E40P_PerformanceModel* perfModel = static_cast<CV32E40P_PerformanceModel*>(perfModel_);
    uint64_t enterPoint = perfModel->entrancePoint;

    uint64_t n_IF_stage_ID = perfModel->graph.add_node(F_Type::IF_stage);
    perfModel->graph.add_edge(0, n_IF_stage_ID);
    perfModel->graph.set_inorder(perfModel->nodes_IF.back(), n_IF_stage_ID);
    perfModel->graph.add_edge(perfModel->staBranchPredModel.getPc(), n_IF_stage_ID);
    perfModel->staBranchPredModel.setPc_p(n_IF_stage_ID);

    uint64_t n_ID_stage_ID = perfModel->graph.add_node(F_Type::ID_stage);
    perfModel->graph.add_stage_connection(n_IF_stage_ID, n_ID_stage_ID);
    perfModel->graph.set_inorder(perfModel->nodes_ID.back(), n_ID_stage_ID);

    // ALU delay = 1
    uint64_t n_EX_stage_ID = perfModel->graph.add_node(F_Type::EX_stage);
    perfModel->graph.add_stage_connection(n_ID_stage_ID, n_EX_stage_ID);
    perfModel->graph.set_inorder(perfModel->nodes_EX.back(), n_EX_stage_ID);
    perfModel->graph.add_edge(perfModel->regModel.getXa(), n_EX_stage_ID);
    perfModel->graph.add_edge(perfModel->regModel.getXb(), n_EX_stage_ID);
    perfModel->staBranchPredModel.setPc_np(n_EX_stage_ID);
    
    uint64_t n_WB_stage_ID = perfModel->nodes_WB.back();

    // Add Nodes IDs to Stack
    perfModel->nodes_IF.push_back(n_IF_stage_ID);
    perfModel->nodes_ID.push_back(n_ID_stage_ID);
    perfModel->nodes_EX.push_back(n_EX_stage_ID);
    perfModel->nodes_WB.push_back(n_WB_stage_ID);
    perfModel->staBranchPredModel_trace.push_back(perfModel->staBranchPredModel.getInfoStream());

    // Dump Entrance point for info print (tracing)
    perfModel->entrancePoint = enterPoint + 1;
}

inline void Default_Inst(PerformanceModel* perfModel_) {
    CV32E40P_PerformanceModel* perfModel = static_cast<CV32E40P_PerformanceModel*>(perfModel_);
    uint64_t enterPoint = perfModel->entrancePoint;

    uint64_t n_IF_stage_ID = perfModel->graph.add_node(F_Type::IF_stage);
    perfModel->graph.add_edge(0, n_IF_stage_ID);
    perfModel->graph.set_inorder(perfModel->nodes_IF.back(), n_IF_stage_ID);
    perfModel->graph.add_edge(perfModel->staBranchPredModel.getPc(), n_IF_stage_ID);
    perfModel->staBranchPredModel.setPc_p(n_IF_stage_ID);

    uint64_t n_ID_stage_ID = perfModel->nodes_ID.back();
    uint64_t n_EX_stage_ID = perfModel->nodes_EX.back();
    uint64_t n_WB_stage_ID = perfModel->nodes_WB.back();

    // Add Nodes IDs to Stack
    perfModel->nodes_IF.push_back(n_IF_stage_ID);
    perfModel->nodes_ID.push_back(n_ID_stage_ID);
    perfModel->nodes_EX.push_back(n_EX_stage_ID);
    perfModel->nodes_WB.push_back(n_WB_stage_ID);
    perfModel->staBranchPredModel_trace.push_back(perfModel->staBranchPredModel.getInfoStream());

    // Dump Entrance point for info print (tracing)
    perfModel->entrancePoint = enterPoint + 1;
}

inline void JAL(PerformanceModel* perfModel_) {
    CV32E40P_PerformanceModel* perfModel = static_cast<CV32E40P_PerformanceModel*>(perfModel_);
    uint64_t enterPoint = perfModel->entrancePoint;

    uint64_t n_IF_stage_ID = perfModel->graph.add_node(F_Type::IF_stage);
    perfModel->graph.add_edge(0, n_IF_stage_ID);
    perfModel->graph.set_inorder(perfModel->nodes_IF.back(), n_IF_stage_ID);
    perfModel->graph.add_edge(perfModel->staBranchPredModel.getPc(), n_IF_stage_ID);
    perfModel->staBranchPredModel.setPc_p(n_IF_stage_ID);

    uint64_t n_ID_stage_ID = perfModel->graph.add_node(F_Type::ID_stage);
    perfModel->graph.add_stage_connection(n_IF_stage_ID, n_ID_stage_ID);
    perfModel->graph.set_inorder(perfModel->nodes_ID.back(), n_ID_stage_ID);
    perfModel->staBranchPredModel.setPc_np(n_ID_stage_ID);

    // ALU delay = 1
    uint64_t n_EX_stage_ID = perfModel->graph.add_node(F_Type::EX_stage);
    perfModel->graph.add_stage_connection(n_ID_stage_ID, n_EX_stage_ID);
    perfModel->graph.set_inorder(perfModel->nodes_EX.back(), n_EX_stage_ID);
    perfModel->regModel.setXd(n_EX_stage_ID);

    uint64_t n_WB_stage_ID = perfModel->nodes_WB.back();

    // Add Nodes IDs to Stack
    perfModel->nodes_IF.push_back(n_IF_stage_ID);
    perfModel->nodes_ID.push_back(n_ID_stage_ID);
    perfModel->nodes_EX.push_back(n_EX_stage_ID);
    perfModel->nodes_WB.push_back(n_WB_stage_ID);
    perfModel->staBranchPredModel_trace.push_back(perfModel->staBranchPredModel.getInfoStream());

    // Dump Entrance point for info print (tracing)
    perfModel->entrancePoint = enterPoint + 1;
}

inline void JALR(PerformanceModel* perfModel_) {
    CV32E40P_PerformanceModel* perfModel = static_cast<CV32E40P_PerformanceModel*>(perfModel_);
    uint64_t enterPoint = perfModel->entrancePoint;

    uint64_t n_IF_stage_ID = perfModel->graph.add_node(F_Type::IF_stage);
    perfModel->graph.add_edge(0, n_IF_stage_ID);
    perfModel->graph.set_inorder(perfModel->nodes_IF.back(), n_IF_stage_ID);
    perfModel->graph.add_edge(perfModel->staBranchPredModel.getPc(), n_IF_stage_ID);
    perfModel->staBranchPredModel.setPc_p(n_IF_stage_ID);

    uint64_t n_ID_stage_ID = perfModel->graph.add_node(F_Type::ID_stage);
    perfModel->graph.add_stage_connection(n_IF_stage_ID, n_ID_stage_ID);
    perfModel->graph.set_inorder(perfModel->nodes_ID.back(), n_ID_stage_ID);
    perfModel->graph.add_edge(perfModel->regModel.getXa(), n_ID_stage_ID);
    perfModel->staBranchPredModel.setPc_np(n_ID_stage_ID);

    // ALU delay = 1
    uint64_t n_EX_stage_ID = perfModel->graph.add_node(F_Type::EX_stage);
    perfModel->graph.add_stage_connection(n_ID_stage_ID, n_EX_stage_ID);
    perfModel->graph.set_inorder(perfModel->nodes_EX.back(), n_EX_stage_ID);
    perfModel->regModel.setXd(n_EX_stage_ID);

    uint64_t n_WB_stage_ID = perfModel->nodes_WB.back();

    // Add Nodes IDs to Stack
    perfModel->nodes_IF.push_back(n_IF_stage_ID);
    perfModel->nodes_ID.push_back(n_ID_stage_ID);
    perfModel->nodes_EX.push_back(n_EX_stage_ID);
    perfModel->nodes_WB.push_back(n_WB_stage_ID);
    perfModel->staBranchPredModel_trace.push_back(perfModel->staBranchPredModel.getInfoStream());

    // Dump Entrance point for info print (tracing)
    perfModel->entrancePoint = enterPoint + 1;
}

}  // namespace CV32E40P