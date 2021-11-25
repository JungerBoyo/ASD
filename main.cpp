#include <fmt/format.h>
#include "dataStructers/Bst_avl.h"
#include "Timer/Timer.h"

int main()
{
    bool f1 = true;
    bool f2 = true;

    bool f3 = f1^f2;


    AVLTree<int> tree{};

    tree.insert(10);
    tree.insert(11);
    tree.insert(12);
    tree.insert(7);
    tree.insert(6);
    tree.insert(8);
    tree.insert(9);

    tree.erase(10);
    /*
    tree.insert(40);
    tree.insert(30);
    tree.insert(50);
    tree.insert(24);
    tree.insert(35);
    tree.insert(27);

    tree.erase(40);
    */

    return 0;
}