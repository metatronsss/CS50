// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file A.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        fclose(input);
        printf("Could not open file B.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    // TODO: Copy header from input file to output file
    // Copy header from input file to output file
    uint8_t header[HEADER_SIZE];
    // Read a unit of 44 bytes (header size) from the input file and store it in the 'header'
    // structure.
    fread(header, HEADER_SIZE, 1, input);
    // Read a unit of 44 bytes (header size) from the header structure and store it in the output
    // file.
    fwrite(header, HEADER_SIZE, 1, output);
    // TODO: Read samples from input file and write updated data to output file
    // Create a buffer for a single sample
    int16_t *buffer = malloc(sizeof(int16_t));
    // Read single sample from input into buffer while there are samples left to read
    while (fread(buffer, sizeof(int16_t), 1, input))
    {
        if (buffer == NULL)
        {
            printf("Malloc failed");
            return 1;
        }
        // Update volume of sample
        *buffer *= factor;

        // Write updated sample to new file
        fwrite(buffer, sizeof(int16_t), 1, output);
    }
    // Close files
    fclose(input);
    fclose(output);

    // free memory
    free(buffer);

    return 0;
}
