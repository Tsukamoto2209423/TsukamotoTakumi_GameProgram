#pragma once

#include <vector>

//CSVファイル読み込み処理
namespace CSV_LOADER
{
	/// <summary>
	/// 引数のpathCSVファイルを読み込み、ハンドルをdataに入れる
	/// </summary>
	/// <param name="path">：読み込むCSVファイルへのパス</param>
	/// <param name="data">：読み込んだデータを格納する配列</param>
	void LoadHandle(const char* path, std::vector<int>& data);

	/// <summary>
	/// 引数のpathCSVファイルを読み込み、ハンドルをdataに入れる
	/// </summary>
	/// <param name="path">：読み込むCSVファイルへのパス</param>
	/// <param name="data">：読み込んだデータを格納する配列</param>
	void LoadHandle(const char* path, int* data);

	/// <summary>
	/// 引数のpathCSVファイルを読み込み、ハンドルをdataに入れる
	/// </summary>
	/// <param name="path">：読み込むCSVファイルへのパス</param>
	/// <param name="data">：読み込んだ音データハンドルを格納する配列</param>
	void LoadSoundHandle(const char* path, std::vector<int>& data);

};
