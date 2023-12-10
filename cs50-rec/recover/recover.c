#include <stdio.h>
#include <stdlib.h>
 
#define BLOCK_SIZE 512

int recover(char* file) {
    
    FILE *inFile = fopen(file, "rb");
    
    printf("%s\n", file);

    unsigned char buffer[BLOCK_SIZE];

    //fread(buffer, 1, BLOCK_SIZE, inFile)
    
    int countBlocks = 0;

    // 247 blocks
    
    

    int foundImages = 0;

    //int onlyone = 1;
    FILE *outFile = NULL;

    while (fread(buffer, 1, BLOCK_SIZE, inFile) == BLOCK_SIZE) {
        // as you  read check for a new beginning for a image. as you read put into buffer and write to output file
        printf("%c - block %d\n", *buffer, countBlocks);
        countBlocks += 1;

        size_t x = 0;

        for (x; BLOCK_SIZE > x; x++) {

            char filename[20];

            if (buffer[x] == 0xff && buffer[x+1] == 0xd8 && buffer[x+2] == 0xff) {
                printf("FOUND ONE\n");
                foundImages += 1;

                // open a output file

                //foundJPG = 1;

                sprintf(filename, "file_%d.jpg", foundImages);
                outFile = fopen(filename, "w");
            }

        }

        if (outFile != NULL) {
            
            fwrite(buffer, 1, BLOCK_SIZE, outFile);
            printf("got exec\n");
        }


    }

    printf("blocks: %d\n", countBlocks);

    printf("images: %d\n", foundImages);

    //printf("outBuffer: %s\n", outBuffer);
    //free(outBuffer);

    //onlyone = 0;

}

int main(int argc, char *argv[])
{
    if (argc != 2) {
        printf("usage: ./recover IMAGE\n");
    }
    else {
        recover(argv[1]);
    }
}