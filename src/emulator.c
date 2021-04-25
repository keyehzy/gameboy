#include "SDL_timer.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <SDL2/SDL.h>

#include <gameboy/cpu.h>
#include <gameboy/emulator.h>
#include <gameboy/opcode.h>

static const uint8_t reverse_table[] = {
    0x00, 0x80, 0x40, 0xc0, 0x20, 0xa0, 0x60, 0xe0, 0x10, 0x90, 0x50, 0xd0,
    0x30, 0xb0, 0x70, 0xf0, 0x08, 0x88, 0x48, 0xc8, 0x28, 0xa8, 0x68, 0xe8,
    0x18, 0x98, 0x58, 0xd8, 0x38, 0xb8, 0x78, 0xf8, 0x04, 0x84, 0x44, 0xc4,
    0x24, 0xa4, 0x64, 0xe4, 0x14, 0x94, 0x54, 0xd4, 0x34, 0xb4, 0x74, 0xf4,
    0x0c, 0x8c, 0x4c, 0xcc, 0x2c, 0xac, 0x6c, 0xec, 0x1c, 0x9c, 0x5c, 0xdc,
    0x3c, 0xbc, 0x7c, 0xfc, 0x02, 0x82, 0x42, 0xc2, 0x22, 0xa2, 0x62, 0xe2,
    0x12, 0x92, 0x52, 0xd2, 0x32, 0xb2, 0x72, 0xf2, 0x0a, 0x8a, 0x4a, 0xca,
    0x2a, 0xaa, 0x6a, 0xea, 0x1a, 0x9a, 0x5a, 0xda, 0x3a, 0xba, 0x7a, 0xfa,
    0x06, 0x86, 0x46, 0xc6, 0x26, 0xa6, 0x66, 0xe6, 0x16, 0x96, 0x56, 0xd6,
    0x36, 0xb6, 0x76, 0xf6, 0x0e, 0x8e, 0x4e, 0xce, 0x2e, 0xae, 0x6e, 0xee,
    0x1e, 0x9e, 0x5e, 0xde, 0x3e, 0xbe, 0x7e, 0xfe, 0x01, 0x81, 0x41, 0xc1,
    0x21, 0xa1, 0x61, 0xe1, 0x11, 0x91, 0x51, 0xd1, 0x31, 0xb1, 0x71, 0xf1,
    0x09, 0x89, 0x49, 0xc9, 0x29, 0xa9, 0x69, 0xe9, 0x19, 0x99, 0x59, 0xd9,
    0x39, 0xb9, 0x79, 0xf9, 0x05, 0x85, 0x45, 0xc5, 0x25, 0xa5, 0x65, 0xe5,
    0x15, 0x95, 0x55, 0xd5, 0x35, 0xb5, 0x75, 0xf5, 0x0d, 0x8d, 0x4d, 0xcd,
    0x2d, 0xad, 0x6d, 0xed, 0x1d, 0x9d, 0x5d, 0xdd, 0x3d, 0xbd, 0x7d, 0xfd,
    0x03, 0x83, 0x43, 0xc3, 0x23, 0xa3, 0x63, 0xe3, 0x13, 0x93, 0x53, 0xd3,
    0x33, 0xb3, 0x73, 0xf3, 0x0b, 0x8b, 0x4b, 0xcb, 0x2b, 0xab, 0x6b, 0xeb,
    0x1b, 0x9b, 0x5b, 0xdb, 0x3b, 0xbb, 0x7b, 0xfb, 0x07, 0x87, 0x47, 0xc7,
    0x27, 0xa7, 0x67, 0xe7, 0x17, 0x97, 0x57, 0xd7, 0x37, 0xb7, 0x77, 0xf7,
    0x0f, 0x8f, 0x4f, 0xcf, 0x2f, 0xaf, 0x6f, 0xef, 0x1f, 0x9f, 0x5f, 0xdf,
    0x3f, 0xbf, 0x7f, 0xff,
};

