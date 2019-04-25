#include<stdio.h>
#include<string.h>
void main()
{
	FILE *fp;
	char oneword[100];
	char c;
	int i;
	char *key[]={"int","void","include","if","else","while","printf","do","scanf","clrscr","getch"};
	char *deli[]={"#",";",",","(",")","{","}"};
	char *header[]={"<stdio.h>","<conio.h>","<string.h>","<ctype.h>"};
	char *operator[]={"=","+","-","%","&","*"};
	char *identifier[]={"a","b","c"};
	fp=fopen("lexanalyzer.txt","r");
	do
	{
		//printf("list of keywords");
		c=fscanf(fp,"%s",oneword);
		for(i=0;i<11;i++)
		{
			//c=fscanf(fp,"%s",oneword);
			if(strcmp(oneword,key[i])==0)
			{
				printf("keyword %s\n",oneword);
				break;
			}
		}

		for(i=0;i<7;i++)
		{
			if(strcmp(oneword,deli[i])==0)
			{
				printf("delimeter %s\n",oneword);
				break;
			}
		}
		for(i=0;i<4;i++)
		{
			if(strcmp(oneword,header[i])==0)
			{
				printf("header %s\n",oneword);
				break;
			}
		}
		for(i=0;i<6;i++)
		{
			if(strcmp(oneword,operator[i])==0)
			{
				printf("operator %s\n",oneword);
				break;
			}
		}
		for(i=0;i<3;i++)
		{
			if(strcmp(oneword,identifier[i])==0)
			{
				printf("identifier %s\n",oneword);
				break;
			}
		}
	}
	while(c!=EOF);

	fclose(fp);
}
