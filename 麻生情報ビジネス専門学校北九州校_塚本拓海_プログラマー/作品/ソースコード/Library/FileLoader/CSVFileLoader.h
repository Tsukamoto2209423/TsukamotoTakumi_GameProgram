#pragma once

#include <vector>

//CSVファイル読み込み処理
namespace CSV_LOADER
{
	/// <summary>
	/// 引数のpathの各種パラメータをまとめてあるCSVファイルのrowNum行目だけ読み込み、そのデータを返す
	/// </summary>
	/// <param name="path">：読み込むCSVファイルへのパス</param>
	/// <param name="rowNum">：読み込む行（縦方向）</param>
	/// <param name="columnNum">：読み込みはじめる最初の列（横方向）</param>
	/// <returns> 指定列番目のデータ </returns>
	decltype(auto) LoadParameterData(const char* path, int rowNum = 1, int columnNum = 1);
	
	/// <summary>
	/// 引数のpathのCSVファイルを読み込み、ハンドルをdataに入れる
	/// </summary>
	/// <param name="path">：読み込むCSVファイルへのパス</param>
	/// <param name="data">：読み込んだデータを格納する配列</param>
	void LoadHandle(const char* path, std::vector<int>& data);

	/// <summary>
	/// 引数のpathのCSVファイルを読み込み、ハンドルをdataに入れる
	/// </summary>
	/// <param name="path">：読み込むCSVファイルへのパス</param>
	/// <param name="data">：読み込んだデータを格納する配列</param>
	void LoadHandle(const char* path, int* data);

	/// <summary>
	/// 引数のpathのCSVファイルを読み込み、音ハンドルをdataに入れる
	/// </summary>
	/// <param name="path">：読み込むCSVファイルへのパス</param>
	/// <param name="data">：読み込んだ音データハンドルを格納する配列</param>
	void LoadSoundHandle(const char* path, std::vector<int>& data);

};
