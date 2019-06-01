struct DirectionalLight
{
	float3 direction;
	float padding;
	float4 colour;
};

struct Pointlight
{
	float4 position;
	float4 colour;
	float range;
	float3 padding2;
};

//--------------------------------------------------------------------------------------
// Constant Buffer Variables
//--------------------------------------------------------------------------------------
cbuffer ConstantBuffer : register(b0)
{
	float4x4 World;
	float4x4 View;
	float4x4 Projection;
	float4 CameraPosition;
	float4 Colour;
	float Time;
	float3 padding3;
}

//A lighting buffer would be nice, could do with setting ambient light in here too

cbuffer LightingBuffer : register (b1)
{
	float numDirLights;
	float3 padding4;
	DirectionalLight dirLights[2];

	float numPointLights; //5 max
	float3 padding5;
	Pointlight pointLights[20];
}

cbuffer DistortionBuffer : register (b2)
{
	float distStrength; //In UV space so keep number below zero
	float3 padding6;
}

Texture2D txDiffuse : register(t0);
SamplerState txDiffSampler : register(s0);

Texture2D txDistortion : register(t1);
SamplerState txBumpSampler : register(s1);

Texture2D txRenderTarget : register(t3);


//--------------------------------------------------------------------------------------
// Shader Inputs
//--------------------------------------------------------------------------------------
struct VS_INPUT
{
	float3 Pos : POSITION;
	float3 Normal : NORMAL;
	//float3 Tangent : TANGENT;
	//float3 Binormal : BINORMAL;
	float2 TexCoord : TEXCOORD0;
	//float3 InstancePos : INSTANCEPOS;
};

struct PS_INPUT
{
	float4 Pos : SV_POSITION;
	float3 Normal: NORMAL;
	float2 canvasXY : TEXCOORD0;
	float2 UV : TEXCOORD1;
};


//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
PS_INPUT VS(VS_INPUT input)
{
	PS_INPUT output = (PS_INPUT)0;

	output.Pos = float4(sign(input.Pos.xy), 0, 1);
	float aspectRatio = Projection._m11 / Projection._m00;
	output.canvasXY = sign(input.Pos.xy) * float2(aspectRatio, 1.0);
	output.UV = sign(input.Pos.xy) / 2.f + 0.5;
	return output;

}


//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 PS(PS_INPUT input) : SV_Target
{
	   ///vec2 uv = vec2(gl_FragCoord.x / windowDimensions.x,  gl_FragCoord.y / windowDimensions.y);

	float2 pos = input.UV;// *windowDimensions;
	float4 distMap = txDistortion.Sample(txDiffSampler, input.UV);

	//Dist = distortion not distance

	float2 distDir = normalize(float2(distMap.x * 2 - 1, distMap.y * 2 - 1));
	float amnt = distMap.z;
	float distStr = 0.155;
	pos -= amnt * distStr * distDir;

	float4 backgroundSample = txRenderTarget.Sample(txDiffSampler, pos);
	backgroundSample.a = 1;

	//outputColor = distMap;
	return backgroundSample;

	//return float4(input.UV.xy,0, 1);
}
