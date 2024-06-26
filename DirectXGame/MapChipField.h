#pragma once
#include <vector>
#include <cstdint>
#include <Vector3.h>

enum class MapChipType
{
	kblank, //空白
	kblock, //空白
};

struct MapChipDate
{
	std::vector<std::vector<MapChipType>> data;
};

///<summary>
/// マップチップフィールド
///</summary>
class MapCHipField
{
public:
	MapCHipField();
	~MapCHipField();

	void ResetmapChipData();

	void LoadMapChipCsv(const std::string& filePath);

	MapChipType getMapChipType(uint32_t xIndex, uint32_t yInadex);

	Vector3 GetMapChipPositionByIndex(uint32_t xIndex, uint32_t yIndex);

	uint32_t GetNumBlockVirtical()
	{return kNumBlockVirtical; };
	uint32_t GetNumBlockHoraizontal()
	{return kNumBlockHorizontal; };

private:
	//1ブロックのサイズ
	static inline const float kBlockHeight = 2.0f;
	static inline const float kBlockWidth = 2.0f;
	//ブロックの個数
	static inline const uint32_t kNumBlockVirtical = 20;
	static inline const uint32_t kNumBlockHorizontal = 100;

	MapChipDate mapChipData_;

};