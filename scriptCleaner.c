#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int main (int argc, char *argv[])
{
  //Buffer
  char buffer[LINE_MAX]; 

  int i;

  FILE *unclean = fopen(argv[1], "r");

  char *fileName = strcat(argv[1], "cleaned");
  FILE *fileName =  fopen(argv, "r");

  while(!feof(unclean))
    {
      
      fgets(buffer, LINE_MAX, unclean);
      
      for(j=0; (buffer[i]) != '\0'; j++)
        {
          switch (buffer[i])
          case '^M';
            
            }
    }

  return 0;
}
