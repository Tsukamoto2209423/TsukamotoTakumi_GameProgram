#pragma once

#include "Vector/Vector3D.h"

//�ʒu�E�����E��]���������N���X
class Transform
{
protected:
	//�ʒu
	Vector3D pos_;

	//�����x�N�g��
	Vector3D dir_;

	//��]�p�x
	Vector3D rot_;

public:
	constexpr Transform() = default;
	virtual ~Transform() = default;

public:
	//���݂̈ʒu(XYZ���W)�擾
	constexpr Vector3D GetPos(void) const noexcept { return pos_; }

	//�ʒu(XYZ���W)�ݒ�
	constexpr void SetPos(const Vector3D& pos) noexcept { pos_ = pos; }

	//�ʒu(XYZ���W)�ݒ�
	constexpr void SetPos(float x, float y, float z) noexcept { pos_.x = x; pos_.y = y; pos_.z = z; }

	//�ʒu(XYZ���W)�𓮂���
	constexpr void MovePos(const Vector3D& direction) noexcept { pos_ += direction; }
	constexpr void MovePos(float x, float y, float z) noexcept { pos_.x += x; pos_.y += y; pos_.z += z; }

	//������
	constexpr void ResetPos(void) { pos_ = { 0.0f,0.0f,0.0f }; }


	//X���擾
	constexpr float GetPosX(void) const noexcept { return pos_.x; }

	//X���ݒ�
	constexpr void SetPosX(float x) { pos_.x = x; }


	//Y���擾
	constexpr float GetPosY(void) const noexcept { return pos_.y; }

	//Y���ݒ�
	constexpr void SetPosY(float y) { pos_.y = y; }


	//Z���擾
	constexpr float GetPosZ(void) const noexcept { return pos_.z; }

	//Z���ݒ�
	constexpr void SetPosZ(float z) { pos_.z = z; }


	//�����x�N�g���擾
	constexpr Vector3D GetDir(void) const noexcept { return dir_; }

	//�����x�N�g���ݒ�
	constexpr void SetDir(const Vector3D& dir) { dir_ = dir; }
	constexpr void SetDir(float x, float y, float z) noexcept { dir_.x = x; dir_.y = y; dir_.z = z; }

	//������
	constexpr void ResetDir(void) { dir_ = { 0.0f,0.0f,0.0f }; }


	//��]������֐�
	constexpr void RotatePitch(float x) noexcept { rot_.x += x; }

	inline void RotateYaw(const Vector3D& dir) noexcept { rot_.y = std::atan2(-dir.x, -dir.z); }
	inline void RotateYaw(float x, float z) noexcept { rot_.y = std::atan2(-x, -z); }

	//��]���擾
	constexpr Vector3D GetRot(void) const noexcept { return rot_; }

	//��]���ݒ�
	constexpr void SetRot(const Vector3D& rot) { rot_ = rot; }

	//������
	constexpr void ResetRot(void) { rot_ = { 0.0f,0.0f,0.0f }; }


	//X���擾
	constexpr float GetRotX(void) const noexcept { return rot_.x; }

	//X���ݒ�
	constexpr void SetRotX(float x) { rot_.x = x; }


	//Y���擾
	constexpr float GetRotY(void) const noexcept { return rot_.y; }

	//Y���ݒ�
	constexpr void SetRotY(float y) { rot_.y = y; }


	//Z���擾
	constexpr float GetRotZ(void) const noexcept { return rot_.z; }

	//Z���ݒ�
	constexpr void SetRotZ(float z) { rot_.z = z; }
};
