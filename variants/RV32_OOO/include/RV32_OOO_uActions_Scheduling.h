#include <algorithm>
#include <cstdint>

#include "PerformanceModel.h"

#include "RV32_OOO_PerformanceModel.h"

namespace RV32_OOO {

inline void Arith_Ra_Rb(PerformanceModel* perfModel_) {
    RV32_OOO_PerformanceModel* perfModel = static_cast<RV32_OOO_PerformanceModel*>(perfModel_);
    uint64_t enterPoint = perfModel->entrancePoint;

    // uint64_t n_PC_stage = perfModel->graph.add_node(F_Type::PC_stage);
    // // perfModel->graph.set_latency(n_IF_stage_ID, 1);
    // perfModel->graph.add_edge(0, n_PC_stage);
    // perfModel->graph.add_edge(perfModel->noBranchPredModel.getPc(), n_PC_stage);
    // perfModel->noBranchPredModel.setPc_p(n_PC_stage);

    // uint64_t n_IF_stage = perfModel->graph.add_node(F_Type::IF_stage);
    // perfModel->graph.add_edge(n_PC_stage, n_IF_stage);
    // perfModel->graph.add_exit_cond(n_IF_stage, perfModel->clobberModel.getCb_out());

    // uint64_t n_IS_stage = perfModel->graph.add_node(F_Type::IS_stage);
    // perfModel->graph.add_edge(n_IF_stage, n_IS_stage);

    // uint64_t n_IB_stage = perfModel->graph.add_parent_node(F_Type::IB_stage, 4);
    // perfModel->graph.add_edge(n_IS_stage, n_IB_stage);

    // uint64_t n_EX_stage_ID = perfModel->graph.add_node(F_Type::EX_alu, 1, 1, n_IB_stage);
    // perfModel->graph.add_edge(n_IS_stage, n_EX_stage_ID);
    // perfModel->graph.add_edge(perfModel->regModel.getXa(), n_EX_stage_ID);
    // perfModel->graph.add_edge(perfModel->regModel.getXb(), n_EX_stage_ID);
    // perfModel->regModel.setXd(n_EX_stage_ID);

    // uint64_t n_WB_stage_ID = perfModel->graph.add_node(F_Type::WB_stage, 1, 4, n_IB_stage);
    // perfModel->regModel.setXd(n_EX_stage_ID);

    // Add Nodes IDs to Stack
    // perfModel->nodes_IF.push_back(n_IF_stage_ID);
    // perfModel->nodes_ID.push_back(n_ID_stage_ID);
    // perfModel->nodes_EX.push_back(n_EX_stage_ID);
    // perfModel->nodes_WB.push_back(n_WB_stage_ID);
    // perfModel->staBranchPredModel_trace.push_back(perfModel->staBranchPredModel.getInfoStream());

    // Dump Entrance point for info print (tracing)
    perfModel->entrancePoint = enterPoint + 1;
}

inline void Arith_Ra(PerformanceModel* perfModel_) {
    RV32_OOO_PerformanceModel* perfModel = static_cast<RV32_OOO_PerformanceModel*>(perfModel_);
    uint64_t enterPoint = perfModel->entrancePoint;

    // Dump Entrance point for info print (tracing)
    perfModel->entrancePoint = enterPoint + 1;
}

inline void Arith_X(PerformanceModel* perfModel_) {
    RV32_OOO_PerformanceModel* perfModel = static_cast<RV32_OOO_PerformanceModel*>(perfModel_);
    uint64_t enterPoint = perfModel->entrancePoint;

    // Dump Entrance point for info print (tracing)
    perfModel->entrancePoint = enterPoint + 1;
}

inline void Mul_Ra_Rb(PerformanceModel* perfModel_) {
    RV32_OOO_PerformanceModel* perfModel = static_cast<RV32_OOO_PerformanceModel*>(perfModel_);
    uint64_t enterPoint = perfModel->entrancePoint;

    // Dump Entrance point for info print (tracing)
    perfModel->entrancePoint = enterPoint + 1;
}

inline void MulH_Ra_Rb(PerformanceModel* perfModel_) {
    RV32_OOO_PerformanceModel* perfModel = static_cast<RV32_OOO_PerformanceModel*>(perfModel_);
    uint64_t enterPoint = perfModel->entrancePoint;

    // Dump Entrance point for info print (tracing)
    perfModel->entrancePoint = enterPoint + 1;
}

inline void Div_Ra_Rb(PerformanceModel* perfModel_) {
    RV32_OOO_PerformanceModel* perfModel = static_cast<RV32_OOO_PerformanceModel*>(perfModel_);
    uint64_t enterPoint = perfModel->entrancePoint;

    // Dump Entrance point for info print (tracing)
    perfModel->entrancePoint = enterPoint + 1;
}

inline void DivU_Ra_Rb(PerformanceModel* perfModel_) {
    RV32_OOO_PerformanceModel* perfModel = static_cast<RV32_OOO_PerformanceModel*>(perfModel_);
    uint64_t enterPoint = perfModel->entrancePoint;

    // Dump Entrance point for info print (tracing)
    perfModel->entrancePoint = enterPoint + 1;
}

inline void Csr_Ra(PerformanceModel* perfModel_) {
    RV32_OOO_PerformanceModel* perfModel = static_cast<RV32_OOO_PerformanceModel*>(perfModel_);
    uint64_t enterPoint = perfModel->entrancePoint;

    // Dump Entrance point for info print (tracing)
    perfModel->entrancePoint = enterPoint + 1;
}

inline void Csr_X(PerformanceModel* perfModel_) {
    RV32_OOO_PerformanceModel* perfModel = static_cast<RV32_OOO_PerformanceModel*>(perfModel_);
    uint64_t enterPoint = perfModel->entrancePoint;

    // Dump Entrance point for info print (tracing)
    perfModel->entrancePoint = enterPoint + 1;
}

inline void Store(PerformanceModel* perfModel_) {
    RV32_OOO_PerformanceModel* perfModel = static_cast<RV32_OOO_PerformanceModel*>(perfModel_);
    uint64_t enterPoint = perfModel->entrancePoint;

    // Dump Entrance point for info print (tracing)
    perfModel->entrancePoint = enterPoint + 1;
}

inline void Load(PerformanceModel* perfModel_) {
    RV32_OOO_PerformanceModel* perfModel = static_cast<RV32_OOO_PerformanceModel*>(perfModel_);
    uint64_t enterPoint = perfModel->entrancePoint;

    // Dump Entrance point for info print (tracing)
    perfModel->entrancePoint = enterPoint + 1;
}

inline void Branch_Ra_Rb(PerformanceModel* perfModel_) {
    RV32_OOO_PerformanceModel* perfModel = static_cast<RV32_OOO_PerformanceModel*>(perfModel_);
    uint64_t enterPoint = perfModel->entrancePoint;

    // Dump Entrance point for info print (tracing)
    perfModel->entrancePoint = enterPoint + 1;
}

inline void Default_Inst(PerformanceModel* perfModel_) {
    RV32_OOO_PerformanceModel* perfModel = static_cast<RV32_OOO_PerformanceModel*>(perfModel_);
    uint64_t enterPoint = perfModel->entrancePoint;

    // Dump Entrance point for info print (tracing)
    perfModel->entrancePoint = enterPoint + 1;
}

inline void JAL(PerformanceModel* perfModel_) {
    RV32_OOO_PerformanceModel* perfModel = static_cast<RV32_OOO_PerformanceModel*>(perfModel_);
    uint64_t enterPoint = perfModel->entrancePoint;

    // Dump Entrance point for info print (tracing)
    perfModel->entrancePoint = enterPoint + 1;
}

inline void JALR(PerformanceModel* perfModel_) {
    RV32_OOO_PerformanceModel* perfModel = static_cast<RV32_OOO_PerformanceModel*>(perfModel_);
    uint64_t enterPoint = perfModel->entrancePoint;

    // Dump Entrance point for info print (tracing)
    perfModel->entrancePoint = enterPoint + 1;
}

}  // namespace RV32_OOO