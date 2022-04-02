#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Enemy.h"
#include "Character.h"

namespace game_framework {

	Enemy::Enemy() {
		Initialize();
	}

	Enemy::~Enemy() {
		
	}

	bool Enemy::GetAlive() {
		return isAlive;
	}

	int Enemy::GetX1() {
		return xPos;
	}

	int Enemy::GetX2() {
		return xPos + Animation.Width();
	}

	int Enemy::GetY1() {
		return yPos;
	}

	int Enemy::GetY2() {
		return yPos + Animation.Height();
	}

	int Enemy::GetHealth() {
		return HealthPoint;
	}

	int Enemy::GetDir() {
		return direction;
	}

	void Enemy::Initialize() {
		Animation.SetDelayCount(5);
		AnimationReverse.SetDelayCount(5);
		Walking.SetDelayCount(5);
		WalkingReverse.SetDelayCount(5);
		Attacking.SetDelayCount(5);
		Jump.SetDelayCount(5);
		JumpReverse.SetDelayCount(5);
		Running.SetDelayCount(5);
		RunningReverse.SetDelayCount(5);
		Knock.SetDelayCount(5);
		KnockBack.SetDelayCount(5);
		KnockReverse.SetDelayCount(5);
		KnockBackReverse.SetDelayCount(5);
		Getup.SetDelayCount(5);
		GetupReverse.SetDelayCount(5);

		xPos = 600;
		yPos = 200;
		InitialVelocity = 10;
		YVelocity = InitialVelocity;
		isGettingUp = isDefending = isAttacking = isJumpping = isWalking = isMovingLeft = isMovingRight = isMovingUp = isMovingDown = false;
		isGettingHit = 0;
		direction = 1;

		HealthPoint = 200;
		AttackPoint = 10;
		DefencePoint = 5;
	}

