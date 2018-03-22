/* author
    Donglai Guo, Zesun Yang and Zhihong Zhai Team 1E
    Created on 1/23/18
*/
void handleInterrupt21 (int AX, int BX, int CX, int DX);
void readString(char * line);
void printString(char * chars);
void readSector(char *buffer , int sector);
int mod(int a, int b);
int div(int a, int b);
void readFile(char * chars, char * buffer , char *numberOfSectors);
void executeProgram(char *name);
void terminate();
void writeSector(char *buffer, int sector);
void deleteFile(char* name);
void writeFile(char* name, char* buffer, int numberOfSectors);
void handleTimerInterrupt(int segment, int sp);
void changegcolor(int a, int b);
void changefcolor(int a, int b);
void readOtherString(char * line);
void printHexNum(int num);
void delay(int time);
void getTimeCounter(int *time);
void enableGraphics();
void drawPixel(int x, int y, int color);
void disableGraphics();
void readChar(char *c);
void scrollDown(char numRows);
void scrollUp(char numRows);
void clean();
void setCursorPos(char x, char y);


typedef struct {
    int activeStatus;
    int processPtr;
    int waiting;
}processTableBox;
processTableBox processTable[8];
int currentProcess=0;
int timerCounter;

int main(){
    char line[80];
    char buffer[512];
    char fileBuffer[13312];
    int i = 0;
    int d = 0;
    for (d =0; d<8; d++){
        processTable[d].activeStatus=0;
        processTable[d].processPtr = 0xff00;
        processTable[d].waiting = d;
    }
    currentProcess=0;
    timerCounter = 0;
     /* this is the maximum size of a file */
    makeInterrupt21();

    for (i = 0; i < 13312; i++){
        fileBuffer[i] = 0;
    }
/*    interrupt(0x21, 6, buffer, 1, 0, 0);*/
    interrupt(0x21, 0, "Start\r\n\0", 0, 0, 0);
    makeTimerInterrupt();
    interrupt(0x21, 4, "shell\0", 0, 0);

    while(1);			            /* hang */

    return 0;
}
void wait(char *name){
    char buffer[13312];
    int i = 0;
    int exeSeg;
    char temp;
    int j=0;
    char debug[4];

    debug[0] = 'h';
    debug[1] = '\n';
    debug[2] = '\r';
    debug[3] = '\0';
/*    printString(debug);*/
    for(i = 0; i < 13312; i++){
        buffer[i] = '\0';
    }
    setKernelDataSegment();
    while(processTable[j].activeStatus!=0 && j<8){
        j++;
    }
    if(j>=8){
        printString("no free entry \0");
        return;
    }
/*    currentProcess=j;*/
    restoreDataSegment();
    debug[0] = j+0x30;
/*    printString(debug);*/
    readFile(name, buffer, &temp);
    debug[0] = j+0x30;
/*    printString(debug);*/
    exeSeg=j *(0x1000) + 0x2000;
    /* void putInMemory (int segment, int address, char character) */
    for(i = 0; i < 13312; i++){
        putInMemory(exeSeg, i, buffer[i]);
    }
    initializeProgram(exeSeg);
    setKernelDataSegment();
    processTable[j].processPtr = 0xff00;
    processTable[j].activeStatus = 1;
    processTable[j].waiting = j;
    processTable[currentProcess].waiting = j;
    restoreDataSegment();
}

