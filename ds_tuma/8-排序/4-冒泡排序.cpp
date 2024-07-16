
// 全站内容仅供学习，禁止以原文或修改形式后的任何企业使用，请准守“一般著作权”协议
// 来源:totuma.cn
#include <stdio.h>
#include <stdlib.h>

#define ElemType int



// totuma.cn
// 冒泡排序
// 先冒最小的到最前面
void Bubble_MinToFront_Sort (ElemType A[], int n) {
  int i, j, temp;
  bool flag = false;
  for (i = 0; i < n - 1; i++) {
    flag = false;
    for (j = n - 1; j > i; j--) {
      // 检查相邻两个元素的大小，如果前一个大于当前，则交换它们
      if (A[j - 1] > A[j]) {
        temp = A[j]; // 临时变量用于交换元素
        A[j] = A[j - 1];
        A[j - 1] = temp;
        flag = true; // 设置标志位为true，表示发生了交换
      }
    }
    // 如果本轮没有发生交换（数组已经有序），则直接返回
    if (flag == false) return;
  }
}


// totuma.cn
// 冒泡排序
// 先冒最大的到最后面
void Bubble_MaxToEnd_Sort (ElemType A[], int n) {
  int i, j, temp;
  bool flag = false;
  for (i = 0; i < n - 1; i++) {
    flag = false; // 初始化标志位为false
    for (j = 0; j < n - 1 - i; j++) { // 执行冒泡排序，将最大的元素冒泡到最后
      // 检查相邻两个元素的大小，如果当前大于后一个，则交换它们
      if (A[j] > A[j + 1]) { // 修改比较条件
        temp = A[j];        // 临时变量用于交换元素
        A[j] = A[j + 1];    // 将较大的元素移动到后面
        A[j + 1] = temp;    // 将较小的元素移动到前面
        flag = true;        // 设置标志位为true，表示发生了交换
      }
    }
    // 如果本轮没有发生交换（数组已经有序），则直接返回
    if (flag == false) return;
  }
}


// totuma.cn
int main () {
  // 注意，0号位置是哨兵，不是要排序的值
  ElemType arr1[9] = {20, 60, 30, 10, 40, 90, 80, 70, 50};
  Bubble_MinToFront_Sort(arr1, 9);
  printf("冒泡排序(最小的往前冒)排序结果：");
  for (int i = 0; i < 9; i++) {
    printf("%d ", arr1[i]);
  }

  ElemType arr2[9] = {20, 60, 30, 10, 40, 90, 80, 70, 50};
  Bubble_MaxToEnd_Sort(arr2, 9);

  printf("\n冒牌排序(最大的往后冒)排序结果：");
  for (int i = 0; i < 9; i++) {
    printf("%d ", arr2[i]);
  }

  return 0;
}