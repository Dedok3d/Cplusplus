#include <stdio.h>
#include <termios.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
static struct termios stored_settings;
int count;
void set_keypress(void)
{
  struct termios new_settings;

  tcgetattr(0,&stored_settings);

  new_settings = stored_settings;
  new_settings.c_lflag &= (~ICANON & ~ECHO);
  newsettings.c_cc[VINTR] = 27;

  tcsetattr(0,TCSANOW,&new_settings);
  return;
}

void reset_keypress(void)
{
  tcsetattr(0,TCSANOW,&stored_settings);
  return;
}

void sigcatch(int sig)
{
	if(sig==SIGQUIT)
	{
		printf("Count = %d\n",count);
		reset_keypress();
		exit(0);
	}
	printf("\a");
	++count;
}

int main(void)
{
  set_keypress();
while(1){
  signal(SIGINT,sigcatch);
	signal(SIGQUIT,sigcatch);
}
  reset_keypress();
  return 0;
}
