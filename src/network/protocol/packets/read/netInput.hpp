
#ifndef NETINPUT_H_INCLUDED
#define NETINPUT_H_INCLUDED

class NetInput {
    private:



    public:
        NetInput();

        //Lis un boolean (8 bits)
        bool readBoolean();

        //Lis un unsigned byte (8 bits, 0 -> 255)
        unsigned char readUByte();

        //Lis un signed byte (8 bits, -128 -> 127)
        signed char readByte();

        //Lis un unsigned short (16 bits, 0 -> 65535)
        unsigned short readUShort();

        //Lis un signed short (16 bits, -32768 -> 32767)
        signed short readShort();

        //Lis un unsigned int (32 bits, 0 -> 4294967295)
        unsigned int readUInt();

        //Lis un signed int (32 bits, -2147483648 -> 2147483647)
        signed int readInt();

        //Lis un unsigned long (?)
        unsigned long readULong();

        //Lis un signed long
        signed long readLong();

        //Lis un nombre à virgule à double précision
        double readDouble();

        //Lis un float
        float readFloat();

        //Lis un tableau de caractère
        char* readString();
};

#endif