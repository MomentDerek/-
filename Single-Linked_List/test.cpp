#include <iostream>
#include "intSLList.h"

int main(void)
{
	IntSLList aList,bList;
	aList.addToHead(1);
	aList.addToHead(0);
	aList.addToTail(2);
	aList.addToTail(3);
	aList.addToTail(4);
	aList.addToTail(5);
	aList.printList();
	bList.addToHead(1);
	bList.addToHead(0);
	bList.addToTail(2);
	bList.addToTail(3);
	bList.addToTail(4);
	bList.addToTail(5);
	bList.printList();
	aList.addListToTail(&bList);
	aList.printList();
}