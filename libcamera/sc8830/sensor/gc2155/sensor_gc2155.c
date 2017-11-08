/*
 * Copyright (C) 2012 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <utils/Log.h>
#include "sensor.h"
#include "jpeg_exif_header.h"
#include "sensor_drv_u.h"

#define GC2155_I2C_ADDR_W		0x3c
#define GC2155_I2C_ADDR_R		0x3c

#define SENSOR_GAIN_SCALE		16

static uint32_t  shutter_flag = 0;

static uint32_t GC2155_PowerOn(uint32_t power_on);
static uint32_t set_preview_mode(uint32_t preview_mode);
static uint32_t GC2155_Identify(uint32_t param);
static uint32_t GC2155_BeforeSnapshot(uint32_t param);
static uint32_t GC2155_After_Snapshot(uint32_t param);
static uint32_t set_brightness(uint32_t level);
static uint32_t set_contrast(uint32_t level);
static uint32_t set_image_effect(uint32_t effect_type);
static uint32_t set_GC2155_ev(uint32_t level);
static uint32_t set_GC2155_awb(uint32_t mode);
static uint32_t set_GC2155_anti_flicker(uint32_t mode);
static uint32_t set_GC2155_video_mode(uint32_t mode);
static void GC2155_set_shutter();

typedef enum
{
	FLICKER_50HZ = 0,
	FLICKER_60HZ,
	FLICKER_MAX
}FLICKER_E;


SENSOR_REG_T GC2155_YUV_COMMON[]=
{

	{0xfe , 0xf0},
	{0xfe , 0xf0},
	{0xfe , 0xf0},
	{0xfc , 0x06},
	{0xf6 , 0x00},
	{0xf7 , 0x1d},
	{0xf8 , 0x84},
	{0xfa , 0x00},
	{0xf9 , 0xfe},
	{0xf2 , 0x00},

	/*ISP reg*/
	{0xfe , 0x00},
	{0x03 , 0x04},
	{0x04 , 0xe2},
	{0x09 , 0x00},
	{0x0a , 0x00},
	{0x0b , 0x00},
	{0x0c , 0x00},
	{0x0d , 0x04},
	{0x0e , 0xc0},//c0
	{0x0f , 0x06},
	{0x10 , 0x50},//50
	{0x12 , 0x2e},
	{0x17 , 0x14},
	{0x18 , 0x02},
	{0x19 , 0x0e},
	{0x1a , 0x01},
	{0x1b , 0x4b},
	{0x1c , 0x07},
	{0x1d , 0x10},
	{0x1e , 0x98},
	{0x1f , 0x78},
	{0x20 , 0x05},
	{0x21 , 0x40},
	{0x22 , 0xf0},
	{0x24 , 0x16},
	{0x25 , 0x01},
	{0x26 , 0x10},
	{0x2d , 0x40},
	{0x30 , 0x01},
	{0x31 , 0x90},
	{0x33 , 0x04},
	{0x34 , 0x01},

	/*ISP reg*/
	{0xfe , 0x00},
	{0x80 , 0xff},
	{0x81 , 0x2c},
	{0x82 , 0xfa},
	{0x83 , 0x00},
	{0x84 , 0x02}, //yuv 01
	{0x85 , 0x08},
	{0x86 , 0x02},
	{0x89 , 0x03},
	{0x8a , 0x00},
	{0x8b , 0x00},
	{0xb0 , 0x55},
	{0xc3 , 0x11}, //00
	{0xc4 , 0x20},
	{0xc5 , 0x30},
	{0xc6 , 0x38},
	{0xc7 , 0x40},
	{0xec , 0x02},
	{0xed , 0x04},
	{0xee , 0x60},
	{0xef , 0x90},
	{0xb6 , 0x01},
	{0x90 , 0x01},
	{0x91 , 0x00},
	{0x92 , 0x00},
	{0x93 , 0x00},
	{0x94 , 0x00},
	{0x95 , 0x04},
	{0x96 , 0xb0},
	{0x97 , 0x06},
	{0x98 , 0x40},

	/*BLK*/
	{0xfe , 0x00},
	{0x18 , 0x02},
	{0x40 , 0x42},
	{0x41 , 0x00},
	{0x43 , 0x54},
	{0x5e , 0x00},
	{0x5f , 0x00},
	{0x60 , 0x00},
	{0x61 , 0x00},
	{0x62 , 0x00},
	{0x63 , 0x00},
	{0x64 , 0x00},
	{0x65 , 0x00},
	{0x66 , 0x20},
	{0x67 , 0x20},
	{0x68 , 0x20},
	{0x69 , 0x20},
	{0x6a , 0x08},
	{0x6b , 0x08},
	{0x6c , 0x08},
	{0x6d , 0x08},
	{0x6e , 0x08},
	{0x6f , 0x08},
	{0x70 , 0x08},
	{0x71 , 0x08},
	{0x72 , 0xf0},
	{0x7e , 0x3c},
	{0x7f , 0x00},
	{0xfe , 0x00},

	/*AEC*/
	{0xfe , 0x01},
	{0x01 , 0x08},
	{0x02 , 0xc0},
	{0x03 , 0x04},
	{0x04 , 0x90},
	{0x05 , 0x30},
	{0x06 , 0x98},
	{0x07 , 0x28},
	{0x08 , 0x6c},
	{0x09 , 0x00},
	{0x0a , 0xc2},
	{0x0b , 0x11},
	{0x0c , 0x10},
	{0x13 , 0x2d},
	{0x17 , 0x00},
	{0x1c , 0x11},
	{0x1e , 0x61},
	{0x1f , 0x30},
	{0x20 , 0x40},
	{0x22 , 0x80},
	{0x23 , 0x20},

	{0x12 , 0x35},
	{0x15 , 0x50},
	{0x10 , 0x31},
	{0x3e , 0x28},
	{0x3f , 0xe0},
	{0x40 , 0xe0},
	{0x41 , 0x08},

	{0xfe , 0x02},
	{0x0f , 0x05},

	/*INTPEE*/
	{0xfe , 0x02},
	{0x90 , 0x6c},
	{0x91 , 0x03},
	{0x92 , 0xc4},
	{0x97 , 0x64},
	{0x98 , 0x88},
	{0x9d , 0x08},
	{0xa2 , 0x11},
	{0xfe , 0x00},

	/*DNDD*/
	{0xfe , 0x02},
	{0x80 , 0xc1},
	{0x81 , 0x08},
	{0x82 , 0x05},
	{0x83 , 0x04},
	{0x84 , 0x0a},
	{0x86 , 0x80},
	{0x87 , 0x30},
	{0x88 , 0x15},
	{0x89 , 0x80},
	{0x8a , 0x60},
	{0x8b , 0x30},

	/*ASDE*/
	{0xfe , 0x01},
	{0x21 , 0x14},
	{0xfe , 0x02},
	{0x3c , 0x06},
	{0x3d , 0x40},
	{0x48 , 0x30},
	{0x49 , 0x06},
	{0x4b , 0x08},
	{0x4c , 0x20},
	{0xa3 , 0x50},
	{0xa4 , 0x30},
	{0xa5 , 0x40},
	{0xa6 , 0x80},
	{0xab , 0x40},
	{0xae , 0x0c},
	{0xb3 , 0x42},
	{0xb4 , 0x24},
	{0xb6 , 0x50},
	{0xb7 , 0x01},
	{0xb9 , 0x28},
	{0xfe , 0x00},

	/*gamma1*/
	{0xfe , 0x02},
	{0x10 , 0x0d},
	{0x11 , 0x12},
	{0x12 , 0x17},
	{0x13 , 0x1c},
	{0x14 , 0x27},
	{0x15 , 0x34},
	{0x16 , 0x44},
	{0x17 , 0x55},
	{0x18 , 0x6e},
	{0x19 , 0x81},
	{0x1a , 0x91},
	{0x1b , 0x9c},
	{0x1c , 0xaa},
	{0x1d , 0xbb},
	{0x1e , 0xca},
	{0x1f , 0xd5},
	{0x20 , 0xe0},
	{0x21 , 0xe7},
	{0x22 , 0xed},
	{0x23 , 0xf6},
	{0x24 , 0xfb},
	{0x25 , 0xff},

	/*gamma2*/
	{0xfe , 0x02},
	{0x26 , 0x0d},
	{0x27 , 0x12},
	{0x28 , 0x17},
	{0x29 , 0x1c},
	{0x2a , 0x27},
	{0x2b , 0x34},
	{0x2c , 0x44},
	{0x2d , 0x55},
	{0x2e , 0x6e},
	{0x2f , 0x81},
	{0x30 , 0x91},
	{0x31 , 0x9c},
	{0x32 , 0xaa},
	{0x33 , 0xbb},
	{0x34 , 0xca},
	{0x35 , 0xd5},
	{0x36 , 0xe0},
	{0x37 , 0xe7},
	{0x38 , 0xed},
	{0x39 , 0xf6},
	{0x3a , 0xfb},
	{0x3b , 0xff},

	/*YCP*/
	{0xfe , 0x02},
	{0xd1 , 0x28},
	{0xd2 , 0x28},
	{0xdd , 0x14},
	{0xde , 0x88},
	{0xed , 0x80},

	/*LSC*/
	{0xfe , 0x01},
	{0xc2 , 0x1f},
	{0xc3 , 0x13},
	{0xc4 , 0x0e},
	{0xc8 , 0x16},
	{0xc9 , 0x0f},
	{0xca , 0x0c},
	{0xbc , 0x52},
	{0xbd , 0x2c},
	{0xbe , 0x27},
	{0xb6 , 0x47},
	{0xb7 , 0x32},
	{0xb8 , 0x30},
	{0xc5 , 0x00},
	{0xc6 , 0x00},
	{0xc7 , 0x00},
	{0xcb , 0x00},
	{0xcc , 0x00},
	{0xcd , 0x00},
	{0xbf , 0x0e},
	{0xc0 , 0x00},
	{0xc1 , 0x00},
	{0xb9 , 0x08},
	{0xba , 0x00},
	{0xbb , 0x00},
	{0xaa , 0x0a},
	{0xab , 0x0c},
	{0xac , 0x0d},
	{0xad , 0x02},
	{0xae , 0x06},
	{0xaf , 0x05},
	{0xb0 , 0x00},
	{0xb1 , 0x05},
	{0xb2 , 0x02},
	{0xb3 , 0x04},
	{0xb4 , 0x04},
	{0xb5 , 0x05},
	{0xd0 , 0x00},
	{0xd1 , 0x00},
	{0xd2 , 0x00},
	{0xd6 , 0x02},
	{0xd7 , 0x00},
	{0xd8 , 0x00},
	{0xd9 , 0x00},
	{0xda , 0x00},
	{0xdb , 0x00},
	{0xd3 , 0x00},
	{0xd4 , 0x00},
	{0xd5 , 0x00},
	{0xa4 , 0x04},
	{0xa5 , 0x00},
	{0xa6 , 0x77},
	{0xa7 , 0x77},
	{0xa8 , 0x77},
	{0xa9 , 0x77},
	{0xa1 , 0x80},
	{0xa2 , 0x80},

	{0xfe , 0x01},
	{0xdc , 0x35},
	{0xdd , 0x28},
	{0xdf , 0x0d},
	{0xe0 , 0x70},
	{0xe1 , 0x78},
	{0xe2 , 0x70},
	{0xe3 , 0x78},
	{0xe6 , 0x90},
	{0xe7 , 0x70},
	{0xe8 , 0x90},
	{0xe9 , 0x70},
	{0xfe , 0x00},

	/*AWB*/
	{0xfe , 0x01},
	{0x4f , 0x00},
	{0x4f , 0x00},
	{0x4b , 0x01},
	{0x4f , 0x00},
	{0x4c , 0x01},
	{0x4d , 0x71},
	{0x4e , 0x02},
	{0x4c , 0x01},
	{0x4d , 0x91},
	{0x4e , 0x02},
	{0x4c , 0x01},
	{0x4d , 0x50},
	{0x4e , 0x02},
	{0x4c , 0x01},
	{0x4d , 0x70},
	{0x4e , 0x02},
	{0x4c , 0x01},
	{0x4d , 0x90},
	{0x4e , 0x02},
	{0x4c , 0x01},
	{0x4d , 0xb0},
	{0x4e , 0x02},
	{0x4c , 0x01},
	{0x4d , 0xd0},
	{0x4e , 0x02},
	{0x4c , 0x01},
	{0x4d , 0x4f},
	{0x4e , 0x02},
	{0x4c , 0x01},
	{0x4d , 0x6f},
	{0x4e , 0x02},
	{0x4c , 0x01},
	{0x4d , 0x8f},
	{0x4e , 0x02},
	{0x4c , 0x01},
	{0x4d , 0xaf},
	{0x4e , 0x02},
	{0x4c , 0x01},
	{0x4d , 0xcf},
	{0x4e , 0x02},
	{0x4c , 0x01},
	{0x4d , 0x6e},
	{0x4e , 0x03},
	{0x4c , 0x01},
	{0x4d , 0x8e},
	{0x4e , 0x03},
	{0x4c , 0x01},
	{0x4d , 0xae},
	{0x4e , 0x03},
	{0x4c , 0x01},
	{0x4d , 0xce},
	{0x4e , 0x03},
	{0x4c , 0x01},
	{0x4d , 0x4d},
	{0x4e , 0x03},
	{0x4c , 0x01},
	{0x4d , 0x6d},
	{0x4e , 0x03},
	{0x4c , 0x01},
	{0x4d , 0x8d},
	{0x4e , 0x03},
	{0x4c , 0x01},
	{0x4d , 0xad},
	{0x4e , 0x03},
	{0x4c , 0x01},
	{0x4d , 0xcd},
	{0x4e , 0x03},
	{0x4c , 0x01},
	{0x4d , 0x4c},
	{0x4e , 0x03},
	{0x4c , 0x01},
	{0x4d , 0x6c},
	{0x4e , 0x03},
	{0x4c , 0x01},
	{0x4d , 0x8c},
	{0x4e , 0x03},
	{0x4c , 0x01},
	{0x4d , 0xac},
	{0x4e , 0x03},
	{0x4c , 0x01},
	{0x4d , 0xcc},
	{0x4e , 0x03},
	{0x4c , 0x01},
	{0x4d , 0xec},
	{0x4e , 0x03},
	{0x4c , 0x01},
	{0x4d , 0x4b},
	{0x4e , 0x03},
	{0x4c , 0x01},
	{0x4d , 0x6b},
	{0x4e , 0x03},
	{0x4c , 0x01},
	{0x4d , 0x8b},
	{0x4e , 0x03},
	{0x4c , 0x01},
	{0x4d , 0xab},
	{0x4e , 0x03},
	{0x4c , 0x01},
	{0x4d , 0x8a},
	{0x4e , 0x04},
	{0x4c , 0x01},
	{0x4d , 0xaa},
	{0x4e , 0x04},
	{0x4c , 0x01},
	{0x4d , 0xca},
	{0x4e , 0x04},
	{0x4c , 0x01},
	{0x4d , 0xa9},
	{0x4e , 0x04},
	{0x4c , 0x01},
	{0x4d , 0xc9},
	{0x4e , 0x04},
	{0x4c , 0x01},
	{0x4d , 0xcb},
	{0x4e , 0x05},
	{0x4c , 0x01},
	{0x4d , 0xeb},
	{0x4e , 0x05},
	{0x4c , 0x02},
	{0x4d , 0x0b},
	{0x4e , 0x05},
	{0x4c , 0x02},
	{0x4d , 0x2b},
	{0x4e , 0x05},
	{0x4c , 0x02},
	{0x4d , 0x4b},
	{0x4e , 0x05},
	{0x4c , 0x01},
	{0x4d , 0xea},
	{0x4e , 0x05},
	{0x4c , 0x02},
	{0x4d , 0x0a},
	{0x4e , 0x05},
	{0x4c , 0x02},
	{0x4d , 0x2a},
	{0x4e , 0x05},
	{0x4c , 0x02},
	{0x4d , 0x6a},
	{0x4e , 0x06},
	{0x4c , 0x02},
	{0x4d , 0x29},
	{0x4e , 0x06},
	{0x4c , 0x02},
	{0x4d , 0x49},
	{0x4e , 0x06},
	{0x4c , 0x02},
	{0x4d , 0x69},
	{0x4e , 0x06},
	{0x4c , 0x02},
	{0x4d , 0x89},
	{0x4e , 0x06},
	{0x4c , 0x02},
	{0x4d , 0xa9},
	{0x4e , 0x06},
	{0x4c , 0x02},
	{0x4d , 0xc9},
	{0x4e , 0x06},
	{0x4c , 0x02},
	{0x4d , 0x48},
	{0x4e , 0x06},
	{0x4c , 0x02},
	{0x4d , 0x68},
	{0x4e , 0x06},
	{0x4c , 0x03},
	{0x4d , 0x09},
	{0x4e , 0x07},
	{0x4c , 0x02},
	{0x4d , 0xa8},
	{0x4e , 0x07},
	{0x4c , 0x02},
	{0x4d , 0xc8},
	{0x4e , 0x07},
	{0x4c , 0x02},
	{0x4d , 0xe8},
	{0x4e , 0x07},
	{0x4c , 0x03},
	{0x4d , 0x08},
	{0x4e , 0x07},
	{0x4c , 0x03},
	{0x4d , 0x28},
	{0x4e , 0x07},
	{0x4c , 0x02},
	{0x4d , 0x87},
	{0x4e , 0x07},
	{0x4c , 0x02},
	{0x4d , 0xa7},
	{0x4e , 0x07},
	{0x4c , 0x02},
	{0x4d , 0xc7},
	{0x4e , 0x07},
	{0x4c , 0x02},
	{0x4d , 0xe7},
	{0x4e , 0x07},
	{0x4c , 0x03},
	{0x4d , 0x07},
	{0x4e , 0x07},
	{0x4f , 0x01},
	{0xfe , 0x01},

	{0x50 , 0x80},
	{0x51 , 0xa8},
	{0x52 , 0x57},
	{0x53 , 0x38},
	{0x54 , 0xc7},
	{0x56 , 0x0e},
	{0x58 , 0x08},
	{0x5b , 0x00},
	{0x5c , 0x74},
	{0x5d , 0x8b},
	{0x61 , 0xd3},
	{0x62 , 0x90},
	{0x63 , 0xaa},
	{0x65 , 0x04},
	{0x67 , 0xb2},
	{0x68 , 0xac},
	{0x69 , 0x00},
	{0x6a , 0xb2},
	{0x6b , 0xac},
	{0x6c , 0xdc},
	{0x6d , 0xb0},
	{0x6e , 0x30},
	{0x6f , 0x40},
	{0x70 , 0x05},
	{0x71 , 0x80},
	{0x72 , 0x80},
	{0x73 , 0x30},
	{0x74 , 0x01},
	{0x75 , 0x01},
	{0x7f , 0x08},
	{0x76 , 0x70},
	{0x77 , 0x48},
	{0x78 , 0xa0},
	{0xfe , 0x00},

	/*CC*/
	{0xfe , 0x02},
	{0xc0 , 0x01},
	{0xc1 , 0x4a},
	{0xc2 , 0xf3},
	{0xc3 , 0xfc},
	{0xc4 , 0xe4},
	{0xc5 , 0x48},
	{0xc6 , 0xec},
	{0xc7 , 0x45},
	{0xc8 , 0xf8},
	{0xc9 , 0x02},
	{0xca , 0xfe},
	{0xcb , 0x42},
	{0xcc , 0x00},
	{0xcd , 0x45},
	{0xce , 0xf0},
	{0xcf , 0x00},
	{0xe3 , 0xf0},
	{0xe4 , 0x45},
	{0xe5 , 0xe8},

	/*ABS*/
	{0xfe , 0x01},
	{0x9f , 0x42},
	{0xfe , 0x00},

	/*OUTPUT*/
	{0xfe , 0x00},
	{0xf2 , 0x0f},

	/*frame rate 50Hz*/
	{0xfe , 0x00},
	{0x05 , 0x01},
	{0x06 , 0x56},
	{0x07 , 0x00},
	{0x08 , 0x32},
	{0xfe , 0x01},
	{0x25 , 0x00},
	{0x26 , 0xfa},
	{0x27 , 0x04},
	{0x28 , 0xe2}, //20fps
	{0x29 , 0x06},
	{0x2a , 0xd6}, //16fps
	{0x2b , 0x07},
	{0x2c , 0xd0}, //12fps
	{0x2d , 0x0b},
	{0x2e , 0xb8}, //8fps
	{0xfe , 0x00},
};

