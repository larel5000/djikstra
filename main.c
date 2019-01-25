#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct etat{
    int poids;    // distance entre origine et noeud
    bool pop;    // true si il est permanent false si non
} etat;

int min(etat * tab, int n); //noeud ayant le plus petit poids du tableau permanent

int main()
{
    int n, i, j;

    printf("Entrez le nombre de noeuds de votre graphe:\n");
    scanf("%d",&n);

    etat *tab_etat = malloc(n * sizeof(etat));

    int *pere = malloc(n * sizeof(int));

    int **mat = malloc(n * sizeof(int*));
    for(i = 0; i < n; i++)
        mat[i] = malloc(n * sizeof(int));

    //initialisation

    printf("Entrez la distance de: \n");
    for(i = 0; i < n; i++)
        for(j = 0; j < n; j++)
    {
        printf("%d ---> %d: ",i+1,j+1);
        scanf("%d", &mat[i][j]);
    }

     for(i = 0; i < n; i++)
     {
         tab_etat[i].poids = -1;    //n'est pas temporaire
         tab_etat[i].pop = false;   //n'est pas permanent
     }

     for(i = 0; i < n; i++)
        pere[i] = i;        //le pere de i est lui meme

     //dijkstra

    int a, temp = 0;
    printf("Entrez le noeud dont on souhaite connaitre l'arbre de recouvrement: ");
    scanf("%d",&a);

    tab_etat[a-1].poids = 0;

    while( temp != n) //tant que permanent n'est pas plein
    {
        int m = min(tab_etat,n); //plus petit du tableau temporaire

        if(tab_etat[m].pop == false) //mettre dans le tableau permanant
        {
            tab_etat[m].pop = true;
            temp++;         //nbre d'element du tableau permanent
        }


        for(j = 0; j < n; j++)
            if(mat[m][j] != 0 && tab_etat[j].pop == false ) //si m---> j existe et que j n'est pas permanent
            {
                if (tab_etat[j].poids == -1) //s'il n'appartient pas au tableau temporaire
                {
                    tab_etat[j].poids = mat[m][j] + tab_etat[m].poids; //ajout au tableau permanent et calcul de distance
                    pere[j] = m;
                }

                else if( mat[m][j] + tab_etat[m].poids <  tab_etat[j].poids )// s'il appartient et le poids est ameliorante
                {
                    tab_etat[j].poids = mat[m][j] + tab_etat[m].poids; //nouveau poids
                    pere[j] = m;                //nouveau pere
                }

            }
    }

    printf("Les arcs de l'arbre des plus court chemin partant de %d est:\n",a);
    for(j = 0; j < n; j++)
        printf("%d ---> %d\n",pere[j]+1,j+1); //affichage pere ---> noeud


    return 0;
}

int min(etat * tab, int n)   //noeud ayant le plus petit poids du tableau permanent
{
    int i = 0;
    int m;

    while(i!=n)
    {
        if(tab[i].poids >= 0 && tab[i].pop == false) //trouver le premier element de la liste permanente
        {
            m = i;
            break;
        }

        i++;
    }

    i = m+1;
    while(i!=n)
    {
        if(tab[m].poids > tab[i].poids && tab[i].poids >= 0 && tab[i].pop == false ) //cherche le min
            m = i;
        i++;
    }
    return m;
}
