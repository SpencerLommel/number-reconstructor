// Spencer Lommel
// May 2nd, 2025
// This file allows us to enter in a row number and generates a BMP image for that row.
// usage: ./line-number <row_number>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "csv-fast-reader/csv.h"
#include "bmp/bmp.h"

static void generate_number_bmp(uint8_t* pixels_data, size_t size, uint8_t number);

int main(int argc, char* argv[]) {
    // print out the usage if no line number given
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <row_number>\n", argv[0]);
        return 1;
    }

    // can only print rows 2+ so warn user
    int target_row = atoi(argv[1]);
    if (target_row < 2) {
        fprintf(stderr, "Row number must be 2 or more (row 1 is header)\n");
        return 1;
    }

    // actually added error handling this time =D
    CsvHandle handle = CsvOpen("mnist-in-csv/mnist_test.csv");
    if (!handle) {
        fprintf(stderr, "Failed to open CSV file.\n");
        return 1;
    }

    // skip header + rows until target_row
    for (int i = 0; i < target_row; i++) {
        char* row = CsvReadNextRow(handle);
        if (!row) {
            fprintf(stderr, "Row %d does not exist in the CSV.\n", target_row);
            CsvClose(handle);
            return 1;
        }
    
        if (i == target_row - 1) {
            const char* col = CsvReadNextCol(row, handle);
            uint8_t number = (uint8_t)atoi(col);
    
            uint8_t pixels[784];
            size_t pixel_count = 0;
    
            while ((col = CsvReadNextCol(row, handle)) && pixel_count < 784) {
                pixels[pixel_count++] = (uint8_t)atoi(col);
            }
    
            generate_number_bmp(pixels, pixel_count, number);
            printf("Generated BMP for row %d with number %u\n", target_row, number);
            break;
        }
    }
    

    CsvClose(handle);
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