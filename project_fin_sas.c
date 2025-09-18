#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct mot {
    char valeur[50];
    int occurrence;
    int longueur;
    int position[50];
    int nposition;
};

struct mot dictionnaire[2000];
int nmot = 0;

void netoyertext(char word[]) {
    char temp[2000];
    int j = 0;
    for (int i = 0; word[i] != '\0'; i++) {
        if (!ispunct(word[i])) {
            temp[j++] = tolower(word[i]);
        }
    }
    temp[j] = '\0';
    strcpy(word, temp);
}

int analysetext(struct mot dictionnaire[], char word[], int nmot) {
    char *text = strtok(word, " ");
    int pos = 1;

    while (text != NULL) {
        int trouve = 0;
        for (int i = 0; i < nmot; i++) {
            if (strcmp(dictionnaire[i].valeur, text) == 0) {
                dictionnaire[i].occurrence++;
                dictionnaire[i].position[dictionnaire[i].nposition++] = pos;
                trouve = 1;
                break;
            }
        }
        if (!trouve) {
            strcpy(dictionnaire[nmot].valeur, text);
            dictionnaire[nmot].longueur = strlen(text);
            dictionnaire[nmot].occurrence = 1;
            dictionnaire[nmot].position[0] = pos;
            dictionnaire[nmot].nposition = 1;
            nmot++;
        }
        pos++;
        text = strtok(NULL, " ");
    }
    return nmot;
}

void afficherdectionaire(struct mot dictionnaire[], int nmot) {
    printf("--------dictionnaire------------\n");
    for (int i = 0; i < nmot; i++) {
        printf("mot : %s\n", dictionnaire[i].valeur);
        printf("longueur : %d\n", dictionnaire[i].longueur);
        printf("occurrence : %d\n", dictionnaire[i].occurrence);
        printf("positions : ");
        for (int j = 0; j < dictionnaire[i].nposition; j++)
            printf("%d ", dictionnaire[i].position[j]);
        printf("\n");
    }
}

void rechercherdectionnaire(struct mot dictionnaire[], char cherchmot[], int nmot) {
    int trouve = 0;
    for (int i = 0; i < nmot; i++) {
        if (strcmp(cherchmot, dictionnaire[i].valeur) == 0) {
            printf("mot trouve : %s\n", dictionnaire[i].valeur);
            printf("occurrence : %d\n", dictionnaire[i].occurrence);
            printf("longueur : %d\n", dictionnaire[i].longueur);
            printf("positions : ");
            for (int j = 0; j < dictionnaire[i].nposition; j++)
                printf("%d ", dictionnaire[i].position[j]);
            printf("\n");
            trouve = 1;
            break;
        }
    }
    if (!trouve) printf("mot non trouve.\n");
}

int recherchepartial(struct mot dictionnaire[], int nmot, char mchercher[]) {
    int trouve = 0;
    for (int i = 0; i < nmot; i++) {
        if (strstr(dictionnaire[i].valeur, mchercher) != NULL) {
            printf("mot trouve : %s\n", dictionnaire[i].valeur);
            printf("longueur : %d\n", dictionnaire[i].longueur);
            printf("occurence : %d\n",dictionnaire[i].occurrence);
            printf("positions : ");
            for (int j = 0; j < dictionnaire[i].nposition; j++)
                printf("%d ", dictionnaire[i].position[j]);
            trouve = 1;
        }
    }
    if (!trouve) printf("mot non trouve.\n");
    return trouve;
}

void trierperorder(struct mot dictionnaire[], int nmot) {
    struct mot temp;
    for (int i = 0; i < nmot - 1; i++)
        for (int j = i + 1; j < nmot; j++)
            if (strcmp(dictionnaire[i].valeur, dictionnaire[j].valeur) > 0) {
                temp = dictionnaire[i];
                dictionnaire[i] = dictionnaire[j];
                dictionnaire[j] = temp;
            }
}

void trierperfrequence(struct mot dictionnaire[], int nmot) {
    struct mot temp;
    for (int i = 0; i < nmot - 1; i++)
        for (int j = i + 1; j < nmot; j++)
            if (dictionnaire[i].occurrence < dictionnaire[j].occurrence) {
                temp = dictionnaire[i];
                dictionnaire[i] = dictionnaire[j];
                dictionnaire[j] = temp;
            }
}

void trierparlongueur(struct mot dictionnaire[], int nmot) {
    struct mot temp;
    for (int i = 0; i < nmot - 1; i++)
        for (int j = i + 1; j < nmot; j++)
            if (dictionnaire[i].longueur < dictionnaire[j].longueur) {
                temp = dictionnaire[i];
                dictionnaire[i] = dictionnaire[j];
                dictionnaire[j] = temp;
            }
}

int palindrom(char word[]) {
    int debut = 0, fin = strlen(word) - 1;
    while (debut < fin) {
        if (word[debut] != word[fin]) return 0;
        debut++; fin--;
    }
    return 1;
}

void triermot(char mot[]) {
    int len = strlen(mot);
    for (int i = 0; i < len - 1; i++)
        for (int j = i + 1; j < len; j++)
            if (mot[i] > mot[j]) {
                char temp = mot[i];
                mot[i] = mot[j];
                mot[j] = temp;
            }
}

