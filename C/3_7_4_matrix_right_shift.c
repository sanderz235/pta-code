#include<stdio.h>
#define MAXN 6
int main(){
	int m,n;
	int arr1[MAXN][MAXN]={0};
	scanf("%d %d",&m,&n);
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			scanf("%d",&arr1[i][j]);
		}
	}
	int arr2[MAXN][MAXN]={0};
	//按列
	for (int i = 0; i < n; i++){
		for(int j=0;j<n;j++){
			arr2[j][(i+m)%n]=arr1[j][i];
		}
	}
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			printf("%d ",arr2[i][j]);
		}
		printf("\n");
	}
	return 0;
 } 
