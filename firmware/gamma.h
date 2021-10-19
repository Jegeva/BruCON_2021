/* 1024-step brightness table: gamma = 2.3 */ 

const uint8_t gamma_table[1024] = {
 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5, 5, 5, 5, 5, 6, 6, 6, 6, 6, 6, 6, 6, 7, 7, 7, 7, 7, 7, 7, 8, 8, 8, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 10, 10, 10, 10, 10, 10, 11, 11, 11, 11, 11, 11, 12, 12, 12, 12, 12, 13, 13, 13, 13, 13, 14, 14, 14, 14, 14, 15, 15, 15, 15, 15, 16, 16, 16, 16, 17, 17, 17, 17, 17, 18, 18, 18, 18, 19, 19, 19, 19, 20, 20, 20, 20, 21, 21, 21, 21, 22, 22, 22, 22, 23, 23, 23, 23, 24, 24, 24, 25, 25, 25, 25, 26, 26, 26, 27, 27, 27, 27, 28, 28, 28, 29, 29, 29, 30, 30, 30, 30, 31, 31, 31, 32, 32, 32, 33, 33, 33, 34, 34, 34, 35, 35, 35, 36, 36, 36, 37, 37, 38, 38, 38, 39, 39, 39, 40, 40, 40, 41, 41, 42, 42, 42, 43, 43, 43, 44, 44, 45, 45, 45, 46, 46, 47, 47, 47, 48, 48, 49, 49, 49, 50, 50, 51, 51, 52, 52, 52, 53, 53, 54, 54, 55, 55, 55, 56, 56, 57, 57, 58, 58, 59, 59, 60, 60, 60, 61, 61, 62, 62, 63, 63, 64, 64, 65, 65, 66, 66, 67, 67, 68, 68, 69, 69, 70, 70, 71, 71, 72, 72, 73, 73, 74, 74, 75, 75, 76, 76, 77, 77, 78, 79, 79, 80, 80, 81, 81, 82, 82, 83, 83, 84, 85, 85, 86, 86, 87, 87, 88, 89, 89, 90, 90, 91, 92, 92, 93, 93, 94, 94, 95, 96, 96, 97, 98, 98, 99, 99, 100, 101, 101, 102, 102, 103, 104, 104, 105, 106, 106, 107, 108, 108, 109, 109, 110, 111, 111, 112, 113, 113, 114, 115, 115, 116, 117, 117, 118, 119, 119, 120, 121, 122, 122, 123, 124, 124, 125, 126, 126, 127, 128, 129, 129, 130, 131, 131, 132, 133, 134, 134, 135, 136, 137, 137, 138, 139, 139, 140, 141, 142, 142, 143, 144, 145, 146, 146, 147, 148, 149, 149, 150, 151, 152, 153, 153, 154, 155, 156, 156, 157, 158, 159, 160, 160, 161, 162, 163, 164, 165, 165, 166, 167, 168, 169, 169, 170, 171, 172, 173, 174, 175, 175, 176, 177, 178, 179, 180, 181, 181, 182, 183, 184, 185, 186, 187, 187, 188, 189, 190, 191, 192, 193, 194, 195, 196, 196, 197, 198, 199, 200, 201, 202, 203, 204, 205, 206, 207, 207, 208, 209, 210, 211, 212, 213, 214, 215, 216, 217, 218, 219, 220, 221, 222, 223, 224, 225, 226, 227, 228, 229, 230, 231, 232, 233, 234, 235, 236, 237, 238, 239, 240, 241, 242, 243, 244, 245, 246, 247, 248, 249, 250, 251, 252, 253, 254, 255, 256, 257, 258, 259, 260, 261, 262, 264, 265, 266, 267, 268, 269, 270, 271, 272, 273, 274, 275, 277, 278, 279, 280, 281, 282, 283, 284, 285, 287, 288, 289, 290, 291, 292, 293, 294, 296, 297, 298, 299, 300, 301, 302, 304, 305, 306, 307, 308, 309, 311, 312, 313, 314, 315, 316, 318, 319, 320, 321, 322, 324, 325, 326, 327, 328, 330, 331, 332, 333, 335, 336, 337, 338, 339, 341, 342, 343, 344, 346, 347, 348, 349, 351, 352, 353, 354, 356, 357, 358, 360, 361, 362, 363, 365, 366, 367, 369, 370, 371, 372, 374, 375, 376, 378, 379, 380, 382, 383, 384, 386, 387, 388, 390, 391, 392, 394, 395, 396, 398, 399, 400, 402, 403, 404, 406, 407, 408, 410, 411, 413, 414, 415, 417, 418, 419, 421, 422, 424, 425, 426, 428, 429, 431, 432, 434, 435, 436, 438, 439, 441, 442, 443, 445, 446, 448, 449, 451, 452, 454, 455, 457, 458, 459, 461, 462, 464, 465, 467, 468, 470, 471, 473, 474, 476, 477, 479, 480, 482, 483, 485, 486, 488, 489, 491, 492, 494, 495, 497, 498, 500, 501, 503, 505, 506, 508, 509, 511, 512, 514, 515, 517, 519, 520, 522, 523, 525, 526, 528, 530, 531, 533, 534, 536, 538, 539, 541, 542, 544, 546, 547, 549, 550, 552, 554, 555, 557, 559, 560, 562, 563, 565, 567, 568, 570, 572, 573, 575, 577, 578, 580, 582, 583, 585, 587, 588, 590, 592, 593, 595, 597, 599, 600, 602, 604, 605, 607, 609, 611, 612, 614, 616, 617, 619, 621, 623, 624, 626, 628, 630, 631, 633, 635, 637, 638, 640, 642, 644, 645, 647, 649, 651, 653, 654, 656, 658, 660, 662, 663, 665, 667, 669, 671, 672, 674, 676, 678, 680, 681, 683, 685, 687, 689, 691, 692, 694, 696, 698, 700, 702, 704, 705, 707, 709, 711, 713, 715, 717, 719, 720, 722, 724, 726, 728, 730, 732, 734, 736, 738, 739, 741, 743, 745, 747, 749, 751, 753, 755, 757, 759, 761, 763, 765, 767, 769, 771, 772, 774, 776, 778, 780, 782, 784, 786, 788, 790, 792, 794, 796, 798, 800, 802, 804, 806, 808, 810, 812, 814, 816, 818, 820, 822, 824, 826, 829, 831, 833, 835, 837, 839, 841, 843, 845, 847, 849, 851, 853, 855, 857, 859, 862, 864, 866, 868, 870, 872, 874, 876, 878, 880, 883, 885, 887, 889, 891, 893, 895, 897, 900, 902, 904, 906, 908, 910, 913, 915, 917, 919, 921, 923, 926, 928, 930, 932, 934, 936, 939, 941, 943, 945, 947, 950, 952, 954, 956, 958, 961, 963, 965, 967, 970, 972, 974, 976, 979, 981, 983, 985, 988, 990, 992, 994, 997, 999, 1001, 1003, 1006, 1008, 1010, 1013, 1015, 1017, 1019, 1022, 1024,};