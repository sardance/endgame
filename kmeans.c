#include<stdio.h>
#include<stdlib.h>
int clusters(int c1[50],int c2[50],int count1,int count2, int mean1, int mean2, int n)
{
	int t1,t2,i,array[100],sum1=0,sum2=0,mean11,mean22,j=0,k=0,temp=0,cluster1[50],cluster2[50];
	for(i=0;i<count1;i++)
	{
		array[i] = c1[i];
	}
	temp = count1;
	for(i=0;i<count2;i++)
	{
		array[temp] = c2[i];
		temp++;
	}
	//printf("temp\n%d",temp);
	for(i=0;i<n;i++)
	{
		t1 = abs(array[i] - mean1);
		t2 = abs(array[i] - mean2);
		if((t1>t2) || (t1 == t2))
		{
			cluster1[j] = array[i];	
			//count1++;		
			
			sum1 = sum1 + cluster1[j];
			//printf("Sum1: %d\t",sum1);
			j++;
		}
		else
		{
			cluster2[k] = array[i];
			//count2++;
			
			sum2 = sum2 + cluster2[k];
			//printf("Sum2: %d\t",sum2);
			k++;
		}
	}
	
	//printf("sum1:%d",sum1);
	//printf("sum2:%d",sum2);
	
	mean11 = sum1/j;
	mean22 = sum2/k;
	
	
	
	if((mean11 != mean2) && (mean22 != mean1))
	{
		//printf("He");
		clusters(cluster1,cluster2,j,k,mean11,mean22,n);
	}
	else
	{
		printf("Cluster1:\n");
		for(i=0;i<j;i++)
			printf("%d\t",cluster1[i]);
		printf("\nCluster2:\n");
		for(i=0;i<k;i++)
			printf("%d\t",cluster2[i]);
	}
	return 0;
	
}
void main()
{
	int m1,m2,i,a[10],n,c1[10],c2[10],t1,t2,avg1,avg2,sum1=0,sum2=0,count1=0,count2=0,mean11,mean22,k=0,j=0;
	printf("Enter the no. of values u want to enter \n");
	scanf("%d",&n);
	printf("Enter the values\n");
	for(i=0;i<n;i++)
	{
		scanf("%d",&a[i]);
	}
	printf("Enter initial mean values:\n");
	scanf("%d%d",&m1,&m2);

	for(i=0;i<n;i++)
	{
		t1 = abs(a[i] - m1);
		t2 = abs(a[i] - m2);
		if(t1>t2)
		{
			c1[j]=a[i];	
			count1++;		
			sum1=sum1+c1[j];
			j++;
		}
		else
		{
			c2[k]=a[i];
			count2++;
			sum2=sum2+c2[k];
			k++;
		}
	}
	mean11 = sum1/count1;
	mean22 = sum2/count2;
	
	if((mean11 != m1) && (mean22 != m2))
	{
		clusters(c1,c2,count1,count2,mean11,mean22,n);
	}
	else
	{
		printf("Cluster1:\n");
		for(i=0;i<count1;i++)
			printf("%d\t",c1[i]);
		
		printf("\nCluster2:\n");
		for(i=0;i<count2;i++)
			printf("%d\t",c2[i]);
	}

	
}
