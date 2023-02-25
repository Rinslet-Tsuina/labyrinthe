#pragma once
//TISSERAND Orlane
//Visual Studio 2019
#include <iostream>
#include <algorithm>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <time.h>

using namespace std;
void synchro(double duree)
{
	static clock_t jalon = clock();
	jalon = jalon + (clock_t)(duree * CLOCKS_PER_SEC);;
	while (clock() < jalon);
}
class Labyrinthe
{
private:
	int nb_colonnes; //nombre de colonnes longueur
	int nb_lignes; //nombre de lignes largeur
	int taille;
	char* grille;
	int* Pile;
	int Sommet;
	int idRobotA;
	int idRobotB;
	string aff;
	int posA = 0;
	int dernPos[4];
	// Retourne le caractère à afficher pour la valeur val.
	char getAff(char val) { return aff[val]; }
	//empile un entier 
	void push(int x)
	{
		Pile[Sommet] = x;
		Sommet = Sommet + 1;
	}

	//dépile un entier et le retourne 
	int pop()
	{
		Sommet = Sommet - 1;
		int x = Pile[Sommet];
		Pile[Sommet] = -1;
		return x;
	}
	//variables contenant les sprites et la position ou mettre le sprite
	SDL_Rect position;
	SDL_Texture* sol;
	SDL_Texture* quatre;
	SDL_Texture* Bmur;
	SDL_Texture* Hmur;
	SDL_Texture* Dmur;
	SDL_Texture* Gmur;
	SDL_Texture* coinBD;
	SDL_Texture* coinBG;
	SDL_Texture* coinHD;
	SDL_Texture* coinHG;
	SDL_Texture* verti;
	SDL_Texture* hori;
	SDL_Texture* BDmur;
	SDL_Texture* BGmur;
	SDL_Texture* HGmur;
	SDL_Texture* HDmur;
	SDL_Texture* murDGB;
	SDL_Texture* murDHB;
	SDL_Texture* murDHG;
	SDL_Texture* murHGB;
	SDL_Texture* robotA;
	SDL_Texture* robotB;
	SDL_Texture* vide;
	int* dist(int depart);
	//methode pour la bibliotheque SDL
	int NombreMur(int id);//donne le nombre de mur voisin a une case
	void afficheSDLMur(SDL_Renderer* rend, int id);//affiche les sprites des murs
	void afficheSDLBord(SDL_Renderer* rend);//affiche les sprites des bords

public:
	Labyrinthe(int nLignes, int nColonnes, SDL_Renderer* rend);//creer un labyrinthe vide 
	Labyrinthe(int nLignes, int nColonnes, double density, SDL_Renderer* rend);
	Labyrinthe(char* descr, SDL_Renderer* rend);
	Labyrinthe(int nLignes, int nColonnes);//creer un labyrinthe vide 
	Labyrinthe(int nLignes, int nColonnes, double density);
	Labyrinthe(char* descr);
	~Labyrinthe();

	int getID(int ligne, int colonne) { return (ligne * getNbColonnes() + colonne); }
	int getLigne(int id);
	int getCol(int id);
	void modifie(int ligne, int colonne, char x);
	void modifie(int id, char x);
	int lit(int ligne, int colonne) { return grille[ligne * getNbColonnes() + colonne]; }
	int lit(int id) { return grille[id]; }
	int getNbLignes() { return nb_lignes; }
	int getNbColonnes() { return nb_colonnes; }
	void affiche();
	void setAff(string motifs) { aff = motifs; }

	bool connexe();
	void genLaby(int k);
	int distMin(int id1, int id2);
	

	int getIdRobotA() { return idRobotA; }
	int getIdRobotB() { return idRobotB; }
	void setIdRobotA(int id) { idRobotA = id; }
	void setIdRobotB(int id) { idRobotB = id; }

	int caseRandom();
	bool deplaceRobotA(int algo);
	bool deplaceRobotB(int algo);

	bool deplaceRobotA1();
	bool deplaceRobotA2();
	bool deplaceRobotB1();
	bool deplaceRobotB2();
	bool PredFin();

	void visualisation();
	int course(int timeout, bool silent, bool random, int algoA, int algoB);
	int evalue(int nCourses, int timeOut, int algoA, int algoB);

