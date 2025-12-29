#include <algorithm>
#include <cstdint>

#include "PerformanceModel.h"

#include "CVA6_PerformanceModel.h"

namespace CVA6 {

inline void Default_Inst(PerformanceModel* perfModel_) {
    CVA6_PerformanceModel* perfModel = static_cast<CVA6_PerformanceModel*>(perfModel_);
    uint64_t enterPoint = perfModel->entrancePoint;

    // Dump Entrance point for info print (tracing)
    perfModel->entrancePoint = enterPoint + 1;
}

inline void Arith_0(PerformanceModel* perfModel_) {
    CVA6_PerformanceModel* perfModel = static_cast<CVA6_PerformanceModel*>(perfModel_);
    uint64_t enterPoint = perfModel->entrancePoint;

    // Dump Entrance point for info print (tracing)
    perfModel->entrancePoint = enterPoint + 1;
}

inline void Arith_Rs1(PerformanceModel* perfModel_) {
    CVA6_PerformanceModel* perfModel = static_cast<CVA6_PerformanceModel*>(perfModel_);
    uint64_t enterPoint = perfModel->entrancePoint;

    // Dump Entrance point for info print (tracing)
    perfModel->entrancePoint = enterPoint + 1;
}

inline void Arith_Rs1_Rs2(PerformanceModel* perfModel_) {
    CVA6_PerformanceModel* perfModel = static_cast<CVA6_PerformanceModel*>(perfModel_);
    uint64_t enterPoint = perfModel->entrancePoint;

    // Dump Entrance point for info print (tracing)
    perfModel->entrancePoint = enterPoint + 1;
}

inline void Branch(PerformanceModel* perfModel_) {
    CVA6_PerformanceModel* perfModel = static_cast<CVA6_PerformanceModel*>(perfModel_);
    uint64_t enterPoint = perfModel->entrancePoint;

    // Dump Entrance point for info print (tracing)
    perfModel->entrancePoint = enterPoint + 1;
}

inline void Jump(PerformanceModel* perfModel_) {
    CVA6_PerformanceModel* perfModel = static_cast<CVA6_PerformanceModel*>(perfModel_);
    uint64_t enterPoint = perfModel->entrancePoint;

    // Dump Entrance point for info print (tracing)
    perfModel->entrancePoint = enterPoint + 1;
}

inline void JumpR(PerformanceModel* perfModel_) {
    CVA6_PerformanceModel* perfModel = static_cast<CVA6_PerformanceModel*>(perfModel_);
    uint64_t enterPoint = perfModel->entrancePoint;

    // Dump Entrance point for info print (tracing)
    perfModel->entrancePoint = enterPoint + 1;
}

inline void Mul(PerformanceModel* perfModel_) {
    CVA6_PerformanceModel* perfModel = static_cast<CVA6_PerformanceModel*>(perfModel_);
    uint64_t enterPoint = perfModel->entrancePoint;

    // Dump Entrance point for info print (tracing)
    perfModel->entrancePoint = enterPoint + 1;
}

inline void Div(PerformanceModel* perfModel_) {
    CVA6_PerformanceModel* perfModel = static_cast<CVA6_PerformanceModel*>(perfModel_);
    uint64_t enterPoint = perfModel->entrancePoint;

    // Dump Entrance point for info print (tracing)
    perfModel->entrancePoint = enterPoint + 1;
}

inline void DivU(PerformanceModel* perfModel_) {
    CVA6_PerformanceModel* perfModel = static_cast<CVA6_PerformanceModel*>(perfModel_);
    uint64_t enterPoint = perfModel->entrancePoint;

    // Dump Entrance point for info print (tracing)
    perfModel->entrancePoint = enterPoint + 1;
}

inline void Load(PerformanceModel* perfModel_) {
    CVA6_PerformanceModel* perfModel = static_cast<CVA6_PerformanceModel*>(perfModel_);
    uint64_t enterPoint = perfModel->entrancePoint;

    // Dump Entrance point for info print (tracing)
    perfModel->entrancePoint = enterPoint + 1;
}

inline void Store(PerformanceModel* perfModel_) {
    CVA6_PerformanceModel* perfModel = static_cast<CVA6_PerformanceModel*>(perfModel_);
    uint64_t enterPoint = perfModel->entrancePoint;

    // Dump Entrance point for info print (tracing)
    perfModel->entrancePoint = enterPoint + 1;
}

}  // namespace CVA6