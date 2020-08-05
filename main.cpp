#include <iostream>

#define TRUE 1
#define FALSE 0
#define ElemType int
#define  KeyType int

/* 二叉排序树的节点结构定义 */
typedef struct BiTNode{
    int data;
    struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;

//二叉排序树查找算法
int SearchBST(BiTree T, KeyType key, BiTree f, BiTree *p) {
    while(true) {
        //如果 T 指针为空，说明查找失败，令 p 指针指向查找过程中最后一个叶子结点，并返回查找失败的信息
        if (!T) {
            *p = f;
            return FALSE;
        }
        //如果相等，令 p 指针指向该关键字，并返回查找成功信息
        else if (key == T->data) {
            *p = T;
            return TRUE;
        }
        //如果 key 值比 T 根结点的值小，则查找其左子树；反之，查找其右子树
        else if (key < T->data) {
            f=T;
            T=T->lchild;
        } else {
            f=T;
            T=T->rchild;
        }
    }
}

BiTNode* findBST(const BiTree& T,KeyType key) {
    BiTNode* temp=T;
    while(temp!= nullptr){
        if (key==temp->data){
            return temp;
        }
        else{
            (key<temp->data)? (temp=temp->lchild):(temp=temp->rchild);
        }
    }
    //未找到时，temp=nullptr，退出循环。返回nullptr
    return nullptr;//包含了T本身为空树的情况
}

int InsertBST(BiTree& T, ElemType e) {
    BiTree p = nullptr;
    //如果查找不成功，需做插入操作
    if (!SearchBST(T, e, nullptr, &p)) {
        //初始化插入结点
        BiTree s = (BiTree)malloc(sizeof(BiTNode));
        s->data = e;
        s->lchild = s->rchild = nullptr;
        //如果 p 为NULL，说明该二叉排序树为空树，此时插入的结点为整棵树的根结点
        if (!p) {
            T = s;
        }
        //如果 p 不为 NULL，则 p 指向的为查找失败的最后一个叶子结点，只需要通过比较 p 和 e 的值确定 s 到底是 p 的左孩子还是右孩子
        else{
            (e< p->data)? (p->lchild=s): (p->rchild=s);
        }
        return TRUE;
    }
    //如果查找成功，不需要做插入操作，插入失败
    return FALSE;
}

//删除函数
int Delete(BiTree& p){
    BiTree q, s;
    //情况 1，结点 p 本身为叶子结点，直接删除即可
    if (!p->lchild && !p->rchild) {
        free(p);
        p = nullptr;
    }
    else if (!p->lchild) { //左子树为空，只需用结点 p 的右子树根结点代替结点 p 即可；
        q = p;
        p = p->rchild;
        free(q);
    }
    else if (!p->rchild) {//右子树为空，只需用结点 p 的左子树根结点代替结点 p 即可；
        q = p;
        p = p->lchild;//这里不是指针 *p 指向左子树，而是将左子树存储的结点的地址赋值给指针变量 p
        free(q);
    }
    else {  //左右子树均不为空，
        // 找到其右子树的最小节点，然后与p替换，再删除最小节点。因为最小节点肯定是没有左子树的。
        // 所以找上述的把右节点拼接过去
        q=p;
        s=q->rchild;
        while(s->lchild){ // 左子树非空,找到右子树的最小节点（p的直接后继）
            q=s;
            s=s->lchild;
        }// 此时，s为p的右子树的最小节点
        p->data=s->data;
        // 最小节点s确定没有左子树。可能有右子树或者没有。
        // 因为需要另最小节点的父节点的左节点为空（删除最小节点），所以需要一个q记录父节点
        // 首先不管有没有右子树，都可以采取直接上移右子树的做法（右子树为NULL或不为空）
        // 遗漏的情况是：最小节点就是p的右子树的根节点，此时形状不一样
        q==p? (q->rchild=s->rchild): (q->lchild=s->rchild);
        free(s);
    }
    return TRUE;
}

int DeleteBST(BiTree& T, int key){
    if (!T) {//不存在关键字等于key的数据元素
        return FALSE;
    }
    else{
        if (key == T->data) {
            Delete(T);
            return TRUE;
        }
        else if (key < T->data) {
            //使用递归的方式
            return DeleteBST(T->lchild, key);
        }
        else {
            return DeleteBST(T->rchild, key);
        }
    }
}

void order(BiTree t){  //中序输出
    if (t == nullptr) {
        return;
    }
    order(t->lchild);
    printf("%d ", t->data);
    order(t->rchild);
}

int main(){
    int i;
    int a[5] = { 3,4,2,5,9 };
    BiTree T = nullptr;
    for (i = 0; i < 5; i++) {
        InsertBST(T, a[i]);
    }
    printf("中序遍历二叉排序树：\n");
    order(T);
    printf("\n");
    printf("删除3后，中序遍历二叉排序树：\n");
    DeleteBST(T, 3);
    order(T);
}