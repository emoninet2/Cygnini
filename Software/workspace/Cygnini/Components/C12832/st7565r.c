/*
 * Copyright (c) 2019 - Elektronikklaboratoriet
 *                      Fysisk Institutt
 *                      Universitetet i Oslo
 *
 *                      All rights reserved
 */


#include "st7565r.h"

/* Kernel */
#include "cmsis_os.h"

/* Application */
//#include "../ekg_fys4260/ekg_fys4260.h"
#include "C12832Port.h"


#define HUNDRED_MILLISECONDS  	(10 / portTICK_PERIOD_MS)

void st7565r_write_command(uint8_t command) {
	
		uint8_t tmp;

        DISPLAY_CHIP_SELECT_LOW;
        DISPLAY_A0_LOW;
        c12832_hal_spi_write_read (&command, &tmp, 1);
        DISPLAY_CHIP_SELECT_HIGH;
}

void st7565r_write_data(uint8_t data) {
	
		uint8_t tmp;

        DISPLAY_CHIP_SELECT_LOW;
        DISPLAY_A0_HIGH;
        c12832_hal_spi_write_read (&data, &tmp, 1);
        DISPLAY_A0_LOW;
        DISPLAY_CHIP_SELECT_HIGH;
}

/**
 * \brief Perform a soft reset of the LCD controller
 *
 * This functions will reset the LCD controller by sending the reset command.
 * \note this funtions should not be confused with the \ref st7565r_hard_reset()
 * function, this command will not control the RST pin.
 */
void st7565r_soft_reset(void) {
	
        st7565r_write_command(ST7565R_CMD_RESET);
}

/**
 * \brief Perform a hard reset of the LCD controller
 *
 * This functions will reset the LCD controller by setting the reset pin low.
 * \note this funtions should not be confused with the \ref st7565r_soft_reset()
 * function, this command will control the RST pin.
 */
void st7565r_hard_reset(void) {
	
        DISPLAY_RESET_LOW;
        vTaskDelay (HUNDRED_MILLISECONDS);
        DISPLAY_RESET_HIGH;
        vTaskDelay (HUNDRED_MILLISECONDS);
}

/**
 * \brief Set current page in display RAM
 *
 * This command is usually followed by the configuration of the column address
 * because this scheme will provide access to all locations in the display
 * RAM.
 *
 * \param address the page address
 */
void st7565r_set_page_address(uint8_t address)
{
        // Make sure that the address is 4 bits (only 8 pages)
        address &= 0x0F;
        st7565r_write_command(ST7565R_CMD_PAGE_ADDRESS_SET(address));
}

/**
 * \brief Set current column in display RAM
 *
 * \param address the column address
 */
void st7565r_set_column_address(uint8_t address)
{
        // Make sure the address is 7 bits
        address &= 0x7F;
        st7565r_write_command(ST7565R_CMD_COLUMN_ADDRESS_SET_MSB(address >> 4));
        st7565r_write_command(ST7565R_CMD_COLUMN_ADDRESS_SET_LSB(address & 0x0F));
}

/**
 * \brief Set the display start draw line address
 *
 * This function will set which line should be the start draw line for the LCD.
 */
void st7565r_set_display_start_line_address(uint8_t address)
{
        // Make sure address is 6 bits
        address &= 0x3F;
        st7565r_write_command(ST7565R_CMD_START_LINE_SET(address));
}

/**
 * \brief Turn the LCD display on
 *
 * This function will turn on the LCD.
 */
void st7565r_display_on(void)
{
        st7565r_write_command(ST7565R_CMD_DISPLAY_ON);
}

/**
 * \brief Turn the LCD display off
 *
 * This function will turn off the LCD.
 */
void st7565r_display_off(void)
{
        st7565r_write_command(ST7565R_CMD_DISPLAY_OFF);
}

