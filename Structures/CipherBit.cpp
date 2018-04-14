#include "CipherBit.h"

using namespace std;
using namespace seal;

//Constructor
CipherBit::CipherBit(){};
CipherBit::CipherBit(seal::Evaluator &eva,seal::Encryptor &enc, seal::Ciphertext a){
  evaluator = &eva;
  encryptor = &enc;
  cipherBit = a;
}
CipherBit::CipherBit(Evaluator & eva, Encryptor &enc, Decryptor &dec, Ciphertext a){
  evaluator = &eva;
  encryptor = &enc;
  decryptor = &dec;
  cipherBit = a;
}

//Getter
Ciphertext CipherBit::getcipherBit(){
  return this->cipherBit;
}
Evaluator* CipherBit::getEvaluator(){
  return this->evaluator;
}
Encryptor* CipherBit::getEncryptor(){
  return this->encryptor;
}
//Setter
void CipherBit::setcipherBit(Ciphertext a){
  this -> cipherBit = a;
}

//Methods
void CipherBit::XORdebug(CipherBit b, Decryptor decryptor, EvaluationKeys ev_keys){
  Ciphertext xored = b.getcipherBit(); //We get the ciphertext of the CipherBit
  cout << "  Noise budget in xored: " << decryptor.invariant_noise_budget(xored) << " bits" << endl;
  cout << "  Noise budget in this -> cipherBit: " << decryptor.invariant_noise_budget(this -> cipherBit) << " bits" << endl;
  (this -> evaluator) -> negate(xored);
  cout << "  Noise budget in xored after negate: " << decryptor.invariant_noise_budget(xored) << " bits" << endl;
  (this -> evaluator) -> add(this -> cipherBit,xored);
  cout << "  Noise budget in this -> cipherBit after add: " << decryptor.invariant_noise_budget(this -> cipherBit) << " bits" << endl;
  cout << "  Noise budget in xored: " << decryptor.invariant_noise_budget(xored) << " bits" << endl;
  (this -> evaluator) -> square(this -> cipherBit); //Now this->cipherBit has the XORed result
  cout << "  Noise budget in this -> cipherBit after square: " << decryptor.invariant_noise_budget(this -> cipherBit) << " bits" << endl;
  cout << "  Noise budget in xored: " << decryptor.invariant_noise_budget(xored) << " bits" << endl;
  evaluator -> relinearize(this -> cipherBit, ev_keys);
  cout << "  Noise budget in this -> cipherBit after relinearization: " << decryptor.invariant_noise_budget(this -> cipherBit) << " bits" << endl;
  cout << "  Noise budget in xored: " << decryptor.invariant_noise_budget(xored) << " bits" << endl;
}

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
  CipherBit result(*evaluator,*encryptor,*decryptor,(Ciphertext)copy);
  return result;
}

void CipherBit::reverse(){
  Plaintext myPlaintext("1");
  Ciphertext myCipher;
  (this -> encryptor) -> encrypt(myPlaintext,myCipher);
  (this -> evaluator) -> negate(this -> cipherBit);
  (this -> evaluator) -> add(this -> cipherBit,myCipher);
}

CipherBit CipherBit::copy(){
  return CipherBit(*evaluator,*encryptor,*decryptor,(Ciphertext)cipherBit);
}

CipherBit CipherBit::isLesser(CipherBit b){
	CipherBit tmp= this->copy();
	tmp.reverse();
	tmp.multiply(b);
	return tmp;
}

CipherBit CipherBit::isGreaterOrEqual(CipherBit b){
  CipherBit tmp=this->isLesser(b);
  tmp.reverse();
  return tmp;
}

void CipherBit::multiply(CipherBit b){
  Ciphertext mult = b.getcipherBit();
  Ciphertext copy = this -> cipherBit;
  (this -> evaluator) -> multiply(this -> cipherBit,mult);
}

void CipherBit::reduceNoise(){
  Plaintext tmp; Ciphertext tmp2;
  this -> decryptor -> decrypt (this -> cipherBit,tmp);
  cout << "bit = " << tmp.to_string() << endl;
  this -> encryptor -> encrypt(tmp,tmp2);
  this -> cipherBit = tmp2;
}
