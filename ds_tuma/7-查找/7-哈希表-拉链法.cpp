
// 全站内容仅供学习，禁止以原文或修改形式后的任何企业使用，请准守“一般著作权”协议
// 来源:totuma.cn
#include <stdio.h>
#include <stdlib.h>

// 哈希表大小
#define TABLE_SIZE 13

// 哈希表结点的结构
typedef struct HashNode {
  int value;
  HashNode *next;
} HashNode;

// 函数用于检查一个整数是否是质数
int isPrime(int n) {
  if (n <= 1) return 0;
  if (n <= 3) return 1;
  if (n % 2 == 0 || n % 3 == 0) return 0;

  for (int i = 5; i * i <= n; i += 6) {
    if (n % i == 0 || n % (i + 2) == 0) {
      return 0;
    }
  }
  return 1;
}


// totuma.cn
// 哈希函数
int hash(int key) {
  // 【除留余数法】
  int p = TABLE_SIZE; // 不大于m但最接近m的质数
  while (p >= 2) {
    // 是质数
    if (isPrime(p)) break;
    p--;
  }

  //【直接定址法】
  // a * key + b

  //【数字分析法】
  //【平方取中法】
  return key % p; // 使用取余运算计算哈希值
}


// totuma.cn
// 插入值到链表
void insert(HashNode* table[], int value) {
  HashNode *newNode = (HashNode *)malloc(sizeof(HashNode));

  HashNode **head = &table[hash(value)];
  newNode->value = value;
  newNode->next = *head;
  *head = newNode;
}


// totuma.cn
// 查找值是否存在于链表中
int find(HashNode* table[], int value) {
  // 开头结点
  HashNode *current = table[hash(value)];
  while (current != NULL) {
    if (current->value == value) {
      return 1; // 找到值
    }
    current = current->next;
  }
  return 0; // 没有找到值
}


// totuma.cn
// 从链表中删除值
void removeValue(HashNode* table[], int value) {
  HashNode *head = table[hash(value)];
  HashNode *current = head;
  HashNode *pre = NULL;

  while (current != NULL) {
    if (current->value == value) {
      // 仅有一个结点
      if (pre == NULL) {
        head = current->next;
      } else {
        pre->next = current->next;
      }
      free(current);
      return;
    }

    // 继续遍历
    pre = current;
    current = current->next;
  }
}


// totuma.cn
// 打印哈希表及链表内容
void printHashTable(HashNode* table[]) {
  for (int i = 0; i < TABLE_SIZE; ++i) {
    printf("Index %d:", i);
    HashNode* current = table[i];
    while (current != NULL) {
        printf(" -> %d", current->value);
        current = current->next;
    }
    printf(" -> NULL\n");
  }
}


// totuma.cn
int main () {
  HashNode* table[TABLE_SIZE];
  // 初始化哈希表
  for (int i = 0; i < TABLE_SIZE; ++i) {
    table[i] = NULL;
  }

  // 插入值
  insert(table, 19);
  insert(table, 14);
  insert(table, 23);
  insert(table, 1);
  insert(table, 68);
  insert(table, 20);
  insert(table, 84);
  insert(table, 27);
  insert(table, 55);
  insert(table, 11);
  insert(table, 10);
  insert(table, 79);

  printHashTable(table);

  // 查找值
  printf("Value 20 exists: %s\n", find(table, 20) ? "Yes" : "No");
  printf("Value 300 exists: %s\n", find(table, 300) ? "Yes" : "No");
  printf("Value 200 exists: %s\n", find(table, 200) ? "Yes" : "No");

  // 删除值
  int removedValue = 10;
  removeValue(table, removedValue);
  printf("Value %d removed\n", removedValue);

  // 查找值
  printf("Value 200 exists: %s\n", find(table, removedValue) ? "Yes" : "No");

  printHashTable(table);
  // 释放内存
  for (int i = 0; i < TABLE_SIZE; ++i) {
    HashNode* current = table[i];
    while (current != NULL) {
      HashNode* temp = current;
      current = current->next;
      free(temp);
    }
  }

  return 0;
}