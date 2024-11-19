// RUN: %run_test hipify "%s" "%t" %hipify_args 3 --amap --skip-excluded-preprocessor-conditional-blocks --experimental %clang_args -D__CUDA_API_VERSION_INTERNAL -ferror-limit=500

// CHECK: #include <hip/hip_runtime.h>
#include <cuda_runtime.h>
#include <stdio.h>
// CHECK: #include "hiptensor.h"
#include "cutensor.h"
// CHECK-NOT: #include "hiptensor.h"

int main() {

#if CUTENSOR_MAJOR >= 2
  // CHECK: hiptensorComputeType_t tensorDataType_t;
  // CHECK-NEXT hiptensorComputeType_t TENSOR_R_16F = HIPTENSOR_COMPUTE_16F;
  // CHECK-NEXT hiptensorComputeType_t TENSOR_R_16BF = HIPTENSOR_COMPUTE_16BF;
  // CHECK-NEXT hiptensorComputeType_t TENSOR_R_32F = HIPTENSOR_COMPUTE_32F;
  // CHECK-NEXT hiptensorComputeType_t TENSOR_C_32F = HIPTENSOR_COMPUTE_C32F;
  // CHECK-NEXT hiptensorComputeType_t TENSOR_R_64F = HIPTENSOR_COMPUTE_64F;
  // CHECK-NEXT hiptensorComputeType_t TENSOR_C_64F = HIPTENSOR_COMPUTE_C64F;
  // CHECK-NEXT hiptensorComputeType_t TENSOR_R_8I = HIPTENSOR_COMPUTE_8I;
  // CHECK-NEXT hiptensorComputeType_t TENSOR_R_8U = HIPTENSOR_COMPUTE_8U;
  // CHECK-NEXT hiptensorComputeType_t TENSOR_R_32I = HIPTENSOR_COMPUTE_32I;
  // CHECK-NEXT hiptensorComputeType_t TENSOR_R_32U = HIPTENSOR_COMPUTE_32U;
  cutensorDataType_t tensorDataType_t;
  cutensorDataType_t TENSOR_R_16F = CUTENSOR_R_16F;
  cutensorDataType_t TENSOR_R_16BF = CUTENSOR_R_16BF;
  cutensorDataType_t TENSOR_R_32F = CUTENSOR_R_32F;
  cutensorDataType_t TENSOR_C_32F = CUTENSOR_C_32F;
  cutensorDataType_t TENSOR_R_64F = CUTENSOR_R_64F;
  cutensorDataType_t TENSOR_C_64F = CUTENSOR_C_64F;
  cutensorDataType_t TENSOR_R_8I = CUTENSOR_R_8I;
  cutensorDataType_t TENSOR_R_8U = CUTENSOR_R_8U;
  cutensorDataType_t TENSOR_R_32I = CUTENSOR_R_32I;
  cutensorDataType_t TENSOR_R_32U = CUTENSOR_R_32U;
#endif

#if CUTENSOR_MAJOR >= 1
  // CHECK: hiptensorOperator_t tensorOperator_t;
  // CHECK-NEXT hiptensorOperator_t TENSOR_OP_IDENTITY = HIPTENSOR_OP_IDENTITY;
  // CHECK-NEXT hiptensorOperator_t TENSOR_OP_SQRT = HIPTENSOR_OP_SQRT;
  // CHECK-NEXT hiptensorOperator_t TENSOR_OP_UNKNOWN = HIPTENSOR_OP_UNKNOWN;
  cutensorOperator_t tensorOperator_t;
  cutensorOperator_t TENSOR_OP_IDENTITY = CUTENSOR_OP_IDENTITY;
  cutensorOperator_t TENSOR_OP_SQRT = CUTENSOR_OP_SQRT;
  cutensorOperator_t TENSOR_OP_UNKNOWN = CUTENSOR_OP_UNKNOWN;

  // CHECK: hiptensorStatus_t tensorStatus_t;
  // CHECK-NEXT hiptensorStatus_t TENSOR_STATUS_SUCCESS = HIPTENSOR_STATUS_SUCCESS;
  // CHECK-NEXT hiptensorStatus_t TENSOR_STATUS_NOT_INITIALIZED = HIPTENSOR_STATUS_NOT_INITIALIZED;
  // CHECK-NEXT hiptensorStatus_t TENSOR_STATUS_ALLOC_FAILED = HIPTENSOR_STATUS_ALLOC_FAILED;
  // CHECK-NEXT hiptensorStatus_t TENSOR_STATUS_INVALID_VALUE = HIPTENSOR_STATUS_INVALID_VALUE;
  // CHECK-NEXT hiptensorStatus_t TENSOR_STATUS_ARCH_MISMATCH = HIPTENSOR_STATUS_ARCH_MISMATCH;
  // CHECK-NEXT hiptensorStatus_t TENSOR_STATUS_EXECUTION_FAILED = HIPTENSOR_STATUS_EXECUTION_FAILED;
  // CHECK-NEXT hiptensorStatus_t TENSOR_STATUS_INTERNAL_ERROR = HIPTENSOR_STATUS_INTERNAL_ERROR;
  // CHECK-NEXT hiptensorStatus_t TENSOR_STATUS_NOT_SUPPORTED = HIPTENSOR_STATUS_NOT_SUPPORTED;
  // CHECK-NEXT hiptensorStatus_t TENSOR_STATUS_INSUFFICIENT_WORKSPACE = HIPTENSOR_STATUS_INSUFFICIENT_WORKSPACE;
  // CHECK-NEXT hiptensorStatus_t TENSOR_STATUS_INSUFFICIENT_DRIVER = HIPTENSOR_STATUS_INSUFFICIENT_DRIVER;
  // CHECK-NEXT hiptensorStatus_t TENSOR_STATUS_IO_ERROR = HIPTENSOR_STATUS_IO_ERROR;
  cutensorStatus_t tensorStatus_t;
  cutensorStatus_t TENSOR_STATUS_SUCCESS = CUTENSOR_STATUS_SUCCESS;
  cutensorStatus_t TENSOR_STATUS_NOT_INITIALIZED = CUTENSOR_STATUS_NOT_INITIALIZED;
  cutensorStatus_t TENSOR_STATUS_ALLOC_FAILED = CUTENSOR_STATUS_ALLOC_FAILED;
  cutensorStatus_t TENSOR_STATUS_INVALID_VALUE = CUTENSOR_STATUS_INVALID_VALUE;
  cutensorStatus_t TENSOR_STATUS_ARCH_MISMATCH = CUTENSOR_STATUS_ARCH_MISMATCH;
  cutensorStatus_t TENSOR_STATUS_EXECUTION_FAILED = CUTENSOR_STATUS_EXECUTION_FAILED;
  cutensorStatus_t TENSOR_STATUS_INTERNAL_ERROR = CUTENSOR_STATUS_INTERNAL_ERROR;
  cutensorStatus_t TENSOR_STATUS_NOT_SUPPORTED = CUTENSOR_STATUS_NOT_SUPPORTED;
  cutensorStatus_t TENSOR_STATUS_INSUFFICIENT_WORKSPACE = CUTENSOR_STATUS_INSUFFICIENT_WORKSPACE;
  cutensorStatus_t TENSOR_STATUS_INSUFFICIENT_DRIVER = CUTENSOR_STATUS_INSUFFICIENT_DRIVER;
  cutensorStatus_t TENSOR_STATUS_IO_ERROR = CUTENSOR_STATUS_IO_ERROR;

  // CHECK: hiptensorAlgo_t tensorAlgo_t;
  // CHECK-NEXT hiptensorAlgo_t TENSOR_ALGO_DEFAULT = HIPTENSOR_ALGO_DEFAULT;
  cutensorAlgo_t tensorAlgo_t;
  cutensorAlgo_t TENSOR_ALGO_DEFAULT = CUTENSOR_ALGO_DEFAULT;
#endif

#if CUTENSOR_VERSION >= 1400
  // CHECK-NEXT hiptensorAlgo_t TENSOR_ALGO_DEFAULT_PATIENT = HIPTENSOR_ALGO_DEFAULT_PATIENT;
  cutensorAlgo_t TENSOR_ALGO_DEFAULT_PATIENT = CUTENSOR_ALGO_DEFAULT_PATIENT;
#endif
}
