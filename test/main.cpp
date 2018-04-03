#include <vector>
#include <seal/seal.h>
#include <../Structures/CipherBit.h>

using namespace std;
using namespace seal;

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

  //Test
  Plaintext myPlaintext("1");
  Ciphertext myCipher; encryptor.encrypt(myPlaintext,myCipher);
  CipherBit myFirstBit(evaluator, myCipher);
  myFirstBit.XOR(myFirstBit);
  decryptor.decrypt(myFirstBit.getcipherBit(),myPlaintext);
  cout << myPlaintext.to_string() <<endl;
  return 0;
}
