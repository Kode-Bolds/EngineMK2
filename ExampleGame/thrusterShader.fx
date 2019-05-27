

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

cbuffer ParticleBuffer : register (b2)
{
	//float ttl ;
	float3 padding6;
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
	float4 ParticleColour : TECXOORD2;
};


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
// Vertex Shader
//--------------------------------------------------------------------------------------
PS_INPUT VS(VS_INPUT input)
{
	PS_INPUT output = (PS_INPUT)0;

	//input.Pos.xyz = input.Pos.zyx;
	output.PosWorld = mul(float4(input.Pos, 1.0f), World);

	float index = abs(input.Pos.z);

	

	
	float ttl = 1;
	float4 inPos = float4(input.Pos, 1);
	float lifeTime = ttl - ((Time + index) % ttl);

	float n = noise(float2(Time + index * 50, Time));
	//Scaling
	input.Pos.xy = inPos.xy * (10 + n * 5) * (1 - pow(1 - lifeTime,2));// *input.Scale.xy;


	//Animation
	float pi = 3.14159265359;
	float turn = ((pi * 2) / 100) * (index * 400);
	float radius = 10;
	float3 animPos = float3(0,0,0);
	//animPos.x = sin(turn) * radius * (lifeTime);
	//animPos.y = cos(turn) * radius * (lifeTime);
	animPos.z = ((1 - lifeTime) * -50); //sin(inPos.z * 1000 + time);
	animPos = mul(float4(animPos, 1), View).xyz;


	//Colouring
	float blueness = smoothstep(0.8, 1, lifeTime);

	output.ParticleColour = float4(1 - blueness - 0.25 * noise(float2(index * 10, index * 43)), 0, blueness, 1);
	output.ParticleColour.a = 0.75;



	float4x4 worldViewMatrix = mul(World, View);
	float3 positionVS = input.Pos  + float3(worldViewMatrix._41, worldViewMatrix._42, worldViewMatrix._43);
	output.Pos = mul(float4(positionVS + animPos, 1.0f), Projection);

	output.TexCoord = input.TexCoord;

	//output.Pos.xyz += animPos;
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


//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 PS(PS_INPUT input) : SV_Target
{
	//Load texture pixels
	//Apply colour modification
	//return

	//return input.ParticleColour;

	float distFromCentre = 1 - saturate(distance(float2(0.5, 0.5), input.TexCoord));
	return float4(input.ParticleColour.xyz, distFromCentre);// , 1);
}