SENSOR_REG_T GC2155_YUV_800x600[]=
{
	{0xfe , 0x00},
	{0xfa , 0x00},
	{0xfd , 0x01},
	//crop window
	{0xfe , 0x00},
	{0x99 , 0x11},
	{0x9a , 0x06},
	{0x9b , 0x00},
	{0x9c , 0x00},
	{0x9d , 0x00},
	{0x9e , 0x00},
	{0x9f , 0x00},
	{0xa0 , 0x00},
	{0xa1 , 0x00},
	{0xa2  ,0x00},
	{0x90 , 0x01},
	{0x91 , 0x00},
	{0x92 , 0x00},
	{0x93 , 0x00},
	{0x94 , 0x00},
	{0x95 , 0x02},
	{0x96 , 0x58},
	{0x97 , 0x03},
	{0x98 , 0x20},
	//AWB
	{0xfe , 0x00},
	{0xec , 0x01},
	{0xed , 0x02},
	{0xee , 0x30},
	{0xef , 0x48},
	{0xfe , 0x01},
	{0x74 , 0x00},
	//AEC
	{0xfe , 0x01},
	{0x01 , 0x04},
	{0x02 , 0x60},
	{0x03 , 0x02},
	{0x04 , 0x48},
	{0x05 , 0x18},
	{0x06 , 0x4c},
	{0x07 , 0x14},
	{0x08 , 0x36},
	{0x0a , 0xc0},
	{0x21 , 0x14},
	{0xfe , 0x00},
	//gamma
	{0xfe , 0x00},
	{0xc3 , 0x11},
	{0xc4 , 0x20},
	{0xc5 , 0x30},
	{0xfe , 0x00},
};

