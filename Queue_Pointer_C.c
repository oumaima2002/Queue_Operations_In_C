#include <stdio.h>
#include <stdlib.h>

//File dynamique
typedef struct fl
{
int info;
struct fl *svt;// pointeur sur l'�l�ment suivant
}cellule;

typedef struct dfl
{
cellule *debut;//pointeur sur le d�but de la file
cellule *fin;//pointeur sur la fin de la file
}Dfile;

/**
Nom: initialiser_Dfile
Role: Cette fonction sert � initialiser la file
Entrees :la file
Sorties : la file initialis�e
*/
Dfile* initialiser_Dfile(Dfile*F)
{//initialiser le d�but et la fin par NULL
F->debut=F->fin=NULL;
return((Dfile*)F);
}

/**
Nom: cree_Dfile
Role: Cette fonction permet de cr�er la file,on allouant de l�espace m�moire pour une nouvelle file
     et nous initialisons le d�but et la fin par NULL.
Entrees :Rien
Sorties : la file cr�e
*/
Dfile *cree_Dfile()
{
Dfile*F;
F=(Dfile*)malloc(sizeof(Dfile));//allocation de la m�moire
if(!F)// erreur d'allocation de la m�moire
{
printf("m�moire satur�e\n");
exit(0);//sortir du programme
}
F=initialiser_Dfile(F);//initialiser le file
return((Dfile*)F);
}

/*le nom: cree_cellule
les entr�es: un entier qui repr�sente la valeur � stock�e
les sorties: un pointeur qui pointe sur nouvel �l�ment de type cellule
le r�le: Cette fonction permet d�allouer de l�espace m�moire pour une nouvelle cellule,
et au m�me temps elle remplit le champ d�information par la valeur pass�e par argument */
cellule* cree_Cellule(int valeur)
{
cellule* NE;//d�claration du nouveau �l�ment
NE=(cellule*)malloc(sizeof(cellule));//allocation de la m�moire
if(!NE)// erreur d'allocation de la m�moire
{
printf("m�moire satur�e\n");
exit(0);//sortir du programme
}
NE->info=valeur;//affectation de la valeur
NE->svt=NULL;//initialiser le suivant du nouvel �l�ment
return ((cellule*)NE);
}

/**
Nom: Est_vide_Dfile
Role: Cette fonction permet de v�rifier si la file est vide ou non .
Entrees :la file
Sorties :cette fonction retourne 1 si la file est vide ,sinon 0.
*/
int Est_vide_Dfile(Dfile*F)
{
if((F->debut==NULL)&&(F->fin==NULL))
return ((int)1);//liste vide
return((int)0);
}

/**
Nom: Enfiler_Dfile
Role: Cette fonction permet d�enfiler un �l�ment dans la file. C'est-�-dire ajouter un nouvel �l�ment au d�but de la file.
 Et on va distinguer entre les diff�rentes situations qu�on peut avoir.
Entrees :l'adresse de la file et un entier.
Sorties :l'adresse de la nouvelle file.
*/
int Enfiler_Dfile(Dfile*F,int valeur)
{
cellule*NE;
if(!F) return ((int)-1);//file n'existe pas
NE=cree_Cellule(valeur);//cr�er cellule
//ins�rer dans une file vide
if(Est_vide_Dfile(F))
F->debut=F->fin=NE;
//les autres cas
else
{
F->fin->svt=NE;
F->fin=NE;
}
return((int)1);
}

/**
Nom: Defiler_Dfile
Role: Cette fonction permet de d�filer la file. C'est-�-dire, on va supprimer l��l�ment qui se trouve dans la t�te de la file.
Entrees :l'adresse de la file.
Sorties :l'adresse de la nouvelle file.
*/
int Defiler_Dfile(Dfile *F)
{
cellule *ptr;//�l�ment de suppression
if(!F) return ((int )-1);//file n'existe pas
if(Est_vide_Dfile(F)) return((int)0);//file vide
//cas 1 seul �l�ment dans la file
if(F->debut==F->fin)
{
ptr=F->debut;
F=initialiser_Dfile(F);
}
//cas ou on a plus qu'un �l�ment
else
{
ptr=F->debut;
F->debut=F->debut->svt;
}
free(ptr);//lib�rer la m�moire
return ((int)1);
}

