#include<stdio.h>
#include<string.h>
#include<ctype.h>
int main() 
{
	FILE *fp;
	char inst[3][3]={"L","A","ST"}; 
	char dir[7][9] ={"START","END","ORIGINAL","EQU","LTORG","USING","BALR"};
	char full[2][2]={"F","H"};
	char def[2][3] = {"DC","DS"}; 
	char ch,word[10]; 
	int flag1,flag2,flag3,lc=0; 
	char symbol[10][10],right[2][4],left[2][4]; 
	int i,j,index=-1,btindex=-1; 
	int loc[10]; 
	int uloc[5];
	fp=fopen("pass1.txt","r");
	ch=fscanf(fp,"%s",word);
	while(ch!=EOF)
	{
		flag1=0; 
		flag2=0;
		flag3=0;
		for(i=0;i<3;i++) 
		{
			if(strcmp(word,inst[i])==0) 
			{
				flag1=1; 
				lc=lc+4; 
				break;
			} 
		}
		for(j=0;j<7;j++)
		{
			if(strcmp(word,dir[j])==0) 
			{
				flag2=1;
				if(strcmp(word,"USING")==0) 
				{
					btindex++; 
					fscanf(fp,"%s",left[btindex]);
					if(left[btindex][0]=='*') 
						uloc[btindex]=lc;
					fscanf(fp,"%s",right[btindex]); 
				} 
				break; 
			} 
		}
		for(j=0;j<2;j++) 
		{
			if(strcmp(word,def[j])==0) 
			{
				flag3=1; 
				fscanf(fp,"%s",word);
				if(strcmp(word,"F")==0) 
					lc = lc+4;
				else 
					lc = lc+2;
			} 
		}
		for(j=0;j<2;j++)
		{
			if(strcmp(word,full[j])==0) 
			{
				flag3=1; 
				break; 
			} 
		}
		if(!(isdigit(word[0]) || word[0]=='*' || word[0]=='\''|| word[0]==',' )) 
		{
			if(flag1==0 && flag2==0 && flag3==0) 
			{
				index++;
				strcpy(symbol[index],word);
				loc[index]=lc;
			}
		}
		ch=fscanf(fp,"%s",word); 
	}
	printf("Symbol\tLocation counter\n");
	for(i=0;i<=index;i++) 
		printf("%s\t%d\n",symbol[i],loc[i]);
	printf("\n\nBase register\tContents\n");
	for(i=0;i<=btindex;i++) 
	{
		printf("%s\t\t",right[i]); 
		if(left[i][0]=='*') 
			printf("%d\n",uloc[i]); 
		else
			printf("%s\n",left[i]); 
	}
	fclose(fp);
	return 0; 
}