SENSOR_REG_T GC2155_YUV_1280x960[]=
{
	//1280X960
	{0xfe , 0x00},
	{0xfa , 0x00},
	{0xfd , 0x00},
	//crop window
	{0xfe , 0x00},
	{0x99 , 0x55},
	{0x9a , 0x06},
	{0x9b , 0x00},
	{0x9c , 0x00},
	{0x9d , 0x01},
	{0x9e , 0x23},
	{0x9f , 0x00},
	{0xa0 , 0x00},
	{0xa1 , 0x01},
	{0xa2  ,0x23},
	{0x90 , 0x01},
	{0x91 , 0x00},
	{0x92 , 0x00},
	{0x93 , 0x00},
	{0x94 , 0x00},
	{0x95 , 0x03},
	{0x96 , 0xc0},
	{0x97 , 0x05},
	{0x98 , 0x00},

	//AWB
	{0xfe , 0x00},
	{0xec , 0x02},
	{0xed , 0x04},
	{0xee , 0x60},
	{0xef , 0x90},
	{0xfe , 0x01},
	{0x74 , 0x01},
	//AEC
	{0xfe , 0x01},
	{0x01 , 0x08},
	{0x02 , 0xc0},
	{0x03 , 0x04},
	{0x04 , 0x90},
	{0x05 , 0x30},
	{0x06 , 0x98},
	{0x07 , 0x28},
	{0x08 , 0x6c},
	{0x0a , 0xc2},
	{0x21 , 0x15},
	{0xfe , 0x00},
	//gamma
	{0xfe , 0x00},
	{0xc3 , 0x00},
	{0xc4 , 0x90},
	{0xc5 , 0x98},
	{0xfe , 0x00},
};

