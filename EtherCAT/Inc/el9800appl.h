/**
 * \addtogroup EL9800Appl EL9800 application
 * @{
 * This application includes three functional modules:<br>
 * Digital Input<br>
 * Digital Outputs<br>
 * Analog Input<br>
 * The objects of the modules are defined according the ETG.5001.<br>
 */

/**
\file el9800appl.h
\author EthercatSSC@beckhoff.com
\brief EL9800 Application defines, typedefs and global variables

\version 5.01

<br>Changes to version - :<br>
V5.01 : Start file change log
 */
#ifndef _EL9800APPL_H_
#define _EL9800APPL_H_

/*-----------------------------------------------------------------------------------------
------
------    Includes
------
-----------------------------------------------------------------------------------------*/
#include "ecatappl.h"


/*-----------------------------------------------------------------------------------------
------
------    Defines and Typedef
------
-----------------------------------------------------------------------------------------*/

/**
 * \addtogroup PdoMappingObjects PDO Mapping Objects
 *
 * Digital Input PDO mapping : 0x1A00<br>
 * Digital Output PDO mapping : 0x1601<br>
 * Analog Input PDO mapping : 0x1A02
 * @{
 */
/** \brief 0x1601 (Basic Control RxPDO) data structure*/
typedef struct OBJ_STRUCT_PACKED_START {
   UINT16   u16SubIndex0; /**< \brief SubIndex 0*/
   UINT32   aEntries[5]; /**< \brief Entry buffer 多预留空间是不会报错的*/
} OBJ_STRUCT_PACKED_END
TOBJ1601;

/** \brief 0x1610 (User Config RxPDO) data structure*/
typedef struct OBJ_STRUCT_PACKED_START {
   UINT16   u16SubIndex0; /**< \brief SubIndex 0*/
   UINT32   aEntries[6]; /**< \brief Entry buffer*/
} OBJ_STRUCT_PACKED_END
TOBJ1610;

/** \brief 0x1620 (IO Config RxPDO) data structure*/
typedef struct OBJ_STRUCT_PACKED_START {
   UINT16   u16SubIndex0; /**< \brief SubIndex 0*/
   UINT32   aEntries[17]; /**< \brief Entry buffer*/
} OBJ_STRUCT_PACKED_END
TOBJ1620;


/** \brief 0x1A00 (Digital input TxPDO) data structure*/
typedef struct OBJ_STRUCT_PACKED_START {
   UINT16   u16SubIndex0; /**< \brief SubIndex 0*/
   UINT32   aEntries[9]; /**< \brief Entry buffer*/
} OBJ_STRUCT_PACKED_END
TOBJ1A00;


/** \brief 0x1A02 (Analog input TxPDO) data structure*/
typedef struct OBJ_STRUCT_PACKED_START {
   UINT16   u16SubIndex0; /**< \brief SubIndex 0*/
   UINT32   aEntries[8]; /**< \brief Entry buffer*/
} OBJ_STRUCT_PACKED_END
TOBJ1A02;
/** @}*/


/**
 * \addtogroup SmAssignObjects SyncManager Assignment Objects
 * SyncManager 2 : 0x1C12 
 * <br>SyncManager 3 : 0x1C13
 * @{
 */
/** \brief 0x1C12 (SyncManager 2 assignment) data structure*/
typedef struct OBJ_STRUCT_PACKED_START {
   UINT16   u16SubIndex0; /**< \brief SubIndex 0*/
   UINT16   aEntries[3]; /**< \brief Entry buffer*/
} OBJ_STRUCT_PACKED_END
TOBJ1C12;


/** \brief 0x1C13 (SyncManager 3 assignment) data structure*/
typedef struct OBJ_STRUCT_PACKED_START {
   UINT16   u16SubIndex0; /**< \brief SubIndex 0*/
   UINT16   aEntries[1]; /**< \brief Entry buffer*/
} OBJ_STRUCT_PACKED_END
TOBJ1C13;
/** @}*/


/**
 * \addtogroup PDO Process Data Objects
 * Digital Inputs : 0x6000<br>
 * Analog Inputs : 0x6010<br> 
 * Digital Outputs : 0x7020
 * @{
 */
/** \brief 0x6000 (Digital input object) data structure*/
typedef struct OBJ_STRUCT_PACKED_START {
	UINT16 u16SubIndex0; /**< \brief SubIndex 0*/
	UINT16 init;
	UINT16 clamping;
	UINT16 position;
	UINT16 speed;
	UINT16 current;
	UINT16 error;
	UINT16 opinfo;
	UINT16 log;
} OBJ_STRUCT_PACKED_END
TOBJ6000;


/** \brief 0x6020 (Analog input object) data structure*/
typedef struct OBJ_STRUCT_PACKED_START {
   UINT16   u16SubIndex0; /**< \brief SubIndex 0*/
   BOOLEAN(bUnderrange); /**< \brief (SI1) Analog input under range*/
   BOOLEAN(bOverrange); /**< \brief (SI2) Analog input over range*/
   BIT2(b2Limit1); /**< \brief (SI3) Analog input 1st limit*/
   BIT2(b2Limit2); /**< \brief (SI5) Analog input 2nd limit*/
   ALIGN2(SubIndex006) /**< \brief 2Bit alignment*/
   ALIGN6(SubIndex007) /**< \brief 2Bit alignment*/
   BOOLEAN(bTxPDOState); /**< \brief (SI15) TxPdo state*/
   BOOLEAN(bTxPDOToggle); /**< \brief (SI16) TxPdo toggle*/
   INT16   i16Analoginput; /**< \brief (SI17) Analog input value*/
} OBJ_STRUCT_PACKED_END
TOBJ6020;

/** \brief 0x7000 gripper basic control data structure*/
typedef struct OBJ_STRUCT_PACKED_START {
	UINT16 u16SubIndex0; /**< \brief SubIndex 0*/
	UINT16 init;
	UINT16 closeforce;
	UINT16 openforce;
	UINT16 position;
	UINT16 speed;
} OBJ_STRUCT_PACKED_END
TOBJ7000;
/** @}*/

/** \brief 0x7200 gripper user config data structure*/
typedef struct OBJ_STRUCT_PACKED_START {
	UINT16 u16SubIndex0; /**< \brief SubIndex 0*/
	UINT16 save;
	UINT16 initdirection;
	UINT16 id;
	UINT16 baudrate;
	UINT16 stopbit;
	UINT16 checkdigit;
} OBJ_STRUCT_PACKED_END
TOBJ7200;
/** @}*/

