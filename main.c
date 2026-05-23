#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//pour utiliser les chaines de type string et leurs fonctions prédefinies
#include <ctype.h>
//pour utiliser la fonction toupper
#include <time.h>
//pour choisir aleatoirement les questions proposées a partir de notre base de données
#include <unistd.h>
//pour utiliser la fonction 'sleep' qui assure la distinction/sans ordonencement des question proposés
#include <windows.h>
//pour utiliser les fonctions "nice to have" comme beep() et system()
#define taille 500
//taille des chaines qu'on a enregistré dans notre base de données

//----------------------------------------------------------------------------------------------------------------

// les prototypes:
void debut();
// l'affichage de declanchement du jeu
void start();
//commencer le jeu
void edit_score(int niveau);
//ajouter de l'argent avec chaque reponse correcte (selon le niveau, la somme augmente)
void show_score();
//voir le meilleur score d'un joueur qui a deja joué (mais n'a pas quitter le jeu)
void reset_score();
//reinitialisation du meilleur score à 0 (etat initiale)
void help();
// menu d'aide avec résumé du jeu et ses règles
void quit();
// message pour quitter le jeu
void menu();
//le menu ou l'utilisateur choisit s'il veut jouer , quitter, ...
void base_donnees();
// où toutes les questions sont stockées
char choix;
//la lettre que l'utlisateur va taper

//les questions sous forme d'enregistrements
typedef struct question
{
    char q[taille];//la question
    char options[taille];//les 4 propositions sous forme d'une chaine
    char correct;//la lettre de la reponse correcte
}Question;

int passed(Question tab[],int niveau);
//si l'utilisateur a repondu correctement "niveau/numero de reponses correctes" fois, il passe au niveau suivant sinon il échoe et le quiz arrete

Question tab_facile[6],tab_moyen[6],tab_difficile[6] ;
//on a 6 categories (science, sport, technologie, santé générale, geographie et cinema)
//pour chaque categorie on a une question facile, une question moyenne et une question difficle,
//on les met dans des tableaux selon leurs degrés de difficulté

//declaration des variables globales
int high_score=0, score=0;
//'score' est celui de l'utilisateuur qui est en train de jouer
//'high_score' est celui le plus élevé
char name[50],best_name[50];
//le nom de jouer pour le mettreà coté de meilleur score ou si il gagne
int efface=0;
/*on a ajouter la variable 'efface' afin de tester si on a exécuté le jeu, on doit afficher debut
et menu (les deux procédures d'affichage) sans effacer l'Ecran pour la 1ére fois lors du debut de
jeu mais après a chaque retour au menu suite a l'entrer de la lettre m on efface tout ce qui précède
et l'utilisateur ne voit que le menu*/

//----------------------------------------------------------------------------------------------------------------

void debut()
{
    printf("\t\t\t C PROGRAM QUIZ GAME \n");
    printf("\t\t______________________________________\n");
    printf("\t\t\t\      WELCOME \n");
    printf("\t\t\t\t to \n");
    printf("\t\t\t      THE GAME \n");
    printf("\t\t______________________________________\n");
    printf("\t\t______________________________________\n");
    printf("\t\t\t BECOME A MILLIONAIRE!!!! \t\t\t\n");
}

void menu()
{
    if (efface==1)
    {
        system("CLS");//effacer tout ce qui precede pour la lisibilité
    }
    efface=1;
    while (1)
    {
    printf("\t\t______________________________________\n");
    printf("\t\t______________________________________\n");
    printf("\t\t >Press S to start the game \n");
    printf("\t\t >Press V to view the highest score \n");
    printf("\t\t >Press R to reset score \n");
    printf("\t\t >Press H for help \n");
    printf("\t\t >Press Q to quit \n");
    scanf(" %c",&choix);
    choix=toupper(choix);//pour accepter les lettres majuscules ou miniscules
    switch (choix){
    case 'S':
        start();
        return;
        break;
    case 'V':
        show_score();
        break;
    case 'R':
        reset_score();
        break;
    case 'H':
        help();
        break;
    case 'Q':
        quit();
        exit(0);
    default:printf("\n\t Invalid choice! Please press the right key \n ");
    }
    }
}

