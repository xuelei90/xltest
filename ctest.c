#include <stdio.h>
#include <string.h>

#define _TIMES_PER_MINUTE_ 140
#define _VERSION_NAME_ "demo V1.1"

typedef unsigned int UINT;

typedef int (*PFunCallBack)(const char *pMsg, unsigned int nMsgLen); //函数指针

void testDefine()
{
	printf("%d\n", _TIMES_PER_MINUTE_);
	printf("%s\n", _VERSION_NAME_);
	UINT a = 10;
	printf("%u\n", a);
}

//RedisSubCommand函数的参数有一个PFunCallBack类型的回调函数，这样写起来更清晰
int RedisSubCommand(const char *szKey, PFunCallBack pfun, bool onlyOne)
{
	printf("%s %d，", szKey, onlyOne);
	int rtn = pfun("结果msg", 5);
	printf("返回：%d\n", rtn);
}

int testC()
{
	printf("testc----------\n");

	char cData = 't';
	printf("%c\n", cData);
	printf("sizeof(char):%lu\n", sizeof(cData));

	int iIndex = 4;
	printf("%d %p\n", iIndex, &iIndex); //整型变量地址
	int * lpIndex = &iIndex; //整型指针正确定义赋值
	printf("%p %d\n", lpIndex, *lpIndex);

	long lData = 23445234;
	printf("%ld\n", lData);
	long long llData = 3454654646463454;
	printf("%lld\n", llData);

	float fData = 9.3;
	printf("%f\n", fData);
	double dData = 998;
	printf("%lf\n", dData);

	int aData[3] = {1,2,3};
	printf("%d %d\n", aData[0], aData[1]);
	printf("%p\n", aData);
	printf("sizeof(int[]):%lu\n", sizeof(aData));
	printf("%p %p %p %p\n", aData, &aData[0], &aData[1], &aData[2]);

	char szData[10] = "abcdefg";
	printf("%s %p %p\n", szData, szData, &szData); //字符串abc地址，字符串abc地址
	printf("%c\n", szData[1]);
	printf("sizeof(char[]):%lu\n", sizeof(szData));
	printf("strlen(szData):%lu\n", strlen(szData));
	printf("%c\n", szData[7]); //'\0'
	printf("%s\n", szData+1);

	//char * lpData = "hello"; //#错误写法 不能指向常量，应该指向字符数组
	//printf("%s %p %p\n", lpData, lpData, &lpData); //hello 常量内存区 栈内存

	char * lpData2 = szData;
	printf("%s %p %p\n", lpData2, lpData2, &lpData2);	//字符串abc地址，指针变量地址
	printf("%s\n", lpData2+1);

	return 0;
}

void testArray()
{
	//数组
	int iData[5] = {1,2,3,4,5};
	for (int i=0; i<5; i++)
	{
		printf("%d ", iData[i]);
	}
	printf("\n");
	printf("%p %p\n", iData, &iData); //iData是首元素地址，&iData是数组地址 这里相等
	printf("sizeof(int a[5]):%lu\n", sizeof(iData));
	//int *pData = &iData; //#错误写法 定义变量应该用数组指针类型
	int (*pData)[5] = &iData; //数组指针正确定义赋值（可参考整型）
	//int (*pData)[5] = iData; //#错误写法 iData是int*类型
	printf("%p %p\n", pData, iData);

	//看优先级()>[]>*，优先级高的是【中心词】
	int *p1[5];		//先[] p1是个数组，包含5个int *类型数据（指针数组）
	int (*p2)[5]; //先() p2是个指针，指向一个包含5个int类型数据的匿名数组（数组指针）
	int *pInt;
	printf("%lu %lu %lu\n", sizeof(pInt), sizeof(p2), sizeof(p1));
	
	//数组指针
	int a[5] = { 1, 2, 3, 4, 5 };
	int (*p)[5];
	p = &a;
	printf("%p\n", a); //输出数组名，一般用数组的首元素地址来标识一个数组，则输出数组首元素地址
	printf("%p\n", p); //根据上面，p为数组a的地址，输出数组a的地址
	printf("%p\n", *p); //*p表示数组a本身，一般用数组的首元素地址来标识一个数组
	printf("%p\n", &a[0]); //a[0]的地址
	printf("%p\n", &a[1]); //a[1]的地址
	printf("%p\n", p[0]); //数组首元素的地址
	printf("%d\n", **p); //*p为数组a本身，即为数组a首元素地址，则*(*p)为值，当*p为数组首元素地址时，**p表示首元素的值1
	printf("%d\n", *p[0]); //根据优先级，p[0] 表示首元素地址，则*p[0]表示首元素本身，即首元素的值1
	printf("%d\n", *p[1]); //为一个绝对值很大的负数，不表示a[1]...表示什么我还不知道

	//指针数组
	int *q[2];
	int x = 1, y = 2;
	q[0] = &x;
	q[1] = &y;
	printf("%p %p\n", q[0], &y);
	printf("%d %d\n", *q[0], *q[1]);

	//总结
	int ia = 10;
	int *pia = &ia;
	printf("%p %p %d\n", pia, &ia, *pia);
	int arr[5] = {1, 2, 3, 4, 5};
	int (*parr)[5] = &arr;
	printf("%p %p\n", parr, &arr);

	//移动
	printf("%d %d\n", arr[1], *(arr+1));
	int *m = &arr[0]; //等效于 int *m = arr;
	int *n = m + 2;
	printf("%d %d\n", *m, *n);

	//越界访问
	printf("越界：%d\n", arr[10]);
}

