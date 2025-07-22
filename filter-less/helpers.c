#include <math.h>

#include "helpers.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int avg = 0;
    // Loop over all pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Take average of red, green, and blue
            avg = (int) round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) /
                              3.0);
            // Update pixel values
            image[i][j].rgbtBlue = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtRed = avg;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    int cmp_r = 0, cmp_g = 0, cmp_b = 0;
    // Loop over all pixels
    for (int i = 0; i < height; i++)
    {

        for (int j = 0; j < width; j++)
        {
            // Compute sepia values
            cmp_r = (int) round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen +
                                .189 * image[i][j].rgbtBlue);
            cmp_g = (int) round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen +
                                .168 * image[i][j].rgbtBlue);
            cmp_b = (int) round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen +
                                .131 * image[i][j].rgbtBlue);
            // Update pixel with sepia values
            image[i][j].rgbtRed = cmp_r > 255 ? 255 : cmp_r;
            image[i][j].rgbtGreen = cmp_g > 255 ? 255 : cmp_g;
            image[i][j].rgbtBlue = cmp_b > 255 ? 255 : cmp_b;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE swap;
    // Loop over all pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            // Swap pixels
            swap = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = swap;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Box -5 -4 -3 -1 0 1 3 4 5
    // Loop over all pixels
    // Create a copy of image
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Initialize
            int sum_r = 0, sum_g = 0, sum_b = 0;
            int count = 0;
            // Iterate through 3X3 grids
            for (int gi = -1; gi <= 1; gi++)
            {
                for (int gj = -1; gj <= 1; gj++)
                {
                    // Boundary issue first or last, row or column
                    // Conor 4 grids, side 6 grids
                    int ii = i + gi, jj = j + gj;
                    if (ii >= 0 && ii < height && jj >= 0 && jj < width)
                    {
                        sum_r += image[ii][jj].rgbtRed;
                        sum_g += image[ii][jj].rgbtGreen;
                        sum_b += image[ii][jj].rgbtBlue;
                        count++;
                    }
                }
            }
            // Make sure the original image won't be effect by blurred pixel
            copy[i][j].rgbtRed = (int) round((float) sum_r / count);
            copy[i][j].rgbtGreen = (int) round((float) sum_g / count);
            copy[i][j].rgbtBlue = (int) round((float) sum_b / count);
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = copy[i][j];
        }
    }
    return;
}
