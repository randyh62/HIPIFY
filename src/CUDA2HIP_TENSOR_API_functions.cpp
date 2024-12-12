/*
Copyright (c) 2015 - present Advanced Micro Devices, Inc. All rights reserved.

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

#include "CUDA2HIP.h"

const std::map<llvm::StringRef, hipCounter> CUDA_TENSOR_FUNCTION_MAP {
  {"cutensorCreate",                                              {"hiptensorCreate",                                     "",                                     CONV_LIB_FUNC, API_TENSOR, 2}},
  {"cutensorDestroy",                                             {"hiptensorDestroy",                                    "",                                     CONV_LIB_FUNC, API_TENSOR, 2}},
  {"cutensorHandleResizePlanCache",                               {"",                                                    "",                                     CONV_LIB_FUNC, API_TENSOR, 2, UNSUPPORTED}},
  {"cutensorHandleWritePlanCacheToFile",                          {"",                                                    "",                                     CONV_LIB_FUNC, API_TENSOR, 2, UNSUPPORTED}},
  {"cutensorHandleReadPlanCacheFromFile",                         {"",                                                    "",                                     CONV_LIB_FUNC, API_TENSOR, 2, UNSUPPORTED}},
};


const std::map<llvm::StringRef, cudaAPIversions> CUDA_TENSOR_FUNCTION_VER_MAP {
  {"cutensorCreate",                                 {CUTENSOR_1700,  CUDA_0,    CUDA_0   }},
  {"cutensorDestroy",                                {CUTENSOR_1700,  CUDA_0,    CUDA_0   }},
  {"cutensorHandleResizePlanCache",                  {CUTENSOR_2000,  CUDA_0,    CUDA_0   }},
  {"cutensorHandleWritePlanCacheToFile",             {CUTENSOR_2000,  CUDA_0,    CUDA_0   }},
  {"cutensorHandleReadPlanCacheFromFile",            {CUTENSOR_2000,  CUDA_0,    CUDA_0   }},
};

const std::map<llvm::StringRef, hipAPIversions> HIP_TENSOR_FUNCTION_VER_MAP {
  {"hiptensorCreate",                                {HIP_5070,       HIP_0,         HIP_0,       }},
  {"hiptensorDestroy",                               {HIP_5070,       HIP_0,         HIP_0,       }},
};

const std::map<unsigned int, llvm::StringRef> CUDA_TENSOR_API_SECTION_MAP {
  {1, "CUTENSOR Data types"},
  {2, "CUTENSOR Function Reference"},
};
