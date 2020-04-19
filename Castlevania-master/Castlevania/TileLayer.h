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
	std::string name; //tên TileLayer
	std::vector<std::vector<int>> tileMatrix; // <=> int** tilematrix dùng vector 2 chiều khỏi dọn rác

public:
	TileLayer(std::string name, int width, int height, int tileWidth, int tileHeight, int mapId)
		:name(name), width(width), height(height), tileWidth(tileWidth), tileHeight(tileHeight),mapID(mapId)
	{
		//tạo ma trận 2 chiều

		tileMatrix.resize(height); // tạo ra số hàng = với height
		for (int i = 0; i < height; i++)// mỗi hàng tạo ra số cột = width
			tileMatrix[i].resize(width);

	};

	void Render(D3DXVECTOR2 cam);

	// hàm gán 2 ma trận
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

