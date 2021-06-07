#include "doctest.h"

#include "BinaryTree.hpp"
#include <iostream>
#include <stdexcept>
#include <vector>

using namespace ariel;
using namespace std;

TEST_CASE("int BT basic")
{
    BinaryTree<int> tree_of_ints;
    CHECK_NOTHROW(tree_of_ints.add_root(1));
    CHECK_NOTHROW(tree_of_ints.add_left(1, 9));
    CHECK_NOTHROW(tree_of_ints.add_left(9, 4));
    CHECK_NOTHROW(tree_of_ints.add_right(9, 5));
    CHECK_NOTHROW(tree_of_ints.add_right(1, 3));
    CHECK_NOTHROW(tree_of_ints.add_left(1, 2));
    CHECK_THROWS(tree_of_ints.add_right(13, 3));
    CHECK_THROWS(tree_of_ints.add_left(20, 2));
    CHECK_NOTHROW(tree_of_ints.add_root(7));
    CHECK_THROWS(tree_of_ints.add_right(1, 3));
    CHECK_THROWS(tree_of_ints.add_left(1, 2));
    CHECK_NOTHROW(tree_of_ints.add_right(2, 8));
    CHECK_NOTHROW(tree_of_ints.add_left(2, 10));
}

TEST_CASE("int BT right")
{
    BinaryTree<int> tree_of_ints;
    CHECK_NOTHROW(tree_of_ints.add_root(1));
    CHECK_NOTHROW(tree_of_ints.add_right(1, 2));
    CHECK_NOTHROW(tree_of_ints.add_right(2, 3));
    CHECK_NOTHROW(tree_of_ints.add_right(3, 4));
    CHECK_NOTHROW(tree_of_ints.add_right(4, 5));
    CHECK_NOTHROW(tree_of_ints.add_right(5, 6));
    CHECK_NOTHROW(tree_of_ints.add_right(6, 7));
    CHECK_NOTHROW(tree_of_ints.add_right(7, 8));
    CHECK_NOTHROW(tree_of_ints.add_right(8, 9));
    CHECK_NOTHROW(tree_of_ints.add_right(9, 10));

    vector<int> tempVector = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    auto itPre = tree_of_ints.begin_preorder();
    unsigned int i = 0;
    while (itPre != tree_of_ints.end_preorder())
    {
        CHECK((*itPre) == tempVector[i]);
        i++;
        ++itPre;
    }

    auto itIn = tree_of_ints.begin_inorder();
    i = 0;
    while (itIn != tree_of_ints.end_inorder())
    {
        CHECK((*itIn) == tempVector[i]);
        i++;
        ++itIn;
    }

    i = 0;
    for (int element : tree_of_ints)
    {
        CHECK(element == tempVector[i]);
        i++;
    }

    tempVector = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    auto itPost = tree_of_ints.begin_postorder();
    i = 0;
    while (itPost != tree_of_ints.end_postorder())
    {
        CHECK((*itPost) == tempVector[i]);
        i++;
        itPost++;
    }
}

TEST_CASE("int BT left")
{
    BinaryTree<int> tree_of_ints;
    CHECK_NOTHROW(tree_of_ints.add_root(1));
    CHECK_NOTHROW(tree_of_ints.add_left(1, 2));
    CHECK_NOTHROW(tree_of_ints.add_left(2, 3));
    CHECK_NOTHROW(tree_of_ints.add_left(3, 4));
    CHECK_NOTHROW(tree_of_ints.add_left(4, 5));
    CHECK_NOTHROW(tree_of_ints.add_left(5, 6));
    CHECK_NOTHROW(tree_of_ints.add_left(6, 7));
    CHECK_NOTHROW(tree_of_ints.add_left(7, 8));
    CHECK_NOTHROW(tree_of_ints.add_left(8, 9));
    CHECK_NOTHROW(tree_of_ints.add_left(9, 10));

    vector<int> tempVector = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    auto itPre = tree_of_ints.begin_preorder();
    unsigned int i = 0;
    while (itPre != tree_of_ints.end_preorder())
    {
        CHECK((*itPre) == tempVector[i]);
        i++;
        itPre++;
    }

    tempVector = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    auto itIn = tree_of_ints.begin_inorder();
    i = 0;
    while (itIn != tree_of_ints.end_inorder())
    {
        CHECK((*itIn) == tempVector[i]);
        i++;
        itIn++;
    }

    i = 0;
    for (int element : tree_of_ints)
    {
        CHECK(element == tempVector[i]);
        i++;
    }

    auto itPost = tree_of_ints.begin_postorder();
    i = 0;
    while (itPost != tree_of_ints.end_postorder())
    {
        CHECK((*itPost) == tempVector[i]);
        i++;
        ++itPost;
    }
}

