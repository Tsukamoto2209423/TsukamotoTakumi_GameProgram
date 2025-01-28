#pragma once

namespace FRAMERATE
{
	//�ݒ�t���[�����[�g
	constexpr int FRAME_RATE = 60;

	//�P�t���[���̎���(�~���b)
	constexpr int FRAME_TIME = (1000 / FRAME_RATE);
}

//�t���[�����[�g���
class FrameRate
{
private:
	static inline int currentTime_;			//���݂̎���
	static inline int lastFrameTime_;		//�O��̃t���[�����s���̎���
	static inline int count_;				//�t���[���J�E���g�p
	static inline int calcFpsTime_;			//FPS���v�Z��������
	static inline float fps_;				//�v������FPS(�\���p)

public:
	//�����֐�
	static void Step();

	//�X�V�֐�
	static void Update(void);

	//�������s����֐�
	static bool IsPassedFrameRateTime(void);

	//FPS�v�Z�֐�
	static void CalcFPS(void);

	//FPS�\���֐�
	static void DrawFPS(void);
};
