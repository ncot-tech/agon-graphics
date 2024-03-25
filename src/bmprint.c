#include "bmprint.h"
#include <stdarg.h>
#include <string.h>
#include "xitoa.h"
#include "graphics.h"

void load_font_def(char *font_def, font *font)
{
    uint16_t path_length = strlen(font_def) * 2 + 5;
    // We're making a path of "font_def/font_def.dat\0"
    char *filename = (char *)malloc(sizeof(char) * path_length);
    strcpy(filename, font_def);
    strcat(filename, "/");
    strcat(filename, font_def);
    strcat(filename, ".dat");
    uint8_t file = mos_fopen(filename, 0x01);
	if (!file) {
        printf ("Can't open file %s\n", filename);
        exit(1);
	}

    char file_tag[5];
	mos_fread(file, (char *)file_tag, 5);
	if (file_tag[0] != 'N' || file_tag[1] != 'C' || file_tag[2] != 'O'
	    || file_tag[3] != 'T' || file_tag[4] != 'F') {
        printf ("Not a font %c%c%c%c%c\n", file_tag[0], file_tag[1], file_tag[2],
                file_tag[3], file_tag[4]);
        exit(1);
	}

    uint16_t name_length = 0;
    mos_fread(file, (char *)&name_length, 2);

    printf ("Name is %d long\n", name_length);

    font->font_name = (char *)malloc(sizeof(char) * name_length + 1);
    mos_fread(file, font->font_name, name_length);
    font->font_name[name_length] = 0;   // Null terminate it

    printf ("Font name is %s\n", font->font_name);

    mos_fread(file, (char *)&font->char_count, 3);   // Read count, width, height

    printf ("Read %s which is %dx%d and contains %d chars\n",
            font->font_name, font->char_width, font->char_height, font->char_count);
}

uint8_t bm_load_font(char *font_def, font *font, uint16_t bitmap_id)
{
    load_font_def(font_def, font);
   
    font->start_bitmap_id = bitmap_id;
    bitmap_load_result res;

    ncotb_header image_header;
    
    // We're making a path of "font_def/font_def_xx.222\0"
    uint16_t path_length = strlen(font_def) * 2 + 9;
    printf ("Path length is %d\n", path_length);

    char *fontname = (char *)malloc(sizeof(char) * path_length);
	for (int i = 0; i < font->char_count; i++) {
		snprintf(fontname, path_length, "%s/%s_%02d.222", font_def, font_def, i);
		res = load_bitmap_into_buffer(bitmap_id + i, fontname, &image_header);
		if (res != SUCCESS) {
			printf ("Failed to load %s\n", fontname);
			return 1;
		}
		assign_buffer_to_bitmap(bitmap_id + i,RGBA2222,image_header.width,image_header.height);
	}

    return 0;
}
void bm_put_string(font *font, uint8_t screenx, uint8_t screeny, char *s)
{
    char *currentChar = s;
    int xpos = 0;
    int ypos = 0;
    uint16_t id = 10;   // Default character is a * for "can't draw that"
    while (*currentChar) {
        if ((*currentChar)-32 <= 58)    // Char within range?
            id = (*currentChar)-32;    // Calculate the ID
        vdp_plot_bitmap(font->start_bitmap_id + id, screenx+(xpos*8), screeny+(ypos*8));
        currentChar++;
        xpos++;
        if (xpos >= 320) {
            xpos = 0;
            ypos += 8;
        }
    }
}

void bm_printf(font *font, uint8_t screenx, uint8_t screeny, char *format, ...)
{
    char tmpStr[33];
    int xpos = 0;
    int ypos = 0;
    uint16_t id = 10;   // Default * for "can't print this"
    va_list argp;
    va_start(argp, format);
    while (*format != '\0') {
        if (*format == '%') {
            format++;
            switch (*format) {
                case '%': tmpStr[0] = '%'; tmpStr[1] = 0; break;
                case 'c': tmpStr[0] = va_arg(argp, int); tmpStr[1] = 0; break;
                case 'd': xitoa(va_arg(argp, int), tmpStr, 10); break;
                case 'x': xitoa(va_arg(argp, int), tmpStr, 16); break;
                case 's': strncpy(tmpStr, va_arg(argp, char*), 32); tmpStr[32] = 0; break;
                default : tmpStr[0] = '?';tmpStr[1] = 0; break;
            }
            bm_put_string(font, screenx+(xpos*8), screeny+(ypos*8), tmpStr);
            xpos += strlen(tmpStr) - 1;
            if (xpos >= 320) {
                ypos += 8;
                xpos = 0;
            }
        } else {
            if ((*format)-32 <= 58)    // Char within range?
                id = (*format)-32;    // Calculate the ID
            else
                id = 10;    // Draw a * instead
            vdp_plot_bitmap(font->start_bitmap_id + id, screenx+(xpos*8), screeny+(ypos*8));
        }
        format++;
        xpos+=4;
        if (xpos >= 320) {
            xpos = 0;
            ypos += 8;
        }

    }
    va_end(argp);

  //  
}

