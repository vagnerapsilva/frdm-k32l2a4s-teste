/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2021 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __DISPLAY_LIB_H__
#define __DISPLAY_LIB_H__

#include <stdint.h>

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/* SSD1306 Display Configuration */
#define DISPLAY_LINE_LENGTH   18      /* Characters per line (128px / 7px per char) */
#define DISPLAY_VISIBLE_LINES 5       /* Visible lines on display */
#define DISPLAY_BUFFER_LINES  64      /* Total buffer lines for scrolling */
#define DISPLAY_X_START       0
#define DISPLAY_Y_LINES       5       /* Y positions: 13, 23, 33, 43, 53 */

/*******************************************************************************
 * Public Functions
 ******************************************************************************/

/*!
 * @brief Initialize display buffer and SSD1306 screen
 */
void display_init(void);

/*!
 * @brief Clear display buffer and screen
 */
void display_clear(void);

/*!
 * @brief Add formatted line to display buffer with automatic wrapping
 * @param format Printf-style format string
 * @param ... Variable arguments for format string
 */
void display_add_line(const char* format, ...);

/*!
 * @brief Add hex data with automatic line wrapping
 * @param prefix Prefix string for each line
 * @param data Pointer to data bytes
 * @param length Number of bytes to display
 */
void display_add_data(const char* prefix, const uint8_t* data, uint16_t length);

/*!
 * @brief Add speed information to display
 * @param label Label text for the speed
 * @param speed Speed value in MB/s
 */
void display_add_speed(const char* label, float speed);

/*!
 * @brief Render display buffer to SSD1306 screen
 */
void display_render(void);

/*!
 * @brief Print data bytes to display with formatting
 * @param data Pointer to data bytes
 * @param length Number of bytes to print
 */
void display_print_data(const uint8_t* data, uint32_t length);

#endif /* __DISPLAY_LIB_H__ */
