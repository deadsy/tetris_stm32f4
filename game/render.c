//-----------------------------------------------------------------------------
/*

Game State Rendering Code

*/
//-----------------------------------------------------------------------------

#include <stdint.h>

#include "stm32f429i_discovery_lcd.h"
#include "game.h"

//-----------------------------------------------------------------------------

static uint32_t current_layer;

//-----------------------------------------------------------------------------

#define INVISIBLE_Y (PF_ROWS_INVISIBLE * BLOCK_PIXELS)

static void render_block(block_t *blk)
{
    if (blk->y >= INVISIBLE_Y) {
        BSP_LCD_SetTextColor(blk->color);
        BSP_LCD_FillRect(blk->x, blk->y - INVISIBLE_Y, BLOCK_PIXELS, BLOCK_PIXELS);
    }
}

//-----------------------------------------------------------------------------

void render(gs_t *gs)
{
    uint32_t next_layer = 0;
    int i;

    next_layer = ~current_layer & 1;
    BSP_LCD_SelectLayer(next_layer);
    BSP_LCD_Clear(LCD_COLOR_RED);

    for (i = 0; i < 5; i ++) {
        render_block(&gs->blocks[i]);
    }

    //BSP_LCD_SetLayerVisible(next_layer, ENABLE);
    //BSP_LCD_SetLayerVisible(current_layer, DISABLE);

    BSP_LCD_SetTransparency(current_layer, 0);
    BSP_LCD_SetTransparency(next_layer, 0xff);

    current_layer = next_layer;
}

//-----------------------------------------------------------------------------

void render_init(void)
{
    BSP_LCD_Init();

    BSP_LCD_LayerDefaultInit(0, (uint32_t) LCD_FRAME_BUFFER);
    BSP_LCD_SelectLayer(0);
    BSP_LCD_Clear(LCD_COLOR_RED);
    BSP_LCD_SetBackColor(LCD_COLOR_RED);
    BSP_LCD_SetTextColor(LCD_COLOR_WHITE);

    BSP_LCD_LayerDefaultInit(1, (uint32_t) LCD_FRAME_BUFFER + 76800);
    BSP_LCD_SelectLayer(1);
    BSP_LCD_Clear(LCD_COLOR_RED);
    BSP_LCD_SetBackColor(LCD_COLOR_RED);
    BSP_LCD_SetTextColor(LCD_COLOR_WHITE);

    BSP_LCD_SetLayerVisible(0, ENABLE);
    BSP_LCD_SetLayerVisible(1, ENABLE);
    current_layer = 0;

    BSP_LCD_DisplayOn();
}

//-----------------------------------------------------------------------------
