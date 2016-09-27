#define _CRT_SECURE_NO_DEPRECATE
#include <assert.h>
#include "bf2mesh.h"


bf2mesh mesh;
size_t result;


// loads mesh from file
int bf2mesh::Load(const char *filename)
{
    assert(filename != NULL);

// open file
    FILE *fp = fopen(filename,"rb");
    if (!fp)
    {
        printf("File \"%s\" not found.\n",filename);
        return 1;
    }

//! header
// Check for != 1 since fread returns number of sizeof(bf2head) bytes read which are
// specified by argument '1' after the 'sizeof(bf2head)' argument.
    if (fread(&head,sizeof(bf2head),1,fp) != 1)
    {
        fputs ("Malformed file header!\n...\n",stderr);
        exit (3);
    }
    else
    {
        printf("head start at %ld\n", ftell(fp) );
        printf(" u1: %i\n",       head.u1 );
        printf(" version: %i\n",  head.version );
        printf(" u3: %i\n",       head.u5 );
        printf(" u4: %i\n",       head.u5 );
        printf(" u5: %i\n",       head.u5 );
        printf("head end at %ld\n", ftell(fp) );
        printf("\n");
    }
// unknown (1 byte)
// stupid little byte that misaligns the entire file!

    if (fread(&u1,1,1,fp) != 1)
    {
        fputs ("Missing alignment byte!\n File is misaligned\n",stderr);
        exit (3);
    }
    else
    {

        printf("u1: %i\n", u1);
        printf("game version: ");
// for BFP4F, the value is "1", so perhaps this is a version number as well
        if (u1 == 1)
        {
            isBFP4F = true;
            printf("Battlefield Play4Free\n\n");
        }
        else
        {
            printf("Battlefield 2\n\n");
        }

// --- geom table ---------------------------------------------------------------------------
        printf("geom table start at %ld\n", ftell(fp) );
    }
// geomnum (4 bytes)
    if (fread(&geomnum,4,1,fp) != 1)
    {
        fputs ("Could not read geometry number!\n",stderr);
        exit (3);
    }
    else
    {
        printf(" geomnum: %i\n", geomnum);
// geom table (4 bytes * groupnum)
        geom = new bf2geom[ geomnum ];
        for (int i=0; i<geomnum; i++)
        {
            geom[i].Read(fp, head.version);
        }

        printf("geom table end at %ld\n", ftell(fp) );
        printf("\n");

    }

// --- vertex attribute table -------------------------------------------------------------------------------

    printf("attrib block at %ld\n", ftell(fp) );

// vertattribnum (4 bytes)
    fread(&vertattribnum,sizeof(vertattribnum),1,fp);
    printf(" vertattribnum: %i\n", vertattribnum);

// vertex attributes
    vertattrib = new bf2attrib[ vertattribnum ];
    fread(vertattrib,sizeof(bf2attrib)*vertattribnum,1,fp);
    for (int i=0; i<vertattribnum; i++)
    {
        printf(" attrib[%i]: %i %i %i %i\n", i, vertattrib[i].flag,
               vertattrib[i].offset,
               vertattrib[i].vartype,
               vertattrib[i].usage);
    }

    printf("attrib block end at %ld\n", ftell(fp) );
    printf("\n");

// --- vertices -----------------------------------------------------------------------------

    printf("vertex block start at %ld\n", ftell(fp) );

    fread(&vertformat,4,1,fp);
    fread(&vertstride,4,1,fp);
    fread(&vertnum,4,1,fp);
    printf(" vertformat: %i\n", vertformat);
    printf(" vertstride: %i\n", vertstride);
    printf(" vertnum: %i\n", vertnum);

    vert = new float[ vertnum * (vertstride / vertformat) ];
    fread(vert,vertnum*vertstride,1,fp);

    printf("vertex block end at %ld\n", ftell(fp) );
    printf("\n");

// --- indices ------------------------------------------------------------------------------

    printf("index block start at %ld\n", ftell(fp) );

    fread(&indexnum,4,1,fp);
    printf(" indexnum: %i\n", indexnum);
    index = new unsigned short[ indexnum ];
    fread(index,2*indexnum,1,fp);

    printf("index block end at %ld\n", ftell(fp) );
    printf("\n");

// --- rigs -------------------------------------------------------------------------------

// unknown (4 bytes)
    if (!mesh.isSkinnedMesh)
    {
        fread(&u2,4,1,fp); // always 8?
        printf("u2: %i\n", u2);
        printf("\n");
    }

// rigs/nodes
    printf("nodes chunk start at %ld\n", ftell(fp) );
    for (int i=0; i<geomnum; i++)
    {
        if (i > 0) printf("\n");
        printf(" geom %i start\n", i);
        for (int j=0; j<geom[i].lodnum; j++)
        {
            printf("  lod %i start\n", j);
            geom[i].lod[j].ReadNodeData( fp, head.version );
            printf("  lod %i end\n", j);
        }
        printf(" geom %i end\n", i);
    }
    printf("nodes chunk end at %ld\n", ftell(fp) );
    printf("\n");

// --- geoms ------------------------------------------------------------------------------

    for (int i=0; i<geomnum; i++)
    {
        printf("geom %i start at %ld\n", i, ftell(fp) );
        //geom[i].ReadMatData( fp, head.version );

        for (int j=0; j<geom[i].lodnum; j++)
        {
            printf(" lod %i start\n", j);
            geom[i].lod[j].ReadMatData(fp,head.version);
            printf(" lod %i end\n", j);
        }

        printf("geom %i block end at %ld\n", i, ftell(fp) );
        printf("\n");
    }

// --- end of file -------------------------------------------------------------------------

    printf("done reading %ld\n", ftell(fp) );
    fseek(fp, 0, SEEK_END);
    printf("file size is %ld\n", ftell(fp) );
    printf("\n");

// close file
    fclose(fp);
    fp = NULL;

// success!
    return 0;
}


