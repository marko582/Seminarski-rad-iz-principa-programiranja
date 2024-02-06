#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "kki.h"

typedef struct element* P_ELEMENT;

typedef struct element {
	P_ELEMENT pred; //struct element* pred;
	int info;
	P_ELEMENT sled; //struct element* sled;
}ELEMENT;

void ispisListeOdPocetka(P_ELEMENT glava);
void ispisListeOdKraja(P_ELEMENT glava);



int dodajElementNaPocetakListe(P_ELEMENT* glava,int vrednost);
int dodajElementNaKrajListe(P_ELEMENT* glava,int vrednost);
void dodajElementNaZadatuPoziciju(P_ELEMENT* glava, int vrednost, int pozicija);

void obrisiElementSaPocetkaListe(P_ELEMENT* glava);
void obrisiElementSaKrajaListe(P_ELEMENT* glava);
void obrisiElementNaPoziciji(P_ELEMENT* glava, int pozicija);
void obrisiElementSaVrednoscu(P_ELEMENT* glava, int vrednost);
void obrisiSveElementeSaVrednoscu(P_ELEMENT* glava, int vrednost);
void obrisiCeluListu(P_ELEMENT* glava);

void kreirajListu(P_ELEMENT* glava);

int duzinaListe(P_ELEMENT glava);
int maxListe(P_ELEMENT glava);
int minListe(P_ELEMENT glava);
int sumaListe(P_ELEMENT glava);
double srednjaVrednostListe(P_ELEMENT glava);

int daLiSuRazliciti(P_ELEMENT glava);
void daLiPostojiUListi(P_ELEMENT glava, int vrednost);

void ZamenaElemenataListe(P_ELEMENT glava, int pozicija1, int pozicija2);
void promeniElementPoVrednosti(P_ELEMENT glava, int staraVrednost, int novaVrednost);
void promeniElementPoPoziciji(P_ELEMENT glava, int vrednost, int pozicija);

void SortirajListu(P_ELEMENT glava);
void ObrniListu(P_ELEMENT* glava);
void izbaciDuplikate(P_ELEMENT* glava);
void frekvencija(P_ELEMENT glava);

void kopirajListu(P_ELEMENT* glava1, P_ELEMENT* glava2);
int uporediListe(P_ELEMENT glava1, P_ELEMENT glava2);
void unija(P_ELEMENT glava1, P_ELEMENT glava2,P_ELEMENT* glava3);
void presek(P_ELEMENT glava1, P_ELEMENT glava2,P_ELEMENT* glava3);
void razlika(P_ELEMENT glava1, P_ELEMENT glava2,P_ELEMENT* glava3);



void Liste();

int main() {
	//ne moze se unese 0
	logo();
	naslov();
	Liste();

	return EXIT_SUCCESS;
}

