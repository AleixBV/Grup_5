#pragma once
#include <windows.h>
#include <stdio.h>

#define LOG(format, ...) log(__FILE__, __LINE__, format, __VA_ARGS__);

void log(const char file[], int line, const char* format, ...);

#define CAP(n) ((n <= 0.0f) ? n=0.0f : (n >= 1.0f) ? n=1.0f : n=n)

enum update_status
{
	UPDATE_CONTINUE = 1,
	UPDATE_STOP,
	UPDATE_ERROR
};

// Configuration -----------
#define SCREEN_WIDTH 384
#define SCREEN_HEIGHT 240
#define SCREEN_SIZE 3
#define WIN_FULLSCREEN false
#define WIN_RESIZABLE false
#define WIN_BORDERLESS false
#define WIN_FULLSCREEN_DESKTOP false
#define VSYNC true
#define TITLE "R-Type"

//Enemy types

#define _RED 0
#define _WORM 1
#define _TOWER 2
#define _ROBOT 3
#define _TOWER2 4

//Boss position

#define _BOSS_POSITION -3546 * SCREEN_SIZE
