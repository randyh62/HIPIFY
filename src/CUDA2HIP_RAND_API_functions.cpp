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

// Map of all functions
const std::map<llvm::StringRef, hipCounter> CUDA_RAND_FUNCTION_MAP {
  // RAND Host functions
  {"curandCreateGenerator",                         {"hiprandCreateGenerator",                         "rocrand_create_generator",                                   CONV_LIB_FUNC, API_RAND, 2}},
  {"curandCreateGeneratorHost",                     {"hiprandCreateGeneratorHost",                     "rocrand_create_generator_host_blocking",                     CONV_LIB_FUNC, API_RAND, 2}},
  {"curandCreatePoissonDistribution",               {"hiprandCreatePoissonDistribution",               "rocrand_create_poisson_distribution",                        CONV_LIB_FUNC, API_RAND, 2}},
  {"curandDestroyDistribution",                     {"hiprandDestroyDistribution",                     "rocrand_destroy_discrete_distribution",                      CONV_LIB_FUNC, API_RAND, 2}},
  {"curandDestroyGenerator",                        {"hiprandDestroyGenerator",                        "rocrand_destroy_generator",                                  CONV_LIB_FUNC, API_RAND, 2}},
  {"curandGenerate",                                {"hiprandGenerate",                                "rocrand_generate",                                           CONV_LIB_FUNC, API_RAND, 2}},
  {"curandGenerateLogNormal",                       {"hiprandGenerateLogNormal",                       "rocrand_generate_log_normal",                                CONV_LIB_FUNC, API_RAND, 2}},
  {"curandGenerateLogNormalDouble",                 {"hiprandGenerateLogNormalDouble",                 "rocrand_generate_log_normal_double",                         CONV_LIB_FUNC, API_RAND, 2}},
  {"curandGenerateLongLong",                        {"hiprandGenerateLongLong",                        "rocrand_generate_long_long",                                 CONV_LIB_FUNC, API_RAND, 2}},
  {"curandGenerateNormal",                          {"hiprandGenerateNormal",                          "rocrand_generate_normal",                                    CONV_LIB_FUNC, API_RAND, 2}},
  {"curandGenerateNormalDouble",                    {"hiprandGenerateNormalDouble",                    "rocrand_generate_normal_double",                             CONV_LIB_FUNC, API_RAND, 2}},
  {"curandGeneratePoisson",                         {"hiprandGeneratePoisson",                         "rocrand_generate_poisson",                                   CONV_LIB_FUNC, API_RAND, 2}},
  {"curandGenerateSeeds",                           {"hiprandGenerateSeeds",                           "rocrand_initialize_generator",                               CONV_LIB_FUNC, API_RAND, 2}},
  {"curandGenerateUniform",                         {"hiprandGenerateUniform",                         "rocrand_generate_uniform",                                   CONV_LIB_FUNC, API_RAND, 2}},
  {"curandGenerateUniformDouble",                   {"hiprandGenerateUniformDouble",                   "rocrand_generate_uniform_double",                            CONV_LIB_FUNC, API_RAND, 2}},
  {"curandGetDirectionVectors32",                   {"hiprandGetDirectionVectors32",                   "rocrand_get_direction_vectors32",                            CONV_LIB_FUNC, API_RAND, 2}},
  {"curandGetDirectionVectors64",                   {"hiprandGetDirectionVectors64",                   "rocrand_get_direction_vectors64",                            CONV_LIB_FUNC, API_RAND, 2}},
  {"curandGetProperty",                             {"hiprandGetProperty",                             "",                                                           CONV_LIB_FUNC, API_RAND, 2, UNSUPPORTED}},
  {"curandGetScrambleConstants32",                  {"hiprandGetScrambleConstants32",                  "rocrand_get_scramble_constants32",                           CONV_LIB_FUNC, API_RAND, 2}},
  {"curandGetScrambleConstants64",                  {"hiprandGetScrambleConstants64",                  "rocrand_get_scramble_constants64",                           CONV_LIB_FUNC, API_RAND, 2}},
  {"curandGetVersion",                              {"hiprandGetVersion",                              "rocrand_get_version",                                        CONV_LIB_FUNC, API_RAND, 2}},
  {"curandSetGeneratorOffset",                      {"hiprandSetGeneratorOffset",                      "rocrand_set_offset",                                         CONV_LIB_FUNC, API_RAND, 2}},
  {"curandSetGeneratorOrdering",                    {"hiprandSetGeneratorOrdering",                    "rocrand_set_ordering",                                       CONV_LIB_FUNC, API_RAND, 2}},
  {"curandSetPseudoRandomGeneratorSeed",            {"hiprandSetPseudoRandomGeneratorSeed",            "rocrand_set_seed",                                           CONV_LIB_FUNC, API_RAND, 2}},
  {"curandSetQuasiRandomGeneratorDimensions",       {"hiprandSetQuasiRandomGeneratorDimensions",       "rocrand_set_quasi_random_generator_dimensions",              CONV_LIB_FUNC, API_RAND, 2}},
  {"curandSetStream",                               {"hiprandSetStream",                               "rocrand_set_stream",                                         CONV_LIB_FUNC, API_RAND, 2}},
  {"curandMakeMTGP32Constants",                     {"hiprandMakeMTGP32Constants",                     "rocrand_make_constant",                                      CONV_LIB_FUNC, API_RAND, 2}},
  {"curandMakeMTGP32KernelState",                   {"hiprandMakeMTGP32KernelState",                   "rocrand_make_state_mtgp32",                                  CONV_LIB_FUNC, API_RAND, 2}},

  // RAND Device functions
  {"curand",                                        {"hiprand",                                        "rocrand",                                                    CONV_LIB_DEVICE_FUNC, API_RAND, 3}},
  {"curand_init",                                   {"hiprand_init",                                   "rocrand_init",                                               CONV_LIB_DEVICE_FUNC, API_RAND, 3}},
  {"curand_log_normal",                             {"hiprand_log_normal",                             "rocrand_log_normal",                                         CONV_LIB_DEVICE_FUNC, API_RAND, 3}},
  {"curand_log_normal_double",                      {"hiprand_log_normal_double",                      "rocrand_log_normal_double",                                  CONV_LIB_DEVICE_FUNC, API_RAND, 3}},
  {"curand_log_normal2",                            {"hiprand_log_normal2",                            "rocrand_log_normal2",                                        CONV_LIB_DEVICE_FUNC, API_RAND, 3}},
  {"curand_log_normal2_double",                     {"hiprand_log_normal2_double",                     "rocrand_log_normal_double2",                                 CONV_LIB_DEVICE_FUNC, API_RAND, 3}},
  {"curand_log_normal4",                            {"hiprand_log_normal4",                            "rocrand_log_normal4",                                        CONV_LIB_DEVICE_FUNC, API_RAND, 3}},
  {"curand_log_normal4_double",                     {"hiprand_log_normal4_double",                     "rocrand_log_normal_double4",                                 CONV_LIB_DEVICE_FUNC, API_RAND, 3}},
  {"curand_mtgp32_single",                          {"hiprand_mtgp32_single",                          "",                                                           CONV_LIB_DEVICE_FUNC, API_RAND, 3, UNSUPPORTED}},
  {"curand_mtgp32_single_specific",                 {"hiprand_mtgp32_single_specific",                 "",                                                           CONV_LIB_DEVICE_FUNC, API_RAND, 3, UNSUPPORTED}},
  {"curand_mtgp32_specific",                        {"hiprand_mtgp32_specific",                        "",                                                           CONV_LIB_DEVICE_FUNC, API_RAND, 3, UNSUPPORTED}},
  {"curand_normal",                                 {"hiprand_normal",                                 "rocrand_normal",                                             CONV_LIB_DEVICE_FUNC, API_RAND, 3}},
  {"curand_normal_double",                          {"hiprand_normal_double",                          "rocrand_normal_double",                                      CONV_LIB_DEVICE_FUNC, API_RAND, 3}},
  {"curand_normal2",                                {"hiprand_normal2",                                "rocrand_normal2",                                            CONV_LIB_DEVICE_FUNC, API_RAND, 3}},
  {"curand_normal2_double",                         {"hiprand_normal2_double",                         "rocrand_normal_double2",                                     CONV_LIB_DEVICE_FUNC, API_RAND, 3}},
  {"curand_normal4",                                {"hiprand_normal4",                                "rocrand_normal4",                                            CONV_LIB_DEVICE_FUNC, API_RAND, 3}},
  {"curand_normal4_double",                         {"hiprand_normal4_double",                         "rocrand_normal_double4",                                     CONV_LIB_DEVICE_FUNC, API_RAND, 3}},
  {"curand_uniform",                                {"hiprand_uniform",                                "rocrand_uniform",                                            CONV_LIB_DEVICE_FUNC, API_RAND, 3}},
  {"curand_uniform_double",                         {"hiprand_uniform_double",                         "rocrand_uniform_double",                                     CONV_LIB_DEVICE_FUNC, API_RAND, 3}},
  {"curand_uniform2_double",                        {"hiprand_uniform2_double",                        "rocrand_uniform_double2",                                    CONV_LIB_DEVICE_FUNC, API_RAND, 3}},
  {"curand_uniform4",                               {"hiprand_uniform4",                               "rocrand_uniform4",                                           CONV_LIB_DEVICE_FUNC, API_RAND, 3}},
  {"curand_uniform4_double",                        {"hiprand_uniform4_double",                        "rocrand_uniform_double4",                                    CONV_LIB_DEVICE_FUNC, API_RAND, 3}},
  {"curand_discrete",                               {"hiprand_discrete",                               "rocrand_discrete",                                           CONV_LIB_DEVICE_FUNC, API_RAND, 3}},
  {"curand_discrete4",                              {"hiprand_discrete4",                              "rocrand_discrete4",                                          CONV_LIB_DEVICE_FUNC, API_RAND, 3}},
  {"curand_poisson",                                {"hiprand_poisson",                                "rocrand_poisson",                                            CONV_LIB_DEVICE_FUNC, API_RAND, 3}},
  {"curand_poisson4",                               {"hiprand_poisson4",                               "rocrand_poisson4",                                           CONV_LIB_DEVICE_FUNC, API_RAND, 3}},
  {"curand_Philox4x32_10",                          {"hiprand_Philox4x32_10",                          "",                                                           CONV_LIB_DEVICE_FUNC, API_RAND, 3, UNSUPPORTED}},
  {"__curand_umul",                                 {"__hiprand_umul",                                 "",                                                           CONV_LIB_DEVICE_FUNC, API_RAND, 3, UNSUPPORTED}},
  // unchanged function names: skipahead, skipahead_sequence, skipahead_subsequence
};