SENSOR_REG_T GC2155_YUV_1600x1200[]=
{
	{0xfe , 0x00},
	{0xfa , 0x00},
	{0xfd , 0x00},
	//crop window
	{0xfe , 0x00},
	{0x99 , 0x11},
	{0x9a , 0x06},
	{0x9b , 0x00},
	{0x9c , 0x00},
	{0x9d , 0x00},
	{0x9e , 0x00},
	{0x9f , 0x00},
	{0xa0 , 0x00},
	{0xa1 , 0x00},
	{0xa2  ,0x00},
	{0x90 , 0x01},
	{0x91 , 0x00},
	{0x92 , 0x00},
	{0x93 , 0x00},
	{0x94 , 0x00},
	{0x95 , 0x04},
	{0x96 , 0xb0},
	{0x97 , 0x06},
	{0x98 , 0x40},
	//AWB
	{0xfe , 0x00},
	{0xec , 0x02},
	{0xed , 0x04},
	{0xee , 0x60},
	{0xef , 0x90},
	{0xfe , 0x01},
	{0x74 , 0x01},
	//AEC
	{0xfe , 0x01},
	{0x01 , 0x08},
	{0x02 , 0xc0},
	{0x03 , 0x04},
	{0x04 , 0x90},
	{0x05 , 0x30},
	{0x06 , 0x98},
	{0x07 , 0x28},
	{0x08 , 0x6c},
	{0x0a , 0xc2},
	{0x21 , 0x15},
	{0xfe , 0x00},
	//gamma
	{0xfe , 0x00},
	{0xc3 , 0x00},
	{0xc4 , 0x90},
	{0xc5 , 0x98},
	{0xfe , 0x00},
};

static SENSOR_REG_TAB_INFO_T s_GC2155_resolution_Tab_YUV[]=
{
	// COMMON INIT
	{ADDR_AND_LEN_OF_ARRAY(GC2155_YUV_COMMON), 0, 0, 24, SENSOR_IMAGE_FORMAT_YUV422},

	// YUV422 PREVIEW 1
	{ADDR_AND_LEN_OF_ARRAY(GC2155_YUV_800x600), 800, 600, 24, SENSOR_IMAGE_FORMAT_YUV422},
	{ADDR_AND_LEN_OF_ARRAY(GC2155_YUV_1280x960), 1280, 960, 24, SENSOR_IMAGE_FORMAT_YUV422},
	{ADDR_AND_LEN_OF_ARRAY(GC2155_YUV_1600x1200), 1600, 1200, 24, SENSOR_IMAGE_FORMAT_YUV422},
	{PNULL, 0, 0, 0, 0, 0},

	// YUV422 PREVIEW 2
	{PNULL, 0, 0, 0, 0, 0},
	{PNULL, 0, 0, 0, 0, 0},
	{PNULL, 0, 0, 0, 0, 0},
	{PNULL, 0, 0, 0, 0, 0}
};

static SENSOR_IOCTL_FUNC_TAB_T s_GC2155_ioctl_func_tab =
{
	// Internal
	PNULL,
	GC2155_PowerOn,
	PNULL,
	GC2155_Identify,

	PNULL,			// write register
	PNULL,			// read  register
	PNULL,
	PNULL,

	// External
	PNULL,
	PNULL,
	PNULL,

	set_brightness,
	set_contrast,
	PNULL,			//set_sharpness,
	PNULL,			//set_saturation,

	set_preview_mode,
	set_image_effect,

	GC2155_BeforeSnapshot,
	GC2155_After_Snapshot,

	PNULL,

	PNULL,
	PNULL,
	PNULL,
	PNULL,
	PNULL,
	PNULL,
	PNULL,
	PNULL,
	set_GC2155_awb,
	PNULL,
	PNULL,
	set_GC2155_ev,
	PNULL,
	PNULL,
	PNULL,
	PNULL,
	PNULL,
	set_GC2155_anti_flicker,
	set_GC2155_video_mode,
	PNULL,
	PNULL,
	PNULL,			//get_status
	PNULL,
	PNULL,
	PNULL,
};

