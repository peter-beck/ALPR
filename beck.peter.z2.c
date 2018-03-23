/********************
Zadanie 2, ALPR
(c) Peter Beck
********************/
#include <stdio.h>									//vkladanie kniznic
#include <stdlib.h>
#include <time.h>
#include <stdlib.h>

#define S "Kombinacia na prvy hod kockami: "		//makro S

/*pomocou srand() sa  zaisti nahodne vyberanie cisiel funkciou rand(), hodnoty kociek sa ukladaju do pola kocka[6], zavola funkciu predcasny_vysledok ktora zisti, 
ake figury sa nachadzaju v prvom hode; pomocou pomocneho pola nahradi casti pola, ktore si hrac praje vymenit a spocita body pomocou funkcii, ktore testuju jednotlive figury*/
int hod_kockou();

/*nasledujuce funkcie testuju figury a vracaju body za ne*/
int postupka(int kocka1, int kocka2, int kocka3, int kocka4, int kocka5, int kocka6, int prepinac);
int dvojice(int kocka1, int kocka2, int kocka3, int kocka4, int kocka5, int kocka6, int prepinac);
int trojice(int kocka1, int kocka2, int kocka3, int kocka4, int kocka5, int kocka6, int prepinac);
int poker(int kocka1, int kocka2, int kocka3, int kocka4, int kocka5, int kocka6, int prepinac);
int penta(int kocka1, int kocka2, int kocka3, int kocka4, int kocka5, int kocka6, int prepinac);
int general(int kocka1, int kocka2, int kocka3, int kocka4, int kocka5, int kocka6, int prepinac);
int full_house(int kocka1, int kocka2, int kocka3, int kocka4, int kocka5, int kocka6, int prepinac);

/*testuje figury po prvom hode*/
int predcasny_vysledok(int kocka1, int kocka2, int kocka3, int kocka4, int kocka5, int kocka6, int prepinac);

/*pre jdnotlivych hracov volaju funkciu hod_kockou() a vracaju bodove hodnotenie z dosiahnutych figur*/
int hrac_1();
int hrac_2();
/*funkcia sa pyta, ci si uzivatel praje vypisat pravidla, pri stlaceni P alebo p ich vypise*/
void pravidla();

/*funkcia pyta pocet kol a systematicky vola funkcie hrac_1() a hrac_2(), ktorymi zbiera do premennych body, vypise stav a vitaza hry*/
void hra();


