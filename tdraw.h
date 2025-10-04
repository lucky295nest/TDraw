#ifndef TDRAW_H
#define TDRAW_H

typedef struct
{
    int red;
    int green;
    int blue;
} tdraw_rgb;

#define TDRAW_BLOCK_STR "  "

// --- Basic definitions ---
extern const tdraw_rgb EMPTY;
extern const tdraw_rgb BLACK;
extern const tdraw_rgb WHITE;
extern const tdraw_rgb RED;
extern const tdraw_rgb GREEN;
extern const tdraw_rgb BLUE;

// --- Red Declarations ---
extern const tdraw_rgb RED_GARNET;    // Original
extern const tdraw_rgb RED_SCARLET;   // Original (Very Bright)
extern const tdraw_rgb RED_BRICK;     // Muted/Earthy
extern const tdraw_rgb RED_CRANBERRY; // Muted/Earthy
extern const tdraw_rgb RED_BORDEAUX;  // Deep/Rich Muted
extern const tdraw_rgb RED_MAROON;    // Deep/Rich Muted

// --- Pink Declarations ---
extern const tdraw_rgb PINK_BLUSH;   // Original (Very Light)
extern const tdraw_rgb PINK_FUCHSIA; // Original
extern const tdraw_rgb PINK_ROSE;    // Muted/Earthy
extern const tdraw_rgb PINK_DUST;    // Muted/Earthy
extern const tdraw_rgb PINK_BALLET;  // Deep/Rich Muted
extern const tdraw_rgb PINK_CORAL;   // Deep/Rich Muted

// --- Green Declarations ---
extern const tdraw_rgb GREEN_EMERALD; // Original
extern const tdraw_rgb GREEN_SAGE;    // Original (Light)
extern const tdraw_rgb GREEN_PINE;    // Original (Deep)
extern const tdraw_rgb GREEN_LIME;    // Original (Very Bright)
extern const tdraw_rgb GREEN_OLIVE;   // Muted/Earthy
extern const tdraw_rgb GREEN_MOSS;    // Muted/Earthy
extern const tdraw_rgb GREEN_TEAL;    // Muted/Earthy
extern const tdraw_rgb GREEN_MINT;    // Muted/Earthy (Light)
extern const tdraw_rgb GREEN_FOREST;  // Deep/Rich Muted
extern const tdraw_rgb GREEN_JADE;    // Deep/Rich Muted
extern const tdraw_rgb GREEN_CYPRESS; // Deep/Rich Muted
extern const tdraw_rgb GREEN_AVOCADO; // Deep/Rich Muted

// --- Blue Declarations ---
extern const tdraw_rgb BLUE_SAPPHIRE;   // Original (Deep)
extern const tdraw_rgb BLUE_POWDER;     // Original (Light)
extern const tdraw_rgb BLUE_CERULEAN;   // Original
extern const tdraw_rgb BLUE_PETROL;     // Original (Deep Muted)
extern const tdraw_rgb BLUE_NAVY;       // Muted/Earthy (Deep)
extern const tdraw_rgb BLUE_STEEL;      // Muted/Earthy
extern const tdraw_rgb BLUE_AIR;        // Muted/Earthy (Light)
extern const tdraw_rgb BLUE_DENIM;      // Muted/Earthy
extern const tdraw_rgb BLUE_INDIGO;     // Deep/Rich Muted
extern const tdraw_rgb BLUE_PERIWINKLE; // Deep/Rich Muted
extern const tdraw_rgb BLUE_AZURE;      // Deep/Rich Muted (Slightly Brighter)
extern const tdraw_rgb BLUE_CORNFLOWER; // Deep/Rich Muted

// --- Yellow Declarations ---
extern const tdraw_rgb YELLOW_SAFFRON; // Original (Bright)
extern const tdraw_rgb YELLOW_MUSTARD; // Muted/Earthy
extern const tdraw_rgb YELLOW_CHAMOIS; // Deep/Rich Muted (Light)

// --- Orange Declarations ---
extern const tdraw_rgb ORANGE_PEACH;      // Original (Light)
extern const tdraw_rgb ORANGE_RUST;       // Original
extern const tdraw_rgb ORANGE_TERRACOTTA; // Muted/Earthy
extern const tdraw_rgb ORANGE_APRICOT;    // Muted/Earthy (Light)
extern const tdraw_rgb ORANGE_CIDER;      // Deep/Rich Muted
extern const tdraw_rgb ORANGE_RUSSET;     // Deep/Rich Muted (Deep)

