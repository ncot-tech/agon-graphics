#include "screen1.h"
#include <stdio.h>
#include <mos_api.h>
#include "graphics.h"
#include <agon/vdp_vdu.h>

void draw_colour_bars()
{
    uint8_t startx = 32;
    uint8_t starty = 208;
    uint8_t gap = 12; 
    uint8_t size = 56;
    int c = 0;
    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++) {
            vdp_plot_rect(c++, startx+(x*(size+gap)), SCREEN_HEIGHT-(starty+(y*(size+gap))), size, size);
        }
    }
}

void draw_palette()
{
    char *header = "\nA G O N  L I G H T  C O L O U R S\n";
    putch(30); // Homes the cursor without doing anything else to the screen
    printf("%s", header);
    printf  ("=================================\n");
    printf("X 0 1 2 3 4 5 6 7\n\n");
    printf("0\n\n1\n\n2\n\n3\n\n4\n\n5\n\n6\n\n7");
    draw_colour_bars();
}

// Define functions for Screen 1
void screen1_init(void) {
}

int screen1_update(void) {
//    if (1) {
//        return 1; // ID of the next screen
//    }
    return -1; // Continue with the current screen
}

void screen1_draw(void) {
    draw_palette();
}

