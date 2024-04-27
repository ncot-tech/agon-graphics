#include <agon/vdp_vdu.h>
#include <agon/vdp_key.h>
#include <stdio.h>
#include <stdlib.h>
#include <mos_api.h>
#include "graphics.h"
#include <math.h>
#include <string.h>
#include "screen.h"
#include "screen1.h"
#include "screen2.h"
#include "screen3.h"
#include "screen4.h"
#include "screen5.h"
#include "screen6.h"
#include "keyboard.h"
// https://github.com/AgonConsole8/agon-docs/blob/main/VDP---Screen-Modes.md
#define SC_MODE 136
//#define SC_MODE 8

volatile SYSVAR *sv;

int main(int argc, char **argv)
{
    
    sv = vdp_vdu_init();
    if ( vdp_key_init() == -1 ) return 1;

    
    init_keys();
    
    define_screen(screen1_init, screen1_update, screen1_draw);
    define_screen(screen2_init, screen2_update, screen2_draw);
    define_screen(screen3_init, screen3_update, screen3_draw);
    define_screen(screen4_init, screen4_update, screen4_draw);
    define_screen(screen5_init, screen5_update, screen5_draw);
    define_screen(screen6_init, screen6_update, screen6_draw);

    // Each screen's index is 1 less than its name, so screen 1 is id 0
    // Here's what each screen does
    // Screen 1 - Draws the colour palette
    // Screen 2 - Draws some fancy rotating shapes
    // Screen 3 - Mystify screensaver
    // Screen 4 - Starfield screensaver
    // Screen 5 - Moving logos demo thing
    // Screen 6 - Scrolling tilemap

    if (argc == 2) {
        int current_screen = atoi(argv[1]);
        if (current_screen < 6)
            set_current_screen(current_screen);
        else
            set_current_screen(0);
    } else
        set_current_screen(5);

    while (1) {
        update_keys();
        if (IS_KEY_PRESSED(KEY_ESC))
            break;

        run_screens();
    }

    set_video_mode(0);
    vdp_clear_screen();
    vdp_logical_scr_dims( true );
    vdp_cursor_enable( true );
    
    return 0;
}

// # vim: set expandtab tabstop=4:
