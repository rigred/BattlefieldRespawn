
//#include <process.h>
//#include <vld.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "loader/bf2mesh.h"


// case-insensitive string compare
bool StrMatch(const char *a, const char *b)
{
    assert(a != NULL);
    assert(b != NULL);
    const size_t lena = strlen(a);
    const size_t lenb = strlen(b);
    if (lena != lenb) return false;
    for (size_t i=0; i<lena; i++)
    {
        if (tolower(a[i]) != tolower(b[i])) return false;
    }
    return true;
}



// main
int main(int argnum, char *arg[])
{
    printf("---------------------------------------------\n");
    printf("BF2 Mesh Exporter v0.1.1\n");
    printf("By Rigo \"Pixel\" Reddig\n");
    printf("For Project Reality Mod (www.realitymod.com)\n");
    printf("---------------------------------------------\n");

    if (argnum != 2)
    {
        printf("Error: Invalid argument.\n");
        printf("Usage: meshman <filename>\n");
        return 2;
    }

    const char *fname = arg[1];

    printf("Input: %s\n", fname);

// determine file extension
    const char *ext = strrchr(fname,'.');
    if (ext == NULL)
    {
        printf("Input file name extension missing.\n");
        return 3;
    }
    ext++;
    mesh.isBundledMesh = StrMatch(ext,"BundledMesh");
    mesh.isSkinnedMesh = StrMatch(ext,"SkinnedMesh");
    if (mesh.isBundledMesh)
    {
        printf("Using BundledMesh profile...\n");
    }
    else if (mesh.isSkinnedMesh)
    {
        printf("Using SkinnedMesh profile...\n");
    }
    else
    {
        printf("Using StaticMesh profile...\n");
    }
    printf("\n");

// load mesh
    const int ret = mesh.Load( fname );
    if (ret != 0)
    {
        printf("Error occurred while parsing file.\n");
        return ret;
    }

// success
    printf("---------------------------------------------\n");
    return 0;
}

