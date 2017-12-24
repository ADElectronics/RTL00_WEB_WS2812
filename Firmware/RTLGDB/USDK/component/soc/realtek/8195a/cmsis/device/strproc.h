/*
 *  Routines to access hardware
 *
 *  Copyright (c) 2013 Realtek Semiconductor Corp.
 *
 *  This module is a confidential and proprietary property of RealTek and
 *  possession or use of this module requires written permission of RealTek.
 */

#ifndef _STRPROC_H_
#define _STRPROC_H_

#include <stddef.h> /* for size_t */
#include <stdarg.h>

#ifndef isprint
#define in_range(c, lo, up)  ((uint8_t)c >= lo && (uint8_t)c <= up)
#define isprint(c)           in_range(c, 0x20, 0x7f)
#define isdigit(c)           in_range(c, '0', '9')
#define isxdigit(c)          (isdigit(c) || in_range(c, 'a', 'f') || in_range(c, 'A', 'F'))
#define islower(c)           in_range(c, 'a', 'z')
#define isspace(c)           (c == ' ' || c == '\f' || c == '\n' || c == '\r' || c == '\t' || c == '\v' || c == ',')
#endif  

#ifdef _MSC_VER // IntelliSense
#define _LONG_CALL_ROM_
#endif

extern _LONG_CALL_ROM_ char *_strncpy(char *dest, const char *src, size_t count);
extern _LONG_CALL_ROM_ char *_strcpy(char *dest, const char *src);
extern _LONG_CALL_ROM_ size_t _strlen(const char *s);
extern _LONG_CALL_ROM_ size_t _strnlen(const char *s, size_t count);
extern _LONG_CALL_ROM_ int _strcmp(const char *cs, const char *ct);
extern _LONG_CALL_ROM_ int _strncmp(const char *cs, const char *ct, size_t count);
extern _LONG_CALL_ROM_ int _sscanf(const char *buf, const char *fmt, ...);
extern _LONG_CALL_ROM_ char *_strsep(char **s, const char *ct);
extern _LONG_CALL_ROM_ char *skip_spaces(const char *str);
extern _LONG_CALL_ROM_ int skip_atoi(const char **s);
extern _LONG_CALL_ROM_ int _vsscanf(const char *buf, const char *fmt, va_list args);
extern _LONG_CALL_ROM_ unsigned long long simple_strtoull(const char *cp, char **endp, unsigned int base);
extern _LONG_CALL_ROM_ long simple_strtol(const char *cp, char **endp, unsigned int base);
extern _LONG_CALL_ROM_ long long simple_strtoll(const char *cp, char **endp, unsigned int base);
extern _LONG_CALL_ROM_ unsigned long simple_strtoul(const char *cp, char **endp, unsigned int base);
extern _LONG_CALL_ROM_ const char *_parse_integer_fixup_radix(const char *s, unsigned int *base);
extern _LONG_CALL_ROM_ unsigned int _parse_integer(const char *s, unsigned int base, unsigned long long *p);
extern _LONG_CALL_ROM_ uint64_t div_u64(uint64_t dividend, uint32_t divisor);
extern _LONG_CALL_ROM_ int64_t div_s64(int64_t dividend, int32_t divisor);
extern _LONG_CALL_ROM_ uint64_t div_u64_rem(uint64_t dividend, uint32_t divisor, uint32_t *remainder);
extern _LONG_CALL_ROM_ int64_t div_s64_rem(int64_t dividend, int32_t divisor, int32_t *remainder);
extern _LONG_CALL_ROM_ char *_strpbrk(const char *cs, const char *ct);
extern _LONG_CALL_ROM_ char *_strchr(const char *s, int c);


extern _LONG_CALL_ROM_ void
prvStrCpy(
    IN  uint8_t  *pDES,
    IN  const uint8_t  *pSRC
);

extern _LONG_CALL_ROM_ uint32_t
prvStrLen(
    IN  const   uint8_t  *pSRC
);

extern _LONG_CALL_ROM_  uint8_t
prvStrCmp(
    IN  const   uint8_t  *string1,
    IN  const   uint8_t  *string2
);

extern _LONG_CALL_ROM_ uint8_t*
StrUpr(
    IN  uint8_t  *string
);

extern _LONG_CALL_ROM_ int prvAtoi(
	IN const char * s
);

extern _LONG_CALL_ROM_ const char * prvStrStr(
	IN const char * str1, 
	IN const char * str2
);

#ifndef __GNUC__
/*
 * Fast implementation of tolower() for internal usage. Do not use in your
 * code.
 */
static inline char _tolower(const char c)
{
    return c | 0x20;
}
#endif

/* Fast check for octal digit */
static inline int isodigit(const char c)
{
    return c >= '0' && c <= '7';
}
#ifndef strtoul
#define strtoul(str, endp, base)       simple_strtoul(str, endp, base)
#endif
#ifndef strtol
#define strtol(str, endp, base)        simple_strtol(str, endp, base)
#endif

#endif