/********************************************************************/
/* $FF0F IF Interrupt Flag                                          */
/*                                                                  */
/*         Bit 4: Transition from High to Low of Pin number P10-P13 */
/*         Bit 3: Serial I/O transfer complete                      */
/*         Bit 2: Timer Overflow                                    */
/*         Bit 1: LCDC (see STAT)                                   */
/*         Bit 0: V-Blank                                           */
/*                                                                  */
/* Interrupt        Priority     Start Address                      */
/* V-Blank             1         $0040                              */
/* LCDC Status         2         $0048                              */
/* Timer Overflow      3         $0050                              */
/* Serial Transfer     4         $0058                              */
/* Hi-Lo of P10-P13    5         $0060                              */
/********************************************************************/
#define IF 0xFF0F
/*********************************************************************/
/* $FFFF IE - Interrupt Enable                                       */
/*                                                                   */
/*         Bit 4: Transition from High to Low of Pin number P10-P13. */
/*         Bit 3: Serial I/O transfer complete                       */
/*         Bit 2: Timer Overflow                                     */
/*         Bit 1: LCDC (see STAT)                                    */
/*         Bit 0: V-Blank 0: disable 1: enable                       */
/*********************************************************************/
#define IE 0xFFFF

static void request_interupt(CPU *u, int kind)
{
    uint8_t set_interrupt = m_get8(u, IF) | (1 << kind);
    m_set8(u, IF, set_interrupt);
}

static void handle_interupt(CPU *u, int kind)
{
    u->interrupts = 0;
    uint8_t reset_interrupt = m_get8(u, IF) & ~(1 << kind);
    m_set8(u, IF, reset_interrupt);

    s_push16(u, u->mem.ptr);

    switch (kind)
    {
    case 0:
        u->mem.ptr = 0x40;
        break;
        u->mem.ptr = 0x48;
        break;
        u->mem.ptr = 0x50;
        break;
        u->mem.ptr = 0x60;
        break;
    }
}

void execute_interupts(CPU *u)
{
    if (u->interrupts)
    {
        uint8_t interrupt_flag = m_get8(u, IF);
        uint8_t interrupt_enabled = m_get8(u, IE);

        if (interrupt_flag)
        {
            for (uint8_t i = 0; i < 5; i++)
            {
                if ((interrupt_flag & interrupt_enabled) & (1 << i))
                {
                    handle_interupt(u, i);
                }
            }
        }
    }
}
/*********************************************************/
/* $FF40  LCDC  (value $91 at reset) - LCD Control (R/W) */
/*                                                       */
/*         Bit 7 - LCD Control Operation                 */
/*             0: Stop completely (no picture on screen) */
/*             1: operation                              */
/*         Bit 6 - Window Tile Map Display Select        */
/*             0: $9800-$9BFF                            */
/*             1: $9C00-$9FFF                            */
/*         Bit 5 - Window Display                        */
/*             0: off                                    */
/*             1: on                                     */
/*         Bit 4 - BG & Window Tile Data Select          */
/*             0: $8800-$97FF                            */
/*             1: $8000-$8FFF <- Same area as OBJ        */
/*         Bit 3 - BG Tile Map Display Select            */
/*             0: $9800-$9BFF                            */
/*             1: $9C00-$9FFF                            */
/*         Bit 2 - OBJ (Sprite) Size                     */
/*             0: 8*8                                    */
/*             1: 8*16 (width*height)                    */
/*         Bit 1 - OBJ (Sprite) Display                  */
/*             0: off                                    */
/*             1: on                                     */
/*         Bit 0 - BG & Window Display                   */
/*             0: off                                    */
/*             1: on                                     */
/*********************************************************/
#define LCDC 0xFF40

static uint8_t check_lcd(CPU *u)
{
    return m_get8(u, LCDC) & 0x80;
}

static uint8_t check_lcd_window(CPU *u)
{
    return m_get8(u, LCDC) & 0x20;
}

static uint16_t window_tile_map_mem_offset(CPU *u)
{
    uint8_t select = m_get8(u, LCDC) & 0x40;
    return select ? 0x9C00 : 0x9FFF;
}

static uint16_t bg_tile_map_mem_offset(CPU *u)
{
    uint8_t select = m_get8(u, LCDC) & 0x8;
    return select ? 0x9C00 : 0x9FFF;
}

static uint16_t tile_data_mem_offset(CPU *u)
{
    uint8_t select = m_get8(u, LCDC) & 0x10;
    return select ? 0x8000 : 0x8800;
}

static uint16_t location_of_tile(CPU *u, uint16_t tile_row, uint16_t tile_col)
{
    uint8_t tile_data_select = m_get8(u, LCDC) & 0x10;
    int16_t tile_identifier;
    if (tile_data_select)
    {
        tile_identifier = (uint8_t)m_get8(u, 0x8000 + tile_row + tile_col);
        return 0x8000 + 0x10 * tile_identifier;
    }
    else
    {
        tile_identifier = (int8_t)m_get8(u, 0x8800 + tile_row + tile_col);
        return 0x8800 + 0x10 * (tile_identifier + 0x80);
    }
}

