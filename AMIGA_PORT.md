Micropolis for AmigaOS 3.x
==========================

Micropolis is the GPL release of the original SimCity Classic simulation
by Will Wright and Don Hopkins. This is a port to AmigaOS 3.x on a 68040 or
68060 with an FPU and an RTG graphics card.

Source
------

The port starts from Tomasz Staniak's "Micropolis for AROS"
(https://github.com/tomaszstaniak/aros-micropolis, GPL 3 or later, commit
79e360658640dda67a2cc9b156e0833835f4fd0a, 0.1.0-rc4). It is a native
Intuition / GadTools / ASL / CyberGraphics / AHI front end over the
MicropolisCore C++ engine (https://github.com/SimHacker/MicropolisCore,
pinned at 69ccf87ed72d2d2950b70cf16ef1391439bd9d48 with the AROS port's
patch series). It already plays the whole classic game: the startup screen
with the eight scenarios, every tool and the pie menus, budget, evaluation,
graphs, overview map, messages, disasters, and load/save of .cty cities.
Since AROS has the AmigaOS 3.1 API, nearly all of it builds for the 68k
unchanged; no SDL is needed.

What was done for AmigaOS 3.x
-----------------------------

* `amiga/Makefile.amigaos`: one make file for GFOpenAmigaGCC 16.2,
  `-noixemul -m68040 -m68881 -O2`, C++17. The variables (`STOVE`, `NDK`,
  `DEPS`, `ICONTOOL`) default to the CradleLab paths.
* `amiga/deps/micropoliscore/`: the engine sources at the pin with the
  whole patch series applied, plus the game data the drawer needs (cities,
  tiles.bmp, sprites, licences), so the tree builds without fetching
  anything. `patches/micropoliscore/` and `series` still say how it was
  made.
* `amiga/data/sounds/`: the original MP3 effects decoded to the mono
  22050 Hz 16-bit WAV files the AHI player reads (the AROS build did this
  with ffmpeg at staging time).
* `amiga/include/`: what the OS 3.x NDK lacks: CyberGraphX's constants and
  the five calls the game makes (`WritePixelArray`, `LockBitMapTags`,
  `UnLockBitMap`, `GetCyberMapAttr`, `BestCModeIDTags`), the AHI request,
  the raw key names, and `amiga_prelude.h` (AROS's `IPTR`/`RAWARG` as
  32-bit types, and pthread.h first so libstdc++'s cancellation macros do
  not turn every `close()` method into a call of POSIX `close()`).
* `amiga/amiga_libs.c` opens cybergraphics.library (libnix opens the rest)
  and says plainly that an RTG system is needed when it is missing.
  `amiga/stack.c` asks for a 512 KB stack and holds the `$VER:` string;
  `amiga/pthread_stubs.c` is the single-thread pthread for libstdc++.
* Pixels: the front end keeps every picture as native 0xAARRGGBB words and
  hands them to AROS as `RECTFMT_BGRA32`. In the 68k's memory those words
  are A, R, G, B bytes, so here `RECTFMT_BGRA32` is CyberGraphX's
  `RECTFMT_ARGB`. The off-screen map bitmap is a friend of the screen's
  bitmap (in the screen's own format) instead of a 32-bit ARGB bitmap, so
  WritePixelArray converts once and the window blit is a plain copy on
  15/16/24/32-bit screens alike; the direct-lock fallback is only used on an
  ARGB32 bitmap.
* Display: the map window opens on the Workbench when that is an RTG
  screen of 15 bits or more. On a planar or 8-bit Workbench the game opens
  its own 640x480 16-bit RTG screen (`BestCModeIDTags`). F9's screen-mode
  requester now offers 15- and 16-bit modes as well as 24/32.
* Files: everything is found from PROGDIR: (the game changes to its own
  drawer on start), and the save/load requester starts in `PROGDIR:Saves`
  instead of AROS's `SYS:Micropolis`. The "does this name exist" test of
  the safe save asks DOS (Lock/IoErr) instead of trusting libnix's errno.
  icon.library V37 is enough for the icons the game writes beside saved
  cities.

Big-endian city files
---------------------

A .cty file is a stream of big-endian 16-bit words on every platform (the
Mac and Unix originals, Windows, and the web version alike). The engine
swaps words on a little-endian host and must not on a big-endian one, but
it decided that with `#if !defined(__BIG_ENDIAN__)`, which GCC for m68k
does not define: on the Amiga every city would have loaded and saved
byte-swapped. Patch `0010-big-endian-hosts` decides on `__BYTE_ORDER__`
instead (checked: the 68k fileio.o has no swap, an x86 build still does).
The 32-bit fields of the history block are put together from two words
explicitly, and the front end's BMP, PNG, WAV and art loaders all read
bytes, so they do not depend on byte order. Cities saved on a PC and on
the Amiga are the same bytes and load on both.

Building
--------

    make -f amiga/Makefile.amigaos -j2

with, if they are not at the default places:

    STOVE=/path/to/openamigagcc-16.2.0-open4-x86_64-linux
    NDK=/path/to/OpenNDK/Include_H
    DEPS=/path/to/m68k-amigaos          (libpng, zlib)
    ICONTOOL=/path/to/amicradle/scripts/port_icons.py

It builds `build/amigaos/Micropolis.debug`, strips it to
`dist/Micropolis/Micropolis` and lays out the drawer `dist/Micropolis/`
with `dist/Micropolis.info` beside it. Python 3 makes the classic art
headers and the startup BMPs (`scripts/build-classic-art.py`,
`scripts/build-startup-art.py`) and the GlowIcons
(`amiga/icons/icons.json`).

The drawer
----------

    Micropolis          the program (Workbench or Shell)
    CITY.CTY            Haight-Ashbury, opened by its icon
    cities/             the eight scenarios and 24 classic cities
    Saves/              where the requester starts for your cities
    tiles.bmp sprites/ startup/ sounds/ icons/   game data
    Licenses/ COPYING.txt ReadMe

Double-click a city icon to open that city directly. Cities you save get
an icon of their own. Keys: F1-F7 windows (commands, budget, evaluation,
messages, graphs, speed, overview), F9 screen mode, F10 own screen /
Workbench, Space run/pause, S/L save/load, Esc quit, + and - zoom, Shift
and the left button for the pie menu, the right button for the menus.

Needs
-----

* AmigaOS 3.x, 68040 or 68060 with FPU.
* An RTG system with cybergraphics.library V40+ (CyberGraphX, Picasso96 or
  GFOpenRTG) and a 15/16/24/32-bit screen mode of at least 640x480.
* About 8 MB of free memory.
* AHI for the sound effects (optional: without it the game is silent).
* A NewMouse-compatible mouse driver for the wheel zoom (optional).

Known limits
------------

* No AGA/ECS: all drawing is 32-bit through CyberGraphics.
* The whole map view is scaled and converted every frame on the CPU; at
  100% zoom on a 640x480 window that is ~300 KB a frame. Slow on a 68040,
  and 200% zoom costs the most.
* No music, as in the original (sound effects only).
* The AROS port's host tests and release scripts are kept but are not part
  of this build.
* Each save of an existing city keeps the previous file as `NAME.bak`
  (then `.bak.1`, ...), as the AROS port does; delete old ones by hand.