///afficher la file
/*Fonction   : Afficher_pfile
Description: Cette fonction sert � afficher les valeurs de la
             file
Entrees    : la file
Sorties    : pas de sorties
*/
void Afficher_Dfile(Dfile* file)
{
    Dfile* file2=NULL;//une file temporelle
    file2=cree_Dfile();//creation de la file temporelle
    //Si la file n'existe pas
    if(!file)
        printf("\nLa file n'existe pas\n");
   //Si la file est vide
    else if(Est_vide_Dfile(file))
        printf("\nLa file est vide");
    else{
    printf("\nLes elements de la file sont : \n");
    //Tantque la file n'est pas vide
            while(!Est_vide_Dfile(file))
            {
                printf("%d\t",file->debut->info);
                Enfiler_Dfile(file2,file->debut->info);
                Defiler_Dfile(file);
            }
//remettre les valeurs de la file 2 dans la file initiale
            while(!Est_vide_Dfile(file2))
            {
                Enfiler_Dfile(file,file2->debut->info);
                Defiler_Dfile(file2);
            }
        }
}

/**
Nom: occurence_Dfile
Role: Cette fonction nous permet de d�terminer le nombre d'occurence d'un �l�ment.
Entrees :l'adresse de la file,L'entier que nous voulons trouver le nombre de ses occurrences.
Sorties :cette fonction retourne -1 si la file n'existe pas,0 si la file est vide sinon il retourne compt qui
contient le nombre d'occurence de l'�l�ment.
*/
int occurence_Dfile(Dfile*F,int valeur)
{
  Dfile* file2=NULL;//file temporelle
  file2=cree_Dfile();
int compt=0;//nombre d'occurrence
if(!F) return((int)-1);//file n'existe pas
if ((Est_vide_Dfile(F))) return((int)0);//file vide
//Tantque la file n'est pas vide j'enfile dans la file 2
    while(!Est_vide_Dfile(F))
    {   // condition d'occurrence
        if((F->debut->info)==valeur) compt++;//incr�menter compteur
        Enfiler_Dfile(file2,F->debut->info);
        Defiler_Dfile(F);
    }
    //remettre les valeurs de la file 2 dans la file initiale
    while(!Est_vide_Dfile(file2))
    {
        Enfiler_Dfile(F,file2->debut->info);
        Defiler_Dfile(file2);
    }
return((int)compt);
}

/**
Nom: chercher_Dfile
Role: Cette fonction nous permet de chercher un �l�ment dans la file .
Entrees :l'adresse de la file,L'entier que nous voulons chercher.
Sorties :cette fonction retourne 0 si l'�l�ment n'existe pas,s
*/
int chercher_Dfile(Dfile*F,int valeur)
{//si le nombre d'occurrence est sup�rieur a 0 l'�l�ment existe(return 1)
return ((int)(occurence_Dfile(F,valeur)>0));
}

