#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <ctype.h>

int lc = 0; 
int prev_lc = 0;
FILE *ptr,*p;
char c; 
int n = 0;
char *base_reg;
int base_lc=0;
int base = 0;

int pass2_lc=0; 
int potSearch(char str[]); 
int motSearch(char str[]); 
int symbol_table_lc(char str[]);

typedef struct
{
	char mnemonic[10]; 
	int length;
}mot;

typedef struct
{
 	char pseudo[20]; 
}pot;

typedef struct
{
	char symbol[20]; 
	int lc_val; 
}st; 

st symbol_table[10];
mot m_table[10];
pot p_table[10];

void main()
{
	char str[1000];
	char words[50]; 
	int val; 
	int flag = 0;
	int j;
	ptr = fopen("pass2.txt","r");
	if(ptr == NULL)
	{
		printf("error"); 
		exit(1); 
	}
	strcpy(p_table[0].pseudo,"START");
	strcpy(p_table[1].pseudo,"BALR");
	strcpy(p_table[2].pseudo,"USING");
	strcpy(p_table[3].pseudo,"EQU");
	strcpy(p_table[4].pseudo,"DC");
	strcpy(p_table[5].pseudo,"DS");
	strcpy(p_table[6].pseudo,"END");

	strcpy(m_table[0].mnemonic,"L");
	m_table[0].length = 4;
	strcpy(m_table[1].mnemonic,"A");
	m_table[1].length = 4;
	strcpy(m_table[2].mnemonic,"ST");
	m_table[2].length = 4;
	strcpy(m_table[3].mnemonic,"BNE");
	m_table[3].length = 4;
	strcpy(m_table[4].mnemonic,"BR");
	m_table[4].length = 4;
	
	while(fscanf(ptr,"%s",str)==1)
	{
		flag = 0; 
		for(j=0;j<(int)(sizeof(str)/sizeof(str[0]));j++)
		{ 
			if((str[0] >= 'A'&& str[0] <='Z'))
			{
				flag = 1; 
			} 
		}
		if(flag == 1)
		{
			val = potSearch(str); 
			if(val == 1)
			{
				while( (c = getc(ptr)) != '\n' )
				{ 
					if(c ==EOF)
					{ 
						break; 
					} 
				}
			}
			else
			{
				val = motSearch(str); 
				if(val == 1)
				{
					while( (c = getc(ptr)) != '\n' )
					{ 
						if(c == EOF)
						{ 
							break;
						} 
					}

				}
				else
				{
					strcpy(symbol_table[n].symbol,str);
					symbol_table[n].lc_val = lc;
					fscanf(ptr,"%s",str); 
					val = potSearch(str);
					if(val == 0)
					{
						val = motSearch(str); 
					}
					while( (c = getc(ptr)) != '\n' )
					{ 
						if(c == EOF)
						{ 
							break; 
						} 
					}

					printf("%s\t%d\n",symbol_table[n].symbol,symbol_table[n].lc_val);
					n++; 
				}
			} 
		}
	}
	fclose(ptr);

//PASS 2
	p = fopen("prog.txt","r");
	printf("\nPass 2:\n");
	while(fscanf(p,"%s",str)==1)
	{
		if(strcmp(str,"USING")==0)
		{ 
			fscanf(p,"%s",str);
			if(strcmp(str,"*")==0) 
			{
				fscanf(p,"%s",str); 
				char temp[10]; 
				base_reg = strcpy(temp,str);
				base_lc = pass2_lc; 
				printf("Base Reg: %s || LC value: %d\n",base_reg, base_lc);

			} 
		}
		if(strcmp(str,"L")==0 || strcmp(str,"A")==0 ||strcmp(str,"ST")==0)
		{
			printf("%s ", str); 
			fscanf(p,"%s",str); 
			printf("%s ", str);
			fscanf(p,"%s",str); 
			int index = symbol_table_lc(str); 
			printf("%d(%s, %d)\n", symbol_table[index].lc_val, base_reg, base_lc);

		}
	}
	fclose(p); 
}
int motSearch(char str[])
{
	int i=0; 
	for(i=0;i<5;i++)
	{
		if(strcmp(m_table[i].mnemonic,str) == 0)
		{
			lc += m_table[i].length; 
			return 1; 
		} 
	}
	return 0; 
}
int potSearch(char str[])
{
	int i=0; 
	for(i=0;i<7;i++)
	{
		if(strcmp(p_table[i].pseudo,str) == 0)
		{
			if(strcmp(p_table[i].pseudo,"DC") ==0 || strcmp(p_table[i].pseudo,"DS") == 0)
			{
				fscanf(ptr,"%s",str); 
				if((str[0] >= 'A'&& str[0] <='Z'))
				{
					if(strcmp(str,"F") == 0)
					{
						lc += 4; 
					}
					else
					{
						lc += 2;
					} 
				}
				else
				{
					fscanf(ptr,"%s",str);
					if(strcmp(str,"F") == 0)
					{
						lc += 4; 
					}
					else
					{
						lc += 2; 
					} 
				} 
			}
			else
				if(strcmp(p_table[i].pseudo,"EQU") == 0)
				{
					fscanf(ptr,"%s",str); 
					symbol_table[n].lc_val = atoi(str);
				}
			return 1; 
		} 
	}
	return 0; 
}
int symbol_table_lc(char str[])
{
	int i=0; 
	for(i=0;i<5;i++)
	{
		if(strcmp(symbol_table[i].symbol, str) == 0)
		{
			return i; 
		} 
	}
	return 0; 
}
