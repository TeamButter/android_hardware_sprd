/******************************************************************************
 ** File Name:      JpegEnc_table.c                                                 *
 ** Author:         Yi.Wang                                                *
 ** Date:           2007/12/13                                                *
 ** Copyright:      2007 Spreadtrum, Incoporated. All Rights Reserved.        *
 ** Description:    define the tables used in the JPEG codec                  *
 ******************************************************************************

 ******************************************************************************
 **                        Edit History                                       *
 ** ------------------------------------------------------------------------- *
 ** DATE           NAME             DESCRIPTION                               *
 ** 2007/12/13     Yi.Wang          Create.                                   *
 ******************************************************************************/
#include "jpegcodec_def.h"
/************************************************************************/
/* Quant table                                                          */
/************************************************************************/

uint8 jpeg_fw_lum_quant_tbl_default[5][64] = 
{
    {
        10,   7,   6,  10,  14,  24,  31,  37,      //q70
        7,   7,   8,  11,  16,  35,  36,  33, 
        8,   8,  10,  14,  24,  34,  41,  34,
        8,  10,  13,  17,  31,  52,  48,  37, 
        11,  13,  22,  34,  41,  65,  62,  46,
        14,  21,  33,  38,  49,  62,  68,  55, 
        29,  38,  47,  52,  62,  73,  72,  61,
        43,  55,  57,  59,  67,  60,  62,  59, 
    },

    {
        6,   4,   4,   6,  10,  16,  20,  24,     //q80
        5,   5,   6,   8,  10,  23,  24,  22,        
        6,   5,   6,  10,  16,  23,  28,  22,
        6,   7,   9,  12,  20,  35,  32,  25,
        7,   9,  15,  22,  27,  44,  41,  31,
        10,  14,  22,  26,  32,  42,  45,  37,
        20,  26,  31,  35,  41,  48,  48,  40,
        29,  37,  38,  39,  45,  40,  41,  40,          
    },

    { 
        5,   3,   3,   5,   7,  12,  15,  18,      //q85
        4,   4,   4,   6,   8,  17,  18,  17,     
        4,   4,   5,   7,  12,  17,  18,  17,
        4,   5,   7,   9,  15,  26,  24,  19,
        5,   7,  11,  17,  20,  33,  31,  23,
        7,  11,  17,  19,  24,  31,  34,  28,
        15,  19,  23,  26,  31,  36,  36,  30,
        22,  28,  29,  29,  34,  30,  31,  30,
    },

    {
        0x3,    0x2,    0x2,    0x3,    0x5,    0x8,    0xa,    0xc,   //q90
        0x2,    0x2,    0x3,    0x4,    0x5,    0xc,    0xc,    0xb,
        0x3,    0x3,    0x3,    0x5,    0x8,    0xb,    0xe,    0xb, 
        0x3,    0x3,    0x4,    0x6,    0xa,   0x11,   0x10,    0xc, 
        0x4,    0x4,    0x7,    0xb,    0xe,   0x16,   0x15,    0xf, 
        0x5,    0x7,    0xb,    0xd,   0x10,   0x15,   0x17,   0x12, 
        0xa,    0xd,   0x10,   0x11,   0x15,   0x18,   0x18,   0x14, 
        0xe,   0x12,   0x13,   0x14,   0x16,   0x14,   0x15,   0x14,                      
    },

    { 
#if 0
        0x2,    0x1,    0x1,    0x2,    0x2,    0x4,    0x5,    0x6,   //q95
        0x1,    0x1,    0x1,    0x2,    0x3,    0x6,    0x6,    0x6, 
        0x1,    0x1,    0x2,    0x2,    0x4,    0x6,    0x7,    0x6, 
        0x1,    0x2,    0x2,    0x3,    0x5,    0x9,    0x8,    0x6, 
        0x2,    0x2,    0x4,    0x6,    0x7,    0xb,    0xa,    0x8, 
        0x2,    0x4,    0x6,    0x6,    0x8,    0xa,    0xb,    0x9, 
        0x5,    0x6,    0x8,    0x9,    0xa,    0xc,    0xc,    0xa, 
        0x7,    0x9,    0xa,    0xa,    0xb,    0xa,    0xa,    0xa
#else
		0x01, 0x01, 0x02, 0x03, 0x03, 0x03, 0x02, 0x03,
		0x01, 0x01, 0x03, 0x03, 0x01, 0x01, 0x05, 0x03,
		0x01, 0x01, 0x01, 0x01, 0x01, 0x04, 0x02, 0x04,
		0x01, 0x01, 0x01, 0x01, 0x03, 0x01, 0x04, 0x07,
		0x01, 0x01, 0x03, 0x01, 0x04, 0x06, 0x06, 0x07,
		0x02, 0x04, 0x01, 0x06, 0x06, 0x05, 0x06, 0x06,
		0x03, 0x02, 0x06, 0x05, 0x04, 0x04, 0x05, 0x05,
		0x03, 0x04, 0x03, 0x04, 0x05, 0x05, 0x06, 0x05
#endif

    }

};
uint8 jpeg_fw_chr_quant_tbl_default[5][64] = 
{
    {
        10,   7,   6,  10,  14,  24,  31,  37,      //q70
        7,   7,   8,  11,  16,  35,  36,  33, 
        8,   8,  10,  14,  24,  34,  41,  34,
        8,  10,  13,  17,  31,  52,  48,  37, 
        11,  13,  22,  34,  41,  65,  62,  46,
        14,  21,  33,  38,  49,  62,  68,  55, 
        29,  38,  47,  52,  62,  73,  72,  61,
        43,  55,  57,  59,  67,  60,  62,  59, 
    },

    {
        6,   4,   4,   6,  10,  16,  20,  24,     //q80
        5,   5,   6,   8,  10,  23,  24,  22,        
        6,   5,   6,  10,  16,  23,  28,  22,
        6,   7,   9,  12,  20,  35,  32,  25,
        7,   9,  15,  22,  27,  44,  41,  31,
        10,  14,  22,  26,  32,  42,  45,  37,
        20,  26,  31,  35,  41,  48,  48,  40,
        29,  37,  38,  39,  45,  40,  41,  40,          
    },

    { 
        5,   3,   3,   5,   7,  12,  15,  18,      //q85
        4,   4,   4,   6,   8,  17,  18,  17,     
        4,   4,   5,   7,  12,  17,  18,  17,
        4,   5,   7,   9,  15,  26,  24,  19,
        5,   7,  11,  17,  20,  33,  31,  23,
        7,  11,  17,  19,  24,  31,  34,  28,
        15,  19,  23,  26,  31,  36,  36,  30,
        22,  28,  29,  29,  34,  30,  31,  30,
    },

    {
        0x3,    0x2,    0x2,    0x3,    0x5,    0x8,    0xa,    0xc,   //q90
        0x2,    0x2,    0x3,    0x4,    0x5,    0xc,    0xc,    0xb,
        0x3,    0x3,    0x3,    0x5,    0x8,    0xb,    0xe,    0xb, 
        0x3,    0x3,    0x4,    0x6,    0xa,   0x11,   0x10,    0xc, 
        0x4,    0x4,    0x7,    0xb,    0xe,   0x16,   0x15,    0xf, 
        0x5,    0x7,    0xb,    0xd,   0x10,   0x15,   0x17,   0x12, 
        0xa,    0xd,   0x10,   0x11,   0x15,   0x18,   0x18,   0x14, 
        0xe,   0x12,   0x13,   0x14,   0x16,   0x14,   0x15,   0x14,                      
    },

    { 
#if 0
        0x2,    0x1,    0x1,    0x2,    0x2,    0x4,    0x5,    0x6,   //q95
        0x1,    0x1,    0x1,    0x2,    0x3,    0x6,    0x6,    0x6, 
        0x1,    0x1,    0x2,    0x2,    0x4,    0x6,    0x7,    0x6, 
        0x1,    0x2,    0x2,    0x3,    0x5,    0x9,    0x8,    0x6, 
        0x2,    0x2,    0x4,    0x6,    0x7,    0xb,    0xa,    0x8, 
        0x2,    0x4,    0x6,    0x6,    0x8,    0xa,    0xb,    0x9, 
        0x5,    0x6,    0x8,    0x9,    0xa,    0xc,    0xc,    0xa, 
        0x7,    0x9,    0xa,    0xa,    0xb,    0xa,    0xa,    0xa
#else
		0x01, 0x01, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05,
		0x01, 0x05, 0x05, 0x05, 0x01, 0x05, 0x05, 0x05,
		0x03, 0x01, 0x05, 0x01, 0x04, 0x05, 0x05, 0x05,
		0x01, 0x04, 0x03, 0x03, 0x05, 0x05, 0x05, 0x05,
		0x01, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05,
		0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05,
		0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05,
		0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05
#endif

    }
};


