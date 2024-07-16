
// 全站内容仅供学习，禁止以原文或修改形式后的任何企业使用，请准守“一般著作权”协议
// 来源:totuma.cn
#include <stdio.h>
#include <stdlib.h>
#define MAXM 10 // 定义B树的最大的阶数

const int m = 5;             // 设定B树的阶数
const int Max = m - 1;       // 结点的最大关键字数量
const int Min = (m - 1) / 2; // 结点的最小关键字数量
typedef int ElemType;        // ElemType为关键字类型

// B树和B树结点类型
typedef struct node {
  int keynum;             // 结点关键字个数
  ElemType key[MAXM];     // 关键字数组，key[0]不使用
  struct node *parent;    // 双亲结点指针
  struct node *children[MAXM]; // 孩子结点指针数组
} BTNode, *BTree;

// B树查找结果类型
typedef struct {
  BTNode *pt; // 指向找到的结点
  int i;      // 在结点中的关键字位置;
  int tag;    // 查找成功与否标志
} Result;

// 链表和链表结点类型
typedef struct LNode {
  BTree data;         // 数据域
  struct LNode *next; // 指针域
} LNode, *LinkList;

// 枚举类型（依次递增）
typedef enum status {
  TRUE,
  FALSE,
  OK,
  ERROR,
  OVERFLOW,
  EMPTY
} Status;

// 初始化B树
Status InitBTree(BTree &t) {
  t = NULL;
  return OK;
}


// totuma.cn
/**
* 在结点p中查找关键字k的插入位置i，使得p->key[i] <= k < p->key[i+1]。
* @param p - 目标结点
* @param k - 要查找的关键字
* @return int - 插入位置i，表示在结点p的第i个关键字之后插入k
*/
int SearchBTNode(BTNode *p, ElemType k) {
 int i = 0;

 // 从前向后逐个查找结点p中的关键字，找到第一个满足 p->key[i] <= k < p->key[i+1] 的位置
 for (
   i = 0;
   i < p->keynum && p->key[i + 1] <= k;
   i++
 );

 return i;
}


// totuma.cn
/**
* 在B树t上查找关键字k，返回查找结果。
* @param t - B树的根结点指针
* @param k - 要查找的关键字
* @return Result - 包含查找结果的结构体，包括指向找到的结点、关键字位置和查找成功与否标志
*/
Result SearchBTree(BTree t, ElemType k) {
 BTNode *p = t, *q = NULL; // 初始化结点p和结点q，p指向待查结点，q指向p的双亲
 int found_tag = 0;        // 设定查找成功与否标志
 int i = 0;
 Result r; // 设定返回的查找结果

 while (p != NULL && found_tag == 0) {
   i = SearchBTNode(p, k);      // 在结点p中查找关键字k，使得p->key[i] <= k < p->key[i+1]
   if (i > 0 && p->key[i] == k) // 找到待查关键字
     found_tag = 1;             // 查找成功
   else { // 查找失败
     q = p;      // 将当前结点p作为双亲结点q
     p = p->children[i]; // 移动到子结点继续查找
   }
 }

 if (found_tag == 1) { // 查找成功
   r.pt = p;   // 指向找到的结点
   r.i = i;    // 在结点中的关键字位置
   r.tag = 1;  // 查找成功标志
 } else { // 查找失败
   r.pt = q;   // 指向双亲结点q
   r.i = i;    // 在结点中的关键字位置
   r.tag = 0;  // 查找失败标志
 }

 return r; // 返回关键字k的位置(或插入位置)
}


// totuma.cn
/**
* 在结点p中插入关键字k和子树指针q，并保持关键字有序。
* @param p - 要插入关键字的目标结点
* @param i - 插入位置，表示在结点p的第i个关键字之后插入k
* @param k - 要插入的关键字
* @param q - 要插入的子树指针
*/
void InsertBTNode(BTNode *&p, int i, ElemType k, BTNode *q) {
 int j;

 // 从结点p的末尾开始，依次后移关键字和子树指针，为新关键字和子树指针腾出位置
 for (j = p->keynum; j > i; j--) {
   p->key[j + 1] = p->key[j];
   p->children[j + 1] = p->children[j];
 }

 // 插入新关键字k和子树指针q到目标位置
 p->key[i + 1] = k;
 p->children[i + 1] = q;

 if (q != NULL)
   q->parent = p; // 更新子树指针的父节点为当前结点p

 p->keynum++; // 增加结点p中的关键字数量
}


