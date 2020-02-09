#include "helpers.h"
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    BYTE blue = 0;
    BYTE green = 0;
    BYTE red = 0;
    float gray = 0;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            blue = image[i][j].rgbtBlue;
            green = image[i][j].rgbtGreen;
            red = image[i][j].rgbtRed;
            gray = round(((float)(blue + green + red) / 3.0));
            image[i][j].rgbtBlue = gray;
            image[i][j].rgbtGreen = gray;
            image[i][j].rgbtRed = gray;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Allocate memory for transfornedImage
    RGBTRIPLE(*transformedImage)[width] = calloc(height, width * sizeof(RGBTRIPLE));
    if (transformedImage == NULL)
    {
        fprintf(stderr, "Not enough memory to store image.\n");
        // fclose(outptr);
        // fclose(inptr);
        return;
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            transformedImage[i][j] = image[i][width - j - 1];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = transformedImage[i][j].rgbtBlue;
            image[i][j].rgbtGreen = transformedImage[i][j].rgbtGreen;
            image[i][j].rgbtRed = transformedImage[i][j].rgbtRed;
        }
    }
    free(transformedImage);
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}
