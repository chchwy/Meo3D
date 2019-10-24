
cbuffer GlobalBuffer
{
	matrix projectionMatrix;
};

struct VS_INPUT 
{
	float4 position : POSITION;
	float4 color : COLOR;
};

struct PS_INPUT
{
	float4 position : SV_POSITION;
	float4 color : COLOR;
};

PS_INPUT vs_main( VS_INPUT input )
{
	PS_INPUT output;
	output.position = input.position;
	output.color = input.color;
	return output;
}

float4 ps_main(PS_INPUT input) : SV_TARGET
{
	return input.color;
}