/** \brief 0x7300 gripper io config data structure*/
typedef struct OBJ_STRUCT_PACKED_START {
	UINT16 u16SubIndex0; /**< \brief SubIndex 0*/
	UINT16 iocontrol;
	UINT16 save;
	UINT16 onoff;
	UINT16 output;
	UINT16 input;
	UINT16 pos1;
	UINT16 force1;
	UINT16 speed1;
	UINT16 pos2;
	UINT16 force2;
	UINT16 speed2;
	UINT16 pos3;
	UINT16 force3;
	UINT16 speed3;
	UINT16 pos4;
	UINT16 force4;
	UINT16 speed4;
} OBJ_STRUCT_PACKED_END
TOBJ7300;
/** @}*/

/** \brief 0x7010 (Digital output object) data structure*/
typedef struct OBJ_STRUCT_PACKED_START {
   UINT16   u16SubIndex0; /**< \brief SubIndex 0*/
   BOOLEAN(bLED1); /**< \brief LED 1*/
   BOOLEAN(bLED2); /**< \brief LED 2*/
   BOOLEAN(bLED3); /**< \brief LED 3*/
   BOOLEAN(bLED4); /**< \brief LED 4*/
   BOOLEAN(bLED5); /**< \brief LED 5*/
   BOOLEAN(bLED6); /**< \brief LED 6*/
   BOOLEAN(bLED7); /**< \brief LED 7*/
   BOOLEAN(bLED8); /**< \brief LED 8*/
   ALIGN8(SubIndex008) /**< \brief 8Bit alignment*/
} OBJ_STRUCT_PACKED_END
TOBJ7010;
/** @}*/


/**
 * \addtogroup ConfigObjects Configuration Objects
 * Analog input settings: 0x8020
 * @{
 */
/** \brief 0x8020 (Analog input settings object) data structure*/
typedef struct OBJ_STRUCT_PACKED_START {
   UINT16   u16SubIndex0; /**< \brief SubIndex 0*/
   BOOLEAN(bEnableuserscale); /**< \brief Enable user scaling*/
   BIT3(b3Presentation); /**< \brief Value presentation*/
   ALIGN2(SubIndex005) /**< \brief 2Bit Alignment*/
   BOOLEAN(bEnablelimit1); /**< \brief Enable limit 1*/
   BOOLEAN(bEnablelimit2); /**< \brief Enable limit 2*/
   ALIGN8(SubIndex009) /**< \brief 8Bit Alignment*/
   INT16   i16Offset; /**< \brief Value offset*/
   INT32   i32Gain; /**< \brief Value gain*/
   INT16   i16Limit1; /**< \brief Value limit 1*/
   INT16   i16Limit2; /**< \brief Value limit 2*/
} OBJ_STRUCT_PACKED_END
TOBJ8020;
/** @}*/


/**
 * \addtogroup DeviceParaObjects Device Parameter Objects
 * Modular Device Profile: 0xF000
 * @{
 */
/** \brief 0xF000 (Modular Device Profile) data structure*/
typedef struct OBJ_STRUCT_PACKED_START {
   UINT16   u16SubIndex0; /**< \brief SubIndex0*/
   UINT16   u16Moduleindexdistance; /**< \brief Module Index distance
                                     * 
                                     * Index distance between two modules (maximum number of objects per module and area)<br>
                                     * Default: 0x10*/
   UINT16   u16Maximumnumberofmodules; /**< \brief Maximum number of modules*/
} OBJ_STRUCT_PACKED_END
TOBJF000;


/** \brief 0xF010 (Module Profile List) data structure*/
typedef struct OBJ_STRUCT_PACKED_START {
   UINT16   u16SubIndex0; /**< \brief SubIndex0*/
   UINT32   aEntries[3]; /**< \brief Module profile information buffer
                          * 
                          * Bit 0..15: Profile number of the module on position 1<br>
                          * Bit 16..31: Profile specific*/
} OBJ_STRUCT_PACKED_END
TOBJF010;
/** @}*/

#endif //_EL9800APPL_H_

#ifdef _EVALBOARD_
    #define PROTO
#else
    #define PROTO extern
#endif


#ifdef _OBJD_
/**
 * \addtogroup SmAssignObjects SyncManager Assignment Objects
 * @{
 */
/**
 * \brief Entry descriptions of SyncManager assign objects
 *
 * SubIndex0<br>
 * SubIndex1 (for all other entries the same description will be used (because the object code is ARRAY))
 */
OBJCONST TSDOINFOENTRYDESC    OBJMEM asPDOAssignEntryDesc[] = {
   {DEFTYPE_UNSIGNED8, 0x08, ACCESS_READ},
   {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READ}};
/** @}*/

   
/**
 * \addtogroup EnumObjects Enum Objects
 * @{
 * Presentation (Signed/Unsigned) : 0x800
 */

/*---------------------------------------------
-    0x0800: ENUM (Signed/Unsigned Presentation)
-----------------------------------------------*/
CHAR sEnum0800_Value00[] = "\000\000\000\000Signed presentation"; /**< \brief Value = 0x00, Text = Signed presentation */
CHAR sEnum0800_Value01[] = "\001\000\000\000Unsigned presentation"; /**< \brief Value = 0x01, Text = Unsigned presentation */
CHAR *apEnum0800[2] = { sEnum0800_Value00, sEnum0800_Value01};/**< \brief List of Enum (0x800) values*/

/**
 * \brief Enum entry description
 *
 * SubIndex0<br>
 * Enum (Signed Presentation)
 * enum (Unsigned Presentation)
 */
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x0800[] =
   {{DEFTYPE_UNSIGNED8, 8, ACCESS_READ | OBJACCESS_NOPDOMAPPING},
    {DEFTYPE_OCTETSTRING, 8*SIZEOF(sEnum0800_Value00), ACCESS_READ | OBJACCESS_NOPDOMAPPING},
   {DEFTYPE_OCTETSTRING, 8*SIZEOF(sEnum0800_Value01), ACCESS_READ | OBJACCESS_NOPDOMAPPING}};
/** @}*/


