#include "eadkpp.h"
#include <stdio.h>
#include "save.h"
#include "affichage.h"
#include "palette.h"
using namespace EADK;

extern const char eadk_app_name[] __attribute__((section(".rodata.eadk_app_name"))) = "BladeClicker";
extern const uint32_t eadk_api_level __attribute__((section(".rodata.eadk_api_level"))) = 0;

int main(int argc, char * argv[]) {
  int click = 1;
  int compteur = 0;
  int selection = 0;

  int nb_items = 3;
  int prix[10]  = {100, 5000, 20000};
  int multi[10] = {1, 2, 3};

  int nb_items_bm = 7;
  int prix_black_marcket[10]  = {500, 2000, 10000, 1000, 5000, 20000, 1000000};

  char texte[20];

  bool ok_precedent    = false;
  bool exe_precedent   = false;
  bool ans_precedent   = false;
  bool paste_precedent = false;
  bool back_precedent  = false;
  bool shift_prec      = false;
  bool alpha_prec      = false;

  bool dans_shop          = false;
  bool dans_black_marcket = false;
  bool dans_setting       = false;

  SaveData save = {0, 1, {100, 5000, 20000}};
  charger(save);
  compteur = save.compteur;
  click    = save.click;
  for (int i = 0; i < nb_items; i++) prix[i] = save.prix[i];

  afficher_main(compteur, rouge, blanc);

  while (1) {
    // Scan le clavier et defini true ou false si touche detecter ou non
    Keyboard::State touches = Keyboard::scan();
    bool ok_maintenant = touches.keyDown(Keyboard::Key::OK);
    bool exe_presse    = touches.keyDown(Keyboard::Key::EXE);
    bool ans_presse    = touches.keyDown(Keyboard::Key::Ans);
    bool shift_presse  = touches.keyDown(Keyboard::Key::Shift);
    bool paste_presse  = touches.keyDown(Keyboard::Key::Toolbox);
    bool back_presse   = touches.keyDown(Keyboard::Key::Back);
    bool alpha_presse  = touches.keyDown(Keyboard::Key::Alpha);

    // Si la touche OK n'est pas sur false alors on verifi que l'on est pas dans le shop et si toute est bon l'utilisateur peut clicker
    if (ok_maintenant && !ok_precedent) {
      if (!dans_shop && !dans_black_marcket && !dans_setting) {
        compteur += click;
        sprintf(texte, "%d", compteur);
        Display::drawString(texte, Point(80, 50), true, blanc, rouge);
      }
    }


    // --- BOUTIQUE ---
    // Si la touche EXE n'est pas sur false alors on verifi que l'on est pas dans le shop et si toute est bon l'utilisateur peut acceder au shop
    else if (exe_presse && !exe_precedent) {
      if (!dans_shop && !dans_black_marcket && !dans_setting) {
        dans_shop = true;
        selection = 0;
        afficher_shop(selection, nb_items, multi, prix, bleu, blanc);
      }
    }

    // Si la touche BACK est presse on quitte l'ecran actuel et on revient au menu principal
    if (back_presse && !back_precedent) {
      if (dans_shop) {
        dans_shop = false;
        afficher_main(compteur, rouge, blanc);
      } else if (dans_black_marcket) {
        dans_black_marcket = false;
        afficher_main(compteur, rouge, blanc);
      } else if (dans_setting) {
        dans_setting = false;
        afficher_main(compteur, rouge, blanc);
      }
    }

    // Si l'utilisateur est dans le shop
    if (dans_shop) {
      // Regarde si les fleches du haut et du bas son pressé et creation de variable deja sur false
      bool haut = touches.keyDown(Keyboard::Key::Up);
      bool bas  = touches.keyDown(Keyboard::Key::Down);
      static bool haut_prec = false, bas_prec = false;

      // Si la fleche du haut est detecter on change la variable selection de place et inversement pour la fleche du bas
      if (haut && !haut_prec) { selection = (selection - 1 + nb_items) % nb_items; afficher_shop(selection, nb_items, multi, prix, bleu, blanc); }
      if (bas  && !bas_prec)  { selection = (selection + 1) % nb_items;             afficher_shop(selection, nb_items, multi, prix, bleu, blanc); }

      // Si l'utilisateur appuie sur OK et que son nombre de click est > au prix alors ont enleve le prix au click et augmente le prix
      if (ok_maintenant && !ok_precedent) {
        if (compteur >= prix[selection]) {
          compteur -= prix[selection];
          click += multi[selection];
          prix[selection] *= 2;
          afficher_shop(selection, nb_items, multi, prix, bleu, blanc);
        }
      }

      // On remet les variable sur false
      haut_prec = haut;
      bas_prec  = bas;
    }


    // --- BLACK MARKET ---
    // Si la touche ANS n'est pas sur false alors on verifi que l'on est pas dans le black market et si toute est bon l'utilisateur peut y acceder
    else if (ans_presse && !ans_precedent) {
      if (!dans_shop && !dans_black_marcket && !dans_setting) {
        dans_black_marcket = true;
        selection = 0;
        afficher_black_marcket(selection, nb_items_bm, prix_black_marcket, noir, blanc);
      }
    }

    // Si l'utilisateur est dans le black market
    if (dans_black_marcket) {
      // Regarde si les fleches du haut et du bas son pressé et creation de variable deja sur false
      bool haut = touches.keyDown(Keyboard::Key::Up);
      bool bas  = touches.keyDown(Keyboard::Key::Down);
      static bool haut_prec_bm = false, bas_prec_bm = false;

      // Si la fleche du haut est detecter on change la variable selection de place et inversement pour la fleche du bas
      if (haut && !haut_prec_bm) { selection = (selection - 1 + nb_items_bm) % nb_items_bm; afficher_black_marcket(selection, nb_items_bm, prix_black_marcket, noir, blanc); }
      if (bas  && !bas_prec_bm)  { selection = (selection + 1) % nb_items_bm;                afficher_black_marcket(selection, nb_items_bm, prix_black_marcket, noir, blanc); }

      // Si l'utilisateur appuie sur OK et que son nombre de click est > au prix alors ont enleve le prix au click et augmente le prix
      if (ok_maintenant && !ok_precedent) {
        if (compteur >= prix_black_marcket[selection]) {
          compteur -= prix_black_marcket[selection];
          prix_black_marcket[selection] *= 2;
          afficher_black_marcket(selection, nb_items_bm, prix_black_marcket, noir, blanc);
        }
      }

      // On remet les variable sur false
      haut_prec_bm = haut;
      bas_prec_bm  = bas;
    }


    // --- SAUVEGARDE ---
    // si la touche SHIFT est pressé on recupere la fonction "faire_sauvegarde" et affiche un message qui informe de la sauvegarde
    if (shift_presse && !shift_prec) {
      faire_sauvegarde(save, compteur, click, nb_items, prix);
      Display::drawString("Sauvegarde!", Point(10, 200), true, blanc, dans_shop ? bleu : rouge);
    }
    shift_prec = shift_presse;  // Remettre SHIFT sur false

    // --- SUPPRIMER SAUVEGARDE ---
    // Si la touche ALPHA est presse et qu'une sauvegarde est existante alors ont la suprime
    if (alpha_presse && !alpha_prec) {
      if (extapp_fileExists("bladeclicker.sav")) {
        extapp_fileErase("bladeclicker.sav");
        Display::drawString("Save supprimee!", Point(10, 200), true, blanc, dans_shop ? bleu : rouge);
      }
    }
    alpha_prec = alpha_presse;  // Remettre ALPHA sur false

    // --- SETTING ---
    // Si le boutton "paste" est presser ont ouvre les settings
    if (paste_presse && !paste_precedent) {
      if (!dans_shop && !dans_black_marcket && !dans_setting) {
        dans_setting = true;
        affiche_setting(gris, blanc);
      }
    }
    paste_precedent = paste_presse;  // Remettre PASTE sur false

    // Remet les variables sur false et ajoute un delai pour la securiter
    back_precedent = back_presse;
    ok_precedent   = ok_maintenant;
    exe_precedent  = exe_presse;
    ans_precedent  = ans_presse;
    Timing::msleep(1);
  }
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