#include<stdio.h>
float iterations(int a[50][50], float iteration0[100], int outdegree[100], int n, int it)
{
	int i,j,b;
	float iteration1[50],max,temp,temp1;
	char alpha[50];
	it = it -1;
	for(j=0;j<n;j++)
	{
		for(i=0;i<n;i++)
		{
			if(a[i][j] == 1)
			{
				iteration1[j] = iteration1[j] + (iteration0[i]/outdegree[i]);
			}	
		}
	}
	printf("Next Iteration:\n");
	for(i=0;i<n;i++)
	{
		printf("%.2f\n",iteration1[i]);
	}
	if(it!=0)
	{
		iterations(a,iteration1,outdegree,n,it);
	}
	else
	{
		printf("Page Rank:\n");
		for(b=0;b<n;b++)
		{
			alpha[b] = 65 + b;
		}
			
		for(i=0;i<n-1;i++)
		{
			for(j=0;j<n-i-1;j++)
			{
				if(iteration1[j+1] < iteration1[j])
				{
					temp = iteration1[j];
					temp1 = alpha[j];
					iteration1[j] = iteration1[j+1];
					alpha[j] = alpha[j+1];
					iteration1[j+1] = temp;
					alpha[j+1] = temp1;
				}
			}	
			
		}
		printf("IT:\n");
		for(i=0;i<n;i++)
		{
			printf("%.2f\n",iteration1[i]);
		}
		for(i=0;i<n;i++)
		{
			printf("%c\t",alpha[i]);
		}
	}
}
void main()
{
	int a[50][50],i,j,it,outdegree[10],temp;
	float iteration[50],n;
	printf("Enter no of nodes:");
	scanf("%f",&n);
	
	printf("Enter the links");
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			scanf("%d",&a[i][j]);
		}
	}
	
	printf("The entered matrix is:\n");
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			printf("%d",a[i][j]);
		}
		printf("\n");
	}
	
	printf("Enter no of iterations:\n");
	scanf("%d",&it);
	
	for(i=0;i<n;i++)
	{
		iteration[i] = (1/n);
	}
	
	printf("Iteration0:\n");
	for(i=0;i<n;i++)
	{
		printf("%.2f",iteration[i]);
		printf("\n");
	}
	
	for(i=0;i<n;i++)
	{
		temp = 1;
		for(j=0;j<n;j++)
		{
			if(a[i][j] == 1)
			{
				outdegree[i] = temp;
				temp++;
			}
		}	
	}
	
	/*for(i=0;i<n;i++)
	{
		printf("%d",outdegree[i]);
		printf("\n");
	}*/
	it = it-1;
	if(it>1)
	{
		iterations(a,iteration,outdegree,n,it);
	}
}
