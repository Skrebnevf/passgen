#include "helpers.h"
#include <string.h>
#include <stdio.h>

DisplayServer detect_display_server(void) {
    const char *session_type = getenv("XDG_SESSION_TYPE");

    if (session_type != NULL) {
        if (strcmp(session_type, "wayland") == 0)
            return DISPLAY_WAYLAND;
        if (strcmp(session_type, "x11") == 0)
            return DISPLAY_X11;
    }

    if (getenv("WAYLAND_DISPLAY") != NULL) {
        return DISPLAY_WAYLAND;
    }

    if (getenv("DISPLAY") != NULL) {
        return DISPLAY_X11;
    }

    return DISPLAY_UNKNOWN;
}

int copy_to_clipboard(DisplayServer env, char const *password) {
#if defined(__APPLE__) || defined(__FreeBSD__) || defined(__OpenBSD__)
    (void)env;
    FILE *pipe = popen("pbcopy", "w");
    if (!pipe) {
        perror("clipboard (pbcopy)");
        return STATUS_CANNOT_COPY_TO_CLIPBOARD;
    }

    fprintf(pipe, "%s", password);

    int status = pclose(pipe);
    if (status != 0) {
        fprintf(stderr, "Warning: clipboard copy may have failed (exit %d)\n", status);
    } else {
        fprintf(stderr, "Password copy to clipboard\n");
    }
    return STATUS_OK;
#else
    if (env == DISPLAY_UNKNOWN) {
        fprintf(stderr, "Cannot detect display server. Password was not copied to clipboard\n");
        return STATUS_CANNOT_DETECT_DISPLAY;
    }

    if (env == DISPLAY_WAYLAND) {
        FILE *pipe = popen("wl-copy", "w");
        if (!pipe) {
            perror("clipboard (wl-copy)");
            return STATUS_CANNOT_COPY_TO_CLIPBOARD;
        }

        fprintf(pipe, "%s", password);

        int status = pclose(pipe);
        if (status != 0) {
            fprintf(stderr, "Warning: clipboard copy may have failed (exit %d)\n", status);
        } else {
            fprintf(stderr, "Password copied to clipboard\n");
        }
    } else {
        FILE *pipe = popen("xclip -selection clipboard", "w");
        if (!pipe) {
            perror("clipboard (xclip)");
            return STATUS_CANNOT_COPY_TO_CLIPBOARD;
        }

        fprintf(pipe, "%s", password);

        int status = pclose(pipe);
        if (status != 0) {
            fprintf(stderr, "Warning: clipboard copy may have failed (exit %d)\n", status);
        }
    }

    return STATUS_OK;
#endif
}
