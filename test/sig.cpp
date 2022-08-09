#if 0

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

void sighandler(int);

int main()
{
   signal(SIGINT, sighandler);

   while(1) 
   {
      printf("开始休眠一秒钟...\n");
      sleep(1);
   }

   return(0);
}

void sighandler(int signum)
{
   printf("捕获信号 %d，跳出...\n", signum);
   exit(1);
}

#else

#include <iostream>
#include <csignal>
#include <unistd.h>
 
using namespace std;
 
void signalHandler( int signum )
{
    cout << "Interrupt signal (" << signum << ") received.\n";
    // 清理并关闭, 终止程序
    exit(signum);
}
 
int main ()
{
    // 注册信号 SIGINT 和信号处理程序
    signal(SIGINT, signalHandler);  

    while(1)
    {
       cout << "Going to sleep...." << endl;
       sleep(1);
    }
 
    return 0;
}

#endif
