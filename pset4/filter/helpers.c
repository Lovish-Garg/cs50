#include "helpers.h"
#include<math.h>

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    float greater;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float sepia_red = (.393 * image[i][j].rgbtRed) + (.769 * image[i][j].rgbtGreen) + (.189 * image[i][j].rgbtBlue);

            greater = sepia_red - (int)sepia_red;

            if (greater > 0.5)
            {
                sepia_red += 0.5;
            }
            if ((int)sepia_red > 255)
            {
                sepia_red = 255;
            }


            float sepia_green = (.349 * image[i][j].rgbtRed) + (.686 * image[i][j].rgbtGreen) + (.168 * image[i][j].rgbtBlue);

            greater = sepia_green - (int)sepia_green;

            if (greater > 0.5)
            {
                sepia_green += 0.5;
            }
            if (sepia_green > 255)
            {
                sepia_green = 255;
            }


            float sepia_blue = (.272 * image[i][j].rgbtRed) + (.534 * image[i][j].rgbtGreen) + (.131 * image[i][j].rgbtBlue);

            greater = sepia_blue - (int)sepia_blue;

            if (greater > 0.5)
            {
                sepia_blue += 0.5;
            }
            if (sepia_blue > 255)
            {
                sepia_blue = 255;
            }

            image[i][j].rgbtRed = (int)sepia_red;
            image[i][j].rgbtGreen = (int)sepia_green;
            image[i][j].rgbtBlue = (int)sepia_blue;

        }
    }
    return;
}

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    float average;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j <width; j++)
        {
            average = (image[i][j].rgbtRed + image[i][j].rgbtBlue + image[i][j].rgbtGreen) / 3.0;
            float check_greater = average - (int)average;
            if (check_greater > 0.5)
            {
                image[i][j].rgbtBlue = (int)(average + 0.5);
                image[i][j].rgbtRed = (int)(average + 0.5);
                image[i][j].rgbtGreen = (int)(average + 0.5);
            }
            else
            {
                image[i][j].rgbtBlue = (int)average;
                image[i][j].rgbtRed = (int)average;
                image[i][j].rgbtGreen = (int)average;
            }
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width/2; j++)
        {
            int red = image[i][width - j - 1].rgbtRed;
            int blue = image[i][width - j - 1].rgbtBlue;
            int green = image[i][width - j - 1].rgbtGreen;

            // Copying RGB's to the opposite array
            image[i][width - j - 1].rgbtRed = image[i][j].rgbtRed;
            image[i][width - j - 1].rgbtBlue = image[i][j].rgbtBlue;
            image[i][width - j- 1].rgbtGreen = image[i][j].rgbtGreen;

            // Initialising recorded data to [i][j] array
            image[i][j].rgbtRed = red;
            image[i][j].rgbtBlue = blue;
            image[i][j].rgbtGreen = green;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    int check1, check2;

    RGBTRIPLE copy[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j].rgbtRed = image[i][j].rgbtRed;
            copy[i][j].rgbtBlue = image[i][j].rgbtBlue;
            copy[i][j].rgbtGreen = image[i][j].rgbtGreen;
        }
    }

    int red,blue,green;
    float diff, average;

    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            // if pixel is a top left corner
            if(i == 0 && j == 0)
            {
                red = copy[i][j].rgbtRed + copy[i][j + 1].rgbtRed + copy[i + 1][j].rgbtRed + copy[i + 1][j + 1].rgbtRed;

                blue = copy[i][j].rgbtBlue + copy[i][j + 1].rgbtBlue + copy[i + 1][j].rgbtBlue + copy[i + 1][j + 1].rgbtBlue;

                green = copy[i][j].rgbtGreen + copy[i][j + 1].rgbtGreen + copy[i + 1][j].rgbtGreen + copy[i + 1][j + 1].rgbtGreen;

                average = red / 4.0; // 4 because we have been colecting data of only 4 pixels
                diff = average - (int)average;

                if (diff >= 0.5)
                {
                    average += 0.5;
                }

                image[i][j].rgbtRed = (int)average;

                average = blue / 4.0; // 4 because we have been colecting data of only 4 pixels
                diff = average - (int)average;

                if (diff >= 0.5)
                {
                    average += 0.5;
                }

                image[i][j].rgbtBlue = (int)average;

                average = green / 4.0; // 4 because we have been colecting data of only 4 pixels
                diff = average - (int)average;

                if(diff >= 0.5)
                {
                    average +=0.5;
                }

                image[i][j].rgbtGreen = (int)average;
            }  // if pixel is a corner at top-right
            else if(i == 0 && j == width - 1)
            {
                red = copy[i][j - 1].rgbtRed + copy[i][j].rgbtRed + copy[i + 1][j - 1].rgbtRed + copy[i + 1][j].rgbtRed;

                blue = copy[i][j- 1 ].rgbtBlue + copy[i][j].rgbtBlue + copy[i + 1][j - 1].rgbtBlue + copy[i + 1][j].rgbtBlue;

                green = copy[i][j - 1].rgbtGreen + copy[i][j].rgbtGreen + copy[i + 1][j - 1].rgbtGreen + copy[i + 1][j].rgbtGreen;

                average = red / 4.0; // 4 because we have been colecting data of only 4 pixels
                diff = average - (int)average;

                if (diff >= 0.5)
                {
                    average += 0.5;
                }

                image[i][j].rgbtRed = (int)average;

                average = blue / 4.0; // 4 because we have been colecting data of only 4 pixels
                diff = average - (int)average;

                if(diff >= 0.5)
                {
                    average += 0.5;
                }

                image[i][j].rgbtBlue = (int)average;

                average = green / 4.0; // 4 because we have been colecting data of only 4 pixels
                diff = average - (int)average;

                if(diff >= 0.5)
                {
                    average += 0.5;
                }

                image[i][j].rgbtGreen = (int)average;
            } // if pixel is at bottom left corner
            else if(i == height-1 && j == 0)
            {
                red = copy[i - 1][j].rgbtRed + copy[i - 1][j + 1].rgbtRed + copy[i][j].rgbtRed + copy[i][j + 1].rgbtRed;

                blue = copy[i - 1][j].rgbtBlue + copy[i - 1][j + 1].rgbtBlue + copy[i][j].rgbtBlue + copy[i][j + 1].rgbtBlue;

                green = copy[i - 1][j].rgbtGreen + copy[i - 1][j + 1].rgbtGreen + copy[i][j].rgbtGreen + copy[i][j + 1].rgbtGreen;

                average = red / 4.0; // 4 because we have been colecting data of only 4 pixels
                diff = average - (int)average;

                if(diff >= 0.5)
                {
                    average += 0.5;
                }

                image[i][j].rgbtRed = (int)average;

                average = blue / 4.0; // 4 because we have been colecting data of only 4 pixels
                diff = average - (int)average;

                if(diff >= 0.5)
                {
                    average += 0.5;
                }

                image[i][j].rgbtBlue = (int)average;

                average = green / 4.0; // 4 because we have been colecting data of only 4 pixels
                diff = average - (int)average;

                if (diff >= 0.5)
                {
                    average += 0.5;
                }

                image[i][j].rgbtGreen = (int)average;
            } // if pixel is at right bottom
            else if(i == height-1 && j == width-1)
            {
                red = copy[i - 1][j - 1].rgbtRed + copy[i - 1][j].rgbtRed + copy[i][j - 1].rgbtRed + copy[i][j].rgbtRed;

                blue = copy[i - 1][j - 1].rgbtBlue + copy[i - 1][j].rgbtBlue + copy[i][j - 1].rgbtBlue + copy[i][j].rgbtBlue;

                green = copy[i - 1][j - 1].rgbtGreen + copy[i - 1][j].rgbtGreen + copy[i][j - 1].rgbtGreen + copy[i][j].rgbtGreen;

                average = red / 4.0; // 4 because we have been colecting data of only 4 pixels
                diff = average - (int)average;

                if(diff >= 0.5)
                {
                    average +=0.5;
                }

                image[i][j].rgbtRed = (int)average;

                average = blue / 4.0; // 4 because we have been colecting data of only 4 pixels
                diff = average - (int)average;

                if(diff >= 0.5)
                {
                    average += 0.5;
                }

                image[i][j].rgbtBlue = (int)average;

                average = green / 4.0; // 4 because we have been colecting data of only 4 pixels
                diff = average - (int)average;

                if(diff >= 0.5)
                {
                    average += 0.5;
                }

                image[i][j].rgbtGreen = (int)average;
            } // if pixel is at between of first row edge
            else if(i == 0 && (j > 0 && j != width-1))
            {
                red = copy[i][j - 1].rgbtRed + copy[i][j].rgbtRed + copy[i][j + 1].rgbtRed + copy[i + 1][j - 1].rgbtRed + copy[i+1][j].rgbtRed + copy[i+1][j+1].rgbtRed;

                blue = copy[i][j-1].rgbtBlue + copy[i][j].rgbtBlue + copy[i][j+1].rgbtBlue + copy[i+1][j-1].rgbtBlue + copy[i+1][j].rgbtBlue + copy[i+1][j+1].rgbtBlue;

                green = copy[i][j-1].rgbtGreen + copy[i][j].rgbtGreen + copy[i][j+1].rgbtGreen+ copy[i+1][j-1].rgbtGreen + copy[i+1][j].rgbtGreen + copy[i+1][j+1].rgbtGreen;

                average = red / 6.0; // 4 because we have been colecting data of only 4 pixels
                diff = average - (int)average;

                if(diff >= 0.5)
                {
                    average +=0.5;
                }

                image[i][j].rgbtRed = (int)average;

                average = blue / 6.0; // 4 because we have been colecting data of only 4 pixels
                diff = average - (int)average;

                if(diff >= 0.5)
                {
                    average += 0.5;
                }

                image[i][j].rgbtBlue = (int)average;

                average = green / 6.0; // 4 because we have been colecting data of only 4 pixels
                diff = average - (int)average;

                if(diff >= 0.5)
                {
                    average += 0.5;
                }

                image[i][j].rgbtGreen = (int)average;
            } // if pixel is in between last row edge
            else if(i == height-1 && (j > 0 && j != width-1))
            {
                red = copy[i-1][j-1].rgbtRed + copy[i-1][j].rgbtRed + copy[i-1][j+1].rgbtRed + copy[i][j-1].rgbtRed + copy[i][j].rgbtRed + copy[i][j+1].rgbtRed;

                blue = copy[i-1][j-1].rgbtBlue + copy[i-1][j].rgbtBlue + copy[i-1][j+1].rgbtBlue + copy[i][j-1].rgbtBlue + copy[i][j].rgbtBlue + copy[i][j+1].rgbtBlue;

                green = copy[i-1][j-1].rgbtGreen + copy[i-1][j].rgbtGreen + copy[i-1][j+1].rgbtGreen+ copy[i][j-1].rgbtGreen + copy[i][j].rgbtGreen + copy[i][j+1].rgbtGreen;

                average = red / 6.0; // 4 because we have been colecting data of only 4 pixels
                diff = average - (int)average;

                if(diff >= 0.5)
                {
                    average +=0.5;
                }

                image[i][j].rgbtRed = (int)average;

                average = blue / 6.0; // 4 because we have been colecting data of only 4 pixels
                diff = average - (int)average;

                if(diff >= 0.5)
                {
                    average += 0.5;
                }

                image[i][j].rgbtBlue = (int)average;

                average = green / 6.0; // 4 because we have been colecting data of only 4 pixels
                diff = average - (int)average;

                if(diff >= 0.5)
                {
                    average += 0.5;
                }

                image[i][j].rgbtGreen = (int)average;
            } // if pixel is in between left edge
            else if((i != 0 && i != height-1) && j == 0)
            {
                red = copy[i - 1][j].rgbtRed + copy[i-1][j+1].rgbtRed + copy[i][j].rgbtRed + copy[i][j+1].rgbtRed + copy[i+1][j].rgbtRed + copy[i+1][j+1].rgbtRed;

                blue = copy[i-1][j].rgbtBlue + copy[i-1][j+1].rgbtBlue + copy[i][j].rgbtBlue + copy[i][j+1].rgbtBlue + copy[i+1][j].rgbtBlue + copy[i+1][j+1].rgbtBlue;

                green = copy[i-1][j].rgbtGreen + copy[i-1][j+1].rgbtGreen + copy[i][j].rgbtGreen+ copy[i][j+1].rgbtGreen + copy[i+1][j].rgbtGreen + copy[i+1][j+1].rgbtGreen;

                average = red/6.0; // 4 because we have been colecting data of only 4 pixels
                diff = average - (int)average;

                if(diff >= 0.5)
                {
                    average += 0.5;
                }

                image[i][j].rgbtRed = (int)average;

                average = blue / 6.0; // 4 because we have been colecting data of only 4 pixels
                diff = average - (int)average;

                if(diff >= 0.5)
                {
                    average += 0.5;
                }

                image[i][j].rgbtBlue = (int)average;

                average = green / 6.0; // 4 because we have been colecting data of only 4 pixels
                diff = average - (int)average;

                if(diff >= 0.5)
                {
                    average += 0.5;
                }

                image[i][j].rgbtGreen = (int)average;
            } // if pixel is in right edge
            else if((i != 0 && i != height-1) && j == width-1)
            {
                red = copy[i-1][j-1].rgbtRed + copy[i-1][j].rgbtRed + copy[i][j-1].rgbtRed + copy[i][j].rgbtRed + copy[i+1][j-1].rgbtRed + copy[i+1][j].rgbtRed;

                blue = copy[i-1][j-1].rgbtBlue + copy[i-1][j].rgbtBlue + copy[i][j-1].rgbtBlue + copy[i][j].rgbtBlue + copy[i+1][j-1].rgbtBlue + copy[i+1][j].rgbtBlue;

                green = copy[i-1][j-1].rgbtGreen + copy[i-1][j].rgbtGreen + copy[i][j-1].rgbtGreen+ copy[i][j].rgbtGreen + copy[i+1][j-1].rgbtGreen + copy[i+1][j].rgbtGreen;

                average = red / 6.0; // 4 because we have been colecting data of only 4 pixels
                diff = average - (int)average;

                if(diff >= 0.5)
                {
                    average +=0.5;
                }

                image[i][j].rgbtRed = (int)average;

                average = blue / 6.0; // 4 because we have been colecting data of only 4 pixels
                diff = average - (int)average;

                if(diff >= 0.5)
                {
                    average += 0.5;
                }

                image[i][j].rgbtBlue = (int)average;

                average = green / 6.0; // 4 because we have been colecting data of only 4 pixels
                diff = average - (int)average;

                if(diff >= 0.5)
                {
                    average += 0.5;
                }

                image[i][j].rgbtGreen = (int)average;
            } // here thee pixel could only be one that can have full 3*3 grid
            else
            {
                red = copy[i - 1][j - 1].rgbtRed + copy[i-1][j].rgbtRed + copy[i-1][j+1].rgbtRed + copy[i][j-1].rgbtRed + copy[i][j].rgbtRed + copy[i][j+1].rgbtRed + copy[i+1][j-1].rgbtRed + copy[i+1][j].rgbtRed +copy[i+1][j+1].rgbtRed;

                blue = copy[i-1][j-1].rgbtBlue + copy[i-1][j].rgbtBlue + copy[i-1][j+1].rgbtBlue + copy[i][j-1].rgbtBlue + copy[i][j].rgbtBlue + copy[i][j+1].rgbtBlue + copy[i+1][j-1].rgbtBlue + copy[i+1][j].rgbtBlue +copy[i+1][j+1].rgbtBlue;

                green = copy[i-1][j-1].rgbtGreen + copy[i-1][j].rgbtGreen + copy[i-1][j+1].rgbtGreen + copy[i][j-1].rgbtGreen + copy[i][j].rgbtGreen + copy[i][j+1].rgbtGreen + copy[i+1][j-1].rgbtGreen + copy[i+1][j].rgbtGreen +copy[i+1][j+1].rgbtGreen;

                 average = red / 9.0;
                 diff = average - (int)average;

                if(diff >= 0.5)
                {
                    average += 0.5;
                }

                image[i][j].rgbtRed = (int)average;

                average = blue / 9.0; // 4 because we have been colecting data of only 4 pixels
                diff = average - (int)average;

                if(diff >= 0.5)
                {
                    average += 0.5;
                }

                image[i][j].rgbtBlue = (int)average;

                average = green / 9.0; // 4 because we have been colecting data of only 4 pixels
                diff = average - (int)average;

                if(diff >= 0.5)
                {
                    average += 0.5;
                }

                image[i][j].rgbtGreen = (int)average;
            }
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    // copying the image to copy matrix
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j].rgbtRed = image[i][j].rgbtRed;
            copy[i][j].rgbtBlue = image[i][j].rgbtBlue;
            copy[i][j].rgbtGreen = image[i][j].rgbtGreen;
        }
    }
    int red, blue, green, red2, blue2, green2;


    double sum;

    int GX[3][3] ;

    GX[0][0] = -1;
    GX[0][1] = 0;
    GX[0][2] = 1;

    GX[1][0] = -2;
    GX[1][1] = 0;
    GX[1][2] = 2;

    GX[2][0] = -1;
    GX[2][1] = 0;
    GX[2][2] = 1;

    int GY[3][3];

    GY[0][0] = -1;
    GY[0][1] = -2;
    GY[0][2] = -1;

    GY[1][0] = 0;
    GY[1][1] = 0;
    GY[1][2] = 0;

    GY[2][0] = 1;
    GY[2][1] = 2;
    GY[2][2] = 1;
    // here the work starts
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // if pixel is a corner at left-top side
            if (i == 0 && j == 0)
            {
                // GX matrix
                red = (GX[0][0] * 0) + (GX[0][1] * 0) + (GX[0][2] * 0) + (GX[1][0] * 0) + (GX[1][1] * copy[i][j].rgbtRed) + (GX[1][2] * copy[i][j + 1].rgbtRed) + (GX[2][0] * 0) + (GX[2][1] * copy[i + 1][j].rgbtRed) + (GX[2][2] * copy[i + 1][j + 1].rgbtRed);

                blue = (GX[0][0] * 0) + (GX[0][1] * 0) + (GX[0][2] * 0) + (GX[1][0] * 0) + (GX[1][1] * copy[i][j].rgbtBlue) + (GX[1][2] * copy[i][j + 1].rgbtBlue) + (GX[2][0] * 0) + (GX[2][1] * copy[i + 1][j].rgbtBlue) + (GX[2][2] * copy[i + 1][j + 1].rgbtBlue);

                green = (GX[0][0] * 0) + (GX[0][1] * 0) + (GX[0][2] * 0) + (GX[1][0] * 0) + (GX[1][1] * copy[i][j].rgbtGreen) + (GX[1][2] * copy[i][j + 1].rgbtGreen) + (GX[2][0] * 0) + (GX[2][1] * copy[i + 1][j].rgbtGreen) + (GX[2][2] * copy[i + 1][j + 1].rgbtGreen);

                // GY matrix
                red2 = (GY[0][0] * 0) + (GY[0][1] * 0) + (GY[0][2] * 0) + (GY[1][0] * 0) + (GY[1][1] * copy[i][j].rgbtRed) + (GY[1][2] * copy[i][j + 1].rgbtRed) + (GY[2][0] * 0) + (GY[2][1] * copy[i + 1][j].rgbtRed) + (GY[2][2] * copy[i + 1][j + 1].rgbtRed);

                blue2 = (GY[0][0] * 0) + (GY[0][1] * 0) + (GY[0][2] * 0) + (GY[1][0] * 0) + (GY[1][1] * copy[i][j].rgbtBlue) + (GY[1][2] * copy[i][j + 1].rgbtBlue) + (GY[2][0] * 0) + (GY[2][1] * copy[i + 1][j].rgbtBlue) + (GY[2][2] * copy[i + 1][j + 1].rgbtBlue);

                green2 = (GY[0][0] * 0) + (GY[0][1] * 0) + (GY[0][2] * 0) + (GY[1][0] * 0) + (GY[1][1] * copy[i][j].rgbtGreen) + (GY[1][2] * copy[i][j + 1].rgbtGreen) + (GY[2][0] * 0) + (GY[2][1] * copy[i + 1][j].rgbtGreen) + (GY[2][2] * copy[i + 1][j + 1].rgbtGreen);

                // all proccess required for initialising value to original pixels
                // red
                sum = pow(red, 2) + pow(red2, 2);

                sum = sqrt(sum);

                if(round(sum) > 255)
                {
                    image[i][j].rgbtRed =  255;
                }
                else
                {
                    image[i][j].rgbtRed =  round(sum);
                }

                // blue
                sum = pow(blue, 2) + pow(blue2, 2);

                sum = sqrt(sum);

                if(round(sum) > 255)
                {
                    image[i][j].rgbtBlue =  255;
                }
                else
                {
                    image[i][j].rgbtBlue =  round(sum);
                }
                // green
                sum = pow(green, 2) + pow(green2, 2);

                sum = sqrt(sum);

                if(round(sum) > 255)
                {
                    image[i][j].rgbtGreen =  255;
                }
                else
                {
                    image[i][j].rgbtGreen =  round(sum);
                }

            }// id pixel is a corner at top-right
            else if(i == 0 && j == width - 1)
            {
                // GX matrix
                red = (GX[0][0] * 0) + (GX[0][1] * 0) + (GX[0][2] * 0) + (GX[1][0] * copy[i][j - 1].rgbtRed) + (GX[1][1] * copy[i][j].rgbtRed) + (GX[1][2] * 0) + (GX[2][0] * copy[i + 1][j - 1].rgbtRed) + (GX[2][1] * copy[i + 1][j].rgbtRed) + (GX[2][2] * 0);

                blue = (GX[0][0] * 0) + (GX[0][1] * 0) + (GX[0][2] * 0) + (GX[1][0] * copy[i][j - 1].rgbtBlue) + (GX[1][1] * copy[i][j].rgbtBlue) + (GX[1][2] * 0) + (GX[2][0] * copy[i + 1][j - 1].rgbtBlue) + (GX[2][1] * copy[i + 1][j].rgbtBlue) + (GX[2][2] * 0);

                green = (GX[0][0] * 0) + (GX[0][1] * 0) + (GX[0][2] * 0) + (GX[1][0] * copy[i][j - 1].rgbtGreen) + (GX[1][1] * copy[i][j].rgbtGreen) + (GX[1][2] * 0) + (GX[2][0] * copy[i + 1][j - 1].rgbtGreen) + (GX[2][1] * copy[i + 1][j].rgbtGreen) + (GX[2][2] * 0);

                // GY matrix
                red2 = (GY[0][0] * 0) + (GY[0][1] * 0) + (GY[0][2] * 0) + (GY[1][0] * copy[i][j - 1].rgbtRed) + (GY[1][1] * copy[i][j].rgbtRed) + (GY[1][2] * 0) + (GY[2][0] * copy[i + 1][j - 1].rgbtRed) + (GY[2][1] * copy[i + 1][j].rgbtRed) + (GY[2][2] * 0);

                blue2 = (GY[0][0] * 0) + (GY[0][1] * 0) + (GY[0][2] * 0) + (GY[1][0] * copy[i][j - 1].rgbtBlue) + (GY[1][1] * copy[i][j].rgbtBlue) + (GY[1][2] * 0) + (GY[2][0] * copy[i + 1][j - 1].rgbtBlue) + (GY[2][1] * copy[i + 1][j].rgbtBlue) + (GY[2][2] * 0);

                green2 = (GY[0][0] * 0) + (GY[0][1] * 0) + (GY[0][2] * 0) + (GY[1][0] * copy[i][j - 1].rgbtGreen) + (GY[1][1] * copy[i][j].rgbtGreen) + (GY[1][2] * 0) + (GY[2][0] * copy[i + 1][j - 1].rgbtGreen) + (GY[2][1] * copy[i + 1][j].rgbtGreen) + (GY[2][2] * 0);

                // all proccess required for initialising value to original pixels
                // red
                sum = pow(red, 2) + pow(red2, 2);

                sum = sqrt(sum);

                if(round(sum) > 255)
                {
                    image[i][j].rgbtRed =  255;
                }
                else
                {
                    image[i][j].rgbtRed =  round(sum);
                }
                // blue
                sum = pow(blue, 2) + pow(blue2, 2);

                sum = sqrt(sum);

                if(round(sum) > 255)
                {
                    image[i][j].rgbtBlue =  255;
                }
                else
                {
                    image[i][j].rgbtBlue =  round(sum);
                }
                // green
                sum = pow(green, 2) + pow(green2, 2);

                sum = sqrt(sum);

                if(round(sum) > 255)
                {
                    image[i][j].rgbtGreen =  255;
                }
                else
                {
                    image[i][j].rgbtGreen =  round(sum);
                }

            }// if pixel is a corner at bottom-left side
            else if (i == height - 1 && j == 0)
            {
                // GX matrix
                red = (GX[0][0] * 0) + (GX[0][1] * copy[i - 1][j].rgbtRed) + (GX[0][2] * copy[i - 1][j + 1].rgbtRed) + (GX[1][0] * 0) + (GX[1][1] * copy[i][j].rgbtRed) + (GX[1][2] * copy[i][j + 1].rgbtRed) + (GX[2][0] * 0) + (GX[2][1] * 0) + (GX[2][2] * 0);

                blue = (GX[0][0] * 0) + (GX[0][1] * copy[i - 1][j].rgbtBlue) + (GX[0][2] * copy[i - 1][j + 1].rgbtBlue) + (GX[1][0] * 0) + (GX[1][1] * copy[i][j].rgbtBlue) + (GX[1][2] * copy[i][j + 1].rgbtBlue) + (GX[2][0] * 0) + (GX[2][1] * 0) + (GX[2][2] * 0);

                green = (GX[0][0] * 0) + (GX[0][1] * copy[i - 1][j].rgbtGreen) + (GX[0][2] * copy[i - 1][j + 1].rgbtGreen) + (GX[1][0] * 0) + (GX[1][1] * copy[i][j].rgbtGreen) + (GX[1][2] * copy[i][j + 1].rgbtGreen) + (GX[2][0] * 0) + (GX[2][1] * 0) + (GX[2][2] * 0);

                // GY matrix
                red2 = (GY[0][0] * 0) + (GY[0][1] * copy[i - 1][j].rgbtRed) + (GY[0][2] * copy[i - 1][j + 1].rgbtRed) + (GY[1][0] * 0) + (GY[1][1] * copy[i][j].rgbtRed) + (GY[1][2] * copy[i][j + 1].rgbtRed) + (GY[2][0] * 0) + (GY[2][1] * 0) + (GY[2][2] * 0);

                blue2 = (GY[0][0] * 0) + (GY[0][1] * copy[i - 1][j].rgbtBlue) + (GY[0][2] * copy[i - 1][j + 1].rgbtBlue) + (GY[1][0] * 0) + (GY[1][1] * copy[i][j].rgbtBlue) + (GY[1][2] * copy[i][j + 1].rgbtBlue) + (GY[2][0] * 0) + (GY[2][1] * 0) + (GY[2][2] * 0);

                green2 = (GY[0][0] * 0) + (GY[0][1] * copy[i - 1][j].rgbtGreen) + (GY[0][2] * copy[i - 1][j + 1].rgbtGreen) + (GY[1][0] * 0) + (GY[1][1] * copy[i][j].rgbtGreen) + (GY[1][2] * copy[i][j + 1].rgbtGreen) + (GY[2][0] * 0) + (GY[2][1] * 0) + (GY[2][2] * 0);

                // all proccess required for initialising value to original pixels
                // red
                sum = pow(red, 2) + pow(red2, 2);

                sum = sqrt(sum);

                if(round(sum) > 255)
                {
                    image[i][j].rgbtRed =  255;
                }
                else
                {
                    image[i][j].rgbtRed =  round(sum);
                }
                // blue
                sum = pow(blue, 2) + pow(blue2, 2);

                sum = sqrt(sum);

                if(round(sum) > 255)
                {
                    image[i][j].rgbtBlue =  255;
                }
                else
                {
                    image[i][j].rgbtBlue =  round(sum);
                }
                // green
                sum = pow(green, 2) + pow(green2, 2);

                sum = sqrt(sum);

                if(round(sum) > 255)
                {
                    image[i][j].rgbtGreen =  255;
                }
                else
                {
                    image[i][j].rgbtGreen =  round(sum);
                }

        }// if pixel is a corner at bottom-right
            else if(i == height - 1 && j == width - 1)
            {
                // GX matrix
                red = (GX[0][0] * copy[i - 1][j - 1].rgbtRed) + (GX[0][1] * copy[i - 1][j].rgbtRed) + (GX[0][2] * 0) + (GX[1][0] * copy[i][j - 1].rgbtRed) + (GX[1][1] * copy[i][j].rgbtRed) + (GX[1][2] * 0) + (GX[2][0] * 0) + (GX[2][1] * 0) + (GX[2][2] * 0);

                blue = (GX[0][0] * copy[i - 1][j - 1].rgbtBlue) + (GX[0][1] * copy[i - 1][j].rgbtBlue) + (GX[0][2] * 0) + (GX[1][0] * copy[i][j - 1].rgbtBlue) + (GX[1][1] * copy[i][j].rgbtBlue) + (GX[1][2] * 0) + (GX[2][0] * 0) + (GX[2][1] * 0) + (GX[2][2] * 0);

                green = (GX[0][0] * copy[i - 1][j - 1].rgbtGreen) + (GX[0][1] * copy[i - 1][j].rgbtGreen) + (GX[0][2] * 0) + (GX[1][0] * copy[i][j - 1].rgbtGreen) + (GX[1][1] * copy[i][j].rgbtGreen) + (GX[1][2] * 0) + (GX[2][0] * 0) + (GX[2][1] * 0) + (GX[2][2] * 0);

                // GY matrix
                red2 = (GY[0][0] * copy[i - 1][j - 1].rgbtRed) + (GY[0][1] * copy[i - 1][j].rgbtRed) + (GY[0][2] * 0) + (GY[1][0] * copy[i][j - 1].rgbtRed) + (GY[1][1] * copy[i][j].rgbtRed) + (GY[1][2] * 0) + (GY[2][0] * 0) + (GY[2][1] * 0) + (GY[2][2] * 0);

                blue2 = (GY[0][0] * copy[i - 1][j - 1].rgbtBlue) + (GY[0][1] * copy[i - 1][j].rgbtBlue) + (GY[0][2] * 0) + (GY[1][0] * copy[i][j - 1].rgbtBlue) + (GY[1][1] * copy[i][j].rgbtBlue) + (GY[1][2] * 0) + (GY[2][0] * 0) + (GY[2][1] * 0) + (GY[2][2] * 0);

                green2 = (GY[0][0] * copy[i - 1][j - 1].rgbtGreen) + (GY[0][1] * copy[i - 1][j].rgbtGreen) + (GY[0][2] * 0) + (GY[1][0] * copy[i][j - 1].rgbtGreen) + (GY[1][1] * copy[i][j].rgbtGreen) + (GY[1][2] * 0) + (GY[2][0] * 0) + (GY[2][1] * 0) + (GY[2][2] * 0);

                // all proccess required for initialising value to original pixels
                // red
                sum = pow(red, 2) + pow(red2, 2);

                sum = sqrt(sum);

                if(round(sum) > 255)
                {
                    image[i][j].rgbtRed =  255;
                }
                else
                {
                    image[i][j].rgbtRed =  round(sum);
                }
                // blue
                sum = pow(blue, 2) + pow(blue2, 2);

                sum = sqrt(sum);

                if(round(sum) > 255)
                {
                    image[i][j].rgbtBlue =  255;
                }
                else
                {
                    image[i][j].rgbtBlue =  round(sum);
                }
                // green
                sum = pow(green, 2) + pow(green2, 2);

                sum = sqrt(sum);

                if(round(sum) > 255)
                {
                    image[i][j].rgbtGreen =  255;
                }
                else
                {
                    image[i][j].rgbtGreen =  round(sum);
                }

            } // if pixel is a top-edge
            else if(i == 0 && (j != 0 && j != width-1))
            {
                // GX array
                red = (GX[0][0] * 0) + (GX[0][1] * 0) + (GX[0][2] * 0) + (GX[1][0] * copy[i][j - 1].rgbtRed) + (GX[1][1] * copy[i][j].rgbtRed) + (GX[1][2] * copy[i][j + 1].rgbtRed) + (GX[2][0] * copy[i + 1][j - 1].rgbtRed) + (GX[2][1] * copy[i + 1][j].rgbtRed) + (GX[2][2] * copy[i + 1][j + 1].rgbtRed);

                blue = (GX[0][0] * 0) + (GX[0][1] * 0) + (GX[0][2] * 0) + (GX[1][0] * copy[i][j - 1].rgbtBlue) + (GX[1][1] * copy[i][j].rgbtBlue) + (GX[1][2] * copy[i][j + 1].rgbtBlue) + (GX[2][0] * copy[i + 1][j - 1].rgbtBlue) + (GX[2][1] * copy[i + 1][j].rgbtBlue) + (GX[2][2] * copy[i + 1][j + 1].rgbtBlue);

                green = (GX[0][0] * 0) + (GX[0][1] * 0) + (GX[0][2] * 0) + (GX[1][0] * copy[i][j - 1].rgbtGreen) + (GX[1][1] * copy[i][j].rgbtGreen) + (GX[1][2] * copy[i][j + 1].rgbtGreen) + (GX[2][0] * copy[i + 1][j - 1].rgbtGreen) + (GX[2][1] * copy[i + 1][j].rgbtGreen) + (GX[2][2] * copy[i + 1][j + 1].rgbtGreen);

                // GY array
                red2 = (GY[0][0] * 0) + (GY[0][1] * 0) + (GY[0][2] * 0) + (GY[1][0] * copy[i][j - 1].rgbtRed) + (GY[1][1] * copy[i][j].rgbtRed) + (GY[1][2] * copy[i][j + 1].rgbtRed) + (GY[2][0] * copy[i + 1][j - 1].rgbtRed) + (GY[2][1] * copy[i + 1][j].rgbtRed) + (GY[2][2] * copy[i + 1][j + 1].rgbtRed);

                blue2 = (GY[0][0] * 0) + (GY[0][1] * 0) + (GY[0][2] * 0) + (GY[1][0] * copy[i][j - 1].rgbtBlue) + (GY[1][1] * copy[i][j].rgbtBlue) + (GY[1][2] * copy[i][j + 1].rgbtBlue) + (GY[2][0] * copy[i + 1][j - 1].rgbtBlue) + (GY[2][1] * copy[i + 1][j].rgbtBlue) + (GY[2][2] * copy[i + 1][j + 1].rgbtBlue);

                green2 = (GY[0][0] * 0) + (GY[0][1] * 0) + (GY[0][2] * 0) + (GY[1][0] * copy[i][j - 1].rgbtGreen) + (GY[1][1] * copy[i][j].rgbtGreen) + (GY[1][2] * copy[i][j + 1].rgbtGreen) + (GY[2][0] * copy[i + 1][j - 1].rgbtGreen) + (GY[2][1] * copy[i + 1][j].rgbtGreen) + (GY[2][2] * copy[i + 1][j + 1].rgbtGreen);

                // all proccess required for initialising value to original pixels
                // red
                sum = pow(red, 2) + pow(red2, 2);

                sum = sqrt(sum);

                if(round(sum) > 255)
                {
                    image[i][j].rgbtRed =  255;
                }
                else
                {
                    image[i][j].rgbtRed =  round(sum);
                }
                // blue
                sum = pow(blue, 2) + pow(blue2, 2);

                sum = sqrt(sum);

                if(round(sum) > 255)
                {
                    image[i][j].rgbtBlue =  255;
                }
                else
                {
                    image[i][j].rgbtBlue =  round(sum);
                }
                // green
                sum = pow(green, 2) + pow(green2, 2);

                sum = sqrt(sum);

                if(round(sum) > 255)
                {
                    image[i][j].rgbtGreen =  255;
                }
                else
                {
                    image[i][j].rgbtGreen =  round(sum);
                }

            }// pixel is an edge at bottom
            else if(i == height - 1 && (j != width - 1 && j != 0))
            {
                // GX array
                red = (GX[0][0] * copy[i - 1][j - 1].rgbtRed) + (GX[0][1] * copy[i - 1][j].rgbtRed) + (GX[0][2] * copy[i - 1][j + 1].rgbtRed) + (GX[1][0] * copy[i][j - 1].rgbtRed) + (GX[1][1] * copy[i][j].rgbtRed) + (GX[1][2] * copy[i][j + 1].rgbtRed) + (GX[2][0] * 0) + (GX[2][1] * 0) + (GX[2][2] * 0);

                blue = (GX[0][0] * copy[i - 1][j - 1].rgbtBlue) + (GX[0][1] * copy[i - 1][j].rgbtBlue) + (GX[0][2] * copy[i - 1][j + 1].rgbtBlue) + (GX[1][0] * copy[i][j - 1].rgbtBlue) + (GX[1][1] * copy[i][j].rgbtBlue) + (GX[1][2] * copy[i][j + 1].rgbtBlue) + (GX[2][0] * 0) + (GX[2][1] * 0) + (GX[2][2] * 0);

                green = (GX[0][0] * copy[i - 1][j - 1].rgbtGreen) + (GX[0][1] * copy[i - 1][j].rgbtGreen) + (GX[0][2] * copy[i - 1][j + 1].rgbtGreen) + (GX[1][0] * copy[i][j - 1].rgbtGreen) + (GX[1][1] * copy[i][j].rgbtGreen) + (GX[1][2] * copy[i][j + 1].rgbtGreen) + (GX[2][0] * 0) + (GX[2][1] * 0) + (GX[2][2] * 0);

                // GY array
                red2 = (GY[0][0] * copy[i - 1][j - 1].rgbtRed) + (GY[0][1] * copy[i - 1][j].rgbtRed) + (GY[0][2] * copy[i - 1][j + 1].rgbtRed) + (GY[1][0] * copy[i][j - 1].rgbtRed) + (GY[1][1] * copy[i][j].rgbtRed) + (GY[1][2] * copy[i][j + 1].rgbtRed) + (GY[2][0] * 0) + (GY[2][1] * 0) + (GY[2][2] * 0);

                blue2 = (GY[0][0] * copy[i - 1][j - 1].rgbtBlue) + (GY[0][1] * copy[i - 1][j].rgbtBlue) + (GY[0][2] * copy[i - 1][j + 1].rgbtBlue) + (GY[1][0] * copy[i][j - 1].rgbtBlue) + (GY[1][1] * copy[i][j].rgbtBlue) + (GY[1][2] * copy[i][j + 1].rgbtBlue) + (GY[2][0] * 0) + (GY[2][1] * 0) + (GY[2][2] * 0);

               green2 = (GY[0][0] * copy[i - 1][j - 1].rgbtGreen) + (GY[0][1] * copy[i - 1][j].rgbtGreen) + (GY[0][2] * copy[i - 1][j + 1].rgbtGreen) + (GY[1][0] * copy[i][j - 1].rgbtGreen) + (GY[1][1] * copy[i][j].rgbtGreen) + (GY[1][2] * copy[i][j + 1].rgbtGreen) + (GY[2][0] * 0) + (GY[2][1] * 0) + (GY[2][2] * 0);

                // all proccess required for initialising value to original pixels
                // red
                sum = pow(red, 2) + pow(red2, 2);

                sum = sqrt(sum);

                if(round(sum) > 255)
                {
                    image[i][j].rgbtRed =  255;
                }
                else
                {
                    image[i][j].rgbtRed =  round(sum);
                }
                // blue
                sum = pow(blue, 2) + pow(blue2, 2);

                sum = sqrt(sum);

                if(round(sum) > 255)
                {
                    image[i][j].rgbtBlue =  255;
                }
                else
                {
                    image[i][j].rgbtBlue =  round(sum);
                }
                // green
                sum = pow(green, 2) + pow(green2, 2);

                sum = sqrt(sum);

                if(round(sum) > 255)
                {
                    image[i][j].rgbtGreen =  255;
                }
                else
                {
                    image[i][j].rgbtGreen =  round(sum);
                }

            }// if pixel is a edge at left
            else if ((i != 0 && i != height - 1) && j == 0)
            {
                //GX matrix
             red = (GX[0][0] * 0) + (GX[0][1] * copy[i - 1][j].rgbtRed) + (GX[0][2] * copy[i - 1][j + 1 ].rgbtRed) + (GX[1][0] * 0) + (GX[1][1] * copy[i][j].rgbtRed) + (GX[1][2] * copy[i][j + 1 ].rgbtRed) + (GX[2][0] * 0) + (GX[2][1] * copy[i + 1][j].rgbtRed) + (GX[2][2] * copy[i + 1][j + 1 ].rgbtRed);

             blue = (GX[0][0] * 0) + (GX[0][1] * copy[i - 1][j].rgbtBlue) + (GX[0][2] * copy[i - 1][j + 1 ].rgbtBlue) + (GX[1][0] * 0) + (GX[1][1] * copy[i][j].rgbtBlue) + (GX[1][2] * copy[i][j + 1 ].rgbtBlue) + (GX[2][0] * 0) + (GX[2][1] * copy[i + 1][j].rgbtBlue) + (GX[2][2] * copy[i + 1][j + 1 ].rgbtBlue);

             green = (GX[0][0] * 0) + (GX[0][1] * copy[i - 1][j].rgbtGreen) + (GX[0][2] * copy[i - 1][j + 1 ].rgbtGreen) + (GX[1][0] * 0) + (GX[1][1] * copy[i][j].rgbtGreen) + (GX[1][2] * copy[i][j + 1 ].rgbtGreen) + (GX[2][0] * 0) + (GX[2][1] * copy[i + 1][j].rgbtGreen) + (GX[2][2] * copy[i + 1][j + 1 ].rgbtGreen);

             // GY matrix
             red2 = (GY[0][0] * 0) + (GY[0][1] * copy[i - 1][j].rgbtRed) + (GY[0][2] * copy[i - 1][j + 1 ].rgbtRed) + (GY[1][0] * 0) + (GY[1][1] * copy[i][j].rgbtRed) + (GY[1][2] * copy[i][j + 1 ].rgbtRed) + (GY[2][0] * 0) + (GY[2][1] * copy[i + 1][j].rgbtRed) + (GY[2][2] * copy[i + 1][j + 1 ].rgbtRed);

             blue2 = (GY[0][0] * 0) + (GY[0][1] * copy[i - 1][j].rgbtBlue) + (GY[0][2] * copy[i - 1][j + 1 ].rgbtBlue) + (GY[1][0] * 0) + (GY[1][1] * copy[i][j].rgbtBlue) + (GY[1][2] * copy[i][j + 1 ].rgbtBlue) + (GY[2][0] * 0) + (GY[2][1] * copy[i + 1][j].rgbtBlue) + (GY[2][2] * copy[i + 1][j + 1 ].rgbtBlue);

             green2 = (GY[0][0] * 0) + (GY[0][1] * copy[i - 1][j].rgbtGreen) + (GY[0][2] * copy[i - 1][j + 1 ].rgbtGreen) + (GY[1][0] * 0) + (GY[1][1] * copy[i][j].rgbtGreen) + (GY[1][2] * copy[i][j + 1 ].rgbtGreen) + (GY[2][0] * 0) + (GY[2][1] * copy[i + 1][j].rgbtGreen) + (GY[2][2] * copy[i + 1][j + 1 ].rgbtGreen);

                // all proccess required for initialising value to original pixels
                // red
                sum = pow(red, 2) + pow(red2, 2);

                sum = sqrt(sum);

                if(round(sum) > 255)
                {
                    image[i][j].rgbtRed =  255;
                }
                else
                {
                    image[i][j].rgbtRed =  round(sum);
                }
                // blue
                sum = pow(blue, 2) + pow(blue2, 2);

                sum = sqrt(sum);

                if(round(sum) > 255)
                {
                    image[i][j].rgbtBlue =  255;
                }
                else
                {
                    image[i][j].rgbtBlue =  round(sum);
                }
                // green
                sum = pow(green, 2) + pow(green2, 2);

                sum = sqrt(sum);

                if(round(sum) > 255)
                {
                    image[i][j].rgbtGreen =  255;
                }
                else
                {
                    image[i][j].rgbtGreen =  round(sum);
                }
            }// if pixel is a edge at right
            else if ((i != 0 && i != height - 1) && j == width - 1)
            {
                //GX matrix
             red = (GX[0][0] * copy[i - 1][j - 1].rgbtRed) + (GX[0][1] * copy[i - 1][j].rgbtRed) + (GX[0][2] * 0) + (GX[1][0] * copy[i][j - 1].rgbtRed) + (GX[1][1] * copy[i][j].rgbtRed) + (GX[1][2] * 0) + (GX[2][0] * copy[i + 1][j - 1].rgbtRed) + (GX[2][1] * copy[i + 1][j].rgbtRed) + (GX[2][2] * 0);

             blue = (GX[0][0] * copy[i - 1][j - 1].rgbtBlue) + (GX[0][1] * copy[i - 1][j].rgbtBlue) + (GX[0][2] * 0) + (GX[1][0] * copy[i][j - 1].rgbtBlue) + (GX[1][1] * copy[i][j].rgbtBlue) + (GX[1][2] * 0) + (GX[2][0] * copy[i + 1][j - 1].rgbtBlue) + (GX[2][1] * copy[i + 1][j].rgbtBlue) + (GX[2][2] * 0);

              green = (GX[0][0] * copy[i - 1][j - 1].rgbtGreen) + (GX[0][1] * copy[i - 1][j].rgbtGreen) + (GX[0][2] * 0) + (GX[1][0] * copy[i][j - 1].rgbtGreen) + (GX[1][1] * copy[i][j].rgbtGreen) + (GX[1][2] * 0) + (GX[2][0] * copy[i + 1][j - 1].rgbtGreen) + (GX[2][1] * copy[i + 1][j].rgbtGreen) + (GX[2][2] * 0);

             // GY matrix
             red2 = (GY[0][0] * copy[i - 1][j - 1].rgbtRed) + (GY[0][1] * copy[i - 1][j].rgbtRed) + (GY[0][2] * 0) + (GY[1][0] * copy[i][j - 1].rgbtRed) + (GY[1][1] * copy[i][j].rgbtRed) + (GY[1][2] * 0) + (GY[2][0] * copy[i + 1][j - 1].rgbtRed) + (GY[2][1] * copy[i + 1][j].rgbtRed) + (GY[2][2] * 0);

             blue2 = (GY[0][0] * copy[i - 1][j - 1].rgbtBlue) + (GY[0][1] * copy[i - 1][j].rgbtBlue) + (GY[0][2] * 0) + (GY[1][0] * copy[i][j - 1].rgbtBlue) + (GY[1][1] * copy[i][j].rgbtBlue) + (GY[1][2] * 0) + (GY[2][0] * copy[i + 1][j - 1].rgbtBlue) + (GY[2][1] * copy[i + 1][j].rgbtBlue) + (GY[2][2] * 0);

              green2 = (GY[0][0] * copy[i - 1][j - 1].rgbtGreen) + (GY[0][1] * copy[i - 1][j].rgbtGreen) + (GY[0][2] * 0) + (GY[1][0] * copy[i][j - 1].rgbtGreen) + (GY[1][1] * copy[i][j].rgbtGreen) + (GY[1][2] * 0) + (GY[2][0] * copy[i + 1][j - 1].rgbtGreen) + (GY[2][1] * copy[i + 1][j].rgbtGreen) + (GY[2][2] * 0);

                // all proccess required for initialising value to original pixels
                // red
                sum = pow(red, 2) + pow(red2, 2);

                sum = sqrt(sum);

                if(round(sum) > 255)
                {
                    image[i][j].rgbtRed =  255;
                }
                else
                {
                    image[i][j].rgbtRed =  round(sum);
                }
                // blue
                sum = pow(blue, 2) + pow(blue2, 2);

                sum = sqrt(sum);

                if(round(sum) > 255)
                {
                    image[i][j].rgbtBlue =  255;
                }
                else
                {
                    image[i][j].rgbtBlue =  round(sum);
                }
                // green
                sum = pow(green, 2) + pow(green2, 2);

                sum = sqrt(sum);

                if(round(sum) > 255)
                {
                    image[i][j].rgbtGreen =  255;
                }
                else
                {
                    image[i][j].rgbtGreen =  round(sum);
                }
            }// if pixel is in middle portion
            else
            {
                // GX matrix
                red = (GX[0][0] * copy[i - 1][j - 1].rgbtRed) + (GX[0][1] * copy[i - 1][j].rgbtRed) + (GX[0][2] * copy[i - 1][j + 1].rgbtRed) + (GX[1][0] * copy[i][j - 1].rgbtRed) + (GX[1][1] * copy[i][j].rgbtRed) + (GX[1][2] * copy[i][j + 1].rgbtRed) + (GX[2][0] * copy[i + 1][j - 1].rgbtRed) + (GX[2][1] * copy[i + 1][j].rgbtRed) + (GX[2][2] * copy[i + 1][j + 1].rgbtRed);

                blue = (GX[0][0] * copy[i - 1][j - 1].rgbtBlue) + (GX[0][1] * copy[i - 1][j].rgbtBlue) + (GX[0][2] * copy[i - 1][j + 1].rgbtBlue) + (GX[1][0] * copy[i][j - 1].rgbtBlue) + (GX[1][1] * copy[i][j].rgbtBlue) + (GX[1][2] * copy[i][j + 1].rgbtBlue) + (GX[2][0] * copy[i + 1][j - 1].rgbtBlue) + (GX[2][1] * copy[i + 1][j].rgbtBlue) + (GX[2][2] * copy[i + 1][j + 1].rgbtBlue);

                green = (GX[0][0] * copy[i - 1][j - 1].rgbtGreen) + (GX[0][1] * copy[i - 1][j].rgbtGreen) + (GX[0][2] * copy[i - 1][j + 1].rgbtGreen) + (GX[1][0] * copy[i][j - 1].rgbtGreen) + (GX[1][1] * copy[i][j].rgbtGreen) + (GX[1][2] * copy[i][j + 1].rgbtGreen) + (GX[2][0] * copy[i + 1][j - 1].rgbtGreen) + (GX[2][1] * copy[i + 1][j].rgbtGreen) + (GX[2][2] * copy[i + 1][j + 1].rgbtGreen);

                // GY matrix
                red2 = (GY[0][0] * copy[i - 1][j - 1].rgbtRed) + (GY[0][1] * copy[i - 1][j].rgbtRed) + (GY[0][2] * copy[i - 1][j + 1].rgbtRed) + (GY[1][0] * copy[i][j - 1].rgbtRed) + (GY[1][1] * copy[i][j].rgbtRed) + (GY[1][2] * copy[i][j + 1].rgbtRed) + (GY[2][0] * copy[i + 1][j - 1].rgbtRed) + (GY[2][1] * copy[i + 1][j].rgbtRed) + (GY[2][2] * copy[i + 1][j + 1].rgbtRed);

                blue2 = (GY[0][0] * copy[i - 1][j - 1].rgbtBlue) + (GY[0][1] * copy[i - 1][j].rgbtBlue) + (GY[0][2] * copy[i - 1][j + 1].rgbtBlue) + (GY[1][0] * copy[i][j - 1].rgbtBlue) + (GY[1][1] * copy[i][j].rgbtBlue) + (GY[1][2] * copy[i][j + 1].rgbtBlue) + (GY[2][0] * copy[i + 1][j - 1].rgbtBlue) + (GY[2][1] * copy[i + 1][j].rgbtBlue) + (GY[2][2] * copy[i + 1][j + 1].rgbtBlue);

                green2 = (GY[0][0] * copy[i - 1][j - 1].rgbtGreen) + (GY[0][1] * copy[i - 1][j].rgbtGreen) + (GY[0][2] * copy[i - 1][j + 1].rgbtGreen) + (GY[1][0] * copy[i][j - 1].rgbtGreen) + (GY[1][1] * copy[i][j].rgbtGreen) + (GY[1][2] * copy[i][j + 1].rgbtGreen) + (GY[2][0] * copy[i + 1][j - 1].rgbtGreen) + (GY[2][1] * copy[i + 1][j].rgbtGreen) + (GY[2][2] * copy[i + 1][j + 1].rgbtGreen);

                // all proccess required for initialising value to original pixels
                // red
                sum = pow(red, 2) + pow(red2, 2);

                sum = sqrt(sum);

                if(round(sum) > 255)
                {
                    image[i][j].rgbtRed =  255;
                }
                else
                {
                    image[i][j].rgbtRed =  round(sum);
                }
                // blue
                sum = pow(blue, 2) + pow(blue2, 2);

                sum = sqrt(sum);

                if(round(sum) > 255)
                {
                    image[i][j].rgbtBlue =  255;
                }
                else
                {
                    image[i][j].rgbtBlue =  round(sum);
                }
                // green
                sum = pow(green, 2) + pow(green2, 2);

                sum = sqrt(sum);

                if(round(sum) > 255)
                {
                    image[i][j].rgbtGreen =  255;
                }
                else
                {
                    image[i][j].rgbtGreen =  round(sum);
                }
            }
        }
    }
    return;
}
