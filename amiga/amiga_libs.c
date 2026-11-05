/* The one library libnix does not open for us. Without an RTG system
 * (cybergraphics.library: CyberGraphX, Picasso96 or GFOpenRTG) the game
 * cannot draw its 32-bit pictures, so it says so and stops.
 * GPL 3 or later, like the rest of the port. */
#include <exec/types.h>
#include <intuition/intuition.h>
#include <proto/exec.h>
#include <proto/intuition.h>

struct Library *CyberGfxBase = 0;

int amiga_open_libs(void)
{
	if (!CyberGfxBase)
		CyberGfxBase = OpenLibrary((CONST_STRPTR)"cybergraphics.library", 40);
	if (!CyberGfxBase) {
		struct EasyStruct es = { sizeof(struct EasyStruct), 0,
			(UBYTE *)"Micropolis",
			(UBYTE *)"Micropolis needs an RTG graphics system\n"
			         "(cybergraphics.library V40 or later)\n"
			         "and a 15-, 16-, 24- or 32-bit screen.",
			(UBYTE *)"Quit" };
		EasyRequestArgs(0, &es, 0, 0);
		return 0;
	}
	return 1;
}

void amiga_close_libs(void)
{
	if (CyberGfxBase) {
		CloseLibrary(CyberGfxBase);
		CyberGfxBase = 0;
	}
}