TEST_CASE("int BT")
{
    BinaryTree<int> tree_of_ints;
    CHECK_NOTHROW(tree_of_ints.add_root(1));
    CHECK_NOTHROW(tree_of_ints.add_left(1, 2));
    CHECK_NOTHROW(tree_of_ints.add_right(1, 3));
    CHECK_NOTHROW(tree_of_ints.add_left(2, 4));
    CHECK_NOTHROW(tree_of_ints.add_right(2, 5));
    CHECK_NOTHROW(tree_of_ints.add_left(3, 6));
    CHECK_NOTHROW(tree_of_ints.add_right(3, 7));
    CHECK_NOTHROW(tree_of_ints.add_left(4, 8));
    CHECK_NOTHROW(tree_of_ints.add_right(4, 9));
    CHECK_NOTHROW(tree_of_ints.add_left(5, 10));
    CHECK_NOTHROW(tree_of_ints.add_right(5, 11));
    CHECK_NOTHROW(tree_of_ints.add_left(6, 12));
    CHECK_NOTHROW(tree_of_ints.add_right(6, 13));
    CHECK_NOTHROW(tree_of_ints.add_left(7, 14));
    CHECK_NOTHROW(tree_of_ints.add_right(7, 15));

    vector<int> tempVector = {1, 2, 4, 8, 9, 5, 10, 11, 3, 6, 12, 13, 7, 14, 15};
    auto itPre = tree_of_ints.begin_preorder();
    unsigned int i = 0;
    while (itPre != tree_of_ints.end_preorder())
    {
        CHECK((*itPre) == tempVector[i]);
        i++;
        itPre++;
    }

    tempVector = {8, 4, 9, 2, 10, 5, 11, 1, 12, 6, 13, 3, 14, 7, 15};
    auto itIn = tree_of_ints.begin_inorder();
    i = 0;
    while (itIn != tree_of_ints.end_inorder())
    {
        CHECK((*itIn) == tempVector[i]);
        i++;
        itIn++;
    }

    i = 0;
    for (int element : tree_of_ints)
    {
        CHECK(element == tempVector[i]);
        i++;
    }

    tempVector = {8, 9, 4, 10, 11, 5, 2, 12, 13, 6, 14, 15, 7, 3, 1};
    auto itPost = tree_of_ints.begin_postorder();
    i = 0;
    while (itPost != tree_of_ints.end_postorder())
    {
        CHECK((*itPost) == tempVector[i]);
        i++;
        ++itPost;
    }
}

TEST_CASE("string BT basic")
{
    BinaryTree<string> tree_of_strings;
    CHECK_NOTHROW(tree_of_strings.add_root("root"));
    CHECK_NOTHROW(tree_of_strings.add_left("root", "first"));
    CHECK_NOTHROW(tree_of_strings.add_left("first", "grand"));
    CHECK_NOTHROW(tree_of_strings.add_right("first", "hey"));
    CHECK_NOTHROW(tree_of_strings.add_right("root", "you"));
    CHECK_NOTHROW(tree_of_strings.add_left("root", "are"));
    CHECK_THROWS(tree_of_strings.add_right("bat", "you"));
    CHECK_THROWS(tree_of_strings.add_left("rat", "are"));
    CHECK_NOTHROW(tree_of_strings.add_root("new"));
    CHECK_THROWS(tree_of_strings.add_right("root", "you"));
    CHECK_THROWS(tree_of_strings.add_left("root", "are"));
    CHECK_NOTHROW(tree_of_strings.add_right("are", "he"));
    CHECK_NOTHROW(tree_of_strings.add_left("are", "she"));
}

