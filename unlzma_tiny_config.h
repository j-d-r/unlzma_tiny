/* vi: set sw=4 ts=4: */
/*
 * SPDX-License-Identifier: GPL-2.0
 *
 * wrapper for target environment
 */

#ifndef UNLZMA_TINY_CONFIG_H_
#define UNLZMA_TINY_CONFIG_H_

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <inttypes.h>
#include <stddef.h>

#if DEBUG
# define warn(...) do { fprintf(stderr, __VA_ARGS__); fputc('\n', stderr);} while(0)
# define die(...) do { fprintf(stderr, __VA_ARGS__); fputc('\n', stderr); exit(-1); } while(0)
#else
# define warn(...) do { } while(0)
# define die(...) do { exit(-1); } while(0)
#endif

#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
# define SWAP_LE32(x) (x)
# define SWAP_LE64(x) (x)
#else
# define SWAP_LE32(x) __builtin_bswap32(x)
# define SWAP_LE64(x) __builtin_bswap64(x)
#endif

#if USE_ALLOCA
# define alloc_probs(size) alloca(size)
# define free_probs(ptr) do { } while(0)
#else
# define alloc_probs(size) malloc(size)
# define free_probs(ptr) free(ptr)
#endif

#define ALWAYS_INLINE __attribute__ ((always_inline)) inline
#define PACKED __attribute__ ((__packed__))
#define FAST_FUNC

#define speed_inline

#endif /* UNLZMA_TINY_CONFIG_H_ */
