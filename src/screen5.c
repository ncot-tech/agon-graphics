#include "screen5.h"
#include <stdio.h>
#include <stdlib.h>
#include <mos_api.h>
#include "graphics.h"
#include <agon/vdp_vdu.h>
#include "maths_utils.h"
#include "bmprint.h"

#define LOGO_COUNT 10
typedef struct Sprite {
    Point position;
    uint16_t bitmap_id;
} Sprite;

Sprite logos[LOGO_COUNT];
font my_font;

void screen5_init(void) {
    ncotb_header header;
    bitmap_load_result res = load_bitmap_into_buffer(1, "ncot-logo.222", &header);
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

    for (int i = 0; i < LOGO_COUNT; i++) {
        logos[i].position.x = rand_between(0, SCREEN_WIDTH);
        logos[i].position.y = rand_between(0, SCREEN_HEIGHT);
        int rand = rand_between(0, 10);
        if (rand == 8) logos[i].bitmap_id = 2;
        else logos[i].bitmap_id = 1;
    }

    bm_load_font("08X08-F5", &my_font, 100);
}

int screen5_update(void) {
    for (int i = 0; i < LOGO_COUNT; i++) {
        logos[i].position.x += 3;
        if (logos[i].position.x > SCREEN_WIDTH) {
            logos[i].position.x = 0;
            logos[i].position.y = rand_between(0, SCREEN_HEIGHT);
            int rand = rand_between(0, 10);
            if (rand >= 8) logos[i].bitmap_id = 2;
            else logos[i].bitmap_id = 1;
        }
    }
    bm_printf(&my_font, 100,100, "HELLO WORLD!");
    return -1; // Continue with the current screen
}

void screen5_draw(void) {
    for (int i = 0; i < LOGO_COUNT; i++) {
        vdp_plot_bitmap(logos[i].bitmap_id, logos[i].position.x,logos[i].position.y);
    }
}

