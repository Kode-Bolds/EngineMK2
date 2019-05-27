

struct DirectionalLight
{
	float3 direction;
	float4 colour;
};

struct Pointlight
{
	float4 position;
	float4 colour;

	float range;
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
	//float4 Time;

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

Texture2D txRenderTexture : register(t3);


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
	output.Pos = mul(float4(input.Pos, 1.0f), World);
	output.Pos = mul(output.Pos, View);
	output.Pos = mul(output.Pos, Projection);
	output.Normal = mul(World, float4(input.Normal, 1.0f)).xyz;
	output.Normal = normalize(output.Normal);
	output.PosWorld = mul(float4(input.Pos, 1.0f), World);
	output.TexCoord = input.TexCoord;

	return output;
}

float4 CalcLightColour(float4 matDiffuse, float4 matSpec, float3 viewDirection, float3 lightDir, float4 lightColour, PS_INPUT input)
{
	float diffuse = max(0.0, dot(lightDir, input.Normal));
	float3 R = normalize(reflect(-lightDir, input.Normal));
	float spec = pow(max(0.0, dot(viewDirection, R)), 50);

	return (lightColour * matDiffuse * diffuse) + (lightColour * matSpec * spec);
}

float3x3 cotangent_frame(float3 N, float3 p, float2 uv)
{
	// get edge vectors of the pixel triangle
	float3 dp1 = ddx(p);
	float3 dp2 = ddy(p);
	float2 duv1 = ddx(uv);
	float2 duv2 = ddy(uv);

	// solve the linear system
	float3 dp2perp = cross(dp2, N);
	float3 dp1perp = cross(N, dp1);
	float3 T = dp2perp * duv1.x + dp1perp * duv2.x;
	float3 B = dp2perp * duv1.y + dp1perp * duv2.y;

	// construct a scale-invariant frame 
	float invmax = rsqrt(max(dot(T, T), dot(B, B)));
	return transpose(float3x3(T * invmax, B * invmax, N));
}

float3 perturb_normal(float3 N, float3 V, float2 texcoord)
{
	// assume N, the interpolated vertex normal and 
	// V, the view vector (vertex to eye)
	float3 map = txBump.Sample(txBumpSampler, texcoord).xyz; 
	////float4 texColour = txDiffuse.Sample(txSampler, input.TexCoord);

	//map.y = -map.y;
	float3x3 TBN = cotangent_frame(N, -V, texcoord);
	return normalize(mul(TBN, map));
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

float2 random2(float2 st)
{
	st = float2(dot(st, float2(127.1, 311.7)),
		dot(st, float2(269.5, 183.3)));
	return -1.0 + 2.0*frac(sin(st)*43758.5453123);
}

float noise2(in float2 st)
{
	float2 i = floor(st);
	float2 f = frac(st);

	float2 u = f * f*(3.0 - 2.0*f);

	return lerp(lerp(dot(random2(i + float2(0.0, 0.0)), f - float2(0.0, 0.0)),
		dot(random2(i + float2(1.0, 0.0)), f - float2(1.0, 0.0)), u.x),
		lerp(dot(random2(i + float2(0.0, 1.0)), f - float2(0.0, 1.0)),
			dot(random2(i + float2(1.0, 1.0)), f - float2(1.0, 1.0)), u.x), u.y);
}



//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 PS(PS_INPUT input) : SV_Target
{
	float fill = 0;

	float2 uv = input.TexCoord * 5 + noise((input.TexCoord) * 2) + Time * 0.01; //+ (noise(input.TexCoord * 20));// *time;
	//uv.x += Time;

	//colour = 1. * smoothstep(.18, .2, noise(uv)); // Big black drops
	fill += smoothstep(-.55, .2, noise2(uv*10.)); // Black splatter
	fill -= smoothstep(.35 + (sin(Time) * 0.3), .8, noise2(uv*10.));

	fill = pow((1 - fill), sin(Time.x) + 10);

	float3 sunBrightSpot = float3(1, 1, 0.9) * fill;

	float3 sunOrange = float3(1, 0.5, 0);
	float3 sunYellow = float3(0.1, 0.1, 0);

	
	float testNoise = noise2((input.TexCoord * 50) - Time);
	float testNoise2 = noise2((input.TexCoord * 100) + Time);


	//return (testNoise * testNoise2).rrrr;


	float3 sunColour = lerp(sunOrange, sunYellow, testNoise * testNoise2);
	float3 colour = sunColour + sunBrightSpot ;


	float3 viewDirection = normalize(CameraPosition - input.PosWorld);

	float rim = 1 - saturate(dot(viewDirection, input.Normal));

	colour += pow(rim.rrr, 3);

	//colour = noise(input.TexCoord * 25);
	return float4(colour,1);

}