int main() {
	
	pravidla();			//volanie funkcii
	hra();
	
	return 0;
}
void hra() {
	int pocet_kol, kolo = 1, body_hrac1 = 0, body_hrac2 = 0, pomocna1, pomocna2, i, predcasny_koniec = 0;
	int test_figur1[10];
	int test_figur2[10];
	
	for (i=0; i<=6; i++) {
		test_figur1[i] = 0;
		test_figur2[i] = 0;
	}
	
	printf("Zadajte pocet kol: ");					
	scanf("%i", &pocet_kol);
	system("cls");											//zmazanie prikazoveho riadku
	
	while (kolo <= pocet_kol) {
		printf("STAV:\n Hrac 1: %i\n Hrac 2: %i\n", body_hrac1, body_hrac2);
		system("pause");
		system("cls");
		printf("Hrac 1\n%i. kolo z %i: \n\n", kolo, pocet_kol);
		pomocna1 = hrac_1();
		if (pomocna1 == 3) {
			test_figur1[0] = 1;
		}
		if (pomocna1 == 4) {
			test_figur1[1] = 1;
		}
		if (pomocna1 == 5) {
			test_figur1[2] = 1;
		}
		if (pomocna1 == 8) {
			test_figur1[3] = 1;
		}
		if (pomocna1 == 10) {
			test_figur1[4] = 1;
		}
		if (pomocna1 == 20) {
			test_figur1[5] = 1;
		}
		if (pomocna1 == 50) {
			test_figur1[6] = 1;
		}
		body_hrac1 += pomocna1;
		if ((test_figur1[0] + test_figur1[1] + test_figur1[2] + test_figur1[3] + test_figur1[4] + test_figur1[5] + test_figur1[6]) == 7) {
			predcasny_koniec = 1;
			printf("Dostali ste 10 bonusovych bodov za nazbieranie vsetkych figur.\n");
			body_hrac1 += 10;
		}
		system("pause");
		system("cls");
		printf("Hrac 2\n%i. kolo z %i: \n\n", kolo, pocet_kol);
		pomocna2 = hrac_2();
		if (pomocna2 == 3) {
			test_figur2[0] = 1;
		}
		if (pomocna2 == 4) {
			test_figur2[1] = 1;
		}
		if (pomocna2 == 5) {
			test_figur2[2] = 1;
		}
		if (pomocna2 == 8) {
			test_figur2[3] = 1;
		}
		if (pomocna2 == 10) {
			test_figur2[4] = 1;
		}
		if (pomocna2 == 20) {
			test_figur2[5] = 1;
		}
		if (pomocna2 == 50) {
			test_figur2[6] = 1;
		}
		body_hrac2 += pomocna2;
		if ((test_figur2[0] + test_figur2[1] + test_figur2[2] + test_figur2[3] + test_figur2[4] + test_figur2[5] + test_figur2[6]) == 7) {
			predcasny_koniec = 1;
			printf("Dostali ste 10 bonusovych bodov za nazbieranie vsetkych figur.\n");
			body_hrac2 += 10;
		}
		system("pause");
		system("cls");
		if (predcasny_koniec == 1) {
			break;
		}
		kolo++;
	}
	printf("STAV:\n Hrac 1: %i\n Hrac 2: %i\n", body_hrac1, body_hrac2);
	if (body_hrac1 > body_hrac2) {
		printf("\nVitazom je Hrac 1 s %i bodmi s naskokom %i bodov\n", body_hrac1, body_hrac1 - body_hrac2);
	}
	if (body_hrac2 > body_hrac1) {
		printf("\nVitazom je Hrac 2 s %i bodmi s naskokom %i bodov\n", body_hrac2, body_hrac2 - body_hrac1);
	}
	if (body_hrac1 == body_hrac2) {
		printf("\nBola to remiza.");
	}
	system("pause");
}
int hrac_1() {
	int body;
	
	body = hod_kockou();
	return body;
}
int hrac_2() {
	int body;
	
	body = hod_kockou();
	return body;
}

void pravidla() {
	int c;
	printf("Stlacte \"P\" pre zobrazenie pravidiel\n");
	c = getchar();
	switch (c) {
		case 'P' :
			printf("****************************************\n\n");
			printf("Zakladne pravidla: \n\tPOSTUPKA:\t\t3 BODY\n\t3 DVOJICE:\t\t4 BODY\n\t2 TROJICE:\t\t5 BODOV\n\tFULL HOUSE:\t\t8 BODOV\n\tPOKER(STVORICA):\t10 BODOV\n\tPENTA(PATICA):\t\t20 BODOV\n\tGENERAL(SESTICA):\t50 BODOV\n\n");
			printf("****************************************\n");
			system ("pause");
			break;
		case 'p' :
			printf("****************************************\n\n");
			printf("Zakladne pravidla: \n\tPOSTUPKA:\t\t3 BODY\n\t3 DVOJICE:\t\t4 BODY\n\t2 TROJICE:\t\t5 BODOV\n\tFULL HOUSE:\t\t8 BODOV\n\tPOKER(STVORICA):\t10 BODOV\n\tPENTA(PATICA):\t\t20 BODOV\n\tGENERAL(SESTICA):\t50 BODOV\n\n");
			printf("****************************************\n");
			system ("pause");
			break;
		default :
			break;	
	}
	system("cls");
}

