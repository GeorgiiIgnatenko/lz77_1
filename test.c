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
    char *output = (char *) malloc(10 * inputSize * sizeof(char)); // Output size can be up to 10 times of input size
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

int main() {

    const char *input = "ABBBAARTSAFS";
    int inputSize = strlen(input);
    char *compressed = lz77_compress(input, inputSize, 4, 4);
    printf("Compressed: %s\n", compressed);
    free(compressed);

    return 0;
}
