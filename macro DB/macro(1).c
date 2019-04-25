#include<stdio.h>
#include<string.h>
void main() 
{
	char s1[10], s2[10], s3[10], s4[10]; 
	int mdtc=1,mntc=1,flag=1,alac=1,mdt_index=1, active = 0, fline = 0, for_mdt=0, i = 1,x=1; 
	FILE *f1, *f2, *f4, *f3; 
	f1=fopen("macro.txt","r");
	f2=fopen("mnt.txt", "w"); 
	f3=fopen("mdt.txt","w"); 
	f4=fopen("ala.txt","w");
	while(!feof(f1)) 
	{ 
		fscanf(f1, "%s%s%s", s1, s2, s3);
		if (strcmp(s1,"MACRO") == 0)
		{ 
			active = 1; 
			for_mdt =1; 
			fline = 1;
			printf(" "); 
		} 
		else 
			if(strcmp(s1,"MEND") == 0) 
			{ 
				active= 0; 
				//printf(" "); 
			} 
			else 
				if(active ==1) 
				{ 
					//printf(" "); 
					if (fline == 1) 
					{
						fprintf(f4, "%s #%d\n",s2, alac); 
						fprintf(f4, "%s#%d",s3, alac+1); 
					} 
					fline = 0; 
					fprintf(f3,"%d%s %s %s \n",i , s1, s2, s3); 
					//fprintf(f3,"%d %s #%d #%d \n",i , s1, j, j+1); 
					++i;
					if(for_mdt==1) 
					{
						fprintf(f2, "%s %d", s1, mdtc);
						mdtc += 3;
						for_mdt =0;
					}
				}
	}

	mdtc += 3;
}
