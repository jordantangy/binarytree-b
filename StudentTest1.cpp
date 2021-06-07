#include "BinaryTree.hpp"
#include "doctest.h"
using namespace ariel;

#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>
using namespace std;

const int max_rand = 1000;
const int div_factor = 100;

double NextDouble() {
    return (double)((unsigned int)rand() % max_rand) / div_factor;
}

int NextInt() {
    return (rand() % max_rand);
}

bool RandomBool() {
    return rand() % 2 == 0;
}

enum class _order {
    inorder,
    postorder,
    preorder,
};

template <typename T>
BinaryTree<T> create_dummy(int adder = 0) {
    BinaryTree<T> tree;

    // create the following tree
    //                    1
    //              2          3
    //         4        5
    //               10   11
    //             20       23
    tree.add_root(1 + adder);
    tree.add_left(1 + adder, 2 + adder);
    tree.add_right(1 + adder, 3 + adder);
    tree.add_left(2 + adder, 4 + adder);
    tree.add_right(2 + adder, 5 + adder);
    tree.add_left(5 + adder, 10 + adder);
    tree.add_right(5 + adder, 11 + adder);
    tree.add_left(10 + adder, 20 + adder);
    tree.add_right(11 + adder, 23 + adder);

    return tree;
}

template <typename T>
bool isEqual(BinaryTree<T> &tree, vector<T> const &v2, _order order) {
    // This function checks if a given tree order is equal to some vector.
    if (order == _order::inorder) {
        auto end = tree.end_inorder();
        auto pair = std::mismatch(tree.begin_inorder(), tree.end_inorder(), v2.begin());
        return (pair.first == end && pair.second == v2.end());
    } else if (order == _order::postorder) {
        auto end = tree.end_postorder();
        auto pair = std::mismatch(tree.begin_postorder(), tree.end_postorder(), v2.begin());
        return (pair.first == end && pair.second == v2.end());
    }
    auto end = tree.end_preorder();
    auto pair = std::mismatch(tree.begin_preorder(), tree.end_preorder(), v2.begin());
    return (pair.first == end && pair.second == v2.end());
}

TEST_CASE("check normal order = inorder") {
    BinaryTree<int> tree = create_dummy<int>();

    auto pair = std::mismatch(tree.begin_inorder(), tree.end_inorder(), tree.begin());
    CHECK(((pair.first == tree.end_inorder()) && (pair.second == tree.end())));
}

TEST_CASE("TEST binary on ints simple") {
    srand(time(nullptr));
    // create the following tree on i = 0
    //                    1
    //              2          3
    //         4        5
    //               10   11
    //             20       23

    // inorder : 4, 10, 5, 11, 2, 1, 3
    vector<int> inorder = {4, 2, 20, 10, 5, 11, 23, 1, 3};
    //postorder : 4, 20, 10, 23, 11, 5, 2, 3, 1
    vector<int> postorder = {4, 20, 10, 23, 11, 5, 2, 3, 1};
    //preorder : 1, 2, 4, 5, 10, 20, 11, 23, 3
    vector<int> preorder = {1, 2, 4, 5, 10, 20, 11, 23, 3};

    // Test inorder preorder postorder with match.
    for (int i = 0; i < 10; i++) {
        BinaryTree<int> tree = create_dummy<int>(i);

        CHECK(isEqual(tree, inorder, _order::inorder));

        CHECK(isEqual(tree, preorder, _order::preorder));

        CHECK(isEqual(tree, postorder, _order::postorder));

        transform(inorder.begin(), inorder.end(), inorder.begin(), [](int val) { return val + 1; });
        transform(preorder.begin(), preorder.end(), preorder.begin(), [](int val) { return val + 1; });
        transform(postorder.begin(), postorder.end(), postorder.begin(), [](int val) { return val + 1; });
    }
}

TEST_CASE("TEST binary transofmations") {
    // create the following tree on i = 0
    //                    1
    //              2          3
    //         4        5
    //               10   11
    //             20       23

    auto f = [](int val, int add) {
        return val + add;
    };

    // Test inorder preorder postorder with match.
    // We change the values on the tree by random value everywhere.
    // but here we are using the transform algorithm.
    for (int i = 1; i < 15; i++) {
        // inorder : 4, 10, 5, 11, 2, 1, 3
        vector<int> inorder = {4, 2, 20, 10, 5, 11, 23, 1, 3};
        //postorder : 4, 20, 10, 23, 11, 5, 2, 3, 1
        vector<int> postorder = {4, 20, 10, 23, 11, 5, 2, 3, 1};
        //preorder : 1, 2, 4, 5, 10, 20, 11, 23, 3
        vector<int> preorder = {1, 2, 4, 5, 10, 20, 11, 23, 3};

        int val = NextInt();
        BinaryTree<int> tree = create_dummy<int>();

        auto f2 = std::bind(f, placeholders::_1, val);
        transform(tree.begin(), tree.end(), tree.begin(), f2);

        transform(inorder.begin(), inorder.end(), inorder.begin(), f2);
        transform(preorder.begin(), preorder.end(), preorder.begin(), f2);
        transform(postorder.begin(), postorder.end(), postorder.begin(), f2);

        CHECK(isEqual(tree, inorder, _order::inorder));
        CHECK(isEqual(tree, preorder, _order::preorder));
        CHECK(isEqual(tree, postorder, _order::postorder));
    }
}

TEST_CASE("Test random permutation") {
    const int tsize = 50;
    vector<double> randomVals(tsize);
    auto random_unique_double = []() {
        static double n = 1;
        double v = (double)((unsigned int)rand() % 100) / 100;
        n++;
        return n + v;
    };

    auto print = [](double n) { cout << ", " << n; };
    // for_each(randomVals.begin(), randomVals.end(), print);

    for (int i = 0; i < 5; i++) {
        generate(randomVals.begin(), randomVals.end(), random_unique_double);
        // for_each(randomVals.begin(), randomVals.end(), print);

        // transform(begin(v1), end(v1), begin(v2), back_inserter(v3),
        BinaryTree<double> tree;
        tree.add_root(randomVals[0]);

        // generate random tree, but with values that in the vector we created
        // this new tree inorder, postorder and preorder should be a permutation of the vector!
        for (unsigned int k = 1; k < randomVals.size(); k++) {
            if (RandomBool()) {
                tree.add_left(randomVals[k - 1], randomVals[k]);
            } else {
                tree.add_right(randomVals[k - 1], randomVals[k]);
            }
        }

        // looks like the checking permutation on the default iterator is impossible
        // so we copying tree values into a list and then comparing the two vectors.
        vector<double> copied(tsize);
        unsigned int j = 0;
        for (auto it = tree.begin_preorder(); it != tree.end_preorder(); ++it, j++) {
            copied[j] = *it;
        } // prints: 1 2 4 5 3
        CHECK(is_permutation(copied.begin(), copied.end(), randomVals.begin(), randomVals.end()));

        j = 0;
        for (auto it = tree.begin_inorder(); it != tree.end_inorder(); ++it, j++) {
            copied[j] = *it;
        } // prints: 4 2 5 1 3
        CHECK(is_permutation(copied.begin(), copied.end(), randomVals.begin(), randomVals.end()));

        j = 0;
        for (auto it = tree.begin_postorder(); it != tree.end_postorder(); ++it, j++) {
            copied[j] = *it;
        } // prints: 4 5 2 3 1
        CHECK(is_permutation(copied.begin(), copied.end(), randomVals.begin(), randomVals.end()));
    }
}

// define a string class
// we define it in order to have an easy + int or + double operator.
// iam just lazy.
class myString {
public:
    string val;
    myString(int a) {
        val = std::to_string(a);
    }

    myString &operator+(const myString &other) {
        val += other.val;
        return *this;
    }

    myString &operator+(int other) {
        val += to_string(other);
        return *this;
    }

    myString &operator+(double other) {
        val += to_string(other);
        return *this;
    }

    bool operator==(const myString &other) {
        return this->val == other.val;
    }

    // need to define this for maps...
    friend bool operator<(const myString &t, const myString &other) {
        return t.val < other.val;
    }

    friend std::ostream &operator<<(std::ostream &os, const myString &c) {
        return (os << c.val);
    }
};

