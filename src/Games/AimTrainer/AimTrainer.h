#ifndef AIMTRAINER_H
#define AIMTRAINER_H

extern int timer;
extern bool isAimTrainerInitialized;

int generateXCoord();
int generateYCoord();
void drawTarget(int x, int y);
void clearTarget(int x, int y);
void AimTrainerSetup();
void AimTrainerLoop();

#endif // AIMTRAINER_H
