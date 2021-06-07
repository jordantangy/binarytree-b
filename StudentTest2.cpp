/**
 * Tests for binarytree
 *
 * AUTHOR: Yuval Moshe
 * 
 * Date: 2021-05
 */
#include <stdlib.h>
#include "doctest.h"
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <iterator>
#include <sstream>
using namespace std;

#include "BinaryTree.hpp"
using namespace ariel;

TEST_CASE("Test Basic Binary Tree Operations Correctnes")
{
    SUBCASE("Check add_root() Replacment")
    {
        BinaryTree<int> t_int;
        time_t t;
        srand((unsigned)time(&t));
        for (int i = 0; i < 100; i++)
        {
            int root = rand();
            /* Replacing the root with a random variable*/
            t_int.add_root(root);
            /* In all traversal orders, the iterator should be pointing to the new root*/
            CHECK_EQ(*(t_int.begin()), root);
            CHECK_EQ(*(t_int.begin_inorder()), root);
            CHECK_EQ(*(t_int.begin_postorder()), root);
            CHECK_EQ(*(t_int.begin_preorder()), root);
        }
    }

    SUBCASE("Check add_left() - Left Sons Linked List")
    {
        BinaryTree<char> t_char;
        time_t t;
        /* Generate random root char*/
        char root = 'a';
        t_char.add_root(root);
        char prev = root;
        string inOrder, postOrder, preOrder;
        inOrder = postOrder = preOrder = "a";
        for (int i = 1; i < 26; i++)
        {
            /* Pick random new chanr*/
            char curr = 'a' + i;
            /* Add him as the previous char's left son */
            t_char.add_left(prev, curr);
            /* inOrder - add the char at the front of the string */
            inOrder = curr + inOrder;
            /* postOrder - add the char at the front of the string */
            postOrder = curr + postOrder;
            /* preOrder - add the char at the end of the string */
            preOrder += curr;
            prev = curr;
        }
        auto it = t_char.begin();
        auto in_it = t_char.begin_inorder();
        auto post_it = t_char.begin_postorder();
        auto pre_it = t_char.begin_preorder();
        /* Iterate over the tree in see if the output is identical to the strings */
        for (unsigned long i = 0; i < inOrder.length(); i++)
        {
            CHECK_EQ(*(it++), inOrder[i]);
            CHECK_EQ(*(in_it++), inOrder[i]);
            CHECK_EQ(*(post_it++), postOrder[i]);
            CHECK_EQ(*(pre_it++), preOrder[i]);
        }
        /* At the end of the for loop, the iterator should be pointing to the end of the tree*/
        CHECK((it == t_char.end()));
        CHECK((in_it == t_char.end_inorder()));
        CHECK((post_it == t_char.end_postorder()));
        CHECK((pre_it == t_char.end_preorder()));
    }

    SUBCASE("Check add_right() - Right Sons Linked List")
    {
        string word_bank[11] = {"Checking ", "correctness ", "of ", "right ", "linked ", "list, ", "the ", "sentence ", "should ", "be ", "logical."};
        BinaryTree<string> t_str;
        time_t t;
        /* Add "Checking " as the root of the tree */
        t_str.add_root(word_bank[0]);
        /* Save "Checking " as prev*/
        string prev = word_bank[0];
        for (int i = 1; i < 11; i++)
        {
            /* Add each word in the array in order as the right son of the previous word */
            string curr = word_bank[i];
            t_str.add_right(prev, curr);
            prev = curr;
        }
        auto it = t_str.begin();
        auto in_it = t_str.begin_inorder();
        auto post_it = t_str.begin_postorder();
        auto pre_it = t_str.begin_preorder();
        /* Iterate over the tree in see if the output is identical to the strings */
        for (unsigned long i = 0; i < 11; i++)
        {
            /* inOrder + Regular Iterator - the output should be: "Checking correctness of right linked list, the sentence should be logical." */
            CHECK_EQ(*(in_it++), word_bank[i]);
            CHECK_EQ(*(it++), word_bank[i]);
            /* postOrder - the output should be: "logical. be should sentence the list, linked right of correctness Checking" */
            CHECK_EQ(*(post_it++), word_bank[10 - i]);
            /* preOrder - the output should be: "Checking correctness of right linked list, the sentence should be logical." */
            CHECK_EQ(*(pre_it++), word_bank[i]);
        }
        /* At the end of the for loop, the iterator should be pointing to the end of the tree*/
        CHECK((it == t_str.end_inorder()));
        CHECK((in_it == t_str.end_inorder()));
        CHECK((post_it == t_str.end_postorder()));
        CHECK((pre_it == t_str.end_preorder()));
    }

    SUBCASE("Throw Excepction On add_left()/add_right() with no prev value/ no root")
    {
        BinaryTree<bool> t_bool;
        /* Add true as the root of the tree */
        t_bool.add_root(true);
        for (int i = 0; i < 50; i++)
        {
            /* Create a tree of only true values */
            t_bool.add_left(true, true);
            t_bool.add_right(true, true);
        }
        /* Since there is no false value in the tree, trying to add any left or right sons of true
        should throw an exception */
        CHECK_THROWS(t_bool.add_left(false, true));
        CHECK_THROWS(t_bool.add_right(false, true));
        bool check = true;
        for (auto it = t_bool.begin_inorder(); it != t_bool.end_inorder(); it++)
        {
            check &= *it;
        }
        /* Since all tree value are true, &'ing them should be true */
        CHECK(check);
        /* Replace tree root with false */
        t_bool.add_root(false);
        /* Now trying to add right and left sons of false should not throw exception
        since the root of the tree is false */
        CHECK_NOTHROW(t_bool.add_left(false, true));
        CHECK_NOTHROW(t_bool.add_right(false, true));
        check = true;
        for (auto it = t_bool.begin_inorder(); it != t_bool.end_inorder(); it++)
        {
            check &= *it;
        }
        /* Since thre root of the tree is false, &'ing him with true's should be false */
        CHECK_FALSE(check);
        BinaryTree<bool> t_bool_2;
        for (int i = 0; i < 50; i++)
        {
            /* Adding sons, left or right to a tree with no root, should throw and exception */
            CHECK_THROWS(t_bool_2.add_left(true, true));
            CHECK_THROWS(t_bool_2.add_right(true, true));
            CHECK_THROWS(t_bool_2.add_left(false, true));
            CHECK_THROWS(t_bool_2.add_right(false, true));
        }
    }
}

