#include <stdio.h>
#include <string.h>

/*
This program removes extra crap that script puts into its output.
This particular implementation might not remove all the extra
things script puts in. Colin Trembley was a great person to chat
with while writing this, and his hex numbers for the characters
came in handy. This could definitely use some more improvement.
*/

int main(int argc, char* argv[]) {
	FILE *fp;
	char str[80];
	int i, j;
	char strClean[80];
	// open file
	fp = fopen(argv[1], "r");
	// check for null file
	if(fp == NULL) {
		perror("Error opening file");
		return (-1);
	} // if
	FILE *fileWrite;
	fileWrite = fopen(strcat(argv[1], "Clean"), "w");
	if(!fileWrite) {
		printf("Failed to open write file\n");
		return 1;
	} // if

	while(fgets(str, 80, fp) != NULL) {
		j = 0;
		for(i = 0; i < 80; i++) {
			if(str[i] == '\r') {
				i++;
				strClean[j++] = '\n';
			} else if(str[i] == 0x08) {
				// skip ahead for i because ^H followed by ^[[K
				i += 3;
				// go back one character for each backspace
				j--;
			} else if(str[i] == 0x1B) {
				// case of beginning ^[
				continue;
			} else {
				strClean[j++] = str[i];
			} // if else
		} // for
		strClean[j] = '\0';
		fputs(strClean, fileWrite);
	} // while
	fclose(fp);
	fclose(fileWrite);

	return 0;
}
