#include "Cipher4Bit.h"

using namespace std;
using namespace seal;
//Constructor
Cipher4Bit::Cipher4Bit(Cipher2Bit a,Cipher2Bit b){
	(this->partieZero)=a.copy();
	(this->partieUne)=b.copy();
}

//Getter
Cipher2Bit Cipher4Bit::getPartieZero(){
	return (this->partieZero);
}
Cipher2Bit Cipher4Bit::getPartieUne(){
	return (this->partieUne);
}

//Setter
void Cipher4Bit::setPartieZero(Cipher2Bit a){
	this->partieZero=a.copy();
}
void Cipher4Bit::setPartieUne(Cipher2Bit b){
	this->partieUne=b.copy();
}

//Methods
CipherBit Cipher4Bit::add(Cipher4Bit b){
	Plaintext myPlaintext0("0");
	Ciphertext myCipher0;
	this->partieZero.getCipherBit0().getEncryptor()->encrypt(myPlaintext0,myCipher0);
	CipherBit myCipherBit0(*(this->partieZero.getCipherBit0().getEvaluator()),*this->partieZero.getCipherBit0().getEncryptor(), myCipher0);
	Cipher2Bit carry(myCipherBit0,myCipherBit0);
	carry.getCipherBit0()=this->partieZero.add(b.getPartieZero());
	carry.getCipherBit0()=this->partieUne.add(carry);
	myCipherBit0=carry.getCipherBit0().add(this->partieUne.add(b.getPartieUne()));
	return carry.getCipherBit0();
}