// totuma.cn
/**
* 将结点p分裂成两个结点，前一半保留，后一半移入结点q。
* @param p - 待分裂的结点
* @param q - 分裂后的新结点
*/
void SplitBTNode(BTNode *&p, BTNode *&q) {
 int i;
 int s = (m + 1) / 2; // 计算分裂位置s，即后一半移入结点q
 q = (BTNode *)malloc(sizeof(BTNode)); // 为新结点q分配空间

 // 后一半关键字和子树指针从结点p移动到结点q
 q->children[0] = p->children[s];
 for (i = s + 1; i <= m; i++) {
   q->key[i - s] = p->key[i];
   q->children[i - s] = p->children[i];
 }
 
 q->keynum = p->keynum - s; // 更新新结点q的关键字数量
 q->parent = p->parent;    // 更新新结点q的父节点指针

 // 更新子树指针的父节点指针为新结点q
 for (i = 0; i <= p->keynum - s; i++)
   if (q->children[i] != NULL)
     q->children[i]->parent = q;

 p->keynum = s - 1; // 更新结点p的关键字数量，前一半保留
}


// totuma.cn
/**
* 生成新的根结点t，原p和q为子树指针。
* @param t - 新的根结点指针
* @param k - 新的根结点的关键字
* @param p - 原根结点的左子树
* @param q - 原根结点的右子树
*/
void NewRoot(BTNode *&t, ElemType k, BTNode *p, BTNode *q) {
 t = (BTNode *)malloc(sizeof(BTNode)); // 分配空间
 t->keynum = 1; // 根结点的关键字数量为1
 t->children[0] = p; // 左子树指针指向原p
 t->children[1] = q; // 右子树指针指向原q
 t->key[1] = k; // 新根结点的关键字为k

 if (p != NULL) // 调整结点p和结点q的双亲指针
   p->parent = t;
 if (q != NULL)
   q->parent = t;
 t->parent = NULL; // 新根结点的双亲为空
}


// totuma.cn
/**
* 在B树t中插入关键字k，如果需要，进行结点分裂和根结点更新操作
* @param t - B树的根结点指针
* @param i - 插入位置，表示在结点t的第i个关键字之后插入k
* @param k - 要插入的关键字
* @param p - 结点t的双亲结点指针
*/
void InsertBTree(BTree &t, int i, ElemType k, BTNode *p) {
 BTNode *q; // 用于指向可能需要分裂的子节点
 int finish_tag, newroot_tag, s; // 设定需要新结点标志和插入完成标志
 ElemType x;
 if (p == NULL)               // t是空树
   NewRoot(t, k, NULL, NULL); // 生成仅含关键字k的根结点t
 else {
   x = k;           // 将变量x的值设置为待插入的关键字k
   q = NULL;        // 将指针变量q初始化为NULL，用于指向可能需要分裂的子节点
   finish_tag = 0;  // 初始化finish_tag为0，表示插入尚未完成
   newroot_tag = 0; // 初始化newroot_tag为0，表示不需要创建新的根节点
   while (finish_tag == 0 && newroot_tag == 0) {
     InsertBTNode(p, i, x, q); // 将关键字x和结点q分别插入到p->key[i+1]和p->children[i+1]
     if (p->keynum <= Max)
       finish_tag = 1; // 插入完成
     else {
       s = (m + 1) / 2;
       SplitBTNode(p, q); // 分裂结点
       x = p->key[s];
       if (p->parent) { // 查找x的插入位置
         p = p->parent;
         i = SearchBTNode(p, x);
       }
       else // 没找到x，需要新结点
         newroot_tag = 1;
     }
   }
   if (newroot_tag == 1)  // 根结点已分裂为结点p和q
     NewRoot(t, x, p, q); // 生成新根结点t,p和q为子树指针
 }
}


