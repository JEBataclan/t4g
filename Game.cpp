#include <iostream>
#include <time.h>
#include <string>
#include <SDL2/SDL_mixer.h>
#include "Game.h"
#include "GameObject.h"
#include "GameText.h"
#include "Player1.h"
#include "Player2.h"
#include "PowerUp.h"
#include "CheckCollision.h"

#define SCREEN_HEIGHT 600
#define SCREEN_WIDTH 800



Player1 *player1;
Player2 *player2;

GameObject *ground1, *ground2, *ground3, *ground4,
           *ground5, *ground6, *ground7, *ground8;

PowerUp *powerup;
int pLoc;

GameText *timer, *text1, *text2, *subEv, *subCh, *p1Win, *p2Win, *Win;

float curTime, prevTime;

int prev, pres;

Mix_Music *menu, *play, *win;
Mix_Chunk *round, *power;

//////////////////////////
//MENU VARIABLES
GameObject *titleScreen, *helpScreen, *playButton, *helpButton, *backButton;


Game::Game()
{}

Game::~Game()
{}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
    int flags = 0;
    if (fullscreen) {
        flags = 1;
    }

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        std::cout << "Subsystems initialized..." << std::endl;

        window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
        if (window) {
            std::cout << "Window created!" << std::endl;
        }

        renderer = SDL_CreateRenderer(window, -1, 0);
        if (renderer) {
            std::cout << "Renderer created!" << std::endl;
        }

        if (TTF_Init() < 0) {
            std::cout << "TTF initialization successful!" << std::endl;
        }
        if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0){
            std::cout<<"Error"<<std::endl;

        }

        isRunning = true;
    } else {
        isRunning = false;
    }
    menu = Mix_LoadMUS("assets/music/MENU.mp3");
    play = Mix_LoadMUS("assets/music/PLAY.mp3");
    win = Mix_LoadMUS("assets/music/WIN.mp3");
    round = Mix_LoadWAV("assets/music/ROUND.mp3");
    power = Mix_LoadWAV("assets/music/POWERUP.mp3");

    player1 = new Player1("assets/player1.png", renderer, 10, 0, 41, 60);
    player2 = new Player2("assets/player2.png", renderer, 750, 400, 41, 60);

    text1 = new GameText("012345", renderer, 0, 0, 100, 100, {76, 167, 246}, 20, 10);
    text2 = new GameText("012345", renderer, 700, 0, 100, 100, {246, 76, 76}, 20, 10);
    timer = new GameText("000102030405060708091011121314151617181920", renderer,350, 0, 100, 75, {255,255,255}, 20, 5);
    timer->rectX = 20*20;
    subCh = new GameText("CHASE", renderer, 0, 100, 100, 50, {255, 255, 255}, 30, 1);
    subEv = new GameText("EVADE", renderer, 700, 100, 100, 50, {255, 255, 255}, 30, 1);
    p1Win = new GameText("BLUE", renderer, 300, 150, 200, 100, {76, 167, 246}, 30, 1);
    p2Win = new GameText("RED", renderer, 300, 150, 200, 100, {246, 76, 76}, 20, 1);
    Win = new GameText("WINS", renderer, 300, 350, 200, 100, {255, 255, 255}, 20, 1);
    // SETS POWERUPS' POSITIONS AND SIZES THEN ALLOCATES IT TO A VECTOR
    srand(time(NULL));
    pxLoc.resize(10);pyLoc.resize(10);

    pxLoc[0] = 90;  pyLoc[0] = 130;
    pxLoc[1] = 390; pyLoc[1] = 30;
    pxLoc[2] = 690; pyLoc[2] = 130;
    pxLoc[3] = 90;  pyLoc[3] = 330;
    pxLoc[4] = 390; pyLoc[4] = 230;
    pxLoc[5] = 690; pyLoc[5] = 330;
    pxLoc[6] = 90;  pyLoc[6] = 530;
    pxLoc[7] = 390; pyLoc[7] = 430;
    pxLoc[8] = 690; pyLoc[8] = 530;
    pxLoc[9] = 390; pyLoc[9] = 530;
    pLoc = rand() % 10;
    powerup = new PowerUp("assets/powerups.png", renderer, pxLoc[pLoc], pyLoc[pLoc], 20, 30, rand() % 2);
    powerup->isActive = true;
    powerup->pspawnTime = SDL_GetTicks();


    // SETS PLATFORMS' POSITIONS AND SIZES THEN ALLOCATES IT TO A VECTOR
    gColliders.resize(8);
    ground1 = new GameObject("assets/ground.png", renderer, -50, 580, 850, 20);
    gColliders[0].x = -50; gColliders[0].y = 580; gColliders[0].w = 900; gColliders[0].h = 20;

    ground2 = new GameObject("assets/ground.png", renderer, 300, 480, 200, 20);
    gColliders[1].x = 300; gColliders[1].y = 480; gColliders[1].w = 200; gColliders[1].h = 20;

    ground3 = new GameObject("assets/ground.png", renderer, -50, 380, 250, 20);
    gColliders[2].x = -50; gColliders[2].y = 380; gColliders[2].w = 250; gColliders[2].h = 20;

    ground4 = new GameObject("assets/ground.png", renderer, 600, 380, 250, 20);
    gColliders[3].x = 600; gColliders[3].y = 380; gColliders[3].w = 250; gColliders[3].h = 20;

    ground5 = new GameObject("assets/ground.png", renderer, 300, 280, 200, 20);
    gColliders[4].x = 300; gColliders[4].y = 280; gColliders[4].w = 200; gColliders[4].h = 20;

    ground6 = new GameObject("assets/ground.png", renderer, -50, 180, 250, 20);
    gColliders[5].x = -50; gColliders[5].y = 180; gColliders[5].w = 250; gColliders[5].h = 20;

    ground7 = new GameObject("assets/ground.png", renderer, 600, 180, 250, 20);
    gColliders[6].x = 600; gColliders[6].y = 180; gColliders[6].w = 250; gColliders[6].h = 20;

    ground8 = new GameObject("assets/ground.png", renderer, 300, 80, 200, 20);
    gColliders[7].x = 300; gColliders[7].y = 80; gColliders[7].w = 200; gColliders[7].h = 20;


    ///////////////////////////////////////////////
    //MENU
    activeMenu = true;
    titleScreen = new GameObject ("assets/title.png", renderer, 0, 0, 800, 600);
    helpScreen = new GameObject ("assets/instruct.png", renderer, 0, 0, 800, 600);

    playButton = new GameObject ("assets/playButton.png", renderer, 37, 244, 294, 92);
    helpButton = new GameObject ("assets/helpButton.png", renderer, 486, 244, 294, 92);

    backButton = new GameObject ("assets/backButton.png", renderer, 0, 0, 187, 58);
}