TEST_CASE("string BT right")
{
    BinaryTree<string> tree_of_string;
    CHECK_NOTHROW(tree_of_string.add_root("one"));
    CHECK_NOTHROW(tree_of_string.add_right("one", "two"));
    CHECK_NOTHROW(tree_of_string.add_right("two", "three"));
    CHECK_NOTHROW(tree_of_string.add_right("three", "four"));
    CHECK_NOTHROW(tree_of_string.add_right("four", "five"));
    CHECK_NOTHROW(tree_of_string.add_right("five", "six"));
    CHECK_NOTHROW(tree_of_string.add_right("six", "seven"));
    CHECK_NOTHROW(tree_of_string.add_right("seven", "eight"));
    CHECK_NOTHROW(tree_of_string.add_right("eight", "nine"));
    CHECK_NOTHROW(tree_of_string.add_right("nine", "ten"));

    vector<string> tempVector = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten"};
    auto itPre = tree_of_string.begin_preorder();
    unsigned int i = 0;
    while (itPre != tree_of_string.end_preorder())
    {
        CHECK((*itPre) == tempVector[i]);
        i++;
        ++itPre;
    }

    auto itIn = tree_of_string.begin_inorder();
    i = 0;
    while (itIn != tree_of_string.end_inorder())
    {
        CHECK((*itIn) == tempVector[i]);
        i++;
        itIn++;
    }

    i = 0;
    for (string element : tree_of_string)
    {
        CHECK(element == tempVector[i]);
        i++;
    }

    tempVector = {"ten", "nine", "eight", "seven", "six", "five", "four", "three", "two", "one"};
    auto itPost = tree_of_string.begin_postorder();
    i = 0;
    while (itPost != tree_of_string.end_postorder())
    {
        CHECK((*itPost) == tempVector[i]);
        i++;
        itPost++;
    }
}

TEST_CASE("string BT left")
{
    BinaryTree<string> tree_of_string;
    CHECK_NOTHROW(tree_of_string.add_root("one"));
    CHECK_NOTHROW(tree_of_string.add_left("one", "two"));
    CHECK_NOTHROW(tree_of_string.add_left("two", "three"));
    CHECK_NOTHROW(tree_of_string.add_left("three", "four"));
    CHECK_NOTHROW(tree_of_string.add_left("four", "five"));
    CHECK_NOTHROW(tree_of_string.add_left("five", "six"));
    CHECK_NOTHROW(tree_of_string.add_left("six", "seven"));
    CHECK_NOTHROW(tree_of_string.add_left("seven", "eight"));
    CHECK_NOTHROW(tree_of_string.add_left("eight", "nine"));
    CHECK_NOTHROW(tree_of_string.add_left("nine", "ten"));

    vector<string> tempVector = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten"};
    auto itPre = tree_of_string.begin_preorder();
    unsigned int i = 0;
    while (itPre != tree_of_string.end_preorder())
    {
        CHECK((*itPre) == tempVector[i]);
        i++;
        itPre++;
    }

    tempVector = {"ten", "nine", "eight", "seven", "six", "five", "four", "three", "two", "one"};
    auto itIn = tree_of_string.begin_inorder();
    i = 0;
    while (itIn != tree_of_string.end_inorder())
    {
        CHECK((*itIn) == tempVector[i]);
        i++;
        ++itIn;
    }

    i = 0;
    for (string element : tree_of_string)
    {
        CHECK(element == tempVector[i]);
        i++;
    }

    auto itPost = tree_of_string.begin_postorder();
    i = 0;
    while (itPost != tree_of_string.end_postorder())
    {
        CHECK((*itPost) == tempVector[i]);
        i++;
        ++itPost;
    }
}

