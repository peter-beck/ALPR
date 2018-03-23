/********************************************************************************
zadanie cislo 1, ALPR LS 2015/2016
(c) Peter Beck

ZDROJE:
http://www.hypotekarna-kalkulacka.sk/ 
-> kalkulacka+splatkovy kalendar s periodicitou 12 splatok rocne

http://www.aristoteles.cz/matematika/financni_matematika/hypoteka-vypocet.php
->prilozeny .xls subor ponukany na stiahnutie
->vypocet rocnej splatky a splatkoveho kalendara s periodicitou 1 splatka rocne
********************************************************************************/

#include <stdio.h>
#include <math.h>

/*funkcia na zaklade sumy, uroku a doby splacania vypocita mesacnu splatku*/
double vyska_splatky( double suma, double urok_percenta, double roky_splacania);								//deklaracia funkcii
/*funkcia na zaklade mesacnej splatky, rokov splacania a pozicanej sumy vypocita sumu, ktoru musime zaplatit a tu, ktoru platime navyse*/
double zaplatene(double mes_splatka, double roky_splacania, double suma);
/*funkcia ma za ulohu vypisat splatkovy kalendar, podla volby uzivatela, funkcia necaka navratovu hodnotu*/
void kalendar(int podm_vyber, double suma, double urok_percenta, double roky_splacania, double mes_splatka);

int main() {
	double mes_splatka;												//deklaracia premennych
	double suma, urok_percenta, roky_splacania, uver_plus_urok;
	int podm_vyber;

    printf("zadajte sumu pozicanych penazi: ");						//program vypyta od uzivatela sumu uveru
    scanf("%lf",&suma);												//suma sa ulozi do premennej suma

    printf("zadajte urok v percentach: ");							//program vypyta od uzivatela urok v percentach
    scanf("%lf",&urok_percenta);									//urok sa ulozi do premennej urok_percenta

    printf("zadajte pocet rokov splacania: ");						//program vypyta od uzivatela pocet rokov splacania
    scanf("%lf",&roky_splacania);									//roky sa ulozia do premennej roky_splacania

	mes_splatka = vyska_splatky(suma, urok_percenta, roky_splacania);	//volanie funkcie vyska_splatky(), vysledok sa ulozi do premennej mes_splatka
	uver_plus_urok = zaplatene(mes_splatka, roky_splacania, suma);		//volanie funkcie zaplatene(), vysledok sa ulozi do premennej uver_plus_urok
	
	printf("Chcete vypisat splatkovy kalendar? \n[1=Rocne, 2=Mesacne, iny vyber=ukoncenie programu]: ");	//program sa spyta, ci uzivatel chce vypisat kalendar a da mu moznosti
	scanf("%i", &podm_vyber);																				//odpoved sa ulozila do premennej podm_vyber
	kalendar(podm_vyber, suma, urok_percenta, roky_splacania, mes_splatka);									//volanie funkcie kalendar()

    return 0;																								//program vracia funkcii main hodnotu 0, program sa ukonci
}
void kalendar(int podm_vyber, double suma, double urok_percenta, double roky_splacania, double mes_splatka) { 
	double rocna_urokova_sadzba = (urok_percenta/100);					//deklaracia premennych
	int mesiac = 1;
	int rok = 1;
	
	if (podm_vyber == 1) {												//pri volbe uzivatela pre vypis rocneho kalendara sa spusti tato vetva, pretoze podm_vyber = 1
		double pomocna = 1/(1+rocna_urokova_sadzba);					//deklaracia a vypocet hodnot premennych
		double splatka = ((rocna_urokova_sadzba*suma)/(1-(pow(pomocna, roky_splacania)))), urok = suma*rocna_urokova_sadzba, umor = (splatka-(suma*rocna_urokova_sadzba)), dlh = (suma-(splatka-(suma*rocna_urokova_sadzba)));
		
		printf("\nPociatocny dlh: %.2lfeur\n", suma);					//vypis dlhu
		
		while (rok <= roky_splacania) {									//cyklus while vypisuje a prepocitava hodnoty splatky pri mesacnom, uroku, umora a dlhu kym sa pocet rokov nerovna roku zadanym uzivatelom
			printf("\n%2i. rok:\n", rok);								//na konci cyklu by sa dlh mal rovnat 0 a program sa odzdravi.
			printf(" splatka: %.2lfeur\n urok: %.2lfeur\n umor: %.2lfeur\n stav dlhu: %.2lfeur\n", splatka, urok, umor, dlh);
			urok = dlh *rocna_urokova_sadzba;
			umor = splatka - urok;
			dlh = dlh - umor;
			
			rok++;
		}
		printf("\nDovidenia!\n");
	}
	else if (podm_vyber == 2) {											//pri volbe uzivatela pre vypis mesacneho kalendara sa spusti tato vetva, pretoze podm_vyber = 2
		double mes_urokova_sadzba = rocna_urokova_sadzba/12;			//deklaracia a vypocet hodnot premennych
		double splatka = mes_splatka, urok = suma*mes_urokova_sadzba, umor = (mes_splatka-(suma*mes_urokova_sadzba)), dlh = (suma-(mes_splatka-(suma*mes_urokova_sadzba)));
		
		printf("\nPociatocny dlh: %.2lfeur\n", suma);					//vypis dlhu
		
		while (mesiac <= roky_splacania*12) {							//cyklus while vypisuje a prepocitava hodnoty splatky pri rocnom splacani(splatka sa pocitala rozdielne), uroku, umoru a dlhu kym sa pocet rokov nerovna roku zadanym uzivatelom
			printf("\n%3i. mesiac: \n", mesiac);						//na konci cyklu by sa dlh mal rovnat 0 a program sa odzdravi.
			printf(" splatka: %.2lfeur\n urok: %.2lfeur\n umor: %.2lfeur\n stav dlhu: %.2lfeur\n", splatka, urok, umor, dlh);
			urok = dlh *mes_urokova_sadzba;
			umor = splatka - urok;
			dlh = dlh - umor;
			
			mesiac++;
		}
		printf("\nDovidenia!\n");
	}
	else {																//pri volbe uzivatela ukoncit program sa program odzdravi a vypne, pretoze podm_vyber ~= 1 || 2
		printf("\nDovidenia!\n");
	}
}
double zaplatene(double mes_splatka, double roky_splacania, double suma) {		
	double uver_plus_urok;														//deklaracia premennej
	
	uver_plus_urok=mes_splatka*roky_splacania*12;								//vypocet
	
	printf("\nspolu zaplatene: %.2lfeur\n", uver_plus_urok);					//vypis na obrazovku
	printf("pozicana suma: %.2lfeur\n", suma);
	printf("preplatite: %.2lfeur\n\n", uver_plus_urok-suma);
	return uver_plus_urok;														//funkcia vracia hodnotu uver_plus_urok
}

double vyska_splatky(double suma, double urok_percenta,double roky_splacania) { 	
	double mes_splatka, pocet_splatok_mes, urokova_sadzba; 							//deklaracia premennych
   

    pocet_splatok_mes=roky_splacania*12;											//vypocty
    urokova_sadzba=(urok_percenta/12)/100;
    mes_splatka=suma*(urokova_sadzba/(1-(1/pow((1+urokova_sadzba),pocet_splatok_mes))));

    printf("vyska mesacnej splatky: %.2lfeur\n", mes_splatka);						//vypis mesacne splatky
    
    return mes_splatka;																//funkcia vracia hodnotu mes_splatka
}