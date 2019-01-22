//
// Created by yurass on 18.11.18.
//
#ifndef LAB3_DOUBLYLINKEDLIST_H
#define LAB3_DOUBLYLINKEDLIST_H

#include "./ListNode.h"

class DoublyLinkedList {
    ListNode *head;
    ListNode *tail;//Для зручної роботи з кінцем списку.
public:

    DoublyLinkedList();

    ~DoublyLinkedList();

    int size();

    bool empty();

    void clear();

    void push_back(const ListNode &nd);

    void push_front(const ListNode &nd);

    void pop_front();

    void pop_back();

    //Функція видаляє по індексу елементи списку і повертає їх значення.
    char *removeNode(int position);

    //Функція повертає ноду по індексу.
    ListNode *getNode(int position);

    void insert_ord(ListNode &nd);

    void sort();

    bool insert_after(char *_data, const ListNode &nd);

    void operator=(const DoublyLinkedList &dl);

    void merge(DoublyLinkedList &dl);

    //Для рекурсії я добавив параметри deleteCount і deleteCount.
    //Щоб коли в нас список повністю з _data ми могл його очистити.
    //deleteCount - кількість видалених елементів.
    //size - початкова кількість списку(оскільки вона зменшується мусимо її переносити з собою).
    void erase(char * _data, int deleteCount, int size);

    void unique();

    void assign(DoublyLinkedList &dl, int first, int last);

    void splice(int where, const DoublyLinkedList &dl);

    void splice(int where, const DoublyLinkedList &dl, int first, int last);

    void print();

    void print_bkw();

private:

};

#endif //LAB3_DOUBLYLINKEDLIST_H
