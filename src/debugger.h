#ifndef DEBUGGER_H
#define DEBUGGER_H

#include "chip8.h"
#include "colors.h"
#include "platform.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

int platform_init_debugger(const char *title, int x, int y, int w, int h);
void debugger_shutdown(void);
void debugger_render_registers(const Chip8 *c8);

#endif // DEBUGGER_H
