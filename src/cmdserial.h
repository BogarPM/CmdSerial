#ifndef CMDSERIAL_H
#define CMDSERIAL_H

#include<Stream.h>
#include<Arduino.h>

typedef void (*callback) (uint8_t* data, uint8_t len);

class cmdserial
{
private:
    bool _debug = 0;
    callback _callbacks[255] = {};
    Stream* _iface;
    bool isCommand(uint8_t* cmd,uint8_t len);
    void execute(callback cbk, uint8_t* data, uint8_t len);
public:
    cmdserial();
    cmdserial(Stream *iface);
    void sendCmd(uint8_t cmd,uint8_t *data,uint8_t len);
    void decode(uint8_t *command,uint8_t len);
    void setIface(Stream* iface);
    void writeRaw(uint8_t* data,uint8_t len);
    ~cmdserial();
    void setCbk(uint8_t cmd, callback cbk);

    void onLoop();
};


#endif