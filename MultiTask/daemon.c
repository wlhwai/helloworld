/*	函数／类型		头文件		说明
 *	fork()			unistd.h	父进程调用返回的值为子进程的PID，子进程调用返回值为0
 *	pid_t			sys/types.h	进程id类型	
 * */
#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<string.h>
#include<sys/types.h>
#include<unistd.h>

int main()
{
	pid_t pid;
	int MAXFILE, i, fd;
	char* buf = "This is daemon process writing log...\n";
	/*新建子进程*/
	pid = fork();
	/*根据pid区分父／子进程，进入不同分支*/
	if (pid < 0)
	{
		printf("apply sub process fail.\n");
		exit(1);
	}
	else if (pid != 0) // 父进程退出
	{	
		printf("main process exit.\n");
	}
	else // 将子进程设置为守护进程
	{
		/*1. 创建新会话组*/
		setsid();
		/*2. 改变当前目录为目标目录*/
		chdir("/");
		/*3. 设置文件权限掩码*/
		umask(0);
		/*4. 关闭文件描述符*/
		MAXFILE = getdtablesize();
		for (i = 0; i < MAXFILE; i++)
		{
			close(i);
		}
		/*5. 守护进程开始工作*/
		for (i = 0; i < 5; i++)
		{
			if ((fd=open("/tmp/daemon.log", O_CREAT|O_WRONLY|O_APPEND, 0600)) < 0)
			{
				printf("Open file error.\n");
				exit(1);
			}
			write(fd, buf, strlen(buf)+1);
			close(fd);
			sleep(5);
		}
	}
	
	exit(0);
}
