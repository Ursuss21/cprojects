#include "stdio.h"
#include "stdlib.h"
#include <SFML/Graphics.h>

int gameTab[3][3] = {0};

void printGame2(){
    int i, j;
    system("clear");
    for(i = 0; i < 3; ++i){
        for(j = 0; j < 3; ++j){
            switch(gameTab[i][j]){
                case 0:
                    printf(" ");
                    break;
                case 1:
                    printf("O");
                    break;
                case 2:
                    printf("X");
                    break;
            }
            if(j < 2){
                printf("|");
            }
            else if(j == 2){
                printf(" %d", i);
            }
        }
        if(i < 2){
            printf("\n_____\n");
        }
        if(i == 2){
            printf("\n\n0 1 2\n");
        }
    }
}

int checkVictory(){
    int i;
    for(i = 1; i < 3; ++i){
        if((gameTab[0][0] == i && gameTab[0][1] == i && gameTab[0][2]) || 
            (gameTab[1][0] == i && gameTab[1][1] == i && gameTab[1][2]) ||
            (gameTab[2][0] == i && gameTab[2][1] == i && gameTab[2][2]) ||
            (gameTab[0][0] == i && gameTab[1][0] == i && gameTab[2][0]) || 
            (gameTab[0][1] == i && gameTab[1][1] == i && gameTab[2][1]) || 
            (gameTab[0][2] == i && gameTab[1][2] == i && gameTab[2][2]) || 
            (gameTab[0][0] == i && gameTab[1][1] == i && gameTab[2][2]) || 
            (gameTab[0][2] == i && gameTab[1][1] == i && gameTab[2][0])){
                printGame2();
                return 1;
            }
    }
    return 0;
}

void gameLoop(){
    sfVideoMode mode = {600, 600, 32};
    sfRenderWindow* window;
    sfSprite* fieldSprite;
    sfSprite* circleSprite[3][3] = {NULL};
    sfSprite* crossSprite[3][3] = {NULL};
    sfTexture* fieldTexture;
    sfTexture* circleTexture[3][3] = {NULL};
    sfTexture* crossTexture[3][3] = {NULL};
    sfEvent event;
    int win = 0, currentPlayer = 1, inputX, drawX, inputY, drawY, i, j;

    fieldTexture = sfTexture_createFromFile("field.png", NULL);
    if (!fieldTexture){
        return;
    }

    fieldSprite = sfSprite_create();
    sfSprite_setTexture(fieldSprite, fieldTexture, sfTrue);

    window = sfRenderWindow_create(mode, "Tic Tac Toe", sfResize | sfClose, NULL);
    if (!window){
        return;
    }

    while (sfRenderWindow_isOpen(window))
    {
        while(win == 0){
            while (sfRenderWindow_pollEvent(window, &event))
            {
                switch(event.type){
                    case sfEvtClosed:
                        sfRenderWindow_close(window);
                        break;
                    case sfEvtMouseButtonPressed:{
                        sfVector2i pos;
                        pos = sfMouse_getPosition((sfWindow*) window);
                        if(pos.x >= 0 && pos.x < 200){
                            inputX = 0;
                            drawX = 0;
                        }
                        else if(pos.x >= 200 && pos.x < 400){
                            inputX = 1;
                            drawX = 200;
                        }
                        else if(pos.x >= 400 && pos.x <= 600){
                            inputX = 2;
                            drawX = 400;
                        }
                        if(pos.y >= 0 && pos.y < 200){
                            inputY = 0;
                            drawY = 0;
                        }
                        else if(pos.y >= 200 && pos.y < 400){
                            inputY = 1;
                            drawY = 200;
                        }
                        else if(pos.y >= 400 && pos.y <= 600){
                            inputY = 2;
                            drawY = 400;
                        }
                        if(inputX < 0 || inputX > 2 || inputY < 0 || inputY > 2 || gameTab[inputX][inputY] != 0){
                            break;
                        }
                        switch(currentPlayer){
                            case 1:
                                gameTab[inputX][inputY] = 1;
                                currentPlayer = 2;
                                break;
                            case 2:
                                gameTab[inputX][inputY] = 2;
                                currentPlayer = 1;
                                break;
                        }
                        printf("%d %d, %d %d\n", pos.x, inputX, pos.y, inputY);
                        break;
                    }
                }
            }
            sfRenderWindow_clear(window, sfWhite);
            sfRenderWindow_drawSprite(window, fieldSprite, NULL);
            for(i = 0; i < 3; ++i){
                for(j = 0; j < 3; ++j){
                    if(gameTab[i][j] == 1){
                        circleTexture[i][j] = sfTexture_createFromFile("circle.png", NULL);
                        if (!circleTexture[i][j]){
                            return;
                        }
                        circleSprite[i][j] = sfSprite_create();
                        sfSprite_setTexture(circleSprite[i][j], circleTexture[i][j], sfTrue);
                        sfVector2f drawPos = {i*200, j*200};
                        sfSprite_move(circleSprite[i][j], drawPos);
                        sfRenderWindow_drawSprite(window, circleSprite[i][j], NULL);
                    }
                    else if(gameTab[i][j] == 2){
                        crossTexture[i][j] = sfTexture_createFromFile("cross.png", NULL);
                        if (!crossTexture[i][j]){
                            return;
                        }
                        crossSprite[i][j] = sfSprite_create();
                        sfSprite_setTexture(crossSprite[i][j], crossTexture[i][j], sfTrue);
                        sfVector2f drawPos = {i*200, j*200};
                        sfSprite_move(crossSprite[i][j], drawPos);
                        sfRenderWindow_drawSprite(window, crossSprite[i][j], NULL);
                    }
                }
            }
            sfRenderWindow_display(window);
            win = checkVictory();
            inputX = 0, inputY = 0;
        }
        if(win == 1){
            printf("Wygralo kolko!\n");
            break;
        }
        else{
            printf("Wygral krzyzyk!\n");
            break;
        }
    }
    for(i = 0; i < 3; ++i){
        for(j = 0; j < 3; ++j){
            sfSprite_destroy(crossSprite[i][j]);
            sfSprite_destroy(circleSprite[i][j]);
            sfTexture_destroy(crossTexture[i][j]);
            sfTexture_destroy(circleTexture[i][j]);
        }
    }
    sfSprite_destroy(fieldSprite);
    sfTexture_destroy(fieldTexture);
    sfRenderWindow_destroy(window);
    /*while(win == 0 && scanf("%d %d", &inputX, &inputY)){
        if(inputX < 0 || inputX > 2 || inputY < 0 || inputY > 2 || gameTab[inputX][inputY] != 0){
            break;
        }
        switch(currentPlayer){
            case 1:
                gameTab[inputX][inputY] = 1;
                currentPlayer = 2;
                break;
            case 2:
                gameTab[inputX][inputY] = 2;
                currentPlayer = 1;
                break;
        }
        win = checkVictory();
        printGame2();
        inputX = 0, inputY = 0;
    }
    if(win == 1){
        printf("Wygralo kolko!\n");
    }
    else{
        printf("Wygral krzyzyk!\n");
    }*/
}

int main(){
    gameLoop();
    return 0;
}
