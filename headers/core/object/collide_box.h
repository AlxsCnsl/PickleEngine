#ifndef COLLIDE_BOX_H
#define COLLIDE_BOX_H

#include<stdio.h>
#include<stdlib.h>

typedef struct{
    int x_size;
    int y_size;
    int x_pose;
    int y_pose;
    int x_speed;
    int y_speed;
}CollideBox;

CollideBox* collide_box_init(int x_size, int y_size);

int check_collision(CollideBox* box_one, CollideBox* box_two);

int check_left_collision(CollideBox* box_one, CollideBox* box_two);

int check_reft_collision(CollideBox* box_one, CollideBox* box_two);

int check_left_collision(CollideBox* box_one, CollideBox* box_two);

int check_left_collision(CollideBox* box_one, CollideBox* box_two);

#endif // COLLIDE_BOX_H