#include<stdio.h>
#include<stdlib.h>
#include<signal.h>

void sig_usr(int signo)
{
 if(signo == SIGUSR1)
     printf("received SIGUSR1\n");
 else if(signo == SIGUSR2)
     printf("received SIGUSR2\n");
 else
     printf("received signal %d\n",signo);
}

int main()
{
 if(signal(SIGUSR1,sig_usr)==SIG_ERR)
 {
   printf("cant catch SIGUSR1\n");
   exit(1);
 }
 if(signal(SIGUSR2,sig_usr)==SIG_ERR)
 {
   printf("cant catch SIGUSR2\n");
   exit(1);
 }

 if(signal(SIGTERM,sig_usr)==SIG_ERR)
 {
   printf("cant catch SIGTERM\n");
   exit(1);
 }
 while(1)
 {
     sleep(2);               // if pid == 0 sent to processes with same group id 
     kill(getpid(),SIGTERM); // if pid > 0 sent to the pid process;
     kill(getpid(),SIGUSR1);
//     raise(SIGUSR1);         // if pid < 0 sent to group id with abs value pid;
     raise(SIGUSR2);
     sleep(1); 
 }
}