/*******************************************************/
/* $FF42 SCY - Scroll Y                                */
/*                                                     */
/* 8 Bit value $00-$FF to scroll BG Y screen position. */
/*******************************************************/
#define SCY 0xFF42

/*******************************************************/
/* $FF43 SCX - Scroll X                                */
/*                                                     */
/* 8 Bit value $00-$FF to scroll BG X screen position. */
/*******************************************************/
#define SCX 0xFF43

/*********************************************************************************/
/* $FF47 BGP - BG & Window Palette Data */
/*                                                                               */
/*         Bit 7-6 - Data for Dot Data 11 (Normally darkest color) */
/*         Bit 5-4 - Data for Dot Data 10 */
/*         Bit 3-2 - Data for Dot Data 01 */
/*         Bit 1-0 - Data for Dot Data 00 (Normally lightest color) */
/*                                                                               */
/* This selects the shade of grays to use for the background (BG) & */
/* window pixels.  Since each pixel uses 2 bits, the corresponding shade will be
 */
/* selected from here. */
/*********************************************************************************/
#define BGP 0xFF47
typedef struct
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
} Color;

static Color get_color(CPU *u, uint8_t color_number, uint16_t address)
{
    Color color = {.r = 0xFF, .g = 0xFF, .b = 0xFF};
    uint8_t pallete = m_get8(u, address);
    uint8_t color_byte;

    switch (color_number)
    {
    case 0x00:
        color_byte = (pallete & 0x0) + ((pallete & 0x1) << 1);
        break;
    case 0x01:
        color_byte = (pallete & 0x2) + ((pallete & 0x3) << 1);
        break;
    case 0x10:
        color_byte = (pallete & 0x4) + ((pallete & 0x5) << 1);
        break;
    case 0x11:
        color_byte = (pallete & 0x6) + ((pallete & 0x7) << 1);
        break;
    }

    switch (color_byte)
    {
    case 0x00:
        color = (Color){.r = 0xFF, .g = 0xFF, .b = 0xFF};
        break;
    case 0x01:
        color = (Color){.r = 0xCC, .g = 0xCC, .b = 0xCC};
        break;
    case 0x10:
        color = (Color){.r = 0x77, .g = 0x77, .b = 0x77};
        break;
    case 0x11:
        color = (Color){.r = 0x0, .g = 0x0, .b = 0x0};
        break;
    }

    return color;
}

/*********************************************************************************/
/* $FF48 OBP0 - Object Palette 0 Data */
/*                                                                               */
/* This selects the colors for sprite palette 0. It works exactly as BGP ($FF47)
 */
/* except each each value of 0 is transparent.40. */
/*********************************************************************************/
#define OBP0 0xFF48

/**************************************************************************/
/* $FF49 OBP1 - Object Palette 1 Data                                     */
/*                                                                        */
/* This Selects the colors for sprite palette 1. It works exactly as OBP0 */
/* ($FF48). See BGP for details.                                          */
/**************************************************************************/
#define OBP1 0xFF49

/******************************************************************/
/* $FF4A WY - Window Y Position - 0 <= WY <= 143                  */
/*                                                                */
/* WY must be greater than or equal to 0 and must be less than or */
/* equal to 143 for window to be visible                          */
/******************************************************************/
#define WY 0xFF4A

/******************************************************************/
/* FF4B WX - Window X Position - 0 <= WX <= 166                   */
/*                                                                */
/* WX must be greater than or equal to 0 and must be less than or */
/* equal to 166 for window to be visible.  WX is offset from      */
/* absolute screen coordinates by 7. Setting the window to WX=7,  */
/* WY=0 will put the upper left corner of the window at absolute  */
/* screen coordinates 0,0.                                        */
/******************************************************************/
#define WX 0xFF4B

/**********************************************************************************/
/* $FF44 LY - LCDC Y-Coordinate */
/*                                                                                */
/* The LY indicates the vertical line to which the present data is transferred
 * to */
/* the LCD Driver. The LY can take on any value between 0 through 153. The
 * values */
/* between 144 and 153 indicate the V-Blank period. Writing will reset the */
/* counter. It takes 456 CPU clock cycles to draw on scanline and move to the */
/* next. */
/**********************************************************************************/
#define LY 0xFF44
int scanline_counter = 456;

uint8_t SCREEN[160][144];

