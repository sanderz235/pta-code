#include <stdio.h>

int main() {
    int n;
	scanf("%d", &n);
	int arr[1005];
	for (int i=0;i<n;i++)
	{
		scanf("%d",&arr[i]);
	}
	int k=0;
	int arr1[1005]={arr[0]},arr2[1005]={0};
	for(int i=0;i<n;i++)
	{
		int Diff=1;
		for(int j=0;j<=i;j++)
		{
			if(arr1[j]==arr[i])
			{
				Diff=0;
				arr2[j]+=1;
				break;
			}
		}
		if(Diff)
			{
				k++;
				arr1[k]=arr[i];
				arr2[k]++;
			}
	}
	int max=arr2[0],flag=0;
	for(int i=0;i<=k;i++)
	{
		if(arr2[i]>max)
		{
			max=arr2[i];
			flag=i;
		}
	}
	printf("%d %d",arr1[flag],max);
    return 0;
} 
