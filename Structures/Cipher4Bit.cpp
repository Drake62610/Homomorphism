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
Cipher4Bit Cipher4Bit::copy(){
	Cipher4Bit copy(this->partieZero,this->partieUne);
	return copy;
}
void Cipher4Bit::XOR(Cipher4Bit b){
	this->partieZero.XOR(b.getPartieZero());
	this->partieUne.XOR(b.getPartieUne());
}
void Cipher4Bit::reverse(){
	this->partieZero.reverse();
	this->partieUne.reverse();
}
CipherBit Cipher4Bit::multiplyComposant(){
	CipherBit result=this->partieZero.multiplyComposant();
	result.multiply(this->partieUne.multiplyComposant());
	return result;
}
CipherBit Cipher4Bit::isLesser(Cipher4Bit b){
	Cipher2Bit tmp=this->partieUne.copy();
	tmp.XOR(b.getPartieUne());
	tmp.reverse();
	CipherBit result=tmp.multiplyComposant();
	result.multiply(this->partieZero.isLesser(b.getPartieZero()));
	result.add(this->partieUne.isLesser(b.getPartieUne()));
	return result;
}
CipherBit Cipher4Bit::isGreaterOrEqual(Cipher4Bit b){
	CipherBit result=this->isLesser(b);
	result.reverse();
	return result;
}
void Cipher4Bit::reduceNoise(){
	(this->partieZero).reduceNoise();
	(this->partieUne).reduceNoise();
}
/*Cipher4Bit Cipher4Bit::multiply(Cipher4Bit b){
	Cipher2Bit tmp0=this->partieZero.copy();
	Cipher2Bit tmp1=this->partieUne.copy();
	tmp0.multiply(b.getPartieZero());
	tmp1.multiply(b.getPartieUne());
	this->partieZero.multiply(b.getPartieZero());
	this->partieUne.multiply(b.getPartieUne());
	CipherBit carry=this->bitUn.add(tmp0);
	carry=tmp1.add(carry);
	Cipher2Bit carry2(tmp1,carry);
	return carry2;
}*/