int hod_kockou() {
	int hold, i = 0, cislo, body = 0, prepinac;
	int pole_hold[6];									//deklarania poli
	int kocka[6];
	
	printf("Prvy hod kockami:\n");
	
	srand(time(NULL));									//nastavenie srand() na nahodnu hodnotu
	
	kocka[0] = (rand() % 6) + 1;						//rand() nahodne vybera hodnoty pre jedtlive kocky a zapisujeme ich do pola
	kocka[1] = (rand() % 6) + 1;
	kocka[2] = (rand() % 6) + 1;
	kocka[3] = (rand() % 6) + 1;
	kocka[4] = (rand() % 6) + 1;
	kocka[5] = (rand() % 6) + 1;
	
	printf(" Kocka 1: %i\n Kocka 2: %i\n Kocka 3: %i\n Kocka 4: %i\n Kocka 5: %i\n Kocka 6: %i\n\n", kocka[0], kocka[1], kocka[2], kocka[3], kocka[4], kocka[5]);
	
	prepinac = 0;
	predcasny_vysledok(kocka[0], kocka[1], kocka[2], kocka[3], kocka[4], kocka[5], prepinac);
	
	printf("\n\nKolkymi kockami si prajete hodit este raz? ");
	scanf("%i", &hold);
	if (hold > 0) {																			//ak chceme hodit este raz s kockami(hold je nenulovy, nasledujuce prikazy sa spustia
		printf("\nZadajte poradove cisla kociek, s ktorymi si prajete hodit este raz\n");
		while (i < hold) {																	//pomocou pomocneho pola sa prepisu kocky, ktore chceme hodit znova
			printf("%i. cislo: ", i+1);
			scanf("%i", &cislo);
			pole_hold[i] = cislo;
			srand(time(NULL));
			kocka[(pole_hold[i]) - 1] = (rand() % 6) + 1;
			i++;
		}
		printf("\nDruhy hod kockami: \n");
		printf(" Kocka 1: %i\n Kocka 2: %i\n Kocka 3: %i\n Kocka 4: %i\n Kocka 5: %i\n Kocka 6: %i\n\n", kocka[0], kocka[1], kocka[2], kocka[3], kocka[4], kocka[5]);
	}
	prepinac = 1;
	
	body = body + postupka(kocka[0], kocka[1], kocka[2], kocka[3], kocka[4], kocka[5], prepinac);			//pripocitaju sa body pomocou testov na figury
	body = body + dvojice(kocka[0], kocka[1], kocka[2], kocka[3], kocka[4], kocka[5], prepinac);
	body = body + trojice(kocka[0], kocka[1], kocka[2], kocka[3], kocka[4], kocka[5], prepinac);
	body = body + poker(kocka[0], kocka[1], kocka[2], kocka[3], kocka[4], kocka[5], prepinac);
	body = body + penta(kocka[0], kocka[1], kocka[2], kocka[3], kocka[4], kocka[5], prepinac);
	body = body + general(kocka[0], kocka[1], kocka[2], kocka[3], kocka[4], kocka[5], prepinac);
	body = body + full_house(kocka[0], kocka[1], kocka[2], kocka[3], kocka[4], kocka[5], prepinac);
	
	return body;
}

