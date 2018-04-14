#ifndef DEFCIPHERBIT
#define DEFCIPHERBIT

#include <string>
#include <vector>
#include <seal/seal.h>

class CipherBit{
public:
  //Constructor
  /*
    Empty constructor wich will be called by the other classes
  */
  CipherBit();
  /*
    Input : evaluator and encryptor from the seal context, needed to use public key and do seal Operations
            Ciphertext to stock in this CipherBit
    Noise : no noise are consumed in this constructor
  */
  CipherBit(seal::Evaluator &evaluator,seal::Encryptor &encryptor, seal::Ciphertext);
  CipherBit(seal::Evaluator & eva, seal::Encryptor &enc, seal::Decryptor &dec, seal::Ciphertext a);
  //Getter
  seal::Ciphertext getcipherBit();
  seal::Evaluator* getEvaluator();
  seal::Encryptor* getEncryptor();
  //Setter
  void setcipherBit(seal::Ciphertext a);

  //Methods
  /*
    A methods that will display at each stage of the XOR the noise, useful for debug
  */
  void XORdebug(CipherBit b, seal::Decryptor decryptor, seal::EvaluationKeys ev_keys);
  /*
    Input : b is the Cipherbit to XOR to this->cipherBit
    this->cipherBit will be override by the result
    XOR will be comuted by (a-b)^2
  */
  void XOR(CipherBit b);
  /*
    Input : b is the Cipherbit to add to this->cipherBit
    Output : The carry as a Cipherbit
    this->cipherBit will be override by the result
  */
  CipherBit add(CipherBit b);
  /*
    Output : The not gate computed using 1- (this -> CipherBit)
  */
  void reverse();
  /*
    Output : A CipherBit wich is a copy of "this".
  */
  CipherBit copy();
  /*
    Input : the CipherBit to compare using the "<" operation
    Output : A Cipherbit containing an encrypted
    "1" if True or "0" if false
  */
  CipherBit isLesser(CipherBit b);
  /*
    Input : the CipherBit to compare using the ">=" operation
    Output : A Cipherbit containing an encrypted
    "1" if True or "0" if false
  */
  CipherBit isGreaterOrEqual(CipherBit b);
  /*
    Input : b is the Cipherbit to multiply to this->cipherBit
    this->cipherBit will be override by the result
  */
  void multiply(CipherBit b);
  /*
    Will reset the noise budget, should be replaced by batching
  */
  void reduceNoise();


private:
  seal::Ciphertext cipherBit; //A cipherbit is composed by one Ciphertext wich will either be the polynomial "0" or "1"
  seal::Evaluator* evaluator; //Use an adress to avoid calling a constructor (witch won't exist)
  seal::Encryptor* encryptor; //Same here
  seal::Decryptor* decryptor;
};
#endif