TEST_CASE("string BT")
{
    BinaryTree<string> tree_of_string;
    CHECK_NOTHROW(tree_of_string.add_root("one"));
    CHECK_NOTHROW(tree_of_string.add_left("one", "two"));
    CHECK_NOTHROW(tree_of_string.add_right("one", "three"));
    CHECK_NOTHROW(tree_of_string.add_left("two", "four"));
    CHECK_NOTHROW(tree_of_string.add_right("two", "five"));
    CHECK_NOTHROW(tree_of_string.add_left("three", "six"));
    CHECK_NOTHROW(tree_of_string.add_right("three", "seven"));
    CHECK_NOTHROW(tree_of_string.add_left("four", "eight"));
    CHECK_NOTHROW(tree_of_string.add_right("four", "nine"));
    CHECK_NOTHROW(tree_of_string.add_left("five", "ten"));
    CHECK_NOTHROW(tree_of_string.add_right("five", "eleven"));
    CHECK_NOTHROW(tree_of_string.add_left("six", "twelve"));
    CHECK_NOTHROW(tree_of_string.add_right("six", "thirteen"));
    CHECK_NOTHROW(tree_of_string.add_left("seven", "fourteen"));
    CHECK_NOTHROW(tree_of_string.add_right("seven", "fifthteen"));

    vector<string> tempVector = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten", "eleven", "twelve", "thirteen", "fourteen", "fifthteen"};

    tempVector = {"one", "two", "four", "eight", "nine", "five", "ten", "eleven", "three", "six", "twelve", "thirteen", "seven", "fourteen", "fifthteen"};
    auto itPre = tree_of_string.begin_preorder();
    unsigned int i = 0;
    while (itPre != tree_of_string.end_preorder())
    {
        CHECK((*itPre) == tempVector[i]);
        i++;
        itPre++;
    }

    tempVector = {"eight", "four", "nine", "two", "ten", "five", "eleven", "one", "twelve", "six", "thirteen", "three", "fourteen", "seven", "fifthteen"};
    auto itIn = tree_of_string.begin_inorder();
    i = 0;
    while (itIn != tree_of_string.end_inorder())
    {
        CHECK((*itIn) == tempVector[i]);
        i++;
        ++itIn;
    }

    i = 0;
    for (string element : tree_of_string)
    {
        CHECK(element == tempVector[i]);
        i++;
    }

    tempVector = {"eight", "nine", "four", "ten", "eleven", "five", "two", "twelve", "thirteen", "six", "fourteen", "fifthteen", "seven", "three", "one"};
    auto itPost = tree_of_string.begin_postorder();
    i = 0;
    while (itPost != tree_of_string.end_postorder())
    {
        CHECK((*itPost) == tempVector[i]);
        i++;
        itPost++;
    }
}

TEST_CASE("char BT basic")
{
    BinaryTree<char> tree_of_char;
    CHECK_NOTHROW(tree_of_char.add_root('r'));
    CHECK_NOTHROW(tree_of_char.add_left('r', 'f'));
    CHECK_NOTHROW(tree_of_char.add_left('f', 'g'));
    CHECK_NOTHROW(tree_of_char.add_right('f', 'h'));
    CHECK_NOTHROW(tree_of_char.add_right('r', 'y'));
    CHECK_NOTHROW(tree_of_char.add_left('r', 'a'));
    CHECK_THROWS(tree_of_char.add_right('b', 'y'));
    CHECK_THROWS(tree_of_char.add_left('$', 'a'));
    CHECK_NOTHROW(tree_of_char.add_root('n'));
    CHECK_THROWS(tree_of_char.add_right('r', 'y'));
    CHECK_THROWS(tree_of_char.add_left('r', 'a'));
    CHECK_NOTHROW(tree_of_char.add_right('y', '*'));
    CHECK_NOTHROW(tree_of_char.add_left('y', 't'));
}

