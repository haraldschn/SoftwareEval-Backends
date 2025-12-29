#include <algorithm>
#include <cstdint>

#include "PerformanceModel.h"

#include "CVA6_PerformanceModel.h"

namespace CVA6 {

inline void Default_Inst(PerformanceModel* perfModel_) {
    CVA6_PerformanceModel* perfModel = static_cast<CVA6_PerformanceModel*>(perfModel_);
    // Enter
    uint64_t n_Enter = perfModel->PC_stage;
    // PCGen
    uint64_t n_PCGen;
    n_PCGen = n_Enter + 1;
    // uA_PcCorrect
    uint64_t n_uA_PcCorrect;
    n_uA_PcCorrect = std::max({n_Enter, perfModel->dynBranchPredModel.getPc_mp()});
    // uA_CacheBlock
    uint64_t n_uA_CacheBlock;
    n_uA_CacheBlock = std::max({n_Enter, perfModel->iCacheModel.getIc_out()});
    // PC_stage
    uint64_t n_PC_stage;
    n_PC_stage = std::max({n_PCGen, n_uA_PcCorrect, n_uA_CacheBlock, perfModel->IF_stage.get(3), perfModel->IF_substage_0});
    perfModel->PC_stage = n_PC_stage;
    // ICacheCtrl
    uint64_t n_ICacheCtrl;
    n_ICacheCtrl = n_PC_stage + 1;
    // uA_PcPredict
    uint64_t n_uA_PcPredict;
    n_uA_PcPredict = std::max({n_PC_stage, perfModel->dynBranchPredModel.getPc_pt()});
    // IF_substage_0
    uint64_t n_IF_substage_0;
    n_IF_substage_0 = std::max({n_ICacheCtrl, n_uA_PcPredict, perfModel->IF_substage_1});
    perfModel->IF_substage_0 = n_IF_substage_0;
    // ICache
    uint64_t n_ICache;
    n_ICache = n_IF_substage_0 + perfModel->iCacheModel.getDelay();
    perfModel->iCacheModel.setIc_in(n_ICache);
    // IF_substage_1
    uint64_t n_IF_substage_1;
    n_IF_substage_1 = std::max({n_ICache, perfModel->IF_substage_2});
    perfModel->IF_substage_1 = n_IF_substage_1;
    // IScan
    uint64_t n_IScan;
    n_IScan = n_IF_substage_1 + 1;
    // IF_stage
    uint64_t n_IF_stage;
    n_IF_stage = std::max({n_IScan, perfModel->IF_stage.get(1), perfModel->IQ_stage.get(7)});
    perfModel->IF_stage.set(n_IF_stage);
    perfModel->IF_substage_2 = n_IF_stage;
    // IQInsert
    uint64_t n_IQInsert;
    n_IQInsert = n_IF_stage + 1;
    // IQ_stage
    uint64_t n_IQ_stage;
    n_IQ_stage = std::max({n_IQInsert, perfModel->IQ_stage.get(1), perfModel->ID_stage});
    perfModel->IQ_stage.set(n_IQ_stage);
    // Decoder
    uint64_t n_Decoder;
    n_Decoder = n_IQ_stage + 1;
    // ID_stage
    uint64_t n_ID_stage;
    n_ID_stage = std::max({n_Decoder, perfModel->IS_stage});
    perfModel->ID_stage = n_ID_stage;
    // Issue
    uint64_t n_Issue = n_ID_stage;
    // IS_stage
    uint64_t n_IS_stage;
    n_IS_stage = std::max({n_Issue, perfModel->EX_stage.get(8), perfModel->EX_substage_alu, perfModel->EX_substage_mul_o, perfModel->EX_substage_div});
    perfModel->IS_stage = n_IS_stage;
    // ALU
    uint64_t n_ALU;
    n_ALU = n_IS_stage + 1;
    // EX_substage_alu
    uint64_t n_EX_substage_alu = n_ALU;
    perfModel->EX_substage_alu = n_EX_substage_alu;
    // EX_stage
    uint64_t n_EX_stage;
    n_EX_stage = std::max({n_EX_substage_alu, perfModel->EX_stage.get(1), perfModel->COM_stage.get(2)});
    perfModel->EX_stage.set(n_EX_stage);
    // Commit
    uint64_t n_Commit;
    n_Commit = n_EX_stage + 1;
    // COM_stage
    uint64_t n_COM_stage;
    n_COM_stage = std::max({n_Commit, perfModel->COM_stage.get(1)});
    perfModel->COM_stage.set(n_COM_stage);

    // Dump Entrance point for info print (tracing)
    perfModel->entrancePoint = n_Enter;
}

inline void Arith_0(PerformanceModel* perfModel_) {
    CVA6_PerformanceModel* perfModel = static_cast<CVA6_PerformanceModel*>(perfModel_);
    // Enter
    uint64_t n_Enter = perfModel->PC_stage;
    // PCGen
    uint64_t n_PCGen;
    n_PCGen = n_Enter + 1;
    // uA_PcCorrect
    uint64_t n_uA_PcCorrect;
    n_uA_PcCorrect = std::max({n_Enter, perfModel->dynBranchPredModel.getPc_mp()});
    // uA_CacheBlock
    uint64_t n_uA_CacheBlock;
    n_uA_CacheBlock = std::max({n_Enter, perfModel->iCacheModel.getIc_out()});
    // PC_stage
    uint64_t n_PC_stage;
    n_PC_stage = std::max({n_PCGen, n_uA_PcCorrect, n_uA_CacheBlock, perfModel->IF_stage.get(3), perfModel->IF_substage_0});
    perfModel->PC_stage = n_PC_stage;
    // ICacheCtrl
    uint64_t n_ICacheCtrl;
    n_ICacheCtrl = n_PC_stage + 1;
    // uA_PcPredict
    uint64_t n_uA_PcPredict;
    n_uA_PcPredict = std::max({n_PC_stage, perfModel->dynBranchPredModel.getPc_pt()});
    // IF_substage_0
    uint64_t n_IF_substage_0;
    n_IF_substage_0 = std::max({n_ICacheCtrl, n_uA_PcPredict, perfModel->IF_substage_1});
    perfModel->IF_substage_0 = n_IF_substage_0;
    // ICache
    uint64_t n_ICache;
    n_ICache = n_IF_substage_0 + perfModel->iCacheModel.getDelay();
    perfModel->iCacheModel.setIc_in(n_ICache);
    // IF_substage_1
    uint64_t n_IF_substage_1;
    n_IF_substage_1 = std::max({n_ICache, perfModel->IF_substage_2});
    perfModel->IF_substage_1 = n_IF_substage_1;
    // IScan
    uint64_t n_IScan;
    n_IScan = n_IF_substage_1 + 1;
    // IF_stage
    uint64_t n_IF_stage;
    n_IF_stage = std::max({n_IScan, perfModel->IF_stage.get(1), perfModel->IQ_stage.get(7)});
    perfModel->IF_stage.set(n_IF_stage);
    perfModel->IF_substage_2 = n_IF_stage;
    // IQInsert
    uint64_t n_IQInsert;
    n_IQInsert = n_IF_stage + 1;
    // IQ_stage
    uint64_t n_IQ_stage;
    n_IQ_stage = std::max({n_IQInsert, perfModel->IQ_stage.get(1), perfModel->ID_stage});
    perfModel->IQ_stage.set(n_IQ_stage);
    // Decoder
    uint64_t n_Decoder;
    n_Decoder = n_IQ_stage + 1;
    // ID_stage
    uint64_t n_ID_stage;
    n_ID_stage = std::max({n_Decoder, perfModel->IS_stage});
    perfModel->ID_stage = n_ID_stage;
    // Issue
    uint64_t n_Issue = n_ID_stage;
    // IS_stage
    uint64_t n_IS_stage;
    n_IS_stage = std::max({n_Issue, perfModel->EX_stage.get(8), perfModel->EX_substage_alu, perfModel->EX_substage_mul_o, perfModel->EX_substage_div});
    perfModel->IS_stage = n_IS_stage;
    // ALU
    uint64_t n_ALU;
    n_ALU = n_IS_stage + 1;
    perfModel->regModel.setXd(n_ALU);
    // EX_substage_alu
    uint64_t n_EX_substage_alu = n_ALU;
    perfModel->EX_substage_alu = n_EX_substage_alu;
    // EX_stage
    uint64_t n_EX_stage;
    n_EX_stage = std::max({n_EX_substage_alu, perfModel->EX_stage.get(1), perfModel->COM_stage.get(2)});
    perfModel->EX_stage.set(n_EX_stage);
    // Commit
    uint64_t n_Commit;
    n_Commit = n_EX_stage + 1;
    perfModel->clobberModel.setCb_in(n_Commit);
    // COM_stage
    uint64_t n_COM_stage;
    n_COM_stage = std::max({n_Commit, perfModel->COM_stage.get(1)});
    perfModel->COM_stage.set(n_COM_stage);

    // Dump Entrance point for info print (tracing)
    perfModel->entrancePoint = n_Enter;
}

inline void Arith_Rs1(PerformanceModel* perfModel_) {
    CVA6_PerformanceModel* perfModel = static_cast<CVA6_PerformanceModel*>(perfModel_);
    // Enter
    uint64_t n_Enter = perfModel->PC_stage;
    // PCGen
    uint64_t n_PCGen;
    n_PCGen = n_Enter + 1;
    // uA_PcCorrect
    uint64_t n_uA_PcCorrect;
    n_uA_PcCorrect = std::max({n_Enter, perfModel->dynBranchPredModel.getPc_mp()});
    // uA_CacheBlock
    uint64_t n_uA_CacheBlock;
    n_uA_CacheBlock = std::max({n_Enter, perfModel->iCacheModel.getIc_out()});
    // PC_stage
    uint64_t n_PC_stage;
    n_PC_stage = std::max({n_PCGen, n_uA_PcCorrect, n_uA_CacheBlock, perfModel->IF_stage.get(3), perfModel->IF_substage_0});
    perfModel->PC_stage = n_PC_stage;
    // ICacheCtrl
    uint64_t n_ICacheCtrl;
    n_ICacheCtrl = n_PC_stage + 1;
    // uA_PcPredict
    uint64_t n_uA_PcPredict;
    n_uA_PcPredict = std::max({n_PC_stage, perfModel->dynBranchPredModel.getPc_pt()});
    // IF_substage_0
    uint64_t n_IF_substage_0;
    n_IF_substage_0 = std::max({n_ICacheCtrl, n_uA_PcPredict, perfModel->IF_substage_1});
    perfModel->IF_substage_0 = n_IF_substage_0;
    // ICache
    uint64_t n_ICache;
    n_ICache = n_IF_substage_0 + perfModel->iCacheModel.getDelay();
    perfModel->iCacheModel.setIc_in(n_ICache);
    // IF_substage_1
    uint64_t n_IF_substage_1;
    n_IF_substage_1 = std::max({n_ICache, perfModel->IF_substage_2});
    perfModel->IF_substage_1 = n_IF_substage_1;
    // IScan
    uint64_t n_IScan;
    n_IScan = n_IF_substage_1 + 1;
    // IF_stage
    uint64_t n_IF_stage;
    n_IF_stage = std::max({n_IScan, perfModel->IF_stage.get(1), perfModel->IQ_stage.get(7)});
    perfModel->IF_stage.set(n_IF_stage);
    perfModel->IF_substage_2 = n_IF_stage;
    // IQInsert
    uint64_t n_IQInsert;
    n_IQInsert = n_IF_stage + 1;
    // IQ_stage
    uint64_t n_IQ_stage;
    n_IQ_stage = std::max({n_IQInsert, perfModel->IQ_stage.get(1), perfModel->ID_stage});
    perfModel->IQ_stage.set(n_IQ_stage);
    // Decoder
    uint64_t n_Decoder;
    n_Decoder = n_IQ_stage + 1;
    // ID_stage
    uint64_t n_ID_stage;
    n_ID_stage = std::max({n_Decoder, perfModel->IS_stage});
    perfModel->ID_stage = n_ID_stage;
    // Issue
    uint64_t n_Issue = n_ID_stage;
    // uA_Clobber
    uint64_t n_uA_Clobber;
    n_uA_Clobber = std::max({n_ID_stage, perfModel->clobberModel.getCb_out()});
    // uA_OF_A
    uint64_t n_uA_OF_A;
    n_uA_OF_A = std::max({n_ID_stage, perfModel->regModel.getXa()});
    // IS_stage
    uint64_t n_IS_stage;
    n_IS_stage = std::max({n_Issue, n_uA_Clobber, n_uA_OF_A, perfModel->EX_stage.get(8), perfModel->EX_substage_alu, perfModel->EX_substage_mul_o, perfModel->EX_substage_div});
    perfModel->IS_stage = n_IS_stage;
    // ALU
    uint64_t n_ALU;
    n_ALU = n_IS_stage + 1;
    perfModel->regModel.setXd(n_ALU);
    // EX_substage_alu
    uint64_t n_EX_substage_alu = n_ALU;
    perfModel->EX_substage_alu = n_EX_substage_alu;
    // EX_stage
    uint64_t n_EX_stage;
    n_EX_stage = std::max({n_EX_substage_alu, perfModel->EX_stage.get(1), perfModel->COM_stage.get(2)});
    perfModel->EX_stage.set(n_EX_stage);
    // Commit
    uint64_t n_Commit;
    n_Commit = n_EX_stage + 1;
    perfModel->clobberModel.setCb_in(n_Commit);
    // COM_stage
    uint64_t n_COM_stage;
    n_COM_stage = std::max({n_Commit, perfModel->COM_stage.get(1)});
    perfModel->COM_stage.set(n_COM_stage);

    // Dump Entrance point for info print (tracing)
    perfModel->entrancePoint = n_Enter;
}

inline void Arith_Rs1_Rs2(PerformanceModel* perfModel_) {
    CVA6_PerformanceModel* perfModel = static_cast<CVA6_PerformanceModel*>(perfModel_);
    // Enter
    uint64_t n_Enter = perfModel->PC_stage;
    // PCGen
    uint64_t n_PCGen;
    n_PCGen = n_Enter + 1;
    // uA_PcCorrect
    uint64_t n_uA_PcCorrect;
    n_uA_PcCorrect = std::max({n_Enter, perfModel->dynBranchPredModel.getPc_mp()});
    // uA_CacheBlock
    uint64_t n_uA_CacheBlock;
    n_uA_CacheBlock = std::max({n_Enter, perfModel->iCacheModel.getIc_out()});
    // PC_stage
    uint64_t n_PC_stage;
    n_PC_stage = std::max({n_PCGen, n_uA_PcCorrect, n_uA_CacheBlock, perfModel->IF_stage.get(3), perfModel->IF_substage_0});
    perfModel->PC_stage = n_PC_stage;
    // ICacheCtrl
    uint64_t n_ICacheCtrl;
    n_ICacheCtrl = n_PC_stage + 1;
    // uA_PcPredict
    uint64_t n_uA_PcPredict;
    n_uA_PcPredict = std::max({n_PC_stage, perfModel->dynBranchPredModel.getPc_pt()});
    // IF_substage_0
    uint64_t n_IF_substage_0;
    n_IF_substage_0 = std::max({n_ICacheCtrl, n_uA_PcPredict, perfModel->IF_substage_1});
    perfModel->IF_substage_0 = n_IF_substage_0;
    // ICache
    uint64_t n_ICache;
    n_ICache = n_IF_substage_0 + perfModel->iCacheModel.getDelay();
    perfModel->iCacheModel.setIc_in(n_ICache);
    // IF_substage_1
    uint64_t n_IF_substage_1;
    n_IF_substage_1 = std::max({n_ICache, perfModel->IF_substage_2});
    perfModel->IF_substage_1 = n_IF_substage_1;
    // IScan
    uint64_t n_IScan;
    n_IScan = n_IF_substage_1 + 1;
    // IF_stage
    uint64_t n_IF_stage;
    n_IF_stage = std::max({n_IScan, perfModel->IF_stage.get(1), perfModel->IQ_stage.get(7)});
    perfModel->IF_stage.set(n_IF_stage);
    perfModel->IF_substage_2 = n_IF_stage;
    // IQInsert
    uint64_t n_IQInsert;
    n_IQInsert = n_IF_stage + 1;
    // IQ_stage
    uint64_t n_IQ_stage;
    n_IQ_stage = std::max({n_IQInsert, perfModel->IQ_stage.get(1), perfModel->ID_stage});
    perfModel->IQ_stage.set(n_IQ_stage);
    // Decoder
    uint64_t n_Decoder;
    n_Decoder = n_IQ_stage + 1;
    // ID_stage
    uint64_t n_ID_stage;
    n_ID_stage = std::max({n_Decoder, perfModel->IS_stage});
    perfModel->ID_stage = n_ID_stage;
    // Issue
    uint64_t n_Issue = n_ID_stage;
    // uA_Clobber
    uint64_t n_uA_Clobber;
    n_uA_Clobber = std::max({n_ID_stage, perfModel->clobberModel.getCb_out()});
    // uA_OF_A
    uint64_t n_uA_OF_A;
    n_uA_OF_A = std::max({n_ID_stage, perfModel->regModel.getXa()});
    // uA_OF_B
    uint64_t n_uA_OF_B;
    n_uA_OF_B = std::max({n_ID_stage, perfModel->regModel.getXb()});
    // IS_stage
    uint64_t n_IS_stage;
    n_IS_stage = std::max({n_Issue, n_uA_Clobber, n_uA_OF_A, n_uA_OF_B, perfModel->EX_stage.get(8), perfModel->EX_substage_alu, perfModel->EX_substage_mul_o, perfModel->EX_substage_div});
    perfModel->IS_stage = n_IS_stage;
    // ALU
    uint64_t n_ALU;
    n_ALU = n_IS_stage + 1;
    perfModel->regModel.setXd(n_ALU);
    // EX_substage_alu
    uint64_t n_EX_substage_alu = n_ALU;
    perfModel->EX_substage_alu = n_EX_substage_alu;
    // EX_stage
    uint64_t n_EX_stage;
    n_EX_stage = std::max({n_EX_substage_alu, perfModel->EX_stage.get(1), perfModel->COM_stage.get(2)});
    perfModel->EX_stage.set(n_EX_stage);
    // Commit
    uint64_t n_Commit;
    n_Commit = n_EX_stage + 1;
    perfModel->clobberModel.setCb_in(n_Commit);
    // COM_stage
    uint64_t n_COM_stage;
    n_COM_stage = std::max({n_Commit, perfModel->COM_stage.get(1)});
    perfModel->COM_stage.set(n_COM_stage);

    // Dump Entrance point for info print (tracing)
    perfModel->entrancePoint = n_Enter;
}

inline void Branch(PerformanceModel* perfModel_) {
    CVA6_PerformanceModel* perfModel = static_cast<CVA6_PerformanceModel*>(perfModel_);
    // Enter
    uint64_t n_Enter = perfModel->PC_stage;
    // PCGen
    uint64_t n_PCGen;
    n_PCGen = n_Enter + 1;
    // uA_PcCorrect
    uint64_t n_uA_PcCorrect;
    n_uA_PcCorrect = std::max({n_Enter, perfModel->dynBranchPredModel.getPc_mp()});
    // uA_CacheBlock
    uint64_t n_uA_CacheBlock;
    n_uA_CacheBlock = std::max({n_Enter, perfModel->iCacheModel.getIc_out()});
    // PC_stage
    uint64_t n_PC_stage;
    n_PC_stage = std::max({n_PCGen, n_uA_PcCorrect, n_uA_CacheBlock, perfModel->IF_stage.get(3), perfModel->IF_substage_0});
    perfModel->PC_stage = n_PC_stage;
    // ICacheCtrl
    uint64_t n_ICacheCtrl;
    n_ICacheCtrl = n_PC_stage + 1;
    // uA_PcPredict
    uint64_t n_uA_PcPredict;
    n_uA_PcPredict = std::max({n_PC_stage, perfModel->dynBranchPredModel.getPc_pt()});
    // IF_substage_0
    uint64_t n_IF_substage_0;
    n_IF_substage_0 = std::max({n_ICacheCtrl, n_uA_PcPredict, perfModel->IF_substage_1});
    perfModel->IF_substage_0 = n_IF_substage_0;
    // ICache
    uint64_t n_ICache;
    n_ICache = n_IF_substage_0 + perfModel->iCacheModel.getDelay();
    perfModel->iCacheModel.setIc_in(n_ICache);
    // IF_substage_1
    uint64_t n_IF_substage_1;
    n_IF_substage_1 = std::max({n_ICache, perfModel->IF_substage_2});
    perfModel->IF_substage_1 = n_IF_substage_1;
    // IScan
    uint64_t n_IScan;
    n_IScan = n_IF_substage_1 + 1;
    perfModel->dynBranchPredModel.setPc_p(n_IScan);
    // IF_stage
    uint64_t n_IF_stage;
    n_IF_stage = std::max({n_IScan, perfModel->IF_stage.get(1), perfModel->IQ_stage.get(7)});
    perfModel->IF_stage.set(n_IF_stage);
    perfModel->IF_substage_2 = n_IF_stage;
    // IQInsert
    uint64_t n_IQInsert;
    n_IQInsert = n_IF_stage + 1;
    // IQ_stage
    uint64_t n_IQ_stage;
    n_IQ_stage = std::max({n_IQInsert, perfModel->IQ_stage.get(1), perfModel->ID_stage});
    perfModel->IQ_stage.set(n_IQ_stage);
    // Decoder
    uint64_t n_Decoder;
    n_Decoder = n_IQ_stage + 1;
    // ID_stage
    uint64_t n_ID_stage;
    n_ID_stage = std::max({n_Decoder, perfModel->IS_stage});
    perfModel->ID_stage = n_ID_stage;
    // Issue
    uint64_t n_Issue = n_ID_stage;
    // uA_OF_A
    uint64_t n_uA_OF_A;
    n_uA_OF_A = std::max({n_ID_stage, perfModel->regModel.getXa()});
    // uA_OF_B
    uint64_t n_uA_OF_B;
    n_uA_OF_B = std::max({n_ID_stage, perfModel->regModel.getXb()});
    // IS_stage
    uint64_t n_IS_stage;
    n_IS_stage = std::max({n_Issue, n_uA_OF_A, n_uA_OF_B, perfModel->EX_stage.get(8), perfModel->EX_substage_alu, perfModel->EX_substage_mul_o, perfModel->EX_substage_div});
    perfModel->IS_stage = n_IS_stage;
    // ALU
    uint64_t n_ALU;
    n_ALU = n_IS_stage + 1;
    perfModel->dynBranchPredModel.setPc_c(n_ALU);
    // EX_substage_alu
    uint64_t n_EX_substage_alu = n_ALU;
    perfModel->EX_substage_alu = n_EX_substage_alu;
    // EX_stage
    uint64_t n_EX_stage;
    n_EX_stage = std::max({n_EX_substage_alu, perfModel->EX_stage.get(1), perfModel->COM_stage.get(2)});
    perfModel->EX_stage.set(n_EX_stage);
    // Commit
    uint64_t n_Commit;
    n_Commit = n_EX_stage + 1;
    // COM_stage
    uint64_t n_COM_stage;
    n_COM_stage = std::max({n_Commit, perfModel->COM_stage.get(1)});
    perfModel->COM_stage.set(n_COM_stage);

    // Dump Entrance point for info print (tracing)
    perfModel->entrancePoint = n_Enter;
}

inline void Jump(PerformanceModel* perfModel_) {
    CVA6_PerformanceModel* perfModel = static_cast<CVA6_PerformanceModel*>(perfModel_);
    // Enter
    uint64_t n_Enter = perfModel->PC_stage;
    // PCGen
    uint64_t n_PCGen;
    n_PCGen = n_Enter + 1;
    // uA_PcCorrect
    uint64_t n_uA_PcCorrect;
    n_uA_PcCorrect = std::max({n_Enter, perfModel->dynBranchPredModel.getPc_mp()});
    // uA_CacheBlock
    uint64_t n_uA_CacheBlock;
    n_uA_CacheBlock = std::max({n_Enter, perfModel->iCacheModel.getIc_out()});
    // PC_stage
    uint64_t n_PC_stage;
    n_PC_stage = std::max({n_PCGen, n_uA_PcCorrect, n_uA_CacheBlock, perfModel->IF_stage.get(3), perfModel->IF_substage_0});
    perfModel->PC_stage = n_PC_stage;
    // ICacheCtrl
    uint64_t n_ICacheCtrl;
    n_ICacheCtrl = n_PC_stage + 1;
    // uA_PcPredict
    uint64_t n_uA_PcPredict;
    n_uA_PcPredict = std::max({n_PC_stage, perfModel->dynBranchPredModel.getPc_pt()});
    // IF_substage_0
    uint64_t n_IF_substage_0;
    n_IF_substage_0 = std::max({n_ICacheCtrl, n_uA_PcPredict, perfModel->IF_substage_1});
    perfModel->IF_substage_0 = n_IF_substage_0;
    // ICache
    uint64_t n_ICache;
    n_ICache = n_IF_substage_0 + perfModel->iCacheModel.getDelay();
    perfModel->iCacheModel.setIc_in(n_ICache);
    // IF_substage_1
    uint64_t n_IF_substage_1;
    n_IF_substage_1 = std::max({n_ICache, perfModel->IF_substage_2});
    perfModel->IF_substage_1 = n_IF_substage_1;
    // IScan
    uint64_t n_IScan;
    n_IScan = n_IF_substage_1 + 1;
    perfModel->dynBranchPredModel.setPc_p_j(n_IScan);
    // IF_stage
    uint64_t n_IF_stage;
    n_IF_stage = std::max({n_IScan, perfModel->IF_stage.get(1), perfModel->IQ_stage.get(7)});
    perfModel->IF_stage.set(n_IF_stage);
    perfModel->IF_substage_2 = n_IF_stage;
    // IQInsert
    uint64_t n_IQInsert;
    n_IQInsert = n_IF_stage + 1;
    // IQ_stage
    uint64_t n_IQ_stage;
    n_IQ_stage = std::max({n_IQInsert, perfModel->IQ_stage.get(1), perfModel->ID_stage});
    perfModel->IQ_stage.set(n_IQ_stage);
    // Decoder
    uint64_t n_Decoder;
    n_Decoder = n_IQ_stage + 1;
    // ID_stage
    uint64_t n_ID_stage;
    n_ID_stage = std::max({n_Decoder, perfModel->IS_stage});
    perfModel->ID_stage = n_ID_stage;
    // Issue
    uint64_t n_Issue = n_ID_stage;
    // uA_Clobber
    uint64_t n_uA_Clobber;
    n_uA_Clobber = std::max({n_ID_stage, perfModel->clobberModel.getCb_out()});
    // IS_stage
    uint64_t n_IS_stage;
    n_IS_stage = std::max({n_Issue, n_uA_Clobber, perfModel->EX_stage.get(8), perfModel->EX_substage_alu, perfModel->EX_substage_mul_o, perfModel->EX_substage_div});
    perfModel->IS_stage = n_IS_stage;
    // ALU
    uint64_t n_ALU;
    n_ALU = n_IS_stage + 1;
    perfModel->regModel.setXd(n_ALU);
    // EX_substage_alu
    uint64_t n_EX_substage_alu = n_ALU;
    perfModel->EX_substage_alu = n_EX_substage_alu;
    // EX_stage
    uint64_t n_EX_stage;
    n_EX_stage = std::max({n_EX_substage_alu, perfModel->EX_stage.get(1), perfModel->COM_stage.get(2)});
    perfModel->EX_stage.set(n_EX_stage);
    // Commit
    uint64_t n_Commit;
    n_Commit = n_EX_stage + 1;
    perfModel->clobberModel.setCb_in(n_Commit);
    // COM_stage
    uint64_t n_COM_stage;
    n_COM_stage = std::max({n_Commit, perfModel->COM_stage.get(1)});
    perfModel->COM_stage.set(n_COM_stage);

    // Dump Entrance point for info print (tracing)
    perfModel->entrancePoint = n_Enter;
}

inline void JumpR(PerformanceModel* perfModel_) {
    CVA6_PerformanceModel* perfModel = static_cast<CVA6_PerformanceModel*>(perfModel_);
    // Enter
    uint64_t n_Enter = perfModel->PC_stage;
    // PCGen
    uint64_t n_PCGen;
    n_PCGen = n_Enter + 1;
    // uA_PcCorrect
    uint64_t n_uA_PcCorrect;
    n_uA_PcCorrect = std::max({n_Enter, perfModel->dynBranchPredModel.getPc_mp()});
    // uA_CacheBlock
    uint64_t n_uA_CacheBlock;
    n_uA_CacheBlock = std::max({n_Enter, perfModel->iCacheModel.getIc_out()});
    // PC_stage
    uint64_t n_PC_stage;
    n_PC_stage = std::max({n_PCGen, n_uA_PcCorrect, n_uA_CacheBlock, perfModel->IF_stage.get(3), perfModel->IF_substage_0});
    perfModel->PC_stage = n_PC_stage;
    // ICacheCtrl
    uint64_t n_ICacheCtrl;
    n_ICacheCtrl = n_PC_stage + 1;
    // uA_PcPredict
    uint64_t n_uA_PcPredict;
    n_uA_PcPredict = std::max({n_PC_stage, perfModel->dynBranchPredModel.getPc_pt()});
    // IF_substage_0
    uint64_t n_IF_substage_0;
    n_IF_substage_0 = std::max({n_ICacheCtrl, n_uA_PcPredict, perfModel->IF_substage_1});
    perfModel->IF_substage_0 = n_IF_substage_0;
    // ICache
    uint64_t n_ICache;
    n_ICache = n_IF_substage_0 + perfModel->iCacheModel.getDelay();
    perfModel->iCacheModel.setIc_in(n_ICache);
    // IF_substage_1
    uint64_t n_IF_substage_1;
    n_IF_substage_1 = std::max({n_ICache, perfModel->IF_substage_2});
    perfModel->IF_substage_1 = n_IF_substage_1;
    // IScan
    uint64_t n_IScan;
    n_IScan = n_IF_substage_1 + 1;
    perfModel->dynBranchPredModel.setPc_p_jr(n_IScan);
    // IF_stage
    uint64_t n_IF_stage;
    n_IF_stage = std::max({n_IScan, perfModel->IF_stage.get(1), perfModel->IQ_stage.get(7)});
    perfModel->IF_stage.set(n_IF_stage);
    perfModel->IF_substage_2 = n_IF_stage;
    // IQInsert
    uint64_t n_IQInsert;
    n_IQInsert = n_IF_stage + 1;
    // IQ_stage
    uint64_t n_IQ_stage;
    n_IQ_stage = std::max({n_IQInsert, perfModel->IQ_stage.get(1), perfModel->ID_stage});
    perfModel->IQ_stage.set(n_IQ_stage);
    // Decoder
    uint64_t n_Decoder;
    n_Decoder = n_IQ_stage + 1;
    // ID_stage
    uint64_t n_ID_stage;
    n_ID_stage = std::max({n_Decoder, perfModel->IS_stage});
    perfModel->ID_stage = n_ID_stage;
    // Issue
    uint64_t n_Issue = n_ID_stage;
    // uA_Clobber
    uint64_t n_uA_Clobber;
    n_uA_Clobber = std::max({n_ID_stage, perfModel->clobberModel.getCb_out()});
    // uA_OF_A
    uint64_t n_uA_OF_A;
    n_uA_OF_A = std::max({n_ID_stage, perfModel->regModel.getXa()});
    // IS_stage
    uint64_t n_IS_stage;
    n_IS_stage = std::max({n_Issue, n_uA_Clobber, n_uA_OF_A, perfModel->EX_stage.get(8), perfModel->EX_substage_alu, perfModel->EX_substage_mul_o, perfModel->EX_substage_div});
    perfModel->IS_stage = n_IS_stage;
    // ALU
    uint64_t n_ALU;
    n_ALU = n_IS_stage + 1;
    perfModel->regModel.setXd(n_ALU);
    perfModel->dynBranchPredModel.setPc_c(n_ALU);
    // EX_substage_alu
    uint64_t n_EX_substage_alu = n_ALU;
    perfModel->EX_substage_alu = n_EX_substage_alu;
    // EX_stage
    uint64_t n_EX_stage;
    n_EX_stage = std::max({n_EX_substage_alu, perfModel->EX_stage.get(1), perfModel->COM_stage.get(2)});
    perfModel->EX_stage.set(n_EX_stage);
    // Commit
    uint64_t n_Commit;
    n_Commit = n_EX_stage + 1;
    perfModel->clobberModel.setCb_in(n_Commit);
    // COM_stage
    uint64_t n_COM_stage;
    n_COM_stage = std::max({n_Commit, perfModel->COM_stage.get(1)});
    perfModel->COM_stage.set(n_COM_stage);

    // Dump Entrance point for info print (tracing)
    perfModel->entrancePoint = n_Enter;
}

inline void Mul(PerformanceModel* perfModel_) {
    CVA6_PerformanceModel* perfModel = static_cast<CVA6_PerformanceModel*>(perfModel_);
    // Enter
    uint64_t n_Enter = perfModel->PC_stage;
    // PCGen
    uint64_t n_PCGen;
    n_PCGen = n_Enter + 1;
    // uA_PcCorrect
    uint64_t n_uA_PcCorrect;
    n_uA_PcCorrect = std::max({n_Enter, perfModel->dynBranchPredModel.getPc_mp()});
    // uA_CacheBlock
    uint64_t n_uA_CacheBlock;
    n_uA_CacheBlock = std::max({n_Enter, perfModel->iCacheModel.getIc_out()});
    // PC_stage
    uint64_t n_PC_stage;
    n_PC_stage = std::max({n_PCGen, n_uA_PcCorrect, n_uA_CacheBlock, perfModel->IF_stage.get(3), perfModel->IF_substage_0});
    perfModel->PC_stage = n_PC_stage;
    // ICacheCtrl
    uint64_t n_ICacheCtrl;
    n_ICacheCtrl = n_PC_stage + 1;
    // uA_PcPredict
    uint64_t n_uA_PcPredict;
    n_uA_PcPredict = std::max({n_PC_stage, perfModel->dynBranchPredModel.getPc_pt()});
    // IF_substage_0
    uint64_t n_IF_substage_0;
    n_IF_substage_0 = std::max({n_ICacheCtrl, n_uA_PcPredict, perfModel->IF_substage_1});
    perfModel->IF_substage_0 = n_IF_substage_0;
    // ICache
    uint64_t n_ICache;
    n_ICache = n_IF_substage_0 + perfModel->iCacheModel.getDelay();
    perfModel->iCacheModel.setIc_in(n_ICache);
    // IF_substage_1
    uint64_t n_IF_substage_1;
    n_IF_substage_1 = std::max({n_ICache, perfModel->IF_substage_2});
    perfModel->IF_substage_1 = n_IF_substage_1;
    // IScan
    uint64_t n_IScan;
    n_IScan = n_IF_substage_1 + 1;
    // IF_stage
    uint64_t n_IF_stage;
    n_IF_stage = std::max({n_IScan, perfModel->IF_stage.get(1), perfModel->IQ_stage.get(7)});
    perfModel->IF_stage.set(n_IF_stage);
    perfModel->IF_substage_2 = n_IF_stage;
    // IQInsert
    uint64_t n_IQInsert;
    n_IQInsert = n_IF_stage + 1;
    // IQ_stage
    uint64_t n_IQ_stage;
    n_IQ_stage = std::max({n_IQInsert, perfModel->IQ_stage.get(1), perfModel->ID_stage});
    perfModel->IQ_stage.set(n_IQ_stage);
    // Decoder
    uint64_t n_Decoder;
    n_Decoder = n_IQ_stage + 1;
    // ID_stage
    uint64_t n_ID_stage;
    n_ID_stage = std::max({n_Decoder, perfModel->IS_stage});
    perfModel->ID_stage = n_ID_stage;
    // Issue
    uint64_t n_Issue = n_ID_stage;
    // uA_Clobber
    uint64_t n_uA_Clobber;
    n_uA_Clobber = std::max({n_ID_stage, perfModel->clobberModel.getCb_out()});
    // uA_OF_A
    uint64_t n_uA_OF_A;
    n_uA_OF_A = std::max({n_ID_stage, perfModel->regModel.getXa()});
    // uA_OF_B
    uint64_t n_uA_OF_B;
    n_uA_OF_B = std::max({n_ID_stage, perfModel->regModel.getXb()});
    // IS_stage
    uint64_t n_IS_stage;
    n_IS_stage = std::max({n_Issue, n_uA_Clobber, n_uA_OF_A, n_uA_OF_B, perfModel->EX_stage.get(8), perfModel->EX_substage_mul_i, perfModel->EX_substage_div});
    perfModel->IS_stage = n_IS_stage;
    // MUL_I
    uint64_t n_MUL_I;
    n_MUL_I = n_IS_stage + 1;
    // EX_substage_mul_i
    uint64_t n_EX_substage_mul_i;
    n_EX_substage_mul_i = std::max({n_MUL_I, perfModel->EX_substage_mul_o});
    perfModel->EX_substage_mul_i = n_EX_substage_mul_i;
    // MUL_O
    uint64_t n_MUL_O;
    n_MUL_O = n_EX_substage_mul_i + 1;
    perfModel->regModel.setXd(n_MUL_O);
    // EX_substage_mul_o
    uint64_t n_EX_substage_mul_o = n_MUL_O;
    perfModel->EX_substage_mul_o = n_EX_substage_mul_o;
    // EX_stage
    uint64_t n_EX_stage;
    n_EX_stage = std::max({n_EX_substage_mul_o, perfModel->EX_stage.get(1), perfModel->COM_stage.get(2)});
    perfModel->EX_stage.set(n_EX_stage);
    // Commit
    uint64_t n_Commit;
    n_Commit = n_EX_stage + 1;
    perfModel->clobberModel.setCb_in(n_Commit);
    // COM_stage
    uint64_t n_COM_stage;
    n_COM_stage = std::max({n_Commit, perfModel->COM_stage.get(1)});
    perfModel->COM_stage.set(n_COM_stage);

    // Dump Entrance point for info print (tracing)
    perfModel->entrancePoint = n_Enter;
}

inline void Div(PerformanceModel* perfModel_) {
    CVA6_PerformanceModel* perfModel = static_cast<CVA6_PerformanceModel*>(perfModel_);
    // Enter
    uint64_t n_Enter = perfModel->PC_stage;
    // PCGen
    uint64_t n_PCGen;
    n_PCGen = n_Enter + 1;
    // uA_PcCorrect
    uint64_t n_uA_PcCorrect;
    n_uA_PcCorrect = std::max({n_Enter, perfModel->dynBranchPredModel.getPc_mp()});
    // uA_CacheBlock
    uint64_t n_uA_CacheBlock;
    n_uA_CacheBlock = std::max({n_Enter, perfModel->iCacheModel.getIc_out()});
    // PC_stage
    uint64_t n_PC_stage;
    n_PC_stage = std::max({n_PCGen, n_uA_PcCorrect, n_uA_CacheBlock, perfModel->IF_stage.get(3), perfModel->IF_substage_0});
    perfModel->PC_stage = n_PC_stage;
    // ICacheCtrl
    uint64_t n_ICacheCtrl;
    n_ICacheCtrl = n_PC_stage + 1;
    // uA_PcPredict
    uint64_t n_uA_PcPredict;
    n_uA_PcPredict = std::max({n_PC_stage, perfModel->dynBranchPredModel.getPc_pt()});
    // IF_substage_0
    uint64_t n_IF_substage_0;
    n_IF_substage_0 = std::max({n_ICacheCtrl, n_uA_PcPredict, perfModel->IF_substage_1});
    perfModel->IF_substage_0 = n_IF_substage_0;
    // ICache
    uint64_t n_ICache;
    n_ICache = n_IF_substage_0 + perfModel->iCacheModel.getDelay();
    perfModel->iCacheModel.setIc_in(n_ICache);
    // IF_substage_1
    uint64_t n_IF_substage_1;
    n_IF_substage_1 = std::max({n_ICache, perfModel->IF_substage_2});
    perfModel->IF_substage_1 = n_IF_substage_1;
    // IScan
    uint64_t n_IScan;
    n_IScan = n_IF_substage_1 + 1;
    // IF_stage
    uint64_t n_IF_stage;
    n_IF_stage = std::max({n_IScan, perfModel->IF_stage.get(1), perfModel->IQ_stage.get(7)});
    perfModel->IF_stage.set(n_IF_stage);
    perfModel->IF_substage_2 = n_IF_stage;
    // IQInsert
    uint64_t n_IQInsert;
    n_IQInsert = n_IF_stage + 1;
    // IQ_stage
    uint64_t n_IQ_stage;
    n_IQ_stage = std::max({n_IQInsert, perfModel->IQ_stage.get(1), perfModel->ID_stage});
    perfModel->IQ_stage.set(n_IQ_stage);
    // Decoder
    uint64_t n_Decoder;
    n_Decoder = n_IQ_stage + 1;
    // ID_stage
    uint64_t n_ID_stage;
    n_ID_stage = std::max({n_Decoder, perfModel->IS_stage});
    perfModel->ID_stage = n_ID_stage;
    // Issue
    uint64_t n_Issue = n_ID_stage;
    // uA_Clobber
    uint64_t n_uA_Clobber;
    n_uA_Clobber = std::max({n_ID_stage, perfModel->clobberModel.getCb_out()});
    // uA_OF_A
    uint64_t n_uA_OF_A;
    n_uA_OF_A = std::max({n_ID_stage, perfModel->regModel.getXa()});
    // uA_OF_B
    uint64_t n_uA_OF_B;
    n_uA_OF_B = std::max({n_ID_stage, perfModel->regModel.getXb()});
    // IS_stage
    uint64_t n_IS_stage;
    n_IS_stage = std::max({n_Issue, n_uA_Clobber, n_uA_OF_A, n_uA_OF_B, perfModel->EX_stage.get(8), perfModel->EX_substage_div});
    perfModel->IS_stage = n_IS_stage;
    // DIV
    uint64_t n_DIV;
    n_DIV = n_IS_stage + perfModel->divider.getDelay();
    // EX_substage_div
    uint64_t n_EX_substage_div = n_DIV;
    perfModel->EX_substage_div = n_EX_substage_div;
    // EX_stage
    uint64_t n_EX_stage;
    n_EX_stage = std::max({n_EX_substage_div, perfModel->EX_stage.get(1), perfModel->COM_stage.get(2)});
    perfModel->EX_stage.set(n_EX_stage);
    // Commit
    uint64_t n_Commit;
    n_Commit = n_EX_stage + 1;
    perfModel->clobberModel.setCb_in(n_Commit);
    // COM_stage
    uint64_t n_COM_stage;
    n_COM_stage = std::max({n_Commit, perfModel->COM_stage.get(1)});
    perfModel->COM_stage.set(n_COM_stage);

    // Dump Entrance point for info print (tracing)
    perfModel->entrancePoint = n_Enter;
}

inline void DivU(PerformanceModel* perfModel_) {
    CVA6_PerformanceModel* perfModel = static_cast<CVA6_PerformanceModel*>(perfModel_);
    // Enter
    uint64_t n_Enter = perfModel->PC_stage;
    // PCGen
    uint64_t n_PCGen;
    n_PCGen = n_Enter + 1;
    // uA_PcCorrect
    uint64_t n_uA_PcCorrect;
    n_uA_PcCorrect = std::max({n_Enter, perfModel->dynBranchPredModel.getPc_mp()});
    // uA_CacheBlock
    uint64_t n_uA_CacheBlock;
    n_uA_CacheBlock = std::max({n_Enter, perfModel->iCacheModel.getIc_out()});
    // PC_stage
    uint64_t n_PC_stage;
    n_PC_stage = std::max({n_PCGen, n_uA_PcCorrect, n_uA_CacheBlock, perfModel->IF_stage.get(3), perfModel->IF_substage_0});
    perfModel->PC_stage = n_PC_stage;
    // ICacheCtrl
    uint64_t n_ICacheCtrl;
    n_ICacheCtrl = n_PC_stage + 1;
    // uA_PcPredict
    uint64_t n_uA_PcPredict;
    n_uA_PcPredict = std::max({n_PC_stage, perfModel->dynBranchPredModel.getPc_pt()});
    // IF_substage_0
    uint64_t n_IF_substage_0;
    n_IF_substage_0 = std::max({n_ICacheCtrl, n_uA_PcPredict, perfModel->IF_substage_1});
    perfModel->IF_substage_0 = n_IF_substage_0;
    // ICache
    uint64_t n_ICache;
    n_ICache = n_IF_substage_0 + perfModel->iCacheModel.getDelay();
    perfModel->iCacheModel.setIc_in(n_ICache);
    // IF_substage_1
    uint64_t n_IF_substage_1;
    n_IF_substage_1 = std::max({n_ICache, perfModel->IF_substage_2});
    perfModel->IF_substage_1 = n_IF_substage_1;
    // IScan
    uint64_t n_IScan;
    n_IScan = n_IF_substage_1 + 1;
    // IF_stage
    uint64_t n_IF_stage;
    n_IF_stage = std::max({n_IScan, perfModel->IF_stage.get(1), perfModel->IQ_stage.get(7)});
    perfModel->IF_stage.set(n_IF_stage);
    perfModel->IF_substage_2 = n_IF_stage;
    // IQInsert
    uint64_t n_IQInsert;
    n_IQInsert = n_IF_stage + 1;
    // IQ_stage
    uint64_t n_IQ_stage;
    n_IQ_stage = std::max({n_IQInsert, perfModel->IQ_stage.get(1), perfModel->ID_stage});
    perfModel->IQ_stage.set(n_IQ_stage);
    // Decoder
    uint64_t n_Decoder;
    n_Decoder = n_IQ_stage + 1;
    // ID_stage
    uint64_t n_ID_stage;
    n_ID_stage = std::max({n_Decoder, perfModel->IS_stage});
    perfModel->ID_stage = n_ID_stage;
    // Issue
    uint64_t n_Issue = n_ID_stage;
    // uA_Clobber
    uint64_t n_uA_Clobber;
    n_uA_Clobber = std::max({n_ID_stage, perfModel->clobberModel.getCb_out()});
    // uA_OF_A
    uint64_t n_uA_OF_A;
    n_uA_OF_A = std::max({n_ID_stage, perfModel->regModel.getXa()});
    // uA_OF_B
    uint64_t n_uA_OF_B;
    n_uA_OF_B = std::max({n_ID_stage, perfModel->regModel.getXb()});
    // IS_stage
    uint64_t n_IS_stage;
    n_IS_stage = std::max({n_Issue, n_uA_Clobber, n_uA_OF_A, n_uA_OF_B, perfModel->EX_stage.get(8), perfModel->EX_substage_div});
    perfModel->IS_stage = n_IS_stage;
    // DIVU
    uint64_t n_DIVU;
    n_DIVU = n_IS_stage + perfModel->divider_u.getDelay();
    // EX_substage_div
    uint64_t n_EX_substage_div = n_DIVU;
    perfModel->EX_substage_div = n_EX_substage_div;
    // EX_stage
    uint64_t n_EX_stage;
    n_EX_stage = std::max({n_EX_substage_div, perfModel->EX_stage.get(1), perfModel->COM_stage.get(2)});
    perfModel->EX_stage.set(n_EX_stage);
    // Commit
    uint64_t n_Commit;
    n_Commit = n_EX_stage + 1;
    perfModel->clobberModel.setCb_in(n_Commit);
    // COM_stage
    uint64_t n_COM_stage;
    n_COM_stage = std::max({n_Commit, perfModel->COM_stage.get(1)});
    perfModel->COM_stage.set(n_COM_stage);

    // Dump Entrance point for info print (tracing)
    perfModel->entrancePoint = n_Enter;
}

inline void Load(PerformanceModel* perfModel_) {
    CVA6_PerformanceModel* perfModel = static_cast<CVA6_PerformanceModel*>(perfModel_);
    // Enter
    uint64_t n_Enter = perfModel->PC_stage;
    // PCGen
    uint64_t n_PCGen;
    n_PCGen = n_Enter + 1;
    // uA_PcCorrect
    uint64_t n_uA_PcCorrect;
    n_uA_PcCorrect = std::max({n_Enter, perfModel->dynBranchPredModel.getPc_mp()});
    // uA_CacheBlock
    uint64_t n_uA_CacheBlock;
    n_uA_CacheBlock = std::max({n_Enter, perfModel->iCacheModel.getIc_out()});
    // PC_stage
    uint64_t n_PC_stage;
    n_PC_stage = std::max({n_PCGen, n_uA_PcCorrect, n_uA_CacheBlock, perfModel->IF_stage.get(3), perfModel->IF_substage_0});
    perfModel->PC_stage = n_PC_stage;
    // ICacheCtrl
    uint64_t n_ICacheCtrl;
    n_ICacheCtrl = n_PC_stage + 1;
    // uA_PcPredict
    uint64_t n_uA_PcPredict;
    n_uA_PcPredict = std::max({n_PC_stage, perfModel->dynBranchPredModel.getPc_pt()});
    // IF_substage_0
    uint64_t n_IF_substage_0;
    n_IF_substage_0 = std::max({n_ICacheCtrl, n_uA_PcPredict, perfModel->IF_substage_1});
    perfModel->IF_substage_0 = n_IF_substage_0;
    // ICache
    uint64_t n_ICache;
    n_ICache = n_IF_substage_0 + perfModel->iCacheModel.getDelay();
    perfModel->iCacheModel.setIc_in(n_ICache);
    // IF_substage_1
    uint64_t n_IF_substage_1;
    n_IF_substage_1 = std::max({n_ICache, perfModel->IF_substage_2});
    perfModel->IF_substage_1 = n_IF_substage_1;
    // IScan
    uint64_t n_IScan;
    n_IScan = n_IF_substage_1 + 1;
    // IF_stage
    uint64_t n_IF_stage;
    n_IF_stage = std::max({n_IScan, perfModel->IF_stage.get(1), perfModel->IQ_stage.get(7)});
    perfModel->IF_stage.set(n_IF_stage);
    perfModel->IF_substage_2 = n_IF_stage;
    // IQInsert
    uint64_t n_IQInsert;
    n_IQInsert = n_IF_stage + 1;
    // IQ_stage
    uint64_t n_IQ_stage;
    n_IQ_stage = std::max({n_IQInsert, perfModel->IQ_stage.get(1), perfModel->ID_stage});
    perfModel->IQ_stage.set(n_IQ_stage);
    // Decoder
    uint64_t n_Decoder;
    n_Decoder = n_IQ_stage + 1;
    // ID_stage
    uint64_t n_ID_stage;
    n_ID_stage = std::max({n_Decoder, perfModel->IS_stage});
    perfModel->ID_stage = n_ID_stage;
    // Issue
    uint64_t n_Issue = n_ID_stage;
    // uA_Clobber
    uint64_t n_uA_Clobber;
    n_uA_Clobber = std::max({n_ID_stage, perfModel->clobberModel.getCb_out()});
    // uA_OF_A
    uint64_t n_uA_OF_A;
    n_uA_OF_A = std::max({n_ID_stage, perfModel->regModel.getXa()});
    // IS_stage
    uint64_t n_IS_stage;
    n_IS_stage = std::max({n_Issue, n_uA_Clobber, n_uA_OF_A, perfModel->EX_stage.get(8), perfModel->EX_substage_lCtrl});
    perfModel->IS_stage = n_IS_stage;
    // LCtrl
    uint64_t n_LCtrl;
    n_LCtrl = n_IS_stage + 1;
    // EX_substage_lCtrl
    uint64_t n_EX_substage_lCtrl;
    n_EX_substage_lCtrl = std::max({n_LCtrl, perfModel->EX_substage_dCache});
    perfModel->EX_substage_lCtrl = n_EX_substage_lCtrl;
    // DCache
    uint64_t n_DCache;
    n_DCache = n_EX_substage_lCtrl + perfModel->dCacheModel.getDelay();
    // EX_substage_dCache
    uint64_t n_EX_substage_dCache;
    n_EX_substage_dCache = std::max({n_DCache, perfModel->EX_substage_lUnit});
    perfModel->EX_substage_dCache = n_EX_substage_dCache;
    // LUnit
    uint64_t n_LUnit;
    n_LUnit = n_EX_substage_dCache + 1;
    perfModel->regModel.setXd(n_LUnit);
    // EX_substage_lUnit
    uint64_t n_EX_substage_lUnit = n_LUnit;
    perfModel->EX_substage_lUnit = n_EX_substage_lUnit;
    // EX_stage
    uint64_t n_EX_stage;
    n_EX_stage = std::max({n_EX_substage_lUnit, perfModel->EX_stage.get(1), perfModel->COM_stage.get(2)});
    perfModel->EX_stage.set(n_EX_stage);
    // Commit
    uint64_t n_Commit;
    n_Commit = n_EX_stage + 1;
    perfModel->clobberModel.setCb_in(n_Commit);
    // COM_stage
    uint64_t n_COM_stage;
    n_COM_stage = std::max({n_Commit, perfModel->COM_stage.get(1)});
    perfModel->COM_stage.set(n_COM_stage);

    // Dump Entrance point for info print (tracing)
    perfModel->entrancePoint = n_Enter;
}

inline void Store(PerformanceModel* perfModel_) {
    CVA6_PerformanceModel* perfModel = static_cast<CVA6_PerformanceModel*>(perfModel_);
    // Enter
    uint64_t n_Enter = perfModel->PC_stage;
    // PCGen
    uint64_t n_PCGen;
    n_PCGen = n_Enter + 1;
    // uA_PcCorrect
    uint64_t n_uA_PcCorrect;
    n_uA_PcCorrect = std::max({n_Enter, perfModel->dynBranchPredModel.getPc_mp()});
    // uA_CacheBlock
    uint64_t n_uA_CacheBlock;
    n_uA_CacheBlock = std::max({n_Enter, perfModel->iCacheModel.getIc_out()});
    // PC_stage
    uint64_t n_PC_stage;
    n_PC_stage = std::max({n_PCGen, n_uA_PcCorrect, n_uA_CacheBlock, perfModel->IF_stage.get(3), perfModel->IF_substage_0});
    perfModel->PC_stage = n_PC_stage;
    // ICacheCtrl
    uint64_t n_ICacheCtrl;
    n_ICacheCtrl = n_PC_stage + 1;
    // uA_PcPredict
    uint64_t n_uA_PcPredict;
    n_uA_PcPredict = std::max({n_PC_stage, perfModel->dynBranchPredModel.getPc_pt()});
    // IF_substage_0
    uint64_t n_IF_substage_0;
    n_IF_substage_0 = std::max({n_ICacheCtrl, n_uA_PcPredict, perfModel->IF_substage_1});
    perfModel->IF_substage_0 = n_IF_substage_0;
    // ICache
    uint64_t n_ICache;
    n_ICache = n_IF_substage_0 + perfModel->iCacheModel.getDelay();
    perfModel->iCacheModel.setIc_in(n_ICache);
    // IF_substage_1
    uint64_t n_IF_substage_1;
    n_IF_substage_1 = std::max({n_ICache, perfModel->IF_substage_2});
    perfModel->IF_substage_1 = n_IF_substage_1;
    // IScan
    uint64_t n_IScan;
    n_IScan = n_IF_substage_1 + 1;
    // IF_stage
    uint64_t n_IF_stage;
    n_IF_stage = std::max({n_IScan, perfModel->IF_stage.get(1), perfModel->IQ_stage.get(7)});
    perfModel->IF_stage.set(n_IF_stage);
    perfModel->IF_substage_2 = n_IF_stage;
    // IQInsert
    uint64_t n_IQInsert;
    n_IQInsert = n_IF_stage + 1;
    // IQ_stage
    uint64_t n_IQ_stage;
    n_IQ_stage = std::max({n_IQInsert, perfModel->IQ_stage.get(1), perfModel->ID_stage});
    perfModel->IQ_stage.set(n_IQ_stage);
    // Decoder
    uint64_t n_Decoder;
    n_Decoder = n_IQ_stage + 1;
    // ID_stage
    uint64_t n_ID_stage;
    n_ID_stage = std::max({n_Decoder, perfModel->IS_stage});
    perfModel->ID_stage = n_ID_stage;
    // Issue
    uint64_t n_Issue = n_ID_stage;
    // uA_OF_A
    uint64_t n_uA_OF_A;
    n_uA_OF_A = std::max({n_ID_stage, perfModel->regModel.getXa()});
    // uA_OF_B
    uint64_t n_uA_OF_B;
    n_uA_OF_B = std::max({n_ID_stage, perfModel->regModel.getXb()});
    // IS_stage
    uint64_t n_IS_stage;
    n_IS_stage = std::max({n_Issue, n_uA_OF_A, n_uA_OF_B, perfModel->EX_stage.get(8), perfModel->EX_substage_sCtrl});
    perfModel->IS_stage = n_IS_stage;
    // SCtrl
    uint64_t n_SCtrl;
    n_SCtrl = n_IS_stage + 1;
    // EX_substage_sCtrl
    uint64_t n_EX_substage_sCtrl;
    n_EX_substage_sCtrl = std::max({n_SCtrl, perfModel->EX_substage_sUnit});
    perfModel->EX_substage_sCtrl = n_EX_substage_sCtrl;
    // SUnit
    uint64_t n_SUnit;
    n_SUnit = n_EX_substage_sCtrl + 1;
    // EX_substage_sUnit
    uint64_t n_EX_substage_sUnit = n_SUnit;
    perfModel->EX_substage_sUnit = n_EX_substage_sUnit;
    // EX_stage
    uint64_t n_EX_stage;
    n_EX_stage = std::max({n_EX_substage_sUnit, perfModel->EX_stage.get(1), perfModel->COM_stage.get(2)});
    perfModel->EX_stage.set(n_EX_stage);
    // Commit
    uint64_t n_Commit;
    n_Commit = n_EX_stage + 1;
    // COM_stage
    uint64_t n_COM_stage;
    n_COM_stage = std::max({n_Commit, perfModel->COM_stage.get(1)});
    perfModel->COM_stage.set(n_COM_stage);

    // Dump Entrance point for info print (tracing)
    perfModel->entrancePoint = n_Enter;
}

}  // namespace CVA6