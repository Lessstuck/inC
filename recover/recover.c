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
    int i = 0;
    long j = 0;
    int k = 0;
    int jpegCounter = 0;
    char writeFile[7];
    FILE *writePtr = NULL;

    for (i = 0; i < 7314; i++)  // magic number of blocks in test file
    {
         if (fread(buffer, 1, 512, rawPtr) < 512)
         {
            fclose(rawPtr);
            fclose(writePtr);
            return 0;
         }
        // look for jpeg header
        if ((buffer[0] == 0xff) && (buffer[1] == 0xd8) && (buffer[2] == 0xff) && ((buffer[3] & 0xf0) == 0xe0))
        {
            if (jpegCounter == 0)
            {
                sprintf(writeFile, "%03i.jpg", jpegCounter);
                writePtr = fopen(writeFile, "w");
                if (writePtr == NULL)
                {
                    return 1;
                }
                fwrite(buffer, 1, 512, writePtr);
                jpegCounter++;
            }
            else
            {
                fclose(writePtr); // close previous file, open new one
                sprintf(writeFile, "%03i.jpg", jpegCounter);
                writePtr = fopen(writeFile, "w");
                if (writePtr == NULL)
                {
                    return 1;
                }
                fwrite(buffer, 1, 512, writePtr);
                jpegCounter++;
            }
            printf("jpegCounter: %i, block: %i\n", jpegCounter, i);
        }
        else
        {
            fwrite(buffer, 1, 512, writePtr);
        }
    }
    fclose(rawPtr);
    return 0;
}
