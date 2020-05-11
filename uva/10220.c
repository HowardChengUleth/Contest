/* @JUDGE_ID: 1102NT 10220 C "" */

#include <stdio.h>

int table[1001] = {
  1,
  1,
  2,
  6,
  6,
  3,
  9,
  9,
  9,
  27,
  27,
  36,
  27,
  27,
  45,
  45,
  63,
  63,
  54,
  45,
  54,
  63,
  72,
  99,
  81,
  72,
  81,
  108,
  90,
  126,
  117,
  135,
  108,
  144,
  144,
  144,
  171,
  153,
  108,
  189,
  189,
  144,
  189,
  180,
  216,
  207,
  216,
  225,
  234,
  225,
  216,
  198,
  279,
  279,
  261,
  279,
  333,
  270,
  288,
  324,
  288,
  315,
  306,
  333,
  324,
  351,
  351,
  369,
  342,
  351,
  459,
  423,
  432,
  315,
  378,
  432,
  441,
  432,
  423,
  441,
  450,
  486,
  477,
  486,
  477,
  414,
  495,
  495,
  531,
  549,
  585,
  594,
  540,
  513,
  549,
  585,
  648,
  648,
  639,
  648,
  648,
  639,
  630,
  621,
  702,
  648,
  639,
  594,
  666,
  657,
  657,
  693,
  765,
  666,
  648,
  648,
  729,
  738,
  756,
  774,
  783,
  774,
  738,
  765,
  747,
  855,
  801,
  873,
  828,
  819,
  864,
  927,
  873,
  846,
  846,
  819,
  864,
  927,
  954,
  981,
  954,
  963,
  1026,
  936,
  1017,
  972,
  1017,
  954,
  1008,
  1107,
  1053,
  990,
  990,
  999,
  1062,
  1053,
  1098,
  1125,
  1134,
  1089,
  1107,
  1134,
  1125,
  1134,
  1098,
  1116,
  1188,
  1089,
  1188,
  1188,
  1179,
  1242,
  1215,
  1206,
  1215,
  1233,
  1215,
  1278,
  1368,
  1260,
  1305,
  1323,
  1287,
  1314,
  1323,
  1260,
  1296,
  1377,
  1422,
  1386,
  1350,
  1422,
  1404,
  1458,
  1395,
  1413,
  1422,
  1512,
  1395,
  1413,
  1404,
  1350,
  1404,
  1476,
  1494,
  1530,
  1584,
  1647,
  1602,
  1530,
  1548,
  1512,
  1593,
  1530,
  1674,
  1674,
  1575,
  1638,
  1665,
  1575,
  1701,
  1692,
  1665,
  1701,
  1773,
  1728,
  1728,
  1656,
  1638,
  1701,
  1746,
  1665,
  1809,
  1728,
  1872,
  1746,
  1755,
  1890,
  1818,
  1818,
  1926,
  1890,
  1971,
  1980,
  1863,
  1944,
  1827,
  1872,
  1935,
  1881,
  1953,
  1926,
  1917,
  2025,
  1926,
  1899,
  1989,
  1953,
  1863,
  1971,
  1962,
  2079,
  2088,
  2061,
  1953,
  2106,
  2124,
  2043,
  2133,
  2106,
  2151,
  2169,
  2133,
  1980,
  2088,
  2187,
  2043,
  2313,
  2367,
  2223,
  2241,
  2367,
  2340,
  2349,
  2241,
  2304,
  2313,
  2385,
  2322,
  2385,
  2313,
  2331,
  2412,
  2385,
  2358,
  2511,
  2484,
  2394,
  2376,
  2448,
  2466,
  2376,
  2511,
  2493,
  2394,
  2529,
  2457,
  2466,
  2430,
  2412,
  2646,
  2556,
  2565,
  2502,
  2601,
  2556,
  2637,
  2574,
  2655,
  2583,
  2700,
  2628,
  2808,
  2637,
  2610,
  2700,
  2727,
  2682,
  2718,
  2754,
  2655,
  2772,
  2853,
  2862,
  2835,
  2790,
  2907,
  2817,
  2925,
  2817,
  2754,
  2961,
  2835,
  2844,
  2844,
  2916,
  2808,
  2844,
  2970,
  2934,
  2952,
  2862,
  3123,
  2844,
  2925,
  3069,
  2952,
  2979,
  2979,
  3087,
  3024,
  2997,
  3060,
  3060,
  3087,
  3114,
  3024,
  3033,
  3132,
  3204,
  3186,
  3213,
  3195,
  3258,
  3186,
  3159,
  3249,
  3186,
  3132,
  3312,
  3240,
  3195,
  3204,
  3357,
  3339,
  3375,
  3366,
  3204,
  3348,
  3366,
  3321,
  3384,
  3474,
  3312,
  3348,
  3312,
  3582,
  3429,
  3528,
  3627,
  3402,
  3339,
  3366,
  3483,
  3474,
  3600,
  3528,
  3609,
  3465,
  3483,
  3447,
  3573,
  3672,
  3600,
  3654,
  3708,
  3618,
  3726,
  3708,
  3564,
  3672,
  3807,
  3690,
  3627,
  3636,
  3780,
  3618,
  3753,
  3636,
  3762,
  3807,
  3798,
  3897,
  3771,
  3834,
  3879,
  3780,
  3780,
  4059,
  3807,
  3726,
  3852,
  3861,
  3753,
  4041,
  3969,
  3825,
  3978,
  4023,
  4185,
  3825,
  3888,
  4059,
  4203,
  4140,
  4059,
  4176,
  4176,
  4149,
  3969,
  4077,
  4131,
  4158,
  4221,
  4041,
  4194,
  4275,
  4140,
  4257,
  4140,
  4275,
  4338,
  4284,
  4266,
  4419,
  4428,
  4383,
  4194,
  4356,
  4365,
  4356,
  4059,
  4320,
  4266,
  4302,
  4383,
  4329,
  4536,
  4509,
  4419,
  4284,
  4410,
  4608,
  4302,
  4455,
  4464,
  4374,
  4644,
  4527,
  4608,
  4599,
  4446,
  4518,
  4536,
  4671,
  4644,
  4527,
  4581,
  4671,
  4707,
  4644,
  4554,
  4635,
  4761,
  4563,
  4716,
  4698,
  4779,
  4860,
  4752,
  4761,
  4680,
  4698,
  4842,
  4815,
  4860,
  4761,
  4968,
  4986,
  4941,
  4977,
  4950,
  4923,
  4896,
  4932,
  4851,
  4977,
  4797,
  4986,
  4869,
  5202,
  5067,
  5085,
  4941,
  4968,
  5076,
  5112,
  5274,
  5121,
  4923,
  5139,
  4860,
  5337,
  4950,
  5067,
  5193,
  5409,
  5166,
  5247,
  5346,
  5139,
  5274,
  5202,
  5373,
  5265,
  5391,
  5301,
  5337,
  5472,
  5319,
  5265,
  5427,
  5400,
  5427,
  5364,
  5346,
  5337,
  5454,
  5265,
  5400,
  5373,
  5499,
  5562,
  5382,
  5427,
  5292,
  5706,
  5562,
  5499,
  5526,
  5562,
  5652,
  5562,
  5679,
  5328,
  5616,
  5724,
  5787,
  5697,
  5634,
  5715,
  5634,
  5760,
  5787,
  5589,
  5742,
  5661,
  5499,
  5823,
  5931,
  5823,
  5877,
  5823,
  5787,
  5832,
  5841,
  5850,
  5886,
  5778,
  5841,
  5922,
  6039,
  5859,
  6003,
  5931,
  5958,
  6120,
  5895,
  5904,
  5904,
  6057,
  6012,
  5931,
  5967,
  6147,
  5859,
  5859,
  6237,
  6210,
  6336,
  6057,
  6291,
  6021,
  6291,
  6021,
  6219,
  6156,
  6282,
  6012,
  6372,
  6300,
  6399,
  6372,
  6282,
  6246,
  6291,
  6318,
  6219,
  6453,
  6192,
  6516,
  6408,
  6444,
  6147,
  6417,
  6381,
  6327,
  6498,
  6462,
  6453,
  6363,
  6489,
  6417,
  6480,
  6615,
  6453,
  6561,
  6831,
  6444,
  6444,
  6444,
  6417,
  6534,
  6687,
  6786,
  6651,
  6687,
  6615,
  6777,
  6795,
  6876,
  6966,
  6957,
  6669,
  6822,
  6831,
  6696,
  6741,
  6957,
  6885,
  6723,
  6777,
  6741,
  6849,
  6840,
  6678,
  6849,
  6831,
  6957,
  7065,
  7056,
  7092,
  6966,
  6876,
  7083,
  6912,
  7191,
  7101,
  7020,
  7191,
  7164,
  6957,
  7110,
  7047,
  7092,
  6957,
  7083,
  7182,
  7407,
  7065,
  7254,
  7137,
  7254,
  7155,
  7155,
  7128,
  7515,
  7317,
  7029,
  7461,
  7263,
  7218,
  7425,
  7317,
  7326,
  7362,
  7641,
  7452,
  7263,
  7380,
  7416,
  7263,
  7398,
  7524,
  7533,
  7308,
  7524,
  7452,
  7488,
  7434,
  7461,
  7488,
  7353,
  7731,
  7470,
  7641,
  7461,
  7272,
  7542,
  7569,
  7713,
  7704,
  7767,
  7551,
  7776,
  7596,
  7722,
  7875,
  7659,
  7686,
  7659,
  7677,
  7776,
  7686,
  7983,
  7857,
  7938,
  8001,
  7839,
  7965,
  7929,
  8109,
  7812,
  7938,
  8001,
  8001,
  8091,
  8100,
  7884,
  8001,
  7929,
  7965,
  7947,
  8127,
  7947,
  7965,
  7812,
  8028,
  8217,
  8208,
  8181,
  8280,
  8028,
  8037,
  8298,
  8172,
  8424,
  8127,
  8235,
  8001,
  8163,
  8307,
  8496,
  8181,
  8172,
  8415,
  8343,
  8424,
  8217,
  8361,
  8397,
  8433,
  8307,
  8649,
  8352,
  8370,
  8514,
  8514,
  8082,
  8568,
  8316,
  8370,
  8478,
  8649,
  8658,
  8541,
  8550,
  8388,
  8622,
  8586,
  8586,
  8595,
  8649,
  8550,
  8694,
  8685,
  8694,
  8676,
  8685,
  8793,
  8667,
  8802,
  8757,
  8901,
  8937,
  8694,
  8946,
  8820,
  8829,
  9000,
  9009,
  9009,
  8955,
  8811,
  8883,
  8928,
  8928,
  8982,
  8757,
  8901,
  9090,
  8973,
  9117,
  8946,
  8838,
  9099,
  9189,
  9099,
  9072,
  8811,
  9054,
  9054,
  8865,
  9063,
  9126,
  9189,
  9135,
  9045,
  9216,
  9090,
  9324,
  9162,
  9324,
  9081,
  9045,
  9414,
  9153,
  9369,
  9333,
  9486,
  9126,
  9081,
  9477,
  9198,
  9468,
  9504,
  9603,
  9360,
  9396,
  9477,
  9423,
  9522,
  9450,
  9702,
  9432,
  9594,
  9558,
  9630,
  9549,
  9477,
  9675,
  9549,
  9702,
  9540,
  9738,
  9666,
  9729,
  9801,
  9657,
  9810,
  9729,
  9513,
  9612,
  9774,
  9684,
  9702,
  9675,
  9504,
  9792,
  9684,
  9639,
  10035,
  9855,
  9774,
  9783,
  9990,
  9999,
  9954,
  9945,
  9981,
  9954,
  9999,
  9900,
  10071,
  10125,
  10080,
  9828,
  10116,
  10143,
  10089,
  10134,
  9711,
  10053,
  10314,
  10035,
  10278,
  9990,
  10053,
  10179,
  10413,
  10134,
  10341,
  10458,
  9990,
  10296,
  10053,
  10296,
  10206,
  10287,
  10332,
  10467,
  10287,
  10296,
  10251,
  10584,
  10395,
  10233,
  10368,
  10287,
  10539,
  10539
};

int main(void)
{
  int n;
  while (scanf("%d", &n) == 1) {
    printf("%d\n", table[n]);
  }
  return 0;
}
