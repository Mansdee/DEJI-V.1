#ifndef EYE_EMOT_H
#define EYE_EMOT_H
#include <Arduino.h>
#include <pgmspace.h>

// ================== INCLUDE FRAME SET ==================
#include "frames/eye1.h"        
#include "frames/eye2.h"        
#include "frames/tidur.h"
#include "frames/mengejek.h"
#include "frames/evil_laugh.h"
#include "frames/kiss.h"
#include "frames/tanjiro.h"
#include "frames/spido.h"
#include "frames/game.h"
#include "frames/rising_star.h"
#include "frames/makan.h"
#include "frames/navigation.h"  

// ================== DIMENSI FRAME ==================
#define FRAME_WIDTH 128
#define FRAME_HEIGHT 64

// ================== JUMLAH FRAME PER SET ==================
#define EYE1_FRAME_COUNT 63
#define EYE2_FRAME_COUNT 116
#define TIDUR_FRAME_COUNT 188
#define MENGEJEK_COUNT 86
#define EVIL_COUNT 81
#define KISS_COUNT 109
#define TANJIRO_COUNT 69
#define SPIDO_COUNT 229
#define GAME_COUNT 279
#define RISING_COUNT 197
#define MAKAN_COUNT 281
#define NAVIGATION_ICON_COUNT 7

// ================== INDEKS AWAL PER SET ==================
enum AnimationStartIndex {
   EYE1_START_INDEX = 0,
   EYE2_START_INDEX = EYE1_FRAME_COUNT, 
   TIDUR_START_INDEX = EYE2_START_INDEX + EYE2_FRAME_COUNT, 
   MENGEJEK_START_INDEX = TIDUR_START_INDEX + TIDUR_FRAME_COUNT,
   EVIL_LAUGH_START_INDEX = MENGEJEK_START_INDEX + MENGEJEK_COUNT,
   KISS_V2_START_INDEX = EVIL_LAUGH_START_INDEX + EVIL_COUNT,
   TANJIRO_START_INDEX = KISS_V2_START_INDEX + KISS_COUNT,
   SPIDO_START_INDEX = TANJIRO_START_INDEX + TANJIRO_COUNT,
   GAME_START_INDEX = SPIDO_START_INDEX + SPIDO_COUNT,
   RISING_START_INDEX = GAME_START_INDEX + GAME_COUNT,
   MAKAN_START_INDEX = RISING_START_INDEX + RISING_COUNT,
   NAVIGATION_START_INDEX = MAKAN_START_INDEX + MAKAN_COUNT
};

// ================== TOTAL FRAME ==================
// Total semua frame digabung: 63+116+188+86+81+109+69+7 = 719
#define TOTAL_FRAMES (EYE1_FRAME_COUNT + EYE2_FRAME_COUNT + TIDUR_FRAME_COUNT + MENGEJEK_COUNT + EVIL_COUNT + KISS_COUNT + TANJIRO_COUNT + SPIDO_COUNT + GAME_COUNT + RISING_COUNT + MAKAN_COUNT + NAVIGATION_ICON_COUNT)

