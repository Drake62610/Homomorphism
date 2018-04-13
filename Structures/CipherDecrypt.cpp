#include "CipherDecrypt.h"

using namespace std;
using namespace seal;
//constructor
CipherDecrypt::CipherDecrypt(){
}

CipherDecrypt::CipherDecrypt(Decryptor &dec){
  decryptor = &dec;
}

int CipherDecrypt::toInt(string n){
  return 0;
}

int CipherDecrypt::decryptCipher(CipherBit a){
  return 0;
}

int CipherDecrypt::decryptCipher(Cipher2Bit a){
  Plaintext plainResult("0");
  decryptor.decrypt(c2B.getCipherBit0().getcipherBit(),plainResult);
  cout << "bit0= " << plainResult.to_string();
  string =  plainResult.to_string();
  decryptor.decrypt(c2B.getCipherBit1().getcipherBit(),plainResult);
  cout << " bit1= " << plainResult.to_string() << endl;
  string = string +  plainResult.to_string()
  cout << string << endl;
  return 0;
}
