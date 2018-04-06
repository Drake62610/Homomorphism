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
void Cipher2Bit::print(){
	Plaintext plainResult("5");
	(this->decryptor)->decrypt(this->getCipherBit0().getcipherBit(),plainResult);
	cout<<"bit0 = "<<plainResult.to_string()<<endl;
}

CipherBit Cipher2Bit::add(Cipher2Bit b){
	cout<<"on add1"<<endl;
	Plaintext plainResult("6");
	CipherBit carry0=this->bitZero.add(b.getCipherBit0());
	cout<<"on add2"<<endl;
	(this->decryptor)->decrypt(carry0.getcipherBit(),plainResult);
	cout<<"carry0= "<<plainResult.to_string()<<endl;
	carry0=this->bitUn.add(carry0);
	cout<<"on add"<<endl;
	CipherBit carryUnused = carry0.add(this->bitUn.add(b.getCipherBit1()));
	cout<<"on add"<<endl;
	return carry0;
}