int est_anagrame(char mot1[], char mot2[]) {
    if (strlen(mot1) != strlen(mot2)) return 0;
    char copie1[50], copie2[50];
    strcpy(copie1, mot1);
    strcpy(copie2, mot2);
    triermot(copie1);
    triermot(copie2);
    return strcmp(copie1, copie2) == 0;
}

void afficher_anagrame(struct mot dictionnaire[], int nmot, char word[]) {
    int trouve = 0;
    for (int i = 0; i < nmot; i++)
        if ((strcmp(word, dictionnaire[i].valeur) != 0) &&
            est_anagrame(word, dictionnaire[i].valeur)) {
            printf("%s\n", dictionnaire[i].valeur);
            trouve = 1;
        }
    if (!trouve) printf("anagrame pas trouvee.\n");
}

void statistiques_globales(struct mot dictionnaire[], int nmot) {
    int totalmots=0, totallongue=0, maxlongue=0, minlongue=999, maxoccurence=0;
    char motpluslong[50]="", motpluscourt[50]="", motfrequent[50]="";

    for(int i=0;i<nmot;i++){
        totalmots += dictionnaire[i].occurrence;
        totallongue += dictionnaire[i].longueur * dictionnaire[i].occurrence;
        if(dictionnaire[i].longueur>maxlongue){
            maxlongue=dictionnaire[i].longueur;
            strcpy(motpluslong,dictionnaire[i].valeur);
        }
        if(dictionnaire[i].longueur<minlongue){
            minlongue=dictionnaire[i].longueur;
            strcpy(motpluscourt,dictionnaire[i].valeur);
        }
        if(dictionnaire[i].occurrence>maxoccurence){
            maxoccurence=dictionnaire[i].occurrence;
            strcpy(motfrequent,dictionnaire[i].valeur);
        }
    }
    float diversite = (float)nmot/(float)totalmots;
    float longueur_moyen = (float)totallongue/(float)totalmots;

    printf("Nombre total des mots : %d\n", totalmots);
    printf("Nombre de mots uniques : %d\n", nmot);
    printf("Diversité lexicale : %.2f\n", diversite);
    printf("Longueur moyenne : %.2f\n", longueur_moyen);
    printf("Mot le plus long : %s\n", motpluslong);
    printf("Mot le plus court : %s\n", motpluscourt);
    printf("Mot le plus fréquent : %s\n", motfrequent);
}

void nuage_de_mots(struct mot dictionnaire[], int nmot) {
    printf("Nuage de mots :\n");
    for(int i=0;i<nmot;i++){
        printf("%s : ",dictionnaire[i].valeur);
        for(int j=0;j<dictionnaire[i].occurrence;j++)
            printf("*");
        printf("\n");
    }
}

int main() {
    int choix;
    char text[2000], mot[50];

    do {
            printf(" menu : \n");
        printf("1. saisir un texte et analyser :\n");
        printf("2. afficher tous les mots : \n");
        printf("3. rechercher un mot exact : \n");
        printf("4. rechercher un mot partiel : \n");
        printf("5. trier les mots : \n");
        printf("6. statistiques globales : \n");
        printf("7. analyses : \n");
        printf("0. quitter .\n");
        printf("saisir votre choix : ");
        scanf("%d",&choix);
        getchar();
        switch(choix) {
            case 1:
                printf("Entrez le texte : ");
                fgets(text,2000,stdin);
                text[strcspn(text,"\n")]=0;
                netoyertext(text);
                nmot = analysetext(dictionnaire,text,nmot);
                break;
            case 2:
                afficherdectionaire(dictionnaire,nmot);
                break;
            case 3:
                printf("Entrez le mot a rechercher : ");
                scanf("%s",mot);
                rechercherdectionnaire(dictionnaire,mot,nmot);
                break;
            case 4:
                printf("Entrez le mot partiel : ");
                scanf("%s",mot);
                recherchepartial(dictionnaire,nmot,mot);
                break;
            case 5: {
                int choix_tri;
                printf("1. Par ordre alphabétique\n2. Par fréquence\n3. Par longueur\n");
                scanf("%d",&choix_tri);
                switch(choix_tri){
                    case 1: trierperorder(dictionnaire,nmot); break;
                    case 2: trierperfrequence(dictionnaire,nmot); break;
                    case 3: trierparlongueur(dictionnaire,nmot); break;
                    default: printf("Choix invalide.\n"); break;
                }
                afficherdectionaire(dictionnaire,nmot);
                break;
            }
            case 6:
                statistiques_globales(dictionnaire,nmot);
                break;
            case 7: {
                int choix_ana;
                printf("1. Nuage de mots\n2. Palindromes\n3. Anagrammes d'un mot\n");
                scanf("%d",&choix_ana);
                getchar();
                switch(choix_ana){
                    case 1: nuage_de_mots(dictionnaire,nmot); break;
                    case 2:
                        printf("Palindromes :\n");
                        for(int i=0;i<nmot;i++)
                            if(palindrom(dictionnaire[i].valeur))
                                printf("%s\n",dictionnaire[i].valeur);
                        break;
                    case 3:
                        printf("Entrez le mot pour ses anagrammes : ");
                        scanf("%s",mot);
                        afficher_anagrame(dictionnaire,nmot,mot);
                        break;
                    default: printf("Choix invalide.\n"); break;
                }
                break;
            }
            case 8:
                printf("Au revoir !\n");
                break;
            default:
                printf("Choix invalide.\n");
                break;
        }
    } while(choix != 8);

    return 0;
}
