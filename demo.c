// Spencer Lommel
// May 2nd, 2025
// This file creates a BMP image for the 4th line in the mnist_train.csv dataset.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "csv-fast-reader/csv.h"
#include "bmp/bmp.h"

static void generate_number_bmp(uint8_t* pixels_data, size_t size, uint8_t number);

int main() {
    char* row;
    CsvHandle handle = CsvOpen("mnist-in-csv/mnist_train.csv");

    // skip header row to number 4 in csv training set
    row = CsvReadNextRow(handle);
    row = CsvReadNextRow(handle);
    row = CsvReadNextRow(handle);
    row = CsvReadNextRow(handle);



    const char* col;
    col = CsvReadNextCol(row, handle);
    uint8_t number = (uint8_t)atoi(col);

    // each number is 28x28 pixels so that's where the 784 comes from (28*28)
    uint8_t pixels[784];
    size_t pixel_count = 0;


    while ((col = CsvReadNextCol(row, handle)) && pixel_count < 784) {
        pixels[pixel_count++] = (uint8_t)atoi(col);
    }

    generate_number_bmp(pixels, pixel_count, number);

    return 0;
}

static void generate_number_bmp(uint8_t* pixels_data, size_t size, uint8_t number) {
    bmp_t bmp;
    unsigned int width = 28, height = 28;

    // Initialize a 24-bit BMP, we don't use 32-bit color-depth because not all photo viewers support it
    // which is odd because it's part of the BMP spec so it should be supported >:(
    bmp_init_data(&bmp, width, height, 24);
    color_24bpp_t* pixels = (color_24bpp_t*)bmp.data;

    // Convert each intensity value to a grayscale color
    // We'll read from bottom to top to flip the image

    // The reason we are doing this flip is mostly due to my BMP parser implementation. I do plan on extending this in the future.
    for (unsigned int y = 0; y < height; y++) {
        for (unsigned int x = 0; x < width; x++) {
            // Calculate source and destination indices
            size_t src_idx = y * width + x;  // Original index
            size_t dst_idx = (height - 1 - y) * width + x;  // Flipped index
            
            if (src_idx < size) {
                uint8_t intensity = pixels_data[src_idx];
                pixels[dst_idx] = (color_24bpp_t){intensity, intensity, intensity};
            }
        }
    }

    char filename[32];
    snprintf(filename, sizeof(filename), "%u.bmp", number);

    bmp_save(&bmp, filename);
    bmp_destroy(&bmp);
}