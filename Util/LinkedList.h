//
//  LinkedList.h
//  Wonderland
//
//  Created by Artur Mazurek on 08/02/2013.
//  Copyright (c) 2013 Artur Mazurek. All rights reserved.
//

#ifndef Wonderland_LinkedList_h
#define Wonderland_LinkedList_h


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
        T next() {
            T result = mNode.next;
            if(result) {
                mNode = mNode.next;
            }
            return result;
        };
        
    private:        
        LinkedList::Node mNode;
    };

    typedef LinkedListIterator<ObjT> Iterator;
    
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
    template <typename T> friend class Iterator;

    Node* mHead;
};

#endif