static uint8_t inside_bounds(uint8_t x, uint8_t y)
{
    return (x >= 0 && x <= 159) && (y >= 0 && y <= 143);
}

static void render_tiles(CPU *u)
{
    uint8_t X = m_get8(u, WX);
    uint8_t Y = m_get8(u, WY);
    uint8_t offset_X = m_get8(u, SCX);
    uint8_t offset_Y = m_get8(u, SCY);

    uint8_t draw_window;
    uint16_t bg_mem_offset;
    uint16_t tile_mem_offset;

    if (check_lcd_window(u))
    {
        draw_window = 1;
        bg_mem_offset = window_tile_map_mem_offset(u);
    }
    else
    {
        draw_window = 0;
        bg_mem_offset = bg_tile_map_mem_offset(u);
    }

    tile_mem_offset = tile_data_mem_offset(u);

    uint8_t relative_y = 0;

    if (draw_window)
    {
        relative_y = m_get8(u, LY) - Y;
    }
    else
    {
        relative_y = offset_Y + m_get8(u, LY);
    }

    uint16_t row = (((uint8_t)(relative_y / 8)) * 32); /* XXX */

    for (int pixel = 0; pixel < 160; pixel++)
    {
        uint8_t relative_x = offset_X + pixel;

        if (draw_window)
        {
            relative_x = pixel % X;
        }

        uint16_t col = relative_x / 8;
        int16_t tile_location = location_of_tile(u, row, col);

        uint8_t line = 2 * (relative_y % 8);
        uint8_t color_byte1 = m_get8(u, tile_location + line);
        uint8_t color_byte2 = m_get8(u, tile_location + line + 1);

        uint8_t color_bit = reverse_table[relative_x % 8];

        uint8_t color_number =
            (color_byte1 & color_bit) + ((color_byte2 & color_bit) << 1);

        Color color = get_color(u, color_number, BGP);

        uint8_t pos = m_get8(u, LY);

        if (!inside_bounds(pixel, pos))
            continue;

        SCREEN[pixel][pos] = (color.r << 2) + (color.g << 1) + (color.b);
    }
}

static void render_sprites(CPU *u)
{
    uint8_t resolution = m_get8(u, LCDC) & 0x4;

    for (int sprite = 0; sprite < 40; sprite++)
    {
        uint8_t idx = 4 * sprite;
        uint8_t relative_y = m_get8(u, 0xFE00 + idx) - 16;
        uint8_t relative_x = m_get8(u, 0xFE00 + idx + 1) - 8;
        uint8_t tile_location = m_get8(u, 0xFE00 + idx + 2);
        uint8_t attr = m_get8(u, 0xFE00 + idx + 3);

        uint8_t flip_x = attr & 0x40;
        uint8_t flip_y = attr & 0x20;

        uint8_t scanline = m_get8(u, LY);

        uint8_t Y = resolution ? 16 : 8;

        if ((scanline >= relative_y) && (scanline < (Y + relative_y)))
        {
            uint8_t line = scanline - relative_y;

            if (flip_y)
            {
                line = reverse_table[line];
            }

            line *= 2;
            uint16_t data_address = (0x8000 + (tile_location * 16)) + line;
            uint8_t color_byte1 = m_get8(u, data_address);
            uint8_t color_byte2 = m_get8(u, data_address + 1);

            for (int pixel = 0; pixel < 7; pixel++)
            {
                uint8_t color_bit = reverse_table[pixel];

                if (flip_x)
                {
                    color_bit = reverse_table[color_bit];
                }

                uint8_t color_number = (color_byte1 & color_bit) +
                                       ((color_byte2 & color_bit) << 1);

                uint16_t color_address = attr & 0x10 ? 0xFF49 : 0xFF48;
                Color color = get_color(u, color_number, color_address);

                uint8_t pixel_x = 7 - pixel;
                uint8_t total_pixel = relative_x + pixel_x;

                if (!inside_bounds(total_pixel, scanline))
                {
                    continue;
                }

                SCREEN[total_pixel][scanline] =
                    (color.r << 2) + (color.g << 1) + (color.b);
            }
        }
    }
}

