#include<stdio.h>
void bubble_sort(int *p,int n){
	int sort=0;
	int temp;
	for(int i=0;i<n-1;i++){
		sort=0;
		for(int j=0;j<n-1-i;j++){
			if(p[j]>p[j+1]){
				temp=p[j];
				p[j]=p[j+1];
				p[j+1]=temp;
				sort=1;
			}
		}
		for(int k=0;k<n;k++){
		printf("%d ",p[k]);
	}
	printf("\n");
		if(!sort)break;
	}
}
int main()
{
	int n,arr[105]={0};
	scanf("%d",&n);
	for(int i=0;i<n;i++){
		scanf("%d",&arr[i]);
	}
	bubble_sort(arr,n);
	for(int i=0;i<n;i++){
		printf("%d ",arr[i]);
	}
	return 0;
 } 