	void Enemy::LoadBitmap() {
		//Normal
		Animation.AddBitmap(IDB_PLAYER0_NORMAL1, RGB(0, 0, 0));
		Animation.AddBitmap(IDB_PLAYER0_NORMAL2, RGB(0, 0, 0));
		Animation.AddBitmap(IDB_PLAYER0_NORMAL3, RGB(0, 0, 0));
		Animation.AddBitmap(IDB_PLAYER0_NORMAL4, RGB(0, 0, 0));

		//Normal Reverse
		AnimationReverse.AddBitmap(IDB_PLAYER1_NORMAL1_REVERSE, RGB(0, 0, 0));
		AnimationReverse.AddBitmap(IDB_PLAYER1_NORMAL2_REVERSE, RGB(0, 0, 0));
		AnimationReverse.AddBitmap(IDB_PLAYER1_NORMAL3_REVERSE, RGB(0, 0, 0));
		AnimationReverse.AddBitmap(IDB_PLAYER1_NORMAL4_REVERSE, RGB(0, 0, 0));

		//Walking
		Walking.AddBitmap(IDB_PLAYER0_WALK1, RGB(0, 0, 0));
		Walking.AddBitmap(IDB_PLAYER0_WALK2, RGB(0, 0, 0));
		Walking.AddBitmap(IDB_PLAYER0_WALK3, RGB(0, 0, 0));
		Walking.AddBitmap(IDB_PLAYER0_WALK4, RGB(0, 0, 0));
		Walking.AddBitmap(IDB_PLAYER0_WALK3, RGB(0, 0, 0));
		Walking.AddBitmap(IDB_PLAYER0_WALK2, RGB(0, 0, 0));
		Walking.AddBitmap(IDB_PLAYER0_WALK1, RGB(0, 0, 0));

		//Walking Reverse
		WalkingReverse.AddBitmap(IDB_PLAYER0_WALK1_REVERSE, RGB(0, 0, 0));
		WalkingReverse.AddBitmap(IDB_PLAYER0_WALK2_REVERSE, RGB(0, 0, 0));
		WalkingReverse.AddBitmap(IDB_PLAYER0_WALK3_REVERSE, RGB(0, 0, 0));
		WalkingReverse.AddBitmap(IDB_PLAYER0_WALK4_REVERSE, RGB(0, 0, 0));
		WalkingReverse.AddBitmap(IDB_PLAYER0_WALK3_REVERSE, RGB(0, 0, 0));
		WalkingReverse.AddBitmap(IDB_PLAYER0_WALK2_REVERSE, RGB(0, 0, 0));
		WalkingReverse.AddBitmap(IDB_PLAYER0_WALK1_REVERSE, RGB(0, 0, 0));

		//Attack
		Attacking.AddBitmap(IDB_PLAYER1_ATTACK1, RGB(0, 0, 0));
		Attacking.AddBitmap(IDB_PLAYER1_ATTACK2, RGB(0, 0, 0));
		Attacking.AddBitmap(IDB_PLAYER1_ATTACK3, RGB(0, 0, 0));
		Attacking.AddBitmap(IDB_PLAYER1_ATTACK4, RGB(0, 0, 0));
		Attacking.AddBitmap(IDB_PLAYER1_ATTACK5, RGB(0, 0, 0));
		Attacking.AddBitmap(IDB_PLAYER1_ATTACK6, RGB(0, 0, 0));

		//Attack Reverse
		AttackingReverse.AddBitmap(IDB_PLAYER1_ATTACK1_REVERSE, RGB(0, 0, 0));
		AttackingReverse.AddBitmap(IDB_PLAYER1_ATTACK2_REVERSE, RGB(0, 0, 0));
		AttackingReverse.AddBitmap(IDB_PLAYER1_ATTACK3_REVERSE, RGB(0, 0, 0));
		AttackingReverse.AddBitmap(IDB_PLAYER1_ATTACK4_REVERSE, RGB(0, 0, 0));
		AttackingReverse.AddBitmap(IDB_PLAYER1_ATTACK5_REVERSE, RGB(0, 0, 0));
		AttackingReverse.AddBitmap(IDB_PLAYER1_ATTACK6_REVERSE, RGB(0, 0, 0));

		//Jump
		Jump.AddBitmap(IDB_PLAYER1_JUMP3, RGB(0, 0, 0));
		Jump.AddBitmap(IDB_PLAYER1_JUMP3, RGB(0, 0, 0));
		Jump.AddBitmap(IDB_PLAYER1_JUMP3, RGB(0, 0, 0));
		Jump.AddBitmap(IDB_PLAYER1_JUMP3, RGB(0, 0, 0));
		Jump.AddBitmap(IDB_PLAYER1_JUMP3, RGB(0, 0, 0));
		Jump.AddBitmap(IDB_PLAYER1_JUMP3, RGB(0, 0, 0));
		Jump.AddBitmap(IDB_PLAYER1_JUMP1, RGB(0, 0, 0));
		Jump.AddBitmap(IDB_PLAYER1_JUMP2, RGB(0, 0, 0));
		Jump.AddBitmap(IDB_PLAYER1_JUMP1, RGB(0, 0, 0));

		//Jump Reverse
		JumpReverse.AddBitmap(IDB_PLAYER1_JUMP3_REVERSE, RGB(0, 0, 0));
		JumpReverse.AddBitmap(IDB_PLAYER1_JUMP3_REVERSE, RGB(0, 0, 0));
		JumpReverse.AddBitmap(IDB_PLAYER1_JUMP3_REVERSE, RGB(0, 0, 0));
		JumpReverse.AddBitmap(IDB_PLAYER1_JUMP3_REVERSE, RGB(0, 0, 0));
		JumpReverse.AddBitmap(IDB_PLAYER1_JUMP3_REVERSE, RGB(0, 0, 0));
		JumpReverse.AddBitmap(IDB_PLAYER1_JUMP3_REVERSE, RGB(0, 0, 0));
		JumpReverse.AddBitmap(IDB_PLAYER1_JUMP1_REVERSE, RGB(0, 0, 0));
		JumpReverse.AddBitmap(IDB_PLAYER1_JUMP2_REVERSE, RGB(0, 0, 0));
		JumpReverse.AddBitmap(IDB_PLAYER1_JUMP1_REVERSE, RGB(0, 0, 0));

		//Running
		Running.AddBitmap(IDB_PLAYER1_RUN1, RGB(0, 0, 0));
		Running.AddBitmap(IDB_PLAYER1_RUN2, RGB(0, 0, 0));
		Running.AddBitmap(IDB_PLAYER1_RUN3, RGB(0, 0, 0));
		Running.AddBitmap(IDB_PLAYER1_RUN2, RGB(0, 0, 0));

		//Running Reverse
		RunningReverse.AddBitmap(IDB_PLAYER1_RUN1_REVERSE, RGB(0, 0, 0));
		RunningReverse.AddBitmap(IDB_PLAYER1_RUN2_REVERSE, RGB(0, 0, 0));
		RunningReverse.AddBitmap(IDB_PLAYER1_RUN3_REVERSE, RGB(0, 0, 0));
		RunningReverse.AddBitmap(IDB_PLAYER1_RUN2_REVERSE, RGB(0, 0, 0));

		//Knock
		Knock.AddBitmap(IDB_PLAYER0_KNOCK1, RGB(0, 0, 0));
		Knock.AddBitmap(IDB_PLAYER0_KNOCK2, RGB(0, 0, 0));
		Knock.AddBitmap(IDB_PLAYER0_KNOCK3, RGB(0, 0, 0));
		Knock.AddBitmap(IDB_PLAYER0_KNOCK4, RGB(0, 0, 0));
		Knock.AddBitmap(IDB_PLAYER0_KNOCK5, RGB(0, 0, 0));
		Knock.AddBitmap(IDB_PLAYER0_KNOCK5, RGB(0, 0, 0));

		KnockReverse.AddBitmap(IDB_PLAYER0_KNOCK1_REVERSE, RGB(0, 0, 0));
		KnockReverse.AddBitmap(IDB_PLAYER0_KNOCK2_REVERSE, RGB(0, 0, 0));
		KnockReverse.AddBitmap(IDB_PLAYER0_KNOCK3_REVERSE, RGB(0, 0, 0));
		KnockReverse.AddBitmap(IDB_PLAYER0_KNOCK4_REVERSE, RGB(0, 0, 0));
		KnockReverse.AddBitmap(IDB_PLAYER0_KNOCK5_REVERSE, RGB(0, 0, 0));
		KnockReverse.AddBitmap(IDB_PLAYER0_KNOCK5_REVERSE, RGB(0, 0, 0));

		KnockBack.AddBitmap(IDB_PLAYER0_KNOCKBACK1, RGB(0, 0, 0));
		KnockBack.AddBitmap(IDB_PLAYER0_KNOCKBACK2, RGB(0, 0, 0));
		KnockBack.AddBitmap(IDB_PLAYER0_KNOCKBACK3, RGB(0, 0, 0));
		KnockBack.AddBitmap(IDB_PLAYER0_KNOCKBACK4, RGB(0, 0, 0));
		KnockBack.AddBitmap(IDB_PLAYER0_KNOCKBACK5, RGB(0, 0, 0));
		KnockBack.AddBitmap(IDB_PLAYER0_KNOCKBACK5, RGB(0, 0, 0));

		KnockBackReverse.AddBitmap(IDB_PLAYER0_KNOCKBACK1_REVERSE, RGB(0, 0, 0));
		KnockBackReverse.AddBitmap(IDB_PLAYER0_KNOCKBACK2_REVERSE, RGB(0, 0, 0));
		KnockBackReverse.AddBitmap(IDB_PLAYER0_KNOCKBACK3_REVERSE, RGB(0, 0, 0));
		KnockBackReverse.AddBitmap(IDB_PLAYER0_KNOCKBACK4_REVERSE, RGB(0, 0, 0));
		KnockBackReverse.AddBitmap(IDB_PLAYER0_KNOCKBACK5_REVERSE, RGB(0, 0, 0));
		KnockBackReverse.AddBitmap(IDB_PLAYER0_KNOCKBACK5_REVERSE, RGB(0, 0, 0));

		//getup
		Getup.AddBitmap(IDB_PLAYER0_KNOCK5, RGB(0, 0, 0));
		Getup.AddBitmap(IDB_PLAYER0_GETUP1, RGB(0, 0, 0));
		Getup.AddBitmap(IDB_PLAYER0_GETUP2, RGB(0, 0, 0));
		Getup.AddBitmap(IDB_PLAYER0_GETUP2, RGB(0, 0, 0));

		GetupReverse.AddBitmap(IDB_PLAYER0_KNOCK5_REVERSE, RGB(0, 0, 0));
		GetupReverse.AddBitmap(IDB_PLAYER0_GETUP1_REVERSE, RGB(0, 0, 0));
		GetupReverse.AddBitmap(IDB_PLAYER0_GETUP2_REVERSE, RGB(0, 0, 0));
		GetupReverse.AddBitmap(IDB_PLAYER0_GETUP2_REVERSE, RGB(0, 0, 0));

		GetupBack.AddBitmap(IDB_PLAYER0_KNOCKBACK5, RGB(0, 0, 0));
		GetupBack.AddBitmap(IDB_PLAYER0_GETUPBACK1, RGB(0, 0, 0));
		GetupBack.AddBitmap(IDB_PLAYER0_GETUP2, RGB(0, 0, 0));
		GetupBack.AddBitmap(IDB_PLAYER0_GETUP2, RGB(0, 0, 0));

		GetupBackReverse.AddBitmap(IDB_PLAYER0_KNOCKBACK5_REVERSE, RGB(0, 0, 0));
		GetupBackReverse.AddBitmap(IDB_PLAYER0_GETUP1_REVERSE, RGB(0, 0, 0));
		GetupBackReverse.AddBitmap(IDB_PLAYER0_GETUP2_REVERSE, RGB(0, 0, 0));
		GetupBackReverse.AddBitmap(IDB_PLAYER0_GETUP2_REVERSE, RGB(0, 0, 0));
	}

