//object.c===
#include "../../headers/object/object.h"

Object* object_init(char* path_name, int size_x, int size_y){
    Object* object = (Object*)malloc(sizeof(Object));
    object->sprite = sprite_init(path_name, size_x, size_y);
    object->collide_box = collide_box_init(size_x, size_y);
    return object;
}

void display_object(Object* object){
    display_sprite(object->sprite, object->collide_box->x_pose, object->collide_box->y_pose);
}

void replace_object(Object* object, int x_pose, int y_pose){
    object->collide_box->x_pose = x_pose;
    object->collide_box->y_pose = y_pose;
}

void x_move_object(Object* object, int x_move){
    object->collide_box->x_pose += x_move;
}

void y_move_object(Object* object, int y_move){
    object->collide_box->y_pose += y_move;
}
//===