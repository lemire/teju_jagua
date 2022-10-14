// This file was auto-generated. DO NOT EDIT IT.

#include "ieee32_full.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef uint32_t suint_t;
typedef uint64_t duint_t;
typedef amaru_fields_32_t rep_t;

enum {
  is_compact       = 0,
  size             = 32,
  mantissa_size    = 23,
  bin_exponent_min = -149,
  dec_exponent_min = -45,
  shift            = 55
};

static struct {
  suint_t  const upper;
  suint_t  const lower;
} const multipliers[] = {
  { 0x0059aedf, 0xc10d727a }, // -149
  { 0x00b35dbf, 0x821ae4f4 }, // -148
  { 0x0166bb7f, 0x0435c9e8 }, // -147
  { 0x0047bf19, 0x673df52f }, // -146
  { 0x008f7e32, 0xce7bea5d }, // -145
  { 0x011efc65, 0x9cf7d4b9 }, // -144
  { 0x023df8cb, 0x39efa972 }, // -143
  { 0x0072cb5b, 0xd86321e4 }, // -142
  { 0x00e596b7, 0xb0c643c8 }, // -141
  { 0x01cb2d6f, 0x618c878f }, // -140
  { 0x005bd5e3, 0x13828183 }, // -139
  { 0x00b7abc6, 0x27050306 }, // -138
  { 0x016f578c, 0x4e0a060c }, // -137
  { 0x004977e8, 0xdc68679c }, // -136
  { 0x0092efd1, 0xb8d0cf38 }, // -135
  { 0x0125dfa3, 0x71a19e70 }, // -134
  { 0x024bbf46, 0xe3433cdf }, // -133
  { 0x00758ca7, 0xc70d7293 }, // -132
  { 0x00eb194f, 0x8e1ae526 }, // -131
  { 0x01d6329f, 0x1c35ca4c }, // -130
  { 0x005e0a1f, 0xd2712876 }, // -129
  { 0x00bc143f, 0xa4e250ec }, // -128
  { 0x0178287f, 0x49c4a1d7 }, // -127
  { 0x004b3b4c, 0xa85a86c5 }, // -126
  { 0x00967699, 0x50b50d89 }, // -125
  { 0x012ced32, 0xa16a1b12 }, // -124
  { 0x0259da65, 0x42d43624 }, // -123
  { 0x00785ee1, 0x0d5da46e }, // -122
  { 0x00f0bdc2, 0x1abb48dc }, // -121
  { 0x01e17b84, 0x357691b7 }, // -120
  { 0x00604be7, 0x3de4838b }, // -119
  { 0x00c097ce, 0x7bc90716 }, // -118
  { 0x01812f9c, 0xf7920e2c }, // -117
  { 0x004d0985, 0xcb1d3609 }, // -116
  { 0x009a130b, 0x963a6c12 }, // -115
  { 0x01342617, 0x2c74d823 }, // -114
  { 0x02684c2e, 0x58e9b046 }, // -113
  { 0x007b426f, 0xab61f00e }, // -112
  { 0x00f684df, 0x56c3e01c }, // -111
  { 0x01ed09be, 0xad87c038 }, // -110
  { 0x00629b8c, 0x891b2672 }, // -109
  { 0x00c53719, 0x12364ce4 }, // -108
  { 0x018a6e32, 0x246c99c7 }, // -107
  { 0x004ee2d6, 0xd415b85b }, // -106
  { 0x009dc5ad, 0xa82b70b6 }, // -105
  { 0x013b8b5b, 0x5056e16c }, // -104
  { 0x027716b6, 0xa0adc2d7 }, // -103
  { 0x007e37be, 0x2022c092 }, // -102
  { 0x00fc6f7c, 0x40458123 }, // -101
  { 0x01f8def8, 0x808b0246 }, // -100
  { 0x0064f964, 0xe68233a8 }, // -99
  { 0x00c9f2c9, 0xcd04674f }, // -98
  { 0x0193e593, 0x9a08ce9e }, // -97
  { 0x0050c783, 0xeb9b5c86 }, // -96
  { 0x00a18f07, 0xd736b90c }, // -95
  { 0x01431e0f, 0xae6d7218 }, // -94
  { 0x00409f9c, 0xbc7c4a05 }, // -93
  { 0x00813f39, 0x78f8940a }, // -92
  { 0x01027e72, 0xf1f12814 }, // -91
  { 0x0204fce5, 0xe3e25027 }, // -90
  { 0x006765c7, 0x93fa1008 }, // -89
  { 0x00cecb8f, 0x27f42010 }, // -88
  { 0x019d971e, 0x4fe8401f }, // -87
  { 0x0052b7d2, 0xdcc80cd3 }, // -86
  { 0x00a56fa5, 0xb99019a6 }, // -85
  { 0x014adf4b, 0x7320334c }, // -84
  { 0x00422ca8, 0xb0a00a43 }, // -83
  { 0x00845951, 0x61401485 }, // -82
  { 0x0108b2a2, 0xc280290a }, // -81
  { 0x02116545, 0x85005213 }, // -80
  { 0x0069e10d, 0xe76676d1 }, // -79
  { 0x00d3c21b, 0xcecceda2 }, // -78
  { 0x01a78437, 0x9d99db43 }, // -77
  { 0x0054b40b, 0x1f852bdb }, // -76
  { 0x00a96816, 0x3f0a57b5 }, // -75
  { 0x0152d02c, 0x7e14af69 }, // -74
  { 0x0043c33c, 0x19375649 }, // -73
  { 0x00878678, 0x326eac91 }, // -72
  { 0x010f0cf0, 0x64dd5921 }, // -71
  { 0x021e19e0, 0xc9bab241 }, // -70
  { 0x006c6b93, 0x5b8bbd41 }, // -69
  { 0x00d8d726, 0xb7177a81 }, // -68
  { 0x01b1ae4d, 0x6e2ef501 }, // -67
  { 0x0056bc75, 0xe2d63101 }, // -66
  { 0x00ad78eb, 0xc5ac6201 }, // -65
  { 0x015af1d7, 0x8b58c401 }, // -64
  { 0x00456391, 0x8244f401 }, // -63
  { 0x008ac723, 0x0489e801 }, // -62
  { 0x01158e46, 0x0913d001 }, // -61
  { 0x022b1c8c, 0x1227a001 }, // -60
  { 0x006f05b5, 0x9d3b2001 }, // -59
  { 0x00de0b6b, 0x3a764001 }, // -58
  { 0x01bc16d6, 0x74ec8001 }, // -57
  { 0x0058d15e, 0x17628001 }, // -56
  { 0x00b1a2bc, 0x2ec50001 }, // -55
  { 0x01634578, 0x5d8a0001 }, // -54
  { 0x00470de4, 0xdf820001 }, // -53
  { 0x008e1bc9, 0xbf040001 }, // -52
  { 0x011c3793, 0x7e080001 }, // -51
  { 0x02386f26, 0xfc100001 }, // -50
  { 0x0071afd4, 0x98d00001 }, // -49
  { 0x00e35fa9, 0x31a00001 }, // -48
  { 0x01c6bf52, 0x63400001 }, // -47
  { 0x005af310, 0x7a400001 }, // -46
  { 0x00b5e620, 0xf4800001 }, // -45
  { 0x016bcc41, 0xe9000001 }, // -44
  { 0x0048c273, 0x95000001 }, // -43
  { 0x009184e7, 0x2a000001 }, // -42
  { 0x012309ce, 0x54000001 }, // -41
  { 0x0246139c, 0xa8000001 }, // -40
  { 0x00746a52, 0x88000001 }, // -39
  { 0x00e8d4a5, 0x10000001 }, // -38
  { 0x01d1a94a, 0x20000001 }, // -37
  { 0x005d21db, 0xa0000001 }, // -36
  { 0x00ba43b7, 0x40000001 }, // -35
  { 0x0174876e, 0x80000001 }, // -34
  { 0x004a817c, 0x80000001 }, // -33
  { 0x009502f9, 0x00000001 }, // -32
  { 0x012a05f2, 0x00000001 }, // -31
  { 0x02540be4, 0x00000001 }, // -30
  { 0x00773594, 0x00000001 }, // -29
  { 0x00ee6b28, 0x00000001 }, // -28
  { 0x01dcd650, 0x00000001 }, // -27
  { 0x005f5e10, 0x00000001 }, // -26
  { 0x00bebc20, 0x00000001 }, // -25
  { 0x017d7840, 0x00000001 }, // -24
  { 0x004c4b40, 0x00000001 }, // -23
  { 0x00989680, 0x00000001 }, // -22
  { 0x01312d00, 0x00000001 }, // -21
  { 0x02625a00, 0x00000001 }, // -20
  { 0x007a1200, 0x00000001 }, // -19
  { 0x00f42400, 0x00000001 }, // -18
  { 0x01e84800, 0x00000001 }, // -17
  { 0x0061a800, 0x00000001 }, // -16
  { 0x00c35000, 0x00000001 }, // -15
  { 0x0186a000, 0x00000001 }, // -14
  { 0x004e2000, 0x00000001 }, // -13
  { 0x009c4000, 0x00000001 }, // -12
  { 0x01388000, 0x00000001 }, // -11
  { 0x02710000, 0x00000001 }, // -10
  { 0x007d0000, 0x00000001 }, // -9
  { 0x00fa0000, 0x00000001 }, // -8
  { 0x01f40000, 0x00000001 }, // -7
  { 0x00640000, 0x00000001 }, // -6
  { 0x00c80000, 0x00000001 }, // -5
  { 0x01900000, 0x00000001 }, // -4
  { 0x00500000, 0x00000001 }, // -3
  { 0x00a00000, 0x00000001 }, // -2
  { 0x01400000, 0x00000001 }, // -1
  { 0x00400000, 0x00000001 }, // 0
  { 0x00800000, 0x00000001 }, // 1
  { 0x01000000, 0x00000001 }, // 2
  { 0x02000000, 0x00000001 }, // 3
  { 0x00666666, 0x66666667 }, // 4
  { 0x00cccccc, 0xcccccccd }, // 5
  { 0x01999999, 0x9999999a }, // 6
  { 0x0051eb85, 0x1eb851ec }, // 7
  { 0x00a3d70a, 0x3d70a3d8 }, // 8
  { 0x0147ae14, 0x7ae147af }, // 9
  { 0x00418937, 0x4bc6a7f0 }, // 10
  { 0x0083126e, 0x978d4fe0 }, // 11
  { 0x010624dd, 0x2f1a9fbf }, // 12
  { 0x020c49ba, 0x5e353f7d }, // 13
  { 0x0068db8b, 0xac710cb3 }, // 14
  { 0x00d1b717, 0x58e21966 }, // 15
  { 0x01a36e2e, 0xb1c432cb }, // 16
  { 0x0053e2d6, 0x238da3c3 }, // 17
  { 0x00a7c5ac, 0x471b4785 }, // 18
  { 0x014f8b58, 0x8e368f09 }, // 19
  { 0x00431bde, 0x82d7b635 }, // 20
  { 0x008637bd, 0x05af6c6a }, // 21
  { 0x010c6f7a, 0x0b5ed8d4 }, // 22
  { 0x0218def4, 0x16bdb1a7 }, // 23
  { 0x006b5fca, 0x6af2bd22 }, // 24
  { 0x00d6bf94, 0xd5e57a43 }, // 25
  { 0x01ad7f29, 0xabcaf486 }, // 26
  { 0x0055e63b, 0x88c230e8 }, // 27
  { 0x00abcc77, 0x118461cf }, // 28
  { 0x015798ee, 0x2308c39e }, // 29
  { 0x0044b82f, 0xa09b5a53 }, // 30
  { 0x0089705f, 0x4136b4a6 }, // 31
  { 0x0112e0be, 0x826d694c }, // 32
  { 0x0225c17d, 0x04dad297 }, // 33
  { 0x006df37f, 0x675ef6eb }, // 34
  { 0x00dbe6fe, 0xcebdedd6 }, // 35
  { 0x01b7cdfd, 0x9d7bdbac }, // 36
  { 0x0057f5ff, 0x85e59256 }, // 37
  { 0x00afebff, 0x0bcb24ab }, // 38
  { 0x015fd7fe, 0x17964956 }, // 39
  { 0x00465e66, 0x04b7a845 }, // 40
  { 0x008cbccc, 0x096f5089 }, // 41
  { 0x01197998, 0x12dea112 }, // 42
  { 0x0232f330, 0x25bd4224 }, // 43
  { 0x00709709, 0xa125da08 }, // 44
  { 0x00e12e13, 0x424bb40f }, // 45
  { 0x01c25c26, 0x8497681d }, // 46
  { 0x005a126e, 0x1a84ae6d }, // 47
  { 0x00b424dc, 0x35095cd9 }, // 48
  { 0x016849b8, 0x6a12b9b1 }, // 49
  { 0x00480ebe, 0x7b9d5857 }, // 50
  { 0x00901d7c, 0xf73ab0ad }, // 51
  { 0x01203af9, 0xee75615a }, // 52
  { 0x024075f3, 0xdceac2b4 }, // 53
  { 0x00734aca, 0x5f6226f1 }, // 54
  { 0x00e69594, 0xbec44de2 }, // 55
  { 0x01cd2b29, 0x7d889bc3 }, // 56
  { 0x005c3bd5, 0x191b525b }, // 57
  { 0x00b877aa, 0x3236a4b5 }, // 58
  { 0x0170ef54, 0x646d4969 }, // 59
  { 0x0049c977, 0x47490eaf }, // 60
  { 0x009392ee, 0x8e921d5e }, // 61
  { 0x012725dd, 0x1d243abb }, // 62
  { 0x024e4bba, 0x3a487575 }, // 63
  { 0x00760f25, 0x3edb4ab1 }, // 64
  { 0x00ec1e4a, 0x7db69562 }, // 65
  { 0x01d83c94, 0xfb6d2ac4 }, // 66
  { 0x005e7284, 0x3249088e }, // 67
  { 0x00bce508, 0x6492111b }, // 68
  { 0x0179ca10, 0xc9242236 }, // 69
  { 0x004b8ed0, 0x283a6d3e }, // 70
  { 0x00971da0, 0x5074da7c }, // 71
  { 0x012e3b40, 0xa0e9b4f8 }, // 72
  { 0x025c7681, 0x41d369f0 }, // 73
  { 0x0078e480, 0x405d7b97 }, // 74
  { 0x00f1c900, 0x80baf72d }, // 75
  { 0x01e39201, 0x0175ee5a }, // 76
  { 0x0060b6cd, 0x004ac946 }, // 77
  { 0x00c16d9a, 0x0095928b }, // 78
  { 0x0182db34, 0x012b2515 }, // 79
  { 0x004d5f0a, 0x66a23a9e }, // 80
  { 0x009abe14, 0xcd44753c }, // 81
  { 0x01357c29, 0x9a88ea77 }, // 82
  { 0x026af853, 0x3511d4ee }, // 83
  { 0x007bcb43, 0xd769f763 }, // 84
  { 0x00f79687, 0xaed3eec6 }, // 85
  { 0x01ef2d0f, 0x5da7dd8b }, // 86
  { 0x00630903, 0x12bb2c4f }, // 87
  { 0x00c61206, 0x2576589e }, // 88
  { 0x018c240c, 0x4aecb13c }, // 89
  { 0x004f3a68, 0xdbc8f040 }, // 90
  { 0x009e74d1, 0xb791e07f }, // 91
  { 0x013ce9a3, 0x6f23c0fd }, // 92
  { 0x0279d346, 0xde4781fa }, // 93
  { 0x007ec3da, 0xf9418066 }, // 94
  { 0x00fd87b5, 0xf28300cb }, // 95
  { 0x01fb0f6b, 0xe5060195 }, // 96
  { 0x0065697b, 0xfa9acd1e }, // 97
  { 0x00cad2f7, 0xf5359a3c }, // 98
  { 0x0195a5ef, 0xea6b3477 }, // 99
  { 0x0051212f, 0xfbaf0a7f }, // 100
  { 0x00a2425f, 0xf75e14fd }, // 101
  { 0x014484bf, 0xeebc29f9 }, // 102
  { 0x0040e759, 0x9625a1ff }, // 103
  { 0x0081ceb3, 0x2c4b43fd }, // 104
};

static struct {
  suint_t const multiplier;
  suint_t const bound;
} const minverse[] = {
  { 0x00000001, 0xffffffff },
  { 0xcccccccd, 0x33333333 },
  { 0xc28f5c29, 0x0a3d70a3 },
  { 0x26e978d5, 0x020c49ba },
  { 0x3afb7e91, 0x0068db8b },
  { 0x0bcbe61d, 0x0014f8b5 },
  { 0x68c26139, 0x000431bd },
  { 0xae8d46a5, 0x0000d6bf },
  { 0x22e90e21, 0x00002af3 },
  { 0x3a2e9c6d, 0x00000897 },
  { 0x3ed61f49, 0x000001b7 },
  { 0x0c913975, 0x00000057 },
  { 0xcf503eb1, 0x00000011 },
  { 0xf6433fbd, 0x00000003 },
};

#ifdef __cplusplus
}
#endif

#define AMARU_FUNCTION amaru_binary_to_decimal_ieee32_full
#include "amaru/amaru.h"

#undef AMARU_FUNCTION