	//affichage des sprites dans une fenetre
	void afficheSDL(SDL_Renderer *rend);
	//methodes modifier pour afficher une partie 
	void visualisationSDL(SDL_Renderer *rend);
	int courseSDL(int timeout, bool silent, bool random, int algoA, int algoB, SDL_Renderer* rend);
};
//autres
Labyrinthe::Labyrinthe(int nLignes, int nColonnes, SDL_Renderer* rend)
{
	//initialisation des images en textures
	SDL_Surface* temp = IMG_Load("sol.png");
	sol = SDL_CreateTextureFromSurface(rend, temp);
	temp = IMG_Load("quatre.png");
	quatre = SDL_CreateTextureFromSurface(rend, temp);
	temp = IMG_Load("vide.png");
	vide = SDL_CreateTextureFromSurface(rend, temp);
	temp = IMG_Load("droite.png");
	Dmur = SDL_CreateTextureFromSurface(rend, temp);
	temp = IMG_Load("haut.png");
	Hmur = SDL_CreateTextureFromSurface(rend, temp);
	temp = IMG_Load("gauche.png");
	Gmur = SDL_CreateTextureFromSurface(rend, temp);
	temp = IMG_Load("bas.png");
	Bmur = SDL_CreateTextureFromSurface(rend, temp);
	temp = IMG_Load("hautDroite.png");
	HDmur = SDL_CreateTextureFromSurface(rend, temp);
	temp = IMG_Load("hautGauche.png");
	HGmur = SDL_CreateTextureFromSurface(rend, temp);
	temp = IMG_Load("basDroite.png");
	BDmur = SDL_CreateTextureFromSurface(rend, temp);
	temp = IMG_Load("basGauche.png");
	BGmur = SDL_CreateTextureFromSurface(rend, temp);
	temp = IMG_Load("coinHD.png");
	coinHD = SDL_CreateTextureFromSurface(rend, temp);
	temp = IMG_Load("coinHG.png");
	coinHG = SDL_CreateTextureFromSurface(rend, temp);
	temp = IMG_Load("coinBD.png");
	coinBD = SDL_CreateTextureFromSurface(rend, temp);
	temp = IMG_Load("coinBG.png");
	coinBG = SDL_CreateTextureFromSurface(rend, temp);
	temp = IMG_Load("Hori.png");
	hori = SDL_CreateTextureFromSurface(rend, temp);
	temp = IMG_Load("verti.png");
	verti = SDL_CreateTextureFromSurface(rend, temp);
	temp = IMG_Load("murDGB.png");
	murDGB = SDL_CreateTextureFromSurface(rend, temp);
	temp = IMG_Load("murDHB.png");
	murDHB = SDL_CreateTextureFromSurface(rend, temp);
	temp = IMG_Load("murDHG.png");
	murDHG = SDL_CreateTextureFromSurface(rend, temp);
	temp = IMG_Load("murHGB.png");
	murHGB = SDL_CreateTextureFromSurface(rend, temp);
	temp = IMG_Load("robotA.png");
	robotA = SDL_CreateTextureFromSurface(rend, temp);
	temp = IMG_Load("robotB.png");
	robotB = SDL_CreateTextureFromSurface(rend, temp);
	setAff(" XAB.");
	nb_lignes = nLignes;
	nb_colonnes = nColonnes;
	grille = new char[getNbColonnes() * getNbLignes()];
	Pile = new int[getNbColonnes() * getNbLignes()];
	for (int l = 0; l < getNbLignes(); l++)
	{
		for (int c = 0; c < getNbColonnes(); ++c)
		{
			modifie(l, c, 0);
		}
	}
	idRobotA = getID(0, 0);
	idRobotB = getID(getNbLignes() - 1, getNbColonnes() - 1);
	//initialisation des valeurs des pixels pour la bibliotheque SDL
	position.x = 0;
	position.y = 0;
	position.h = 32;
	position.w = 32;
	//destruction des textures créés
	SDL_FreeSurface(temp);
}
Labyrinthe::Labyrinthe(int nLignes, int nColonnes, double density, SDL_Renderer* rend)
{
	//initialisation des images en textures
	SDL_Surface* temp = IMG_Load("sol.png");
	sol = SDL_CreateTextureFromSurface(rend, temp);
	temp = IMG_Load("quatre.png");
	quatre = SDL_CreateTextureFromSurface(rend, temp);
	temp = IMG_Load("vide.png");
	vide = SDL_CreateTextureFromSurface(rend, temp);
	temp = IMG_Load("droite.png");
	Dmur = SDL_CreateTextureFromSurface(rend, temp);
	temp = IMG_Load("haut.png");
	Hmur = SDL_CreateTextureFromSurface(rend, temp);
	temp = IMG_Load("gauche.png");
	Gmur = SDL_CreateTextureFromSurface(rend, temp);
	temp = IMG_Load("bas.png");
	Bmur = SDL_CreateTextureFromSurface(rend, temp);
	temp = IMG_Load("hautDroite.png");
	HDmur = SDL_CreateTextureFromSurface(rend, temp);
	temp = IMG_Load("hautGauche.png");
	HGmur = SDL_CreateTextureFromSurface(rend, temp);
	temp = IMG_Load("basDroite.png");
	BDmur = SDL_CreateTextureFromSurface(rend, temp);
	temp = IMG_Load("basGauche.png");
	BGmur = SDL_CreateTextureFromSurface(rend, temp);
	temp = IMG_Load("coinHD.png");
	coinHD = SDL_CreateTextureFromSurface(rend, temp);
	temp = IMG_Load("coinHG.png");
	coinHG = SDL_CreateTextureFromSurface(rend, temp);
	temp = IMG_Load("coinBD.png");
	coinBD = SDL_CreateTextureFromSurface(rend, temp);
	temp = IMG_Load("coinBG.png");
	coinBG = SDL_CreateTextureFromSurface(rend, temp);
	temp = IMG_Load("Hori.png");
	hori = SDL_CreateTextureFromSurface(rend, temp);
	temp = IMG_Load("verti.png");
	verti = SDL_CreateTextureFromSurface(rend, temp);
	temp = IMG_Load("murDGB.png");
	murDGB = SDL_CreateTextureFromSurface(rend, temp);
	temp = IMG_Load("murDHB.png");
	murDHB = SDL_CreateTextureFromSurface(rend, temp);
	temp = IMG_Load("murDHG.png");
	murDHG = SDL_CreateTextureFromSurface(rend, temp);
	temp = IMG_Load("murHGB.png");
	murHGB = SDL_CreateTextureFromSurface(rend, temp);
	temp = IMG_Load("robotA.png");
	robotA = SDL_CreateTextureFromSurface(rend, temp);
	temp = IMG_Load("robotB.png");
	robotB = SDL_CreateTextureFromSurface(rend, temp);
	setAff(" XAB.");
	nb_lignes = nLignes;
	nb_colonnes = nColonnes;
	grille = new char[getNbColonnes() * getNbLignes()];
	Pile = new int[getNbColonnes() * getNbLignes()];
	for (int l = 0; l < getNbLignes(); l++)
	{
		for (int c = 0; c < getNbColonnes(); ++c)
		{
			modifie(l, c, 0);
		}
	}
	idRobotA = getID(0, 0);
	idRobotB = getID(getNbLignes() - 1, getNbColonnes() - 1);
	genLaby(getNbLignes() * getNbColonnes() * density);
	//initialisation des valeurs des pixels pour la bibliotheque SDL
	position.x = 0;
	position.y = 0;
	position.h = 32;
	position.w = 32;
	//destruction des textures créés
	SDL_FreeSurface(temp);
}
Labyrinthe::Labyrinthe(char* descr, SDL_Renderer* rend)
{
	//initialisation des images en textures
	SDL_Surface* temp = IMG_Load("sol.png");
	sol = SDL_CreateTextureFromSurface(rend, temp);
	temp = IMG_Load("quatre.png");
	quatre = SDL_CreateTextureFromSurface(rend, temp);
	temp = IMG_Load("vide.png");
	vide = SDL_CreateTextureFromSurface(rend, temp);
	temp = IMG_Load("droite.png");
	Dmur = SDL_CreateTextureFromSurface(rend, temp);
	temp = IMG_Load("haut.png");
	Hmur = SDL_CreateTextureFromSurface(rend, temp);
	temp = IMG_Load("gauche.png");
	Gmur = SDL_CreateTextureFromSurface(rend, temp);
	temp = IMG_Load("bas.png");
	Bmur = SDL_CreateTextureFromSurface(rend, temp);
	temp = IMG_Load("hautDroite.png");
	HDmur = SDL_CreateTextureFromSurface(rend, temp);
	temp = IMG_Load("hautGauche.png");
	HGmur = SDL_CreateTextureFromSurface(rend, temp);
	temp = IMG_Load("basDroite.png");
	BDmur = SDL_CreateTextureFromSurface(rend, temp);
	temp = IMG_Load("basGauche.png");
	BGmur = SDL_CreateTextureFromSurface(rend, temp);
	temp = IMG_Load("coinHD.png");
	coinHD = SDL_CreateTextureFromSurface(rend, temp);
	temp = IMG_Load("coinHG.png");
	coinHG = SDL_CreateTextureFromSurface(rend, temp);
	temp = IMG_Load("coinBD.png");
	coinBD = SDL_CreateTextureFromSurface(rend, temp);
	temp = IMG_Load("coinBG.png");
	coinBG = SDL_CreateTextureFromSurface(rend, temp);
	temp = IMG_Load("Hori.png");
	hori = SDL_CreateTextureFromSurface(rend, temp);
	temp = IMG_Load("verti.png");
	verti = SDL_CreateTextureFromSurface(rend, temp);
	temp = IMG_Load("murDGB.png");
	murDGB = SDL_CreateTextureFromSurface(rend, temp);
	temp = IMG_Load("murDHB.png");
	murDHB = SDL_CreateTextureFromSurface(rend, temp);
	temp = IMG_Load("murDHG.png");
	murDHG = SDL_CreateTextureFromSurface(rend, temp);
	temp = IMG_Load("murHGB.png");
	murHGB = SDL_CreateTextureFromSurface(rend, temp);
	temp = IMG_Load("robotA.png");
	robotA = SDL_CreateTextureFromSurface(rend, temp);
	temp = IMG_Load("robotB.png");
	robotB = SDL_CreateTextureFromSurface(rend, temp);
	setAff(" XAB.");
	nb_lignes = descr[0];
	nb_colonnes = descr[1];
	grille = new char[getNbColonnes() * getNbLignes()];
	Pile = new int[getNbColonnes() * getNbLignes()];
	for (int l = 0; l < getNbLignes(); l++)
	{
		for (int c = 0; c < getNbColonnes(); ++c)
		{
			modifie(l, c, descr[getID(l, c) + 2]);
		}
	}
	idRobotA = getID(0, 0);
	idRobotB = getID(getNbLignes() - 1, getNbColonnes() - 1);
	//initialisation des valeurs des pixels pour la bibliotheque SDL
	position.x = 0;
	position.y = 0;
	position.h = 32;
	position.w = 32;
	//destruction des textures créés
	SDL_FreeSurface(temp);
}
Labyrinthe::Labyrinthe(int nLignes, int nColonnes)
{
	setAff(" XAB.");
	nb_lignes = nLignes;
	nb_colonnes = nColonnes;
	grille = new char[getNbColonnes() * getNbLignes()];
	Pile = new int[getNbColonnes() * getNbLignes()];
	for (int l = 0; l < getNbLignes(); l++)
	{
		for (int c = 0; c < getNbColonnes(); ++c)
		{
			modifie(l, c, 0);
		}
	}
	idRobotA = getID(0, 0);
	idRobotB = getID(getNbLignes() - 1, getNbColonnes() - 1);
}
Labyrinthe::Labyrinthe(int nLignes, int nColonnes, double density)
{
	setAff(" XAB.");
	nb_lignes = nLignes;
	nb_colonnes = nColonnes;
	grille = new char[getNbColonnes() * getNbLignes()];
	Pile = new int[getNbColonnes() * getNbLignes()];
	for (int l = 0; l < getNbLignes(); l++)
	{
		for (int c = 0; c < getNbColonnes(); ++c)
		{
			modifie(l, c, 0);
		}
	}
	idRobotA = getID(0, 0);
	idRobotB = getID(getNbLignes() - 1, getNbColonnes() - 1);
	genLaby(getNbLignes() * getNbColonnes() * density);
}
Labyrinthe::Labyrinthe(char* descr)
{
	setAff(" XAB.");
	nb_lignes = descr[0];
	nb_colonnes = descr[1];
	grille = new char[getNbColonnes() * getNbLignes()];
	Pile = new int[getNbColonnes() * getNbLignes()];
	for (int l = 0; l < getNbLignes(); l++)
	{
		for (int c = 0; c < getNbColonnes(); ++c)
		{
			modifie(l, c, descr[getID(l, c) + 2]);
		}
	}
	idRobotA = getID(0, 0);
	idRobotB = getID(getNbLignes() - 1, getNbColonnes() - 1);
}
Labyrinthe::~Labyrinthe()
{
	SDL_DestroyTexture(sol);
	SDL_DestroyTexture(vide);
	SDL_DestroyTexture(quatre);
	SDL_DestroyTexture(robotA);
	SDL_DestroyTexture(robotB);
	SDL_DestroyTexture(hori);
	SDL_DestroyTexture(verti);
	SDL_DestroyTexture(Hmur);
	SDL_DestroyTexture(Bmur);
	SDL_DestroyTexture(Gmur);
	SDL_DestroyTexture(Dmur);
	SDL_DestroyTexture(BDmur);
	SDL_DestroyTexture(BGmur);
	SDL_DestroyTexture(HGmur);
	SDL_DestroyTexture(HDmur);
	SDL_DestroyTexture(coinBD);
	SDL_DestroyTexture(coinBG);
	SDL_DestroyTexture(coinHD);
	SDL_DestroyTexture(coinHG);
	SDL_DestroyTexture(murDGB);
	SDL_DestroyTexture(murDHB);
	SDL_DestroyTexture(murDHG);
	SDL_DestroyTexture(murHGB);
	//delete[] grille;
	//delete[] Pile;
}

