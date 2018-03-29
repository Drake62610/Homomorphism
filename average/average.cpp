#include <seal/seal.h>
#include <vector>

using namespace std;
using namespace seal;



int main()
{
//Configuration des paramètre homomorphiques
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

//Generation des clées publiques et privées
  KeyGenerator keygen(context);
  PublicKey public_key = keygen.public_key();
  SecretKey secret_key = keygen.secret_key();

//Création de l'objet Encryptor, Evaluator et Decryptor
  Encryptor encryptor(context, public_key); //On a besoinde la clée publique pour l'encryption
  Evaluator evaluator(context); //Objet permettant de faire diverses opérations
  Decryptor decryptor(context, secret_key); //On decrypte avec la clée privée

  const vector<double> rational_numbers {
      6.12,1.10,8.43,9.30,7.05
  };
  vector<Ciphertext> numbers;
  for (int i = 0; i < rational_numbers.size(); i++)
  {
    numbers.emplace_back(parms);
    encryptor.encrypt(encoder.encode(rational_numbers[i]), numbers[i]);
  }
  cout << "Encryption de numbers réussie" << endl;

  //Les poids sont en clairs
  const vector<double> coefficients {
      0.20,0.20,0.35,0.15,0.20
  };
  vector<Plaintext> weights;
  for (int i = 0; i < rational_numbers.size(); i++)
  {
      weights.emplace_back(encoder.encode(coefficients[i]));
  }

  cout << "Encryption des poids réussie" << endl;

// On multiplie les nombres avec les poids dans un Ciphertext result
  Ciphertext result = numbers[0];
  evaluator.multiply_plain(result, weights[0]);
  for (int i = 1; i<5; ++i)  {
    Ciphertext prod = numbers[i];//On multiplie nombre et poids
    evaluator.multiply_plain(prod, weights[i]);
    evaluator.add(result, prod); // On l'ajoute au résultat
  }
// Maintenant on divise par le nombre de produit cad 5 ici
  evaluator.multiply_plain(result,encoder.encode(0.2));

//On vérifie le résultat
  double clearRes = 0;
  for (int i = 0; i < rational_numbers.size(); i++) {
    clearRes += rational_numbers[i]*coefficients[i];
  }
  clearRes = clearRes /5;
  Plaintext plain_result;
  decryptor.decrypt(result,plain_result);
  cout << "Result: " << encoder.decode(plain_result) << endl;
  cout << "Plain Result without Homomorphic : " << clearRes << endl;
  return 0;
}
