#include "screen2.h"
#include <agon/vdp_vdu.h>
#include <agon/vdp_key.h>
#include <stdio.h>
#include <mos_api.h>
#include "graphics.h"
#include <math.h>
#include <stdlib.h>

typedef struct Shape {
    uint8_t num_points;
    uint8_t colours[2];
    Point centre_point;
    Point *points;
    Point *rotated_points;
} Shape;

#define PI_180 3.141 / 180.0
#define TO_RADS(x) (PI_180 * x)

float angle = 2;
float rotation_speed = 4;
uint8_t colour = 1;
Shape shapes[10];

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

// Define functions for Screen 1
void screen2_init(void) {
    for (int i = 0; i < 10; i++) {
        shapes[i] = make_shape(rand() % 7 + 3, (SCREEN_WIDTH / 2 - 600) + (rand() % 1200), (SCREEN_HEIGHT / 2 - 400) + (rand() % 800), rand() % 100 + 50);
    }
}

int screen2_update(void) {
    for (int i = 0; i < 10; i++) {
        rotate_shape(shapes[i], angle);
    }
    angle += rotation_speed;
    if (angle >= 360) angle -= 360;

    return -1; // Continue with the current screen
}

void screen2_draw(void) {
    for (int i = 0; i < 10; i++) {
        draw_shape(shapes[i], colour);
    }
}

