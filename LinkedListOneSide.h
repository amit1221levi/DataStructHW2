//
// Created by Dan Cohen on 26/12/2022.
///=============================================================================================
///=============================================================================================
//                         ###           ########
//                         ##            ###
//                         ##               ###
//                         ##                 ###
//                         #########     ########
///=============================================================================================
///=============================================================================================

#ifndef DATASTRUCTHW2_LINKEDLISTONESIDE_H
#define DATASTRUCTHW2_LINKEDLISTONESIDE_H
#include <iostream>
///==================================LinkedList======================================================
//implementation of a generic liked list to keep track of data for removal. Do not add values twice!
template<class T>
class LinkedList
{
    class Node
    {
    public:
        T* data;
        Node* next;
        Node(T* val): data(val), next(nullptr) {}
    };
public:
    Node *head;//the first node of the list
    int size;//the number of objects in the list

///====================================LinkedList======================================================
public:
    LinkedList(): head(nullptr),size(0){}
    class ALREADY_EXIST{};
    class NOT_EXIST{};
    class ALLOC_ERROR{};
    ///====================================D'tor======================================================
    //Removes data and nodes
    ~LinkedList()
    {
        Node *tmp = nullptr;
        while (head)
        {
            tmp = head;
            head = head->next;
            delete tmp->data;
            delete tmp;
        }
        head = nullptr;
    }

    ///=====================================insert======================================================
    //inseret a new node if its not already existing, inseration occurs in the head of the list therefore the complexity is of O(1)
    void insert(T* val)
    {
        Node *node = new Node(val);
        if (head == nullptr)
        {
            head = node;
        }
        else
        {
            node->next = head;
            head = node;
        }
        size++;
    }

///=====================================operator_<<_======================================================
    friend std::ostream & operator<<(std::ostream & os, const LinkedList<T> & dll){
        dll.display(os);
        return os;
    }

///=====================================display======================================================
    void display(std::ostream& out = std::cout) const
    {
        Node *node = head;
        while(node != nullptr)
        {
            out << *(node->data) << " ";
            node = node->next;
        }
    }
};

#endif //ONESIDE
///=============================================================================================
///=============================================================================================
//                         ###           ########
//                         ##            ###
//                         ##               ###
//                         ##                 ###
//                         #########     ########
///=============================================================================================
///=============================================================================================
