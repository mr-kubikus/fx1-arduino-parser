//
// 16 bit data access
//
void set16BitLE(unsigned char *pData, UINT16 value)
{
    *(pData+0) = value & 0xFF;
    *(pData+1) = (value >> 8) & 0xFF;
}

UINT16 get16BitLE(unsigned char *pData)
{
    UINT16 value = 0;
    value  = *(pData+0);
    value += (*(pData+1) << 8) & 0xFF00;
    return value;
}

void set16BitBE(unsigned char *pData, UINT16 value)
{
    *(pData+0) = (value >> 8) & 0xFF;
    *(pData+1) = value & 0xFF;
}

UINT16 get16BitBE(unsigned char *pData)
{
    UINT16 value = 0;
    value  = (*(pData+0) << 8) & 0xFF00;
    value += *(pData+1);
    return value;
}

//
// 32 bit data access
//
void set32BitLE(unsigned char *pData, UINT32 value)
{
    *(pData+0) = value & 0xFF;
    *(pData+1) = (value >> 8)  & 0xFF;
    *(pData+2) = (value >> 16) & 0xFF;
    *(pData+3) = (value >> 24) & 0xFF;
}

UINT32 get32BitLE(unsigned char *pData)
{
    UINT32 value = 0;
    value  = *(pData+0);
    value += *(pData+1) << 8;
    value += *(pData+2) << 16;
    value += *(pData+3) << 24;
    return value;
}

void set32BitBE(unsigned char *pData, UINT32 value)
{
    *(pData+0) = (value >> 24) & 0xFF;
    *(pData+1) = (value >> 16) & 0xFF;
    *(pData+2) = (value >> 8) & 0xFF;
    *(pData+3) = value & 0xFF;
}


unsigned short calcCheckSum(unsigned char Message[], int nBytes)
{
    unsigned short  sum = 0;
    
    while(nBytes-- > 0) {
      sum += *(Message++);
    }
    sum = (~sum);
    sum++;

    return sum;
}

