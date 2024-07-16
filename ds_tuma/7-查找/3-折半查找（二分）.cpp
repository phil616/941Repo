
// 全站内容仅供学习，禁止以原文或修改形式后的任何企业使用，请准守“一般著作权”协议
// 来源:totuma.cn
#include <stdio.h>
#include <stdlib.h>

#define ElemType int

// 查找表的数据结构
typedef struct {
  ElemType *elem; // 元素存储空间地址
  int TableLen; // 表长度
} SSTable; // search seq table


// totuma.cn
// 成功返回数据下标，失败返回 -1
int Binary_Search (SSTable ST, ElemType key) {
  int low = 0; // 初始化搜索范围的下界。
  int high = ST.TableLen - 1; // 初始化搜索范围的上界。
  int mid; // 声明一个变量来存储中间索引。

   // 在下界小于等于上界的情况下执行二分查找。
  while (low <= high)  {
    mid = (low + high) / 2; // 通过计算下界和上界的平均值来计算中间索引。
    if (ST.elem[mid] == key) // 将中间索引处的元素与关键字进行比较。
      return mid; // 如果元素与关键字匹配，则返回找到的索引。
    else if (ST.elem[mid] > key)
      high = mid - 1; // 如果元素大于关键字，则将上界更新为前半部分进行搜索。
    else
      low = mid + 1;  // 如果元素小于关键字，则将下界更新为后半部分进行搜索。
  }
  // 如果循环完成仍未找到关键字，则返回 -1 表示搜索失败。
  return -1;
}


// totuma.cn
int main () {
  // 待查找的值
  ElemType searchNum = 100;
  // 查找到的下标
  int searchResultIndex;
  // 普通模式查找
  SSTable SS;
  SS.TableLen = 7;
  SS.elem = (ElemType *)malloc(sizeof(ElemType) * SS.TableLen);
  SS.elem[0] = 20;
  SS.elem[1] = 40;
  SS.elem[2] = 50;
  SS.elem[3] = 60;
  SS.elem[4] = 70;
  SS.elem[5] = 80;
  SS.elem[6] = 90;
  searchResultIndex = Binary_Search(SS, searchNum);
  if (searchResultIndex == -1) {
    printf("未查找到值：%d, 查找结果为：%d", searchNum, searchResultIndex);
  } else {
    printf("查找到值：%d, 下标为：%d", searchNum, searchResultIndex);
  }

  return 0;
}