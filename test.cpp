
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <cmath>


using namespace std;

struct Token {
    int offset;
    int length;
    char nextChar;
};

string lz77_compress(const string& input, int windowSize, int bufferSize) {
    string output;
    int inputSize = input.size();
    int currentIndex = 0;
    while (currentIndex < inputSize) {
        int windowStart = max(0, currentIndex - windowSize);
        int windowEnd = min(currentIndex, inputSize - bufferSize);
        Token bestToken;
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
        output += to_string(bestToken.offset) + "," + to_string(bestToken.length) + "," + bestToken.nextChar;
        currentIndex += bestToken.length + 1;
    }
    return output;
}

int main(){

    string compressed = lz77_compress("ABBBAARTSAFS", 4,4);
    cout << "Compressed: " << compressed << endl;
}
