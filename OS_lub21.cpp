#include <stdio.h>
#include <termios.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
const int DeleteCode = 063;
int bell_count = 0;
static struct termios stored_settings;

void set_keypress(void)
{
  struct termios new_settings;

  tcgetattr(0,&stored_settings);

  new_settings = stored_settings;
  new_settings.c_lflag &= (~ICANON & ~ECHO);
  new_settings.c_cc[VTIME] = 0;
  new_settings.c_cc[VMIN] = 1;

  tcsetattr(0,TCSANOW,&new_settings);
  return;
}

void reset_keypress(void)
{
  tcsetattr(0,TCSANOW,&stored_settings);
  return;
}
int main(void)
{
  set_keypress();
   char n;
  printf("You're here?  ");
while(1){
   n = putchar(getchar());
  printf(" \n");
  if(n == DeleteCode){
        printf( "\a");
            bell_count++;
 }
 if(n == EOF){
        printf("Oh, really?\n");
        reset_keypress();
        break;
 }
}
  reset_keypress();
  return 0;
}