typedef struct SInfo
{
	char szName[8+1]; //12byte 4字节对齐
	int iAge; //4byte
	char szAddr[8+1]; //12byte 4字节对齐
}*pSInfo;

void testStruct()
{
	SInfo stInfo, astInfo[3], *alpstInfo[3];
	SInfo &refstInfo = stInfo;
	SInfo *lpstInfo = &stInfo;
	printf("sizeof:%lu, %p %p %p %p\n", sizeof(stInfo), &stInfo, &refstInfo, lpstInfo, &lpstInfo);
	pSInfo lpstInfo2 = &stInfo;
	strcpy(lpstInfo2->szName, "xue");
	printf("%s %s\n", lpstInfo2->szName, stInfo.szName);
}

int funMsgShow(const char *pMsg, unsigned int nMsgLen)
{
	printf("被调啦：%s %d 咱可以展现\n", pMsg, nMsgLen);
	return nMsgLen+1;
}

int funMsgModel(const char *pMsg, unsigned int nMsgLen)
{
	printf("被调啦：%s %d 咱可以创建模型\n", pMsg, nMsgLen);
	return nMsgLen+2;
}

int testFile()
{
	//打开
	FILE *fp = fopen("file.txt", "a+");
	if (fp == NULL)
	{
		printf("fopen() error");
		return -1;
	}

	//写
	char szText[12+1] = "hellotext ";
	int count = fwrite(szText, strlen(szText), 1, fp);
	if (count != 1)
	{
		printf("fwrite() error");
		return -1;
	}

	//读
	//rewind(fp); //写完再读就需要重新定位到文件头，等价fseek到0
	fseek(fp, 0, SEEK_SET); //SEEK_SET,SEEK_CUR,SEEK_END
	while (!feof(fp))
	{
		char szContent[24+1];
		memset(szContent, 0x00, sizeof(szContent)); //一定要先清空缓冲区
		fread(szContent, sizeof(szContent)-1, 1, fp);
		//szContent[sizeof(szContent)-1] = '\0';
		printf("读一段：%s\n", szContent);
	}
	
	//关闭
	fclose(fp);
	return 0;
}

int getFileLen()
{
	FILE *fp = fopen("file.txt", "r+");
	if (fp == NULL)
	{
		return -1;
	}
	
	//先定位到尾部，再获取位置
	fseek(fp, 0, SEEK_END);
	int len = ftell(fp);
	printf("fileLen:%d\n", len);

	//替换一段内容
	fseek(fp, 10, SEEK_SET);
	fwrite("xxxxx", 5, 1, fp);

	//其他操作：定位到头部 读取内容，动态分配内存存储

	fclose(fp);
	return len;
}

int main()
{
	//RedisSubCommand("key", funMsgModel, true);
	getFileLen();
	return 0;
}

