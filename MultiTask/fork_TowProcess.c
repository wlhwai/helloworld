/*	函数／类型		头文件		说明
 *	fork()			unistd.h	父进程调用返回的值为子进程的PID，子进程调用返回值为0
 *	pid_t			sys/types.h	进程id类型	
 * */
#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>

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
		printf("this is sub process. the return value is %d, the PID is %d\n", pid, getpid());
	}
	else // 父进程得到的pid为子进程的PID
	{
		printf("this is main process.the return value is %d, the PID is %d\n", pid, getpid());
	}
	
	return pid;
}
