#include "player.h"

int Player::getLevel(){
	return level;
}
int Player::getScore(){
	return score;
}

int Player::getBalls(){
	return balls;
}

void Player::setLevel(int level){
	this->level = level;
}
void Player::setScore(int score){
	this->score = score;
}
void Player::setBalls(int balls){
	this->balls = balls;
}