//methode partie 1 et 2
//retroune la ligne d'une case dont l'identifiant est donne
int Labyrinthe::getLigne(int  id)
{
	int ligne=0;
	if (id >= 0 && id < getNbLignes() * getNbColonnes())
	{
		ligne = id / getNbColonnes();
	}
	return ligne;
}
//retroune la colonne d'une case dont l'identifiant est donne
int Labyrinthe::getCol(int  id)
{
	int col=0;
	if (id >= 0 && id < getNbColonnes() * getNbLignes())
	{
		col = id % getNbColonnes();
	}
	return col;
}
//place la valeur x dans la case(i,j)
void Labyrinthe::modifie(int ligne, int colonne, char x)
{
	if (ligne >= 0 && ligne < getNbLignes())
	{
		if (colonne >= 0 && colonne < getNbColonnes())
		{
			grille[ligne * getNbColonnes() + colonne] = x;
		}
	}
}
void Labyrinthe::modifie(int id, char x)
{
	if (getLigne(id) >= 0 && getLigne(id) < getNbLignes())
	{
		if (getCol(id) >= 0 && getCol(id) < getNbColonnes())
		{
			grille[id] = x;
		}
	}
}
//affiche la grille
void Labyrinthe::affiche()
{
	for (int l = 0; l < getNbLignes() + 2; l++)
	{
		for (int c = 0; c < getNbColonnes() + 2; c++)
		{
			if (l == 0 || l == getNbLignes() + 1 || c == 0 || c == getNbColonnes() + 1)
			{
				printf("%c", getAff(4));
			}
			else
			{
				if (lit(l - 1, c - 1) == 1)
				{
					printf("%c", getAff(1));
				}
				if (lit(l - 1, c - 1) == 0)
				{
					printf("%c", getAff(0));
				}
				if (lit(l - 1, c - 1) == 2)
				{
					printf("%c", getAff(2));
				}
				if (lit(l - 1, c - 1) == 3)
				{
					printf("%c", getAff(3));
				}
			}
		}
		printf("\n");
	}
}

