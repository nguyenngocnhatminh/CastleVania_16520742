#pragma once
#include<string>
#include<vector>
#include<d3dx9.h>
class TileLayer
{
private:
	int width; 
	int height;
	int tileWidth;
	int tileHeight;
	int mapID;
	std::string name; 
	std::vector<std::vector<int>> tileMatrix;
public:
	TileLayer(std::string name, int width, int height, int tileWidth, int tileHeight, int mapId)
		:name(name), width(width), height(height), tileWidth(tileWidth), tileHeight(tileHeight),mapID(mapId)
	{
		tileMatrix.resize(height); 
		for (int i = 0; i < height; i++)
			tileMatrix[i].resize(width);

	};

	void Render(D3DXVECTOR2 cam);

	void SetTileMatrix(std::vector<std::vector<int>> tileMatrix)
	{
		for (size_t i = 0; i < height; i++)
		{
			for (size_t j = 0; j < width; j++)
			{
				this->tileMatrix[i][j] = tileMatrix[i][j];
			}
		}


	}

};

