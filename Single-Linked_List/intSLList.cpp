#include <iostream>
#include "intSLList.h"

IntSLList::IntSLList()
{
	//��ʼ��head��tailΪ��
	head = tail = 0;
}

IntSLList::~IntSLList()
{
	//�ȳ�ʼ��һ��pָ�룬���ڴ�ŵڶ����ڵ㣬
	//���ÿ��ɾ����ͷ�ڵ��ʱ��ԭ��p��ŵĵڶ����ڵ㸳���ͷָ�룬���������˾��˳�
	for (IntSLLNode* p; !isEmpty(); head = p) {
		p = head->next;
		delete head;
	}
}

int IntSLList::isEmpty()
{
	//ֻҪhead��Ϊ�գ�������Ϊ��
	return head == 0;
}

void IntSLList::addToHead(int el)
{
	head = new IntSLLNode(
		el, head); //�˴��Ƚ�ԭ�е�headָ�븳����½ڵ㣬�ڽ��½ڵ��ָ�븳��head
	if (tail == 0) //�˴��ж�ԭ����������û�ж��������û�У���βָ��Ҳָ���½ڵ�
		tail = head;
}

void
IntSLList::addToTail(int el)
{
	if (tail != 0) //�ж�����������û�ж����������ж�head�Ƿ�Ϊ0Ҳ��һ����
	{
		tail->next =
			new IntSLLNode(el); //�˴����½ڵ��ָ�븳��ԭ��β���Ľڵ��next
		tail = tail->next; //�˴����½ڵ��ָ�루ԭ��β���ڵ��nextֵ������tail
	}
	else //���û�оͽ�ͷָ���βָ�붼ָ���½ڵ㣬�˲�������addToHead�е�if�Ĺ�����ͬ
		head = tail = new IntSLLNode(el);
}

int IntSLList::deleteFromHead()
{
	int el = head->info; //��ȡͷ����ֵ����������
	IntSLLNode* temp =
		head; //��ʱ���ͷ�ڵ��ָ�루����head���Ϊ��һ�ڵ��ָ�룬�����Ҹ��ط����Ż��Ҳ�����
	if (head == tail)  //�ж�ɾ���ڵ�������Ƿ�Ϊ��
		head = tail = 0; //Ϊ��ֱ���������
	else
		head = head->next; //��Ϊ�յĽ�ͷָ��ָ��ڶ����ڵ�
	delete temp; //�ͷ�ԭ����ͷ�ڵ㡣ע�⣬��ʱheadָ���Ѿ�����ԭ����headָ���ˣ���Ҫ��������֮ǰ��ʱ��ŵ�
	return el;
}

int IntSLList::deleteFromTail()
{
	int el = tail->info;//��ȡͷ����ֵ����������
	if (head == tail) {//���ֻ��һ���ڵ㣬ֱ��ɾ���ڵ㲢���
		delete head;
		head = tail = 0;
	}
	else {
		IntSLLNode* temp;
		for (temp = head; temp->next != tail; temp = temp->next)//�������нڵ㣬����ǰ�ڵ����һ���ڵ�Ϊβ�ڵ�ʱ��������
			;
		delete tail;//ɾ��β�ڵ�
		tail = temp;//��βָ��ָ��ǰ�ڵ�
		tail->next = 0;//����β�ڵ��next��Ϊ0
	}
	return el;
}

void IntSLList::deleteNode(int el)
{
	if (head != 0) {
		if (head == tail && el == head->info) {//ֻ��һ���ڵ�����
			delete head;
			head = tail = 0;
		}
		else if (el == head->info) {//ͷ�ڵ����Ŀ��ڵ��������������deleteFromHead
			IntSLLNode* temp = head;
			head = head->next;
			delete temp;
		}
		else {//ͷ�ڵ㲻��Ŀ��ڵ�����
			IntSLLNode* pred, * temp;
			for (pred = head, temp = head->next;//��������ָ�룬һ�������һ���ڵ㣬һ����ŵ�ǰ�ڵ�
				temp != 0 && !(temp->info == el); //����ǰ�ڵ�Ϊ�գ�������tailҲû�ҵ������ߵ�ǰ�ڵ����Ŀ��ʱ����������
				pred = pred->next, temp = temp->next);
			if (temp != 0) {//�ҵ��ڵ��
				pred->next = temp->next;//����ǰ�ڵ��next������һ���ڵ��next����־�ŵ�ǰ�ڵ��������б�ɾ����
				if (temp == tail)//�����ǰ�ڵ�Ϊβ�ڵ㣬����Ҫ��tailָ����
					tail = pred;
				delete temp;//�ͷŵ�ǰ�ڵ�
			}
		}
	}
}

bool IntSLList::isInList(int el) const
{
	IntSLLNode* temp;
	for (temp = head; temp != 0 && (temp->info) != el; temp = temp->next);//��ͷ�ڵ㿪ʼ���������û�ҵ���temp != 0�������ҵ��ˣ���������
	return temp != 0;//���temp != 0��ζ���ҵ��ˣ�ֵΪtrue����֮Ϊfalse
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