/**
* \addtogroup PdoMappingObjects PDO Mapping Objects
* @{
*/
/**
 * \brief Object 0x1601 entry descriptions
 * 
 * SubIndex 0 : read only<br>
 * SubIndex x : read only<br>
 *  (x > 0)
 */
OBJCONST TSDOINFOENTRYDESC	OBJMEM asEntryDesc0x1601[] = {
   {DEFTYPE_UNSIGNED8, 0x5, ACCESS_READ },
   {DEFTYPE_UNSIGNED32, 0x20, ACCESS_READ},
   {DEFTYPE_UNSIGNED32, 0x20, ACCESS_READ},
   {DEFTYPE_UNSIGNED32, 0x20, ACCESS_READ},
   {DEFTYPE_UNSIGNED32, 0x20, ACCESS_READ},
//   {DEFTYPE_UNSIGNED32, 0x20, ACCESS_READ},
};

/**
 * \brief Object 0x1601 (Basic Control RxPDO) name
 *
 * In this example no specific entry name is defined ("SubIndex xxx" is used)
 */
OBJCONST UCHAR OBJMEM aName0x1601[] = "DO RxPDO-Map\000\377";
#endif //#ifdef _OBJD_


/**
 * \brief Object 0x1601 (Digital output RxPDO) variable to handle object data
 * 
 * SubIndex 0 : 1<br>
 * SubIndex 1 : init <br>
 * SubIndex 2 : close force <br>
 * SubIndex 3 : open force <br>
 * SubIndex 4 : position <br>
 * SubIndex 5 : speed <br>
 */
PROTO TOBJ1601 sDORxPDOMap
#ifdef _EVALBOARD_
 = {4, {0x70000110, 0x70000210, /*0x70000310,*/ 0x70000410,0x70000510}}
#endif
;
/** @}*/
 
 
 /**
* \addtogroup User Config PDO Mapping Objects
* @{
*/
 #ifdef _OBJD_
OBJCONST TSDOINFOENTRYDESC	OBJMEM asEntryDesc0x1610[] = {
   {DEFTYPE_UNSIGNED8, 0x6, ACCESS_READ },
   {DEFTYPE_UNSIGNED32, 0x20, ACCESS_READ},
   {DEFTYPE_UNSIGNED32, 0x20, ACCESS_READ},
   {DEFTYPE_UNSIGNED32, 0x20, ACCESS_READ},
   {DEFTYPE_UNSIGNED32, 0x20, ACCESS_READ},
   {DEFTYPE_UNSIGNED32, 0x20, ACCESS_READ},
   {DEFTYPE_UNSIGNED32, 0x20, ACCESS_READ}
};

/**
 * \brief Object 0x1610 (User Config RxPDO) name
 *
 * In this example no specific entry name is defined ("SubIndex xxx" is used)
 */
OBJCONST UCHAR OBJMEM aName0x1610[] = "User Config-Map\000\377";
#endif //#ifdef _OBJD_

PROTO TOBJ1610 sUserConfigPDOMap
#ifdef _EVALBOARD_
 = {6, {0x72000110, 0x72000210, 0x72000310, 0x72000410,0x72000510,0x72000610}}
#endif
;
/** @}*/
 
 /**
* \addtogroup User Config PDO Mapping Objects
* @{
*/
 #ifdef _OBJD_
OBJCONST TSDOINFOENTRYDESC	OBJMEM asEntryDesc0x1620[] = {
   {DEFTYPE_UNSIGNED8, 0x17, ACCESS_READ },
   {DEFTYPE_UNSIGNED32, 0x20, ACCESS_READ},
   {DEFTYPE_UNSIGNED32, 0x20, ACCESS_READ},
   {DEFTYPE_UNSIGNED32, 0x20, ACCESS_READ},
   {DEFTYPE_UNSIGNED32, 0x20, ACCESS_READ},
   {DEFTYPE_UNSIGNED32, 0x20, ACCESS_READ},
   {DEFTYPE_UNSIGNED32, 0x20, ACCESS_READ},
   {DEFTYPE_UNSIGNED32, 0x20, ACCESS_READ},
   {DEFTYPE_UNSIGNED32, 0x20, ACCESS_READ},
   {DEFTYPE_UNSIGNED32, 0x20, ACCESS_READ},
   {DEFTYPE_UNSIGNED32, 0x20, ACCESS_READ},
   {DEFTYPE_UNSIGNED32, 0x20, ACCESS_READ},
   {DEFTYPE_UNSIGNED32, 0x20, ACCESS_READ},
   {DEFTYPE_UNSIGNED32, 0x20, ACCESS_READ},
   {DEFTYPE_UNSIGNED32, 0x20, ACCESS_READ},
   {DEFTYPE_UNSIGNED32, 0x20, ACCESS_READ},
   {DEFTYPE_UNSIGNED32, 0x20, ACCESS_READ},
   {DEFTYPE_UNSIGNED32, 0x20, ACCESS_READ}
};

/**
 * \brief Object 0x1620 (IO Config RxPDO) name
 *
 * In this example no specific entry name is defined ("SubIndex xxx" is used)
 */
OBJCONST UCHAR OBJMEM aName0x1620[] = "IO Config-Map\000\377";
#endif //#ifdef _OBJD_

PROTO TOBJ1620 sIOConfigPDOMap
#ifdef _EVALBOARD_
 = {17, {0x73000110, 0x73000210, 0x73000310, 0x73000410, 0x73000510, 0x73000610 \
		,0x73000710, 0x73000810, 0x73000910, 0x73000A10, 0x73000B10, 0x73000C10 \
		,0x73000D10, 0x73000E10, 0x73000F10, 0x73001010, 0x73001110}}
#endif
;
/** @}*/
 
 

/**
 * \addtogroup PdoParameter PDO Parameter
 * @{
 *
 * Parameter for PDO mapping object 0x1A02 : 0x1802
 */
