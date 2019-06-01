#pragma once
#include <d3d11.h>
#include "KodeBoldsMath.h"

class Quad
{
public:
	DirectX::VertexPositionColor mTopLeftPoint;
	DirectX::VertexPositionColor mTopRightPoint;
	DirectX::VertexPositionColor mBottomRightPoint;
	DirectX::VertexPositionColor mBottomLeftPoint;

	bool mIsVisible;
};