TEST_CASE("test castume class") {
    srand(time(nullptr));
    // create the following tree on i = 0
    //                    1
    //              2          3
    //         4        5
    //               10   11
    //             20       23

    // inorder : 4, 10, 5, 11, 2, 1, 3
    vector<myString> inorder = {4, 2, 20, 10, 5, 11, 23, 1, 3};
    //postorder : 4, 20, 10, 23, 11, 5, 2, 3, 1
    vector<myString> postorder = {4, 20, 10, 23, 11, 5, 2, 3, 1};
    //preorder : 1, 2, 4, 5, 10, 20, 11, 23, 3
    vector<myString> preorder = {1, 2, 4, 5, 10, 20, 11, 23, 3};

    auto print = [](myString n) { cout << ", " << n; };
    // for_each(preorder.begin(), preorder.end(), print);

    // Test inorder preorder postorder with match.
    BinaryTree<myString> tree = create_dummy<myString>();
    for (int i = 0; i < 5; i++) {
        int randval = NextInt();

        // you can uncomment this to see what should be vs you'r output.

        // for_each(inorder.begin(), inorder.end(), print);
        // cout << endl;
        // for_each(tree.begin(), tree.end(), print);
        // cout << endl
        //      << endl;

        // // for_each(postorder.begin(), postorder.end(), print);
        // // cout << endl;
        // for_each(tree.begin_postorder(), tree.end_postorder(), print);
        // cout << endl
        //      << endl;

        // // for_each(preorder.begin(), preorder.end(), print);
        // // cout << endl;
        // for_each(tree.begin_preorder(), tree.end_preorder(), print);
        // cout << endl
        //      << endl;

        CHECK(isEqual(tree, inorder, _order::inorder));

        CHECK(isEqual(tree, preorder, _order::preorder));

        CHECK(isEqual(tree, postorder, _order::postorder));

        auto f = [](myString val, int add) {
            return val + add;
        };

        // here we are creating a transformation function in order to update the tree and the vector.
        auto f2 = bind(f, placeholders::_1, randval);

        transform(inorder.begin(), inorder.end(), inorder.begin(), f2);
        transform(preorder.begin(), preorder.end(), preorder.begin(), f2);
        transform(postorder.begin(), postorder.end(), postorder.begin(), f2);
        transform(tree.begin(), tree.end(), tree.begin(), f2);
    }
}

TEST_CASE("throws") {

    const int max_val = 20;
    BinaryTree<myString> tree;

    CHECK_THROWS(tree.add_left(0, 5));
    CHECK_THROWS(tree.add_left(0, 10));

    for (int j = 0; j < 30; j++) {
        BinaryTree<myString> tree2;
        tree2.add_root(0);
        // build a random tree with only even nodes.
        for (int i = 2; i < max_val; i += 2) {
            if (RandomBool()) {
                tree2.add_left(i - 2, i);
            } else {
                tree2.add_right(i - 2, i);
            }
        }

        // pick random number if even the should not trow error,
        // otherwise odd, not in tree throw error.
        int val = (unsigned int)rand() % max_val;
        if (val % 2 == 0) {
            CHECK_NOTHROW(tree2.add_left(val, 1));
        } else {
            CHECK_THROWS(tree2.add_right(val, 1));
        }
    }
}