TEST_CASE("char BT right")
{
    BinaryTree<char> tree_of_char;
    CHECK_NOTHROW(tree_of_char.add_root('a'));
    CHECK_NOTHROW(tree_of_char.add_right('a', 'b'));
    CHECK_NOTHROW(tree_of_char.add_right('b', 'c'));
    CHECK_NOTHROW(tree_of_char.add_right('c', 'd'));
    CHECK_NOTHROW(tree_of_char.add_right('d', 'e'));
    CHECK_NOTHROW(tree_of_char.add_right('e', 'f'));
    CHECK_NOTHROW(tree_of_char.add_right('f', 'g'));
    CHECK_NOTHROW(tree_of_char.add_right('g', 'h'));
    CHECK_NOTHROW(tree_of_char.add_right('h', 'i'));
    CHECK_NOTHROW(tree_of_char.add_right('i', 'j'));

    vector<char> tempVector = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j'};
    auto itPre = tree_of_char.begin_preorder();
    unsigned int i = 0;
    while (itPre != tree_of_char.end_preorder())
    {
        CHECK((*itPre) == tempVector[i]);
        i++;
        ++itPre;
    }

    auto itIn = tree_of_char.begin_inorder();
    i = 0;
    while (itIn != tree_of_char.end_inorder())
    {
        CHECK((*itIn) == tempVector[i]);
        i++;
        ++itIn;
    }

    i = 0;
    for (int element : tree_of_char)
    {
        CHECK(element == tempVector[i]);
        i++;
    }

    tempVector = {'j', 'i', 'h', 'g', 'f', 'e', 'd', 'c', 'b', 'a'};
    auto itPost = tree_of_char.begin_postorder();
    i = 0;
    while (itPost != tree_of_char.end_postorder())
    {
        CHECK((*itPost) == tempVector[i]);
        i++;
        itPost++;
    }
}

TEST_CASE("char BT left")
{
    BinaryTree<char> tree_of_char;
    CHECK_NOTHROW(tree_of_char.add_root('a'));
    CHECK_NOTHROW(tree_of_char.add_left('a', 'b'));
    CHECK_NOTHROW(tree_of_char.add_left('b', 'c'));
    CHECK_NOTHROW(tree_of_char.add_left('c', 'd'));
    CHECK_NOTHROW(tree_of_char.add_left('d', 'e'));
    CHECK_NOTHROW(tree_of_char.add_left('e', 'f'));
    CHECK_NOTHROW(tree_of_char.add_left('f', 'g'));
    CHECK_NOTHROW(tree_of_char.add_left('g', 'h'));
    CHECK_NOTHROW(tree_of_char.add_left('h', 'i'));
    CHECK_NOTHROW(tree_of_char.add_left('i', 'j'));

    vector<char> tempVector = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j'};
    auto itPre = tree_of_char.begin_preorder();
    unsigned int i = 0;
    while (itPre != tree_of_char.end_preorder())
    {
        CHECK((*itPre) == tempVector[i]);
        i++;
        itPre++;
    }

    tempVector = {'j', 'i', 'h', 'g', 'f', 'e', 'd', 'c', 'b', 'a'};
    auto itIn = tree_of_char.begin_inorder();
    i = 0;
    while (itIn != tree_of_char.end_inorder())
    {
        CHECK((*itIn) == tempVector[i]);
        i++;
        itIn++;
    }

    i = 0;
    for (int element : tree_of_char)
    {
        CHECK(element == tempVector[i]);
        i++;
    }

    auto itPost = tree_of_char.begin_postorder();
    i = 0;
    while (itPost != tree_of_char.end_postorder())
    {
        CHECK((*itPost) == tempVector[i]);
        i++;
        ++itPost;
    }
}

