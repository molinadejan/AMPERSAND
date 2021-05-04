#pragma once

#include "PlayerData.h"

void PrintPlayer(playerData& data, int mode);

void ChangeXPos(playerData& data);
void ChangeYPos(playerData& data, int yDir);

void GetGravity(playerData& data);
bool CheckGround(playerData& data, int xPos);
void Jump(playerData& data);

// ������ �浹 �� -1 ��ȯ
// Ż�ⱸ�� �浹 �� -2 ��ȯ
// ������ �浹�� ������ ���� ��ȯ
int CheckCollision(playerData& data);

void UpdatePlayer(playerData& data);