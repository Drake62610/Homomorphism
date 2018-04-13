#include <vector>
#include <seal/seal.h>
#include <../Structures/CipherEncrypt.h>

using namespace std;
using namespace seal;

void print2Bit(Decryptor decryptor,Cipher2Bit c2B){
  Plaintext plainResult("0");
  decryptor.decrypt(c2B.getCipherBit0().getcipherBit(),plainResult);
  cout << "bit0= " << plainResult.to_string();
  decryptor.decrypt(c2B.getCipherBit1().getcipherBit(),plainResult);
  cout << "bit1= " << plainResult.to_string() << endl;
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
    EvaluationKeys ev_keys;
    keygen.generate_evaluation_keys(30, ev_keys);
  //Homomorphic Objects
    Encryptor encryptor(context, public_key);
    Evaluator evaluator(context);
    Decryptor decryptor(context, secret_key);

  //Test
  CipherEncrypt myEncryptor = CipherEncrypt(evaluator,encryptor);
  print2Bit(decryptor, myEncryptor.encodeInt2bit(2));
}
