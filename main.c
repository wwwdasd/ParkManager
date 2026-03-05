#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

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
		printf("输入数字选择模式：\n\t1.增加车牌，2更改车牌，3.删除车牌，4.查询车牌，5.清空当前屏幕，6.退出 \n");
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
			system("cls");
			break;
		case 6:
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
	FILE* fa = fopen("CarKey.txt", "a");
	char carKey[200];
	printf("\n请输入车牌：");
	scanf("%s",carKey);

	rewind(f);
	char buf[1024];
	int flag=0;

	while (fgets(buf, sizeof(buf), f))
	{
		if (strstr(buf, carKey))
		{
			flag = 1;
			break;
		}
		else
		{
			flag = 0;
		}

	}

	//输入校验（车牌7位）
	if ( strlen(carKey) != 8 || strncmp("辽",carKey,1)) 
	{

		printf("\n** 请输入正确车牌 **\n");
	}
	else if (flag == 1)
	{
		printf("\n** 车牌已存在 **\n");
	}
	else
	{
		fprintf(fa, "%s\n", carKey);
		printf("success\n");
	}

	fflush(fa);
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

	printf("\n请输入要删除的车牌：");
	scanf("%s", carKey);

	//车牌校验
	if (strlen(carKey) == 8 || !strncmp("辽", carKey, 1))
	{
		//查找是否存在，借用list();

		rewind(f);
		char buf[1024];
		int flag = 0;

		while (fgets(buf, sizeof(buf), f))
		{
			if (strstr(buf, carKey)) 
			{
				flag = 1;
				break;
			}
			else
			{
				flag = 0;
			}

		}

		if (flag==1)
		{
			//指针回到文件最前端
			rewind(f);

			//删除确认
			printf("确认删除吗 Y/N :");
			getchar();
			char YN;
			scanf("%c", &YN);

			switch (YN)
			{
				case 'Y':
				case 'y':

					rewind(f);

					while (fgets(buf, sizeof(buf), f))
					{
						if (!strstr(buf, carKey))
						{
							fputs(buf, ftmp);
						}
					}
					printf("success\n");
					break;

				default:
					printf("\n取消删除\n");
					break;
			}
		}
		else
		{
			printf("\n**未找到该车牌，请确认车牌是否正确**\n\n");
		}
		
	}
	else 
	{
		printf("\n** 请输入正确车牌 **\n");
	}

	fclose(ftmp);
	fclose(f);

	remove("CarKey.txt");
	rename("tmp.txt", "CarKey.txt");
	

	f = fopen("CarKey.txt", "r+");

	fflush(f);
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

	printf("\n请输入旧的车牌：");
	scanf("%s", oldCarKey);
	printf("\n请输入新的车牌：");
	scanf("%s", newCarKey);

	rewind(f);
	int flag = 0;

	while (fgets(buf, sizeof(buf), f))
	{
		if (strstr(buf, newCarKey))
		{
			flag = 1;
			break;
		}
		else
		{
			flag = 0;
		}

	}

	rewind(f);
	if (strlen(newCarKey) != 8 || strncmp("辽", newCarKey, 1))
	{
		printf("\n** 请输入正确车牌 **\n");
	}
	else if (flag==1)
	{
		printf("\n** 该车牌已存在 **\n");
	}
	else
	{	
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
}

void list(FILE* f) {
	rewind(f);
	char buf[1024];
	printf("\n车牌列表：\n");
	while (fgets(buf, sizeof(buf), f))
	{
		printf(buf);
	}
	printf("\n\n\n");
}