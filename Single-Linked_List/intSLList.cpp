#include <iostream>
#include "intSLList.h"

IntSLList::IntSLList()
{
	//初始化head和tail为空
	head = tail = 0;
}

IntSLList::~IntSLList()
{
	//先初始化一个p指针，用于存放第二个节点，
	//随后每次删除完头节点的时候将原来p存放的第二个节点赋予给头指针，如果链表空了就退出
	for (IntSLLNode* p; !isEmpty(); head = p) {
		p = head->next;
		delete head;
	}
}

int IntSLList::isEmpty()
{
	//只要head不为空，那链表不为空
	return head == 0;
}

void IntSLList::addToHead(int el)
{
	head = new IntSLLNode(
		el, head); //此处先将原有的head指针赋予给新节点，在将新节点的指针赋给head
	if (tail == 0) //此处判断原来数组内有没有东西，如果没有，将尾指针也指向新节点
		tail = head;
}

void
IntSLList::addToTail(int el)
{
	if (tail != 0) //判断链表里面有没有东西，这里判断head是否为0也是一样的
	{
		tail->next =
			new IntSLLNode(el); //此处将新节点的指针赋给原本尾部的节点的next
		tail = tail->next; //此处将新节点的指针（原本尾部节点的next值）赋给tail
	}
	else //如果没有就将头指针和尾指针都指向新节点，此步与上面addToHead中的if的功能相同
		head = tail = new IntSLLNode(el);
}

int IntSLList::deleteFromHead()
{
	int el = head->info; //获取头部的值，用来返回
	IntSLLNode* temp =
		head; //临时存放头节点的指针（下面head会变为下一节点的指针，不先找个地方存着会找不到）
	if (head == tail)  //判断删除节点后链表是否为空
		head = tail = 0; //为空直接清空链表
	else
		head = head->next; //不为空的将头指针指向第二个节点
	delete temp; //释放原来的头节点。注意，此时head指针已经不是原来的head指针了，需要用上我们之前临时存放的
	return el;
}

int IntSLList::deleteFromTail()
{
	int el = tail->info;//获取头部的值，用来返回
	if (head == tail) {//如果只有一个节点，直接删除节点并清空
		delete head;
		head = tail = 0;
	}
	else {
		IntSLLNode* temp;
		for (temp = head; temp->next != tail; temp = temp->next)//遍历所有节点，当当前节点的下一个节点为尾节点时结束遍历
			;
		delete tail;//删除尾节点
		tail = temp;//将尾指针指向当前节点
		tail->next = 0;//将新尾节点的next设为0
	}
	return el;
}

void IntSLList::deleteNode(int el)
{
	if (head != 0) {
		if (head == tail && el == head->info) {//只有一个节点的情况
			delete head;
			head = tail = 0;
		}
		else if (el == head->info) {//头节点就是目标节点的情况，程序参照deleteFromHead
			IntSLLNode* temp = head;
			head = head->next;
			delete temp;
		}
		else {//头节点不是目标节点的情况
			IntSLLNode* pred, * temp;
			for (pred = head, temp = head->next;//建立两个指针，一个存放上一个节点，一个存放当前节点
				temp != 0 && !(temp->info == el); //当当前节点为空（遍历到tail也没找到）或者当前节点就是目标时，结束遍历
				pred = pred->next, temp = temp->next);
			if (temp != 0) {//找到节点后
				pred->next = temp->next;//将当前节点的next赋给上一个节点的next（标志着当前节点在链表中被删除）
				if (temp == tail)//如果当前节点为尾节点，还需要将tail指针变更
					tail = pred;
				delete temp;//释放当前节点
			}
		}
	}
}

bool IntSLList::isInList(int el) const
{
	IntSLLNode* temp;
	for (temp = head; temp != 0 && (temp->info) != el; temp = temp->next);//从头节点开始遍历，如果没找到（temp != 0）或者找到了，结束遍历
	return temp != 0;//如果temp != 0意味着找到了，值为true，反之为false
}

void IntSLList::addListToTail(IntSLList* addList)
{
	IntSLList* temp = addList;
	for (IntSLLNode* i = addList->head; i != addList->tail; i = i->next) {
		addToTail(i->info);
	}
	addToTail(addList->tail->info);
}

IntSLList* IntSLList::mergeList(IntSLList *frontList, IntSLList *backList) const
{
	IntSLList *newList = new IntSLList();
	for (IntSLLNode* i = frontList->head;i!=frontList->tail ; i = i->next){
		newList->addToTail(i->info);
	}
	newList->addToTail(frontList->tail->info);
	for (IntSLLNode* i = backList->head; i != backList->tail; i = i->next) {
		newList->addToTail(i->info);
	}
	newList->addToTail(backList->tail->info);
	return newList;
}

void IntSLList::printList()
{
	for (IntSLLNode* i = head; i != tail; i = i->next) {
		std::cout << i->info;
	}
	std::cout << tail->info <<std::endl;
}


