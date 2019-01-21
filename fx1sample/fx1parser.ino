//
// ROBO Pro to Arduino pins map:
//

// Outputs
const int OUT1 =  6; //
const int OUT2 =  7; //
const int OUT3 =  8; //
const int OUT4 =  9; // PWM
const int OUT5 = 10; // PWM
const int OUT6 = 11; // PWM
const int OUT7 = 12; // 
const int OUT8 = 13; // 

// Inputs
const int IN1 =  2; // 
const int IN2 =  3; //
const int IN3 =  4; //
const int IN4 = A0; // Analog
const int IN5 = A1; // Analog
const int IN6 = A2; // Analog
const int IN7 = A3; // Analog
const int IN8 = A4; // Analog

void fx1ParserInit()
{
  x1FSMState   = FSM_WAIT_STX;
  x1SHFSMState = GET_0D_START;
  nX1TicketId  = 0;
  nX1SessionId = 0;  
  
  // Configure the output pins:
  pinMode(OUT1, OUTPUT);
  pinMode(OUT2, OUTPUT);
  pinMode(OUT3, OUTPUT);
  pinMode(OUT4, OUTPUT);
  pinMode(OUT5, OUTPUT);
  pinMode(OUT6, OUTPUT);
  pinMode(OUT7, OUTPUT);
  pinMode(OUT8, OUTPUT);
  
  digitalWrite(OUT1, LOW);
  digitalWrite(OUT2, LOW);
  digitalWrite(OUT3, LOW);
  digitalWrite(OUT4, LOW);
  digitalWrite(OUT5, LOW);
  digitalWrite(OUT6, LOW);
  digitalWrite(OUT7, LOW);
  digitalWrite(OUT8, LOW);
  
  // Configure the input pins:
  pinMode(IN1, INPUT_PULLUP);
  pinMode(IN2, INPUT_PULLUP);
  pinMode(IN3, INPUT_PULLUP); 
}

void fx1ParserParse(unsigned char  symbol)
{
  switch (x1SHFSMState) {
    case GET_0D_START:
      if ( symbol != 0x0D ) break;
      x1SHFSMState = GET_67;
      break;
      
    case GET_67:
      if ( symbol != 0x67 ) {
        x1SHFSMState = GET_0D_START;
        break;
      }
      x1SHFSMState = GET_0D_END;      
      break; 
    
    case GET_0D_END: 
      if ( symbol != 0x0D ) break;
      sendShellData();
      x1SHFSMState = GET_0D_START;      
      break; 
    
    default:
      break;      
  }
  
  switch (x1FSMState) {
    case FSM_WAIT_STX:
      if ( symbol == 0x02 ) {
        nRXDataLen = 0;
        pDataPtr = rxData;
        *(pDataPtr) = symbol;
        nRXDataLen++;
        x1FSMState = FSM_WAIT_55;
        break;
      }
      break;
    
    case FSM_WAIT_55:
      if ( symbol != 0x55 ) {
        x1FSMState = FSM_WAIT_STX;
	break;
      }
      *(pDataPtr+nRXDataLen) = symbol;
      nRXDataLen++;
      nX1DataLen = 0;
      nCheckSum  = 0;
      x1FSMState = FSM_WAIT_L_1;
      break;
      
    case FSM_WAIT_L_1:   
      nX1DataLen = ((symbol << 8) & 0xFF00);
      nCheckSum += symbol;
      *(pDataPtr+nRXDataLen) = symbol;
      nRXDataLen++;
      x1FSMState = FSM_WAIT_L_2;
      break;
    
    case FSM_WAIT_L_2:
      nX1DataLen += symbol;
      nCheckSum += symbol;
      *(pDataPtr+nRXDataLen) = symbol;
      nRXDataLen++;
      nX1DataCnt = 0;
      x1FSMState = FSM_WAIT_DATA;
      break;

    case FSM_WAIT_DATA:
      nCheckSum += symbol;
      *(pDataPtr+nRXDataLen) = symbol;
      nRXDataLen++;
      nX1DataCnt++;

      if ( nX1DataCnt == nX1DataLen )
          x1FSMState = FSM_WAIT_CS_1;
      break;
  
    case FSM_WAIT_CS_1:
      nX1CheckSum = ((symbol << 8) & 0xFF00);
      x1FSMState = FSM_WAIT_CS_2;
      break;
  
    case FSM_WAIT_CS_2:
      nX1CheckSum += symbol;
      x1FSMState = FSM_WAIT_ETX;
      break;
  
    case FSM_WAIT_ETX:
      if ( symbol != 0x03 ) {
          x1FSMState = FSM_WAIT_STX;
          return;
      }

      nCheckSum = (~nCheckSum) + 1;
      if ( nCheckSum != nX1CheckSum ) {
          x1FSMState = FSM_WAIT_STX;
          return;
      }

      //fx1ParserProcPacket(pDataPtr+CMD_HEAD_OFFS, nRXDataLen);
      fx1ParserProcPacket(pDataPtr, nRXDataLen);
      
      x1FSMState = FSM_WAIT_STX;
      break;
                
    default:
      break;      
  }     
}