TEST_CASE("char BT")
{
    BinaryTree<char> tree_of_char;
    CHECK_NOTHROW(tree_of_char.add_root('a'));
    CHECK_NOTHROW(tree_of_char.add_left('a', 'b'));
    CHECK_NOTHROW(tree_of_char.add_right('a', 'c'));
    CHECK_NOTHROW(tree_of_char.add_left('b', 'd'));
    CHECK_NOTHROW(tree_of_char.add_right('b', 'e'));
    CHECK_NOTHROW(tree_of_char.add_left('c', 'f'));
    CHECK_NOTHROW(tree_of_char.add_right('c', 'g'));
    CHECK_NOTHROW(tree_of_char.add_left('d', 'h'));
    CHECK_NOTHROW(tree_of_char.add_right('d', 'i'));
    CHECK_NOTHROW(tree_of_char.add_left('e', 'j'));
    CHECK_NOTHROW(tree_of_char.add_right('e', 'k'));
    CHECK_NOTHROW(tree_of_char.add_left('f', 'l'));
    CHECK_NOTHROW(tree_of_char.add_right('f', 'm'));
    CHECK_NOTHROW(tree_of_char.add_left('g', 'n'));
    CHECK_NOTHROW(tree_of_char.add_right('g', 'o'));

    vector<char> tempVector = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o'};

    tempVector = {'a', 'b', 'd', 'h', 'i', 'e', 'j', 'k', 'c', 'f', 'l', 'm', 'g', 'n', 'o'};
    auto itPre = tree_of_char.begin_preorder();
    unsigned int i = 0;
    while (itPre != tree_of_char.end_preorder())
    {
        CHECK((*itPre) == tempVector[i]);
        i++;
        ++itPre;
    }

    tempVector = {'h', 'd', 'i', 'b', 'j', 'e', 'k', 'a', 'l', 'f', 'm', 'c', 'n', 'g', 'o'};
    auto itIn = tree_of_char.begin_inorder();
    i = 0;
    while (itIn != tree_of_char.end_inorder())
    {
        CHECK((*itIn) == tempVector[i]);
        i++;
        itIn++;
    }

    i = 0;
    for (char element : tree_of_char)
    {
        CHECK(element == tempVector[i]);
        i++;
    }

    tempVector = {'h', 'i', 'd', 'j', 'k', 'e', 'b', 'l', 'm', 'f', 'n', 'o', 'g', 'c', 'a'};
    auto itPost = tree_of_char.begin_postorder();
    i = 0;
    while (itPost != tree_of_char.end_postorder())
    {
        CHECK((*itPost) == tempVector[i]);
        i++;
        itPost++;
    }
}

class test_object
{
private:
    int i;

public:
    test_object(int j)
    {
        i = j;
    }
    bool operator==(const test_object &a) const
    {
        return (i == a.i);
    }
    bool operator>(const test_object &a) const
    {
        return (i > a.i);
    }
    bool operator<(const test_object &a) const
    {
        return (i < a.i);
    }
};

TEST_CASE("OBJECT BT basic")
{
    test_object root = test_object(1);
    test_object first = test_object(2);
    test_object grand = test_object(3);
    test_object hey = test_object(4);
    test_object you = test_object(5);
    test_object are = test_object(6);
    test_object bat = test_object(7);
    test_object rat = test_object(8);
    test_object new1 = test_object(9);
    test_object hat = test_object(10);
    test_object here = test_object(11);

    BinaryTree<test_object> tree_of_object;
    CHECK_NOTHROW(tree_of_object.add_root(root));
    CHECK_NOTHROW(tree_of_object.add_left(root, first));
    CHECK_NOTHROW(tree_of_object.add_left(first, grand));
    CHECK_NOTHROW(tree_of_object.add_right(first, hey));
    CHECK_NOTHROW(tree_of_object.add_right(root, you));
    CHECK_NOTHROW(tree_of_object.add_left(root, are));
    CHECK_THROWS(tree_of_object.add_right(bat, you));
    CHECK_THROWS(tree_of_object.add_left(rat, are));
    CHECK_NOTHROW(tree_of_object.add_root(new1));
    CHECK_THROWS(tree_of_object.add_right(root, you));
    CHECK_THROWS(tree_of_object.add_left(root, are));
    CHECK_NOTHROW(tree_of_object.add_right(you, hat));
    CHECK_NOTHROW(tree_of_object.add_left(you, here));
}

