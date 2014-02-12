#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>

int 
main (int argc, char *argv[]) {
  // Exit if incorrect number of arguments
  if (2 != argc) {
    printf("Usage: %s filename\n", argv[0]);
    return 1;
  }

  // Open the file
  char *filename = argv[1];
  FILE *file = fopen(filename, "r");

  // Create an output filename
  char *output_filename = malloc(strlen(filename) + strlen("clean-") + 1);
  if (!output_filename) {
    printf("Error allocating memory");
    return 1;
  }
  output_filename[0] = '\0';
  strcat(output_filename, "clean-");
  strcat(output_filename, argv[1]);

  // Open the output file
  FILE *output = fopen(output_filename , "w");
  // Exit if fopen returned null
  if (!output) {
    printf("Failed to open file %s\n", argv[1]);
    return 1;
  }
  
  char buffer[LINE_MAX];
  while (fgets(buffer, LINE_MAX, file)) {
    int i, j, start;
    // Remove the opening garbage (see note below)
    start = 0;
    if (0x1b == buffer[0]) {
      char *cntrl_G_pointer = strchr(buffer, 0x07);
      if (cntrl_G_pointer) {
	start = cntrl_G_pointer - buffer + 1;
      } 
    }
    
    // Loop through the line and remove characters
    for (i = start, j = 0; '\0' != buffer[i]; i++) {
      // Handle backspace
      if (0x08 == buffer[i]) {
	j--;
	// skip the what follows (^[[k) 
	i += 3;
      }
      // Handle ^M and ^G
      else if ('\r' != buffer[i] && 0x07 != buffer[i]) {
	buffer[j++] = buffer[i];
      }
    }
    buffer[j] = '\0';
    fputs(buffer, output);
  }

  // Close the files
  fclose(file);
  fclose(output);
  return 0; 
}

   /*******************************************************
     * Remove the opening garbage
     *  I am not sure if this appears on other machines, but
     *  on mine, script output lines look like this:
^[]0;colin@colin-VirtualBox: ~/Documents^Gcolin@colin-VirtualBox:~/Documents$
     * even though the shell itself looks like this:
       colin@colin-VirtualBox:~/Documents$ 
   *********************************************************/
