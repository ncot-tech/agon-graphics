#include "screen6.h"
#include <stdio.h>
#include <stdlib.h>
#include <mos_api.h>
#include "graphics.h"
#include <agon/vdp_vdu.h>
#include "maths_utils.h"
#include "bmprint.h"
#include "tilemap.h"

tilemap map1;
void screen6_init(void) {
    tilemap_load("tiles-conv/test-level.map", &map1);
}


int screen6_update(void) {
    
    return -1; // Continue with the current screen
}

uint8_t scrollAmount = 0;
int startx = 0;
void screen6_draw(void) {
    tilemap_draw(&map1, startx, scrollAmount);
    
    //bm_printf(&my_font, 0+scrollAmount*4,SCREEN_HEIGHT-32, "HELLO WORLD!");
    //vdp_plot_bitmap(2, rmc.x+scrollAmount*4, rmc.y );
    
    scrollAmount ++;
    if (scrollAmount == 16) {
        scrollAmount = 0;
        startx ++;
        if (startx > 40) startx = 0;
//        putch(23); putch(7); putch(2); putch(0); putch(16);
    }
}

