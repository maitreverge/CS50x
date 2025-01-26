#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop in each pixel in the image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Define average
            float average = (image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0;
            image[i][j].rgbtRed = round(average);
            image[i][j].rgbtGreen = round(average);
            image[i][j].rgbtBlue = round(average);
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop in each pixel in the image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Define sepia
            float sepiaRed = ((0.393 * image[i][j].rgbtRed) + (0.769 * image[i][j].rgbtGreen) + (0.189 * image[i][j].rgbtBlue));
            float sepiaGreen = ((0.349 * image[i][j].rgbtRed) + (0.686 * image[i][j].rgbtGreen) + (0.168 * image[i][j].rgbtBlue));
            float sepiaBlue = ((0.272 * image[i][j].rgbtRed) + (0.534 * image[i][j].rgbtGreen) + (0.131 * image[i][j].rgbtBlue));


            int red = round(sepiaRed);
            int green = round(sepiaGreen);
            int blue = round(sepiaBlue);
            // Apply Sepia Red
            if (red > 255)
            {
                image[i][j].rgbtRed = 255;
            }
            else if (red >= 0 && red <= 255)
            {
                image[i][j].rgbtRed = red;
            }

            // Apply sepia green
            if (green > 255)
            {
                image[i][j].rgbtGreen = 255;
            }
            else if (green >= 0 && green <= 255)
            {
                image[i][j].rgbtGreen = green;
            }

            // Apply Sepia blue
            if (blue > 255)
            {
                image[i][j].rgbtBlue = 255;
            }
            else if (blue >= 0 && blue <= 255)
            {
                image[i][j].rgbtBlue = blue;
            }
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop in each pixel in the image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            // swap
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = temp;

        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}

