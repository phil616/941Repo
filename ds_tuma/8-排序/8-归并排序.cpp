
// 全站内容仅供学习，禁止以原文或修改形式后的任何企业使用，请准守“一般著作权”协议
// 来源:totuma.cn
#include <stdio.h>
#include <stdlib.h>

#define ElemType int
#define n 10

// 动态分配内存来存储辅助数组
ElemType *B = (ElemType *)malloc(n * sizeof(ElemType));



// totuma.cn
// 归并操作函数，将两个有序子数组合并为一个有序数组
void Merge (ElemType A[], int low, int mid, int high) {
  int i, j, k;

  // 将原始数组 A 复制到辅助数组 B
  for (k = low; k <= high; k++)
    B[k] = A[k];
  
  // 合并两个有序子数组
  for (
    i = low,             // 左子数组起始位置
    j = mid + 1,         // 右子数组起始位置
    k = i;               // 合并后数组起始位置
    i <= mid && j <= high; // 当两个子数组都未遍历完时
    k++
  ) {
    if (B[i] <= B[j])
      A[k] = B[i++]; // 如果左子数组的元素小于等于右子数组，将左子数组元素放入合并后数组
    else {
      A[k] = B[j++]; // 否则，将右子数组元素放入合并后数组
    }
  }

  // 处理可能剩余的左子数组元素
  while (i <= mid) A[k++] = B[i++];
  // 处理可能剩余的右子数组元素
  while (j <= high) A[k++] = B[j++];
}

// 归并排序函数，递归地将数组分成两半并排序，然后合并它们
void Merge_Sort (ElemType A[], int low, int high) {
  if (low < high) {
    int mid = (low + high) / 2; // 计算数组的中间位置

    // 递归排序左子数组
    Merge_Sort(A, low, mid);
    // 递归排序右子数组
    Merge_Sort(A, mid + 1, high);
    // 合并左右子数组
    Merge(A, low, mid, high);
  }
}


// totuma.cn
int main () {
  // 注意，0号位置是暂存单元，不是要排序的值
  ElemType Arr[n] = {49, 38, 65, 97, 76, 13, 27, 49, 55, 40};
  Merge_Sort(Arr, 0, n - 1);
  printf("归并排序结果：");

  for (int i = 0; i < n; i++) {
    printf("%d ", Arr[i]);
  }
  return 0;
}