void ispisListeOdPocetka(P_ELEMENT glava) {
	if (glava == NULL) {
		printc("Lista je prazna!",S_CRVENA);
	}
	else {
		P_ELEMENT pom;
		pom = glava;
		printc("Lista je: ",S_AQUA);
		do {
			printf("%d ", pom->info);
			pom = pom->sled;
		} while (pom != glava);
	}
	printf("\n\n");
}
void ispisListeOdKraja(P_ELEMENT glava) {
	if (glava == NULL) {
		printf("Lista je prazna!");
	}
	else {
		P_ELEMENT pom;
		pom = glava->pred;
		printc("Lista je: ", S_AQUA);
		do {
			printf("%d ", pom->info);
			pom = pom->pred;
		} while (pom != glava->pred);
	}
	printf("\n\n");
}
int dodajElementNaKrajListe(P_ELEMENT* glava, int vrednost) {
	P_ELEMENT noviElement;
	P_ELEMENT rep=NULL;
	noviElement = (P_ELEMENT)malloc(sizeof(ELEMENT));
	noviElement->info = vrednost;
	if ((*glava) == NULL) {
		*glava = noviElement;
		noviElement->pred = *glava;
		noviElement->sled = *glava;
		rep = noviElement;
	}
	else {
		//rep = *glava;
		//while (rep->sled != *glava)
		//{
		//	rep = rep->sled;
		//}
		rep = (*glava)->pred;//ovo iznad je isto, ali ovo je brze - koristimo svojstvo cirkularnih listi

		noviElement->pred = rep;
		rep->sled = noviElement;
		(*glava)->pred = noviElement;
		noviElement->sled = *glava;
		rep = noviElement;
	}
	return noviElement->info;
}
int dodajElementNaPocetakListe(P_ELEMENT* glava, int vrednost) {
	P_ELEMENT noviElement;
	P_ELEMENT rep = NULL;
	noviElement = (P_ELEMENT)malloc(sizeof(ELEMENT));
	noviElement->info = vrednost;
	if ((*glava) == NULL) {
		*glava = noviElement;
		(*glava)->sled = *glava;
		(*glava)->pred = *glava;
		rep = *glava;
	}
	else {
		rep = *glava;
		while (rep->sled != *glava)
		{
			rep = rep->sled;
		}
		rep->sled = noviElement;
		noviElement->pred = rep;
		(*glava)->pred = noviElement;
		noviElement->sled = *glava;
		*glava = noviElement;
	}
	return noviElement->info;
}
void dodajElementNaZadatuPoziciju(P_ELEMENT* glava, int vrednost, int pozicija) {
	P_ELEMENT noviElement;
	P_ELEMENT pom;
	int i = 1;
	int n = 0;
	if (*glava != NULL) {
		n = duzinaListe(*glava);
	}
	if (pozicija == 1) {
		dodajElementNaPocetakListe(glava, vrednost);
	}
	else if (pozicija < 1 || pozicija > n + 1) {
		printc("Uneta pozicija je pogresna\n\n", S_CRVENA);
		return;
	}
	else {
		noviElement = (P_ELEMENT)malloc(sizeof(ELEMENT));
		noviElement->info = vrednost;
		pom = *glava;
		while (i < pozicija - 1) {
			pom = pom->sled;
			i++;
		}
		noviElement->pred = pom;
		noviElement->sled = pom->sled;
		pom->sled->pred = noviElement;
		pom->sled = noviElement;
	}
	printc("Element je dodat\n\n", S_AQUA);
}
void kreirajListu(P_ELEMENT* glava) {
	int vrednost;
	int i = 1;
	while (1)
	{
		printf("Unesite %d. element.(unesite 0 za kraj unosa)\n",i);
		scanf("%d", &vrednost);
		i++;
		if (vrednost == 0)
			break;
		dodajElementNaKrajListe(glava, vrednost);
	}
	printc("Lista je kreirana!\n\n",S_AQUA);
}
void obrisiElementSaPocetkaListe(P_ELEMENT* glava) {
	P_ELEMENT pom;
	pom = *glava;
	P_ELEMENT rep;
	rep = *glava;
	if (*glava == NULL) {
		printc("Lista je prazna!\n\n",S_CRVENA);
		return;
	}
	while (rep->sled != *glava)
	{
		rep = rep->sled;
	}

	if (*glava == (*glava)->sled) {
		*glava = NULL;
		rep = NULL;
		free(pom);
	}
	else {
		*glava = (*glava)->sled;
		(*glava)->pred = rep;
		rep->sled = *glava;
		free(pom);
	}
}
void obrisiElementSaKrajaListe(P_ELEMENT* glava) {
	P_ELEMENT pom;
	P_ELEMENT rep;
	rep = *glava;
	if (*glava == NULL) {
		printc("Lista je prazna!\n\n",S_CRVENA);
		return;
	}
	while (rep->sled != *glava)
	{
		rep = rep->sled;
	}
	pom = rep;

	if (*glava == (*glava)->sled) {
		*glava = NULL;
		rep = NULL;
		free(pom);
	}
	else {
		rep = rep->pred;
		rep->sled = *glava;
		(*glava)->pred = rep;
		free(pom);
	}

}
void obrisiElementNaPoziciji(P_ELEMENT* glava, int pozicija) {
	P_ELEMENT pom;
	pom = *glava;
	int n = duzinaListe(*glava);
	int i = 1;
	if (pozicija<1 || pozicija>n) {
		printc("Pozicija ne postoji\n\n",S_CRVENA);
	}
	else if(pozicija==1){
		obrisiElementSaPocetkaListe(glava);
	}
	else if (pozicija == n) {
		obrisiElementSaKrajaListe(glava);
	}
	else {
		while (i<pozicija)
		{
			pom = pom->sled;
			i++;
		}
		pom->pred->sled = pom->sled;
		pom->sled->pred = pom->pred;
		free(pom);
	}
	

}
void obrisiElementSaVrednoscu(P_ELEMENT* glava, int vrednost) {
	//SAMO PRVI sa tom vrednostcu brise
	P_ELEMENT pom;
	pom = *glava;
	int daLiSeJavlja = 0;
	int i = 1;
	if (*glava == NULL) {
		printc("Lista je prazna!\n\n", S_CRVENA);
		return;
	}
	do {
		if (pom->info == vrednost) {
			obrisiElementNaPoziciji(glava, i);
			pom = *glava;
			i--;
			daLiSeJavlja = 1;
		}
		else {
			pom = pom->sled;
			i++;
		}

	} while (pom != *glava);
	if (!daLiSeJavlja) {
		printc("Uneta vrednost ne postoji u listi\n\n", S_CRVENA);
		return;
	}
	


}

