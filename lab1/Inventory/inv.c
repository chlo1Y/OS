/* This is where you implement the core solution.
   by <Zesun Yang>, <Nov 30 2017>
*/
#include "./inv.h"
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char *argv[]) {
    struct Inventory array[100];
    int i;

    if (argc != 3) {
        printf("number of files incorrect");
        return 0;
    }
    FILE *input = NULL;
    input = fopen(argv[1], "r");
    if (input == NULL) {
        printf("file cannot be opened\n");
        exit(1);
    }
    int j = 0;
    while (!feof(input)) {
        fscanf(input, "%d %d %f %d/%d",
        &array[j].itemNumber,
        &array[j].quantityOnHand,
        &array[j].price,
        &array[j].expireDate.month,
        &array[j].expireDate.year);
        if (feof(input)) {
            break;
        }
        j++;
    }

    printf("item Quantity Price    ExireDate\n");
    for (i = 0; i < j; i++) {
    printf("%d\t%d\t%.2f\t%d/%d\n",
        array[i].itemNumber,
        array[i].quantityOnHand,
        array[i].price,
        array[i].expireDate.month,
        array[i].expireDate.year);
  }
  fclose(input);
  FILE *output = NULL;
  output = fopen(argv[2], "w");
  for (i = 0; i < j; i++) {
      if ((array[i].expireDate.year > 2008) ||
      ((array[i].expireDate.year == 2008)
      && (array[i].expireDate.month > 10))) {
          fprintf(output, "%d\t%d\t%.2f\t%d/%d\n",
        array[i].itemNumber,
        array[i].quantityOnHand,
        array[i].price,
        array[i].expireDate.month,
        array[i].expireDate.year);
      } else {
      }
  }
  fclose(output);
}
