/*
 * CC0 (Public domain)
 * see http://git.ozlabs.org/?p=ccan;a=blob;f=licenses/CC0;hb=HEAD
 */

/*
 * You can add the following to your .vim/after/syntax/c.vim to get
 * syntax highlighting for these new types
 *
 * syn keyword cType u64
 * syn keyword cType s64
 * syn keyword cType u32
 * syn keyword cType s32
 * syn keyword cType u16
 * syn keyword cType s16
 * syn keyword cType  u8
 * syn keyword cType  s8
 */

#ifndef CCAN_SHORT_TYPES_H
#define CCAN_SHORT_TYPES_H
#include <stdint.h>

typedef uint64_t u64;
typedef int64_t  s64;
typedef uint32_t u32;
typedef int32_t  s32;
typedef uint16_t u16;
typedef int16_t  s16;
typedef uint8_t   u8;
typedef int8_t    s8;

#endif /* CCAN_SHORT_TYPES_H */
