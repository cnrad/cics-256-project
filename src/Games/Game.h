// Game.h
#ifndef GAME_H
#define GAME_H

// This is so all files can get/set the current game
enum Game
{
    MENU,
    SIMON,
    AIM_TRAINER
};

extern Game game;

#endif // GAME_H