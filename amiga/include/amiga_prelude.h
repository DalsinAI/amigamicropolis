/* Included before every file of the game on AmigaOS 3.x: the AROS SDK's
 * names for types the frontend uses, in the OS 3.x NDK's terms.
 * GPL 3 or later, like the rest of the port. */
#ifndef AMIGA_PRELUDE_H
#define AMIGA_PRELUDE_H
#ifdef __cplusplus
/* libstdc++ pulls in the toolchain's pthread.h, which turns close(), read()
 * and friends into macros when <unistd.h> came first: then every member
 * function called close() (GameAudio's, the windows') fails to compile.
 * Seen first, pthread.h finds no <unistd.h> and wraps nothing. */
#include <pthread.h>
#endif
#include <exec/types.h>
/* A pointer-sized integer: 32 bits on the 68k. */
typedef ULONG IPTR;
typedef LONG SIPTR;
/* The argument array of EasyRequestArgs() and friends. */
typedef APTR RAWARG;
#ifndef BNULL
#define BNULL ((BPTR)0)
#endif
#ifdef __cplusplus
extern "C" {
#endif
/* amiga/amiga_libs.c */
int amiga_open_libs(void);
void amiga_close_libs(void);
#ifdef __cplusplus
}
#endif
#endif