// totuma.cn
/**
* 从结点p中删除关键字p->key[i]和对应的孩子指针p->children[i]。
* @param p - 目标结点
* @param i - 要删除的关键字位置
*/
void Remove(BTNode *p, int i) {
 int j;

 // 使用循环将后续的关键字和孩子指针前移，覆盖要删除的关键字和孩子指针
 for (j = i + 1; j <= p->keynum; j++) {
   p->key[j - 1] = p->key[j];
   p->children[j - 1] = p->children[j];
 }

 p->keynum--; // 减少结点p的关键字数量，实现删除操作
}


// totuma.cn
/**
* 查找被删除关键字 p->key[i]（在非叶子结点中）的替代叶子结点，即右子树中值最小的关键字。
* @param p - 目标结点，非叶子结点
* @param i - 被删除关键字的位置
*/
void Substitution(BTNode *p, int i) {
 BTNode *q;

 // 从当前结点p的右子树开始，一直向左下遍历，找到右子树中的最小关键字所在的叶子结点
 for (q = p->children[i]; q->children[0] != NULL; q = q->children[0])
   ;

 p->key[i] = q->key[1]; // 将找到的最小关键字值复制到原位置，用于替代被删除的关键字
}


// totuma.cn
/**
* 将双亲结点p中的最后一个关键字移入右结点q中，
* 将左结点aq中的最后一个关键字移入双亲结点p中。
* @param p - 双亲结点
* @param i - 从p的第i个孩子开始操作
*/
void MoveRight(BTNode *p, int i) {
 int j;
 BTNode *q = p->children[i];     // 获取右兄弟q
 BTNode *aq = p->children[i - 1]; // 获取左兄弟aq

 // 将右兄弟q中的所有关键字和孩子指针向后移动一位
 for (j = q->keynum; j > 0; j--) {
   q->key[j + 1] = q->key[j];
   q->children[j + 1] = q->children[j];
 }

 q->children[1] = q->children[0]; // 从双亲结点p移动关键字到右兄弟q中
 q->key[1] = p->key[i];           // 复制双亲结点p中的关键字值
 q->keynum++;

 p->key[i] = aq->key[aq->keynum]; // 将左兄弟aq中最后一个关键字移动到双亲结点p中
 p->children[i]->children[0] = aq->children[aq->keynum]; // 更新孩子指针
 aq->keynum--; // 减少左兄弟aq的关键字数量
}


// totuma.cn
/**
* 将双亲结点p中的第一个关键字移入左结点aq中，
* 将右结点q中的第一个关键字移入双亲结点p中。
*
* @param p - 双亲结点
* @param i - 从p的第i个孩子开始操作
*/
void MoveLeft(BTNode *p, int i) {
 int j;
 BTNode *aq = p->children[i - 1]; // 获取左兄弟aq
 BTNode *q = p->children[i];     // 获取右兄弟q

 aq->keynum++;                // 将双亲结点p中的关键字移动到左兄弟aq中
 aq->key[aq->keynum] = p->key[i];          // 复制双亲结点p中的关键字值
 aq->children[aq->keynum] = p->children[i]->children[0]; // 更新孩子指针

 p->key[i] = q->key[1];  // 把右兄弟q中的关键字移动到双亲节点p中
 q->children[0] = q->children[1]; // 更新右兄弟q的孩子指针
 q->keynum--;

 // 将右兄弟q中的所有关键字和孩子指针向前移动一位
 for (j = 1; j <= aq->keynum; j++) {
   aq->key[j] = aq->key[j + 1];
   aq->children[j] = aq->children[j + 1];
 }
}


// totuma.cn
/**
* 将双亲结点p、右结点q合并入左结点aq，并调整双亲结点p中的剩余关键字的位置。
*
* @param p - 双亲结点
* @param i - 从p的第i个孩子开始合并
*/
void Combine(BTNode *p, int i) {
 int j;
 BTNode *q = p->children[i];     // 获取右兄弟结点q
 BTNode *aq = p->children[i - 1]; // 获取左兄弟结点aq

 aq->keynum++;               // 将双亲结点的关键字p->key[i]插入到左结点aq
 aq->key[aq->keynum] = p->key[i];
 aq->children[aq->keynum] = q->children[0];

 for (j = 1; j <= q->keynum; j++) { // 将右结点q中的所有关键字插入到左结点aq
   aq->keynum++;
   aq->key[aq->keynum] = q->key[j];
   aq->children[aq->keynum] = q->children[j];
 }

 for (j = i; j < p->keynum; j++) { // 将双亲结点p中的p->key[i]后的所有关键字向前移动一位
   p->key[j] = p->key[j + 1];
   p->children[j] = p->children[j + 1];
 }
 p->keynum--; // 修改双亲结点p的keynum值
 free(q);     // 释放空右结点q的空间
}