/************************************************************************/
/* Huffman Table                                                        */
/************************************************************************/
/*default vaule for luminance component*/
uint8 jpeg_fw_lum_dc_bits_default[MAX_BITS_SIZE+1] = 
{
	0, 0, 1, 5, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0 
};

uint8 jpeg_fw_lum_dc_huffvalue_default[DC_SYMBOL_NUM] = 
{
	0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 
};

uint8 jpeg_fw_lum_ac_bits_default[MAX_BITS_SIZE+1] = 
{
	0, 0, 2, 1, 3, 3, 2, 4, 3, 5, 5, 4, 4, 0, 0, 1, 0x7d 
};

uint8 jpeg_fw_lum_ac_huffvalue_default[AC_SYMBOL_NUM] = 
{
	0x01, 0x02, 0x03, 0x00, 0x04, 0x11, 0x05, 0x12,
	0x21, 0x31, 0x41, 0x06, 0x13, 0x51, 0x61, 0x07,
	0x22, 0x71, 0x14, 0x32, 0x81, 0x91, 0xa1, 0x08,
	0x23, 0x42, 0xb1, 0xc1, 0x15, 0x52, 0xd1, 0xf0,
	0x24, 0x33, 0x62, 0x72, 0x82, 0x09, 0x0a, 0x16,
	0x17, 0x18, 0x19, 0x1a, 0x25, 0x26, 0x27, 0x28,
	0x29, 0x2a, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39,
	0x3a, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49,
	0x4a, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59,
	0x5a, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69,
	0x6a, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79,
	0x7a, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89,
	0x8a, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97, 0x98,
	0x99, 0x9a, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7,
	0xa8, 0xa9, 0xaa, 0xb2, 0xb3, 0xb4, 0xb5, 0xb6,
	0xb7, 0xb8, 0xb9, 0xba, 0xc2, 0xc3, 0xc4, 0xc5,
	0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xd2, 0xd3, 0xd4,
	0xd5, 0xd6, 0xd7, 0xd8, 0xd9, 0xda, 0xe1, 0xe2,
	0xe3, 0xe4, 0xe5, 0xe6, 0xe7, 0xe8, 0xe9, 0xea,
	0xf1, 0xf2, 0xf3, 0xf4, 0xf5, 0xf6, 0xf7, 0xf8,
	0xf9, 0xfa, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0

};

