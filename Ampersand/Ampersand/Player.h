#pragma once

void InitPlayer(void);
void PrintPlayer(int mode);

void ChangeXPos(void);
void ChangeYPos(int yDir);

void GetGravity(void);
bool CheckGround(int xPos);
void Jump(void);

void UpdatePlayer(void);