void start()
{
    system("CLS");
    printf("\t Name of the player= \t");
    scanf(" %s",name);
    score=0;
    sleep(1);
    if (passed(tab_facile,1))
    {
        system("CLS");
        Beep(1000, 300);
        //signal de reussite
        printf("\033[92;107m CONGRATS %s! You have passed to Level: 2!!\033[30;107m",name);
        //message ecrit en vert vif
        printf("\n");
        printf("Your score has reached %d $\n Keep going!!!\n",score);
        if (passed(tab_moyen,2))
        {
            system("CLS");
            Beep(1000, 300);
            printf("\033[92;107m CONGRATS %s! You have passed to Level: 3!!\033[30;107m",name);
            printf("\n");
            printf("Your score has reached %d $\n Stay Strong, Final Push!!!\n",score);
            if (passed(tab_difficile,3))
            {
                system("CLS");
                Beep(1000, 300);
                printf("\n\t");
                printf("\033[92;107m CONGRATULATION! YOU WON THE QUIZ!!!!\033[30;107m");
                printf("\n\t");
                printf("\033[92;107m ~~~~~~~~~~~~~ VICTORY ACHIEVED ~~~~~~~~~~~~~\033[30;107m");
                printf("\n\t");
                printf("Your score has reached %d $ !!!\n",score);
                printf("\n\t\t");
                printf("\033[92;107m %s,YOU BECAME A MILLIONAIRE!!!!\033[30;107m",name);
                printf("\n");
            }
            if (score>=high_score)
            high_score=score;
            strcpy(best_name,name);
            printf("\n\t do you want to play again,%s?\n \t\t >Press M to return to the menu \n",name);
            scanf(" %c",&choix);
            if (toupper(choix)=='M')
                menu();
        }
        else
        {
            if (score>=high_score)
            high_score=score;
            strcpy(best_name,name);
            printf("\n do you want to play again, %s?\n \t\t >Press M to return to the menu \n",name);
            scanf(" %c",&choix);
            if (toupper(choix)=='M')
                menu();
        }
    }
    else
    {
        if (score>=high_score)
            high_score=score;
            strcpy(best_name,name);
            printf("\n do you want to play again,%s?\n \t\t >Press M to return to the menu \n",name);
            scanf(" %c",&choix);
            if (toupper(choix)=='M')
                menu();
    }
}

int passed(Question tab[6],int niveau)
/*'niveau' correspent aussi au nombre des questions minimum que l'utilisateur doit repondre correctement
par exemple: pour passer le niveau 1 if faut avoir au moins une (1) reponse correcte
de meme pour passer le niveau 2 il faut avoir au moins deux (2) reponses correctes
ainsi de suite*/
{
    char reponse;
    int i,j,right=0;
    //i=compteur des questions proposées, j=compteur aleatoire de choix des questions, right=compteur des reponses correctes
    int used[6]={0,0,0,0,0,0};
    //un tableau pour marquer les numero des questions proposées
    time_t t;
    printf("\n\t Let's start with level: %d\n You need to get at least %d out of these 3 questions right to pass to the next level!\n",niveau,niveau);
    base_donnees();
    for (i=1;i<=3;i++)
    {
        srand((unsigned) time(&t));
        do {
            j=rand()%5;
            sleep(1);
        }while (used[j]);
        used[j]=1;
        printf("%s",tab[j].q);
        printf("%s",tab[j].options);
        printf("Your choice:");
        scanf(" %c",&reponse);
        if (toupper(reponse)== tab[j].correct)
        {
            printf("\033[32;107mCorrect!!!\033[30;107m");
            //message ecrit en vert
            printf("\n\n");
            Beep(700,300);
            //signal de reussite
            right++;
            edit_score(niveau);
        }
        else
        {
            printf("\033[31;107mIncorrect answer :(\033[30;107m");
            //message ecrit en rouge
            printf("\n\n");
            Beep(300,500);
            //signal d'échoue
        }
        sleep(1);
    }
    if (right<niveau)
    {
        system("CLS");
        Beep(500,600);
        //signal d'echoue
        printf("\033[34;107m you have failed :(\n Try again next time!\033[30;107m");
        //message ecrit en bleu
        printf("\n");
        printf("Your score is %d $\n",score);
        return 0;
    }
    else
        return 1;
}

