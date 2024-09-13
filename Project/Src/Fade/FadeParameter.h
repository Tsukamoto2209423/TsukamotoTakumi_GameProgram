#pragma once

//フェードクラスで使う定義群
namespace FADE
{
	enum STATE
	{
		NONE,
		F_IN,
		F_OUT,
	};

	//フェードイン・フェードアウト中に見せる画像一覧
	constexpr char PATH[] = "Data/Image/Loading/LoadingImageList.csv";

	//透過度に加算する速さ
	constexpr int ALPHA_SPEED = 3;

	//画像を動かす速さ
	constexpr int MOVE_SPEED = 15;

	//画像の大きさ
	constexpr int IMAGE_SIZE = 512;
}
