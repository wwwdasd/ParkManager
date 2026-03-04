#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<string.h>

void add(FILE* f);
void del(FILE* f);
void edit(FILE* f);
void list(FILE* f);

int main() {
	int start_sign,flag=1;
	//读写

	FILE* fr = NULL;
	fr = fopen("CarKey.txt", "r+");
	if (fr == NULL) {
		printf("提示：CarKey.txt不存在，已自动创建！\n");
		fr = fopen("CarKey.txt", "w+");
		if (fr == NULL) {
			printf("错误：文件创建失败，请检查权限！\n");
			return 1; // 异常退出
		}
	}

	while (flag)
	{
		printf("\t\t\t  停车场管理系统\n");
		printf("输入数字选择模式：\n\t1.增加车牌，2更改车牌，3.删除车牌，4.查询车牌，5.退出 \n");
		scanf("%d",&start_sign);

		switch (start_sign){
		case 1:
			add(fr);
			fflush(fr);
			fclose(fr);
			fr = fopen("CarKey.txt", "r+");
			break;
		case 2:
			edit(fr);
			fflush(fr);
			fclose(fr);
			fr = fopen("CarKey.txt", "r+");
			break;
		case 3:
			del(fr);
			fflush(fr);
			fclose(fr);
			fr = fopen("CarKey.txt", "r+");
			break;
		case 4:
			list(fr);
			fflush(fr);
			fclose(fr);
			fr = fopen("CarKey.txt", "r+");
			break;
		case 5:
			flag = 0;
			printf("程序退出");
			fclose(fr);
			break;
		default:
			flag = 0;
			printf("程序异常退出");
			fclose(fr);
			break;
		}
	}
	return 0;
}

void add(FILE* f)
{
	f = fopen("CarKey.txt", "a");
	char carKey[200];
	printf("请输入车牌：");
	scanf("%s",carKey);
	fprintf(f, "%s\n", carKey);
	printf("success\n");
	fflush(f);
}

void del(FILE* f)
{
	FILE* ftmp = fopen("tmp.txt", "w");
	char carKey[20];
	char buf[1024];

	if (ftmp == NULL)
	{
		ftmp = fopen("tmp.txt", "w");
	}

	printf("请输入要删除的车牌：");
	scanf("%s", carKey);

	rewind(f);

	while (fgets(buf, sizeof(buf), f))
	{
		if (!strstr(buf, carKey))
		{
			fputs(buf, ftmp);
		}
	}
	fclose(ftmp);
	fclose(f);

	remove("CarKey.txt");
	rename("tmp.txt", "CarKey.txt");
	printf("success\n");
	freopen("CarKey.txt", "r+", f);
}

void edit(FILE* f)
{
	//先调用删除在进行修改
	FILE* ftmp = fopen("tmp.txt", "w");
	char oldCarKey[200], newCarKey[200];
	char buf[1024];

	if (ftmp == NULL)
	{
		ftmp = fopen("tmp.txt", "w");
	}

	printf("请输入旧的车牌：");
	scanf("%s", oldCarKey);
	printf("请输入新的车牌：");
	scanf("%s", newCarKey);

	rewind(f);

	//调用删除
	while (fgets(buf, sizeof(buf), f))
	{
		if (!strstr(buf, oldCarKey))
		{
			fputs(buf, ftmp);
		}
	}
	//写入新车牌
	fprintf(ftmp, "%s", newCarKey);
	//关闭
	fclose(ftmp);
	fclose(f);

	remove("CarKey.txt");
	rename("tmp.txt", "CarKey.txt");
	printf("success\n");
	freopen("CarKey.txt", "r+", f);
}

void list(FILE* f) {
	rewind(f);
	char buf[1024];
	printf("车牌列表：\n");
	while (fgets(buf, sizeof(buf), f))
	{
		printf(buf);
	}
	printf("\n\nsuccess\n");
}

