#include <iostream>
#include <cstring>

#include "include/DoublyLinkedList.h"
#include "include/ListNode.h"

using namespace std;


int main() {
    DoublyLinkedList LIST = DoublyLinkedList();

    cout << "Метод size:" << endl;

    cout << "Пустий список:" << endl;
    int size = LIST.size();
    cout << "LIST:" << endl;
    LIST.print();
    cout << "LIST(print_bkw):" << endl;
    LIST.print_bkw();
    cout << "size:" << size << endl;

    ListNode node = ListNode();
    char *arrayTest[6] = {"bespatter", "equator", "essay", "catch-up", "chew", "hair-breadth"};
    for (int i = 0; i < 6; i++) {
        node.setData(arrayTest[i]);
        LIST.push_back(node);
    }

    cout << "Не пустий список:" << endl;
    size = LIST.size();
    cout << "LIST:" << endl;
    LIST.print();
    cout << "LIST(print_bkw):" << endl;
    LIST.print_bkw();
    cout << "size:" << size << endl << endl;


    LIST.clear();


    cout << "Метод empty:" << endl;

    cout << "Пустий список:" << endl;
    cout << "LIST:" << endl;
    LIST.print();
    cout << "LIST (print_bkw):" << endl;
    LIST.print_bkw();
    bool empty = LIST.empty();
    cout << "empty:" << empty << endl;

    for (int i = 0; i < 6; i++) {
        node.setData(arrayTest[i]);
        LIST.push_back(node);
    }

    cout << "Не пустий список:" << endl;
    cout << "LIST:" << endl;
    LIST.print();
    cout << "LIST (print_bkw):" << endl;
    LIST.print_bkw();
    empty = LIST.empty();
    cout << "empty:" << empty << endl << endl;


    cout << "Метод clear:" << endl;
    cout << "LIST:" << endl;
    LIST.print();
    cout << "LIST (print_bkw):" << endl;
    LIST.print_bkw();
    LIST.clear();
    cout << " clear:" << endl;
    cout << "LIST:" << endl;
    LIST.print();
    cout << "LIST (print_bkw):" << endl;
    LIST.print_bkw();
    cout << endl;


    for (int i = 0; i < 6; i++) {
        node.setData(arrayTest[i]);
        LIST.push_back(node);
    }


    cout << "Метод push_back:" << endl;
    cout << "LIST:" << endl;
    LIST.print();
    cout << "LIST(print_bkw):" << endl;
    LIST.print_bkw();
    LIST.push_back((char *) "push_back");
    cout << "push_back (push_back):" << endl;
    cout << "LIST:" << endl;
    LIST.print();
    cout << "LIST(print_bkw):" << endl;
    LIST.print_bkw();
    cout << endl;


    cout << "Метод push_front:" << endl;
    cout << "LIST:" << endl;
    LIST.print();
    cout << "LIST(print_bkw):" << endl;
    LIST.print_bkw();
    LIST.push_front((char *) "push_front");
    cout << "push_front (push_front):" << endl;
    cout << "LIST:" << endl;
    LIST.print();
    cout << "LIST(print_bkw):" << endl;
    LIST.print_bkw();
    cout << endl;


    cout << "Метод pop_back:" << endl;
    cout << "LIST:" << endl;
    LIST.print();
    cout << "LIST(print_bkw):" << endl;
    LIST.print_bkw();
    LIST.pop_back();
    cout << "pop_back:" << endl;
    cout << "LIST:" << endl;
    LIST.print();
    cout << "LIST(print_bkw):" << endl;
    LIST.print_bkw();
    cout << endl;


    cout << "Метод pop_front:" << endl;
    cout << "LIST:" << endl;
    LIST.print();
    cout << "LIST(print_bkw):" << endl;
    LIST.print_bkw();
    LIST.pop_front();
    cout << "pop_front:" << endl;
    cout << "LIST:" << endl;
    LIST.print();
    cout << "LIST(print_bkw):" << endl;
    LIST.print_bkw();
    cout << endl;


    cout << "Метод sort:" << endl;
    cout << "LIST:" << endl;
    LIST.print();
    cout << "LIST(print_bkw):" << endl;
    LIST.print_bkw();
    LIST.sort();
    cout << "sort:" << endl;
    cout << "LIST:" << endl;
    LIST.print();
    cout << "LIST(print_bkw):" << endl;
    LIST.print_bkw();
    cout << endl;


    cout << "Метод insert_ord:" << endl;
    cout << "LIST:" << endl;
    LIST.print();
    cout << "LIST(print_bkw):" << endl;
    LIST.print_bkw();
    node.setData((char *) "insert_ord");
    LIST.insert_ord(node);
    cout << "insert_ord (insert_ord):" << endl;
    cout << "LIST:" << endl;
    LIST.print();
    cout << "LIST(print_bkw):" << endl;
    LIST.print_bkw();
    cout << endl;


    cout << "Метод insert_after:" << endl;
    cout << "LIST:" << endl;
    LIST.print();
    cout << "LIST(print_bkw):" << endl;
    LIST.print_bkw();
    node.setData((char *) "insert_after");
    LIST.insert_after((char *) "catch-up", node);
    cout << "insert_after (insert_after after catch-up):" << endl;
    cout << "LIST:" << endl;
    LIST.print();
    cout << "LIST(print_bkw):" << endl;
    LIST.print_bkw();
    cout << endl;


    DoublyLinkedList dl = DoublyLinkedList();
    char *dlTest[4] = {"data1", "data2", "data3", "data4"};
    for (int i = 0; i < 4; i++) {
        node.setData(dlTest[i]);
        dl.push_back(node);
    }


    cout << "Метод merge:" << endl;
    cout << "LIST:" << endl;
    LIST.print();
    cout << "LIST(print_bkw):" << endl;
    LIST.print_bkw();
    cout << "dl:" << endl;
    dl.print();
    cout << "dl(print_bkw):" << endl;
    dl.print_bkw();
    LIST.merge(dl);
    cout << "merge (dl):" << endl;
    cout << "LIST:" << endl;
    LIST.print();
    cout << "LIST(print_bkw):" << endl;
    LIST.print_bkw();
    cout << "dl:" << endl;
    dl.print();
    cout << "dl(print_bkw):" << endl;
    dl.print_bkw();
    cout << endl;

    LIST.clear();
    char *erase[6] = {"data0", "equator", "data0", "catch-up", "chew", "data0"};
    for (int i = 0; i < 6; i++) {
        node.setData(erase[i]);
        LIST.push_back(node);
    }

    cout << "Метод erase:" << endl;
    cout << "LIST:" << endl;
    LIST.print();
    cout << "LIST(print_bkw):" << endl;
    LIST.print_bkw();
    LIST.erase((char *) "data0", 0, LIST.size());
    cout << "erase (data0):" << endl;
    cout << "LIST:" << endl;
    LIST.print();
    cout << "LIST(print_bkw):" << endl;
    LIST.print_bkw();
    cout << endl;


    LIST.clear();
    for (int i = 0; i < 6; i++) {
        node.setData(erase[i]);
        LIST.push_back(node);
    }
    LIST.sort();

    cout << "Метод unique:" << endl;
    cout << "LIST:" << endl;
    LIST.print();
    cout << "LIST(print_bkw):" << endl;
    LIST.print_bkw();
    LIST.unique();
    cout << "unique:" << endl;
    cout << "LIST:" << endl;
    LIST.print();
    cout << "LIST(print_bkw):" << endl;
    LIST.print_bkw();
    cout << endl;


    for (int i = 0; i < 4; i++) {
        node.setData(dlTest[i]);
        dl.push_back(node);
    }


    cout << "Метод assign:" << endl;
    cout << "LIST:" << endl;
    LIST.print();
    cout << "LIST(print_bkw):" << endl;
    LIST.print_bkw();
    cout << "dl:" << endl;
    dl.print();
    cout << "dl(print_bkw):" << endl;
    dl.print_bkw();
    LIST.assign(dl, 0, 3);
    cout << "assign (dl, 0, 3):" << endl;
    cout << "LIST:" << endl;
    LIST.print();
    cout << "LIST(print_bkw):" << endl;
    LIST.print_bkw();
    cout << "dl:" << endl;
    dl.print();
    cout << "dl(print_bkw):" << endl;
    dl.print_bkw();
    cout << endl;


    for (int i = 0; i < 4; i++) {
        node.setData(dlTest[i]);
        dl.push_back(node);
    }
    LIST.clear();
    for (int i = 0; i < 6; i++) {
        node.setData(arrayTest[i]);
        LIST.push_back(node);
    }


    cout << "Метод splice:" << endl;
    cout << "LIST:" << endl;
    LIST.print();
    cout << "LIST(print_bkw):" << endl;
    LIST.print_bkw();
    cout << "dl:" << endl;
    dl.print();
    cout << "dl(print_bkw):" << endl;
    dl.print_bkw();
    LIST.splice(0, dl);
    cout << "splice (0, dl):" << endl;
    cout << "LIST:" << endl;
    LIST.print();
    cout << "LIST(print_bkw):" << endl;
    LIST.print_bkw();
    cout << "dl:" << endl;
    dl.print();
    cout << "dl(print_bkw):" << endl;
    dl.print_bkw();
    cout << endl;


    LIST.clear();
    for (int i = 0; i < 6; i++) {
        node.setData(arrayTest[i]);
        LIST.push_back(node);
    }


    cout << "Метод splice:" << endl;
    cout << "LIST:" << endl;
    LIST.print();
    cout << "LIST(print_bkw):" << endl;
    LIST.print_bkw();
    cout << "dl:" << endl;
    dl.print();
    cout << "dl(print_bkw):" << endl;
    dl.print_bkw();
    LIST.splice(6, dl, 0, 3);
    cout << "splice (6, dl, 0, 3):" << endl;
    cout << "LIST:" << endl;
    LIST.print();
    cout << "LIST(print_bkw):" << endl;
    LIST.print_bkw();
    cout << "dl:" << endl;
    dl.print();
    cout << "dl(print_bkw):" << endl;
    dl.print_bkw();
    cout << endl;

    cout << "Метод operator=:" << endl;
    cout << "Використовується в коді." << endl;

    cout << "print_bkw вивожу щоб показати, що хвіст не загубився під час виконання тестів." << endl;

    LIST.clear();
    dl.clear();

    return 0;
}