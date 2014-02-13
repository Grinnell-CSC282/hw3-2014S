#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>


// Attempt at using STDIN, STDOUT
//  DOESN'T WORK
int 
main (int argc, char *argv[]) {
  char buffer[LINE_MAX];
  while (gets(buffer)) {
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
      switch (buffer[i]) {
      case 0x08: // Backspace
        j--;
        i += 3; // Skip garbage
        break;
      case 0x07: // ^G
      case '\r': // ^M
        break;
      default:
	buffer[j++] = buffer[i];
        break;
      }
    }
    buffer[j] = '\0';
    puts(buffer);
  }

  return 0; 
}

   /*******************************************************
     * Remove the opening garbage
     *  I am not sure if this appears on other machines, but
     *  on mine, script output lines look like this:
^[]0;colin@colin-VirtualBox: ~/Documents^Gcolin@colin-VirtualBox:~/Documents$
     * even though the shell itself looks like this:
       colin@colin-VirtualBox:~/Documents$ 
     * 
     * Update: This doesn't appear on mathLAN machines
     * but it doesn't break it so, I'm leaving it in
   *********************************************************/
