#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    typedef uint8_t BYTE;
    BYTE buffer[512];
    int byte_read = 0;
    int compteur = 0;


    char filename[8];

    FILE *f = fopen(argv[1], "r");
    FILE *image = NULL;
    if (argc != 2)
    {
        printf("There is more/less than one command line argument\n");
        return 1;
    }
    if(f == NULL)
    {
        printf("Empty\n");
        return 1;
    }

    while (1)
    {
        // read 512 bytes from the buffer
        byte_read = fread(buffer, sizeof(BYTE), 512, f);
        if (byte_read == 0)
        {
            break;
        }

        // condition for new image jpg file
        if(buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && ((buffer[3] & 0xf0)== 0xe0))
        {
            // premiere image
            if(compteur == 0)
            {
                sprintf(filename, "%03i.jpg", compteur);
                image = fopen(filename, "w");
                fwrite(buffer, sizeof(BYTE), byte_read, image);
                compteur++;
            }
            else // close file and open a new one
            {
                fclose(image);
                sprintf(filename, "%03i.jpg", compteur);
                image = fopen(filename, "w");
                fwrite(buffer, sizeof(BYTE), byte_read, image);
                compteur++;
            }
        }
        else if (compteur != 0)
        {
            fwrite(buffer, sizeof(BYTE), byte_read, image);
            if(byte_read == 0)
            {
                fclose(image);
                fclose(f);
            }
        }
    }
    fclose(image);
    fclose(f);
    return 0;
}