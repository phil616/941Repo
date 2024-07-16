
// 全站内容仅供学习，禁止以原文或修改形式后的任何企业使用，请准守“一般著作权”协议
// 来源:totuma.cn
#include <stdio.h>
#include <stdlib.h>

#define ElemType int

// 查找表的数据结构
typedef struct {
  ElemType *elem; // 元素存储空间地址
  int TableLen; // 表长度
} SSTable; //ss search seq table


// totuma.cn
// 哨兵版查找
// 注意: 成功返回数据下标，失败返回0
// 由于0号下标是哨兵，找到哨兵后则证明没有返回找到值，返回0为查找失败
int Sentinel_Search_Seq (SSTable ST, ElemType key) {
  ST.elem[0] = key; // 使哨兵 = 查找元素
  int i;
  // 下面 for 循环的写法也是正确的
  // for (i = ST.TableLen; ST.elem[i] != key; --i)
  // 为了方便理解，改写成while循环的
  i = ST.TableLen;
  while (ST.elem[i] != key) {
    i = i - 1;
  }

  return i;
}


// totuma.cn
// 普通版查找
// 成功返回数据下标，失败返回 -1
int Search_Seq (SSTable ST, ElemType key) {
  int i;
  // 下面 for 循环的写法也是正确的
  // for (i = 0; i < ST.TableLen && ST.elem[i] != key; ++i);
  // 为了方便理解，改写成while循环的
  i = 0;
  while (i < ST.TableLen) {
    if (ST.elem[i] == key) break;
    i = i + 1;
  }

  return i == ST.TableLen ? - 1 : i;
}


// totuma.cn
int main () {
  // 待查找的值
  ElemType searchNum = 60;
  // 查找到的下标
  int searchResultIndex;

  // 带哨兵版查找
  SSTable SentinelSS;
  // 注意：带哨兵的 table 长度为有效数据长度，不包含哨兵
  SentinelSS.TableLen = 7;
  SentinelSS.elem = (ElemType *)malloc(sizeof(ElemType) * (SentinelSS.TableLen + 1)); // + 1 是哨兵位置
  // 下标0，存储哨兵
  SentinelSS.elem[0] = -1;
  SentinelSS.elem[1] = 40;
  SentinelSS.elem[2] = 20;
  SentinelSS.elem[3] = 50;
  SentinelSS.elem[4] = 10;
  SentinelSS.elem[5] = 60;
  SentinelSS.elem[6] = 80;
  SentinelSS.elem[7] = 70;
  searchResultIndex = Sentinel_Search_Seq(SentinelSS, searchNum);
  if (searchResultIndex == 0) {
    printf("哨兵版未查找到值：%d, 查找结果为：%d\n", searchNum, searchResultIndex);
  } else {
    printf("哨兵版查找值：%d, 下标为：%d\n", searchNum, searchResultIndex);
  }


  // 普通模式查找
  SSTable SS;
  SS.TableLen = 7;
  SS.elem = (ElemType *)malloc(sizeof(ElemType) * SS.TableLen);
  SS.elem[0] = 40;
  SS.elem[1] = 20;
  SS.elem[2] = 50;
  SS.elem[3] = 10;
  SS.elem[4] = 60;
  SS.elem[5] = 80;
  SS.elem[6] = 70;
  searchResultIndex = Search_Seq(SS, searchNum);
  if (searchResultIndex == -1) {
    printf("普通版未查找到值：%d, 查找结果为：%d\n", searchNum, searchResultIndex);
  } else {
    printf("普通版查找值：%d, 下标为：%d\n", searchNum, searchResultIndex);
  }

  return 0;
}