TEST_CASE("OBJECT BT right")
{
    test_object one = test_object(1);
    test_object two = test_object(2);
    test_object three = test_object(3);
    test_object four = test_object(4);
    test_object five = test_object(5);
    test_object six = test_object(6);
    test_object seven = test_object(7);
    test_object eight = test_object(8);
    test_object nine = test_object(9);
    test_object ten = test_object(10);

    BinaryTree<test_object> tree_of_object;
    CHECK_NOTHROW(tree_of_object.add_root(one));
    CHECK_NOTHROW(tree_of_object.add_right(one, two));
    CHECK_NOTHROW(tree_of_object.add_right(two, three));
    CHECK_NOTHROW(tree_of_object.add_right(three, four));
    CHECK_NOTHROW(tree_of_object.add_right(four, five));
    CHECK_NOTHROW(tree_of_object.add_right(five, six));
    CHECK_NOTHROW(tree_of_object.add_right(six, seven));
    CHECK_NOTHROW(tree_of_object.add_right(seven, eight));
    CHECK_NOTHROW(tree_of_object.add_right(eight, nine));
    CHECK_NOTHROW(tree_of_object.add_right(nine, ten));

    vector<test_object> tempVector = {one, two, three, four, five, six, seven, eight, nine, ten};
    auto itPre = tree_of_object.begin_preorder();
    unsigned int i = 0;
    while (itPre != tree_of_object.end_preorder())
    {
        CHECK((*itPre) == tempVector[i]);
        i++;
        ++itPre;
    }

    auto itIn = tree_of_object.begin_inorder();
    i = 0;
    while (itIn != tree_of_object.end_inorder())
    {
        CHECK((*itIn) == tempVector[i]);
        i++;
        ++itIn;
    }

    i = 0;
    for (test_object element : tree_of_object)
    {
        CHECK(element == tempVector[i]);
        i++;
    }

    tempVector = {ten, nine, eight, seven, six, five, four, three, two, one};
    auto itPost = tree_of_object.begin_postorder();
    i = 0;
    while (itPost != tree_of_object.end_postorder())
    {
        CHECK((*itPost) == tempVector[i]);
        i++;
        itPost++;
    }
}

TEST_CASE("OBJECT BT left")
{
    test_object one = test_object(1);
    test_object two = test_object(2);
    test_object three = test_object(3);
    test_object four = test_object(4);
    test_object five = test_object(5);
    test_object six = test_object(6);
    test_object seven = test_object(7);
    test_object eight = test_object(8);
    test_object nine = test_object(9);
    test_object ten = test_object(10);

    BinaryTree<test_object> tree_of_object;
    CHECK_NOTHROW(tree_of_object.add_root(one));
    CHECK_NOTHROW(tree_of_object.add_left(one, two));
    CHECK_NOTHROW(tree_of_object.add_left(two, three));
    CHECK_NOTHROW(tree_of_object.add_left(three, four));
    CHECK_NOTHROW(tree_of_object.add_left(four, five));
    CHECK_NOTHROW(tree_of_object.add_left(five, six));
    CHECK_NOTHROW(tree_of_object.add_left(six, seven));
    CHECK_NOTHROW(tree_of_object.add_left(seven, eight));
    CHECK_NOTHROW(tree_of_object.add_left(eight, nine));
    CHECK_NOTHROW(tree_of_object.add_left(nine, ten));

    vector<test_object> tempVector = {one, two, three, four, five, six, seven, eight, nine, ten};
    auto itPre = tree_of_object.begin_preorder();
    unsigned int i = 0;
    while (itPre != tree_of_object.end_preorder())
    {
        CHECK((*itPre) == tempVector[i]);
        i++;
        itPre++;
    }

    tempVector = {ten, nine, eight, seven, six, five, four, three, two, one};
    auto itIn = tree_of_object.begin_inorder();
    i = 0;
    while (itIn != tree_of_object.end_inorder())
    {
        CHECK((*itIn) == tempVector[i]);
        i++;
        itIn++;
    }

    i = 0;
    for (test_object element : tree_of_object)
    {
        CHECK(element == tempVector[i]);
        i++;
    }

    auto itPost = tree_of_object.begin_postorder();
    i = 0;
    while (itPost != tree_of_object.end_postorder())
    {
        CHECK((*itPost) == tempVector[i]);
        i++;
        ++itPost;
    }
}

