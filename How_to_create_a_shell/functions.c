#include "Functions.h"

char **split_line(char *line)
{
  int bufsize = LSH_TOK_BUFSIZE, position = 0;
  char **tokens = malloc(bufsize * sizeof(char*));
  char *token, **tokens_backup;

  token = strtok(line, LSH_TOK_DELIM);
  while (token != NULL) {
    tokens[position] = token;
    position++;

    token = strtok(NULL, LSH_TOK_DELIM);
  }
  tokens[position] = NULL;
  return tokens;
}

int launch(char **args)
{
  pid_t pid;
  int status;

  pid = fork();
  if (pid == 0) {
    // Child process
    if (execvp(args[0], args) == -1) {
      perror("error");
    }
    exit(EXIT_FAILURE);
  } else if (pid < 0) {
    // Error forking
    perror("error");
  } else {
    // Parent process
    do {
      waitpid(pid, &status, WUNTRACED);
    } while (!WIFEXITED(status) && !WIFSIGNALED(status));
  }

  return status;
}

int execute(char **args)
{

  if (args[0] == NULL) {
    // An empty command was entered.
    return 1;
  }
 
  return launch(args);
}


int findCommandTypeNum(char *line){
  int i;
  char type;
  int type_num;

  for(i=0; i<strlen(line); i++){
    if(line[i] == ';'){
      type = ';';
      type_num = 0;
      break;
    }else if(line[i] == '&'){
      type = '&';
      type_num = 1;
      break;
    }else{
      if(i == strlen(line)-1){
        type = ' ';
        type_num = 2;
        break;
      }
    }
  }
  return type_num;
}

char *findCommandType(int type_num){

  char *type;

  switch(type_num){
    case 0:
      type = ";";
      break;
    case 1:
      type = "&";
      break;
    case 2:
      type = " ";
      break;
  }

  return type;

}

int
getcmd(char *buf, int nbuf,FILE *fp)
{
  
  if (isatty(fileno(fp)))
    fprintf(stdout, "$ ");
  memset(buf, 0, nbuf);
  fgets(buf, nbuf, fp);
  if(buf[0] == 0) // EOF
    return -1;
  return 0;
}

void exec_cmd(char *line){

  int pid;
  char **args;
  char *token;
  int status;
  char *type;
  int type_num;
  int p[2];

  type_num = findCommandTypeNum(line);
  type = findCommandType(type_num);

  if((strcmp(line, "quit") == 0) ||(strcmp(line, "quit\n") == 0)){
  	type_num = 3;
  }

   switch(type_num){
   	  default:
        exit(0);
   	    break;
      case 0:
        token = strtok(line, type);

        while(token != NULL){

          pid = fork();

          if(pid == 0){
            args = split_line(token);
            status = execute(args);
            exit(0);
          }else{
            wait(NULL);
            token = strtok(NULL,type);
          }
        }
        break;
      case 1:

        pipe(p);

        token = strtok(line, type);

        while(token != NULL){

          int success = 1;

          pid = fork();

          if(pid == 0){
          	close(p[0]);

            args = split_line(token);
            status = execute(args);
            if(status != 0){
              success = 0;
              write(p[1],&success,1);
            }
            exit(0);
          }else{
            waitpid(pid,&status,WUNTRACED);
            close(p[1]);
            read(p[0],&success,1);
            if(success == 1)
              token = strtok(NULL,type);
            else
              return;
        }
      }
      break;
     case 2:
       args = split_line(line);
       status = execute(args);
     break;
    }
}

