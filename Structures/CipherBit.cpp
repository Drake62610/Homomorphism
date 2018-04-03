#include "CipherBit.h"

using namespace std;
using namespace seal;

//Constructor
CipherBit::CipherBit(seal::Evaluator &eva,seal::Encryptor &enc, seal::Ciphertext a){
  evaluator = &eva;
  encryptor = &enc;
  cipherBit = a;
}

//Getter
Ciphertext CipherBit::getcipherBit(){
  return this->cipherBit;
}
Evaluator* CipherBit::getEvaluator(){
  return this->evaluator;
}
//Setter
void CipherBit::setcipherBit(Ciphertext a){
  this -> cipherBit = a;
}

//Methods
void CipherBit::XOR(CipherBit b){
  Ciphertext xored = b.getcipherBit(); //We get the ciphertext of the CipherBit
  (this -> evaluator) -> negate(xored);
  (this -> evaluator) -> add(this -> cipherBit,xored);
  (this -> evaluator) -> square(this -> cipherBit); //Now this->cipherBit has the XORed result
}

CipherBit CipherBit::add(CipherBit b){
  Ciphertext adding = b.getcipherBit();
  Ciphertext copy = this -> cipherBit;
  this -> XOR(b);
  (this -> evaluator) -> multiply(copy,adding);
  CipherBit result(*evaluator,*encryptor,(Ciphertext)copy);
  return result;
}

void CipherBit::reverse(){
  Plaintext myPlaintext("1");
  Ciphertext myCipher;
  (this -> encryptor) -> encrypt(myPlaintext,myCipher);
  this -> XOR(CipherBit(*evaluator,*encryptor,(Ciphertext)myCipher));
}
CipherBit multiply(CipherBit b){
  return b;
}
