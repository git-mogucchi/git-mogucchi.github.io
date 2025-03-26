#pragma once


#define HEIGHT 600
#define WIDTH 420
#define TILE_HEIGHT 30
#define TILE_WIDTH 30

//テトリミノ
typedef struct{
	int x;
	int y;
}MINO;

//色
typedef struct {
	float r;
	float g;
	float b;
	float a;
}COLOR;