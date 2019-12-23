#pragma once
#define SHORT_BUILD_VERSION "Dev Build 454"

// =  disabled - remove // enabled

//(Step 1) enable 1 base model
//GT2560 Boards - vscode: default_envs = megaatmega2560 in platformio.ini
#define GTA10       // A10 & Variants - tested working
//#define GTA20       // A20 & Variants - tested working
//#define MECREATOR2  // Mecreator2     - tested working
//#define I3PROA      // PI3A Pro       - testing
//#define I3PROB      // I3PROB         - testing
//#define I3PROC      // I3PROC         - testing
//#define I3PROW      // I3PROW         - testing
//#define I3PROX      // I3PROX         - testing

//GTM32 Boards - vscode: default_envs = STM32F103VE_longer in platformio.ini
//#define GTA30       // A30  - Tested mostly works
//#define GTE180      // E180 - Tested mostly works 
//#define GTM201      // M201 - experimental
//#define GTD200      // D200 - experimental

//(Step 2) enable 1 driver timing set
//#define STOCK     // Enable A4988   on all drivers (stock drivers)
#define T2208    // Enable TMC2208 Standalone on all drivers
//#define T2209    // Enable TMC2209 Standalone all drivers
//#define T2130    // Enable TMC2130 Standalone all drivers
//#define T2160    // Enable TMC2160 Standalone all drivers
//#define T26X     // Enable TMC226X Standalone all drivers
//#define T2660    // Enable TMC2660 Standalone all drivers
//#define T5130    // Enable TMC5130 Standalone all drivers
//#define T5160    // Enable TMC5160 Standalone all drivers
//#define A598     // Enable A5984   all drivers
//#define D8825    // Enable DRV8825 all drivers
//#define L8729    // Enable LV8729  all drivers
//#define L647     // Enable L6470   all drivers
//#define T6560    // Enable TB6560  all drivers
//#define T6600    // Enable TB6600  all drivers
//#define CUSTOM   // Fill in #elif ENABLED (CUSTOM) in configuration.h with a custom set & invert if needed below #if ENABLED (CUSTOM)

//(Step 3) enable 1 if you have mixing or multi extruder (C D M T variants)
//#define MIX      // Enable Mixing    2 in 1 - Virtual Motor Control 
//#define CYCLOPS  // Enable Cyclops   2 in 1 - Physical Motor Control
//#define DUALEX   // 2 Extruder       2 in 2 - Physical Motor Control 
//#define MIXT     // Enable Mixing    3 in 1 - Virtual Motor Control
//#define CYCLOPST // Enable Cyclops   3 in 1 - Physical Motor Control
//#define TRIEX    // 3 Extruder       3 in 3 - Physical Motor Control 
 
//(Step 4) enable 1 probe type or none for manual (stock)
#define TOUCHPROBE  // Enable Bltouch Type Probe
//#define FMP         // Enable Fixed Mounted Type Probe

//Do you have bed clips to avoid?
#define BEDCLIPS     // Enabled if you have bed clips manual or probe
//--------------------------------------------------------------------------------------------------------------------------------------------------------

//logic used to reduce setup steps.
#if ANY(MIX, MIXT, CYCLOPS, CYCLOPST, DUALEX, TRIEX)
#define MULTIEXTRUDER 
#endif

#if ANY(T2208, T2209, T2130, T2160, T26X, T2660,  T5130, T5160)
#define TMCCHIPS
#endif

#if ANY(MECREATOR2, I3PROA, I3PROB, I3PROC, I3PROW, I3PROX)
#define DIRECTDRIVE
#endif

//Bed clip logic
#if ENABLED (BEDCLIPS)
#define MPE 10         // To keep probe away from edges #mm/2 all sides
#else
#define MPE 0         // To keep probe away from edges #mm/2 all sides
#endif

//Bed offset logic
#if ANY(GTA10, GTA30)
#define XMP -10      // X Min Position - distance from endstop to bed, adjust to nozzle front left bed edge X0
#define YMP -5       // Y Min Position - distance from endstop to bed, adjust to nozzle front left bed edge Y0
#elif ENABLED (GTA20)
#define XMP -10      // X Min Position - distance from endstop to bed, adjust to nozzle front left bed edge X0
#define YMP 0        // Y Min Position - distance from endstop to bed, adjust to nozzle front left bed edge Y0
#else 
#define XMP 0        // X Min Position - distance from endstop to bed, adjust to nozzle front left bed edge X0
#define YMP 0        // Y Min Position - distance from endstop to bed, adjust to nozzle front left bed edge Y0
#endif

//Probe offset logic
#if DISABLED (MULTIEXTRUDER)
#define NPO { -38, 5, 0 } // Nozzle To Probe offset XYZ A10/A20 calibration suggested 
#elif ENABLED (MULTIEXTRUDER)
#define NPO { -40, 0, 0 }  // Nozzle To Probe offset XYZ A10M/A20M calibration suggested
#endif

//Steps selection logic
#if DISABLED (MULTIEXTRUDER) 
#define XYZESTEPS  { 80, 80, 400, 98 }  // ungeared extruder found on a10/a20/a30/i3pro
//#define XYZESTEPS  { 80, 80, 2560, 98 } // M8 Z rod steps 2560 found on old I3pro
#endif

#if ENABLED (MIX) || ENABLED (CYCLOPS) || ENABLED (DUALEX)
#define XYZESTEPS  { 80, 80, 400, 430, 430 } // geared extruder found on M & T variants
//#define XYZESTEPS  { 80, 80, 2560,430, 430 } // M8 Z rod steps 2560 found on old I3pro
#endif

#if ENABLED (MIXT) || ENABLED (CYCLOPST) || ENABLED (TRIEX)
#define XYZESTEPS  { 80, 80, 400, 430, 430, 430 } // geared extruder found on M & T variants
//#define XYZESTEPS  { 80, 80, 2560,430, 430, 430 } // M8 Z rod steps 2560 found on old I3pro
#endif

//Motor direction logic
#if ENABLED (TMCCHIPS) && DISABLED (MULTIEXTRUDER) || DISABLED (CUSTOM) && ENABLED (MULTIEXTRUDER) 
#define INVERTE     // Invert E direction disabe if wrong direction - M & T variants invert E (stock)
#endif

#if ENABLED (TMCCHIPS)
#define INVERTXYZ   // Invert XYZ direction disable if wrong direction. 
#endif

#if ENABLED (CUSTOM)
//#define INVERTE     // Invert E direction disabe if wrong direction - M & T variants invert E (stock)
#define INVERTXYZ   // Invert XYZ direction disable if wrong direction. adjust for custom
#endif