#include <map>
#include <fstream>
#include <sstream>
#include "MapChipField.h"
#include <string>
#include <cassert>

namespace{
	std::map<std::string, MapChipType> mapChipTable = {
		{"0", MapChipType::kblock},
		{"1", MapChipType::kblock},
	};
}

MapCHipField::MapCHipField()
{
}

MapCHipField::~MapCHipField()
{
}

void MapCHipField::ResetmapChipData()
{
	//マップチップデータをリセット
	mapChipData_.data.clear();
	mapChipData_.data.resize(kNumBlockVirtical);
	for (std::vector<MapChipType>& mapChipDataLine : mapChipData_.data)
	{
		mapChipDataLine.resize(kNumBlockHorizontal);
	}
}

void MapCHipField::LoadMapChipCsv(const std::string& filePath)
{
	//マップチップデータをリセット
	ResetmapChipData();

	//ファイルを開く
	std::ifstream file;
	file.open(filePath);
	assert(file.is_open());

	//マップチップCSV
	std::stringstream mapChipCsv;
	//ファイルの内容を文字列ストリームにコピー
	mapChipCsv << file.rdbuf();
	//ファイルを閉じる
	file.close();

	//CSVからマップチップデータを読み込む
	for (uint32_t i = 0; i < kNumBlockVirtical; ++i)
	{
		std::string line;
		getline(mapChipCsv, line);

		//1行分の文字列をストリームに変換しやすくする
		std::istringstream line_stream(line);

		for (uint32_t j = 0; j < kNumBlockHorizontal; ++j)
		{
			std::string word;
			getline(line_stream, word, ',');

			if (mapChipTable.contains(word))
			{
				mapChipData_.data[i][j] = mapChipTable[word];
			}
		}
	}
}

MapChipType MapCHipField::getMapChipType(uint32_t xIndex, uint32_t yIndex)
{
	if (xIndex < 0 || kNumBlockHorizontal - 1 < xIndex)
	{
		return MapChipType::kblock;
	}
	if (yIndex < 0 || kNumBlockVirtical - 1 < yIndex)
	{
		return MapChipType::kblock;
	}
	return mapChipData_.data[yIndex][xIndex];
}

Vector3 MapCHipField::GetMapChipPositionByIndex(uint32_t xIndex, uint32_t yIndex)
{
	return Vector3(kBlockWidth * xIndex,kBlockHeight * (kNumBlockVirtical - 1 - yIndex), 0);
}
