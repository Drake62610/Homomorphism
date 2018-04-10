#ifndef DEFCIPHER2BIT
#define DEFCIPHER2BIT

#include <string>
#include <vector>
#include <seal/seal.h>
#include "Cipher2Bit.h"

class Cipher4Bit{
public:
  //Constructor
  Cipher4Bit(Cipher2Bit a,Cipher2Bit b);
  //Getter
  Cipher4Bit getPartieZero();
  Cipher4Bit getPartieUne();
  //Setter
  void setPartieZero(Cipher2Bit a);
  void setPartieUne(Cipher2Bit b);

private:
  Cipher2Bit partieZero;
  Cipher2Bit partieUne;
};
#endif
