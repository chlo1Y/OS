/* author
    Donglai Guo, Zesun Yang and Zhihong Zhai Team 1E
    Created on 2/7/18
*/


Usage. boot the system using ./compileOs.sh

Note ** Extra features are documented  in seaction 6

1. Timer Interrupt 
    We perfromed timer interrupt first. It is very similar to interrupt 0x21 and the purpose of it is to back up all the registers and reinitialize the timer. We frist put makeTimerInterrupt at the end of main in kernel.c before launching shell. TimerInterrupt takes two arguement, a segment input in the form of integer, and a status pointer. 

    How we verify it:
     
    In kernel. c, the handeTimerInterrupt routine called printString to print "tic". and called returnFromTimer afterwards. It is is successful, then after compile, you will see a screen filled up with "tic"
    

2. Process Table
    In this section, we commented out printString and then we create a process table to get ready for multi-tasking. The table keeps track of whether a process is active or not as well as that process's stack pointer. 
    We then modified executeproragm to search through the process table for a free entry, set it to active and call launch program. 

    How we verify:
    This step cannot be fully tested by itslef. We need too complete the next step in order to throughtly test this step. Currently, what we did is to compile the code, and see no error messages. 


3. Load Program  and scheduling
    We want to make the program continue running while the new program runs for multitasking. Insetad of calling launch program, we called initializeProgram. We also modifed ternimate and added set kenerl data segment, enableInterrupts. Then the scheduler cna choose a program using round robin to look for anther process to run. 

    How we verifiy
    We compiled our operating system and checked the shell file was loaded correctly. Then we type "execute phello" to print "hello world" ten thousand times, and while it is printing, we can type other commands (for example, type "dir") and be bale to see their results. 


4. Kill Process
    We wrote the kill routine in kernel.c and implemented in shell command. It should terminal the targeted proess. If you entered "kill 3", then process 3 will be terminated. The idea of it to set the targeted process status to inactive, and prompt user for corrent process number if entered incorrectly. 
    
    How we verify it:
    after we compile the code, from shell, type "execute phello"
    then it should start printing messages. Quickly do a "kill 1" before all 10000 messages finsihes printing. Then you should immediately stop seeing "hello world"  and be able to type shell command normally. 


5. Process Blocking 
    execute currently run concurrently with shell. Our goal is to have shell stop executing temporarily while the new process is running. Then resume when new proess is terminated. We added a "waiting" state in the processtable to achieve processing blocking. 

    How we verfiy it:
    if we run "execforegound phello", then you run "dir" (or any other commant", you should not see the result of the other process untill the current process is finished. We have verfied that is functioing peoperly. 

6. Optional features 

    a. wrinting file sizes 
        when compile Os, user type "dir", and the size of the files in sectors will be printed on the screen. 
        Example: shell>> dir 
        kernel size :10
        message size :1 .......
    b. clear screen 
        when compiled OS and launched shell, if user types "clear" in the shell, contents in the window will be cleared. 
    c. Quit 
        after the shell is launched, if user types "quit" in the shell, then a message "bye" will be printed, and user cannot input tp the shell any more, unless the user starts a new shell. 
    d. help 
        after the shell is launched, if user types "help" in the shell, then a table of available functions  as well as information on how to use them will be printed to the screen. 
    e. color changing (background)
        After the shell is lanuched, if user tyeps "changebg + color code", then it is going to change the backgound color of the shell 
        We have 7 color options. example:nput "changebg bl" to change the color to blue. Available colors are listed as follows:
        bl-blue
        bk-black
        wh-white
        yw-yellow
        lm-magenta
        gn-green
        rd-red
    f. color changing (foreground)
        After the shell is lanuched, if user tyeps "changefg + color code", then it is going to change the text color in the shell. COlor code is similar to background change. 
    g. scroll
        When help is typed in shell, sometimes, the table is too long to show the entire thing. We added scroll function. Use "w" to scroll up and "s" to scroll down, "q" to quit helo menu. Only available under help.
    h. snake
        when user typed snake in shell, a snake will show up and make truns. press anykey in the shell can return to shell. 
    i. wait 
        the user can type wait for wait for 1 second in the shell.
    j. time
        type "time" in shell will return the time tick in hex of the internal color 
    

