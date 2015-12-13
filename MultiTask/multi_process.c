/*	文件				文件说明
 *  multi_process		主进程创建两个子进程，第一个子进程运行 "ls -l"命令，另一个子进程等待5s并退出 
 * */
#include<stdio.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<stdlib.h>

int main(int argc, char* argv[])
{
	pid_t pchild1, pchild2, prt;
	char *FuncType = argv[1];
	//if (argc != 2 || (*FuncType != '1' && *FuncType != '2'))
	//{
	//	printf("parameter number is wrong, please check again.\n");
	//	return 0;
	//}
	/*新建子进程*/
	pchild1 = fork();
	/*根据pid区分父／子进程，进入不同分支*/
	if (pchild1  < 0)
	{
		printf("apply sub process fail.\n");
	}
	else if (pchild1  == 0) // 该子进程运行 "ls -l"命令
	{	
		printf("this is the first sub process, which is going to execute 'ls -l'.\n");
		if (execlp("ls", "ls", "-l", NULL) < 0)
		{
			printf ("execute 'ls -l' failed.\n");
		}
	}
	else // 父进程得到的pid为子进程的PID
	{
		pchild2 = fork();
		if (pchild2 < 0)
		{
			printf("apply sub process fail.\n");
		}
		else if (pchild2 == 0)
		{
			printf("this is the second sub process, which is going to sleep 5s.\n");
			sleep(5);
			printf("this is the second sub process, which has waken up.\n");
		}
		else
		{
			printf("this is main process, which is waiting the first process exit.\n");
			prt = waitpid(pchild1, NULL, 0);
			if (prt < 0)					
			{
				printf("wait first sub process fail.\n");
			} 
			else
			{
				printf("thsi is main process, the first sub process has exited.\n");
				do
				{
					prt = waitpid(pchild2, NULL, WNOHANG);
					if (prt == 0)
					{
						printf("this is main process, waiting the second process wake up...\n");
						sleep(1);
					}
				} while (prt == 0);
				if (prt < 0)
				{
					printf("wait second sub process fail.\n");
				}
				else
				{
					printf("this is main process, the second sub process has waken up.\n");
				}
			}
		}
	}
	return 0;
}

