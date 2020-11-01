#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>
#include <queue>
using namespace std;

int tickNum = 10;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; //静态初始化
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
bool ok = false;
sem_t sem;

void *sellTick(void *para)
{
	for (int i=0; i<tickNum; i++)
	{
		pthread_mutex_lock(&mutex);
		if (tickNum > 0)
		{
			tickNum--;
			string *who = (string *)para;
			//int *who = (int *)para;
			cout << *who << "卖出一张票,剩余" << tickNum << endl;
		}
		else
		{
			break;
		}
		pthread_mutex_unlock(&mutex);
	}
}

int testMultiThread()
{
	const int NUM = 4;
	//创建线程
	int flag;
	pthread_t tids[NUM];
	string name[NUM] = {"张","王","李","赵"};
	for (int i=0; i<NUM; i++)
	{
		flag = pthread_create(&tids[i], NULL, &sellTick, &name[i]);
		//flag = pthread_create(&tids[i], NULL, &sellTick, &i);
		if (flag != 0)
		{
			cout << "pthread_create error!" << endl;
			return flag;
		}
	}
	
	//等线程结束，回收
	for (int i=0; i<NUM; i++)
	{
		void *ans;
		flag = pthread_join(tids[i], &ans);
		if (flag != 0)
		{
			cout << "pthread_join error!" << endl;
			return flag;
		}
	}

	return 0;
}

//低效wait（忙轮询）
void *fbusywait(void *arg)
{
	while (!ok) 												//1.循环判断条件是否满足
	{
		cout << "wait.." << endl;
		sleep(1);													//2.不满足sleep
	}
	cout << "需要条件的操作" << endl;			//3.执行需要条件的操作
}

//高效wait模型（为避免接收不到信号，设计为双重判断(条件值+条件变量)）
void *fwait(void *arg)
{
//	sleep(3); //这个函数不管先后 都能到后续操作
	pthread_mutex_lock(&mutex); 				//1.互斥锁加锁
	if (!ok) 														//2.if判断条件是否满足
	{
		cout << "wait.." << endl;
		pthread_cond_wait(&cond, &mutex); //3.不满足阻塞等待条件变量（cond_wait函数会自动释放mutex 以引发另一处执行）
	}
	cout << "需要条件的操作" << endl;			//4.执行需要条件的操作
}

//signal模型（如果pthread_cond_wait没在阻塞等待中，发的信号无效）
void *fset(void *arg)
{
	sleep(2);
	pthread_mutex_lock(&mutex);					//1.加互斥锁
	ok = true;													//2.设置条件
	pthread_mutex_unlock(&mutex);				//3.互斥锁解锁
	pthread_cond_signal(&cond); 				//4.条件变量发信号
}

void testThreadCond()
{
	pthread_t pt1;
	pthread_create(&pt1, NULL, &fwait, NULL);

	pthread_t pt2;
	pthread_create(&pt2, NULL, &fset, NULL);

	pthread_join(pt1, NULL);
	pthread_join(pt2, NULL);
}

std::queue<int> qImg;

//生产者
void *fproducer(void *arg)
{
	for (int i=0; i<5; i++)
	{
		sleep(1);
		qImg.push(i);
		cout << "生产+" << i << endl;
		sem_post(&sem);
	}
}

//消费者
void * fconsumer(void *arg)
{
	while (1)
	{
		if (sem_wait(&sem) == 0)
		{
			cout << "消费-" << qImg.front() << endl;
			qImg.pop();
		}
		sleep(2);
	}
}

void testSem()
{
	sem_init(&sem, 0, 0);

	pthread_t pt1;
	pthread_create(&pt1, NULL, &fproducer, NULL);
	pthread_t pt2;
	pthread_create(&pt2, NULL, &fconsumer, NULL);

	pthread_join(pt1, NULL);
	pthread_join(pt2, NULL);

	//sem_destory(&sem); 编译不过（man找不到）
}

//创建守护进程
void createDeamon()
{
	//1.创建子进程，父进程退出
	pid_t pid = fork();
	if (pid < 0)
	{
		cout << "fork error!" << endl;
		exit(1);
	}
	else if (pid > 0) //父进程
	{
		exit(0);
	}

	//释放子进程从父进程复制过来的资源
	//2.子进程创建新会话
	setsid();

	//文件相关
	//3.改变工作目录
	chdir("/tmp");
	//4,重设文件权限掩码
	umask(0);
	//5.关闭所有文件描述符
	for (int i=0; i<getdtablesize(); i++)
	{
		close(i);
	}

	//开始工作
	while (1)
	{
		FILE *f = fopen("deamon.log", "a+");
		char szText[] = "hellodeamon ";
		fwrite(szText, strlen(szText), 1, f);
		sleep(5);
		fclose(f);
	}
}

int main()
{
	//testMultiThread();
	//testThreadCond();
	testSem();
	//createDeamon();
}