void Game::handleEvents()
{
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type) {
        case SDL_QUIT:
            isRunning = false;
            break;
        default:
            break;
    }

    player1->HandleEvents(event);
    player2->HandleEvents(event);
}

void Game::update()
{
    curTime = SDL_GetTicks();
/////UPDATE
    if(!Mix_PlayingMusic()&& player1->pts < 5 && player2->pts < 5){
        Mix_PlayMusic(play, -1);
    }
    {
    ground1->Update();
    ground2->Update();
    ground3->Update();
    ground4->Update();
    ground5->Update();
    ground6->Update();
    ground7->Update();
    ground8->Update();

    powerup->Update();

    player1->Update();
    player2->Update();

    text1->Update();
    text2->Update();
    timer->Update();
    subCh->Update();
    subEv->Update();

    }
/////COLLISIONS GENERAL
    {

    // POWERUP: HANDLING COLLISIONS
    if (CheckCollision::AABB(player1->collider, powerup->collider)){
        if(powerup->isActive){
        powerup->CheckPlayer(0);
        powerup->pickUpTime = curTime;
        powerup->player = 0;
        powerup->onEffect = true;
        powerup->isActive = false;
        Mix_PlayChannel(-1, power, 0);
        }
    }
    if (CheckCollision::AABB(player2->collider, powerup->collider)){
        if(powerup->isActive){
        powerup->CheckPlayer(1);
        powerup->pickUpTime = curTime;
        powerup->player = 1;
        powerup->onEffect = true;
        powerup->isActive = false;
        Mix_PlayChannel(-1, power, 0);
        }
    }

    //PLAYER 1: HANDLING COLLISIONS
   /* std::cout << player1->xpos << ", " << player1->ypos
              << "; vX: " << player1->xvel
              << ", vY: " << player1->yvel
              << "; G: " << player1->grounded
              << ", F: " << player1->falling
              << ", J: " << player1->jump << std::endl;*/

    player1->xpos += player1->xvel;
    player1->collider.x = player1->xpos;
    if (player1->xpos <= -50){
        player1->xpos = 809;
    }
    if (player1->xpos + player1->width > SCREEN_WIDTH+50){
        player1->xpos = -41;
    }

    if(CheckCollision::AABB(player1->collider, gColliders)) {
        player1->xpos -= player1->xvel;
        player1->collider.x = player1->xpos;
    }

    prev = player1->ypos;
    player1->ypos += player1->yvel;
    player1->collider.y = player1->ypos;
    pres = player1->ypos;

    if (pres > prev) {
        player1->grounded = false;
    }

    if ((player1->ypos + player1->height > SCREEN_HEIGHT ||
        CheckCollision::AABB(player1->collider, gColliders)) && (player1->yvel > 0)) {
        player1->ypos -= player1->yvel;
        player1->collider.y = player1->ypos;
        player1->grounded = true;
    }

    if ((player1->ypos + player1->height > SCREEN_HEIGHT ||
        CheckCollision::AABB(player1->collider, gColliders)) && (player1->yvel < 0)) {
        player1->ypos -= player1->yvel;
        player1->collider.y = player1->ypos;
        player1-> yvel = 0;
        player1->onGravity = true;
    }

    //PLAYER 2: HANDLING COLLISIONS
//    std::cout << player2->xpos << ", " << player2->ypos
//              << "; vX: " << player2->xvel
//              << ", vY: " << player2->yvel
//              << "; G: " << player2->grounded
//              << ", F: " << player2->falling
//              << ", F: " << player2->jump << std::endl;

    player2->xpos += player2->xvel;
    player2->collider.x = player2->xpos;


    if (player2->xpos <= -50){
        player2->xpos = 809;
    }
    if (player2->xpos + player1->width > SCREEN_WIDTH+50){
        player2->xpos = -41;
    }
    if (CheckCollision::AABB(player2->collider, gColliders)) {
        player2->xpos -= player2->xvel;
        player2->collider.x = player2->xpos;
    }

    prev = player2->ypos;
    player2->ypos += player2->yvel;
    player2->collider.y = player2->ypos;
    pres = player2->ypos;

    if (pres > prev) {
        player2->grounded = false;
    }

    if ((player2->ypos + player2->height > SCREEN_HEIGHT ||
        CheckCollision::AABB(player2->collider, gColliders)) && (player2->yvel > 0)) {
        player2->ypos -= player2->yvel;
        player2->collider.y = player2->ypos;
        player2->grounded = true;
    }
    if ((player2->ypos + player2->height > SCREEN_HEIGHT ||
        CheckCollision::AABB(player2->collider, gColliders)) && (player2->yvel < 0)) {
        player2->ypos -= player2->yvel;
        player2->collider.y = player2->ypos;
        player2->yvel = 0;
        player2->onGravity = true;
    }
    }
//////////////////////////////////////////////////////////////////
    //ROUND END
     //GAME END
    //std::cout<<curTime<<" "<<gameStartTime<<std::endl;
    if(player1->pts == 5 || player2->pts == 5){
        if(player1->pts == 5){
            p1Win->Update();
            SDL_SetTextureColorMod(Win->objText, 76, 167, 246);
        }
        else{
            p2Win->Update();
            SDL_SetTextureColorMod(Win->objText, 246, 76, 76);
        }
        Win->Update();

        if(!Mix_PlayingMusic())
            Mix_PlayMusic(win, 0);
        if(SDL_TICKS_PASSED(SDL_GetTicks(), winTime+10000)){
        Mix_HaltMusic();
        activeMenu = true;
        }
    }

    //CHASE
    if (CheckCollision::AABB(player1->hitbox, player2->hitbox)&&
             (player1->pts < 5 && player2->pts < 5)) {
        //POWERUP RESPAWN UPON ROUND END
        if(powerup->isActive){
        powerup->pspawnTime = SDL_GetTicks();
        powerup->pickUpTime = curTime-4000;
        powerup->isActive = false;
        }
        else
        curTime += 4000;
        powerup->onEffect = false;
        powerup->Effect(&player1->onPowerup, powerup->powerup);
        powerup->Effect(&player2->onPowerup, powerup->powerup);

        if(rounds%2){
        text1->RoundWin = true;
        player1->pts++;
        std::cout << "Player 1 won the round" << std::endl;
        }
        else{
        text2->RoundWin = true;
        player2->pts++;
        std::cout << "Player 2 won the round" << std::endl;
        }

        if (player1->pts == 5 || player2->pts == 5){
            winTime = SDL_GetTicks();
            Mix_HaltMusic();
        }
        if(player1->pts == 4 && player2->pts ==4)
            rounds = rand()%2;
        Mix_PlayChannel(-1, round, 0);
        ++rounds;
        timer->rectX = 20*20;
        prevTime = SDL_GetTicks();
        player1->RestartPos(rounds);
        player2->RestartPos(rounds);

    }
    //EVADE
    else if (((SDL_TICKS_PASSED(curTime, player2->spawnTime+20000)&&(rounds%2)) ||
            (SDL_TICKS_PASSED(curTime, player1->spawnTime+20000)&&(rounds%2 == 0)))&&
             (player1->pts < 5 && player2->pts < 5)) {
        //POWERUP RESPAWN UPON ROUND END
        if(powerup->isActive){
        powerup->pickUpTime = curTime-4000;
        powerup->pspawnTime = SDL_GetTicks();
        powerup->isActive = false;
        }
        else
        curTime += 4000;
        powerup->onEffect = false;
        powerup->Effect(&player1->onPowerup, powerup->powerup);
        powerup->Effect(&player2->onPowerup, powerup->powerup);


        if(rounds%2 == 0){
        text1->RoundWin = true;
        player1->pts++;
        std::cout << "Player 1 won the round" << std::endl;
        }
        else{
        text2->RoundWin = true;
        player2->pts++;
        std::cout << "Player 2 won the round" << std::endl;
        }
        if (player1->pts == 5 || player2->pts == 5){
            winTime = SDL_GetTicks();
            Mix_HaltMusic();
        }
        if(player1->pts == 4 && player2->pts ==4)
            rounds = rand()%2;
        Mix_PlayChannel(-1, round, 0);
        ++rounds;
        timer->rectX = 20*20;
        prevTime = SDL_GetTicks();
        player1->RestartPos(rounds);
        player2->RestartPos(rounds);

    }
    //Text update;
    if(rounds%2)
    {
        subCh->xpos = 0;
        subEv->xpos = 700;

        SDL_SetTextureColorMod(subCh->objText, 76, 167, 246);
        SDL_SetTextureColorMod(subEv->objText, 246, 76, 76);
    }
    else
    {
        subCh->xpos = 700;
        subEv->xpos = 0;

        SDL_SetTextureColorMod(subCh->objText, 246, 76, 76);
        SDL_SetTextureColorMod(subEv->objText, 76, 167, 246);
    }

    //TIMER
    if(SDL_TICKS_PASSED(SDL_GetTicks(), prevTime+1000)&&player1->pts < 5 && player2->pts < 5)
    {
        timer->rectX -= 20;
        prevTime = SDL_GetTicks();
    }
    //POWERUP RESPAWN THINGS, MUST BE IN THIS LINE
    if(powerup->isActive == false && player1 ->pts < 5 && player2->pts < 5)
    {
        //GIVES EFFECT TO PLAYER
        if(powerup->CheckPlayer(powerup->player) == 0 &&(curTime == powerup->pickUpTime))
        {
            if(powerup->powerup)
           {
            powerup->Effect(&player1->onPowerup, powerup->powerup);
            SDL_SetTextureColorMod(player1->objTexture, 0, 0, 255);
           }
            else
            {
                powerup->Effect(&player2->onPowerup, powerup->powerup);
                SDL_SetTextureColorMod(player2->objTexture, 246, 0 ,255);
                player2->xvel = 0;
            }
        }
        if(powerup->CheckPlayer(powerup->player) == 1 &&(curTime == powerup->pickUpTime))
        {
            if(powerup->powerup)
            {
                powerup->Effect(&player2->onPowerup, powerup->powerup);
                SDL_SetTextureColorMod(player2->objTexture, 255, 0 ,0);
            }
            else
            {
                powerup->Effect(&player1->onPowerup, powerup->powerup);
                SDL_SetTextureColorMod(player1->objTexture, 255, 0, 246);
                player1->xvel = 0;
            }
        }

        //EFFECT ENDS AFTER 4 SECONDS
        if(SDL_TICKS_PASSED(curTime, powerup->pickUpTime+3000))
        {
            powerup->onEffect = false;
            powerup->Effect(&player1->onPowerup, powerup->powerup);
            powerup->Effect(&player2->onPowerup, powerup->powerup);
            SDL_SetTextureColorMod(player1->objTexture, 255, 255 ,255);
            SDL_SetTextureColorMod(player2->objTexture, 255, 255 ,255);
        }

        //NEW POWERUP SPAWNS AFTER 5 SECONDS
        if(SDL_TICKS_PASSED(curTime, powerup->pickUpTime+4000)){
        //anti memory leak, maybe
        powerup->~PowerUp();
        pLoc = rand() % 10;
        powerup = new PowerUp("assets/powerups.png", renderer, pxLoc[pLoc], pyLoc[pLoc], 20, 30, rand() % 2);
        powerup->isActive = true;
        powerup->Update();
        }
    }
    if(powerup->isActive && (SDL_TICKS_PASSED(SDL_GetTicks(), powerup->pspawnTime + 6000)))
    {
        powerup->~PowerUp();
        pLoc = rand() % 10;
        powerup = new PowerUp("assets/powerups.png", renderer, pxLoc[pLoc], pyLoc[pLoc], 20, 30, rand() % 2);
        powerup->isActive = true;
        powerup->pspawnTime = SDL_GetTicks();
        powerup->Update();
    }

}

