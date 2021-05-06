#pragma once

#include "PlayerData.h"

// �÷��̾� ȭ�鿡 ���
void PrintPlayer(const playerData& data, const int &mode);

// �÷��̾� ���� �̵�
void ChangeVerticalPos(playerData& data);

// �÷��̾� ���� �̵�
void ChangeHorizontalPos(playerData& data, const int &yDir);

// �÷��̾� �߷� ����
void GetGravity(playerData& data);

// �÷��̾� �� ���� �ִ��� Ȯ��
bool CheckGround(const playerData& data, const int &xPos);

// �÷��̾� ����
void Jump(playerData& data);

// �÷��̾� �浹 üũ, -1 : ��ֹ��� �浹, 0 �Ǵ� ���� ���� : �浹�� ������ ����
int CheckCollision(const playerData& data);

// �÷��̾� ����
void PlayerLoop(playerData& data);