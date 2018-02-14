#include "main.h" 


int main(int argc, char **argv)
{
	if(argc == 1)
      InteractiveMode();
    else
      BatchMode(argc,argv);

  return EXIT_SUCCESS;
}