/**
  * FileHeader:
  * File Name: compress.cpp
  * Description: this file is the main function of compress functionality.
  * Authors: Junyi Wu, Chuhuan Huang
  */
#include "HCTree.hpp"
#include "HCNode.hpp"
#include <fstream>

using namespace std;

int main(int argc, char const *argv[]) {


  /* code */
  ifstream in;
  // declare an ifstream
  string file = argv[1];
  // get the filename arg
  in.open(file, ios::binary);
  // open file
  vector<int> freqs (256, 0);
  // init freqs vector
  in.seekg(0,ios::end);
  // error case immediately return
  if((in.tellg())==0){
      ofstream out;
      out.open(argv[2],ios::out);
      out.close();
      return 0;
  }
  in.close();
  // reopen file
  in.open(file, ios::binary);
  // read the first char and cast to int
  int read=in.get();
  //read bytes and count frequency
  while (in.good()) {

    freqs[read]++;
    read=in.get();
  }

  in.close();

  //construct the HC tree
  HCTree tree;
  tree.build(freqs);
  int count=0;
  for(int i =0; i<freqs.size();i++){
  count+=freqs[i];
}
  //open output file
  ofstream out;
  out.open(argv[2],ios::out);
  //write header to output
  //for(unsigned int i=0; i< freqs.size();i++){
  //  out<<freqs[i]<<endl;
  //}
  out<<count<<endl;
  //open input file and read again

  in.open(file, ios::binary);
  read=in.get();
  //create bitwiseStream file
  BitOutputStream bitOut(out);
  // preOrder traverse.
  tree.traverseTree(bitOut);
  //bitwise encoding
  while(read!=EOF){
    tree.encode(read,bitOut);
    read=in.get();
  }
  //add padding to print the last char
  bitOut.padding();
  //close files
  in.close();
  out.close();
  return 0;
}
