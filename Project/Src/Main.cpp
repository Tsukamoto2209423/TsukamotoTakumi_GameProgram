/*
	麻生情報ビジネス専門学校 北九州校
	学籍番号：2209423
	氏名：塚本拓海
	プログラマー
*/

#include "Game/System.h"

//メイン関数
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//ゲームの起動
	GameSystem::Start();

	//ゲームのループ
	GameSystem::MainLoop();

	//ゲームの終了
	GameSystem::Fin();

	//プログラムの終了
	return 0;

}//WinMain関数終わり括弧
