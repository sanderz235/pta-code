#include<stdio.h>
	int arr[1005][1005];
int main()
{
	int n;
	scanf("%d",&n);
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			scanf("%d",&arr[i][j]);
		}
	}
	int row_start,row_end,column_start,column_end;
	int flag = 0;
	for(int i=0;i<n;i++){
		if(flag==1)break;
		for(int j=0;j<n;j++){
			if(arr[i][j]==0){
				row_start=i;
				column_start=j;
				printf("row_start:%d\n",row_start);
				printf("column_start:%d\n",column_start);
				flag=1;
				break;
			}
		}
	}
	//find row_end
	for(int i=row_start;i<n;i++){
		if(arr[i][column_start]==255){
			row_end=i;
			printf("row_end:%d\n",row_end);
			break;
		}
	}
	//find column_end
	for(int i=column_start;i<n;i++){
		if(arr[row_start][i]==255){
			column_end=i;
			printf("column_end:%d\n",column_end);
			break;
		}
	}
	int area=(row_end-row_start-1)*(column_end-column_start-1);
	printf("%d",area);
	return 0;
 } 
