## 🚀 Getting Started

The `tdraw` library is designed for ease of use in a single-file setup.

### Integration

To use the library, you need to include the header file (`tdraw.h`) and define the `TDRAW_IMPLEMENTATION` preprocessor macro in **exactly one** C source file to include the function definitions.

**`main.c` example:**

```c
#define TDRAW_IMPLEMENTATION // Must be defined in one C file
#include "tdraw.h"

int main()
{
    // 1. Initialize the drawing canvas
    tdraw_init_canvas(); 
    
    // 2. Clear the canvas to the EMPTY color
    tdraw_clear_canvas();
    
    // 3. Draw something (e.g., a pixel)
    tdraw_set_pixel(1, 1, RED); 
    
    // 4. Render the frame to the terminal
    tdraw_draw_frame(); 

    // 5. Free the memory
    tdraw_free_canvas();
    
    return 0;
}
```

### Canvas and Coordinates

The library utilizes a 2D canvas defined by the terminal's size.

  * **Size:** The canvas dimensions are determined by the terminal's current size at initialization.
      * `tdraw_term_y`: The height of the canvas (in terminal rows).
      * `tdraw_term_x`: The width of the canvas (in drawing pixels). Note that the internal drawing width (`tdraw_term_x`) is **half** the actual terminal column width, as each "pixel" is rendered using the `TDRAW_BLOCK_STR` (`"  "`), which is 2 spaces wide to provide a roughly square aspect ratio for terminal cells.
  * **Coordinates:** The coordinate system is **origin-at-bottom-left**.
      * $x$-coordinates increase to the **right**.
      * $y$-coordinates increase **upwards** (from $0$ at the bottom row to `tdraw_term_y - 1` at the top row).

-----

## 🎨 Color System

Colors are defined using the `tdraw_rgb` structure:

```c
typedef struct
{
    int red;
    int green;
    int blue;
} tdraw_rgb;
```

Color components range from $0$ to $255$.

### Predefined Colors

The library provides a comprehensive set of predefined `tdraw_rgb` constants, grouped by hue and tone.

  * **Basic Colors:** `BLACK`, `WHITE`, `RED`, `GREEN`, `BLUE`, and the special **transparent** color `EMPTY` (used to clear or leave a pixel uncolored, often defined as $\{-1, -1, -1\}$).
  * **Named Colors:** A large palette of named colors (e.g., `RED_SCARLET`, `GREEN_EMERALD`, `BLUE_NAVY`, `PINK_FUCHSIA`, `YELLOW_SAFFRON`, etc.) categorized by tone (Original, Muted/Earthy, Deep/Rich Muted).

**Example Usage:**

```c
tdraw_set_pixel(5, 5, BLUE_SAPPHIRE);
tdraw_set_pixel(6, 5, PINK_CORAL);
```

-----

## 🛠️ API Functions

### Initialization and Cleanup

| Function | Description |
| :--- | :--- |
| `void tdraw_init_canvas(void)` | Initializes the canvas array (`tdraw_canvas`) based on the current terminal size and allocates memory. **Must be called first.** |
| `void tdraw_free_canvas(void)` | Frees the memory allocated for the canvas. **Must be called at the end.** |
| `void tdraw_clear_canvas(void)` | Sets every pixel in the canvas to the `EMPTY` color. |

### Drawing

| Function | Description |
| :--- | :--- |
| `void tdraw_set_pixel(int x, int y, tdraw_rgb c)` | Sets the color of a specific pixel at coordinates $(x, y)$ on the canvas to color $c$. Coordinates outside the canvas bounds are ignored. |
| `void tdraw_draw_frame(void)` | Renders the current state of the `tdraw_canvas` to the terminal. It clears the terminal, resets the cursor to the top-left, and then draws the frame row by row. **Must be called to see any changes.** |

### Terminal Control (Lower-Level)

These functions are primarily used internally by `tdraw_draw_frame()` but are available for more control.

| Function | Description |
| :--- | :--- |
| `void tdraw_clear_terminal(void)` | Clears all content on the terminal screen (`\033[2J`). |
| `void tdraw_reset_cursor(void)` | Moves the cursor to the top-left corner (`\033[H`). |
| `void tdraw_reset_colour(void)` | Resets the terminal's foreground and background color to default (`\033[0m`). |
| `void tdraw_set_colour(tdraw_rgb c)` | Sets the terminal's **background** color to the given RGB color $c$ using 24-bit ANSI codes (`\033[48;2;R;G;Bm`). |

-----

## 💡 Animation

Creating animations involves a loop that repeatedly:

1.  Clears the canvas (`tdraw_clear_canvas()`).
2.  Calculates new positions/states and draws the frame content (`tdraw_set_pixel()`).
3.  Renders the frame (`tdraw_draw_frame()`).
4.  Pauses for a short duration (often using `usleep()` for microsecond delay) to control the framerate.

**Example from example.c code (`homework_anim`):**

```c
// ... inside an animation loop ...
tdraw_clear_canvas(); // Clear the previous frame
// ... calculate and draw new pixels ...
tdraw_draw_frame();   // Display the new frame
usleep(400000);       // Pause for 400,000 microseconds (0.4 seconds)
```
