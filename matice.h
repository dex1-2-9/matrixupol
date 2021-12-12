/*
 * Header file for matice.c
 */

 #ifndef MATICE_H
 #define MATICE_H

// Structure definition

typedef struct Matice {
  int radky;
  int sloupce;
  float *data;
} Matice;

extern Matice inicializace(int radky, int sloupce);
extern Matice nulova(int radky, int sloupce);
extern Matice jednotkova(int radky, int sloupce);

extern Matice plus(Matice mat1, Matice mat2);
extern Matice minus(Matice mat1, Matice mat2);
extern Matice nasobeni(Matice mat1, Matice mat2);
extern Matice transpozice(Matice mat);
extern Matice krat(Matice mat, float skalar);

extern int nacti_ze_souboru(const char *soubor);
extern void uloz_do_souboru(Matice mat, const char *soubor);
extern int velikost(Matice mat, int dimenze);
extern void nastav_prvek(Matice mat, int i, int j, float hodnota);
extern float prvek(Matice mat, int i, int j, float hodnota);
extern void odstran(Matice mat);
extern void vypis(Matice mat);

#endif
