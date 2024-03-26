#include "screen6.h"
#include <stdio.h>
#include <stdlib.h>
#include <mos_api.h>
#include "graphics.h"
#include <agon/vdp_vdu.h>
#include "maths_utils.h"
#include "bmprint.h"

font my_font;
typedef struct Tile {
    int id;
} Tile;

#define TILE_WIDTH 60
#define TILE_HEIGHT 16

uint8_t tilemap[] = {
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
};
vector2 rmcVec;
Point rmc;
void screen6_init(void) {
    ncotb_header header;
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
    rmcVec.y = -4;
}


int screen6_update(void) {
    rmc.x += rmcVec.x;
    rmc.y += rmcVec.y;
    if (rmc.x < 0 || rmc.x > SCREEN_WIDTH-200) rmcVec.x *= -1;
    if (rmc.y < 0 || rmc.y > SCREEN_HEIGHT-200) rmcVec.y *= -1;
    return -1; // Continue with the current screen
}

uint8_t scrollAmount = 0;
int startx = 0;
void screen6_draw(void) {
    for (int y = 0; y < TILE_HEIGHT ; y++) {
        for (int x = 0; x < 20; x++) {
            vdp_plot_bitmap(tilemap[startx + x + y * TILE_WIDTH], (x*64), y*64);
        }
    }
    bm_printf(&my_font, 0+scrollAmount*4,SCREEN_HEIGHT-32, "HELLO WORLD!");
    vdp_plot_bitmap(2, rmc.x+scrollAmount*4, rmc.y );
    if (scrollAmount > 0) {
        putch(23); putch(7); putch(3); putch(1); putch(scrollAmount);

        for (int y = 0; y < TILE_HEIGHT; y++) {
            vdp_plot_bitmap(tilemap[startx + 20 + y * TILE_WIDTH], (1280-scrollAmount*4), y*64);
        }
    }

    scrollAmount ++;
    if (scrollAmount == 16) {
        scrollAmount = 0;
        startx ++;
        if (startx > 40) startx = 0;
//        putch(23); putch(7); putch(2); putch(0); putch(16);
    }
}

