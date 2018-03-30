#ifndef DEF_Cipher_INT_8bit
#define DEF_Cipher_INT_8bit

#include <string>
#include <vector>
#include <seal/seal.h>
class CipherInt8bit{
public:
  //Constructor
  CipherInt8bit();
  //Methods
  seal::Ciphertext add(seal::Ciphertext b);
  void negate();
  seal::Ciphertext multiply(seal::Ciphertext b);

private:
  //We put 8 bool encoded as polynomial 0 or 1 in this vector
  //plainInt[i]is the i th bit of the integer (with i <8)
  vector<seal::Ciphertext> cipherInt = vector<seal::Ciphertext>(8);
};
#endif
