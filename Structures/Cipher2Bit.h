#ifndef DEFCIPHER2BIT
#define DEFCIPHER2BIT

#include <string>
#include <vector>
#include <seal/seal.h>
#include "CipherBit.h"

class Cipher2Bit{
public:
  //Constructor
  Cipher2Bit(CipherBit a,CipherBit b);
  //Getter
  CipherBit getCipherBit0();
  CipherBit getCipherBit1();
  //Setter
  void setCipherBit0(CipherBit &a);
  void setCipherBit1(CipherBit &b);
  //Methods
  /*
    Input : b is the Cipher2Bit to add to the current cipher2Bit
    The cipher2Bit will be override by the result
    The output is the last carry
  */
  CipherBit add(Cipher2Bit b);
  Cipher2Bit copy();
  void XOR(Cipher2Bit b);
  CipherBit bitZero;
  CipherBit bitUn;


private:

  seal::Decryptor* decryptor;
  seal::Evaluator* evaluator; //Use an adress to avoid calling a constructor (witch won't exist)
  seal::Encryptor* encryptor; //Same here
};
#endif