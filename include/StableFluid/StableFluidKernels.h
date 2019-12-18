#pragma once
#include "../../Extra/helper_functions.h"
#include "../../Extra/helper_cuda.h"
#include <cuda_runtime.h>
#include <cuda_gl_interop.h>

void WashColor(cudaArray_t arr,int width, int height,float delT);