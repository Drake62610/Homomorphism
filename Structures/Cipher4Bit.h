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

private:
  Cipher2Bit partieZero;
  Cipher2Bit partieUne;
};
#endif