//determine si toutes les cases blanches sont connectees
bool Labyrinthe::connexe()
{
	Sommet = 0;
	for (int i = 0; i < getNbLignes() * getNbColonnes(); i++)
	{
		Pile[i] = -1;
	}
	int caseBlanche = 0;
	for (int l = 0; l < getNbLignes(); l++)
	{
		for (int c = 0; c < getNbColonnes(); ++c)
		{
			if (lit(l, c) == 0)
			{
				caseBlanche = caseBlanche + 1;
			}
		}
	}
	if (caseBlanche == 0)
	{
		printf("\nErreur aucune case Blanche\n");
		return false;
	}
	//marquage de la case(0,0)
	push(0);
	modifie(0, 0, 2);
	int iden;
	while (Pile[0] != -1)
	{
		iden = pop();
		int idGauche = iden - 1;
		int idDroite = iden + 1;
		int idHaut = iden - getNbColonnes();
		int idBas = iden + getNbColonnes();
		if (iden % getNbColonnes() != 0 && lit(getLigne(idGauche), getCol(idGauche)) == 0)
		{
			push(idGauche);
			modifie(getLigne(idGauche), getCol(idGauche), 2);
		}
		if (iden % getNbColonnes() != (getNbColonnes() - 1) && lit(getLigne(idDroite), getCol(idDroite)) == 0)
		{
			push(idDroite);
			modifie(getLigne(idDroite), getCol(idDroite), 2);
		}
		if (idHaut >= 0 && lit(getLigne(idHaut), getCol(idHaut)) == 0)
		{
			push(idHaut);
			modifie(getLigne(idHaut), getCol(idHaut), 2);
		}
		if (idBas < (getNbLignes() * getNbColonnes()) && lit(getLigne(idBas), getCol(idBas)) == 0)
		{
			push(idBas);
			modifie(getLigne(idBas), getCol(idBas), 2);
		}
	}
	int caseMarque = 0;
	for (int l = 0; l < getNbLignes(); l++)
	{
		for (int c = 0; c < getNbColonnes(); ++c)
		{
			if (lit(l, c) == 2)
			{
				caseMarque = caseMarque + 1;
				modifie(l, c, 0);
			}
		}
	}

	if (caseBlanche == caseMarque)
	{
		return true;
	}
	else
	{
		return false;
	}
}
void Labyrinthe::genLaby(int k)
{
	Sommet = 0;
	int nbCase = getNbLignes() * getNbColonnes();
	int total = k;
	int essai = 10;
	int passe;
	for (int i = 0; i < getNbLignes() * getNbColonnes(); i++)
	{
		Pile[i] = -1;
	}
	do
	{
		passe = 0;
		//met des murs aléatoirement jusqu'à ce qu'il y ait k cases blanches
		if (nbCase != total)
		{
			int nombre = 1 + rand() % (getNbLignes() * getNbColonnes() - 2);
			if (lit(getLigne(nombre), getCol(nombre)) != 1)
			{
				modifie(getLigne(nombre), getCol(nombre), 1);
				if (connexe())
				{
					nbCase = nbCase - 1;
				}
				else
				{
					modifie(getLigne(nombre), getCol(nombre), 0);
				}
			}
		}
		else
		{
			if (essai != 0)
			{
				//verifie si le labyrinthe est connexe 
				if (connexe())
				{
					passe = 1;
				}
				else
				{
					essai = essai - 1;
					nbCase = getNbLignes() * getNbColonnes();
					for (int i = 0; i < getNbLignes() * getNbColonnes(); ++i)
					{
						modifie(getLigne(i), getCol(i), 0);
					}
				}
			}
			else
			{
				//change le nombre de cases blanches
				nbCase = getNbLignes() * getNbColonnes();
				essai = 10;
				for (int i = 0; i < getNbLignes() * getNbColonnes(); ++i)
				{
					modifie(getLigne(i), getCol(i), 0);
				}
				if (k == getNbLignes() + getNbColonnes())
				{
					total = total + 1;
				}
				else
				{
					total = total - 1;
				}
			}
		}
	} while (passe == 0);
	printf("\nOk\n");
}

//methode partie 3
int Labyrinthe::caseRandom()
{
	bool isOk = false;
	int idnb;
	do
	{
		idnb = rand() % (getNbLignes() * getNbColonnes());
		if (lit(getLigne(idnb), getCol(idnb)) == 0)
		{
			isOk = true;
		}
	} while (!isOk);
	return idnb;
}

// Méthode à compléter
// methode de choix du deplacement du robotA
bool Labyrinthe::deplaceRobotA(int algo)
{
	bool isOk=true;
	int initA = getIdRobotA();
	dernPos[posA] = getIdRobotA();
	posA = (posA + 1) % 4;
	if (algo == 1)
	{
		isOk = deplaceRobotA1();
	}
	if (initA == getIdRobotA() || dernPos[0] == getIdRobotA() || dernPos[1] == getIdRobotA() || dernPos[2] == getIdRobotA())
	{
		isOk = deplaceRobotA2();
	}
	return isOk;
}