void obrisiSveElementeSaVrednoscu(P_ELEMENT* glava, int vrednost) {
	//SVE brise
	P_ELEMENT pom;
	pom = *glava;
	int j = 1;
	int daLiSeJavlja = 0;
	int n = duzinaListe(*glava);
	if (*glava == NULL) {
		printc("Lista je prazna!\n\n", S_CRVENA);
		return;
	}
	for (int i = 0; i <= n; i++)
	{
		if (pom->info == vrednost) {
			obrisiElementNaPoziciji(glava, j);
			pom = *glava;
			i = 0;
			j = 1;
			n--;
			daLiSeJavlja = 1;
		}
		else {
			pom = pom->sled;
			j++;
		}
	}
	if (!daLiSeJavlja) {
		printc("Uneta vrednost ne postoji u listi\n\n", S_CRVENA);
		return;
	}
}
void obrisiCeluListu(P_ELEMENT* glava) {

	P_ELEMENT pom;
	P_ELEMENT tekuci;
	if (*glava == NULL) {
		//printc("Lista je prazna!\n\n",S_CRVENA);
		return 0;
	}
	else{
		tekuci = (*glava)->sled;
		while (tekuci != *glava) {
			pom = tekuci->sled;
			free(tekuci);
			tekuci = pom;
		}
		free(*glava);
		*glava = NULL;
	}
	printc("Lista je obrisana\n", S_AQUA);

}
int duzinaListe(P_ELEMENT glava) {
	int n = 0;
	P_ELEMENT pom;
	if (glava == NULL) {
		return n;
	}
	else {
		pom = glava;
		do {
			n++;
			pom = pom->sled;
		} while (pom != glava);
	}
	return n;
}
int maxListe(P_ELEMENT glava) {
	int max;
	if (glava == NULL) {
		//printf("Lista je prazna, pa nema maksimum!\n");
		return 0;
	}
	else {
		P_ELEMENT pom;
		pom = glava;
		max = pom->info;
		do {
			
			pom = pom->sled;
			if (max < pom->info) {
				max = pom->info;
			}
		} while (pom != glava);
	}
	return max;
}
int minListe(P_ELEMENT glava) {
	int min;
	if (glava == NULL) {
		//printf("Lista je prazna, pa nema minimum!\n");
		return 0;
	}
	else {
		P_ELEMENT pom;
		pom = glava;
		min = pom->info;
		do {

			pom = pom->sled;
			if (min > pom->info) {
				min = pom->info;
			}
		} while (pom != glava);
	}
	return min;
}
int sumaListe(P_ELEMENT glava) {
	int suma = 0;
	if (glava == NULL) {
		return 0;
	}
	else {
		P_ELEMENT pom;
		pom = glava;
		do {
			suma += pom->info;
			pom = pom->sled;
		} while (pom != glava);
	}
	return suma;
}
double srednjaVrednostListe(P_ELEMENT glava) {
	double srvr = 0;
	int n = duzinaListe(glava);
	int suma = sumaListe(glava);
	if (!n) {
		return 0;
	}
	else {
		srvr = (double)suma / n;
		return srvr;
	}
}
int daLiSuRazliciti(P_ELEMENT glava) {
	int daLiSePojavljuje = 0;
	if (glava == NULL) {
		printc("Lista je prazna!\n\n", S_CRVENA);
		return;
	}
	if (glava != NULL) {
		P_ELEMENT predhodni;
		P_ELEMENT tekuci;
		predhodni = glava;
		tekuci = glava->sled;
		do {
			do {
				if (tekuci != predhodni && predhodni->info == tekuci->info) {
					daLiSePojavljuje = 1;
					return 0;//printf("Nisu svi elementi u listi razliciti");
				}
				tekuci = tekuci->sled;
			} while (tekuci != glava);

			predhodni = predhodni->sled;
		} while (predhodni != glava);
	}
	if (!daLiSePojavljuje)
		return 1; //printf("Svi elementi u listi su razliciti");
}
void daLiPostojiUListi(P_ELEMENT glava, int vrednost) {
	int i = 0;
	int br = 0;
	int daLiSePojavljuje = 0;
	if (glava == NULL) {
		printc("Lista je prazna!\n\n", S_CRVENA);
		return;
	}
	if (glava != NULL) {
		P_ELEMENT pom;
		pom = glava;
		do {
			i++;
			if (pom->info == vrednost) {
				printf("%d se nalazi na %d. poziciji u listi\n", vrednost, i);
				daLiSePojavljuje = 1;
				br++;
			}
			pom = pom->sled;
		} while (pom != glava);
	}
	if (!daLiSePojavljuje)
		printf("%d se ne nalazi u listi\n", vrednost);
	else
		printf("%d je %d puta nadjen u listi\n\n",vrednost,br);
}
void ZamenaElemenataListe(P_ELEMENT glava, int pozicija1, int pozicija2) {
	int n = duzinaListe(glava);
	if (glava == NULL) {
		printc("Lista je prazna!\n\n", S_CRVENA);
		return;
	}
	if (pozicija1<1 || pozicija1>n || pozicija2<1 || pozicija2>n) {
		return;
	}
	P_ELEMENT prvi = glava;
	P_ELEMENT drugi = glava;
	for (int i = 1; i < pozicija1; i++)
	{
		prvi = prvi->sled;
	}
	for (int i = 1; i < pozicija2; i++)
	{
		drugi = drugi->sled;
	}
	int pom;
	pom = prvi->info;
	prvi->info = drugi->info;
	drugi->info = pom;

}
void promeniElementPoVrednosti(P_ELEMENT glava, int staraVrednost, int novaVrednost) {
	if (glava == NULL) {
		printc("Lista je prazna!\n\n", S_CRVENA);
		return;
	}
	if (glava != NULL) {
		P_ELEMENT pom;
		pom = glava;
		do {
			if (pom->info == staraVrednost) {
				pom->info = novaVrednost;
			}
			pom = pom->sled;
		} while (pom != glava);
	}
}
void promeniElementPoPoziciji(P_ELEMENT glava, int vrednost, int pozicija) {
	if (glava == NULL) {
		printc("Lista je prazna!\n\n", S_CRVENA);
		return;
	}
	if (glava != NULL) {
		P_ELEMENT pom;
		pom = glava;
		for (int i = 1; i < pozicija; i++)
		{
			pom = pom->sled;
		}
		pom->info = vrednost;
	}
}
void SortirajListu(P_ELEMENT glava) {
	int pom;
	if (glava != NULL) {
		P_ELEMENT predhodni;
		P_ELEMENT tekuci;
		predhodni = glava;
		tekuci = glava->sled;
		do {
			do {
				if (predhodni->info < tekuci->info) {
					pom = predhodni->info;
					predhodni->info = tekuci->info;
					tekuci->info = pom;
				}
				tekuci = tekuci->sled;
			} while (tekuci != glava);

			predhodni = predhodni->sled;
		} while (predhodni != glava);
	}
	printc("Lista je sortirana\n\n",S_AQUA);
}
void ObrniListu(P_ELEMENT* glava) {
	if (*glava != NULL) {
		P_ELEMENT predhodni = *glava;
		P_ELEMENT pom = *glava;
		P_ELEMENT tekuci = (*glava)->sled;

		predhodni->sled = predhodni;
		predhodni->pred = predhodni;

		while (tekuci != *glava)
		{
			pom = tekuci->sled;

			tekuci->sled = predhodni;
			predhodni->pred = tekuci;
			(*glava)->sled = tekuci;
			tekuci->pred = *glava;

			predhodni = tekuci;
			tekuci = pom;
		}
		*glava = predhodni;
	}
	printc("Lista je obrnuta\n\n", S_AQUA);
}

