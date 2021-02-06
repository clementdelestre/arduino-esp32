
#ifndef NETOUTPUT_H_INCLUDED
#define NETOUTPUT_H_INCLUDED

class NetOutput {
    private:


    public:
        NetOutput();

        //Ecris un boolean (8 bits)
        void writeBoolean(bool boolean);

        //Ecris un unsigned byte (8 bits, 0 -> 255)
        void writeUByte(unsigned int byte);

        //Ecris un signed byte (8 bits, -128 -> 127)
        void writeByte(signed int byte);

        //Ecris un unsigned short (16 bits, 0 -> 65535)
        void writeUShort(unsigned short value);

        //Ecris un signed short (16 bits, -32768 -> 32767)
        void writeShort(signed short value);

        //Ecris un unsigned int (32 bits, 0 -> 4294967295)
        void writeUInt(unsigned int value);

        //Ecris un signed int (32 bits, -2147483648 -> 2147483647)
        void writeInt(signed int value);

        //Ecris un unsigned long (?)
        void writeULong(unsigned long value);

        //Ecris un signed long
        void writeLong(signed long value);

        //Ecris un nombre à virgule à double précision
        void writeDouble(double value);

        //Ecris un float
        void writeFloat(float value);

        //Ecris un tableau de caractère
        void writeString(char* value);


};

#endif