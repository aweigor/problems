#include "memory"
#include <unordered_map>

/**
 * TODO: description
 * 
 * 
 */

struct Node {
    Node* next;
    void setNext(Node* nextPtr) {
        next = nextPtr;
    };
    Node* getNext() {
        return next;
    };
};


int getLoopSize(Node* startNode)
{
    Node* searchNode = startNode;
    std::unordered_map<Node*, int> map;
    auto search = map.end(); int i = 0;
    while (search == map.end()) {
        map.insert({searchNode, ++i});
        searchNode = searchNode->getNext();
        if (searchNode == nullptr)
            return -1;
        search = map.find(searchNode);
    }
    return (int)map.size() - (search -> second - 1);
}

int getLoopSize_bp(Node* startNode)
{
  Node* turtle = startNode;
  Node* rabbit = startNode->getNext();
  while(turtle != rabbit) {
    turtle = turtle->getNext();
    rabbit = rabbit->getNext()->getNext();
  }
  turtle = turtle->getNext();
  int count = 1;
  while(turtle != rabbit) {
    turtle = turtle->getNext();
    count++;
  }
  return count;
}
