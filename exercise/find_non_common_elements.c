#include<stdio.h>
int main()
{
	int arr1[20],arr2[20];
	int n,m;
	scanf("%d",&n);
	for(int i=0;i<n;i++)
	{
		scanf("%d",&arr1[i]);
	}
	scanf("%d",&m);
	for(int i=0;i<m;i++)
	{
		scanf("%d",&arr2[i]);
	}
	int arr3[40]={0};
	int j=0,is_common=0;//arr3
	// 处理arr1
	for(int i=0;i<n;i++)
	{
		for(int k=0;k<m;k++)
		{
			if(arr1[i]==arr2[k])
			{
				is_common=1;
				break;
			}
		}
		if(!is_common)
		{
			int already_in_arr3=0;
			for(int l=0;l<j;l++)//去除重复
		{
			if (arr1[i]==arr3[l])
			{
				already_in_arr3=1;
				break;
			}
		}
			if(!already_in_arr3)
			{
				arr3[j]=arr1[i];
				j++;
			}
		}
		is_common=0;
	}
	//处理arr2
	for(int i=0;i<m;i++)
	{
		for(int k=0;k<n;k++)
		{
			if(arr2[i]==arr1[k])
			{
				is_common=1;
				break;
			}
		}
		if(!is_common)
		{
			int already_in_arr3=0;
		for(int l=0;l<j;l++)//去除重复
		{
			if (arr2[i]==arr3[l])
			{
				already_in_arr3=1;
				break;
			}
		}
			if(!already_in_arr3)
			{
				arr3[j]=arr2[i];
				j++;
			}
		}
		is_common=0;
	}
	//打印
	printf("%d",arr3[0]);
	for (int i=1;i<j;i++)
	{
		printf(" %d",arr3[i]);
	}
	return 0;
 } 