bool Labyrinthe::deplaceRobotA1()
{
	if (PredFin())
	{
		return false;
	}
	else
	{
		int distAB = distMin(getIdRobotA(), getIdRobotB());
		int newA[4];
		for (int i = 0; i < 4; ++i)
		{
			newA[i] = -1;
		}
		if (getIdRobotA() % getNbColonnes() != 0 && lit(getLigne(getIdRobotA() - 1), getCol(getIdRobotA() - 1)) == 0)
		{
			if (distMin(getIdRobotA() - 1, getIdRobotB()) < distAB)
			{
				newA[0] = getIdRobotA() - 1;
			}
		}
		if (getIdRobotA() % getNbColonnes() != (getNbColonnes() - 1) && lit(getLigne(getIdRobotA() + 1), getCol(getIdRobotA() + 1)) == 0)
		{
			if (distMin(getIdRobotA() + 1, getIdRobotB()) < distAB)
			{
				newA[1] = getIdRobotA() + 1;
			}
		}
		if (getIdRobotA() - getNbColonnes() >= 0 && lit(getLigne(getIdRobotA() - getNbColonnes()), getCol(getIdRobotA() - getNbColonnes())) == 0)
		{
			if (distMin(getIdRobotA() - getNbColonnes(), getIdRobotB()) < distAB)
			{
				newA[2] = getIdRobotA() - getNbColonnes();
			}
		}
		if (getIdRobotA() + getNbColonnes() < getNbColonnes() * getNbLignes() && lit(getLigne(getIdRobotA() + getNbColonnes()), getCol(getIdRobotA() + getNbColonnes())) == 0)
		{
			if (distMin(getIdRobotA() + getNbColonnes(), getIdRobotB()) < distAB)
			{
				newA[3] = getIdRobotA() + getNbColonnes();
			}
		}
		int idnb;
		bool passe = true;
		do
		{
			passe = true;
			idnb = rand() % 4;
			if (newA[0] == -1 && newA[1] == -1 && newA[2] == -1 && newA[3] == -1)
			{
				passe = true;
				idnb = -1;
			}
			if (dernPos[0] == newA[idnb] || dernPos[1] == newA[idnb] || dernPos[2] == newA[idnb] || dernPos[3] == newA[idnb])
			{
				passe = false;
				newA[idnb] = -1;
			}
			if (newA[idnb] == -1)
			{
				passe = false;
			}
		} while (!passe);
		if (idnb == -1)
		{
			passe = false;
		}
		else
		{
			setIdRobotA(newA[idnb]);
		}
		return passe;
	}
}
//methode de deplacement du robotA aleatoirement
bool Labyrinthe::deplaceRobotA2()
{
	//verification que les robots sont en contact
	if (PredFin())
	{
		return false;
	}
	else
	{
		//recherche des cases vides voisines et mis dans un tableau
		int newA[4];
		for (int i = 0; i < 4; ++i)
		{
			newA[i] = -1;
		}
		//gauche
		if (getIdRobotA() % getNbColonnes() != 0 && lit(getLigne(getIdRobotA() - 1), getCol(getIdRobotA() - 1)) == 0)
		{
			newA[0] = getIdRobotA() - 1;
		}
		//droite
		if (getIdRobotB() % getNbColonnes() != (getNbColonnes() - 1) && lit(getLigne(getIdRobotA() + 1), getCol(getIdRobotA() + 1)) == 0)
		{
			newA[1] = getIdRobotA() + 1;
		}
		//haut
		if (getIdRobotA() - getNbColonnes() >= 0 && lit(getLigne(getIdRobotA() - getNbColonnes()), getCol(getIdRobotA() - getNbColonnes())) == 0)
		{
			newA[2] = getIdRobotA() - getNbColonnes();
		}
		//bas
		if (getIdRobotA() + getNbColonnes() < getNbColonnes() * getNbLignes() && lit(getLigne(getIdRobotA() + getNbColonnes()), getCol(getIdRobotA() + getNbColonnes())) == 0)
		{
			newA[3] = getIdRobotA() + getNbColonnes();
		}
		//choix aleatoire d'une des cases vides voisines 
		int idnb;
		bool passe = true;
		do
		{
			passe = true;
			idnb = rand() % 4;
			if (newA[0] == -1 && newA[1] == -1 && newA[2] == -1 && newA[3] == -1)
			{
				passe = false;
			}
			if (dernPos[0] == newA[idnb] || dernPos[1] == newA[idnb] || dernPos[2] == newA[idnb] || dernPos[3] == newA[idnb])
			{
				passe = false;
			}
			if (newA[idnb] == -1)
			{
				passe = false;
			}
		} while (!passe);
		setIdRobotA(newA[idnb]);
		return true;
	}
}

//methode de choix du deplacement du robotB en fonction du parametre
bool Labyrinthe::deplaceRobotB(int algo)
{
	bool isOk=true;
	int iniB = getIdRobotB();
	if (algo == 1)
	{
		isOk = deplaceRobotB1();
	}
	else
	{
		if (algo == 2)
		{
			isOk = deplaceRobotB2();
		}
	}
	if (iniB == getIdRobotB())
	{
		isOk = deplaceRobotB1();
	}
	return isOk;
}
//methode de deplacement du robotB aleatoirement
bool Labyrinthe::deplaceRobotB1()
{
	//verification que les robots sont en contact
	if (PredFin())
	{
		return false;
	}
	else
	{
		//recherche des cases vides voisines et mis dans un tableau
		int newB[4];
		for (int i = 0; i < 4; ++i)
		{
			newB[i] = -1;
		}
		//gauche
		if (getIdRobotB() % getNbColonnes() != 0 && lit(getLigne(getIdRobotB() - 1), getCol(getIdRobotB() - 1)) == 0)
		{
			newB[0] = getIdRobotB() - 1;
		}
		//droite
		if (getIdRobotB() % getNbColonnes() != (getNbColonnes() - 1) && lit(getLigne(getIdRobotB() + 1), getCol(getIdRobotB() + 1)) == 0)
		{
			newB[1] = getIdRobotB() + 1;
		}
		//haut
		if (getIdRobotB() - getNbColonnes() >= 0 && lit(getLigne(getIdRobotB() - getNbColonnes()), getCol(getIdRobotB() - getNbColonnes())) == 0)
		{
			newB[2] = getIdRobotB() - getNbColonnes();
		}
		//bas
		if (getIdRobotB() + getNbColonnes() < getNbColonnes() * getNbLignes() && lit(getLigne(getIdRobotB() + getNbColonnes()), getCol(getIdRobotB() + getNbColonnes())) == 0)
		{
			newB[3] = getIdRobotB() + getNbColonnes();
		}
		//choix aleatoire d'une des cases vides voisines 
		int idnb;
		do
		{
			idnb = rand() % 4;
		} while (newB[idnb] == -1);
		setIdRobotB(newB[idnb]);
		return true;
	}
}
//methode de deplacement du robotB avec un case plus eloigne que celle actuelle
bool Labyrinthe::deplaceRobotB2()
{
	//verification que les deux robots sont en contact
	if (PredFin())
	{
		return false;
	}
	else
	{
		int distAB = distMin(getIdRobotA(), getIdRobotB());
		//mise dans un tableau des cases vides voisines ayant une distance superieur avec le robot A que la case actuelle
		int newB[4];
		for (int i = 0; i < 4; ++i)
		{
			newB[i] = -1;
		}
		//gauche
		if (getIdRobotB() % getNbColonnes() != 0 && lit(getLigne(getIdRobotB() - 1), getCol(getIdRobotB() - 1)) == 0)
		{
			if (distMin(getIdRobotA(), getIdRobotB() - 1) > distAB)
			{
				newB[0] = getIdRobotB() - 1;
			}
		}
		//droite
		if (getIdRobotB() % getNbColonnes() != (getNbColonnes() - 1) && lit(getLigne(getIdRobotB() + 1), getCol(getIdRobotB() + 1)) == 0)
		{
			if (distMin(getIdRobotA(), getIdRobotB() + 1) > distAB)
			{
				newB[1] = getIdRobotB() + 1;
			}
		}
		//haut
		if (getIdRobotB() - getNbColonnes() >= 0 && lit(getLigne(getIdRobotB() - getNbColonnes()), getCol(getIdRobotB() - getNbColonnes())) == 0)
		{
			if (distMin(getIdRobotA(), getIdRobotB() - getNbColonnes()) > distAB)
			{
				newB[2] = getIdRobotB() - getNbColonnes();
			}
		}
		//bas
		if (getIdRobotB() + getNbColonnes() < getNbColonnes() * getNbLignes() && lit(getLigne(getIdRobotB() + getNbColonnes()), getCol(getIdRobotB() + getNbColonnes())) == 0)
		{
			if (distMin(getIdRobotA(), getIdRobotB() + getNbColonnes()) > distAB)
			{
				newB[3] = getIdRobotB() + getNbColonnes();
			}
		}
		//choix aleatoire d'une des cases vides voisines ayant une distance superieur avec le robot A que la case actuelle
		int idnb;
		bool passe = true;
		do
		{
			idnb = rand() % 4;
			if (newB[0] == -1 && newB[1] == -1 && newB[2] == -1 && newB[3] == -1)
			{
				passe = false;
			}
			if (newB[idnb] == -1)
			{
				passe = false;
			}
		} while (!passe);
		setIdRobotB(newB[idnb]);
		return passe;
	}

}

