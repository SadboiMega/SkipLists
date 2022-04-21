// Mohammad Adyan Zahid
// HW 4 Skiplist
#ifndef SKIPLIST_H
#define SKIPLIST_H

#include <iostream>

using namespace std;

class SkipList {
  //friend function formating
  friend ostream &operator<<(ostream &Out, const SkipList &SkipL);
public:
  // default SkipList has depth of 1, just one doubly-linked list 
  explicit SkipList(int Depth = 1);
  // destructor
  virtual ~SkipList();
  // adds the number to the list
  bool Add(int Data);
  // removes the number from the list
  bool Remove(int Data);
  // checks if the number is already in the list
  bool Contains(int Data);

private:
  struct SNode {
    // SNode stores int as data 
    explicit SNode(int Data);
    int Data;
    // link to next SNode 
    SNode *next;
    // link to prev SNode 
    SNode *prev;
    // link to up one level 
    SNode *upLevel;
    // link to down one level 
    SNode *downLevel;
  };

  using Snode = struct Snode;
  // array of depth SNode* objects as frontGuards linking levels 
  // if depth = 2, we'd have frontGuards[0] and frontGuards[1]
  SNode **frontGuards;
  // depth of SkipList, levels are 0 to depth-1 
  int depth;
  // array of depth SNode* objects as rearGuards linking levels 
  SNode **rearGuards;
  // return true 50% of time,
  // each node has a 50% chance of being at higher level
  bool alsoHigher() const;
  // given a SNode, place it before the given NextNode
  void addBefore(SNode *NewNode, SNode *NextNode);
};

#endif // SKIPLIST_H