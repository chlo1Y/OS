/**
 * Tokenizer.c 1.0 03/18/2004
 *
 *
 * authors:  Example obtained from C Resource Network.
 *           Modified by:  David Mutchler, Archana Chidanandan, and
 *			   Delvin Defoe
 */

/******************************************************/
/* This program is an example on how to use the "strtok"
function.  

Prototype:
char *  strtok ( const char * string, const char * delimiters ); 

Library: string.h

Description:
If string is not NULL, the function scans string for the first
occurrence of any character included in delimiters. If it is 
found, the function overwrites the delimiter in string with a 
null-character and returns a pointer to the token, i.e.
the part of the scanned string previous to the delimiter.
After a first call to strtok, the function may be called 
with NULL as the string parameter, and it will continue from 
where the last call to strtok found a delimiter. Delimiters
may vary from one call to another.

Return Value:
A pointer to the last token found in string.   NULL is 
returned when there are no more tokens to be found. 
********************************************************/

#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[]) {
  char str[] ="This is a sample string,just testing.";
  char *pch;

  printf("Splitting string \"%s\" in tokens:\n", str);
  /*The first call, with str as the string and space as the delimiter.
   * If this call is successful, pch points to  the "T" and the space 
   * encountered will be replaced by NULL. Moreover, the next search 
   * will begin at the space that was just replaced by a NULL 
   * */
  pch = strtok(str, " ");
  /* 1. What do you think "str" will be?
   * Print the value of "str" to see if you are right. 
   * */

  while (pch != NULL) {
    printf("%s\n", pch);
    /* Use of more than 1 delimiter. 
     * The function will look for both and will return a value when 
     * it encounters either of them.
     * Will not look for spaces anymore. 
     * */
    pch = strtok(NULL, ".,");
  } 
  

  /* 2. Replace the "NULL" in the previous function call with "str".
   * What do you think will happen? */

  return 0;
}


