#pragma once

#include <vector>

//CSV�t�@�C���ǂݍ��ݏ���
namespace CSV_LOADER
{
	/// <summary>
	/// ������path�̊e��p�����[�^���܂Ƃ߂Ă���CSV�t�@�C����rowNum�s�ڂ����ǂݍ��݁A���̃f�[�^��Ԃ�
	/// </summary>
	/// <param name="path">�F�ǂݍ���CSV�t�@�C���ւ̃p�X</param>
	/// <param name="rowNum">�F�ǂݍ��ލs�i�c�����j</param>
	/// <param name="columnNum">�F�ǂݍ��݂͂��߂�ŏ��̗�i�������j</param>
	/// <returns> �w���Ԗڂ̃f�[�^ </returns>
	decltype(auto) LoadParameterData(const char* path, int rowNum = 1, int columnNum = 1);
	
	/// <summary>
	/// ������path��CSV�t�@�C����ǂݍ��݁A�n���h����data�ɓ����
	/// </summary>
	/// <param name="path">�F�ǂݍ���CSV�t�@�C���ւ̃p�X</param>
	/// <param name="data">�F�ǂݍ��񂾃f�[�^���i�[����z��</param>
	void LoadHandle(const char* path, std::vector<int>& data);

	/// <summary>
	/// ������path��CSV�t�@�C����ǂݍ��݁A�n���h����data�ɓ����
	/// </summary>
	/// <param name="path">�F�ǂݍ���CSV�t�@�C���ւ̃p�X</param>
	/// <param name="data">�F�ǂݍ��񂾃f�[�^���i�[����z��</param>
	void LoadHandle(const char* path, int* data);

	/// <summary>
	/// ������path��CSV�t�@�C����ǂݍ��݁A���n���h����data�ɓ����
	/// </summary>
	/// <param name="path">�F�ǂݍ���CSV�t�@�C���ւ̃p�X</param>
	/// <param name="data">�F�ǂݍ��񂾉��f�[�^�n���h�����i�[����z��</param>
	void LoadSoundHandle(const char* path, std::vector<int>& data);

};
