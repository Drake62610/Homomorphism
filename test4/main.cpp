#include <vector>
#include <seal/seal.h>
#include <../Structures/CipherBit.h>
#include <../Structures/Cipher2Bit.h>
#include <../Structures/Cipher4Bit.h>

using namespace std;
using namespace seal;

//Test1Bit
void test_xor1bit(Evaluator evaluator, Decryptor decryptor,Encryptor encryptor){
  cout << "Table de vérité du XOR sur 1 bit" << endl;
  Plaintext myPlaintext1("1");Plaintext myPlaintext0("0");
  Plaintext plainResult("0");
  Ciphertext myCipher1; encryptor.encrypt(myPlaintext1,myCipher1);
  Ciphertext myCipher0; encryptor.encrypt(myPlaintext0,myCipher0);
  CipherBit myCipherBit1(evaluator,encryptor, myCipher1);
  CipherBit myCipherBit0(evaluator,encryptor, myCipher0);

  //Tests
  CipherBit result = myCipherBit0;
  result.XOR(myCipherBit0);
  decryptor.decrypt(result.getcipherBit(),plainResult);
  cout << "0 XOR 0 = " << plainResult.to_string() << endl;

  result.XOR(myCipherBit1);
  decryptor.decrypt(result.getcipherBit(),plainResult);
  cout << "0 XOR 1 = " << plainResult.to_string() << endl;

  result = myCipherBit1;
  result.XOR(myCipherBit0);
  decryptor.decrypt(result.getcipherBit(),plainResult);
  cout << "1 XOR 0 = " << plainResult.to_string() << endl;

  result.XOR(myCipherBit1);
  decryptor.decrypt(result.getcipherBit(),plainResult);
  cout << "1 XOR 1 = " << plainResult.to_string() << endl;
}
void test_add1bit(Evaluator evaluator, Decryptor decryptor,Encryptor encryptor){
  cout << "Table de vérité du + sur 1 bit" << endl;
  Plaintext myPlaintext1("1");Plaintext myPlaintext0("0");
  Plaintext plainResult("0"); Plaintext plainCarry("0");
  Ciphertext myCipher1; encryptor.encrypt(myPlaintext1,myCipher1);
  Ciphertext myCipher0; encryptor.encrypt(myPlaintext0,myCipher0);
  CipherBit myCipherBit1(evaluator,encryptor, myCipher1);
  CipherBit myCipherBit0(evaluator,encryptor, myCipher0);
  CipherBit cipherCarry(evaluator,encryptor, myCipher0);

  //Tests
  CipherBit result = myCipherBit0;
  cipherCarry = result.add(myCipherBit0);
  decryptor.decrypt(result.getcipherBit(),plainResult);
  decryptor.decrypt(cipherCarry.getcipherBit(),plainCarry);
  cout << "0 + 0 = " << plainResult.to_string() << "  carry = " << plainCarry.to_string() << endl;

  result = myCipherBit0;
  cipherCarry = result.add(myCipherBit1);
  decryptor.decrypt(result.getcipherBit(),plainResult);
  decryptor.decrypt(cipherCarry.getcipherBit(),plainCarry);
  cout << "0 + 1 = " << plainResult.to_string() << "  carry = " << plainCarry.to_string() << endl;

  result = myCipherBit1;
  cipherCarry = result.add(myCipherBit0);
  decryptor.decrypt(result.getcipherBit(),plainResult);
  decryptor.decrypt(cipherCarry.getcipherBit(),plainCarry);
  cout << "1 + 0 = " << plainResult.to_string() << "  carry = " << plainCarry.to_string() << endl;

  result = myCipherBit1;
  cipherCarry = result.add(myCipherBit1);
  decryptor.decrypt(result.getcipherBit(),plainResult);
  decryptor.decrypt(cipherCarry.getcipherBit(),plainCarry);
  cout << "1 + 1 = " << plainResult.to_string() << "  carry = " << plainCarry.to_string() << endl;
}
void test_isLesser1bit(Evaluator evaluator, Decryptor decryptor,Encryptor encryptor){
  cout << "Table de vérité du < sur 1 bit" << endl;
  Plaintext myPlaintext1("1");Plaintext myPlaintext0("0");
  Plaintext plainResult("0");
  Ciphertext myCipher1; encryptor.encrypt(myPlaintext1,myCipher1);
  Ciphertext myCipher0; encryptor.encrypt(myPlaintext0,myCipher0);
  CipherBit myCipherBit1(evaluator,encryptor, myCipher1);
  CipherBit myCipherBit0(evaluator,encryptor, myCipher0);

  //Tests
  CipherBit result = myCipherBit0;
  decryptor.decrypt(result.isLesser(myCipherBit0).getcipherBit(),plainResult);
  cout << "0 < 0 = " << plainResult.to_string() << endl;

  result = myCipherBit0;
  decryptor.decrypt(result.isLesser(myCipherBit1).getcipherBit(),plainResult);
  cout << "0 < 1 = " << plainResult.to_string() << endl;

  result = myCipherBit1;
  decryptor.decrypt(result.isLesser(myCipherBit0).getcipherBit(),plainResult);
  cout << "1 < 0 = " << plainResult.to_string() << endl;

  result = myCipherBit1;
  decryptor.decrypt(result.isLesser(myCipherBit1).getcipherBit(),plainResult);
  cout << "1 < 1 = " << plainResult.to_string() << endl;
}
void test_isGreaterOrEqual1bit(Evaluator evaluator, Decryptor decryptor,Encryptor encryptor){
  cout << "Table de vérité du >= sur 1 bit" << endl;
  Plaintext myPlaintext1("1");Plaintext myPlaintext0("0");
  Plaintext plainResult("0");
  Ciphertext myCipher1; encryptor.encrypt(myPlaintext1,myCipher1);
  Ciphertext myCipher0; encryptor.encrypt(myPlaintext0,myCipher0);
  CipherBit myCipherBit1(evaluator,encryptor, myCipher1);
  CipherBit myCipherBit0(evaluator,encryptor, myCipher0);

  //Tests
  CipherBit result = myCipherBit0;
  decryptor.decrypt(result.isGreaterOrEqual(myCipherBit0).getcipherBit(),plainResult);
  //cout << "0 >= 0 = " << plainResult.to_string() << endl;

  decryptor.decrypt(result.isGreaterOrEqual(myCipherBit1).getcipherBit(),plainResult);
  //cout << "0 >= 1 = " << plainResult.to_string() << endl;

  result = myCipherBit1;
  decryptor.decrypt(result.isGreaterOrEqual(myCipherBit0).getcipherBit(),plainResult);
  //cout << "1 >= 0 = " << plainResult.to_string() << endl;

  decryptor.decrypt(result.isGreaterOrEqual(myCipherBit1).getcipherBit(),plainResult);
  //cout << "1 >= 1 = " << plainResult.to_string() << endl;
}
void test_reverse(Evaluator evaluator, Decryptor decryptor,Encryptor encryptor){
  Plaintext myPlaintext1("1"); Plaintext plainResult("0");
  Ciphertext myCipher; encryptor.encrypt(myPlaintext1,myCipher);
  CipherBit cipherBit1(evaluator,encryptor, myCipher);
  cipherBit1.reverse();
  decryptor.decrypt(cipherBit1.getcipherBit(),plainResult);
  cout << "Reverse of 1 is " << plainResult.to_string() << endl;
  Plaintext myPlaintext0("0");
  encryptor.encrypt(myPlaintext0,myCipher);
  CipherBit cipherBit2(evaluator,encryptor, myCipher);
  cipherBit2.reverse();
  decryptor.decrypt(cipherBit2.getcipherBit(),plainResult);
  cout << "Reverse of 0 is " << plainResult.to_string() << endl;
}
void test_multiply1bit(Evaluator evaluator, Decryptor decryptor,Encryptor encryptor){
  cout << "Table de vérité du x sur 1 bit" << endl;
  Plaintext myPlaintext1("1");Plaintext myPlaintext0("0");
  Plaintext plainResult("0");
  Ciphertext myCipher1; encryptor.encrypt(myPlaintext1,myCipher1);
  Ciphertext myCipher0; encryptor.encrypt(myPlaintext0,myCipher0);
  CipherBit myCipherBit1(evaluator,encryptor, myCipher1);
  CipherBit myCipherBit0(evaluator,encryptor, myCipher0);

  //Tests
  CipherBit result = myCipherBit0;
  result.multiply(myCipherBit0);
  decryptor.decrypt(result.getcipherBit(),plainResult);
  cout << "0 x 0 = " << plainResult.to_string() << endl;

  result = myCipherBit0;
  result.multiply(myCipherBit1);
  decryptor.decrypt(result.getcipherBit(),plainResult);
  cout << "0 x 1 = " << plainResult.to_string() << endl;

  result = myCipherBit1;
  result.multiply(myCipherBit0);
  decryptor.decrypt(result.getcipherBit(),plainResult);
  cout << "1 x 0 = " << plainResult.to_string() << endl;

  result = myCipherBit1;
  result.multiply(myCipherBit1);
  decryptor.decrypt(result.getcipherBit(),plainResult);
  cout << "1 x 1 = " << plainResult.to_string() << endl;
}


