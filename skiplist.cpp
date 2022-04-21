// Mohammad Adyan Zahid
// HW 4 Skiplist
#include <climits>
#include <cstdlib>
#include <iostream>
#include "skiplist.h"
#include <assert.h>

using namespace std;

//friend function formating
ostream &operator<<(ostream &Out, const SkipList &SkipL) {
	for(int s = SkipL.depth-1; s >= 0; s--) {
		Out<<"Level: "<< s <<" -- ";
		
		SkipList::SNode *node=SkipL.frontGuards[s];
		while(node!= nullptr){
			Out<<node->Data<<", ";
			
			node=node->next;
		}
		Out<<endl;
	}
	return Out;
}

SkipList::SNode::SNode(int Data) {
	this->Data=Data;
	this->next= nullptr;
    // link to prev SNode
    this->prev= nullptr;
    // link to up one level
    this->upLevel= nullptr;
    // link to down one level
    this->downLevel= nullptr;
}
//constructor
SkipList::SkipList(int depth) {
	this->depth=depth;
	this->frontGuards=new SNode *[depth];
	this->rearGuards=new SNode *[depth]; 
	for(int s = 0; s< depth; s++) {
		this->frontGuards[s]=new SNode(INT_MIN);
		this->rearGuards[s]=new SNode(INT_MAX);
		this->frontGuards[s]->next=this->rearGuards[s];
		this->rearGuards[s]->prev=this->frontGuards[s];
		if(s > 0) {
			this->frontGuards[s]->downLevel=this->frontGuards[s-1];
			this->frontGuards[s-1]->upLevel=this->frontGuards[s];
			this->rearGuards[s]->downLevel=this->rearGuards[s-1];
			this->rearGuards[s-1]->upLevel=this->rearGuards[s];
		}
	}
	this->frontGuards[0]->downLevel= nullptr;
	this->frontGuards[depth-1]->upLevel= nullptr;
	this->rearGuards[0]->downLevel= nullptr;
	this->rearGuards[depth-1]->upLevel= nullptr;
}
// return true 50% of time,
// each node has a 50% chance of being at higher level
bool SkipList::alsoHigher() const {
	int number = rand() % 2;
	if(number==1) {
		return  true;
	}
	return false; 
}
// given a SNode, place it before the given NextNode
void SkipList::addBefore(SNode *NewNode, SNode *nextNode) {
	assert(NewNode != nullptr && nextNode != nullptr &&NewNode->Data < nextNode->Data);
	//add before nextNode
	SNode *prevNode=nextNode->prev;
	prevNode->next=NewNode;
	NewNode->prev=prevNode;
	NewNode->next=nextNode;
	nextNode->prev=NewNode;
	assert (NewNode->next == nextNode&&nextNode->prev == NewNode);
	assert (NewNode->prev != nullptr &&NewNode->prev->Data < NewNode->Data);
}
// destructor
SkipList::~SkipList() {
	// need to delete individual nodes
	SNode *node,*last;
	
	int s;
	//loop to delete nodes
	for(s=depth-1;s>=0;s--){
		node=frontGuards[s];
		while(node!= nullptr){
			last=node;
			node=node->next;
			delete last;
		}
	}
	
	//delete skiplist guards array
	delete [] frontGuards;
	delete [] rearGuards;
}
// adds the number to the list
bool SkipList::Add(int Data) {
	SNode *nextNode=frontGuards[0]->next;
	while(nextNode->next!= nullptr && nextNode->Data < Data)
		nextNode=nextNode->next;		
	if(nextNode->Data == Data) {
		return false;
	}
	SNode *newNode=new SNode(Data);
	addBefore(newNode, nextNode);
	int count=1;
	while(count<depth){
		if(alsoHigher()){
			SNode *NewUpper=new SNode(Data);
			NewUpper->downLevel=newNode;
			newNode->upLevel=NewUpper;
			SNode *node=newNode->prev;
			while(node->upLevel == nullptr) {
				// link to prev SNode 
				node=node->prev;	
			}
			count++;		
			// link to up one level 
			node=node->upLevel;
			// link to next SNode 
			node=node->next;			
			addBefore(NewUpper, node);
			newNode=NewUpper;
		}else
			break;
	}
	
	return true;
}
// removes the number from the list
bool SkipList::Remove(int Data) {
  // current node
  SNode *current = nullptr;
  // temp node
  SNode *temp = nullptr;
  for (int z = depth - 1; z >= 0; --z) {
    current = frontGuards[z]->next;
    while (current->next != nullptr && current != frontGuards[z]) {
      // if data is in list
      if (current->Data == Data) {
        while (current != nullptr) {
          current->prev->next = current->next;
          current->next->prev = current->prev;
          temp = current;
          // move down level
          current = current->downLevel;
          // delete node
          delete temp;
          temp = nullptr;
        }
        return true;
      }
      current = current->next;
    }
  }
  return false;
}

// checks if the number is already in the list
bool SkipList::Contains(int Data) {
	SNode *current=frontGuards[depth-1];
	while(current!= nullptr){
		while(current->next->Data < Data) {
			current=current->next;		
		}	
		if(current->next->Data == Data) {
			return true;
		}
		// link to down one level
		current=current->downLevel;
	}
	
	return false;
} 