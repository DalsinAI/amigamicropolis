/* The part of cybergraphics.library's interface this game uses, for
 * AmigaOS 3.x with any CyberGraphX-compatible RTG system (CyberGraphX,
 * Picasso96, GFOpenRTG). Values as the CyberGraphX V41 developer kit
 * documents them; written for this port so its tree builds on its own.
 * GPL 3 or later, like the rest of the port. */
#ifndef CYBERGRAPHX_CYBERGRAPHICS_H
#define CYBERGRAPHX_CYBERGRAPHICS_H

#include <exec/types.h>
#include <utility/tagitem.h>

#define CYBERGFXNAME "cybergraphics.library"

/* GetCyberMapAttr() */
#define CYBRMATTR_XMOD        0x80000001UL
#define CYBRMATTR_BPPIX       0x80000002UL
#define CYBRMATTR_PIXFMT      0x80000004UL
#define CYBRMATTR_WIDTH       0x80000005UL
#define CYBRMATTR_HEIGHT      0x80000006UL
#define CYBRMATTR_DEPTH       0x80000007UL
#define CYBRMATTR_ISCYBERGFX  0x80000008UL
#define CYBRMATTR_ISLINEARMEM 0x80000009UL

/* BestCModeIDTags() */
#define CYBRBIDTG_TB            (TAG_USER + 0x50000)
#define CYBRBIDTG_Depth         (CYBRBIDTG_TB + 0)
#define CYBRBIDTG_NominalWidth  (CYBRBIDTG_TB + 1)
#define CYBRBIDTG_NominalHeight (CYBRBIDTG_TB + 2)
#define CYBRBIDTG_MonitorID     (CYBRBIDTG_TB + 3)
#define CYBRBIDTG_BoardName     (CYBRBIDTG_TB + 5)

/* LockBitMapTags() */
#define LBMI_WIDTH       0x84001001UL
#define LBMI_HEIGHT      0x84001002UL
#define LBMI_DEPTH       0x84001003UL
#define LBMI_PIXFMT      0x84001004UL
#define LBMI_BYTESPERPIX 0x84001005UL
#define LBMI_BYTESPERROW 0x84001006UL
#define LBMI_BASEADDRESS 0x84001007UL

/* Pixel formats of a bitmap */
#define PIXFMT_LUT8    0UL
#define PIXFMT_RGB15   1UL
#define PIXFMT_BGR15   2UL
#define PIXFMT_RGB15PC 3UL
#define PIXFMT_BGR15PC 4UL
#define PIXFMT_RGB16   5UL
#define PIXFMT_BGR16   6UL
#define PIXFMT_RGB16PC 7UL
#define PIXFMT_BGR16PC 8UL
#define PIXFMT_RGB24   9UL
#define PIXFMT_BGR24   10UL
#define PIXFMT_ARGB32  11UL
#define PIXFMT_BGRA32  12UL
#define PIXFMT_RGBA32  13UL

/* AllocBitMap() of an RTG system: a bitmap of a given pixel format */
#ifndef BMF_SPECIALFMT
#define BMF_SPECIALFMT 0x80UL
#endif
#define SHIFT_PIXFMT(fmt) (((ULONG)(fmt)) << 24UL)

/* Source formats of WritePixelArray() */
#define RECTFMT_RGB   0UL
#define RECTFMT_RGBA  1UL
#define RECTFMT_ARGB  2UL
#define RECTFMT_LUT8  3UL
#define RECTFMT_GREY8 4UL

/* The AROS frontend keeps every picture as native 32-bit 0xAARRGGBB
 * values and hands them over as AROS's RECTFMT_BGRA32, which is what such
 * a buffer is in a little-endian machine's memory. In the 68k's memory the
 * same values are the bytes A, R, G, B: CyberGraphX's RECTFMT_ARGB. */
#define RECTFMT_BGRA32 RECTFMT_ARGB

#endif
