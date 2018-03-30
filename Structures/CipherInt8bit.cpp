#include "CipherInt8bit.h"

using namespace std;
using namespace seal;

//Constructor
CipherInt8bit::CipherInt8bit(){
  cout << "construction en cours" << endl;
}

//Methods
Ciphertext add(Ciphertext b){
  return b;
}
void negate(){

}
Ciphertext multiply(Ciphertext b){
  return b;
}
