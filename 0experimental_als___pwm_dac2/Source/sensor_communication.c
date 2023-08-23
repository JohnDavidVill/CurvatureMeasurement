#include "sensor_communication.h"


/* CMD_TYPE_X_SLAVE are example commands the master sends to the slave.
 * The slave will send example SlaveTypeX buffers in response.
 *
 * CMD_TYPE_X_MASTER are example commands the master sends to the slave.
 * The slave will initialize itself to receive MasterTypeX example buffers.
 * */

#define CMD_TYPE_0_SLAVE      0
#define CMD_TYPE_1_SLAVE      1
#define CMD_TYPE_2_SLAVE      2

#define CMD_TYPE_0_MASTER      3
#define CMD_TYPE_1_MASTER      4
#define CMD_TYPE_2_MASTER      5

#define TMP117_LENGTH    2
#define OPT3001_LENGTH   2
#define HDC2080_LENGTH   1

extern uint8_t Opt3001SlaveBuffer[OPT3001_LENGTH] = {0};
extern uint8_t TMP117SlaveBuffer[TMP117_LENGTH] = {0};
extern uint8_t HDC2080SlaveBuffer[HDC2080_LENGTH] = {0};

//******************************************************************************
// Use to get the Opt3001 Lux data *********************************************
//******************************************************************************
//uint16_t caculateQuadraticValue(char number)
uint32_t caculateQuadraticValue(char number)
{
    uint8_t count;
    //uint16_t returnValue =1;
    uint32_t returnValue =1;
    for(count=0; count<number; count++)
    {
        returnValue = returnValue*2;
    }
    return returnValue;
}
//00h (h=hex) = Result address
//01h         = Configuration address
//02h         = Low Limit address
//03h         = High Limit address

void opt3001Init()
{
    Opt3001SlaveBuffer[0] =0xCE; //Make OPT3001 works under continues mode
    Opt3001SlaveBuffer[1] =0x01;
    I2C_Master_WriteReg(OPT3001_SLAVE_ADDR, 0x01, Opt3001SlaveBuffer, OPT3001_LENGTH);
    //Writes 01CE (hex) to register 01h (configuration register) in the OPT3001 - light sensor.
    //This is equivalent to Buffer[0] |= BIT1 | BIT2 | BIT3 | BIT6 | BIT7
    //                      Buffer[1] |= BIT0

    //Given that they mentioned continuous mode, 10:9 must be 10 or 11. So, it's 0xCE, 0x01, as expected.
    //Just shift Buffer[0]'s on bits 8 to the left (so, |= BIT9 | BIT10 | BIT11 | BIT14 | BIT15) to see the register effect.

    //So, what is set? Well, RN - 15:12 - is 1100b, which enables Automatic Full-Scale Setting Mode.
    //In this mode, the range is reported in the result exponent - bits 15:12 of reg-offset 0x00 (results).

    //BIT11 means the conversion time field is 800ms rather than 100ms, slower but more accurate.

    //BIT10 and BIT9 being 1 means Continuous Conversions are on, read more about alternatives (singleshot etc) later. ##TODO

    //BIT0 being 1 means *two* (rather than 1, default) concecutive *fault events*
    //     are required to trigger the interrupt reporting mechanisms (explained in doc). INT pin, flag high/flag low fields ##TODO read those


    //I think it's better to only deconvert the Lux once it's in Python territory, either that or expand the ints usable for it.
    //Currently it seems to overflow easily with the 65535 max. Try expanding the usable ints first? To test before Python.
}
//uint16_t getOpt3001LuxData(void)
uint32_t getOpt3001LuxData(void)
{
    //uint16_t luxData;
    uint32_t luxData;
    I2C_Master_ReadReg(OPT3001_SLAVE_ADDR, 0x00, OPT3001_LENGTH);//read to result register
    CopyArray(ReceiveBuffer, Opt3001SlaveBuffer, OPT3001_LENGTH);
    luxData = ((caculateQuadraticValue(Opt3001SlaveBuffer[0]>>4))*((Opt3001SlaveBuffer[0]<<8) + Opt3001SlaveBuffer[1]));
    //JACK: luxData = x * y:
    //x = 2^a, where
    //a = 4 leftmost (MSB?) bits of cell 0.

    //y = buffer[0] * 2^8  + buffer[1] -- suspect this is just decimal format

    return luxData;
}
//******************************************************************************
// Use to get the Opt3001 Lux data *********************************************
//******************************************************************************
int8_t getTmp117TemperatureData(void)
{
    uint16_t tempData;
    I2C_Master_ReadReg(TMP117_SLAVE_ADDR, 0x00, TMP117_LENGTH);//read to result register
    CopyArray(ReceiveBuffer, TMP117SlaveBuffer, TMP117_LENGTH);
    tempData = (TMP117SlaveBuffer[0]<<8)+ TMP117SlaveBuffer[1];

    if(tempData<0x8000) //temp>0 C
    {
        return (tempData/(0x7FFF>>8));
    }
    else
    {
        return -((0xFFFF-tempData)/(0x7FFF>>8));
    }
}

//******************************************************************************
// Use to get the Humidity data *********************************************
//******************************************************************************
uint8_t getHdc2080HumidityData(void)
{
    uint32_t humidityData;
    HDC2080SlaveBuffer[0] =0x01;
    I2C_Master_WriteReg(HDC2080_SLAVE_ADDR, 0x0F, HDC2080SlaveBuffer,HDC2080_LENGTH);//Write to result register
    __delay_cycles(16000); //1ms
    __delay_cycles(16000); //1ms
    __delay_cycles(16000); //1ms
    I2C_Master_ReadReg(HDC2080_SLAVE_ADDR, 0x02, HDC2080_LENGTH);//Read result register
    CopyArray(ReceiveBuffer, HDC2080SlaveBuffer, HDC2080_LENGTH);
    humidityData = HDC2080SlaveBuffer[0];
    I2C_Master_ReadReg(HDC2080_SLAVE_ADDR, 0x03, HDC2080_LENGTH);//Read result register
    CopyArray(ReceiveBuffer, HDC2080SlaveBuffer, HDC2080_LENGTH);
    humidityData += (HDC2080SlaveBuffer[0]<<8);
    return ((humidityData *100)>>16);
}

void hdc2080Init()
{

}