void killProcess(int processNum){
    int i = 0;
    setKernelDataSegment();
    for (i = 0; i < 8; i++){
        if (processTable[i].waiting == processNum){
            processTable[i].waiting = i;
        }
    }
    processTable[processNum].activeStatus=0;
    restoreDataSegment();
}
void readFile(char * chars, char * buffer, char *numberOfSectors){
    char out[512];
    int i;
    int j;
    readSector(out, 2);
    *numberOfSectors = 0;
    for (i=0; i<16; i++){
        for(j=0; j<6; j++){
            char test[5];
            test[4] = '\0';
            test[3] = '\r';
            test[2] = '\n';
            test[1] = 0x30;
            test[0] = 0x30 + i;
/*            interrupt(0x21, 0, test, 0, 0);*/
            if(out[32*i+j]!= chars[j]){
                break;
            }else if (j==5){
                int m=0;
                j=6;
                test[0] = 'f';
/*                interrupt(0x21, 0, test, 0, 0);*/
                while (out[32*i+j]!=00){
                    int z;
                    char newOut[512];
                    test[0] = div(out[32*i+j], 10) + 0x30;
                    test[1] = mod(out[32*i+j], 10) + 0x30;
/*                    printString(test);*/
                    readSector(newOut, out[32*i+j]);
                    test[0] = 'r';
/*                    printString(test);*/
                    for(z=0; z<512; z++){
                        buffer[512*m+z]=  newOut[z];
                    }
                    m++;
                    j++;

                    *numberOfSectors = m;

                }
                test[0] = 'd';
/*                printString(test);*/
                return;
            }
        }
    }
    return ;


}

void handleInterrupt21 (int AX, int BX, int CX, int DX) {
    switch(AX) {
        case 0: printString(BX); break;
        case 1: readString(BX); break;
        case 2: readSector(BX, CX); break;
        case 3: readFile(BX, CX, DX); break;
        case 4: executeProgram(BX); break;
        case 5: terminate(); break;
        case 6: writeSector(BX, CX); break;
        case 7: deleteFile(BX); break;
        case 8: writeFile(BX,CX,DX); break;
        case 9: killProcess(BX); break;
        case 10: wait(BX); break;
        case 11: changegcolor(BX,CX);break;
        case 12: readOtherString(BX); break;
        case 13: changefcolor(BX,CX); break;
        case 14: delay(BX);break;
        case 15: getTimeCounter(BX);break;
        case 16: enableGraphics();break;
        case 17: drawPixel(BX, CX, DX); break;
        case 18: disableGraphics();break;
        case 19: readChar(BX);break;
        case 20: scrollDown(BX);break;
        case 21: scrollUp(BX);break;
        case 22: clean();break;
        case 23: setCursorPos(BX, CX);break;
        default: printString("Error\0");
    }

}
void changegcolor(int a, int b){
    interrupt(0x10,a, b,0,0);
}
void changefcolor(int a, int b){
    interrupt(0x10,a, b,0,0x2580);
}

void printString(char * chars){
    int i = 0;
    while(chars[i]!='\0'){
        interrupt(0x10,0xe*256+ chars[i],0,0,0);
        i++;
    }
}
void readChar(char *c){
    *c = interrupt(0x16,0,0,0,0);
}
void readString(char * line){
    int index = 0;
    char temp[2];

    temp[1] = '\0';
    while(1){
      temp[0] = interrupt(0x16,0,0,0,0);
      printString(temp);
      if(temp[0]==0xd){
        line[index] = 0xd;
        line[index+1] = 0xa;
        line[index+2] = 0x0;
        break;
      } else if(temp[0] == 0x8){
        temp[0] = ' ';
      	printString(temp);
        temp[0] = 0x8;
        printString(temp);
        if (index > 0){
          index --;
        }
      } else{
        line[index] = temp[0];
        index++;
      }


    }
    temp[0] = 0xa;
    printString(temp);

}

void readOtherString(char * line){
    int index = 0;
    char temp[3];
    int test;
    temp[2] = '\0';
    while(1){
      test = interrupt(0x16,0x1000,0,0,0);
      test = test >> 8;
      temp[0] = div(test, 10) + 0x30;
      temp[1] = mod(test, 10) + 0x30;
    printString(temp);
      if(temp[0]==0xd){
        line[index] = 0xd;
        line[index+1] = 0xa;
        line[index+2] = 0x0;
        break;
      } else if(temp[0] == 0x8){
        temp[0] = ' ';
        printString(temp);
        temp[0] = 0x8;
        printString(temp);
        if (index > 0){
          index --;
        }
      } else{
        line[index] = temp[0];
        index++;
      }


    }
    temp[0] = 0xa;
    printString(temp);

}

