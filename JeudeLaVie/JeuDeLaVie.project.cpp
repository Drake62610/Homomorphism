#include <vector>
#include <seal/seal.h>
#include <../Structures/Cipher3Bit.h>

using namespace std;
using namespace seal;


//Fonctions du jeu de la vie en homomorphique
void destroy(CipherBit** matrix,int largeur,int longueur){

	for(int i = 0; i < largeur; i++) {
		delete(matrix[i]);
	}
	delete(matrix);
}
Cipher3Bit compteurLivingCell(CipherBit** matrix,int largeur,int longueur,int posC,int posL,Encryptor encryptor,Evaluator evaluator, Decryptor decryptor, Cipher3Bit compteur){
	CipherBit tmp; Plaintext print;
	int colonne,ligne;
	for (int i=-1;i<2;i++){
		for(int j=-1;j<2;j++){
			//cout<<"i= "<<i<<endl;
			//cout<<"j= "<<j<<endl;
			colonne=posC+j;
			ligne=posL+i;
			if ((colonne==-1)||(ligne==-1)||(colonne==largeur)||(ligne==longueur)){
				continue;
			}
			else if (i==0 && j==0){
				continue;
			}
			else {
				//cout<<"avant l'incrementation"<<endl;
				//tmp=matrix[(posC+i+largeur)%largeur][(posL+j+longueur)%longueur].copy();
				tmp=matrix[ligne%largeur][colonne%longueur];
				//decryptor.decrypt(tmp.getcipherBit(),print);
				//cout << "etat = " << print.to_string() << endl;
				compteur.incrementation(tmp); // On ajoute l'etat de la case au compteur pour compter les cellules vivantes
				compteur.reduceNoise(); //Triche simulation du futur
			}
		}
	}
	//std::cout << "fini" << '\n';
	compteur.reduceNoise(); //Triche simulation du futur
	return compteur;
}

void initToZero(CipherBit** matrix,int largeur,int longueur,Encryptor encryptor,Evaluator evaluator, Decryptor decryptor){
	Plaintext myplain0("0");	Ciphertext myCipher0;
	for (int i=0;i<largeur;i++){
		for (int j=0;j<longueur;j++){
			encryptor.encrypt(myplain0,myCipher0);	CipherBit faux(evaluator,encryptor,myCipher0);
			matrix[i][j]=faux.copy();
		}
	}
}

int initGrenouille(CipherBit** matrix,Encryptor encryptor,Evaluator evaluator, Decryptor decryptor){
	initToZero(matrix,4,4,encryptor,evaluator,decryptor);
	Plaintext myplain1("1");	Ciphertext myCipher1;	encryptor.encrypt(myplain1,myCipher1);
	CipherBit vrai(evaluator,encryptor,myCipher1);
	matrix[2][0]=vrai.copy();
	matrix[1][1]=vrai.copy();
	matrix[1][2]=vrai.copy();
	matrix[2][1]=vrai.copy();
	matrix[2][2]=vrai.copy();
	matrix[1][3]=vrai.copy();
	return 4;
}

void printMatrix(CipherBit** matrix,int largeur,int longueur,Decryptor decryptor){
	Plaintext plainResult("0");
	for (int i=0;i<largeur;i++){
		for (int j=0;j<longueur;j++){
			decryptor.decrypt(matrix[i][j].getcipherBit(),plainResult);
  			cout << plainResult.to_string();
		}
		cout<<""<<endl;
	}
}

