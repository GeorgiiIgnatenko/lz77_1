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

void findLongestMatch(char *searchBuffer, char *lookAhead)
{	
	
}

int encodeLZ77(char *inputString) {
	int position = 0;
	char lookAhead[16];
	char searchBuffer[4086];

	for (int i = 0; i < strlen(inputString); i++){
		searchBuffer[i] = inputString[i];
		memcpy(lookAhead, inputString + i + 1, 16);
		position++;
		printf("Search buffer = %s, lookahead = %s, position = %d\n", searchBuffer, lookAhead, position);
		findLongestMatch(searchBuffer, lookAhead);	
	}
}

int decodeLZ77() {}

int main(int argc, char *argv[]) {
	char testString[] = "ABB";
	int mode = 0;
	if (argc == 4){	
		if(strcmp(argv[1], "-c") == 0)
		{
			mode = 1;
		}else if (strcmp(argv[1], "-d") == 0)
		{
			mode = 2;
		}else {
			printf("error");
		}
	}else if(argc < 4){
		printf("need more arguments\n");
	}
	printf("%d\n",mode);

	encodeLZ77(testString);

	return 0;
}
