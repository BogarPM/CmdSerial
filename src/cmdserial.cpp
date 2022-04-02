#include <cmdserial.h>>
#include<Stream.h>

cmdserial::cmdserial(){

}

cmdserial::cmdserial(Stream* iface,int baud){
    _iface = iface;

}

cmdserial::~cmdserial(){

}

void cmdserial::sendCmd(uint8_t cmd,uint8_t* data,uint8_t len){
    char cmdstr[255] = "";
    cmdstr[0] = "<";
    cmdstr[1] = cmd;
    cmdstr[2] = ":";
    for (uint8_t i = 0; i < len; i++){
        cmdstr[3 + i] = *data;
        data++;
    }
    cmdstr[3 + len] = ">";

    _iface -> write(cmdstr,len + 4);

}


void cmdserial::decode(uint8_t *command){

}

void cmdserial::setIface(Stream* iface){
    _iface = iface;
}

void cmdserial::writeRaw(uint8_t* data,uint8_t len){
    _iface -> write(data,len);
}