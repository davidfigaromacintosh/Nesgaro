#if defined __UINT32_MAX__ or UINT32_MAX
  #include <inttypes.h>
  #else
  typedef unsigned char uint8_t;
  typedef unsigned short uint16_t;
  typedef unsigned long uint32_t;
  typedef unsigned long long uint64_t;
  #endif