//Test2Bits
void print2Bit(Decryptor decryptor,Cipher2Bit c2B){
  Plaintext plainResult("0");
  decryptor.decrypt(c2B.getCipherBit0().getcipherBit(),plainResult);
  cout << "bit0= " << plainResult.to_string();
  decryptor.decrypt(c2B.getCipherBit1().getcipherBit(),plainResult);
  cout << " bit1= " << plainResult.to_string() << endl;
}
void test_add2bit(Evaluator evaluator, Decryptor decryptor,Encryptor encryptor){
  cout<<"Test add 2 Bits"<<endl;
  Plaintext myPlaintext1("1");Plaintext myPlaintext0("0");
  Plaintext plainResult("0");
  Ciphertext myCipher1; encryptor.encrypt(myPlaintext1,myCipher1);
  Ciphertext myCipher0; encryptor.encrypt(myPlaintext0,myCipher0);
  CipherBit myCipherBit1(evaluator,encryptor, myCipher1);
  CipherBit myCipherBit0(evaluator,encryptor, myCipher0);

  //Tests
  
  Cipher2Bit trois(myCipherBit1,myCipherBit1);
  cout<<"on a un trois"<<endl;
  print2Bit(decryptor,trois);

  Ciphertext carry =trois.add(trois).getcipherBit();
  decryptor.decrypt(carry,plainResult);
  cout << "carry= " << plainResult.to_string() << endl;
  
  cout<<"apres addition avec 3"<<endl;
  print2Bit(decryptor,trois);
  cout << "Noise budget in carry after add: " << decryptor.invariant_noise_budget(carry) << " bits" << endl <<endl;
  cout << "Noise budget in bit0 after add: " << decryptor.invariant_noise_budget(trois.getCipherBit0().getcipherBit()) << " bits" << endl <<endl;
  cout << "Noise budget in bit1 after add: " << decryptor.invariant_noise_budget(trois.getCipherBit1().getcipherBit()) << " bits" << endl <<endl;
}
void test_XOR2bit(Evaluator evaluator, Decryptor decryptor,Encryptor encryptor){
  cout<<"Test xor 2 bit"<<endl;
  Plaintext myPlaintext1("1");Plaintext myPlaintext0("0");
  Plaintext plainResult("0");
  Ciphertext myCipher1; encryptor.encrypt(myPlaintext1,myCipher1);
  Ciphertext myCipher0; encryptor.encrypt(myPlaintext0,myCipher0);
  CipherBit myCipherBit1(evaluator,encryptor, myCipher1);
  CipherBit myCipherBit0(evaluator,encryptor, myCipher0);

  //Tests
  Cipher2Bit zero(myCipherBit0,myCipherBit0);
  Cipher2Bit un(myCipherBit1,myCipherBit0);
  Cipher2Bit deux(myCipherBit0,myCipherBit1);
  Cipher2Bit trois(myCipherBit1,myCipherBit1);
  Cipher2Bit result(myCipherBit1,myCipherBit1);

  cout<<"xor entre 0 et 0"<<endl;
  result=zero.copy();
  result.XOR(zero);
  cout<<"result= ";
  print2Bit(decryptor,result);

  cout<<"xor entre 0 et 1"<<endl;
  result=zero.copy();
  result.XOR(un);
  cout<<"result= ";
  print2Bit(decryptor,result);

  cout<<"xor entre 0 et 2"<<endl;
  result=zero.copy();
  result.XOR(deux);
  cout<<"result= ";
  print2Bit(decryptor,result);

  cout<<"xor entre 0 et 3"<<endl;
  result=zero.copy();
  result.XOR(trois);
  cout<<"result= ";
  print2Bit(decryptor,result);

  cout<<"xor entre 1 et 1"<<endl;
  result=un.copy();
  result.XOR(un);
  cout<<"result= ";
  print2Bit(decryptor,result);

  cout<<"xor entre 1 et 2"<<endl;
  result=un.copy();
  result.XOR(deux);
  cout<<"result= ";
  print2Bit(decryptor,result);


  //cout << "Noise budget in carry after add: " << decryptor.invariant_noise_budget(carry) << " bits" << endl <<endl;
  cout << "Noise budget in bit0 after add: " << decryptor.invariant_noise_budget(trois.getCipherBit0().getcipherBit()) << " bits" << endl <<endl;
  cout << "Noise budget in bit1 after add: " << decryptor.invariant_noise_budget(trois.getCipherBit1().getcipherBit()) << " bits" << endl <<endl;
}
void test_reverse2bit(Evaluator evaluator, Decryptor decryptor,Encryptor encryptor){
  cout<<"Test reverse"<<endl;
  Plaintext myPlaintext1("1");Plaintext myPlaintext0("0");
  Plaintext plainResult("0");
  Ciphertext myCipher1; encryptor.encrypt(myPlaintext1,myCipher1);
  Ciphertext myCipher0; encryptor.encrypt(myPlaintext0,myCipher0);
  CipherBit myCipherBit1(evaluator,encryptor, myCipher1);
  CipherBit myCipherBit0(evaluator,encryptor, myCipher0);

  //Tests
  
  Cipher2Bit trois(myCipherBit1,myCipherBit1);
  cout<<"on a un trois"<<endl;
  print2Bit(decryptor,trois);
  trois.reverse();
  cout<<"après le reverse"<<endl;
  cout<<"result= ";
  print2Bit(decryptor,trois);
}
void test_multiplyComposant2bit(Evaluator evaluator, Decryptor decryptor,Encryptor encryptor){
  cout<<"Test multiply composant"<<endl;
  Plaintext myPlaintext1("1");Plaintext myPlaintext0("0");
  Plaintext plainResult("0");
  Ciphertext myCipher1; encryptor.encrypt(myPlaintext1,myCipher1);
  Ciphertext myCipher0; encryptor.encrypt(myPlaintext0,myCipher0);
  CipherBit myCipherBit1(evaluator,encryptor, myCipher1);
  CipherBit myCipherBit0(evaluator,encryptor, myCipher0);

  //Tests
  Cipher2Bit zero(myCipherBit0,myCipherBit0);
  Cipher2Bit un(myCipherBit1,myCipherBit0);
  Cipher2Bit deux(myCipherBit0,myCipherBit1);
  Cipher2Bit trois(myCipherBit1,myCipherBit1);
  CipherBit result=myCipherBit0.copy();

  cout<<"test for 3"<<endl;
  decryptor.decrypt(trois.getCipherBit0().getcipherBit(),plainResult);
  cout << "bit0= " << plainResult.to_string();
  decryptor.decrypt(trois.getCipherBit1().getcipherBit(),plainResult);
  cout << " bit1= " << plainResult.to_string() << endl;
  
  result=trois.multiplyComposant();
  decryptor.decrypt(result.getcipherBit(),plainResult);
  cout << "multiply result of '3'= " << plainResult.to_string() << endl;

  cout<<"test for 2"<<endl;
  decryptor.decrypt(deux.getCipherBit0().getcipherBit(),plainResult);
  cout << "bit0= " << plainResult.to_string();
  decryptor.decrypt(deux.getCipherBit1().getcipherBit(),plainResult);
  cout << " bit1= " << plainResult.to_string() << endl;
  
  result=deux.multiplyComposant();
  decryptor.decrypt(result.getcipherBit(),plainResult);
  cout << "multiply result of '2'= " << plainResult.to_string() << endl;

  cout<<"test for 1"<<endl;
  decryptor.decrypt(un.getCipherBit0().getcipherBit(),plainResult);
  cout << "bit0= " << plainResult.to_string();
  decryptor.decrypt(un.getCipherBit1().getcipherBit(),plainResult);
  cout << " bit1= " << plainResult.to_string() << endl;

  result=un.multiplyComposant();
  decryptor.decrypt(result.getcipherBit(),plainResult);
  cout << "multiply result of '1'= " << plainResult.to_string() << endl;

  cout<<"test for 0"<<endl;
  decryptor.decrypt(zero.getCipherBit0().getcipherBit(),plainResult);
  cout << "bit0= " << plainResult.to_string();
  decryptor.decrypt(zero.getCipherBit1().getcipherBit(),plainResult);
  cout << " bit1= " << plainResult.to_string() << endl;
  
  result=zero.multiplyComposant();
  decryptor.decrypt(result.getcipherBit(),plainResult);
  cout << "multiply result of '0'= " << plainResult.to_string() << endl;
}
void test_isLesser2bit(Evaluator evaluator, Decryptor decryptor,Encryptor encryptor){
  cout<<"Test < 2 bit"<<endl;
  Plaintext myPlaintext1("1");Plaintext myPlaintext0("0");
  Plaintext plainResult("0");
  Ciphertext myCipher1; encryptor.encrypt(myPlaintext1,myCipher1);
  Ciphertext myCipher0; encryptor.encrypt(myPlaintext0,myCipher0);
  CipherBit myCipherBit1(evaluator,encryptor, myCipher1);
  CipherBit myCipherBit0(evaluator,encryptor, myCipher0);

  //Tests
  Cipher2Bit zero(myCipherBit0,myCipherBit0);
  Cipher2Bit un(myCipherBit1,myCipherBit0);
  Cipher2Bit deux(myCipherBit0,myCipherBit1);
  Cipher2Bit trois(myCipherBit1,myCipherBit1);
  CipherBit result(evaluator,encryptor,myCipher0);

  cout<<"0<0 "<<endl;
  result=zero.isLesser(zero);
  decryptor.decrypt(result.getcipherBit(),plainResult);
  cout << "result= " << plainResult.to_string() << endl;

  cout<<"0<1"<<endl;
  result=zero.isLesser(un);
  decryptor.decrypt(result.getcipherBit(),plainResult);
  cout << "result= " << plainResult.to_string() << endl;

  cout<<"0<2"<<endl;
  result=zero.isLesser(deux);
  decryptor.decrypt(result.getcipherBit(),plainResult);
  cout << "result= " << plainResult.to_string() << endl;

  cout<<"0<3"<<endl;
  result=zero.isLesser(trois);
  decryptor.decrypt(result.getcipherBit(),plainResult);
  cout << "result= " << plainResult.to_string() << endl;

  cout<<"1<0"<<endl;
  result=un.isLesser(zero);
  decryptor.decrypt(result.getcipherBit(),plainResult);
  cout << "result= " << plainResult.to_string() << endl;

  cout<<"1<1"<<endl;
  result=un.isLesser(un);
  decryptor.decrypt(result.getcipherBit(),plainResult);
  cout << "result= " << plainResult.to_string() << endl;

  cout<<"1<2"<<endl;
  result=un.isLesser(deux);
  decryptor.decrypt(result.getcipherBit(),plainResult);
  cout << "result= " << plainResult.to_string() << endl;

  cout<<"3<2"<<endl;
  result=trois.isLesser(deux);
  decryptor.decrypt(result.getcipherBit(),plainResult);
  cout << "result= " << plainResult.to_string() << endl;

  cout<<"2<3"<<endl;
  result=deux.isLesser(trois);
  decryptor.decrypt(result.getcipherBit(),plainResult);
  cout << "result= " << plainResult.to_string() << endl;
}
void test_isGreaterOrEqual2bit(Evaluator evaluator, Decryptor decryptor,Encryptor encryptor){
  cout<<"Test >= 2 bit"<<endl;
  Plaintext myPlaintext1("1");Plaintext myPlaintext0("0");
  Plaintext plainResult("0");
  Ciphertext myCipher1; encryptor.encrypt(myPlaintext1,myCipher1);
  Ciphertext myCipher0; encryptor.encrypt(myPlaintext0,myCipher0);
  CipherBit myCipherBit1(evaluator,encryptor, myCipher1);
  CipherBit myCipherBit0(evaluator,encryptor, myCipher0);

  //Tests
  Cipher2Bit zero(myCipherBit0,myCipherBit0);
  Cipher2Bit un(myCipherBit1,myCipherBit0);
  Cipher2Bit deux(myCipherBit0,myCipherBit1);
  Cipher2Bit trois(myCipherBit1,myCipherBit1);
  CipherBit result(evaluator,encryptor,myCipher0);

  cout<<"0>=0 "<<endl;
  result=zero.isGreaterOrEqual(zero);
  decryptor.decrypt(result.getcipherBit(),plainResult);
  cout << "result= " << plainResult.to_string() << endl;

  cout<<"0>=1"<<endl;
  result=zero.isGreaterOrEqual(un);
  decryptor.decrypt(result.getcipherBit(),plainResult);
  cout << "result= " << plainResult.to_string() << endl;

  cout<<"0>=2"<<endl;
  result=zero.isGreaterOrEqual(deux);
  decryptor.decrypt(result.getcipherBit(),plainResult);
  cout << "result= " << plainResult.to_string() << endl;

  cout<<"0>=3"<<endl;
  result=zero.isGreaterOrEqual(trois);
  decryptor.decrypt(result.getcipherBit(),plainResult);
  cout << "result= " << plainResult.to_string() << endl;

  cout<<"1>=0"<<endl;
  result=un.isGreaterOrEqual(zero);
  decryptor.decrypt(result.getcipherBit(),plainResult);
  cout << "result= " << plainResult.to_string() << endl;

  cout<<"1>=1"<<endl;
  result=un.isGreaterOrEqual(un);
  decryptor.decrypt(result.getcipherBit(),plainResult);
  cout << "result= " << plainResult.to_string() << endl;

  cout<<"1>=2"<<endl;
  result=un.isGreaterOrEqual(deux);
  decryptor.decrypt(result.getcipherBit(),plainResult);
  cout << "result= " << plainResult.to_string() << endl;

  cout<<"3>=2"<<endl;
  result=trois.isGreaterOrEqual(deux);
  decryptor.decrypt(result.getcipherBit(),plainResult);
  cout << "result= " << plainResult.to_string() << endl;

  cout<<"2>=3"<<endl;
  result=deux.isGreaterOrEqual(trois);
  decryptor.decrypt(result.getcipherBit(),plainResult);
  cout << "result= " << plainResult.to_string() << endl;
}
void test_multiply2bit(Evaluator evaluator, Decryptor decryptor,Encryptor encryptor){
  cout<<"Test < 2 bit"<<endl;
  Plaintext myPlaintext1("1");Plaintext myPlaintext0("0");
  Plaintext plainResult("0");
  Ciphertext myCipher1; encryptor.encrypt(myPlaintext1,myCipher1);
  Ciphertext myCipher0; encryptor.encrypt(myPlaintext0,myCipher0);
  CipherBit myCipherBit1(evaluator,encryptor, myCipher1);
  CipherBit myCipherBit0(evaluator,encryptor, myCipher0);

  //Tests
  Cipher2Bit zero(myCipherBit0,myCipherBit0);
  Cipher2Bit un(myCipherBit1,myCipherBit0);
  Cipher2Bit deux(myCipherBit0,myCipherBit1);
  Cipher2Bit trois(myCipherBit1,myCipherBit1);
  Cipher2Bit carry=zero.copy();
  Cipher2Bit result=zero.copy();

  cout<<"0x0 "<<endl;
  result=zero.copy();
  carry=result.multiply(zero);
  cout<<"result = ";
  print2Bit(decryptor,result);
  cout<<"carry  = ";
  print2Bit(decryptor,carry);
 
  cout<<"0x1"<<endl;
  result=zero.copy();
  carry=result.multiply(un);
  cout<<"result = ";
  print2Bit(decryptor,result);
  cout<<"carry  = ";
  print2Bit(decryptor,carry);

  cout<<"0x2"<<endl;
  result=zero.copy();
  carry=result.multiply(deux);
  cout<<"result = ";
  print2Bit(decryptor,result);
  cout<<"carry  = ";
  print2Bit(decryptor,carry);

  cout<<"0x3"<<endl;
  result=zero.copy();
  carry=result.multiply(trois);
  cout<<"result = ";
  print2Bit(decryptor,result);
  cout<<"carry  = ";
  print2Bit(decryptor,carry);

  cout<<endl;

  cout<<"1x1"<<endl;
  result=un.copy();
  carry=result.multiply(un);
  cout<<"result = ";
  print2Bit(decryptor,result);
  cout<<"carry  = ";
  print2Bit(decryptor,carry);

  cout<<"1x2"<<endl;
  result=un.copy();
  carry=result.multiply(deux);
  cout<<"result = ";
  print2Bit(decryptor,result);
  cout<<"carry  = ";
  print2Bit(decryptor,carry);

  cout<<"1x3"<<endl;
  result=un.copy();
  carry=result.multiply(trois);
  cout<<"result = ";
  print2Bit(decryptor,result);
  cout<<"carry  = ";
  print2Bit(decryptor,carry);

  cout<<endl;

  cout<<"2x2"<<endl;
  result=deux.copy();
  carry=result.multiply(deux);
  cout<<"result = ";
  print2Bit(decryptor,result);
  cout<<"carry  = ";
  print2Bit(decryptor,carry);

  cout<<"2x3"<<endl;
  result=deux.copy();
  carry=result.multiply(trois);
  cout<<"result = ";
  print2Bit(decryptor,result);
  cout<<"carry  = ";
  print2Bit(decryptor,carry);

  cout<<endl;

  cout<<"3x3"<<endl;
  result=trois.copy();
  carry=result.multiply(trois);
  cout<<"result = ";
  print2Bit(decryptor,result);
  cout<<"carry  = ";
  print2Bit(decryptor,carry);
}

