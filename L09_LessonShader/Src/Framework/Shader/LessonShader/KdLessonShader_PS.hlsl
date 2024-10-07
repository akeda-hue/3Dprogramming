#include "../inc_KdCommon.hlsli"
#include "inc_KdLessonShader.hlsli"

//テクスチャの受け取り(画像データ)※そのままでは使えない
Texture2D g_baseTex : register(t0); //ベースカラーテクスチャ
Texture2D g_metalRoughTex : register(t1); // メタリック/ラフネステクスチャ
Texture2D g_normalTex : register(t3); // 法線マップ

//サンプラ
SamplerState g_ss : register(s0);	//通常のテクスチャ描画用

float BlinnPhong(float3 lightDir, float3 vCam, float3 normal, float specPower)
{
	float3 H = normalize(-lightDir + vCam);
	float NdotH = saturate(dot(normal, H)); // カメラの角度差(0～1)
	float spec = pow(NdotH, specPower);

	// 正規化Blinn-Phong
	return spec * ((specPower + 2) / (2 * 3.1415926535));
}

float4 main(VSOutput In) : SV_TARGET
{
	//------------------------------------------
	// 材質色
	//------------------------------------------
	float4 baseColor = g_baseTex.Sample(g_ss, In.UV) * g_BaseColor * In.Color;
	
	// カメラへの方向
	float3 vCam = g_CamPos - In.wPos;
	float camDist = length(vCam); // カメラ - ピクセル距離
	vCam = normalize(vCam);

	// 法線マップから法線ベクトル取得
	float3 wN = g_normalTex.Sample(g_ss, In.UV).rgb;

	// UV座標（0～1）から 射影座標（-1～1）へ変換
	wN = wN * 2.0 - 1.0;
	
	{
		// 3種の法線から法線行列を作成
		row_major float3x3 mTBN =
		{
			normalize(In.wT),
			normalize(In.wB),
			normalize(In.wN),
		};
	
		// 法線ベクトルをこのピクセル空間へ変換
		wN = mul(wN, mTBN);
	}

	// 法線正規化
	wN = normalize(wN);

	float4 mr = g_metalRoughTex.Sample(g_ss, In.UV);
	
	// 金属性
	float metallic = mr.b * 0.0f;
	
	// 粗さ
	float roughness = mr.g * g_Roughness;
	
	// ラフネスを逆転させ「滑らか」さにする
	float smoothness = 1.0 - roughness;
	float specPower = pow(2, 11 * smoothness); // 1～2048
	
	//------------------------------------------
	// ライティング
	//------------------------------------------
	// 最終的な色
	float3 outColor = 0;

	// 材質の拡散色　非金属ほど材質の色になり、金属ほど拡散色は無くなる
	const float3 baseDiffuse = lerp(baseColor.rgb, float3(0, 0, 0), 0.0f);

	// 材質の反射色　非金属ほど光の色をそのまま反射し、金属ほど材質の色が乗る
	const float3 baseSpecular = lerp(0.04, baseColor.rgb, 0.0f);

	float shadow = 1;
	
	//-------------------------
	// 平行光
	//-------------------------
	// Diffuse(拡散光)
	{
		// 光の方向と法線の方向との角度さが光の強さになる
		float lightDiffuse = dot(-g_DL_Dir, wN);
		lightDiffuse = saturate(lightDiffuse); // マイナス値は0にする　0(暗)～1(明)になる

		// 正規化Lambert
		lightDiffuse /= 3.1415926535;

		// 光の色 * 材質の拡散色 * 透明率
		outColor += (g_DL_Color * lightDiffuse) * baseDiffuse * baseColor.a * shadow;
	}

	// Specular(反射色)
	{
		// 反射した光の強さを求める
		// Blinn-Phong NDF
		float spec = BlinnPhong(g_DL_Dir, vCam, wN, specPower);

		// 光の色 * 反射光の強さ * 材質の反射色 * 透明率 * 適当な調整値
		outColor += (g_DL_Color * spec) * baseSpecular * baseColor.a * 0.5 * shadow;
	}

		// 全体の明度：環境光に1が設定されている場合は影響なし
	// 環境光の不透明度を下げる事により、明度ライトの周り以外は描画されなくなる
	float totalBrightness = g_AmbientLight.a;
	
	//return g_baseTex.Sample(g_ss, In.UV) * g_BaseColor * In.Color;

	return float4(outColor, baseColor.a);

}
