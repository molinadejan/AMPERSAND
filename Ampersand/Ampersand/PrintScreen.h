#pragma once

#include <Windows.h>

// �ش� ��ġ(���� ��ǥ)�� ���ӿ��� ���ڿ� ���
void PrintGameover(COORD pos);

// �ش� ��ġ(���� ��ǥ)�� �������� Ŭ���� ���ڿ� ���
void PrintStageClear(COORD pos);

// ���ӿ��� ȭ�� ���
void ShowGameover(void);

// ���� Ŭ���� ȭ�� ���
void ShowGameClear(void);

// �������� �ε� ȭ�� ���
void ShowStageLoading(const int stage);