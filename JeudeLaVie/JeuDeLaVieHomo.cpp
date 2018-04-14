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
	for (int i=-1;i<2;i++){
		for(int j=-1;j<2;j++){
			cout<<"i= "<<i<<endl;
			cout<<"j= "<<j<<endl;
			if (i==0 && j==0){
				continue;
			}
			else {
				//cout<<"avant l'incrementation"<<endl;
				tmp=matrix[(posC+i+largeur)%largeur][(posL+j+longueur)%longueur].copy();
			  decryptor.decrypt(tmp.getcipherBit(),print);
				cout << "etat = " << print.to_string() << endl;
				compteur.incrementation(tmp); // On ajoute l'etat de la case au compteur pour compter les cellules vivantes
				compteur.reduceNoise(); //Triche simulation du futur
			}
		}
	}
	std::cout << "fini" << '\n';
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
	initToZero(matrix,5,5,encryptor,evaluator,decryptor);
	Plaintext myplain1("1");	Ciphertext myCipher1;	encryptor.encrypt(myplain1,myCipher1);
	CipherBit vrai(evaluator,encryptor,myCipher1);
	matrix[2][0]=vrai.copy();
	matrix[1][1]=vrai.copy();
	matrix[1][2]=vrai.copy();
	matrix[2][1]=vrai.copy();
	matrix[2][2]=vrai.copy();
	matrix[1][3]=vrai.copy();
	return 5;
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
			cout<<"eke"<<endl;
			test=matrix[i][j].copy();
			cout<<"test init"<<endl;
			tmp=matrixNext[i][j].copy();
			cout<<"tmp init"<<endl;

			matrix[i][j]=matrixNext[i][j].copy();
		}
	}
	cout<<"Copy Done "<<endl;
}
void globale(CipherBit** matrix,int largeur,int longueur,int nbEtape,Encryptor encryptor,Evaluator evaluator, Decryptor decryptor){
	//Init compteur
	Plaintext myplain0("0");	Plaintext plainResult;	Ciphertext myCipher0; CipherBit tmp;
	encryptor.encrypt(myplain0,myCipher0); cout << "creation compteur" <<endl;
	CipherBit compteurMSB(evaluator,encryptor, decryptor,myCipher0); // MSB = 0
	Cipher2Bit compteur0(compteurMSB.copy(),compteurMSB.copy()); // 0 0
	Cipher3Bit compteur(compteur0,compteurMSB); //Compteur = 0 0 0
	Cipher3Bit _cmptr;
	//????
	CipherBit** matrixNext;
	matrixNext = (CipherBit**) malloc(largeur * sizeof(CipherBit*));
	for(int i = 0; i < largeur; i++) {
		matrixNext[i] = (CipherBit*) malloc(longueur * sizeof(CipherBit));
	}

	for (int etape=0;etape<nbEtape;etape++){
		for (int i=0;i<largeur;i++){
			for (int j=0;j<longueur;j++){
				//cout<<"on est dans les for"<<endl;
				cout<<"cellule n° "<<i+j<<endl;
				std::cout << "creation du tampon" << '\n';
				_cmptr = compteur.copy();
					cout << "Affichage du tampon avant comptage" << endl;
					Cipher2Bit test; test = _cmptr.getPartie0();
					decryptor.decrypt(test.getCipherBit0().getcipherBit(),plainResult);
					cout << "bit0= " << plainResult.to_string()<< endl;
					decryptor.decrypt(test.getCipherBit1().getcipherBit(),plainResult);
					cout << "bit1= " << plainResult.to_string() << endl;
					decryptor.decrypt(_cmptr.getMSB().getcipherBit(),plainResult);
					cout << "bit2= " << plainResult.to_string()<<endl;
				_cmptr = compteurLivingCell(matrix,largeur,longueur,i,j,encryptor,evaluator,decryptor,_cmptr);
				cout<<"On a le compteur"<<endl;
				_cmptr.reduceNoise();
					cout << "Affichage du tampon après comptage" << endl;
					test = _cmptr.getPartie0();
					decryptor.decrypt(test.getCipherBit0().getcipherBit(),plainResult);
					cout << "bit0= " << plainResult.to_string()<< endl;
					decryptor.decrypt(test.getCipherBit1().getcipherBit(),plainResult);
					cout << "bit1= " << plainResult.to_string() << endl;
					decryptor.decrypt(_cmptr.getMSB().getcipherBit(),plainResult);
					cout << "bit2= " << plainResult.to_string()<<endl;
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
				Cipher3Bit tmp3B=_cmptr.copy();
				cout<<"Xor tmp3B & deux"<<endl;
				compteur.XOR(deux);
				cout<<"2"<<endl;
				tmp3B.reverse();
				cout<<"3"<<endl;
				tmp=tmp3B.multiplyComposant();
				cout<<"4"<<endl;
				tmp.multiply(matrix[i][j]);
				cout<<"5"<<endl;
				result.add(tmp);

				//égal à 3?
				cout<<"Xor tmp3B & trois"<<endl;
				tmp3B=_cmptr.copy();
				tmp3B.XOR(trois);
				cout<<"2"<<endl;
				tmp3B.reverse();
				cout<<"3"<<endl;
				tmp=tmp3B.multiplyComposant();
				cout<<"4"<<endl;
				tmp.multiply(matrix[i][j]);
				cout<<"5"<<endl;
				result.add(tmp);
				//result.add(XOR(compteur,"3").inverse().4BitsTo1Bit());
				std::cout << "ecrasement" << '\n';
				//matrixNext[i][j]=result;

				/*if (compteur==2){
					matrixNext[i][j]=matrix[i][j].copy();
				}
				else if (compteur==3){
					matrixNext[i][j]=true;
				}
				else {
					matrixNext[i][j]=false;
				}
				/* Pour changer les conditions en une ligne:
					compteur=Struct4Bits
					"2" et "3"=Struct4Bits
					result et "true" et "false"=1Bit
					methodes utilisées :-XOR de Struct 4 Bits (ici seul les 3 premiers bits sont intéréssants) !!!!    return Cipher4bit !!! XOR(Cipher4Bit,Cipher4Bit)
										-inverse4Bits() ->not logic sur chaque bit de la structure
										-4BitsTo1Bit() -> multiplier chaque bit entre eux pour obtenir soit un 0 soit un 1
					result="false";
					result.add(XOR(compteur,"2").inverse4Bits().4BitsTo1Bit().multiply(matrix[i][j]));
					result.add(XOR(compteur,"3").inverse().4BitsTo1Bit());

					//result+=XOR(compteur,"2").inverse4Bits().4BitsTo1Bit()*(matrix[i][j]) + XOR(compteur,"3").inverse().4BitsTo1Bit()*("true");

				*/
				cout<<"première itération fini"<<endl;
			}
		}
		cout<<"WHAT"<<endl;
		copyMatrix(matrix,matrixNext,largeur,longueur);
		cout<<"Après l'étape "<<etape<<endl;
		printMatrix(matrix,largeur,longueur,decryptor);
	}
	destroy(matrixNext,largeur,longueur);
}


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

    cout<<"/Lancement de l'exemple de la Grenouille"<<endl;
	int largeur=5,longueur=5;
	CipherBit** matrix;

	matrix = (CipherBit**) malloc(largeur * sizeof(CipherBit*));
	for(int i = 0; i < largeur; i++) {
		matrix[i] = (CipherBit*) malloc(longueur * sizeof(CipherBit));
	}

	largeur=longueur=initGrenouille(matrix,encryptor,evaluator,decryptor);
	printMatrix(matrix,largeur,longueur,decryptor);

	// //Creation de compteur
	// Plaintext myplain0("0");
	// Plaintext plainResult;
	// Ciphertext myCipher0;
	// CipherBit tmp;
	// encryptor.encrypt(myplain0,myCipher0);
	// CipherBit compteurMSB(evaluator,encryptor,decryptor,myCipher0); // MSB = 0
	// Cipher2Bit compteur0(compteurMSB.copy(),compteurMSB.copy()); // 0 0
	// Cipher3Bit compteur(compteur0,compteurMSB); //Compteur = 0 0 0
	//
	// tmp=matrix[4][4].copy();
	// compteur.incrementation(tmp);
	// compteur.reduceNoise();
	// tmp=matrix[4][0].copy();
	// compteur.incrementation(tmp); // On ajoute l'etat de la case au compteur pour compter les cellules vivantes
	//
	// CipherBit faux(evaluator,encryptor,decryptor,myCipher0);
	// Plaintext myplain1("1");	Ciphertext myCipher1;	encryptor.encrypt(myplain1,myCipher1);
	// CipherBit vrai(evaluator,encryptor,decryptor,myCipher1);
	// Cipher2Bit deux2(faux,vrai);
	// Cipher2Bit trois2(vrai,vrai);
	// Cipher3Bit deux(deux2,faux);
	// Cipher3Bit trois(trois2,faux);
	// CipherBit result=faux.copy();
	// tmp=faux.copy();
	// cout<<"Début des if"<<endl;
	// //egal à 2?
	// Cipher3Bit tmp3B=compteur.copy();
	// cout<<"Xor tmp3B & deux"<<endl;
	// tmp3B.XOR(deux);

  globale(matrix,largeur,longueur,1,encryptor,evaluator,decryptor);
	//destroy(matrix,largeur,longueur);
	return 0;
}
