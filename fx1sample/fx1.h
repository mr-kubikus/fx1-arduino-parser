#ifndef _FX1_H_
#define _FX1_H_

#include "common.h"

#define TX_BAUD      38400
#define BUF_MAXLEN   256

//
// Constantas from ROBO_TX_FW.h
//
#define N_CNT                   4           // Number of counters
#define N_PWM_CHAN              8           // Number of PWM channels
#define N_MOTOR                 4           // Number of motors
#define N_UNI                   8           // Number of universal inputs

// 5kOhm range
#define R_MIN                   10          // [Ohm]
#define R_MAX                   4999        // [Ohm]
#define R_OVR                   5000        // [Ohm] overload

// 10V range
#define U_MIN                   0           // [mV]
#define U_MAX                   9999        // [mV]
#define U_OVR                   10000       // [mV] overload

// Ultrasonic Sensor range
#define ULTRASONIC_MIN          2           // [cm]
#define ULTRASONIC_MAX          1023        // [cm]
#define ULTRASONIC_OVR          1024        // [cm] overload
#define NO_ULTRASONIC           4096        // Not present

// Motor outputs PWM values range
#define DUTY_MIN                0
#define DUTY_MAX                512

// Length of strings
#define DEV_NAME_LEN_MAX        16          // "ROBO TX-xxxxxxxx"
#define BT_ADDR_STR_LEN         17          // "xx:xx:xx:xx:xx:xx"
#define DISPL_MSG_LEN_MAX       98          // Max. length of a pop-up display message

// Number of Bluetooth channels
#define BT_CNT_MAX              8

// Allowed values for channel index are 1...8
#define BT_CHAN_IDX_MIN         1
#define BT_CHAN_IDX_MAX         8

#define BT_ADDR_LEN             6           // Bluetooth address length
#define BT_MSG_LEN              16          // Max. Bluetooth message length

// Identifiers of the Transfer Area
enum ta_id_e
{
    TA_LOCAL = 0,           // Transfer Area for local Controller. Corresponds to the Controller
                            // on which program is currently running in download (local) mode or
                            // to the remotely controlled Controller (seen from controlled device,
                            // not from controlling device) in online mode.
    TA_EXT_1,               // Transfer Area for Extension 1 Controller
    TA_EXT_2,               // Transfer Area for Extension 2 Controller
    TA_EXT_3,               // Transfer Area for Extension 3 Controller
    TA_EXT_4,               // Transfer Area for Extension 4 Controller
    TA_EXT_5,               // Transfer Area for Extension 5 Controller
    TA_EXT_6,               // Transfer Area for Extension 6 Controller
    TA_EXT_7,               // Transfer Area for Extension 7 Controller
    TA_EXT_8,               // Transfer Area for Extension 8 Controller
    TA_COUNT                // Number of Transfer Areas in array = 9
};

#define N_EXT               (TA_COUNT - 1)  // Number of extension Controllers = 8

//
// FishX1 command codes
//
enum eX1CmdCode {
    CMD_001               = 1,
    CMD_001_REPLY         = 101, // 0x65
    CMD_002               = 2,
    CMD_002_REPLY         = 102, // 0x66
    CMD_005               = 5,
    CMD_005_REPLY         = 105, // 0x69
    CMD_006               = 6,
    CMD_006_REPLY         = 106, // 0x6A
    CMD_007               = 7,
    CMD_007_REPLY         = 107, // 0x6B
};

//
// Program information, 8 bytes
//
typedef struct
{
    unsigned char   name_ptr[4];  // Name of a program with a full path, for example, "/ramdisk/Program_1"
    unsigned char   state;        // See enum pgm_state_e
    char            dummy[3];
} PGM_INFO;

//
// Bluetooth connection status structure, 8 bytes
//
typedef struct
{
    UINT16          conn_state;     // See enum BtConnState
    BOOL16          is_listen;      // If TRUE - BT channel is waiting for incoming connection (listening)
    BOOL16          is_receive;     // If TRUE - BT channel is ready to receive incoming messages
    UINT16          link_quality;   // 0...31, 0 - the worst, 31 - the best signal quality
} BT_STATUS;

//
// Version structure definition, 4 bytes
//
typedef union
{
    UINT32          abcd;
    struct
    {
        UCHAR8      a;
        UCHAR8      b;
        UCHAR8      c;
        UCHAR8      d;
    } part;
} FT_VER;

//
// Versions of hardware and firmware components, 16 bytes
//
typedef struct
{
    FT_VER          hardware;   // Version of hardware (hardware.part.a = 'A' or 'B' or 'C')
    FT_VER          firmware;   // Version of firmware ("V %d.%02d, DLL %d", firmware.part.c,
                                // firmware.part.d, firmware.part.b)
    FT_VER          ta;         // Version of transfer area ("V %d.%02d", ta.part.c, ta.part.d)
    char            reserved[4];
} FT_VERSION;

