
TARGET_SOURCES(SWEVAL_BACKENDS_LIB PRIVATE
  	src/RV32_4ISSUE_Channel.cpp
	src/RV32_4ISSUE_InstructionPrinters.cpp
	src/RV32_4ISSUE_PerformanceModel.cpp
	src/RV32_4ISSUE_Printer.cpp
	src/RV32_4ISSUE_SchedulingFunction.cpp

)

TARGET_INCLUDE_DIRECTORIES(SWEVAL_BACKENDS_LIB PRIVATE
include
)
