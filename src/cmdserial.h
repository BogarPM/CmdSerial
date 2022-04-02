#ifndef CMDSERIAL_H
#define CMDSERIAL_H

#include<Stream.h>

class cmdserial
{
private:
    Stream* _iface;
public:
    cmdserial();
    cmdserial(Stream *iface,int baud);
    void sendCmd(uint8_t cmd,uint8_t *data,uint8_t len);
    void decode(uint8_t *command);
    void setIface(Stream* iface);
    void writeRaw(uint8_t* data,uint8_t len);
    ~cmdserial();
};


#endif