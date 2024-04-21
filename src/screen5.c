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
static font my_font;
Point origin;

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
    origin.x = 0;
    origin.y = 0;
}

float t = 0;

int screen5_update(void) {
    t+= 0.01;

    for (int i = 0; i < LOGO_COUNT; i++) {
        logos[i].position.x += 3;
        if (logos[i].position.x > SCREEN_WIDTH) {
            logos[i].position.x = -200;
            logos[i].position.y = rand_between(0, SCREEN_HEIGHT);
            int rand = rand_between(0, 10);
            if (rand >= 8) logos[i].bitmap_id = 2;
            else logos[i].bitmap_id = 1;
        }
    }
    return -1; // Continue with the current screen
}

char *scrolltext = "HELLO WORLD! THIS IS A TEST OF THE SCROLLING TEXT ROUTINE. IT SHOULD SCROLL AND LOOP!     ";
Point helloText = {SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};
vector2 textVect = {4,-6};
int xoff = SCREEN_WIDTH;
void screen5_draw(void) {
    vdp_clear_screen();
    for (size_t i = 0; i < strlen(scrolltext); i++) {
        int x = xoff+(i*32);
        int y = SCREEN_WIDTH / 2 + (sin(x * 0.02) * 50);
        bm_put_char(&my_font, x,y, scrolltext[i]);
    }
    bm_printf(&my_font, helloText.x,helloText.y, "HELLO WORLD!");
    for (int i = 0; i < LOGO_COUNT; i++) {
        vdp_plot_bitmap(logos[i].bitmap_id, logos[i].position.x,logos[i].position.y);
    }
    xoff -= 16;
    if (xoff < (int)(-32*strlen(scrolltext))) xoff = SCREEN_WIDTH;
    helloText.x += textVect.x;
    helloText.y += textVect.y;
    if (helloText.x < 0 || helloText.x+(strlen("HELLO WORLD!") * 32) > SCREEN_WIDTH) textVect.x *= -1;
    if (helloText.y < 0 || helloText.y+32 > SCREEN_HEIGHT) textVect.y *= -1;
}