static const SENSOR_REG_T s_gc2155_800x600_video_tab[SENSOR_VIDEO_MODE_MAX][1] = {
	/*video mode 0: ?fps*/
	{
		{0xffff, 0xff}
	},
	/* video mode 1:?fps*/
	{
		{0xffff, 0xff}
	},
	/* video mode 2:?fps*/
	{
		{0xffff, 0xff}
	},
	/* video mode 3:?fps*/
	{
		{0xffff, 0xff}
	}
};

static const SENSOR_REG_T s_gc2155_1280x960_video_tab[SENSOR_VIDEO_MODE_MAX][1] = {
	/*video mode 0: ?fps*/
	{
		{0xffff, 0xff}
	},
	/* video mode 1:?fps*/
	{
		{0xffff, 0xff}
	},
	/* video mode 2:?fps*/
	{
		{0xffff, 0xff}
	},
	/* video mode 3:?fps*/
	{
		{0xffff, 0xff}
	}
};

static const SENSOR_REG_T s_gc2155_1600x1200_video_tab[SENSOR_VIDEO_MODE_MAX][1] = {
	/*video mode 0: ?fps*/
	{
		{0xffff, 0xff}
	},
	/* video mode 1:?fps*/
	{
		{0xffff, 0xff}
	},
	/* video mode 2:?fps*/
	{
		{0xffff, 0xff}
	},
	/* video mode 3:?fps*/
	{
		{0xffff, 0xff}
	}
};