TEST_CASE("OBJECT BT")
{
    test_object one = test_object(1);
    test_object two = test_object(2);
    test_object three = test_object(3);
    test_object four = test_object(4);
    test_object five = test_object(5);
    test_object six = test_object(6);
    test_object seven = test_object(7);
    test_object eight = test_object(8);
    test_object nine = test_object(9);
    test_object ten = test_object(10);
    test_object eleven = test_object(11);
    test_object twelve = test_object(12);
    test_object thirteen = test_object(13);
    test_object fourteen = test_object(14);
    test_object fifthteen = test_object(15);

    BinaryTree<test_object> tree_of_object;
    CHECK_NOTHROW(tree_of_object.add_root(one));
    CHECK_NOTHROW(tree_of_object.add_left(one, two));
    CHECK_NOTHROW(tree_of_object.add_right(one, three));
    CHECK_NOTHROW(tree_of_object.add_left(two, four));
    CHECK_NOTHROW(tree_of_object.add_right(two, five));
    CHECK_NOTHROW(tree_of_object.add_left(three, six));
    CHECK_NOTHROW(tree_of_object.add_right(three, seven));
    CHECK_NOTHROW(tree_of_object.add_left(four, eight));
    CHECK_NOTHROW(tree_of_object.add_right(four, nine));
    CHECK_NOTHROW(tree_of_object.add_left(five, ten));
    CHECK_NOTHROW(tree_of_object.add_right(five, eleven));
    CHECK_NOTHROW(tree_of_object.add_left(six, twelve));
    CHECK_NOTHROW(tree_of_object.add_right(six, thirteen));
    CHECK_NOTHROW(tree_of_object.add_left(seven, fourteen));
    CHECK_NOTHROW(tree_of_object.add_right(seven, fifthteen));

    vector<test_object> tempVector = {one, two, three, four, five, six, seven, eight, nine, ten, eleven, twelve, thirteen, fourteen, fifthteen};

    tempVector = {one, two, four, eight, nine, five, ten, eleven, three, six, twelve, thirteen, seven, fourteen, fifthteen};
    auto itPre = tree_of_object.begin_preorder();
    unsigned int i = 0;
    while (itPre != tree_of_object.end_preorder())
    {
        CHECK((*itPre) == tempVector[i]);
        i++;
        ++itPre;
    }

    tempVector = {eight, four, nine, two, ten, five, eleven, one, twelve, six, thirteen, three, fourteen, seven, fifthteen};
    auto itIn = tree_of_object.begin_inorder();
    i = 0;
    while (itIn != tree_of_object.end_inorder())
    {
        CHECK((*itIn) == tempVector[i]);
        i++;
        itIn++;
    }

    i = 0;
    for (test_object element : tree_of_object)
    {
        CHECK(element == tempVector[i]);
        i++;
    }

    tempVector = {eight, nine, four, ten, eleven, five, two, twelve, thirteen, six, fourteen, fifthteen, seven, three, one};
    auto itPost = tree_of_object.begin_postorder();
    i = 0;
    while (itPost != tree_of_object.end_postorder())
    {
        CHECK((*itPost) == tempVector[i]);
        i++;
        itPost++;
    }
}
