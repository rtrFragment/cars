#pragma once

#include <vector>
#include <math.h>

#include "C:\glm\glm.hpp"

enum Camera_Movement
{
	CameraMoveOnX,
	CameraMoveOnY,
	CameraMoveOnZ,
};

class Camera
{
private:

	glm::vec3 Front;
	glm::vec3 MoveFront;
	glm::vec3 Right;
	glm::vec3 WorldUp;
	float Yaw;
	float Pitch;

	float MouseSensitivity = 0.25f;

public:
	glm::vec3 Position;
	glm::vec3 Target;
	glm::vec3 Up;

	Camera()
	{
		this->Position = glm::vec3(0.0f, 0.0f, -6.0f);
		this->Target = glm::vec3(0.0f, 0.0f, 0.0f);;
		this->Up = glm::vec3(0.0f, 1.0f, 0.0f);
		
		this->WorldUp = this->Up;
		this->Front = this->Target - this->Position;
		glm::vec3 lookDir = normalize(this->Front);
		glm::vec3 projection = normalize(glm::vec3(lookDir.x, 0, lookDir.z));
		this->Pitch = glm::degrees(asin(lookDir.y));
		if (projection.z > 0)
			this->Yaw = glm::degrees(acos(projection.x));
		else
			this->Yaw = 360 - glm::degrees(acos(projection.x));
		this->updateCameraVectors();
	}

	Camera(glm::vec3 _Position, glm::vec3 _Target, glm::vec3 _Up)
	{
		this->Position = _Position;
		this->Target = _Target;
		this->Up = _Up;

		this->WorldUp = this->Up;
		this->Front = this->Target - this->Position;
		
		glm::vec3 lookDir = normalize(this->Front);
		glm::vec3 projection = normalize(glm::vec3(lookDir.x, 0, lookDir.z));
		this->Pitch = glm::degrees(asin(lookDir.y));
		if (projection.z > 0)
			this->Yaw = glm::degrees(acos(projection.x));
		else
			this->Yaw = 360 - glm::degrees(acos(projection.x));
		this->updateCameraVectors();
	}

	void MoveCamera(Camera_Movement _Direction, double _unitMoveBy,float delta)
	{
		float Speed = (float)_unitMoveBy * delta;
		if (_Direction == CameraMoveOnX)
		{
			this->Position.x += _unitMoveBy;
			this->Target.x += _unitMoveBy;
		}
		else if(_Direction == CameraMoveOnY)
		{
			this->Position.y += _unitMoveBy;
			this->Target.y += _unitMoveBy;
		}
		else if (_Direction == CameraMoveOnZ)
		{
			this->Position.z += _unitMoveBy;
			this->Target.z += _unitMoveBy;
		}
		this->updateCameraVectors();
	}


	void ProcessMouseMovement(GLfloat xoffset, GLfloat yoffset, GLboolean constrainPitch = true)
	{
		xoffset *= this->MouseSensitivity;
		yoffset *= this->MouseSensitivity;

		this->Yaw += xoffset;
		this->Pitch += yoffset;

		if (constrainPitch)
		{
			if (this->Pitch > 89.0f)
				this->Pitch = 89.0f;
			if (this->Pitch < -89.0f)
				this->Pitch = -89.0f;
		}

		this->updateCameraVectors();
	}

	void updateCameraVectors()
	{
		glm::vec3 front;
		front.x = cos(glm::radians(this->Yaw)) * cos(glm::radians(this->Pitch));
		front.y = sin(glm::radians(this->Pitch));
		front.z = sin(glm::radians(this->Yaw)) * cos(glm::radians(this->Pitch));
		this->Front = glm::normalize(front);
		this->MoveFront = glm::normalize(glm::vec3(front.x, 0, front.z));
		this->Right = glm::normalize(glm::cross(this->Front, this->WorldUp));
		this->Up = glm::normalize(glm::cross(this->Right, this->Front));
	}

	glm::mat4 getViewMatrix()
	{

		glm::vec3 f(normalize((this->Position + this->Front) - this->Position));
		glm::vec3 s(normalize(cross(f, this->Up)));
		glm::vec3 u(cross(s, f));

		glm::mat4x4 Result(1);
		Result[0][0] = s.x;
		Result[1][0] = s.y;
		Result[2][0] = s.z;
		Result[0][1] = u.x;
		Result[1][1] = u.y;
		Result[2][1] = u.z;
		Result[0][2] = -f.x;
		Result[1][2] = -f.y;
		Result[2][2] = -f.z;
		Result[3][0] = -dot(s, this->Position);
		Result[3][1] = -dot(u, this->Position);
		Result[3][2] = dot(f, this->Position);
		return Result;
	}
};