bool Labyrinthe::PredFin()
{
	bool contact = false;
	int Next[4];//gauche droite haut bas
	for (int i = 0; i < 4; ++i)
	{
		Next[i] = -1;
	}
	if (getIdRobotA() % getNbColonnes() != 0)
	{
		Next[0] = lit(getIdRobotA()-1);
	}
	if (getIdRobotA() % getNbColonnes() != (getNbColonnes() - 1))
	{
		Next[1] = lit(getIdRobotA()+1);
	}
	if (getIdRobotA() - getNbColonnes() >= 0)
	{
		Next[2] = lit(getIdRobotA() - getNbColonnes());
	}
	if (getIdRobotA() + getNbColonnes() < getNbColonnes() * getNbLignes())
	{
		Next[3] = lit(getIdRobotA() + getNbColonnes());
	}
	for (int i = 0; i < 4; ++i)
	{
		if (Next[i] != -1)
		{
			if (Next[i] == getIdRobotB())
			{
				contact = true;
			}
		}
	}
	if (getIdRobotA() == getIdRobotB())
	{
		contact = true;
	}
	return contact;
}
//distance minimale
int Labyrinthe::distMin(int depart, int fin)
{
	for (int l = 0; l < getNbLignes(); l++)
	{
		for (int c = 0; c < getNbColonnes(); ++c)
		{
			Pile[getID(l, c)] = -1;
		}
	}
	Sommet = 0;
	int* dista = dist(depart);
	int distance = dista[fin];
	delete[] dista;
	return distance;
}
int* Labyrinthe::dist(int depart)
{
	int* dist = new int[getNbLignes() * getNbColonnes()];
	for (int i = 0; i < getNbLignes() * getNbColonnes(); i++)
	{
		if (lit(getLigne(i), getCol(i)) == 1)
		{
			dist[i] = -1;
		}
		else
		{
			dist[i] = -2;
		}
	}
	push(depart);
	dist[depart] = 0;
	int iden;
	while (Pile[0] != -1)
	{
		iden = pop();
		int idGauche = iden - 1;
		int idDroite = iden + 1;
		int idHaut = iden - getNbColonnes();
		int idBas = iden + getNbColonnes();
		if (iden % getNbColonnes() != 0 && dist[idGauche] != -1)
		{
			if (dist[idGauche] == -2)
			{
				push(idGauche);
				dist[idGauche] = dist[iden] + 1;
			}
			if (dist[iden] + 1 < dist[idGauche])
			{
				push(idGauche);
				dist[idGauche] = dist[iden] + 1;
			}
		}
		if (iden % getNbColonnes() != (getNbColonnes() - 1) && dist[idDroite] != -1)
		{
			if (dist[idDroite] == -2)
			{
				push(idDroite);
				dist[idDroite] = dist[iden] + 1;
			}
			if (dist[iden] + 1 < dist[idDroite])
			{
				push(idDroite);
				dist[idDroite] = dist[iden] + 1;
			}
		}
		if (idHaut >= 0 && dist[idHaut] != -1)
		{
			if (dist[idHaut] == -2)
			{
				push(idHaut);
				dist[idHaut] = dist[iden] + 1;
			}
			if (dist[iden] + 1 < dist[idHaut])
			{
				push(idHaut);
				dist[idHaut] = dist[iden] + 1;
			}
		}
		if (idBas < (getNbLignes() * getNbColonnes()) && dist[idBas] != -1)
		{
			if (dist[idBas] == -2)
			{
				push(idBas);
				dist[idBas] = dist[iden] + 1;
			}
			if (dist[iden + 1] < dist[idBas])
			{
				push(idBas);
				dist[idBas] = dist[iden] + 1;
			}
		}
	}
	return dist;
}
// Méthode fournie par O. Bailleux
void Labyrinthe::visualisation()
{
	// Les robots sont placés dans la grille avant l'affichage
	modifie(getIdRobotA(), 2);
	modifie(getIdRobotB(), 3);

	system("clear");//linux
	//windows
	for (int i = 0; i < getNbLignes()+10; ++i)
	{
		printf("\n");
	}
	affiche();

	// Les robots sont retirés de la grille pour ne pas perturber la recherche de chemins
	// optimaux par la méthode distMin.
	modifie(getIdRobotA(), 0);
	modifie(getIdRobotB(), 0);
}

// Méthode fournie par O. Bailleux
int Labyrinthe::course(int timeout, bool silent, bool random, int algoA, int algoB)
{
	if (random)
	{// Course avec positions initiales des robots aléatoire
		idRobotB = caseRandom();
		idRobotA = caseRandom();
	}
	else
	{// Course avec départ dans les coins opposés.
		idRobotA = getID(0, 0);
		idRobotB = getID(getNbLignes() - 1, getNbColonnes() - 1);
	}

	int nEtapes = 0;
	bool contact = false;
	dernPos[0] = -1; dernPos[1] = -2; dernPos[2] = -3; dernPos[3] = -4;
	// Arret quand les robots se touchent ou de nombre maxi d'étapes atteint
	while (!contact && nEtapes < timeout)
	{
		//printf("A:%d B:%d\n", getIdRobotA(),getIdRobotB());
		  // On déplace le robot A
		contact = !deplaceRobotA(algoA);

		// On déplace le robot B sauf s'il est en contact avec A
		if (!contact) contact = !deplaceRobotB(algoB);

		nEtapes++;
		if (!silent)
		{// Délai et affichage seulement si on est pas en mode silencieux
			synchro(0.1);
			visualisation();
		}
	}

	if (contact) return nEtapes;
	else return timeout + 1;
}

