/* Author:
    Donglai Guo, Zesun Yang and Zhihong Zhai Team 1E
    Created on 01/31/18
*/

void printHexNum(char num);
int mod(int a, int b);
int div(int a,int b);
void fillBox(int x1, int y1, int x2, int y2, int color);
void printHelp(int x);

int main(){
    char command[512];
    int i = 0;
    enableInterrupts();
    while(1){
      for (i = 0; i < 512; i++){
        command[i] = '\0';
      }
      interrupt(0x21, 0, "SHELL>\r\n\0", 0, 0);
      interrupt(0x21, 1, command, 0, 0);
      i = 0;
      if (command[0] == 't' && command[1] == 'y' &&
        command[2] == 'p' && command[3] == 'e' &&
        (command[4] == '\n' || command[4] == '\r' || command[4] == ' ')) {
        char fileBuffer[13312];
        for (i = 0; i < 13312; i++){
            fileBuffer[i] = '\0';
        }
        if (command[4] != '\n' && command[4] != '\r'){
            char j = 0;
            interrupt(0x21, 3, &command[5], fileBuffer, &j);
            interrupt(0x21, 0, fileBuffer, 0, 0);
        }

      }else if (command[0] == 'e' && command[1] == 'x' &&
        command[2] == 'e' && command[3] == 'c'
        && command[4] == 'u' && command[5] == 't'
        && command[6] == 'e' &&
        (command[7] == '\n' || command[7] == '\r' || command[7] == ' ')){
        if (command[7] != '\n' && command[7] != '\r'){
            interrupt(0x21, 4, &command[8], 0, 0);
        }

/*            interrupt(0x21, 5, 0, 0, 0);*/

      }else if (command[0] == 'd' && command[1] == 'e' &&
        command[2] == 'l' && command[3] == 'e'
        && command[4] == 't' && command[5] == 'e'
        && (command[6] == '\n' || command[6] == '\r' || command[6] == ' ')){
        if (command[6] != '\n' && command[6] != '\r'){
            interrupt(0x21, 7, &command[7], 0, 0);
        }

/*            interrupt(0x21, 5, 0, 0, 0);*/

      }else if (command[0] == 'c' && command[1] == 'o' &&
        command[2] == 'p' && command[3] == 'y'
        && (command[4] == '\n' || command[4] == '\r' || command[4] == ' ')){
        if (command[4] != '\n' && command[4] != '\r'){
            int i = 0;
            while(command[5 + i] != ' '){
                i++;
            }
            command[5 + i] = '\0';
            if (command[5 + i + 1] != '\n' || command[5 + i + 1] != '\r'){
                char j;
                char fileBuffer[13312];
                interrupt(0x21, 3, &(command[5]), fileBuffer, &j);

                interrupt(0x21, 8, &(command[5 + i + 1]), fileBuffer, j);
            }

        }

/*            interrupt(0x21, 5, 0, 0, 0);*/

      }else if (command[0]=='d' && command[1]=='i'
      && command[2]=='r'&& (command[3]=='\n' ||
      command[3] == '\r' || command[3]==' ')){

            char bufferDir[512];
            char temp[7];
            int z=0;
            int w=0;
            char countB[3];
            int count;
            int tenCount;
            interrupt(0x21, 2, bufferDir, 2,0);
            for(z=0;z<16; z++){
                if (bufferDir[32*z]==0)
                    continue;
                for(w=0;w<6;w++){
                    if (bufferDir[32*z+w] == '\n' ||bufferDir[32*z+w] == '\r'){
                      temp[w] = '\0';
                      continue;
                    }

                    temp[w]=bufferDir[32*z+w];

                }
                count=0;

                for(w=6; w<32; w++){
                    if(bufferDir[32*z+w]!=0){
                        count++;
                    }
                }
                tenCount=0;
                if(count>=10){
                    while(count>=10){
                        tenCount++;
                        count=count-10;
                    }
                    countB[0]=tenCount+ 0x30;
                    countB[1]=count + 0x30;
                    countB[2]='\0';
                }else{
                    countB[0]=count + 0x30;
                    countB[1]='\0';
                    countB[2]='\0';
                }
                temp[6]='\0';
                interrupt(0x21, 0,temp,0,0);
                interrupt(0x21, 0, "   size:", 0,0);
                interrupt(0x21, 0, countB,0,0);
                interrupt(0x21,0,"\r\n\0",0,0);
            }

        }else if (command[0] == 'c' && command[1] == 'r' &&
          command[2] == 'e' && command[3] == 'a' && command[4] == 't' && command[5] =='e'
          && (command[6] == '\n' || command[6] == '\r' || command[6] == ' ')){
           int i = 0, j = 0, acc = 0;
           char buffer[13312];
           char content[13312];
               while(1){
                   for (j = 0; j < i; j++){
                       buffer[j] = 0;
                   }
                   i = 0;
                   interrupt(0x21, 1, buffer, 0, 0);
                   if(buffer[0] =='\n' || buffer[0] == '\r'){
                       break;
                   }
                   while(buffer[i]!='\0'){
                       content[acc + i] = buffer[i];
                       i++;
                   }
                   acc += i;
               }
               i = 1;
               while(acc > 512){
                   acc -= 512;
                   i++;
               }
               interrupt(0x21, 8, &(command[7]), content, i);


        }else if(command[0] == 'k' && command[1] == 'i' &&
        command[2] == 'l' && command[3] == 'l' &&
        (command[4] == '\n' || command[4] == '\r' || command[4] == ' ')){
            if (command[4] != '\n' && command[4] != '\r'){
            if(command[5]-0x30>=8 || command[5]-0x30<0){
                interrupt(0x21, 0, "No such process, enter 0-7!\r\n\0", 0, 0);
                continue;
            }
            interrupt(0x21, 9, command[5]-0x30, 0,0);
        }

            }else if(command[0] == 'e' && command[1] == 'x' &&
        command[2] == 'e' && command[3] == 'c' && command[4] == 'f' && command[5] == 'o'
        && command[6] == 'r' && command[7] == 'e' &&command[8] == 'g' &&command[9] == 'r'
        && command[10] == 'o' && command[11] == 'u' && command[12] == 'n' && command[13] == 'd' &&
        (command[14] == '\n' || command[14] == '\r' || command[14] == ' ')){
              if (command[14] != '\n' && command[14] != '\r'){
                 interrupt(0x21,10, &command[15],0,0);
              }
            }
            else if (command[0] == 'q' && command[1] == 'u' &&
        command[2] == 'i' && command[3] == 't' &&
        (command[4] == '\n' || command[4] == '\r' || command[4] == ' ')) {
              interrupt(0x21, 0, "Bye!", 0, 0, 0);
              break;



            }else if (command[0]=='h' && command[1]=='e' && command[2]=='l'
             && command[3]=='p' && (command[5]=='\n' || command[5]=='\r'
             || command[5]==' ')){
                char temp = 0;
                int num2 = 34;
                int num;
                for (num = 0; num < num2; num++){
                  printHelp(num);
                }
                num = num2-25;
                while(1){
                  interrupt(0x21, 19, &temp, 0, 0);
                  if (temp == 'q')break;
                  if (temp == 'w'){
                    interrupt(0x21, 20, 1, 0, 0);
                    interrupt(0x21, 23, 0, 0, 0);
                    printHelp(num);
                    num--;
                    num2--;
                  }
                  if (temp == 's')
                    {
                      interrupt(0x21, 21, 1, 0, 0);
                      interrupt(0x21, 23, 0, 23, 0);
                      printHelp(num2);
                      num++;
                      num2++;
                    }

                }
                interrupt(0x21, 22, 0, 0, 0);


            } else if (command[0] == 'c' && command[1] == 'l' &&
          command[2] == 'e' && command[3] == 'a' && command[4] == 'r'
          && (command[5] == '\n' || command[5] == '\r' || command[5] == ' ')){
              clear();
              interrupt(0x21, 0, "\r\n\0", 0, 0);
            } else if(command[0] == 'c' && command[1] == 'h' &&
          command[2] == 'a' && command[3] == 'n' && command[4] == 'g' &&
          command[5] == 'e' && command[6] == 'b' && command[7] == 'g' &&
          (command[8] == '\n' || command[8] == '\r' || command[8] == ' ')){
              int color=0;
              if(command[9] == 'y' && command[10] == 'w'){
                color = 14;
              } else if(command[9]=='b' && command[10] == 'l'){
                color = 9;
              } else if(command[9]=='l' && command[10] == 'm'){
                color = 13;
              } else if(command[9]=='r' && command[10] == 'd'){
                color = 4;
              } else if(command[9]=='g' && command[10] == 'n'){
                color = 2;
              } else if(command[9]=='b' && command[10] == 'k'){
                color = 0;
              } else if(command[9]=='w' && command[10] == 'h'){
                color = 15;
              }

              interrupt(0x21, 11, 0x0b00, color,0,0);
            } else if(command[0] == 'c' && command[1] == 'h' &&
          command[2] == 'a' && command[3] == 'n' && command[4] == 'g' &&
          command[5] == 'e' && command[6] == 'f' && command[7] == 'g' &&
          (command[8] == '\n' || command[8] == '\r' || command[8] == ' ')){
              int color=0;
              if(command[9] == 'y' && command[10] == 'w'){
                color = 14;
              } else if(command[9]=='b' && command[10] == 'l'){
                color = 9;
              } else if(command[9]=='l' && command[10] == 'm'){
                color = 13;
              } else if(command[9]=='r' && command[10] == 'd'){
                color = 4;
              } else if(command[9]=='g' && command[10] == 'n'){
                color = 2;
              } else if(command[9]=='b' && command[10] == 'k'){
                color = 0;
              } else if(command[9]=='w' && command[10] == 'h'){
                color = 15;
              }

              interrupt(0x21, 13, 0x0700, color*256,0,0);
            }else if (command[0]== 'a' && (command[1] == '\n' || command[1] == '\r' || command[1] == ' ')){
              interrupt(0x21,12,command,0,0);
            }
            else if(command[0] == 't' && command[1] == 'i' &&
        command[2] == 'm' && command[3] == 'e' &&
        (command[4] == '\n' || command[4] == '\r' || command[4] == ' ')){
              int time = 0;
            interrupt(0x21, 15, &time, 0, 0);
              printHexNum(time>>8);
              printHexNum(time);


            }
            else if(command[0] == 'w' && command[1] == 'a' &&
        command[2] == 'i' && command[3] == 't' &&
        (command[4] == '\n' || command[4] == '\r' || command[4] == ' ')){
              int start = 0;
              interrupt(0x21, 0, "Start\n\r\0", 0, 0);
              interrupt(0x21, 15, &start, 0, 0);
/*              while(1){
                int temp = 0;
                interrupt(0x21, 15, &temp, 0, 0);
                if (temp - start > 40) break;
              }*/
              interrupt(0x21, 14, 0, 0, 0);
              interrupt(0x21, 0, "End\n\r\0", 0, 0);

            }
            else if(command[0] == 's' && command[1] == 'n' &&
        command[2] == 'a' && command[3] == 'k' && command[4] == 'e' &&
        (command[5] == '\n' || command[5] == '\r' || command[5] == ' ')){
                  char temp = 0;/*320*200*/
                  int x1 = 8, y1 = 0, x2 = 0, y2 = 0;
                  interrupt(0x21, 16, 0, 0, 0);
                  fillBox(0, 0, 39, 4, 2);
                  interrupt(0x21, 14, 1, 0, 0);
                  while(x1 < 63){
                    fillBox(x1*4, 0, x1*4+4, 4, 2);
                    fillBox((x1-8)*4, 0, (x1-8)*4+4, 4, 0);
                    x1++;
                    x2++;
                    interrupt(0x21, 14, 1, 0, 0);
                  }
                  while(y1 < 39){
                    fillBox(x1*4, y1*4, x1*4+4, y1*4+4, 2);
                    if(x2 < 63){
                      fillBox(x2*4, 0, x2*4+4, 4, 0);
                      x2++;
                    }else {
                      fillBox(x2*4, y2*4, x2*4+4, y2*4+4, 0);
                      y2++;
                    }
                    y1++;
                    interrupt(0x21, 14, 1, 0, 0);
                  }
                  while(x1>0){
                    fillBox(x1*4, y1*4, x1*4+4, y1*4+4, 2);
                    if (y2 < 39){
                      fillBox(x2*4, y2*4, x2*4+4, y2*4+4, 0);
                      y2++;
                    }else{
                      fillBox(x2*4, y2*4, x2*4+4, y2*4+4, 0);
                      x2--;
                    }
                    x1--;
                    interrupt(0x21, 14, 1, 0, 0);
                  }
                  while(y1 > 0){
                    fillBox(x1*4, y1*4, x1*4+4, y1*4+4, 2);
                    if (x2 > 0){
                      fillBox(x2*4, y2*4, x2*4+4, y2*4+4, 0);
                      x2--;
                    }
                    else {
                      fillBox(x2*4, y2*4, x2*4+4, y2*4+4, 0);
                      y2--;
                    }
                    y1--;
                    interrupt(0x21, 14, 1, 0, 0);
                  }
                  interrupt(0x21, 19, &temp, 0, 0);
                  interrupt(0x21, 18, 0, 0, 0);

            }
          else{
          interrupt(0x21, 0, "Bad Command!\r\n\0", 0, 0);
        }



      }
      interrupt(0x21, 5, 0, 0, 0);


    return 0;

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
    interrupt(0x21, 0, out, 0, 0, 0);

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

void fillBox(int x1, int y1, int x2, int y2, int color){
    int i = 0, j = 0;
    color = color & 0x00ff;
    color = color | 0x0c00;
    for (i = x1; i <= x2; i++){
        for(j = y1; j <= y2; j++){
            interrupt(0x21, 17, i, j, color);
        }
    }
}

void printHelp(int x){
  switch (x){
    case 0: interrupt(0x21, 0, "1. type (filename)  \r\n\0", 0, 0);break;
    case 1: interrupt(0x21, 0, "load the file to memory and print out content  \r\n\0", 0, 0);break;
    case 2: interrupt(0x21, 0, "========================\r\n\0", 0, 0);break;
    case 3: interrupt(0x21, 0, "2. execute (filename)\r\n\0", 0, 0);break;
    case 4: interrupt(0x21, 0, "execute a file \r\n\0", 0, 0);break;
    case 5: interrupt(0x21, 0, "========================\r\n\0", 0, 0);break;
    case 6: interrupt(0x21, 0, "3. delete (filename) \r\n\0", 0, 0);break;
    case 7: interrupt(0x21, 0, "delete the  file \r\n\0", 0, 0);break;
    case 8: interrupt(0x21, 0, "========================\r\n\0", 0, 0);break;
    case 9: interrupt(0x21, 0, "4. copy (filename1) (filename2) \r\n\0", 0, 0);break;
    case 10: interrupt(0x21, 0, "create a file named filename2 and copy all bytes from filename1 \r\n\0", 0, 0);break;
    case 11: interrupt(0x21, 0, "========================\r\n\0", 0, 0);break;
    case 12: interrupt(0x21, 0, "5. dir \r\n\0", 0, 0);break;
    case 13: interrupt(0x21, 0, "listing directory contents \r\n\0", 0, 0);break;
    case 14: interrupt(0x21, 0, "========================\r\n\0", 0, 0);break;
    case 15: interrupt(0x21, 0, "6. create (filename) \r\n\0", 0, 0);break;
    case 16: interrupt(0x21, 0, " allow user to create a text file \r\n\0", 0, 0);break;
    case 17: interrupt(0x21, 0, "========================\r\n\0", 0, 0);break;
    case 18: interrupt(0x21, 0, "7. kill (process#) \r\n\0", 0, 0);break;
    case 19: interrupt(0x21, 0, "kill the process according to the index num\r\n\0", 0, 0);break;
    case 20: interrupt(0x21, 0, "========================\r\n\0", 0, 0);break;
    case 21: interrupt(0x21, 0, "8. execforeground (filename) \r\n\0", 0, 0);break;
    case 22: interrupt(0x21, 0, "make the program wait untill current process finish running \r\n\0", 0, 0);break;
    case 23: interrupt(0x21, 0, "========================\r\n\0", 0, 0);break;
    case 24: interrupt(0x21, 0, "9. clear \r\n\0", 0, 0);break;
    case 25: interrupt(0x21, 0, "clear the terminal, with cool color text displayed \r\n\0", 0, 0);break;
    case 26: interrupt(0x21, 0, "========================\r\n\0", 0, 0);break;
    case 27: interrupt(0x21, 0, "10. quit \r\n\0", 0, 0);break;
    case 28: interrupt(0x21, 0, "Quit from the shell and disable input\r\n\0", 0, 0);break;
    case 29: interrupt(0x21, 0, "========================\r\n\0", 0, 0);break;
    case 30: interrupt(0x21, 0, "11. changebg/fg (2 letter color code) \r\n\0", 0, 0);break;
    case 31: interrupt(0x21, 0, "change the background/ foreground color of the shell\r\n\0", 0, 0);break;
    case 32: interrupt(0x21, 0, "bl-blue   yw-yellow  lm-magenta rd-red \r\n\0", 0, 0);break;
    case 33: interrupt(0x21, 0, "gn-green  bk-black wh-white \r\n\0", 0, 0);break;
    case 34: interrupt(0x21, 0, "========================\r\n\0", 0, 0);break;
    case 35: interrupt(0x21, 0, "12. snake \r\n\0", 0, 0);break;
    case 36: interrupt(0x21, 0, "when user typed snake in shell, a snake will show up and make truns. press anykey in the shell can return to shell. \r\n\0", 0, 0);break;
    case 37: interrupt(0x21, 0, "========================\r\n\0", 0, 0);break;
    case 38: interrupt(0x21, 0, "13. scroll\r\n\0", 0, 0);break;
    case 39: interrupt(0x21, 0, "When help is typed in shell, sometimes, the table is too long to show the entire thing. We added scroll function. Use w to scroll up and s to scroll down, q to quit helo menu. Only available under help.\r\n\0", 0, 0);break;
    case 40: interrupt(0x21, 0, "========================\r\n\0", 0, 0);break;
    case 41: interrupt(0x21, 0, "14. wait \r\n\0", 0, 0);break;
    case 42: interrupt(0x21, 0, "the user can type wait for wait for 1 second in the shell.\r\n\0", 0, 0);break;
    case 43: interrupt(0x21, 0, "========================\r\n\0", 0, 0);break;
    case 44: interrupt(0x21, 0, "15. type \r\n\0", 0, 0);break;
    case 45: interrupt(0x21, 0, "type time in shell will return the time tick in hex of the internal color \r\n\0", 0, 0);break;
    
    default: break;
  }
}