#include <cmdserial.h>>
#include<Stream.h>

cmdserial::cmdserial(){

}

cmdserial::cmdserial(Stream* iface){
    _iface = iface;

}

cmdserial::~cmdserial(){

}

void cmdserial::sendCmd(uint8_t cmd,uint8_t* data,uint8_t len){
    uint8_t cmdstr[255] = {};
    uint8_t finallen = len + 5;
    cmdstr[0] = 60;
    cmdstr[1] = cmd;
    cmdstr[2] = len;
    cmdstr[3] = 58;
    for (uint8_t i = 0; i < len; i++){
        cmdstr[4 + i] = *data;
        data++;
    }
    cmdstr[4 + len] = 62;
    if(_debug == 1){
        _iface-> print("Sent Command: ");
        _iface-> write(cmdstr,finallen);
    }
    _iface -> write(cmdstr,finallen);
}


void cmdserial::decode(uint8_t *command,uint8_t cmdlen){
    // _iface->write(command,cmdlen);
    // _iface->write(10);
    uint8_t cmdi = 0;
    uint8_t len = 0;
    uint8_t data[255] = {};
    uint8_t idx = 0;
    uint8_t initiali = 0;
    // Look for the starting of command
    while (*command != 60){
        initiali ++;
        command++;
    }
    for (uint8_t i = initiali; i < cmdlen; i++){
        if (i == initiali + 1){cmdi = *command;}
        if (i == initiali + 2){len = *command;}
        if (i > initiali + 3 && i < cmdlen -1){data[idx] = *command; idx++;}
        command ++;
    }

    if(cmdi == 49){
        execute(_callbacks[cmdi],data,idx);
        if( _debug == 1 ){
            _iface->write(cmdi);
            _iface->write(" ");
            _iface->write(len);
            _iface->write(" ");
            _iface->write(data,idx);
            _iface->write(10);
        }
    }
    // _iface->write("cmd:");
}

void cmdserial::setIface(Stream* iface){
    _iface = iface;
}

void cmdserial::writeRaw(uint8_t* data,uint8_t len){
    _iface -> write(data,len);
}

void cmdserial::onLoop(){
    if(_iface -> available() > 0){
        uint8_t cmdin[255] = {};
        uint8_t i = 0;
        while (_iface->available() > 0){cmdin[i] = _iface->read();delayMicroseconds(270);i++;}
        //_iface->write(cmdin,i);
        if( _debug == 1 ){ _iface -> print("Received Command: "); }
        decode(cmdin,i);
        
    }
}

bool cmdserial::isCommand(uint8_t* cmd,uint8_t len){
    bool iscmd = 0;
    for (uint8_t i = 0; i < len; i++){

    }
    return iscmd;
}

void cmdserial::execute(callback cbk, uint8_t* data, uint8_t len){
    cbk(data,len);
}

void cmdserial::setCbk(uint8_t cmd, callback cbk){
    _callbacks[cmd] = cbk;
}