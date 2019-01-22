//
// Created by yurass on 18.11.18.
//
#include <iostream>
#include <cstring>

#include "../include/ListNode.h"

using namespace std;

ListNode::ListNode() {
    data = NULL;
    prev = NULL;
    next = NULL;
}

ListNode::ListNode(const ListNode &node) {
    data = new char[strlen(node.getData()) + 1];
    strcpy(data, node.getData());
    setNext(*node.getNext());
    setPrev(*node.getPrev());
}

ListNode::ListNode(char *_data) {
    data = new char[strlen(_data) + 1];
    strcpy(data, _data);
    prev = NULL;
    next = NULL;
}

ListNode::~ListNode() {
    delete [] data;
    prev = NULL;
    next = NULL;
}

char *ListNode::getData() const {
    return data;
}

ListNode *ListNode::getNext() const {
    return next;
}

ListNode *ListNode::getPrev() const {
    return prev;
}

void ListNode::setData(char *_data) {
    data = new char[strlen(_data) + 1];
    strcpy(data, _data);
}

void ListNode::setNext(ListNode &node) {
    next = &node;
}

void ListNode::setPrev(ListNode &node) {
    prev = &node;
}

void ListNode::removePrev() {
    prev = NULL;
}

void ListNode::removeNext() {
    next = NULL;
}