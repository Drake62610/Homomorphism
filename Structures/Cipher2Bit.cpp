#include "Cipher2Bit.h"

using namespace std;
using namespace seal;
//Constructor
Cipher2Bit::Cipher2Bit(CipherBit a,CipherBit b){
	(this->bitZero)=a.copy();
	(this->bitUn)=b.copy();
}

//Getter
CipherBit Cipher2Bit::getCipherBit0(){
	return (this->bitZero);
}
CipherBit Cipher2Bit::getCipherBit1(){
	return (this->bitUn);
}

//Setter
void Cipher2Bit::setCipherBit0(CipherBit &a){
	this->bitZero=a.copy();
}
void Cipher2Bit::setCipherBit1(CipherBit &b){
	this->bitUn=b.copy();
}


//Methods

CipherBit Cipher2Bit::add(Cipher2Bit b){
	cout<<"on add"<<endl;
	Plaintext plainResult("0");
	CipherBit carry=b.getCipherBit0().copy();
	carry=this->bitZero.add(b.getCipherBit0());
	carry=this->bitUn.add(carry);
	CipherBit carryUnused = carry.add(this->bitUn.add(b.getCipherBit1()));
	return carry;
}