const std::map<llvm::StringRef, cudaAPIversions> CUDA_RAND_FUNCTION_VER_MAP {
  {"curandGetProperty",                             {CUDA_80,  CUDA_0,   CUDA_0, }},
  {"__curand_umul",                                 {CUDA_115, CUDA_0,   CUDA_0, }},
};

const std::map<llvm::StringRef, hipAPIversions> HIP_RAND_FUNCTION_VER_MAP {
  {"hiprandCreateGenerator",                        {HIP_1050, HIP_0,    HIP_0,  }},
  {"hiprandCreateGeneratorHost",                    {HIP_1050, HIP_0,    HIP_0,  }},
  {"hiprandCreatePoissonDistribution",              {HIP_1050, HIP_0,    HIP_0,  }},
  {"hiprandDestroyDistribution",                    {HIP_1050, HIP_0,    HIP_0,  }},
  {"hiprandDestroyGenerator",                       {HIP_1050, HIP_0,    HIP_0,  }},
  {"hiprandGenerate",                               {HIP_1050, HIP_0,    HIP_0,  }},
  {"hiprandGenerateLogNormal",                      {HIP_1050, HIP_0,    HIP_0,  }},
  {"hiprandGenerateLogNormalDouble",                {HIP_1050, HIP_0,    HIP_0,  }},
  {"hiprandGenerateNormal",                         {HIP_1050, HIP_0,    HIP_0,  }},
  {"hiprandGenerateNormalDouble",                   {HIP_1050, HIP_0,    HIP_0,  }},
  {"hiprandGeneratePoisson",                        {HIP_1050, HIP_0,    HIP_0,  }},
  {"hiprandGenerateSeeds",                          {HIP_1050, HIP_0,    HIP_0,  }},
  {"hiprandGenerateUniform",                        {HIP_1050, HIP_0,    HIP_0,  }},
  {"hiprandGenerateUniformDouble",                  {HIP_1050, HIP_0,    HIP_0,  }},
  {"hiprandGetVersion",                             {HIP_1050, HIP_0,    HIP_0,  }},
  {"hiprandSetGeneratorOffset",                     {HIP_1050, HIP_0,    HIP_0,  }},
  {"hiprandSetPseudoRandomGeneratorSeed",           {HIP_1050, HIP_0,    HIP_0,  }},
  {"hiprandSetQuasiRandomGeneratorDimensions",      {HIP_1050, HIP_0,    HIP_0,  }},
  {"hiprandSetStream",                              {HIP_1050, HIP_0,    HIP_0,  }},
  {"hiprandMakeMTGP32Constants",                    {HIP_1050, HIP_0,    HIP_0,  }},
  {"hiprandMakeMTGP32KernelState",                  {HIP_1050, HIP_0,    HIP_0,  }},
  {"hiprand",                                       {HIP_1050, HIP_0,    HIP_0,  }},
  {"hiprand_init",                                  {HIP_1050, HIP_0,    HIP_0,  }},
  {"hiprand_log_normal",                            {HIP_1050, HIP_0,    HIP_0,  }},
  {"hiprand_log_normal_double",                     {HIP_1050, HIP_0,    HIP_0,  }},
  {"hiprand_log_normal2",                           {HIP_1050, HIP_0,    HIP_0,  }},
  {"hiprand_log_normal2_double",                    {HIP_1050, HIP_0,    HIP_0,  }},
  {"hiprand_log_normal4",                           {HIP_1050, HIP_0,    HIP_0,  }},
  {"hiprand_log_normal4_double",                    {HIP_1050, HIP_0,    HIP_0,  }},
  {"hiprand_normal",                                {HIP_1050, HIP_0,    HIP_0,  }},
  {"hiprand_normal_double",                         {HIP_1050, HIP_0,    HIP_0,  }},
  {"hiprand_normal2",                               {HIP_1050, HIP_0,    HIP_0,  }},
  {"hiprand_normal2_double",                        {HIP_1050, HIP_0,    HIP_0,  }},
  {"hiprand_normal4",                               {HIP_1050, HIP_0,    HIP_0,  }},
  {"hiprand_normal4_double",                        {HIP_1050, HIP_0,    HIP_0,  }},
  {"hiprand_uniform",                               {HIP_1050, HIP_0,    HIP_0,  }},
  {"hiprand_uniform_double",                        {HIP_1050, HIP_0,    HIP_0,  }},
  {"hiprand_uniform2_double",                       {HIP_1050, HIP_0,    HIP_0,  }},
  {"hiprand_uniform4",                              {HIP_1050, HIP_0,    HIP_0,  }},
  {"hiprand_uniform4_double",                       {HIP_1050, HIP_0,    HIP_0,  }},
  {"hiprand_discrete",                              {HIP_1050, HIP_0,    HIP_0,  }},
  {"hiprand_discrete4",                             {HIP_1050, HIP_0,    HIP_0,  }},
  {"hiprand_poisson",                               {HIP_1050, HIP_0,    HIP_0,  }},
  {"hiprand_poisson4",                              {HIP_1050, HIP_0,    HIP_0,  }},
  {"hiprandGetDirectionVectors32",                  {HIP_6000, HIP_0,    HIP_0,  }},
  {"hiprandGetDirectionVectors64",                  {HIP_6000, HIP_0,    HIP_0,  }},
  {"hiprandGetScrambleConstants32",                 {HIP_6000, HIP_0,    HIP_0,  }},
  {"hiprandGetScrambleConstants64",                 {HIP_6000, HIP_0,    HIP_0,  }},
  {"hiprandSetGeneratorOrdering",                   {HIP_6020, HIP_0,    HIP_0,  }},
  {"hiprandGenerateLongLong",                       {HIP_5050, HIP_0,    HIP_0,  }},

  {"rocrand_create_generator",                      {HIP_1050, HIP_0,    HIP_0,  }},
  {"rocrand_create_generator_host_blocking",        {HIP_6020, HIP_0,    HIP_0,  }},
  {"rocrand_destroy_generator",                     {HIP_1050, HIP_0,    HIP_0,  }},
  {"rocrand_generate",                              {HIP_1050, HIP_0,    HIP_0,  }},
  {"rocrand_generate_long_long",                    {HIP_5040, HIP_0,    HIP_0,  }},
  {"rocrand_generate_uniform",                      {HIP_1050, HIP_0,    HIP_0,  }},
  {"rocrand_generate_uniform_double",               {HIP_1050, HIP_0,    HIP_0,  }},
  {"rocrand_generate_normal",                       {HIP_1050, HIP_0,    HIP_0,  }},
  {"rocrand_generate_normal_double",                {HIP_1050, HIP_0,    HIP_0,  }},
  {"rocrand_generate_log_normal",                   {HIP_1050, HIP_0,    HIP_0,  }},
  {"rocrand_generate_log_normal_double",            {HIP_1050, HIP_0,    HIP_0,  }},
  {"rocrand_generate_poisson",                      {HIP_1050, HIP_0,    HIP_0,  }},
  {"rocrand_initialize_generator",                  {HIP_1050, HIP_0,    HIP_0,  }},
  {"rocrand_set_stream",                            {HIP_1050, HIP_0,    HIP_0,  }},
  {"rocrand_set_seed",                              {HIP_1050, HIP_0,    HIP_0,  }},
  {"rocrand_set_offset",                            {HIP_1050, HIP_0,    HIP_0,  }},
  {"rocrand_set_ordering",                          {HIP_5050, HIP_0,    HIP_0,  }},
  {"rocrand_set_quasi_random_generator_dimensions", {HIP_1050, HIP_0,    HIP_0,  }},
  {"rocrand_get_version",                           {HIP_1050, HIP_0,    HIP_0,  }},
  {"rocrand_create_poisson_distribution",           {HIP_1050, HIP_0,    HIP_0,  }},
  {"rocrand_get_direction_vectors32",               {HIP_6000, HIP_0,    HIP_0,  }},
  {"rocrand_get_direction_vectors64",               {HIP_6000, HIP_0,    HIP_0,  }},
  {"rocrand_get_scramble_constants32",              {HIP_6000, HIP_0,    HIP_0,  }},
  {"rocrand_get_scramble_constants64",              {HIP_6000, HIP_0,    HIP_0,  }},
  {"rocrand_destroy_discrete_distribution",         {HIP_1050, HIP_0,    HIP_0,  }},
  {"rocrand_make_constant",                         {HIP_1050, HIP_0,    HIP_0,  }},
  {"rocrand_make_state_mtgp32",                     {HIP_1050, HIP_0,    HIP_0,  }},
  {"rocrand",                                       {HIP_1050, HIP_0,    HIP_0,  }},
  {"rocrand_init",                                  {HIP_1050, HIP_0,    HIP_0,  }},
  {"rocrand_log_normal",                            {HIP_1050, HIP_0,    HIP_0,  }},
  {"rocrand_log_normal_double",                     {HIP_1050, HIP_0,    HIP_0,  }},
  {"rocrand_log_normal2",                           {HIP_1050, HIP_0,    HIP_0,  }},
  {"rocrand_log_normal_double2",                    {HIP_1050, HIP_0,    HIP_0,  }},
  {"rocrand_log_normal4",                           {HIP_1050, HIP_0,    HIP_0,  }},
  {"rocrand_log_normal_double4",                    {HIP_1050, HIP_0,    HIP_0,  }},
  {"rocrand_normal",                                {HIP_1050, HIP_0,    HIP_0,  }},
  {"rocrand_normal_double",                         {HIP_1050, HIP_0,    HIP_0,  }},
  {"rocrand_normal2",                               {HIP_1050, HIP_0,    HIP_0,  }},
  {"rocrand_normal_double2",                        {HIP_1050, HIP_0,    HIP_0,  }},
  {"rocrand_normal4",                               {HIP_1050, HIP_0,    HIP_0,  }},
  {"rocrand_normal_double4",                        {HIP_1050, HIP_0,    HIP_0,  }},
  {"rocrand_uniform",                               {HIP_1050, HIP_0,    HIP_0,  }},
  {"rocrand_uniform_double",                        {HIP_1050, HIP_0,    HIP_0,  }},
  {"rocrand_uniform_double2",                       {HIP_1050, HIP_0,    HIP_0,  }},
  {"rocrand_uniform4",                              {HIP_1050, HIP_0,    HIP_0,  }},
  {"rocrand_uniform_double4",                       {HIP_1050, HIP_0,    HIP_0,  }},
  {"rocrand_discrete",                              {HIP_1050, HIP_0,    HIP_0,  }},
  {"rocrand_discrete4",                             {HIP_1050, HIP_0,    HIP_0,  }},
  {"rocrand_poisson",                               {HIP_1050, HIP_0,    HIP_0,  }},
  {"rocrand_poisson4",                              {HIP_1050, HIP_0,    HIP_0,  }},
};

const std::map<unsigned int, llvm::StringRef> CUDA_RAND_API_SECTION_MAP {
  {1, "CURAND Data types"},
  {2, "Host API Functions"},
  {3, "Device API Functions"},
};
