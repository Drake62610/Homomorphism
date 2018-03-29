#include <seal/seal.h>

using namespace std;
using namespace seal;

/*
Helper function: Prints the name of the example in a fancy banner.
*/
/*
Helper function: Prints the parameters in a SEALContext.
*/
void print_parameters(const SEALContext &context)
{
    cout << "/ Encryption parameters:" << endl;
    cout << "| poly_modulus: " << context.poly_modulus().to_string() << endl;

    /*
    Print the size of the true (product) coefficient modulus
    */
    cout << "| coeff_modulus size: " 
        << context.total_coeff_modulus().significant_bit_count() << " bits" << endl;

    cout << "| plain_modulus: " << context.plain_modulus().value() << endl;
    cout << "\\ noise_standard_deviation: " << context.noise_standard_deviation() << endl;
    cout << endl;
}

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
	print_parameters(context);

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

    int b = -7;
    Plaintext plain2 = encoder.encode(b);
    cout << "Encodage de " << b << " en polynome : \n" << plain2.to_string() << endl;

    Ciphertext encrypted1, encrypted2;
    encryptor.encrypt(plain1, encrypted1); 
    encryptor.encrypt(plain2, encrypted2);
    cout << "Encryption Réussie" << endl;

    //Operations sur nos donnée encryptées
    Ciphertext enc_sum,enc_prod;
    enc_sum = encrypted1;
    evaluator.add(enc_sum,encrypted2); //Attention l'addition écrase le premier argument
    enc_prod = encrypted1;
    evaluator.multiply(enc_prod,encrypted2); //De même avec la multiplication

    //Decryptage
    Plaintext plain_sum,plain_prod;
    decryptor.decrypt(enc_sum,plain_sum);
    decryptor.decrypt(enc_prod,plain_prod);
    cout << "Sum : " << encoder.decode_int32(plain_sum) << endl;
    cout << "Prod : " << encoder.decode_int32(plain_prod) << endl;

    //Test Unitaire
    bool bool_sum = (a+b == encoder.decode_int32(plain_sum));
    bool bool_prod = (a*b == encoder.decode_int32(plain_prod));

    cout << "Somme executée avec succès : " << test_unitaire(bool_sum) << endl;
    cout << "Multiplication executée avec succès : " << test_unitaire(bool_prod) << endl;



	return 0;
}



