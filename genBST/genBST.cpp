#include "genBST.h"

template<class T>
void BST<T>::clear(BSTNode<T>* p) {
    if (p != 0) {
        clear(p->left); //递归删除左侧
        clear(p->right);//递归删除右侧
        delete p;//递归体，左右都没有后释放p指针指向的对象
    }
}

template<class T>
void BST<T>::insert(const T& el) {
    BSTNode<T>* p = root, * prev = 0;
    while (p != 0) {  //找到空的位置来存放新节点
        prev = p;   //当前节点指针设为前指针
        if (el < p->el) //如果要插入的值小于当前节点的值，则向左搜索，将当前指针指向左边
            p = p->left;
        else p = p->right;//反之指向右边
    }
    if (root == 0)    // 如果树为空，则直接插入当前节点在root上
        root = new BSTNode<T>(el);
    else if (el < prev->el)  //如果要插入的值小于空位置之上的节点，就占据左边的空节点，反之则占据右边的空节点
        prev->left = new BSTNode<T>(el);
    else prev->right = new BSTNode<T>(el);
}

template<class T>
void BST<T>::recursiveInsert(BSTNode<T>*& p, const T& el) {//上面insert的递归实现方式
    if (p == 0)
        p = new BSTNode<T>(el);
    else if (el < p->el)
        recursiveInsert(p->left, el);
    else recursiveInsert(p->right, el);
}

template<class T>
T* BST<T>::search(BSTNode<T>* p, const T& el) const {//搜索，代码简单，不注释了
    while (p != 0)
        if (el == p->el)
            return &p->el;
        else if (el < p->el)
            p = p->left;
        else p = p->right;
    return 0;
}

template<class T>
T* BST<T>::recursiveSearch(BSTNode<T>* p, const T& el) const {//搜索的递归实现
    if (p != 0)
        if (el == p->el)
            return &p->el;
        else if (el < p->el)
            return recursiveSearch(p->left, el);
        else return recursiveSearch(p->right, el);
    else return 0;
}

template<class T>
void BST<T>::inorder(BSTNode<T>* p) {//中序遍历，在第二次经过该节点的时候打印
    if (p != 0) {
        inorder(p->left);//先遍历左边的
        visit(p);//遍历到左边的最末端，打印当前值
        inorder(p->right);//打印完后再向右遍历一个节点，如果没有就弹出，打印上一个节点，并遍历上一个节点的右侧
    }
}

template<class T>
void BST<T>::preorder(BSTNode<T>* p) {//前序遍历，在第一次经过改节点的时候打印
    if (p != 0) {
        visit(p);
        preorder(p->left);
        preorder(p->right);
    }
}

template<class T>
void BST<T>::postorder(BSTNode<T>* p) {//后序遍历，在第三次经过该节点的时候打印
    if (p != 0) {
        postorder(p->left);
        postorder(p->right);
        visit(p);
    }
}

template<class T>
void BST<T>::deleteByCopying(BSTNode<T>*& node) {
    BSTNode<T>* previous, * tmp = node;
    if (node->right == 0)                  // node has no right child;
        node = node->left;
    else if (node->left == 0)              // node has no left child;
        node = node->right;
    else {
        tmp = node->left                  // node has both children;
            previous = node;                  // 1.
        while (tmp->right != 0) {         // 2.
            previous = tmp;
            tmp = tmp->right;
        }
        node->el = tmp->el;               // 3.
        if (previous == node)
            previous->left = tmp->left;
        else previous->right = tmp->left; // 4.
    }
    delete tmp;                            // 5.
}

// findAndDeleteByCopying() searches the tree to locate the node containing
// el. If the node is located, the function DeleteByCopying() is called.

