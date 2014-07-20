//-----------------------------------------------------------------------------




//-----------------------------------------------------------------------------

typedef struct block_type {

    uint16_t x;
    uint16_t y;
    uint32_t color;

} block_t;

typedef struct game_state_type {

    block_t blocks[5];

} gs_t;

//-----------------------------------------------------------------------------

#define LCD_HEIGHT 320
#define LCD_WIDTH 240

//-----------------------------------------------------------------------------
// playfield

#define PF_COLS 10
#define PF_ROWS 22
#define PF_ROWS_INVISIBLE 2
#define PF_ROWS_VISIBLE (PF_ROWS - PF_ROWS_INVISIBLE)

// blocks
#define BLOCK_PIXELS (LCD_HEIGHT / PF_ROWS_VISIBLE)

//-----------------------------------------------------------------------------

// rendering
void render_init(void);
void render(gs_t *gs);

// update
void update_init(gs_t *gs);
void update(gs_t *gs);

//-----------------------------------------------------------------------------
