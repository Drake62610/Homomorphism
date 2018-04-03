#include "CipherBit.h"

using namespace std;
using namespace seal;

//Constructor
CipherBit::CipherBit(seal::Evaluator &eva, seal::Ciphertext a){
  cout << "construction en cours" << endl;
  evaluator = &eva;
  cipherBit = a;
  cout << "done" << endl;
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
/*
  Input : b is the Cipherbit to XOR to this->cipherBit
  this->cipherBit will be override by the result
  XOR will be comuted by (a-b)^2
*/
void CipherBit::XOR(CipherBit b){
  Ciphertext xored = b.getcipherBit(); //We get the ciphertext of the CipherBit
  (this -> evaluator) -> negate(xored);
  (this -> evaluator) -> add(this -> cipherBit,xored);
  (this -> evaluator) -> square(this -> cipherBit); //Now this->cipherBit has the XORed result
}
/*
  Input : b is the Cipherbit to add to this->cipherBit
  Output : The carry as a Cipherbit
*/
CipherBit CipherBit::add(CipherBit b){
  Ciphertext adding = b.getcipherBit();
  Ciphertext copy = this -> cipherBit;
  this -> XOR(b);
  (this -> evaluator) -> multiply(copy,adding);
  CipherBit result(*evaluator,(Ciphertext)copy);
  return result;
}

void CipherBit::negate(){

}
CipherBit multiply(CipherBit b){
  return b;
}
