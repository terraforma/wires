#include <cstdio>

#include <libterra/Bitmap.h>

#include <Landscape.h>

using namespace LibTerra;

void usage();

//
//	Entry point.
int main(int _argc, char *_argv[])
{
	if (_argc < 5) {
		usage();
		return 1;
	}
	// Load our bitmaps
	tfBitmap* heightMap = new tfBitmap(_argv[1]);
	tfBitmap* waterMap = new tfBitmap(_argv[2]);
	tfBitmap* densityMap = new tfBitmap(_argv[3]);
	tfLandscape landscape(heightMap, waterMap, densityMap);
	landscape.GenerateGrid();
	landscape.Export(_argv[4]);
	return 0;
}

void usage() {
	printf("usage: wires <heightmap.bmp> <watermap.bmp> <density.bmp> <output.xml>\n");
}
