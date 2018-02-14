#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define CMD_LENGTH 512

#define LSH_TOK_BUFSIZE 64
#define LSH_TOK_DELIM " \t\r\n\a"

char **split_line(char *line);
int launch(char **args);
int execute(char **args);
int findCommandTypeNum(char *line);
void exec_cmd(char *line);
char *findCommandType(int type_num);
int getcmd(char *buf, int nbuf,FILE *fp);