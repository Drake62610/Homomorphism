#include "Cipher2Bit.h"

using namespace std;
using namespace seal;
//Constructor
Cipher2Bit::Cipher2Bit(){};
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
	CipherBit carry=b.getCipherBit0().copy();
	carry=this->bitZero.add(b.getCipherBit0());
	carry=this->bitUn.add(carry);
	CipherBit carryUnused = carry.add(this->bitUn.add(b.getCipherBit1()));
	return carry;
}
Cipher2Bit Cipher2Bit::copy(){
	Cipher2Bit copy(this->bitZero,this->bitUn);
	return copy;
}
void Cipher2Bit::XOR(Cipher2Bit b){
	this->bitZero.XOR(b.getCipherBit0());
	this->bitUn.XOR(b.getCipherBit1());
}
void Cipher2Bit::reverse(){
	this->bitZero.reverse();
	this->bitUn.reverse();
}
CipherBit Cipher2Bit::multiplyComposant(){
	CipherBit result=this->bitZero;
	result.multiply(this->bitUn);
	return result;
}
CipherBit Cipher2Bit::isLesser(Cipher2Bit b){
	CipherBit tmp=this->bitUn.copy();
	tmp.XOR(b.getCipherBit1());
	tmp.reverse();
	tmp.multiply(this->bitZero.isLesser(b.getCipherBit0()));
	tmp.add(this->bitUn.isLesser(b.getCipherBit1()));
	return tmp;
}
CipherBit Cipher2Bit::isGreaterOrEqual(Cipher2Bit b){
	CipherBit result=this->isLesser(b);
	result.reverse();
	return result;
}

Cipher2Bit Cipher2Bit::multiply(Cipher2Bit b){
	CipherBit tmp0=this->bitZero.copy();
	CipherBit tmp1=this->bitUn.copy();
	tmp0.multiply(b.getCipherBit1());
	tmp1.multiply(b.getCipherBit1());
	this->bitZero.multiply(b.getCipherBit0());
	this->bitUn.multiply(b.getCipherBit0());
	CipherBit carry=this->bitUn.add(tmp0);
	carry=tmp1.add(carry);
	Cipher2Bit carry2(tmp1,carry);
	return carry2;
}
CipherBit Cipher2Bit::incrementation(CipherBit adding){
	CipherBit carry=this->bitZero.add(adding);
	carry=this->bitUn.add(adding);
	return carry;
}