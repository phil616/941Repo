
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
// 有序表的顺序查找
// 成功返回数据下标，失败返回 -1
int Search_Seq (SSTable ST, ElemType key) {
  for (int i = 0; i < ST.TableLen; i++) {
    if (ST.elem[i] == key) return i; // 返回目标元素在有序表中的索引位置
    if (ST.elem[i] > key) return -1; // 返回-1表示未找到目标元素
  }
  return -1; // 如果遍历完整个有序表仍未找到目标元素，则返回-1
}


// totuma.cn
int main () {
  // 待查找的值
  ElemType searchNum = 60;
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
  searchResultIndex = Search_Seq(SS, searchNum);
  if (searchResultIndex == -1) {
    printf("未查找到值：%d, 查找结果为：%d", searchNum, searchResultIndex);
  } else {
    printf("查找到值：%d, 下标为：%d", searchNum, searchResultIndex);
  }

  return 0;
}