//
//  llist.hpp
//  algorithms
//
//  Created by Igor on 13.05.2025.
//

#ifndef llist_hpp
#define llist_hpp

#include <stdio.h>

#endif /* llist_hpp */

struct Node {
    Node* next;
    void setNext(Node* nextPtr) {
        next = nextPtr;
    };
    Node* getNext() {
        return next;
    };
};

int getLoopSize(Node* startNode);
