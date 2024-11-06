#ifndef OBJECT_H
#define OBJECT_H

#include<stdio.h>
#include<stdlib.h>
//#include<string.h>
#include "collide_box.h"
#include "../graphic/sprite.h"

typedef struct{
    CollideBox* collide_box;
    Sprite* sprite;
}Object;

Object* object_init(char* path_name, int size_x, int size_y);

void display_object(Object* object);

void replace_object(Object* object, int x_pose, int y_pose);

void x_move_object(Object* object, int x_move);

void y_move_object(Object* object, int y_move);

#endif // COLLIDE_BOX_H