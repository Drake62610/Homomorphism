#include <vector>
#include <seal/seal.h>
#include <../Structures/CipherBit.h>
#include <../Structures/Cipher2Bit.h>
#include <../Structures/Cipher3Bit.h>

using namespace std;
using namespace seal;

int main(){
  //Configuration des paramètres homomorphiques
    EncryptionParameters parms;
    parms.set_poly_modulus("1x^16384 + 1");
    parms.set_coeff_modulus(coeff_modulus_128(16384));
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

  Plaintext myplain0("0");	Ciphertext myCipher0;	encryptor.encrypt(myplain0,myCipher0);
  CipherBit faux(evaluator,encryptor,decryptor,myCipher0);
  Plaintext myplain1("1");	Ciphertext myCipher1;	encryptor.encrypt(myplain1,myCipher1);
  CipherBit vrai(evaluator,encryptor,decryptor,myCipher1);
  Cipher2Bit deux2(faux,vrai);
  Cipher2Bit trois2(vrai,vrai);
  Cipher3Bit deux(deux2,faux);
  Cipher3Bit trois(trois2,faux);
  CipherBit result=faux.copy();
  CipherBit tmp=faux.copy();

  cout<<"Début des if"<<endl;
  //egal à 2?
  Cipher3Bit tmp3B(deux2.copy(),vrai.copy());
  cout<<"1"<<endl;
  tmp3B.XOR(deux);
}