int predcasny_vysledok(int kocka1, int kocka2, int kocka3, int kocka4, int kocka5, int kocka6, int prepinac) {
	int pomocna = 0;
	
	if((postupka(kocka1, kocka2, kocka3, kocka4, kocka5, kocka6, prepinac)) != 0) {				//testuju sa jednotlive figury
		printf("%s%s", S, "Postupka za 3 body");
	}
	else {
		pomocna += 1;
	}
	if((dvojice(kocka1, kocka2, kocka3, kocka4, kocka5, kocka6, prepinac)) != 0) {
		printf("%s%s", S, "Dvojice za 4 body");
	}
	else {
		pomocna += 1;
	}
	if((trojice(kocka1, kocka2, kocka3, kocka4, kocka5, kocka6, prepinac)) != 0) {
		printf("%s%s", S, "Trojice za 5 bodov");
	}
	else {
		pomocna += 1;
	}
	if((poker(kocka1, kocka2, kocka3, kocka4, kocka5, kocka6, prepinac)) != 0) {
		printf("%s%s", S, "Poker za 10 bodov");
	}
	else {
		pomocna += 1;
	}
	if((penta(kocka1, kocka2, kocka3, kocka4, kocka5, kocka6, prepinac)) != 0) {
		printf("%s%s", S, "Penta za 20 bodov");
	}
	else {
		pomocna += 1;
	}
	if((general(kocka1, kocka2, kocka3, kocka4, kocka5, kocka6, prepinac)) != 0) {
		printf("%s%s", S, "General za 50 bodov");
	}
	else {
		pomocna += 1;
	}
	if((full_house(kocka1, kocka2, kocka3, kocka4, kocka5, kocka6, prepinac)) != 0) {
		printf("%s%s", S, "Full House za 8 bodov");
	}
	else {
		pomocna += 1;
	}
	
	if (pomocna == 7) {													//ak sa ziadna figura nevyskytla, pomocna sa bude rovnat 7
		printf("Ziadna znama kombinacia nedosiahnuta.");
	}
}

int postupka(int kocka1, int kocka2, int kocka3, int kocka4, int kocka5, int kocka6, int prepinac) {
	int i, jedna = 0, dva = 0, tri = 0, styri = 0, pat = 0, sest = 0;
	int body = 0;
	int pomocne_pole[6];
	
	pomocne_pole[0] = kocka1;								//do pomocneho pola sa zapisu hodnoty kociek
	pomocne_pole[1] = kocka2;
	pomocne_pole[2] = kocka3;
	pomocne_pole[3] = kocka4;
	pomocne_pole[4] = kocka5;
	pomocne_pole[5] = kocka6;
	
	if((kocka1+kocka2+kocka3+kocka4+kocka5+kocka6) == 21) {		//test
		for(i=0; i<=5; i++) {
			if ((pomocne_pole[i]) == 1) {
				jedna++;
			}
			if ((pomocne_pole[i]) == 2) {
				dva++;
			}
			if ((pomocne_pole[i]) == 3) {
				tri++;
			}
			if ((pomocne_pole[i]) == 4) {
				styri++;
			}
			if ((pomocne_pole[i]) == 5) {
				pat++;
			}
			if ((pomocne_pole[i]) == 6) {
				sest++;
			}
		}
		if ((jedna && dva && tri && styri && pat && sest) != 0) {	//test
			body = 3;
			if (prepinac == 1) {
				printf("Postupka, ziskavate 3 body\n");
			}
			if (prepinac == 0) {
				;
			}
		}
	}
	return body;
}

int dvojice(int kocka1, int kocka2, int kocka3, int kocka4, int kocka5, int kocka6, int prepinac) {
	int i, jedna = 0, dva = 0, tri = 0, styri = 0, pat = 0, sest = 0;
	int body = 0;
	int pomocne_pole[6];
	
	pomocne_pole[0] = kocka1;
	pomocne_pole[1] = kocka2;
	pomocne_pole[2] = kocka3;
	pomocne_pole[3] = kocka4;
	pomocne_pole[4] = kocka5;
	pomocne_pole[5] = kocka6;
	
	for(i=0; i<=5; i++) {
		if ((pomocne_pole[i]) == 1) {
			jedna++;
		}
		if ((pomocne_pole[i]) == 2) {
			dva++;
		}
		if ((pomocne_pole[i]) == 3) {
			tri++;
		}
		if ((pomocne_pole[i]) == 4) {
			styri++;
		}
		if ((pomocne_pole[i]) == 5) {
			pat++;
		}
		if ((pomocne_pole[i]) == 6) {
			sest++;
		}
	}
	if ((jedna == 2 || dva == 2 || tri == 2 || styri == 2 || pat == 2 || sest == 2) && (jedna == 0 || dva == 0 || tri == 0 || styri == 0 || pat == 0 || sest == 0)) {
		if ((jedna != 1 && dva != 1 && tri != 1 && styri != 1 && pat != 1 && sest != 1) && (jedna != 3 && dva != 3 && tri != 3 && styri != 3 && pat != 3 && sest != 3) && (jedna != 4 && dva != 4 && tri != 4 && styri != 4 && pat != 4 && sest != 4)) {
			body = 4;
			if (prepinac == 1) {
				printf("Dvojice, ziskavate 4 body\n");
			}
			if (prepinac == 0) {
				;
			}
		}
	}
	return body;
}

