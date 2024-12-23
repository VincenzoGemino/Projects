#include <stdio.h>
#include <stdlib.h>
#define MAX_CICLI 10

void buttonCheck(int *isMoving, int *button, int *buttonState){
    switch (*isMoving)
    {
    case 0:
        while(*button < 0 || *button > 2){
            printf("Waiting for input (0, 1, 2): \n");
            scanf("%d", button);
        }
        *buttonState = 1;
        break;
    case 1:
        printf("Elevator still moving...\n");
        break;
    case 2:
        printf("Elevator arrived... Freeing button\n");
        *button = -1;
        *buttonState = 0;
        buttonCheck(isMoving, button, buttonState);
        break;
    default:
        printf("Elevator free-falling...\n");
        break;
    }
}

void movingElevator(int *button, int *isMoving, int *curr_floor, int *next_floor){
    if(*curr_floor == *button){
        printf("Elevator arrived... Opening doors\n");
        *isMoving = 2;
    }
    if(*curr_floor != *next_floor){
        printf("Elevator moving: %d -> %d\n", curr_floor, next_floor);
        *curr_floor = *next_floor;
        *next_floor = *button;
        
    }
}

int main(){
    int button = -1, button_state = 0, floor = 0, next_floor = 0, moving = 0;
    FILE *fp;
    if((fp = fopen("output.txt", "w")) == NULL){
        printf("error opening file. \n");
        return -1;
    }

    for(int i = 0; i < MAX_CICLI; i++){
        buttonCheck(&moving, &button, &button_state);
        movingElevator(&button, &moving, &floor, &next_floor);
    }


    return 0;
}
