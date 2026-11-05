/* A Shell gives 4 KB of stack; libnix's startup swaps to this much instead.
 * The engine's flood fills and the C++ frontend's requesters run deep.
 * GPL 3 or later, like Micropolis. */
unsigned long __stack = 512 * 1024;
static const char version[] __attribute__((used)) = "$VER: Micropolis 0.1.0 AmigaOS (05.11.2026)";
