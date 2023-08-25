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

#define OPT3001_LENGTH   2

#define EXP_MASK 15

extern uint8_t Opt3001SlaveBuffer[OPT3001_LENGTH] = {0};

//******************************************************************************
// Use to get the Opt3001 Lux data *********************************************
//******************************************************************************
//uint16_t caculateQuadraticValue(char number)
uint16_t caculateQuadraticValue(char number)
{
    uint8_t count;
    //uint16_t returnValue =1;
    uint16_t returnValue =1;
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

    //BIT10 and BIT9 being 1 means Continuous Conversions are on.

    //BIT0 being 1 means *two* (rather than 1, default) concecutive *fault events*
    //are required to trigger the interrupt reporting mechanisms (explained in doc). INT pin, flag high/flag low fields
}
uint32_t getOpt3001LuxData(void)
{
    uint32_t luxData;
    uint32_t quadResult;
    uint32_t linResult;
    I2C_Master_ReadReg(OPT3001_SLAVE_ADDR, 0x00, OPT3001_LENGTH);//read to result register
    CopyArray(ReceiveBuffer, Opt3001SlaveBuffer, OPT3001_LENGTH);
    quadResult = (caculateQuadraticValue(Opt3001SlaveBuffer[0]>>4));
    linResult = ((Opt3001SlaveBuffer[0]&EXP_MASK)<<8) + Opt3001SlaveBuffer[1];
    luxData = quadResult * linResult;
    //JACK: luxData = x * y:
    //x = 2^a, where
    //a = 4 leftmost (MSB?) bits of cell 0.

    //y = buffer[0] * 2^8  + buffer[1] -- suspect this is just decimal format

    return luxData;
}