static SENSOR_VIDEO_INFO_T s_gc2155_video_info[] = {
	{{{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}, PNULL},
	{{{0, 0, 0, 0}, {30, 30, 175, 100}, {0, 0, 0, 0}, {0, 0, 0, 0}}, (SENSOR_REG_T**)s_gc2155_800x600_video_tab},
	{{{0, 0, 0, 0}, {30, 30, 219, 100}, {0, 0, 0, 0}, {0, 0, 0, 0}}, (SENSOR_REG_T**)s_gc2155_1280x960_video_tab},
	{{{0, 0, 0, 0}, {30, 30, 219, 100}, {0, 0, 0, 0}, {0, 0, 0, 0}}, (SENSOR_REG_T**)s_gc2155_1600x1200_video_tab},
	{{{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}, PNULL},
	{{{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}, PNULL},

	{{{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}, PNULL},
	{{{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}, PNULL},
	{{{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}, PNULL}
};

SENSOR_INFO_T g_GC2155_yuv_info =
{
	GC2155_I2C_ADDR_W,			// salve i2c write address
	GC2155_I2C_ADDR_R,			// salve i2c read address

	0,					// bit0: 0: i2c register value is 8 bit, 1: i2c register value is 16 bit
						// bit2: 0: i2c register addr  is 8 bit, 1: i2c register addr  is 16 bit
						// other bit: reseved
	SENSOR_HW_SIGNAL_PCLK_N|\
	SENSOR_HW_SIGNAL_VSYNC_N|\
	SENSOR_HW_SIGNAL_HSYNC_P,		// bit0: 0:negative; 1:positive -> polarily of pixel clock
						// bit2: 0:negative; 1:positive -> polarily of horizontal synchronization signal
						// bit4: 0:negative; 1:positive -> polarily of vertical synchronization signal
						// other bit: reseved

	// preview mode
	SENSOR_ENVIROMENT_NORMAL|\
	SENSOR_ENVIROMENT_NIGHT|\
	SENSOR_ENVIROMENT_SUNNY,

	// image effect
	SENSOR_IMAGE_EFFECT_NORMAL|\
	SENSOR_IMAGE_EFFECT_BLACKWHITE|\
	SENSOR_IMAGE_EFFECT_RED|\
	SENSOR_IMAGE_EFFECT_GREEN|\
	SENSOR_IMAGE_EFFECT_BLUE|\
	SENSOR_IMAGE_EFFECT_YELLOW|\
	SENSOR_IMAGE_EFFECT_NEGATIVE|\
	SENSOR_IMAGE_EFFECT_CANVAS,

	// while balance mode
	0,

	7,					// bit[0:7]: count of step in brightness, contrast, sharpness, saturation
						// bit[8:31] reseved

	SENSOR_LOW_PULSE_RESET,		// reset pulse level
	100,					// reset pulse width(ms)

	SENSOR_HIGH_LEVEL_PWDN,		// 1: high level valid; 0: low level valid

	1,					// count of identify code
	{{0xf0, 0x21},				// supply two code to identify sensor.
	 {0xf1, 0x55}},				// for Example: index = 0-> Device id, index = 1 -> version id

	SENSOR_AVDD_2800MV,			// voltage of avdd

	1600,					// max width of source image
	1200,					// max height of source image
	"GC2155",				// name of sensor

	SENSOR_IMAGE_FORMAT_YUV422,		// define in SENSOR_IMAGE_FORMAT_E enum,
						// if set to SENSOR_IMAGE_FORMAT_MAX here, image format depent on SENSOR_REG_TAB_INFO_T
	SENSOR_IMAGE_PATTERN_YUV422_YUYV,	// pattern of input image form sensor;

	s_GC2155_resolution_Tab_YUV,		// point to resolution table information structure
	&s_GC2155_ioctl_func_tab,			// point to ioctl function table

	PNULL,					// information and table about Rawrgb sensor
	PNULL,					// extend information about sensor
	SENSOR_AVDD_1800MV,			// iovdd
	SENSOR_AVDD_1800MV,			// dvdd
	2,					// skip frame num before preview
	1,					// skip frame num before capture
	0,					// deci frame num during preview
	0,					// deci frame num during video preview
	0,					// threshold enable(only analog TV)
	0,					// atv output mode 0 fix mode 1 auto mode
	0,					// atv output start postion
	0,					// atv output end postion
	0,
	{SENSOR_INTERFACE_TYPE_CCIR601, 8, 16, 1},
	s_gc2155_video_info,
	1,					// skip frame num while change setting
	48,					// horizontal view angle
	48,					// vertical view angle
};

static void GC2155_WriteReg( uint8_t  subaddr, uint8_t data )
{

	Sensor_WriteReg_8bits(subaddr, data);

}

static uint8_t GC2155_ReadReg( uint8_t subaddr)
{
	uint8_t value = 0;

	value = Sensor_ReadReg( subaddr);

	return value;
}

static uint32_t GC2155_PowerOn(uint32_t power_on)
{
	SENSOR_AVDD_VAL_E dvdd_val = g_GC2155_yuv_info.dvdd_val;
	SENSOR_AVDD_VAL_E avdd_val = g_GC2155_yuv_info.avdd_val;
	SENSOR_AVDD_VAL_E iovdd_val = g_GC2155_yuv_info.iovdd_val;
	BOOLEAN power_down = g_GC2155_yuv_info.power_down_level;
	BOOLEAN reset_level = g_GC2155_yuv_info.reset_pulse_level;

	if (SENSOR_TRUE == power_on) {
		Sensor_PowerDown(power_down);
		// Open power
		Sensor_SetVoltage(dvdd_val, avdd_val, iovdd_val);
		usleep(10*1000);
		Sensor_SetMCLK(SENSOR_DEFALUT_MCLK);
		usleep(10*1000);
		Sensor_PowerDown(!power_down);
		// Reset sensor
		Sensor_Reset(reset_level);
	} else {
		Sensor_PowerDown(power_down);
		Sensor_SetMCLK(SENSOR_DISABLE_MCLK);
		Sensor_SetVoltage(SENSOR_AVDD_CLOSED, SENSOR_AVDD_CLOSED,
		SENSOR_AVDD_CLOSED);
	}
	SENSOR_PRINT("(1:on, 0:off): %d", power_on);
	return SENSOR_SUCCESS;
}

static uint32_t GC2155_Identify(uint32_t param)
{
#define GC2155_PID_ADDR1		0xf0
#define GC2155_PID_ADDR2		0xf1
#define GC2155_SENSOR_ID		0x2155

	uint16_t sensor_id = 0;
	uint8_t pid_value = 0;
	uint8_t ver_value = 0;
	int i;
	BOOLEAN ret_value = 0XFF;

	for (i=0;i<3;i++) {
		sensor_id = GC2155_ReadReg(GC2155_PID_ADDR1) << 8;
		sensor_id |= GC2155_ReadReg(GC2155_PID_ADDR2);
		CMR_LOGI("%s sensor_id is %x\n", __func__, sensor_id);
		if(sensor_id == GC2155_SENSOR_ID) {
			SENSOR_PRINT("the main sensor is GC2155\n");
			return SENSOR_SUCCESS;
		}
	}

	return SENSOR_FAIL;
}

static void GC2155_set_shutter()
{
	uint32_t   shutter = 0;

	GC2155_WriteReg(0xfe,0x00);
	GC2155_WriteReg(0xb6,0x00);//AEC CLOSE
	shutter = (GC2155_ReadReg(0x03)<<8 )|( GC2155_ReadReg(0x04));

	shutter = shutter/2;

	if (shutter < 1) {
		shutter = 1;
	}
	GC2155_WriteReg(0x03, (shutter >> 8)&0xff);/* Shutter */
	GC2155_WriteReg(0x04, shutter&0xff);
}

SENSOR_REG_T GC2155_brightness_tab[][4]=
{
	{{0xfe , 0x02},{0xd5 , 0xc0},{0xfe , 0x00},{0xff , 0xff}},
	{{0xfe , 0x02},{0xd5 , 0xe0},{0xfe , 0x00},{0xff , 0xff}},
	{{0xfe , 0x02},{0xd5 , 0xf0},{0xfe , 0x00},{0xff , 0xff}},
	{{0xfe , 0x02},{0xd5 , 0x00},{0xfe , 0x00},{0xff , 0xff}},
	{{0xfe , 0x02},{0xd5 , 0x10},{0xfe , 0x00},{0xff , 0xff}},
	{{0xfe , 0x02},{0xd5 , 0x20},{0xfe , 0x00},{0xff , 0xff}},
	{{0xfe , 0x02},{0xd5 , 0x30},{0xfe , 0x00},{0xff , 0xff}}
};

static uint32_t set_brightness(uint32_t level)
{
	uint16_t i;
	SENSOR_REG_T* sensor_reg_ptr = (SENSOR_REG_T*)GC2155_brightness_tab[level];

	if (level>6)
		return 0;

	for (i = 0; (0xFF != sensor_reg_ptr[i].reg_addr) && (0xFF != sensor_reg_ptr[i].reg_value); i++) {
		GC2155_WriteReg(sensor_reg_ptr[i].reg_addr, sensor_reg_ptr[i].reg_value);
	}

	return 0;
}

SENSOR_REG_T GC2155_ev_tab[][4]=
{
	{{0xfe , 0x01},{0x13 , 0x08},{0xfe , 0x00},{0xff , 0xff}},
	{{0xfe , 0x01},{0x13 , 0x10},{0xfe , 0x00},{0xff , 0xff}},
	{{0xfe , 0x01},{0x13 , 0x1c},{0xfe , 0x00},{0xff , 0xff}},
	{{0xfe , 0x01},{0x13 , 0x2d},{0xfe , 0x00},{0xff , 0xff}},
	{{0xfe , 0x01},{0x13 , 0x35},{0xfe , 0x00},{0xff , 0xff}},
	{{0xfe , 0x01},{0x13 , 0x40},{0xfe , 0x00},{0xff , 0xff}},
	{{0xfe , 0x01},{0x13 , 0x50},{0xfe , 0x00},{0xff , 0xff}}
};

static uint32_t set_GC2155_ev(uint32_t level)
{
	uint16_t i;
	SENSOR_REG_T* sensor_reg_ptr = (SENSOR_REG_T*)GC2155_ev_tab[level];

	if (level>6)
		return 0;

	for (i = 0; (0xFF != sensor_reg_ptr[i].reg_addr) ||(0xFF != sensor_reg_ptr[i].reg_value) ; i++) {
		GC2155_WriteReg(sensor_reg_ptr[i].reg_addr, sensor_reg_ptr[i].reg_value);
	}

	return 0;
}

static uint32_t set_GC2155_anti_flicker(uint32_t param )
{
	shutter_flag = 0;

	switch (param) {
	case FLICKER_50HZ:
		GC2155_WriteReg(0x05 , 0x01);//hb
		GC2155_WriteReg(0x06 , 0x56);
		GC2155_WriteReg(0x07 , 0x00);//vb
		GC2155_WriteReg(0x08 , 0x32);
		GC2155_WriteReg(0xfe , 0x01);
		GC2155_WriteReg(0x25 , 0x00);//step
		GC2155_WriteReg(0x26 , 0xfa);
		GC2155_WriteReg(0x27 , 0x04);//level1
		GC2155_WriteReg(0x28 , 0xe2);
		GC2155_WriteReg(0x29 , 0x06);//level2
		GC2155_WriteReg(0x2a , 0xd6);
		GC2155_WriteReg(0x2b , 0x07);////level3
		GC2155_WriteReg(0x2c , 0xd0);
		GC2155_WriteReg(0x2d , 0x0b);//level4
		GC2155_WriteReg(0x2e , 0xb8);
		GC2155_WriteReg(0xfe , 0x00);
		break;
	case FLICKER_60HZ:
		GC2155_WriteReg(0x05 , 0x01);//hb
		GC2155_WriteReg(0x06 , 0x58);
		GC2155_WriteReg(0x07 , 0x00);//vb
		GC2155_WriteReg(0x08 , 0x32);
		GC2155_WriteReg(0xfe , 0x01);
		GC2155_WriteReg(0x25 , 0x00);//step
		GC2155_WriteReg(0x26 , 0xd0);
		GC2155_WriteReg(0x27 , 0x04);//level1
		GC2155_WriteReg(0x28 , 0xe0);
		GC2155_WriteReg(0x29 , 0x06);//level2
		GC2155_WriteReg(0x2a , 0x80);
		GC2155_WriteReg(0x2b , 0x08);//level3
		GC2155_WriteReg(0x2c , 0x20);
		GC2155_WriteReg(0x2d , 0x0b);//level4
		GC2155_WriteReg(0x2e , 0x60);
		GC2155_WriteReg(0xfe , 0x00);
		break;

	default:
		break;
	}

	return 0;
}

static uint32_t set_GC2155_video_mode(uint32_t mode)
{
	uint16_t i;
	SENSOR_REG_T* sensor_reg_ptr = PNULL;
	uint8_t tempregval = 0;

#ifdef GC2155_CMCC
	if (0 == mode) {
		GC2155_WriteReg(0xfe , 0x00);
		GC2155_WriteReg(0xf8 , 0x84);
		GC2155_WriteReg(0x05 , 0x01);//hb
		GC2155_WriteReg(0x06 , 0x56);
		GC2155_WriteReg(0x07 , 0x00);//vb
		GC2155_WriteReg(0x08 , 0x32);
		GC2155_WriteReg(0xfe , 0x01);
		GC2155_WriteReg(0x25 , 0x00);//step
		GC2155_WriteReg(0x26 , 0xfa);
		GC2155_WriteReg(0x27 , 0x04);//level1
		GC2155_WriteReg(0x28 , 0xe2);
		GC2155_WriteReg(0x29 , 0x06);//level2
		GC2155_WriteReg(0x2a , 0xd6);
		GC2155_WriteReg(0x2b , 0x07);////level3
		GC2155_WriteReg(0x2c , 0xd0);
		GC2155_WriteReg(0x2d , 0x0b);//level4
		GC2155_WriteReg(0x2e , 0xb8);
		GC2155_WriteReg(0xfe , 0x00);

		SENSOR_TRACE("2155 SENSOR: set_video_mode000000");
	} else {
		GC2155_WriteReg(0xfe , 0x00);
		GC2155_WriteReg(0xf8 , 0x85);
		GC2155_WriteReg(0x05 , 0x01);//hb
		GC2155_WriteReg(0x06 , 0x28);
		GC2155_WriteReg(0x07 , 0x00);//vb
		GC2155_WriteReg(0x08 , 0x32);
		GC2155_WriteReg(0xfe , 0x01);
		GC2155_WriteReg(0x25 , 0x01);//step
		GC2155_WriteReg(0x26 , 0x04);
		GC2155_WriteReg(0x27 , 0x04);//level1  24
		GC2155_WriteReg(0x28 , 0x10);
		GC2155_WriteReg(0x29 , 0x04);//level2 24
		GC2155_WriteReg(0x2a , 0x10);
		GC2155_WriteReg(0x2b , 0x04);////level3  24
		GC2155_WriteReg(0x2c , 0x10);
		GC2155_WriteReg(0x2d , 0x04);//level4  24
		GC2155_WriteReg(0x2e , 0x10);
		GC2155_WriteReg(0xfe , 0x00);

		SENSOR_TRACE("2155 SENSOR: set_video_mode2222222");
	}
#else
	if (0 == mode) {
		GC2155_WriteReg(0x05 , 0x01);//hb
		GC2155_WriteReg(0x06 , 0x56);
		GC2155_WriteReg(0x07 , 0x00);//vb
		GC2155_WriteReg(0x08 , 0x32);
		GC2155_WriteReg(0xfe , 0x01);
		GC2155_WriteReg(0x25 , 0x00);//step
		GC2155_WriteReg(0x26 , 0xfa);
		GC2155_WriteReg(0x27 , 0x04);//level1
		GC2155_WriteReg(0x28 , 0xe2);
		GC2155_WriteReg(0x29 , 0x06);//level2
		GC2155_WriteReg(0x2a , 0xd6);
		GC2155_WriteReg(0x2b , 0x07);////level3
		GC2155_WriteReg(0x2c , 0xd0);
		GC2155_WriteReg(0x2d , 0x0b);//level4
		GC2155_WriteReg(0x2e , 0xb8);
		GC2155_WriteReg(0xfe , 0x00);
		CMR_LOGI("2155 SENSOR: set_video_mode000000");
	} else {
		GC2155_WriteReg(0x05 , 0x01);//hb
		GC2155_WriteReg(0x06 , 0x1f);
		GC2155_WriteReg(0x07 , 0x00);//vb
		GC2155_WriteReg(0x08 , 0x32);
		GC2155_WriteReg(0xfe , 0x01);
		GC2155_WriteReg(0x25 , 0x01);//step
		GC2155_WriteReg(0x26 , 0x06);
		GC2155_WriteReg(0x27 , 0x04);//level1
		GC2155_WriteReg(0x28 , 0x18);
		GC2155_WriteReg(0x29 , 0x04);//level2
		GC2155_WriteReg(0x2a , 0x18);
		GC2155_WriteReg(0x2b , 0x04);////level3
		GC2155_WriteReg(0x2c , 0x18);
		GC2155_WriteReg(0x2d , 0x04);//level4
		GC2155_WriteReg(0x2e , 0x18);
		GC2155_WriteReg(0xfe , 0x00);

		CMR_LOGI("2155 SENSOR: set_video_mode2222222");
	}
#endif
	return 0;
}

SENSOR_REG_T GC2155_awb_tab[][6]=
{
	//Auto
	{
		{0xfe , 0x00},
		{0xfe , 0x00},
		{0xfe , 0x00},
		{0xfe , 0x00},
		{0x82 , 0xfe},
		{0xff , 0xff}
	},

	//Office
	{
		{0xfe , 0x00},
		{0x82 , 0xfc},
		{0xb3 , 0x50},
		{0xb4 , 0x40},
		{0xb5 , 0xa8},
		{0xff , 0xff}
	},

	//U30  //not use
	{
		{0xfe , 0x00},
		{0x82 , 0xfc},
		{0xb3 , 0x50},
		{0xb4 , 0x40},
		{0xb5 , 0xa8},
		{0xff , 0xff}
	},

	//CWF  //not use
	{
		{0xfe , 0x00},
		{0x82 , 0xfc},
		{0xb3 , 0x50},
		{0xb4 , 0x40},
		{0xb5 , 0xa8},
		{0xff , 0xff}
	},

	//HOME
	{
		{0xfe , 0x00},
		{0x82 , 0xfc},
		{0xb3 , 0xa0},
		{0xb4 , 0x45},
		{0xb5 , 0x40},
		{0xff , 0xff}
	},

	//SUN:
	{
		{0xfe , 0x00},
		{0x82 , 0xfc},
		{0xb3 , 0x78},
		{0xb4 , 0x40},
		{0xb5 , 0x50},
		{0xff , 0xff}
	},

	//CLOUD:
	{
		{0xfe , 0x00},
		{0x82 , 0xfc},
		{0xb3 , 0x58},
		{0xb4 , 0x40},
		{0xb5 , 0x50},
		{0xff , 0xff}
	}
};

static uint32_t set_GC2155_awb(uint32_t mode)
{
	uint8_t awb_en_value;
	uint16_t i;
	SENSOR_REG_T* sensor_reg_ptr = (SENSOR_REG_T*)GC2155_awb_tab[mode];

	if (mode>6)
		return 0;

	for (i = 0; (0xFF != sensor_reg_ptr[i].reg_addr) || (0xFF != sensor_reg_ptr[i].reg_value); i++) {
		GC2155_WriteReg(sensor_reg_ptr[i].reg_addr, sensor_reg_ptr[i].reg_value);
	}

	return 0;
}

SENSOR_REG_T GC2155_contrast_tab[][4]=
{
	{{0xfe,0x02}, {0xd3,0x28}, {0xfe,0x00}, {0xff,0xff}},
	{{0xfe,0x02}, {0xd3,0x30}, {0xfe,0x00}, {0xff,0xff}},
	{{0xfe,0x02}, {0xd3,0x38}, {0xfe,0x00}, {0xff,0xff}},
	{{0xfe,0x02}, {0xd3,0x40}, {0xfe,0x00}, {0xff,0xff}},
	{{0xfe,0x02}, {0xd3,0x48}, {0xfe,0x00}, {0xff,0xff}},
	{{0xfe,0x02}, {0xd3,0x50}, {0xfe,0x00}, {0xff,0xff}},
	{{0xfe,0x02}, {0xd3,0x58}, {0xfe,0x00}, {0xff,0xff}}
};

static uint32_t set_contrast(uint32_t level)
{
	uint16_t i;
	SENSOR_REG_T* sensor_reg_ptr;
	sensor_reg_ptr = (SENSOR_REG_T*)GC2155_contrast_tab[level];

	if (level>6)
		return 0;

	for (i = 0; (0xFF != sensor_reg_ptr[i].reg_addr) && (0xFF != sensor_reg_ptr[i].reg_value); i++) {
		GC2155_WriteReg(sensor_reg_ptr[i].reg_addr, sensor_reg_ptr[i].reg_value);
	}

	return 0;
}

static uint32_t set_preview_mode(uint32_t preview_mode)
{
	SENSOR_PRINT("set_preview_mode: preview_mode = %d\n", preview_mode);

	set_GC2155_anti_flicker(0);
	switch (preview_mode) {
	case DCAMERA_ENVIRONMENT_NORMAL:
		//YCP_saturation
		GC2155_WriteReg(0xfe , 0x02);
		GC2155_WriteReg(0xd1 , 0x28);
		GC2155_WriteReg(0xd2 , 0x28);

		GC2155_WriteReg(0xfe , 0x01);
		GC2155_WriteReg(0x3c , 0x40);
		GC2155_WriteReg(0xfe , 0x00);
		SENSOR_PRINT("set_preview_mode: DCAMERA_ENVIRONMENT_NORMAL\n");
		break;

	case 1://DCAMERA_ENVIRONMENT_NIGHT://1
		//YCP_saturation
		GC2155_WriteReg(0xfe , 0x02);
		GC2155_WriteReg(0xd1 , 0x28);
		GC2155_WriteReg(0xd2 , 0x28);

		GC2155_WriteReg(0xfe , 0x01);
		GC2155_WriteReg(0x3c , 0x60);
		GC2155_WriteReg(0xfe , 0x00);
		SENSOR_PRINT("set_preview_mode: DCAMERA_ENVIRONMENT_NIGHT\n");
		break;

	case 3://SENSOR_ENVIROMENT_PORTRAIT://3
		//YCP_saturation
		GC2155_WriteReg(0xfe , 0x02);
		GC2155_WriteReg(0xd1 , 0x34);
		GC2155_WriteReg(0xd2 , 0x34);

		GC2155_WriteReg(0xfe , 0x01);
		GC2155_WriteReg(0x3c , 0x40);
		GC2155_WriteReg(0xfe , 0x00);
		SENSOR_PRINT("set_preview_mode: SENSOR_ENVIROMENT_PORTRAIT\n");
		break;

	case 4://SENSOR_ENVIROMENT_LANDSCAPE://4
		//nightmode disable
		GC2155_WriteReg(0xfe , 0x02);
		GC2155_WriteReg(0xd1 , 0x4c);
		GC2155_WriteReg(0xd2 , 0x4c);

		GC2155_WriteReg(0xfe , 0x01);
		GC2155_WriteReg(0x3c , 0x40);
		GC2155_WriteReg(0xfe , 0x00);
		SENSOR_PRINT("set_preview_mode: SENSOR_ENVIROMENT_LANDSCAPE\n");
		break;

	case 2://SENSOR_ENVIROMENT_SPORTS://2
		//nightmode disable
		//YCP_saturation
		GC2155_WriteReg(0xfe , 0x02);
		GC2155_WriteReg(0xd1 , 0x40);
		GC2155_WriteReg(0xd2 , 0x40);

		GC2155_WriteReg(0xfe , 0x01);
		GC2155_WriteReg(0x3c , 0x40);
		GC2155_WriteReg(0xfe , 0x00);
		SENSOR_PRINT("set_preview_mode: SENSOR_ENVIROMENT_SPORTS\n");
		break;
	default:
		break;
	}

	SENSOR_Sleep(10);
	return 0;
}

SENSOR_REG_T GC2155_image_effect_tab[][2]=
{
	//Normal
	{{0x83 , 0xe0},{0xff , 0xff}},
	//BLACK&WHITE
	{{0x83 , 0x12},{0xff , 0xff}},
	//RED
	{{0x83 , 0x12},{0xff , 0xff}},
	//GREEN
	{{0x83 , 0x52},{0xff , 0xff}},
	//BLUE
	{{0x83 , 0x62},{0xff , 0xff}},
	//YELLOW
	{{0x83 , 0x12},{0xff , 0xff}},
	//NEGATIVE
	{{0x83 , 0x01},{0xff , 0xff}},
	//SEPIA
	{{0x83 , 0x82},{0xff , 0xff}}
};

static uint32_t set_image_effect(uint32_t effect_type)
{
	uint16_t i;
	SENSOR_REG_T* sensor_reg_ptr = (SENSOR_REG_T*)GC2155_image_effect_tab[effect_type];

	if (effect_type>7)
		return 0;

	for (i = 0; (0xFF != sensor_reg_ptr[i].reg_addr) || (0xFF != sensor_reg_ptr[i].reg_value) ; i++) {
		Sensor_WriteReg_8bits(sensor_reg_ptr[i].reg_addr, sensor_reg_ptr[i].reg_value);
	}

	return 0;
}

static uint32_t GC2155_After_Snapshot(uint32_t param)
{
	GC2155_WriteReg(0xfe,0x00);
	GC2155_WriteReg(0xb6,0x01);
	SENSOR_PRINT("GC2155_After_Snapshot param = %x \n",param);
	return 0;
}

static uint32_t GC2155_BeforeSnapshot(uint32_t sensor_snapshot_mode)
{
	sensor_snapshot_mode &= 0xffff;
	Sensor_SetMode(sensor_snapshot_mode);
	Sensor_SetMode_WaitDone();

	switch (sensor_snapshot_mode) {
	case SENSOR_MODE_PREVIEW_ONE:
		SENSOR_PRINT("Capture VGA Size");
		break;
	case SENSOR_MODE_SNAPSHOT_ONE_FIRST:
	case SENSOR_MODE_SNAPSHOT_ONE_SECOND:
		//GC2155_set_shutter();
		//usleep(100*1000);
		SENSOR_PRINT("Capture 1.3M&2M Size");
		break;
	default:
		break;
	}

	SENSOR_PRINT("SENSOR_GC2155: Before Snapshot");

	return 0;
}