TEST_CASE("Check Binary Tree Complex Additions")
{

    SUBCASE("InOrder")
    {
        /*********************** SUBCASE("InOrder") *****************************
        *************************************************************************
        *                                ____iteration,(11)___                  *
        *                               /                     \                 *
        *                             in(9)                    logical(21)      *
        *                            /  \                     /       \         *
        *                          to(7) InOrder(10)     exact(19)     order(22)*
        *                        /   \                  /     \                 *
        *                   we're(5)  check,(8)      In(17)    same(20)         *
        *                  /     \                   /  \                       *
        *          sentence(3)    going(6)      be(15)   THE(18)                *
        *         /        \                      /  \                          *
        *       is(1)       that(4)     Sentence(13)  presented(16)             *
        *     /    \                     /        \                             *
        * This(0)      the(2)         The(12)      should(14)                   *
        *                                                                       *
        *************************************************************************
        */

        string s = "This is the sentence that we're going to check, in InOrder iteration, The Sentence should be presented In THE exact same logical order.";
        BinaryTree<string> t_str;
        istringstream iss(s);
        /* Create a vector of all the words in the senctence, without the spaces */
        vector<string> words{istream_iterator<string>{iss}, istream_iterator<string>{}};
        /* Add "iteration" as the root of the tree, "in" as his left son and "logical" as his right son */
        t_str.add_root(string("iteration,"));
        t_str.add_left(string("iteration,"), string("in"));
        t_str.add_right(string("iteration,"), string("logical"));
        /* Add the words based on the index of the word in the vector (view the image above for better understaing) */
        for (unsigned long i = 9; i >= 3; i-=2)
        {
            string prev_l = words[i];
            string left_l = words[i - 2];
            string right_l = words[i + 1];
            t_str.add_left(prev_l, left_l);
            t_str.add_right(prev_l, right_l);
        }
        t_str.add_left(string("is"), string("This"));
        t_str.add_right(string("is"), string("the"));
        for (unsigned long i = 21; i >= 15; i-=2)
        {
            string prev_l = words[i];
            string left_l = words[i - 2];
            string right_l = words[i + 1];
            t_str.add_left(prev_l, left_l);
            t_str.add_right(prev_l, right_l);
        }
        t_str.add_left(string("Sentence"), string("The"));
        t_str.add_right(string("Sentence"), string("should"));
        string ans, ans_in;
        /* Create the comparison string by adding the word with spaces sperating them */
        for (auto it = t_str.begin_inorder(); it != t_str.end_inorder(); it++)
        {
            ans_in = ans_in + " " + *it;
        }
        /* Check both regular and inOrder iterator because they should act the same */
        for (auto it = t_str.begin(); it != t_str.end(); it++)
        {
            ans = ans + " " + *it;
        }
        /* Remove the space before the first word, and compare */
        CHECK_EQ(s, ans.substr(1));
        CHECK_EQ(s, ans_in.substr(1));
    }

    SUBCASE("PostOrder")
    {
        /*********************** SUBCASE("PostOrder") ***************************
        *************************************************************************
        *                                ________order(22)_______               *
        *                               /                    \                  *
        *                           PostOrder(10)             logical(21)       *
        *                          /        \                /       \          *
        *                     check,(8)      in(9)        exact(19)   same(20)  *
        *                    /   \                         /     \              *
        *               going(6)  to(7)                 In(17)    THE(18)       *
        *              /     \                          /  \                    *
        *          that(4)    we're(5)               be(15)  presented(16)      *
        *         /    \                             /  \                       *
        *      the(2)   sentence(3)        Sentence(13)  should(14)             *
        *     /   \                         /        \                          *
        * This(0)  is(1)         iteration,(11)       The(12)                   *
        *                                                                       *
        *************************************************************************
        */

        string s = "This is the sentence that we're going to check, in PostOrder iteration, The Sentence should be presented In THE exact same logical order.";
        BinaryTree<string> t_str;
        istringstream iss(s);
        /* Create a vector of all the words in the senctence, without the spaces */
        vector<string> words{istream_iterator<string>{iss}, istream_iterator<string>{}};
        /* Add "order" as the root of the tree, "PostOrder" as his left son and "logical" as his right son */
        t_str.add_root(string("order."));
        t_str.add_left(string("order."), string("PostOrder"));
        t_str.add_right(string("order."), string("logical"));
        /* Add the words based on the index of the word in the vector (view the image above for better understaing) */
        for (unsigned long i = 10; i >= 2; i -= 2)
        {
            string prev_l = words[i];
            string left_l = words[i - 2];
            string right_l = words[i - 1];
            t_str.add_left(prev_l, left_l);
            t_str.add_right(prev_l, right_l);
        }
        for (unsigned long i = 21; i >= 13; i -= 2)
        {
            string prev_l = words[i];
            string left_l = words[i - 2];
            string right_l = words[i - 1];
            t_str.add_left(prev_l, left_l);
            t_str.add_right(prev_l, right_l);
        }
        string ans;
        /* Create the comparison string by adding the word with spaces sperating them */
        for (auto it = t_str.begin_postorder(); it != t_str.end_postorder(); ++it)
        {
            ans = ans + " " + *it;
        }
        /* Remove the space before the first word, and compare */
        CHECK_EQ(s, ans.substr(1));
    }

    SUBCASE("PreOrder")
    {
        /*********************** SUBCASE("PreOrder") *****************************
        **************************************************************************
        *                                  __________This(0)_________            *
        *                                 /                       \              *
        *                               is(1)                      The(12)       *
        *                              /  \                       /   \          *
        *                          the(2)  iteration,(11) Sentence(13) order(22) *
        *                          /   \                  /     \                *
        *                 sentence(3)   PreOrder(10) should(14)  logical(21)     *
        *                 /        \                 /      \                    *
        *            that(4)       in(9)          be(15)     same(20)            *
        *            /    \                       /  \                           *
        *      we're(5)    check,(8)   presented(16)  exact(19)                  *
        *      /     \                   /         \                             *
        * going(6)    to(7)           In(17)        THE(18)                      *
        *                                                                        *
        **************************************************************************
        */

        string s = "This is the sentence that we're going to check, in PreOrder iteration, The Sentence should be presented In THE exact same logical order.";
        BinaryTree<string> t_str;
        istringstream iss(s);
        /* Create a vector of all the words in the senctence, without the spaces */
        vector<string> words{istream_iterator<string>{iss}, istream_iterator<string>{}};
        /* Add "This" as the root of the tree, "is" as his left son and "The" as his right son */
        t_str.add_root(string("This"));
        t_str.add_left(string("This"), string("is"));
        t_str.add_right(string("This"), string("The"));
        /* Add the words based on the index of the word in the vector (view the image above for better understaing) */
        for (unsigned long i = 1; i <= 5; i++)
        {
            string prev_l = words[i];
            string left_l = words[i + 1];
            string right_l = words[12 - i];
            t_str.add_left(prev_l, left_l);
            t_str.add_right(prev_l, right_l);
        }
        for (unsigned long i = 12; i <= 16; i++)
        {
            string prev_l = words[i];
            string left_l = words[i + 1];
            string right_l = words[34 - i];
            t_str.add_left(prev_l, left_l);
            t_str.add_right(prev_l, right_l);
        }
        string ans;
        /* Create the comparison string by adding the word with spaces sperating them */
        for (auto it = t_str.begin_preorder(); it != t_str.end_preorder(); ++it)
        {
            ans = ans + " " + *it;
        }
        /* Remove the space before the first word, and compare */
        CHECK_EQ(s, ans.substr(1));
    }
}