	void Enemy::OnMove() {
		int speed = 5;
		if (isRunning == true) {
			speed = 10;
		}
		Animation.OnMove();
		AnimationReverse.OnMove();

		if (isRunning) {
			Running.OnMove();
			RunningReverse.OnMove();
		}

		if (isAttacking) {
			Attacking.OnMove();
			AttackingReverse.OnMove();
		}

		if (isGettingHit) {
			Knock.OnMove();
		}

		if (isGettingUp) {
			Getup.OnMove();
		}

		if (isJumpping || isGettingHit) {
			Jump.OnMove();
			JumpReverse.OnMove();
			if (isRising) {
				if (YVelocity > 0) {
					yPos -= YVelocity;
					YVelocity--;
				}
				else {
					isRising = false;
					YVelocity = 1;
				}
			}
			else if (!isRising) {
				if (yPos < JumpYposTemp - 1) {
					yPos += YVelocity;
					YVelocity++;
				}
				else {
					yPos = JumpYposTemp - 1;
					YVelocity = InitialVelocity;
					isJumpping = false;
					if (isGettingHit==true) {
						isGettingHit = false;
						SetGettingUp(true);
					}
				}
			}
		}

		if (isMovingLeft) {
			xPos -= speed;
			isWalking = true;
			direction = 0;
		}
		if (isMovingRight) {
			xPos += speed;
			isWalking = true;
			direction = 1;
		}
		if (isMovingUp && !isJumpping) {
			yPos -= speed;
			isWalking = true;
		}
		if (isMovingDown && !isJumpping) {
			yPos += speed;
			isWalking = true;
		}
		if (isWalking) {
			Walking.OnMove();
			WalkingReverse.OnMove();
		}
		if (isMovingLeft == false && isMovingRight == false && isMovingUp == false && isMovingDown == false) {
			isWalking = false;
		}
		if (isGettingHit) {
			if (hitDirection) {
				xPos += 7;
			}
			else {
				xPos -= 7;
			}
		}
	}

