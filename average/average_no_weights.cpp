#include <seal/seal.h>
#include <vector>

using namespace std;
using namespace seal;

int main()
{
cout << "////////////////////CLIENT////////////////////" << endl;
//Get list of integer from client
vector<double> rational_numbers ;
cout << "Please enter some double (q to end):\n";
double mydouble;
do {
    std::cin >> mydouble;
    if (mydouble != 0) {
      rational_numbers.push_back(mydouble);
    }
  } while (mydouble);
cout << "vector of double : ";
for (int i = 0; i < rational_numbers.size(); i++) {
  cout << rational_numbers[i] << " ";
}
cout << endl;

//Configuration des paramètres homomorphiques
  EncryptionParameters parms;
  parms.set_poly_modulus("1x^8192 + 1");
  parms.set_coeff_modulus(coeff_modulus_128(8192));
  parms.set_plain_modulus(65537);

  //Validation des paramètres et création du contexte
  SEALContext context(parms);

  //Utilisation d'un encoder pour fraction
  BalancedFractionalEncoder encoder(parms.
  plain_modulus(), parms.poly_modulus(),
  256, 64);
  cout << "Encryption parameters set ...... DONE" << endl;

//Generation des clées publiques et privées
  KeyGenerator keygen(context);
  PublicKey public_key = keygen.public_key();
  SecretKey secret_key = keygen.secret_key();
  cout << "Public and Private key generated ...... DONE" << endl;

//Création de l'objet Encryptor, Evaluator et Decryptor
  Encryptor encryptor(context, public_key); //On a besoinde la clée publique pour l'encryption
  Evaluator evaluator(context); //Objet permettant de faire diverses opérations
  Decryptor decryptor(context, secret_key); //On decrypte avec la clée privée

//Encryption du vecteur
  vector<Ciphertext> numbers;
  for (int i = 0; i < rational_numbers.size(); i++)
  {
    numbers.emplace_back(parms);
    encryptor.encrypt(encoder.encode(rational_numbers[i]), numbers[i]);
  }
  cout << "Encryption and cipher of numbers ...... DONE" << endl;
  cout << "Sending numbers and weights vector to the server ...... DONE." << endl;
  cout << endl;
//Le server recevra donc deux vecteurs, un encrypté (donnée sensibles) et un encodé (donnée insensible)

cout << "////////////////////SERVER////////////////////" << endl;
// On multiplie les nombres avec les poids dans un Ciphertext result
  Ciphertext result = numbers[0];
  for (int i = 1; i<rational_numbers.size(); ++i)  {
    Ciphertext prod = numbers[i];//On multiplie nombre et poids
    evaluator.add(result, prod); // On l'ajoute au résultat
  }
  cout <<"multiplication of the two vector ...... DONE." << endl;
  cout <<"addition of the resulting vector ...... DONE." << endl;

// Maintenant on divise par le nombre de produit
  double inv = 1/(double)rational_numbers.size();
  evaluator.multiply_plain(result,encoder.encode(inv));
  cout <<"division to obtain the average ...... DONE." << endl;
  cout <<"sending result to client ...... DONE." << endl;
//Le serveur peux renvoyer result
  cout << endl;

cout <<"////////////////////CLIENT////////////////////" << endl;
  Plaintext plain_result;
  decryptor.decrypt(result,plain_result);
  cout << "Decoding using private key" << endl;
  cout << "Result: " << encoder.decode(plain_result) << endl;

//On vérifie le résultat
  double clearRes = 0;
  for (int i = 0; i < rational_numbers.size(); i++) {
    clearRes += rational_numbers[i];
  }
  clearRes = clearRes /(double)rational_numbers.size();
  cout << "Plain Result without Homomorphic : " << clearRes << endl;
  return 0;
}