// totuma.cn
/**
* 删除结点p中的第i个关键字后，调整B树的结构。
* 如果必要，进行关键字的移动或合并操作。
* @param p - 待调整的结点
* @param i - 被删除关键字的索引
*/
void AdjustBTree(BTNode *p, int i) {
 if (i == 0) { // 删除的是最左边的关键字
   if (p->children[1]->keynum > Min) // 右结点可以借
     MoveLeft(p, 1);
   else // 右兄弟不够借，需要合并
     Combine(p, 1);
 } else if (i == p->keynum) { // 删除的是最右边的关键字
   if (p->children[i - 1]->keynum > Min) // 左结点可以借
     MoveRight(p, i);
   else // 左兄弟不够借，需要合并
     Combine(p, i);
 } else if (p->children[i - 1]->keynum > Min) { // 删除关键字在中部且左结点够借
   MoveRight(p, i);
 } else if (p->children[i + 1]->keynum > Min) { // 删除关键字在中部且右结点够借
   MoveLeft(p, i + 1);
 } else { // 删除关键字在中部且左右结点都不够借，需要合并
   Combine(p, i);
 }
}


// totuma.cn
/**
* 在结点p中查找关键字k并更新i的值以指示查找结果。
* @param p - 当前要查找的结点
* @param k - 要查找的关键字
* @param i - 输出参数，指示查找结果：
*            -1 表示未找到关键字k；
*             0 表示关键字k小于结点p中的第一个关键字；
*             1 到 keynum 表示找到关键字k的位置。
* @return - 如果找到关键字k，返回1；否则返回0。
*/
int FindBTNode(BTNode *p, ElemType k, int &i) {
 if (k < p->key[1]) { // 如果关键字k小于结点p中的第一个关键字
   i = 0;            // 查找失败，设置i为0
 } else { // 在结点p中查找
   i = p->keynum;     // 初始化i为结点p的关键字数量
   while (k < p->key[i] && i > 1) // 从后往前查找关键字k的位置
     i--;
   if (k == p->key[i]) // 找到关键字k
     return 1;        // 返回查找成功标志
 }
 return 0;            // 未找到关键字k，返回查找失败标志
}


// totuma.cn
/**
* 在结点p中查找并删除关键字k。
* @param p - 当前要查找和删除关键字的结点
* @param k - 要删除的关键字
* @return - 如果成功删除关键字k，返回1；否则返回0。
*/
int BTNodeDelete(BTNode *p, ElemType k) {
 int i;
 int found_tag; // 查找标志

 if (p == NULL)
   return 0; // 结点p为空，查找失败

 found_tag = FindBTNode(p, k, i); // 在结点p中查找关键字k，返回查找结果

 if (found_tag == 1) { // 查找成功
   if (p->children[i - 1] != NULL) { // 删除的是非叶子结点
     Substitution(p, i); // 寻找相邻关键字(右子树中最小的关键字)
     BTNodeDelete(p->children[i], p->key[i]); // 递归删除关键字k
   } else
     Remove(p, i); // 从结点p中位置i处删除关键字k
 } else
   found_tag = BTNodeDelete(p->children[i], k); // 沿孩子结点递归查找并删除关键字k

 if (p->children[i] != NULL)
   if (p->children[i]->keynum < Min) // 删除后关键字个数小于Min
     AdjustBTree(p, i); // 调整B树

 return found_tag; // 返回查找和删除结果标志
}


// totuma.cn
// 构建删除框架，执行删除操作
void BTreeDelete(BTree &t, ElemType k) {
  BTNode *p;
  int a = BTNodeDelete(t, k); // 删除关键字k
  if (a == 0)                 // 查找失败
    printf("   关键字%d不在B树中\n", k);
  else if (t->keynum == 0) { // 调整
    p = t;
    t = t->children[0];
    free(p);
  }
}

// 递归释放B树
void DestroyBTree(BTree &t) {
  int i;
  BTNode *p = t;
  if (p != NULL) { // B树不为空
    for (i = 0; i <= p->keynum; i++) { // 递归释放每一个结点
      DestroyBTree(*&p->children[i]);
    }
    free(p);
  }
  t = NULL;
}

