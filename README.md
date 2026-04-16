===== EADK — Documentation NumWorks =====

--- Infos ---
Pour développer une application sur la calculatrice NumWorks il est possible d'utiliser plusieurs langages :
C, C++, Rust, Zig. Cette documentation se concentre sur le C++ avec les librairies spécifiques à la NumWorks.

Librairies disponibles :
  - EADK     : librairie principale --> affichage, clavier, temps
  - Storage  : librairie de fichiers --> lire, ecrire, supprimer des fichiers

  #include "eadkpp.h"  --> inclure EADK
  #include "storage.h" --> inclure Storage

Librairies standard C++ NON disponibles :
  - iostream  : pas de cout, cin
  - string    : pas de std::string
  - vector    : pas de std::vector
  - list      : pas de std::list

Librairies standard C disponibles :
  - stdio.h   : sprintf, printf
  - string.h  : memcpy, strlen, strcmp
  - stdint.h  : uint32_t, uint8_t, etc.
  - stdbool.h : bool, true, false

/!\ Les librairies C++ de la STL ne sont pas disponibles car l'environnement
    embarqué de la NumWorks ne les supporte pas. Il faut utiliser des tableaux
    de taille fixe et des structs a la place.

--- Metadonnees ---
extern const char eadk_app_name[] __attribute__((section(".rodata.eadk_app_name"))) = "NomDeLApp";
extern const uint32_t eadk_api_level __attribute__((section(".rodata.eadk_api_level"))) = 0;

  - extern        : visible depuis l'extérieur du fichier (la calculatrice peut le lire)
  - const         : non modifiable
  - __attribute__ : place la variable dans une section mémoire précise du binaire
  - eadk_app_name : nom affiché dans le menu
  - eadk_api_level: version de l'API (mettre 0 pour la dernière)

using namespace EADK;  --> evite d'ecrire les "EADK::" au debut de chaque instruction


