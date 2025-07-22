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

// Detect edges
// gx -1 0 1   gy -1 -2 -1
//    -2 0 2       0  0  0
//    -1 0 1       1  2  1
// sum = 根號 gx^2+gy^2  < 255
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    int gx[] = {-1, 0, 1, -2, 0, 2, -1, 0, 1};
    int gy[] = {-1, -2, -1, 0, 0, 0, 1, 2, 1};
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Initialize
            double sum_r = 0.0, sum_g = 0.0, sum_b = 0.0;
            int sum_r_gx = 0, sum_g_gx = 0, sum_b_gx = 0;
            int sum_r_gy = 0, sum_g_gy = 0, sum_b_gy = 0;
            int k = 0;
            // Iterate through 3X3 grids
            for (int gi = -1; gi <= 1; gi++)
            {
                for (int gj = -1; gj <= 1; gj++, k++)
                {
                    int ii = i + gi, jj = j + gj;
                    // Inside the boundry
                    if (ii >= 0 && ii < height && jj >= 0 && jj < width)
                    {
                        sum_r_gx += image[ii][jj].rgbtRed * gx[k];
                        sum_r_gy += image[ii][jj].rgbtRed * gy[k];
                        sum_g_gx += image[ii][jj].rgbtGreen * gx[k];
                        sum_g_gy += image[ii][jj].rgbtGreen * gy[k];
                        sum_b_gx += image[ii][jj].rgbtBlue * gx[k];
                        sum_b_gy += image[ii][jj].rgbtBlue * gy[k];
                    }
                }
            }
            sum_r = (int) round(sqrt(sum_r_gx * sum_r_gx + sum_r_gy * sum_r_gy));
            sum_g = (int) round(sqrt(sum_g_gx * sum_g_gx + sum_g_gy * sum_g_gy));
            sum_b = (int) round(sqrt(sum_b_gx * sum_b_gx + sum_b_gy * sum_b_gy));
            // Cap the value at 255
            copy[i][j].rgbtRed = sum_r > 255 ? 255 : sum_r;
            copy[i][j].rgbtGreen = sum_g > 255 ? 255 : sum_g;
            copy[i][j].rgbtBlue = sum_b > 255 ? 255 : sum_b;
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
