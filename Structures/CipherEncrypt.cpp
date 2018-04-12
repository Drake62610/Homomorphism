#include "CipherEncrypt.h"


using namespace std;
using namespace seal;
//constructor
CipherEncrypt::CipherEncrypt(){
}

CipherEncrypt::CipherEncrypt(Evaluator &eval, Encryptor &enc){
  evaluator = &eval;
  encryptor = &enc;
}

string CipherEncrypt::toBinary(int n){
    string r;
    while(n!=0) {
      r=(n%2==0 ?"0":"1")+r;
      n/=2;
    }
    return r;
}

CipherBit CipherEncrypt::encryptCipher(char a){
  if (a=='1'){
    Plaintext myPlaintext1("1");
    Ciphertext myCipher1; this -> encryptor -> encrypt(myPlaintext1,myCipher1);
    cout << "one" << endl;
    return CipherBit(*evaluator,*encryptor, myCipher1);
  }
  else if(a=='0'){
    Plaintext myPlaintext0("0");
    Ciphertext myCipher0; this -> encryptor -> encrypt(myPlaintext0,myCipher0);
    cout << "zero" << endl;
    return CipherBit(*evaluator,*encryptor, myCipher0);
  }
  else{
    throw string("Cipherbit can't be generated");
  }
}

Cipher2Bit CipherEncrypt::encodeInt2bit(int a){
  if (a <= 3 && a>= 0){
    string tmp = this -> toBinary(a);
    //bitOne = CipherBit(this -> evaluator, this -> encryptor, )
    //cout << "1: " << tmp[1] << endl;
    //this -> encryptCipher(tmp[1]);
    //cout << "0: " << tmp[0] << endl;
    //this -> encryptCipher(tmp[0]);
    return Cipher2Bit(this -> encryptCipher(tmp[1]),this -> encryptCipher(tmp[0]));
  }
  else{
    throw string("Integer not taken in charge");
  }
}