/*default vaule for chroma component*/
uint8 jpeg_fw_chr_dc_bits_default[MAX_BITS_SIZE+1] = 
{
	0, 0, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0
};
uint8 jpeg_fw_chr_dc_huffvalue_default[DC_SYMBOL_NUM] = 
{
 	0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11
};

uint8 jpeg_fw_chr_ac_bits_default[MAX_BITS_SIZE+1] = 
{
	0, 0, 2, 1, 2, 4, 4, 3, 4, 7, 5, 4, 4, 0, 1, 2, 0x77
};
uint8 jpeg_fw_chr_ac_huffvalue_default[AC_SYMBOL_NUM] = 
{
	0x00, 0x01, 0x02, 0x03, 0x11, 0x04, 0x05, 0x21,
	0x31, 0x06, 0x12, 0x41, 0x51, 0x07, 0x61, 0x71,
	0x13, 0x22, 0x32, 0x81, 0x08, 0x14, 0x42, 0x91,
	0xa1, 0xb1, 0xc1, 0x09, 0x23, 0x33, 0x52, 0xf0,
	0x15, 0x62, 0x72, 0xd1, 0x0a, 0x16, 0x24, 0x34,
	0xe1, 0x25, 0xf1, 0x17, 0x18, 0x19, 0x1a, 0x26,
	0x27, 0x28, 0x29, 0x2a, 0x35, 0x36, 0x37, 0x38,
	0x39, 0x3a, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48,
	0x49, 0x4a, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58,
	0x59, 0x5a, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68,
	0x69, 0x6a, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78,
	0x79, 0x7a, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87,
	0x88, 0x89, 0x8a, 0x92, 0x93, 0x94, 0x95, 0x96,
	0x97, 0x98, 0x99, 0x9a, 0xa2, 0xa3, 0xa4, 0xa5,
	0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xb2, 0xb3, 0xb4,
	0xb5, 0xb6, 0xb7, 0xb8, 0xb9, 0xba, 0xc2, 0xc3,
	0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xd2,
	0xd3, 0xd4, 0xd5, 0xd6, 0xd7, 0xd8, 0xd9, 0xda,
	0xe2, 0xe3, 0xe4, 0xe5, 0xe6, 0xe7, 0xe8, 0xe9,
	0xea, 0xf2, 0xf3, 0xf4, 0xf5, 0xf6, 0xf7, 0xf8,
	0xf9, 0xfa, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0	

};

/*huffman table*/
/*
uint8 ac_bits[NUM_HUFF_TBLS][17];
uint8 ac_huffvalue[NUM_HUFF_TBLS][256];
uint8 dc_bits[NUM_HUFF_TBLS][17];
uint8 dc_huffvalue[NUM_HUFF_TBLS][256];
*/

/************************************************************************/
/* ZigZag table                                                         */
/************************************************************************/

const uint8 jpeg_fw_zigzag_order[64+16] = 
{
	  0,  1,  8, 16,  9,  2,  3, 10,
	 17, 24, 32, 25, 18, 11,  4,  5,
	 12, 19, 26, 33, 40, 48, 41, 34,
	 27, 20, 13,  6,  7, 14, 21, 28,
	 35, 42, 49, 56, 57, 50, 43, 36,
	 29, 22, 15, 23, 30, 37, 44, 51,
	 58, 59, 52, 45, 38, 31, 39, 46,
	 53, 60, 61, 54, 47, 55, 62, 63,
	 63, 63, 63, 63, 63, 63, 63, 63,
	 63, 63, 63, 63, 63, 63, 63, 63
};

//
const uint32 jpeg_fw_hufftab_dcLuma [12] = 
{
	(0x0<<16) | 2, (0x2<<16) | 3, (0x3<<16) | 3, (0x4<<16) | 3,
		(0x5<<16) | 3, (0x6<<16) | 3, (0xe<<16) | 4, (0x1e<<16) | 5,
		(0x3e<<16) | 6, (0x7e<<16) | 7, (0xfe<<16) | 8, (0x1fe<<16) | 9,
};

const uint32 jpeg_fw_hufftab_dcChroam [12] = 
{
	(0x0<<16) | 2, (0x1<<16) | 2, (0x2<<16) | 2, (0x6<<16) | 3,
		(0xe<<16) | 4, (0x1e<<16) | 5, (0x3e<<16) | 6, (0x7e<<16) | 7,
		(0xfe<<16) | 8, (0x1fe<<16) | 9, (0x3fe<<16) | 10, (0x7fe<<16) | 11,
};

