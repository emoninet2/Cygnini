/*
 * Copyright (c) 2015 - 2016 Elektronikklaboratoriet
 *                           Fysisk Institutt
 *                           Universitetet i Oslo
 *
 *							 All rights reserved
 */

#ifndef GRAPHIC_LCD_H
#define GRAPHIC_LCD_H

#define LINE_COUNT			4
#define LINE_PIXEL_LENGHT	128

int graphic_lcd_clear_screen(void);
int graphic_lcd_write(int line, int offset, char *text);
int graphic_lcd_initialize (void);
int graphics_lcd_write_byte (int line, int offset, uint8_t data);
int graphics_lcd_clear_line(int line);

#endif /* GRAPHIC_LCD_H */