///le maximum de la file
/**
Nom: max_Dfile
Role: Cette fonction sert � trouver le maximum de la file
Entrees :la file
Sorties : -1 si la file n'existe pas 0 si la file est vide sinon il retourne le max
*/
int max_Dfile(Dfile* file)
{
    Dfile* file2=NULL;//file temporelle
    file2=cree_Dfile();
    int max=0;
    if(!file)   return((int)-1);
    if(Est_vide_Dfile(file))  return((int)0);
    max=file->debut->info;
//Tantque la file n'est pas vide j'enfile dans la file 2
    while(!Est_vide_Dfile(file))
    {   Enfiler_Dfile(file2,file->debut->info);
        Defiler_Dfile(file);
        if(!Est_vide_Dfile(file)&&((file->debut->info)>(max)))
            max=file->debut->info;//l'affectation du maximum
    }
//remettre les valeurs de la file 2 dans la file initiale
    while(!Est_vide_Dfile(file2))
    {
        Enfiler_Dfile(file,file2->debut->info);
        Defiler_Dfile(file2);
    }
    return((int)max);
}
///le minimum de la file
/**
Nom : min_Dfile
Role: Cette fonction sert � trouver le minimum de la file
Entr�es: la file
Sorties : -1 si la file n'existe pas,0 si la file est vide sinon il retourne le min
*/
int min_Dfile(Dfile* file)
{
    Dfile* file2=NULL;//file temporelle
    file2=cree_Dfile();
    int min;
    if(!file)  return((int)-1);
    if(Est_vide_Dfile(file)) return((int)0);
    min=file->debut->info;
   //Tantque la file n'est pas vide j'enfile dans la file 2
    while(!Est_vide_Dfile(file))
    {
        Enfiler_Dfile(file2,file->debut->info);
        Defiler_Dfile(file);
     //l'affectation du maximum
     if(!Est_vide_Dfile(file)&&((file->debut->info)<(min)))
        min=file->debut->info;
    }
   //remettre les valeurs de la file 2 dans la file initiale
    while(!Est_vide_Dfile(file2))
    {
        Enfiler_Dfile(file,file2->debut->info);
        Defiler_Dfile(file2);
    }
    return((int)min);
}
///vider la file
/**
Nom : Raz_Dfile
Role: Cette fonction sert � vider la file
Entr�es    : la file
Sorties    : pas de sorties
*/
void Raz_Dfile(Dfile* file)
{
 //Si la file n'existe pas
    if(!file)  printf("\nLa file n'existe pas\n");
  //Si la file est vide
    else{
    if(Est_vide_Dfile(file))  printf("\nLa file est deja vide\n");
    else{
    //Tantque la file n'est pas vide je defile
    while(!Est_vide_Dfile(file))
    Defiler_Dfile(file);}
    }
}

///supp pos
/**
Nom: supp_pos_Dfile
Role: Cette fonction sert � supprimer une valeur dans la file dans une position donn�e
Entrees:la file et la position
Sorties: void
*/
void supp_pos_Dfile(Dfile* file,int pos)
{
    Dfile *file2=NULL;//une file temporelle
    file2=cree_Dfile();//creation de la file temporelle
    int comp=0;//compteur
    //Si la file n'existe pas
    if(!file)  printf("\nLa file n'existe pas\n");
   //Si la file est vide
    else if(Est_vide_Dfile(file)) printf("\nLa file est vide");
   //Si la position est incorrecte
    else if((pos>=taille_Dfile(file))||(pos<0))
    printf("\n Position Incorrecte\n");
    else{
   //Tantque la file initiale n'est pas vide et le compteur est inferieur
   //� la postion j'enfile dans la file 2 et j'incremente
            while(!Est_vide_Dfile(file)&&(comp<pos))
                {
                    Enfiler_Dfile(file2,file->debut->info);
                    Defiler_Dfile(file);
                    comp++;
                }
    //Defilement de la valeur � supprimer
                Defiler_Dfile(file);
    //je continue � enfiler le reste de la file dans la file 2
                while(!Est_vide_Dfile(file))
                {
                    Enfiler_Dfile(file2,file->debut->info);
                    Defiler_Dfile(file);
                }
//remettre les valeurs de la file 2 dans la file initiale
                while(!Est_vide_Dfile(file2))
                {
                    Enfiler_Dfile(file,file2->debut->info);
                    Defiler_Dfile(file2);
                }
            }
}

