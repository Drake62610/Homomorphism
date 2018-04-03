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

//Setter
void CipherBit::setcipherBit(Ciphertext a){
  this -> cipherBit = a;
}

//Methods
/*
  Input : b is the Cipherbit to add to This
  Output : The carry as a Cipherbit
*/
CipherBit CipherBit::add(CipherBit b){
  Ciphertext a = this -> cipherBit;
  (this -> evaluator) -> add(a,b.cipherBit);
  return b;
}
void CipherBit::negate(){

}
CipherBit multiply(CipherBit b){
  return b;
}
