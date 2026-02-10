#pragma once
#include "Monster.h"
#include <iostream>

class Skeleton : public Monster {
	
public : 
	Skeleton() : Monster("Ã¢À» µç ½ºÄÌ·¹Åæ", 30, 25, 10, 10, 30, 40, 20) {}

	void attackEffect() override {
		std::cout << ">> [Ã¢À» µç ½ºÄÌ·¹Åæ] »ß±×´ö°Å¸®¸ç Ã¢À¸·Î Âî¸¥´Ù! <<" << std::endl;
	}
};

