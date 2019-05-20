/**
  * FileHeader:
  * File Name: BitOutputStream.hpp
  * Description: this header file defines the class BitOutputStream and its
  * functionality.
  * Authors: Chuhuan Huang, Junyi Wu
  */
#ifndef BITOUTPUTSTREAM_HPP
#define BITOUTPUTSTREAM_HPP
#include <iostream>
using namespace std;
class BitOutputStream {
private:
  char buf; // one byte buffer of bits
  int nbits; // how many bits have been written to buf
  std::ostream & out; // reference to the output stream to use
public:
/** Initialize a BitOutputStream that will use
* the given ostream for output */
  BitOutputStream(std::ostream & os) : out(os), buf(0), nbits(0) {
// clear buffer and bit counter
}
/** Send the buffer to the output, and clear it */
void flush();
/** Write the least significant bit of the argument to
  * the bit buffer, and increment the bit buffer index.
  * But flush the buffer first, if it is full.
  */
void writeBit(int i);
/** helper to write a byte*/
void writeByte(char a);
/** helepr to set up a padding*/
void padding();
};
#endif
