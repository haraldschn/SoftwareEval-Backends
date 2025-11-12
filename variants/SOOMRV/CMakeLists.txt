
TARGET_SOURCES(SWEVAL_BACKENDS_LIB PRIVATE
  	src/SOOMRV_Channel.cpp
	src/SOOMRV_InstructionPrinters.cpp
	src/SOOMRV_PerformanceModel.cpp
	src/SOOMRV_Printer.cpp
	src/SOOMRV_SchedulingFunction.cpp

)

TARGET_INCLUDE_DIRECTORIES(SWEVAL_BACKENDS_LIB PRIVATE
include
)
