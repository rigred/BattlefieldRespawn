## BF2 Animation File Format Structure ##
.baf

```cpp
struct baf_file {

	int64_t version; 		// signed int64 (8 bytes)
	int bonenum; 			//32bit signed int (4 bytes)
	int boneId; 			//32bit signed int (4 bytes)
	int framenum; 			//32bit signed int (4 bytes)
	unsigned char precision;//(Byte) unsigned 8bit Char (1 byte)
	boneData *baf_bonedata;
}

struct baf_bonedata {
	int dataSize;
	frame *baf_frame;
}

struct baf_frame {
	quaternion rot;
	float3 pos;
}


```

## BF2 Skeleton File Format Structure ##
.ske

```cpp
struct bf2ske_file {
	int64_t version;
	
	int64_t nodenum;
	skenode* node;
	
	//internal and functions
	int cambone;
	std::string filename;
	bool loaded;
}

struct skenode {
	std::string name;
	int parent;
	quaternion rot;
	float3 pos;

	//internal and functions
	matrix4 localmat;
	matrix4 localmatanim;
	matrix4 worldmat;
	matrix4 worldmatbackup;
}

```

## BF2 Occluder File Format Structure ##

```cpp
struct occ_file {
	int64_t groupnum;
	occ_group *group;
	
	//internal and functions
	std::string filename;
	bool loadok;
}

struct occ_group {
	int64_t planenum;
	occ_plane *plane;
	int64_t vertnum;
	float3 *vert;
}

struct occ_plane {
	int64_t v1;
	int64_t v2;
	int64_t v3;
	int64_t v4;
}

```

## BF2 Collision Mesh File Format Structure ##

```cpp
struct bf2col_file{

	//header
	int64_t u1;			//0 Unknown
	int64_t version;	//8 file format version

	//geometry
	int64_t geomnum;	//number of geometries in array
	bf2colgeom *geom;	//array of geometries

	//internal and functions
	int64_t maxId;
	bool loadOk;
	bool drawOk;
	std::string filename;
}

struct bf2colgeom {
	int64_t subgnum;
	bf2colsub *subg;
}

struct bf2colsub {
	int64_t lodnum;
	bf2collod *lod;
}

struct bf2collod {
	//type of collider
	int64_t coltype; 	//0=projectile, 1=vehicle, 2=solder, 3=AI
	
	//face data
	int64_t facenum;
	colface *face;

	//vertex data
	int64_t vertnum;
	float3 *vert;

	//unknown - perhaps spacer
	int *vertid;

	//vertex bounds
	float3 min;
	float3 max;

	//unknown
	unsigned char u7;

	//tree bounds
	float3 bmin;
	float3 bmax;

	//unknown
	int64_t ynum;
	ystruct *ydata;

	//unknown
	int64_t znum;
	int *zdata;

	//uknown
	int64_t anum;
	int64_t adata;

	//internal and functions
	float3 *norm;
	int64_t badtri;
}

struct ystruct {
	float u1; //Single precision float, matches a vertex X, Y, or Z coordinate
	int u2;
	int u3;
	int64_t u4;
	int64_t u5;
}

struct colface {
	int v1;		//the three vertices that make up a collision triangle
	int v2;
	int v3;
	int m;
}

```
