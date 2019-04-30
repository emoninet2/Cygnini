/*
 * Copyright (c) 2015 - 2016 Elektronikklaboratoriet
 *                           Fysisk Institutt
 *                           Universitetet i Oslo
 *
 *							 All rights reserved
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

/* Application */
//#include "../ekg_fys4260/ekg_fys4260.h"

#include "C12832Port.h"

#include "graphic_lcd.h"
#include "st7565r.h"
#include "font.h"

int graphic_lcd_clear_screen(void) {
	
	int i, j;
	
	for (i=0; i<LINE_COUNT; i++) {
		st7565r_set_page_address(i);
		st7565r_set_column_address(0);
		st7565r_set_display_start_line_address(0);
		for (j=0; j<LINE_PIXEL_LENGHT + FONT_SIZE; j++)
			st7565r_write_data(0);
	}
	
	return EXIT_SUCCESS;
}

int graphic_lcd_write(int line, int offset, char *text) {

	int i, j;
	
	st7565r_set_page_address(line);
	st7565r_set_column_address(offset + FONT_SIZE);
	
	for (i=0; i<strlen(text); i++) {
	
		for (j=0; j<FONT_SIZE; j++) {
			st7565r_write_data(font_5x8_table[(((text[i] - ASCII_FONT_FIRST) * FONT_SIZE) + j)]);
		}
		st7565r_write_data(0);
	}
		
	return EXIT_SUCCESS;
}

int graphic_lcd_initialize (void) {
	
	return st7565r_init ();
	
}

int graphics_lcd_write_byte (int line, int offset, uint8_t data) {

	st7565r_set_page_address(line);
	st7565r_set_column_address(offset);
	st7565r_write_data(data);

	return EXIT_SUCCESS;
}
	