	void Enemy::SetMovingDown(bool flag) {
		isMovingDown = flag;
	}

	void Enemy::SetMovingUp(bool flag) {
		isMovingUp = flag;
	}

	void Enemy::SetMovingLeft(bool flag) {
		isMovingLeft = flag;
	}

	void Enemy::SetMovingRight(bool flag) {
		isMovingRight = flag;
	}

	void Enemy::SetGettingUp(bool flag) {
		isGettingUp = flag;
		Getup.Reset();
	}

	void Enemy::SetWalking(bool flag) {
		isWalking = flag;
	}

	void Enemy::SetAttack(bool flag) {
		isAttacking = flag;
		Attacking.Reset();
		AttackingReverse.Reset();
	}

	void Enemy::SetDefense(bool flag) {
		isDefending = flag;
	}

	void Enemy::SetRunning(bool flag) {
		isRunning = flag;
		Running.Reset();
		RunningReverse.Reset();
	}

	void Enemy::SetJump(bool flag) {
		if (!isJumpping) {
			Jump.Reset();
			JumpReverse.Reset();
			isJumpping = flag;
			YVelocity = 10;
			JumpYposTemp = yPos + 1;
			isRising = true;
		}
	}

	void Enemy::SetGettingHit(bool flag, int Dir) {
		if (isGettingHit==false) {
			//reset animation
			Knock.Reset();
			KnockReverse.Reset();
			KnockBack.Reset();
			KnockBackReverse.Reset();
			//give
			isGettingHit = flag;
			hitDirection = Dir;
			YVelocity = 10;
			JumpYposTemp = yPos + 1;
			isRising = true;
		}
	}

