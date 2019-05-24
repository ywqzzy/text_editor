#include<unistd.h>
#include<termios.h>
#include<ctype.h>
#include<stdlib.h>
#include<stdio.h>


struct  termios orig_termios;
void disbaleRawMode() {
    tcsetattr(STDIN_FILENO,TCSAFLUSH, &orig_termios);
}


void enableRawMode() {
  tcgetattr(STDIN_FILENO, &orig_termios);

  atexit(disbaleRawMode);

  struct termios raw = orig_termios;
  raw.c_iflag &= ~(IXON);
  raw.c_lflag &= ~(ECHO | ICANON | ISIG);

  tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}



int main() {
    enableRawMode();
    char c;
    while(read(STDIN_FILENO, &c, 1) == 1 && c!='q') {
        if(iscntrl(c)) {
            printf("%d\n", c);
        } else {
            printf("%d ('%c') \n", c, c);
        }
    }
    printf("shit\n");
    return 0;
}

