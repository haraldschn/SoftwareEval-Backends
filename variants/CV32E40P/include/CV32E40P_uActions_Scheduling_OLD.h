#include <algorithm>
#include <cstdint>

#include "PerformanceModel.h"

#include "CV32E40P_PerformanceModel.h"

namespace CV32E40P {

inline void Arith_Ra_Rb(PerformanceModel* perfModel_) {
    CV32E40P_PerformanceModel* perfModel = static_cast<CV32E40P_PerformanceModel*>(perfModel_);
    // Enter
    uint64_t n_Enter = perfModel->IF_stage; // ID_start [i-1]
    // IPort_R
    uint64_t n_IPort_R;
    uint64_t n_IPort_R_max;
    n_IPort_R_max = std::max({n_Enter, perfModel->staBranchPredModel.getPc()});
    n_IPort_R = n_IPort_R_max + 1;
    // PCGen
    uint64_t n_PCGen;
    uint64_t n_PCGen_max;
    n_PCGen_max = std::max({n_Enter, perfModel->staBranchPredModel.getPc()});
    n_PCGen = n_PCGen_max + 1;
    perfModel->staBranchPredModel.setPc_p(n_PCGen);
    // IF_stage
    uint64_t n_IF_stage;
    n_IF_stage = std::max({n_IPort_R, n_PCGen, perfModel->ID_stage});
    perfModel->IF_stage = n_IF_stage; //ID_start [i]
    // Decoder
    uint64_t n_Decoder;
    n_Decoder = n_IF_stage + 1;
    // uA_OF_A
    uint64_t n_uA_OF_A;
    n_uA_OF_A = std::max({n_IF_stage, perfModel->regModel.getXa()});
    // uA_OF_B
    uint64_t n_uA_OF_B;
    n_uA_OF_B = std::max({n_IF_stage, perfModel->regModel.getXb()});
    // ID_stage
    uint64_t n_ID_stage;
    n_ID_stage = std::max({n_Decoder, n_uA_OF_A, n_uA_OF_B, perfModel->EX_stage});
    perfModel->ID_stage = n_ID_stage; //EX_start [i]
    // ALU
    uint64_t n_ALU;
    n_ALU = n_ID_stage + 1;
    perfModel->regModel.setXd(n_ALU);
    // EX_stage
    uint64_t n_EX_stage = n_ALU;
    perfModel->EX_stage = n_EX_stage; //max(WB_start[i], EX_end [i])

    // Dump Entrance point for info print (tracing)
    perfModel->entrancePoint = n_Enter;
}

inline void Arith_Ra(PerformanceModel* perfModel_) {
    CV32E40P_PerformanceModel* perfModel = static_cast<CV32E40P_PerformanceModel*>(perfModel_);
    // Enter
    uint64_t n_Enter = perfModel->IF_stage;
    // IPort_R
    uint64_t n_IPort_R;
    uint64_t n_IPort_R_max;
    n_IPort_R_max = std::max({n_Enter, perfModel->staBranchPredModel.getPc()});
    n_IPort_R = n_IPort_R_max + 1;
    // PCGen
    uint64_t n_PCGen;
    uint64_t n_PCGen_max;
    n_PCGen_max = std::max({n_Enter, perfModel->staBranchPredModel.getPc()});
    n_PCGen = n_PCGen_max + 1;
    perfModel->staBranchPredModel.setPc_p(n_PCGen);
    // IF_stage
    uint64_t n_IF_stage;
    n_IF_stage = std::max({n_IPort_R, n_PCGen, perfModel->ID_stage});
    perfModel->IF_stage = n_IF_stage;
    // Decoder
    uint64_t n_Decoder;
    n_Decoder = n_IF_stage + 1;
    // uA_OF_A
    uint64_t n_uA_OF_A;
    n_uA_OF_A = std::max({n_IF_stage, perfModel->regModel.getXa()});
    // ID_stage
    uint64_t n_ID_stage;
    n_ID_stage = std::max({n_Decoder, n_uA_OF_A, perfModel->EX_stage});
    perfModel->ID_stage = n_ID_stage;
    // ALU
    uint64_t n_ALU;
    n_ALU = n_ID_stage + 1;
    perfModel->regModel.setXd(n_ALU);
    // EX_stage
    uint64_t n_EX_stage = n_ALU;
    perfModel->EX_stage = n_EX_stage;

    // Dump Entrance point for info print (tracing)
    perfModel->entrancePoint = n_Enter;
}

inline void Arith_X(PerformanceModel* perfModel_) {
    CV32E40P_PerformanceModel* perfModel = static_cast<CV32E40P_PerformanceModel*>(perfModel_);
    // Enter
    uint64_t n_Enter = perfModel->IF_stage;
    // IPort_R
    uint64_t n_IPort_R;
    uint64_t n_IPort_R_max;
    n_IPort_R_max = std::max({n_Enter, perfModel->staBranchPredModel.getPc()});
    n_IPort_R = n_IPort_R_max + 1;
    // PCGen
    uint64_t n_PCGen;
    uint64_t n_PCGen_max;
    n_PCGen_max = std::max({n_Enter, perfModel->staBranchPredModel.getPc()});
    n_PCGen = n_PCGen_max + 1;
    perfModel->staBranchPredModel.setPc_p(n_PCGen);
    // IF_stage
    uint64_t n_IF_stage;
    n_IF_stage = std::max({n_IPort_R, n_PCGen, perfModel->ID_stage});
    perfModel->IF_stage = n_IF_stage;
    // Decoder
    uint64_t n_Decoder;
    n_Decoder = n_IF_stage + 1;
    // ID_stage
    uint64_t n_ID_stage;
    n_ID_stage = std::max({n_Decoder, perfModel->EX_stage});
    perfModel->ID_stage = n_ID_stage;
    // ALU
    uint64_t n_ALU;
    n_ALU = n_ID_stage + 1;
    perfModel->regModel.setXd(n_ALU);
    // EX_stage
    uint64_t n_EX_stage = n_ALU;
    perfModel->EX_stage = n_EX_stage;

    // Dump Entrance point for info print (tracing)
    perfModel->entrancePoint = n_Enter;
}

inline void Mul_Ra_Rb(PerformanceModel* perfModel_) {
    CV32E40P_PerformanceModel* perfModel = static_cast<CV32E40P_PerformanceModel*>(perfModel_);
    // Enter
    uint64_t n_Enter = perfModel->IF_stage;
    // IPort_R
    uint64_t n_IPort_R;
    uint64_t n_IPort_R_max;
    n_IPort_R_max = std::max({n_Enter, perfModel->staBranchPredModel.getPc()});
    n_IPort_R = n_IPort_R_max + 1;
    // PCGen
    uint64_t n_PCGen;
    uint64_t n_PCGen_max;
    n_PCGen_max = std::max({n_Enter, perfModel->staBranchPredModel.getPc()});
    n_PCGen = n_PCGen_max + 1;
    perfModel->staBranchPredModel.setPc_p(n_PCGen);
    // IF_stage
    uint64_t n_IF_stage;
    n_IF_stage = std::max({n_IPort_R, n_PCGen, perfModel->ID_stage});
    perfModel->IF_stage = n_IF_stage;
    // Decoder
    uint64_t n_Decoder;
    n_Decoder = n_IF_stage + 1;
    // uA_OF_A
    uint64_t n_uA_OF_A;
    n_uA_OF_A = std::max({n_IF_stage, perfModel->regModel.getXa()});
    // uA_OF_B
    uint64_t n_uA_OF_B;
    n_uA_OF_B = std::max({n_IF_stage, perfModel->regModel.getXb()});
    // ID_stage
    uint64_t n_ID_stage;
    n_ID_stage = std::max({n_Decoder, n_uA_OF_A, n_uA_OF_B, perfModel->EX_stage});
    perfModel->ID_stage = n_ID_stage;
    // MUL
    uint64_t n_MUL;
    n_MUL = n_ID_stage + 1;
    perfModel->regModel.setXd(n_MUL);
    // EX_stage
    uint64_t n_EX_stage = n_MUL;
    perfModel->EX_stage = n_EX_stage;

    // Dump Entrance point for info print (tracing)
    perfModel->entrancePoint = n_Enter;
}

inline void MulH_Ra_Rb(PerformanceModel* perfModel_) {
    CV32E40P_PerformanceModel* perfModel = static_cast<CV32E40P_PerformanceModel*>(perfModel_);
    // Enter
    uint64_t n_Enter = perfModel->IF_stage;
    // IPort_R
    uint64_t n_IPort_R;
    uint64_t n_IPort_R_max;
    n_IPort_R_max = std::max({n_Enter, perfModel->staBranchPredModel.getPc()});
    n_IPort_R = n_IPort_R_max + 1;
    // PCGen
    uint64_t n_PCGen;
    uint64_t n_PCGen_max;
    n_PCGen_max = std::max({n_Enter, perfModel->staBranchPredModel.getPc()});
    n_PCGen = n_PCGen_max + 1;
    perfModel->staBranchPredModel.setPc_p(n_PCGen);
    // IF_stage
    uint64_t n_IF_stage;
    n_IF_stage = std::max({n_IPort_R, n_PCGen, perfModel->ID_stage});
    perfModel->IF_stage = n_IF_stage;
    // Decoder
    uint64_t n_Decoder;
    n_Decoder = n_IF_stage + 1;
    // uA_OF_A
    uint64_t n_uA_OF_A;
    n_uA_OF_A = std::max({n_IF_stage, perfModel->regModel.getXa()});
    // uA_OF_B
    uint64_t n_uA_OF_B;
    n_uA_OF_B = std::max({n_IF_stage, perfModel->regModel.getXb()});
    // ID_stage
    uint64_t n_ID_stage;
    n_ID_stage = std::max({n_Decoder, n_uA_OF_A, n_uA_OF_B, perfModel->EX_stage});
    perfModel->ID_stage = n_ID_stage;
    // MULH
    uint64_t n_MULH;
    n_MULH = n_ID_stage + 5;
    perfModel->regModel.setXd(n_MULH);
    // EX_stage
    uint64_t n_EX_stage = n_MULH;
    perfModel->EX_stage = n_EX_stage;

    // Dump Entrance point for info print (tracing)
    perfModel->entrancePoint = n_Enter;
}

inline void Div_Ra_Rb(PerformanceModel* perfModel_) {
    CV32E40P_PerformanceModel* perfModel = static_cast<CV32E40P_PerformanceModel*>(perfModel_);
    // Enter
    uint64_t n_Enter = perfModel->IF_stage;
    // IPort_R
    uint64_t n_IPort_R;
    uint64_t n_IPort_R_max;
    n_IPort_R_max = std::max({n_Enter, perfModel->staBranchPredModel.getPc()});
    n_IPort_R = n_IPort_R_max + 1;
    // PCGen
    uint64_t n_PCGen;
    uint64_t n_PCGen_max;
    n_PCGen_max = std::max({n_Enter, perfModel->staBranchPredModel.getPc()});
    n_PCGen = n_PCGen_max + 1;
    perfModel->staBranchPredModel.setPc_p(n_PCGen);
    // IF_stage
    uint64_t n_IF_stage;
    n_IF_stage = std::max({n_IPort_R, n_PCGen, perfModel->ID_stage});
    perfModel->IF_stage = n_IF_stage;
    // Decoder
    uint64_t n_Decoder;
    n_Decoder = n_IF_stage + 1;
    // uA_OF_A
    uint64_t n_uA_OF_A;
    n_uA_OF_A = std::max({n_IF_stage, perfModel->regModel.getXa()});
    // uA_OF_B
    uint64_t n_uA_OF_B;
    n_uA_OF_B = std::max({n_IF_stage, perfModel->regModel.getXb()});
    // ID_stage
    uint64_t n_ID_stage;
    n_ID_stage = std::max({n_Decoder, n_uA_OF_A, n_uA_OF_B, perfModel->EX_stage});
    perfModel->ID_stage = n_ID_stage;
    // DIV
    uint64_t n_DIV;
    n_DIV = n_ID_stage + perfModel->divider.getDelay();
    perfModel->regModel.setXd(n_DIV);
    // EX_stage
    uint64_t n_EX_stage = n_DIV;
    perfModel->EX_stage = n_EX_stage;

    // Dump Entrance point for info print (tracing)
    perfModel->entrancePoint = n_Enter;
}

inline void DivU_Ra_Rb(PerformanceModel* perfModel_) {
    CV32E40P_PerformanceModel* perfModel = static_cast<CV32E40P_PerformanceModel*>(perfModel_);
    // Enter
    uint64_t n_Enter = perfModel->IF_stage;
    // IPort_R
    uint64_t n_IPort_R;
    uint64_t n_IPort_R_max;
    n_IPort_R_max = std::max({n_Enter, perfModel->staBranchPredModel.getPc()});
    n_IPort_R = n_IPort_R_max + 1;
    // PCGen
    uint64_t n_PCGen;
    uint64_t n_PCGen_max;
    n_PCGen_max = std::max({n_Enter, perfModel->staBranchPredModel.getPc()});
    n_PCGen = n_PCGen_max + 1;
    perfModel->staBranchPredModel.setPc_p(n_PCGen);
    // IF_stage
    uint64_t n_IF_stage;
    n_IF_stage = std::max({n_IPort_R, n_PCGen, perfModel->ID_stage});
    perfModel->IF_stage = n_IF_stage;
    // Decoder
    uint64_t n_Decoder;
    n_Decoder = n_IF_stage + 1;
    // uA_OF_A
    uint64_t n_uA_OF_A;
    n_uA_OF_A = std::max({n_IF_stage, perfModel->regModel.getXa()});
    // uA_OF_B
    uint64_t n_uA_OF_B;
    n_uA_OF_B = std::max({n_IF_stage, perfModel->regModel.getXb()});
    // ID_stage
    uint64_t n_ID_stage;
    n_ID_stage = std::max({n_Decoder, n_uA_OF_A, n_uA_OF_B, perfModel->EX_stage});
    perfModel->ID_stage = n_ID_stage;
    // DIVU
    uint64_t n_DIVU;
    n_DIVU = n_ID_stage + perfModel->divider_u.getDelay();
    perfModel->regModel.setXd(n_DIVU);
    // EX_stage
    uint64_t n_EX_stage = n_DIVU;
    perfModel->EX_stage = n_EX_stage;

    // Dump Entrance point for info print (tracing)
    perfModel->entrancePoint = n_Enter;
}

inline void Csr_Ra(PerformanceModel* perfModel_) {
    CV32E40P_PerformanceModel* perfModel = static_cast<CV32E40P_PerformanceModel*>(perfModel_);
    // Enter
    uint64_t n_Enter = perfModel->IF_stage;
    // IPort_R
    uint64_t n_IPort_R;
    uint64_t n_IPort_R_max;
    n_IPort_R_max = std::max({n_Enter, perfModel->staBranchPredModel.getPc()});
    n_IPort_R = n_IPort_R_max + 1;
    // PCGen
    uint64_t n_PCGen;
    uint64_t n_PCGen_max;
    n_PCGen_max = std::max({n_Enter, perfModel->staBranchPredModel.getPc()});
    n_PCGen = n_PCGen_max + 1;
    perfModel->staBranchPredModel.setPc_p(n_PCGen);
    // IF_stage
    uint64_t n_IF_stage;
    n_IF_stage = std::max({n_IPort_R, n_PCGen, perfModel->ID_stage});
    perfModel->IF_stage = n_IF_stage;
    // Decoder
    uint64_t n_Decoder;
    n_Decoder = n_IF_stage + 1;
    // uA_OF_A
    uint64_t n_uA_OF_A;
    n_uA_OF_A = std::max({n_IF_stage, perfModel->regModel.getXa()});
    // ID_stage
    uint64_t n_ID_stage;
    n_ID_stage = std::max({n_Decoder, n_uA_OF_A, perfModel->EX_stage});
    perfModel->ID_stage = n_ID_stage;
    // CSR
    uint64_t n_CSR;
    n_CSR = n_ID_stage + 1;
    perfModel->regModel.setXd(n_CSR);
    // EX_stage
    uint64_t n_EX_stage = n_CSR;
    perfModel->EX_stage = n_EX_stage;

    // Dump Entrance point for info print (tracing)
    perfModel->entrancePoint = n_Enter;
}

inline void Csr_X(PerformanceModel* perfModel_) {
    CV32E40P_PerformanceModel* perfModel = static_cast<CV32E40P_PerformanceModel*>(perfModel_);
    // Enter
    uint64_t n_Enter = perfModel->IF_stage;
    // IPort_R
    uint64_t n_IPort_R;
    uint64_t n_IPort_R_max;
    n_IPort_R_max = std::max({n_Enter, perfModel->staBranchPredModel.getPc()});
    n_IPort_R = n_IPort_R_max + 1;
    // PCGen
    uint64_t n_PCGen;
    uint64_t n_PCGen_max;
    n_PCGen_max = std::max({n_Enter, perfModel->staBranchPredModel.getPc()});
    n_PCGen = n_PCGen_max + 1;
    perfModel->staBranchPredModel.setPc_p(n_PCGen);
    // IF_stage
    uint64_t n_IF_stage;
    n_IF_stage = std::max({n_IPort_R, n_PCGen, perfModel->ID_stage});
    perfModel->IF_stage = n_IF_stage;
    // Decoder
    uint64_t n_Decoder;
    n_Decoder = n_IF_stage + 1;
    // ID_stage
    uint64_t n_ID_stage;
    n_ID_stage = std::max({n_Decoder, perfModel->EX_stage});
    perfModel->ID_stage = n_ID_stage;
    // CSR
    uint64_t n_CSR;
    n_CSR = n_ID_stage + 1;
    perfModel->regModel.setXd(n_CSR);
    // EX_stage
    uint64_t n_EX_stage = n_CSR;
    perfModel->EX_stage = n_EX_stage;

    // Dump Entrance point for info print (tracing)
    perfModel->entrancePoint = n_Enter;
}

inline void Store(PerformanceModel* perfModel_) {
    CV32E40P_PerformanceModel* perfModel = static_cast<CV32E40P_PerformanceModel*>(perfModel_);
    // Enter
    uint64_t n_Enter = perfModel->IF_stage;
    // IPort_R
    uint64_t n_IPort_R;
    uint64_t n_IPort_R_max;
    n_IPort_R_max = std::max({n_Enter, perfModel->staBranchPredModel.getPc()});
    n_IPort_R = n_IPort_R_max + 1;
    // PCGen
    uint64_t n_PCGen;
    uint64_t n_PCGen_max;
    n_PCGen_max = std::max({n_Enter, perfModel->staBranchPredModel.getPc()});
    n_PCGen = n_PCGen_max + 1;
    perfModel->staBranchPredModel.setPc_p(n_PCGen);
    // IF_stage
    uint64_t n_IF_stage;
    n_IF_stage = std::max({n_IPort_R, n_PCGen, perfModel->ID_stage});
    perfModel->IF_stage = n_IF_stage;
    // Decoder
    uint64_t n_Decoder;
    n_Decoder = n_IF_stage + 1;
    // uA_OF_A
    uint64_t n_uA_OF_A;
    n_uA_OF_A = std::max({n_IF_stage, perfModel->regModel.getXa()});
    // uA_OF_B
    uint64_t n_uA_OF_B;
    n_uA_OF_B = std::max({n_IF_stage, perfModel->regModel.getXb()});
    // ID_stage
    uint64_t n_ID_stage;
    n_ID_stage = std::max({n_Decoder, n_uA_OF_A, n_uA_OF_B, perfModel->EX_stage});
    perfModel->ID_stage = n_ID_stage;
    // LSU
    uint64_t n_LSU;
    n_LSU = n_ID_stage + 1;
    // EX_stage
    uint64_t n_EX_stage;
    n_EX_stage = std::max({n_LSU, perfModel->WB_stage});
    perfModel->EX_stage = n_EX_stage;
    // DPort_W
    uint64_t n_DPort_W;
    n_DPort_W = n_EX_stage + 1;
    // WB_stage
    uint64_t n_WB_stage = n_DPort_W;
    perfModel->WB_stage = n_WB_stage;

    // Dump Entrance point for info print (tracing)
    perfModel->entrancePoint = n_Enter;
}

inline void Load(PerformanceModel* perfModel_) {
    CV32E40P_PerformanceModel* perfModel = static_cast<CV32E40P_PerformanceModel*>(perfModel_);
    // Enter
    uint64_t n_Enter = perfModel->IF_stage;
    // IPort_R
    uint64_t n_IPort_R;
    uint64_t n_IPort_R_max;
    n_IPort_R_max = std::max({n_Enter, perfModel->staBranchPredModel.getPc()});
    n_IPort_R = n_IPort_R_max + 1;
    // PCGen
    uint64_t n_PCGen;
    uint64_t n_PCGen_max;
    n_PCGen_max = std::max({n_Enter, perfModel->staBranchPredModel.getPc()});
    n_PCGen = n_PCGen_max + 1;
    perfModel->staBranchPredModel.setPc_p(n_PCGen);
    // IF_stage
    uint64_t n_IF_stage;
    n_IF_stage = std::max({n_IPort_R, n_PCGen, perfModel->ID_stage});
    perfModel->IF_stage = n_IF_stage;
    // Decoder
    uint64_t n_Decoder;
    n_Decoder = n_IF_stage + 1;
    // uA_OF_A
    uint64_t n_uA_OF_A;
    n_uA_OF_A = std::max({n_IF_stage, perfModel->regModel.getXa()});
    // ID_stage
    uint64_t n_ID_stage;
    n_ID_stage = std::max({n_Decoder, n_uA_OF_A, perfModel->EX_stage});
    perfModel->ID_stage = n_ID_stage;
    // LSU
    uint64_t n_LSU;
    n_LSU = n_ID_stage + 1;
    // EX_stage
    uint64_t n_EX_stage;
    n_EX_stage = std::max({n_LSU, perfModel->WB_stage});
    perfModel->EX_stage = n_EX_stage;
    // DPort_R
    uint64_t n_DPort_R;
    n_DPort_R = n_EX_stage + 1;
    perfModel->regModel.setXd(n_DPort_R);
    // WB_stage
    uint64_t n_WB_stage = n_DPort_R;
    perfModel->WB_stage = n_WB_stage;

    // Dump Entrance point for info print (tracing)
    perfModel->entrancePoint = n_Enter;
}

inline void Branch_Ra_Rb(PerformanceModel* perfModel_) {
    CV32E40P_PerformanceModel* perfModel = static_cast<CV32E40P_PerformanceModel*>(perfModel_);
    // Enter
    uint64_t n_Enter = perfModel->IF_stage;
    // IPort_R
    uint64_t n_IPort_R;
    uint64_t n_IPort_R_max;
    n_IPort_R_max = std::max({n_Enter, perfModel->staBranchPredModel.getPc()});
    n_IPort_R = n_IPort_R_max + 1;
    // PCGen
    uint64_t n_PCGen;
    uint64_t n_PCGen_max;
    n_PCGen_max = std::max({n_Enter, perfModel->staBranchPredModel.getPc()});
    n_PCGen = n_PCGen_max + 1;
    perfModel->staBranchPredModel.setPc_p(n_PCGen);
    // IF_stage
    uint64_t n_IF_stage;
    n_IF_stage = std::max({n_IPort_R, n_PCGen, perfModel->ID_stage});
    perfModel->IF_stage = n_IF_stage;
    // Decoder
    uint64_t n_Decoder;
    n_Decoder = n_IF_stage + 1;
    // uA_OF_A
    uint64_t n_uA_OF_A;
    n_uA_OF_A = std::max({n_IF_stage, perfModel->regModel.getXa()});
    // uA_OF_B
    uint64_t n_uA_OF_B;
    n_uA_OF_B = std::max({n_IF_stage, perfModel->regModel.getXb()});
    // ID_stage
    uint64_t n_ID_stage;
    n_ID_stage = std::max({n_Decoder, n_uA_OF_A, n_uA_OF_B, perfModel->EX_stage});
    perfModel->ID_stage = n_ID_stage;
    // ALU
    uint64_t n_ALU;
    n_ALU = n_ID_stage + 1;
    perfModel->staBranchPredModel.setPc_np(n_ALU);
    // EX_stage
    uint64_t n_EX_stage = n_ALU;
    perfModel->EX_stage = n_EX_stage;

    // Dump Entrance point for info print (tracing)
    perfModel->entrancePoint = n_Enter;
}

inline void Default_Inst(PerformanceModel* perfModel_) {
    CV32E40P_PerformanceModel* perfModel = static_cast<CV32E40P_PerformanceModel*>(perfModel_);
    // Enter
    uint64_t n_Enter = perfModel->IF_stage;
    // IPort_R
    uint64_t n_IPort_R;
    uint64_t n_IPort_R_max;
    n_IPort_R_max = std::max({n_Enter, perfModel->staBranchPredModel.getPc()});
    n_IPort_R = n_IPort_R_max + 1;
    // PCGen
    uint64_t n_PCGen;
    uint64_t n_PCGen_max;
    n_PCGen_max = std::max({n_Enter, perfModel->staBranchPredModel.getPc()});
    n_PCGen = n_PCGen_max + 1;
    perfModel->staBranchPredModel.setPc_p(n_PCGen);
    // IF_stage
    uint64_t n_IF_stage;
    n_IF_stage = std::max({n_IPort_R, n_PCGen});
    perfModel->IF_stage = n_IF_stage;

    // Dump Entrance point for info print (tracing)
    perfModel->entrancePoint = n_Enter;
}

inline void JAL(PerformanceModel* perfModel_) {
    CV32E40P_PerformanceModel* perfModel = static_cast<CV32E40P_PerformanceModel*>(perfModel_);
    // Enter
    uint64_t n_Enter = perfModel->IF_stage;
    // IPort_R
    uint64_t n_IPort_R;
    uint64_t n_IPort_R_max;
    n_IPort_R_max = std::max({n_Enter, perfModel->staBranchPredModel.getPc()});
    n_IPort_R = n_IPort_R_max + 1;
    // PCGen
    uint64_t n_PCGen;
    uint64_t n_PCGen_max;
    n_PCGen_max = std::max({n_Enter, perfModel->staBranchPredModel.getPc()});
    n_PCGen = n_PCGen_max + 1;
    perfModel->staBranchPredModel.setPc_p(n_PCGen);
    // IF_stage
    uint64_t n_IF_stage;
    n_IF_stage = std::max({n_IPort_R, n_PCGen, perfModel->ID_stage});
    perfModel->IF_stage = n_IF_stage;
    // JumpDecoder
    uint64_t n_JumpDecoder;
    n_JumpDecoder = n_IF_stage + 1;
    perfModel->staBranchPredModel.setPc_np(n_JumpDecoder);
    // ID_stage
    uint64_t n_ID_stage;
    n_ID_stage = std::max({n_JumpDecoder, perfModel->EX_stage});
    perfModel->ID_stage = n_ID_stage;
    // ALU
    uint64_t n_ALU;
    n_ALU = n_ID_stage + 1;
    perfModel->regModel.setXd(n_ALU);
    // EX_stage
    uint64_t n_EX_stage = n_ALU;
    perfModel->EX_stage = n_EX_stage;

    // Dump Entrance point for info print (tracing)
    perfModel->entrancePoint = n_Enter;
}

inline void JALR(PerformanceModel* perfModel_) {
    CV32E40P_PerformanceModel* perfModel = static_cast<CV32E40P_PerformanceModel*>(perfModel_);
    // Enter
    uint64_t n_Enter = perfModel->IF_stage;
    // IPort_R
    uint64_t n_IPort_R;
    uint64_t n_IPort_R_max;
    n_IPort_R_max = std::max({n_Enter, perfModel->staBranchPredModel.getPc()});
    n_IPort_R = n_IPort_R_max + 1;
    // PCGen
    uint64_t n_PCGen;
    uint64_t n_PCGen_max;
    n_PCGen_max = std::max({n_Enter, perfModel->staBranchPredModel.getPc()});
    n_PCGen = n_PCGen_max + 1;
    perfModel->staBranchPredModel.setPc_p(n_PCGen);
    // IF_stage
    uint64_t n_IF_stage;
    n_IF_stage = std::max({n_IPort_R, n_PCGen, perfModel->ID_stage});
    perfModel->IF_stage = n_IF_stage; // ID_start [i]
    // JumpDecoder
    uint64_t n_JumpDecoder;
    uint64_t n_JumpDecoder_max;
    n_JumpDecoder_max = std::max({n_IF_stage, perfModel->regModel.getXa()});
    n_JumpDecoder = n_JumpDecoder_max + 1;
    perfModel->staBranchPredModel.setPc_np(n_JumpDecoder);
    // ID_stage
    uint64_t n_ID_stage;
    n_ID_stage = std::max({n_JumpDecoder, perfModel->EX_stage});
    perfModel->ID_stage = n_ID_stage; // EX_start [i]
    // ALU
    uint64_t n_ALU;
    n_ALU = n_ID_stage + 1;
    perfModel->regModel.setXd(n_ALU);
    // EX_stage
    uint64_t n_EX_stage = n_ALU;
    perfModel->EX_stage = n_EX_stage; // max(WB_start[i], EX_end[i])

    // Dump Entrance point for info print (tracing)
    perfModel->entrancePoint = n_Enter;
}

}  // namespace CV32E40P