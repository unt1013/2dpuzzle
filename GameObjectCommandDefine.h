#pragma once

typedef struct tagKeyBuffer
{
	bool isActive;

	bool left;
	bool up;
	bool right;
	bool down;

	tagKeyBuffer(bool b = false)
	{
		isActive = false;
		left = b;
		up = b;
		right = b;
		down = b;
	}
}KEYBUF;