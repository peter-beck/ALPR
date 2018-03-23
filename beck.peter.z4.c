/*************************
Zadanie 4, ALPR
(c) Peter Beck
*************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*podla zadaneho nazvu subora otvori subor, ak sa nachadza v rovnakom adresari, ak sa nenachadza, treba zadat celu cestu k suboru;
do premennej pocet spocita pocet znakov v subore a vracia hodnotu premennej pocet*/
int pocet_znakov(char (*subor)[100]);
/*otvori opat zadany subor a pomocny subor; do pola veta[] sa uklada text z textoveho suboru, pricom velkost pola zavisi od premennej dlzka, vsetky znaky sa premienaju na medzeru a velke
pismena na male; pomocou funkcie strtok() sa rozdeli text v poli na tokeny(slova), tie sa ukladaju pod seba do textoveho subora, funkcia vracia pocet slov*/
int rozdelenie_na_slova(int dlzka, char (*subor)[100]);
/*funkcia nacitava slova z pomocneho suboru do pola a vola funkciu anagramy()*/
int slova_do_pola(int pocet_slov);
/*funkcia porovnava slova v poli, ak su rovnakeho poctu pismen, prebieha skuska, ci su slova anagramy, na konci sa este odskusa, ci sa retazce nerovnaju, ak nie, slova su anagram*/
void anagramy(char (*slova)[20], int pocet_slov);
/*do dvoch poli s hodnotami 0 sa inkrementuju miesta pismeniek na jednotky, na konci sa porovnaju, ak sa rovnaju polia, su to potencionalne anagramy*/
int skuska_anagramov(int i, int j, char (*slova)[20]);
/*porovnavaju sa dlzky dvoch retazcov, ak sa rovnaju, vracia 1, ak nie, vracia 0*/
int pocet_pismen(int i, int j, char (*slova)[20]);

int main() {
	int dlzka, pocet_slov;
	char subor[1][100];
	
	printf("Zadajte nazov suboru: ");
	scanf("%s", subor[0]);
	
	dlzka = pocet_znakov(subor);
	if (dlzka == 1) {
		return 1;
	}
	pocet_slov = rozdelenie_na_slova(dlzka, subor);
	slova_do_pola(pocet_slov);
	
	return 0;
}

int pocet_pismen(int i, int j, char (*slova)[20]) {
	
	if ((strlen(slova[i])) == strlen(slova[j])) {
		return 1;
	}
	else {
		return 0;
	}
}

int skuska_anagramov(int i, int j, char (*slova)[20]) {
	int pole1[26] = {0}, pole2[26] = {0}, x = 0; 
 
	while (slova[i][x] != '\0') {
    	pole1[slova[i][x]-'a']++;
    	x++;
	}
	x = 0;
	while (slova[j][x] != '\0') {
    	pole2[slova[j][x]-'a']++;
    	x++;
	}
	for (x = 0; x < 26; x++) {
   		if (pole1[x] != pole2[x])
    	return 0;
	}
	return 1;
}

void anagramy(char (*slova)[20], int pocet_slov) {
	int i, j, anagram, prve_slovo, pocet;
	
	for(i=0; i<pocet_slov; i++) {
		prve_slovo = 1;
		pocet = 0;
		for(j=i+1; j<=pocet_slov; j++) {
			if (pocet_pismen(i, j, slova) == 1) {
				anagram = skuska_anagramov(i, j, slova);
				if (strcmp(slova[i], slova[j]) == 0) {
					anagram += 1;
				}
				if (anagram == 1) {
					if (prve_slovo == 1) {
						printf("%s ", slova[i]);
						prve_slovo++;
						pocet++;
					}
					printf("%s ", slova[j]);
					strcpy(slova[j], "0");
				}
			}
			
		}
		if (pocet > 0) {
			printf("\n");
		}
	}
}

int slova_do_pola(int pocet_slov) {
	FILE *fr;
	int i = 0;
	char slova[pocet_slov][20];
	
	if((fr = fopen("pomocny_txt.txt", "r")) == NULL) {
		printf("subor pomocny_txt.txt sa nepodarilo otvorit");
		return 1;
	}
	while (i < pocet_slov) {
		fscanf(fr, "%s\n", slova[i]);
		i++;
	}
	
	anagramy(slova, pocet_slov);
	
	if (fclose(fr) == EOF) {
		printf("subor pomocny_txt.txt sa nepodarilo zatvorit");
		return 1;
	}
	return 500;
}

int rozdelenie_na_slova(int dlzka, char (*subor)[100]) {
	char veta[dlzka+1];
	char oddelovac[] = " ";
	char *p_pomocny;
	FILE *fr, *fw;
	int i, pocet_slov = 1, c;
	
	if((fr = fopen(subor[0], "r")) == NULL) {
		printf("subor %s sa nepodarilo otvorit", subor[0]);
		return 1;
	}
	if((fw = fopen("pomocny_txt.txt", "w")) == NULL) {
		printf("subor pomocny_txt.txt sa nepodarilo otvorit");
		return 1;
	}
	
	for(i=0; i<=dlzka; i++) {
		if (((c = getc(fr)) >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) {
			if (c >= 'A' && c <= 'Z') {
				c = tolower(c);
			}
			veta[i] = c;
		}
		else {
			c = ' ';
			veta[i] = c;
		}	
	}
	
	p_pomocny = (char *) malloc(sizeof(char));
	
	p_pomocny = strtok(veta, oddelovac); 
	fprintf(fw,"%s\n",p_pomocny);
	
	while (p_pomocny != NULL) {
		p_pomocny = strtok(NULL, oddelovac);
		fprintf(fw,"%s\n",p_pomocny);
		pocet_slov++;
	}
	
	if (fclose(fr) == EOF) {
		printf("subor %s sa nepodarilo zatvorit", subor[0]);
		return 1;
	}
	if (fclose(fw) == EOF) {
		printf("subor pomocny_txt.txt sa nepodarilo zatvorit");
		return 1;
	}
	return pocet_slov;
}

int pocet_znakov(char (*subor)[100]) {
	int pocet = 0;
	FILE *fr;
	
	if((fr = fopen(subor[0], "r")) == NULL) {
		printf("subor %s sa nepodarilo otvorit", subor[0]);
		return 1;
	}
	while (getc(fr) != EOF) {
		pocet++;
	}
	if (fclose(fr) == EOF) {
		printf("subor %s sa nepodarilo zatvorit", subor[0]);
		return 1;
	}
	
	return pocet;
}
