#include "debugger.h"

static SDL_Window *debugger_reg_window = NULL;
static SDL_Renderer *debugger_reg_renderer = NULL;

void debugger_render_registers(const Chip8 *c8) {
#ifdef USE_SDL
  if (!debugger_reg_renderer || !c8)
    return;

  SDL_SetRenderDrawColor(debugger_reg_renderer, CRT_DARK_BG.r, CRT_DARK_BG.g,
                         CRT_DARK_BG.b, CRT_DARK_BG.a);

  SDL_RenderClear(debugger_reg_renderer);

  const int origin_x = 10;
  const int origin_y = 10;

  char text_buffer[64];

  for (size_t register_index = 0; register_index < 20; register_index++) {

    size_t grid_col = register_index / 10;
    size_t grid_row = register_index % 10;

    switch (register_index) {
    case 0 ... 15:
      snprintf(text_buffer, sizeof(text_buffer), "V%lX = %02X",
               (unsigned long)register_index, c8->V[register_index]);
      break;

    case 16:
      snprintf(text_buffer, sizeof(text_buffer), "I  = %03X", c8->I);
      break;

    case 17:
      snprintf(text_buffer, sizeof(text_buffer), "PC = %03X", c8->pc);
      break;

    case 18:
      snprintf(text_buffer, sizeof(text_buffer), "SP = %X", c8->sp);
      break;

    case 19:
      snprintf(text_buffer, sizeof(text_buffer), "DT = %02X", c8->timers.dt);
      break;
    }

    platform_render_text(debugger_reg_renderer,
                         origin_x + (int)(grid_col * 110),
                         origin_y + (int)(grid_row * 20), text_buffer);
  }

  SDL_RenderPresent(debugger_reg_renderer);
#endif
}

int platform_init_debugger(const char *title, int x, int y, int w, int h) {
#ifdef USE_SDL
  if (!title)
    return -1;

  return platform_create_window(title, x, y, w, h, &debugger_reg_window,
                                &debugger_reg_renderer);
#else
  (void)title;
  (void)x;
  (void)y;
  (void)w;
  (void)h;
  return 0;
#endif
}

void debugger_shutdown() {
#ifdef USE_SDL
  if (debugger_reg_renderer) {
    SDL_DestroyRenderer(debugger_reg_renderer);
    debugger_reg_renderer = NULL;
  }
  if (debugger_reg_window) {
    SDL_DestroyWindow(debugger_reg_window);
    debugger_reg_window = NULL;
  }
#endif
}
