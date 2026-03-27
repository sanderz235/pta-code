#include <stdio.h>

int main() {
    int array1[10], array2[10], array[20];
    int len1 = 0, len2 = 0;

    // 输入第一个升序数组，以0结尾
    while (scanf("%d", &array1[len1]) == 1 && array1[len1] != 0)
        len1++;
    // 输入第二个升序数组，以0结尾
    while (scanf("%d", &array2[len2]) == 1 && array2[len2] != 0)
        len2++;

    // 归并过程
    int i = 0, j = 0, k = 0;
    while (i < len1 && j < len2) {
        if (array1[i] < array2[j])
            array[k++] = array1[i++];
        else
            array[k++] = array2[j++];
    }
    // 收尾，把没合完的直接放后面
    while (i < len1)
        array[k++] = array1[i++];
    while (j < len2)
        array[k++] = array2[j++];

    // 输出
    for (int t = 0; t < k; t++)
        printf("%d ", array[t]);
    return 0;
}