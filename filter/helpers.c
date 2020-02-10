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
        fprintf(stderr, "Not enough memory to process image.\n");
        return;
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            transformedImage[i][j] = image[i][width - j - 1];
        }
    }
    // copy tranformedImage into image
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
    if (height == 1 && width == 1)
    {
        printf("Can't blur single pixel image!\n");
        return;
    }
    float blue = 0;
    float green = 0;
    float red = 0;
    int n = 0;
    // Allocate memory for transfornedImage
    RGBTRIPLE(*transformedImage)[width] = calloc(height, width * sizeof(RGBTRIPLE));
    if (transformedImage == NULL)
    {
        fprintf(stderr, "Not enough memory to process image.\n");
        return;
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            blue = 0;
            green = 0;
            red = 0;
            n = 0;
            for (int s = i - 1; s <= i + 1; s++)
            {
                for (int t = j - 1; t <= j + 1; t++)
                {
                    // choose surrounding pixels, check for edges
                    if (s >= 0 && s < height && t >= 0 && t < width)
                    {
                        blue = blue + (float) image[s][t].rgbtBlue;
                        green = green + (float) image[s][t].rgbtGreen;
                        red = red + (float) image[s][t].rgbtRed;
                        n++;
                    }
                }
            }
            // average of surrounding pixeds
            if (n > 0)
            {
                blue = round(blue / n);
                green = round(green / n);
                red = round(red / n);
                transformedImage[i][j].rgbtBlue = blue;
                transformedImage[i][j].rgbtGreen = green;
                transformedImage[i][j].rgbtRed = red;
            }
        }
    }
    // copy tranformedImage into image
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

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Allocate memory for transfornedImage
    RGBTRIPLE(*transformedImage)[width] = calloc(height, width * sizeof(RGBTRIPLE));
    if (transformedImage == NULL)
    {
        fprintf(stderr, "Not enough memory to process image.\n");
        return;
    }
    int blueX = 0;
    int greenX = 0;
    int redX = 0;
    int blueY = 0;
    int greenY = 0;
    int redY = 0;
    float blue;
    float green;
    float red;
    // Sobel kernals
    int Gx[3][3] = {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };
        int Gy[3][3] = {
        {-1, -2, -1},
        {0, 0, 0},
        {1, 2, 1}
    };

for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            blueX = 0;
            greenX = 0;
            redX = 0;
            blueY = 0;
            greenY = 0;
            redY = 0;
            for (int s = 0; s < 3; s++)
            {
                for (int t = 0; t < 3; t++)
                {
                    // choose surrounding pixels
                    // TODO: pad edges with black pixels
                    if (i + s >= 0 && i + s < height && j + t >= 0 && j + t < width)
                    {
                        blueX = blueX + Gx[s][t] * image[i + s][j + t].rgbtBlue;
                        greenX = greenX + Gx[s][t] * image[i + s][j + t].rgbtGreen;
                        redX = redX + Gx[s][t] * image[i + s][j + t].rgbtRed;

                        blueY = blueY + Gy[s][t] * image[i + s][j + t].rgbtBlue;
                        greenY = greenY + Gy[s][t] * image[i + s][j + t].rgbtGreen;
                        redY= redY + Gy[s][t] * image[i + s][j + t].rgbtRed;
                    }
                }
            }
            blue = round(sqrt(pow(blueX, 2) + pow(blueY,2)));
            if (blue > 255)
            {
                blue = 255;
            }
            green = round(sqrt(pow(greenX, 2) + pow(greenY,2)));
            if (green > 255)
            {
                green = 255;
            }
            red = round((sqrt(pow(redX, 2) + pow(redY,2))));
            if (red > 255)
            {
                red = 255;
            }
            image[i][j].rgbtBlue = (int) blue;
            image[i][j].rgbtGreen = (int) green;
            image[i][j].rgbtRed = (int) red;
        }
    }
    // printf("blue %c, green %c, red %c\n", image[height][width].rgbtBlue, image[height][width].rgbtGreen, image[height][width].rgbtRed);
    // printf("blue %f, green %f, red %f\n", blue, green, red);
    return;
}
