#ifndef DEFCIPHER2BIT
#define DEFCIPHER2BIT

#include <string>
#include <vector>
#include <seal/seal.h>
#include "CipherBit.h"

class Cipher2Bit{
public:
  //Constructor
  Cipher2Bit();
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
  /*
    Output : A Cipher2Bit wich is a copy of "this".
  */
  Cipher2Bit copy();
  /*
    Input : b is the Cipher2Bit to XOR to "this".
    this will be override by the result
    XOR will be comuted using the methods in CipherBit
  */
  void XOR(Cipher2Bit b);
  /*
    Output : The not gate computed using the CiberBit methods on our two parts
  */
  void reverse();
  /*
    Output : multiply every bit between them and put it in a CipherBit
  */
  CipherBit multiplyComposant();
  /*
    Input : the Cipher2Bit to compare using the ">=" operation
    Output : A Cipherbit containing an encrypted "1" if True or "0" if false
    a<b is computing using this boolean equation :
    (a1<b1)+(a1.XOR(b1).reverse()*(a0<b0))
  */
  CipherBit isLesser(Cipher2Bit b);
  /*
    Input : the CipherBit to compare using the ">=" operation
    Output : A Cipher2bit containing an encrypted
    "1" if True or "0" if false
  */
  CipherBit isGreaterOrEqual(Cipher2Bit b);
  /*
    Input : b is the Cipherbit to multiply
    this will be override by the result
    The result will look like BA where B and A are two Cipher2bit
    Output : The B part wich will be considered as the "carry"
    Tha A part will override the Cipher2bit
  */
  Cipher2Bit multiply(Cipher2Bit b);
  
private:
  CipherBit bitZero; //A cipher2Bit is composed of two part which are two Cipherbit
  CipherBit bitUn;
};
#endif