int trojice(int kocka1, int kocka2, int kocka3, int kocka4, int kocka5, int kocka6, int prepinac) {
	int i, jedna = 0, dva = 0, tri = 0, styri = 0, pat = 0, sest = 0;
	int body = 0;
	int pomocne_pole[6];
	
	pomocne_pole[0] = kocka1;
	pomocne_pole[1] = kocka2;
	pomocne_pole[2] = kocka3;
	pomocne_pole[3] = kocka4;
	pomocne_pole[4] = kocka5;
	pomocne_pole[5] = kocka6;
	
	for(i=0; i<=5; i++) {
		if ((pomocne_pole[i]) == 1) {
			jedna++;
		}
		if ((pomocne_pole[i]) == 2) {
			dva++;
		}
		if ((pomocne_pole[i]) == 3) {
			tri++;
		}
		if ((pomocne_pole[i]) == 4) {
			styri++;
		}
		if ((pomocne_pole[i]) == 5) {
			pat++;
		}
		if ((pomocne_pole[i]) == 6) {
			sest++;
		}
	}
	if ((jedna == 3 || dva == 3 || tri == 3 || styri == 3 || pat == 3 || sest == 3) && (jedna == 0 || dva == 0 || tri == 0 || styri == 0 || pat == 0 || sest == 0)) {
		if ((jedna != 1 && dva != 1 && tri != 1 && styri != 1 && pat != 1 && sest != 1) && (jedna != 2 && dva != 2 && tri != 2 && styri != 2 && pat != 2 && sest != 2)) {
			body = 5;
			if (prepinac == 1) {
				printf("Trojice, ziskavate 5 bodov\n");
			}
			if (prepinac == 0) {
				;
			}
		}
	}
	return body;
}

int poker(int kocka1, int kocka2, int kocka3, int kocka4, int kocka5, int kocka6, int prepinac) {
	int i, jedna = 0, dva = 0, tri = 0, styri = 0, pat = 0, sest = 0;
	int body = 0;
	int pomocne_pole[6];
	
	pomocne_pole[0] = kocka1;
	pomocne_pole[1] = kocka2;
	pomocne_pole[2] = kocka3;
	pomocne_pole[3] = kocka4;
	pomocne_pole[4] = kocka5;
	pomocne_pole[5] = kocka6;
	
	for(i=0; i<=5; i++) {
		if ((pomocne_pole[i]) == 1) {
			jedna++;
		}
		if ((pomocne_pole[i]) == 2) {
			dva++;
		}
		if ((pomocne_pole[i]) == 3) {
			tri++;
		}
		if ((pomocne_pole[i]) == 4) {
			styri++;
		}
		if ((pomocne_pole[i]) == 5) {
			pat++;
		}
		if ((pomocne_pole[i]) == 6) {
			sest++;
		}
	}
	if (jedna == 4 || dva == 4 || tri == 4 || styri == 4 || pat == 4 || sest == 4) {
		body = 10;
		if (prepinac == 1) {
				printf("Poker, ziskavate 10 bodov\n");
			}
			if (prepinac == 0) {
				;
			}
	}
	return body;
}

