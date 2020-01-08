//singly linked list class to store integers保存整数的单向链表
#ifndef INT_LINKED_LIST
#define INT_LINKED_LIST

class IntSLLNode
{
public:
	int info;
	IntSLLNode* next;
	IntSLLNode() {
		next = 0;
	}
	IntSLLNode(int el, IntSLLNode* ptr = 0) {
		info = el;
		next = ptr;
	}
};

class IntSLList
{
public:
	IntSLList();
	~IntSLList();
	int isEmpty();
	void addToHead(int);
	void addToTail(int);
	int deleteFromHead();
	int deleteFromTail();
	void deleteNode(int);
	bool isInList(int) const;
	void addListToTail(IntSLList* addList);
	IntSLList* mergeList(IntSLList* frontList, IntSLList* backList) const;
	void printList();

private:
	IntSLLNode* head, * tail;
};
#endif // !INT_LINKED_LIST
