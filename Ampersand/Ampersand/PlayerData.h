#pragma once

#include "CoordData.h"

// �÷��̾� ������
typedef struct _playerData
{
	// ���� ��ġ
	COORD pos;

	// ���� �ӵ�
	double xVelocity;

	// ���� ����� ���� �Ǽ��� ���� ��ġ
	double xPosDouble;
	
	// ���� ������ ȸ��
	int jumpCnt;

	// ������
	_playerData(COORD _pos) : pos(_pos), xVelocity(0), xPosDouble(0), jumpCnt(0) {}
	_playerData() : pos({ 98, 2 }), xVelocity(0), xPosDouble(0), jumpCnt(0) {}

} playerData;