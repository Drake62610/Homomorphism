#ifndef DEFCIPHER3BIT
#define DEFCIPHER3BIT

#include <string>
#include <vector>
#include <seal/seal.h>
#include "Cipher2Bit.h"

class Cipher3Bit{
public:
  //Constructor
  Cipher3Bit();
  Cipher3Bit(Cipher2Bit a,CipherBit b);
  //Getter
  Cipher2Bit getPartie0();
  CipherBit getMSB();
  //Setter
  void setPartie0(Cipher2Bit a);
  void setMSB(CipherBit b);

  //Methods
  /*
    Output : A Cipher4Bit wich is a copy of "this".
  */
  Cipher3Bit copy();
  /*
    Input : b is the Cipher3Bit to XOR to "this".
    this will be override by the result
    XOR will be comuted using the methods in CipherBit
  */
  void XOR(Cipher3Bit b);
  /*
    Output : The not gate computed using the CiberBit methods on our two parts
  */
  void reverse();
   /*
    Output : multiply every bit between them and put it in a CipherBit
  */
  CipherBit multiplyComposant();
  /*
    Input : adding is the Cipherbit to add
    this will be override by the result
    Output: the carry of the addition
  */
  CipherBit incrementation(CipherBit adding);

private:
  Cipher2Bit partie0;
  CipherBit msb;
};
#endif
