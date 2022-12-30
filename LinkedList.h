//
// Created by amit levi on 21/12/2022.
///=============================================================================================
///=============================================================================================
//                         ###           ########
//                         ##            ###
//                         ##               ###
//                         ##                 ###
//                         #########     ########
///=============================================================================================
///=============================================================================================

#ifndef DATASTRUCTHW2_LINKEDLIST_H
#define DATASTRUCTHW2_LINKEDLIST_H
#include <iostream>
///==================================DoublyLinkedList======================================================
//implementation of a generic double sides liked list
template<class K,class V>
class DoublyLinkedList
{
    class Node
    {
    public:
        V& data;
        K& key;
        Node* next;
        Node* prev;
        Node(K& key,V& val): data(val), key(key), next(nullptr), prev(nullptr) {}
    };
public:
    Node *head;//the first node of the list
    int size;//the number of objects in the list

///====================================DoublyLinkedList======================================================
public:
    DoublyLinkedList(): head(nullptr),size(0){}
    class ALREADY_EXIST{};
    class NOT_EXIST{};
    ~DoublyLinkedList()
    {
        Node *tmp = nullptr;
        while (head)
        {
            tmp = head;
            head = head->next;
            delete tmp;
        }
        head = nullptr;
    }

    ///=====================================insert======================================================
    //inseret a new node if its not already existing, inseration occurs in the head of the list therefore the complexity is of O(1)
    void insert(K key,V& val)
    {
        if(findVal(key)!=nullptr)
        {
            throw (ALREADY_EXIST());
        }
        Node *node = new Node(key, val);
        if (head == nullptr)
        {
            head = node;
        }
        else
        {
            node->next = head;
            head = node;
            node->next->prev = node;
        }
        size++;
    }
///=====================================deleteVal======================================================
    //remove a node if its existing, removal demends going through all of the list therefore the complexity is of O(n)
    void deleteVal(K& key)
    {
        Node* find = findVal(key);
        if(find==nullptr)
            throw(NOT_EXIST());
        Node *tmp = head;
        if(tmp == find)
        {
            head = tmp->next;
        }
        else
        {
            while(find != nullptr)
            {
                if(tmp->next == find)
                {
                    tmp->next = find->next;
                    if(find->next ==nullptr)
                    {
                        size--;
                        delete find;
                        return;
                    }
                    find->next->prev = tmp;
                    delete find;
                    size--;
                    return;
                }
                tmp = tmp->next;
            }
        }
    }

///=====================================operator_<<_======================================================
    friend std::ostream & operator<<(std::ostream & os, const DoublyLinkedList<K,V> & dll){
        dll.display(os);
        return os;
    }

///=====================================findVal======================================================
    Node *findVal(K& key) //returns node of the given value
    {
        Node *node = head;
        while(node != nullptr)
        {
            if(node->key == key)
                return node;

            node = node->next;
        }
        return nullptr;
    }

///=====================================display======================================================
    void display(std::ostream& out = std::cout) const
    {
        Node *node = head;
        while(node != nullptr)
        {
            out << node->data << " ";
            node = node->next;
        }
    }
};

#endif //DATASTRUCTHW2_LINKEDLIST_H
///=============================================================================================
///=============================================================================================
//                         ###           ########
//                         ##            ###
//                         ##               ###
//                         ##                 ###
//                         #########     ########
///=============================================================================================
///=============================================================================================