//
// Execute callback functions according to command code CMD in received packet.
//
void fx1ParserProcPacket(unsigned char *pData, int nDataLength)
{
  short nCmd   = get32BitLE(pData+16);
  short nItems = get32BitLE(pData+20);

  nX1TicketId  = get16BitLE(pData+12);    

  //
  // Select and call reply function for received CMD code
  //
  switch(nCmd) {
    case CMD_001  : CMD001Reply(nItems, pData+24);
      break;
    
    case CMD_002  : CMD002Reply(nItems, pData+24);
      break;
    
    case CMD_005  : CMD005Reply(nItems, pData+24);
      break;
    
    case CMD_006  : CMD006Reply(nItems, pData+24);
      break;
    
    case CMD_007  : CMD007Reply(nItems, pData+24);
      break;
    
    default:
      break;
  }
        
}

void CMD001Reply(short nItems, unsigned char *data)
{
  sendX1Data(txData, CMD_001_REPLY, 0, (unsigned char*)NULL, 0);
}

void CMD002Reply(short nItems, unsigned char *data)
{
  CMD002_REQ *request = (CMD002_REQ *) data ;
  
  if (request->X1Data.duty[0] != 0) {
    digitalWrite(OUT1, HIGH);
  } else {
    digitalWrite(OUT1, LOW);
  }

  if (request->X1Data.duty[1] != 0) {
    digitalWrite(OUT2, HIGH);
  } else {
    digitalWrite(OUT2, LOW);
  }

  if (request->X1Data.duty[2] != 0) {
    digitalWrite(OUT3, HIGH);
  } else {
    digitalWrite(OUT3, LOW);
  }

  analogWrite(OUT4, constrain(request->X1Data.duty[3] / 2 , 0, 255));
  analogWrite(OUT5, constrain(request->X1Data.duty[4] / 2 , 0, 255)); 
  analogWrite(OUT6, constrain(request->X1Data.duty[5] / 2 , 0, 255));
    
  if (request->X1Data.duty[6] != 0) {
    digitalWrite(OUT7, HIGH);
  } else {
    digitalWrite(OUT7, LOW);
  }
  
  if (request->X1Data.duty[7] != 0) {
    digitalWrite(OUT8, HIGH);
  } else {
    digitalWrite(OUT8, LOW);
  }
  
  CMD002_REPLY *reply = (CMD002_REPLY *) data;  
  
  memset((unsigned char*)reply, 0, sizeof(CMD002_REPLY));
  reply->TAId = TA_LOCAL;  
  reply->X1Data.uni[0]=digitalRead(IN1);
  reply->X1Data.uni[1]=digitalRead(IN2);
  reply->X1Data.uni[2]=digitalRead(IN3);
  reply->X1Data.uni[3]=map(analogRead(IN4), 0, 1023, 0, 500);
  reply->X1Data.uni[4]=map(analogRead(IN5), 0, 1023, 0, 500);
  reply->X1Data.uni[5]=map(analogRead(IN6), 0, 1023, 0, 500);
  reply->X1Data.uni[6]=map(analogRead(IN7), 0, 1023, 0, 500);
  reply->X1Data.uni[7]=map(analogRead(IN8), 0, 1023, 0, 500);
  
  sendX1Data(txData, CMD_002_REPLY, 1, (unsigned char*)reply, sizeof(CMD002_REPLY)); 
}

