
// 全站内容仅供学习，禁止以原文或修改形式后的任何企业使用，请准守“一般著作权”协议
// 来源:totuma.cn
#include <stdio.h>
#include <stdlib.h>

#define ElemType int



// totuma.cn
// 哨兵版，0号位置为哨兵
void Sentinel_Insert_Sort (ElemType A[], int n) {
  int i, j;

  // 从第二个元素开始排序，循环遍历整个数组
  for (i = 2; i <= n; i++) {
    // 如果当前元素比前一个元素小，则将A[i]插入有序表
    if (A[i] < A[i - 1]) {
      // 将当前元素存储在 A[0] 中，作为哨兵元素
      A[0] = A[i];

      // 从当前元素的前一个元素开始向前遍历，直到找到合适的位置插入哨兵元素
      for (j = i - 1; A[0] < A[j]; --j) {
        // 将比哨兵元素大的元素向后移动一位
        A[j + 1] = A[j];
      }
      // 插入哨兵元素到正确的位置
      A[j + 1] = A[0];
    }
  }
}


// totuma.cn
// 普通版
void Insert_Sort (ElemType A[], int n) {
  int i, j, temp;

  // 从第二个元素开始，循环遍历整个数组
  for (i = 1; i < n; i++) {
     // 检查当前元素是否小于前一个元素，如果是，则需要插入操作
    if (A[i] < A[i - 1]) {
      // 将当前元素存储在临时变量 temp 中
      temp = A[i];
      // 从当前元素的前一个元素开始向前遍历，直到找到合适的位置插入元素
      for (j = i - 1; j >= 0 && temp < A[j]; --j) {
        // 将比当前元素大的元素向后移动一位
        A[j + 1] = A[j];
      }
      // 插入元素到正确的位置
      A[j + 1] = temp;
    }
  }
}


// totuma.cn
int main () {
  // 注意，0号位置是哨兵，不是要排序的值
  ElemType SentinelArr[10] = {-1, 20, 60, 30, 10, 40, 90, 80, 70, 50};
  Sentinel_Insert_Sort(SentinelArr, 9);
  printf("哨兵模式排序结果：");
  for (int i = 1; i < 10; i++) {
    printf("%d ", SentinelArr[i]);
  }

  ElemType NormalArr[9] = {20, 60, 30, 10, 40, 90, 80, 70, 50};
  Insert_Sort(NormalArr, 9);

  printf("\n普通模式排序结果：");
  for (int i = 0; i < 9; i++) {
    printf("%d ", NormalArr[i]);
  }

  return 0;
}