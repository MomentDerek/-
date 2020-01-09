#include "genBST.h"

template<class T>
void BST<T>::clear(BSTNode<T>* p) {
    if (p != 0) {
        clear(p->left); //�ݹ�ɾ�����
        clear(p->right);//�ݹ�ɾ���Ҳ�
        delete p;//�ݹ��壬���Ҷ�û�к��ͷ�pָ��ָ��Ķ���
    }
}

template<class T>
void BST<T>::insert(const T& el) {
    BSTNode<T>* p = root, * prev = 0;
    while (p != 0) {  //�ҵ��յ�λ��������½ڵ�
        prev = p;   //��ǰ�ڵ�ָ����Ϊǰָ��
        if (el < p->el) //���Ҫ�����ֵС�ڵ�ǰ�ڵ��ֵ������������������ǰָ��ָ�����
            p = p->left;
        else p = p->right;//��ָ֮���ұ�
    }
    if (root == 0)    // �����Ϊ�գ���ֱ�Ӳ��뵱ǰ�ڵ���root��
        root = new BSTNode<T>(el);
    else if (el < prev->el)  //���Ҫ�����ֵС�ڿ�λ��֮�ϵĽڵ㣬��ռ����ߵĿսڵ㣬��֮��ռ���ұߵĿսڵ�
        prev->left = new BSTNode<T>(el);
    else prev->right = new BSTNode<T>(el);
}

template<class T>
void BST<T>::recursiveInsert(BSTNode<T>*& p, const T& el) {//����insert�ĵݹ�ʵ�ַ�ʽ
    if (p == 0)
        p = new BSTNode<T>(el);
    else if (el < p->el)
        recursiveInsert(p->left, el);
    else recursiveInsert(p->right, el);
}

template<class T>
T* BST<T>::search(BSTNode<T>* p, const T& el) const {//����������򵥣���ע����
    while (p != 0)
        if (el == p->el)
            return &p->el;
        else if (el < p->el)
            p = p->left;
        else p = p->right;
    return 0;
}

template<class T>
T* BST<T>::recursiveSearch(BSTNode<T>* p, const T& el) const {//�����ĵݹ�ʵ��
    if (p != 0)
        if (el == p->el)
            return &p->el;
        else if (el < p->el)
            return recursiveSearch(p->left, el);
        else return recursiveSearch(p->right, el);
    else return 0;
}

template<class T>
void BST<T>::inorder(BSTNode<T>* p) {//����������ڵڶ��ξ����ýڵ��ʱ���ӡ
    if (p != 0) {
        inorder(p->left);//�ȱ�����ߵ�
        visit(p);//��������ߵ���ĩ�ˣ���ӡ��ǰֵ
        inorder(p->right);//��ӡ��������ұ���һ���ڵ㣬���û�о͵�������ӡ��һ���ڵ㣬��������һ���ڵ���Ҳ�
    }
}

template<class T>
void BST<T>::preorder(BSTNode<T>* p) {//ǰ��������ڵ�һ�ξ����Ľڵ��ʱ���ӡ
    if (p != 0) {
        visit(p);
        preorder(p->left);
        preorder(p->right);
    }
}

template<class T>
void BST<T>::postorder(BSTNode<T>* p) {//����������ڵ����ξ����ýڵ��ʱ���ӡ
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
void BST<T>::iterativePreorder() { //ǰ������ķǵݹ�ʵ��
    Stack<BSTNode<T>*> travStack; //����ջ
    BSTNode<T>* p = root;
    if (p != 0) {
        travStack.push(p);          //����ǰ�ڵ��Ƴ�ջ��
        while (!travStack.empty()) {
            p = travStack.pop();    //�����ո�����ջ�Ľڵ�
            visit(p);               //��ӡ�����Ľڵ�
            if (p->right != 0)
                travStack.push(p->right);   //�Ƚ���ǰ�ڵ���ҽڵ�����ջ��
            if (p->left != 0)             
                travStack.push(p->left);    //�ٽ���ڵ�����ջ�У��������ᵯ�����ľ�����ڵ�
        }
    }
}

template<class T>
void BST<T>::iterativeInorder() {
    Stack<BSTNode<T>*> travStack;
    BSTNode<T>* p = root;
    while (p != 0) {
        while (p != 0) {                 //���ѭ��ֱ����ǰ�ڵ�Ϊ��Ϊֹ
            if (p->right)                //�����ǰ�ڵ����ҽڵ������ջ��
                travStack.push(p->right);
            travStack.push(p);          //����ǰ�ڵ�ѹ��ջ��
            p = p->left;                //�������
        }
        p = travStack.pop();             //�ȵ�����ǰ�ڵ㣬��ʱ��ɵ�һ��ѹջ
        while (!travStack.empty() && p->right == 0) { //�𲽵������нڵ����ҽڵ�Ϊֹ
            visit(p);                                 //��;��ӡ��ǰ�ڵ��ֵ
            p = travStack.pop();
        }
        visit(p);                        //��ӡ��ǰ�ڵ��ֵ����ʱ��ǰ�ڵ����ҽڵ㣬����ͬ���ĵ�һ��whileѭ����ջ�ڻ��иýڵ���ҽڵ�
        if (!travStack.empty())          
            p = travStack.pop();         //�����ҽڵ㣬Ȼ������Ե�ǰ�ڵ�Ϊ�����ظ�whileѭ�����������
        else p = 0;                      //��ǰ�ڵ����ڵ�ǰ��϶��Ǳ������ˣ������û���ҽڵ㣬��ζ���Ѿ����������Ҷ˵�Ҷ�ڵ�
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