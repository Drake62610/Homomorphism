#ifndef DEFCIPHER4BIT
#define DEFCIPHER4BIT

#include <string>
#include <vector>
#include <seal/seal.h>
#include "Cipher2Bit.h"

class Cipher4Bit{
public:
  //Constructor
  Cipher4Bit(Cipher2Bit a,Cipher2Bit b);
  //Getter
  Cipher2Bit getPartieZero();
  Cipher2Bit getPartieUne();
  //Setter
  void setPartieZero(Cipher2Bit a);
  void setPartieUne(Cipher2Bit b);

  //Methods
  /*
    Input : b is the Cipher4Bit to add to the current cipher4Bit
    The cipher4Bit will be override by the result
    The output is the last carry
  */
  CipherBit add(Cipher4Bit b);
  /*
    Output : A Cipher4Bit wich is a copy of "this".
  */
  Cipher4Bit copy();
  /*
    Input : b is the Cipher4Bit to XOR to "this".
    this will be override by the result
    XOR will be comuted using the methods in CipherBit
  */
  void XOR(Cipher4Bit b);
  /*
    Output : The not gate computed using the CiberBit methods on our two parts
  */
  void reverse();
  /*
    Output : multiply every bit between them and put it in a CipherBit
  */
  CipherBit multiplyComposant();
  /*
    Input : the Cipher4Bit to compare using the "<" operation
    Output : A Cipherbit containing an encrypted "1" if True or "0" if false
  */
  CipherBit isLesser(Cipher4Bit b);
  /*
    Input : the CipherBit to compare using the ">=" operation
    Output : A Cipher2bit containing an encrypted
    "1" if True or "0" if false
  */
  CipherBit isGreaterOrEqual(Cipher4Bit b);

private:
  Cipher2Bit partieZero;
  Cipher2Bit partieUne;
};
#endif
