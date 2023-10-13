#pragma once
#include "LevelLayout.h"

void LevelLayout::Init(rapidjson::Value& serializedData) {
	if (serializedData.HasMember("layout")) {
		const rapidjson::Value& layoutData = serializedData["layout"];
		if (layoutData.IsArray()) {
			for (rapidjson::SizeType i = 0; i < layoutData.Size(); i++) {
				int tileValue = layoutData[i].GetInt();
				layout.push_back(tileValue);
		/*		const rapidjson::Value& row = layoutData[i];

				if (row.IsArray()) {
					for (rapidjson::SizeType j = 0; j < row.Size(); j++) {
						int tileValue = row[j].GetInt();
						rowData.push_back(tileValue);
					}
				}

				layout.push_back(rowData);*/
			}
		}
	}

	// Parse cube positions from serialized data
	if (serializedData.HasMember("cubePositions")) {
		const rapidjson::Value& positionsData = serializedData["cubePositions"];
		if (positionsData.IsArray()) {
			for (rapidjson::SizeType i = 0; i < positionsData.Size(); i++) {
				const rapidjson::Value& position = positionsData[i];
				if (position.IsArray() && position.Size() == 3) {
					float x = static_cast<float>(position[0].GetDouble());
					float y = static_cast<float>(position[1].GetDouble());
					float z = static_cast<float>(position[2].GetDouble());
					cubePositions.emplace_back(x, y, z);
				}
			}
		}
	}
}
void LevelLayout::Test() {

}