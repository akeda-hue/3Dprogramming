//定数バッファ(メッシュ単位)
cbuffer cbMesh : register(b1)//b1スロットを見る
{
	//オブジェクト情報
	row_major float4x4 g_mWorld;//ワールド変換行列
}

//定数バッファ(マテリアル単位)
cbuffer cbMaterial : register(b2) //b2スロットを見る
{
	float4 g_BaseColor;	//ベース色
	float3 g_Emissive;	//自己発光
	float4 g_Metaliic;	//金属度
	float g_Roughness;	//粗さ
}

//頂点シェーダーから出力するデータ
struct VSOutput
{
	float4 Pos	: SV_Position;
	float3 wPos : TEXCOORD0; // ワールド3D座標
	
	float2 UV : TEXCOORD01;
	float4 Color : TEXCOORD02;
	
	float3 wN : TEXCOORD3; // ワールド法線
	float3 wT : TEXCOORD4; // ワールド接線
	float3 wB : TEXCOORD5; // ワールド従法線
};
