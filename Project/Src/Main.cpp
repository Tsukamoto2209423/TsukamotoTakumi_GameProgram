/*
	ถ๎๑rWlX๊ๅwZ kใBZ
	wะิF2209423
	ผFห{๑C
	vO}[
*/

#include "Game/System.h"

//Cึ
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//Q[ฬNฎ
	GameSystem::Start();

	//Q[ฬ[v
	GameSystem::MainLoop();

	//Q[ฬIน
	GameSystem::Fin();

	//vOฬIน
	return 0;

}//WinMainึIํ่ส
