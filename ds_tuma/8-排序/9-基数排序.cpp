
// 全站内容仅供学习，禁止以原文或修改形式后的任何企业使用，请准守“一般著作权”协议
// 来源:totuma.cn
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// 定义链表节点结构
typedef struct Node {
  int data;
  struct Node* next;
} Node;


// totuma.cn
// 找到数字的最大位数(...、千、百、十、个)
int getMaxDigits (int arr[], int n) {
  // 默认最大值为第0个元素
  int maxNum = arr[0];
  // 找到数组中的最大值
  for (int i = 1; i < n; i++) {
    if (arr[i] > maxNum) {
      maxNum = arr[i];
    }
  }

  int digits = 0;
  // 计算最大的位数
  while (maxNum > 0) {
    maxNum /= 10;
    digits++;
  }

  return digits;
}


// totuma.cn
// 将数字插入到链表中
void insert (Node ** head, int data) {
  // 分配新节点内存并设置其数据和下一个节点指针为NUL
  Node* newNode = (Node*)malloc(sizeof(Node));
  newNode->data = data;
  newNode->next = NULL;

  if (!(*head)) {
    // 如果链表为空，将新节点作为头节点
    *head = newNode;
  } else {
    // 否则，找到链表的末尾，然后将新节点链接到末尾
    struct Node* current = *head;
    // 这里也可以使用头尾指针的方式，就避免循环找尾节点
    while (current->next) {
      current = current->next;
    }
    current->next = newNode;
  }
}

// 通过遍历链表，依次取出节点的数据，将数据存入数组，然后释放节点的内存
void extract(Node **head, int arr[], int *index) {
  while (*head) {
    // 保存当前头节点的指针
    Node* temp = *head;
    // 将头节点的数据存入数组
    arr[(*index)++] = (*head)->data;
    // 移动头节点到下一个节点
    *head = (*head)->next;
    // 释放先前的头节点的内存
    free(temp);
  }
}

// 基数排序
void Radix_Sort (int arr[], int n) {
  int maxDigits = getMaxDigits(arr, n);

  // 创建10个链表，用于存放每个位上的数字
  Node *Q[10] = {NULL};

  for (int digit = 1; digit <= maxDigits; digit++) {
    // 【分配】将数组中的元素分配到链表中
    for (int i = 0; i < n; i++) {
      // 取出当前的位数，找出0-9对应的链表
      int linkIndex = (arr[i] / (int)pow(10, digit - 1)) % 10;
      insert(&Q[linkIndex], arr[i]);
    }

    // 【收集】从桶中取回元素并重新排列数组
    int index = 0;
    for (int i = 0; i < 10; i++) {
      extract(&Q[i], arr, &index);
    }
  }

  // 释放内存
  for (int i = 0; i < 10; i++) {
    while (Q[i]) {
      Node *temp = Q[i];
      Q[i] = Q[i]->next;
      free(temp);
    }
  }
}


// totuma.cn
int main() {
  int arr[] = {170, 45, 75, 90, 802, 24, 2, 66};
  int n = sizeof(arr) / sizeof(arr[0]);

  Radix_Sort(arr, n);
  printf("归并排序结果：");
  for (int i = 0; i < n; i++) {
      printf("%d ", arr[i]);
  }

  return 0;
}