int penta(int kocka1, int kocka2, int kocka3, int kocka4, int kocka5, int kocka6, int prepinac) {
	int i, jedna = 0, dva = 0, tri = 0, styri = 0, pat = 0, sest = 0;
	int body = 0;
	int pomocne_pole[6];
	
	pomocne_pole[0] = kocka1;
	pomocne_pole[1] = kocka2;
	pomocne_pole[2] = kocka3;
	pomocne_pole[3] = kocka4;
	pomocne_pole[4] = kocka5;
	pomocne_pole[5] = kocka6;
	
	for(i=0; i<=5; i++) {
		if ((pomocne_pole[i]) == 1) {
			jedna++;
		}
		if ((pomocne_pole[i]) == 2) {
			dva++;
		}
		if ((pomocne_pole[i]) == 3) {
			tri++;
		}
		if ((pomocne_pole[i]) == 4) {
			styri++;
		}
		if ((pomocne_pole[i]) == 5) {
			pat++;
		}
		if ((pomocne_pole[i]) == 6) {
			sest++;
		}
	}
	if (jedna == 5 || dva == 5 || tri == 5 || styri == 5 || pat == 5 || sest == 5) {
		body = 20;
		if (prepinac == 1) {
				printf("Penta, ziskavate 20 bodov\n");
			}
			if (prepinac == 0) {
				;
			}
	}
	return body;
}

int general(int kocka1, int kocka2, int kocka3, int kocka4, int kocka5, int kocka6, int prepinac) {
	int i, jedna = 0, dva = 0, tri = 0, styri = 0, pat = 0, sest = 0;
	int body = 0;
	int pomocne_pole[6];
	
	pomocne_pole[0] = kocka1;
	pomocne_pole[1] = kocka2;
	pomocne_pole[2] = kocka3;
	pomocne_pole[3] = kocka4;
	pomocne_pole[4] = kocka5;
	pomocne_pole[5] = kocka6;
	
	for(i=0; i<=5; i++) {
		if ((pomocne_pole[i]) == 1) {
			jedna++;
		}
		if ((pomocne_pole[i]) == 2) {
			dva++;
		}
		if ((pomocne_pole[i]) == 3) {
			tri++;
		}
		if ((pomocne_pole[i]) == 4) {
			styri++;
		}
		if ((pomocne_pole[i]) == 5) {
			pat++;
		}
		if ((pomocne_pole[i]) == 6) {
			sest++;
		}
	}
	if (jedna == 6 || dva == 6 || tri == 6 || styri == 6 || pat == 6 || sest == 6) {
		body = 50;
		if (prepinac == 1) {
				printf("General, ziskavate 50 bodov\n");
			}
			if (prepinac == 0) {
				;
			}
	}
	return body;
}
int full_house(int kocka1, int kocka2, int kocka3, int kocka4, int kocka5, int kocka6, int prepinac) {
	int i, jedna = 0, dva = 0, tri = 0, styri = 0, pat = 0, sest = 0;
	int body = 0;
	int pomocne_pole[6];
	
	pomocne_pole[0] = kocka1;
	pomocne_pole[1] = kocka2;
	pomocne_pole[2] = kocka3;
	pomocne_pole[3] = kocka4;
	pomocne_pole[4] = kocka5;
	pomocne_pole[5] = kocka6;
	
	for(i=0; i<=5; i++) {
		if ((pomocne_pole[i]) == 1) {
			jedna++;
		}
		if ((pomocne_pole[i]) == 2) {
			dva++;
		}
		if ((pomocne_pole[i]) == 3) {
			tri++;
		}
		if ((pomocne_pole[i]) == 4) {
			styri++;
		}
		if ((pomocne_pole[i]) == 5) {
			pat++;
		}
		if ((pomocne_pole[i]) == 6) {
			sest++;
		}
	}
	if ((jedna == 3 || dva == 3 || tri == 3 || styri == 3 || pat == 3 || sest == 3) && (jedna == 2 || dva == 2 || tri == 2 || styri == 2 || pat == 2 || sest == 2)) {
		body = 8;
		if (prepinac == 1) {
				printf("Full House, ziskavate 8 bodov\n");
			}
			if (prepinac == 0) {
				;
			}
	}
	return body;
}

