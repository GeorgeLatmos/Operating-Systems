#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "Batch.h"


void BatchMode(int argc, char **argv){

	char *filename;
	char *filetype = ".txt";
    char buf[CMD_LENGTH];
	int num_of_cmds = 0;
	FILE *fp;

	filename = argv[1];
	strcat(filename,filetype);

    if ((fp = fopen(filename, "r")) == NULL)
    {
      printf("Error! opening file\n");
      exit(1);         
    }

    num_of_cmds = get_num_of_cmds(fp);

    //printf("%d\n",num_of_cmds);

	fseek(fp,0,SEEK_SET);

	int k = getcmd(buf,sizeof(buf),fp);

    int i;

    for(i=0; i<num_of_cmds; i++){
    	exec_cmd(buf);
    	k = getcmd(buf,sizeof(buf),fp);
    }

    fclose(fp);
}

int get_num_of_cmds(FILE *fp){

	int num_of_cmds = 0;
	char buf[CMD_LENGTH];

	int k = getcmd(buf,sizeof(buf),fp);
	
	while(k>=0){
	  num_of_cmds++;
      k = getcmd(buf,sizeof(buf),fp);
	}

	return num_of_cmds;
}