// --- Violet Declarations ---
extern const tdraw_rgb VIOLET_WISTERIA; // Original (Light)
extern const tdraw_rgb VIOLET_LAVENDER; // Muted/Earthy (Similar to Wisteria)
extern const tdraw_rgb VIOLET_THISTLE;  // Deep/Rich Muted (Very Light)

// --- Purple Declarations ---
extern const tdraw_rgb PURPLE_AMETHYST; // Original
extern const tdraw_rgb PURPLE_EGGPLANT; // Original (Very Deep)
extern const tdraw_rgb PURPLE_MAUVE;    // Muted/Earthy
extern const tdraw_rgb PURPLE_PLUM;     // Muted/Earthy (Deep)
extern const tdraw_rgb PURPLE_WINE;     // Deep/Rich Muted (Very Deep)
extern const tdraw_rgb PURPLE_MULBERRY; // Deep/Rich Muted

// --- Brown Declarations ---
extern const tdraw_rgb BROWN_MOCHA;    // Original
extern const tdraw_rgb BROWN_CLAY;     // Original
extern const tdraw_rgb BROWN_TAUPE;    // Muted/Earthy (Gray-Brown)
extern const tdraw_rgb BROWN_SIENNA;   // Muted/Earthy
extern const tdraw_rgb BROWN_SEPIA;    // Deep/Rich Muted
extern const tdraw_rgb BROWN_CHESTNUT; // Deep/Rich Muted

// --- Gray Declarations ---
extern const tdraw_rgb GRAY_CHARCOAL; // Original (Blue-Gray)
extern const tdraw_rgb GRAY_FOG;      // Original (Light)
extern const tdraw_rgb GRAY_SLATE;    // Muted/Earthy (Blue-Gray)
extern const tdraw_rgb GRAY_PEBBLE;   // Muted/Earthy (Light)
extern const tdraw_rgb GRAY_CARBON;   // Deep/Rich Muted (Neutral Dark)
extern const tdraw_rgb GRAY_MIST;     // Deep/Rich Muted (Light)

extern tdraw_rgb **tdraw_canvas;
extern int tdraw_term_x;
extern int tdraw_term_y;

void tdraw_init_canvas(void);
void tdraw_free_canvas(void);
void tdraw_clear_canvas(void);
void tdraw_clear_terminal(void);
void tdraw_reset_cursor(void);
void tdraw_reset_colour(void);
void tdraw_set_colour(tdraw_rgb c);
void tdraw_set_pixel(int x, int y, tdraw_rgb c);
void tdraw_draw_frame(void);

#endif // TDRAW_H


// --- Implementation section ---
#ifdef TDRAW_IMPLEMENTATION

// --- Includes ---
#include <sys/ioctl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

// --- Basic definitions ---
const tdraw_rgb EMPTY = {-1, -1, -1};
const tdraw_rgb BLACK = {0, 0, 0};
const tdraw_rgb WHITE = {255, 255, 255};
const tdraw_rgb RED = {255, 0, 0};
const tdraw_rgb GREEN = {0, 255, 0};
const tdraw_rgb BLUE = {0, 0, 255};
// --- Red definitions ---
const tdraw_rgb RED_GARNET = {123, 30, 48};    // Original
const tdraw_rgb RED_SCARLET = {255, 36, 0};    // Original (Very Bright)
const tdraw_rgb RED_BRICK = {149, 69, 70};     // Muted/Earthy
const tdraw_rgb RED_CRANBERRY = {153, 51, 84}; // Muted/Earthy
const tdraw_rgb RED_BORDEAUX = {108, 25, 41};  // Deep/Rich Muted
const tdraw_rgb RED_MAROON = {128, 0, 0};      // Deep/Rich Muted

// --- Pink definitions ---
const tdraw_rgb PINK_BLUSH = {254, 221, 227};  // Original (Very Light)
const tdraw_rgb PINK_FUCHSIA = {200, 50, 120}; // Original
const tdraw_rgb PINK_ROSE = {223, 172, 185};   // Muted/Earthy
const tdraw_rgb PINK_DUST = {186, 151, 151};   // Muted/Earthy
const tdraw_rgb PINK_BALLET = {223, 196, 207}; // Deep/Rich Muted
const tdraw_rgb PINK_CORAL = {218, 126, 116};  // Deep/Rich Muted