uint16 jpeg_fw_new_lum_quant_tbl_default[5][64] = 
{
    // 70
	{
		3277,	2341,	2731,	3277,	2341,	2731,	2114,	3542,
		2341,	2341,	2048,	2979,	2048,	3745,	3641,	3972,
		2048,	2048,	3277,	2341,	2731,	3855,	3197,	3855,
		2048,	3277,	2521,	3855,	2114,	2521,	2731,	3542,
		2979,	2521,	2979,	3855,	3197,	4033,	2114,	2849,
		2341,	3121,	3972,	3449,	2675,	2114,	3855,	2383,
		2260,	3449,	2789,	2521,	2114,	3591,	3641,	2149,
		3048,	2383,	2300,	2222,	3913,	2185,	2114,	2222,
	},
	
	// 80 aa
	{
		2731,	2048,	2048,	2731,	3277,	2048,	3277,	2731,
		3277,	3277,	2731,	2048,	3277,	2849,	2731,	2979,
		2731,	3277,	2731,	3277,	2048,	2849,	2341,	2979,
		2731,	2341,	3641,	2731,	3277,	3745,	2048,	2621,
		2341,	3641,	2185,	2979,	2427,	2979,	3197,	2114,
		3277,	2341,	2979,	2521,	2048,	1560,	2913,	3542,
		3277,	2521,	2114,	3745,	3197,	2731,	2731,	3277,
		2260,	3542,	3449,	1680,	2913,	3277,	3197,	3277,
	},

    // 85
	{
		3277,	2731,	2731,	3277,	2341,	2731,	2185,	3641,
		2048,	2048,	2048,	2731,	2048,	3855,	3641,	3855,
		2048,	2048,	3277,	2341,	2731,	3855,	3641,	3855,
		2048,	3277,	2341,	3641,	2185,	2521,	2731,	3449,
		3277,	2341,	2979,	3855,	3277,	3972,	2114,	2849,
		2341,	2979,	3855,	3449,	2731,	2114,	3855,	2341,
		2185,	3449,	2849,	2521,	2114,	3641,	3641,	2185,
		2979,	2341,	2260,	2260,	3855,	2185,	2114,	2185,
	},

    // 90 aa
	{
		2731,	2048,	2048,	2731,	3277,	2048,	3277,	2731,
		2048,	2048,	2731,	2048,	3277,	2731,	2731,	2979,
		2731,	2731,	2731,	3277,	2048,	2979,	2341,	2979,
		2731,	2731,	2048,	2731,	3277,	3855,	2048,	2731,
		2048,	2048,	2341,	2979,	2341,	2979,	3121,	2185,
		3277,	2341,	2979,	2521,	2048,	3121,	2849,	3641,
		3277,	2521,	2048,	3855,	3121,	2731,	2731,	3277,
		2341,	3641,	3449,	3277,	2979,	3277,	3121,	3277,
	},



    // 95
#if 0
	{
		2048,	2048,	2048,	2048,	2048,	2048,	3277,	2731,
		2048,	2048,	2048,	2048,	2731,	2731,	2731,	2731,
		2048,	2048,	2048,	2048,	2048,	2731,	2341,	2731,
		2048,	2048,	2048,	2731,	3277,	3641,	2048,	2731,
		2048,	2048,	2048,	2731,	2341,	2979,	3277,	2048,
		2048,	2048,	2731,	2731,	2048,	3277,	2979,	3641,
		3277,	2731,	2048,	3641,	3277,	2731,	2731,	3277,
		2341,	3641,	3277,	3277,	2979,	3277,	3277,	3277,
	}
#else
	{
		2048,	2048,	2048,	2731,	2731,	2731,	2048,	2731,
		2048,	2048,	2731,	2731,	2048,	2048,	3277,	2731,
		2048,	2048,	2048,	2048,	2048,	2048,	2048,	2048,
		2048,	2048,	2048,	2048,	2731,	2048,	2048,	2341,
		2048,	2048,	2731,	2048,	2048,	2731,	2731,	2341,
		2048,	2048,	2048,	2731,	2731,	3277,	2731,	2731,
		2731,	2048,	2731,	3277,	2048,	2048,	3277,	3277,
		2731,	2048,	2731,	2048,	3277,	3277,	2731,	3277,
	}
#endif
		
};