void copyMatrix(CipherBit** matrix,CipherBit** matrixNext,int largeur,int longueur){
	CipherBit test;
	CipherBit tmp;
	for (int i=0;i<largeur;i++){
		for (int j=0;j<longueur;j++){
			//cout<<"eke"<<endl;
			test=matrix[i][j].copy();
			//cout<<"test init"<<endl;
			tmp=matrixNext[i][j].copy();
			//cout<<"tmp init"<<endl;

			matrix[i][j]=matrixNext[i][j].copy();
		}
	}
	cout<<"Copy Done "<<endl;
}
void globale(CipherBit** matrix,CipherBit** matrixNext,int largeur,int longueur,int nbEtape,Encryptor encryptor,Evaluator evaluator, Decryptor decryptor){
	//Init compteur
	Plaintext myplain0("0");	Plaintext plainResult;	Ciphertext myCipher0;
	encryptor.encrypt(myplain0,myCipher0); //cout << "creation compteur" <<endl;
	CipherBit compteurMSB(evaluator,encryptor, decryptor,myCipher0); // MSB = 0
	Cipher2Bit compteur0(compteurMSB.copy(),compteurMSB.copy()); // 0 0
	Cipher3Bit compteur(compteur0,compteurMSB); //Compteur = 0 0 0
	Cipher3Bit _cmptr;

	cout <<	"initToZero" << endl;
	matrixNext[0][0]= compteurMSB;
	int cellule=0;
	for (int etape=0;etape<nbEtape;etape++){
		for (int i=0;i<largeur;i++){
			for (int j=0;j<longueur;j++){
				//cout<<"on est dans les for"<<endl;
				cellule+=1;
				cout<<"cellule n° "<<cellule<<endl;
				//std::cout << "copy dans _cmptr" << '\n';
				_cmptr = compteur.copy();
					_cmptr.reduceNoise();
				_cmptr = compteurLivingCell(matrix,largeur,longueur,j,i,encryptor,evaluator,decryptor,_cmptr);
				_cmptr.reduceNoise();

				Plaintext myplain0("0");	Ciphertext myCipher0;	encryptor.encrypt(myplain0,myCipher0);
				CipherBit faux(evaluator,encryptor,decryptor,myCipher0);
				Plaintext myplain1("1");	Ciphertext myCipher1;	encryptor.encrypt(myplain1,myCipher1);
				CipherBit vrai(evaluator,encryptor,decryptor,myCipher1);
				Cipher2Bit deux2(faux,vrai);
				Cipher2Bit trois2(vrai,vrai);
				Cipher3Bit deux(deux2,faux);
				Cipher3Bit trois(trois2,faux);
				CipherBit result=faux.copy();

				//pswitch(a,result), a est comparé aux différents cas, result est affecté d'une nouvelle valeure si un cas correspond.
				pswitch(_cmptr, result){
						default: faux;
						case deux: matrix[i][j];
						case trois: vrai;
				}
				matrixNext[i][j]= result;
			}
		}
		cout<<"première itération fini"<<endl;
		//cout<<"WHAT"<<endl;
		copyMatrix(matrix,matrixNext,largeur,longueur);
		cout<<"Après l'étape "<<etape<<endl;
		printMatrix(matrix,largeur,longueur,decryptor);
	}
	//destroy(matrixNext,largeur,longueur);
}


int main(){
  //Configuration des paramètres homomorphiques
    EncryptionParameters parms;
    parms.set_poly_modulus("1x^4096 + 1");
    parms.set_coeff_modulus(coeff_modulus_128(4096));
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

    cout<<"/Lancement de l'exemple de la Grenouille"<<endl;
	int largeur=4,longueur=4;
	CipherBit** matrix;

	matrix = (CipherBit**) malloc(largeur * sizeof(CipherBit*));
	for(int i = 0; i < largeur; i++) {
		matrix[i] = (CipherBit*) malloc(longueur * sizeof(CipherBit));
	}
	//Malloc
	CipherBit** matrixNext;
	matrixNext = (CipherBit**) malloc(largeur * sizeof(CipherBit*));
	for(int i = 0; i < largeur; i++) {
		matrixNext[i] = (CipherBit*) malloc(longueur * sizeof(CipherBit));
	}


	largeur=longueur=initGrenouille(matrix,encryptor,evaluator,decryptor);
	printMatrix(matrix,largeur,longueur,decryptor);

	// //Creation de compteur
	Plaintext myplain0("0");
	Plaintext plainResult;
	Ciphertext myCipher0;
	CipherBit tmp;
	encryptor.encrypt(myplain0,myCipher0);
	CipherBit compteurMSB(evaluator,encryptor,decryptor,myCipher0);

  globale(matrix,matrixNext,largeur,longueur,2,encryptor,evaluator,decryptor);
	//destroy(matrix,largeur,longueur);
	return 0;
}
