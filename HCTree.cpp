/**
  * FileHeader:
  * File Name: HCTree.cpp
  * Description: this file implements its header file.
  * Authors: Chuhuan Huang, Junyi Wu
  */
#include "HCTree.hpp"
#include "HCNode.hpp"

/** Use the Huffman algorithm to build a Huffman coding trie.
*  PRECONDITION: freqs is a vector of ints, such that freqs[i] is
*  the frequency of occurrence of byte i in the message.
*  POSTCONDITION:  root points to the root of the trie,
*  and leaves[i] points to the leaf node containing byte i.
*/
HCTree::~HCTree() {
  deleteAll(root);
}
void HCTree::deleteAll(HCNode * n) {
  /* Pseudo Code:
  if current node is null: return;
  recursively delete left sub-tree
  recursively delete right sub-tree
  delete current node
  */

  //if current node is null, return
  if (n == nullptr) {return;}
  //recursively delete left subtree
  deleteAll(n->c0);
  //recursively delete right subtree
  deleteAll(n->c1);
  //delete current node
  delete n;
  return;
}
void HCTree::build(const vector<int>& freqs) {
  for (size_t i = 0; i < freqs.size(); i++) {
    if (freqs[i] != 0) {
      leaves[i] = new HCNode(freqs[i],i);
    }
  }
  for (size_t i = 0; i < leaves.size(); i++) {
    if (leaves[i] != nullptr) {
      body.push(leaves[i]);
    }
  }
  //root = buildHelper();
  while (body.size() > 1) {
    HCNode * p0 = body.top();
    body.pop();
    HCNode * p1 = body.top();
    body.pop();
    HCNode * internal = new HCNode(p0->count + p1->count, p0->symbol);
    internal->c0 = p0;
    internal->c1 = p1;
    p0->p = internal;
    p1->p = internal;
    body.push(internal);
  }
  root = body.top();
}

/** Write to the given BitOutputStream
*  the sequence of bits coding the given symbol.
*  PRECONDITION: build() has been called, to create the coding
*  tree, and initialize root pointer and leaves vector.
*/
void HCTree::encode(byte symbol, BitOutputStream& out) const {
  HCNode * traverse = leaves[symbol];
  string str = "";
  while (traverse != root) {
    if (traverse == traverse->p->c0) {
      //out.writeBit(0);
      str = "0" + str;
    }
    else {
      //out.writeBit(1);
      str = "1" + str;

    }
    traverse = traverse->p;
  }

  //write the string to bit int
  for(char& c : str) {
    int x = (int)c-48;
    out.writeBit(x);
  }

}

/** Write to the given ofstream
*  the sequence of bits (as ASCII) coding the given symbol.
*  PRECONDITION: build() has been called, to create the coding
*  tree, and initialize root pointer and leaves vector.
*  THIS METHOD IS USEFUL FOR THE CHECKPOINT BUT SHOULD NOT
*  BE USED IN THE FINAL SUBMISSION.
*/
void HCTree::encode(byte symbol, ofstream& out) const {
  /*
  HCNode * traverse = leaves[0];
  for (size_t i = 0; i < leaves.size(); i++) {
  if (traverse->symbol == symbol) {
  break;
}
traverse = leaves[i];
} */
HCNode * traverse = leaves[symbol];
string str = "";
while (traverse != root) {
  if (traverse == traverse->p->c0) {
    str = "0" + str;
  }
  else {
    str = "1" + str;
  }
  traverse = traverse->p;
}
out << str;
}

/** Return symbol coded in the next sequence of bits from the stream.
*  PRECONDITION: build() has been called, to create the coding
*  tree, and initialize root pointer and leaves vector.
*/
int HCTree::decode(BitInputStream& in) const {
  HCNode * trav = root;
  //char c = in.get(); //TODO : readBit
  int c = in.readBit();
  while (trav->c1!=nullptr||trav->c0!=nullptr) {
    /* code */

    if (c == 0) {
      if (trav->c0 != nullptr) {
        trav = trav->c0;
      }
    }
    if (c == 1) {
      if (trav->c1 != nullptr) {
        trav = trav->c1;
      }
    }
    if(trav->c1==nullptr&&trav->c0==nullptr)
    return trav->symbol;

    c = in.readBit();
  }
  return (int) trav->symbol;
}

/** Return the symbol coded in the next sequence of bits (represented as
*  ASCII text) from the ifstream.
*  PRECONDITION: build() has been called, to create the coding
*  tree, and initialize root pointer and leaves vector.
*  THIS METHOD IS USEFUL FOR THE CHECKPOINT BUT SHOULD NOT BE USED
*  IN THE FINAL SUBMISSION.
*/
int HCTree::decode(ifstream& in) const {
  HCNode * trav = root;
  string set("01");
  char c = in.get();
  while (in.good()) {
    /* code */

    if (c == set[0]) {
      if (trav->c0 != nullptr) {
        trav = trav->c0;
      }
    }
    if (c == set[1]) {
      if (trav->c1 != nullptr) {
        trav = trav->c1;
      }
    }
    if(trav->c1==nullptr&&trav->c0==nullptr)
    return trav->symbol;
    c = in.get();
  }
  return (int) trav->symbol;
}
/** PreOrder Traverse of the HCTree*/
void HCTree::traverseTree(BitOutputStream& out )  {
  traverseTreeHelper(root, out);

}
/** recursive helper to pre-order traverse*/
void HCTree::traverseTreeHelper(HCNode* node,BitOutputStream& out )  {
  // base case
  if(node==nullptr){
    return;
  }
  // leaf case
  if(node->c0==nullptr&&node->c1==nullptr){
    out.writeBit(1);
    out.writeByte(node->symbol);
  }
  // internal case
  else{
    out.writeBit(0);
    traverseTreeHelper(node->c0, out);
    traverseTreeHelper(node->c1, out);
  }
}
/** rebuild the HCTree*/
void HCTree::rebuild(BitInputStream& in){
  root = rebuildHelper(nullptr,in);
}
/** recursive helper to rebuild*/
HCNode* HCTree::rebuildHelper(HCNode * node,BitInputStream& in){
  // read in
  int num=in.readBit();
  // internal case
  if(num==0){
    HCNode * curr=new HCNode(0,0);
    curr->c0=rebuildHelper(curr,in);
    if(curr->c0 != nullptr){
      curr->c0->p = curr;
    }
    curr->c1=rebuildHelper(curr,in);
    if(curr->c1 != nullptr){
      curr->c1->p = curr;
    }
    return curr;
  }
  // leaf case
  if(num==1){
    int symb=0;
    for(int i=0;i<=7;i++){
      int a=in.readBit();
      symb=symb|(a<<(7-i));
    }
    HCNode * leaf=new HCNode(0,(char)symb);
    return leaf;
  }
}
