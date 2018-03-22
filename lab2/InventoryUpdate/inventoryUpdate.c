/* Zesun Yang Dec 10 2017*/
#include <stdio.h>
#include <stdlib.h>
#include "./inv.h"

int populateArray(Inventory** arrayAddr, int* size, FILE* input);
void printInventory(Inventory* array, int numEntries);
int deleteExpiredItems(Inventory** arrayAddr, int* size, int numEntries);
void saveInventory(Inventory* array, int size, FILE* output);

int main(int argc, char* argv[]) {
  if (argc != 3) {
        printf("number of files incorrect\n");
        return 0;
    }
    FILE *input = NULL;
    input = fopen(argv[1], "r");
    if (input == NULL) {
        printf("file cannot be opened\n");
        exit(1);
    }
    int size = 2;
    Inventory* array = (Inventory*) malloc(size * sizeof(Inventory));
    int validEntry = populateArray(&array, &size, input);
    printInventory(array, validEntry);
    int newNum;
    newNum = deleteExpiredItems(&array, &size, validEntry);
    printInventory(array, newNum);
    FILE *output = NULL;
    output = fopen(argv[2], "w");
    saveInventory(array, size, output);
    free(array);
    fclose(input);
    fclose(output);
    return 0;
}

int populateArray(Inventory** arrayAddr, int* size, FILE* inputFile) {
  Inventory array;
  int i = 0;
  while (!feof(inputFile)) {
    fscanf(inputFile, "%d %d %f %d/%d",
        &array.itemNumber,
        &array.quantityOnHand,
        &array.price,
        &array.expireDate.month,
        &array.expireDate.year);
        if (feof(inputFile)) {
            break;
        }
        if (i >= *size) {
            *size = (*size) * 2;
            *arrayAddr = (Inventory*) realloc(*arrayAddr,
            *size*sizeof(Inventory));
        }
         (*arrayAddr)[i] = array;
         i++;
  }
  return i;
}

void printInventory(Inventory* array, int validEntry) {
  printf("item# Quantity Price  ExireDate\n");
  int i;
  for (i = 0; i < validEntry; i++) {
    printf("%d\t%d\t%.2f\t%d/%d\n",
        array[i].itemNumber,
        array[i].quantityOnHand,
        array[i].price,
        array[i].expireDate.month,
        array[i].expireDate.year);
  }
}

int deleteExpiredItems(Inventory** arrayAddr, int* size, int validEntry) {
  Inventory* temp = (Inventory*) malloc(*size*sizeof(Inventory));
  int i;
  int j = 0;
  for (i = 0; i < validEntry; i++) {
    if ((*arrayAddr)[i].expireDate.year >= 2005) {
      temp[j] = (*arrayAddr)[i];
      j++;
    }
  }
  *size = j;
  *arrayAddr = (Inventory*) realloc(*arrayAddr, *size*sizeof(Inventory));
  int k;
  for (k = 0; k < *size; k++) {
    (*arrayAddr)[k] = temp[k];
  }
  free(temp);
  return *size;
}

void saveInventory(Inventory* array, int size, FILE* output) {
  int i;
  for (i = 0; i < size; i++) {
    fprintf(output, "%d\t%d\t%.2f\t%d/%d\n",
        array[i].itemNumber,
        array[i].quantityOnHand,
        array[i].price,
        array[i].expireDate.month,
        array[i].expireDate.year);
  }
}
