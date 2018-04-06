#include "Cipher2Bit.h"

using namespace std;
using namespace seal;
//Constructor
Cipher2Bit::Cipher2Bit(CipherBit a,CipherBit b){
	(this -> bit0)=&a;
	(this -> bit1)=&b;
}

//Getter
CipherBit Cipher2Bit::getCipherBit0(){
	return *(this->bit0);
}
CipherBit Cipher2Bit::getCipherBit1(){
	return *(this->bit1);
}

//Setter
void Cipher2Bit::setCipherBit0(CipherBit &a){
	this->bit0=&a;
}
void Cipher2Bit::setCipherBit1(CipherBit &b){
	this->bit1=&b;
}


//Methods
CipherBit Cipher2Bit::add(Cipher2Bit b){
	CipherBit carry=this->bit0->add(b.getCipherBit0());
	carry=this->bit1->add(carry);
	CipherBit carryUnused = carry.add(this->bit1->add(b.getCipherBit1()));
	return carry;
}