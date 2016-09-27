
#ifndef _BF2MESH_H_
#define _BF2MESH_H_

#include <stdio.h>
#include <stdlib.h>
#include <string>


// three dimensional floating point vector
struct float3 // 12 bytes
{
    float x;
    float y;
    float z;
};


// bounding box
struct aabb // 24 bytes
{
    float3 min;
    float3 max;
};


// 4x4 transformation matrix
struct matrix4 // 64 bytes
{
    float m[4][4];
};


// bf2 mesh file header
struct bf2head             // 20 bytes
{
    unsigned int u1;          // 0
    unsigned int version;     // 10 for most bundledmesh, 6 for some bundledmesh, 11 for staticmesh
    unsigned int u3;          // 0
    unsigned int u4;          // 0
    unsigned int u5;          // 0
};


// vertex attribute table entry
struct bf2attrib           // 8 bytes
{
    unsigned short flag;      // some sort of boolean flag (if true the below field are to be ignored?)
    unsigned short offset;    // offset from vertex data start
    unsigned short vartype;   // attribute type (vec2, vec3 etc)
    unsigned short usage;     // usage ID (vertex, texcoord etc)

// Note: "usage" field correspond to the definition in DX SDK "Include\d3d9types.h"
//       Looks like DICE extended these for additional UV channels, these constants
//       are much larger to avoid conflict with core DX enums.
};


// bone structure
struct bf2bone       // 68 bytes
{
    unsigned int id;    //  4 bytes
    matrix4 transform;  // 64 bytes
};


// rig structure
struct bf2rig
{
    int bonenum;
    bf2bone *bone;

// constructor/destrutor
    bf2rig()
    {
        bone = NULL;
    };
    ~bf2rig()
    {
        if (bone) delete [] bone;
    };

// functions
    bool Read(FILE *fp, int version);
};


// material (aka drawcall)
struct bf2mat
{
    unsigned int alphamode;             // 0=opaque, 1=blend, 2=alphatest
    std::string fxfile;                 // shader filename string
    std::string technique;              // technique name

// texture map filenames
    int mapnum;                         // number of texture map filenames
    std::string *map;                   // map filename array

// geometry info
    unsigned int vstart;                // vertex start offset
    unsigned int istart;                // index start offset
    unsigned int inum;                  // number of indices
    unsigned int vnum;                  // number of vertices

// misc
    unsigned int u4;                    // always 1?
    unsigned short u5;                  // always 0x34E9?
    unsigned short u6;                  // most often 18/19
    aabb bounds;                        // per-material bounding box (StaticMesh only)

// constructor/destructor
    bf2mat()
    {
        map = NULL;
    };
    ~bf2mat()
    {
        if (map) delete [] map;
    };

// functions
    bool Read(FILE *fp, int version);
};


// lod, holds mainly a collection of materials
struct bf2lod
{
// bounding box
    float3 min;
    float3 max;
    float3 pivot; // not sure this is really a pivot (only on version<=6)

// skinning matrices (SkinnedMesh only)
    int rignum;              // this usually corresponds to meshnum (but what was meshnum again??)
    bf2rig *rig;             // array of rigs

// nodes (staticmesh and bundledmesh only)
    int nodenum;
    matrix4 *node;

// material/drawcalls
    int matnum;              // number of materials
    bf2mat *mat;             // material array

// constructor/destructor
    bf2lod()
    {
        rig = NULL;
        node = NULL;
        mat = NULL;
    };
    ~bf2lod()
    {
        if (rig) delete [] rig;
        if (node) delete [] node;
        if (mat) delete [] mat;
    };

// functions
    bool ReadNodeData(FILE *fp, int version);
    bool ReadMatData(FILE *fp, int version);
};


// geom, holds a collection of LODs
struct bf2geom
{
    int lodnum;              // number of LODs
    bf2lod *lod;             // array of LODs

// constructor/destructor
    bf2geom()
    {
        lod = NULL;
    };
    ~bf2geom()
    {
        if (lod) delete [] lod;
    }

// functions
    bool Read(FILE *fp, int version);
};


// BF2 mesh file structure
struct bf2mesh
{
// header
    bf2head head;

// unknown
    unsigned char u1; // always 0?

// geoms
    int geomnum;                      // numer of geoms
    bf2geom *geom;                    // geom array

// vertex attribute table
    int vertattribnum;                // number of vertex attribute table entries
    bf2attrib *vertattrib;            // array of vertex attribute table entries

// vertices
    int vertformat;                   // always 4?  (e.g. GL_FLOAT)
    int vertstride;                   // vertex stride
    int vertnum;                      // number of vertices in buffer
    float *vert;                      // vertex array

// indices
    int indexnum;                     // number of indices
    unsigned short *index;            // index array

// unknown
    int u2;                           // always 8?

// constructor/destructor
    bf2mesh()
    {
        geom = NULL;
        vertattrib = NULL;
        vert = NULL;
        index = NULL;
    };
    ~bf2mesh()
    {
        if (geom) delete [] geom;
        if (vertattrib) delete [] vertattrib;
        if (vert) delete [] vert;
        if (index) delete [] index;
    };

// functions
    int Load(const char *filename);

// internal/hacks
    bool isSkinnedMesh;
    bool isBundledMesh;
    bool isBFP4F;
};


extern bf2mesh mesh;


// helper functions
std::string BF2ReadString(FILE *fp);


#endif