#ifdef _OBJD_
/**
 * \brief Entry descriptions of TxPDO Parameter object (0x1802)
 * 
 * Subindex 0<br>
 * SubIndex 1 - 5 : not defined<br>
 * SubIndex 6 : Exclude TxPDOs<br>
 * SubIndex 7 : TxPDO State<br>
 * SubIndex 8 : not defined<br>
 * SubIndex 9 : TxPDO Toggle
 */
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x1802[] = {
   {DEFTYPE_UNSIGNED8, 0x8, ACCESS_READ },
   {0, 0x0, 0},
   {0, 0x0, 0},
   {0, 0x0, 0},
   {0, 0x0, 0},
   {0, 0x0, 0},
   {DEFTYPE_OCTETSTRING, 0x00, ACCESS_READ | OBJACCESS_TXPDOMAPPING},
   {DEFTYPE_BOOLEAN, 0x01, ACCESS_READ | OBJACCESS_TXPDOMAPPING},
   {0, 0x0, 0},
   {DEFTYPE_BOOLEAN, 0x01, ACCESS_READ | OBJACCESS_TXPDOMAPPING}};

/**
 * \brief Object 0x1802 (TxPDO Parameter) object and entry names
 */
OBJCONST UCHAR OBJMEM aName0x1802[] = "TxPDO Parameter\000\000\000\000\000\000Exclude TxPDOs\000TxPDOState\000\000TxPDO Toggle\000\377";
#endif //#ifdef _OBJD_



/**
 * \brief Object 0x1802 (TxPDO Parameter) variable to handle object data
 * 
 * Only Subindex0 for this Object is stored here (all values are stored in other structures, see "ReadObject0x1802" for more details)
 */
PROTO UINT16 TxPDO1802Subindex0
#ifdef _EVALBOARD_
    = 9
#endif
    ;
/** @}*/


/**
 * \addtogroup PdoMapping PDO Mapping Objects
 * @{
 */
/**
 * \brief Object 0x1A00 (Digital input TxPDO) entry descriptions
 *
 * SubIndex 0 : read only<br>
 * SubIndex x : read only<br>
 *  (x > 0)
*/
#ifdef _OBJD_
OBJCONST TSDOINFOENTRYDESC	OBJMEM asEntryDesc0x1A00[] = {
   {DEFTYPE_UNSIGNED8, 0x8, ACCESS_READ },
//   {DEFTYPE_UNSIGNED32, 0x20, ACCESS_READ},
//   {DEFTYPE_UNSIGNED32, 0x20, ACCESS_READ},
//   {DEFTYPE_UNSIGNED32, 0x20, ACCESS_READ},
   {DEFTYPE_UNSIGNED32, 0x20, ACCESS_READ},
   {DEFTYPE_UNSIGNED32, 0x20, ACCESS_READ},
   {DEFTYPE_UNSIGNED32, 0x20, ACCESS_READ},
   {DEFTYPE_UNSIGNED32, 0x20, ACCESS_READ},
   {DEFTYPE_UNSIGNED32, 0x20, ACCESS_READ},
   {DEFTYPE_UNSIGNED32, 0x20, ACCESS_READ}};


/**
 * \brief Object 0x1A00 (Digital input TxPDO) object and entry names
 *
 * In this example no specific entry name is defined ("SubIndex xxx" is used)
 */
OBJCONST UCHAR OBJMEM aName0x1A00[] = "DI TxPDO-Map\000\377";
#endif //#ifdef _OBJD_


/**
 * \brief Object 0x1A00 (Digital Input TxPDO) variable to handle object data
 * 
 * SubIndex 0 : 1<br>
 * SubIndex 1 : <br>
 */
PROTO TOBJ1A00 sDITxPDOMap
#ifdef _EVALBOARD_
 = {5, {0x60000110, 0x60000210, 0x60000310, /*0x60000410,*/ 0x60000510, 0x60000610/*, 0x60000710, 0x60000810*/}}
#endif
;


/**
 * \brief Object 0x1A02 (Analog input TxPDO) entry descriptions
 *
 * SubIndex 0 : read only<br>
 * SubIndex x : read only<br>
 *  (x > 0)
*/
#ifdef _OBJD_
OBJCONST TSDOINFOENTRYDESC	OBJMEM asEntryDesc0x1A02[] = {
   {DEFTYPE_UNSIGNED8, 0x8, ACCESS_READ }, /* Subindex 000 */
   {DEFTYPE_UNSIGNED32, 0x20, ACCESS_READ}, /* SubIndex 001: SubIndex 001 */
   {DEFTYPE_UNSIGNED32, 0x20, ACCESS_READ}, /* SubIndex 002: SubIndex 002 */
   {DEFTYPE_UNSIGNED32, 0x20, ACCESS_READ}, /* SubIndex 003: SubIndex 003 */
   {DEFTYPE_UNSIGNED32, 0x20, ACCESS_READ}, /* SubIndex 004: SubIndex 004 */
   {DEFTYPE_UNSIGNED32, 0x20, ACCESS_READ}, /* SubIndex 005: SubIndex 005 */
   {DEFTYPE_UNSIGNED32, 0x20, ACCESS_READ}, /* SubIndex 006: SubIndex 006 */
   {DEFTYPE_UNSIGNED32, 0x20, ACCESS_READ}, /* SubIndex 007: SubIndex 007 */
   {DEFTYPE_UNSIGNED32, 0x20, ACCESS_READ}}; /* SubIndex 008: SubIndex 008 */


/**
 * \brief Object 0x1A02 (Analog input TxPDO) object and entry names
 *
 * In this example no specific entry name is defined ("SubIndex xxx" is used)
 */
OBJCONST UCHAR OBJMEM aName0x1A02[] = "AI TxPDO-Map\000\377";
#endif //#ifdef _OBJD_



/**
 * \brief Object 0x1A02 (Analog Input TxPDO) variable to handle object data
 * 
 * SubIndex 0 : 1<br>
 * SubIndex 1 : 0x6020.1 1bit (Reference to Analog under range)<br>
 * SubIndex 2 : 0x6020.2 1bit (Reference to Analog over range)<br>
 * SubIndex 3 : 0x6020.3 2bit (Reference to limit 1)<br>
 * SubIndex 4 : 0x6020.5 2bit (Reference to limit 2)<br>
 * SubIndex 5 : 8Bit Alignment<br>
 * SubIndex 6 : 0x1802.7 1bit (Reference to TxPDO State (stored in analog input struct))<br>
 * SubIndex 7 : 0x1802.9 1bit (Reference to TxPDO Toggle (stored in analog input struct))<br>
 * SubIndex 8 : 0x6020.17 16bit (Reference to Analog input value)
 */
PROTO TOBJ1A02 sAITxPDOMap
#ifdef _EVALBOARD_
= {8, {0x60200101, 0x60200201, 0x60200302, 0x60200502, 0x08, 0x18020701, 0x18020901, 0x60201110}}
#endif
;
/** @}*/


