# -*-coding:Latin-1 -*

import os

#Fonction qui renvoi 'rien'/ 'Pswitch' / etc
def filter(ligne):
    if('if' in ligne):
        return('if')
    if('pswitch' in ligne):
        return('pswitch')
    else:
        return('nothing')

def pswitch(comparateur1,comparateur2,affecte,valeur):
    tmp = 	"\ntmp3B="+ comparateur1 +".copy();\ntmp3B.XOR("+ comparateur2 +");\ntmp3B.reverse();\ntmp=tmp3B.multiplyComposant();\ntmp.multiply("+ valeur +");\n"+ affecte +".add(tmp);"
    return (tmp)


# Ouverture d'un fichier en *lecture*:
reading = open("../JeudeLaVie/JeuDeLaVie.project.cpp", "r")
#Ouverture d'un fichier en écriture
writing = open("output.cpp","w")

flagp = False
firstTime = True
# Utilisation du fichier
for ligne in reading:
    if('//' in ligne):
        writing.write(ligne.split('//')[0] + '\n')
    elif ('pswitch' in ligne):
        #First time doing a Pswitch
        if (firstTime):
            firstTime = False
            writing.write("Cipher3Bit tmp3B;")
        #Read argument of pswitch
        tmp = ligne.split('(')
        tmp = tmp[1].split(')')[0]
        comparateur1, affecte = tmp.split(',') #two arguments
        comparateur1 = comparateur1.strip() #remove spaces at the beginning and at the end
        affecte = affecte.strip()
        flagp = True
    elif (flagp):
        if '}' in ligne:
            flagp = False
        elif 'case' in ligne:
            tmp = ligne.split('case')[1].strip().split(':')
            comparateur2 = tmp[0].strip()
            valeur = tmp[1].strip()[0:-1]
            writing.write(pswitch(comparateur1,comparateur2,affecte,valeur))
        elif 'default' in ligne:
            tmp = ligne.split(':')[1].strip()[0:-1]
            writing.write("CipherBit tmp="+ tmp +".copy();")

    else:
        writing.write(ligne)


# Fermeture du fichier
reading.close()
writing.close()

#make the makefile
os.system('make')