TEST_CASE("Check BinaryTree Actions")
{
    SUBCASE("Overriding Values")
    {
        /************ Creating State ****************
        *                                          *
        *                100                       *
        *               /   \                      *
        *             99     101                   *
        *            /         \                   *
        *          98           102                *
        *         ...             ...              *
        *        ...               ...             *
        *       ...                 ...            *
        *      3                     197           *
        *     /                        \           *
        *    2                          198        *
        *   /                             \        *
        *  1                               199     *
        *                                          *
        ********************************************
        */

        BinaryTree<double> t_double;
        /* Add 100 as the root of the tree*/
        t_double.add_root(100);
        double prev = 100;
        /*Create the left side of the tree as a descending tree from 99 to 1 */
        for (double i = 99; i >= 0; i--)
        {
            t_double.add_left(prev, i);
            prev = i;
        }
        prev = 100;
        /*Create the right side of the tree as an ascending tree from 101 to 199 */
        for (double i = 101; i < 200; i++)
        {
            t_double.add_right(prev, i);
            prev = i;
        }
        auto prev_it = t_double.begin();
        auto prev_it_in = t_double.begin_inorder();
        /*In inOrder & Regulate iteration, each node should be greter than by value then the previous node in the iteration */
        for (auto it = ++(t_double.begin_inorder()); it != t_double.end_inorder(); ++it)
        {
            CHECK_LT(*prev_it_in, *it);
        }
        for (auto it = ++(t_double.begin()); it != t_double.end(); ++it)
        {
            CHECK_LT(*prev_it, *it);
        }
        /********** Changing State To: **************
        *                                          *
        *               -100                       *
        *               /   \                      *
        *            -99    -101                   *
        *            /          \                  *
        *         -98            -102              *
        *         ...              ...             *
        *        ...                ...            *
        *       ...                  ...           *
        *     -3                     -197          *
        *     /                         \          *
        *   -2                          -198       *
        *   /                              \       *
        * -1                               -199    *
        *                                          *
        ********************************************
        */

        /* Replace the root of the tree with -100 */
        t_double.add_root(-100);
        prev = -100;
        /*Replace the left side of the tree as a ascending tree from -99 to -1 */
        for (double i = 99; i >= 0; i--)
        {
            t_double.add_left(prev, -i);
            prev = -i;
        }
        prev = -100;
        /*Replace the right side of the tree as a descending tree from -101 to -199 */
        for (double i = 101; i < 200; i++)
        {
            t_double.add_right(prev, -i);
            prev = -i;
        }
        prev_it = t_double.begin();
        prev_it_in = t_double.begin_inorder();
        /*In inOrder & Regular iteration, each node should be less than by value then the previous node in the iteration */
        for (auto it = ++(t_double.begin_inorder()); it != t_double.end_inorder(); ++it)
        {
            CHECK_GT(*prev_it, *it);
        }
        for (auto it = ++(t_double.begin()); it != t_double.end(); ++it)
        {
            CHECK_GT(*prev_it, *it);
        }
    }

    SUBCASE("Replacing left and right sons shouldn't also remove all sub-nodes of the replaced nodes ")
    {
        /************ Creating State ************
        *                                       *
        *                 a                     *
        *               /   \                   *
        *            'b'     'B'                *
        *            /         \                *
        *          'c'          'C'             *
        *         ...             ...           *
        *        ...               ...          *
        *       ...                 ...         *
        *     'w'                    'W'        *
        *     /                        \        *
        *   'x'                         'X'     *
        *   /                             \     *
        * 'y'                              'Y'  *
        *                                       *
        ****************************************/

        BinaryTree<char> t_char;
        /* Add 'a' as the root of the tree, 'b' as left son and 'B' as right son */
        t_char.add_root('a');
        t_char.add_left('a', 'b');
        t_char.add_right('a', 'B');
        char prev = 'b';
        /* Create a tree as shown above, the right sub tree nodes are all
        upper case letters, sorted from B to Y, the left tree nodes are all
        lower case letters, sorted from b to y */
        for (char i = 'c'; i < 'z'; i++)
        {
            t_char.add_left(prev, i);
            t_char.add_right((char)(prev - 32), (char)(i - 32));
            prev = i;
        }
        t_char.add_left('a', 'z');
        t_char.add_right('a', 'Z');

        /*********** State After Change *********
        *                                       *
        *                 a                     *
        *               /   \                   *
        *            'z'     'Z'                *
        *            /         \                *
        *          'c'          'C'             *
        *         ...             ...           *
        *        ...               ...          *
        *       ...                 ...         *
        *     'w'                    'W'        *
        *     /                        \        *
        *   'x'                         'X'     *
        *   /                             \     *
        * 'y'                              'Y'  *
        *                                       *
        *****************************************
        After replacing the right and left sons of 'a' (the root) to 'z' and
        'Z' (as shown above), the entire sub-left and sub-right tree should remain,
        only the values themselvs should change  */
        CHECK_THROWS(t_char.add_left('b', 'c'));
        CHECK_THROWS(t_char.add_right('B', 'C'));
        string inOrder_compare = "zaZ";
        prev = 'z';
        for (char i = 'c'; i < 'z'; i++)
        {
            CHECK_NOTHROW(t_char.add_left(prev, i));
            CHECK_NOTHROW(t_char.add_right((char)(prev - 32), (char)(i - 32)));
            inOrder_compare = i + inOrder_compare + (char)(i - 32);
            prev = i;
        }
        string inOrder, Regular;
        /* Build a string by iterating in pre,post, and in order*/
        for (auto it = t_char.begin_inorder(); it != t_char.end_inorder(); it++)
        {
            inOrder += *it;
        }
        for (auto it = t_char.begin(); it != t_char.end(); it++)
        {
            Regular += *it;
        }
        /*Compare to the expected output*/
        CHECK_EQ(inOrder_compare, inOrder);
        CHECK_EQ(inOrder_compare, Regular);
    }
}

