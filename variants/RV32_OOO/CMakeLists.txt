
TARGET_SOURCES(SWEVAL_BACKENDS_LIB PRIVATE
  	src/RV32_OOO_Channel.cpp
	src/RV32_OOO_InstructionPrinters.cpp
	src/RV32_OOO_PerformanceModel.cpp
	src/RV32_OOO_Printer.cpp
	src/RV32_OOO_SchedulingFunction.cpp

)

TARGET_INCLUDE_DIRECTORIES(SWEVAL_BACKENDS_LIB PRIVATE
include
)
