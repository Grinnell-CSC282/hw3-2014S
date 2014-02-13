#include <stdio.h>
#include <string.h>
#include <limits.h>

/*
This program removes extra crap that script puts into its output.
This particular implementation might not remove all the extra
things script puts in. Colin Trembley was a great person to chat
with while writing this, and his hex numbers for the characters
came in handy. This could definitely use some more improvement.

Authors:
Andrew Kelley
Mark Lewis
*/

int main(int argc, char* argv[]) {
	FILE *fp;
	char str[LINE_MAX];
	int i, j;
	char strClean[LINE_MAX];
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
//0x07 is ^G
	while(fgets(str, LINE_MAX, fp) != NULL) {
		j = 0;
		for(i = 0; str[i] != '\0'; i++) {
			switch (str[i]) {
				case '\r' :
					i++;
					strClean[j++] = '\n';
					break;
				case 0x08 : 
					// skip ahead for i because ^H followed by ^[[K
					i += 3;	
					// go back one character for each backspace
					j--;
					break;
				case 0x1B :
					// case of beginning ^[
				case 0x07 :
					// case of ^G
					break;
				default :
					strClean[j++] = str[i];
					break;	
			} // switch
		} // for
		strClean[j] = '\0';
		fputs(strClean, fileWrite);
	} // while
	// close files
	fclose(fp);
	fclose(fileWrite);

	return 0;
}