// ================== ARRAY MASTER FRAMES ==================
const uint8_t* const frames[TOTAL_FRAMES] = {
  // -------- eye1.h (63 frames) --------
  eye_1eye_400001, eye_1eye_400002, eye_1eye_400003, eye_1eye_400004, eye_1eye_400005, eye_1eye_400006, eye_1eye_400007, eye_1eye_400008, eye_1eye_400009, eye_1eye_400012, eye_1eye_400013, eye_1eye_400014, eye_1eye_400015, eye_1eye_400016, eye_1eye_400017, eye_1eye_400018, eye_1eye_400019, eye_1eye_400020, eye_1eye_400023, eye_1eye_400024, eye_1eye_400025, eye_1eye_400026, eye_1eye_400027, eye_1eye_400028, eye_1eye_400029, eye_1eye_400030, eye_1eye_400031, eye_1eye_400034, eye_1eye_400035, eye_1eye_400036, eye_1eye_400037, eye_1eye_400038, eye_1eye_400039, eye_1eye_400040, eye_1eye_400041, eye_1eye_400042, eye_1eye_400045, eye_1eye_400046, eye_1eye_400047, eye_1eye_400048, eye_1eye_400049, eye_1eye_400050, eye_1eye_400051, eye_1eye_400052, eye_1eye_400053, eye_1eye_400056, eye_1eye_400057, eye_1eye_400058, eye_1eye_400059, eye_1eye_400060, eye_1eye_400061, eye_1eye_400062, eye_1eye_400063, eye_1eye_400064, eye_1eye_400067, eye_1eye_400068, eye_1eye_400069, eye_1eye_400070, eye_1eye_400071, eye_1eye_400072, eye_1eye_400073, eye_1eye_400074, eye_1eye_400075,

  // -------- eye2.h (116 frames) --------
  eye_2eye_200001, eye_2eye_200002, eye_2eye_200003, eye_2eye_200004, eye_2eye_200005, eye_2eye_200006, eye_2eye_200007, eye_2eye_200008, eye_2eye_200009, eye_2eye_200010, eye_2eye_200011, eye_2eye_200012, eye_2eye_200013, eye_2eye_200014, eye_2eye_200015, eye_2eye_200016, eye_2eye_200017, eye_2eye_200018, eye_2eye_200019, eye_2eye_200020, eye_2eye_200021, eye_2eye_200022, eye_2eye_200023, eye_2eye_200024, eye_2eye_200025, eye_2eye_200026, eye_2eye_200027, eye_2eye_200028, eye_2eye_200029, eye_2eye_200030, eye_2eye_200031, eye_2eye_200032, eye_2eye_200033, eye_2eye_200034, eye_2eye_200035, eye_2eye_200036, eye_2eye_200037, eye_2eye_200038, eye_2eye_200039, eye_2eye_200040, eye_2eye_200041, eye_2eye_200042, eye_2eye_200043, eye_2eye_200044, eye_2eye_200045, eye_2eye_200046, eye_2eye_200047, eye_2eye_200048, eye_2eye_200049, eye_2eye_200050, eye_2eye_200051, eye_2eye_200052, eye_2eye_200053, eye_2eye_200054, eye_2eye_200055, eye_2eye_200056, eye_2eye_200057, eye_2eye_200058, eye_2eye_200059, eye_2eye_200060, eye_2eye_200061, eye_2eye_200062, eye_2eye_200063, eye_2eye_200064, eye_2eye_200065, eye_2eye_200066, eye_2eye_200067, eye_2eye_200068, eye_2eye_200069, eye_2eye_200070, eye_2eye_200071, eye_2eye_200072, eye_2eye_200073, eye_2eye_200074, eye_2eye_200075, eye_2eye_200076, eye_2eye_200077, eye_2eye_200078, eye_2eye_200079, eye_2eye_200080, eye_2eye_200081, eye_2eye_200082, eye_2eye_200083, eye_2eye_200084, eye_2eye_200085, eye_2eye_200086, eye_2eye_200087, eye_2eye_200088, eye_2eye_200089, eye_2eye_200090, eye_2eye_200091, eye_2eye_200092, eye_2eye_200093, eye_2eye_200094, eye_2eye_200095, eye_2eye_200096, eye_2eye_200097, eye_2eye_200098, eye_2eye_200099, eye_2eye_200100, eye_2eye_200101, eye_2eye_200102, eye_2eye_200103, eye_2eye_200104, eye_2eye_200105, eye_2eye_200106, eye_2eye_200107, eye_2eye_200108, eye_2eye_200109, eye_2eye_200110, eye_2eye_200111, eye_2eye_200112, eye_2eye_200113, eye_2eye_200114, eye_2eye_200115, eye_2eye_200116,

  // -------- tidur.h (188 frames) --------
  mengorokframe00001, mengorokframe00002, mengorokframe00003, mengorokframe00004, mengorokframe00005, mengorokframe00006, mengorokframe00007, mengorokframe00008, mengorokframe00009, mengorokframe00010, mengorokframe00011, mengorokframe00012, mengorokframe00013, mengorokframe00014, mengorokframe00015, mengorokframe00016, mengorokframe00017, mengorokframe00018, mengorokframe00019, mengorokframe00020, mengorokframe00021, mengorokframe00022, mengorokframe00023, mengorokframe00024, mengorokframe00025, mengorokframe00026, mengorokframe00027, mengorokframe00028, mengorokframe00029, mengorokframe00030, mengorokframe00031, mengorokframe00032, mengorokframe00033, mengorokframe00034, mengorokframe00035, mengorokframe00036, mengorokframe00037, mengorokframe00038, mengorokframe00039, mengorokframe00040, mengorokframe00041, mengorokframe00042, mengorokframe00043, mengorokframe00044, mengorokframe00045, mengorokframe00046, mengorokframe00047, mengorokframe00048, mengorokframe00049, mengorokframe00050, mengorokframe00051, mengorokframe00052, mengorokframe00053, mengorokframe00054, mengorokframe00055, mengorokframe00056, mengorokframe00057, mengorokframe00058, mengorokframe00059, mengorokframe00060, mengorokframe00061, mengorokframe00062, mengorokframe00063, mengorokframe00064, mengorokframe00065, mengorokframe00066, mengorokframe00067, mengorokframe00068, mengorokframe00069, mengorokframe00070, mengorokframe00071, mengorokframe00072, mengorokframe00073, mengorokframe00074, mengorokframe00075, mengorokframe00076, mengorokframe00077, mengorokframe00078, mengorokframe00079, mengorokframe00080, mengorokframe00081, mengorokframe00082, mengorokframe00083, mengorokframe00084, mengorokframe00085, mengorokframe00086, mengorokframe00087, mengorokframe00088, mengorokframe00089, mengorokframe00090, mengorokframe00091, mengorokframe00092, mengorokframe00093, mengorokframe00094, mengorokframe00095, mengorokframe00096, mengorokframe00097, mengorokframe00098, mengorokframe00099, mengorokframe00100, mengorokframe00101, mengorokframe00102, mengorokframe00103, mengorokframe00104, mengorokframe00105, mengorokframe00106, mengorokframe00107, mengorokframe00108, mengorokframe00109, mengorokframe00110, mengorokframe00111, mengorokframe00112, mengorokframe00113, mengorokframe00114, mengorokframe00115, mengorokframe00116, mengorokframe00117, mengorokframe00118, mengorokframe00119, mengorokframe00120, mengorokframe00121, mengorokframe00122, mengorokframe00123, mengorokframe00124, mengorokframe00125, mengorokframe00126, mengorokframe00127, mengorokframe00128, mengorokframe00129, mengorokframe00130, mengorokframe00131, mengorokframe00132, mengorokframe00133, mengorokframe00134, mengorokframe00135, mengorokframe00136, mengorokframe00137, mengorokframe00138, mengorokframe00139, mengorokframe00140, mengorokframe00141, mengorokframe00142, mengorokframe00143, mengorokframe00144, mengorokframe00145, mengorokframe00146, mengorokframe00147, mengorokframe00148, mengorokframe00149, mengorokframe00150, mengorokframe00151, mengorokframe00152, mengorokframe00153, mengorokframe00154, mengorokframe00155, mengorokframe00156, mengorokframe00157, mengorokframe00158, mengorokframe00159, mengorokframe00160, mengorokframe00161, mengorokframe00162, mengorokframe00163, mengorokframe00164, mengorokframe00165, mengorokframe00166, mengorokframe00167, mengorokframe00168, mengorokframe00169, mengorokframe00170, mengorokframe00171, mengorokframe00172, mengorokframe00173, mengorokframe00174, mengorokframe00175, mengorokframe00176, mengorokframe00177, mengorokframe00178, mengorokframe00179, mengorokframe00180, mengorokframe00181, mengorokframe00182, mengorokframe00183, mengorokframe00184, mengorokframe00185, mengorokframe00186, mengorokframe00187, mengorokframe00188,

  // -------- mengejek.h (86 frames) --------
  mengejekframe00001, mengejekframe00002, mengejekframe00003, mengejekframe00004, mengejekframe00005, mengejekframe00006, mengejekframe00007, mengejekframe00008, mengejekframe00009, mengejekframe00010, mengejekframe00011, mengejekframe00012, mengejekframe00013, mengejekframe00014, mengejekframe00015, mengejekframe00016, mengejekframe00017, mengejekframe00018, mengejekframe00019, mengejekframe00020, mengejekframe00021, mengejekframe00022, mengejekframe00023, mengejekframe00024, mengejekframe00025, mengejekframe00026, mengejekframe00027, mengejekframe00028, mengejekframe00029, mengejekframe00030, mengejekframe00031, mengejekframe00032, mengejekframe00033, mengejekframe00034, mengejekframe00035, mengejekframe00036, mengejekframe00037, mengejekframe00038, mengejekframe00039, mengejekframe00040, mengejekframe00041, mengejekframe00042, mengejekframe00043, mengejekframe00044, mengejekframe00045, mengejekframe00046, mengejekframe00047, mengejekframe00048, mengejekframe00049, mengejekframe00050, mengejekframe00051, mengejekframe00052, mengejekframe00053, mengejekframe00054, mengejekframe00055, mengejekframe00056, mengejekframe00057, mengejekframe00058, mengejekframe00059, mengejekframe00060, mengejekframe00061, mengejekframe00062, mengejekframe00063, mengejekframe00064, mengejekframe00065, mengejekframe00066, mengejekframe00067, mengejekframe00068, mengejekframe00069, mengejekframe00070, mengejekframe00071, mengejekframe00072, mengejekframe00073, mengejekframe00074, mengejekframe00075, mengejekframe00076, mengejekframe00077, mengejekframe00078, mengejekframe00079, mengejekframe00080, mengejekframe00081, mengejekframe00082, mengejekframe00083, mengejekframe00084, mengejekframe00085, mengejekframe00086,

  // -------- evil_laugh.h (81 frames) --------
  evil_laughframe00004, evil_laughframe00005, evil_laughframe00006, evil_laughframe00007, evil_laughframe00008, evil_laughframe00009, evil_laughframe00010, evil_laughframe00011, evil_laughframe00012, evil_laughframe00013, evil_laughframe00014, evil_laughframe00015, evil_laughframe00016, evil_laughframe00017, evil_laughframe00018, evil_laughframe00019, evil_laughframe00020, evil_laughframe00021, evil_laughframe00022, evil_laughframe00023, evil_laughframe00024, evil_laughframe00025, evil_laughframe00026, evil_laughframe00027, evil_laughframe00028, evil_laughframe00029, evil_laughframe00030, evil_laughframe00031, evil_laughframe00032, evil_laughframe00033, evil_laughframe00034, evil_laughframe00035, evil_laughframe00036, evil_laughframe00037, evil_laughframe00038, evil_laughframe00039, evil_laughframe00040, evil_laughframe00041, evil_laughframe00042, evil_laughframe00043, evil_laughframe00044, evil_laughframe00045, evil_laughframe00046, evil_laughframe00047, evil_laughframe00048, evil_laughframe00049, evil_laughframe00050, evil_laughframe00051, evil_laughframe00052, evil_laughframe00053, evil_laughframe00054, evil_laughframe00055, evil_laughframe00056, evil_laughframe00057, evil_laughframe00058, evil_laughframe00059, evil_laughframe00060, evil_laughframe00061, evil_laughframe00062, evil_laughframe00063, evil_laughframe00064, evil_laughframe00065, evil_laughframe00066, evil_laughframe00067, evil_laughframe00068, evil_laughframe00069, evil_laughframe00070, evil_laughframe00071, evil_laughframe00072, evil_laughframe00073, evil_laughframe00074, evil_laughframe00075, evil_laughframe00076, evil_laughframe00077, evil_laughframe00078, evil_laughframe00079, evil_laughframe00080, evil_laughframe00081, evil_laughframe00082, evil_laughframe00083, evil_laughframe00084,

  // -------- kiss.h (109 frames) --------
  kissframe00001, kissframe00002, kissframe00003, kissframe00004, kissframe00005, kissframe00006, kissframe00007, kissframe00008, kissframe00009, kissframe00010, kissframe00011, kissframe00012, kissframe00013, kissframe00014, kissframe00015, kissframe00016, kissframe00017, kissframe00018, kissframe00019, kissframe00020, kissframe00021, kissframe00022, kissframe00023, kissframe00024, kissframe00025, kissframe00026, kissframe00027, kissframe00028, kissframe00029, kissframe00030, kissframe00031, kissframe00032, kissframe00033, kissframe00034, kissframe00035, kissframe00036, kissframe00037, kissframe00038, kissframe00039, kissframe00040, kissframe00041, kissframe00042, kissframe00043, kissframe00044, kissframe00045, kissframe00046, kissframe00047, kissframe00048, kissframe00049, kissframe00050, kissframe00051, kissframe00052, kissframe00053, kissframe00054, kissframe00055, kissframe00056, kissframe00057, kissframe00058, kissframe00059, kissframe00060, kissframe00061, kissframe00062, kissframe00063, kissframe00064, kissframe00065, kissframe00066, kissframe00067, kissframe00068, kissframe00069, kissframe00070, kissframe00071, kissframe00072, kissframe00073, kissframe00074, kissframe00075, kissframe00076, kissframe00077, kissframe00078, kissframe00079, kissframe00080, kissframe00081, kissframe00082, kissframe00083, kissframe00084, kissframe00085, kissframe00086, kissframe00087, kissframe00088, kissframe00089, kissframe00090, kissframe00091, kissframe00092, kissframe00093, kissframe00094, kissframe00095, kissframe00096, kissframe00097, kissframe00098, kissframe00099, kissframe00100, kissframe00101, kissframe00102, kissframe00103, kissframe00104, kissframe00105, kissframe00106, kissframe00107, kissframe00108, kissframe00109,

  // -------- tanjiro.h (69 frames) --------
  tanjiroframe00001, tanjiroframe00002, tanjiroframe00003, tanjiroframe00004, tanjiroframe00005, tanjiroframe00006, tanjiroframe00007, tanjiroframe00008, tanjiroframe00009, tanjiroframe00010, tanjiroframe00011, tanjiroframe00012, tanjiroframe00013, tanjiroframe00014, tanjiroframe00015, tanjiroframe00016, tanjiroframe00017, tanjiroframe00018, tanjiroframe00019, tanjiroframe00020, tanjiroframe00021, tanjiroframe00022, tanjiroframe00023, tanjiroframe00024, tanjiroframe00025, tanjiroframe00026, tanjiroframe00027, tanjiroframe00028, tanjiroframe00029, tanjiroframe00030, tanjiroframe00031, tanjiroframe00032, tanjiroframe00033, tanjiroframe00034, tanjiroframe00035, tanjiroframe00036, tanjiroframe00037, tanjiroframe00038, tanjiroframe00039, tanjiroframe00040, tanjiroframe00041, tanjiroframe00042, tanjiroframe00043, tanjiroframe00044, tanjiroframe00045, tanjiroframe00046, tanjiroframe00047, tanjiroframe00048, tanjiroframe00049, tanjiroframe00050, tanjiroframe00051, tanjiroframe00052, tanjiroframe00053, tanjiroframe00054, tanjiroframe00055, tanjiroframe00056, tanjiroframe00057, tanjiroframe00058, tanjiroframe00059, tanjiroframe00060, tanjiroframe00061, tanjiroframe00062, tanjiroframe00063, tanjiroframe00064, tanjiroframe00065, tanjiroframe00066, tanjiroframe00067, tanjiroframe00068, tanjiroframe00069,

  // -------- spido.h (229 frames) --------
  spidoframe00001, spidoframe00002, spidoframe00003, spidoframe00004, spidoframe00005, spidoframe00006, spidoframe00007, spidoframe00008, spidoframe00009, spidoframe00010,
  spidoframe00011, spidoframe00012, spidoframe00013, spidoframe00014, spidoframe00015, spidoframe00016, spidoframe00017, spidoframe00018, spidoframe00019, spidoframe00020,
  spidoframe00021, spidoframe00022, spidoframe00023, spidoframe00024, spidoframe00025, spidoframe00026, spidoframe00027, spidoframe00028, spidoframe00029, spidoframe00030,
  spidoframe00031, spidoframe00032, spidoframe00033, spidoframe00034, spidoframe00035, spidoframe00036, spidoframe00037, spidoframe00038, spidoframe00039, spidoframe00040,
  spidoframe00041, spidoframe00042, spidoframe00043, spidoframe00044, spidoframe00045, spidoframe00046, spidoframe00047, spidoframe00048, spidoframe00049, spidoframe00050,
  spidoframe00051, spidoframe00052, spidoframe00053, spidoframe00054, spidoframe00055, spidoframe00056, spidoframe00057, spidoframe00058, spidoframe00059, spidoframe00060,
  spidoframe00061, spidoframe00062, spidoframe00063, spidoframe00064, spidoframe00065, spidoframe00066, spidoframe00067, spidoframe00068, spidoframe00069, spidoframe00070,
  spidoframe00071, spidoframe00072, spidoframe00073, spidoframe00074, spidoframe00075, spidoframe00076, spidoframe00077, spidoframe00078, spidoframe00079, spidoframe00080,
  spidoframe00081, spidoframe00082, spidoframe00083, spidoframe00084, spidoframe00085, spidoframe00086, spidoframe00087, spidoframe00088, spidoframe00089, spidoframe00090,
  spidoframe00091, spidoframe00092, spidoframe00093, spidoframe00094, spidoframe00095, spidoframe00096, spidoframe00097, spidoframe00098, spidoframe00099, spidoframe00100,
  spidoframe00101, spidoframe00102, spidoframe00103, spidoframe00104, spidoframe00105, spidoframe00106, spidoframe00107, spidoframe00108, spidoframe00109, spidoframe00110,
  spidoframe00111, spidoframe00112, spidoframe00113, spidoframe00114, spidoframe00115, spidoframe00116, spidoframe00117, spidoframe00118, spidoframe00119, spidoframe00120,
  spidoframe00121, spidoframe00122, spidoframe00123, spidoframe00124, spidoframe00125, spidoframe00126, spidoframe00127, spidoframe00128, spidoframe00129, spidoframe00130,
  spidoframe00131, spidoframe00132, spidoframe00133, spidoframe00134, spidoframe00135, spidoframe00136, spidoframe00137, spidoframe00138, spidoframe00139, spidoframe00140,
  spidoframe00141, spidoframe00142, spidoframe00143, spidoframe00144, spidoframe00145, spidoframe00146, spidoframe00147, spidoframe00148, spidoframe00149, spidoframe00150,
  spidoframe00151, spidoframe00152, spidoframe00153, spidoframe00154, spidoframe00155, spidoframe00156, spidoframe00157, spidoframe00158, spidoframe00159, spidoframe00160,
  spidoframe00161, spidoframe00162, spidoframe00163, spidoframe00164, spidoframe00165, spidoframe00166, spidoframe00167, spidoframe00168, spidoframe00169, spidoframe00170,
  spidoframe00171, spidoframe00172, spidoframe00173, spidoframe00174, spidoframe00175, spidoframe00176, spidoframe00177, spidoframe00178, spidoframe00179, spidoframe00180,
  spidoframe00181, spidoframe00182, spidoframe00183, spidoframe00184, spidoframe00185, spidoframe00186, spidoframe00187, spidoframe00188, spidoframe00189, spidoframe00190,
  spidoframe00191, spidoframe00192, spidoframe00193, spidoframe00194, spidoframe00195, spidoframe00196, spidoframe00197, spidoframe00198, spidoframe00199, spidoframe00200,
  spidoframe00201, spidoframe00202, spidoframe00203, spidoframe00204, spidoframe00205, spidoframe00206, spidoframe00207, spidoframe00208, spidoframe00209, spidoframe00210,
  spidoframe00211, spidoframe00212, spidoframe00213, spidoframe00214, spidoframe00215, spidoframe00216, spidoframe00217, spidoframe00218, spidoframe00219, spidoframe00220,
  spidoframe00221, spidoframe00222, spidoframe00223, spidoframe00224, spidoframe00225, spidoframe00226, spidoframe00227, spidoframe00228, spidoframe00229,

  // -------- game.h (279 frames) --------
  gameframe00001, gameframe00002, gameframe00003, gameframe00004, gameframe00005, gameframe00006, gameframe00007, gameframe00008, gameframe00009, gameframe00010,
  gameframe00011, gameframe00012, gameframe00013, gameframe00014, gameframe00015, gameframe00016, gameframe00017, gameframe00018, gameframe00019, gameframe00020,
  gameframe00021, gameframe00022, gameframe00023, gameframe00024, gameframe00025, gameframe00026, gameframe00027, gameframe00028, gameframe00029, gameframe00030,
  gameframe00031, gameframe00032, gameframe00033, gameframe00034, gameframe00035, gameframe00036, gameframe00037, gameframe00038, gameframe00039, gameframe00040,
  gameframe00041, gameframe00042, gameframe00043, gameframe00044, gameframe00045, gameframe00046, gameframe00047, gameframe00048, gameframe00049, gameframe00050,
  gameframe00051, gameframe00052, gameframe00053, gameframe00054, gameframe00055, gameframe00056, gameframe00057, gameframe00058, gameframe00059, gameframe00060,
  gameframe00061, gameframe00062, gameframe00063, gameframe00064, gameframe00065, gameframe00066, gameframe00067, gameframe00068, gameframe00069, gameframe00070,
  gameframe00071, gameframe00072, gameframe00073, gameframe00074, gameframe00075, gameframe00076, gameframe00077, gameframe00078, gameframe00079, gameframe00080,
  gameframe00081, gameframe00082, gameframe00083, gameframe00084, gameframe00085, gameframe00086, gameframe00087, gameframe00088, gameframe00089, gameframe00090,
  gameframe00091, gameframe00092, gameframe00093, gameframe00094, gameframe00095, gameframe00096, gameframe00097, gameframe00098, gameframe00099, gameframe00100,
  gameframe00101, gameframe00102, gameframe00103, gameframe00104, gameframe00105, gameframe00106, gameframe00107, gameframe00108, gameframe00109, gameframe00110,
  gameframe00111, gameframe00112, gameframe00113, gameframe00114, gameframe00115, gameframe00116, gameframe00117, gameframe00118, gameframe00119, gameframe00120,
  gameframe00121, gameframe00122, gameframe00123, gameframe00124, gameframe00125, gameframe00126, gameframe00127, gameframe00128, gameframe00129, gameframe00130,
  gameframe00131, gameframe00132, gameframe00133, gameframe00134, gameframe00135, gameframe00136, gameframe00137, gameframe00138, gameframe00139, gameframe00140,
  gameframe00141, gameframe00142, gameframe00143, gameframe00144, gameframe00145, gameframe00146, gameframe00147, gameframe00148, gameframe00149, gameframe00150,
  gameframe00151, gameframe00152, gameframe00153, gameframe00154, gameframe00155, gameframe00156, gameframe00157, gameframe00158, gameframe00159, gameframe00160,
  gameframe00161, gameframe00162, gameframe00163, gameframe00164, gameframe00165, gameframe00166, gameframe00167, gameframe00168, gameframe00169, gameframe00170,
  gameframe00171, gameframe00172, gameframe00173, gameframe00174, gameframe00175, gameframe00176, gameframe00177, gameframe00178, gameframe00179, gameframe00180,
  gameframe00181, gameframe00182, gameframe00183, gameframe00184, gameframe00185, gameframe00186, gameframe00187, gameframe00188, gameframe00189, gameframe00190,
  gameframe00191, gameframe00192, gameframe00193, gameframe00194, gameframe00195, gameframe00196, gameframe00197, gameframe00198, gameframe00199, gameframe00200,
  gameframe00201, gameframe00202, gameframe00203, gameframe00204, gameframe00205, gameframe00206, gameframe00207, gameframe00208, gameframe00209, gameframe00210,
  gameframe00211, gameframe00212, gameframe00213, gameframe00214, gameframe00215, gameframe00216, gameframe00217, gameframe00218, gameframe00219, gameframe00220,
  gameframe00221, gameframe00222, gameframe00223, gameframe00224, gameframe00225, gameframe00226, gameframe00227, gameframe00228, gameframe00229, gameframe00230,
  gameframe00231, gameframe00232, gameframe00233, gameframe00234, gameframe00235, gameframe00236, gameframe00237, gameframe00238, gameframe00239, gameframe00240,
  gameframe00241, gameframe00242, gameframe00243, gameframe00244, gameframe00245, gameframe00246, gameframe00247, gameframe00248, gameframe00249, gameframe00250,
  gameframe00251, gameframe00252, gameframe00253, gameframe00254, gameframe00255, gameframe00256, gameframe00257, gameframe00258, gameframe00259, gameframe00260,
  gameframe00261, gameframe00262, gameframe00263, gameframe00264, gameframe00265, gameframe00266, gameframe00267, gameframe00268, gameframe00269, gameframe00270,
  gameframe00271, gameframe00272, gameframe00273, gameframe00274, gameframe00275, gameframe00276, gameframe00277, gameframe00278, gameframe00279,

  // -------- rising_star.h (197 frames) --------
  rising_starframe00001, rising_starframe00002, rising_starframe00003, rising_starframe00004, rising_starframe00005, rising_starframe00006, rising_starframe00007, rising_starframe00008, rising_starframe00009, rising_starframe00010,
  rising_starframe00011, rising_starframe00012, rising_starframe00013, rising_starframe00014, rising_starframe00015, rising_starframe00016, rising_starframe00017, rising_starframe00018, rising_starframe00019, rising_starframe00020,
  rising_starframe00021, rising_starframe00022, rising_starframe00023, rising_starframe00024, rising_starframe00025, rising_starframe00026, rising_starframe00027, rising_starframe00028, rising_starframe00029, rising_starframe00030,
  rising_starframe00031, rising_starframe00032, rising_starframe00033, rising_starframe00034, rising_starframe00035, rising_starframe00036, rising_starframe00037, rising_starframe00038, rising_starframe00039, rising_starframe00040,
  rising_starframe00041, rising_starframe00042, rising_starframe00043, rising_starframe00044, rising_starframe00045, rising_starframe00046, rising_starframe00047, rising_starframe00048, rising_starframe00049, rising_starframe00050,
  rising_starframe00051, rising_starframe00052, rising_starframe00053, rising_starframe00054, rising_starframe00055, rising_starframe00056, rising_starframe00057, rising_starframe00058, rising_starframe00059, rising_starframe00060,
  rising_starframe00061, rising_starframe00062, rising_starframe00063, rising_starframe00064, rising_starframe00065, rising_starframe00066, rising_starframe00067, rising_starframe00068, rising_starframe00069, rising_starframe00070,
  rising_starframe00071, rising_starframe00072, rising_starframe00073, rising_starframe00074, rising_starframe00075, rising_starframe00076, rising_starframe00077, rising_starframe00078, rising_starframe00079, rising_starframe00080,
  rising_starframe00081, rising_starframe00082, rising_starframe00083, rising_starframe00084, rising_starframe00085, rising_starframe00086, rising_starframe00087, rising_starframe00088, rising_starframe00089, rising_starframe00090,
  rising_starframe00091, rising_starframe00092, rising_starframe00093, rising_starframe00094, rising_starframe00095, rising_starframe00096, rising_starframe00097, rising_starframe00098, rising_starframe00099, rising_starframe00100,
  rising_starframe00101, rising_starframe00102, rising_starframe00103, rising_starframe00104, rising_starframe00105, rising_starframe00106, rising_starframe00107, rising_starframe00108, rising_starframe00109, rising_starframe00110,
  rising_starframe00111, rising_starframe00112, rising_starframe00113, rising_starframe00114, rising_starframe00115, rising_starframe00116, rising_starframe00117, rising_starframe00118, rising_starframe00119, rising_starframe00120,
  rising_starframe00121, rising_starframe00122, rising_starframe00123, rising_starframe00124, rising_starframe00125, rising_starframe00126, rising_starframe00127, rising_starframe00128, rising_starframe00129, rising_starframe00130,
  rising_starframe00131, rising_starframe00132, rising_starframe00133, rising_starframe00134, rising_starframe00135, rising_starframe00136, rising_starframe00137, rising_starframe00138, rising_starframe00139, rising_starframe00140,
  rising_starframe00141, rising_starframe00142, rising_starframe00143, rising_starframe00144, rising_starframe00145, rising_starframe00146, rising_starframe00147, rising_starframe00148, rising_starframe00149, rising_starframe00150,
  rising_starframe00151, rising_starframe00152, rising_starframe00153, rising_starframe00154, rising_starframe00155, rising_starframe00156, rising_starframe00157, rising_starframe00158, rising_starframe00159, rising_starframe00160,
  rising_starframe00161, rising_starframe00162, rising_starframe00163, rising_starframe00164, rising_starframe00165, rising_starframe00166, rising_starframe00167, rising_starframe00168, rising_starframe00169, rising_starframe00170,
  rising_starframe00171, rising_starframe00172, rising_starframe00173, rising_starframe00174, rising_starframe00175, rising_starframe00176, rising_starframe00177, rising_starframe00178, rising_starframe00179, rising_starframe00180,
  rising_starframe00181, rising_starframe00182, rising_starframe00183, rising_starframe00184, rising_starframe00185, rising_starframe00186, rising_starframe00187, rising_starframe00188, rising_starframe00189, rising_starframe00190,
  rising_starframe00191, rising_starframe00192, rising_starframe00193, rising_starframe00194, rising_starframe00195, rising_starframe00196, rising_starframe00197,

  // -------- makan.h (281 frames) --------
  makanframe00001, makanframe00002, makanframe00003, makanframe00004, makanframe00005, makanframe00006, makanframe00007, makanframe00008, makanframe00009, makanframe00010,
  makanframe00011, makanframe00012, makanframe00013, makanframe00014, makanframe00015, makanframe00016, makanframe00017, makanframe00018, makanframe00019, makanframe00020,
  makanframe00021, makanframe00022, makanframe00023, makanframe00024, makanframe00025, makanframe00026, makanframe00027, makanframe00028, makanframe00029, makanframe00030,
  makanframe00031, makanframe00032, makanframe00033, makanframe00034, makanframe00035, makanframe00036, makanframe00037, makanframe00038, makanframe00039, makanframe00040,
  makanframe00041, makanframe00042, makanframe00043, makanframe00044, makanframe00045, makanframe00046, makanframe00047, makanframe00048, makanframe00049, makanframe00050,
  makanframe00051, makanframe00052, makanframe00053, makanframe00054, makanframe00055, makanframe00056, makanframe00057, makanframe00058, makanframe00059, makanframe00060,
  makanframe00061, makanframe00062, makanframe00063, makanframe00064, makanframe00065, makanframe00066, makanframe00067, makanframe00068, makanframe00069, makanframe00070,
  makanframe00071, makanframe00072, makanframe00073, makanframe00074, makanframe00075, makanframe00076, makanframe00077, makanframe00078, makanframe00079, makanframe00080,
  makanframe00081, makanframe00082, makanframe00083, makanframe00084, makanframe00085, makanframe00086, makanframe00087, makanframe00088, makanframe00089, makanframe00090,
  makanframe00091, makanframe00092, makanframe00093, makanframe00094, makanframe00095, makanframe00096, makanframe00097, makanframe00098, makanframe00099, makanframe00100,
  makanframe00101, makanframe00102, makanframe00103, makanframe00104, makanframe00105, makanframe00106, makanframe00107, makanframe00108, makanframe00109, makanframe00110,
  makanframe00111, makanframe00112, makanframe00113, makanframe00114, makanframe00115, makanframe00116, makanframe00117, makanframe00118, makanframe00119, makanframe00120,
  makanframe00121, makanframe00122, makanframe00123, makanframe00124, makanframe00125, makanframe00126, makanframe00127, makanframe00128, makanframe00129, makanframe00130,
  makanframe00131, makanframe00132, makanframe00133, makanframe00134, makanframe00135, makanframe00136, makanframe00137, makanframe00138, makanframe00139, makanframe00140,
  makanframe00141, makanframe00142, makanframe00143, makanframe00144, makanframe00145, makanframe00146, makanframe00147, makanframe00148, makanframe00149, makanframe00150,
  makanframe00151, makanframe00152, makanframe00153, makanframe00154, makanframe00155, makanframe00156, makanframe00157, makanframe00158, makanframe00159, makanframe00160,
  makanframe00161, makanframe00162, makanframe00163, makanframe00164, makanframe00165, makanframe00166, makanframe00167, makanframe00168, makanframe00169, makanframe00170,
  makanframe00171, makanframe00172, makanframe00173, makanframe00174, makanframe00175, makanframe00176, makanframe00177, makanframe00178, makanframe00179, makanframe00180,
  makanframe00181, makanframe00182, makanframe00183, makanframe00184, makanframe00185, makanframe00186, makanframe00187, makanframe00188, makanframe00189, makanframe00190,
  makanframe00191, makanframe00192, makanframe00193, makanframe00194, makanframe00195, makanframe00196, makanframe00197, makanframe00198, makanframe00199, makanframe00200,
  makanframe00201, makanframe00202, makanframe00203, makanframe00204, makanframe00205, makanframe00206, makanframe00207, makanframe00208, makanframe00209, makanframe00210,
  makanframe00211, makanframe00212, makanframe00213, makanframe00214, makanframe00215, makanframe00216, makanframe00217, makanframe00218, makanframe00219, makanframe00220,
  makanframe00221, makanframe00222, makanframe00223, makanframe00224, makanframe00225, makanframe00226, makanframe00227, makanframe00228, makanframe00229, makanframe00230,
  makanframe00231, makanframe00232, makanframe00233, makanframe00234, makanframe00235, makanframe00236, makanframe00237, makanframe00238, makanframe00239, makanframe00240,
  makanframe00241, makanframe00242, makanframe00243, makanframe00244, makanframe00245, makanframe00246, makanframe00247, makanframe00248, makanframe00249, makanframe00250,
  makanframe00251, makanframe00252, makanframe00253, makanframe00254, makanframe00255, makanframe00256, makanframe00257, makanframe00258, makanframe00259, makanframe00260,
  makanframe00261, makanframe00262, makanframe00263, makanframe00264, makanframe00265, makanframe00266, makanframe00267, makanframe00268, makanframe00269, makanframe00270,
  makanframe00271, makanframe00272, makanframe00273, makanframe00274, makanframe00275, makanframe00276, makanframe00277, makanframe00278, makanframe00279, makanframe00280,
  makanframe00281,

  // -------- navigation.h (7 frames) --------
  navigationBelok_Kanan, navigationBelok_Kiri, navigationLurus, navigationPutar_Balik, navigationdestinasi_sampai, navigationSedikit_ke_kanan, navigationsedikit_ke_kiri
};

#endif  // EYE_EMOT_H