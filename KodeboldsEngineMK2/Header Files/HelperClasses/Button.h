#pragma once
#include <wrl.h>
#include <d3d11.h>
#include "functional"

#include "Sprite.h"
#include "Text.h"

class Button
{
public:
	Sprite mSprite;
	Text mText;
	std::function<void()> mOnClickFunction = nullptr;
};