TEST_CASE("Check Aditional Iterator Operators")
{
    SUBCASE("==, !=, ++pre, post++")
    {
        BinaryTree<bool> t_bool;
        /* If the tree is empty, begin() and end() iterators should be the same; */
        CHECK((t_bool.begin() == t_bool.end()));
        CHECK((t_bool.begin_inorder() == t_bool.end_inorder()));
        CHECK((t_bool.begin_postorder() == t_bool.end_postorder()));
        CHECK((t_bool.begin_preorder() == t_bool.end_preorder()));
        t_bool.add_root(true);
        /* After adding root to the tree, begin() and end() iterators shouldn't be the same; */
        CHECK_FALSE((t_bool.begin() == t_bool.end()));
        CHECK_FALSE((t_bool.begin_inorder() == t_bool.end_inorder()));
        CHECK_FALSE((t_bool.begin_postorder() == t_bool.end_postorder()));
        CHECK_FALSE((t_bool.begin_preorder() == t_bool.end_preorder()));
        auto it = t_bool.begin();
        auto it_in = t_bool.begin_inorder();
        auto it_post = t_bool.begin_postorder();
        auto it_pre = t_bool.begin_preorder();
        /* In post increment, begin() and end() iterators shouldn't be the same; */
        CHECK_FALSE((it++ == t_bool.end()));
        CHECK_FALSE((it_in++ == t_bool.end_inorder()));
        CHECK_FALSE((it_post++ == t_bool.end_postorder()));
        CHECK_FALSE((it_pre++ == t_bool.end_preorder()));
        CHECK((it == t_bool.end()));
        CHECK((it_in == t_bool.end_inorder()));
        CHECK((it_post == t_bool.end_postorder()));
        CHECK((it_pre == t_bool.end_preorder()));
        it = t_bool.begin();
        it_in = t_bool.begin_inorder();
        it_post = t_bool.begin_postorder();
        it_pre = t_bool.begin_preorder();
        /* In pre increment, begin() and end() iterators shouldn't be the same; */
        CHECK((++it == t_bool.end_inorder()));
        CHECK((++it_in == t_bool.end_inorder()));
        CHECK((++it_post == t_bool.end_postorder()));
        CHECK((++it_pre == t_bool.end_preorder()));
    }

    SUBCASE("->")
    {
        /* Create a tree of string in increading length from 1 to 50 */
        BinaryTree<string> t_str;
        string root = "|";
        t_str.add_root(root);
        string prev = root;
        for (int i = 2; i <= 50; i++)
        {
            string str;
            for (int j = 0; j < i; j++)
            {
                str += "|";
            }
            t_str.add_left(prev, str);
            prev = str;
        }
        int i = 50;
        /* Comparing the increasing size to the size of the string in inOrder iteration*/
        for (auto it = t_str.begin_inorder(); it != t_str.end_inorder(); it++)
        {
            CHECK_EQ(i--, it->size());
        }
        i = 50;
        /* Comparing the increasing size to the size of the string in regular iteration*/
        for (auto it = t_str.begin(); it != t_str.end(); it++)
        {
            CHECK_EQ(i--, it->size());
        }
    }
    SUBCASE("*")
    {
        /****************************************
        *                   ____0____
        *                  /         \
        *                 1           2
        *               /   \       /   \
        *              3     4     5     6
        *             / \   / \   / \   / \
        *            7   8 9  10 11 12 13  14
        *           /\  /\/\  /\ /\ /\ /\  /\
        *          ... ... ... ... ... ... ...
        *         ... ... ... ... ... ... ... ..
        *        ... ... ... ... ... ... ... ... .
        */
        BinaryTree<int> t_int;
        t_int.add_root(0);
        for (int i = 0; i <= 100; i++)
        {
            t_int.add_left(i, 2 * i + 1);
            t_int.add_right(i, 2 * i + 2);
        }
        /* Sum of all elements in the tree should be the sum of an arithmetic progression from 1 to 202 = 20503 */
        int sum = (202 + 1) * 202 / 2;
        int sum_inOrder, sum_preOrder, sum_postOrder, sum_Regular;
        sum_inOrder = sum_postOrder = sum_preOrder = sum_Regular= 0;
        /* Iterate over the tree and sum all the elements, in all the methods */
        for (auto it = t_int.begin(); it != t_int.end(); it++)
        {
            sum_Regular += *it;
        }
        for (auto it = t_int.begin_inorder(); it != t_int.end_inorder(); it++)
        {
            sum_inOrder += *it;
        }
        for (auto it = t_int.begin_preorder(); it != t_int.end_preorder(); it++)
        {
            sum_preOrder += *it;
        }
        for (auto it = t_int.begin_postorder(); it != t_int.end_postorder(); it++)
        {
            sum_postOrder += *it;
        }
        CHECK_EQ(sum, sum_Regular);
        CHECK_EQ(sum, sum_inOrder);
        CHECK_EQ(sum, sum_preOrder);
        CHECK_EQ(sum, sum_postOrder);
        /* Replace 201 and 201 with 0's by using * operator */
        for (auto it = t_int.begin_inorder(); it != t_int.end_inorder(); it++)
        {
            if (*it == 201 || *it == 202)
            {
                *it = 0;
            }
        }
        /* After removing 202 and 201, the sun of all elements in the tree should be the sum of an
         arithmetic progression from 1 to 200 = 20100 */
        sum = (200 + 1) * 200 / 2;
        sum_inOrder = sum_postOrder = sum_preOrder = sum_Regular = 0;
        /* Iterate over the tree and sum all the elements, in all the methods */
        for (auto it = t_int.begin(); it != t_int.end(); it++)
        {
            sum_Regular += *it;
        }
        for (auto it = t_int.begin_inorder(); it != t_int.end_inorder(); it++)
        {
            sum_inOrder += *it;
        }
        for (auto it = t_int.begin_preorder(); it != t_int.end_preorder(); it++)
        {
            sum_preOrder += *it;
        }
        for (auto it = t_int.begin_postorder(); it != t_int.end_postorder(); it++)
        {
            sum_postOrder += *it;
        }
        CHECK_EQ(sum, sum_Regular);
        CHECK_EQ(sum, sum_inOrder);
        CHECK_EQ(sum, sum_preOrder);
        CHECK_EQ(sum, sum_postOrder);
        /* Replace all the values in the tree with 0 except the value 1*/
        for (auto it = t_int.begin_inorder(); it != t_int.end_inorder(); it++)
        {
            if (*it != 1)
            {
                *it = 0;
            }
        }
        sum_inOrder = sum_postOrder = sum_preOrder = sum_Regular = 0;
        /* Iterate over the tree and sum all the elements, in all the methods */
        for (auto it = t_int.begin(); it != t_int.end(); it++)
        {
            sum_Regular += *it;
        }
        for (auto it = t_int.begin_inorder(); it != t_int.end_inorder(); it++)
        {
            sum_inOrder += *it;
        }
        for (auto it = t_int.begin_preorder(); it != t_int.end_preorder(); it++)
        {
            sum_preOrder += *it;
        }
        for (auto it = t_int.begin_postorder(); it != t_int.end_postorder(); it++)
        {
            sum_postOrder += *it;
        }
        CHECK_EQ(1, sum_Regular);
        CHECK_EQ(1, sum_inOrder);
        CHECK_EQ(1, sum_preOrder);
        CHECK_EQ(1, sum_postOrder);
    } 
    
}