// 初始化队列
Status InitQueue(LinkList &L) {
  L = (LNode *)malloc(sizeof(LNode)); // 分配结点空间
  if (L == NULL)                      // 分配失败
    return OVERFLOW;
  L->next = NULL;
  return OK;
}

// 新建一个结点
LNode *CreateNode(BTNode *p) {
  LNode *q;
  q = (LNode *)malloc(sizeof(LNode)); // 分配结点空间
  if (q != NULL) { // 分配成功
    q->data = p;
    q->next = NULL;
  }
  return q;
}

// 元素q入队列
Status Enqueue(LNode *p, BTNode *q) {
  if (p == NULL)
    return ERROR;
  while (p->next != NULL) // 调至队列最后
    p = p->next;
  p->next = CreateNode(q); // 生成结点让q进入队列
  return OK;
}

// 出队列，并以q返回值
Status Dequeue(LNode *p, BTNode *&q) {
  LNode *aq;
  if (p == NULL || p->next == NULL) // 删除位置不合理
    return ERROR;
  aq = p->next; // 修改被删结点aq的指针域
  p->next = aq->next;
  q = aq->data;
  free(aq); // 释放结点aq
  return OK;
}

// 队列判空
Status IfEmpty(LinkList L) {
  if (L == NULL) // 队列不存在
    return ERROR;
  if (L->next == NULL) // 队列为空
    return TRUE;
  return FALSE; // 队列非空
}

// 销毁队列
void DestroyQueue(LinkList L) {
  LinkList p;
  if (L != NULL) {
    p = L;
    L = L->next;
    free(p); // 逐一释放
    DestroyQueue(L);
  }
}

// 用队列遍历输出B树
Status Traverse(BTree t, LinkList L, int newline, int sum) {
  int i;
  BTree p;
  if (t != NULL) {
    printf("  [ ");
    Enqueue(L, t->children[0]); // 入队
    for (i = 1; i <= t->keynum; i++) {
      printf(" %d ", t->key[i]);
      Enqueue(L, t->children[i]); // 子结点入队
    }
    sum += t->keynum + 1;
    printf("]");
    if (newline == 0) { // 需要另起一行
      printf("\n");
      newline = sum - 1;
      sum = 0;
    }
    else
      newline--;
  }

  if (IfEmpty(L) == FALSE) {                               // l不为空
    Dequeue(L, p);                // 出队，以p返回
    Traverse(p, L, newline, sum); // 遍历出队结点
  }
  return OK;
}

// 输出B树
Status PrintBTree(BTree t) {
  LinkList L;
  if (t == NULL) {
    printf("  B树为空树");
    return OK;
  }
  InitQueue(L);         // 初始化队列
  Traverse(t, L, 0, 0); // 利用队列输出
  DestroyQueue(L);      // 销毁队列
  return OK;
}


// totuma.cn
int main() {
  BTNode *t = NULL;
  Result s; // 设定查找结果
  int i, n;
  ElemType k;
  ElemType a[] = {25, 38, 49, 60, 80, 90, 99, 88, 83, 87, 70, 92, 93, 94, 73, 74, 75};
  n = sizeof(a) / sizeof(ElemType);
  printf("创建一棵%d阶B树:\n", m);
  for (i = 0; i < n; i++) { // 逐一插入元素
    s = SearchBTree(t, a[i]);
    // 未查找到才插入
    if (s.tag == 0)
      InsertBTree(t, s.i, a[i], s.pt);
    printf("   第%d步,插入元素%d:\n ", i + 1, a[i]);
    PrintBTree(t);
  }

  printf("\n");
  printf("删除操作:\n");
  k=25;
  BTreeDelete(t,k);
  printf("  删除%d:\n ",k);
  printf("  删除后的B树: \n");
  PrintBTree(t);
  printf("\n");

  k=1;
  BTreeDelete(t,k);
  printf("  删除%d:\n ",k);
  printf("  删除后的B树: \n");
  PrintBTree(t);
  printf("\n");

  printf("  递归释放B树\n"); // 递归释放B树
  DestroyBTree(t);
  PrintBTree(t);
  return 0;
}