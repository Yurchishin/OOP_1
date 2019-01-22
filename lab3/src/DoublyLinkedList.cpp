//
// Created by yurass on 18.11.18.
//
#include <iostream>
#include <cstring>

#include "../include/DoublyLinkedList.h"

using namespace std;

int cmp_func(const void *a, const void *b) {//callback для qsort, по якому сортуватимемо список
    return strcmp(*(char **) a, *(char **) b);
}

DoublyLinkedList::DoublyLinkedList() {
    head = NULL;
    tail = NULL;
}

DoublyLinkedList::~DoublyLinkedList() {
    if (head != NULL || tail != NULL) clear();
    head = NULL;
    tail = NULL;
}

int DoublyLinkedList::size() {
    int count = 0;
    ListNode *yetNode = head;
    while (yetNode != NULL) {
        count += 1;
        yetNode = yetNode->getNext();
    }
    return count;
}

bool DoublyLinkedList::empty() {
    if (head == NULL && tail == NULL) return true;
    else return false;
}

void DoublyLinkedList::clear() {
    if (head != NULL || tail != NULL) {
        for (int i = 0; i < size(); i++) pop_back();
        head = NULL;
        tail = NULL;
    }
}

void DoublyLinkedList::push_back(const ListNode &nd) {
    ListNode *node = new ListNode(nd.getData());
    if (head == NULL) {
        head = node;
        tail = node;
    } else {
        node->setPrev(*tail);
        tail->setNext(*node);
        tail = node;
    }
}

void DoublyLinkedList::push_front(const ListNode &nd) {
    ListNode *node = new ListNode(nd.getData());
    if (head == NULL) {
        head = node;
        tail = head;
    } else {
        node->setNext(*head);
        head->setPrev(*node);
        head = node;
    }
}

void DoublyLinkedList::pop_back() {
    if (tail == head) delete head;
    else {
        ListNode *yetNode = tail->getPrev();
        if (yetNode == NULL) return;
        if (yetNode->getNext() == NULL) pop_front();

        delete tail;
        yetNode->removeNext();
        tail = yetNode;
    }
}

void DoublyLinkedList::pop_front() {
    if (tail == head) delete head;
    else {
        ListNode *yetNode = head;
        if (yetNode == NULL) return;
        head = yetNode->getNext();
        head->removePrev();
        delete yetNode;
    }
}

//Функція видаляє по індексу елементи списку і повертає їх значення.
char *DoublyLinkedList::removeNode(int position) {
    if (position > size() - 1) {
        cout << "Position > size list." << endl;
        exit(1);
    }
    if (position < 0) {
        cout << "Position < 0." << endl;
        exit(1);
    }
    if (position == 0) {//при видаленні голови.
        ListNode *yetNode = head;
        char *value = new char[strlen(head->getData()) + 1];
        strcpy(value, head->getData());
        head = yetNode->getNext();
        head->removePrev();
        delete yetNode;
        return value;
    }
    if (position == size() - 1) {//при видаленні хвоста.
        ListNode *yetNode = tail->getPrev();
        char *value = new char[strlen(tail->getData()) + 1];
        strcpy(value, tail->getData());
        delete tail;
        yetNode->removeNext();
        tail = yetNode;
        return value;
    }

    //При видаленні середини тіла
    int count = 0;
    ListNode *yetNode = head;
    while (yetNode->getNext()->getNext() != NULL && count != position - 1) {
        count++;
        yetNode = yetNode->getNext();
    }

    ListNode *node = yetNode->getNext();
    char *value = new char[strlen(node->getData()) + 1];
    strcpy(value, node->getData());
    yetNode->setNext(*node->getNext());
    node->getNext()->setPrev(*yetNode);
    delete node;
    return value;
}

//Функція повертає ноду по індексу.
ListNode *DoublyLinkedList::getNode(int position) {
    if (position > size() - 1) {
        cout << "Position > size list." << endl;
        exit(1);
    }
    if (position < 0) {
        cout << "Position < 0." << endl;
        exit(1);
    }
    if (position == 0) return new ListNode(*head);//При голові.
    if (position == size() - 1) return new ListNode(*tail);//При хвості.

    //При середині тіла.
    int count = 0;
    ListNode *yetNode = head;
    while (yetNode != NULL && count != position - 1) {
        count++;
        yetNode = yetNode->getNext();
    }

    return new ListNode(*yetNode->getNext());
}