TEST_CASE("override values test") {
    srand(time(nullptr));
    // create the following tree on i = 0
    //                    1
    //              2          3
    //         4        5
    //               10   11
    //             20       23

    // if true that means the value is a left child
    map<int, bool> is_left_child{
        {2, true},
        {3, false},
        {4, true},
        {5, false},
        {10, true},
        {20, true},
        {23, false},
        {11, false},
    };

    // this maps values to parent index in the tree_vals ( by the vector )
    map<int, unsigned int> pindex{
        {2, 0},
        {3, 0},
        {4, 1},
        {5, 1},
        {10, 4},
        {20, 5},
        {23, 6},
        {11, 4},
    };

    vector<int> tree_vals = {1, 2, 3, 4, 5, 10, 11, 20, 23};
    // inorder : 4, 10, 5, 11, 2, 1, 3
    vector<int> inorder = {4, 2, 20, 10, 5, 11, 23, 1, 3};
    //postorder : 4, 20, 10, 23, 11, 5, 2, 3, 1
    vector<int> postorder = {4, 20, 10, 23, 11, 5, 2, 3, 1};
    //preorder : 1, 2, 4, 5, 10, 20, 11, 23, 3
    vector<int> preorder = {1, 2, 4, 5, 10, 20, 11, 23, 3};

    // Test inorder preorder postorder with match.
    BinaryTree<int> tree = create_dummy<int>();
    const unsigned int size = tree_vals.size();
    for (int i = 0; i < 25; i++) {
        unsigned int index = ((unsigned int)rand() % (size - 1)) + 1;
        int new_val = (unsigned int)rand() % 10;
        // avoid duplicates!
        new_val += (i + 3) * 10;

        int old_val = tree_vals[index];
        replace(postorder.begin(), postorder.end(), old_val, new_val);
        replace(preorder.begin(), preorder.end(), old_val, new_val);
        replace(inorder.begin(), inorder.end(), old_val, new_val);

        unsigned int parent_index = pindex[old_val];
        pindex[new_val] = pindex[old_val];
        is_left_child[new_val] = is_left_child[old_val];

        // cout << "index : " << index << ", old val :" << old_val << " old parent : " << parent_index << endl;
        // cout << "putting new val : " << new_val << endl;

        tree_vals[index] = new_val;

        CHECK_THROWS(tree.add_left(0, new_val));
        CHECK_THROWS(tree.add_left(new_val, 0));

        if (is_left_child[new_val]) {
            CHECK_NOTHROW(tree.add_left(tree_vals[parent_index], new_val));
        } else {
            CHECK_NOTHROW(tree.add_right(tree_vals[parent_index], new_val));
        }
        //CHECK_NOTHROW(tree.)

        CHECK(isEqual(tree, inorder, _order::inorder));
        CHECK(isEqual(tree, preorder, _order::preorder));
        CHECK(isEqual(tree, postorder, _order::postorder));
    }

    tree.add_root(333);
    CHECK_THROWS(tree.add_left(1, 33));
}

TEST_CASE("override values test but with myString") {
    srand(time(nullptr));
    // create the following tree on i = 0
    //                    1
    //              2          3
    //         4        5
    //               10   11
    //             20       23

    // if true that means the value is a left child
    map<myString, bool> is_left_child{
        {2, true},
        {3, false},
        {4, true},
        {5, false},
        {10, true},
        {20, true},
        {23, false},
        {11, false},
    };

    // this maps values to parent index in the tree_vals ( by the vector )
    map<myString, unsigned int> pindex{
        {myString{1}, 0},
        {myString{3}, 0},
        {myString{4}, 1},
        {myString{5}, 1},
        {myString{10}, 4},
        {myString{20}, 5},
        {myString{23}, 6},
        {myString{11}, 4},
    };

    vector<myString> tree_vals = {1, 2, 3, 4, 5, 10, 11, 20, 23};
    // inorder : 4, 10, 5, 11, 2, 1, 3
    vector<myString> inorder = {4, 2, 20, 10, 5, 11, 23, 1, 3};
    //postorder : 4, 20, 10, 23, 11, 5, 2, 3, 1
    vector<myString> postorder = {4, 20, 10, 23, 11, 5, 2, 3, 1};
    //preorder : 1, 2, 4, 5, 10, 20, 11, 23, 3
    vector<myString> preorder = {1, 2, 4, 5, 10, 20, 11, 23, 3};

    // Test inorder preorder postorder with match.
    BinaryTree<myString> tree = create_dummy<myString>();
    const unsigned int size = tree_vals.size();
    for (int i = 0; i < 25; i++) {
        unsigned int index = ((unsigned int)rand() % (size - 1)) + 1;
        int new_vali = (unsigned int)rand() % 10;
        new_vali += (i + 3) * 10;
        myString new_val{new_vali};
        // avoid duplicates!

        myString old_val = tree_vals[index];
        replace(postorder.begin(), postorder.end(), old_val, new_val);
        replace(preorder.begin(), preorder.end(), old_val, new_val);
        replace(inorder.begin(), inorder.end(), old_val, new_val);

        unsigned int parent_index = pindex[old_val];
        pindex[new_val] = pindex[old_val];
        is_left_child[new_val] = is_left_child[old_val];

        // cout << "index : " << index << ", old val :" << old_val << " old parent : " << parent_index << endl;
        // cout << "putting new val : " << new_val << endl;

        tree_vals[index] = new_val;

        CHECK_THROWS(tree.add_left(0, new_val));
        CHECK_THROWS(tree.add_left(new_val, 0));

        if (is_left_child[new_val]) {
            CHECK_NOTHROW(tree.add_left(tree_vals[parent_index], new_val));
        } else {
            CHECK_NOTHROW(tree.add_right(tree_vals[parent_index], new_val));
        }
        //CHECK_NOTHROW(tree.)

        CHECK(isEqual(tree, inorder, _order::inorder));
        CHECK(isEqual(tree, preorder, _order::preorder));
        CHECK(isEqual(tree, postorder, _order::postorder));
    }

    tree.add_root(333);
    CHECK_THROWS(tree.add_left(1, 33));
}

