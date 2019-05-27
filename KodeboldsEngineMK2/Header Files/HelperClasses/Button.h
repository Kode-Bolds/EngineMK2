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
	KodeboldsMath::Vector4 mTextColourOriginal;
	KodeboldsMath::Vector4 mTextColourHover;

	std::function<void()> mOnClickFunction = nullptr;
	//std::function<void()> mOnHoverFunction = nullptr;
};