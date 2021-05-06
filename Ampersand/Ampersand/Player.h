#pragma once

#include "PlayerData.h"

// 플레이어 화면에 출력
void PrintPlayer(const playerData& data, const int &mode);

// 플레이어 수직 이동
void ChangeVerticalPos(playerData& data);

// 플레이어 수평 이동
void ChangeHorizontalPos(playerData& data, const int &yDir);

// 플레이어 중력 적용
void GetGravity(playerData& data);

// 플레이어 땅 위에 있는지 확인
bool CheckGround(const playerData& data, const int &xPos);

// 플레이어 점프
void Jump(playerData& data);

// 플레이어 충돌 체크, -1 : 장애물과 충돌, 0 또는 양의 정수 : 충돌한 코인의 개수
int CheckCollision(const playerData& data);

// 플레이어 루프
void PlayerLoop(playerData& data);