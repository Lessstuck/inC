#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // open file for reading
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

    // get 512-byte buffers
    BYTE gotc;
    BYTE buffer[512];
    long j = 0;
    long k = 0;
    int jpegCounter = 0;
    char filename[8];
    for (long i = 0; i < 7314; i++)  // magic number of blocks in test file
    {
        for (j = 0; j < 512; j++)
        {
            gotc = fgetc(rawPtr);
            {
                buffer[j] = gotc;
            }
        }
        // open first file for writing
        sprintf("filename", "%03i.jpg", jpegCounter);
        FILE *writePtr = fopen(filename, "w");
        if (rawPtr == NULL)
        {
            return 1;
        }

        // look for jpeg header
        if ((buffer[0] == 0xff) && (buffer[1] == 0xd8) && (buffer[2] == 0xff) && ((buffer[3] & 0xf0) == 0xe0))
        {
            jpegCounter++;
            printf("jpegCounter: %i, block: %li\n", jpegCounter, i);
            for (k = 0; k < 512; k++)
            {
                fputc(buffer[k], writePtr);
            }
        }
            fclose(writePtr);
    }

    fclose(rawPtr);
    return 0;
}
