
// 全站内容仅供学习，禁止以原文或修改形式后的任何企业使用，请准守“一般著作权”协议
// 来源:totuma.cn
/**
* Partition函数：
* 这个函数用于将数组分成两部分，以枢纽元素（pivot）为基准，将小于等于枢纽元素的元素移到数组的左侧，
* 将大于等于枢纽元素的元素移到数组的右侧。这个函数的核心思想是使用两个指针（low和high），从数组的两端开始，
* 不断地向中间移动，找到需要交换的元素，直到low和high相遇，此时枢纽元素的最终位置确定。这个函数返回枢纽元素的位置。
* 
* Quick_Sort函数：
* 这是快速排序的主要函数，它使用递归的方式对数组进行排序。它接受一个数组以及待排序部分的起始索引和结束索引作为参数。
* 首先，它检查是否有足够多的元素需要排序（即，low小于high），如果是的话，就调用Partition函数找到枢纽元素的位置。
* 然后，它递归地对枢纽元素左侧和右侧的两个部分分别调用自身进行排序。通过不断地分割和排序子数组，最终整个数组会被排序。
* 
* 这两个函数一起实现了快速排序算法的分治思想。
* Partition函数负责将数组分成两部分，而Quick_Sort函数负责递归地对这两部分进行排序。
* 它是一种高效的排序算法，常被用于实际应用中。
* @author cscub.com
*/

#include <stdio.h>
#include <stdlib.h>

#define ElemType int


// totuma.cn
// 定义一个分区函数，用于将数组划分为两部分，使得左边的元素都小于等于枢纽元素，右边的元素都大于等于枢纽元素。
int Partition(ElemType A[], int low, int high) {
  // 选择枢纽元素，这里选择数组的第一个元素作为枢纽元素
  ElemType pivot = A[low];
  
  // 进入循环，直到low和high相遇
  while (low < high) {
    // 从右侧开始，找到第一个小于枢纽元素的元素的位置
    while (low < high && A[high] >= pivot) {
      --high;
    }
    // 将找到的小于枢纽元素的元素移到左侧
    A[low] = A[high];
    // 从左侧开始，找到第一个大于枢纽元素的元素的位置
    while (low < high && A[low] <= pivot) {
      ++low;
    }
    // 将找到的大于枢纽元素的元素移到右侧
    A[high] = A[low];
  }
  
  // 当low和high相遇时，将枢纽元素放置在这个位置，此时枢纽元素左侧的元素都小于等于它，右侧的元素都大于等于它
  A[low] = pivot;
  // 返回枢纽元素的位置
  return low;
}

// 快速排序算法
void Quick_Sort (ElemType A[], int low, int high) {
  // 当low小于high时，说明待排序的部分至少有两个元素
  if (low < high) {
    // 调用Partition函数将数组分为两部分，并获得枢纽元素的位置
    int pivotPos = Partition(A, low, high);
    
    // 递归对枢纽元素左侧的部分进行快速排序
    Quick_Sort(A, low, pivotPos - 1);
    
    // 递归对枢纽元素右侧的部分进行快速排序
    Quick_Sort(A, pivotPos + 1, high);
  }
}


// totuma.cn
int main () {
  // 注意，0号位置是哨兵，不是要排序的值
  ElemType arr[9] = {20, 60, 30, 10, 40, 90, 80, 70, 50};
  // 起始索引 low 应为 0
  // 结束索引 high 应为数组的最后一个元素的索引（通常为 n - 1，其中 n 是数组的长度）
  Quick_Sort(arr, 0, 9 - 1);
  printf("快速排序结果：");
  for (int i = 0; i < 9; i++) {
    printf("%d ", arr[i]);
  }

  return 0;
}