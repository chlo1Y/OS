/* 
Zesun Yang
*/
#include <stdio.h>
#include <math.h>
int main() {
    float x;
    int y;
    int i;
    float output = 1;
    float powOutput;
    printf("Enter a float");
    scanf("%f", &x);
    printf("Enter an int");
    scanf("%d", &y);
    powOutput = pow(x, y);
    if (y == 0) {
    } else if (y > 0) {
        for (i = 1; i <= y; i++) {
            output = output*x;
        }
    } else {
        y = -y;
        for (i = 1; i <= y; i++) {
            output = output*x;
        }
        output = 1/output;
    }
    printf("the output is %.2f\n", output);
    printf("the next line is the result using POW library \n");
    printf("the output from math library is %.2f\n", powOutput);
    return 0;
}


