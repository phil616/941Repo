
// 全站内容仅供学习，禁止以原文或修改形式后的任何企业使用，请准守“一般著作权”协议
// 来源:totuma.cn
#include <stdio.h>
#include <stdlib.h>

#define ElemType int



// totuma.cn
// 辅助函数：将以 k 为根节点的子树调整成最大堆
void HeadAdjust(ElemType A[], int k, int len) {
  int i;
  // 保存当前节点的值，将 A[k] 暂存到 A[0]
  A[0] = A[k];
  
  // 从 k 节点的左子节点开始
  for (i = 2 * k; i <= len; i *= 2) {
    // 如果存在右子节点并且右子节点的值大于左子节点，则选择右子节点
    if (i < len && A[i] < A[i + 1]) {
      i++;
    }
    // 如果当前节点的值大于等于子节点中的最大值，则不需要调整
    if (A[0] >= A[i]) break;
    else {
      // 否则，将子节点的值上移覆盖当前节点，并继续向下调整
      A[k] = A[i];
      k = i;
    }
  }
  // 最终将暂存的 A[k] 放回正确的位置
  A[k] = A[0];
}

// 堆排序算法的主要入口函数，对输入数组 A 进行升序排序
void HeapSort (ElemType A[], int len) {
  // 第一步：构建最大堆 BuildMaxHeap
  // 从最后一个非叶子节点开始，依次向前调整堆
  for (int i = len / 2; i > 0; i--) {
    HeadAdjust(A, i, len);
  }

  // 第二步：每次从堆顶取出最大元素，放到已排序部分的末尾，然后重新调整堆
  for (int i = len; i > 1; i--) {
    // 交换堆顶元素和当前堆的最后一个元素
    A[0] = A[i];
    A[i] = A[1];
    A[1] = A[0];
     // 调整堆，重新使其成为最大堆
    HeadAdjust(A, 1, i - 1);
  }
}


// totuma.cn
int main() {
  // 创建待排序的数组
  ElemType A[9] = {0, 87, 45, 78, 32, 17, 65, 53, 9}; // 注意：数组的第一个元素A[0]不使用，用于辅助操作

  int len = 9 - 1; // 计算数组长度（不包括A[0]）

  // 调用堆排序函数
  HeapSort(A, len);

  // 打印排序结果
  printf("堆排序结果: ");
  for (int i = 1; i <= len; i++) {
    printf("%d ", A[i]);
  }
  return 0;
}