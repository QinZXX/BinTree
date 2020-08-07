#ifndef AVL_TREE_H
#define AVL_TREE_H

template <typename T>
class avltree {
public:
    struct Node {
        Node(T x)
                : val(x), left(nullptr), right(nullptr) {}
        Node(const Node* n)
                : val(n->val), left(n->left), right(n->right) {}
        T val;
        Node* left;
        Node* right;
    };
public:
    avltree() : root(nullptr) {}
    ~avltree(){
        destroy(root);
    }
    void insert(const T& val){
        root = insert(root, val);
    }
    void remove(const T& val){
        root = remove(root, val);
    }
    Node* get_root(){
        return root;
    }
    static int balance_fector(Node* node){
        if (node == nullptr)
            return 0;
        return height(node->left) - height(node->right);
    }

private:
    void destroy(Node* node){
        if (node != nullptr){
            destroy(node->left);
            destroy(node->right);
            delete node;
        }
    }
    Node* insert(Node* node, const T& val){
        if (node == nullptr)
            return new Node(val);

        if (val == node->val)
            return node;
        if (val < node->val)
            node->left = insert(node->left, val);
        else
            node->right = insert(node->right, val);

        return rebalance(node);
    }
    Node* remove(Node* node, const T& val){
        if (node == nullptr) return node;
        if (val < node->val){
            node->left = remove(node->left, val);
        }
        else if (val > node->val){
            node->right = remove(node->right, val);
        }
        else{
            if (node->left == nullptr){
                Node* del = node;
                node = node->right;
                delete del;
            }
            else if (node->right == nullptr){
                Node* del = node;
                node = node->left;
                delete del;
            }
            else{
                Node* successor = new Node(minimum(node->right));
                node->right = remove(node->right, successor->val);
                successor->left = node->left;
                successor->right = node->right;
                delete node;
                node = successor;
            }
        }
        return rebalance(node);
    }
    Node* minimum(Node* node){
        while (node->left){
            node = node->left;
        }
        return node;
    }

    Node* rebalance(Node* node){
        int fector = balance_fector(node);
        if (fector == 2){
            if (balance_fector(node->left) > 0)
                node = rightRotate(node);
            else
                node = leftRightRotate(node);
        }
        if (fector == -2){
            if (balance_fector(node->right) < 0)
                node = leftRotate(node);
            else
                node = rightLeftRotate(node);
        }
        return node;
    }
    static int height(Node* node){
        if (node == nullptr)
            return 0;
        return std::max(height(node->left), height(node->right)) + 1;
    }
    Node* rightRotate(Node* node)  {//LL
        Node* left = node->left;
        node->left = left->right;
        left->right = node;
        return left;
    }
    Node* leftRotate(Node* node)  {//RR
        Node* right = node->right;
        node->right = right->left;
        right->left = node;
        return right;
    }
    Node* leftRightRotate(Node* node) {//LR
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    Node* rightLeftRotate(Node* node)  {//RL
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

private:
    Node* root;
};

#endif
