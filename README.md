# LES FONCTIONS

## les sprites:
```c++
typedef struct {
    int x_size;
    int y_size;
    SDL_Texture* texture;
}Sprite;

//pour cree un Sprite
Sprite* sprite_init(char* path_name, int width, int height);

//pour afficher un Sprite
void display_sprite(Sprite* sprite, int x_pose, int y_pose);
```

## Les collision:

```c++
typedef struct{
    int x_size;
    int y_size;
    int x_pose;
    int y_pose;
    int x_speed;
    int y_speed;
}CollideBox;

//pour initié une CollideBox
CollideBox* collide_box_init(int x_size, int y_size);

//pour géré si il y à une collision dans X direction
int check_collision(CollideBox* box_one, CollideBox* box_two);

int check_left_collision(CollideBox* box_one, CollideBox* box_two);

int check_reft_collision(CollideBox* box_one, CollideBox* box_two);

int check_left_collision(CollideBox* box_one, CollideBox* box_two);

int check_left_collision(CollideBox* box_one, CollideBox* box_two);
```


## les interaction materielle:

### le clavier:

```cpp
intkeyboard_press_check(SDL_Scancode key_check)
```

Liste des SDL_Scancode :

    !!!par raport aux qwerty!!!
    
    SDL_SCANCODE_A à SDL_SCANCODE_Z : Touches A à Z (en majuscules).
    SDL_SCANCODE_1 à SDL_SCANCODE_9 : Touches numériques 1 à 9 sur la ligne supérieure.
    SDL_SCANCODE_0 : Touche numérique 0 sur la ligne supérieure.
    SDL_SCANCODE_RETURN : Touche Entrée.
    SDL_SCANCODE_ESCAPE : Touche Échap.
    SDL_SCANCODE_BACKSPACE : Touche Retour arrière.
    SDL_SCANCODE_TAB : Touche Tabulation.
    SDL_SCANCODE_SPACE : Touche Espace.
    SDL_SCANCODE_MINUS : Touche moins (-).
    SDL_SCANCODE_EQUALS : Touche égal (=).
    SDL_SCANCODE_LEFTBRACKET : Touche crochet gauche ([).
    SDL_SCANCODE_RIGHTBRACKET : Touche crochet droit (]).
    SDL_SCANCODE_BACKSLASH : Touche barre oblique inversée ().
    SDL_SCANCODE_SEMICOLON : Touche point-virgule (;).
    SDL_SCANCODE_QUOTE : Touche apostrophe (').
    SDL_SCANCODE_COMMA : Touche virgule (,).
    SDL_SCANCODE_PERIOD : Touche point (.).
    SDL_SCANCODE_SLASH : Touche barre oblique (/).
    SDL_SCANCODE_CAPSLOCK : Touche Verr Maj.
    SDL_SCANCODE_F1 à SDL_SCANCODE_F12 : Touches F1 à F12.
    SDL_SCANCODE_PRINTSCREEN : Touche Impr écran.
    SDL_SCANCODE_SCROLLLOCK : Touche Arrêt défil.
    SDL_SCANCODE_PAUSE : Touche Pause.
    SDL_SCANCODE_INSERT : Touche Ins.
    SDL_SCANCODE_HOME : Touche Accueil.
    SDL_SCANCODE_PAGEUP : Touche Page Up.
    SDL_SCANCODE_PAGEDOWN : Touche Page Down.
    SDL_SCANCODE_DELETE : Touche Suppr.
    SDL_SCANCODE_END : Touche Fin.
    SDL_SCANCODE_RIGHT : Flèche droite.
    SDL_SCANCODE_LEFT : Flèche gauche.
    SDL_SCANCODE_DOWN : Flèche bas.
    SDL_SCANCODE_UP : Flèche haut.
    SDL_SCANCODE_NUMLOCKCLEAR : Touche Num Lock.
    SDL_SCANCODE_KP_DIVIDE : Touche Diviser (pavé numérique).
    SDL_SCANCODE_KP_MULTIPLY : Touche Multiplier (pavé numérique).
    SDL_SCANCODE_KP_MINUS : Touche Moins (pavé numérique).
    SDL_SCANCODE_KP_PLUS : Touche Plus (pavé numérique).
    SDL_SCANCODE_KP_ENTER : Touche Entrée (pavé numérique).
    SDL_SCANCODE_KP_1 à SDL_SCANCODE_KP_9 : Touches numériques 1 à 9 (pavé numérique).
    SDL_SCANCODE_KP_0 : Touche numérique 0 (pavé numérique).
    SDL_SCANCODE_KP_PERIOD : Touche point (pavé numérique).
    SDL_SCANCODE_NONUSHASH : Touche # (pavé numérique, selon la disposition du clavier).
    SDL_SCANCODE_KP_EQUALS : Touche égal (pavé numérique).
    SDL_SCANCODE_LCTRL, SDL_SCANCODE_LSHIFT, SDL_SCANCODE_LALT, SDL_SCANCODE_LGUI : Touche de contrôle gauche, Maj gauche, Alt gauche, GUI gauche.
    SDL_SCANCODE_RCTRL, SDL_SCANCODE_RSHIFT, SDL_SCANCODE_RALT, SDL_SCANCODE_RGUI : Touche de contrôle droit, Maj droite, Alt droite, GUI droit.
    SDL_SCANCODE_MENU : Touche Menu (généralement utilisée pour ouvrir le menu de l'application).
    SDL_SCANCODE_LSUPER, SDL_SCANCODE_RSUPER : Touche Super gauche/droit (Windows/Command).
    SDL_SCANCODE_KP_COMMA : Touche virgule (pavé numérique).

Codes pour les touches de modification (majuscule, etc.) :

    SDL_SCANCODE_LSHIFT, SDL_SCANCODE_RSHIFT : Maj gauche et droite.
    SDL_SCANCODE_LCTRL, SDL_SCANCODE_RCTRL : Contrôle gauche et droit.
    SDL_SCANCODE_LALT, SDL_SCANCODE_RALT : Alt gauche et droit.

Codes pour les touches de fonction supplémentaires :

    SDL_SCANCODE_F13 à SDL_SCANCODE_F24 : Touches F13 à F24 (dépend du clavier et du système).