uint8  jpeg_fw_new_lum_quant_tbl_default_shift[5][64] =
{
    // 70
	{
		15,	14,	14,	15,	15,	16,	16,	17,
		14,	14,	14,	15,	15,	17,	17,	17,
		14,	14,	15,	15,	16,	17,	17,	17,
		14,	15,	15,	16,	16,	17,	17,	17,
		15,	15,	16,	17,	17,	18,	17,	17,
		15,	16,	17,	17,	17,	17,	18,	17,
		16,	17,	17,	17,	17,	18,	18,	17,
		17,	17,	17,	17,	18,	17,	17,	17,
	},

    // 80 aa    
	{
		14,	13,	13,	14,	15,	15,	16,	16,
		14,	14,	14,	14,	15,	16,	16,	16,
		14,	14,	14,	15,	15,	16,	16,	16,
		14,	14,	15,	15,	16,	17,	16,	16,
		14,	15,	15,	16,	16,	17,	17,	16,
		15,	15,	16,	16,	16,	16,	17,	17,
		16,	16,	16,	17,	17,	17,	17,	17,
		16,	17,	17,	16,	17,	17,	17,	17,
	},

    // 85
	{
		14,	13,	13,	14,	14,	15,	15,	16,
		13,	13,	13,	14,	14,	16,	16,	16,
		13,	13,	14,	14,	15,	16,	16,	16,
		13,	14,	14,	15,	15,	16,	16,	16,
		14,	14,	15,	16,	16,	17,	16,	16,
		14,	15,	16,	16,	16,	16,	17,	16,
		15,	16,	16,	16,	16,	17,	17,	16,
		16,	16,	16,	16,	17,	16,	16,	16,
	},

    // 90 aa
	{
		13,	12,	12,	13,	14,	14,	15,	15,
		12,	12,	13,	13,	14,	15,	15,	15,
		13,	13,	13,	14,	14,	15,	15,	15,
		13,	13,	13,	14,	15,	16,	15,	15,
		13,	13,	14,	15,	15,	16,	16,	15,
		14,	14,	15,	15,	15,	16,	16,	16,
		15,	15,	15,	16,	16,	16,	16,	16,
		15,	16,	16,	16,	16,	16,	16,	16,
	},

    // 95
#if 0
	{
		12,	11,	11,	12,	12,	13,	14,	14,
		11,	11,	11,	12,	13,	14,	14,	14,
		11,	11,	12,	12,	13,	14,	14,	14,
		11,	12,	12,	13,	14,	15,	14,	14,
		12,	12,	13,	14,	14,	15,	15,	14,
		12,	13,	14,	14,	14,	15,	15,	15,
		14,	14,	14,	15,	15,	15,	15,	15,
		14,	15,	15,	15,	15,	15,	15,	15,
	}
#else
	{
		11, 11, 12, 13, 13, 13, 12, 13,
		11, 11, 13, 13, 11, 11, 14, 13,
		11, 11, 11, 11, 11, 13, 12, 13,
		11, 11, 11, 11, 13, 11, 13, 14,
		11, 11, 13, 11, 13, 14, 14, 14,
		12, 13, 11, 14, 14, 14, 14, 14,
		13, 12, 14, 14, 13, 13, 14, 14,
		13, 13, 13, 13, 14, 14, 14, 14,
	}
#endif
		
};

uint16 jpeg_fw_new_chr_quant_tbl_default[5][64] = 
{

	 // 70
	{
		3277,	2341,	2731,	3277,	2341,	2731,	2114,	3542,
		2341,	2341,	2048,	2979,	2048,	3745,	3641,	3972,
		2048,	2048,	3277,	2341,	2731,	3855,	3197,	3855,
		2048,	3277,	2521,	3855,	2114,	2521,	2731,	3542,
		2979,	2521,	2979,	3855,	3197,	4033,	2114,	2849,
		2341,	3121,	3972,	3449,	2675,	2114,	3855,	2383,
		2260,	3449,	2789,	2521,	2114,	3591,	3641,	2149,
		3048,	2383,	2300,	2222,	3913,	2185,	2114,	2222,
	},
	
	// 80 aa
	{
		2731,	2048,	2048,	2731,	3277,	2048,	3277,	2731,
		3277,	3277,	2731,	2048,	3277,	2849,	2731,	2979,
		2731,	3277,	2731,	3277,	2048,	2849,	2341,	2979,
		2731,	2341,	3641,	2731,	3277,	3745,	2048,	2621,
		2341,	3641,	2185,	2979,	2427,	2979,	3197,	2114,
		3277,	2341,	2979,	2521,	2048,	1560,	2913,	3542,
		3277,	2521,	2114,	3745,	3197,	2731,	2731,	3277,
		2260,	3542,	3449,	1680,	2913,	3277,	3197,	3277,
	},

    // 85
	{
		3277,	2731,	2731,	3277,	2341,	2731,	2185,	3641,
		2048,	2048,	2048,	2731,	2048,	3855,	3641,	3855,
		2048,	2048,	3277,	2341,	2731,	3855,	3641,	3855,
		2048,	3277,	2341,	3641,	2185,	2521,	2731,	3449,
		3277,	2341,	2979,	3855,	3277,	3972,	2114,	2849,
		2341,	2979,	3855,	3449,	2731,	2114,	3855,	2341,
		2185,	3449,	2849,	2521,	2114,	3641,	3641,	2185,
		2979,	2341,	2260,	2260,	3855,	2185,	2114,	2185,
	},

    // 90 aa
	{
		2731,	2048,	2048,	2731,	3277,	2048,	3277,	2731,
		2048,	2048,	2731,	2048,	3277,	2731,	2731,	2979,
		2731,	2731,	2731,	3277,	2048,	2979,	2341,	2979,
		2731,	2731,	2048,	2731,	3277,	3855,	2048,	2731,
		2048,	2048,	2341,	2979,	2341,	2979,	3121,	2185,
		3277,	2341,	2979,	2521,	2048,	3121,	2849,	3641,
		3277,	2521,	2048,	3855,	3121,	2731,	2731,	3277,
		2341,	3641,	3449,	3277,	2979,	3277,	3121,	3277,
	},



    // 95
#if 0
	{
		2048,	2048,	2048,	2048,	2048,	2048,	3277,	2731,
		2048,	2048,	2048,	2048,	2731,	2731,	2731,	2731,
		2048,	2048,	2048,	2048,	2048,	2731,	2341,	2731,
		2048,	2048,	2048,	2731,	3277,	3641,	2048,	2731,
		2048,	2048,	2048,	2731,	2341,	2979,	3277,	2048,
		2048,	2048,	2731,	2731,	2048,	3277,	2979,	3641,
		3277,	2731,	2048,	3641,	3277,	2731,	2731,	3277,
		2341,	3641,	3277,	3277,	2979,	3277,	3277,	3277,
	}
#else
	{
		2048,	2048,	3277,	3277,	3277,	3277,	3277,	3277,
		2048,	3277,	3277,	3277,	2048,	3277,	3277,	3277,
		2731,	2048,	3277,	2048,	2048,	3277,	3277,	3277,
		2048,	2048,	2731,	2731,	3277,	3277,	3277,	3277,
		2048,	3277,	3277,	3277,	3277,	3277,	3277,	3277,
		3277,	3277,	3277,	3277,	3277,	3277,	3277,	3277,
		3277,	3277,	3277,	3277,	3277,	3277,	3277,	3277,
		3277,	3277,	3277,	3277,	3277,	3277,	3277,	3277,
	}
#endif
};

