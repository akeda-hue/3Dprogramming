//定数バッファ(メッシュ単位)
cbuffer cbMesh : register(b1)//b1スロットを見る
{
	//オブジェクト情報
	row_major float4x4 g_mWorld;//ワールド変換行列
}


//頂点シェーダーから出力するデータ
struct VSOutput
{
	float4 Pos : SV_Position;
};
