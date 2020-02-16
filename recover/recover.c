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
    int bufferSize = 0;
    int i = 0;
    long j = 0;
    int k = 0;
    int jpegCounter = 0;
    char writeFile[50];
    FILE *writePtr = NULL;

    do
    {
        bufferSize = fread(buffer, 1, 512, rawPtr);

        // {
        //     fclose(rawPtr);
        //     fclose(writePtr);
        //     return 0;
        // }
        // look for jpeg header
        if ((buffer[0] == 0xff) && (buffer[1] == 0xd8) && (buffer[2] == 0xff) && ((buffer[3] & 0xf0) == 0xe0))
        {
            // close previous file unless this is the first one
            // if (jpegCounter != 0)
            // {
            //     // fclose(writePtr);
            // }

            // name and write new file
            sprintf(writeFile, "%03i.jpg", jpegCounter);
            writePtr = fopen(writeFile, "w");
            if (writePtr == NULL)
            {
                return 1;
            }
            jpegCounter++;
            printf("jpegCounter: %i\n", jpegCounter);
        // segmentation fault happens HERE               <----------------------
        fwrite(buffer, 1, 512, writePtr);
        fclose(writePtr);

        }

    }
    while (bufferSize == 512);
    fclose(rawPtr);
    return 0;
}
