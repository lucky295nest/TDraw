#define TDRAW_IMPLEMENTATION
#include "tdraw.h"

#include <time.h>

// --- Drawings ---
// Line
void interrupted_line(int length)
{
    int space = 1;
    int y = tdraw_term_y / 2;
    for (int i = 0; i < length * 2; i++)
    {
        if (space == 1)
        {
            tdraw_set_pixel(i, tdraw_term_y / 2, GREEN_LIME);
            space *= -1;
        }
        else
        {
            tdraw_set_pixel(i, y, EMPTY);
            space *= -1;
        }
    }
    tdraw_draw_frame();
}

// Stairs
void stairs(int number_of_stairs)
{
    int nos = number_of_stairs + 1;

    for (int i = 0; i < nos; i++)
    {
        for (int j = 0; j < i; j++)
        {
            tdraw_set_pixel(i, j, BLUE_CERULEAN);
        }
    }

    int offset = 2;
    for (int i = 0; i < nos; i++)
    {
        for (int j = 0; j < i; j++)
        {
            tdraw_set_pixel(i + offset, j, EMPTY);
        }
    }
    tdraw_draw_frame();
}

// Flower
void flower(int x_pos, int y_pos, int height, int width, tdraw_rgb color)
{
    if (width % 2 == 0)
    {
        printf("Width must be odd\n");
        return;
    }

    int petal_size = width - (width / 2);
    // int mid_x = (tdraw_term_x / 2);
    // int mid_y = (tdraw_term_y / 2) + (height / 2);

    for (int i = 0; i < height; i++)
    {
        tdraw_set_pixel(x_pos, y_pos - i, GREEN_PINE);
    }

    tdraw_set_pixel(x_pos, y_pos - petal_size + 1, YELLOW_SAFFRON);
    for (int i = 1; i < petal_size; i++)
    {
        tdraw_set_pixel(x_pos + i, y_pos - petal_size + 1, color);
        tdraw_set_pixel(x_pos - i, y_pos - petal_size + 1, color);
        tdraw_set_pixel(x_pos, y_pos + i - petal_size + 1, color);
        tdraw_set_pixel(x_pos, y_pos - i - petal_size + 1, color);

        tdraw_set_pixel(x_pos + i, y_pos - petal_size + 1 + i, color);
        tdraw_set_pixel(x_pos - i, y_pos - petal_size + 1 - i, color);

        tdraw_set_pixel(x_pos - i, y_pos - petal_size + 1 + i, color);
        tdraw_set_pixel(x_pos + i, y_pos - petal_size + 1 - i, color);
    }

    tdraw_draw_frame();
}

// Meadow
void meadow(int col, int row)
{
    tdraw_rgb color = EMPTY;

    int offset_x = 6;
    int offset_y = 11;

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            int c = rand() % 4;
            switch (c)
            {
            case 0:
                color = RED_GARNET;
                break;
            case 1:
                color = VIOLET_WISTERIA;
                break;
            case 2:
                color = PINK_BLUSH;
                break;
            case 3:
                color = ORANGE_RUST;
                break;
            default:
                break;
            }
            flower(3 + offset_x * j, 8 + row + offset_y * i, 10, 5, color);
        }
    }

    tdraw_draw_frame();
}

// --- Animations ---
void squares_anim(int frames)
{
    int main_sqr_size = 6;
    int main_sqr_pos_x = 2;
    int main_sqr_pos_y = 3;

    int scnd_sqr_size = 4;
    int scnd_sqr_pos_x = main_sqr_pos_x + 1;
    int scnd_sqr_pos_y = main_sqr_pos_y + 1;

    int thrd_sqr_size = 2;
    int thrd_sqr_pos_x = main_sqr_pos_x + 2;
    int thrd_sqr_pos_y = main_sqr_pos_y + 2;

    int mvng_sqr_pos_x = 0;
    int mvng_sqr_pos_y = 5;
    int mvng_sqr_state = 0;

    for (int f = 0; f < frames; f++)
    {
        int state = f % 3;

        tdraw_clear_canvas();

        // Main square
        main_sqr_pos_x++;
        for (int i = 0; i < main_sqr_size; i++)
        {
            for (int j = 0; j < main_sqr_size; j++)
            {
                tdraw_set_pixel(main_sqr_pos_x + j, main_sqr_pos_y + i, RED);
            }
        }

        // Second square
        scnd_sqr_pos_x++;
        for (int i = 0; i < scnd_sqr_size; i++)
        {
            for (int j = 0; j < scnd_sqr_size; j++)
            {
                if (state == 1 || state == 2)
                {
                    tdraw_set_pixel(scnd_sqr_pos_x + j, scnd_sqr_pos_y + i, BLUE);
                }
            }
        }

        // Third square
        thrd_sqr_pos_x++;
        for (int i = 0; i < thrd_sqr_size; i++)
        {
            for (int j = 0; j < thrd_sqr_size; j++)
            {
                if (state == 2)
                {
                    tdraw_set_pixel(thrd_sqr_pos_x + j, thrd_sqr_pos_y + i, GREEN);
                }
            }
        }

        // Moving square
        tdraw_set_pixel(mvng_sqr_pos_x + main_sqr_pos_x, mvng_sqr_pos_y + main_sqr_pos_y, GREEN);
        mvng_sqr_state++;
        if (mvng_sqr_state < 6)
        {
            mvng_sqr_pos_x++;
        }
        else if (mvng_sqr_state >= 6 && mvng_sqr_state < 11)
        {
            mvng_sqr_pos_y--;
        }
        else if (mvng_sqr_state >= 11 && mvng_sqr_state < 16)
        {
            mvng_sqr_pos_x--;
        }
        else if (mvng_sqr_state >= 16 && mvng_sqr_state < 21)
        {
            mvng_sqr_pos_y++;
        }
        else if (mvng_sqr_state == 21)
        {
            mvng_sqr_state = 1;
            mvng_sqr_pos_x++;
        }

        tdraw_draw_frame();
        usleep(400000);
    }
}