/**
Nom : taille_Dfile
Role: Cette fonction permet de trouver la taille de la file
Entr�es    : la file
Sorties    :cette fonction retoune -1 si la file n'existe pas,0 si la file est vide
sinon il retourne la taille de la file � l'aide de la variable comp
*/
int taille_Dfile(Dfile* file)
{
    Dfile* file2=NULL;//une file temporelle
    file2=cree_Dfile();//creation de la file temporelle
    int comp=0;//initialisation de la file
    if(!file)  return((int)-1);//si la file n'existe pas
    if(Est_vide_Dfile(file))  return((int)comp);//si la file est vide
   //Tantque la file n'est pas vide compter ses �l�ments
    while(!Est_vide_Dfile(file))
    {
        Enfiler_Dfile(file2,file->debut->info);
        Defiler_Dfile(file);
        comp++;
    }
    /*Tantque la file 2 n'est pas vide mettre les �l�ments de
    la pile 2 dans la 1ere pile*/
    while(!Est_vide_Dfile(file2))
    {   Enfiler_Dfile(file,file2->debut->info);
        Defiler_Dfile(file2);
    }
    return((int)comp);
}
int main()
{
    //les files (version pointeur)
Dfile *F;
int valeur,choix,verifi,pos;
do
{
printf("\n----------------entrer un choix---------------- \n");
printf("1: pour creer et initialise une file \n");
printf("2: pour enfiler une file \n");
printf("3: pour defiler une file \n");
printf("4: pour afficher une file\n");
printf("5: pour afficher le nombre d'occurrence d'un element\n");
printf("6: pour recherche d'un element\n");
printf("7: Le minimum de la file \n");
printf("8: Le maximum de la file \n");
printf("9: pour tasser la file");
printf("10: pour supprimer un element dans une position \n");
printf("11: pour d�terminer la taille de la file\n");
printf("0: pour sortir du programme\n");
scanf("%d",&choix);
switch(choix)
{
case 1:  F=cree_Dfile();
         printf("File cr�e et initialis�e avec succ�s\n");
         break;
case 2:  printf("donner la valeur � enfiler :\n");
         scanf("%d",&valeur);
         verifi=Enfiler_Dfile(F,valeur);
         if(verifi==-1) printf("file n'existe pas\n");
         if(verifi==1) printf("�l�ment enfile avec succ�s\n");
         break;
case 3:  verifi=Defiler_Dfile(F);
         if(verifi==0) printf("file vide\n");
         if(verifi==-1) printf("file n'existe pas\n");
         if(verifi==1) printf("�l�ment d�fil� avec succ�s\n");
         break;
case 4:  Afficher_Dfile(F); break;
case 5:  printf("donner un �l�ment :\n");
         scanf("%d",&valeur);
         verifi=occurence_Dfile(F,valeur);
         if(verifi==0) printf("file vide\n");
         else if(verifi==-1) printf("file n'existe pas\n");
         else printf("le nombre d'occurrence de %d est:%d\n",valeur,verifi);
         break;
case 6:  printf("donner l'�l�ment a chercher :\n");
         scanf("%d",&valeur);
         verifi=chercher_Dfile(F,valeur);
         if(verifi==0) printf(" l'�l�ment %d n'existe pas\n",valeur);
         else printf("l'�l�ment %d existe dans la file\n",valeur);
         break;
case 7:  verifi=min_Dfile(F);
         if(verifi==0) printf("file vide\n");
         if(verifi==-1) printf("file n'existe pas\n");
         else printf("le minimum de la file est:%d\n",verifi);
         break;
case 8:  verifi=max_Dfile(F);
         if(verifi==0) printf("file vide\n");
         if(verifi==-1) printf("file n'existe pas\n");
         else printf("le maximum de la file est:%d\n",verifi);
         break;
case 9:  Raz_Dfile(F); break;
case 10: printf("Donner la position :\n"); scanf("%d",&pos);
         supp_pos_Dfile(F,pos);
         break;
case 11: verifi=taille_Dfile(F);
         if(verifi==0) printf("file vide\n");
         if(verifi==-1) printf("file n'existe pas\n");
         else printf("le taille de la file est:%d\n",verifi);
         break;
case 0: printf("-----------------------------\n");
        break;
default :printf("choix incorrecte !\n");
}
}while(choix);
    return 0;
}