template<class T>
void BST<T>::findAndDeleteByCopying(const T& el) {
    BSTNode<T>* p = root, * prev = 0;
    while (p != 0 && !(p->el == el)) {
        prev = p;
        if (el < p->el)
            p = p->left;
        else p = p->right;
    }
    if (p != 0 && p->el == el)
        if (p == root)
            deleteByCopying(root);
        else if (prev->left == p)
            deleteByCopying(prev->left);
        else deleteByCopying(prev->right);
    else if (root != 0)
        cout << "el " << el << " is not in the tree\n";
    else cout << "the tree is empty\n";
}

template<class T>
void BST<T>::deleteByMerging(BSTNode<T>*& node) {
    BSTNode<T>* tmp = node;
    if (node != 0) {
        if (!node->right)           // node has no right child: its left
            node = node->left;     // child (if any) is attached to its parent;
        else if (node->left == 0)   // node has no left child: its right
            node = node->right;    // child is attached to its parent;
        else {                      // be ready for merging subtrees;
            tmp = node->left;      // 1. move left
            while (tmp->right != 0)// 2. and then right as far as possible;
                tmp = tmp->right;
            tmp->right =           // 3. establish the link between the
                node->right;        //    the rightmost node of the left
                                    //    subtree and the right subtree;
            tmp = node;            // 4.
            node = node->left;     // 5.
        }
        delete tmp;                 // 6.
    }
}

template<class T>
void BST<T>::findAndDeleteByMerging(const T& el) {
    BSTNode<T>* node = root, * prev = 0;
    while (node != 0) {
        if (node->el == el)
            break;
        prev = node;
        if (el < node->el)
            node = node->left;
        else node = node->right;
    }
    if (node != 0 && node->el == el)
        if (node == root)
            deleteByMerging(root);
        else if (prev->left == node)
            deleteByMerging(prev->left);
        else deleteByMerging(prev->right);
    else if (root != 0)
        cout << "el " << el << " is not in the tree\n";
    else cout << "the tree is empty\n";
}

template<class T>
void BST<T>::iterativePreorder() { //前序遍历的非递归实现
    Stack<BSTNode<T>*> travStack; //创建栈
    BSTNode<T>* p = root;
    if (p != 0) {
        travStack.push(p);          //将当前节点推出栈中
        while (!travStack.empty()) {
            p = travStack.pop();    //弹出刚刚推入栈的节点
            visit(p);               //打印弹出的节点
            if (p->right != 0)
                travStack.push(p->right);   //先将当前节点的右节点推入栈中
            if (p->left != 0)             
                travStack.push(p->left);    //再将左节点推入栈中，这样待会弹出来的就是左节点
        }
    }
}

template<class T>
void BST<T>::iterativeInorder() {
    Stack<BSTNode<T>*> travStack;
    BSTNode<T>* p = root;
    while (p != 0) {
        while (p != 0) {                 //这个循环直到当前节点为空为止
            if (p->right)                //如果当前节点有右节点就推入栈中
                travStack.push(p->right);
            travStack.push(p);          //将当前节点压入栈中
            p = p->left;                //向左遍历
        }
        p = travStack.pop();             //先弹出当前节点，此时完成第一次压栈
        while (!travStack.empty() && p->right == 0) { //逐步弹出到有节点有右节点为止
            visit(p);                                 //中途打印当前节点的值
            p = travStack.pop();
        }
        visit(p);                        //打印当前节点的值，此时当前节点有右节点，根据同级的第一个while循环，栈内还有该节点的右节点
        if (!travStack.empty())          
            p = travStack.pop();         //弹出右节点，然后继续以当前节点为根，重复while循环，向左遍历
        else p = 0;                      //当前节点的左节点前面肯定是遍历过了，如果还没有右节点，意味着已经遍历到最右端的叶节点
    }
}

template<class T>
void BST<T>::iterativePostorder() {
    Stack<BSTNode<T>*> travStack;
    BSTNode<T>* p = root, * q = root;
    while (p != 0) {
        for (; p->left != 0; p = p->left)
            travStack.push(p);
        while (p->right == 0 || p->right == q) {
            visit(p);
            q = p;
            if (travStack.empty())
                return;
            p = travStack.pop();
        }
        travStack.push(p);
        p = p->right;
    }
}