/**
 * \addtogroup SmAssignObjects SyncManager Assignment Objects
 * @{
 */
#ifdef _OBJD_
/**
 * \brief 0x1C12 (SyncManager 2 assignment) object name 
 * 
 * No entry names defined because the object code is ARRAY and all entry names are "SubIndex 000"
 */
OBJCONST UCHAR OBJMEM aName0x1C12[] = "RxPDO assign";
#endif //#ifdef _OBJD_


/**
 * \brief 0x1C12 (SyncManager 2 assignment) variable to handle object data
 * 
 * SubIndex 0 : 1<br>
 * SubIndex 1 : 0x1601
 */
PROTO TOBJ1C12 sRxPDOassign
#ifdef _EVALBOARD_
= {0x01, {0x1601/*,0x1610,0x1620*/}}
#endif
;


#ifdef _OBJD_
/**
 * \brief 0x1C13 (SyncManager 3 assignment) object name 
 * 
 * No entry names defined because the object code is ARRAY and all entry names are "SubIndex 000"
 */
OBJCONST UCHAR OBJMEM aName0x1C13[] = "TxPDO assign";
#endif //#ifdef _OBJD_


/**
 * \brief 0x1C13 (SyncManager 3 assignment) variable to handle object data
 * 
 * SubIndex 0 : 1<br>
 * SubIndex 1 : 0x1A00<br>
 * SubIndex 2 : 0x1A02
 */
PROTO TOBJ1C13 sTxPDOassign
#ifdef _EVALBOARD_
= {0x01, {0x1A00}}
#endif
;
/** @}*/


/**
 * \addtogroup PDO Process Data Objects
 * @{
 */
#ifdef _OBJD_
/**
 * \brief Object 0x6000 (gripper feedback) entry descriptions
 *
 * SubIndex 0 : read only <br>
 * SubIndex x : gripper feedback <br>
 *  (x > 0)
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x6000[] = {
   {DEFTYPE_UNSIGNED8, 0x8, ACCESS_READ }, /* Subindex 000 */
   {DEFTYPE_INTEGER16, 0x10, ACCESS_READ | OBJACCESS_TXPDOMAPPING},		/* init feedback */
   {DEFTYPE_INTEGER16, 0x10, ACCESS_READ | OBJACCESS_TXPDOMAPPING}, 	/* clamping state */
   {DEFTYPE_INTEGER16, 0x10, ACCESS_READ | OBJACCESS_TXPDOMAPPING}, 	/* position feedback */
   {DEFTYPE_INTEGER16, 0x10, ACCESS_READ | OBJACCESS_TXPDOMAPPING}, 	/* speed feedback */
   {DEFTYPE_INTEGER16, 0x10, ACCESS_READ | OBJACCESS_TXPDOMAPPING}, 	/* current feedback*/
   {DEFTYPE_INTEGER16, 0x10, ACCESS_READ | OBJACCESS_TXPDOMAPPING}, 	/* error feedback */
   {DEFTYPE_INTEGER16, 0x10, ACCESS_READ | OBJACCESS_TXPDOMAPPING}, 	/* operation information */
   {DEFTYPE_INTEGER16, 0x10, ACCESS_READ | OBJACCESS_TXPDOMAPPING}		/* log */
};

/**
 * \brief 0x6000 (Digital input object) object and entry names
 */
OBJCONST UCHAR OBJMEM aName0x6000[] = "gripper feedback\000\377";
#endif //#ifdef _OBJD_


/**
 * \brief 0x6000 (Digital input object) variable to handle object data
 * 
 * SubIndex 0 : 1<br>
 * SubIndex x : every switch value is 0 by default
 */
PROTO TOBJ6000 sFeedBack
#ifdef _EVALBOARD_
= {8, 0x01, 0x02, 0x03, 0x04,0x05, 0x06, 0x07, 0x08}
#endif
;


#ifdef _OBJD_
/**
 * \brief Object 0x6020 (Analog input object) entry descriptions
 *
 * SubIndex 0 : read only<br>
 * SubIndex 001: Underrange<br>
 * SubIndex 002: Overrange<br>
 * SubIndex 003: Limit 1<br>
 * Subindex 004: doesn't exist<br>
 * SubIndex 005: Limit 2<br>
 * Subindex 006: 2Bit Alignment<br>
 * Subindex 007: 6Bit Alignment<br>
 * Subindex 008: doesn't exist<br>
 * Subindex 009: doesn't exist<br>
 * Subindex 010: doesn't exist<br>
 * Subindex 011: doesn't exist<br>
 * Subindex 012: doesn't exist<br>
 * Subindex 013: doesn't exist<br>
 * Subindex 014: doesn't exist<br>
 * SubIndex 015: TxPDO State<br>
 * SubIndex 016: TxPDO Toggle<br>
 * SubIndex 017: Analog input
 */
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x6020[] = {
   {DEFTYPE_UNSIGNED8, 0x8, ACCESS_READ },
   {DEFTYPE_BOOLEAN, 0x01, ACCESS_READ | OBJACCESS_TXPDOMAPPING},
   {DEFTYPE_BOOLEAN, 0x01, ACCESS_READ | OBJACCESS_TXPDOMAPPING},
   {DEFTYPE_BIT2, 0x02, ACCESS_READ | OBJACCESS_TXPDOMAPPING},
   {0x0000, 0, 0},
   {DEFTYPE_BIT2, 0x02, ACCESS_READ | OBJACCESS_TXPDOMAPPING},
   {0x0000, 0x02, 0},
   {0x0000, 0x06, 0},
   {0x0000, 0, 0},
   {0x0000, 0, 0},
   {0x0000, 0, 0},
   {0x0000, 0, 0},
   {0x0000, 0, 0},
   {0x0000, 0, 0},
   {0x0000, 0, 0},
   {DEFTYPE_BOOLEAN, 0x01, ACCESS_READ | OBJACCESS_TXPDOMAPPING},
   {DEFTYPE_BOOLEAN, 0x01, ACCESS_READ | OBJACCESS_TXPDOMAPPING},
   {DEFTYPE_INTEGER16, 0x10, ACCESS_READ | OBJACCESS_TXPDOMAPPING}};


/**
 * \brief 0x6020 (Analog input object) object and entry names
 */
