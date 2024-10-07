#include "../inc_KdCommon.hlsli"
#include "inc_KdLessonShader.hlsli"

VSOutput main(
	float4 pos : POSITION,
	float2 uv : TEXCOORD,
	float4 color : COLOR,
	float3 normal : NORMAL, // 法線
	float3 tangent : TANGENT // 接線
)
{
	VSOutput Out;

	//受けとった位置をそのまま渡す
	Out.Pos = pos;

	//ここ重要(座標変換)
	Out.Pos = mul(pos, g_mWorld);
	Out.wPos = Out.Pos.xyz;
	Out.Pos = mul(Out.Pos, g_mView);//カメラの位置を考慮
	Out.Pos = mul(Out.Pos, g_mProj);//画面の座標に変換

	//頂点色
	Out.Color = color;

	// 法線
	Out.wN = normalize(mul(normal, (float3x3) g_mWorld));
    // 接線
	Out.wT = normalize(mul(tangent, (float3x3) g_mWorld));
    // 従接線
	float3 binormal = cross(normal, tangent);
	Out.wB = normalize(mul(binormal, (float3x3) g_mWorld));

	//UV座標
	Out.UV = uv;
	
	return Out;
}
