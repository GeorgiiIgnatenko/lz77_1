#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

struct Token {
    int offset;
    int length;
    char nextChar;
};

char *lz77_compress(const char *input, int inputSize, int windowSize, int bufferSize) {
    char *output = (char *) malloc(10 * inputSize * sizeof(char));
    int currentIndex = 0, outputIndex = 0;
    while (currentIndex < inputSize) {
        int windowStart = (currentIndex - windowSize > 0) ? currentIndex - windowSize : 0;
        int windowEnd = (currentIndex > bufferSize) ? currentIndex - bufferSize : 0;
        struct Token bestToken;
        bestToken.offset = 0;
        bestToken.length = 0;
        bestToken.nextChar = input[currentIndex];
        for (int i = windowStart; i < currentIndex; i++) {
            int j = 0;
            while (currentIndex + j < inputSize && j < bufferSize && input[i + j] == input[currentIndex + j]) {
                j++;
            }
            if (j > bestToken.length) {
                bestToken.offset = currentIndex - i;
                bestToken.length = j;
                bestToken.nextChar = input[currentIndex + j];
            }
        }
        outputIndex += sprintf(&output[outputIndex], "%d,%d,%c", bestToken.offset, bestToken.length,
                               bestToken.nextChar);
        currentIndex += bestToken.length + 1;
    }
    return output;
}

char* lz77_decompress(const char* input) {
    int inputSize = strlen(input);
    char* output = malloc(inputSize + 1); // allocate enough space for output
    int currentIndex = 1;
    int outputIndex = 0;
    while (currentIndex < inputSize) {
        int comma1 = strchr(input + currentIndex, ',') - input;
        int comma2 = strchr(input + comma1 + 1, ',') - input;
        int offset = atoi(input + currentIndex);
        int length = atoi(input + comma1 + 1);
        char nextChar = *(input + comma2 + 1);
        for (int i = 0; i < length; i++) {
            output[outputIndex] = output[outputIndex - offset];
            outputIndex++;
        }
        output[outputIndex] = nextChar;
        outputIndex++;
        currentIndex = comma2 + 2;
    }
    output[outputIndex] = '\0';
    return output;
}

int main(int argc, char *argv[]) {

    int mode = 0;
    FILE *inpPtr;
    FILE *outPtr;

    if (argc == 5) {
        if (strcmp(argv[1], "-c") == 0){
            mode = 1;
        }else if (strcmp(argv[1], "-d") == 0){
            mode = 2;
        }else{
            printf("Error");
        }

        if (strcmp(argv[2], "-o") == 0){
            if ((outPtr = fopen(argv[3], "w+")) == NULL) {
                printf("error opening outfile\n");

                exit(1);
            }else{

                printf("file created\n");
            }

            if ((inpPtr = fopen(argv[4], "r")) == NULL) {
                printf("Error! Opening file\n");

                exit(1);
            }else {
                printf("Open succesful\n");
            }
        }
    }else{
        printf("arguments error\n");
        exit(1);
    }

    if (mode == 1){
        char *buffer = 0;
        long length;
        if (inpPtr) {
            fseek(inpPtr, 0, SEEK_END);
            length = ftell(inpPtr);
            fseek(inpPtr, 0, SEEK_SET);
            buffer = malloc(length);
            if (buffer)
            {
                fread(buffer, 1, length, inpPtr);
            }
            fclose(inpPtr);
        }

        if (buffer){

            int bufferSize = strlen(buffer);
            char *compressed = lz77_compress(buffer, bufferSize, 4, 4);
            printf("Input string: %s\n", buffer);
            printf("Compressed: %s\n", compressed);
            fprintf(outPtr, "%s", compressed);
            free(compressed);
            fclose(outPtr);
        }
    }else if (mode == 2){
        char *buffer = 0;
        long length;
        if (inpPtr) {
            fseek(inpPtr, 0, SEEK_END);
            length = ftell(inpPtr);
            fseek(inpPtr, 0, SEEK_SET);
            buffer = malloc(length);
            if (buffer)
            {
                fread(buffer, 1, length, inpPtr);
            }
            fclose(inpPtr);
        }

        if (buffer){
            char *decompressed = lz77_decompress(buffer);
            printf("Input string: %s\n", buffer);
            printf("Compressed: %s\n", decompressed);
            fprintf(outPtr, "%s", decompressed);
            free(decompressed);
            fclose(outPtr);

        }
    }
    return 0;
}
