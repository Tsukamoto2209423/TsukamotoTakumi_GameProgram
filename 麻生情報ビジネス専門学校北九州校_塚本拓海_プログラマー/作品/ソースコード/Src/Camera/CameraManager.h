#pragma once

#include <vector>
#include "CameraBase.h"

#include <memory>

#ifdef _DEBUG
#define New new(_NORMAL_BLOCK,__FILE__,__LINE__)

#else
#define New new

#endif // DEBUG

namespace BOUDAMA
{
	enum CAMERA_STATE
	{
		PLAY,
		DEBUG,
	};

	class CameraManager final
	{
	private:
		static inline std::shared_ptr<CameraManager> instance_;

		std::vector<std::shared_ptr<CameraBase>> cameras_;

		CAMERA_STATE state_;

	public:
		//�R���X�g���N�^
		CameraManager() { state_ = CAMERA_STATE::PLAY; }

		//�f�X�g���N�^
		~CameraManager() {}

		//�R�s�[�R���X�g���N�^
		CameraManager(const CameraManager& other) = delete;
		CameraManager& operator=(const CameraManager& other) = delete;

		//�C���X�^���X�����E�擾
		static inline std::shared_ptr<CameraManager> GetInstance(void)
		{
			return instance_ ? instance_ : instance_ = std::make_shared<CameraManager>();
		}

		//�J�������擾
		std::vector<std::shared_ptr<CameraBase>>& GetCamera(void) { return cameras_; }

		//�ʏ�̃J�������擾
		const std::shared_ptr<CameraBase>& GetPlayCamera(void) { return GetCamera()[CAMERA_STATE::PLAY]; }

		//�f�o�b�O�̃J�������擾
		const std::shared_ptr<CameraBase>& GetDebugCamera(void) { return GetCamera()[CAMERA_STATE::DEBUG]; }

		//�J�����̏�Ԏ擾
		inline CAMERA_STATE GetState(void) const { return state_; }

		//�����������֐�
		void Init(void);

		//�ړ������֐�
		void Step(const Vector3D& playerPos);

		//�X�V�֐�
		void UpDate(void);

		//�j�������֐�
		void Fin(void);

	};
}
