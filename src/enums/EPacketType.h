#ifndef EPACKETTYPE_HEADER
#define EPACKETTYPE_HEADER

enum EPacketType
{
    LOGIN = 0x60,
    HEARTBEAT = 0x61,
    QUERY_FIRMWARE = 0x62,
    SET_NEW_ADDRESS = 0x63,
    QUERY_POWERBANKS = 0x64,
    RENT = 0x65,
    RETURN = 0x66,
    REMOTE_RESTART = 0x67,
    REMOTE_UPDATE = 0x68,
    QUERY_ICCID = 0x69,
    EJECT = 0x80,
    Last, // Required so we can end our loop through the enum
};

#endif