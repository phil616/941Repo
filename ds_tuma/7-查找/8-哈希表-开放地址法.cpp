
// 全站内容仅供学习，禁止以原文或修改形式后的任何企业使用，请准守“一般著作权”协议
// 来源:totuma.cn
#include <stdio.h>
#include <stdlib.h>

// 哈希表结点的结构
typedef struct HashMap {
  int p; // 不大于 TABLE_SIZE 但最接近 TABLE_SIZE 的质数
  int size;
  int* table;
} HashMap;

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
int hash(int key, int size) {
  return key % size; // 使用取余运算计算哈希值
}

// 初始化哈希表
HashMap* CreateHashMap (int size) {
  HashMap* hash = (HashMap *)malloc(sizeof(HashMap));

  int p = size; // 不大于m但最接近m的质数
  while (p >= 2) {
    // 是质数
    if (isPrime(p)) break;
    p--;
  }
  hash->p = p;
  hash->size = size;
  hash->table = (int *)malloc(sizeof(int) * hash->size);

  for (int i = 0; i < size; i++) {
    hash->table[i] = NULL; // 初始化哈希表
  }
  return hash;
}


// totuma.cn
// 线性探测插入
void HashMap_Insert_Linerar (HashMap * hashMap, int value) {
  int index = hash(value, hashMap->p);
  int count = 0; // 记录是否满
  while (hashMap->table[index] != NULL) {
    if (count == hashMap->size) {
      printf("哈希表以满");
      return;
    }
    count++;
    // 线性探测，递增索引
    index = (index + 1) % hashMap->size;
  }
  hashMap->table[index] = value;
}


// totuma.cn
// 线性探测查找
int HashMap_Search_Linerar (HashMap *hashMap, int value) {
  int index = hash(value, hashMap->p);
  int count = 0; // 记录是否没有
  while (hashMap->table[index] != NULL) {
    // 查找完整个表都没有找到
    if (count == hashMap->size) return -1;
    if (hashMap->table[index] == value)
      return index;

    index = (index + 1) % hashMap->size;
  }
  return -1;
}


// totuma.cn
// 平方探测插入
void HashMap_Insert_Quadratic (HashMap * hashMap, int value) {
  int hashIndex = hash(value, hashMap->p);
  int index = hashIndex;
  int d = 1;
  int count = 0; // 记录比较次数
  // 0²，1²，-1²，2²，-2²，.....
  // hashMap->table[index] 即代表了 d = 0 的情况
  while (hashMap->table[index] != NULL) {
    if (d > hashMap->size / 2) {
      printf("增量【d > 表长/2】，退出循环。没有遍历到的位置也不会在遍历到了");
      return;
    }
    count++;
    // 根据 d 的正负，选择使用负平方偏移或正平方偏移来计算新的索引位置
    if (d < 0) {
      index = (-1 * d * d + hashIndex) % hashMap->size;
    } else {
      index = (d * d + hashIndex) % hashMap->size;
    }

    // 如果计算出的新索引为负数，将其转换为对应的正数索引，确保索引在哈希表的有效范围内
    if (index < 0) index = hashMap->size + index;

    d = -d; // 切换正负平方偏移

    if (d >= 0) {
      d++; // 正平方偏移 + 1
    }
  }
  hashMap->table[index] = value;
}


// totuma.cn
// 平方探测查找
int HashMap_Search_Quadratic (HashMap *hashMap, int value) {
  int hashIndex = hash(value, hashMap->p);
  int d = 1;
  int index = hashIndex;
  int count = 0; // 记录比较次数
  while (hashMap->table[index] != NULL) {
    // 查找完整个表都没有找到
    if (d > hashMap->size / 2) {
      printf("增量【d > 表长/2】，退出循环。没有遍历到的位置也不会在遍历到了");
      return -1;
    }

    if (hashMap->table[index] == value) {
      return index;
    }

    if (d < 0) {
      index = (-1 * d * d + hashIndex) % hashMap->size;
    } else {
      index = (d * d + hashIndex) % hashMap->size;
    }

    if (index < 0) index = hashMap->size + index;

    d = -d; // 切换正负平方偏移
    if (d >= 0) {
      d++; // 正平方偏移+1
    }
  }
  return -1; // 未找到值
}


// totuma.cn
int main () {
  HashMap* linerHashMap = CreateHashMap(11);
  linerHashMap->p = 7;

  // 线性探测
  HashMap_Insert_Linerar(linerHashMap, 87);
  HashMap_Insert_Linerar(linerHashMap, 40);
  HashMap_Insert_Linerar(linerHashMap, 30);
  HashMap_Insert_Linerar(linerHashMap, 6);
  HashMap_Insert_Linerar(linerHashMap, 11);
  HashMap_Insert_Linerar(linerHashMap, 22);
  HashMap_Insert_Linerar(linerHashMap, 98);
  HashMap_Insert_Linerar(linerHashMap, 20);

  printf("线性探测哈希表(M:%d,P:%d)：", linerHashMap->size, linerHashMap->p);
  for (int i = 0; i < linerHashMap->size; i++) {
    printf("%d、", linerHashMap->table[i]);
  }

  // 平方探测
  HashMap* QuadraticHashMap = CreateHashMap(27);
  QuadraticHashMap->p = 13;
  HashMap_Insert_Quadratic(QuadraticHashMap, 6);
  HashMap_Insert_Quadratic(QuadraticHashMap, 19);
  HashMap_Insert_Quadratic(QuadraticHashMap, 32);
  HashMap_Insert_Quadratic(QuadraticHashMap, 45);
  HashMap_Insert_Quadratic(QuadraticHashMap, 58);
  HashMap_Insert_Quadratic(QuadraticHashMap, 71);
  HashMap_Insert_Quadratic(QuadraticHashMap, 84);

  printf("\n平方探测哈希表(M:%d,P:%d)：", QuadraticHashMap->size, QuadraticHashMap->p);
  for (int i = 0; i < QuadraticHashMap->size; i++) {
    printf("%d、", QuadraticHashMap->table[i]);
  }

  printf("\n查找84的下标为：%d", HashMap_Search_Quadratic(QuadraticHashMap, 84));

  return 0;
}