void writeSector(char *buffer, int sector){
    int relativeSector=0;
    int head=0;
    int track=0;
    relativeSector=mod(sector,18)+1;
    head = mod(div(sector,18),2);
    track = div(sector, 36);
    interrupt(0x13, 3*256+1, buffer, track*256+relativeSector, head*256);
}

void readSector(char *buffer, int sector){
    int relativeSector=0;
    int head=0;
    int track=0;
    relativeSector=mod(sector,18)+1;
    head = mod(div(sector,18),2);
    track = div(sector, 36);
    interrupt(0x13, 2*256+1, buffer, track*256+relativeSector, head*256);
}

int mod(int a, int b){
    while (a>=b){
         a=a-b;
    }
    return a;
}

int div(int a,int b){
    int quotient =0;
    while((quotient +1)*b <=a){
        quotient =quotient+1;
    }
    return quotient;
}

void executeProgram(char *name){
    char buffer[13312];
	int i = 0;
    int exeSeg;
    char temp;
    int j=0;
    char debug[4];

    debug[0] = 'h';
    debug[1] = '\n';
    debug[2] = '\r';
    debug[3] = '\0';
/*    printString(debug);*/
    for(i = 0; i < 13312; i++){
        buffer[i] = '\0';
    }
    setKernelDataSegment();
    while(processTable[j].activeStatus!=0 && j<8){
        j++;
    }
    if(j>=8){
        printString("no free entry \0");
        return;
    }
    currentProcess=j;
    restoreDataSegment();
    debug[0] = j+0x30;
/*    printString(debug);*/
    readFile(name, buffer, &temp);
    debug[0] = j+0x30;
/*    printString(debug);*/
    exeSeg=j *(0x1000) + 0x2000;
    /* void putInMemory (int segment, int address, char character) */
    for(i = 0; i < 13312; i++){
        putInMemory(exeSeg, i, buffer[i]);
    }
    initializeProgram(exeSeg);
    setKernelDataSegment();
    processTable[j].processPtr = 0xff00;
    processTable[j].activeStatus = 1;
    processTable[j].waiting = j;
    restoreDataSegment();



    /*launchProgram(exeSeg);*/
}

void terminate(){
    char temp [12];
    int i = 0;
    temp[0] = 's';
    temp[1] = 'h';
    temp[2] = 'e';
    temp[3] = 'l';
    temp[4] = 'l';
    temp[5] = '\0';
    temp[6] = '\0';
/*    interrupt(0x21, 0, temp, 0, 0);*/
    /*interrupt(0x21, 4, temp, 0, 0);*/
    setKernelDataSegment();
    for (i = 0; i < 8; i++){
        if (processTable[i].waiting == currentProcess){
            processTable[i].waiting = i;
        }
    }
    temp[0] = currentProcess + 0x30;
    restoreDataSegment();
/*    printString(temp);*/
    setKernelDataSegment();
    processTable[currentProcess].activeStatus=0;
    while(1);
/*    interrupt(0x21, 4, temp, 0, 0);*/
}

void deleteFile(char* name){
    char directory[512];
    int i;
    int j;
    readSector(directory, 2);

    for (i=0; i<16; i++){
        for(j=0; j<6; j++){
            char test[2];
            test[1] = '\0';
            test[0] = 0x30 + i;
/*            interrupt(0x21, 0, test, 0, 0);*/
            if(directory[32*i+j]!= name[j]){
                break;
            }else if (j==5){
                int m=0;
                char map[512];
                directory[32*i] = 0;
                writeSector(directory, 2);
                readSector(map, 1);
                j=6;
                test[1] = 'f';
/*                interrupt(0x21, 0, test, 0, 0);*/
                while (directory[32*i+j]!=0){
                    map[directory[32*i+j]] = 0;
                    writeSector(map, 1);
                    j++;
                }
            }
        }
    }
}

