
// 全站内容仅供学习，禁止以原文或修改形式后的任何企业使用，请准守“一般著作权”协议
// 来源:totuma.cn
#include <stdio.h>
#include <stdlib.h>
#define ElemType int


// totuma.cn
// 简单选择排序
void SelectSort(ElemType A[], int n) {
  int i, j, min, temp;

  // 外循环：从数组的第一个元素到倒数第二个元素进行遍历
  for (i = 0; i < n - 1; i++) {
    min = i; // 假设当前位置的元素是最小的
    
    // 内循环：从外循环的下一个位置到数组末尾进行遍历
    for (j = i + 1; j < n; j++) {
      // 检查是否有比当前最小值更小的元素
      if (A[j] < A[min])
        min = j; // 如果找到更小的元素，更新最小值的索引
    }
    
    // 如果最小值的索引不等于当前位置索引，说明找到了比当前位置更小的元素
    if (min != i) {
      temp = A[i];    // 临时变量用于交换元素
      A[i] = A[min];  // 将当前位置元素与最小值元素交换位置
      A[min] = temp;  // 更新最小值位置的元素为当前位置元素
    }
  }
}


// totuma.cn
int main () {
  // 注意，0号位置是哨兵，不是要排序的值
  ElemType arr[9] = {20, 60, 30, 10, 40, 90, 80, 70, 50};
  SelectSort(arr, 9);
  printf("简单选择排序排序结果：");
  for (int i = 0; i < 9; i++) {
    printf("%d ", arr[i]);
  }
  return 0;
}