// Méthode fournie par O. Bailleux
int Labyrinthe::evalue(int nCourses, int timeout, int algoA, int algoB)
{
	std::vector<int> tab;
	//int* tab = new int[nCourses]; // Tableau des scores

	for (int i = 0; i < nCourses; i++)
	{// On lance une course et récupère le score
		cout << i << " / " << nCourses;
		int score = course(timeout, true, true, algoA, algoB);
		tab.push_back(score);
		cout << " --> " << score << endl;
	}

	// Tri du tableau de score pour calcul de la médiane.
	sort(tab.begin(), tab.end());
	return tab[nCourses / 2];
}
//Methode pour l'affichage avec la bibliotheque SDL
//affichage avec la bibliotheque SDL
void Labyrinthe::afficheSDL(SDL_Renderer* rend)
{
	

	//lancement de la fonction d'affichage des bords
	afficheSDLBord(rend);
	for (int l = 0; l < getNbLignes(); l++)
	{
		for (int c = 0; c < getNbColonnes(); c++)
		{
			position.y = l * 32 + 32;
			position.x = c * 32 + 32;
			//verification de la valeur de la case et affichage de la bonne image
			if (lit(l, c) == 2)
			{
				SDL_RenderCopy(rend, robotA, NULL, &position);
			}
			if (lit(l, c) == 3)
			{
				SDL_RenderCopy(rend, robotB, NULL, &position);
			}
			if (lit(l, c) == 1)
			{
				afficheSDLMur(rend, getID(l, c));
			}
			if (lit(l, c) == 0)
			{
				SDL_RenderCopy(rend, sol, NULL, &position);
			}
		}
	}
	//affichage
	SDL_RenderPresent(rend);
}
//affichage des bords
void Labyrinthe::afficheSDLBord(SDL_Renderer* rend)
{
	position.x = 0;
	position.y = 0;
	//affichage du bord superieur
	for (int i = 0; i < getNbColonnes() + 2; i++)
	{
		position.x = i * 32;
		position.y = 0;
		SDL_RenderCopy(rend, Bmur, NULL, &position);
	}
	int k = 0;
	int w = 0;
	//affichage des bords a gauche et a droite du labyrinthe
	for (int i = 0; i < getNbLignes() + 2; i++)
	{
		position.y = i * 32;
		position.x = 0;
		SDL_RenderCopy(rend, Dmur, NULL, &position);
		position.x = (getNbColonnes() + 1) * 32;
		SDL_RenderCopy(rend, Gmur, NULL, &position);
		k = position.y;
		w = position.x;
	}
	//affichage du bord en bas du labyrinhte
	for (int i = 0; i < getNbColonnes() + 2; i++)
	{
		position.y = k;
		position.x = i * 32;
		SDL_RenderCopy(rend, Hmur, NULL, &position);
	}
	//affichage des coins
	position.x = 0;
	position.y = 0;
	SDL_RenderCopy(rend, coinBD, NULL, &position);
	position.x = w;
	position.y = 0;
	SDL_RenderCopy(rend, coinBG, NULL, &position);
	position.x = w;
	position.y = k;
	SDL_RenderCopy(rend, coinHG, NULL, &position);
	position.y = k;
	position.x = 0;
	SDL_RenderCopy(rend, coinHD, NULL, &position);
}
//affichage des murs 
void Labyrinthe::afficheSDLMur(SDL_Renderer* rend, int id)
{
	int nbM = NombreMur(id);
	int dirVide = 0;//1->gauche 2->haut 3->droite 4->bas
	//affichage d'une case etant entourer de mur
	if (nbM == 4)
	{
		SDL_RenderCopy(rend, vide, NULL, &position);
	}
	//affichage selon ou se trouve la seule case vide voisine
	if (nbM == 3)
	{
		//recherche de la case vide voisine
		//bas
		if (id % getNbColonnes() != 0)
		{
			if (lit(id - 1) == 0)
			{
				dirVide = 1;
			}
		}
		//droite
		if (id % getNbColonnes() != (getNbColonnes() - 1))
		{
			if (lit(id + 1) == 0)
			{
				dirVide = 3;
			}
		}
		//haut
		if (id - getNbColonnes() >= 0)
		{
			if (id - getNbColonnes() == 0)
			{
				dirVide = 2;
			}
		}
		//bas
		if (id + getNbColonnes() < getNbColonnes() * getNbLignes())
		{
			if (lit(id + getNbColonnes()) == 0)
			{
				dirVide = 4;
			}
		}
		//affichage en fonction de la ou se trouve la case vide voisine
		if (dirVide == 1)
		{
			SDL_RenderCopy(rend, Gmur, NULL, &position);
		}
		if (dirVide == 2)
		{
			SDL_RenderCopy(rend, Hmur, NULL, &position);
		}
		if (dirVide == 3)
		{
			SDL_RenderCopy(rend, Dmur, NULL, &position);
		}
		if (dirVide == 4)
		{
			SDL_RenderCopy(rend, Bmur, NULL, &position);
		}
	}
	//affichage d'une case ayant deux murs voisins
	if (nbM == 2)
	{
		//verification ou se trouve les murs voisins
		//gauche
		if (id % getNbColonnes() != 0)
		{
			if (lit(id - 1) == 1)
			{
				//droite
				if (id % getNbColonnes() != (getNbColonnes() - 1))
				{
					if (lit(id + 1) == 1)
					{
						dirVide = 13;
					}
				}
				//haut
				if (id - getNbColonnes() >= 0)
				{
					if (lit(id - getNbColonnes()) == 1)
					{
						dirVide = 12;
					}
				}
				//bas
				if (id + getNbColonnes() < getNbColonnes() * getNbLignes())
				{
					if (lit(id + getNbColonnes()) == 1)
					{
						dirVide = 14;
					}
				}
			}
		}
		//droite
		if (id % getNbColonnes() != (getNbColonnes() - 1))
		{
			if (lit(id + 1) == 1)
			{
				//gauche
				if (id % getNbColonnes() != 0)
				{
					if (lit(id - 1) == 1)
					{
						dirVide = 31;
					}
				}
				//haut
				if (id - getNbColonnes() >= 0)
				{
					if (lit(id - getNbColonnes()) == 1)
					{
						dirVide = 32;
					}
				}
				//bas
				if (id + getNbColonnes() < getNbColonnes() * getNbLignes())
				{
					if (lit(id + getNbColonnes()) == 1)
					{
						dirVide = 34;
					}
				}
			}
		}
		//haut
		if (id - getNbColonnes() >= 0)
		{
			if (lit(id - getNbColonnes()) == 1)
			{
				//gauche
				if (id % getNbColonnes() != 0)
				{
					if (lit(id - 1) == 1)
					{
						dirVide = 21;
					}
				}
				//droite
				if (id % getNbColonnes() != (getNbColonnes() - 1))
				{
					if (lit(id + 1) == 1)
					{
						dirVide = 23;
					}
				}
				//bas
				if (id + getNbColonnes() < getNbColonnes() * getNbLignes())
				{
					if (lit(id + getNbColonnes()) == 1)
					{
						dirVide = 24;
					}
				}
			}
		}
		//bas
		if (id + getNbColonnes() < getNbColonnes() * getNbLignes())
		{
			if (lit(id + getNbColonnes()) == 1)
			{
				//gauche
				if (id % getNbColonnes() != 0)
				{
					if (lit(id - 1) == 1)
					{
						dirVide = 41;
					}
				}
				//droite
				if (id % getNbColonnes() != (getNbColonnes() - 1))
				{
					if (lit(id + 1) == 1)
					{
						dirVide = 43;
					}
				}
				//haut
				if (id - getNbColonnes() >= 0)
				{
					if (lit(id - getNbColonnes()) == 1)
					{
						dirVide = 42;
					}
				}
			}
		}
		//affichage de la case en fonction des cases voisines etant des murs
		if (dirVide == 12)
		{
			SDL_RenderCopy(rend, BDmur, NULL, &position);
		}
		if (dirVide == 13)
		{
			SDL_RenderCopy(rend, hori, NULL, &position);
		}
		if (dirVide == 14)
		{
			SDL_RenderCopy(rend, HDmur, NULL, &position);
		}
		if (dirVide == 21)
		{
			SDL_RenderCopy(rend, BDmur, NULL, &position);
		}
		if (dirVide == 23)
		{
			SDL_RenderCopy(rend, BGmur, NULL, &position);
		}
		if (dirVide == 24)
		{
			SDL_RenderCopy(rend, verti, NULL, &position);
		}
		if (dirVide == 31)
		{
			SDL_RenderCopy(rend, hori, NULL, &position);
		}
		if (dirVide == 32)
		{
			SDL_RenderCopy(rend, BGmur, NULL, &position);
		}
		if (dirVide == 34)
		{
			SDL_RenderCopy(rend, HGmur, NULL, &position);
		}
		if (dirVide == 41)
		{
			SDL_RenderCopy(rend, HDmur, NULL, &position);
		}
		if (dirVide == 42)
		{
			SDL_RenderCopy(rend, verti, NULL, &position);
		}
		if (dirVide == 43)
		{
			SDL_RenderCopy(rend, HGmur, NULL, &position);
		}
	}
	//affichage d'une case ayant qu'un mur voisin
	if (nbM == 1)
	{
		//verification d'ou se trouve le mur voisin
		if (id % getNbColonnes() != 0)
		{
			if (lit(id - 1) == 1)
			{
				dirVide = 1;
			}
		}
		if (id % getNbColonnes() != (getNbColonnes() - 1))
		{
			if (lit(id + 1) == 1)
			{
				dirVide = 3;
			}
		}
		if (id - getNbColonnes() >= 0)
		{
			if (lit(id - getNbColonnes()) == 1)
			{
				dirVide = 2;
			}
		}
		if (id + getNbColonnes() < getNbColonnes() * getNbLignes())
		{
			if (lit(id + getNbColonnes()) == 1)
			{
				dirVide = 4;
			}
		}
		//affichage en fonction de la case voisin ayant un mur
		if (dirVide == 1)
		{
			SDL_RenderCopy(rend, murDHB, NULL, &position);
		}
		if (dirVide == 2)
		{
			SDL_RenderCopy(rend, murDGB, NULL, &position);
		}
		if (dirVide == 3)
		{
			SDL_RenderCopy(rend, murHGB, NULL, &position);
		}
		if (dirVide == 4)
		{
			SDL_RenderCopy(rend, murDHG, NULL, &position);
		}
	}
	//affichage d'une case sans murs adjacents
	if (nbM == 0)
	{
		SDL_RenderCopy(rend, quatre, NULL, &position);
	}
	//affichage d'une case vide
	if (nbM == -1 || lit(id) != 1)
	{
		SDL_RenderCopy(rend, sol, NULL, &position);
	}
}
//calcul du nombre de mur voisin a une case
int Labyrinthe::NombreMur(int id)
{
	int nbMur = -1;
	//si la case est un mur
	if (lit(id) == 1)
	{
		nbMur = 0;
		//comptage du nombre de murs adjacents
		//gauche
		if (id % getNbColonnes() != 0)
		{
			if (lit(id - 1) == 1)
			{
				nbMur = nbMur + 1;
			}
		}
		//droite
		if (id % getNbColonnes() != (getNbColonnes() - 1))
		{
			if (lit(id + 1) == 1)
			{
				nbMur = nbMur + 1;
			}
		}
		//haut
		if (id - getNbColonnes() >= 0)
		{
			if (lit(id - getNbColonnes()) == 1)
			{
				nbMur = nbMur + 1;
			}
		}
		//bas
		if (id + getNbColonnes() < getNbColonnes() * getNbLignes())
		{
			if (lit(id + getNbColonnes()) == 1)
			{
				nbMur = nbMur + 1;
			}
		}
	}
	return nbMur;
}

