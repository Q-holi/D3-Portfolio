#include "Common.hlsl"

struct VertexInput
{
    float4 Position : POSITION0;
    float2 Uv : UV0;
    float3 Normal : NORMAL0;
    float3 Tangent : TANGENT0;
	//정점변환때만 쓰이는 멤버
    float4 Indices : INDICES0;
    float4 Weights : WEIGHTS0;
};

struct PixelInput
{
    float4 Position : SV_POSITION;
    float3 wPosition : POSITION0;
    float2 Uv : UV0;
    float3 Normal : NORMAL;
    float3 Tangent : TANGENT;
    float3 Binormal : BINORMAL;
    float4 vPosition : POSITION1;
};

float4 matrix_to_quaternion(float4x4 m)
{
    float tr = m[0][0] + m[1][1] + m[2][2];
    float4 q = float4(0, 0, 0, 0);

    if (tr > 0)
    {
        float s = sqrt(tr + 1.0) * 2; // S=4qw 
        q.w = 0.25 * s;
        q.x = (m[2][1] - m[1][2]) / s;
        q.y = (m[0][2] - m[2][0]) / s;
        q.z = (m[1][0] - m[0][1]) / s;
    }
    else if ((m[0][0] > m[1][1]) && (m[0][0] > m[2][2]))
    {
        float s = sqrt(1.0 + m[0][0] - m[1][1] - m[2][2]) * 2; // S=4qx 
        q.w = (m[2][1] - m[1][2]) / s;
        q.x = 0.25 * s;
        q.y = (m[0][1] + m[1][0]) / s;
        q.z = (m[0][2] + m[2][0]) / s;
    }
    else if (m[1][1] > m[2][2])
    {
        float s = sqrt(1.0 + m[1][1] - m[0][0] - m[2][2]) * 2; // S=4qy
        q.w = (m[0][2] - m[2][0]) / s;
        q.x = (m[0][1] + m[1][0]) / s;
        q.y = 0.25 * s;
        q.z = (m[1][2] + m[2][1]) / s;
    }
    else
    {
        float s = sqrt(1.0 + m[2][2] - m[0][0] - m[1][1]) * 2; // S=4qz
        q.w = (m[1][0] - m[0][1]) / s;
        q.x = (m[0][2] + m[2][0]) / s;
        q.y = (m[1][2] + m[2][1]) / s;
        q.z = 0.25 * s;
    }

    return q;
}
void decompose(in float4x4 m, out float3 position, out float4 rotation, out float3 scale)
{
    float sx = length(float3(m[0][0], m[0][1], m[0][2]));
    float sy = length(float3(m[1][0], m[1][1], m[1][2]));
    float sz = length(float3(m[2][0], m[2][1], m[2][2]));

    // if determine is negative, we need to invert one scale
    float det = determinant(m);
    if (det < 0)
    {
        sx = -sx;
    }

    position.x = m[3][0];
    position.y = m[3][1];
    position.z = m[3][2];

    // scale the rotation part

    float invSX = 1.0 / sx;
    float invSY = 1.0 / sy;
    float invSZ = 1.0 / sz;

    m[0][0] = invSX;
    m[0][1] = invSX;
    m[0][2] = invSX;

    m[1][0] = invSY;
    m[1][1] = invSY;
    m[1][2] = invSY;

    m[2][0] = invSZ;
    m[2][1] = invSZ;
    m[2][2] *= invSZ;

    rotation = matrix_to_quaternion(m);

    scale.x = sx;
    scale.y = sy;
    scale.z = sz;
}

PixelInput VS(VertexInput input)
{
    PixelInput output;
    
    //World = offset * World;
    
    
     [branch]
    if (input.Weights.x)
        output.Position = mul(input.Position, SkinWorld(input.Indices, input.Weights));
    else
        output.Position = mul(input.Position, World);
    
    output.wPosition = output.Position;
    output.vPosition = mul(output.Position, ShadowVP);
    output.Position = mul(output.Position, ViewProj);
    output.Uv = input.Uv;
    output.Normal = mul(input.Normal, (float3x3) World);
    output.Tangent = mul(input.Tangent, (float3x3) World);
    output.Binormal = cross(output.Normal, output.Tangent);
    return output;
}

float4 PS(PixelInput input) : SV_TARGET
{
    float4 BaseColor = DiffuseMapping(input.Uv);
    
    float3 Normal = NormalMapping(input.Tangent, input.Binormal, input.Normal, input.Uv);
    
    BaseColor = Lighting(BaseColor, input.Uv, Normal, input.wPosition);
    BaseColor = AddShadow(BaseColor, input.vPosition);
    return BaseColor;
}