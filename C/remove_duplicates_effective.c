#include <stdio.h>

int remove_duplicates(int arr[], int count) {
    if (count == 0) return 0;
    int i, j, k;
    for (i = 0; i < count; i++) {
        for (j = i + 1; j < count;) {
            if (arr[i] == arr[j]) {
                // 删除重复元素，后面元素前移
                for (k = j; k < count - 1; k++) {
                    arr[k] = arr[k + 1];
                }
                count--; // 元素个数减少
                // 不递增j，继续检查当前j位置的新元素
            } else {
                j++;
            }
        }
    }
    return count;
}

int main() {
    int arr[10] = {1, 2, 3, 2, 4, 1, 5, 3, 0, 0};
    // 有效数据长度为8，后面两个0只是占位
    int count = 8;

    int new_count = remove_duplicates(arr, count);

    printf("去重后的数组: ");
    for (int i = 0; i < new_count; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    return 0;
}