--- Couleurs ---
EADK::Color rouge(0xFF0000);
  - définit une couleur en RGB hex (0xRRGGBB)
  - la conversion en RGB565 (format de l'écran) est automatique
  - le nom de la variable est libre (rouge, blanc, couleur1, etc.)

Couleurs courantes :
  - 0xFF0000 : rouge
  - 0x00FF00 : vert
  - 0x0000FF : bleu
  - 0xFFFFFF : blanc
  - 0x000000 : noir
  - 0xFFFF00 : jaune
  - 0xFF8800 : orange
  - 0x800080 : violet


--- Affichage ---
Taille ecran : 320x240 pixels
Origine (0,0) : coin superieur gauche
X : augmente vers la droite
Y : augmente vers le bas

Remplir tout l'ecran :
EADK::Display::pushRectUniform(EADK::Screen::Rect, rouge);
  - EADK::Screen::Rect : constante qui represente tout l'ecran (320x240)
  - rouge              : la couleur a utiliser

Remplir un rectangle :
EADK::Rect monRect(x, y, largeur, hauteur);
EADK::Display::pushRectUniform(monRect, rouge);
  - x, y            : position du coin superieur gauche du rectangle
  - largeur, hauteur : dimensions en pixels
  - rouge            : la couleur a utiliser

Afficher un pixel :
EADK::Display::setPixel(EADK::Point(x, y), rouge);
  - EADK::Point(x, y) : position du pixel en pixels
  - rouge             : couleur du pixel


--- Texte ---
EADK::Display::drawString("Texte", EADK::Point(x, y), taille, couleurTexte, couleurFond);
  - "Texte"            : le texte a afficher
  - EADK::Point(x, y) : position en pixels
  - taille true        : grande police (~10px de hauteur)
  - taille false       : petite police (~7px de hauteur)
  - couleurTexte       : couleur des caracteres
  - couleurFond        : couleur du fond derriere le texte

Afficher une variable dans un texte :
  char texte[20];
  --> tableau de caracteres qui stocke le texte formate
  --> le nombre entre crochets est la taille max du texte

  sprintf(texte, "%d", maVariable);   --> entier (int)
  sprintf(texte, "%f", maVariable);   --> decimal (float)
  sprintf(texte, "%s", maVariable);   --> chaine de caracteres (char*)
  sprintf(texte, "score: %d", val);   --> texte fixe + variable
  --> sprintf convertit la variable en chaine et la stocke dans texte
  --> %d, %f, %s sont des marqueurs remplaces par la valeur de la variable

  EADK::Display::drawString(texte, EADK::Point(x, y), true, blanc, rouge);


--- Keyboard ---
Keyboard::State touches = Keyboard::scan();
  - capture l'etat de toutes les touches a un instant T
  - comme une photo du clavier, a appeler a chaque tour de boucle

bool ok = touches.keyDown(Keyboard::Key::OK);
  - retourne true si la touche est enfoncee au moment du scan
  - retourne false sinon

Touches disponibles :
  - Keyboard::Key::Left            (0)  : fleche gauche
  - Keyboard::Key::Up              (1)  : fleche haut
  - Keyboard::Key::Down            (2)  : fleche bas
  - Keyboard::Key::Right           (3)  : fleche droite
  - Keyboard::Key::OK              (4)  : validation (bouton rond du milieu)
  - Keyboard::Key::Back            (5)  : touche retour
  - Keyboard::Key::Home            (6)  : touche Home (quitte l'app)
  - Keyboard::Key::Shift           (12) : touche Shift
  - Keyboard::Key::Alpha           (13) : touche Alpha
  - Keyboard::Key::XNT             (14) : touche XNT
  - Keyboard::Key::Var             (15) : touche Var
  - Keyboard::Key::Toolbox         (16) : touche Toolbox
  - Keyboard::Key::Backspace       (17) : suppression
  - Keyboard::Key::Exp             (18) : exposant (e^x)
  - Keyboard::Key::Ln              (19) : logarithme naturel
  - Keyboard::Key::Log             (20) : logarithme base 10
  - Keyboard::Key::Imaginary       (21) : nombre imaginaire (i)
  - Keyboard::Key::Comma           (22) : virgule
  - Keyboard::Key::Power           (23) : puissance (x^y)
  - Keyboard::Key::Sine            (24) : sinus
  - Keyboard::Key::Cosine          (25) : cosinus
  - Keyboard::Key::Tangent         (26) : tangente
  - Keyboard::Key::Pi              (27) : pi (π)
  - Keyboard::Key::Sqrt            (28) : racine carree
  - Keyboard::Key::Square          (29) : carre (x²)
  - Keyboard::Key::Seven           (30) : chiffre 7
  - Keyboard::Key::Eight           (31) : chiffre 8
  - Keyboard::Key::Nine            (32) : chiffre 9
  - Keyboard::Key::LeftParenthesis (33) : parenthese gauche
  - Keyboard::Key::RightParenthesis(34) : parenthese droite
  - Keyboard::Key::Four            (36) : chiffre 4
  - Keyboard::Key::Five            (37) : chiffre 5
  - Keyboard::Key::Six             (38) : chiffre 6
  - Keyboard::Key::Multiplication  (39) : multiplication
  - Keyboard::Key::Division        (40) : division
  - Keyboard::Key::One             (42) : chiffre 1
  - Keyboard::Key::Two             (43) : chiffre 2
  - Keyboard::Key::Three           (44) : chiffre 3
  - Keyboard::Key::Plus            (45) : addition
  - Keyboard::Key::Minus           (46) : soustraction
  - Keyboard::Key::Zero            (48) : chiffre 0
  - Keyboard::Key::Dot             (49) : point decimal
  - Keyboard::Key::EE              (50) : notation scientifique
  - Keyboard::Key::Ans             (51) : derniere reponse
  - Keyboard::Key::EXE             (52) : touche EXE

Detecter un appui unique (evite la repetition) :
  bool ok_precedent = false;
  --> garde en memoire l'etat de la touche au tour precedent

  bool ok_maintenant = touches.keyDown(Keyboard::Key::OK);
  --> etat de la touche au tour actuel

  if (ok_maintenant && !ok_precedent) {
    --> ok_maintenant == true : la touche EST enfoncee maintenant
    --> !ok_precedent == true : la touche N'ETAIT PAS enfoncee avant
    --> donc c'est le moment exact ou on vient d'appuyer
    // execute une seule fois par appui
  }
  ok_precedent = ok_maintenant;
  --> met a jour pour le prochain tour


--- Temps ---
EADK::Timing::msleep(n);
  - met le programme en pause pendant n millisecondes
  - msleep(1)    = 1 milliseconde
  - msleep(1000) = 1 seconde
  - a mettre a la fin du while(1) pour ne pas surcharger le processeur


--- Sauvegarde ---
#include "storage.h"
  --> a inclure pour utiliser les fonctions de fichiers

extapp_fileExists("fichier.sav")
  --> verifie si le fichier existe
  --> retourne true si oui, false si non

extapp_fileErase("fichier.sav")
  --> supprime le fichier
  --> retourne true si succes, false si le fichier n'existe pas

extapp_fileWrite("fichier.sav", (const char *)&data, sizeof(data))
  --> ecrit les donnees dans le fichier
  --> (const char *)&data : convertit l'adresse de data en pointeur d'octets
  --> sizeof(data)        : taille en octets des donnees a ecrire
  --> retourne true si succes

extapp_fileRead("fichier.sav", &len)
  --> lit le contenu du fichier
  --> &len    : variable qui recevra la taille en octets du fichier lu
  --> retourne un pointeur vers le contenu, NULL si le fichier n'existe pas

Sauvegarder une struct :
  struct SaveData { int score; int niveau; };
  --> struct = regroupe plusieurs variables en un seul bloc

  SaveData data = {0, 1};
  if (extapp_fileExists("save.sav")) extapp_fileErase("save.sav");
  --> on efface d'abord pour eviter d'avoir deux fois le meme fichier

  extapp_fileWrite("save.sav", (const char *)&data, sizeof(SaveData));

Charger une struct :
  size_t len = 0;
  const char * contenu = extapp_fileRead("save.sav", &len);
  if (contenu != NULL && len == sizeof(SaveData)) {
    memcpy(&data, contenu, sizeof(SaveData));
    --> memcpy copie les octets un par un dans data
  }
  /!\ toujours utiliser memcpy et non un cast direct
  --> un cast direct peut causer un crash d'alignement memoire sur ARM


--- Boucle principale ---
while (1) {
  --> boucle infinie, empeche l'app de se terminer

  Keyboard::State touches = Keyboard::scan();
  --> capture les touches a chaque tour

  // logique du jeu
  // mise a jour de l'affichage

  EADK::Timing::msleep(1);
  --> pause de 1ms pour ne pas surcharger le processeur
}


--- Variables ---
Types de base :
  int    : nombre entier          --> int score = 0;
  float  : nombre decimal         --> float vitesse = 1.5;
  bool   : vrai ou faux           --> bool actif = true;
  char   : caractere              --> char lettre = 'A';
  char[] : tableau de caracteres  --> char texte[20] = "hello";

Tableaux :
  int prix[5] = {10, 20, 30, 40, 50};
  --> tableau de 5 entiers
  --> acces par index : prix[0] = 10, prix[1] = 20, etc.
  --> l'index commence toujours a 0
  --> la taille doit etre connue a l'avance

Struct :
  struct MonStruct {
    int score;
    int niveau;
    bool actif;
  };
  MonStruct s = {0, 1, true};
  --> regroupe plusieurs variables en un seul bloc
  --> acces : s.score, s.niveau, s.actif


--- Conditions ---
if (condition) {
  // si condition est vraie
} else if (autre condition) {
  // sinon si autre condition est vraie
} else {
  // sinon
}

Operateurs de comparaison :
  ==  : egal a
  !=  : different de
  >   : superieur a
  <   : inferieur a
  >=  : superieur ou egal
  <=  : inferieur ou egal

Operateurs logiques :
  &&  : ET  (les deux conditions doivent etre vraies)
  ||  : OU  (au moins une condition doit etre vraie)
  !   : NON (inverse la condition)


--- Boucles ---
Boucle while :
  while (condition) {
    // repete tant que condition est vraie
  }

Boucle for :
  for (int i = 0; i < 10; i++) {
    // repete 10 fois, i va de 0 a 9
  }
  --> int i = 0  : valeur de depart
  --> i < 10     : condition d'arret
  --> i++        : increment a chaque tour
