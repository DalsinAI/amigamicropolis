/* cybergraphics.library for GCC on the 68k: the calls this game makes.
 * The base is opened by amiga/amiga_libs.c. GPL 3 or later. */
#ifndef PROTO_CYBERGRAPHICS_H
#define PROTO_CYBERGRAPHICS_H

#include <exec/types.h>
#include <utility/tagitem.h>
#include <cybergraphx/cybergraphics.h>

struct BitMap;
struct RastPort;
struct Library;

#ifdef __cplusplus
extern "C" {
#endif
extern struct Library *CyberGfxBase;
#ifdef __cplusplus
}
#endif

static __inline__ ULONG
__cgx_GetCyberMapAttr(void *__base, struct BitMap *bm, ULONG attr)
{
	register ULONG _d0 __asm("d0") = attr;
	register ULONG _a0 __asm("a0") = (ULONG)bm;
	register void *_a6 __asm("a6") = __base;
	register ULONG _d1 __asm("d1");
	register ULONG _a1 __asm("a1");
	__asm__ __volatile__ ("jsr -96(%%a6)"
		: "+r" (_d0), "=r" (_d1), "+r" (_a0), "=r" (_a1)
		: "r" (_a6)
		: "fp0", "fp1", "cc", "memory");
	return _d0;
}

static __inline__ APTR
__cgx_LockBitMapTagList(void *__base, APTR bm, struct TagItem *tags)
{
	register ULONG _d0 __asm("d0");
	register ULONG _d1 __asm("d1");
	register ULONG _a0 __asm("a0") = (ULONG)bm;
	register ULONG _a1 __asm("a1") = (ULONG)tags;
	register void *_a6 __asm("a6") = __base;
	__asm__ __volatile__ ("jsr -168(%%a6)"
		: "=r" (_d0), "=r" (_d1), "+r" (_a0), "+r" (_a1)
		: "r" (_a6)
		: "fp0", "fp1", "cc", "memory");
	return (APTR)_d0;
}

static __inline__ void
__cgx_UnLockBitMap(void *__base, APTR handle)
{
	register ULONG _d0 __asm("d0");
	register ULONG _d1 __asm("d1");
	register ULONG _a0 __asm("a0") = (ULONG)handle;
	register ULONG _a1 __asm("a1");
	register void *_a6 __asm("a6") = __base;
	__asm__ __volatile__ ("jsr -174(%%a6)"
		: "=r" (_d0), "=r" (_d1), "+r" (_a0), "=r" (_a1)
		: "r" (_a6)
		: "fp0", "fp1", "cc", "memory");
}

static __inline__ ULONG
__cgx_WritePixelArray(void *__base, APTR src, UWORD srcx, UWORD srcy, UWORD srcmod,
	struct RastPort *rp, UWORD dstx, UWORD dsty, UWORD w, UWORD h, UBYTE fmt)
{
	register ULONG _a0 __asm("a0") = (ULONG)src;
	register ULONG _d0 __asm("d0") = srcx;
	register ULONG _d1 __asm("d1") = srcy;
	register ULONG _d2 __asm("d2") = srcmod;
	register ULONG _a1 __asm("a1") = (ULONG)rp;
	register ULONG _d3 __asm("d3") = dstx;
	register ULONG _d4 __asm("d4") = dsty;
	register ULONG _d5 __asm("d5") = w;
	register ULONG _d6 __asm("d6") = h;
	register ULONG _d7 __asm("d7") = fmt;
	register void *_a6 __asm("a6") = __base;
	__asm__ __volatile__ ("jsr -126(%%a6)"
		: "+r" (_d0), "+r" (_d1), "+r" (_a0), "+r" (_a1)
		: "r" (_d2), "r" (_d3), "r" (_d4), "r" (_d5), "r" (_d6), "r" (_d7), "r" (_a6)
		: "fp0", "fp1", "cc", "memory");
	return _d0;
}

static __inline__ ULONG
__cgx_BestCModeIDTagList(void *__base, struct TagItem *tags)
{
	register ULONG _d0 __asm("d0");
	register ULONG _d1 __asm("d1");
	register ULONG _a0 __asm("a0") = (ULONG)tags;
	register ULONG _a1 __asm("a1");
	register void *_a6 __asm("a6") = __base;
	__asm__ __volatile__ ("jsr -60(%%a6)"
		: "=r" (_d0), "=r" (_d1), "+r" (_a0), "=r" (_a1)
		: "r" (_a6)
		: "fp0", "fp1", "cc", "memory");
	return _d0;
}

#define GetCyberMapAttr(bm, attr) __cgx_GetCyberMapAttr(CyberGfxBase, (struct BitMap *)(bm), (ULONG)(attr))
#define LockBitMapTagList(bm, tags) __cgx_LockBitMapTagList(CyberGfxBase, (APTR)(bm), (struct TagItem *)(tags))
#define LockBitMapTags(bm, ...) ({ ULONG _t[] = { __VA_ARGS__ }; __cgx_LockBitMapTagList(CyberGfxBase, (APTR)(bm), (struct TagItem *)_t); })
#define BestCModeIDTags(...) ({ ULONG _t[] = { __VA_ARGS__ }; __cgx_BestCModeIDTagList(CyberGfxBase, (struct TagItem *)_t); })
#define UnLockBitMap(h) __cgx_UnLockBitMap(CyberGfxBase, (APTR)(h))
#define WritePixelArray(src, sx, sy, mod, rp, dx, dy, w, h, fmt) \
	__cgx_WritePixelArray(CyberGfxBase, (APTR)(src), (UWORD)(sx), (UWORD)(sy), (UWORD)(mod), \
		(struct RastPort *)(rp), (UWORD)(dx), (UWORD)(dy), (UWORD)(w), (UWORD)(h), (UBYTE)(fmt))

#endif