/**************************************************************************/
/* $FF41  STAT - LCDC Status                                              */
/*         Bits 6-3 - Interrupt Selection                                 */
/*             Bit 6 - LYC=LY Coincidence (Selectable)                    */
/*             Bit 5 - Mode 10                                            */
/*             Bit 4 - Mode 01                                            */
/*             Bit 3 - Mode 00                                            */
/*                 0: Non Selection                                       */
/*                 1: Selection                                           */
/*         Bit 2 - Coincidence Flag                                       */
/*             0: LYC not equal to LCDC LY                                */
/*             1: LYC = LCDC LY                                           */
/*         Bit 1-0 - Mode Flag                                            */
/*             00: During H-Blank                                         */
/*             01: During V-Blank                                         */
/*             10: During Searching OAM-RAM                               */
/*             11: During Transfering Data to LCD Driver                  */
/*                                                                        */
/*         It takes a total of 456 CPU cycles to write one scanline       */
/*         from which:                                                    */
/*                 80 CPU cycles during `Searching OAM-RAM`               */
/*                 172 CPU cycles during `Transfering Data to LCD Driver` */
/*                 204 CPU cycles during `H-Blank`                        */
/**************************************************************************/
#define STAT 0xFF41

/*******************************************************************/
/* $FF45 (LYC) LYC - LY Compare                                    */
/*                                                                 */
/* The LYC compares itself with the LY. If the values are the same */
/* it causes the STAT to set the coincident flag.                  */
/*******************************************************************/
#define LYC 0xFF45

static void set_lcd_status(CPU *u)
{
    uint8_t *status = m_ptr8(u, STAT);
    if (check_lcd(u) == 0)
    {
        scanline_counter = 456; /* Reset scanline */
        u->mem.content[LY] = 0;
        *status =
            ((*status) & 0xfc) | 0x1; /* set bits 0-1 to 01, i.e V-Blank */
        return;
    }

    uint8_t line = m_get8(u, LY);
    uint8_t mode = m_get8(u, STAT) & 0x3;

    uint8_t new_mode = 0;
    uint8_t check_new_mode = 0;

    if (line >= 144 && line <= 153) /* V-blank, see pg. 55 item 36 */
    {
        new_mode = 0x01;
        *status = ((*status) & 0xfc) | 0x1; /* set bit 0-1 to 01 */
        check_new_mode = (*status) & 0x10;  /* check bit 4 */
    }
    else
    {
        /* Here we need to check where in cycle we are: */
        /* LY = 456-375 --- Mode 2 - `Searching OAM-RAM` */
        /*      374-202 --- Mode 3 - `Transfering Data to LCD Driver` */
        /*      201-0   --- Mode 1 -  `H-Blank` */

        if (scanline_counter >= 375 && scanline_counter <= 456)
        {
            new_mode = 0x10;
            *status = ((*status) & 0xfc) | 0x2; /* set bit 0-1 to 10 */
            check_new_mode = (*status) & 0x20;  /* check bit 5 */
        }

        if (scanline_counter >= 202 && scanline_counter <= 374)
        {
            new_mode = 0x11;
            *status |= 0x3; /* set bit 0-1 to 11 */
        }

        if (scanline_counter >= 0 && scanline_counter <= 201)
        {
            new_mode = 0x00;
            *status &= ~0x3;                  /* set bit 0-1 to 00 */
            check_new_mode = (*status) & 0x8; /* check bit 3 */
        }
    }

    if (check_new_mode && (new_mode != mode))
    {
        request_interupt(u, 1);
    }

    if (line == m_get8(u, LYC)) /* see pg 55 item 36 */
    {
        *status |= 0x4; /* set bit 2 */
        if (*status & 0x40)
        {
            request_interupt(u, 2);
        }
    }
    else
    {
        *status &= ~0x4; /* reset bit 2 */
    }
}

static void draw_scanline(CPU *u)
{
    uint8_t byte = m_get8(u, LCDC);
    if (byte & 0x0)
    {
        render_tiles(u);
    }

    if (byte & 0x1)
    {
        render_sprites(u);
    }
}

void update_graphics(CPU *u, int cycles)
{
    set_lcd_status(u);

    if (check_lcd(u))
    {
        scanline_counter -= cycles;
    }
    else
    {
        return;
    }

    if (scanline_counter <= 0)
    {
        u->mem.content[LY]++;
        uint8_t line = m_get8(u, LY);

        scanline_counter = 456;

        if (line == 144)
        {
            request_interupt(u, 0);
        }
        else if (line > 153)
        {
            u->mem.content[LY] = 0;
        }
        else if (line < 144)
        {
            draw_scanline(u); /* XXX SDL */
        }
    }
}

