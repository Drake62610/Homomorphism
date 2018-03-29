#include <seal/seal.h>

using namespace std;
using namespace seal;

int plainPGCD(int a,int b){
	if (a<b){
		int c = b;
		a=b;
		b=c;
	}
	int r;
	while (r!=0){
		r=a%b;
		a=b;
		b=r;
	}
	return b;
}
/*
	Input : Cyphertext a, donnée cryptée
			Cyphertext b, donnée cryptée
			Cypertext n, nombre d'itérations
	Output : PGCD des deux données cryptées
*/
int cipherPGDC(Ciphertext a,Ciphertext b,int n){

}

bool plainNegative(int a){
	if(a<0){
		return true;
	}
	return false;
}
/*
	Input : Cyphertext a, donnée cryptée
			Cyphertext aOpp, opposé de a encrypté 
	Output : Cyphertext d'un boolean
*/
Ciphertext cipherNegative(Ciphertext a, Ciphertext aOpp, const SEALContext &context, PublicKey public_key){
	FractionalEncoder encoder(context.plain_modulus(), context.poly_modulus(), 64, 32, 3);
    Evaluator evaluator(context); //Objet permettant de faire diverses opérations
    
    evaluator.multiply(a,aOpp);
    evaluator.add_plain(a,encoder.encode(1));
    evaluator.multiply_plain(a,encoder.encode(0.5));
    

	//one = encryptor.encrypt(encoder.encode(1));
	//demi = encryptor.encrypt(encoder.encode(0.5));

	return a;
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
	FractionalEncoder encoder(context.plain_modulus(), context.poly_modulus(), 64, 32, 3);
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

    Ciphertext boolnegative, boolpositive;
    //cipherNegative()
}