// --- Green definitions ---
const tdraw_rgb GREEN_EMERALD = {0, 153, 102};   // Original
const tdraw_rgb GREEN_SAGE = {188, 201, 175};    // Original (Light)
const tdraw_rgb GREEN_PINE = {1, 121, 111};      // Original (Deep)
const tdraw_rgb GREEN_LIME = {167, 255, 100};    // Original (Very Bright)
const tdraw_rgb GREEN_OLIVE = {114, 115, 61};    // Muted/Earthy
const tdraw_rgb GREEN_MOSS = {138, 154, 91};     // Muted/Earthy
const tdraw_rgb GREEN_TEAL = {60, 131, 137};     // Muted/Earthy
const tdraw_rgb GREEN_MINT = {171, 209, 194};    // Muted/Earthy (Light)
const tdraw_rgb GREEN_FOREST = {34, 78, 48};     // Deep/Rich Muted
const tdraw_rgb GREEN_JADE = {0, 168, 119};      // Deep/Rich Muted
const tdraw_rgb GREEN_CYPRESS = {74, 88, 77};    // Deep/Rich Muted
const tdraw_rgb GREEN_AVOCADO = {132, 145, 108}; // Deep/Rich Muted

// --- Blue definitions ---
const tdraw_rgb BLUE_SAPPHIRE = {10, 52, 109};     // Original (Deep)
const tdraw_rgb BLUE_POWDER = {176, 224, 230};     // Original (Light)
const tdraw_rgb BLUE_CERULEAN = {0, 123, 167};     // Original
const tdraw_rgb BLUE_PETROL = {2, 70, 80};         // Original (Deep Muted)
const tdraw_rgb BLUE_NAVY = {34, 47, 68};          // Muted/Earthy (Deep)
const tdraw_rgb BLUE_STEEL = {70, 107, 130};       // Muted/Earthy
const tdraw_rgb BLUE_AIR = {150, 180, 207};        // Muted/Earthy (Light)
const tdraw_rgb BLUE_DENIM = {71, 98, 132};        // Muted/Earthy
const tdraw_rgb BLUE_INDIGO = {75, 0, 130};        // Deep/Rich Muted
const tdraw_rgb BLUE_PERIWINKLE = {149, 147, 203}; // Deep/Rich Muted
const tdraw_rgb BLUE_AZURE = {0, 127, 255};        // Deep/Rich Muted (Slightly Brighter)
const tdraw_rgb BLUE_CORNFLOWER = {100, 149, 237}; // Deep/Rich Muted

// --- Yellow definitions ---
const tdraw_rgb YELLOW_SAFFRON = {255, 198, 93};  // Original (Bright)
const tdraw_rgb YELLOW_MUSTARD = {186, 150, 62};  // Muted/Earthy
const tdraw_rgb YELLOW_CHAMOIS = {243, 220, 150}; // Deep/Rich Muted (Light)

// --- Orange definitions ---
const tdraw_rgb ORANGE_PEACH = {255, 189, 136};     // Original (Light)
const tdraw_rgb ORANGE_RUST = {183, 65, 14};        // Original
const tdraw_rgb ORANGE_TERRACOTTA = {204, 104, 82}; // Muted/Earthy
const tdraw_rgb ORANGE_APRICOT = {247, 185, 149};   // Muted/Earthy (Light)
const tdraw_rgb ORANGE_CIDER = {186, 103, 73};      // Deep/Rich Muted
const tdraw_rgb ORANGE_RUSSET = {130, 70, 40};      // Deep/Rich Muted (Deep)

// --- Violet definitions ---
const tdraw_rgb VIOLET_WISTERIA = {178, 155, 206}; // Original (Light)
const tdraw_rgb VIOLET_LAVENDER = {171, 158, 195}; // Muted/Earthy (Similar to Wisteria)
const tdraw_rgb VIOLET_THISTLE = {210, 190, 219};  // Deep/Rich Muted (Very Light)