void firework()
{
    int speed = 70000;

    int mid_x = tdraw_term_x / 2;
    int mid_y = tdraw_term_y / 2;

    int height = mid_y;
    int fw_x = mid_x;

    int radius = 15;
    int fw_y = 0;

    tdraw_rgb color = BLUE_CERULEAN;

    for (int i = 0; i < height; i++)
    {
        tdraw_clear_canvas();
        tdraw_set_pixel(fw_x, fw_y + i, WHITE);
        tdraw_draw_frame();
        usleep(speed);
    }

    int rays = 20;
    for (int i = 0; i < radius; i++)
    {
        for (int j = 0; j < rays; j++)
        {
            int c = rand() % 6;
            switch (c)
            {
            case 0:
                color = RED_SCARLET;
                break;
            case 1:
                color = RED;
                break;
            case 2:
                color = WHITE;
                break;
            case 3:
                color = BLUE_CERULEAN;
                break;
            case 4:
                color = GREEN_LIME;
                break;
            case 5:
                color = GREEN;
                break;
            default:
                break;
            }

            float angle = (2 * 3.14 * j) / rays;
            int x = mid_x + (int)(cos(angle) * i);
            int y = mid_y + (int)(sin(angle) * i);
            tdraw_set_pixel(x, y, color);
        }
        tdraw_draw_frame();
        usleep(speed);
    }

    for (int i = 0; i < radius; i++)
    {
        for (int j = 0; j < rays; j++)
        {
            float angle = (2 * 3.14 * j) / rays;
            int x = mid_x + (int)(cos(angle) * i);
            int y = mid_y + (int)(sin(angle) * i);
            tdraw_set_pixel(x, y, EMPTY);
        }
        tdraw_draw_frame();
        usleep(speed);
    }
}

// --- Example menu ---
void choice()
{
    int choice = 0;
    int charnum = 0;
    do
    {
        charnum = 0;
        printf("+-----------------------+\n");
        printf("| 0) interrupted line   |\n");
        printf("| 1) stairs             |\n");
        printf("| 2) flower             |\n");
        printf("| 3) meadow             |\n");
        printf("| 4) animation          |\n");
        printf("| 5) firework           |\n");
        printf("+-----------------------+\n");
        printf("choice: ");
        scanf("%d", &choice);
        while (getchar() != '\n')
        {
            charnum++;
        }

    } while (charnum > 0);

    int a = 0;
    int b = 0;

    switch (choice)
    {
    case 0:
        a = 0;
        printf("length: ");
        scanf("%d", &a);
        interrupted_line(a);
        break;
    case 1:
        a = 0;
        printf("stair count: ");
        scanf("%d", &a);
        stairs(a);
        break;
    case 2:
        a = 0;
        b = 0;
        printf("width: ");
        scanf("%d", &a);
        printf("height: ");
        scanf("%d", &b);
        flower(tdraw_term_x / 2, tdraw_term_y / 2, b, a, RED_GARNET);
        break;
    case 3:
        a = 0;
        b = 0;
        printf("rows: ");
        scanf("%d", &a);
        printf("cols: ");
        scanf("%d", &b);
        meadow(b, a);
        break;
    case 4:
        a = 0;
        printf("how long should the animation be (in frames): ");
        scanf("%d", &a);
        squares_anim(a);
        break;
    case 5:
        firework();
        break;
    default:
        return;
        break;
    }
}

int main()
{
    srand(time(NULL));

    tdraw_init_canvas();
    tdraw_clear_canvas();

    choice();

    tdraw_free_canvas();
    return 0;
}