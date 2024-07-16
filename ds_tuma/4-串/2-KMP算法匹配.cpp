
// 全站内容仅供学习，禁止以原文或修改形式后的任何企业使用，请准守“一般著作权”协议
// 来源:totuma.cn
#include <stdio.h>
#include <stdlib.h>

#define MAX_LEN 255

typedef struct {
  char ch[MAX_LEN]; // 字符数组，用于存储字符串
  int length; // 字符串的长度
} SString;


// totuma.cn
// 计算模式串 T 的 next 数组，用于优化匹配过程
void get_next(SString T, int next[]) {
  int i = 1, j = 0; // 初始化主串下标 i 和模式串下标 j
  next[1] = 0; // next 数组的第一个元素初始化为0，因为没有前缀和后缀

  // 使用循环计算 next 数组
  while (i < T.length) {
    if (j == 0 || T.ch[i] == T.ch[j]) {
      // 如果当前字符匹配或者 j 已经回到模式串的开头
      ++i; // 主串下标向后移动
      ++j; // 模式串下标向后移动
      next[i] = j; // 将当前的 j 值存入 next 数组
    } else {
      // 如果当前字符不匹配，且 j 不是0
      j = next[j]; // 回溯 j 到上一次的匹配位置
    }
  }
}


// totuma.cn
// 计算模式串 T 的 nextval 数组（优化版本），用于优化匹配过程
void get_nextval(SString T, int nextval[]) {
  int i = 1, j = 0; // 初始化主串下标 i 和模式串下标 j
  nextval[1] = 0; // nextval 数组的第一个元素初始化为0，因为没有前缀和后缀

  // 使用循环计算 next 数组
  while (i < T.length) {
    if (j == 0 || T.ch[i] == T.ch[j]) {
      // 如果当前字符匹配或者 j 已经回到模式串的开头
      ++i; // 主串下标向后移动
      ++j; // 模式串下标向后移动
      if (T.ch[i] != T.ch[j]) {
        nextval[i] = j; // 如果下一个字符不同，将当前的 j 值存入 nextval 数组
      } else {
        nextval[i] = nextval[j]; // 如果下一个字符相同，使用 nextval[j] 的值进行优化
      }
    } else {
      // 如果当前字符不匹配，且 j 不是0
      j = nextval[j]; // 回溯 j 到上一次的匹配位置
    }
  }
}


// totuma.cn
// 在主串 S 中查找模式串 T，返回第一次匹配的起始位置，若无匹配则返回 0
int Index_KMP (SString S, SString T, int next[])  {
  int i = 1, j = 1; // 初始化主串 S 和模式串 T 的下标

  // 使用循环遍历主串和模式串
  while (i <= S.length && j <= T.length) {
    if (j == 0 || S.ch[i] == T.ch[j]) {
      ++i; // 如果字符匹配，主串下标向后移动
      ++j; // 模式串下标向后移动
    } else {
      j = next[j]; // 不匹配时，根据 next 数组调整模式串下标
    }
  }

  // 如果模式串完全匹配了主串，则返回模式串在主串中的起始位置
  if (j > T.length) return i - T.length;
  else return 0; // 否则返回 0 表示未找到匹配
}


// totuma.cn
int main () {
  SString S, T;
  S.ch[1] = 'a';
  S.ch[2] = 'b';
  S.ch[3] = 'a';
  S.ch[4] = 'b';
  S.ch[5] = 'c';
  S.ch[6] = 'a';
  S.ch[7] = 'b';
  S.ch[8] = 'c';
  S.ch[9] = 'a';
  S.ch[10] = 'c';
  S.ch[11] = 'b';
  S.ch[12] = 'a';
  S.ch[13] = 'b';
  S.length = 13;

  T.ch[1] = 'a';
  T.ch[2] = 'b';
  T.ch[3] = 'c';
  T.ch[4] = 'a';
  T.ch[5] = 'c';
  T.length = 5;
  int next[5];
  get_next(T, next);
  get_nextval(T, next); // 优化后的 next 数组
  int result = Index_KMP(S, T, next);

  if (result != 0) {
    printf("下标从1开始的模式匹配模式T在字符串S中的位置是：%d\n", result);
  } else {
    printf("下标从1开始的模式匹配模式T未在字符串S中找到\n");
  }
}