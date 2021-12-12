/*
 *
 *
 * Program pro praci s maticemi
 * ============================
 *
 * D. Novak, 12/2021
 *
 */
/*
TODO:
1) funkce dimenze, vraci velikost matice DONE
2) ERROR MSGS PARTLY DONE
3) cteni ze souboru DONE
4) fce na delokovani pameti DONE
*/

#include <stdio.h>
#include <stdlib.h>

#include "matice.h"

// Error symbolic constants

#define BEZ_CHYBY "Nedoslo k chybe \n"
#define CHYBA_ALOKACE "Chyba pri alokaci pameti \n"
#define CHYBA_OTEVRENI "Chyba pri otevirani souboru \n"
#define CHYBA_ZAVRENI "Chyba pri zavirani souboru \n"
#define CHYBA_TYPU "Chyba pri provadeni operaci s nespravnou velikosti \n"
#define CHYBA_JINA "Ostatni chyby \n"

// Define prvek

#define prvk(mtc, i, j) \
    mtc.data[(j-1) * mtc.radky + (i-1)]

Matice inicializace(int radky, int sloupce) {
  Matice matrix;
  matrix.data = (float*) malloc(sizeof(float)*radky*sloupce);
  matrix.radky = radky;
  matrix.sloupce = sloupce;
  int i;
  for (i = 0; i < radky*sloupce; i++)
    matrix.data[i] = 0.0;
  return matrix;
}


Matice nulova(int radky, int sloupce) {

  Matice nula = inicializace(radky, sloupce);
  int i;
  for (i = 0; i < radky * sloupce; i++)
    nula.data[i] = 0.0;
  return nula;
}


Matice jednotkova(int radky, int sloupce) {
  Matice one = inicializace(radky, sloupce);
  int i, j;
  for (j = 0; j <= one.sloupce; j++)
    for (i = 0; i <= one.radky; i++)
      if (i == j)
        prvk(one, i, j) = 1;
      else
        prvk(one, i, j) = 0;
  return one;
}


void odstran(Matice mat) {
  free(mat.data);
}


void vypis(Matice mat) {
  int i, j;
  for (i = 0; i < mat.radky; i++) {
    for (j = 0; j < mat.sloupce; j++) {
      printf("% 6.6f ", prvk(mat, i, j));
    }
    printf("\n");
  }
}


Matice plus(Matice mat1, Matice mat2) {
  Matice scitani = inicializace(mat1.radky, mat1.sloupce);


  if(mat1.radky != mat2.radky){
    printf("%s", CHYBA_TYPU);
    return scitani;
  }

   if(mat1.sloupce != mat2.sloupce){
    printf("%s", CHYBA_TYPU);
    return scitani;
  }

  int i, j;
  for (i = 0; i <= mat1.radky; i++)
    for (j = 0; j <= mat1.sloupce; j++)
      prvk(scitani, i, j) =
        prvk(mat1, i, j) + prvk(mat2, i, j);
  return scitani;
}


Matice minus(Matice mat1, Matice mat2) {
  Matice odecitani = inicializace(mat1.radky, mat1.sloupce);

  if(mat1.radky != mat2.radky){
    printf("%s", CHYBA_TYPU);
    return odecitani;
  }

   if(mat1.sloupce != mat2.sloupce){
    printf("%s", CHYBA_TYPU);
    return odecitani;
  }

  int i, j;
  for (i = 0; i <= mat1.radky; i++)
    for (j = 0; j <= mat1.sloupce; j++)
      prvk(odecitani, i, j) =
        prvk(mat1, i, j) - prvk(mat2, i, j);
  return odecitani;
}


Matice nasobeni(Matice mat1, Matice mat2) {
  Matice nasob = inicializace(mat1.radky, mat2.sloupce);

  if(mat1.radky != mat2.radky){
    printf("%s", CHYBA_TYPU);
    return nasob;
  }

   if(mat1.sloupce != mat2.sloupce){
    printf("%s", CHYBA_TYPU);
    return nasob;
  }

  int i, j, k;
  for (i = 0; i <= mat1.radky; i++)
    for (j = 0; j <= mat2.sloupce; j++) {
      float hodnota = 0.0;
      for (k = 0; k <= mat2.radky; k++)
        hodnota += prvk(mat1, i, k) * prvk(mat2, k, j);
      prvk(nasob, i, j) = hodnota;
    }
  return nasob;
}


Matice transpozice(Matice mat) {
  Matice trans = inicializace(mat.radky, mat.sloupce);
  int i, j;
  for (i = 0; i <= mat.radky; i++)
    for (j = 0; j <= mat.sloupce; j++)
       prvk(trans, j, i) = prvk(mat, i, j);
  return trans;
}


Matice krat(Matice mat, float skalar) {
  Matice nasob = inicializace(mat.radky, mat.sloupce);
  int i, j;
  for (i = 0; i <= mat.radky; i++)
    for (j = 0; j <= mat.sloupce; j++)
      prvk(nasob, i, j) = (prvk(mat, i, j)) * skalar;
  return nasob;
}

