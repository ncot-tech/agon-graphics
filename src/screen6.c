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
    /*    ncotb_header header;
    bitmap_load_result res = load_bitmap_into_buffer(1, "tile_0049.222", &header);
    if (res != SUCCESS) {
        printf ("Failed to load %s\n", "ncot-logo.222");
        return;
    }
    assign_buffer_to_bitmap(1,RGBA2222,header.width,header.height);

    res = load_bitmap_into_buffer(2, "rmc.222", &header);
    if (res != SUCCESS) {
        return;
    }
    assign_buffer_to_bitmap(2, RGBA2222, header.width, header.height);

    bm_load_font("08X08-F5", &my_font, 100);

    rmc.x = SCREEN_WIDTH / 2;
    rmc.y = SCREEN_HEIGHT / 2;
    rmcVec.x = 3;
    rmcVec.y = -4;*/
}


int screen6_update(void) {
    
/*    rmc.x += rmcVec.x;
    rmc.y += rmcVec.y;
    if (rmc.x < 0 || rmc.x > SCREEN_WIDTH-200) rmcVec.x *= -1;
    if (rmc.y < 0 || rmc.y > SCREEN_HEIGHT-200) rmcVec.y *= -1;
    */
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

