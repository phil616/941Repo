
// 全站内容仅供学习，禁止以原文或修改形式后的任何企业使用，请准守“一般著作权”协议
// 来源:totuma.cn
#include <stdio.h>
#include <stdlib.h>

#define ElemType int



// totuma.cn
// 定义一个用于二分插入排序的函数
void Binary_Insert_sort(ElemType A[], int n) {
  int i, j, low, high, mid;
  
  // 从第二个元素开始，逐个插入元素
  // 第 0 号位置是用于存储临时数据和 temp 一样
  for (i = 2; i <= n; i++) {
    // 将当前待插入元素保存到A[0]，以便在内部移动元素时不会丢失它
    A[0] = A[i];
    
    // 初始化二分查找的低位和高位索引
    low = 1;
    high = i - 1;
    
    // 开始二分查找插入位置
    while (low <= high) {
      // 计算中间位置
      mid = (low + high) / 2;

      // 如果中间元素大于待插入元素，说明当前待插入的元素应该插入在数组的左半部分
      if (A[mid] > A[0]) high = mid - 1;
      // 否则，当前待插入的元素应该插入在数组的右半部分
      else low = mid + 1;
    }
    
    // 从i-1位置开始，将元素依次右移，为待插入元素腾出位置
    for (j = i - 1; j >= high + 1; --j)
      A[j + 1] = A[j];

    // 将待插入元素放入正确的位置，即 high + 1 处
    A[high + 1] = A[0];
  }
}


// totuma.cn
int main () {
  // 注意，0号位置是待留位置，和哨兵一样，不是要排序的值
  ElemType Arr[10] = {-1, 20, 60, 30, 10, 40, 90, 80, 70, 50};
  Binary_Insert_sort(Arr, 9);
  printf("折半插入排序结果：");

  for (int i = 1; i < 10; i++) {
    printf("%d ", Arr[i]);
  }

  return 0;
}