uint8 jpeg_fw_new_chr_quant_tbl_default_shift[5][64] =
{
	// 70
	{
		15,	14,	14,	15,	15,	16,	16,	17,
		14,	14,	14,	15,	15,	17,	17,	17,
		14,	14,	15,	15,	16,	17,	17,	17,
		14,	15,	15,	16,	16,	17,	17,	17,
		15,	15,	16,	17,	17,	18,	17,	17,
		15,	16,	17,	17,	17,	17,	18,	17,
		16,	17,	17,	17,	17,	18,	18,	17,
		17,	17,	17,	17,	18,	17,	17,	17,
	},

    // 80 aa    
	{
		14,	13,	13,	14,	15,	15,	16,	16,
		14,	14,	14,	14,	15,	16,	16,	16,
		14,	14,	14,	15,	15,	16,	16,	16,
		14,	14,	15,	15,	16,	17,	16,	16,
		14,	15,	15,	16,	16,	17,	17,	16,
		15,	15,	16,	16,	16,	16,	17,	17,
		16,	16,	16,	17,	17,	17,	17,	17,
		16,	17,	17,	16,	17,	17,	17,	17,
	},

    // 85
	{
		14,	13,	13,	14,	14,	15,	15,	16,
		13,	13,	13,	14,	14,	16,	16,	16,
		13,	13,	14,	14,	15,	16,	16,	16,
		13,	14,	14,	15,	15,	16,	16,	16,
		14,	14,	15,	16,	16,	17,	16,	16,
		14,	15,	16,	16,	16,	16,	17,	16,
		15,	16,	16,	16,	16,	17,	17,	16,
		16,	16,	16,	16,	17,	16,	16,	16,
	},

    // 90 aa
	{
		13,	12,	12,	13,	14,	14,	15,	15,
		12,	12,	13,	13,	14,	15,	15,	15,
		13,	13,	13,	14,	14,	15,	15,	15,
		13,	13,	13,	14,	15,	16,	15,	15,
		13,	13,	14,	15,	15,	16,	16,	15,
		14,	14,	15,	15,	15,	16,	16,	16,
		15,	15,	15,	16,	16,	16,	16,	16,
		15,	16,	16,	16,	16,	16,	16,	16,
	},

    // 95
#if 0
	{
		12,	11,	11,	12,	12,	13,	14,	14,
		11,	11,	11,	12,	13,	14,	14,	14,
		11,	11,	12,	12,	13,	14,	14,	14,
		11,	12,	12,	13,	14,	15,	14,	14,
		12,	12,	13,	14,	14,	15,	15,	14,
		12,	13,	14,	14,	14,	15,	15,	15,
		14,	14,	14,	15,	15,	15,	15,	15,
		14,	15,	15,	15,	15,	15,	15,	15,
	}
#else
	{
		11, 11, 14, 14, 14, 14, 14, 14,
		11, 14, 14, 14, 11, 14, 14, 14,
		13, 11, 14, 11, 13, 14, 14, 14,
		11, 13, 13, 13, 14, 14, 14, 14,
		11, 14, 14, 14, 14, 14, 14, 14,
		14, 14, 14, 14, 14, 14, 14, 14,
		14, 14, 14, 14, 14, 14, 14, 14,
		14, 14, 14, 14, 14, 14, 14, 14,
	}
#endif
};

//ASIC_DCT_TRANSFORM_MATRIX
const uint8 jpeg_fw_ASIC_DCT_Matrix[64] =
{
	0,	32,	16,	48,	8,	40,	24,	56,
	4,	36,	20,	52,	12,	44,	28,	60,
	2,	34,	18,	50,	10,	42,	26,	58,
	6,	38,	22,	54,	14,	46,	30,	62,
	1,	33,	17,	49,	 9,	41,	25,	57,
	5,	37,	21,	53,	13,	45,	29,	61,
	3,	35,	19,	51,	11,	43,	27,	59,
	7,	39,	23,	55,	15,	47,	31,	63,
};

