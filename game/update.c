//-----------------------------------------------------------------------------
/*

Game State Update Code

*/
//-----------------------------------------------------------------------------

#include <stdint.h>
#include <stdlib.h>

#include "game.h"

//-----------------------------------------------------------------------------

void update(gs_t *gs)
{
    int i;

    for (i = 0; i < 5; i ++) {
        block_t *blk = &gs->blocks[i];
        blk->y += 1;
    }
}

//-----------------------------------------------------------------------------

void update_init(gs_t *gs)
{
    int i;

    for (i = 0; i < 5; i ++) {
        block_t *blk = &gs->blocks[i];
        blk->x = rand() % (PF_COLS * BLOCK_PIXELS);
        blk->y = rand() % (PF_ROWS * BLOCK_PIXELS);
        blk->color = (0xff << 24) | (rand() & 0xffffff);
    }
}

//-----------------------------------------------------------------------------
