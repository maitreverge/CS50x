#include "helpers.h"

void colorize(int height, int width, RGBTRIPLE image[height][width])
{
    // Define red color
    RGBTRIPLE color;
    color.rgbtRed = 255;
    color.rgbtGreen = 0;
    color.rgbtBlue = 0;

    // Loop in each pixel in the image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Check if the pixel is black
            if (image[i][j].rgbtRed == 0 && image[i][j].rgbtGreen == 0 && image[i][j].rgbtBlue == 0)
            {
                // Change the pixel to red color
                image[i][j] = color;
            }
        }
    }
}
