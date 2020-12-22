#include <stdio.h>
#include <stdlib.h>

void write_data(int size, unsigned char buffer[], int num);

int main(int argc, char *argv[])
{
    // checking if file has been provided
    if (argc != 2)
    {
        printf("2 arguments are required\n");
        return 1;
    }
    // oprning file
    FILE *fp = fopen(argv[1], "r");
    
    char name[10];
    
    unsigned char buffer[515];
    
    int file_count = 0, num = 0, count = 0;
    // first declaring 
    FILE *ptr = NULL;
    
    while (fread(buffer, 512, 1, fp) == 1)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xe0) == 0xe0)
        {
            if (file_count == 1)
            {   
                fclose(ptr);
                sprintf(name, "%03i.jpg", count);
                count++;
                // then initialise
                ptr = fopen(name, "w");
            }
            else
            {
                file_count = 1;
                sprintf(name, "%03i.jpg", count);
                count++;
                ptr = fopen(name, "w");
            }   
        }
        // print only if it is a JPEG
        if (file_count == 1)
        {
            fwrite(buffer, 512, 1, ptr);   
        }
    }
    // closing all the opening files
    fclose(fp);
    fclose(ptr);
    return 0;
}

