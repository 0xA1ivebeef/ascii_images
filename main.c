
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define MY_PGM_IMPLEMENTATION
#include "my_pgm.h"

#define IMAGE_PATH "peter-griffin.jpg"

#define ROWS 70
#define COLS 280

const char* ascii_ramp = "Ñ@#W$9876543210?!abc;:+=-_,. ";

void print_ascii(const unsigned char* gray, int w, int h, int out_w, const char* ramp)
{
    int ramp_len = strlen(ramp);
    int out_h = (int)(h * (out_w / (double)w) * 0.5);
    
    for (int y = 0; y < out_h; ++y)
    {
        int src_y = y*h/out_h;

        for (int x = 0; x < out_w; ++x)
        {
            int src_x = x*w/out_w;

            unsigned char g = gray[src_y * w + src_x];
            int idx = (255-g)*(ramp_len - 1)/255;

            putchar(ascii_ramp[idx]);
        }
        putchar('\n');
    }
}

int main(void)
{
    int w, h, c;
    unsigned char* pixels = stbi_load(IMAGE_PATH, &w, &h, &c, 0);
    if (!pixels)
    {
        fprintf(stderr, "main: could not load image: %s\n", IMAGE_PATH);
        exit(1);
    }

    printf("width %d, height %d, channels %d\n", w, h, c);
    
    unsigned char buff [w*h]; 
    get_pgm_from_rgb(pixels, buff, w, h, c);

    // optional
    // save_pgm("output.pgm", buff, w, h);

    print_ascii(buff, w, h, COLS, ascii_ramp);

    stbi_image_free(pixels);
        
    return 0;
}