OBJCONST UCHAR OBJMEM aName0x6020[] = "AI Inputs\000Underrange\000Overrange\000Limit 1\000\000Limit 2\000\000\000\000\000\000\000\000\000\000TxPDO State\000TxPDO Toggle\000Analog input\000\377";
#endif //#ifdef _OBJD_



/**
 * \brief 0x6020 (Analog input object) variable to handle object data
 * 
 */
PROTO TOBJ6020 sAIInputs
#ifdef _EVALBOARD_
= {17, 0x00, 0x00, 0x00, 0x00, 0, 0, 0x00, 0x00, 0x7FFF}
#endif
;


/**
 * \brief Object 0x7000 entry descriptions
 *
 * SubIndex 0 : read write<br>
 * SubIndex x : gripper basic operation
 *  (x > 0)
*/
#ifdef _OBJD_
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x7000[] = {
   {DEFTYPE_UNSIGNED8, 0x5, ACCESS_READ }, /* Subindex 000 不计算占位符和index*/
   {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING}, /* init */
   {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING}, /* close force */
   {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING}, /* open force */
   {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING}, /* position */
   {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING}, /* speed */
};
/**
 * \brief 0x6000 (Digital input object) object and entry names
 */
OBJCONST UCHAR OBJMEM aName0x7000[] = "Basic Control\000\377";
#endif //#ifdef _OBJD_

PROTO TOBJ7000 sBasicControl
#ifdef _EVALBOARD_
   /* 不带占位符 初始化值 */
= {5, 0x00, 0x00, 0x00, 0x00, 0x00}
#endif
;
/** @}*/

/**
 * \brief Object 0x7200 entry descriptions
 *
 * SubIndex 0 : read write<br>
 * SubIndex x : gripper user config
 *  (x > 0)
*/
#ifdef _OBJD_
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x7200[] = {
   {DEFTYPE_UNSIGNED8, 0x6, ACCESS_READ }, /* Subindex 000 不计算占位符和index*/
   {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING}, /* save */
   {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING}, /* init direction */
   {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING}, /* device id */
   {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING}, /* baudrate */
   {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING}, /* stop bit */
   {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING}, /* check digit */
};
/**
 * \brief 0x6000 (Digital input object) object and entry names
 */
OBJCONST UCHAR OBJMEM aName0x7200[] = "User Config\000\377";
#endif //#ifdef _OBJD_

PROTO TOBJ7200 sUserConfig
#ifdef _EVALBOARD_
   /* 不带占位符 初始化值 */
= {6, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}
#endif
;
/** @}*/

/**
 * \brief Object 0x7300 entry descriptions
 *
 * SubIndex 0 : read write<br>
 * SubIndex x : gripper io config
 *  (x > 0)
*/
#ifdef _OBJD_
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x7300[] = {
   {DEFTYPE_UNSIGNED8, 0x17, ACCESS_READ }, /* Subindex 000 不计算占位符和index*/
   {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING}, /* iocontrol */
   {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING}, /* save */
   {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING}, /* io mode on_off */
   {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING}, /* output */
   {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING}, /* input */
   {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING}, /* position 1 */
   {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING}, /* force 1 */
   {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING}, /* speed 1 */
   {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING}, /* position 2 */
   {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING}, /* force 2 */
   {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING}, /* speed 2 */
   {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING}, /* position 3 */
   {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING}, /* force 3 */
   {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING}, /* speed 3 */
   {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING}, /* position 4 */
   {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING}, /* force 4 */
   {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING}, /* speed 4 */
};
/**
 * \brief 0x6000 (Digital input object) object and entry names
 */
OBJCONST UCHAR OBJMEM aName0x7300[] = "IO Config\000\377";
#endif //#ifdef _OBJD_

PROTO TOBJ7300 sIOConfig
#ifdef _EVALBOARD_
   /* 不带占位符 初始化值 */
= {17, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}
#endif
;
/** @}*/


/**
 * \brief Object 0x7010 (Digital output object) entry descriptions
 *
 * SubIndex 0 : read only<br>
 * SubIndex x : (One description for each led) read only and RxPdo mappable<br>
 *  (x > 0)
*/
#ifdef _OBJD_
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x7010[] = {
   {DEFTYPE_UNSIGNED8, 0x8, ACCESS_READ }, /* Subindex 000 */
   {DEFTYPE_BOOLEAN, 0x01, ACCESS_READ | OBJACCESS_RXPDOMAPPING}, /* SubIndex 001: LED 1 */
   {DEFTYPE_BOOLEAN, 0x01, ACCESS_READ | OBJACCESS_RXPDOMAPPING}, /* SubIndex 002: LED 2 */
   {DEFTYPE_BOOLEAN, 0x01, ACCESS_READ | OBJACCESS_RXPDOMAPPING}, /* SubIndex 003: LED 3 */
   {DEFTYPE_BOOLEAN, 0x01, ACCESS_READ | OBJACCESS_RXPDOMAPPING}, /* SubIndex 004: LED 4 */
   {DEFTYPE_BOOLEAN, 0x01, ACCESS_READ | OBJACCESS_RXPDOMAPPING}, /* SubIndex 005: LED 5 */
   {DEFTYPE_BOOLEAN, 0x01, ACCESS_READ | OBJACCESS_RXPDOMAPPING}, /* SubIndex 006: LED 6 */
   {DEFTYPE_BOOLEAN, 0x01, ACCESS_READ | OBJACCESS_RXPDOMAPPING}, /* SubIndex 007: LED 7 */
   {DEFTYPE_BOOLEAN, 0x01, ACCESS_READ | OBJACCESS_RXPDOMAPPING}, /* SubIndex 008: LED 8 */
   {0x0000, 0x08, 0}}; /* Subindex 008 for align */


/**
 * \brief 0x6000 (Digital input object) object and entry names
 */
OBJCONST UCHAR OBJMEM aName0x7010[] = "DO Outputs\000LED 1\000LED 2\000LED 3\000LED 4\000LED 5\000LED 6\000LED 7\000LED 8\000\000\377";
#endif //#ifdef _OBJD_


/**
 * \brief 0x6020 (Analog input object) variable to handle object data
 * 
 */
