#ifndef PROTOCOL_DHT_H
#define PROTOCOL_DHT_H

// format : message'\n'
//  message : {"temperature":value,"humidity":value}
//    value : %.2f
//  message is json

int protocol_dht_isValid(char* buffer);

#endif  // PROTOCOL_DHT_H
