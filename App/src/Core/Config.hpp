#pragma once

namespace Config
{
	inline constexpr double CamMoveSpeed = { 20.0f };
	inline constexpr double CamRotateSpeed = { 0.001f };
	inline constexpr double CamFOV = { 30_deg };
	inline constexpr Vec3 CamInitialPosition{ 0, 16, -32 };
	inline constexpr double CamZoomSpeed = { 1.0f };
}

//シーンID
enum class SceneState
{
	Title,
	Game,
};

//シーンマネージャーの状態
enum class ManagerState
{
	Standby,     //待機中
	FadeOut,     //フェードアウト中
	ChangeScene, //シーン切り替え中
	FadeIn,      //フェードイン中
};

//フェードの状態
enum class FadeState
{
	Non,
	FadeOut,
	FadeIn,
};

//クリックされたタイルのグリッド座標
struct GridIndex
{
	int row;
	int col;

	// < 演算子を追加
	bool operator<(const GridIndex& other) const
	{
		if (row != other.row)
		{
			return row < other.row;
		}
		return col < other.col;
	}
};
