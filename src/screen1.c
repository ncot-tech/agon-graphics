#include "screen1.h"
#include <stdio.h>
#include <mos_api.h>
#include "graphics.h"
#include <agon/vdp_vdu.h>

void draw_colour_bars()
{
    uint8_t startx = 16;
    uint8_t starty = 40;
    uint8_t gap = 8; 
    uint8_t size = 8;
    static int x = 0;
    static int y = 0;
    static uint32_t timer1 = 0;
    static int c = 0;
    
    if (y == 8) return;
    if (sv->time >= timer1) {    
        vdp_plot_rect(c, startx+(x*(size+gap)), starty+(y*(size+gap)), size, size);
        c++;
        x++;
        timer1 = sv->time + 10;
        if (x == 8) { x = 0; y++; }
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
    printf("Initializing Screen 1...\n");
}

int screen1_update(void) {
    printf("Updating Screen 1...\n");
    // Example: Switch to next screen if a condition is met
    if (1) {
        return 1; // ID of the next screen
    }
    return -1; // Continue with the current screen
}

void screen1_draw(void) {
    printf("Drawing Screen 1...\n");
}

