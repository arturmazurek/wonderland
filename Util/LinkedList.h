//
//  LinkedList.h
//  Wonderland
//
//  Created by Artur Mazurek on 08/02/2013.
//  Copyright (c) 2013 Artur Mazurek. All rights reserved.
//

#ifndef Wonderland_LinkedList_h
#define Wonderland_LinkedList_h

#include <cassert>

template <typename ObjT>
class LinkedList {
private:
    struct Node {
        ObjT obj;
        Node* next;
    };
public:
    template <typename T>
    class LinkedListIterator {
    public:
        bool hasNext() {
            return mNode != nullptr;
        }
        
        T& next() {
            assert(mNode && "Iterator is invalid if mNode is null");
            if(!mNode) {
                static T empty;
                return empty;
            }
            
            LinkedList::Node* temp = mNode;
            mNode = mNode->next;
            return temp->obj;
        };
        
    private:
        template <class U> friend class LinkedList;
        LinkedList::Node* mNode;
    };

    typedef LinkedListIterator<ObjT> Iterator;
    
    LinkedList() : mHead(nullptr) {
        
    }
    
    ~LinkedList() {
        eraseAll();
    }
    
    void erase(ObjT obj) {
        if(!mHead) {
            return;
        }
        
        if(mHead->obj == obj) {
            delete mHead;
            mHead = nullptr;
            return;
        }
        
        Node* previous = mHead;
        Node* current = mHead->next;
        while(current) {
            if(current->obj == obj) {
                break;
            }
            previous = current;
            current = current->next;
        }
    
        previous->next = current->next;
        delete current;
    }

    void eraseAll() {
        while(mHead) {
            Node* temp = mHead;
            mHead = mHead->next;
            delete temp;
        }
    }
    
    void add(ObjT obj) {
        Node* n = new Node();
        n->obj = obj;
        n->next = mHead;
        mHead = n;
    }
    
    Iterator iterator() {
        Iterator result;
        result.mNode = mHead;
        return result;
    }
    
private:
    LinkedList(const LinkedList&);
    LinkedList& operator=(const LinkedList&);
    
private:
    template <typename T> friend class LinkedListIterator;

    Node* mHead;
};

#endif
