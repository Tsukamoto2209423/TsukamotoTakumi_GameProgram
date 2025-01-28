#pragma once

//��`�Q
namespace NUMBER_GRAPH
{
	//�摜�p�X
	constexpr char PATH[] = { "Data/Image/Number_0_to_9.png" };

	//0�`9�̍��v10��
	constexpr int ALL_NUM = 10;

	//�摜1���̑傫��
	constexpr int SIZE = 64;

	//1�����`�悷��Ƃ��ɋ󂯂�Ԋu
	constexpr int DRAW_POS_INTERVAL = 48;

}

//0�`9�̐����̉摜��ۑ�����N���X
class NumberGraph final
{
private:
	//0�`9�̐����̉摜��ۑ�����n���h��
	static inline int graphHandle_[NUMBER_GRAPH::ALL_NUM];

public:
	/// <summary>
	/// �ꌅ�ڂ̐������珇�ɕ`�悷��֐�
	/// </summary>
	/// <param name="drawNum">�`�悷�鐔</param>
	/// <param name="initPosX">�ꌅ�ڂ̐�����X���̈ʒu</param>
	/// <param name="initPosY">�ꌅ�ڂ̐�����Y���̈ʒu</param>
	/// <param name="drawInterval">�`�悷�鐔���̊Ԋu</param>
	/// <param name="drawNumScale">�`�悷�鐔���̑傫��</param>
	static void Draw(int drawNum, int initPosX, int initPosY,int drawInterval = NUMBER_GRAPH::DRAW_POS_INTERVAL,float drawNumScale = 0.75f);

	//�����������֐�
	static void Init(void);

	//�ǂݍ��ݏ����֐�
	static void Load(void);

	//�j�������֐�
	static void Fin(void);

	//0�`9�̐����̉摜��ۑ�����n���h�����擾
	static inline int* GetGraphHandle(void) { return graphHandle_; }

	//0�`9�̐����̉摜��ۑ�����n���h���̗v�f�擾
	static inline int GetGraphHandle(int index) { return graphHandle_[index]; }

};
