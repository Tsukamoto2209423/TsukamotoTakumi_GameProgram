#include "CSVFileLoader.h"
#include "DxLib.h"

#include <string>
#include <fstream>
#include <iostream>

/// <summary>
/// 引数のpathCSVファイルを読み込み、ハンドルをdataに入れる
/// </summary>
/// <param name="path">：読み込むCSVファイルへのパス</param>
/// <param name="data">：読み込んだデータを格納する配列</param>
void CSV_LOADER::LoadHandle(const char* path, std::vector<int>& data)
{
	//CSVファイルを開く
	std::ifstream imageList(path);

	//画像のパス
	std::string imagePath;

	//1行ずつ画像を読み込む
	while (std::getline(imageList, imagePath))
	{
		data.emplace_back(LoadGraph(imagePath.c_str()));
	}
}


/// <summary>
/// 引数のpathCSVファイルを読み込み、ハンドルをdataに入れる
/// </summary>
/// <param name="path">：読み込むCSVファイルへのパス</param>
/// <param name="data">：読み込んだデータを格納する配列</param>
void CSV_LOADER::LoadHandle(const char* path, int* data)
{
	//CSVファイルを開く
	std::ifstream imageList(path);

	//画像のパス
	std::string imagePath;

	//画像を読み込む配列の添え字
	int imageIndex = 0;

	//1行ずつ画像を読み込む
	while (std::getline(imageList, imagePath))
	{
		*(data + imageIndex) = LoadGraph(imagePath.c_str());

		++imageIndex;
	}
}


/// <summary>
/// 引数のpathCSVファイルを読み込み、ハンドルをdataに入れる
/// </summary>
/// <param name="path">：読み込むCSVファイルへのパス</param>
/// <param name="data">：読み込んだ音データハンドルを格納する配列</param>
void CSV_LOADER::LoadSoundHandle(const char* path, std::vector<int>& data)
{
	//CSVファイルを開く
	std::ifstream imageList(path);

	//画像のパス
	std::string imagePath;

	//1行ずつ画像を読み込む
	while (std::getline(imageList, imagePath))
	{
		data.emplace_back(LoadSoundMem(imagePath.c_str()));
	}
}