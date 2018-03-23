/*************************
Zadanie 3, ALPR 2015/2016
(c) Peter Beck
*************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char hrac1[20];				//znakove polia, do ktorych sa vlozi meno hracov
char hrac2[20];

/*funkcia pyta mena jednotlivych hraca1 a hraca2, mena vypise a vola funkciu generacia_struktur()*/
void pomenovanie_hracov();
/*do jednotlivych struktur uklada udaje o jednotlivych bojovnikoch; pomocou volania funkcie vypis_udajov() vypise generovane udaje o bojovnikoch;
vola funkciu hra()*/
void generacia_struktur();
/*cyklicky vola fukciu suboje() a uklada jej vysledok do premennej koniec; funkcia konci az sa koniec rovna 10 alebo 20*/
void hra();
/*funkcia rozlisuje parne a neparne kola, pretoze sa bojovnici v utoku striedaju podla vitaza predosleho kola;
po vypytani potrebnych udajov o bojovnikoch, ktory sa proti sebe postavia sa zavola funkcia utok11()/utok12() ktoreho vysledky uklada
do premennej vitaz, podla ktorej bude pytat vstup pre vojaka; funkcia sa cyklicky opakuje, kym sa zivoty vsetkych bojovnikov jednej strany
nerovnaju 0, v tom pripade vracia hodnotu 10/20 a konci sa aj funkcia hra()*/
int suboje();
/*funkcia vypisuje vsetkych zivych bojovnikov*/
void vypis_udajov();
/*funkcie utok11() a utok12() pomocou nahodne generovanych cisel medzi vypocitanymi hranicami utocia. ak je hodnota utoku vyssia 
ako hodnota obrany obrancu, odpocitava sa zo zivota obrancu 1 zivot; funkcia konci predcasne, ak sa hodnota zivota jednej strany rovna nule*/
int utok11(int ironman, int cap);
int utok12(int ironman, int cap);
/*tu su definovane struktury hraca1 a hraca2*/
typedef struct hrac1 {
	char bojovnici1[5][100];
	int zivot;
	int utok;
	int obrana;
} HRAC1;
	
static HRAC1 meno1, vojak1[10], ATT1[5], DEF1[5];
	
typedef struct hrac2 {
	char bojovnici2[5][100];
	int zivot;
	int utok;
	int obrana;
} HRAC2;
	
static HRAC2 meno2, vojak2[10], ATT2[5], DEF2[5];

int main() {
	system("COLOR 4F");
	
	pomenovanie_hracov();
	system("pause");
	
	return 0;
}

void pomenovanie_hracov() {
	
	printf("Zadajte meno prveho hraca[#TeamIronMan]: ");
	scanf("%s", &hrac1);
	printf("Zadajte meno druheho hraca[#TeamCap]: ");
	scanf("%s", &hrac2);
	
	system("pause");
	system("cls");
	
	printf("hrac 1: %s\n", hrac1);
	printf("hrac 2: %s\n", hrac2);
	
	generacia_struktur();
}

void generacia_struktur() {
	int i;
	
	srand(time(NULL));
	
	//generacia hraca 1
	
	for(i = 0; i<=4; i++) {
		ATT1[i].utok = (rand() % 4) + 1;
		DEF1[i].obrana = 5 - ATT1[i].utok;
	}

	for(i = 0; i<= 4; i++) {
		vojak1[i].zivot = 5;
	}
	
	strcpy(meno1.bojovnici1[1], "Iron Man");
	strcpy(meno1.bojovnici1[2], "War Machine");
	strcpy(meno1.bojovnici1[3], "Black Widow");
	strcpy(meno1.bojovnici1[4], "Vision");
	strcpy(meno1.bojovnici1[5], "Spider-Man");
	
	//generacia hraca 2
	
	for(i = 0; i<=4; i++) {
		ATT2[i].utok = (rand() % 4) + 1;
		DEF2[i].obrana = 5 - ATT2[i].utok;
	}
	
	for(i = 0; i<= 4; i++) {
		vojak2[i].zivot = 5;
	}
	
	strcpy(meno2.bojovnici2[1], "Captain America");
	strcpy(meno2.bojovnici2[2], "Winter Soldier");
	strcpy(meno2.bojovnici2[3], "Falcon");
	strcpy(meno2.bojovnici2[4], "Ant-Man");
	strcpy(meno2.bojovnici2[5], "Scarlet Witch");
	
	vypis_udajov();
	hra();
}

void hra() {
	int koniec = 0;
	
	while (1) {
		if (koniec == 10) {
			printf("Vyhral #TeamCap [%s]\n", hrac2);
			break;
		}
		if (koniec == 20) {
			printf("Vyhral #TeamIronMan [%s]\n", hrac1);
			break;
		}
		koniec = suboje();
	}
}