void writeFile(char* name, char* buffer, int numberOfSectors){
    char mapBuffer[512];
    char directoryBuffer[512];
    int i,j,m;
    int numName;
    readSector(mapBuffer, 1);
    readSector(directoryBuffer, 2);


    for (i=0; i<16; i++){

            if(directoryBuffer[32*i]!=0){
                continue;
            }else {
                j = 0;
                while (name[j] != '\0' && j < 6){
                    directoryBuffer[32*i+j]= name[j];
                    j++;
                }
                while(j < 6){
                    directoryBuffer[32*i+j]= 0;
                    j++;
                }
                break;
            }
    }
    m = 0;
            while(numberOfSectors > 0){
                for(j = 0; j < 512; j++){
                    if (mapBuffer[j] == 0){
                        directoryBuffer[32*i+6+m] = j;
                        mapBuffer[j] = 0xFF;

                        writeSector(buffer+512*m, j);
                        m++;
                        numberOfSectors--;
                        break;
                    }
                }

            }
        for (m = 0; m < 26; m++){
            directoryBuffer[32*i+m];
        }
            writeSector(mapBuffer, 1);
            writeSector(directoryBuffer, 2);



    return;
}

void handleTimerInterrupt(int segment, int sp){
    int m = 0;
    char temp [4];
    int newSegment = segment, newSp = sp;
    setKernelDataSegment();
    temp[0] = 'T';
    temp[1] = 'i';
    temp[2] = 'c';
    temp[3] = '\0';
/*    printString(temp);*/
    timerCounter++;
    currentProcess = div(segment, 0x1000) - 2;
    temp[0] = currentProcess + 0x30;
/*    printString(temp);*/

    processTable[currentProcess].processPtr = sp;

    currentProcess++;
    while(processTable[currentProcess].activeStatus!=1 || processTable[currentProcess].waiting!=currentProcess){
        currentProcess++;
        m++;
        if (m > 8){
/*            printString(temp);*/
            restoreDataSegment();
            returnFromTimer(segment, sp);
            break;
        }
        if (currentProcess >= 8)
            currentProcess = 0;

    }
    newSp = processTable[currentProcess].processPtr;
    newSegment = currentProcess * 0x1000 + 0x2000;
    temp[0] = currentProcess + 0x30;
    temp[1] = '\n';
    temp[2] = '\r';
    restoreDataSegment();
/*    printString(temp);*/
    returnFromTimer(newSegment, newSp);
/*    returnFromTimer(segment, sp);*/
}

void getTimeCounter(int *time){
    int temp = 0;
    setKernelDataSegment();
    temp = timerCounter;
    restoreDataSegment();
    *time = temp;
}
void delay(int time){
    int a = 0;
    int temp = 0;
    int cnt = time;
    setKernelDataSegment();
    a = timerCounter;
    restoreDataSegment();
    while(1){
        setKernelDataSegment();
        temp = timerCounter;
        restoreDataSegment();
        if (temp - a > 19)
            cnt--;
        if(cnt <= 0)break;
    }
}

void printHexNum(char num){
    char out[3];
    char num0, num1;
    out[0] = 0;
    out[1] = 0;
    out[2] = '\0';
    num0 = div(num, 16);
    if (num0 >= 0 && num0 <= 9){
        out[0] = num0 + 0x30;
    } else
        out[0] = num0 - 10 + 'A';
    num1 = mod(num, 16);
    if (num1 >= 0 && num1 <= 9){
        out[1] = num1 + 0x30;
    } else
        out[1] = num1 - 10 + 'A';
    printString(out);

}

void enableGraphics(){
    char debug[3];
    debug[2] = '\0';
    debug[1] = 'G';
    debug[0] = 'E';
    printString(debug);
    delay(3);
    interrupt(0x10, 4, 0, 0, 0);
}

void drawPixel(int x, int y, int color){
    interrupt(0x10, color, 0, x, y);
}

void disableGraphics(){
    interrupt(0x10, 3, 0, 0, 0);
}

void scrollDown(char numRows){

    interrupt(0x10, 0x0700+numRows, 0x0f00, 0, 256*200+320);
}

void scrollUp(char numRows){

    interrupt(0x10, 0x0600+numRows, 0x0f00, 0, 256*200+320);
}

void clean(){
    interrupt(0x10, 3, 0, 0, 0);
}

void setCursorPos(char x, char y){
    interrupt(0x10, 0x0200, 0, 0, y*256+x);
}
