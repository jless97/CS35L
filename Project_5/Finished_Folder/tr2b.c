#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

int main(int argc, char* argv[]) {

  //Check to make sure only two operands are provided
  if (argc != 3) {
    fprintf(stderr, "Error: incorrect number of command-line arguments supplied!\n");
    exit(1);
  }

  //Fill the from and to operands with the command-line argument inputs
  char *from = argv[1];
  char *to = argv[2];
  
  size_t fromLength = strlen(from), toLength = strlen(to);
  size_t i, j;

  //Error if from and to aren't the same length
  if (fromLength != toLength) {
    fprintf(stderr, "Error: Input are not of the same length!\n");
    exit(1);
  }

  //Error if from has duplicate bytes
  for (i = 0; i < fromLength - 1; i++) {
    if (from[i] == from[i + 1]) {
      fprintf(stderr, "Error: Input from contains duplicate bytes!\n");
      exit(1);
    }
  }

  // Transliteration of from bytes into to bytes of a given input 
  char currentByte = getchar();
  int validByteInFrom = FALSE;
  while (currentByte != EOF) {
    for (i = 0; i < fromLength; i++) {
      //If the input contains bytes of from replace with bytes of to
      if (currentByte == from[i]) {
	putchar(to[i]);
	validByteInFrom = TRUE;
        break;
      }
      else {
	validByteInFrom = FALSE;
      }
    }
    //If the current byte is not equal to a byte in the from operand, then leave as is
    if (!validByteInFrom)
      putchar(currentByte);

    currentByte = getchar();
  }

  return(0);
}
