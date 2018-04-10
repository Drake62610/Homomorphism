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