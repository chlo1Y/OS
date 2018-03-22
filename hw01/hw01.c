#include <stdio.h>
#include "CuTest.h"
#include <string.h>

/*
Copyright 2016 Rose-Hulman Institute of Technology
*/

/* Returns true (non-zero) if a number is power of 3, false otherwise.

   For example:

   9 returns true
   12 returns false 
   14 returns false 
   3 returns true 
   27 returns true 
   1 returns true 
   0 returns false
*/
int isPowerOfThree(unsigned int num) {
  if (num == 1)
    return 1;
  if (num == 0 || num%3 != 0)
    return 0;
  return isPowerOfThree(num/3);
}


void test_isPowerOfThree(CuTest *tc) {
  CuAssertTrue(tc, isPowerOfThree(9));
  CuAssertTrue(tc, !isPowerOfThree(11));
  CuAssertTrue(tc, !isPowerOfThree(12));
  CuAssertTrue(tc, !isPowerOfThree(15));
  CuAssertTrue(tc, isPowerOfThree(27));
  CuAssertTrue(tc, isPowerOfThree(59049));
  CuAssertTrue(tc, isPowerOfThree(3));
  CuAssertTrue(tc, isPowerOfThree(1));
  /* I am leaving this one off because if you don't handle it
     correctly it tends to seg-fault your code.  But make sure your
     version works - uncomment it when you're ready!  */
  CuAssertTrue(tc, !isPowerOfThree(0));
}

/* Takes a number between 0 and 1 and an output array.

   Modifies the output array to be a C string (zero terminated)
   containing the number as a percentage with two decmal places of
   accuracy.

   For example:

   .45 returns "45.00%"
   1 returns "100.00%"
   .122222222 returns "12.22%"
   .155555    returns "15.56%"

   NOTE: Don't solve this yourself!  Use the built in C function snprintf.

   The linter will want you to use sizeof(output) for the size but
   that can't work in this case.  Use the actual size which is 100.
*/
void floatAsPercentString(float input, char* output) {
  snprintf(output, sizeof(output), "%.2f%%", input*100);
}

void test_floatAsPercentString(CuTest *tc) {
  char outputString[100];
  floatAsPercentString(0.45, outputString);
  CuAssertStrEquals(tc, "45.00%", outputString);
  floatAsPercentString(1, outputString);
  CuAssertStrEquals(tc, "100.00%", outputString);
  floatAsPercentString(0, outputString);
  CuAssertStrEquals(tc, "0.00%", outputString);
  floatAsPercentString(0.2222222, outputString);
  CuAssertStrEquals(tc, "22.22%", outputString);
  floatAsPercentString(0.555555, outputString);
  CuAssertStrEquals(tc, "55.56%", outputString);
}

/* Takes pointers to three equally sized arrays and the array size.  Computes
   array1 + array2 and places the result in the output array.

   Note that the arrays will come in as pointers, because in C arrays
   and pointers are interchangable.

   Example:
   {1, 2, 3} plus {3,5,-6} yields {4,7,-3}
*/
void sumPairOfArrays(int* array1, int* array2, int* output, int size) {
  int i;
  for (i = 0; i < size; i++) {
     output[i]= array1[i]+ array2[i];
  }
}

void test_sumPairOfArrays(CuTest *tc) {
  int a1[] = {1, 2, 3};
  int a2[] = {7, 44, -6};
  int a3[3];

  int b1[] = {1, 100};
  int b2[] = {2, 10};
  int b3[2];

  sumPairOfArrays(a1, a2, a3, 3);

  CuAssertIntEquals(tc, 8, a3[0]);
  CuAssertIntEquals(tc, 46, a3[1]);
  CuAssertIntEquals(tc, -3, a3[2]);

  sumPairOfArrays(b1, b2, b3, 2);
  CuAssertIntEquals(tc, 3, b3[0]);
  CuAssertIntEquals(tc, 110, b3[1]);
}

/*
Returns true (non-zero) if given string has duplicate characters,
false otherwise.

"abcd" returns false
"abcda" returns true

You'll probably find it more instructive to use two nested for/while
loops than crazy shenanigans like an array that your keep character
counts in.

Remember that in c, a string is just an array with a \0 character at the end
*/
int hasDuplicateCharacters(char* inputString) {
  int i, j;
  if (sizeof(inputString) == 0) {
    return 1;
  }
  for (i = 0; i <strlen(inputString)-1; i++) {
    for (j = i+1; j <strlen(inputString); j++) {
      if (inputString[i] == inputString[j]) {
        return 1;
      }
    }
  }
  return 0;
}

void test_hasDuplicateCharacters(CuTest *tc) {
  CuAssertTrue(tc, !hasDuplicateCharacters("abcdefg"));
  CuAssertTrue(tc, hasDuplicateCharacters("abcdefgb"));
  CuAssertTrue(tc, hasDuplicateCharacters("abcdefga"));
  CuAssertTrue(tc, !hasDuplicateCharacters("123456789"));
  CuAssertTrue(tc, !hasDuplicateCharacters(""));
  CuAssertTrue(tc, hasDuplicateCharacters("123456788"));
}

struct LinkedListNode {
  int data;
  struct LinkedListNode* next;
};

/*
  Given 2 nodes in a singly linked list, start, which occurs before
  end, determines the distance between the nodes.

  For example, in a list like this:

  A -> B -> C -> D

  linkedListDistance(A,D) returns 3
  linkedListDistance(A,B) returns 1
  linkedListDistance(B,D) returns 2
  linkedListDistance(C,C) returns 0
 */
int linkedListDistance(struct LinkedListNode* start,
                       struct LinkedListNode* end) {
  int i;
  if (start == end) {
    return 0;
  }
  return linkedListDistance((*start).next, end)+1;
}

void test_linkedListDistance(CuTest *tc) {
  struct LinkedListNode last = {0, NULL};
  struct LinkedListNode first = {0, &last};
  struct LinkedListNode middleNodes[10];
  int i;

  CuAssertIntEquals(tc, 1, linkedListDistance(&first, &last));
  for (i = 0; i < 9; i++) {
    middleNodes[i].data = 0;
    middleNodes[i].next = middleNodes + i + 1;
  }
  first.next = middleNodes;
  middleNodes[9].next = &last;
  CuAssertIntEquals(tc, 11, linkedListDistance(&first, &last));
  CuAssertIntEquals(tc, 1, linkedListDistance(&first, middleNodes));
  CuAssertIntEquals(tc, 2, linkedListDistance(&first, middleNodes+1));
  CuAssertIntEquals(tc, 3, linkedListDistance(&first, middleNodes+2));
}


void RunAllTests() {
  CuString *output = CuStringNew();
  CuSuite* suite = CuSuiteNew();
  SUITE_ADD_TEST(suite, test_isPowerOfThree);
  SUITE_ADD_TEST(suite, test_floatAsPercentString);
  SUITE_ADD_TEST(suite, test_sumPairOfArrays);
  SUITE_ADD_TEST(suite, test_hasDuplicateCharacters);
  SUITE_ADD_TEST(suite, test_linkedListDistance);

  CuSuiteRun(suite);
  CuSuiteSummary(suite, output);
  CuSuiteDetails(suite, output);
  printf("%s\n", output->buffer);
}

int main() {
  /* if you want to test by hand, feel free to comment out this line
     and use your own code */
  RunAllTests();
}
