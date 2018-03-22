/* Implement your solution to the File Copy problem here.
   by <Zesun Yang>, <Nov 30 2017>
*/
#include <stdio.h>
int ReadLineFromFile(FILE *input, char buffer[]);
void WriteLineToFile(FILE *output, char buffer[], int n);

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("error, unspecificed files");
        return 0;
    }
    char buf[512];
    int num;
    FILE *input = NULL;
    input = fopen(argv[1], "r");
    if (input == NULL) {
        printf("open file error \n");
        return 0;
    }
    FILE *output = NULL;
    output = fopen(argv[2], "w");
    if (output == NULL) {
        printf("open file error \n");
        return 0;
    }
    int i;
    for (i = 0; i < 50; i++) {
        num =  ReadLineFromFile(input, buf);
        WriteLineToFile(output, buf, num);
    }
    fclose(input);
    fclose(output);
}
int ReadLineFromFile(FILE *input, char buffer[]) {
    int i = 0;
    if (fgets(buffer, 512, input) != NULL) {
        while (buffer[i]!= '\n') {
            i++;
        }
    }
    return i;
}
void WriteLineToFile(FILE *output, char buffer[], int n) {
    int i;
    for (i = 0; i < n; i++) {
       fputc(buffer[i], output);
    }
}