void CMD005Reply(short nItems, unsigned char *data)
{
  CMD005_REPLY *reply = (CMD005_REPLY *) data;
    
  memset((unsigned char*)reply, 0, sizeof(CMD005_REPLY));
  reply->TAId = TA_LOCAL;  
  sendX1Data(txData, CMD_005_REPLY, 1, (unsigned char*)reply, sizeof(CMD005_REPLY)); 
}

void CMD006Reply(short nItems, unsigned char *data)
{
  CMD006_REPLY *reply = (CMD006_REPLY *) tmpData;

  memset((unsigned char*)reply, 0, sizeof(CMD006_REPLY));
  reply->TAId = TA_LOCAL;
  sprintf(reply->X1Data.device_name, "ROBO TX-000");
  sprintf(reply->X1Data.bt_addr, "00:00:00:00:00:00");
  
  reply->X1Data.ta_array_start_addr = 0; // Sniffed value 0x20000204
  reply->X1Data.pgm_area_start_addr = 0; // Sniffed value 0x30700000
  reply->X1Data.pgm_area_size = 0;       // Sniffed value 0x000d0000
  
  reply->X1Data.version.hardware.part.a = 0x43; // 67
  reply->X1Data.version.hardware.part.b = 0x00;
  reply->X1Data.version.hardware.part.c = 0x00;
  reply->X1Data.version.hardware.part.d = 0x00; 
  
  reply->X1Data.version.firmware.part.a = 0x00; // 0
  reply->X1Data.version.firmware.part.b = 0x06; // 6 
  reply->X1Data.version.firmware.part.c = 0x01; // 1
  reply->X1Data.version.firmware.part.d = 0x1E; // 30  

  reply->X1Data.version.ta.part.a = 0x01;
  reply->X1Data.version.ta.part.b = 0x01;
  reply->X1Data.version.ta.part.c = 0x01;
  reply->X1Data.version.ta.part.d = 0x08; 
  
  sendX1Data(txData, CMD_006_REPLY, 1, (unsigned char*)reply, sizeof(CMD006_REPLY));
}

void CMD007Reply(short nItems, unsigned char *data)
{
  CMD006_REPLY *reply = (CMD006_REPLY *) tmpData;

  memset((unsigned char*)reply, 0, sizeof(CMD006_REPLY));
  reply->TAId = TA_LOCAL;
  
  sendX1Data(txData, CMD_007_REPLY, 1, (unsigned char*)reply, 28);
}

void sendShellData(void)
{
  short ii=0;
  
  sprintf((char*)txData, "\r\nROBO TX-000/USB>get_ser_num\r\n0000000001\r\nROBO TX-000/USB>");

  while (ii < 0x3B) {
    Serial.write(txData[ii]);
    ii++;
  }
}

void sendX1Data(UINT8 *pPacket, int replyID, short items, unsigned char *pData, short dataLength)
{
    int    packetLength = 0;
    UINT16 nCheckSum = 0;
    
    //
    // Fill the packet structure with data according FishX1 protocol structure from PDF
    //
    // Set STX + 0x55
    *(pPacket+0) = 0x02;
    *(pPacket+1) = 0x55;
    packetLength += 2;

    // Set Total length
    set16BitBE(pPacket+2, dataLength+20);
    packetLength += 2;

    // Set FROM
    set32BitLE(pPacket+4, 2);
    packetLength += 4;

    // Set TO
    set32BitLE(pPacket+8, 2);
    packetLength += 4;

    // Set TID
    set16BitLE(pPacket+12, nX1TicketId);
    packetLength += 2;

    // Set SID
    set16BitLE(pPacket+14, nX1SessionId);
    packetLength += 2;

    // Set Command Code
    set32BitLE(pPacket+16, replyID);
    packetLength += 4;

    // Set Number of following Fish.X1 data structures
    set32BitLE(pPacket+20, items);
    packetLength += 4;

    // Set TA ID and Fish.X1 data
    memcpy((void*)(pPacket+24), (void*)pData, dataLength);
    packetLength += dataLength;

    // Set CheckSum
    nCheckSum = calcCheckSum(pPacket+2, packetLength-2);
    set16BitBE(pPacket+packetLength, nCheckSum);
    packetLength += 2;

    // Set ETX
    *(pPacket+packetLength) = 0x03;
    packetLength++;

    short dataCounter=0;

    while (dataCounter < packetLength) {
      Serial.write(pPacket[dataCounter]);
      dataCounter++;
    }
    
    return;
}
