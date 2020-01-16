#pragma once
#include "../../Extra/helper_functions.h"
#include "../../Extra/helper_cuda.h"
#include <cuda_runtime.h>
#include <cuda_gl_interop.h>
#define DIM 512
#define PI 3.1415926535897932f
#define MAX_TEMP 1.0f
#define MIN_TEMP 0.0001f
#define SPEED   0.25f
void init_datablock();