void izbaciDuplikate(P_ELEMENT* glava) {
	P_ELEMENT pom;
	P_ELEMENT pom2;
	if (*glava == NULL) {
		printc("Lista je prazna!\n\n", S_CRVENA);
		return;
	}
	pom = *glava;
	pom2 = (*glava)->sled;
	do {
		do {
			if (pom!=pom2 && pom->info == pom2->info) {
				obrisiElementSaVrednoscu(glava, pom->info);
				pom = *glava;
				pom2 = (*glava)->sled;
			}
			pom2 = pom2->sled;
		} while (pom2 != *glava);
		pom = pom->sled;
	} while (pom != *glava);
	printc("Duplikati izbaceni\n\n", S_AQUA);
	
}
void frekvencija(P_ELEMENT glava) {

	//P_ELEMENT kopija=NULL;
	//P_ELEMENT tekuci = glava;
	//do {
	//	dodajElementNaKrajListe(&kopija, tekuci->info);
	//	tekuci = tekuci->sled;
	//} while (tekuci != glava);

	P_ELEMENT kopija = NULL;
	kopirajListu(&glava, &kopija);

	P_ELEMENT pom;
	P_ELEMENT pom2;
	pom = kopija;
	pom2 = kopija;
	int vrednost = 0;
	int i = 0;
	if (glava == NULL) {
		printc("Lista je prazna!\n\n", S_CRVENA);
		return;
	}
	do {
		pom = kopija;
		do {
			
			if (pom == NULL)
				return;
			vrednost = pom->info;
			if (pom->info == pom2->info) {
				i++;	
			}
			pom2 = pom2->sled;
		} while (pom2 != kopija);
		printf("%d je nalazi na %d mesta u listi\n",vrednost, i);
		obrisiSveElementeSaVrednoscu(&kopija, pom->info);
		
		pom2 = kopija;
		i = 0;
		pom = pom->sled;
	} while (pom != kopija);
	printf("\n");
}
void kopirajListu(P_ELEMENT* glava1, P_ELEMENT* glava2) {
	obrisiCeluListu(glava2);
	P_ELEMENT tekuci = *glava1;
	if (*glava1 != NULL) {
		do {
			dodajElementNaKrajListe(glava2, tekuci->info);
			tekuci = tekuci->sled;
		} while (tekuci != *glava1);
	}
}
int uporediListe(P_ELEMENT glava1, P_ELEMENT glava2) {
	P_ELEMENT glava3 = NULL;
	razlika(glava1, glava2, &glava3);
	int n = duzinaListe(glava3);
	if (!n) {
		return 1;
	}
	else {
		return 0;
	}
}
void unija(P_ELEMENT glava1, P_ELEMENT glava2,P_ELEMENT* glava3) {
	P_ELEMENT pom = glava1;
	P_ELEMENT pom2 = glava2;
	if (glava1 == NULL && glava2 == NULL) {
		*glava3 = NULL;
		return;
	}
	if (glava1 == NULL) {
		do {
			dodajElementNaKrajListe(glava3, pom2->info);
			pom2 = pom2->sled;
		} while (pom2 != glava2);
		return;
	}
	else if (glava2 == NULL) {
		do {
			dodajElementNaKrajListe(glava3, pom->info);
			pom = pom->sled;
		} while (pom != glava1);
		return;
	}
	else {
		
		do {
			dodajElementNaKrajListe(glava3, pom->info);
			pom = pom->sled;
		} while (pom != glava1);

		do {
			dodajElementNaKrajListe(glava3, pom2->info);
			pom2 = pom2->sled;
		} while (pom2 != glava2);
		return;
	}
	printc("Izvrsena unija\n\n",S_AQUA);
}
void presek(P_ELEMENT glava1, P_ELEMENT glava2, P_ELEMENT* glava3) {
	P_ELEMENT pom = glava1;
	P_ELEMENT pom2 = glava2;
	if (glava1 == NULL || glava2 == NULL) {
		*glava3 = NULL;
		return;
	}
	else {
		do {
			do {
				if (pom->info == pom2->info) {
					dodajElementNaKrajListe(glava3, pom->info);
				}
				pom2 = pom2->sled;
			} while (pom2 != glava2);
			pom = pom->sled;
		} while (pom != glava1);
	}
	printc("Izvrsen presek\n\n", S_AQUA);

}
void razlika(P_ELEMENT glava1, P_ELEMENT glava2, P_ELEMENT* glava3) {
	P_ELEMENT pom = glava1;
	P_ELEMENT pom2 = glava2;
	int daLisePojavljuje = 0;
	if (glava1 == NULL || (glava1==NULL && glava2==NULL)) {
		*glava3 = NULL;
		return;
	}
	else if (glava2 == NULL) {
		do {
			dodajElementNaKrajListe(glava3, pom->info);
			pom = pom->sled;
		} while (pom != glava1);
		return;
	}
	else {
		do {
			daLisePojavljuje = 0;
			do {
				if (pom->info == pom2->info) {
					daLisePojavljuje = 1;
					break;
				}
				pom2 = pom2->sled;
			} while (pom2 != glava2);
			if (!daLisePojavljuje) {
				dodajElementNaKrajListe(glava3, pom->info);
			}
			pom = pom->sled;
		} while (pom != glava1);
		return;
	}
	printc("Izvrsena razlika\n\n", S_AQUA);

}
void Liste() {
	int izbor = 0;
	int ispisi = 0;
	int obrisi = 0;
	int pozicija = 0;
	int vrednost = 0;
	int vrednostD = 0;
	int pozicijaD = 0;
	int dodaj = 0;
	int lista = 0;
	int operacijeA = 0;
	int vrednostP = 0;
	int zamena = 0;
	int operacije2 = 0;
	P_ELEMENT glave[1000] = {0};
	int i = 0;
	while (1) {
		printc("Izaberite opciju:\n", S_BELA);
		printc("1.unos liste\n", S_ZELENA);
		printc("2.prikaz liste\n", S_BELA);
		printc("3.promena liste\n", S_ZUTA);
		printc("4.dodavanje elemenata\n", S_BELA);
		printc("5.brisanje elemenata\n", CRVENA);
		printc("6.aritmeticke operacije sa listom\n", S_BELA);
		printc("7.sortiraj listu\n", S_PLAVA);
		printc("8.obrni listu\n", S_BELA);
		printc("9.izbaci duplikate iz liste\n",S_ZELENA);
		printc("10.frekvencija elemenata\n", S_BELA);
		printc("11.da li su svi elementi u listi razliciti\n", S_ZUTA);
		printc("12.da li element postoji u listi\n", S_BELA);
		printc("13.zamena elemenata u listi\n", S_PLAVA);
		printc("14.operacije sa dve liste(unija,presek,razlika,kopiranje,uporedjivanje)\n", S_BELA);

		printc("0.kraj rada\n",SIVA);

		printf("Vas izbor:\n");
		scanf("%d", &izbor);
		switch (izbor) {
		case 1:
			i++;
			kreirajListu(&glave[i]);
			break;
		case 2:
			printf("Unesite 1 za prikaz od pocetka, unesite 2 za prikaz od kraja\n");
			printf("Vas izbor:\n");
			scanf("%d", &ispisi);
			if (ispisi == 2) {
				ispisListeOdKraja(glave[i]);
			}
			else {
				ispisListeOdPocetka(glave[i]);
			}
			break;
		case 3:
			printf("Unesite redni broj liste na koju zelite da se pozicionirate\n");
			scanf("%d", &lista);
			i = lista;
			printc("Pozicionirali ste se na listu sa rednim brojem ", S_AQUA);
			printf("%d\n\n", lista);
			break;
		case 4:
			printf("Unesite 1 za dodavanje na pocetak, 2 za dodavanje na kraj\
 i 3 za dodavanje na mesto po izboru\n");
			scanf("%d", &dodaj);
			switch (dodaj) {
			case 1:
				printf("Unesite vrednost za dodavanje\n");
				scanf("%d", &vrednostD);
				dodajElementNaPocetakListe(&glave[i], vrednostD);
				printc("Element je dodat na pocetak liste\n\n", S_AQUA);
				break;
			case 2:
				printf("Unesite vrednost za dodavanje\n");
				scanf("%d", &vrednostD);
				dodajElementNaKrajListe(&glave[i], vrednostD);
				printc("Element je dodat na kraj liste\n\n", S_AQUA);
				break;
			case 3:
				printf("Unesite vrednost za dodavanje\n");
				scanf("%d", &vrednostD);
				printf("Unesite poziciju na koju zelite da dodate element\n");
				scanf("%d", &pozicijaD);
				dodajElementNaZadatuPoziciju(&glave[i], vrednostD, pozicijaD);
				break;
			}
			break;
		case 5:
			printf("Unesite 1 za brisanje poslednjeg elementa\n\
Unesite 2 za brisanje prvog elementa\n\
Unesite 3 za brisnanje elementa na zadatoj poziciji\n\
Unesite 4 za brisanje prvog elementa sa unetom vrednoscu\n\
Unesite 5 za brisanje svih elemenata sa unetom vrednoscu\n\
Unesite 6 za brisanje cele liste\n");
			scanf("%d", &obrisi);
			switch (obrisi)
			{
			case 1:
				obrisiElementSaKrajaListe(&glave[i]);
				if (glave[i] != NULL) {
					printc("Element je obrisan\n", S_AQUA);
				}
				break;
			case 2:
				obrisiElementSaPocetkaListe(&glave[i]);
				if (glave[i] != NULL) {
					printc("Element je obrisan\n", S_AQUA);
				}
				break;
			case 3:
				printf("Unesite poziciju elementa koji zelite da obrisete\n");
				scanf("%d", &pozicija);
				obrisiElementNaPoziciji(&glave[i],pozicija);
				if (glave[i] != NULL) {
					printc("Element je obrisan\n", S_AQUA);
				}
				break;
			case 4:
				printf("Unesite vrednost elementa koji zelite da obrisete\n");
				scanf("%d", &vrednost);
				obrisiElementSaVrednoscu(&glave[i],vrednost);
				if (glave[i] != NULL) {
					printc("Element je obrisan\n", S_AQUA);
				}
				break;
			case 5:
				printf("Unesite vrednost elementa koji zelite da obrisete\n");
				scanf("%d", &vrednost);
				obrisiSveElementeSaVrednoscu(&glave[i],vrednost);
				if (glave[i] != NULL) {
					printc("Elementi su obrisani\n", S_AQUA);
				}
				break;
			case 6:
				obrisiCeluListu(&glave[i]);
				break;
			}
			break;
		case 6:
			printf("Unesite 1 za duzinu liste\n\
Unesite 2 za maksimum liste\n\
Unesite 3 za minimum liste\n\
Unesite 4 za sumu liste\n\
Unesite 5 za srednju vrednost liste\n");
			scanf("%d", &operacijeA);
			switch (operacijeA)
			{
			case 1:
				printf("Duzina liste je %d\n\n", duzinaListe(glave[i]));
				break;
			case 2:
				printf("Maksimum liste je %d\n\n", maxListe(glave[i]));
				break;
			case 3:
				printf("Minimum liste je %d\n\n", minListe(glave[i]));
				break;
			case 4:
				printf("Suma liste je %d\n\n", sumaListe(glave[i]));
				break;
			case 5:
				printf("Srednja vrednost liste je %lf\n\n", srednjaVrednostListe(glave[i]));
				break;
			}
			break;
		case 7:
			SortirajListu(glave[i]);
			break;
		case 8:
			ObrniListu(&glave[i]);
			break;
		case 9:
			izbaciDuplikate(&glave[i]);
			break;
		case 10:
			frekvencija(glave[i]);
			break;
		case 11:
			if (daLiSuRazliciti(glave[i])) {
				printc("Svi elementi u listi su razliciti\n",S_AQUA);
			}
			else {
				printc("Nisu svi elementi u listi razliciti\n",S_AQUA);
			}
			break;
		case 12:
			printf("Unesite vrednost koju treba naci u listi\n");
			scanf("%d", &vrednostP);
			daLiPostojiUListi(glave[i], vrednostP);
			break;
		case 13:
			printf("Unesite 1 za zamenu dva elementa liste\n\
Unesite 2 za promenu vrednosti elementa\n\
Unesite 3 za promenu vrednosti na unetoj poziciji\n");
			scanf("%d", &zamena);
			switch (zamena)
			{
				int pozicija1 = 0, pozicija2 = 0;
				int staraVr = 0, novaVr = 0;
				int vrednostZ = 0, pozicijaZ = 0;
			case 1:
				printf("Unesite pozicije sa razmakom\n");
				scanf("%d %d", &pozicija1, &pozicija2);
				ZamenaElemenataListe(glave[i], pozicija1, pozicija2);
				break;
			case 2:
				printf("Unesite vrednosti sa razmakom\n");
				scanf("%d %d", &staraVr, &novaVr);
				promeniElementPoVrednosti(glave[i], staraVr, novaVr);
				break;
			case 3:
				printf("Unesite poziciju\n");
				scanf("%d", &pozicijaZ);
				printf("Unesite vrednost\n");
				scanf("%d", &vrednostZ);
				promeniElementPoPoziciji(glave[i], vrednostZ,pozicijaZ);
				break;
			}
			break;
		case 14:
			printf("Unesite 1 za uniju dve liste\n\
Unesite 2 za presek dve liste\n\
Unesute 3 za razliku dve liste\n\
Unesite 4 za kopiranje liste1 u listu 2\n\
Unesite 5 za poredjenje dve liste\n");
			scanf("%d", &operacije2);
			int j = 0, k = 0, l = 0;
			switch (operacije2)
			{
			case 1:
				printf("Unesite redne brojeve tri liste sa razmakom izmedju\n");
				scanf("%d %d %d", &j, &k,&l);
				unija(glave[j], glave[k], &glave[l]);
				break;
			case 2:
				printf("Unesite redne brojeve tri liste sa razmakom izmedju\n");
				scanf("%d %d %d", &j, &k, &l);
				presek(glave[j], glave[k], &glave[l]);
				break;
			case 3:
				printf("Unesite redne brojeve tri liste sa razmakom izmedju\n");
				scanf("%d %d %d", &j, &k, &l);
				razlika(glave[j], glave[k], &glave[l]);
				break;
			case 4:
				printf("Unesite redne brojeve dve liste sa razmakom izmedju\n");
				scanf("%d %d", &j, &k);
				kopirajListu(&glave[j], &glave[k]);
				printc("Izvrseno kopiranje\n\n", S_AQUA);
				break;
			case 5:
				printf("Unesite redne brojeve dve liste sa razmakom izmedju\n");
				scanf("%d %d", &j, &k);
				if (uporediListe(&glave[j], &glave[k])) {
					printf("Ove dve liste su iste\n");
				}
				else {
					printf("Ove dve liste nisu iste\n");
				}
				break;
			}
			break;
		default:
			printf("Dovidjenja\n");
			exit(1);
			break;
		}

	}

}