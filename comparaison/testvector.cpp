#include <seal/seal.h>


using namespace std;
using namespace seal;
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



int main()
{
  //EncryptionParameters
  EncryptionParameters parms;
  parms.set_poly_modulus("1x^4096 + 1");
  parms.set_coeff_modulus(coeff_modulus_128(4096));
  parms.set_plain_modulus(40961);
  SEALContext context(parms);
  //Check if batching is enabled
  auto qualifiers = context.qualifiers();
  cout << "Batching enabled: " << boolalpha << qualifiers.enable_batching << endl;
  //Generate Keys
  KeyGenerator keygen(context);
  auto public_key = keygen.public_key();
  auto secret_key = keygen.secret_key();
  GaloisKeys gal_keys;  keygen.generate_galois_keys(30, gal_keys);
  EvaluationKeys ev_keys;  keygen.generate_evaluation_keys(30, ev_keys);
  //Create Homomorphic objects
  Encryptor encryptor(context, public_key);
  Evaluator evaluator(context);
  Decryptor decryptor(context, secret_key);
  PolyCRTBuilder crtbuilder(context);
  //Row size
  int slot_count = crtbuilder.slot_count();
  int row_size = slot_count / 2;
  cout << "Plaintext matrix row size: " << row_size << endl;
  //Encore 2 and three in a matrix
  vector<uint64_t> matrix_two(slot_count, 0); matrix_two[1]=1;
  Plaintext two; crtbuilder.compose(matrix_two, two);
  //Plaintext three = encoder.encode(3);
  Ciphertext two_cipher;
  Ciphertext three_cipher;
  encryptor.encrypt(two,two_cipher);
  //encryptor.encrypt(three,three_cipher);

  //Create vector to project
  vector<uint64_t> pod_matrix(slot_count, 0);
  pod_matrix[0] = 1;

  Plaintext plain_matrix;
  crtbuilder.compose(pod_matrix, plain_matrix);

  //multiplication
  evaluator.multiply_plain(two_cipher,plain_matrix);
  decryptor.decrypt(two_cipher,two);
  crtbuilder.decompose(two,matrix_two);

  cout << "Result : " <<  endl;
  print_matrix(matrix_two, crtbuilder);

}
