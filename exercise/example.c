#include<stdio.h>
int main()
{
	int array1[10]={0};
	int array2[10]={0};
	int array[20]={0};
	int i=0;
	while(scanf("%d",&array1[i])==1&&array1[i]!=0)
	i++;
	int len1=i;
	i=0;
	while(scanf("%d",&array2[i])==1&&array2[i]!=0)
	i++;
	int len2=i;
	for(int j=0;j<len1;j++)
	{
		array[j]=array1[j];
	}
	for(int j=len1-1;j<len1-1+len2;j++)
	{
		array[j]=array2[j-len1+1];
	}
	int len=len1+len2,swapped=0,temp;
	for(int j=0;j<len-1;j++)
	{
		for(int k=0;k<len-1-j;k++)
		{
			if(array[k]>array[k+1])
			{
				temp=array[k];
				array[k]=array[k+1];
				array[k+1]=temp;
				swapped = 1;
			}
		}
		if(!swapped)
		break;
	}
	for(int j=0;j<len;j++)
	{
		printf("%d ",array[j]);
	}
	return 0;
 } 