/**
 * \brief Sets all LCD pixels on
 *
 * This function can be used to test the LCD by setting all pixels on, this will
 * not affect the current LCD RAM.
 *
 * \param pixels_on if true all the LCD pixels are turned on, false the display
 *                  is back in normal mode displaying what is in the display
 *                  RAM.
 */
void st7565r_set_all_pixels(uint8_t pixels_on)
{
        if (pixels_on) {
                st7565r_write_command(ST7565R_CMD_DISPLAY_ALL_POINTS_ON);
        } else {
                st7565r_write_command(ST7565R_CMD_DISPLAY_ALL_POINTS_OFF);
        }
}

#define ST7565R_DISPLAY_CONTRAST_MIN	30
#define ST7565R_DISPLAY_CONTRAST_MAX	40
/**
 * \brief Set the LCD contrast level
 *
 * \warning This will set the voltage for the LCD, settings this value too high
 * may result in damage to the LCD. Hence the limit for these settings must be
 * defined in the \ref conf_st7565r.h file.
 *
 * Contrast values outside the max and min values will be clipped to the defined
 * \ref ST7565R_DISPLAY_CONTRAST_MAX and \ref ST7565R_DISPLAY_CONTRAST_MIN.
 *
 * \param contrast a number between 0 and 63 where the max values is given by
 *                 the LCD.
 *
 * \retval contrast the contrast value written to the LCD controller
 */
uint8_t st7565r_set_contrast(uint8_t contrast)
{
        if (contrast < ST7565R_DISPLAY_CONTRAST_MIN) {
                contrast = ST7565R_DISPLAY_CONTRAST_MIN;
        }
        if (contrast > ST7565R_DISPLAY_CONTRAST_MAX) {
                contrast = ST7565R_DISPLAY_CONTRAST_MAX;
        }
        st7565r_write_command(ST7565R_CMD_ELECTRONIC_VOLUME_MODE_SET);
        st7565r_write_command(ST7565R_CMD_ELECTRONIC_VOLUME(contrast));
        return contrast;
}

/**
 * \brief Invert all pixels on the device
 *
 * This function will invert all pixels on the LCD
 *
 */
void st7565r_display_invert_enable(void)
{
        st7565r_write_command(ST7565R_CMD_DISPLAY_REVERSE);
}

/**
 * \brief Disable invert of all pixels on the device
 *
 * This function will disable invert on all pixels on the LCD
 *
 */
void st7565r_display_invert_disable(void)
{
        st7565r_write_command(ST7565R_CMD_DISPLAY_NORMAL);
}

int st7565r_init(void) {
	
        // Do a hard reset of the LCD display controller
        st7565r_hard_reset();

        // Set the A0 pin to the default state (command)
        DISPLAY_A0_LOW;

        // The column address
        st7565r_write_command(ST7565R_CMD_ADC_NORMAL);

        // Non-inverted display
        st7565r_display_invert_disable();

        // The common mode scan direction
        st7565r_write_command(ST7565R_CMD_REVERSE_SCAN_DIRECTION);

        // Set the voltage bias ratio to 1/6
        st7565r_write_command(ST7565R_CMD_LCD_BIAS_1_DIV_6_DUTY33);

        // Set booster circuit, voltage regulator and voltage follower all to on
        st7565r_write_command(ST7565R_CMD_POWER_CTRL_ALL_ON);

        // Set the booster ratio to 2X,3X,4X
        st7565r_write_command(ST7565R_CMD_BOOSTER_RATIO_SET);
        st7565r_write_command(ST7565R_CMD_BOOSTER_RATIO_2X_3X_4X);

        // Set voltage resistor ratio to 1
        st7565r_write_command(ST7565R_CMD_VOLTAGE_RESISTOR_RATIO_1);

        /* Set contrast to min value, no need to check return value as the contrast
        is set to the defined min*/
        st7565r_set_contrast(ST7565R_DISPLAY_CONTRAST_MIN);

        // Turn on the display
        st7565r_display_on();
		
		return EXIT_SUCCESS;
}
