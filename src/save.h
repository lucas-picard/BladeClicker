#pragma once
#include <string.h>
#include "storage.h"

struct SaveData {
  int compteur;
  int click;
  int prix[10];
};

inline void sauvegarder(SaveData & data) {
  // Si il y a deja une sauvegarde on la suprime et on la remplace par la nouvelle
  if (extapp_fileExists("bladeclicker.sav")) {
    extapp_fileErase("bladeclicker.sav");
  }
  extapp_fileWrite("bladeclicker.sav", (const char *)&data, sizeof(SaveData));
}

inline void charger(SaveData & data) {
  // Si aucune sauvegarde existante on continu
  if (!extapp_fileExists("bladeclicker.sav")) {
    return;
  }
  // On regarde la taille du fichier et retourne un pointeur vers le contenu du fichier
  size_t len = 0;
  const char * contenu = extapp_fileRead("bladeclicker.sav", &len);
  // On verifi vérifie que la lecture a réussi et la taille du fichier correspond exactement à la taille de la struct
  if (contenu != NULL && len == sizeof(SaveData)) {
    memcpy(&data, contenu, sizeof(SaveData));
  }
}

inline void faire_sauvegarde(SaveData & save, int compteur, int click, int nb_items, int * prix) {
  // On copie les valeurs du jeu actuel et appelle la fonction pour sauvegarder apres
  save.compteur = compteur;
  save.click    = click;
  for (int i = 0; i < nb_items; i++) save.prix[i] = prix[i];
  sauvegarder(save);
}





/*
,-.
      / \  .  __..-,O
     :   \ --''_..-'.'
     |    . .-' . '.
     :     .     ..'
      \     .  /  ..
       \      .   ' .
        `,       .   \
       ,|,.        -.\
      '.||  `-...__..-
       |  |
       |__|
       /||\
      //||\\
     // || \\
  __//__||__\\__
 '--------------'

010011001101111011011110111001101100011
0110000101110011
*/