/*
 * Copyright 2022 Chair of EDA, Technical University of Munich
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

#include "models/rv32_ooo/NoBranchPredictModel.h"

#include <cstdint>
#include <string>
#include <sstream>

namespace rv32_ooo{

std::string NoBranchPredictModel::getInfoHeader()
{
  std::stringstream ret_strs;
  ret_strs << "br:mispredict";
  ret_strs << "," << "br:pc_avail";
  return ret_strs.str();
}

std::string NoBranchPredictModel::getInfoStream()
{
  std::stringstream ret_strs;
  ret_strs << mispredicted_info;
  ret_strs << "," << pc_info;
  return ret_strs.str();
}

    
} // namespace common