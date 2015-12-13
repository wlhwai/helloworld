/*	函数／类型		头文件		说明
 *  wait()			sys/wait.h	等待子进程结束或者收到指定信号	
 *  waitpid()		sys/wait.h	指定pid等待子进程
 * */
#include<stdio.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>

int main(int argc, char* argv[])
{
	pid_t pid, prt;
	char *FuncType = argv[1];
	if (argc != 2 || (*FuncType != '1' && *FuncType != '2'))
	{
		printf("parameter number is wrong, please check again.\n");
		return 0;
	}
	/*新建子进程*/
	pid = fork();
	/*根据pid区分父／子进程，进入不同分支*/
	if (pid < 0)
	{
		printf("apply sub process fail.\n");
	}
	else if (pid == 0) // 子进程得到的pid为0
	{	
		printf("this is sub process, which is going to sleep.\n");
		sleep(5);
		printf("this is sub process, which has waken up.\n");
	}
	else // 父进程得到的pid为子进程的PID
	{
		if (*FuncType == '1') //调用wait()
		{
			printf("this is main process, which is going to wait sub process return.\n");
			prt = wait(NULL);
			if (prt < 0) // 等待子进程结束失败
			{
				printf("try to wait sub process, but failed.\n");
			}
			else if (prt == pid) // 等待子进程成功
			{
				printf("sub process returned, main process is going to return.\n");
			}
		}
		else if (*FuncType == '2') //调用waitpid() with WNOHANG
		{
			do 
			{
				prt = waitpid(pid, NULL, WNOHANG);
				if (prt == 0) // 返回0，说明子进程没运行完
				{
					printf("waiting sub process return...And I can do something else.\n");
					sleep(1);
				}
			} while(prt == 0);
			if (prt == pid)
			{
				printf("thank god, sub process returned.\n");
			}
			else
			{
				printf("try to wait sub process, but failed.\n");
			}
		}
	}
	return 0;
}

