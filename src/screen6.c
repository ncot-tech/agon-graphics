#include "screen6.h"
#include <stdio.h>
#include <stdlib.h>
#include <mos_api.h>
#include "graphics.h"
#include <agon/vdp_vdu.h>
#include "maths_utils.h"
#include "bmprint.h"
#include "tilemap.h"
#include "keyboard.h"

tilemap map1;
uint8_t scrollAmount = 0;
int startx = 0;
uint16_t cx,ocx = 0;
uint16_t cy,ocy = 0;
void screen6_init(void) {

    printf ("Loading tiles, please wait!");
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
    
    tilemap_draw(&map1, startx, scrollAmount);
    // Copy the screen where the sprite is about to be
    putch(25); putch(4); write16bit(cx); write16bit(cy);
    putch(25); putch(4); write16bit(cx+60); write16bit(cy+64);
    scrollAmount = 1;
}

int screen6_update(void) {

    
    
    
    if (IS_KEY_HELD(KEY_UP)) cy+=8;
    if (IS_KEY_HELD(KEY_DOWN)) cy-=8;
    if (IS_KEY_HELD(KEY_LEFT)) cx-=8;
    if (IS_KEY_HELD(KEY_RIGHT)) cx+=8;
    
    if (cx > SCREEN_WIDTH-64) cx = SCREEN_WIDTH-64;
    if (cx < 0) cx = 0;
    if (cy > SCREEN_HEIGHT-64) cy = SCREEN_HEIGHT-64;
    if (cy < 0) cy = 0;
    

       
/*    rmc.x += rmcVec.x;
    rmc.y += rmcVec.y;
    if (rmc.x < 0 || rmc.x > SCREEN_WIDTH-200) rmcVec.x *= -1;
    if (rmc.y < 0 || rmc.y > SCREEN_HEIGHT-200) rmcVec.y *= -1;
    */
    return -1; // Continue with the current screen
}





int current_tile_id = 0;
int fc = 0;
void screen6_draw(void) {
    fc++;
    int tw4 = map1.tile_width*4;
    int th4 = map1.tile_height*4.3;
    //bm_printf(&my_font, 0+scrollAmount*4,SCREEN_HEIGHT-32, "HELLO WORLD!");
    //vdp_plot_bitmap(2, rmc.x+scrollAmount*4, rmc.y );
    
    
 //   current_tile_id = tilemap_get_tileid(&map1, cx, cy, scrollAmount, startx);
    
 //   scrollAmount ++;
//    if (fc % 6 == 0) {

    // Draw over where the sprite was
    putch(23); putch(27); putch(0x20); write16bit((uint16_t)64000);
    putch(25); putch(0xED); write16bit(ocx); write16bit(ocy);

    putch(23); putch(7); putch(3); putch(1); putch(1);
    scrollAmount++;
    for (int y = 0; y < map1.map_height; y++) {
        vdp_plot_bitmap(map1.bitmap_start_id+map1.map_data[startx + 20 + y * map1.map_width],
            (1280-(scrollAmount*4)),
            (y*th4));
    }
    if (scrollAmount == map1.tile_width) { // because hardware screen scrolling isn't using OS coords?!
        startx ++;
        scrollAmount = 0;
    }
    if (startx == map1.map_width-20) {
        startx = 0;
        scrollAmount = 0;
    }
    
    
    // Copy the screen where the sprite is about to be
    putch(25); putch(4); write16bit(cx); write16bit(cy);
    putch(25); putch(4); write16bit(cx+60); write16bit(cy+64);
   // putch(25); putch(0x65); write16bit(cx+60); write16bit(cy+64);
    putch(23); putch(27); putch(1); putch(0); putch(0); write16bit(0);
    // Draw the screen where the sprite is now
    vdp_plot_bitmap(28, cx, cy);
    
    ocx = cx;
    ocy = cy;
    
 //   printf ("[%d/%d] = [%d/%d] [%d]", cx, cy, cx/64, cy/64, current_tile_id);
}

