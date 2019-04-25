#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct{
	int mdtc;
	char macro[4][3][5];
}mdt;

typedef struct{
	char macro_name[5];
	int mntc;
}mnt;

typedef struct{
	char index[3];
	char arg[3];
}ala_1;

typedef struct{
	char index[3];
	char arg[3];
}ala_2;

mdt mdt_table;
mnt mnt_table;
ala_1 arg_list1[2];
ala_2 arg_list2[2];

FILE *ptr;
char *line = NULL;
ssize_t read;
size_t len = 0;
char buffer[15][5][10];
char string[10];
int i,j,val,prev_i,prev_j;
int macro_count = 0;
int line_count = 0;
int arg_index;

char *rstrip(char *str){
	int k;
	memset(string,0,strlen(string));
	for(k=0;k<strlen(str);k++){
		if(isalnum(str[k]) || str[k] == '&' || str[k] == '*'){
			string[k] = str[k];
		}
	}

	return string;
}

void prepareALA1(){
	int k;
	for(k=0;k<2;k++){
		sprintf(arg_list1[k].index,"#%d",k);
		strcpy(arg_list1[k].arg,buffer[i+1][j+k+1]);
	}
}

int getIndex(char *str){
	int k;
	for(k=0;k<2;k++){
		if(strcmp(arg_list1[k].arg,str) == 0){
			return k;
		}
	}
}

void printTables(){
	int k,n;
	printf("\nMNT:\n\n");
	printf("%s  %d\n",mnt_table.macro_name,mnt_table.mntc);

	printf("\nMDT:\n\n");
	for(k=0;k<4;k++){
		printf("%d",(k+1));
		for(n=0;n<3;n++){
			if(!isalnum(mdt_table.macro[k][n][0]) && mdt_table.macro[k][n][0] != '#'){
    			break;
    		}
			printf("  %s",mdt_table.macro[k][n]);
		}
		printf("\n");
	}
	
	printf("\nALA 1:\n\n");
	for(k=0;k<2;k++){
		printf("%s   %s\n",arg_list1[k].index,arg_list1[k].arg);
	}

	printf("\nALA 2:\n\n");
	for(k=0;k<2;k++){
		printf("%s   %s\n",arg_list2[k].index,arg_list2[k].arg);
	}
}

void prepareALA2(){
	int k;
	for(k=0;k<2;k++){
		sprintf(arg_list2[k].index,"#%d",k);
		strcpy(arg_list2[k].arg,buffer[i][j+k+1]);
	}
}

int getArg(char *str){
	int k;
	for(k=0;k<2;k++){
		if(strcmp(arg_list2[k].index,str) == 0){
			return k;
		}
	}
}

void getMDT(){
	int k,n;
	for(k=1;k<line_count-1;k++){
		for(n=0;n<3;n++){
			if(mdt_table.macro[k][n][0] == '#'){
				arg_index = getArg(mdt_table.macro[k][n]);
				printf("%s ",arg_list2[arg_index].arg);
			}
			else{
				printf("%s ",mdt_table.macro[k][n]);				
			}
		}
		printf("\n");
	}
}

void main(){
	ptr = fopen("macropass2.txt","r");
	char delim[] = " ";
	int line_num = 0;
	int word_num = 0;
	int n;

	while ((read = getline(&line, &len, ptr)) != -1) {
		word_num = 0;
        char *ptr = strtok(line,delim);

        while(ptr != NULL){
    		strcpy(buffer[line_num][word_num],rstrip(ptr));
    		word_num++;
    		ptr = strtok(NULL,delim);
        }
        line_num++;
    }

    for(i=0;i<line_num;i++){
    	for(j=0;j<5;j++){
    		// printf("%s\n",buffer[i][j]);
			if(!isalnum(buffer[i][j][0]) && buffer[i][j][0] != '&' && buffer[i][j][0] != '*'){
    			break;
    		}

    		if(strcmp(buffer[i][j],"MACRO") == 0){
    			macro_count++;
    			j = 0;
    			strcpy(mnt_table.macro_name,buffer[i+1][j]);
    			mnt_table.mntc = macro_count;

    			prepareALA1();
    			do{
    				i++;
    				n = 0;
    				for(j=0;j<5;j++){
						if(!isalnum(buffer[i][j][0]) && buffer[i][j][0] != '&' && buffer[i][j][0] != '*'){
			    			break;
			    		}

    					// printf("i:%d  line_count:%d   j:%d   n:%d\n",i,line_count,j,n);
    					if(buffer[i][j][0] == '&'){
    						arg_index = getIndex(buffer[i][j]);
    						strcpy(mdt_table.macro[line_count][n],arg_list1[arg_index].index);
    					}
    					else{
				    		strcpy(mdt_table.macro[line_count][n],buffer[i][j]);
    					}
			    		// printf("%s\n",buffer[i][j]);
			    		n++;

	    				if(strcmp(buffer[i][j],"MEND") == 0){
	    					break;
	    				}
    				}

    				line_count++;
    			}while(strcmp(buffer[i][j],"MEND") != 0);
				
				prev_i = i;
    			prev_j = j;
    		}

    		else{
    			for(i=prev_i+1;i<line_num;i++){
    				for(j=prev_j;j<5;j++){
    					if(strcmp(buffer[i][j],mnt_table.macro_name) == 0){
    						prepareALA2();
    						getMDT();
    						i++;
    						j=-1;
    					}
    					else{
	    					printf("%s ",buffer[i][j]);
    					}
    				}
    				printf("\n");
    			}
    		}
    	}
    }
    printTables();
}
