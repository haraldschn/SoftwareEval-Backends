#include <algorithm>
#include <cstdint>

#include "PerformanceModel.h"

#include "RV32_OOO_PerformanceModel.h"

namespace RV32_OOO {

inline void Arith_Ra_Rb(PerformanceModel* perfModel_) {
    RV32_OOO_PerformanceModel* perfModel = static_cast<RV32_OOO_PerformanceModel*>(perfModel_);
    // Enter
    uint64_t n_Enter = perfModel->PC_stage;
    // PCGen
    uint64_t n_PCGen;
    uint64_t n_PCGen_max;
    n_PCGen_max = std::max({n_Enter, perfModel->noBranchPredModel.getPc()});
    n_PCGen = n_PCGen_max + 1;
    perfModel->noBranchPredModel.setPc_p(n_PCGen);
    // PC_stage
    uint64_t n_PC_stage;
    n_PC_stage = std::max({n_PCGen, perfModel->IF_stage});
    perfModel->PC_stage = n_PC_stage;
    // IPort_R
    uint64_t n_IPort_R;
    n_IPort_R = n_PC_stage + 1;
    // uA_Clobber
    uint64_t n_uA_Clobber;
    n_uA_Clobber = std::max({n_PC_stage, perfModel->clobberModel.getCb_out()});
    // IF_stage
    uint64_t n_IF_stage;
    n_IF_stage = std::max({n_IPort_R, n_uA_Clobber, perfModel->IS_stage});
    perfModel->IF_stage = n_IF_stage;
    // Decoder
    uint64_t n_Decoder;
    n_Decoder = n_IF_stage + 1;
    perfModel->scheduleModel.setDec_alu(n_Decoder);
    // IS_stage
    uint64_t n_IS_stage;
    n_IS_stage = std::max({n_Decoder, perfModel->IB_stage_OoO.get(4)});
    perfModel->IS_stage = n_IS_stage;
    // uA_OF_A
    uint64_t n_uA_OF_A;
    n_uA_OF_A = std::max({n_IS_stage, perfModel->regModel.getXa()});
    // uA_OF_B
    uint64_t n_uA_OF_B;
    n_uA_OF_B = std::max({n_IS_stage, perfModel->regModel.getXb()});
    // uA_Issue
    uint64_t n_uA_Issue;
    n_uA_Issue = std::max({n_IS_stage, perfModel->scheduleModel.getT_issue()});
    // IB_stage_OoO
    uint64_t n_IB_stage_OoO;
    n_IB_stage_OoO = std::max({n_uA_OF_A, n_uA_OF_B, n_uA_Issue});
    perfModel->IB_stage_OoO.set(n_IB_stage_OoO);
    // ALU
    uint64_t n_ALU;
    n_ALU = n_IB_stage_OoO + 1;
    perfModel->regModel.setXd(n_ALU);
    perfModel->clobberModel.setCb_inRd(n_ALU);
    perfModel->clobberModel.setCb_inR1(n_ALU);
    perfModel->clobberModel.setCb_inR2(n_ALU);
    // EX_stage_alu_NoB
    uint64_t n_EX_stage_alu_NoB = n_ALU;
    perfModel->EX_stage_alu_NoB = n_EX_stage_alu_NoB;
    // WB
    uint64_t n_WB;
    n_WB = n_EX_stage_alu_NoB + 1;
    perfModel->scheduleModel.setT_wb(n_WB);
    // WB_stage_NoB
    uint64_t n_WB_stage_NoB = n_WB;
    perfModel->WB_stage_NoB.set(n_WB_stage_NoB);

    // Dump Entrance point for info print (tracing)
    perfModel->entrancePoint = n_Enter;
}

inline void Arith_Ra(PerformanceModel* perfModel_) {
    RV32_OOO_PerformanceModel* perfModel = static_cast<RV32_OOO_PerformanceModel*>(perfModel_);
    // Enter
    uint64_t n_Enter = perfModel->PC_stage;
    // PCGen
    uint64_t n_PCGen;
    uint64_t n_PCGen_max;
    n_PCGen_max = std::max({n_Enter, perfModel->noBranchPredModel.getPc()});
    n_PCGen = n_PCGen_max + 1;
    perfModel->noBranchPredModel.setPc_p(n_PCGen);
    // PC_stage
    uint64_t n_PC_stage;
    n_PC_stage = std::max({n_PCGen, perfModel->IF_stage});
    perfModel->PC_stage = n_PC_stage;
    // IPort_R
    uint64_t n_IPort_R;
    n_IPort_R = n_PC_stage + 1;
    // uA_Clobber
    uint64_t n_uA_Clobber;
    n_uA_Clobber = std::max({n_PC_stage, perfModel->clobberModel.getCb_out()});
    // IF_stage
    uint64_t n_IF_stage;
    n_IF_stage = std::max({n_IPort_R, n_uA_Clobber, perfModel->IS_stage});
    perfModel->IF_stage = n_IF_stage;
    // Decoder
    uint64_t n_Decoder;
    n_Decoder = n_IF_stage + 1;
    perfModel->scheduleModel.setDec_alu(n_Decoder);
    // IS_stage
    uint64_t n_IS_stage;
    n_IS_stage = std::max({n_Decoder, perfModel->IB_stage_OoO.get(4)});
    perfModel->IS_stage = n_IS_stage;
    // uA_OF_A
    uint64_t n_uA_OF_A;
    n_uA_OF_A = std::max({n_IS_stage, perfModel->regModel.getXa()});
    // uA_Issue
    uint64_t n_uA_Issue;
    n_uA_Issue = std::max({n_IS_stage, perfModel->scheduleModel.getT_issue()});
    // IB_stage_OoO
    uint64_t n_IB_stage_OoO;
    n_IB_stage_OoO = std::max({n_uA_OF_A, n_uA_Issue});
    perfModel->IB_stage_OoO.set(n_IB_stage_OoO);
    // ALU
    uint64_t n_ALU;
    n_ALU = n_IB_stage_OoO + 1;
    perfModel->regModel.setXd(n_ALU);
    perfModel->clobberModel.setCb_inRd(n_ALU);
    perfModel->clobberModel.setCb_inR1(n_ALU);
    // EX_stage_alu_NoB
    uint64_t n_EX_stage_alu_NoB = n_ALU;
    perfModel->EX_stage_alu_NoB = n_EX_stage_alu_NoB;
    // WB
    uint64_t n_WB;
    n_WB = n_EX_stage_alu_NoB + 1;
    perfModel->scheduleModel.setT_wb(n_WB);
    // WB_stage_NoB
    uint64_t n_WB_stage_NoB = n_WB;
    perfModel->WB_stage_NoB.set(n_WB_stage_NoB);

    // Dump Entrance point for info print (tracing)
    perfModel->entrancePoint = n_Enter;
}

inline void Arith_X(PerformanceModel* perfModel_) {
    RV32_OOO_PerformanceModel* perfModel = static_cast<RV32_OOO_PerformanceModel*>(perfModel_);
    // Enter
    uint64_t n_Enter = perfModel->PC_stage;
    // PCGen
    uint64_t n_PCGen;
    uint64_t n_PCGen_max;
    n_PCGen_max = std::max({n_Enter, perfModel->noBranchPredModel.getPc()});
    n_PCGen = n_PCGen_max + 1;
    perfModel->noBranchPredModel.setPc_p(n_PCGen);
    // PC_stage
    uint64_t n_PC_stage;
    n_PC_stage = std::max({n_PCGen, perfModel->IF_stage});
    perfModel->PC_stage = n_PC_stage;
    // IPort_R
    uint64_t n_IPort_R;
    n_IPort_R = n_PC_stage + 1;
    // uA_Clobber
    uint64_t n_uA_Clobber;
    n_uA_Clobber = std::max({n_PC_stage, perfModel->clobberModel.getCb_out()});
    // IF_stage
    uint64_t n_IF_stage;
    n_IF_stage = std::max({n_IPort_R, n_uA_Clobber, perfModel->IS_stage});
    perfModel->IF_stage = n_IF_stage;
    // Decoder
    uint64_t n_Decoder;
    n_Decoder = n_IF_stage + 1;
    perfModel->scheduleModel.setDec_alu(n_Decoder);
    // IS_stage
    uint64_t n_IS_stage;
    n_IS_stage = std::max({n_Decoder, perfModel->IB_stage_OoO.get(4)});
    perfModel->IS_stage = n_IS_stage;
    // uA_Issue
    uint64_t n_uA_Issue;
    n_uA_Issue = std::max({n_IS_stage, perfModel->scheduleModel.getT_issue()});
    // IB_stage_OoO
    uint64_t n_IB_stage_OoO = n_uA_Issue;
    perfModel->IB_stage_OoO.set(n_IB_stage_OoO);
    // ALU
    uint64_t n_ALU;
    n_ALU = n_IB_stage_OoO + 1;
    perfModel->regModel.setXd(n_ALU);
    perfModel->clobberModel.setCb_inRd(n_ALU);
    // EX_stage_alu_NoB
    uint64_t n_EX_stage_alu_NoB = n_ALU;
    perfModel->EX_stage_alu_NoB = n_EX_stage_alu_NoB;
    // WB
    uint64_t n_WB;
    n_WB = n_EX_stage_alu_NoB + 1;
    perfModel->scheduleModel.setT_wb(n_WB);
    // WB_stage_NoB
    uint64_t n_WB_stage_NoB = n_WB;
    perfModel->WB_stage_NoB.set(n_WB_stage_NoB);

    // Dump Entrance point for info print (tracing)
    perfModel->entrancePoint = n_Enter;
}

inline void Mul_Ra_Rb(PerformanceModel* perfModel_) {
    RV32_OOO_PerformanceModel* perfModel = static_cast<RV32_OOO_PerformanceModel*>(perfModel_);
    // Enter
    uint64_t n_Enter = perfModel->PC_stage;
    // PCGen
    uint64_t n_PCGen;
    uint64_t n_PCGen_max;
    n_PCGen_max = std::max({n_Enter, perfModel->noBranchPredModel.getPc()});
    n_PCGen = n_PCGen_max + 1;
    perfModel->noBranchPredModel.setPc_p(n_PCGen);
    // PC_stage
    uint64_t n_PC_stage;
    n_PC_stage = std::max({n_PCGen, perfModel->IF_stage});
    perfModel->PC_stage = n_PC_stage;
    // IPort_R
    uint64_t n_IPort_R;
    n_IPort_R = n_PC_stage + 1;
    // uA_Clobber
    uint64_t n_uA_Clobber;
    n_uA_Clobber = std::max({n_PC_stage, perfModel->clobberModel.getCb_out()});
    // IF_stage
    uint64_t n_IF_stage;
    n_IF_stage = std::max({n_IPort_R, n_uA_Clobber, perfModel->IS_stage});
    perfModel->IF_stage = n_IF_stage;
    // Decoder
    uint64_t n_Decoder;
    n_Decoder = n_IF_stage + 1;
    perfModel->scheduleModel.setDec_mul(n_Decoder);
    // IS_stage
    uint64_t n_IS_stage;
    n_IS_stage = std::max({n_Decoder, perfModel->IB_stage_OoO.get(4)});
    perfModel->IS_stage = n_IS_stage;
    // uA_OF_A
    uint64_t n_uA_OF_A;
    n_uA_OF_A = std::max({n_IS_stage, perfModel->regModel.getXa()});
    // uA_OF_B
    uint64_t n_uA_OF_B;
    n_uA_OF_B = std::max({n_IS_stage, perfModel->regModel.getXb()});
    // uA_Issue
    uint64_t n_uA_Issue;
    n_uA_Issue = std::max({n_IS_stage, perfModel->scheduleModel.getT_issue()});
    // IB_stage_OoO
    uint64_t n_IB_stage_OoO;
    n_IB_stage_OoO = std::max({n_uA_OF_A, n_uA_OF_B, n_uA_Issue});
    perfModel->IB_stage_OoO.set(n_IB_stage_OoO);
    // MUL0
    uint64_t n_MUL0;
    n_MUL0 = n_IB_stage_OoO + 1;
    // EX_stage_mul0v_NoB
    uint64_t n_EX_stage_mul0v_NoB = n_MUL0;
    perfModel->EX_stage_mul0v_NoB = n_EX_stage_mul0v_NoB;
    // MUL1
    uint64_t n_MUL1;
    n_MUL1 = n_EX_stage_mul0v_NoB + 1;
    perfModel->regModel.setXd(n_MUL1);
    perfModel->clobberModel.setCb_inRd(n_MUL1);
    perfModel->clobberModel.setCb_inR1(n_MUL1);
    perfModel->clobberModel.setCb_inR2(n_MUL1);
    // EX_stage_mul_NoB
    uint64_t n_EX_stage_mul_NoB = n_MUL1;
    perfModel->EX_stage_mul_NoB.set(n_EX_stage_mul_NoB);
    perfModel->EX_stage_mul1v_NoB = n_EX_stage_mul_NoB;
    // WB
    uint64_t n_WB;
    n_WB = n_EX_stage_mul_NoB + 1;
    perfModel->scheduleModel.setT_wb(n_WB);
    // WB_stage_NoB
    uint64_t n_WB_stage_NoB = n_WB;
    perfModel->WB_stage_NoB.set(n_WB_stage_NoB);

    // Dump Entrance point for info print (tracing)
    perfModel->entrancePoint = n_Enter;
}

inline void MulH_Ra_Rb(PerformanceModel* perfModel_) {
    RV32_OOO_PerformanceModel* perfModel = static_cast<RV32_OOO_PerformanceModel*>(perfModel_);
    // Enter
    uint64_t n_Enter = perfModel->PC_stage;
    // PCGen
    uint64_t n_PCGen;
    uint64_t n_PCGen_max;
    n_PCGen_max = std::max({n_Enter, perfModel->noBranchPredModel.getPc()});
    n_PCGen = n_PCGen_max + 1;
    perfModel->noBranchPredModel.setPc_p(n_PCGen);
    // PC_stage
    uint64_t n_PC_stage;
    n_PC_stage = std::max({n_PCGen, perfModel->IF_stage});
    perfModel->PC_stage = n_PC_stage;
    // IPort_R
    uint64_t n_IPort_R;
    n_IPort_R = n_PC_stage + 1;
    // uA_Clobber
    uint64_t n_uA_Clobber;
    n_uA_Clobber = std::max({n_PC_stage, perfModel->clobberModel.getCb_out()});
    // IF_stage
    uint64_t n_IF_stage;
    n_IF_stage = std::max({n_IPort_R, n_uA_Clobber, perfModel->IS_stage});
    perfModel->IF_stage = n_IF_stage;
    // Decoder
    uint64_t n_Decoder;
    n_Decoder = n_IF_stage + 1;
    perfModel->scheduleModel.setDec_mul(n_Decoder);
    // IS_stage
    uint64_t n_IS_stage;
    n_IS_stage = std::max({n_Decoder, perfModel->IB_stage_OoO.get(4)});
    perfModel->IS_stage = n_IS_stage;
    // uA_OF_A
    uint64_t n_uA_OF_A;
    n_uA_OF_A = std::max({n_IS_stage, perfModel->regModel.getXa()});
    // uA_OF_B
    uint64_t n_uA_OF_B;
    n_uA_OF_B = std::max({n_IS_stage, perfModel->regModel.getXb()});
    // uA_Issue
    uint64_t n_uA_Issue;
    n_uA_Issue = std::max({n_IS_stage, perfModel->scheduleModel.getT_issue()});
    // IB_stage_OoO
    uint64_t n_IB_stage_OoO;
    n_IB_stage_OoO = std::max({n_uA_OF_A, n_uA_OF_B, n_uA_Issue});
    perfModel->IB_stage_OoO.set(n_IB_stage_OoO);
    // MUL0
    uint64_t n_MUL0;
    n_MUL0 = n_IB_stage_OoO + 1;
    // EX_stage_mul0v_NoB
    uint64_t n_EX_stage_mul0v_NoB = n_MUL0;
    perfModel->EX_stage_mul0v_NoB = n_EX_stage_mul0v_NoB;
    // MUL1
    uint64_t n_MUL1;
    n_MUL1 = n_EX_stage_mul0v_NoB + 1;
    perfModel->regModel.setXd(n_MUL1);
    perfModel->clobberModel.setCb_inRd(n_MUL1);
    perfModel->clobberModel.setCb_inR1(n_MUL1);
    perfModel->clobberModel.setCb_inR2(n_MUL1);
    // EX_stage_mul_NoB
    uint64_t n_EX_stage_mul_NoB = n_MUL1;
    perfModel->EX_stage_mul_NoB.set(n_EX_stage_mul_NoB);
    perfModel->EX_stage_mul1v_NoB = n_EX_stage_mul_NoB;
    // WB
    uint64_t n_WB;
    n_WB = n_EX_stage_mul_NoB + 1;
    perfModel->scheduleModel.setT_wb(n_WB);
    // WB_stage_NoB
    uint64_t n_WB_stage_NoB = n_WB;
    perfModel->WB_stage_NoB.set(n_WB_stage_NoB);

    // Dump Entrance point for info print (tracing)
    perfModel->entrancePoint = n_Enter;
}

inline void Div_Ra_Rb(PerformanceModel* perfModel_) {
    RV32_OOO_PerformanceModel* perfModel = static_cast<RV32_OOO_PerformanceModel*>(perfModel_);
    // Enter
    uint64_t n_Enter = perfModel->PC_stage;
    // PCGen
    uint64_t n_PCGen;
    uint64_t n_PCGen_max;
    n_PCGen_max = std::max({n_Enter, perfModel->noBranchPredModel.getPc()});
    n_PCGen = n_PCGen_max + 1;
    perfModel->noBranchPredModel.setPc_p(n_PCGen);
    // PC_stage
    uint64_t n_PC_stage;
    n_PC_stage = std::max({n_PCGen, perfModel->IF_stage});
    perfModel->PC_stage = n_PC_stage;
    // IPort_R
    uint64_t n_IPort_R;
    n_IPort_R = n_PC_stage + 1;
    // uA_Clobber
    uint64_t n_uA_Clobber;
    n_uA_Clobber = std::max({n_PC_stage, perfModel->clobberModel.getCb_out()});
    // IF_stage
    uint64_t n_IF_stage;
    n_IF_stage = std::max({n_IPort_R, n_uA_Clobber, perfModel->IS_stage});
    perfModel->IF_stage = n_IF_stage;
    // Decoder
    uint64_t n_Decoder;
    n_Decoder = n_IF_stage + 1;
    perfModel->scheduleModel.setDec_div(n_Decoder);
    // IS_stage
    uint64_t n_IS_stage;
    n_IS_stage = std::max({n_Decoder, perfModel->IB_stage_OoO.get(4)});
    perfModel->IS_stage = n_IS_stage;
    // uA_OF_A
    uint64_t n_uA_OF_A;
    n_uA_OF_A = std::max({n_IS_stage, perfModel->regModel.getXa()});
    // uA_OF_B
    uint64_t n_uA_OF_B;
    n_uA_OF_B = std::max({n_IS_stage, perfModel->regModel.getXb()});
    // uA_Issue
    uint64_t n_uA_Issue;
    n_uA_Issue = std::max({n_IS_stage, perfModel->scheduleModel.getT_issue()});
    // IB_stage_OoO
    uint64_t n_IB_stage_OoO;
    n_IB_stage_OoO = std::max({n_uA_OF_A, n_uA_OF_B, n_uA_Issue});
    perfModel->IB_stage_OoO.set(n_IB_stage_OoO);
    // DIV
    uint64_t n_DIV;
    n_DIV = n_IB_stage_OoO + 4;
    perfModel->regModel.setXd(n_DIV);
    perfModel->clobberModel.setCb_inRd(n_DIV);
    perfModel->clobberModel.setCb_inR1(n_DIV);
    perfModel->clobberModel.setCb_inR2(n_DIV);
    // EX_stage_div_NoB
    uint64_t n_EX_stage_div_NoB = n_DIV;
    perfModel->EX_stage_div_NoB = n_EX_stage_div_NoB;
    // WB
    uint64_t n_WB;
    n_WB = n_EX_stage_div_NoB + 1;
    perfModel->scheduleModel.setT_wb(n_WB);
    // WB_stage_NoB
    uint64_t n_WB_stage_NoB = n_WB;
    perfModel->WB_stage_NoB.set(n_WB_stage_NoB);

    // Dump Entrance point for info print (tracing)
    perfModel->entrancePoint = n_Enter;
}

inline void DivU_Ra_Rb(PerformanceModel* perfModel_) {
    RV32_OOO_PerformanceModel* perfModel = static_cast<RV32_OOO_PerformanceModel*>(perfModel_);
    // Enter
    uint64_t n_Enter = perfModel->PC_stage;
    // PCGen
    uint64_t n_PCGen;
    uint64_t n_PCGen_max;
    n_PCGen_max = std::max({n_Enter, perfModel->noBranchPredModel.getPc()});
    n_PCGen = n_PCGen_max + 1;
    perfModel->noBranchPredModel.setPc_p(n_PCGen);
    // PC_stage
    uint64_t n_PC_stage;
    n_PC_stage = std::max({n_PCGen, perfModel->IF_stage});
    perfModel->PC_stage = n_PC_stage;
    // IPort_R
    uint64_t n_IPort_R;
    n_IPort_R = n_PC_stage + 1;
    // uA_Clobber
    uint64_t n_uA_Clobber;
    n_uA_Clobber = std::max({n_PC_stage, perfModel->clobberModel.getCb_out()});
    // IF_stage
    uint64_t n_IF_stage;
    n_IF_stage = std::max({n_IPort_R, n_uA_Clobber, perfModel->IS_stage});
    perfModel->IF_stage = n_IF_stage;
    // Decoder
    uint64_t n_Decoder;
    n_Decoder = n_IF_stage + 1;
    perfModel->scheduleModel.setDec_div(n_Decoder);
    // IS_stage
    uint64_t n_IS_stage;
    n_IS_stage = std::max({n_Decoder, perfModel->IB_stage_OoO.get(4)});
    perfModel->IS_stage = n_IS_stage;
    // uA_OF_A
    uint64_t n_uA_OF_A;
    n_uA_OF_A = std::max({n_IS_stage, perfModel->regModel.getXa()});
    // uA_OF_B
    uint64_t n_uA_OF_B;
    n_uA_OF_B = std::max({n_IS_stage, perfModel->regModel.getXb()});
    // uA_Issue
    uint64_t n_uA_Issue;
    n_uA_Issue = std::max({n_IS_stage, perfModel->scheduleModel.getT_issue()});
    // IB_stage_OoO
    uint64_t n_IB_stage_OoO;
    n_IB_stage_OoO = std::max({n_uA_OF_A, n_uA_OF_B, n_uA_Issue});
    perfModel->IB_stage_OoO.set(n_IB_stage_OoO);
    // DIV
    uint64_t n_DIV;
    n_DIV = n_IB_stage_OoO + 4;
    perfModel->regModel.setXd(n_DIV);
    perfModel->clobberModel.setCb_inRd(n_DIV);
    perfModel->clobberModel.setCb_inR1(n_DIV);
    perfModel->clobberModel.setCb_inR2(n_DIV);
    // EX_stage_div_NoB
    uint64_t n_EX_stage_div_NoB = n_DIV;
    perfModel->EX_stage_div_NoB = n_EX_stage_div_NoB;
    // WB
    uint64_t n_WB;
    n_WB = n_EX_stage_div_NoB + 1;
    perfModel->scheduleModel.setT_wb(n_WB);
    // WB_stage_NoB
    uint64_t n_WB_stage_NoB = n_WB;
    perfModel->WB_stage_NoB.set(n_WB_stage_NoB);

    // Dump Entrance point for info print (tracing)
    perfModel->entrancePoint = n_Enter;
}

inline void Csr_Ra(PerformanceModel* perfModel_) {
    RV32_OOO_PerformanceModel* perfModel = static_cast<RV32_OOO_PerformanceModel*>(perfModel_);
    // Enter
    uint64_t n_Enter = perfModel->PC_stage;
    // PCGen
    uint64_t n_PCGen;
    uint64_t n_PCGen_max;
    n_PCGen_max = std::max({n_Enter, perfModel->noBranchPredModel.getPc()});
    n_PCGen = n_PCGen_max + 1;
    perfModel->noBranchPredModel.setPc_p(n_PCGen);
    // PC_stage
    uint64_t n_PC_stage;
    n_PC_stage = std::max({n_PCGen, perfModel->IF_stage});
    perfModel->PC_stage = n_PC_stage;
    // IPort_R
    uint64_t n_IPort_R;
    n_IPort_R = n_PC_stage + 1;
    // uA_Clobber
    uint64_t n_uA_Clobber;
    n_uA_Clobber = std::max({n_PC_stage, perfModel->clobberModel.getCb_out()});
    // IF_stage
    uint64_t n_IF_stage;
    n_IF_stage = std::max({n_IPort_R, n_uA_Clobber, perfModel->IS_stage});
    perfModel->IF_stage = n_IF_stage;
    // Decoder
    uint64_t n_Decoder;
    n_Decoder = n_IF_stage + 1;
    perfModel->scheduleModel.setDec_alu(n_Decoder);
    // IS_stage
    uint64_t n_IS_stage;
    n_IS_stage = std::max({n_Decoder, perfModel->IB_stage_OoO.get(4)});
    perfModel->IS_stage = n_IS_stage;
    // uA_OF_A
    uint64_t n_uA_OF_A;
    n_uA_OF_A = std::max({n_IS_stage, perfModel->regModel.getXa()});
    // uA_Issue
    uint64_t n_uA_Issue;
    n_uA_Issue = std::max({n_IS_stage, perfModel->scheduleModel.getT_issue()});
    // IB_stage_OoO
    uint64_t n_IB_stage_OoO;
    n_IB_stage_OoO = std::max({n_uA_OF_A, n_uA_Issue});
    perfModel->IB_stage_OoO.set(n_IB_stage_OoO);
    // CSR
    uint64_t n_CSR;
    n_CSR = n_IB_stage_OoO + 1;
    perfModel->regModel.setXd(n_CSR);
    perfModel->clobberModel.setCb_inRd(n_CSR);
    // EX_stage_alu_NoB
    uint64_t n_EX_stage_alu_NoB = n_CSR;
    perfModel->EX_stage_alu_NoB = n_EX_stage_alu_NoB;
    // WB
    uint64_t n_WB;
    n_WB = n_EX_stage_alu_NoB + 1;
    perfModel->scheduleModel.setT_wb(n_WB);
    // WB_stage_NoB
    uint64_t n_WB_stage_NoB = n_WB;
    perfModel->WB_stage_NoB.set(n_WB_stage_NoB);

    // Dump Entrance point for info print (tracing)
    perfModel->entrancePoint = n_Enter;
}

inline void Csr_X(PerformanceModel* perfModel_) {
    RV32_OOO_PerformanceModel* perfModel = static_cast<RV32_OOO_PerformanceModel*>(perfModel_);
    // Enter
    uint64_t n_Enter = perfModel->PC_stage;
    // PCGen
    uint64_t n_PCGen;
    uint64_t n_PCGen_max;
    n_PCGen_max = std::max({n_Enter, perfModel->noBranchPredModel.getPc()});
    n_PCGen = n_PCGen_max + 1;
    perfModel->noBranchPredModel.setPc_p(n_PCGen);
    // PC_stage
    uint64_t n_PC_stage;
    n_PC_stage = std::max({n_PCGen, perfModel->IF_stage});
    perfModel->PC_stage = n_PC_stage;
    // IPort_R
    uint64_t n_IPort_R;
    n_IPort_R = n_PC_stage + 1;
    // uA_Clobber
    uint64_t n_uA_Clobber;
    n_uA_Clobber = std::max({n_PC_stage, perfModel->clobberModel.getCb_out()});
    // IF_stage
    uint64_t n_IF_stage;
    n_IF_stage = std::max({n_IPort_R, n_uA_Clobber, perfModel->IS_stage});
    perfModel->IF_stage = n_IF_stage;
    // Decoder
    uint64_t n_Decoder;
    n_Decoder = n_IF_stage + 1;
    perfModel->scheduleModel.setDec_alu(n_Decoder);
    // IS_stage
    uint64_t n_IS_stage;
    n_IS_stage = std::max({n_Decoder, perfModel->IB_stage_OoO.get(4)});
    perfModel->IS_stage = n_IS_stage;
    // uA_Issue
    uint64_t n_uA_Issue;
    n_uA_Issue = std::max({n_IS_stage, perfModel->scheduleModel.getT_issue()});
    // IB_stage_OoO
    uint64_t n_IB_stage_OoO = n_uA_Issue;
    perfModel->IB_stage_OoO.set(n_IB_stage_OoO);
    // CSR
    uint64_t n_CSR;
    n_CSR = n_IB_stage_OoO + 1;
    perfModel->regModel.setXd(n_CSR);
    perfModel->clobberModel.setCb_inRd(n_CSR);
    // EX_stage_alu_NoB
    uint64_t n_EX_stage_alu_NoB = n_CSR;
    perfModel->EX_stage_alu_NoB = n_EX_stage_alu_NoB;
    // WB
    uint64_t n_WB;
    n_WB = n_EX_stage_alu_NoB + 1;
    perfModel->scheduleModel.setT_wb(n_WB);
    // WB_stage_NoB
    uint64_t n_WB_stage_NoB = n_WB;
    perfModel->WB_stage_NoB.set(n_WB_stage_NoB);

    // Dump Entrance point for info print (tracing)
    perfModel->entrancePoint = n_Enter;
}

inline void Store(PerformanceModel* perfModel_) {
    RV32_OOO_PerformanceModel* perfModel = static_cast<RV32_OOO_PerformanceModel*>(perfModel_);
    // Enter
    uint64_t n_Enter = perfModel->PC_stage;
    // PCGen
    uint64_t n_PCGen;
    uint64_t n_PCGen_max;
    n_PCGen_max = std::max({n_Enter, perfModel->noBranchPredModel.getPc()});
    n_PCGen = n_PCGen_max + 1;
    perfModel->noBranchPredModel.setPc_p(n_PCGen);
    // PC_stage
    uint64_t n_PC_stage;
    n_PC_stage = std::max({n_PCGen, perfModel->IF_stage});
    perfModel->PC_stage = n_PC_stage;
    // IPort_R
    uint64_t n_IPort_R;
    n_IPort_R = n_PC_stage + 1;
    // IF_stage
    uint64_t n_IF_stage;
    n_IF_stage = std::max({n_IPort_R, perfModel->IS_stage});
    perfModel->IF_stage = n_IF_stage;
    // Decoder
    uint64_t n_Decoder;
    n_Decoder = n_IF_stage + 1;
    perfModel->scheduleModel.setDec_st(n_Decoder);
    // IS_stage
    uint64_t n_IS_stage;
    n_IS_stage = std::max({n_Decoder, perfModel->IB_stage_OoO.get(4)});
    perfModel->IS_stage = n_IS_stage;
    // uA_OF_A
    uint64_t n_uA_OF_A;
    n_uA_OF_A = std::max({n_IS_stage, perfModel->regModel.getXa()});
    // uA_OF_B
    uint64_t n_uA_OF_B;
    n_uA_OF_B = std::max({n_IS_stage, perfModel->regModel.getXb()});
    // uA_Issue
    uint64_t n_uA_Issue;
    n_uA_Issue = std::max({n_IS_stage, perfModel->scheduleModel.getT_issue()});
    // IB_stage_OoO
    uint64_t n_IB_stage_OoO;
    n_IB_stage_OoO = std::max({n_uA_OF_A, n_uA_OF_B, n_uA_Issue});
    perfModel->IB_stage_OoO.set(n_IB_stage_OoO);
    // DPort_W
    uint64_t n_DPort_W;
    n_DPort_W = n_IB_stage_OoO + 1;
    perfModel->clobberModel.setCb_inR1(n_DPort_W);
    perfModel->clobberModel.setCb_inR2(n_DPort_W);
    // EX_stage_lsu_NoB
    uint64_t n_EX_stage_lsu_NoB = n_DPort_W;
    perfModel->EX_stage_lsu_NoB.set(n_EX_stage_lsu_NoB);
    perfModel->EX_stage_suv_NoB = n_EX_stage_lsu_NoB;
    // WB
    uint64_t n_WB;
    n_WB = n_EX_stage_lsu_NoB + 1;
    perfModel->scheduleModel.setT_wb(n_WB);
    // WB_stage_NoB
    uint64_t n_WB_stage_NoB = n_WB;
    perfModel->WB_stage_NoB.set(n_WB_stage_NoB);

    // Dump Entrance point for info print (tracing)
    perfModel->entrancePoint = n_Enter;
}

inline void Load(PerformanceModel* perfModel_) {
    RV32_OOO_PerformanceModel* perfModel = static_cast<RV32_OOO_PerformanceModel*>(perfModel_);
    // Enter
    uint64_t n_Enter = perfModel->PC_stage;
    // PCGen
    uint64_t n_PCGen;
    uint64_t n_PCGen_max;
    n_PCGen_max = std::max({n_Enter, perfModel->noBranchPredModel.getPc()});
    n_PCGen = n_PCGen_max + 1;
    perfModel->noBranchPredModel.setPc_p(n_PCGen);
    // PC_stage
    uint64_t n_PC_stage;
    n_PC_stage = std::max({n_PCGen, perfModel->IF_stage});
    perfModel->PC_stage = n_PC_stage;
    // IPort_R
    uint64_t n_IPort_R;
    n_IPort_R = n_PC_stage + 1;
    // uA_Clobber
    uint64_t n_uA_Clobber;
    n_uA_Clobber = std::max({n_PC_stage, perfModel->clobberModel.getCb_out()});
    // IF_stage
    uint64_t n_IF_stage;
    n_IF_stage = std::max({n_IPort_R, n_uA_Clobber, perfModel->IS_stage});
    perfModel->IF_stage = n_IF_stage;
    // Decoder
    uint64_t n_Decoder;
    n_Decoder = n_IF_stage + 1;
    perfModel->scheduleModel.setDec_ld(n_Decoder);
    // IS_stage
    uint64_t n_IS_stage;
    n_IS_stage = std::max({n_Decoder, perfModel->IB_stage_OoO.get(4)});
    perfModel->IS_stage = n_IS_stage;
    // uA_OF_A
    uint64_t n_uA_OF_A;
    n_uA_OF_A = std::max({n_IS_stage, perfModel->regModel.getXa()});
    // uA_Issue
    uint64_t n_uA_Issue;
    n_uA_Issue = std::max({n_IS_stage, perfModel->scheduleModel.getT_issue()});
    // IB_stage_OoO
    uint64_t n_IB_stage_OoO;
    n_IB_stage_OoO = std::max({n_uA_OF_A, n_uA_Issue});
    perfModel->IB_stage_OoO.set(n_IB_stage_OoO);
    // LSU
    uint64_t n_LSU;
    n_LSU = n_IB_stage_OoO + 1;
    // EX_stage_lu0v_NoB
    uint64_t n_EX_stage_lu0v_NoB = n_LSU;
    perfModel->EX_stage_lu0v_NoB = n_EX_stage_lu0v_NoB;
    // DPort_R
    uint64_t n_DPort_R;
    n_DPort_R = n_EX_stage_lu0v_NoB + 1;
    perfModel->regModel.setXd(n_DPort_R);
    perfModel->clobberModel.setCb_inRd(n_DPort_R);
    // EX_stage_lsu_NoB
    uint64_t n_EX_stage_lsu_NoB = n_DPort_R;
    perfModel->EX_stage_lsu_NoB.set(n_EX_stage_lsu_NoB);
    perfModel->EX_stage_lu1v_NoB = n_EX_stage_lsu_NoB;
    // WB
    uint64_t n_WB;
    n_WB = n_EX_stage_lsu_NoB + 1;
    perfModel->scheduleModel.setT_wb(n_WB);
    // WB_stage_NoB
    uint64_t n_WB_stage_NoB = n_WB;
    perfModel->WB_stage_NoB.set(n_WB_stage_NoB);

    // Dump Entrance point for info print (tracing)
    perfModel->entrancePoint = n_Enter;
}

inline void Branch_Ra_Rb(PerformanceModel* perfModel_) {
    RV32_OOO_PerformanceModel* perfModel = static_cast<RV32_OOO_PerformanceModel*>(perfModel_);
    // Enter
    uint64_t n_Enter = perfModel->PC_stage;
    // PCGen
    uint64_t n_PCGen;
    uint64_t n_PCGen_max;
    n_PCGen_max = std::max({n_Enter, perfModel->noBranchPredModel.getPc()});
    n_PCGen = n_PCGen_max + 1;
    perfModel->noBranchPredModel.setPc_p(n_PCGen);
    // PC_stage
    uint64_t n_PC_stage;
    n_PC_stage = std::max({n_PCGen, perfModel->IF_stage});
    perfModel->PC_stage = n_PC_stage;
    // IPort_R
    uint64_t n_IPort_R;
    n_IPort_R = n_PC_stage + 1;
    // IF_stage
    uint64_t n_IF_stage;
    n_IF_stage = std::max({n_IPort_R, perfModel->IS_stage});
    perfModel->IF_stage = n_IF_stage;
    // Decoder
    uint64_t n_Decoder;
    n_Decoder = n_IF_stage + 1;
    perfModel->scheduleModel.setDec_br(n_Decoder);
    // IS_stage
    uint64_t n_IS_stage;
    n_IS_stage = std::max({n_Decoder, perfModel->IB_stage_OoO.get(4)});
    perfModel->IS_stage = n_IS_stage;
    // uA_OF_A
    uint64_t n_uA_OF_A;
    n_uA_OF_A = std::max({n_IS_stage, perfModel->regModel.getXa()});
    // uA_OF_B
    uint64_t n_uA_OF_B;
    n_uA_OF_B = std::max({n_IS_stage, perfModel->regModel.getXb()});
    // uA_Issue
    uint64_t n_uA_Issue;
    n_uA_Issue = std::max({n_IS_stage, perfModel->scheduleModel.getT_issue()});
    // IB_stage_OoO
    uint64_t n_IB_stage_OoO;
    n_IB_stage_OoO = std::max({n_uA_OF_A, n_uA_OF_B, n_uA_Issue});
    perfModel->IB_stage_OoO.set(n_IB_stage_OoO);
    // ADD
    uint64_t n_ADD;
    n_ADD = n_IB_stage_OoO + 1;
    perfModel->noBranchPredModel.setPc_np(n_ADD);
    perfModel->clobberModel.setCb_inR1(n_ADD);
    perfModel->clobberModel.setCb_inR2(n_ADD);
    // EX_stage_br_NoB
    uint64_t n_EX_stage_br_NoB = n_ADD;
    perfModel->EX_stage_br_NoB = n_EX_stage_br_NoB;
    // WB
    uint64_t n_WB;
    n_WB = n_EX_stage_br_NoB + 1;
    perfModel->scheduleModel.setT_wb(n_WB);
    // WB_stage_NoB
    uint64_t n_WB_stage_NoB = n_WB;
    perfModel->WB_stage_NoB.set(n_WB_stage_NoB);

    // Dump Entrance point for info print (tracing)
    perfModel->entrancePoint = n_Enter;
}

inline void Default_Inst(PerformanceModel* perfModel_) {
    RV32_OOO_PerformanceModel* perfModel = static_cast<RV32_OOO_PerformanceModel*>(perfModel_);
    // Enter
    uint64_t n_Enter = perfModel->PC_stage;
    // PCGen
    uint64_t n_PCGen;
    uint64_t n_PCGen_max;
    n_PCGen_max = std::max({n_Enter, perfModel->noBranchPredModel.getPc()});
    n_PCGen = n_PCGen_max + 1;
    perfModel->noBranchPredModel.setPc_p(n_PCGen);
    // PC_stage
    uint64_t n_PC_stage;
    n_PC_stage = std::max({n_PCGen, perfModel->IF_stage});
    perfModel->PC_stage = n_PC_stage;
    // IPort_R
    uint64_t n_IPort_R;
    n_IPort_R = n_PC_stage + 1;
    // IF_stage
    uint64_t n_IF_stage = n_IPort_R;
    perfModel->IF_stage = n_IF_stage;

    // Dump Entrance point for info print (tracing)
    perfModel->entrancePoint = n_Enter;
}

inline void JAL(PerformanceModel* perfModel_) {
    RV32_OOO_PerformanceModel* perfModel = static_cast<RV32_OOO_PerformanceModel*>(perfModel_);
    // Enter
    uint64_t n_Enter = perfModel->PC_stage;
    // PCGen
    uint64_t n_PCGen;
    uint64_t n_PCGen_max;
    n_PCGen_max = std::max({n_Enter, perfModel->noBranchPredModel.getPc()});
    n_PCGen = n_PCGen_max + 1;
    perfModel->noBranchPredModel.setPc_p(n_PCGen);
    // PC_stage
    uint64_t n_PC_stage;
    n_PC_stage = std::max({n_PCGen, perfModel->IF_stage});
    perfModel->PC_stage = n_PC_stage;
    // IPort_R
    uint64_t n_IPort_R;
    n_IPort_R = n_PC_stage + 1;
    // uA_Clobber
    uint64_t n_uA_Clobber;
    n_uA_Clobber = std::max({n_PC_stage, perfModel->clobberModel.getCb_out()});
    // IF_stage
    uint64_t n_IF_stage;
    n_IF_stage = std::max({n_IPort_R, n_uA_Clobber, perfModel->IS_stage});
    perfModel->IF_stage = n_IF_stage;
    // JumpDecoder
    uint64_t n_JumpDecoder;
    n_JumpDecoder = n_IF_stage + 1;
    perfModel->noBranchPredModel.setPc_np(n_JumpDecoder);
    perfModel->scheduleModel.setDec_br(n_JumpDecoder);
    // IS_stage
    uint64_t n_IS_stage;
    n_IS_stage = std::max({n_JumpDecoder, perfModel->IB_stage_OoO.get(4)});
    perfModel->IS_stage = n_IS_stage;
    // uA_Issue
    uint64_t n_uA_Issue;
    n_uA_Issue = std::max({n_IS_stage, perfModel->scheduleModel.getT_issue()});
    // IB_stage_OoO
    uint64_t n_IB_stage_OoO = n_uA_Issue;
    perfModel->IB_stage_OoO.set(n_IB_stage_OoO);
    // ADD
    uint64_t n_ADD;
    n_ADD = n_IB_stage_OoO + 1;
    perfModel->regModel.setXd(n_ADD);
    perfModel->clobberModel.setCb_inRd(n_ADD);
    // EX_stage_br_NoB
    uint64_t n_EX_stage_br_NoB = n_ADD;
    perfModel->EX_stage_br_NoB = n_EX_stage_br_NoB;
    // WB
    uint64_t n_WB;
    n_WB = n_EX_stage_br_NoB + 1;
    perfModel->scheduleModel.setT_wb(n_WB);
    // WB_stage_NoB
    uint64_t n_WB_stage_NoB = n_WB;
    perfModel->WB_stage_NoB.set(n_WB_stage_NoB);

    // Dump Entrance point for info print (tracing)
    perfModel->entrancePoint = n_Enter;
}

inline void JALR(PerformanceModel* perfModel_) {
    RV32_OOO_PerformanceModel* perfModel = static_cast<RV32_OOO_PerformanceModel*>(perfModel_);
    // Enter
    uint64_t n_Enter = perfModel->PC_stage;
    // PCGen
    uint64_t n_PCGen;
    uint64_t n_PCGen_max;
    n_PCGen_max = std::max({n_Enter, perfModel->noBranchPredModel.getPc()});
    n_PCGen = n_PCGen_max + 1;
    perfModel->noBranchPredModel.setPc_p(n_PCGen);
    // PC_stage
    uint64_t n_PC_stage;
    n_PC_stage = std::max({n_PCGen, perfModel->IF_stage});
    perfModel->PC_stage = n_PC_stage;
    // IPort_R
    uint64_t n_IPort_R;
    n_IPort_R = n_PC_stage + 1;
    // uA_Clobber
    uint64_t n_uA_Clobber;
    n_uA_Clobber = std::max({n_PC_stage, perfModel->clobberModel.getCb_out()});
    // IF_stage
    uint64_t n_IF_stage;
    n_IF_stage = std::max({n_IPort_R, n_uA_Clobber, perfModel->IS_stage});
    perfModel->IF_stage = n_IF_stage;
    // JumpDecoder
    uint64_t n_JumpDecoder;
    uint64_t n_JumpDecoder_max;
    n_JumpDecoder_max = std::max({n_IF_stage, perfModel->regModel.getXa()});
    n_JumpDecoder = n_JumpDecoder_max + 1;
    perfModel->noBranchPredModel.setPc_np(n_JumpDecoder);
    perfModel->scheduleModel.setDec_br(n_JumpDecoder);
    // IS_stage
    uint64_t n_IS_stage;
    n_IS_stage = std::max({n_JumpDecoder, perfModel->IB_stage_OoO.get(4)});
    perfModel->IS_stage = n_IS_stage;
    // uA_Issue
    uint64_t n_uA_Issue;
    n_uA_Issue = std::max({n_IS_stage, perfModel->scheduleModel.getT_issue()});
    // IB_stage_OoO
    uint64_t n_IB_stage_OoO = n_uA_Issue;
    perfModel->IB_stage_OoO.set(n_IB_stage_OoO);
    // ADD
    uint64_t n_ADD;
    n_ADD = n_IB_stage_OoO + 1;
    perfModel->regModel.setXd(n_ADD);
    perfModel->clobberModel.setCb_inRd(n_ADD);
    perfModel->clobberModel.setCb_inR1(n_ADD);
    // EX_stage_br_NoB
    uint64_t n_EX_stage_br_NoB = n_ADD;
    perfModel->EX_stage_br_NoB = n_EX_stage_br_NoB;
    // WB
    uint64_t n_WB;
    n_WB = n_EX_stage_br_NoB + 1;
    perfModel->scheduleModel.setT_wb(n_WB);
    // WB_stage_NoB
    uint64_t n_WB_stage_NoB = n_WB;
    perfModel->WB_stage_NoB.set(n_WB_stage_NoB);

    // Dump Entrance point for info print (tracing)
    perfModel->entrancePoint = n_Enter;
}

}  // namespace RV32_OOO