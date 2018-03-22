/*
By <zesun Yang> Dec 9 2017 
Lab2
*/

#include <stdio.h>
#include <string.h>
int main(int argc, char** argv) {
  char phrase[128];
  char* pch;
  printf("Enter a phrase: ");
  scanf("%[^\n]", phrase);
  pch = strtok(phrase, " ");
  while (pch != NULL) {
    printf("%s%cay ", pch+1, pch[0]);
    pch = strtok(NULL, " ");
  }
  printf("\n");
  return 0;
}