//vld module default value of Registers
const uint32 jpeg_fw_vld_default_max_code[66] = 
{
	0x7f807fe0  ,0x7ff37ff7 ,//DC and AC valid;
	0x0			,0x0		,0x6		,0xe		,0x1e		,0x3e		,0x7e		,0xfe		,
	0x1fe		,0x3fe		,0x7fc		,0xff8		,0x1ff0		,0x3fe0		,0x7fc0		,0xff80		,
	0x0			,0x2		,0x6		,0xe		,0x1e		,0x3e		,0x7e		,0xfe		,
	0x1fe		,0x3fe		,0x7fe		,0xffe		,0x1ffc		,0x3ff8		,0x7ff0		,0xffe0		,
	0x0			,0x100		,0x402		,0xc03		,0x1c06		,0x3b09		,0x7b0b		,0xfa0f		,
	0x1fa12		,0x3fa17    ,0x7f91c    ,0xff720	,0x1ff000   ,0x3fe000   ,0x7fc024   ,0xfffe25   ,
	0x0			,0x100		,0x402		,0xb03		,0x1b05		,0x3b09		,0x7a0d		,0xf910		,
	0x1fa14		,0x3fa1b	,0x7f920	,0xff724	,0x1ff000	,0x3fe028	,0x7fc329	,0xfffe2b
};

const uint32	jpeg_fw_vld_default_huffTab[162] = 
{
	0x1,		0x102,		0x203,		0x1000300,  0x2001104,  0x411,	 0x3010505,	0x22112, 0x33121,  0x40631, 
	0x51241,	0x4106,		0x5113,		0x751,		0x4066161,  0x7107,  0x1322,	0x2271,  0x3214,   0x8132,  
	0x881,		0x1491,		0x42a1,		0x9108,		0xa123,		0xb142,  0x507c1b1,	0x9c1,   0x2315,   0x3352,  
	0x52d1,		0xf0f0,		0x1524,		0x6233,		0x7262,		0xd172,  0xa82,		0x1609,  0x608240a,0x3416, 
	0xe117,		0x2518,		0xf119,		0x171a,		0x1825,		0x1926,  0x1a27,	0x2628,  0x2729,   0x282a,  
	0x7092934,  0x2a35,		0x3536,		0x3637,		0x3738,		0x3839,  0x393a,	0x3a43,  0x4344,   0x4445,  
	0x4546,		0x4647,		0x80a4748,  0x4849,		0x494a,		0x4a53,  0x5354,	0x5455,  0x5556,   0x5657,  
	0x5758,		0x5859,		0x595a,		0x5a63,		0x90b6364,  0x6465,  0x6566,	0x6667,  0x6768,   0x6869,  
	0x696a,		0x6a73,		0x7374,		0x7475,		0x7576,		0x7677,  0xa007778, 0x7879,  0x797a,   0x7a83,  
	0x8284,		0x8385,		0x8486,		0x8587,		0x8688,		0x8789,  0x888a,	0x8992,  0xb008a93,0x9294,  
	0x9395,		0x9496,		0x9597,		0x9698,		0x9799,		0x989a,  0x99a2,	0x9aa3,  0xa2a4,   0xa3a5,  
	0xa4a6,		0xa5a7,		0xa6a8,		0xa7a9,		0xa8aa,		0xa9b2,  0xaab3,	0xb2b4,  0xb3b5,   0xb4b6,  
	0xb5b7,		0xb6b8,		0xb7b9,		0xb8ba,		0xb9c2,		0xbac3,  0xc2c4,	0xc3c5,  0xc4c6,   0xc5c7, 
	0xc6c8,		0xc7c9,		0xc8ca,		0xc9d2,		0xcad3,		0xd2d4,  0xd3d5,	0xd4d6,  0xd5d7,   0xd6d8,  
	0xd7d9,		0xd8da,		0xd9e1,		0xdae2,		0xe2e3,		0xe3e4,  0xe4e5,	0xe5e6,  0xe6e7,   0xe7e8, 
	0xe8e9,		0xe9ea,		0xeaf1,		0xf2f2,		0xf3f3,		0xf4f4,  0xf5f5,	0xf6f6,  0xf7f7,   0xf8f8, 
	0xf9f9,		0xfafa  
};

uint32		g_huffTab[162] = 
{
	0x1,		0x102,		0x203,		0x1000300,  0x2001104,  0x411,	 0x3010505,	0x22112, 0x33121,  0x40631, 
	0x51241,	0x4106,		0x5113,		0x751,		0x4066161,  0x7107,  0x1322,	0x2271,  0x3214,   0x8132,  
	0x881,		0x1491,		0x42a1,		0x9108,		0xa123,		0xb142,  0x507c1b1,	0x9c1,   0x2315,   0x3352,  
	0x52d1,		0xf0f0,		0x1524,		0x6233,		0x7262,		0xd172,  0xa82,		0x1609,  0x608240a,0x3416, 
	0xe117,		0x2518,		0xf119,		0x171a,		0x1825,		0x1926,  0x1a27,	0x2628,  0x2729,   0x282a,  
	0x7092934,  0x2a35,		0x3536,		0x3637,		0x3738,		0x3839,  0x393a,	0x3a43,  0x4344,   0x4445,  
	0x4546,		0x4647,		0x80a4748,  0x4849,		0x494a,		0x4a53,  0x5354,	0x5455,  0x5556,   0x5657,  
	0x5758,		0x5859,		0x595a,		0x5a63,		0x90b6364,  0x6465,  0x6566,	0x6667,  0x6768,   0x6869,  
	0x696a,		0x6a73,		0x7374,		0x7475,		0x7576,		0x7677,  0xa007778, 0x7879,  0x797a,   0x7a83,  
	0x8284,		0x8385,		0x8486,		0x8587,		0x8688,		0x8789,  0x888a,	0x8992,  0xb008a93,0x9294,  
	0x9395,		0x9496,		0x9597,		0x9698,		0x9799,		0x989a,  0x99a2,	0x9aa3,  0xa2a4,   0xa3a5,  
	0xa4a6,		0xa5a7,		0xa6a8,		0xa7a9,		0xa8aa,		0xa9b2,  0xaab3,	0xb2b4,  0xb3b5,   0xb4b6,  
	0xb5b7,		0xb6b8,		0xb7b9,		0xb8ba,		0xb9c2,		0xbac3,  0xc2c4,	0xc3c5,  0xc4c6,   0xc5c7, 
	0xc6c8,		0xc7c9,		0xc8ca,		0xc9d2,		0xcad3,		0xd2d4,  0xd3d5,	0xd4d6,  0xd5d7,   0xd6d8,  
	0xd7d9,		0xd8da,		0xd9e1,		0xdae2,		0xe2e3,		0xe3e4,  0xe4e5,	0xe5e6,  0xe6e7,   0xe7e8, 
	0xe8e9,		0xe9ea,		0xeaf1,		0xf2f2,		0xf3f3,		0xf4f4,  0xf5f5,	0xf6f6,  0xf7f7,   0xf8f8, 
	0xf9f9,		0xfafa  
};