// Méthode d'affichage avec la bibliotheque SDL
void Labyrinthe::visualisationSDL(SDL_Renderer* rend)
{
	// Les robots sont placés dans la grille avant l'affichage
	modifie(getIdRobotA(), 2);
	modifie(getIdRobotB(), 3);

	SDL_RenderClear(rend);//remise a zero de la fenetre
	afficheSDL(rend);//preparation et affichage de la fenetre

	// Les robots sont retirés de la grille pour ne pas perturber la recherche de chemins
	// optimaux par la méthode distMin.
	modifie(getIdRobotA(), 0);
	modifie(getIdRobotB(), 0);
}

// methode de course avec la bibliotheque SDL
int Labyrinthe::courseSDL(int timeout, bool silent, bool random, int algoA, int algoB, SDL_Renderer* rend)
{
	if (random)
	{// Course avec positions initiales des robots aléatoire
		idRobotB = caseRandom();
		idRobotA = caseRandom();
	}
	else
	{// Course avec départ dans les coins opposés.
		idRobotA = getID(0, 0);
		idRobotB = getID(getNbLignes() - 1, getNbColonnes() - 1);
	}
	dernPos[0] = -1; dernPos[1] = -2; dernPos[2] = -3; dernPos[3] = -4;
	int nEtapes = 0;
	bool contact = false;
	visualisationSDL(rend);
	// Arret quand les robots se touchent ou de nombre maxi d'étapes atteint
	while (!contact && nEtapes < timeout)
	{
		// On déplace le robot A
		contact = !deplaceRobotA(algoA);

		// On déplace le robot B sauf s'il est en contact avec A
		if (!contact) contact = !deplaceRobotB(algoB);
		nEtapes++;
		if (!silent)
		{// Délai et affichage seulement si on est pas en mode silencieux
			synchro(0.2);
			visualisationSDL(rend);
			synchro(0.7);
			visualisation();
		}
	}

	if (contact) return nEtapes;
	else return timeout + 1;
}