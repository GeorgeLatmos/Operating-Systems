#include <stdlib.h>
#include <stdio.h>

#include "Interactive.h"

void InteractiveMode(void)
{
  char *line;

  do {

    printf("latmos_8683> ");

    line = readInput();

    exec_cmd(line);

  } while (1);
}

char *readInput(void)
{
  int bufsize = CMD_LENGTH;
  int position = 0;
  char *buffer = malloc(sizeof(char) * bufsize);
  int c;

  while (1) {
    // Read a character
    c = getchar();

    if (c == EOF) {
      exit(EXIT_SUCCESS);
    } else if (c == '\n') {
      buffer[position] = '\0';
      return buffer;
    } else {
      buffer[position] = c;
    }
    position++;
  }
}