	void Enemy::SetAlive(bool flag) {
		isAlive = flag;
	}

	void Enemy::SetXY(int X, int Y) {
		xPos = X;
		yPos = Y;
	}

	void Enemy::ShowNormal(int Dir) {
		if (Dir == 0) {
			//left
			AnimationReverse.SetTopLeft(xPos, yPos);
			AnimationReverse.OnShow();
		}
		else if (Dir == 1) {
			//right
			Animation.SetTopLeft(xPos, yPos);
			Animation.OnShow();
		}
	}

	void Enemy::ShowWalking(int Dir) {
		if (Dir == 0) {
			//left
			WalkingReverse.SetTopLeft(xPos, yPos);
			WalkingReverse.OnShow();
		}
		else if (Dir == 1) {
			//right
			Walking.SetTopLeft(xPos, yPos);
			Walking.OnShow();
		}
	}

	void Enemy::ShowAttacking(int Dir) {
		if (Dir == 0) {
			//left
			AttackingReverse.SetTopLeft(xPos, yPos);
			AttackingReverse.OnShow();
		}
		else if (Dir == 1) {
			//right
			Attacking.SetTopLeft(xPos, yPos);
			Attacking.OnShow();
		}
	}

	void Enemy::ShowJump(int Dir) {
		if (Dir == 0) {
			//left
			JumpReverse.SetTopLeft(xPos, yPos);
			JumpReverse.OnShow();
		}
		else if (Dir == 1) {
			//right
			Jump.SetTopLeft(xPos, yPos);
			Jump.OnShow();
		}
	}

	void Enemy::ShowRun(int Dir) {
		if (Dir == 0) {
			//left
			RunningReverse.SetTopLeft(xPos, yPos);
			RunningReverse.OnShow();
		}
		else if (Dir == 1) {
			//right
			Running.SetTopLeft(xPos, yPos);
			Running.OnShow();
		}
	}

	void Enemy::ShowKnock(int Dir, int HitDir) {
		if (Dir == 0) {
			if (HitDir == 1) {
				KnockBackReverse.SetTopLeft(xPos, yPos);
				KnockBackReverse.OnShow();
				if (KnockBackReverse.IsFinalBitmap()) {
					isGettingHit = false;
				}
			}
			else if (HitDir == 0) {
				KnockReverse.SetTopLeft(xPos, yPos);
				KnockReverse.OnShow();
				if (KnockReverse.IsFinalBitmap()) {
					isGettingHit = false;
				}
			}
		}
		else if (Dir == 1) {
			if (HitDir == 1) {
				KnockBack.SetTopLeft(xPos, yPos);
				KnockBack.OnShow();
				if (KnockBack.IsFinalBitmap()) {
					isGettingHit = false;
				}
			}
			else if (HitDir == 0) {
				Knock.SetTopLeft(xPos, yPos);
				Knock.OnShow();
				if (Knock.IsFinalBitmap()) {
					isGettingHit = false;
				}
			}
		}
	}

	void Enemy::ShowGettingUP(int Dir) {
		if (Dir == 0) {
			//left
			KnockReverse.SetTopLeft(xPos, yPos);
			KnockReverse.OnShow();
		}
		else if (Dir == 1) {
			//right
			Getup.SetTopLeft(xPos, yPos);
			Getup.OnShow();
			if (Getup.IsFinalBitmap()) {
				isGettingUp = false;
			}
		}
	}

	void Enemy::OnShow() {
		if (isJumpping == true) {
			ShowJump(direction);
		}
		else if (isAttacking == true || (isAttacking == true && isWalking == true)) {
			ShowAttacking(direction);
		}
		else if (isRunning == true && isAttacking == false) {
			ShowRun(direction);
		}
		else if (isWalking == true && isAttacking == false) {
			ShowWalking(direction);
		}
		else if (isGettingHit == true) {
			ShowKnock(direction, hitDirection);
		}
		else if (isGettingUp) {
			ShowGettingUP(direction);
		}
		else {
			//Normal Animation
			ShowNormal(direction);
		}
	}
}