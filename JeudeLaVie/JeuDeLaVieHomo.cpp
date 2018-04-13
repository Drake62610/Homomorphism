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
Cipher3Bit compteurLivingCell(CipherBit** matrix,int largeur,int longueur,int posC,int posL,Encryptor encryptor,Evaluator evaluator, Decryptor decryptor){
	Plaintext myplain0("0");
	Ciphertext myCipher0;
	CipherBit tmp;
	encryptor.encrypt(myplain0,myCipher0);
	CipherBit compteurMSB(evaluator,encryptor,myCipher0);
	Cipher2Bit compteur0(compteurMSB,compteurMSB);
	Cipher3Bit compteur(compteur0,compteurMSB);
	//cout<<"Init du compteurLivingCell"<<endl;
	for (int i=-1;i<2;i++){
		for(int j=-1;j<2;j++){
			if (i==0 && j==0){
				continue;
			}
			else {
				//cout<<"avant l'incrementation"<<endl;
				tmp=matrix[(posC+i+largeur)%largeur][(posL+j+longueur)%longueur].copy();
				//cout<<"tmp init"<<endl;
				compteur.incrementation(tmp);
				decryptor.decrypt(compteur.getMSB().getcipherBit(),myplain0);
				encryptor.encrypt(myplain0,myCipher0);
				compteur.setMSB(myCipher0);
				decryptor.decrypt(compteur.getPartie0().getCipherBit0().getcipherBit(),myplain0);
				encryptor.encrypt(myplain0,myCipher0);
				compteur.getPartie0().setCipherBit0(myCipher0);
				decryptor.decrypt(compteur.getPartie0().getCipherBit1().getcipherBit(),myplain0);
				encryptor.encrypt(myplain0,myCipher0);
				compteur.getPartie0().setCipherBit1(myCipher0);
				//cout<<"après l'incrementation"<<endl;
			}
		}
	}
	return compteur;
}

void initToZero(CipherBit** matrix,int largeur,int longueur,Encryptor encryptor,Evaluator evaluator, Decryptor decryptor){
	for (int i=0;i<largeur;i++){
		for (int j=0;j<longueur;j++){
			Plaintext myplain0("0");	Ciphertext myCipher0;	encryptor.encrypt(myplain0,myCipher0);	CipherBit faux(evaluator,encryptor,myCipher0);
			matrix[i][j]=faux.copy();
		}
	}
}

int initGrenouille(CipherBit** matrix,Encryptor encryptor,Evaluator evaluator, Decryptor decryptor){
	initToZero(matrix,3,3,encryptor,evaluator,decryptor);
	Plaintext myplain1("1");	Ciphertext myCipher1;	encryptor.encrypt(myplain1,myCipher1);
	CipherBit vrai0(evaluator,encryptor,myCipher1);
	CipherBit vrai1(evaluator,encryptor,myCipher1);
	CipherBit vrai2(evaluator,encryptor,myCipher1);
	CipherBit vrai3(evaluator,encryptor,myCipher1);
	CipherBit vrai4(evaluator,encryptor,myCipher1);
	CipherBit vrai5(evaluator,encryptor,myCipher1);
	matrix[2][0]=vrai0.copy();
	matrix[1][1]=vrai1.copy();
	matrix[1][2]=vrai2.copy();
	matrix[2][1]=vrai3.copy();
	matrix[2][2]=vrai4.copy();
	//matrix[1][3]=vrai5.copy();
	return 3;
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
	cout<<"On est dans le globale"<<endl;
	Cipher3Bit compteur;
	CipherBit** matrixNext;
	matrixNext = (CipherBit**) malloc(largeur * sizeof(CipherBit*));
	for(int i = 0; i < largeur; i++) {
		matrixNext[i] = (CipherBit*) malloc(longueur * sizeof(CipherBit));
	}
	Plaintext myplain1("1");	Ciphertext myCipher1;	encryptor.encrypt(myplain1,myCipher1);
	CipherBit vrai0(evaluator,encryptor,myCipher1);
	cout<<"wesh"<<endl;
	matrixNext[1][1]=vrai0.copy();
	//largeur=longueur=initGrenouille(matrixNext,encryptor,evaluator,decryptor);
	cout<<"on a malloc"<<endl;
	for (int etape=0;etape<nbEtape;etape++){
		for (int i=0;i<largeur;i++){
			for (int j=0;j<longueur;j++){
				//cout<<"on est dans les for"<<endl;
				cout<<"cellule n° "<<i+j<<endl;
				compteur=compteurLivingCell(matrix,largeur,longueur,i,j,encryptor,evaluator,decryptor);
				//cout<<"On a le compteur"<<endl;
				Plaintext myplain0("0");	Ciphertext myCipher0;	encryptor.encrypt(myplain0,myCipher0);	
				CipherBit faux(evaluator,encryptor,myCipher0);
				Plaintext myplain1("1");	Ciphertext myCipher1;	encryptor.encrypt(myplain1,myCipher1);
				CipherBit vrai(evaluator,encryptor,myCipher1);
				Cipher2Bit deux2(faux,vrai);
				Cipher2Bit trois2(vrai,vrai);
				Cipher3Bit deux(deux2,faux);
				Cipher3Bit trois(trois2,faux);
				CipherBit result=faux.copy();
				CipherBit tmp=faux.copy();

				//cout<<"Début des if"<<endl;
				//egal à 2?
				Cipher3Bit tmp3B=compteur.copy();
				tmp3B.XOR(deux);
				tmp3B.reverse();
				tmp=tmp3B.multiplyComposant();
				tmp.multiply(matrix[i][j]);
				result.add(tmp);

				//égal à 3?
				tmp3B=compteur.copy();
				tmp3B.XOR(trois);
				tmp3B.reverse();
				tmp=tmp3B.multiplyComposant();
				tmp.multiply(matrix[i][j]);
				result.add(tmp);
				//result.add(XOR(compteur,"3").inverse().4BitsTo1Bit());
				matrixNext[i][j]=result;
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
    parms.set_poly_modulus("1x^8192 + 1");
    parms.set_coeff_modulus(coeff_modulus_128(8192));
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
	int largeur=3,longueur=3;
	CipherBit** matrix;

	matrix = (CipherBit**) malloc(largeur * sizeof(CipherBit*));
	for(int i = 0; i < largeur; i++) {
		matrix[i] = (CipherBit*) malloc(longueur * sizeof(CipherBit));
	}

	largeur=longueur=initGrenouille(matrix,encryptor,evaluator,decryptor);
	printMatrix(matrix,largeur,longueur,decryptor);
	globale(matrix,largeur,longueur,1,encryptor,evaluator,decryptor);
	destroy(matrix,largeur,longueur);



    return 0;
}