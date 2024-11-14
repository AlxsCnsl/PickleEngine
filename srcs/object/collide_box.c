//collide_box.c===
#include "../../headers/object/collide_box.h"

CollideBox* collide_box_init(int x_size, int y_size){
    CollideBox* returned_box = (CollideBox*)malloc(sizeof(CollideBox));
    returned_box->x_size = x_size;
    returned_box->y_size = y_size;
    returned_box->x_pose = 0;
    returned_box->y_pose = 0;
    returned_box->x_speed = 0;
    returned_box->y_speed = 0;
    return returned_box;
}

int check_collision(CollideBox* box_one, CollideBox* box_two) {
    // Vérifier si les boîtes se chevauchent horizontalement
    if (box_one->x_pose < box_two->x_pose + box_two->x_size && 
        box_one->x_pose + box_one->x_size > box_two->x_pose &&
        box_one->y_pose < box_two->y_pose + box_two->y_size && 
        box_one->y_pose + box_one->y_size > box_two->y_pose) {

        // Si une collision est détectée, annuler la vitesse de box_one
        if (box_one->y_speed > 0) { // Collision venant du bas
            box_one->y_pose = box_two->y_pose - box_one->y_size;
            box_one->y_speed = 0;
        } else if (box_one->y_speed < 0) { // Collision venant du haut
            box_one->y_pose = box_two->y_pose + box_two->y_size;
            box_one->y_speed = 0;
        }

        if (box_one->x_speed > 0) { // Collision venant de la droite
            box_one->x_pose = box_two->x_pose - box_one->x_size;
            box_one->x_speed = 0;
        } else if (box_one->x_speed < 0) { // Collision venant de la gauche
            box_one->x_pose = box_two->x_pose + box_two->x_size;
            box_one->x_speed = 0;
        }

        return 1; // Collision détectée
    }
    return 0; // Pas de collision
}
int check_left_collision(CollideBox* box_one, CollideBox* box_two);

int check_reft_collision(CollideBox* box_one, CollideBox* box_two);

int check_left_collision(CollideBox* box_one, CollideBox* box_two);

int check_left_collision(CollideBox* box_one, CollideBox* box_two);



/*
void handle_collision(Rectangle *rect1, Rectangle rect2, int box_one->x_speed, int box_one->y_speed) {
    // Vérifier d’abord la collision horizontale
    if (box_one->x_pose < box_one->x_pose + box_one->x_size && box_one->x_pose + box_one->x_size > box_one->x_pose) { ==========

        if (box_one->x_speed > 0 && box_one->x_pose + box_one->x_size <= box_one->x_pose) {  // Collision par la droite
            box_one->x_pose = box_one->x_pose - box_one->x_size;
            box_one->x_speed = 0;

        } else if (box_one->x_speed < 0 && box_one->x_pose >= box_one->x_pose + box_one->x_size) {  // Collision par la gauche
            box_one->x_pose = box_one->x_pose + box_one->x_size;
            box_one->x_speed = 0;
        }
    }

    // Vérifier ensuite la collision verticale
    if (box_one->y_pose < box_one->y_pose + box_one->y_size && box_one->y_pose + box_one->y_size > box_one->y_pose) {

        if (box_one->y_speed > 0 && box_one->y_pose + box_one->y_size <= box_one->y_pose) {  // Collision par le bas
            box_one->y_pose = box_one->y_pose - box_one->y_size;
            box_one->y_speed = 0;

        } else if (box_one->y_speed < 0 && box_one->y_pose >= box_one->y_pose + box_one->y_size) {  // Collision par le haut
            box_one->y_pose = box_one->y_pose + box_one->y_size;
            box_one->y_speed = 0;
        }
    }
}
*/
//collide_box.c