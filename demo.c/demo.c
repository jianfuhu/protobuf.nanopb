#include <stdio.h>
#include <stdint.h>
#include "demo.pb.h"
#include "nanopb/pb_encode.h"
#include "nanopb/pb_decode.h"
/*****************************************************************
 *  MACROS
 */
#define  nanopb_init_en(messageType, buffer, len) \
                messageType msg = messageType ## _init_default;  \
                buffer[0] = msg.cmdId; \
                pb_ostream_t ostream = pb_ostream_from_buffer((pb_byte_t*)&buffer[1], len-1)

#define  nanopb_init_de(messageType, buffer, len) \
               messageType msg = messageType ## _init_default;  \
               pb_istream_t istream = pb_istream_from_buffer((pb_byte_t*)&buffer[1], len-1)

#define  nanopb_encode(messageType) pb_encode(&ostream, messageType ## _fields, &msg)
#define  nanopb_decode(messageType) pb_decode(&istream, messageType ## _fields, &msg)

int main(void)
{
    uint8_t buffer[256], size;
    {//Encode
        nanopb_init_en(msgSayHello, buffer, sizeof(buffer));
        sprintf(msg.msg, "hello world.");
        nanopb_encode(msgSayHello);
        size = ostream.bytes_written + 1;
    }
    {//Print to console
        for(int i=0; i<size; i++)
        {
            if(i == 0)
                printf("Encode[msgSayHello]: %02x", buffer[i]);
            else
                printf(" %02x", buffer[i]);
        }printf("\n");
    }
    {//Decode
        nanopb_init_de(msgSayHello, buffer, size);
        if(nanopb_decode(msgSayHello))
            printf("Decode[msgSayHello]: %s\n", msg.msg);
        else
            printf("Cannot decode the message.\n");
    }
}
