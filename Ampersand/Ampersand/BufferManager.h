#pragma once

#include <Windows.h>
#include <iostream>
#include <string>

// GAME CONSOLE SETTING

// 0, 1번 버퍼는 게임플레이, 2번 버퍼는 로딩 화면에 사용
#define BUFFER_MAX 3

#define UPDATE_CYCLE 32

#define SCREEN_COL 224
#define SCREEN_ROW 124

#define STAGE_COL 224
#define STAGE_ROW 100

#define TITLE "JUST THREE JUMP AT A TIME"

// COLOR DEFINE
#define BLACK 0
#define BLACK_L 8

#define BLUE 1
#define BLUE_L 9

#define GREEN 2
#define GREEN_L 10

#define CYAN 3
#define CYAN_L 11

#define RED 4
#define RED_L 12

#define PINK 5
#define PINK_L 13

#define YELLOW 6
#define YELLOW_L 14

#define WHITE 7
#define WHITE_L 15

// 콘솔창 폰트 설정
void InitConsoleFont(void);

// 콘솔창 크기 설정
void InitConsoleSize(void);

// 콘솔창 커서 설정
void InitConsoleCursor(void);

// 0번, 1번 스크린 버퍼 초기화
void InitBuffer(void);

// 2번 로딩 화면 버퍼 초기화
void InitLoadingBuffer(void);

// 로딩 화면 버퍼에 쓰기
void WriteLoadingBuffer(const char * str);

// 로딩 화면 버퍼에 문자열 보이기
void ShowLoadingBuffer(const char * str);
void ShowLoadingBuffer(std::string str);

// 로딩 화면 버퍼 닫기
void CloseLoadingBuffer(void);

// 현재 버퍼에 문자열 출력
void WriteCurrentBuffer(const int &x, const int &y, const char * str);
void WriteCurrentBuffer(const int &x, const int &y, const std::string &str);
void WriteCurrentBuffer(const COORD &pos, const char * str);

// 0번, 1번 버퍼에 문자열 출력
void WriteBothBuffer(const int &x, const int &y, const char * str);
void WriteBothBuffer(const COORD &pos, const char * str);
void WriteBothBuffer(const COORD &pos, const char &c);

void WriteBothBuffer(const int &x, const int &y, const std::string &str);
void WriteBothBuffer(const COORD &pos, const std::string &str);

// 0번, 1번 버퍼 뒤바꾸기
void FlipDoubleBuffer(const DWORD &delayTime);

// 버퍼 지우기
void ClearCurrentBuffer(void);
void ClearBothBuffer(void);

// 버퍼 해제
void ReleaseBothBuffer(void);

// 버퍼 색 바꾸기
void SetCurrrentBufferColor(const unsigned short &text, const unsigned short &back);
void SetBothBufferColor(const unsigned short &text, const unsigned short &back);

// 버퍼 커서 이동하기
void CurrentBufferCursorGoToXY(const int &x, const int &y);
void BothBufferCursorGoToXY(const int &x, const int &y);

// 초기화 세팅
void InitSetting(void);