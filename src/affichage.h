#pragma once
#include "eadkpp.h"
#include <stdio.h>
using namespace EADK;

inline void afficher_main(int compteur, Color rouge, Color blanc) {
  char texte[20];   // Tableau local pour stocker le compteur converti en texte
  Display::pushRectUniform(Screen::Rect, rouge);
  Display::drawString("--- BladeClicker ---", Point(70, 10), true, blanc, rouge);
  Display::drawString("Argent:", Point(10, 50), true, blanc, rouge);
  // Convertie "compteur" en texte et l'affiche a coter de "argent"
  sprintf(texte, "%d", compteur);
  Display::drawString(texte, Point(80, 50), true, blanc, rouge);

  Display::drawString("(paste) Commande", Point(200, 220), false, blanc, rouge);
}

inline void afficher_shop(int selection, int nb_items, int * multi, int * prix, Color bleu, Color blanc) {
  char ligne[30];   // Tableau local pour stocker chaque ligne du shop formatee
  Display::pushRectUniform(Screen::Rect, bleu);
  Display::drawString("--- SHOP ---", Point(10, 10), true, blanc, bleu);
  Display::drawString("(BACK) retour", Point(200, 220), false, blanc, bleu);

  // On affiche ">" devant l'item actuel ou "" si item n'est pas selectionné
  for (int i = 0; i < nb_items; i++) {
    sprintf(ligne, "%s %d. x%d click (%d)", selection == i ? ">" : " ", i + 1, multi[i], prix[i]);    // Construit le texte a partir de variable et le stcoke dans ligne
    Display::drawString(ligne, Point(10, 40 + i * 20), true, blanc, bleu);    // Decal chaque items de 20px
  }
}

inline void affiche_setting(Color gris, Color blanc){
    Display::pushRectUniform(Screen::Rect, gris);
    Display::drawString("--- Commande ---", Point(100, 10), true, blanc, gris);
    Display::drawString("- (Shift) Sauvegarder", Point(10, 30), false, blanc, gris);
    Display::drawString("- (ALPHA) Delete sauvegarde", Point(10, 50), false, blanc, gris);
    Display::drawString("- (EXE) Boutique", Point(10, 70), false, blanc, gris);
    Display::drawString("- (Ans) Black Marcket", Point(10, 90), false, blanc, gris);
    Display::drawString("- (^) Selection vers haut", Point(10, 110), false, blanc, gris);
    Display::drawString("- (v) Selection vers bas", Point(10, 130), false, blanc, gris);
    Display::drawString("- (paste) Setting", Point(10, 150), false, blanc, gris);
    Display::drawString("- (OK) Click, select", Point(10, 170), false, blanc, gris);

    Display::drawString("(BACK) retour", Point(200, 220), false, blanc, gris);
}

inline void afficher_black_marcket(int selection, int nb_items_bm, int * prix_bm, Color noir, Color blanc) {
  Display::pushRectUniform(Screen::Rect, noir);
  Display::drawString("--- BLACK MARKET ---", Point(10, 10), true, blanc, noir);
  Display::drawString("(Back) retour", Point(200, 220), false, blanc, noir);

  Display::drawString("[ Coffres ]", Point(10, 35), false, blanc, noir);
  Display::drawString(selection == 0 ? "> - Coffre commun  (500)"        : "  - Coffre commun  (500)",        Point(10, 50),  false, blanc, noir);
  Display::drawString(selection == 1 ? "> - Coffre rare    (2000)"       : "  - Coffre rare    (2000)",       Point(10, 65),  false, blanc, noir);
  Display::drawString(selection == 2 ? "> - Coffre legendaire (10000)"   : "  - Coffre legendaire (10000)",   Point(10, 80),  false, blanc, noir);

  Display::drawString("[ Items ]", Point(10, 100), false, blanc, noir);
  Display::drawString(selection == 3 ? "> - Epee    (1000)"              : "  - Epee    (1000)",              Point(10, 115), false, blanc, noir);
  Display::drawString(selection == 4 ? "> - Bouclier (5000)"             : "  - Bouclier (5000)",             Point(10, 130), false, blanc, noir);
  Display::drawString(selection == 5 ? "> - Couronne (20000)"            : "  - Couronne (20000)",            Point(10, 145), false, blanc, noir);

  Display::drawString("[ Prestige ]", Point(10, 165), false, blanc, noir);
  Display::drawString(selection == 6 ? "> - Prestige (1000000)"          : "  - Prestige (1000000)",          Point(10, 180), false, blanc, noir);
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