int nacti_ze_souboru(const char *soubor){

    FILE *f;
    float M[3][3]={{'0','0'}};
    f = fopen("load.txt", "r");

    if (f == NULL){
        printf("%s", CHYBA_OTEVRENI);
        return 1;
    }

    int i,j;

    for(i=0; i<3; i++){
        for(j=0; j<3; j++){
            fscanf(f, "%f%*c",&M[i][j]);
            printf("%f %c", M[i][j], " \n"[j+1 == 3]);
        }
    }
    fclose(f);
    /*if (f != NULL){
        printf("%s", CHYBA_ZAVRENI);
        return 1;
    }*/
    return 0;
}

void uloz_do_souboru(Matice mtx, const char *soubor) {

  int i, j;
  FILE *f = fopen(soubor, "w");
  for (i = 0; i < mtx.radky; i++) {
    for (j = 0; j < mtx.sloupce; j++) {
            fprintf(f, "%f %c", prvk(mtx, i, j), " \n"[j+1 == mtx.sloupce]);
        }
    }
    fclose(f);
}

float prvek(Matice mat, int i, int j, float hodnota) {
  hodnota = prvk(mat, i, j);
  return hodnota;
}

void nastav_prvek(Matice mat, int i, int j, float hodnota) {
  prvk(mat, i, j) = hodnota;
  return;
}

int velikost(Matice mat, int dimenze) {
    int vel_dimenze;

    if (dimenze == 1){
        vel_dimenze = mat.radky;
        return vel_dimenze;
    }
    else {
        vel_dimenze = mat.sloupce;
        return vel_dimenze;
    }
}

int main() {
  Matice mat0, mat1, mat2, mat3, mat4, mat5, mat6, mat7;


  mat0 = jednotkova(3, 4);
  printf("\nJednotkova matice mat0:\n");
  vypis(mat0);

  mat1 = inicializace(3, 4);
  nastav_prvek(mat1, 0, 0, 4);
  nastav_prvek(mat1, 0, 1, 6);
  nastav_prvek(mat1, 0, 2, 3);
  nastav_prvek(mat1, 0, 3, 4);
  nastav_prvek(mat1, 1, 0, 1);
  nastav_prvek(mat1, 1, 1, 7);
  nastav_prvek(mat1, 1, 2, 3);
  nastav_prvek(mat1, 1, 3, 2);
  nastav_prvek(mat1, 2, 0, 1);
  nastav_prvek(mat1, 2, 1, 3);
  nastav_prvek(mat1, 2, 2, 3);
  nastav_prvek(mat1, 2, 3, 4);
  nastav_prvek(mat1, 3, 0, 5);
  nastav_prvek(mat1, 3, 1, 2);
  nastav_prvek(mat1, 3, 2, 3);
  nastav_prvek(mat1, 3, 3, 4);

  printf("\nMatice mat1 po nacteni prvku:\n");
  vypis(mat1);

  mat2 = transpozice(mat1);
  printf("\nTranspozice matice mat1:\n");
  vypis(mat2);

  mat3 = inicializace(3, 4);
  nastav_prvek(mat3, 0, 0, 8);
  nastav_prvek(mat3, 0, 1, 8);
  nastav_prvek(mat3, 0, 2, 6);
  nastav_prvek(mat3, 0, 3, 4);
  nastav_prvek(mat3, 1, 0, 4);
  nastav_prvek(mat3, 1, 1, 2);
  nastav_prvek(mat3, 1, 2, 1);
  nastav_prvek(mat3, 1, 3, 4);
  nastav_prvek(mat3, 2, 0, 2);
  nastav_prvek(mat3, 2, 1, 2);
  nastav_prvek(mat3, 2, 2, 6);
  nastav_prvek(mat3, 2, 3, 4);
  nastav_prvek(mat3, 3, 0, 1);
  nastav_prvek(mat3, 3, 1, 5);
  nastav_prvek(mat3, 3, 2, 3);
  nastav_prvek(mat3, 3, 3, 2);
  printf("\nMatice mat3 po nacteni prvku:\n");
  vypis(mat3);

  printf("\nMatice mat4 je souctem matic mat1 a mat3: \n");
  mat4 = plus(mat0, mat3);
  vypis(mat4);

  printf("\nMatice mat5 je rozdilem matic mat0 a mat1:\n");
  mat5 = minus(mat0, mat1);
  vypis(mat5);

  printf("\nMatice mat6 je soucinem matic mat1 a mat3:\n");
  mat6 = nasobeni(mat1, mat3);
  vypis(mat6);

  printf("\nMatice mat7 je soucinem matice mat1 a skalaru 3:\n");
  mat7 = krat(mat1, 3);
  vypis(mat7);

 /*
 OPTIONS: 0,1

 --1, prvni dimenze
 --2, druha dimenze

 use case:

 velikost(<zvolena_matice>,<dimenze>)

 velikost(mat1, 2) -> matice s nazvem mat1, druha dimenze
 velikost(mat3, 1) -> matice s nazvem mat3, prvni dimenze

 */
  printf("\nPrvni dimenze zvolene matice je: %d \n", velikost(mat1, 1));

  printf("\nMatice mat1 ulozena do souboru output.txt \n");
  uloz_do_souboru (mat1, "output.txt");

  printf("\nNacitam matici ze souboru load.txt \n");
  nacti_ze_souboru("load.txt");

  odstran(mat1);
  odstran(mat2);
  odstran(mat3);
  odstran(mat4);
  odstran(mat5);
  odstran(mat6);
  odstran(mat7);

  return 0;

}

