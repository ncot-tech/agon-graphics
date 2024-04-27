#include "screen3.h"
#include <stdio.h>
#include <stdlib.h>
#include <mos_api.h>
#include "graphics.h"
#include <agon/vdp_vdu.h>
#include "maths_utils.h"

typedef struct line {
    Point start, end;
    vector2 vector_s, vector_e;
} line;

typedef struct poly {
    line lines[5];
    int colour;
}poly;

poly mystify[3] = {0};

// Function to calculate five points moving backwards down the vector (u, v)
Point calculate_point_along_vector(Point p1, vector2 v) {
    Point ret;
    vector2 v_copy = v;
    normalise_vector(&v_copy);
    float movement_x = v_copy.x * 30;
    float movement_y = v_copy.y * 30;
    ret.x = p1.x - movement_x;
    ret.y = p1.y - movement_y;

    return ret;
}

void draw_line2(line _line, int colour)
{
    draw_line(_line.start.x, _line.start.y, _line.end.x, _line.end.y, colour);
}

void screen3_init(void) {
    change_screen_mode(136, false, true);
    for (int j = 0; j < 3; j++) {
        mystify[j].colour = 1 + (rand() % 64);
        mystify[j].lines[0].start.x = rand_between(200,1000);
        mystify[j].lines[0].start.y = rand_between(200,1000);
        mystify[j].lines[0].end.x = rand_between(200,1000);
        mystify[j].lines[0].end.y = rand_between(200,1000);

        mystify[j].lines[0].vector_s.x = rand_between(-5,5);
        mystify[j].lines[0].vector_s.y = rand_between(-5,5);
        mystify[j].lines[0].vector_e.x = rand_between(-5,5);
        mystify[j].lines[0].vector_e.y = rand_between(-5,5);
        for (int i = 1; i < 5; i++) {
            mystify[j].lines[i].vector_s = mystify[j].lines[0].vector_s;
            mystify[j].lines[i].vector_e = mystify[j].lines[0].vector_e;
            mystify[j].lines[i].start = calculate_point_along_vector(mystify[j].lines[i-1].start, mystify[j].lines[i].vector_s);
            mystify[j].lines[i].end = calculate_point_along_vector(mystify[j].lines[i-1].end, mystify[j].lines[i].vector_e);
        }
    }
}

int screen3_update(void) {
    for (int j = 0; j < 5; j++) {
        for (int i = 0; i < 5; i++) {
            mystify[j].lines[i].start.x += mystify[j].lines[i].vector_s.x;
            mystify[j].lines[i].start.y += mystify[j].lines[i].vector_s.y;
            mystify[j].lines[i].end.x += mystify[j].lines[i].vector_e.x;
            mystify[j].lines[i].end.y += mystify[j].lines[i].vector_e.y;

            if (mystify[j].lines[i].start.x < 0 || mystify[j].lines[i].start.x >= 1280)
                mystify[j].lines[i].vector_s.x *= -1;
            if (mystify[j].lines[i].start.y < 0 || mystify[j].lines[i].start.y >= 1024)
                mystify[j].lines[i].vector_s.y *= -1;
            if (mystify[j].lines[i].end.x < 0 || mystify[j].lines[i].end.x >= 1280)
                mystify[j].lines[i].vector_e.x *= -1;
            if (mystify[j].lines[i].end.y < 0 || mystify[j].lines[i].end.y >= 1024)
                mystify[j].lines[i].vector_e.y *= -1;
        }
    }
    return -1; // Continue with the current screen
}

void screen3_draw(void) {
    vdp_clear_screen();
    for (int j = 0; j < 3; j++) {
        for (int i = 0; i < 5; i++) {
            draw_line2(mystify[j].lines[i], mystify[j].colour);
        }
    }
    waitvblank();
    flip_buffer();
}

