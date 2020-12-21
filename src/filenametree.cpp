#include "btree.hpp"
#include <list>
#include <stack>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <map>
#include <functional>
#include <iomanip>
#include <cmath>

using namespace std;

using Iterator = BTree<char>::Iterator;

struct SearchWayNode {
    enum Type{
        GO_LEFT,
        GO_RIGHT,
        FINISH
    } type;

    Iterator it;

    SearchWayNode(Type _type, Iterator _it)
        : type(_type),
          it(_it)
    {}
};

using SearchWay = list<SearchWayNode>;

void show(BTree<char>& tree)
{
    using IterList = list<BTree<char>::Iterator>;
    shared_ptr<IterList> prev = make_shared<IterList>();
    shared_ptr<IterList> curr = make_shared<IterList>();

    static constexpr int output_width = 2;

    prev->push_back(tree.root());

    auto depth = tree.depth();
    int field_width = depth * (output_width + 3) - 1;

    for (auto i = depth; i != 0; --i) {
        int field_width = pow(2, i) * (2 + output_width);
        cout << string((field_width - output_width) / 2, ' ');
        for (auto &x : *prev) {
            if (x != tree.end()) {
                auto left = x.left();
                if (left != tree.end())
                    curr->push_back(left);
                else
                    curr->push_back(tree.end());

                auto right = x.right();
                if (right != tree.end())
                    curr->push_back(right);
                else
                    curr->push_back(tree.end());
            }

            if (x == tree.end())
                cout << "   ";
            else
                cout << '[' << setw(output_width) << *x << ']';
            cout << string((field_width / pow(2, i)), ' ');
        }
        cout << endl;
        prev->clear();
        swap(curr, prev);
    }
}

int _dmain(int argc, char *argv[])
{
    BTree<char> tree;
    for (char i = 'A'; i <= 'Z'; ++i) {
        tree.insert(i);
        show(tree);
        cout << tree.depth() << endl;

        cin.get();
    }
    return 0;
}