void DoublyLinkedList::insert_ord(ListNode &nd) {
    push_front(nd);
    sort();
}

void DoublyLinkedList::sort() {
    if (size() == 1) return;//Коли один елемент в списку.
    //Считуємо значення списку в масив.
    char *sortArray[size()];
    ListNode *yetNode = new ListNode(*head);
    for (int i = 0; i < size(); i++) {
        if (i == 0) {//При голові
            sortArray[i] = yetNode->getData();
            yetNode = yetNode->getNext();
        } else if (i == size() - 1) {//При хвості.
            sortArray[i] = yetNode->getData();
        } else {//При середині тіла.
            sortArray[i] = yetNode->getData();
            yetNode = yetNode->getNext();
        }
    }

    //Сортуємо масив.
    qsort(sortArray, size(), sizeof(char *), cmp_func);
    //Повертаємось до голови.
    while (yetNode->getPrev() != NULL) yetNode = yetNode->getPrev();
    //Заповнюємо список новими значеннями.
    for (int i = 0; i < size(); i++) {
        if (i == 0) {
            yetNode->setData(sortArray[i]);
            yetNode = yetNode->getNext();
        } else if (i == size() - 1) {
            yetNode->setData(sortArray[i]);
        } else {
            yetNode->setData(sortArray[i]);
            yetNode = yetNode->getNext();
        }
    }
    tail = yetNode;
    while (yetNode->getPrev() != NULL) yetNode = yetNode->getPrev();
    head = yetNode;
}

bool DoublyLinkedList::insert_after(char *_data, const ListNode &nd) {
    ListNode *node = new ListNode(nd.getData());

    if (strcmp(head->getData(), _data) == 0) {//При голові.
        node->setPrev(*head);
        node->setNext(*head->getNext());
        head->getNext()->setPrev(*node);
        head->setNext(*node);
        return true;
    }

    ListNode *yetNode = head->getNext();
    while (yetNode != NULL) {
        if (strcmp(yetNode->getData(), _data) == 0) {
            if (yetNode == tail) {//При хвості.
                push_back(*node);
                return true;
            } else {//При середині тіла.
                node->setPrev(*yetNode);
                node->setNext(*yetNode->getNext());
                yetNode->getNext()->setPrev(*node);
                yetNode->setNext(*node);
                return true;
            }
        }
        yetNode = yetNode->getNext();
    }

    //Якщо нічого не вставилось.
    cout << "_data not found." << endl;
    return false;
}

void DoublyLinkedList::assign(DoublyLinkedList &dl, int first, int last) {
    if (first >= dl.size()) {
        cout << "Помилка в параметрах (first not found)." << endl;
        return;
    }
    if (first + last + 1 == dl.size()) {//При виборі всього списку.
        int count = first;
        while (count < last) {
            ListNode *removeNode = new ListNode(dl.removeNode(first));
            push_back(*removeNode);
            count++;
            delete removeNode;
        }
        push_back(*dl.tail);
        dl.clear();
        return;
    }
    if (last >= dl.size()) {
        cout << "Помилка в параметрах (last not found)." << endl;
        return;
    }
    if (first > last) {
        cout << "Помилка в параметрах (first > last)." << endl;
        return;
    }

    //Видалення кожної ноди по індексу і створення її копії в кінці списку.
    int count = first;
    while (count <= last) {
        ListNode *removeNode = new ListNode(dl.removeNode(first));
        push_back(*removeNode);
        count++;
    }
}

void DoublyLinkedList::operator=(const DoublyLinkedList &dl) {
    clear();
    ListNode *yetNode = dl.head;
    while (yetNode != NULL) {
        push_back(*yetNode);
        yetNode = yetNode->getNext();
    }
}