int suboje() {
	int i;
	static int kolo = 1; 
	static int koniec;
	static int vitaz;
	
	srand(time(NULL));
	
	int ironman, cap;
		
	if ((kolo % 2) == 1) {
		if (kolo == 1) {
			printf("%s => Vyberte bojovnika do utoku: ", hrac1);
			scanf("%i", &ironman);
			
			printf("%s => Vyberte bojovnika do obrany: ", hrac2);
			scanf("%i", &cap);
			
		}
		else {
		
			if (vitaz == 1) {
				printf("Utocnik:\n Meno: %s\n Zivot: %i\n utok: %i\n obrana: %i\n\n", meno1.bojovnici1[ironman], vojak1[ironman - 1].zivot, ATT1[ironman - 1].utok, DEF1[ironman - 1].obrana);
				
				printf("%s => Vyberte bojovnika do obrany: ", hrac2);
				scanf("%i", &cap);
				while (vojak2[cap - 1].zivot < 1) {
					printf("neplatny vstup, vyberte ziveho bojovnika: ");
					scanf("%i", &cap);	
				}
				printf("Obranca:\n Meno: %s\n Zivot: %i\n utok: %i\n obrana: %i\n\n", meno2.bojovnici2[cap], vojak2[cap - 1].zivot, ATT2[cap - 1].utok, DEF2[cap - 1].obrana);
				system("pause");
			}
			if (vitaz == 2) {
				printf("Obranca:\n Meno: %s\n Zivot: %i\n utok: %i\n obrana: %i\n\n", meno2.bojovnici2[cap], vojak2[cap - 1].zivot, ATT2[cap - 1].utok, DEF2[cap - 1].obrana);
				printf("%s => Vyberte bojovnika do utoku: ", hrac1);
				scanf("%i", &ironman);
				while (vojak1[ironman - 1].zivot < 1) {
					printf("neplatny vstup, vyberte ziveho bojovnika: ");
					scanf("%i", &ironman);	
				}
				printf("Utocnik:\n Meno: %s\n Zivot: %i\n utok: %i\n obrana: %i\n\n", meno1.bojovnici1[ironman], vojak1[ironman - 1].zivot, ATT1[ironman - 1].utok, DEF1[ironman - 1].obrana);
				system("pause");
			}
		}
		vitaz = utok11(ironman, cap);
	}
	if ((kolo % 2) == 0) {
		if (vitaz == 2) {
			printf("Utocnik:\n Meno: %s\n Zivot: %i\n utok: %i\n obrana: %i\n\n", meno2.bojovnici2[cap], vojak2[cap - 1].zivot, ATT2[cap - 1].utok, DEF2[cap - 1].obrana);
			
			printf("%s => Vyberte bojovnika do obrany: ", hrac1);
			scanf("%i", &ironman);
			while (vojak1[ironman - 1].zivot < 1) {
				printf("neplatny vstup, vyberte ziveho bojovnika: ");
				scanf("%i", &ironman);	
			}
			printf("Obranca:\n Meno: %s\n Zivot: %i\n utok: %i\n obrana: %i\n\n", meno1.bojovnici1[ironman], vojak1[ironman - 1].zivot, ATT1[ironman - 1].utok, DEF1[ironman - 1].obrana);
			system("pause");
			
		}
		if (vitaz == 1) {
			printf("Obranca:\n Meno: %s\n Zivot: %i\n utok: %i\n obrana: %i\n\n", meno1.bojovnici1[ironman], vojak1[ironman - 1].zivot, ATT1[ironman - 1].utok, DEF1[ironman - 1].obrana);
			
			printf("%s => Vyberte bojovnika do utoku: ", hrac2);
			scanf("%i", &cap);
			while (vojak2[cap - 1].zivot < 1) {
				printf("neplatny vstup, vyberte ziveho bojovnika: ");
				scanf("%i", &cap);	
			}
			printf("Utocnik:\n Meno: %s\n Zivot: %i\n utok: %i\n obrana: %i\n\n", meno2.bojovnici2[cap], vojak2[cap - 1].zivot, ATT2[cap - 1].utok, DEF2[cap - 1].obrana);
			system("pause");
		}
		vitaz = utok12(ironman, cap);
	}
	
	if ((vojak1[0].zivot + vojak1[1].zivot + vojak1[2].zivot + vojak1[3].zivot + vojak1[4].zivot) == 0) {
		koniec = 10;
	}
	else if ((vojak2[0].zivot + vojak2[1].zivot + vojak2[2].zivot + vojak2[3].zivot + vojak2[4].zivot) == 0) {
		koniec = 20;
	}
	else {
		vypis_udajov();
	}
	
	kolo++;
	
	return koniec;
}

