#LES FONCTIONS

##les sprites:
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

##Les collision:

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