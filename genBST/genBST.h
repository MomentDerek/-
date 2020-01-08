#include <queue>
#include <stack>

#ifndef BINARY_SEARCH_TREE
#define BINARY_SEARCH_TREE

template<class T>
class Stack : public stack<T> {
public:
    T pop() {
        T tmp = top();
        stack<T>::pop();
        return tmp;
    }
};

template<class T>
class Queue : public queue<T> {
public:
    T dequeue() {
        T tmp = front();
        queue<T>::pop();
        return tmp;
    }
    void enqueue(const T& el) {
        push(el);
    }
};
template<class T> class BST;

template<class T>
class BSTNode {
public:
    BSTNode() {
        left = right = 0;
    }
    BSTNode(const T& e, BSTNode<T>* l = 0, BSTNode<T>* r = 0) {
        el = e; left = l; right = r;
    }
    T el;
    BSTNode<T>* left, * right;
};

template<class T>
class BST {
public:
    BST() {
        root = 0;
    }
    ~BST() {
        clear();
    }
    void clear() {
        clear(root);
        root = 0;
    }
    bool isEmpty() const {
        return root == 0;
    }
    void preorder() {
        preorder(root); //参见下面protected部分
    }
    void inorder() {
        inorder(root); //参见下面protected部分
    }
    void postorder() {
        postorder(root); //参见下面protected部分
    }
    void insert(const T&);
    void recursiveInsert(const T& el) {
        recursiveInsert(root, el); //参见下面protected部分
    }
    T* search(const T& el) const {
        return search(root, el); //参见下面protected部分
    }
    T* recursiveSearch(const T& el) const {
        return recursiveSearch(root, el); //参见下面protected部分
    }
    void deleteByCopying(BSTNode<T>*&);
    void findAndDeleteByCopying(const T&);
    void deleteByMerging(BSTNode<T>*&);
    void findAndDeleteByMerging(const T&);
    void iterativePreorder();
    void iterativeInorder();
    void iterativePostorder();
    void breadthFirst();
    void MorrisPreorder();
    void MorrisInorder();
    void MorrisPostorder();
    void balance(T data[], int, int);
protected:
    BSTNode<T>* root;
    void clear(BSTNode<T>*);
    void recursiveInsert(BSTNode<T>*&, const T&);
    T* search(BSTNode<T>*, const T&) const;
    T* recursiveSearch(BSTNode<T>*, const T&) const;
    void preorder(BSTNode<T>*);
    void inorder(BSTNode<T>*);
    void postorder(BSTNode<T>*);
    virtual void visit(BSTNode<T>* p) {
        cout << p->el << ' ';
    }
}; 
#endif