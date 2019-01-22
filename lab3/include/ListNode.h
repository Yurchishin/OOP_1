//
// Created by yurass on 18.11.18.
//
#ifndef LAB3_LISTNODE_H
#define LAB3_LISTNODE_H

class ListNode {
protected:
    char *data;
    ListNode *prev;
    ListNode *next;
public:
    ListNode();

    ListNode(char *_data);

    ListNode(const ListNode &node);

    ~ListNode();

    char *getData() const;

    ListNode *getNext() const;

    ListNode *getPrev() const;

    void setData(char *_data);

    void setNext(ListNode &node);

    void setPrev(ListNode &node);

    void removeNext();

    void removePrev();
};

#endif //LAB3_LISTNODE_H