//Для рекурсії я добавив параметри deleteCount і deleteCount.
//Щоб коли в нас список повністю з _data ми могл його очистити.
//deleteCount - кількість видалених елементів.
//size - початкова кількість списку(оскільки вона зменшується мусимо її переносити з собою).
void DoublyLinkedList::erase(char *_data, int deleteCount, int size) {
    if (deleteCount == size) {
        clear();
        return;
    }
    if (strcmp(head->getData(), _data) == 0) {//При голові.
        pop_front();
        erase(_data, ++deleteCount, size);
        return;
    }
    if (strcmp(tail->getData(), _data) == 0) {//При хвості.
        pop_back();
        erase(_data, ++deleteCount, size);
        return;
    }
    //При середині тіла.
    ListNode *yetNode = head->getNext();
    while (yetNode != NULL) {
        if (strcmp(yetNode->getData(), _data) == 0) {
            yetNode->getNext()->setPrev(*yetNode->getPrev());
            yetNode->getPrev()->setNext(*yetNode->getNext());
            ++deleteCount;
        }
        yetNode = yetNode->getNext();
    }
}

void DoublyLinkedList::merge(DoublyLinkedList &dl) {
    assign(dl, 0, dl.size() - 1);//Видаляємо весь список dl і вставляємо в кінець поточного.
    sort();//Сортуємо.
}

void DoublyLinkedList::unique() {
    sort();
    int position = 0;
    ListNode *yetNode = head;
    while (yetNode != NULL) {
        if (position == 0 && yetNode->getNext() != NULL &&//При голові.
                    strcmp(yetNode->getData(), yetNode->getNext()->getData()) == 0) {
            pop_front();
            yetNode = head;
            position++;
        } else if (position == size() - 1 && yetNode->getPrev() != NULL &&//При хвості.
                   strcmp(yetNode->getData(), yetNode->getPrev()->getData()) == 0) {
            pop_back();
            yetNode = yetNode->getNext();
            position++;
        } else {
            //При середині тіла.
            if (yetNode->getNext() != NULL && strcmp(yetNode->getData(), yetNode->getNext()->getData()) == 0) {
                yetNode = yetNode->getNext();
                char * value = removeNode(position);
                position++;
                delete value;
            } else {//Коли не знайдено.
                position++;
                yetNode = yetNode->getNext();
            }
        }
    }
}

void DoublyLinkedList::splice(int where, const DoublyLinkedList &dl) {
    if (where < 0 || where > size()) {
        cout << "Помилка в параметрах (where not found)." << endl;
        return;
    } else if (where == 0) {//При добавленні на початок.
        ListNode *yetNode = new ListNode(*dl.tail);
        while (yetNode != NULL) {
            push_front(*yetNode);
            yetNode = yetNode->getPrev();
        }
    } else if (where == size()) {//При добавленні в кінець.
        ListNode *yetNode = new ListNode(*dl.head);
        while (yetNode != NULL) {
            push_back(*yetNode);
            yetNode = yetNode->getNext();
        }
    } else {//При середині тіла.
        int count = 0;
        ListNode *yetNode = new ListNode(*head);
        while (count != where - 1) {
            yetNode = yetNode->getNext();
            count++;
        }

        ListNode *yetNodeDL = new ListNode(*dl.tail);
        while (yetNodeDL != NULL) {
            insert_after(yetNode->getData(), *yetNodeDL);
            yetNodeDL = yetNodeDL->getPrev();
        }
    }
}

void DoublyLinkedList::splice(int where, const DoublyLinkedList &dl, int first, int last) {
    if (where < 0 || where > size()) {
        cout << "Помилка в параметрах (where not found)." << endl;
        return;
    }
    if (first < 0) {
        cout << "Помилка в параметрах (first not found)." << endl;
        return;
    }
    if (last > size() - 1) {
        cout << "Помилка в параметрах (last not found)." << endl;
        return;
    }

    //Відбираємо потрібні елементи списку по індексу(getNode).
    DoublyLinkedList list;
    list = dl;

    DoublyLinkedList list2;
    int count = first;
    while (count <= last) {
        ListNode * node = list.getNode(count);
        list2.push_back(*node);
        delete node;
        count++;
    }

    //Вставляємо відібраний список в потрібне місце.
    splice(where, list2);
    return;
}

void DoublyLinkedList::print() {
    ListNode *yetNode = head;
    while (yetNode != NULL) {
        cout << yetNode->getData() << ' ';
        yetNode = yetNode->getNext();
    }
    cout << endl;
}

void DoublyLinkedList::print_bkw() {
    ListNode *yetNode = tail;
    while (yetNode != NULL) {
        cout << yetNode->getData() << ' ';
        yetNode = yetNode->getPrev();
    }
    cout << endl;
}