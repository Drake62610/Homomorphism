#ifndef DEFDECODER
#define DEFDECODER

#include <string>
#include <vector>
#include <seal/seal.h>
#include "CipherBit.h"
#include "Cipher2Bit.h"

class CipherDecrypt{
public:
  //constructor
  /*Empty Constructor*/
  CipherDecrypt();
  /*Constructor of the class*/
  CipherDecrypt(seal::Decryptor &dec);

  //Methods
  /*
    Input : a string of n in base 2
    Output : n in base 10
  */
  int toInt(std::string n);
  /*
    Input : a string a
    Output : a cipherbit if the construction is possible (if input is "1" or "0")
  */
  int decryptCipher(CipherBit a);
  /*
    Input : a Cipher2Bit a
    Output : decryption of a
  */
  int decryptCipher(Cipher2Bit a);


private:
  seal::Decryptor* decryptor; //Use an adress to avoid calling a constructor (witch won't exist)
};

#endif
