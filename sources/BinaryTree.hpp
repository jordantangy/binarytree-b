#pragma once

#include <iostream>
#include <stdexcept>
#include <queue>
using namespace std;
namespace ariel {

  template<typename T> class BinaryTree {
  typedef struct node{
  public:
      T val;
      node* right;
      node* left;
      node(T& value) : val(value), right(NULL),  left(NULL) {
    }
          
   node(node& n) = default;
  ~node() = default;
   node(node&& n) = delete; 
   node& operator=(node& n) = delete; 
   node& operator=(node&& n) = delete ;

  }node;

/*
this function copies a tree by getting the orignal node from 
the tree we want to copy and traverse the tree in order to get each node and 
copy it
*/
void copy_tree(node& origin, node& toCopyTo){
  if(origin.left != NULL) {
    node* copied = new node(origin.left->val);
    toCopyTo.left = copied;
    node& left = *(origin).left;
    copy_tree(left ,*toCopyTo.left);
  }
  if(origin.right != NULL) {
    node* copied = new node(origin.right->val);
    toCopyTo.right = copied;
    node& right = *(origin).right;
    copy_tree(right,*toCopyTo.right);
  }
}

/*
recurse on the left side of the tree and check if the value you are looking for is equal to 
the value of the node you are looking at. Same on the right side. If the value was found
return a pointer to the node found. If not , the tree was traversed and no match was found, then return NULL
*/
node* find_node(const T& value , node* toFind){

  if(toFind == NULL){
      return NULL;
    }
  if(toFind->val == value){
      return toFind;
    }
  node* left_node = find_node(value,toFind->BinaryTree::node::left);

  if(left_node != NULL){
    return left_node;
  }

  node* right_node = find_node(value,toFind->BinaryTree::node::right);

  if(right_node != NULL){
    return right_node;
  }

  return NULL;
}
node* root;

public:

BinaryTree() : root(NULL){}


BinaryTree(const BinaryTree& bt){
  if(bt.root!=NULL) {
    root = new node(bt.root->BinaryTree::node::val);
    copy_tree(*bt.root,*root);
  }
}


BinaryTree(BinaryTree&& bt) noexcept {
        root = bt.root;
        bt.root = NULL;
}

/*
Operator "=" to assign a tree to another tree.
The function copy_tree is used in order to copy the tree (i.e to assign an existing tree to another one).
*/
 BinaryTree& operator=(BinaryTree bt){
     if(this == &bt){
         return *this;
     }
     if(root != NULL){
         delete this->root;
     }
    root = new node(bt.root->val);
    copy_tree(*bt.root,*this->root);
    return *this;

 }

 BinaryTree& operator=(BinaryTree&& bt) noexcept{
     *this->root = bt.root;
 }

~BinaryTree(){}

BinaryTree& add_root(T value){
        if(root!=NULL){
          root->BinaryTree::node::val = value;
        }
        else{
          root = new node(value);
        }
        return *this;
}

/*
Add a node to the left.
First check if the node we want to add to the left of the current node exists 
in the tree. If not, throw an exception, otherwise, get a pointer to the node
we want to add the node to, if the left pointer of the node is null add , create a new node 
and assign it to the left side. Otherwise, update the value on the left side.
The function to add to the right is similar.
*/
BinaryTree& add_left(const T& current,T left_child){

  if(!(find_node(current,root))){
   throw invalid_argument("The specified node was not found");
  }
  node* parent_node = find_node(current,root);

  if(parent_node->BinaryTree::node::left == NULL){
    parent_node->BinaryTree::node::left = new node(left_child);
  }
  else{
    node* tmp = parent_node->BinaryTree::node::left;
    tmp->BinaryTree::node::val = left_child;
  }
  return *this;
}


BinaryTree& add_right(const T& current, T right_child){

  if(!(find_node(current,root))){
   throw invalid_argument("The specified node was not found");
  }
  node* parent_node = find_node(current,root);

  if(parent_node->BinaryTree::node::right == NULL){
    parent_node->BinaryTree::node::right = new node(right_child);
  }
  else{
    node* tmp = parent_node->BinaryTree::node::right;
    tmp->BinaryTree::node::val = right_child;
  }
    return *this;
}



class iterator
{

public:
  node* actual;
  queue<node*> q;


  iterator(){
    this->actual = NULL;
  }
  iterator(node* n){
    this->actual = n;
  }
  
  iterator(node* root ,const string& type){
    
    if(root != NULL){
      evaluate_queue(root,type);
      this->actual = q.front();
    }
    else{
      this->actual =NULL;
    }
  }

T& operator*() const {
  T& value = this->actual->BinaryTree::node::val;
  return value;
}

T* operator->() const {
  T* ptr = &(actual->BinaryTree::node::val);
  return ptr;
}

iterator& operator++(){
  int queue_size = q.size();

    if(queue_size > 1){
      q.pop();
      this->actual = q.front();
    }
    else{
      this->actual =NULL;
    }
  return *this;
}

 iterator operator++(int){
  node* n = q.front();
  iterator it(n);
  ++*this;
  return it;
}

bool operator==(const iterator& it) const {
  bool ans = (this->actual == NULL);
  return ans;
}

bool operator!=(const iterator &it) const {
  bool ans = !(*this == it);
  return ans;
}

/*
A recursive function which adds element to the queue (in order to iterate over the queue once it's complete).
Depending on the way we want to iterate over the tree, pointers to relevant nodes are 
added consequently.
*/
void evaluate_queue(node* n,const string& order){
  if(n == NULL){return;}

  if(order == "preorder") {
    q.push(n);
    }
  evaluate_queue(n->left ,order);
  if(order == "inorder"){
    q.push(n);
  }
  evaluate_queue(n->right ,order);
  if(order == "postorder") {
    q.push(n);
  }

}

};


iterator begin_preorder(){
        return iterator{root,"preorder"};
}
iterator end_preorder(){
        return iterator{};
}


iterator begin_inorder(){
  return iterator{root,"inorder"};
}
iterator end_inorder(){
  return iterator{};
}


iterator begin(){
  return iterator{root,"inorder"};
};
iterator end(){
  return iterator{};
};


iterator begin_postorder(){
      return iterator{root,"postorder"};
}
iterator end_postorder(){
          return iterator{};
}

};


}
