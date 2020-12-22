#include<stdio.h>
#include<stdlib.h>

int main()
{
    FILE* input = fopen("card.raw", "r");
    if (input == NULL)
    {
        printf("Could not open card.raw.\n");
        return 2;
    }
    
    // create buffer
    unsigned char buffer[512];
    
    // filename counter
    int filecount = 0;
    
    FILE* picture = NULL; 
    
    // check if we've found a jpeg yet or not
    int jpg_found = 0; //false
    
    // go through cardfile until there aren't any blocks left
    int num = fread(buffer, 512, 1, input);
    printf("%d",num);
}