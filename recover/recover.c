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

    FILE *rawPtr = fopen(argv[1], "r");
    if (rawPtr == NULL)
    {
        return 1;
    }

    BYTE gotc;
    BYTE buffer[512];
    int bufferSize = 0;
    int i = 0;
    long j = 0;
    int k = 0;
    int jpegCounter = 0;
    int isNew = 0;
    char writeFile[50];
    FILE *writePtr = NULL;

    while ((bufferSize = fread(buffer, 1, 512, rawPtr)) != 0)
    {
        // bufferSize = fread(buffer, 1, 512, rawPtr);
        // look for jpeg header
        if ((buffer[0] == 0xff) && (buffer[1] == 0xd8) && (buffer[2] == 0xff) && ((buffer[3] & 0xf0) == 0xe0))
        {
            isNew = 1;
            // close previous file unless this is the first one
            if (jpegCounter != 0)
            {
                fclose(writePtr);
            }

            // name and write new file
            sprintf(writeFile, "%03i.jpg", jpegCounter);
            writePtr = fopen(writeFile, "a");
            if (writePtr == NULL)
            {
                return 1;
            }
            jpegCounter++;
            fwrite(buffer, 1, 512, writePtr);
        }
        else if (isNew == 0)
        {
            continue; //necessary to deal with first non-image bytes
        }
        else if (isNew == 1)
        {
            fwrite(buffer, 1, 512, writePtr); // appending
        }

    }

    // clean it up and go home!
    fclose(writePtr);
    fclose(rawPtr);
    return 0;
}