uint32 g_huff_tab_enc[162] = 
{
	0x40000000,    0x80004000,    0xa0008000,    0xc000b000,    0xc800d000,    0xe000f000,    0xf000f800,    0xfa00fd80,    
	0xfd80ff82,	   0xff40ff83,    0xb000c000,    0xe400d800,    0xf600f200,    0xfa80fb00,    0xfec0fec0,    0xff50ff84,
    0xff88ff85,	   0xff89ff86,    0xff8aff87,    0xff8bff88,    0xd000e000,    0xf700f900,    0xfdc0fdc0,    0xff60ff40,
    0xff84ff89,    0xff8cff8a,    0xff8dff8b,    0xff8eff8c,    0xff8fff8d,    0xff90ff8e,    0xd800e800,    0xf800fb80,
    0xfe00ff50,    0xff70ff8f,    0xff91ff90,    0xff92ff91,    0xff93ff92,    0xff94ff93,    0xff95ff94,    0xff96ff95,
    0xe800ec00,    0xfb00fe00,    0xff97ff96,    0xff98ff97,    0xff99ff98,    0xff9aff99,    0xff9bff9a,    0xff9cff9b,
    0xff9dff9c,    0xff9eff9d,    0xec00f400,    0xfe40fee0,    0xff9fff9e,    0xffa0ff9f,    0xffa1ffa0,    0xffa2ffa1,
    0xffa3ffa2,    0xffa4ffa3,    0xffa5ffa4,    0xffa6ffa5,    0xf200f600,	   0xfee0ff60,    0xffa7ffa6,    0xffa8ffa7,
    0xffa9ffa8,    0xffaaffa9,    0xffabffaa,    0xffacffab,    0xffadffac,    0xffaeffad,    0xf400fa00,    0xff00ff70,
    0xffafffae,    0xffb0ffaf,    0xffb1ffb0,    0xffb2ffb1,    0xffb3ffb2,    0xffb4ffb3,    0xffb5ffb4,    0xffb6ffb5,
    0xf900fc00,    0xffb7ff80,    0xffb8ffb6,    0xffb9ffb7,    0xffbaffb8,    0xffbbffb9,    0xffbcffba,    0xffbdffbb,
    0xffbeffbc,    0xffbfffbd,    0xfb80fc80,    0xffc0ffbe,    0xffc1ffbf,    0xffc2ffc0,    0xffc3ffc1,    0xffc4ffc2, 
	0xffc5ffc3,    0xffc6ffc4,    0xffc7ffc5,    0xffc8ffc6,    0xfc00fd00,    0xffc9ffc7,    0xffcaffc8,    0xffcbffc9,
    0xffccffca,    0xffcdffcb,    0xffceffcc,    0xffcfffcd,    0xffd0ffce,    0xffd1ffcf,    0xfc80fe40,    0xffd2ffd0,
    0xffd3ffd1,    0xffd4ffd2,    0xffd5ffd3,    0xffd6ffd4,    0xffd7ffd5,    0xffd8ffd6,    0xffd9ffd7,    0xffdaffd8,
    0xfd00fe80,    0xffdbffd9,    0xffdcffda,    0xffddffdb,    0xffdeffdc,    0xffdfffdd,    0xffe0ffde,    0xffe1ffdf,
    0xffe2ffe0,    0xffe3ffe1,    0xff20ff00,    0xffe4ffe2,    0xffe5ffe3,    0xffe6ffe4,    0xffe7ffe5,    0xffe8ffe6,
    0xffe9ffe7,    0xffeaffe8,    0xffebffe9,    0xffecffea,    0xff80ffeb,    0xffedffec,    0xffeeffed,    0xffefffee,
    0xfff0ffef,    0xfff1fff0,    0xfff2fff1,    0xfff3fff2,    0xfff4fff3,    0xfff5fff4,    0xff86fff5,    0xfff6fff6,
    0xfff7fff7,    0xfff8fff8,    0xfff9fff9,    0xfffafffa,    0xfffbfffb,    0xfffcfffc,    0xfffdfffd,    0xfffefffe,
    0x0,		   0x0
};
