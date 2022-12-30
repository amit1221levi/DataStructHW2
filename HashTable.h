//
// Created by amit levi on 21/12/2022.
///================================================================================================
///================================================================================================
//                         ##      ##     #########
//                         ##      ##        ##
//                         ##########        ##
//                         ##      ##        ##
//                         ##      ##        ##
///=================================================================================================
///=================================================================================================
#ifndef DATASTRUCTHW2_HASHTABLE_H
#define DATASTRUCTHW2_HASHTABLE_H
#include "LinkedList.h"
///========================================HashTable======================================================
template <class K,class V>
class HashTable
{
public:
    class NOT_EXIST {};
    DoublyLinkedList<K,V>* arr;//dynmic array of lists
    int size;// the hash table size, initailized with size 10
    int curr_num;//the current number of elements in the hash
    int growth_factor;//10
    int (*getKey)(V);
    //the hash table is a dynamic array of double linked list of T
    HashTable(int (*f)(V)) : size(10), curr_num(0), growth_factor(10), getKey(f)
    {
        arr = new DoublyLinkedList<K,V>[size];
        for (int i = 0; i < size; i++)
        {
            arr[i] = DoublyLinkedList<K,V>();
        }
    }

//=============================================================================================
///=====================================FUNCTIONS==============================================
//=============================================================================================

///========================================operator_=_======================================================
    HashTable& operator=(const HashTable& h)
    {
        size = h.size;
        curr_num = h.curr_num;
        growth_factor = h.growth_factor;
        arr = h.arr;
        return (*this);
    }

///========================================HashTable======================================================
    HashTable(const HashTable& h) : size(h.size), curr_num(h.curr_num), growth_factor(h.growth_factor)
    {
        arr = new DoublyLinkedList<K,V>[size];
        for (int i = 0; i < size; i++)
        {
            arr[i] = h.arr[i];
        }
    }

///========================================~HashTable======================================================
    ~HashTable()
    {
        delete[] arr;
    }

///========================================hashFunc======================================================
    //hash function based on the size of the array will provide a random devsion of the objects
    int hashFunc(int key, int size)
    {
        return (key % (size));
    }

///========================================decreaseSize======================================================
    // the table divide her size by the growth factor if the tabe contains only 1/(growth_factor^2) objects
    void decreaseSize()
    {
        int prev_size = size;
        size = size / growth_factor;
        DoublyLinkedList<K,V>* new_arr = new DoublyLinkedList<K,V>[size];
        for (int i = 0; i < size; i++)
        {
            new_arr[i] = DoublyLinkedList<K,V>();
        }
        for (int i = 0; i < prev_size; i++)
        {
            auto* curr = arr[i].head;
            while (curr != nullptr)
            {
                (new_arr[hashFunc(getKey(curr->data), size)]).insert(curr->data);
                curr = curr->next;
            }
        }
        this->arr = new_arr;
    }
    DoublyLinkedList<K,V>* operator[](V value)
    {
        return arr[hashFunc(getKey(value), size)];
    }

///========================================find======================================================
    //finds an objcet in the hash table return a pointer to the object
    V& find(K& key)
    {
        if ((arr[hashFunc(key, size)]).findVal(key) == nullptr)
            throw(NOT_EXIST());
        return (arr[hashFunc(key, size)]).findVal(key)->data;
    }

///========================================increaseSize======================================================
    //the table multiply her size by the growth factor if the table is full increasing it by the growth factor
    void increaseSize()
    {
        int prev_size = size;
        size = size * growth_factor;
        DoublyLinkedList<K,V>* new_arr = new DoublyLinkedList<K,V>[size];
        for (int i = 0; i < size; i++)
        {
            new_arr[i] = DoublyLinkedList<K,V>();
        }
        for (int i = 0; i < prev_size; i++)
        {
            auto* curr = arr[i].head;
            while (curr != nullptr)
            {
                (new_arr[hashFunc(getKey(curr->data), size)]).insert(curr->data);
                curr = curr->next;
            }
        }
        this->arr = new_arr;
    }

///========================================insertElem======================================================
    //insert new element to the hash
    void insertElem(V& value)
    {
        if ((curr_num / size) >= growth_factor) //alpha>=10
        {
            increaseSize();
        }
        (arr[hashFunc(getKey(value), size)]).insert(getKey(value),value);
        curr_num++;
    }

///========================================print======================================================
    //prints the hash table
    void print()
    {
        std::cout << "tha hash: \n";
        for (int i = 0; i < size; i++)
        {
            std::cout << "arr[" << i << "]: " << arr[i] << " ";
            std::cout << "\n";
        }
    }

///========================================deleteElem======================================================
    //deletes elem from the hash
    void deleteElem(K& key)
    {
        if (curr_num == 0)
            return;
        if (size > 10 && (size / curr_num) >= growth_factor) //alpha>=10
        {
            decreaseSize();
        }
        (arr[hashFunc(key, size)]).deleteVal(key);
        curr_num--;
    }
};

#endif //DATASTRUCTHW2_HASHTABLE_H
///=============================================================================================
///=============================================================================================
//                         ##      ##     #########
//                         ##      ##        ##
//                         ##########        ##
//                         ##      ##        ##
//                         ##      ##        ##
///=============================================================================================
///=============================================================================================
