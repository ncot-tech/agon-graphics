#include "screen4.h"
#include <stdio.h>
#include <stdlib.h>
#include <mos_api.h>
#include "graphics.h"
#include <agon/vdp_vdu.h>
#include "maths_utils.h"

#define STARCOUNT 100
vector3 starfield[STARCOUNT];
// Colours from furthest away to closest
int colours[] = {15, 63, 62, 7, 8};

void screen4_init(void) {
    change_screen_mode(136, false, true);
    for (int i = 0; i < STARCOUNT; i++) {
        starfield[i].x = (float)rand_between(-SCREEN_WIDTH, SCREEN_WIDTH);
        starfield[i].y = (float)rand_between(-SCREEN_HEIGHT, SCREEN_HEIGHT);
        starfield[i].z = (float)rand_between(1, SCREEN_WIDTH);
    }
}

int screen4_update(void) {
    for (int i = 0; i < STARCOUNT; i++) {
        starfield[i].z -= 40;
        if (starfield[i].z < 0)
            starfield[i].z = SCREEN_WIDTH;
    }
    return -1; // Continue with the current screen
}

void screen4_draw(void) {
    vdp_clear_screen();
    for (int i = 0; i < STARCOUNT; i++) {
        int x = SCREEN_WIDTH / 2 + (starfield[i].x * SCREEN_WIDTH / 2 / (2 * starfield[i].z));
        int y = SCREEN_HEIGHT / 2 + (starfield[i].y * SCREEN_HEIGHT / 2 / (2 * starfield[i].z));
        int size = 2 * (1 / (starfield[i].z / SCREEN_WIDTH));

        int colour = map(starfield[i].z, 0, SCREEN_WIDTH, 0, 4);

        plot_circle(x, y, size, colours[colour]);
    }
    waitvblank();
    flip_buffer();
}