PROTO TOBJ7010 sDOOutputs
#ifdef _EVALBOARD_
= {8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0}
#endif
;
/** @}*/



/**
 * \addtogroup ConfigObjects Configuration Objects
 * @{
 */
/**
 * \brief Object 0x8020 (Analog input settings) entry descriptions
 *
 * SubIndex 0<br>
 * SubIndex 001: Enable user scale<br>
 * SubIndex 002: Presentation<br>
 * Subindex 003 doesn't exist<br>
 * Subindex 004 doesn't exist<br>
 * Subindex 005 for align<br>
 * Subindex 006 doesn't exist<br>
 * SubIndex 007: Enable limit 1<br>
 * SubIndex 008: Enable limit 2<br>
 * Subindex 009 for align<br>
 * Subindex 010 doesn't exist<br>
 * Subindex 011 doesn't exist<br>
 * Subindex 012 doesn't exist<br>
 * Subindex 013 doesn't exist<br>
 * Subindex 014 doesn't exist<br>
 * Subindex 015 doesn't exist<br>
 * Subindex 016 doesn't exist<br>
 * SubIndex 017: Offset<br>
 * SubIndex 018: Gain<br>
 * SubIndex 019: Limit 1<br>
 * SubIndex 020: Limit 2
 */
#ifdef _OBJD_
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x8020[] = {
   {DEFTYPE_UNSIGNED8, 0x8, ACCESS_READ },
   {DEFTYPE_BOOLEAN, 0x01, ACCESS_READWRITE | OBJACCESS_BACKUP | OBJACCESS_SETTINGS},
   {0x0800, 0x03, ACCESS_READWRITE | OBJACCESS_BACKUP | OBJACCESS_SETTINGS},
   {0x0000, 0, 0},
   {0x0000, 0, 0},
   {0x0000, 0x02, 0},
   {0x0000, 0, 0},
   {DEFTYPE_BOOLEAN, 0x01, ACCESS_READWRITE | OBJACCESS_BACKUP | OBJACCESS_SETTINGS},
   {DEFTYPE_BOOLEAN, 0x01, ACCESS_READWRITE | OBJACCESS_BACKUP | OBJACCESS_SETTINGS},
   {0x0000, 0x08, 0},
   {0x0000, 0, 0},
   {0x0000, 0, 0},
   {0x0000, 0, 0},
   {0x0000, 0, 0},
   {0x0000, 0, 0},
   {0x0000, 0, 0},
   {0x0000, 0, 0},
   {DEFTYPE_INTEGER16, 0x10, ACCESS_READWRITE | OBJACCESS_BACKUP | OBJACCESS_SETTINGS},
   {DEFTYPE_INTEGER32, 0x20, ACCESS_READWRITE | OBJACCESS_BACKUP | OBJACCESS_SETTINGS},
   {DEFTYPE_INTEGER16, 0x10, ACCESS_READWRITE | OBJACCESS_BACKUP | OBJACCESS_SETTINGS},
   {DEFTYPE_INTEGER16, 0x10, ACCESS_READWRITE | OBJACCESS_BACKUP | OBJACCESS_SETTINGS}};

/** \brief Object 0x8020 (Analog input settings) object and entry names*/
OBJCONST UCHAR OBJMEM aName0x8020[] = "AI Settings\000Enable user scale\000Presentation\000\000\000\000\000Enable limit 1\000Enable limit 2\000\000\000\000\000\000\000\000\000Offset\000Gain\000Limit 1\000Limit 2\000\377";
#endif //#ifdef _OBJD_

/** \brief Object 0x8020 (Analog input settings) variable*/
PROTO TOBJ8020 sAISettings
#ifdef _EVALBOARD_
= {20, 0x00, 0x00, 0, 0x00, 0x00, 0, 0x00, 0x00, 0x00, 0x00}
#endif
;
/** @}*/


/**
 * \addtogroup DeviceParaObjects Device Parameter Objects
 * @{
 */
#ifdef _OBJD_
/** 
 * \brief 0xF000 (Modular Device Profile) entry descriptions
 *
 * Subindex 000<br>
 * SubIndex 001: Module index distance<br>
 * SubIndex 002: Maximum number of modules<br>
 */
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0xF000[] = {
   {DEFTYPE_UNSIGNED8, 0x8, ACCESS_READ },
   {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READ},
   {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READ}};


/** \brief 0xF000 (Modular Device Profile) object and entry names*/
OBJCONST UCHAR OBJMEM aName0xF000[] = "Modular device profile\000Module index distance\000Maximum number of modules\000\377";
#endif


/**
 * \brief 0xF000 (Modular Device Profile) variable to handle the object data
 *
 * SubIndex 0
 * SubIndex 1 (Module Index distance) : 0x10
 * SubIndex 2 (Maximum number of Modules) : 3
 */
/******************************************************************************
*                    Object 0xF000
******************************************************************************/
PROTO TOBJF000 sModulardeviceprofile
#ifdef _EVALBOARD_
= {2, 0x10, 0x03}
#endif
;


#ifdef _OBJD_
/** 
 * \brief 0xF010 (Module profile list) entry descriptions
 *
 * Subindex 0<br>
 * SubIndex x
 * (x > 0)
 */
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0xF010[] = {
   {DEFTYPE_UNSIGNED8, 0x08, ACCESS_READ},
   {DEFTYPE_UNSIGNED32, 0x20, ACCESS_READ},
   {DEFTYPE_UNSIGNED32, 0x20, ACCESS_READ},
   {DEFTYPE_UNSIGNED32, 0x20, ACCESS_READ}};

/**
 * \brief 0xF010 (Module profile list) object name
 *
 * no entry names defined because the object is an array (for every entry > 0 "SubIndex xxx" is returned)
 */
OBJCONST UCHAR OBJMEM aName0xF010[] = "Module profile list";
#endif


/**
 *\brief 0xF010 (Module profile list) variable to handle object data
 * 
 * SubIndex 0 : 3
 * SubIndex 1 : 100 (Digital Input SubProfile)
 * SubIndex 2 : 200 (Digital Output SubProfile)
 * SubIndex 3 : 300 (Analog Input SubProfile)
 */
PROTO TOBJF010 sModulelist
#ifdef _EVALBOARD_
= {0x03,{0x64, 0xC8, 0x12C}}
#endif
;
/** @}*/


#ifdef _OBJD_
PROTO UINT8 ReadObject0x1802( UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess );

/*if _PIC18 is enabled the object dictionary is fixed defined in coeappl.c*/

/**
 *\brief EL9800 Application specific object dictionary
 * 
 */
TOBJECT    OBJMEM ApplicationObjDic[] = {
   /* Enum 0x0800 */
   {NULL,NULL, 0x0800, {DEFTYPE_ENUM, 0x02 | (OBJCODE_REC << 8)}, asEntryDesc0x0800, 0, apEnum0800 },
   /* Object 0x1601 */
   {NULL,NULL,  0x1601, {DEFTYPE_PDOMAPPING, 4 | (OBJCODE_REC << 8)}, asEntryDesc0x1601, aName0x1601, &sDORxPDOMap, NULL, NULL, 0x0000 },
//   /* Object 0x1610 */
//   {NULL,NULL,  0x1610, {DEFTYPE_PDOMAPPING, 9 | (OBJCODE_REC << 8)}, asEntryDesc0x1610, aName0x1610, &sUserConfigPDOMap, NULL, NULL, 0x0000 },
//   /* Object 0x1620 */
//   {NULL,NULL,  0x1620, {DEFTYPE_PDOMAPPING, 9 | (OBJCODE_REC << 8)}, asEntryDesc0x1620, aName0x1620, &sIOConfigPDOMap, NULL, NULL, 0x0000 },
   
   
//   /* Object 0x1802 */
//   {NULL,NULL,  0x1802, {DEFTYPE_RECORD, 9 | (OBJCODE_REC << 8)}, asEntryDesc0x1802, aName0x1802,&TxPDO1802Subindex0, ReadObject0x1802, NULL, 0x0000 },
   /* Object 0x1A00 */
   {NULL,NULL,   0x1A00, {DEFTYPE_PDOMAPPING, 5 | (OBJCODE_REC << 8)}, asEntryDesc0x1A00, aName0x1A00, &sDITxPDOMap, NULL, NULL, 0x0000 },
//   /* Object 0x1A02 */
//   {NULL,NULL,   0x1A02, {DEFTYPE_PDOMAPPING, 8 | (OBJCODE_REC << 8)}, asEntryDesc0x1A02, aName0x1A02, &sAITxPDOMap, NULL, NULL, 0x0000 },
    /* Object 0x1C12 */
   {NULL,NULL,   0x1C12, {DEFTYPE_UNSIGNED16, 1 | (OBJCODE_ARR << 8)}, asPDOAssignEntryDesc, aName0x1C12, &sRxPDOassign, NULL, NULL, 0x0000 },
   /* Object 0x1C13 */
   {NULL,NULL,   0x1C13, {DEFTYPE_UNSIGNED16, 1 | (OBJCODE_ARR << 8)}, asPDOAssignEntryDesc, aName0x1C13, &sTxPDOassign, NULL, NULL, 0x0000 },
   
   /* Object 0x6000 */
   {NULL,NULL,   0x6000, {DEFTYPE_RECORD, 8 | (OBJCODE_REC << 8)}, asEntryDesc0x6000, aName0x6000, &sFeedBack, NULL, NULL, 0x0000 },
//   /* Object 0x6020 */
//   {NULL,NULL,   0x6020, {DEFTYPE_RECORD, 17 | (OBJCODE_REC << 8)}, asEntryDesc0x6020, aName0x6020, &sAIInputs, NULL, NULL, 0x0000 },
   
   /* Object 0x7000 基础控制 计算中间的占位符 不计算最后一个占位符和index*/
   {NULL,NULL,   0x7000, {DEFTYPE_RECORD, 5 | (OBJCODE_REC << 8)}, asEntryDesc0x7000, aName0x7000, &sBasicControl, NULL, NULL, 0x0000 },
//   /* Object 0x7200 用户参数配置*/
//   {NULL,NULL,   0x7200, {DEFTYPE_RECORD, 5 | (OBJCODE_REC << 8)}, asEntryDesc0x7200, aName0x7200, &sUserConfig, NULL, NULL, 0x0000 },
//   /* Object 0x7300 IO配置*/
//   {NULL,NULL,   0x7300, {DEFTYPE_RECORD, 5 | (OBJCODE_REC << 8)}, asEntryDesc0x7300, aName0x7300, &sIOConfig, NULL, NULL, 0x0000 },
   
//   /* Object 0x7010 */
//   {NULL,NULL,   0x7010, {DEFTYPE_RECORD, 8 | (OBJCODE_REC << 8)}, asEntryDesc0x7010, aName0x7010, &sDOOutputs, NULL, NULL, 0x0000 },
//    /* Object 0x8020 */
//    {NULL,NULL,   0x8020, {DEFTYPE_RECORD, 20 | (OBJCODE_REC << 8)}, asEntryDesc0x8020, aName0x8020, &sAISettings, NULL, NULL, 0x0008 },
    /* Object 0xF000 */
   {NULL,NULL,   0xF000, {DEFTYPE_RECORD, 2 | (OBJCODE_REC << 8)}, asEntryDesc0xF000, aName0xF000, &sModulardeviceprofile, NULL, NULL, 0x0000 },
   /* Object 0xF010 */
   {NULL,NULL,   0xF010, {DEFTYPE_UNSIGNED32, 3 | (OBJCODE_ARR << 8)}, asEntryDesc0xF010, aName0xF010, &sModulelist, NULL, NULL, 0x0000 },
   {NULL,NULL, 	0xFFFF, {0, 0}, NULL, NULL, NULL, NULL}};
#endif    //#ifdef _OBJD_

PROTO void APPL_Application(void);

PROTO void   APPL_AckErrorInd(UINT16 stateTrans);
PROTO UINT16 APPL_StartMailboxHandler(void);
PROTO UINT16 APPL_StopMailboxHandler(void);
PROTO UINT16 APPL_StartInputHandler(UINT16 *pIntMask);
PROTO UINT16 APPL_StopInputHandler(void);
PROTO UINT16 APPL_StartOutputHandler(void);
PROTO UINT16 APPL_StopOutputHandler(void);

PROTO UINT16 APPL_GenerateMapping(UINT16 *pInputSize,UINT16 *pOutputSize);
PROTO void APPL_InputMapping(UINT16* pData);
PROTO void APPL_OutputMapping(UINT16* pData);


#undef PROTO
/** @}*/