void base_donnees()
{
    strcpy(tab_facile[0].q,"Q. Which planet is nicknamed the 'Red Planet'?\n");
    strcpy(tab_facile[0].options,"A) Venus        B) Mars         C) Jupiter        D) Mercury\n");
    tab_facile[0].correct='B';
    strcpy(tab_facile[1].q,"Q. How many players does a football team have on the field?\n");
    strcpy(tab_facile[1].options,"A) 10        B) 9         C) 12        D) 11\n");
    tab_facile[1].correct='D';
    strcpy(tab_facile[2].q,"Q. Who is the founder of Microsoft?\n");
    strcpy(tab_facile[2].options,"A) Steve Jobs        B) Elon Musk         C) Bill Gates        D) Jeff Bezos\n");
    tab_facile[2].correct='C';
    strcpy(tab_facile[3].q,"Q. Which organ pumps blood in the human body?\n");
    strcpy(tab_facile[3].options,"A) The liver        B) The heart         C) The brain        D) The lungs\n");
    tab_facile[3].correct='B';
    strcpy(tab_facile[4].q,"Q. What is the capital of France?\n");
    strcpy(tab_facile[4].options,"A) Lyon        B) Marseille         C) Paris        D) Toulouse\n");
    tab_facile[4].correct='C';
    strcpy(tab_facile[5].q,"Q. Who played the main male role in Titanic?\n");
    strcpy(tab_facile[5].options,"A) Leonardo DiCaprio     B) Daniel Day-Lewis      C) Christian Bale     D) Joaquin Phoenix\n");
    tab_facile[5].correct='A';

    strcpy(tab_moyen[0].q,"Q. What is the chemical formula of water?\n");
    strcpy(tab_moyen[0].options,"A) CO2        B) O2         C) H2O        D) HO2\n");
    tab_moyen[0].correct='C';
    strcpy(tab_moyen[1].q,"Q. In what year did France win its first FIFA World Cup?\n");
    strcpy(tab_moyen[1].options,"A) 1998        B) 1994         C) 2002        D) 2008\n");
    tab_moyen[1].correct='A';
    strcpy(tab_moyen[2].q,"Q. Which company developed the Chrome web browser?\n");
    strcpy(tab_moyen[2].options,"A) Opera        B) Microsoft         C) Mozilla        D) Google\n");
    tab_moyen[2].correct='D';
    strcpy(tab_moyen[3].q,"Q. Which vitamin is produced by the skin when exposed to sunlight?\n");
    strcpy(tab_moyen[3].options,"A) Vitamin A        B) Vitamin B12         C) Vitamin C        D) Vitamin D\n");
    tab_moyen[3].correct='D';
    strcpy(tab_moyen[4].q,"Q. What is the largest desert in the world?\n");
    strcpy(tab_moyen[4].options,"A) Sahara        B) Gobi         C) Kalahari        D) Atacama\n");
    tab_moyen[4].correct='A';
    strcpy(tab_moyen[5].q,"Q. Which director is known for the film Inception?\n");
    strcpy(tab_moyen[5].options,"A) Quentin Tarantino     B) Christopher Nolan      C) David Fincher     D) Ridley Scott\n");
    tab_moyen[5].correct='B';

    strcpy(tab_difficile[0].q,"Q. Which subatomic particle has a negative charge?\n");
    strcpy(tab_difficile[0].options,"A) Proton        B) Neutron         C) Positron        D) Electron\n");
    tab_difficile[0].correct='D';
    strcpy(tab_difficile[1].q,"Q. Which runner holds the world record for the 100 meters in athletics (men)?\n");
    strcpy(tab_difficile[1].options,"A) Carl Lewis     B) Usain Bolt      C) Tyson Gay     D) Justin Gatlin\n");
    tab_difficile[1].correct='B';
    strcpy(tab_difficile[2].q,"Q. What was the world's first decentralized cryptocurrency?\n");
    strcpy(tab_difficile[2].options,"A) Bitcoin        B) Ethereum         C) Litecoin        D) Ripple\n");
    tab_difficile[2].correct='A';
    strcpy(tab_difficile[3].q,"Q. What is the scientific name for a red blood cell?\n");
    strcpy(tab_difficile[3].options,"A) Leukocyte      B) Hemoglobin      C) Erythrocyte     D) Thrombocyte\n");
    tab_difficile[3].correct='C';
    strcpy(tab_difficile[4].q,"Q. In which country is Mount Fuji located?\n");
    strcpy(tab_difficile[4].options,"A) China        B) Japan         C) South Korea        D) Thailand\n");
    tab_difficile[4].correct='B';
    strcpy(tab_difficile[5].q,"Q. Which film won the Oscar for Best Picture in 2020?\n");
    strcpy(tab_difficile[5].options,"A) Joker        B) Parasite         C) 1917        D) Once Upon a Time in Hollywood\n");
    tab_difficile[5].correct='B';

}

void show_score()
{
    system("CLS");
    printf("\n\t     =========== HIGHEST SCORE ==========\n");
    printf("\t**********************************************\n");
    printf("\t %s has secured the Highest Score %d\n",best_name,high_score);
    printf("\t**********************************************\n");
    printf("\t\t >Press M to return to the menu \n");
    scanf(" %c",&choix);
    if (toupper(choix)=='M')
    menu();
}

void reset_score()
{
    system("CLS");
    printf("\n\t Reseting the highest score... \n");
    sleep(2);
    high_score=0;
    strcpy(best_name,"");
    printf("\n\t The highest score after reset = %d\n\n",high_score);
    printf("\t\t >Press M to return to the menu \n");
    scanf(" %c",&choix);
    if (toupper(choix)=='M')
    menu();
}

void edit_score(int n)
//n le niveau de difficulte n in {1,2,3}
{
    switch (n)
    {
        case 1:
            score=score+100000;
            break;
        case 2:
            score=score+150000;
            break;
        case 3:
            score=score+200000;
            break;
    }
}

void help()
{
    system("CLS");
    printf("\n\t========== HOW TO PLAY? ==========\n");
    printf("\n\t 1. Press S to start the game.\n");
    printf("\n\t 2. Answer the randomized questions from different categories correctly to add money to your prize.\n");
    printf("\n\t 3. Your highest score will be saved.\n");
    printf("\n\t 4. Press Q anytime to quit.\n\n");
    printf("\t\t >Press M to return to the menu \n");
    scanf(" %c",&choix);
    if (toupper(choix)=='M')
        menu();
}

void quit()
{
    system("CLS");
    printf("\n\t Thank you for playing!\n");
    printf("\n\t\t Goodbye!\n");
}

void main()
{
    system("color F0");
    debut();
    menu();
}