/***************************************************************/
/* $FF04 Name - DIV                                            */
/*                                                             */
/* This register is incremented 16384(~16779 on SGB)times a    */
/* second. Writing any value sets it to $00.  Here we are also */
/* maintaining a counter `div_counter` for this task. At each  */
/* iteration we increase this counter by the number of cycles  */
/* ran. When this counter overflows we increment the div       */
/* register. This way, we have approximately 60 fps.           */
/***************************************************************/
#define DIV 0xFF04
int div_counter = 0;

static void update_div_register(CPU *u, int cycles)
{
    div_counter += cycles;
    if (div_counter >= 0xff /*CLOCK_SPEED/16382*/) /* overflows */
    {
        div_counter = 0;
        u->mem.content[DIV]++;
    }
}

/*********************************************************************/
/* $FF07 - TAC                                                       */
/*                                                                   */
/* This register specifies at what frequency the CPU is running and  */
/* also if the timer is enabled or not. This information is enconded */
/* in a three bit register. Where                                    */
/*                                                                   */
/* bit 0+1:                                                          */
/*         00: 4096 Hz                                               */
/*         01: 262144 hz                                             */
/*         10: 65536 Hz                                              */
/*         11: 16384 Hz                                              */
/* bit 2:                                                            */
/*         0: Stop Timer                                             */
/*         1: Start Timer                                            */
/*********************************************************************/
#define TAC 0xFF07
static uint8_t check_frequency(CPU *u)
{
    return m_get8(u, TAC) & 0x3;
}

static uint16_t get_freq(CPU *u)
{
    uint8_t byte = check_frequency(u);
    switch (byte)
    {
    case 0x00: /* (CLOCK_SPEED / FREQ) */
        return 0x400;
    case 0x01:
        return 0x10;
    case 0x10:
        return 0x40;
    case 0x11:
        return 0x100;
    default:
        fprintf(stderr, "Unknown frequency, aborting.\n");
        exit(1);
    }
}

static uint8_t check_timer(CPU *u)
{
    return m_get8(u, TAC) & 0x4;
}

/*******************************************************************/
/* $FF05 TIMA - Timer counter                                      */
/*                                                                 */
/* This timer is incremented by a clock frequency specified by the */
/* TAC register ($FF07). The timer generates an interrupt when it  */
/* overflows.                                                      */
/*******************************************************************/
#define TIMA 0xFF05

/******************************************************/
/* $FF06 TMA - Timer Modulo                           */
/*                                                    */
/* When the TIMA overflows, this data will be loaded. */
/******************************************************/
#define TMA 0xFF06
int timer_counter = (int)(CLOCK_SPEED / DEFAULT_FREQ);

static void update_timer_counter(CPU *u, int cycles)
{
    timer_counter -= cycles;

    if (timer_counter <= 0)
    {
        timer_counter = get_freq(u);

        if (m_get8(u, TIMA) == 0xff) /* overflows */
        {
            m_set8(u, TIMA, m_get8(u, TMA));
            request_interupt(u, 2);
        }
        else
        {
            m_set8(u, TIMA, m_get8(u, TIMA) + 1);
        }
    }
}

void update_timers(CPU *u, int cycles)
{
    update_div_register(u, cycles);
    if (check_timer(u))
    {
        update_timer_counter(u, cycles);
    }
}

static void update(CPU *u)
{
    const int initial_cycles = u->cycles;
    int delta_cycles = 0;

    while (delta_cycles < MAX_CYCLES_PER_SECOND)
    {
        execute_opcode(u, m_read8(u));
        delta_cycles = u->cycles - initial_cycles;

        update_timers(u, delta_cycles);
        update_graphics(u, delta_cycles);
        execute_interupts(u);
    }
}

int emulate_rom(CPU *u)
{
    if (u->info.cartridge_type !=
        0) /* TODO(keyenzy): Implement multiple ROM Banks */
    {
        puts("Multiple ROM banks not implemented yet.");
        exit(1);
    }

    memset(SCREEN, 255, 160 * 144 * sizeof(uint8_t));

    int quit = 0;
    SDL_Event event;
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window *window = SDL_CreateWindow("Gameboy", SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_UNDEFINED, 160, 144, 0);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_Texture *texture = SDL_CreateTexture(
        renderer, SDL_PIXELFORMAT_RGB888, SDL_TEXTUREACCESS_STATIC, 160, 144);
    while (!quit)
    {
        update(u);

        SDL_UpdateTexture(texture, NULL, SCREEN, 160 * sizeof(uint8_t));

        SDL_WaitEvent(&event);
        switch (event.type)
        {
        case SDL_QUIT:
            quit = 1;
            break;
        }

        SDL_Delay(1000);

        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
