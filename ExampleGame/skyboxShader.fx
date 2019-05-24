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
	Pointlight pointLights[5];
}


Texture2D txDiffuse : register(t0);
SamplerState txDiffSampler : register(s0);

Texture2D txBump : register(t1);
SamplerState txBumpSampler : register(s1);


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
	float4 PosWorld : TEXCOORD0;
	float2 TexCoord : TEXCOORD1;
};


//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
PS_INPUT VS(VS_INPUT input)
{
	PS_INPUT output = (PS_INPUT)0;

	float3 pos = input.Pos;
	pos *= 10000;
	pos += CameraPosition.xyz;
	
	output.Pos = mul(float4(pos, 1.0f), World);
	output.Pos = mul(output.Pos, View);
	output.Pos = mul(output.Pos, Projection);
	output.Normal = mul(World, float4(input.Normal, 1.0f)).xyz;
	output.Normal = normalize(output.Normal);
	output.PosWorld = mul(float4(input.Pos, 1.0f), World);
	output.TexCoord = input.TexCoord;

	return output;
}

float random(in float2 st) 
{
	return frac(sin(dot(st.xy,
		float2(12.9898, 78.233)))
		* 43758.5453123);
}


float noise(in float2 st)
{
	float2 i = floor(st);
	float2 f = frac(st);

	// Four corners in 2D of a tile
	float a = random(i);
	float b = random(i + float2(1.0, 0.0));
	float c = random(i + float2(0.0, 1.0));
	float d = random(i + float2(1.0, 1.0));

	// Smooth Interpolation

	// Cubic Hermine Curve.  Same as SmoothStep()
	float2 u = f * f*(3.0 - 2.0*f);
	// u = smoothstep(0.,1.,f);

	// Mix 4 coorners percentages
	return lerp(a, b, u.x) +
		(c - a)* u.y * (1.0 - u.x) +
		(d - b) * u.x * u.y;
}


//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 PS(PS_INPUT input) : SV_Target
{
	float noiseVal = noise(input.TexCoord * 1000);
	float noiseVal2 = noise(input.TexCoord * 500);
	float noiseVal3 = noise(input.TexCoord * 250);

	float smoke = 1 - saturate(smoothstep(0.1, 0.11, noise((input.TexCoord + float2(0.5,0.25)) * 65) * noise(input.TexCoord * 50))) * random(input.TexCoord);
	smoke *= 0.0025;

	noiseVal = smoothstep(0.8,1, pow(noiseVal, 20));
	noiseVal += smoothstep(0.8, 1, pow(noiseVal2, 20));
	noiseVal += smoothstep(0.8, 1, pow(noiseVal3, 20) );

	float3 starColour = lerp(float3(1, .5, 0.025), float3(0.025, .5, 1), random(input.TexCoord)) * noiseVal;

	float3 finalColour = starColour + smoke.rrr;
	return float4(finalColour, 1);
}
