#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // open files for reading and writing
    if (argc != 2)
    {
        printf("Please include one and only one argument–the raw file to be recovered\n");
        return 1;
    }

    FILE *rawPtr = fopen( argv[1], "r");
    if (rawPtr == NULL)
    {
        return 1;
    }
    FILE *writePtr = fopen("out.raw", "w");
    if (rawPtr == NULL)
    {
        return 1;
    }
    // get 512-byte buffers
    char gotc;
    BYTE buffer[512];
    int j = 0;
    int k = 0;
    int jpegCounter = 0;
    for (long i = 0; i < 3744768; i = i + 512) //size from Finder
    {
        for (j = 0; j < 512; j++)
        {
            while((gotc = fgetc(rawPtr)) != EOF)
            {
                buffer[j] = gotc;
            }
        }

        // look for jpeg header
        // if (buffer[0] == 0xff)
        // && buffer[1] == 0xd8 && buffer[2] == 0xff)
        // &&
        if ((buffer[3] & 0xf0) == 0xe0)
        {
            jpegCounter++;
        }
    }
    // fputc(buffer[], writePtr);
    fclose(rawPtr);
    fclose(writePtr);
    printf("jpegCounter is %i\n", jpegCounter);
    return 0;
}
