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
// 题目要求：
// 给定一个整数序列（长度 n，数值可能有正有负），
// 求出现次数最多的那个数，如果有多个这样的数，
// 则输出最小的那个数，并输出它的出现次数。
// 传统思路可能会用双重循环进行统计，复杂度 O(n^2)。
// 但最优方式是用哈希思想计数：只用一次遍历记录所有数出现的次数，
// 再判断最大值。
// 由于 C 语言无内建哈希表，这里用计数数组（又叫“桶”）来模拟哈希表，
// 前提是输入数的范围有限可控。例如 PTA 常把输入范围设为 -1000 到 1000。
// 优化版本：
// #include <stdio.h>      // 引入标准输入输出头文件

// #define OFFSET 1000     // 定义偏移量，把负数变成非负下标（-1000 到 1000 变 0 到 2000）
// #define SIZE 2001       // 总数组大小，覆盖所有可能整数（包括 0）

// int main() {
//     int n, num;                               // n为输入总个数，num为临时读入的每个数
//     int count[SIZE] = {0};                    // 统计每个整数出现次数的数组，全部初始化为0
//     int maxCount = 0;                         // 当前最大出现次数，初值0
//     int result = 0;                           // 最大出现次数的数，此题要求输出最小的数，因此初始化为0

//     scanf("%d", &n);                          // 读入序列长度 n
//     for (int i = 0; i < n; ++i) {             // 循环读入n个数
//         scanf("%d", &num);                    // 读取一个数，记为num
//         count[num + OFFSET]++;                // 用数组方式计数：num+OFFSET作为下标，将负数正化
//         /*
//             如果当前num出现次数超过已知最大值，则更新结果数和最大次数
//             否则如果次数相同，但num更小，则也要更新（题目要求多解时取最小）
//         */
//         if (count[num + OFFSET] > maxCount) {
//             maxCount = count[num + OFFSET];   // 更新最大次数
//             result = num;                     // 记录此时这个数
//         }
//         else if (count[num + OFFSET] == maxCount && num < result) {
//             result = num;                     // 次数一样，但更小的数，更新结果
//         }
//     }

//     printf("%d %d\n", result, maxCount);      // 输出最终结果：最小的众数和次数
//     return 0;                                // 正常返回
// }