//Test4Bits
void test_4Bit(Evaluator evaluator, Decryptor decryptor,Encryptor encryptor){
  cout<<"Test < 2 bit"<<endl;
  Plaintext myPlaintext1("1");Plaintext myPlaintext0("0");
  Plaintext plainResult("0");
  Ciphertext myCipher1; encryptor.encrypt(myPlaintext1,myCipher1);
  Ciphertext myCipher0; encryptor.encrypt(myPlaintext0,myCipher0);
  CipherBit myCipherBit1(evaluator,encryptor, myCipher1);
  CipherBit myCipherBit0(evaluator,encryptor, myCipher0);

  //Tests
  Cipher2Bit zero(myCipherBit0,myCipherBit0);
  Cipher2Bit un(myCipherBit1,myCipherBit0);
  Cipher2Bit deux(myCipherBit0,myCipherBit1);
  Cipher2Bit trois(myCipherBit1,myCipherBit1);

  Cipher4Bit myZero(deux,zero);
  print2Bit(decryptor,myZero.getPartieZero());
  print2Bit(decryptor,myZero.getPartieUne());

}

int main(){
  //Configuration des paramètres homomorphiques
    EncryptionParameters parms;
    parms.set_poly_modulus("1x^8192 + 1");
    parms.set_coeff_modulus(coeff_modulus_128(8192));
    parms.set_plain_modulus(1<<2);
  //Validation des paramètres et création du contexte
    SEALContext context(parms);
  //Generation des clées publiques et privées
    KeyGenerator keygen(context);
    PublicKey public_key = keygen.public_key();
    SecretKey secret_key = keygen.secret_key();
    //GaloisKeys gal_keys;
    //keygen.generate_galois_keys(30, gal_keys);
    EvaluationKeys ev_keys;
    keygen.generate_evaluation_keys(30, ev_keys);
  //Homomorphic Objects
    Encryptor encryptor(context, public_key);
    Evaluator evaluator(context);
    Decryptor decryptor(context, secret_key);

  //Test with function
  //test_xor1bit(evaluator,decryptor,encryptor);
  //test_add1bit(evaluator,decryptor,encryptor);
  //test_reverse(evaluator,decryptor,encryptor);
  //test_isGreaterOrEqual1bit(evaluator,decryptor,encryptor);
  //test_isLesser1bit(evaluator,decryptor,encryptor);
  //test_multiply1bit(evaluator,decryptor,encryptor);

  //test_add2bit(evaluator,decryptor,encryptor);
  //test_XOR2bit(evaluator,decryptor,encryptor);
  //test_reverse2bit(evaluator,decryptor,encryptor);
  //test_multiplyComposant2bit(evaluator,decryptor,encryptor);
  //test_isLesser2bit(evaluator,decryptor,encryptor);
  //test_isGreaterOrEqual2bit(evaluator,decryptor,encryptor);
  //test_multiply2bit(evaluator,decryptor,encryptor);

  test_4Bit(evaluator,decryptor,encryptor);

  return 0;
}
