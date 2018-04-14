#include "Cipher3Bit.h"

using namespace std;
using namespace seal;
//Constructor
Cipher3Bit::Cipher3Bit(){}
Cipher3Bit::Cipher3Bit(Cipher2Bit a,CipherBit b){
	(this->partie0)=a.copy();
	(this->msb)=b.copy();
}

//Getter
Cipher2Bit Cipher3Bit::getPartie0(){
	return (this->partie0).copy();
}
CipherBit Cipher3Bit::getMSB(){
	return (this->msb).copy();
}

//Setter
void Cipher3Bit::setPartie0(Cipher2Bit a){
	this->partie0=a.copy();
}
void Cipher3Bit::setMSB(CipherBit b){
	this->msb=b.copy();
}
Cipher3Bit Cipher3Bit::copy(){
	Cipher3Bit copy(this->partie0,this->msb);
	return copy;
}
void Cipher3Bit::XOR(Cipher3Bit b){
	this->partie0.XOR(b.getPartie0());
	this->msb.XOR(b.getMSB());
}
void Cipher3Bit::reverse(){
	this->partie0.reverse();
	this->msb.reverse();
}
CipherBit Cipher3Bit::multiplyComposant(){
	CipherBit result=this->partie0.multiplyComposant();
	result.multiply(this->msb);
	return result;
}
CipherBit Cipher3Bit::incrementation(CipherBit adding){
	CipherBit carry=this->partie0.incrementation(adding);
	carry=this->msb.add(carry);
	return carry;
}
void Cipher3Bit::reduceNoise(){
	(this->partie0).reduceNoise();
	(this->msb).reduceNoise();
}