TEST_CASE("test deep copy and operator=") {
    srand(time(nullptr));
    // create the following tree on i = 0
    //                    1
    //              2          3
    //         4        5
    //               10   11
    //             20       23

    auto print = [](myString n) { cout << ", " << n; };
    // for_each(preorder.begin(), preorder.end(), print);

    // Test inorder preorder postorder with match.

    for (int i = 0; i < 5; i++) {
        // create a tree that we can delete at any time!
        BinaryTree<myString> *tree = new BinaryTree<myString>(create_dummy<myString>());
        // inorder : 4, 10, 5, 11, 2, 1, 3
        vector<myString> inorder = {4, 2, 20, 10, 5, 11, 23, 1, 3};
        //postorder : 4, 20, 10, 23, 11, 5, 2, 3, 1
        vector<myString> postorder = {4, 20, 10, 23, 11, 5, 2, 3, 1};
        //preorder : 1, 2, 4, 5, 10, 20, 11, 23, 3
        vector<myString> preorder = {1, 2, 4, 5, 10, 20, 11, 23, 3};

        int randval = NextInt();

        auto f = [](myString val, int add) {
            return val + add;
        };

        // here we are creating a transformation function in order to update the tree and the vector.
        auto f2 = bind(f, placeholders::_1, randval);

        transform(inorder.begin(), inorder.end(), inorder.begin(), f2);
        transform(preorder.begin(), preorder.end(), preorder.begin(), f2);
        transform(postorder.begin(), postorder.end(), postorder.begin(), f2);
        transform(tree->begin(), tree->end(), tree->begin(), f2);

        // check if that tree even working?

        CHECK(isEqual(*tree, inorder, _order::inorder));
        CHECK(isEqual(*tree, preorder, _order::preorder));
        CHECK(isEqual(*tree, postorder, _order::postorder));

        BinaryTree<myString> tree3 = *tree;
        BinaryTree<myString> tree4;
        tree4.add_root(12312312);
        tree4.add_left(12312312, 12312);
        CHECK(isEqual(tree4, inorder, _order::inorder) == false);
        CHECK(isEqual(tree4, preorder, _order::preorder) == false);
        CHECK(isEqual(tree4, postorder, _order::postorder) == false);
        tree4 = *tree;

        // change values of the original again.
        transform(tree->begin(), tree->end(), tree->begin(), f2);

        CHECK(isEqual(tree4, inorder, _order::inorder));
        CHECK(isEqual(tree4, preorder, _order::preorder));
        CHECK(isEqual(tree4, postorder, _order::postorder));
        delete tree;
        //tree2.~BinaryTree();

        tree3 = tree4;

        CHECK(isEqual(tree3, inorder, _order::inorder));
        CHECK(isEqual(tree3, preorder, _order::preorder));
        CHECK(isEqual(tree3, postorder, _order::postorder));

        ///
        CHECK(isEqual(tree4, inorder, _order::inorder));
        CHECK(isEqual(tree4, preorder, _order::preorder));
        CHECK(isEqual(tree4, postorder, _order::postorder));

        // transform tree4
        transform(tree4.begin(), tree4.end(), tree4.begin(), f2);

        // check that tree3 didn't change.
        CHECK(isEqual(tree3, inorder, _order::inorder));
        CHECK(isEqual(tree3, preorder, _order::preorder));
        CHECK(isEqual(tree3, postorder, _order::postorder));

        // update the check's and see if it mach tree4.
        transform(inorder.begin(), inorder.end(), inorder.begin(), f2);
        transform(preorder.begin(), preorder.end(), preorder.begin(), f2);
        transform(postorder.begin(), postorder.end(), postorder.begin(), f2);

        CHECK(isEqual(tree4, inorder, _order::inorder));
        CHECK(isEqual(tree4, preorder, _order::preorder));
        CHECK(isEqual(tree4, postorder, _order::postorder));
    }
}