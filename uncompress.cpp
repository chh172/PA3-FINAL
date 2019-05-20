/**
  * FileHeader:
  * File Name: uncompress.cpp
  * Description: this file is the main function of uncompress functionality.
  * Authors: Junyi Wu, Chuhuan Huang
  */
#include "HCTree.hpp"
#include "HCNode.hpp"
#include <fstream>
#include <string>


using namespace std;

int main(int argc, char const *argv[]) {
  // declare ifstream
  ifstream in;
  // open file
  in.open(argv[1], ios::binary);
  std::string freq;
  // init freqs vector
  vector <int> freqs(256,0);
  //check if empty
  in.seekg(0,ios::end);
  // error case immediately return
  if((in.tellg())==0){
      ofstream out;
      out.open(argv[2],ios::out);
      out.close();
      return 0;
  }
  // reopen the file
  in.close();
  in.open(argv[1], ios::binary);
  int count=0;
  //reconstruct the tree
  /*string read;
  for(int i =0; i<256;i++){
    getline(in,read);
    int freq=stoi(read,nullptr);
    freqs[i]=freq;
    count+=freq;
  }*/

  // default tree
  HCTree tree;
  string read;
  getline(in,read);
  count=stoi(read,nullptr);
  // ofstream
  ofstream out;
  // open outfile
  out.open(argv[2], ios::out);
  BitInputStream bitIn(in);
  // rebuild the tree
  tree.rebuild(bitIn);
  // direct the output the outfile
  for(int i =0; i<count;i++){
    out<<(unsigned char)tree.decode(bitIn);
  }
  // close the streams.
  in.close();
  out.close();


}
