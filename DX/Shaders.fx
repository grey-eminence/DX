struct VertexInput
{
	float2 Pos : POSITION;
	float4 Color : COLOR0;
};

struct VertexOutput
{
	float4 Pos : SV_Position;
	float4 Color : COLOR0;
};

void VSMain( VertexInput In, out VertexOutput Out )
{
	Out.Pos = float4(In.Pos, 0, 1);
	Out.Color = In.Color;
}

void PSMain( VertexOutput In, out float4 Out : SV_Target )
{
	Out = In.Color;
};

