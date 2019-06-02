//--------------------------------------------------------------------------------------
// Constant Buffer Variables
//--------------------------------------------------------------------------------------
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
/*
cbuffer LightingBuffer : register (b1)
{
	float numDirLights;
	float3 padding4;
	DirectionalLight dirLights[2];

	float numPointLights; //5 max
	float3 padding5;
	Pointlight pointLights[5];
}*/
//cbuffer ConstantBufferUniform : register (b1)
//{
//	float4 LightPosition[5];
//	float4 LightColour[5];
//	uint4 NumberOfLights;
//}

//Texture2D txDiffuse : register(t0);

//SamplerState txSampler : register(s0);

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
	//float3 Normal: NORMAL;
	//float4 PosWorld : TEXCOORD0;
	//float2 TexCoord : TEXCOORD1;
};


//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
PS_INPUT VS(VS_INPUT input)
{
	PS_INPUT output = (PS_INPUT)0;
	output.Pos = mul(float4(input.Pos, 1.0f), World);
	output.Pos = mul(output.Pos, View);
	output.Pos = mul(output.Pos, Projection);
	//output.TexCoord = float2(1,1);

	return output;
}

//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 PS(PS_INPUT input) : SV_Target
{
	float depth = input.Pos.z / input.Pos.w;
	return float4(depth.rrr, 1);
}
