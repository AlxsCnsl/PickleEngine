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
if (win_parameter->event.key.keysym.sym  == SDL_KEY){}
```

"SDL_KEY" peut etre remplaçé:

Lettres (alphabet)

    SDLK_a à SDLK_z : touches de a à z
    SDLK_A à SDLK_Z : touches de A à Z (les majuscules sont gérées via la touche Maj)

Nombres

    SDLK_0 à SDLK_9 : chiffres de 0 à 9

Touches de fonction

    SDLK_F1 à SDLK_F12 : touches de fonction F1 à F12

Touches de direction

    SDLK_UP : flèche haut
    SDLK_DOWN : flèche bas
    SDLK_LEFT : flèche gauche
    SDLK_RIGHT : flèche droite

Touches de contrôle

    SDLK_RETURN : Entrée
    SDLK_ESCAPE : Échap
    SDLK_BACKSPACE : Retour arrière
    SDLK_TAB : Tabulation
    SDLK_SPACE : Espace
    SDLK_DELETE : Suppr

Modificateurs

    SDLK_LSHIFT : Maj gauche
    SDLK_RSHIFT : Maj droite
    SDLK_LCTRL : Ctrl gauche
    SDLK_RCTRL : Ctrl droite
    SDLK_LALT : Alt gauche
    SDLK_RALT : Alt droite
    SDLK_LGUI : Touche Windows/Commande gauche
    SDLK_RGUI : Touche Windows/Commande droite

Pavé numérique

    SDLK_KP_0 à SDLK_KP_9 : chiffres du pavé numérique 0 à 9
    SDLK_KP_ENTER : Entrée du pavé numérique
    SDLK_KP_PLUS : + du pavé numérique
    SDLK_KP_MINUS : - du pavé numérique
    SDLK_KP_MULTIPLY : * du pavé numérique
    SDLK_KP_DIVIDE : / du pavé numérique
    SDLK_KP_PERIOD : Point . du pavé numérique

Symboles divers

    SDLK_SEMICOLON : ;
    SDLK_EQUALS : =
    SDLK_COMMA : ,
    SDLK_MINUS : -
    SDLK_PERIOD : .
    SDLK_SLASH : /
    SDLK_BACKSLASH : \
    SDLK_QUOTE : '
    SDLK_LEFTBRACKET : [
    SDLK_RIGHTBRACKET : ]
    SDLK_GRAVE : ``` (accent grave)

Touches spéciales

    SDLK_PRINTSCREEN : Impr écran
    SDLK_SCROLLLOCK : Arrêt défil
    SDLK_PAUSE : Pause
    SDLK_INSERT : Insert
    SDLK_HOME : Début
    SDLK_PAGEUP : Page précédente
    SDLK_PAGEDOWN : Page suivante
    SDLK_END : Fin
    SDLK_CAPSLOCK : Verrouillage des majuscules
    SDLK_NUMLOCKCLEAR : Verr num
    SDLK_APPLICATION : Touche Menu
    SDLK_POWER : Touche d'alimentation
    SDLK_HELP : Aide
    SDLK_MENU : Menu