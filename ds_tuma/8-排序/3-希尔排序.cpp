
// 全站内容仅供学习，禁止以原文或修改形式后的任何企业使用，请准守“一般著作权”协议
// 来源:totuma.cn
#include <stdio.h>
#include <stdlib.h>

#define ElemType int



// totuma.cn
// 增量为自动生成，采用 n / 2 (向下取整)
void Sheel_sort(ElemType A[], int n) {
  int di, i, j;
  // 控制增量(di)的缩小，直到增量为1
  // 0 号位置是暂存单元
  for (di = n / 2; di >= 1; di = di / 2) {
    // 从第一个增量(di)之后开始，逐个比较和排序子数组
    for (i = di + 1; i <= n; ++i) {
      // 如果当前元素比其前一个增量(di)的元素小，就进行插入排序
      if (A[i] < A[i - di]) {
        // 在插入排序中，将当前元素备份到A[0]
        A[0] = A[i];

        // 在子数组中进行插入排序
        for (j = i - di; j > 0 && A[0] < A[j]; j -= di) {
          A[j + di] = A[j]; // 向后移动元素，为A[0]腾出位置
        }
        A[j + di] = A[0]; // 将A[0]插入到正确位置
      }
    }
  }
}


// totuma.cn
// 该方式的增量可以自己输入控制，不用按照 n/2 的方式 请注意 gaps 最后一个应该为 1
void Sheel_sort(ElemType A[], int n, int gaps[], int gap_count) {
  int di, i, j;
  // 循环遍历增量数组中的每个增量
  // 0 号位置是暂存单元
  for (int gap_index = 0; gap_index < gap_count; gap_index++) {
    di = gaps[gap_index]; // 从增量数组中获取当前增量
    for (i = di + 1; i <= n; ++i) { // 第二层循环，遍历数组元素并排序
      // 如果当前元素比其前一个增量(di)的元素小，就进行插入排序
      if (A[i] < A[i - di]) {
        // 在插入排序中，将当前元素备份到A[0]
        A[0] = A[i];

        // 在子数组中进行插入排序
        for (j = i - di; j > 0 && A[0] < A[j]; j -= di) {
          A[j + di] = A[j]; // 向后移动元素，为A[0]腾出位置
        }
        A[j + di] = A[0]; // 将A[0]插入到正确位置
      }
    }
  }
}


// totuma.cn
int main () {
  // 注意，0号位置是暂存单元，不是要排序的值
  ElemType Arr[10] = {-1, 20, 60, 30, 10, 40, 90, 80, 70, 50};
  Sheel_sort(Arr, 9);
  printf("希尔自动增量排序结果：");

  for (int i = 1; i < 10; i++) {
    printf("%d ", Arr[i]);
  }

  ElemType Arr1[10] = {-1, 20, 60, 30, 10, 40, 90, 80, 70, 50};
  int gapsCount = 3;
  int gaps[3] = {3, 2, 1};
  Sheel_sort(Arr1, 9, gaps, gapsCount);
  printf("\n希尔给定增量排序结果：");

  for (int i = 1; i < 10; i++) {
    printf("%d ", Arr1[i]);
  }

  return 0;
}