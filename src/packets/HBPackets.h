#ifndef HBPACKETS_HEADER
#define HBPACKETS_HEADER

class HBPackets
{
public:
    HBPackets(char buffer[]);
    // ~HBPackets();

    void DeserializeHeader();
    void Serialize();

    // Pure virutal function, needs to be defined by derived class.
    virtual void DeserializePayload() = 0;

    uint16_t GetLength();
    uint8_t GetCommand();
    uint8_t GetVersion();
    uint8_t GetCheckVersion();
    uint8_t GetToken();
private:
    // p = packet
    uint16_t m_pLength;
    uint8_t m_pCommand;
    uint8_t m_pVersion;
    uint8_t m_pCheckVersion;
    uint8_t m_pToken;

    char* m_buffer;
};

#endif