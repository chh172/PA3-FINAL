/**
  * FileHeader:
  * File Name: BitInputStream.hpp
  * Description: this header file defines the class BitInputStream and its
  * functionality.
  * Authors: Chuhuan Huang, Junyi Wu
  */
#ifndef BITINPUTSTREAM_HPP
#define BITINPUTSTREAM_HPP

#include <iostream>
using namespace std;
class BitInputStream {
private:
  char buf; // one byte buffer of bits
  int nbits; // how many bits have been read from buf
  std::istream & in; // the input stream to use
public:
  BitInputStream(std::istream & is) : in(is) {
    buf = 0;
    nbits = 8;
  }
  /** Fill the buffer from the input */
  void fill();
  /** Read the next bit from the bit buffer.
    * Fill the buffer from the input stream first if needed.
    * Return 1 if the bit read is 1
    * return 0 if the bit read is 0
    *
    */
  int readBit();
};
#endif
