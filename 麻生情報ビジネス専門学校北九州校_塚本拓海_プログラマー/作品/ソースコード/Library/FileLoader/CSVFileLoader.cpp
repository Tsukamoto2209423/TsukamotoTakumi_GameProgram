#include "CSVFileLoader.h"
#include "DxLib.h"

#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

/// <summary>
/// 引数のpathの各種パラメータをまとめてあるCSVファイルのrowNum行目だけを読み込み、そのデータを返す
/// </summary>
/// <param name="path">：読み込むCSVファイルへのパス</param>
/// <param name="rowNum">：読み込む行（縦方向）</param>
/// <param name="columnNum">：読み込みはじめる最初の列（横方向）</param>
/// <returns> 指定列番目のデータ </returns>
decltype(auto) CSV_LOADER::LoadParameterData(const char* path, int rowNum, int columnNum)
{
	//CSVファイルを開く
	std::ifstream file(path);

	//行データ
	std::string line;

	//取得したセルのデータ
	std::string num;

	//データ一覧
	std::vector<int> data;

	int rowCount = 1;

	int columnCount = 1;

	//1行ずつ読み込む
	while (std::getline(file, line))
	{
		if(rowNum == rowCount)
		{
			std::stringstream lineStream(line);

			//右に1セルずつ読み込む
			while (std::getline(lineStream, num))
			{
				if (columnNum <= columnCount)
				{
					data.emplace_back(std::stoi(num));
				}

				++columnCount;
			}

			break;
		}
	}

	return data;
}

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
/// 引数のpathCSVファイルを読み込み、音ハンドルをdataに入れる
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