// --- Purple definitions ---
const tdraw_rgb PURPLE_AMETHYST = {132, 94, 194}; // Original
const tdraw_rgb PURPLE_EGGPLANT = {47, 43, 60};   // Original (Very Deep)
const tdraw_rgb PURPLE_MAUVE = {145, 96, 127};    // Muted/Earthy
const tdraw_rgb PURPLE_PLUM = {97, 60, 80};       // Muted/Earthy (Deep)
const tdraw_rgb PURPLE_WINE = {84, 18, 52};       // Deep/Rich Muted (Very Deep)
const tdraw_rgb PURPLE_MULBERRY = {124, 73, 110}; // Deep/Rich Muted

// --- Brown definitions ---
const tdraw_rgb BROWN_MOCHA = {105, 75, 50};    // Original
const tdraw_rgb BROWN_CLAY = {170, 104, 73};    // Original
const tdraw_rgb BROWN_TAUPE = {139, 134, 126};  // Muted/Earthy (Gray-Brown)
const tdraw_rgb BROWN_SIENNA = {142, 90, 63};   // Muted/Earthy
const tdraw_rgb BROWN_SEPIA = {112, 66, 20};    // Deep/Rich Muted
const tdraw_rgb BROWN_CHESTNUT = {149, 78, 59}; // Deep/Rich Muted

// --- Gray definitions ---
const tdraw_rgb GRAY_CHARCOAL = {54, 69, 79};  // Original (Blue-Gray)
const tdraw_rgb GRAY_FOG = {201, 201, 204};    // Original (Light)
const tdraw_rgb GRAY_SLATE = {86, 95, 107};    // Muted/Earthy (Blue-Gray)
const tdraw_rgb GRAY_PEBBLE = {180, 180, 176}; // Muted/Earthy (Light)
const tdraw_rgb GRAY_CARBON = {68, 68, 68};    // Deep/Rich Muted (Neutral Dark)
const tdraw_rgb GRAY_MIST = {195, 195, 197};   // Deep/Rich Muted (Light)

tdraw_rgb **tdraw_canvas = NULL;
int tdraw_term_x = 0;
int tdraw_term_y = 0;

// --- Private functions ---
static void tdraw_get_terminal_size(int *x, int *y) {
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    *y = w.ws_row;
    *x = w.ws_col;
}

// --- API functions ---
void tdraw_init_canvas(void)
{
    tdraw_get_terminal_size(&tdraw_term_x, &tdraw_term_y);

    int real_width = tdraw_term_x;

    tdraw_term_x = real_width / 2;

    tdraw_canvas = (tdraw_rgb **)malloc(tdraw_term_y * sizeof(tdraw_rgb *));
    for (int i = 0; i < tdraw_term_y; i++)
    {
        tdraw_canvas[i] = (tdraw_rgb *)malloc(tdraw_term_x * sizeof(tdraw_rgb));
    }
}

void tdraw_free_canvas(void)
{
    for (int i = 0; i < tdraw_term_y; i++)
    {
        free(tdraw_canvas[i]);
    }
    free(tdraw_canvas);
}

void tdraw_clear_canvas(void)
{
    for (int y = 0; y < tdraw_term_y; y++)
    {
        for (int x = 0; x < tdraw_term_x; x++)
        {
            tdraw_canvas[y][x] = EMPTY;
        }
    }
}

void tdraw_clear_terminal(void)
{
    printf("\033[2J");
}

void tdraw_reset_cursor(void)
{
    printf("\033[H");
}

void tdraw_reset_colour(void)
{
    printf("\033[0m");
}

void tdraw_set_colour(tdraw_rgb c)
{
    printf("\033[48;2;%d;%d;%dm", c.red, c.green, c.blue);
}

void tdraw_set_pixel(int x_pos, int y_pos, tdraw_rgb c)
{
    if (y_pos < 0 || y_pos >= tdraw_term_y || x_pos < 0 || x_pos >= tdraw_term_x)
        return;
    tdraw_canvas[y_pos][x_pos] = c;
}

void tdraw_draw_frame(void)
{
    tdraw_clear_terminal();
    tdraw_reset_cursor();
    for (int y = tdraw_term_y - 1; y >= 0; y--)
    {
        for (int x = 0; x < tdraw_term_x; x++)
        {
            if (tdraw_canvas[y][x].red < 0)
            {
                printf("%s", TDRAW_BLOCK_STR);
            }
            else
            {
                tdraw_set_colour(tdraw_canvas[y][x]);
                printf("%s", TDRAW_BLOCK_STR);
                tdraw_reset_colour();
            }
        }
        printf("\n");
    }
    fflush(stdout);
}

#endif // TDRAW_IMPLEMENTATION