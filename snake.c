#include <stdio.h>
#include <stdlib.h> 
#include <time.h>
#include <SFML/Graphics.h>
#include <SFML/System.h>

int gameTab[30][40] = {0};

struct snake{
    int x;
    int y;
};

struct apple{
    int x;
    int y;
};

int randomPos(int i){
    int zarodek;
    time_t tt;
    zarodek = time(&tt);
    srand(zarodek);
    return rand()%i;
}

void gameLoop(){
    sfVideoMode mode = {800, 600, 32};
    sfRenderWindow* window;
    sfSprite* fieldSprite;
    sfSprite* snekSprite[30][40] = {NULL};
    sfSprite* appleSprite[30][40] = {NULL};
    sfTexture* fieldTexture;
    sfTexture* snekTexture[30][40] = {NULL};
    sfTexture* appleTexture[30][40] = {NULL};
    sfEvent event;

    struct snake snakeArray[30*40];
    struct apple apple;
    int i, j, snakeLength = 3;
    int direction = 0;
    int win = 0;
    snakeArray[0].x = 15;
    snakeArray[0].y = 20;
    snakeArray[1].x = 15;
    snakeArray[1].y = 19;
    snakeArray[2].x = 15;
    snakeArray[2].y = 18;
    apple.x = randomPos(30);
    apple.y = randomPos(40);
    while(apple.y == 15 && (apple.x == 20 || apple.x == 19 || apple.x == 18)){
        apple.x = randomPos(30);
        apple.y = randomPos(40);
    }

    fieldTexture = sfTexture_createFromFile("snek.png", NULL);
    if (!fieldTexture){
        return;
    }
    fieldSprite = sfSprite_create();
    sfSprite_setTexture(fieldSprite, fieldTexture, sfTrue);

    window = sfRenderWindow_create(mode, "Sneeek", sfResize | sfClose, NULL);
    sfRenderWindow_setFramerateLimit(window, 5);
    if (!window){
        return;
    }

    while (sfRenderWindow_isOpen(window))
    {
        while(!win){
            while (sfRenderWindow_pollEvent(window, &event))
            {
                switch(event.type){
                    case sfEvtClosed:{
                        sfRenderWindow_close(window);
                        break;
                    }
                    case sfEvtKeyPressed:{
                        switch(event.key.code){
                            case sfKeyD:
                            case sfKeyRight:{
                                if(direction != 2){
                                    direction = 0;
                                }
                                break;
                            }
                            case sfKeyS:
                            case sfKeyDown:{
                                if(direction != 3){
                                    direction = 1;
                                }
                                break;
                            }
                            case sfKeyA:
                            case sfKeyLeft:{
                                if(direction != 0){
                                    direction = 2;
                                }
                                break;
                            }
                            case sfKeyW:
                            case sfKeyUp:{
                                if(direction != 1){
                                    direction = 3;
                                }
                                break;
                            }
                        }
                    }
                }
            }
            sfRenderWindow_clear(window, sfWhite);
            sfRenderWindow_drawSprite(window, fieldSprite, NULL);

            for(i = 0; i < 30; ++i){
                for(j = 0; j < 40; ++j){
                    gameTab[i][j] = 0;
                }
            }
            for(i = 0; i < snakeLength; ++i){
                gameTab[snakeArray[i].x][snakeArray[i].y] = 1;
            }
            gameTab[apple.x][apple.y] = 2;

            for(i = 0; i < 30; ++i){
                for(j = 0; j < 40; ++j){
                    if(gameTab[i][j] == 1){
                        snekTexture[i][j] = sfTexture_createFromFile("snekpart.png", NULL);
                        if (!snekTexture[i][j]){
                            return;
                        }
                        snekSprite[i][j] = sfSprite_create();
                        sfSprite_setTexture(snekSprite[i][j], snekTexture[i][j], sfTrue);
                        sfVector2f drawPos = {j*20, i*20};
                        sfSprite_setPosition(snekSprite[i][j], drawPos);
                        sfRenderWindow_drawSprite(window, snekSprite[i][j], NULL);
                    }
                    else if(gameTab[i][j] == 2){
                        appleTexture[i][j] = sfTexture_createFromFile("snekapple.png", NULL);
                        if (!appleTexture[i][j]){
                            return;
                        }
                        appleSprite[i][j] = sfSprite_create();
                        sfSprite_setTexture(appleSprite[i][j], appleTexture[i][j], sfTrue);
                        sfVector2f drawPos = {j*20, i*20};
                        sfSprite_setPosition(appleSprite[i][j], drawPos);
                        sfRenderWindow_drawSprite(window, appleSprite[i][j], NULL);
                    }
                }
            }

            switch(direction){
                case 0:{
                    for(i = snakeLength - 1; i >= 0; --i){
                        if(!i){
                            ++snakeArray[i].y;
                            if(snakeArray[i].y == 40){
                                snakeArray[i].y = 0;
                            }
                        }
                        else{
                            snakeArray[i].x = snakeArray[i - 1].x;
                            snakeArray[i].y = snakeArray[i - 1].y;
                        }
                    }
                    break;
                }
                case 1:{
                    for(i = snakeLength - 1; i >= 0; --i){
                        if(!i){
                            ++snakeArray[i].x;
                            if(snakeArray[i].x == 30){
                                snakeArray[i].x = 0;
                            }
                        }
                        else{
                            snakeArray[i].x = snakeArray[i - 1].x;
                            snakeArray[i].y = snakeArray[i - 1].y;
                        }
                    }
                    break;
                }
                case 2:{
                    for(i = snakeLength - 1; i >= 0; --i){
                        if(!i){
                            --snakeArray[i].y;
                            if(snakeArray[i].y == -1){
                                snakeArray[i].y = 39;
                            }
                        }
                        else{
                            snakeArray[i].x = snakeArray[i - 1].x;
                            snakeArray[i].y = snakeArray[i - 1].y;
                        }
                    }
                    break;
                }
                case 3:{
                    for(i = snakeLength - 1; i >= 0; --i){
                        if(!i){
                            --snakeArray[i].x;
                            if(snakeArray[i].x == -1){
                                snakeArray[i].x = 29;
                            }
                        }
                        else{
                            snakeArray[i].x = snakeArray[i - 1].x;
                            snakeArray[i].y = snakeArray[i - 1].y;
                        }
                    }
                    break;
                }
            }

            for(i = 1; i < snakeLength; ++i){
                if(snakeArray[0].x == snakeArray[i].x && snakeArray[0].y == snakeArray[i].y){
                    win = 1;
                }
            }

            if(snakeArray[0].x == apple.x && snakeArray[0].y == apple.y){
                ++snakeLength;
                snakeArray[snakeLength-1].x = snakeArray[0].x;
                snakeArray[snakeLength-1].y = snakeArray[0].y;
                while(gameTab[apple.x][apple.y]!=0){
                    apple.x = randomPos(30);
                    apple.y = randomPos(40);
                }
            }
            sfRenderWindow_display(window);
        }
        while (sfRenderWindow_pollEvent(window, &event)){
            switch(event.type){
                case sfEvtClosed:{
                    sfRenderWindow_close(window);
                    break;
                }
            }
        }
    }
}

int main(){
    gameLoop();
    return 0;
}
