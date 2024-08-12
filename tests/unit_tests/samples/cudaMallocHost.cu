// RUN: %run_test hipify "%s" "%t" %hipify_args %clang_args

// CHECK: #include <hip/hip_runtime.h>

template <typename T>
void check(T result, char const *const func, const char *const file, int const line) {
  if (result) {
    fprintf(stderr, "Error at %s:%d code=%d(%s) \" \n", file, line, static_cast<unsigned int>(result), func);
    exit(EXIT_FAILURE);
  }
}

#define checkErrors(val) check((val), #val, __FILE__, __LINE__)
#define num 1024

int main(int argc, const char *argv[]) {
  int *input = nullptr;
  int deviceCount = 0;
  // CHECK: checkErrors(hipGetDeviceCount(&deviceCount));
  checkErrors(cudaGetDeviceCount(&deviceCount));
  printf("Device Count: %d\n", deviceCount);
  // CHECK: hipDeviceProp_t deviceProp;
  cudaDeviceProp deviceProp;
  deviceProp.major = 0;
  deviceProp.minor = 0;
  int deviceID = 0;
  // CHECK: checkErrors(hipGetDeviceProperties(&deviceProp, deviceID));
  checkErrors(cudaGetDeviceProperties(&deviceProp, deviceID));
  // CHECK: checkErrors(hipSetDevice(deviceID));
  checkErrors(cudaSetDevice(deviceID));
  // CHECK: checkErrors(hipHostMalloc(&input, sizeof(int) * num * 2, hipHostMallocDefault));
  checkErrors(cudaMallocHost(&input, sizeof(int) * num * 2));
  for (int i = 0; i < num * 2; ++i) {
    input[i] = i;
  }
  // CHECK: checkErrors(hipHostFree(input));
  checkErrors(cudaFreeHost(input));
  // CHECK: checkErrors(hipDeviceSynchronize());
  checkErrors(cudaDeviceSynchronize());
  return 0;
}