// reads rig
bool bf2rig::Read(FILE *fp, int version)
{

// bonenum (4 bytes)
    fread(&bonenum,4,1,fp);
    printf("   bonenum: %i\n", bonenum);
    assert(bonenum >= 0);
    assert(bonenum < 99);

// bones (68 bytes * bonenum)
    if (bonenum > 0)
    {
        bone = new bf2bone[ bonenum ];
        fread(bone,sizeof(bf2bone)*bonenum,1,fp);

        for (int i=0; i<bonenum; i++)
        {
            printf("   boneid[%i]: %i\n", i, bone[i].id);
        }
    }

// success
    return true;
}


// reads lod node table
bool bf2lod::ReadNodeData(FILE *fp, int version)
{

// bounds (24 bytes)
    fread(&min,12,1,fp);
    fread(&max,12,1,fp);

// unknown (12 bytes)
    if (version <= 6)   // version 4 and 6
    {
        fread(&pivot,12,1,fp);
    }

// skinnedmesh has different rigs
    if (mesh.isSkinnedMesh)
    {

        // rignum (4 bytes)
        fread(&rignum,4,1,fp);
        printf("  rignum: %i\n", rignum);

        // read rigs
        if (rignum > 0)
        {
            rig = new bf2rig[ rignum ];
            for (int i=0; i<rignum; i++)
            {
                printf("  rig block %i start at %ld\n", i, ftell(fp) );

                rig[i].Read(fp, version);

                printf("  rig block %i end at %ld\n", i, ftell(fp) );
            }
        }

    }
    else
    {

        // nodenum (4 bytes)
        fread(&nodenum,4,1,fp);
        printf("   nodenum: %i\n", nodenum);

        // node matrices (64 bytes * nodenum)
        if (!mesh.isBundledMesh)
        {
            printf("   node data\n");
            if (nodenum > 0)
            {
                node = new matrix4[ nodenum ];
                fread(node,sizeof(matrix4)*nodenum,1,fp);
            }
        }

    }

// success
    return true;
}


// reads lod material chunk
bool bf2mat::Read(FILE *fp, int version)
{

// alpha flag (4 bytes)
    if (!mesh.isSkinnedMesh)
    {
        fread(&alphamode,4,1,fp);
        printf("   alphamode: %i\n", alphamode);
    }

// fx filename
    fxfile = BF2ReadString(fp);
    printf("   fxfile: %s\n", fxfile.c_str() );

// material name
    technique = BF2ReadString(fp);
    printf("   matname: %s\n", technique.c_str() );

// mapnum (4 bytes)
    fread(&mapnum,4,1,fp);
    printf("   mapnum: %i\n", mapnum);
    assert(mapnum >= 0);
    assert(mapnum < 99);

// mapnames
    if (mapnum > 0)
    {
        map = new std::string[ mapnum ];
        for (int i=0; i<mapnum; i++)
        {
            map[i] = BF2ReadString(fp);
            printf("    map %i: %s\n", i, map[i].c_str() );
        }
    }

// geometry info
    fread(&vstart,4,1,fp);
    fread(&istart,4,1,fp);
    fread(&inum,4,1,fp);
    fread(&vnum,4,1,fp);
    printf("   vstart: %i\n", vstart);
    printf("   istart: %i\n", istart);
    printf("   inum: %i\n", inum);
    printf("   vnum: %i\n", vnum);

// unknown
    fread(&u4,4,1,fp);
    fread(&u5,2,1,fp);
    fread(&u6,2,1,fp);

// bounds
    if (!mesh.isSkinnedMesh)
    {
        if (version == 11)
        {
            fread(&bounds,sizeof(aabb),1,fp);
        }
    }

// success
    return true;
}


// reads geom lod chunk
bool bf2lod::ReadMatData(FILE *fp, int version)
{
// matnum (4 bytes)
    fread(&matnum,4,1,fp);
    printf("  matnum: %i\n", matnum);

    assert(matnum >= 0);
    assert(matnum < 99);

// materials (? bytes)
    if (matnum > 0)
    {
        mat = new bf2mat[ matnum ];
        for (int i=0; i<matnum; i++)
        {
            printf("  mat %i start at %ld\n", i, ftell(fp) );
            if (!mat[i].Read( fp, version )) return false;
            printf("  mat %i end at %ld\n", i, ftell(fp) );
        }
    }

// success
    return true;
}


// reads geom from file
bool bf2geom::Read(FILE *fp, int version)
{
// lodnum (4 bytes)
    fread(&lodnum,4,1,fp);
    printf("  lodnum: %i\n", lodnum);

    assert(lodnum >= 0);
    assert(lodnum < 99);

// allocate lods
    if (lodnum > 0)
    {
        lod = new bf2lod[ lodnum ];
    }

// success
    return true;
}


// reads string from file
std::string BF2ReadString(FILE *fp)
{
    unsigned int num;
    fread(&num,4,1,fp);

    assert(num >= 0);
    assert(num < 999);

    if (num == 0) return "";

    char *str = new char[num];
    fread(str,num,1,fp);

    std::string tmp(str,num);

    delete [] str;

    return tmp;
}

