#include <seal/seal.h>
#include <vector>

using namespace std;
using namespace seal;

/*
Printing the matrix is a bit of a pain.
*/
void print_matrix (const vector<uint64_t> &matrix, PolyCRTBuilder crtbuilder)
{
    cout << endl;

    /*
    We're not going to print every column of the matrix (there are 2048). Instead
    print this many slots from beginning and end of the matrix.
    */
    int print_size = 5;
    int row_size = crtbuilder.slot_count()/2;

    cout << "    [";
    for (int i = 0; i < print_size; i++)
    {
        cout << matrix[i] << ",";
    }
    cout << " ...,";
    for (int i = row_size - print_size; i < row_size; i++)
    {
        cout << matrix[i] << ((i != row_size - 1) ? "," : " ]\n");
    }
    cout << "    [";
    for (int i = row_size; i < row_size + print_size; i++)
    {
        cout << matrix[i] << ",";
    }
    cout << " ...,";
    for (int i = 2 * row_size - print_size; i < 2 * row_size; i++)
    {
        cout << matrix[i] << ((i != 2 * row_size - 1) ? "," : " ]\n");
    }
    cout << endl;
};
/*
  In : two Ciphertext witch represent one bit each
       the evaluator object to do operations
  Out : EncryptedTrue if a <b
        EncryptedFalse if a>=b
*/
Ciphertext homo_two_bit_comparator(Ciphertext a, Ciphertext b, Evaluator evaluator, Decryptor decryptor, IntegerEncoder encoder){

  Ciphertext c = b;
  Plaintext tmp;

  cout << "FONCTION a<b" << endl;
  //Compute c
  cout << "Compute c" << endl;
  decryptor.decrypt(c, tmp);cout << "b = " << tmp.to_string() << endl;
  decryptor.decrypt(a, tmp);cout << "a = " << tmp.to_string() << endl;
  evaluator.add_plain(a,Plaintext(encoder.encode(1)));
  decryptor.decrypt(a, tmp);cout << "a + 1 = " << tmp.to_string() << endl;
  evaluator.multiply(c,a);
  decryptor.decrypt(c, tmp);cout << "c = (a+1)*b = " << tmp.to_string() << endl;

  //Compute d
  cout << "Compute d" << endl;
  Ciphertext d = b ;
  decryptor.decrypt(b, tmp);cout << "b = " << tmp.to_string() << endl;
  evaluator.negate(a);
  decryptor.decrypt(a, tmp);cout << "-(a+1) = " << tmp.to_string() << endl;
  evaluator.add(d,a);
  decryptor.decrypt(d, tmp);cout << "d = b-(a+1) =" << tmp.to_string() << endl;

  //compute result
  cout << "Compute result" << endl;
  Ciphertext result = c;
  evaluator.add_plain(d,Plaintext(encoder.encode(1)));
  evaluator.multiply(result,d);

  return result;
}

Ciphertext XOR(Ciphertext a, Ciphertext b, Evaluator evaluator, Decryptor decryptor){
  Ciphertext result = a;
  Plaintext tmp;
  //  decryptor.decrypt(b, tmp);cout << "b = " << tmp.to_string() << endl;
  //  decryptor.decrypt(a, tmp);cout << "a = " << tmp.to_string() << endl;
  evaluator.negate(b);
  //  decryptor.decrypt(b, tmp);cout << "-b = " << tmp.to_string() << endl;
  evaluator.add(result,b);
  //  decryptor.decrypt(result, tmp);cout << "a-b = " << tmp.to_string() << endl;
  evaluator.square(result);
  //  decryptor.decrypt(result, tmp);cout << "(a-b)^2 = " << tmp.to_string() << endl;
  return result;
}

Ciphertext XOR_2(Ciphertext a, Ciphertext b, Evaluator evaluator, Decryptor decryptor, IntegerEncoder encoder,PolyCRTBuilder crtbuilder){
  Ciphertext result = a;
  Plaintext tmp;
  //Create vector
  cout << "slot count : " << crtbuilder.slot_count() << endl;
  vector<uint64_t> first_bit(crtbuilder.slot_count(),0);
  first_bit[0]=1;
  vector<uint64_t> second_bit(crtbuilder.slot_count(),0);
  second_bit[1]=1;
  //cout << "Vecteur 1 : " << first_bit << endl;
  //cout << "Vecteur 2 : " << second_bit << endl;
  print_matrix(first_bit, crtbuilder);
  //Encode vector
  Plaintext bit_one;
  crtbuilder.compose(first_bit,bit_one);
  //Plaintext bit_two; crtbuilder.compose(second_bit,bit_two);
  return result;
}