//
// Structures for Transfer Area
//
//
// Info structure, 64 bytes
//
typedef struct
{
    char            device_name[DEV_NAME_LEN_MAX + 1];  // Controller name
    char            bt_addr[BT_ADDR_STR_LEN + 1];       // Bluetooth address as a string
    char            reserved;
    UINT32          ta_array_start_addr;
    UINT32          pgm_area_start_addr;
    UINT32          pgm_area_size;
    FT_VERSION      version;
} TA_INFO;

//
// State structure, 100 bytes
//
typedef struct
{
    // Used by local program
    BOOL8           pgm_initialized;
    char            reserved_1[7];

    // Public state info
    BOOL8           dev_mode;   // See enum dev_mode_e
    UINT8           id;         // Should be increased by 1 each time something (except id fields and btstatus)
                                // is changed in this state structure
    UINT8           info_id;    // Should be increased by 1 each time something is changed in info structure
    UINT8           config_id;  // Should be increased by 1 each time something is changed in config structure
    BOOL8           ext_dev_connect_state[N_EXT];    // See enum ext_dev_connect_state_e
    BT_STATUS       btstatus[BT_CNT_MAX];   // Status of Bluetooth connections
    char            reserved_2[8];
    PGM_INFO        local_pgm;  // Corresponds to the program currently being in the program memory
} TA_STATE;

//
// Input structure, 48 bytes
//
typedef struct
{
    INT16           uni[N_UNI];             // Current values of the universal inputs
    UINT8           cnt_in[N_CNT];          // Current levels (0 or 1) on the counter inputs according
                                            // to their configuration (normal or inverse)
    INT16           counter[N_CNT];         // Current values of the counter inputs
    INT16           display_button_left;    // Number of milliseconds during which the left display button
                                            // is being kept pressed
    INT16           display_button_right;   // Number of milliseconds during which the right display button
                                            // is being kept pressed
    char            reserved[16];
} TA_INPUT;

//
// Output structure, 44 bytes
//
typedef struct
{
    unsigned short  cnt_reset_cmd_id[N_CNT];  // Counter reset requests (should be increased by 1 each time
                                              // counter reset is needed)
    unsigned char   master[N_MOTOR];          // If not 0, synchronize this channel with the given channel
                                              // (1:channel 0, ...)
    short           duty[N_PWM_CHAN];         // Selected motor outputs PWM values
    unsigned short  distance[N_MOTOR];        // Selected distance (counter value) at which motor shall stop
    unsigned short  motor_ex_cmd_id[N_MOTOR]; // Should be increased by 1 each time settings for extended
                                              // motor control mode (duty and/or distance) are changed
} TA_OUTPUT;

//
//  CMD=0x02 Request structure
//
typedef struct {
    UINT32      TAId;
    TA_OUTPUT   X1Data;
} CMD002_REQ;

//
//  CMD=0x02 Reply structure
//
typedef struct {
    UINT32      TAId;
    TA_INPUT    X1Data;
} CMD002_REPLY;

//
//  CMD=0x05 Reply structure
//
typedef struct {
    UINT32	TAId;
} CMD005_REPLY;

//
//  CMD=0x06 Reply structure
//
typedef struct {
    UINT32      TAId;
    TA_INFO     X1Data;
} CMD006_REPLY;

//
//  CMD=0x07 Reply structure
//
typedef struct {
  UINT32	TAId;
  TA_STATE	X1Data;
} CMD007_REPLY;


enum eX1FSMState {
    UNKNOWN_STATE = 0,
    FSM_WAIT_STX,
    FSM_WAIT_55,
    FSM_WAIT_L_1,
    FSM_WAIT_L_2,
    FSM_WAIT_DATA,
    FSM_WAIT_CS_1,
    FSM_WAIT_CS_2,
    FSM_WAIT_ETX
};

enum eSHFSMState {
    S_STATE_UNKNOWN = 0,
    GET_0D_START,
    GET_67,
    GET_0D_END
};

unsigned char   rxData[BUF_MAXLEN];
unsigned char   txData[BUF_MAXLEN];
unsigned char   tmpData[BUF_MAXLEN];

unsigned int    x1FSMState;
unsigned int    x1SHFSMState;

unsigned char   *pDataPtr;
unsigned short  nRXDataLen;

unsigned short  nX1DataLen;
unsigned short  nX1DataCnt;
unsigned short  nX1CheckSum;
unsigned short  nCheckSum;

unsigned short  nX1TicketId;
unsigned short  nX1SessionId;

#endif

