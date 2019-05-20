  FileHeader:
  File Name: readme.md
  Description: this file answers the readme questions
  Authors: Chuhuan Huang, Junyi Wu

  1.there is an advantage to compressing a file before encrypting it because
  encryption before compression make the file unreadable.
  2.
  compress then encryption : 1,870,789 bytes
  encryption then compress: 3,289,122 bytes
  consistent with our hypothesis as encrypted file became harder to compress and
  the resulting compression file is way larger than its counterpart.
  3.
  this compress will work better as XORing encryption is
  less secure but more readable. And compress works better with readable files.
  4.
  same as XORing just flip some bits of the original one, and won't affect the
  overall compress.
  5.
  same, similar reason that XORing just flips some bits and the total number of
  the bytes remains unchanged.
