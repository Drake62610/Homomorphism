

void Globale(bool** matrix,int largeur,int longueur,int nbEtape);
int compteurLivingCell(bool** matrix,int largeur,int longueur,int posC,int posL);
void initToZero(bool** matrix,int largeur,int longueur);
int initGrenouille(bool** matrix);
void printMatrix(bool** matrix,int largeur,int longueur);
void copyMatrix(bool** matrix,bool** matrixNext,int largeur,int longueur);