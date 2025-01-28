/*
	麻生情報ビジネス専門学校 北九州校
	学籍番号：2209423
	氏名：塚本拓海
	プログラマー
*/

#include "Game/GameSystem.h"

//メイン関数
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//ゲームの起動
	BOUDAMA::GameSystem::Start();

	//ゲームのループ
	BOUDAMA::GameSystem::MainLoop();

	//ゲームの終了
	BOUDAMA::GameSystem::Fin();

	//プログラムの終了
	return 0;

}//WinMain関数終わり括弧
