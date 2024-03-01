#include <agon/vdp_vdu.h>
#include <agon/vdp_key.h>
#include <stdio.h>
#include <mos_api.h>
#include "graphics.h"
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include "screen.h"
#include "screen1.h"
#include "screen2.h"

// https://github.com/AgonConsole8/agon-docs/blob/main/VDP---Screen-Modes.md
#define SC_MODE 136
#define SC_WIDTH 1280
#define SC_HEIGHT 1024


static volatile SYSVAR *sv;

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

typedef struct Shape {
    uint8_t num_points;
    uint8_t colours[2];
    Point centre_point;
    Point *points;
    Point *rotated_points;
} Shape;

#define PI_180 3.141 / 180.0
#define TO_RADS(x) (PI_180 * x)

void calc_poly_points(Point *points, uint16_t centre_x, uint16_t centre_y, uint8_t sides, uint16_t size);

Shape make_shape(uint8_t num_points, uint16_t centre_x, uint16_t centre_y, uint16_t size)
{
    Shape new_shape;
    new_shape.num_points = num_points;
    new_shape.points = (Point *)malloc(sizeof(Point) * num_points);
    new_shape.rotated_points = (Point *)malloc(sizeof(Point) * num_points);
    new_shape.centre_point.x = centre_x;
    new_shape.centre_point.y = centre_y;
    calc_poly_points(new_shape.points, centre_x, centre_y, num_points, size);
    new_shape.colours[0] = rand() % 63 + 1;
    new_shape.colours[1] = rand() % 63 + 1;

    return new_shape;
}

void calc_poly_points(Point *points, uint16_t centre_x, uint16_t centre_y, uint8_t sides, uint16_t size)
{
    float angle_increment = 360.0 / sides;
    float current_angle = 0.0;
    for (int i = 0; i < sides; i++) {
        float x = centre_x + size * cos(TO_RADS(current_angle));
        float y = centre_y + size * sin(TO_RADS(current_angle));
        points[i].x = (int)x;
        points[i].y = (int)y;
        current_angle += angle_increment;
    }
}

void rotate_shape(Shape shape, float angle)
{
    for (int i = 0; i < shape.num_points; i++) {
        float x = shape.points[i].x - shape.centre_point.x;
        float y = shape.points[i].y - shape.centre_point.y;
        float x_new = x * cos(TO_RADS(angle)) - y * sin(TO_RADS(angle)) + shape.centre_point.x;
        float y_new = x * sin(TO_RADS(angle)) + y * cos(TO_RADS(angle)) + shape.centre_point.y;
        shape.rotated_points[i].x = (int)x_new;
        shape.rotated_points[i].y = (int)y_new;
    }
}

void draw_shape(Shape shape, uint8_t colour) {
    for (int i = 0; i < shape.num_points; i++) {
        uint8_t next_point_index = (i+1) % shape.num_points;
        draw_triangle(shape.rotated_points[i], shape.rotated_points[next_point_index],
                        shape.centre_point, shape.colours[colour]);
        colour++;
        if (colour == 2) colour = 0;
    }
}

int main(void)
{
    
    sv = vdp_vdu_init();
    if ( vdp_key_init() == -1 ) return 1;

    set_video_mode(SC_MODE);
    vdp_clear_screen();
    vdp_logical_scr_dims( true );
    vdp_cursor_enable( false );

    define_screen(screen1_init, screen1_update, screen1_draw);
    define_screen(screen2_init, screen2_update, screen2_draw);

    float angle = 2;
    float rotation_speed = 4;
    uint8_t colour = 1;

    Shape shapes[10];
    for (int i = 0; i < 10; i++) {
        shapes[i] = make_shape(rand() % 7 + 3, (SC_WIDTH / 2 - 600) + (rand() % 1200), (SC_HEIGHT / 2 - 400) + (rand() % 800), rand() % 100 + 50);
    }

    //putch(19); putch(0); putch(255); putch(255);putch(0);putch(0); 
    while (1) {
        vdp_clear_screen();

        run_screens();

        /* move this 
        for (int i = 0; i < 10; i++) {
            rotate_shape(shapes[i], angle);
            draw_shape(shapes[i], colour);
        }
        angle += rotation_speed;
        if (angle >= 360) angle -= 360;

        /* keep this */
        waitvblank();
        flip_buffer();
    }

    return 0;
}

// # vim: set expandtab tabstop=4:
