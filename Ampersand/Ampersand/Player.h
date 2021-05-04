#pragma once

#include "PlayerData.h"

void PrintPlayer(playerData& data, int mode);

void ChangeXPos(playerData& data);
void ChangeYPos(playerData& data, int yDir);

void GetGravity(playerData& data);
bool CheckGround(playerData& data, int xPos);
void Jump(playerData& data);

// 함정과 충돌 시 -1 반환
// 탈출구와 충돌 시 -2 반환
// 동전과 충돌시 동전의 개수 반환
int CheckCollision(playerData& data);

void UpdatePlayer(playerData& data);