/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2021 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

 /*******************************************************************************
  * Includes
  ******************************************************************************/
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include "display_lib.h"
#include "ssd1306.h"
#include "ssd1306_fonts.h"

  /*******************************************************************************
   * Variables
   ******************************************************************************/
   /* Display buffer management */
typedef struct {
    char lines[DISPLAY_BUFFER_LINES][DISPLAY_LINE_LENGTH + 1];
    uint16_t current_line;
    uint16_t scroll_start;
    uint8_t display_initialized;
} DisplayBuffer_t;

static DisplayBuffer_t g_displayBuffer = { 0 };

/*******************************************************************************
 * Code
 ******************************************************************************/

 /*!
  * @brief Initialize display buffer and SSD1306 screen
  */
void display_init(void)
{
    memset(&g_displayBuffer, 0, sizeof(g_displayBuffer));
    ssd1306_Init();
    ssd1306_Fill(Black);
    ssd1306_UpdateScreen();
    g_displayBuffer.display_initialized = 1;
}

/*!
 * @brief Clear display buffer and screen
 */
void display_clear(void)
{
    memset(g_displayBuffer.lines, 0, sizeof(g_displayBuffer.lines));
    g_displayBuffer.current_line = 0;
    g_displayBuffer.scroll_start = 0;
    ssd1306_Fill(Black);
    ssd1306_UpdateScreen();
}

/*!
 * @brief Add formatted line to display buffer with automatic wrapping
 */
void display_add_line(const char* format, ...)
{
    va_list args;
    char temp_buffer[256];
    char* ptr = temp_buffer;
    int i = 0;

    va_start(args, format);
    vsnprintf(temp_buffer, sizeof(temp_buffer), format, args);
    va_end(args);

    /* Process text and wrap at DISPLAY_LINE_LENGTH characters */
    while (*ptr != '\0' && g_displayBuffer.current_line < DISPLAY_BUFFER_LINES)
    {
        i = 0;
        /* Extract one line worth of characters */
        while (*ptr != '\0' && *ptr != '\n' && i < DISPLAY_LINE_LENGTH)
        {
            g_displayBuffer.lines[g_displayBuffer.current_line][i] = *ptr;
            i++;
            ptr++;
        }

        if (*ptr == '\n')
        {
            ptr++;
        }

        g_displayBuffer.lines[g_displayBuffer.current_line][i] = '\0';
        g_displayBuffer.current_line++;
    }
}

/*!
 * @brief Add hex data with automatic line wrapping
 */
void display_add_data(const char* prefix, const uint8_t* data, uint16_t length)
{
    char line_buffer[DISPLAY_LINE_LENGTH + 1];
    uint16_t i = 0;
    int pos = 0;
    int prefix_len = strlen(prefix);

    while (i < length && g_displayBuffer.current_line < DISPLAY_BUFFER_LINES)
    {
        pos = 0;

        /* Add prefix on new section */
        if (i % 8 == 0 && i > 0)
        {
            g_displayBuffer.lines[g_displayBuffer.current_line][pos] = '\0';
            g_displayBuffer.current_line++;
            if (g_displayBuffer.current_line >= DISPLAY_BUFFER_LINES)
                break;
            pos = 0;
        }

        /* Add prefix if start of line */
        if (pos == 0 && prefix_len > 0)
        {
            strncpy(&line_buffer[pos], prefix, DISPLAY_LINE_LENGTH - pos);
            pos += prefix_len;
        }

        /* Add hex bytes */
        while (i < length && pos + 2 < DISPLAY_LINE_LENGTH)
        {
            snprintf(&line_buffer[pos], 4, "%02x", data[i]);
            pos += 2;
            i++;
            if (i % 8 == 0)
                break;
            if (pos + 1 < DISPLAY_LINE_LENGTH)
            {
                line_buffer[pos] = ',';
                pos++;
            }
        }

        strncpy(g_displayBuffer.lines[g_displayBuffer.current_line], line_buffer, DISPLAY_LINE_LENGTH);
        g_displayBuffer.lines[g_displayBuffer.current_line][DISPLAY_LINE_LENGTH] = '\0';
        g_displayBuffer.current_line++;
    }
}

/*!
 * @brief Add speed information to display
 */
void display_add_speed(const char* label, float speed)
{
    char buffer[DISPLAY_LINE_LENGTH + 1];
    snprintf(buffer, sizeof(buffer), "%s %.1f MB/s", label, (double)speed);
    display_add_line(buffer);
}

/*!
 * @brief Render display buffer to SSD1306 screen
 */
void display_render(void)
{
    const uint8_t y_positions[] = { 13, 23, 33, 43, 53 };
    uint16_t visible_start = g_displayBuffer.scroll_start;
    uint8_t line_idx;

    ssd1306_Fill(Black);

    /* Draw title */
    ssd1306_SetCursor(0, 0);
    ssd1306_WriteString("MMCAU Test", Font_7x10, White);

    /* Draw separator */
    ssd1306_Line(0, 12, 127, 12, White);

    /* Draw visible lines */
    for (line_idx = 0; line_idx < DISPLAY_VISIBLE_LINES && (visible_start + line_idx) < g_displayBuffer.current_line; line_idx++)
    {
        ssd1306_SetCursor(DISPLAY_X_START, y_positions[line_idx]);
        ssd1306_WriteString(g_displayBuffer.lines[visible_start + line_idx], Font_7x10, White);
    }

    /* Draw scroll indicator if needed */
    if (g_displayBuffer.current_line > DISPLAY_VISIBLE_LINES)
    {
        char scroll_indicator[20];
        snprintf(scroll_indicator, sizeof(scroll_indicator), "L:%d/%d", visible_start + 1, g_displayBuffer.current_line);
        ssd1306_SetCursor(80, 58);
        ssd1306_WriteString(scroll_indicator, Font_7x10, White);
    }

    ssd1306_UpdateScreen();
}

/*!
 * @brief Print data bytes to display with formatting
 */
void display_print_data(const uint8_t* data, uint32_t length)
{
    uint32_t i;
    char buffer[DISPLAY_LINE_LENGTH + 1];
    int pos = 0;

    memset(buffer, 0, sizeof(buffer));

    for (i = 0; i < length; i++)
    {
        if (data[i] == ',')
        {
            buffer[pos] = '\0';
            display_add_line(buffer);
            pos = 0;
            memset(buffer, 0, sizeof(buffer));
        }
        else if (pos < DISPLAY_LINE_LENGTH)
        {
            buffer[pos++] = data[i];
        }
        else
        {
            buffer[pos] = '\0';
            display_add_line(buffer);
            pos = 0;
            memset(buffer, 0, sizeof(buffer));
            buffer[pos++] = data[i];
        }
    }

    if (pos > 0)
    {
        buffer[pos] = '\0';
        display_add_line(buffer);
    }
}
