#include <Landscape.h>

// 1 pixel = 1m (512x512 describes 512m2)
#define MAP_SCALE 1.0f

tfLandscape::tfLandscape(tfBitmap* height, tfBitmap* water, tfBitmap* density) 
	: m_heightMap(height), m_waterMap(water), m_densityMap(density) {
	m_height = m_heightMap->Width()*MAP_SCALE;
	m_width = m_heightMap->Height()*MAP_SCALE;
	m_roadMap = new tfRoadmap(m_width, m_height);
}

tfLandscape::~tfLandscape() {
	delete m_heightMap;
	delete m_waterMap;
	delete m_densityMap;
	delete m_roadMap;
}

float tfLandscape::HeightAt(float x, float y) {
	int pixX = (int)(x+m_width/2)/MAP_SCALE;
	int pixY = (int)(y+m_height/2)/MAP_SCALE;
	return m_heightMap->At(pixX, pixY) / 255.0f;
}

float tfLandscape::WaterAt(float x, float y) {
	int pixX = (int)(x+m_width/2)/MAP_SCALE;
	int pixY = (int)(y+m_height/2)/MAP_SCALE;
	return m_waterMap->At(pixX, pixY) / 255.0f;
}

void tfLandscape::GenerateGrid() {
	const static float plotSize = 15.0f;
	const static int numNodesX = m_width/plotSize;
	const static int numNodesY = m_height/plotSize;
	// Create the nodes and store their ids
	int nodeIds[numNodesX+1][numNodesY+1];
	memset(nodeIds, -1, sizeof(int) * (numNodesX+1)*(numNodesY+1));
	float y, x;
	int nodeX, nodeY;
	for (y = -(m_height/2), nodeY = 0; y < m_height/2; y += plotSize, nodeY++) {
		for (x = -(m_width/2), nodeX = 0; x < m_width/2; x += plotSize, nodeX++) {
			// Don't place nodes in water
			if (WaterAt(x, y) == 1.0f) {
				continue;
			}
			nodeIds[nodeX][nodeY] = m_roadMap->AddNode(x, y, HeightAt(x, y));
		}
	}
	// Create the edges between nodes
	for (int x = 0; x < numNodesX; x++) {
		for (int y = 0; y < numNodesY; y++)	{
			if (x > 0) { // Connect to the node to it's left
				int nodeA = nodeIds[x][y];
				int nodeB = nodeIds[x-1][y];
				if (nodeA != -1 && nodeB != -1) {
					m_roadMap->AddEdge(nodeA, nodeB);
				}
			}
			if (y > 0) { // Connect to the node above
				int nodeA = nodeIds[x][y];
				int nodeB = nodeIds[x][y-1];
				if (nodeA != -1 && nodeB != -1) {
					m_roadMap->AddEdge(nodeA, nodeB);
				}
			}
		}
	}
}

void tfLandscape::Export(const char* xmlFile) {
	m_roadMap->Export(xmlFile);
}
