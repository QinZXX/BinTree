#include <iostream>

#define TRUE 1
#define FALSE 0
#define ElemType int
#define  KeyType int

/* �����������Ľڵ�ṹ���� */
typedef struct BiTNode{
    int data;
    struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;

//���������������㷨
int SearchBST(BiTree T, KeyType key, BiTree f, BiTree *p) {
    while(true) {
        //��� T ָ��Ϊ�գ�˵������ʧ�ܣ��� p ָ��ָ����ҹ��������һ��Ҷ�ӽ�㣬�����ز���ʧ�ܵ���Ϣ
        if (!T) {
            *p = f;
            return FALSE;
        }
        //�����ȣ��� p ָ��ָ��ùؼ��֣������ز��ҳɹ���Ϣ
        else if (key == T->data) {
            *p = T;
            return TRUE;
        }
        //��� key ֵ�� T ������ֵС�������������������֮��������������
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
    //δ�ҵ�ʱ��temp=nullptr���˳�ѭ��������nullptr
    return nullptr;//������T����Ϊ���������
}

int InsertBST(BiTree& T, ElemType e) {
    BiTree p = nullptr;
    //������Ҳ��ɹ��������������
    if (!SearchBST(T, e, nullptr, &p)) {
        //��ʼ��������
        BiTree s = (BiTree)malloc(sizeof(BiTNode));
        s->data = e;
        s->lchild = s->rchild = nullptr;
        //��� p ΪNULL��˵���ö���������Ϊ��������ʱ����Ľ��Ϊ�������ĸ����
        if (!p) {
            T = s;
        }
        //��� p ��Ϊ NULL���� p ָ���Ϊ����ʧ�ܵ����һ��Ҷ�ӽ�㣬ֻ��Ҫͨ���Ƚ� p �� e ��ֵȷ�� s ������ p �����ӻ����Һ���
        else{
            (e< p->data)? (p->lchild=s): (p->rchild=s);
        }
        return TRUE;
    }
    //������ҳɹ�������Ҫ���������������ʧ��
    return FALSE;
}

//ɾ������
int Delete(BiTree& p){
    BiTree q, s;
    //��� 1����� p ����ΪҶ�ӽ�㣬ֱ��ɾ������
    if (!p->lchild && !p->rchild) {
        free(p);
        p = nullptr;
    }
    else if (!p->lchild) { //������Ϊ�գ�ֻ���ý�� p ������������������ p ���ɣ�
        q = p;
        p = p->rchild;
        free(q);
    }
    else if (!p->rchild) {//������Ϊ�գ�ֻ���ý�� p ������������������ p ���ɣ�
        q = p;
        p = p->lchild;//���ﲻ��ָ�� *p ָ�������������ǽ��������洢�Ľ��ĵ�ַ��ֵ��ָ����� p
        free(q);
    }
    else {  //������������Ϊ�գ�
        // �ҵ�������������С�ڵ㣬Ȼ����p�滻����ɾ����С�ڵ㡣��Ϊ��С�ڵ�϶���û���������ġ�
        // �����������İ��ҽڵ�ƴ�ӹ�ȥ
        q=p;
        s=q->rchild;
        while(s->lchild){ // �������ǿ�,�ҵ�����������С�ڵ㣨p��ֱ�Ӻ�̣�
            q=s;
            s=s->lchild;
        }// ��ʱ��sΪp������������С�ڵ�
        p->data=s->data;
        // ��С�ڵ�sȷ��û��������������������������û�С�
        // ��Ϊ��Ҫ����С�ڵ�ĸ��ڵ����ڵ�Ϊ�գ�ɾ����С�ڵ㣩��������Ҫһ��q��¼���ڵ�
        // ���Ȳ�����û���������������Բ�ȡֱ��������������������������ΪNULL��Ϊ�գ�
        // ��©������ǣ���С�ڵ����p���������ĸ��ڵ㣬��ʱ��״��һ��
        q==p? (q->rchild=s->rchild): (q->lchild=s->rchild);
        free(s);
    }
    return TRUE;
}

int DeleteBST(BiTree& T, int key){
    if (!T) {//�����ڹؼ��ֵ���key������Ԫ��
        return FALSE;
    }
    else{
        if (key == T->data) {
            Delete(T);
            return TRUE;
        }
        else if (key < T->data) {
            //ʹ�õݹ�ķ�ʽ
            return DeleteBST(T->lchild, key);
        }
        else {
            return DeleteBST(T->rchild, key);
        }
    }
}

void order(BiTree t){  //�������
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
    printf("�������������������\n");
    order(T);
    printf("\n");
    printf("ɾ��3���������������������\n");
    DeleteBST(T, 3);
    order(T);
}