void test_XOR(Evaluator evaluator, Decryptor decryptor, IntegerEncoder encoder, Encryptor encryptor){
  cout << "Table de vérité du XOR" << endl;
  Plaintext one(encoder.encode(1));
  Ciphertext one_;
  encryptor.encrypt(one,one_);
  Plaintext zero(encoder.encode(0));
  Ciphertext zero_;
  encryptor.encrypt(zero,zero_);
  //Try XOR on one bit
  Ciphertext boolonesupzero;
  Plaintext plainTrue;
  boolonesupzero = XOR(one_,zero_,evaluator,decryptor);
  decryptor.decrypt(boolonesupzero,plainTrue);
  cout << "1 + 0 :" << plainTrue.to_string() <<endl;

  Ciphertext boolzerosupone;
  Plaintext plainFalse;
  boolzerosupone = XOR(zero_,one_,evaluator,decryptor);
  decryptor.decrypt(boolzerosupone,plainFalse);
  cout << "0 + 1 :" << plainFalse.to_string() <<endl;

  boolzerosupone = XOR(one_,one_,evaluator,decryptor);
  decryptor.decrypt(boolzerosupone,plainFalse);
  cout << "1 + 1 :" << plainFalse.to_string() <<endl;

  boolzerosupone = XOR(zero_,zero_,evaluator,decryptor);
  decryptor.decrypt(boolzerosupone,plainFalse);
  cout << "0 + 0 :" << plainFalse.to_string() <<endl;
}

void test_XOR2(Evaluator evaluator, Decryptor decryptor, IntegerEncoder encoder, Encryptor encryptor,PolyCRTBuilder crtbuilder){
  Plaintext two = encoder.encode(2);
  Plaintext three = encoder.encode(3);
  Ciphertext two_cipher;
  Ciphertext three_cipher;
  encryptor.encrypt(two,two_cipher);
  encryptor.encrypt(three,three_cipher);
  XOR_2(two_cipher,three_cipher,evaluator,decryptor,encoder,crtbuilder);
}

void test_comparator(Evaluator evaluator, Decryptor decryptor, IntegerEncoder encoder,Encryptor encryptor){
  Plaintext one(encoder.encode(1));
  Ciphertext one_;
  encryptor.encrypt(one,one_);
  Plaintext zero(encoder.encode(0));
  Ciphertext zero_;
  encryptor.encrypt(zero,zero_);
  //Try comparator on one bits
  Ciphertext boolonesupzero;
  Plaintext plainTrue;
  boolonesupzero = homo_two_bit_comparator(one_,zero_,evaluator,decryptor,encoder);
  decryptor.decrypt(boolonesupzero,plainTrue);
  cout << "True:" << plainTrue.to_string() <<endl;

  Ciphertext boolzerosupone;
  Plaintext plainFalse;
  boolzerosupone = homo_two_bit_comparator(zero_,one_,evaluator,decryptor,encoder);
  decryptor.decrypt(boolzerosupone,plainFalse);
  cout << "False:" << plainFalse.to_string() <<endl;

  boolzerosupone = homo_two_bit_comparator(one_,one_,evaluator,decryptor,encoder);
  decryptor.decrypt(boolzerosupone,plainFalse);
  cout << "False:" << plainFalse.to_string() <<endl;

  boolzerosupone = homo_two_bit_comparator(zero_,zero_,evaluator,decryptor,encoder);
  decryptor.decrypt(boolzerosupone,plainFalse);
  cout << "False:" << plainFalse.to_string() <<endl;
}

int main()
{
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
  IntegerEncoder encoder(context.plain_modulus());
  PolyCRTBuilder crtbuilder(context);
//Activate Btching
  auto qualifiers = context.qualifiers();
  cout << "Batching enabled: " << boolalpha << qualifiers.enable_batching << endl;
//Encryption
  Plaintext a(encoder.encode(2));
  Ciphertext a_;
  encryptor.encrypt(a,a_);
  Plaintext b(encoder.encode(3));
  Ciphertext b_;
  encryptor.encrypt(b,b_);

// Extract encryption parameters and print them.
  int coeff_count = parms.poly_modulus().coeff_count();
  int coeff_mod_count = parms.coeff_modulus().size();
  int encrypted_size = a_.size();

//  cout << coeff_count << endl;
//  cout << coeff_mod_count << endl;
//  cout << encrypted_size << endl;

//Test comparator
  //test_comparator(evaluator,decryptor,encoder,encryptor);

//Test test_XOR
  //test_XOR(evaluator,decryptor,encoder,encryptor);
  test_XOR2(evaluator,decryptor,encoder,encryptor,crtbuilder);
  //decryptor.decrypt(XOR(a_,b_),tpm) ;

  //cout << a << " XOR " << b << encoder.decode_int32(tpm) << endl;
}
