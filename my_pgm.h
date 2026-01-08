
#ifndef MY_PGM_H
#define MY_PGM_H

static int save_pgm(const char* filename, const unsigned char* px, const int width, const int height);
static int get_pgm_from_rgb(const unsigned char* px, unsigned char* buff, const int width, const int height, const int channels);

#ifdef MY_PGM_IMPLEMENTATION

#include <stdio.h>
#include <stdlib.h>

static int save_pgm(const char* filename, const unsigned char* px, const int width, const int height) 
{   
    if (!px || width <= 0 || height <= 0)
    {
        fprintf(stderr, "save_pgm: invalid input\n");
        return -1;
    }

    FILE* f = fopen(filename != NULL ? filename : "output.pgm", "wb");
    if (!f)
    {
        fprintf(stderr, "file could not be created\n");
        return -1;
    }

    fprintf(f, "P5\n");
    fprintf(f, "%d %d\n", width, height);
    fprintf(f, "255\n");

    size_t written = fwrite(px, 1, width * height, f);
    if (written != (size_t)(width*height))
    {
        fprintf(stderr, "save_pgm: lost some data while writing\n");
        fclose(f);
        return -1;
    }

    fclose(f);

    return 0;
}

static int get_pgm_from_rgb(const unsigned char* px, unsigned char* buff, const int width, const int height, const int channels)
{
    if (!px || !buff || channels < 3 || width <= 0 || height <= 0)
    {
        fprintf(stderr, "get_pgm_from_rgb: invalid input\n");
        return -1;
    }

    int j = 0;
    size_t count = (size_t)width*height*channels;
    for (size_t i = 0; i < count; i+=channels)
        buff[j++] = (unsigned char)(0.299*px[i] + 0.587*px[i+1] + 0.114*px[i+2]);;

    // saturation: 0-100
    // function to add saturation maps greyscale value x - 0-255
    // the higher saturation, the higher x but max 255

    return 0;
}

#endif
#endif

