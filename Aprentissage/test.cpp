#include <seal/seal.h>

using namespace std;
using namespace seal;

const string test_unitaire(bool condition){
    if (condition){
        return "Vrai";
    }
    else{
        return "Faux";
    }
}

int main(){
//###Parametrage####
    //Configuration des paramètre homomorphiques
	EncryptionParameters parms;
	parms.set_poly_modulus("1x^8192 + 1");
	parms.set_coeff_modulus(coeff_modulus_128(8192));
	parms.set_plain_modulus(65537);

    //Validation des paramètres et création du contexte
	SEALContext context(parms);

	//Utilisation d'un encoder pour integer (voir IntegerEncoder doc SEAL)
	IntegerEncoder encoder(context.plain_modulus());

	//Generation des clées publiques et privées
    KeyGenerator keygen(context);
    PublicKey public_key = keygen.public_key();
    SecretKey secret_key = keygen.secret_key();

    //Création de l'objet Encryptor, Evaluator et Decryptor
    Encryptor encryptor(context, public_key); //On a besoinde la clée publique pour l'encryption
    Evaluator evaluator(context); //Objet permettant de faire diverses opérations
    Decryptor decryptor(context, secret_key); //On decrypte avec la clée privée

    //Encryption de deux integers
    int a = 5;
    Plaintext plain1 = encoder.encode(a);
    cout << "Encodage de " << a << " en polynome : " << plain1.to_string() << endl;

    int b = 5;
    Plaintext plain2 = encoder.encode(b);
    cout << "Encodage de " << b << " en polynome : \n" << plain2.to_string() << endl;

    Ciphertext encrypted1, encrypted2;
    encryptor.encrypt(plain1, encrypted1);
    encryptor.encrypt(plain2, encrypted2);
    cout << "Encryption Réussie" << endl;

    int enca = encoder.decode(encrypted1);
    int encb = encoder.decode(encrypted2);

	return 0;
}
