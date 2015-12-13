/*	函数／类型		头文件		说明
 *	exit()			stdlib.h	调用退出处理函数，清理I/O缓冲，调用exit()系统调用
 *  _exit()			unistd.h	调用exit()系统调用		
 * */
#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>

int main()
{
	pid_t pid;
	/*新建子进程*/
	pid = fork();
	/*根据pid区分父／子进程，进入不同分支*/
	if (pid < 0)
	{
		printf("apply sub process fail.\n");
	}
	else if (pid == 0) // 子进程得到的pid为0
	{	
		printf("\nthis is sub process. call _exit().\n");
		printf("this is buffer content.");
		_exit(0); // 该调用不会清空I/O，因此屏幕不会输出上一行
	}
	else // 父进程得到的pid为子进程的PID
	{
		printf("\nthis is main process. cal exit().\n");
		printf("this is buffer content.");
		exit(0);
	}

}
