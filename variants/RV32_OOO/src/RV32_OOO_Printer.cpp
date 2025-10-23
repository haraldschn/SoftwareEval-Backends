/*
* Copyright 2025 Chair of EDA, Technical University of Munich
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*	 http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

/********************* AUTO GENERATE FILE (create by M2-ISA-R::Trace-Generator) *********************/


#include "RV32_OOO_Printer.h"

#include "Printer.h"

#include "RV32_OOO_Channel.h"

#include <iostream>
#include <iomanip>

extern InstructionPrinterSet* RV32_OOO_InstrPrinterSet;

RV32_OOO_Printer::RV32_OOO_Printer(): Printer("RV32_OOO_Printer", RV32_OOO_InstrPrinterSet)
{}

void RV32_OOO_Printer::connectChannel(Channel* ch_)
{
  RV32_OOO_Channel* channel = static_cast<RV32_OOO_Channel*>(ch_);
  
  rs1_ptr = channel->rs1;
  rs2_ptr = channel->rs2;
  rd_ptr = channel->rd;
  pc_ptr = channel->pc;
}

std::string RV32_OOO_Printer::getPrintHeader(void)
{
  std::stringstream caption_strs;	
  caption_strs << std::setfill(' ') << std::setw(18) << std::left << "rs1" << " | ";
  caption_strs << std::setfill(' ') << std::setw(18) << std::left << "rs2" << " | ";
  caption_strs << std::setfill(' ') << std::setw(18) << std::left << "rd" << " | ";
  caption_strs << std::setfill(' ') << std::setw(18) << std::left << "pc" << " | ";
  caption_strs << std::endl;

  return caption_strs.str();
}