#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LOOK_AHEAD 16
#define WINDOW_SIZE 4096

typedef struct {
	int offset;
	int length;
	char nextChar;
} Match;

Match findLongestMatch(char *searchBuffer, char *lookAhead)
{
	int bestMatch = 0;
	int currentMatch = 0;
	Match ans;
	ans.offset = 0;
	ans.length = 0;
	ans.nextChar = '\0';
	for (int i = 0; i < strlen(searchBuffer); i++) {
		if(searchBuffer[i] == lookAhead[i]){
			currentMatch++;
		}
		if(currentMatch > bestMatch){
			bestMatch = currentMatch;
		}
	}

	return ans;
}

int encodeLZ77(char *inputString) {
	int position = 0;
	char lookAhead[16];
	char searchBuffer[4086];

	for (int i = 0; i < strlen(inputString); i++){
		searchBuffer[i] = inputString[i];
		if (inputString[i+1] != '\0'){
			lookAhead[i] = inputString[i+1];
		}
		lookAhead[i] = inputString[i+1];
		position++;
		printf("Search buffer = %s, lookahead = %s, position = %d\n", searchBuffer, lookAhead, position);
	}
}

int decodeLZ77() {}

int main() {
	char testString[] = "ABB";

	encodeLZ77(testString);

	return 0;
}
