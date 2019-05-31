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

	bool mIsVisible;

	std::function<void()> mOnClickFunction = nullptr;

	void SetVisibility(bool pIsVisible) {
		mIsVisible = pIsVisible;
		mSprite.mIsVisible = pIsVisible;
		mText.mIsVisible = pIsVisible;
	}
	//std::function<void()> mOnHoverFunction = nullptr;
};