template<class T>
void BST<T>::breadthFirst() {
    Queue<BSTNode<T>*> queue;
    BSTNode<T>* p = root;
    if (p != 0) {
        queue.enqueue(p);
        while (!queue.empty()) {
            p = queue.dequeue();
            visit(p);
            if (p->left != 0)
                queue.enqueue(p->left);
            if (p->right != 0)
                queue.enqueue(p->right);
        }
    }
}

template<class T>
void BST<T>::MorrisInorder() {
    BSTNode<T>* p = root, * tmp;
    while (p != 0)
        if (p->left == 0) {
            visit(p);
            p = p->right;
        }
        else {
            tmp = p->left;
            while (tmp->right != 0 &&// go to the rightmost node of
                tmp->right != p)  // the left subtree or
                tmp = tmp->right;   // to the temporary parent of p;
            if (tmp->right == 0) {   // if 'true' rightmost node was
                tmp->right = p;     // reached, make it a temporary
                p = p->left;        // parent of the current root,
            }
            else {                   // else a temporary parent has been
                visit(p);           // found; visit node p and then cut
                tmp->right = 0;     // the right pointer of the current
                p = p->right;       // parent, whereby it ceases to be
            }                        // a parent;
        }
}

template<class T>
void BST<T>::MorrisPreorder() {
    BSTNode<T>* p = root, * tmp;
    while (p != 0) {
        if (p->left == 0) {
            visit(p);
            p = p->right;
        }
        else {
            tmp = p->left;
            while (tmp->right != 0 &&// go to the rightmost node of
                tmp->right != p)  // the left subtree or
                tmp = tmp->right;   // to the temporary parent of p;
            if (tmp->right == 0) {   // if 'true' rightmost node was
                visit(p);           // reached, visit the root and
                tmp->right = p;     // make the rightmost node a temporary
                p = p->left;        // parent of the current root,
            }
            else {                   // else a temporary parent has been
                tmp->right = 0;     // found; cut the right pointer of
                p = p->right;       // the current parent, whereby it ceases
            }                        // to be a parent;
        }
    }
}

template<class T>
void BST<T>::MorrisPostorder() {
    BSTNode<T>* p = new BSTNode<T>(), * tmp, * q, * r, * s;
    p->left = root;
    while (p != 0)
        if (p->left == 0)
            p = p->right;
        else {
            tmp = p->left;
            while (tmp->right != 0 &&// go to the rightmost node of
                tmp->right != p)  // the left subtree or
                tmp = tmp->right;   // to the temporary parent of p;
            if (tmp->right == 0) {   // if 'true' rightmost node was
                tmp->right = p;     // reached, make it a temporary
                p = p->left;        // parent of the current root,
            }
            else {             // else a temporary parent has been found;
                 // process nodes between p->left (included) and p (excluded)
                 // extended to the right in modified tree in reverse order;
                 // the first loop descends this chain of nodes and reverses
                 // right pointers; the second loop goes back, visits nodes,
                 // and reverses right pointers again to restore the pointers
                 // to their original setting;
                for (q = p->left, r = q->right, s = r->right;
                    r != p; q = r, r = s, s = s->right)
                    r->right = q;
                for (s = q->right; q != p->left;
                    q->right = r, r = q, q = s, s = s->right)
                    visit(q);
                visit(p->left);     // visit node p->left and then cut
                tmp->right = 0;     // the right pointer of the current
                p = p->right;       // parent, whereby it ceases to be
            }                        // a parent;
        }
}

template<class T>
void BST<T>::balance(T data[], int first, int last) {
    if (first <= last) {
        int middle = (first + last) / 2;
        insert(data[middle]);
        balance(data, first, middle - 1);
        balance(data, middle + 1, last);
    }
}