void vypis_udajov() {
	int i;
	printf("==============================\n");
	printf("#TeamIronMan:\n[%s]\n\n", hrac1);
	printf("==============================\n");
	printf("******************************\n");
	for (i = 0; i<= 4; i++) {
		if(vojak1[i].zivot > 0) {
		printf("Bojovnik %i: \n Meno: %s\n Zivot: %i\n utok: %i\n obrana: %i\n\n", i+1, meno1.bojovnici1[i+1], vojak1[i].zivot, ATT1[i].utok, DEF1[i].obrana);
		printf("******************************\n");
		}
	}
	printf("==============================\n");
	printf("#TeamCap:\n[%s]\n\n", hrac2);
	printf("==============================\n");
	printf("******************************\n");
	for (i = 0; i<= 4; i++) {
		if(vojak2[i].zivot > 0) {
		printf("Bojovnik %i: \n Meno: %s\n Zivot: %i\n utok: %i\n obrana: %i\n\n", i+1, meno2.bojovnici2[i+1], vojak2[i].zivot, ATT2[i].utok, DEF2[i].obrana);
		printf("******************************\n");
		}
	}
}

int utok11(int ironman, int cap) {
	int utok_max1, utok1, utok_max2, utok2, vitaz;
	
	while(1) {
		utok_max1 = ATT1[ironman - 1].utok + DEF2[cap - 1].obrana;
		utok1 = (rand() % utok_max1) + 1;
		
		if (utok1 > DEF2[cap - 1].obrana) {
			vojak2[cap - 1].zivot -= 1;
			printf("\n%s: Zasah, bojovnikovi \"%s\" ostava %i zivota\n", hrac1, meno2.bojovnici2[cap], vojak2[cap - 1].zivot);
		}
		else {
			printf("\n%s: Tesne vedla. %s ma zlu musku. :/\n", hrac1, meno1.bojovnici1[ironman]);
		}
		if (vojak2[cap - 1].zivot == 0) {
			vitaz = 1;
			printf("\n\nSuboj vyhral %s [%s]\n\n", meno1.bojovnici1[ironman], hrac1);
			system("pause");
			system("cls");
			break;
		}
		utok_max2 = ATT2[cap - 1].utok + DEF1[ironman - 1].obrana;
		utok2 = (rand() % utok_max2) + 1;
		
		if (utok2 > DEF1[ironman - 1].obrana) {
			vojak1[ironman - 1].zivot -= 1;
			printf("\n%s: Zasah, bojovnikovi \"%s\" ostava %i zivota\n", hrac2, meno1.bojovnici1[ironman], vojak1[ironman - 1].zivot);
		}
		else {
			printf("\n%s: Tesne vedla. %s ma zlu musku. :/\n", hrac2, meno2.bojovnici2[cap]);
		}
		if (vojak1[ironman - 1].zivot == 0) {
			vitaz = 2;
			printf("\n\nSuboj vyhral %s [%s]\n\n", meno2.bojovnici2[cap], hrac2);
			system("pause");
			system("cls");
			break;
		}
	}
	
	return vitaz;
}

int utok12(int ironman, int cap) {
	int utok_max1, utok1, utok_max2, utok2, vitaz;
	
	while(1) {
		utok_max2 = ATT2[cap - 1].utok + DEF1[ironman - 1].obrana;
		utok2 = (rand() % utok_max2) + 1;
		
		if (utok2 > DEF1[ironman - 1].obrana) {
			vojak1[ironman - 1].zivot -= 1;
			printf("\n%s: Zasah, bojovnikovi \"%s\" ostava %i zivota\n", hrac2, meno1.bojovnici1[ironman], vojak1[ironman - 1].zivot);
		}
		else {
			printf("\n%s: Tesne vedla. %s ma zlu musku. :/\n", hrac2, meno1.bojovnici1[cap]);
		}
		if (vojak1[ironman - 1].zivot == 0) {
			vitaz = 2;
			printf("\n\nSuboj vyhral %s [%s]\n\n", meno2.bojovnici2[cap], hrac2);
			system("pause");
			system("cls");
			break;
		}
		utok_max1 = ATT1[ironman - 1].utok + DEF2[cap - 1].obrana;
		utok1 = (rand() % utok_max1) + 1;
		
		if (utok1 > DEF2[cap - 1].obrana) {
			vojak2[cap - 1].zivot -= 1;
			printf("\n%s: Zasah, bojovnikovi \"%s\" ostava %i zivota\n", hrac1, meno2.bojovnici2[ironman], vojak2[ironman - 1].zivot);
		}
		else {
			printf("\n%s: Tesne vedla. %s ma zlu musku. :/\n", hrac1, meno1.bojovnici1[ironman]);
		}
		if (vojak2[cap - 1].zivot == 0) {
			vitaz = 1;
			printf("\n\nSuboj vyhral %s [%s]\n\n", meno1.bojovnici1[ironman], hrac1);
			system("pause");
			system("cls");
			break;
		}
	}
	
	return vitaz;
}
