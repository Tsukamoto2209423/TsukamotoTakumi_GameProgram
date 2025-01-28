#include "CSVFileLoader.h"
#include "DxLib.h"

#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

/// <summary>
/// ������path�̊e��p�����[�^���܂Ƃ߂Ă���CSV�t�@�C����rowNum�s�ڂ�����ǂݍ��݁A���̃f�[�^��Ԃ�
/// </summary>
/// <param name="path">�F�ǂݍ���CSV�t�@�C���ւ̃p�X</param>
/// <param name="rowNum">�F�ǂݍ��ލs�i�c�����j</param>
/// <param name="columnNum">�F�ǂݍ��݂͂��߂�ŏ��̗�i�������j</param>
/// <returns> �w���Ԗڂ̃f�[�^ </returns>
decltype(auto) CSV_LOADER::LoadParameterData(const char* path, int rowNum, int columnNum)
{
	//CSV�t�@�C�����J��
	std::ifstream file(path);

	//�s�f�[�^
	std::string line;

	//�擾�����Z���̃f�[�^
	std::string num;

	//�f�[�^�ꗗ
	std::vector<int> data;

	int rowCount = 1;

	int columnCount = 1;

	//1�s���ǂݍ���
	while (std::getline(file, line))
	{
		if(rowNum == rowCount)
		{
			std::stringstream lineStream(line);

			//�E��1�Z�����ǂݍ���
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
/// ������pathCSV�t�@�C����ǂݍ��݁A�n���h����data�ɓ����
/// </summary>
/// <param name="path">�F�ǂݍ���CSV�t�@�C���ւ̃p�X</param>
/// <param name="data">�F�ǂݍ��񂾃f�[�^���i�[����z��</param>
void CSV_LOADER::LoadHandle(const char* path, std::vector<int>& data)
{
	//CSV�t�@�C�����J��
	std::ifstream imageList(path);

	//�摜�̃p�X
	std::string imagePath;

	//1�s���摜��ǂݍ���
	while (std::getline(imageList, imagePath))
	{
		data.emplace_back(LoadGraph(imagePath.c_str()));
	}
}


/// <summary>
/// ������pathCSV�t�@�C����ǂݍ��݁A�n���h����data�ɓ����
/// </summary>
/// <param name="path">�F�ǂݍ���CSV�t�@�C���ւ̃p�X</param>
/// <param name="data">�F�ǂݍ��񂾃f�[�^���i�[����z��</param>
void CSV_LOADER::LoadHandle(const char* path, int* data)
{
	//CSV�t�@�C�����J��
	std::ifstream imageList(path);

	//�摜�̃p�X
	std::string imagePath;

	//�摜��ǂݍ��ޔz��̓Y����
	int imageIndex = 0;

	//1�s���摜��ǂݍ���
	while (std::getline(imageList, imagePath))
	{
		*(data + imageIndex) = LoadGraph(imagePath.c_str());

		++imageIndex;
	}
}


/// <summary>
/// ������pathCSV�t�@�C����ǂݍ��݁A���n���h����data�ɓ����
/// </summary>
/// <param name="path">�F�ǂݍ���CSV�t�@�C���ւ̃p�X</param>
/// <param name="data">�F�ǂݍ��񂾉��f�[�^�n���h�����i�[����z��</param>
void CSV_LOADER::LoadSoundHandle(const char* path, std::vector<int>& data)
{
	//CSV�t�@�C�����J��
	std::ifstream imageList(path);

	//�摜�̃p�X
	std::string imagePath;

	//1�s���摜��ǂݍ���
	while (std::getline(imageList, imagePath))
	{
		data.emplace_back(LoadSoundMem(imagePath.c_str()));
	}
}