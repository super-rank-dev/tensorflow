/* Copyright 2015 The TensorFlow Authors. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/

// See docs in ../ops/array_ops.cc.
#include "tensorflow/core/kernels/debug_ops.h"

#include "tensorflow/core/framework/op_kernel.h"
#include "tensorflow/core/framework/register_types.h"
#include "tensorflow/core/framework/tensor.h"
#include "tensorflow/core/framework/types.h"

namespace tensorflow {

// Register Copy ops.
REGISTER_KERNEL_BUILDER(Name("Copy").Device(DEVICE_CPU), CopyOp);

REGISTER_KERNEL_BUILDER(Name("CopyHost").Device(DEVICE_CPU), CopyOp);

REGISTER_KERNEL_BUILDER(Name("Copy").Device(DEVICE_DEFAULT), CopyOp);

REGISTER_KERNEL_BUILDER(Name("CopyHost")
                            .Device(DEVICE_DEFAULT)
                            .HostMemory("input")
                            .HostMemory("output"),
                        CopyOp);

// Register debug identity (non-ref and ref) ops.
REGISTER_KERNEL_BUILDER(Name("DebugIdentity").Device(DEVICE_CPU),
                        DebugIdentityOp);

REGISTER_KERNEL_BUILDER(Name("DebugIdentity")
                            .Device(DEVICE_DEFAULT)
                            .HostMemory("input")
                            .HostMemory("output"),
                        DebugIdentityOp);

REGISTER_KERNEL_BUILDER(Name("DebugIdentityV3")
                            .Device(DEVICE_DEFAULT)
                            .HostMemory("input")
                            .HostMemory("output"),
                        DebugIdentityV3Op);

// Register debug NaN-counter (non-ref and ref) ops.
#define REGISTER_DEBUG_NAN_COUNT(type)                                    \
  REGISTER_KERNEL_BUILDER(                                                \
      Name("DebugNanCount").Device(DEVICE_CPU).TypeConstraint<type>("T"), \
      DebugNanCountOp<type>);
TF_CALL_REAL_NUMBER_TYPES(REGISTER_DEBUG_NAN_COUNT);

#define REGISTER_DEFAULT_DEBUG_NAN_COUNT(type)            \
  REGISTER_KERNEL_BUILDER(Name("DebugNanCount")           \
                              .Device(DEVICE_DEFAULT)     \
                              .HostMemory("input")        \
                              .HostMemory("output")       \
                              .TypeConstraint<type>("T"), \
                          DebugNanCountOp<type>);
REGISTER_DEFAULT_DEBUG_NAN_COUNT(Eigen::half);
REGISTER_DEFAULT_DEBUG_NAN_COUNT(float);
REGISTER_DEFAULT_DEBUG_NAN_COUNT(double);

// Register debug numeric summary ops.
#define REGISTER_DEBUG_NUMERIC_SUMMARY_COUNT(type)        \
  REGISTER_KERNEL_BUILDER(Name("DebugNumericSummary")     \
                              .Device(DEVICE_CPU)         \
                              .TypeConstraint<type>("T"), \
                          DebugNumericSummaryOp<type>);
TF_CALL_bool(REGISTER_DEBUG_NUMERIC_SUMMARY_COUNT);
TF_CALL_INTEGRAL_TYPES(REGISTER_DEBUG_NUMERIC_SUMMARY_COUNT);
TF_CALL_float(REGISTER_DEBUG_NUMERIC_SUMMARY_COUNT);
TF_CALL_double(REGISTER_DEBUG_NUMERIC_SUMMARY_COUNT);

#define REGISTER_DEFAULT_DEBUG_NUMERIC_SUMMARY_COUNT(type) \
  REGISTER_KERNEL_BUILDER(Name("DebugNumericSummary")      \
                              .Device(DEVICE_DEFAULT)      \
                              .HostMemory("input")         \
                              .HostMemory("output")        \
                              .TypeConstraint<type>("T"),  \
                          DebugNumericSummaryOp<type>);
TF_CALL_bool(REGISTER_DEFAULT_DEBUG_NUMERIC_SUMMARY_COUNT);
TF_CALL_INTEGRAL_TYPES(REGISTER_DEFAULT_DEBUG_NUMERIC_SUMMARY_COUNT);
TF_CALL_float(REGISTER_DEFAULT_DEBUG_NUMERIC_SUMMARY_COUNT);
TF_CALL_double(REGISTER_DEFAULT_DEBUG_NUMERIC_SUMMARY_COUNT);

#undef REGISTER_DEFAULT_DEBUG_NUMERIC_SUMMARY_COUNT

REGISTER_KERNEL_BUILDER(Name("DebugIdentityV2").Device(DEVICE_CPU),
                        DebugIdentityV2Op);

REGISTER_KERNEL_BUILDER(Name("DebugIdentityV2")
                            .Device(DEVICE_DEFAULT)
                            .HostMemory("input")
                            .HostMemory("output"),
                        DebugIdentityV2Op);

#define REGISTER_DEBUG_NUMERIC_SUMMARY_V2_FLOAT(type)                 \
  REGISTER_KERNEL_BUILDER(Name("DebugNumericSummaryV2")               \
                              .Device(DEVICE_CPU)                     \
                              .TypeConstraint<type>("T")              \
                              .TypeConstraint<float>("output_dtype"), \
                          DebugNumericSummaryV2Op<CPUDevice, type, float>);
TF_CALL_half(REGISTER_DEBUG_NUMERIC_SUMMARY_V2_FLOAT);
TF_CALL_bfloat16(REGISTER_DEBUG_NUMERIC_SUMMARY_V2_FLOAT);
TF_CALL_float(REGISTER_DEBUG_NUMERIC_SUMMARY_V2_FLOAT);
TF_CALL_double(REGISTER_DEBUG_NUMERIC_SUMMARY_V2_FLOAT);
TF_CALL_INTEGRAL_TYPES(REGISTER_DEBUG_NUMERIC_SUMMARY_V2_FLOAT);
TF_CALL_bool(REGISTER_DEBUG_NUMERIC_SUMMARY_V2_FLOAT);
// TODO(cais): Add string support.

#define REGISTER_DEBUG_NUMERIC_SUMMARY_V2_DOUBLE(type)                 \
  REGISTER_KERNEL_BUILDER(Name("DebugNumericSummaryV2")                \
                              .Device(DEVICE_CPU)                      \
                              .TypeConstraint<type>("T")               \
                              .TypeConstraint<double>("output_dtype"), \
                          DebugNumericSummaryV2Op<CPUDevice, type, double>);
TF_CALL_half(REGISTER_DEBUG_NUMERIC_SUMMARY_V2_DOUBLE);
TF_CALL_bfloat16(REGISTER_DEBUG_NUMERIC_SUMMARY_V2_DOUBLE);
TF_CALL_float(REGISTER_DEBUG_NUMERIC_SUMMARY_V2_DOUBLE);
TF_CALL_double(REGISTER_DEBUG_NUMERIC_SUMMARY_V2_DOUBLE);
TF_CALL_INTEGRAL_TYPES(REGISTER_DEBUG_NUMERIC_SUMMARY_V2_DOUBLE);
TF_CALL_bool(REGISTER_DEBUG_NUMERIC_SUMMARY_V2_DOUBLE);
// TODO(cais): Add string support.

#if GOOGLE_CUDA || TENSORFLOW_USE_ROCM
#define REGISTER_DEBUG_NUMERIC_SUMMARY_V2_GPU(in_type, out_type) \
  REGISTER_KERNEL_BUILDER(                                       \
      Name("DebugNumericSummaryV2")                              \
          .Device(DEVICE_GPU)                                    \
          .TypeConstraint<in_type>("T")                          \
          .TypeConstraint<out_type>("output_dtype"),             \
      DebugNumericSummaryV2Op<GPUDevice, in_type, out_type>);

REGISTER_DEBUG_NUMERIC_SUMMARY_V2_GPU(Eigen::half, float);
REGISTER_DEBUG_NUMERIC_SUMMARY_V2_GPU(float, float);
REGISTER_DEBUG_NUMERIC_SUMMARY_V2_GPU(double, float);
REGISTER_DEBUG_NUMERIC_SUMMARY_V2_GPU(int16, float);
REGISTER_DEBUG_NUMERIC_SUMMARY_V2_GPU(int32, float);

REGISTER_DEBUG_NUMERIC_SUMMARY_V2_GPU(Eigen::half, double);
REGISTER_DEBUG_NUMERIC_SUMMARY_V2_GPU(float, double);
REGISTER_DEBUG_NUMERIC_SUMMARY_V2_GPU(double, double);
REGISTER_DEBUG_NUMERIC_SUMMARY_V2_GPU(int16, double);
REGISTER_DEBUG_NUMERIC_SUMMARY_V2_GPU(int32, double);

#endif  // GOOGLE_CUDA || TENSORFLOW_USE_ROCM

}  // namespace tensorflow
