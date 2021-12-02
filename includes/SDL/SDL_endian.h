/*
    SDL - Simple DirectMedia Layer
    Copyright (C) 1997-2012 Sam Lantinga

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

    Sam Lantinga
    slouken@libsdl.org
*/

/**
 *  @file SDL_endian.h
 *  Functions for reading and writing endian-specific values
 */

#ifndef _SDL_endian_h
#define _SDL_endian_h

#include "SDL_stdinc.h"

/** @name SDL_ENDIANs
 *  The two types of endianness 
 */
/*@{*/
#define SDL_LIL_ENDIAN	1234
#define SDL_BIG_ENDIAN	4321
/*@}*/
#include <byteswap.h>
#include <endian.h>

#ifndef SDL_BYTEORDER	/* Not defined in SDL_config.h? */
#define SDL_BYTEORDER  __BYTE_ORDER
#if defined(__hppa__) || \
    defined(__m68k__) || defined(mc68000) || defined(_M_M68K) || \
    (defined(__MIPS__) && defined(__MISPEB__)) || \
    defined(__ppc__) || defined(__POWERPC__) || defined(_M_PPC) || \
    defined(__sparc__)
#define SDL_BYTEORDER	SDL_BIG_ENDIAN
#else
#define SDL_BYTEORDER	SDL_LIL_ENDIAN
#endif
#endif /* !SDL_BYTEORDER */


#include "begin_code.h"
/* Set up for C function definitions, even when using C++ */
#ifdef __cplusplus
extern "C" {
#endif


static __inline__ Uint16 SDL_Swap16(Uint16 x) { return bswap_16(x); }

static __inline__ Uint32 SDL_Swap32(Uint32 x) { return bswap_32(x); }

static __inline__ Uint64 SDL_Swap64(Uint64 x) { return bswap_64(x); }

/**
 *  @name SDL_Swap Functions
 *  Use inline functions for compilers that support them, and static
 *  functions for those that do not.  Because these functions become
 *  static for compilers that do not support inline functions, this
 *  header should only be included in files that actually use them.
 */
/*@{*/

/**
 *  @name SDL_SwapLE and SDL_SwapBE Functions
 *  Byteswap item from the specified endianness to the native endianness
 */
/*@{*/
#define SDL_SwapLE16(X)	htole16(X)
#define SDL_SwapLE32(X)	htole32(X)
#define SDL_SwapLE64(X)	htole64(X)
#define SDL_SwapBE16(X)	htobe16(X)
#define SDL_SwapBE32(X)	htobe32(X)
#define SDL_SwapBE64(X)	htobe64(X)
/*@}*/

/* Ends C function definitions when using C++ */
#ifdef __cplusplus
}
#endif
#include "close_code.h"

#endif /* _SDL_endian_h */
