#ifndef HELPERS_H
#define HELPERS_H

#include <stdlib.h>
#include "status.h"

typedef enum {
  DISPLAY_UNKNOWN,
  DISPLAY_X11,
  DISPLAY_WAYLAND
} DisplayServer;

DisplayServer detect_display_server(void);

int copy_to_clipboard(DisplayServer env, char const *password);

#endif
