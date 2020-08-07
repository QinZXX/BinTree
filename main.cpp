#include <iostream>

using namespace std;

#define DataType int

/*����AVL���Ľڵ�*/
typedef struct AvlNode{
    DataType    data;
    AvlNode    * m_pLeft;
    AvlNode    * m_pRight;
    int height;
}*AvlTree,*Position,AvlNode;

int Max(int a,int b){
    return a>b?a:b;
}
//�����ĸ߶�
int Height( AvlTree T){
    return nullptr==T? -1:T->height;
}

//����ת����  LL
AvlTree singleRotateWithRight(AvlTree T){
    AvlTree L = T->m_pLeft;
    T->m_pLeft = L->m_pRight;
    L->m_pRight = T;
    T->height = Max( Height(T->m_pLeft),Height(T->m_pRight) ) + 1;
    L->height = Max( Height(L->m_pLeft),Height(L->m_pRight) ) + 1;
    return L;    //��ʱL��Ϊ���ڵ���
}
//����ת����  RR
AvlTree singleRotateWithLeft(AvlTree T){
    AvlTree R = T->m_pRight;
    T->m_pRight = R->m_pLeft;
    R->m_pLeft = T;
    T->height = Max( Height(T->m_pLeft),Height(T->m_pRight) ) + 1;
    R->height = Max( Height(R->m_pLeft),Height(R->m_pRight) ) + 1;
    return R;    //��ʱR��Ϊ���ڵ��ˣ��ɲο�AVL�Ĳ�����������������ͼ��
}
//˫��ת���������  LR
AvlTree doubleRotateWithLeft(AvlTree T)     {  //�������
    T->m_pLeft = singleRotateWithLeft(T->m_pLeft);
    return singleRotateWithRight(T);
}
//˫��ת�����Һ���  RL
AvlTree doubleRotateWithRight(AvlTree T)   { //���Һ���
    T->m_pRight = singleRotateWithRight(T->m_pRight);
    return singleRotateWithLeft(T);
}
AvlTree AvlTreeInsert(AvlTree T, DataType x){
    if(T == nullptr)  {  //�����Ϊ��
        if(T = (AvlNode *)malloc(sizeof(AvlNode))) {
            T->data = x;
            T->m_pLeft  = nullptr;
            T->m_pRight = nullptr;
            T->height = 0;
        }
        else{
            cout << "Out of memory!" << endl;
            exit(0);
        }
    }
    else if( x < T->data)     {   //������뵽T������������
        T->m_pLeft = AvlTreeInsert(T->m_pLeft,x);    //�Ȳ��룬����ת
        if(Height(T->m_pLeft) - Height(T->m_pRight) == 2)  {//
            if(x < T->m_pLeft->data)     {   //���������ֻ��Ҫ����ת
                T = singleRotateWithRight( T );
            }
            else                   {         //���������˫��ת,����
                T = doubleRotateWithLeft( T );
            }
        }
    }
    else if( x > T->data ){
        T->m_pRight = AvlTreeInsert(T->m_pRight,x);
        if(Height(T->m_pRight) - Height(T->m_pLeft) == 2)
        {
            if(x > T->m_pRight->data)   {     //�����������������
                T = singleRotateWithLeft( T );
            }
            else                 {           //���������˫��ת,����
                T = doubleRotateWithRight( T );
            }
        }
    }
    //���������Ѿ����ڣ���ô�����в���
    T->height = Max(Height(T->m_pLeft),Height(T->m_pRight)) + 1;
    return T;
}
//�ݹ�ʵ���������
void inOrderVisitUseRecur(const AvlTree pCurrent){
    if(pCurrent){
        inOrderVisitUseRecur(pCurrent->m_pLeft);
        cout << pCurrent->data << " ";
        if(pCurrent->m_pLeft)
            cout << " leftChild: "<<pCurrent->m_pLeft->data;
        else
            cout << " leftChild: "<<"nullptr" ;
        if(pCurrent->m_pRight)
            cout << " rightChild: "<<pCurrent->m_pRight->data;
        else
            cout << " rightChild: "<< "nullptr";
        cout << endl;
        inOrderVisitUseRecur(pCurrent->m_pRight);
    }
}

int main(){
    AvlTree root = nullptr;
    root = AvlTreeInsert(root,1);
    root = AvlTreeInsert(root,2);
    root = AvlTreeInsert(root,3);
    root = AvlTreeInsert(root,4);
    root = AvlTreeInsert(root,5);
    root = AvlTreeInsert(root,6);
    root = AvlTreeInsert(root,7);
    root = AvlTreeInsert(root,8);
    root = AvlTreeInsert(root,9);
    root = AvlTreeInsert(root,10);
    root = AvlTreeInsert(root,11);
    root = AvlTreeInsert(root,12);
    root = AvlTreeInsert(root,13);
    root = AvlTreeInsert(root,14);
    root = AvlTreeInsert(root,15);
    inOrderVisitUseRecur(root);
    return 0;
}