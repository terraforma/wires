#ifndef _INCLUDE_LANDSCAPE_H_
#define _INCLUDE_LANDSCAPE_H_

#include <libterra/Roadmap.h>
#include <libterra/Bitmap.h>

using namespace LibTerra;

class tfLandscape {
public:
	tfLandscape(tfBitmap* height, tfBitmap* water, tfBitmap* density);
	virtual ~tfLandscape();

	float HeightAt(float x, float y);
	float WaterAt(float x, float y);
	// Generates a static grid.
	void GenerateGrid();

	void Export(const char* xmlFile);
private:
	tfRoadmap* m_roadMap;
	tfBitmap* m_heightMap;
	tfBitmap* m_waterMap;
	tfBitmap* m_densityMap;
	float m_width;
	float m_height;
};

#endif /* _INCLUDE_LANDSCAPE_H_ */
