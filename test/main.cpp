#include <vector>
#include <seal/seal.h>
#include <../Structures/CipherBit.h>

using namespace std;
using namespace seal;

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
int main(){
  //Configuration des paramètres homomorphiques
    EncryptionParameters parms;
    parms.set_poly_modulus("1x^4096 + 1");
    parms.set_coeff_modulus(coeff_modulus_128(4096));
    parms.set_plain_modulus(40961);
  //Validation des paramètres et création du contexte
    SEALContext context(parms);
  //Generation des clées publiques et privées
    KeyGenerator keygen(context);
    PublicKey public_key = keygen.public_key();
    SecretKey secret_key = keygen.secret_key();
    GaloisKeys gal_keys;
    keygen.generate_galois_keys(30, gal_keys);
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

  //Noise Tests
    Plaintext one("1"); Plaintext zero("0");Plaintext plainResult;
    cout << "Plaintext : " << one.to_string() << " , " << zero.to_string() << endl;
    Ciphertext cipherOne; encryptor.encrypt(one,cipherOne);
    Ciphertext cipherZero; encryptor.encrypt(zero,cipherZero);
    cout << "Ciphertext created" << endl ;
    cout << "Noise budget in cipherOne: " << decryptor.invariant_noise_budget(cipherOne) << " bits" << endl;
    cout << "Noise budget in cipherZero: " << decryptor.invariant_noise_budget(cipherZero) << " bits" << endl <<endl;

    CipherBit cipherBitOne(evaluator,encryptor,decryptor,cipherOne);
    CipherBit cipherBitZero(evaluator,encryptor,decryptor,cipherZero);
    cout << "CipherBit created" <<endl;
    cout << "Noise budget in cipherBitOne: " << decryptor.invariant_noise_budget(cipherBitOne.getcipherBit()) << " bits" << endl;
    cout << "Noise budget in cipherBitZero: " << decryptor.invariant_noise_budget(cipherBitZero.getcipherBit()) << " bits" << endl <<endl;

    cout<< "0 XOR 1 = 1 " << endl;
    cout << "Noise budget in cipherBitZero: " << decryptor.invariant_noise_budget(cipherBitZero.getcipherBit()) << " bits" << endl;
    cipherBitZero.XOR(cipherBitOne);
    cout << "Noise budget in cipherBitZero afer XOR : " << decryptor.invariant_noise_budget(cipherBitZero.getcipherBit()) << " bits" << endl <<endl;
    cout<< "0 XOR 0 = 0 (avec lui même)" << endl;
    cout << "Noise budget in cipherBitZero: " << decryptor.invariant_noise_budget(cipherBitZero.getcipherBit()) << " bits" << endl ;
    cipherBitOne = cipherBitZero;

    cipherBitZero.XOR(cipherBitZero);
    cout << "Noise budget in cipherBitZero after XOR : " << decryptor.invariant_noise_budget(cipherBitZero.getcipherBit()) << " bits" << endl <<endl;

    cout << "Addition d'une copie de sa version bruitée" << endl;
    cout << "Noise budget in cipherBitZero: " << decryptor.invariant_noise_budget(cipherBitZero.getcipherBit()) << " bits" << endl;
    decryptor.decrypt(cipherBitZero.getcipherBit(),plainResult);

    cipherBitZero.add(cipherBitOne);
    cout << "Noise budget in cipherBitZero after add: " << decryptor.invariant_noise_budget(cipherBitZero.getcipherBit()) << " bits" << endl <<endl;
    //cout << "Noise budget in cipherBitOne after XOR: " << decryptor.invariant_noise_budget(cipherBitOne.getcipherBit()) << " bits" << endl;
    //cout << "Noise budget in cipherBitZero after XOR: " << decryptor.invariant_noise_budget(cipherBitZero.getcipherBit()) << " bits" << endl;

    cipherBitZero.reduceNoise();
    cout << "Noise budget in cipherBitZero after reducing: " << decryptor.invariant_noise_budget(cipherBitZero.getcipherBit()) << " bits" << endl <<endl;

    //decryptor.decrypt(cipherBitZero.getcipherBit(),plainResult);
    //cout << "Print result : " << plainResult.to_string() << endl;

  return 0;
}
