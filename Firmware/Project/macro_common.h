#ifndef _MACRO_COMMON_H_
#define _MACRO_COMMON_H_

#define min(a,b)            ((a) < (b) ? (a) : (b))
#define max(a,b)            ((a) > (b) ? (a) : (b))
#define scale_up(x)         ((x) << 8)
#define scale_down(x)       ((x) >> 8)

#endif // _MACRO_COMMON_H_

