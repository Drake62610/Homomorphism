#ifndef DEFENCODER
#define DEFENCODER

#include <string>
#include <vector>
#include <seal/seal.h>
#include "Cipher2Bit.h"
#include "Cipher3Bit.h"
#include "Cipher4Bit.h"

class CipherEncrypt{
public:
  //constructor
  /*Empty Constructor*/
  CipherEncrypt();
  /*Constructor of the class*/
  CipherEncrypt(seal::Evaluator &eval,seal::Encryptor &enc);

  //Methods
  /*
    Input : an integer n
    Output : a string of n writen in base 2.
  */
  std::string toBinary(int n);
  /*
    Input : a string a
    Output : a cipherbit if the construction is possible (if input is "1" or "0")
  */
  CipherBit encryptCipher(char a);
  /*
    Input : an integer a
    Output : a Cipher2Bit if the integer can be coded on 2 bits
  */
  Cipher2Bit encodeInt2bit(int a);
  /*
    Input : an integer a
    Output : a Cipher2Bit if the integer can be coded on 2 bits
  */
  Cipher3Bit encodeInt3bit(int a);
  /*
    Input : an integer a
    Output : a Cipher2Bit if the integer can be coded on 2 bits
  */
  Cipher4Bit encodeInt4bit(int a);



private:
  seal::Evaluator* evaluator; //Use an adress to avoid calling a constructor (witch won't exist)
  seal::Encryptor* encryptor;

};

#endif
