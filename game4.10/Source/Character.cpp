#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Character.h"

namespace game_framework {
	
	Character::Character() {
		Initialize();
	}

	Character::~Character() {

	}

	int Character::GetX1() {
		return xPos;
	}

	int Character::GetX2() {
		if (isAttacking)
			return xPos + Attacking.Width();
		else if (isRunning)
			return xPos + Walking.Width();
		return xPos + Animation.Width();
	}

	int Character::GetY1() {
		return yPos;
	}

	int Character::GetY2() {
		if (isAttacking)
			return xPos + Attacking.Height();
		else if (isRunning)
			return xPos + Walking.Height();
		return yPos + Animation.Height();
	}

	void Character::Initialize() {
		Animation.SetDelayCount(5);
		Walking.SetDelayCount(5);
		xPos = 200;
		yPos = 200;
		isDefending = isAttacking = isJumpping = isRunning = isMovingLeft = isMovingRight = isMovingUp = isMovingDown = false;
	}

	void Character::LoadBitmap() {
		//normal
		Animation.AddBitmap(IDB_PLAYER1_NORMAL1, RGB(0, 0, 0));
		Animation.AddBitmap(IDB_PLAYER1_NORMAL2, RGB(0, 0, 0));
		Animation.AddBitmap(IDB_PLAYER1_NORMAL3, RGB(0, 0, 0));
		Animation.AddBitmap(IDB_PLAYER1_NORMAL4, RGB(0, 0, 0));

		//walking
		Walking.AddBitmap(IDB_PLAYER1_WALK1, RGB(0, 0, 0));
		Walking.AddBitmap(IDB_PLAYER1_WALK2, RGB(0, 0, 0));
		Walking.AddBitmap(IDB_PLAYER1_WALK3, RGB(0, 0, 0));
		Walking.AddBitmap(IDB_PLAYER1_WALK4, RGB(0, 0, 0));
		Walking.AddBitmap(IDB_PLAYER1_WALK3, RGB(0, 0, 0));
		Walking.AddBitmap(IDB_PLAYER1_WALK2, RGB(0, 0, 0));
		Walking.AddBitmap(IDB_PLAYER1_WALK1, RGB(0, 0, 0));

		//attack
		Attacking.AddBitmap(IDB_PLAYER1_ATTACK1, RGB(0, 0, 0));
		Attacking.AddBitmap(IDB_PLAYER1_ATTACK2, RGB(0, 0, 0));
		Attacking.AddBitmap(IDB_PLAYER1_ATTACK3, RGB(0, 0, 0));
		Attacking.AddBitmap(IDB_PLAYER1_ATTACK4, RGB(0, 0, 0));
		Attacking.AddBitmap(IDB_PLAYER1_ATTACK5, RGB(0, 0, 0));
		Attacking.AddBitmap(IDB_PLAYER1_ATTACK6, RGB(0, 0, 0));


	}

	void Character::OnMove() {
		int speed = 5;
		if (isRunning == true) {
			speed = 5;
		}
		Animation.OnMove();
		Walking.OnMove();
		Attacking.OnMove();

		if (isMovingLeft) {
			xPos -= speed;
			isRunning = true;
		}
		if (isMovingRight) {
			xPos += speed;
			isRunning = true;
		}
		if (isMovingUp) {
			yPos -= speed;
			isRunning = true;
		}
		if (isMovingDown) {
			yPos += speed;
			isRunning = true;
		}

		if (isMovingLeft==false && isMovingRight == false && isMovingUp == false && isMovingDown == false) {
			isRunning = false;
		}
	}

	void Character::SetMovingDown(bool flag) {
		isMovingDown = flag;
	}

	void Character::SetMovingUp(bool flag) {
		isMovingUp = flag;
	}

	void Character::SetMovingLeft(bool flag) {
		isMovingLeft = flag;
	}

	void Character::SetMovingRight(bool flag) {
		isMovingRight = flag;
	}

	void Character::SetRunning(bool flag) {
		isRunning = flag;
	}

	void Character::SetAttack(bool flag) {
		isAttacking = flag;
	}

	void Character::SetDefense(bool flag) {
		isDefending = flag;
	}

	void Character::SetJump(bool flag) {
		isJumpping = flag;
	}

	void Character::SetXY(int X, int Y) {
		xPos = X;
		yPos = Y;
	}

	void Character::OnShow() {
		if (isAttacking == true || (isAttacking==true && isRunning==true)) {
			Animation.SetTopLeft(xPos + 10000, yPos + 10000);
			Animation.OnShow();
			Walking.SetTopLeft(xPos + 10000, yPos + 10000);
			Walking.OnShow();
			Attacking.SetTopLeft(xPos, yPos);
			Attacking.OnShow();
		}
		else if (isRunning == true && isAttacking==false) {
			Animation.SetTopLeft(xPos + 10000, yPos + 10000);
			Animation.OnShow();
			Walking.SetTopLeft(xPos, yPos);
			Walking.OnShow();
			Attacking.SetTopLeft(xPos + 10000, yPos + 10000);
			Attacking.OnShow();
		}
		else {
			Animation.SetTopLeft(xPos, yPos);
			Animation.OnShow();
			Walking.SetTopLeft(xPos + 10000, yPos + 10000);
			Walking.OnShow();
			Attacking.SetTopLeft(xPos + 10000, yPos + 10000);
			Attacking.OnShow();

		}

	}
}