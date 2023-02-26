#ifndef MACROS_HEADER
#define MACROS_HEADER

#define max(a, b) ((a > b) ? a : b)
#define min(a, b) ((a < b) ? a : b)
#define clamp(lb, v, hb) (max(lb, min(v, hb)))

#endif