void Game::render()
{
    SDL_RenderClear(renderer);

    text1->Render();
    text2->Render();
    timer->Render();
    subCh->Render();
    subEv->Render();

    ground1->Render();
    ground2->Render();
    ground3->Render();
    ground4->Render();
    ground5->Render();
    ground6->Render();
    ground7->Render();
    ground8->Render();

    if(player1->pts == 5 || player2->pts == 5){
    if(player1->pts==5)
    p1Win->Render();
    else
    p2Win->Render();
    Win->Render();
    }

    powerup->Render(powerup->isActive);

    player1->Render();
    player2->Render();

    SDL_RenderPresent(renderer);
}

void Game::menuEvents()
{
    SDL_Event event;


    SDL_PollEvent(&event);
        if (event.type == SDL_QUIT)
            isRunning = false;
        if (event.type == SDL_MOUSEMOTION)
        {
            if(CheckCollision::MousePos(event.button.x, event.button.y, playButton->collider)&&!helpDisplay)
                    selectPlay = true;
            else if(CheckCollision::MousePos(event.button.x, event.button.y, helpButton->collider)&&!helpDisplay)
                    selectHelp = true;
            else if(CheckCollision::MousePos(event.button.x, event.button.y, backButton->collider)&&helpDisplay)
                    selectBack = true;
            else{
                selectPlay = false;
                selectHelp = false;
                selectBack = false;
            }
            std::cout<<event.button.x<<", "<<event.button.y<<" "<<selectHelp<<std::endl;
        }

        if(event.type == SDL_MOUSEBUTTONDOWN){
            if(event.button.button = SDL_BUTTON_LEFT && selectPlay)
            {
                selectPlay = false;
                gameStartTime = SDL_GetTicks();
                prevTime = SDL_GetTicks();
                rounds = 1;

                player1->xvel = 0;
                player2->xvel = 0;
                player1->RestartPos(rounds);
                player2->RestartPos(rounds);
                player1->pts = 0;
                player2->pts = 0;

                powerup->onEffect = false;
                powerup->Effect(&player1->onPowerup, powerup->powerup);
                powerup->Effect(&player2->onPowerup, powerup->powerup);
                powerup->pspawnTime = SDL_GetTicks();

                text1->rectX = 0;
                text2->rectX = 0;
                timer->rectX = 20*20;

                Mix_HaltMusic();
                activeMenu = false;
            }
            if(event.button.button = SDL_BUTTON_LEFT && selectHelp)
            {
                selectHelp = false;
                helpDisplay = true;
            }
            if(event.button.button = SDL_BUTTON_LEFT && selectBack)
            {
                selectBack = false;
                helpDisplay = false;
            }
        }


}

void Game::menuUpdate(){

    titleScreen->Update();

    if(helpDisplay)
    helpScreen->Update();
    if(helpDisplay)
    backButton->Update();
    if(selectPlay)
    playButton->Update();
    if(selectHelp)
    helpButton->Update();

    if(!Mix_PlayingMusic()&&activeMenu)
        Mix_PlayMusic(menu, -1);
}

void Game::menuRender(){
    SDL_RenderClear(renderer);

    titleScreen->Render();

    if(selectPlay)
        playButton->Render();

    if(selectHelp)
        helpButton->Render();

    if(helpDisplay){
        helpScreen->Render();
        backButton->Render();
    }

    SDL_RenderPresent(renderer);
}

void Game::clean()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
