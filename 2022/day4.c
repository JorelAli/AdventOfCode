#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool encases(int start1, int end1, int start2, int end2) {
	return (start1 <= start2 && end1 >= end2) || (start2 <= start1 && end2 >= end1);
}

bool overlaps(int start1, int end1, int start2, int end2) {
	return (/* max */ start1 <= start2 ? start2 : start1) <= (/* min */ end1 <= end2 ? end1 : end2);
}

int main() {
	FILE* file = fopen("day4_input.txt", "r");
	if (NULL == file) {
		printf("The input file day4_input_1.txt cannot be opened!\n");
		exit(1);
	}

	// Read the file contents
	char* fileContents = NULL;

	fseek(file, 0, SEEK_END);
	long fileLength = ftell(file);
	fseek(file, 0, SEEK_SET);
	fileContents = malloc(fileLength + 1);
	if (fileContents) {
		fread(fileContents, sizeof(char), fileLength, file);

		// Need to terminate this string for strtok(NULL, "\n") to be happy
		fileContents[fileLength - 1] = '\0';
	}
	fclose(file);

	int numberOfFullyContainedAssignments = 0;
	int numberOfOverlappingAssignments = 0;

	// Read each line
	char* line = strtok(fileContents, "\n");
	while (line != NULL) {
		// The rest of the line
		char* rest = line;

		// Read elf 1
		int elfOneStart = strtol(rest, &rest, 10);
		int elfOneEnd = strtol(++rest, &rest, 10);

		// Read elf 2
		int elfTwoStart = strtol(++rest, &rest, 10);
		int elfTwoEnd = strtol(++rest, &rest, 10);

		// Count assignments that fully encase each other
		if (encases(elfOneStart, elfOneEnd, elfTwoStart, elfTwoEnd)) {
			numberOfFullyContainedAssignments++;
		}

		// Count assignments that overlap each other
		if (overlaps(elfOneStart, elfOneEnd, elfTwoStart, elfTwoEnd)) {
			numberOfOverlappingAssignments++;
		}

		line = strtok(NULL, "\n");
	}

	free(fileContents);

	printf("Part 1: %d\n", numberOfFullyContainedAssignments);
	printf("Part 2: %d\n", numberOfOverlappingAssignments);
}
