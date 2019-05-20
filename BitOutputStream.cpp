/**
  * FileHeader:
  * File Name: BitOutputStream.cpp
  * Description: this file implements its header file.
  * Authors: Chuhuan Huang, Junyi Wu
  */
#include "BitOutputStream.hpp"
/** Send the buffer to the output, and clear it */
void BitOutputStream::flush() {
  out.put(buf);
  out.flush();
  buf = nbits = 0;
}
/** Write the least significant bit of the argument to
  * the bit buffer, and increment the bit buffer index.
  * But flush the buffer first, if it is full.
  */
void BitOutputStream::writeBit(int i) {
  // Is the bit buffer full? Then flush it.
  if (nbits == 8) {
    flush();
  }

  // Write the least significant bit of i into the buffer
  // at the current index
  buf=((i << (7-nbits)) | buf);
  // Increment the index
  nbits++;

}
/** helper to set up padding */
void BitOutputStream::padding(){
  if(nbits!=0)
	flush();
}
/** helepr to write a byte*/
void BitOutputStream::writeByte(char a){
  for(int i=0;i<=7;i++){
  	char temp=a;
        int ret=temp>>(7-i)&1;
        writeBit(ret);
  }
}
