#ifndef _BF2ANIM_H_
#define _BF2ANIM_H_

#include <stdio.h>
#include <stdlib.h>
#include <string>

struct bf2anim
{
	uint32_t version;      //32bit unsigned int (4 bytes)
	uint16_t bonenum;      //16bit unsigned int (2 bytes)
	uint16_t boneId;       //16bit unsigned int (2 bytes  * bonenum)
	uint32_t framenum;     //32bit unsigned int (4 bytes)
    uint8_t precision;     //8bit unsigned int (1 byte)
	boneData *baf_bonedata;
}


