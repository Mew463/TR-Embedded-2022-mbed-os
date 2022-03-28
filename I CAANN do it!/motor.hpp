#include "mbed.h"
#include <cstdint>
#ifndef motor_hpp
#define motor_hpp
#include "CANMsg.h"

#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c"
#define BYTE_TO_BINARY(byte)  \
  (byte & 0x80 ? '1' : '0'), \
  (byte & 0x40 ? '1' : '0'), \
  (byte & 0x20 ? '1' : '0'), \
  (byte & 0x10 ? '1' : '0'), \
  (byte & 0x08 ? '1' : '0'), \
  (byte & 0x04 ? '1' : '0'), \
  (byte & 0x02 ? '1' : '0'), \
  (byte & 0x01 ? '1' : '0')

//////////////////////////////////////////////
//VERY IMPORTANT TO SET FREQUENCY HERE AND NOW
//////////////////////////////////////////////

CAN             can1(PA_11,PA_12,1000000);
CAN             can2(PB_12,PB_13,1000000);

static int feedbackIDs[8] = {0x201,0x202,0x203,0x204,0x205,0x206,0x207,0x208}; //IDs to recieve data back from the motors

static int sendIDs[2] = {0x200,0x1FF}; //IDs to send data

int16_t feedback[8][4] = {{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}}; //Array holding the feedback values of the individual motors

int totalMotors; //total number of motors in play

bool motorExists[8] = {0,0,0,0,0,0,0,0};

int16_t motorOut1[4] = {0,0,0,0}; //First four motors in can, controlled through ID 0x200

int16_t motorOut2[4] = {0,0,0,0}; //Second four motors in can, controlled through ID 0x1FF

bool motorDebug = 0;

CANMsg txMsg; //Message object reused to send messages to motors
CANMsg rxMsg; //Message object reused to recieve messages from motors

enum motorMode {DISABLED, POSITION, SPEED, CURRENT};
motorMode mode[8] = {DISABLED, DISABLED, DISABLED, DISABLED, DISABLED, DISABLED, DISABLED, DISABLED};
int multiTurnPositionAngle[8] = {0,0,0,0,0,0,0,0};

class Motor {

    public:

    int motorNumber;
    
    static char* byteToBits(int x){
        char out[8] = {0,0,0,0,0,0,0,0};
        for(int i = 0; i < 8; i++){
            out[8-i] = x & 1;
            x << 1;
        }
        return out;
    }

    /**
     * @brief Construct a new Motor object
     * 
     * @param canNum is a number from 1-8 signifying which CAN id is attached, blinking LED on motor controller will show this
     */
    Motor(int canNum)
    {
        motorNumber = canNum - 1; //Changes range from 1-8 to 0-7
        totalMotors++;
        motorExists[motorNumber] = 1;
        //TODO Throw error when motorNumber isnt within the range [0,7]
    }
    
    /**
     * @brief Set the desired value of this motor
     * 
     * @param value
     * @return int value
     */
    int setDesiredValue(int value){
        if(motorNumber < 4){
            motorOut1[motorNumber] = value;
            return motorOut1[motorNumber];
        }else if(motorNumber >= 4){
            motorOut2[motorNumber-4] = value;
            return motorOut2[motorNumber-4];
        }
        return -1;
    }

    void setDesiredCurrent(int value) {
        setDesiredValue(value);
        mode[motorNumber] = CURRENT;
    }

    void setDesiredSpeed(int value) {
        setDesiredValue(value);
        mode[motorNumber] = SPEED;
    }

    void setDesiredPos(int value) {
        setDesiredValue(value);
        mode[motorNumber] = POSITION;
    }
    
    static int PIDPositionError(int desiredAngle, int motorID) {
        int error = multiTurnPositionAngle[motorID] - desiredAngle;
        static unsigned long lastTime[8] = {0};
        unsigned long Time = us_ticker_read() / 1000;
        unsigned long timeDifference = Time - lastTime[motorID];

        static int lastError[8] = {0};
        static int sumerror[8] = {0};
        sumerror[motorID] += error;
        double kP = .1;
        double kI = 0;
        double kD = .1;

        if (abs(error) < 5000)
            sumerror[motorID] = 0;

        int maxsumerror = 2000;

        if (sumerror[motorID] > maxsumerror)
            sumerror[motorID] = maxsumerror;
        else if (sumerror[motorID] < -maxsumerror)
            sumerror[motorID] = -maxsumerror;   

    
        int PIDCalc = kP * error + kI * sumerror[motorID] + kD * ((double)(error - lastError[motorID])/timeDifference);

        int maxcurrent = 1000;
        if (PIDCalc > maxcurrent)
            PIDCalc = maxcurrent;
        else if (PIDCalc < -maxcurrent)
            PIDCalc = -maxcurrent;

        lastTime[motorID] = Time;
        error = lastError[motorID];

        return PIDCalc;
    }
    

    /**
     * @brief Get the desired value of the motor
     * 
     * @return int value
     */
    int getDesiredValue(){
        if(motorNumber < 4){
            return motorOut1[motorNumber];
        }else if(motorNumber >= 4){
            return motorOut2[motorNumber-4];
        }
        return -1;
    }

    /**
     * @brief Prints a CANMessage nicely
     * 
     * @param msg 
     */
    static void printMsg(CANMessage& msg)
    {
        printf("  ID      = 0x%.3x\r\n", msg.id);
        printf("  Type    = %d\r\n", msg.type);
        printf("  Format  = %d\r\n", msg.format);
        printf("  Length  = %d\r\n", msg.len);
        printf("  Data    =");
        for (int i = 0; i < msg.len; i++)
            printf(" 0x%.2X", msg.data[i]);
        printf("\r\n");
    }

    /**
     * @brief Get feedback back from the motor
     * 
     */
    static void getFeedback(){
        if (can1.read(rxMsg)) {
            if(motorDebug){
                printf("-------------------------------------\r\n");
                printf("CAN message received\r\n");
                printMsg(rxMsg);
            }
            int motorID = rxMsg.id-0x201;
            uint8_t recievedBytes[8] = {0,0,0,0,0,0,0,0};
            for(int i = 0;  i < 8; i ++){
                rxMsg >> recievedBytes[i]; //2 bytes per motor
            }
            if(motorDebug){
                printf("ArrayData    =");
                for (int i = 0; i < sizeof(recievedBytes); i++)
                    printf(" 0x%.2X", recievedBytes[i]);
                printf("\r\n");
            }
   
            feedback[motorID][0] = 0 | (recievedBytes[0]<<8) | recievedBytes[1];
            //printf("Bits: "BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(recievedBytes[0]));
            //printf(BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(recievedBytes[1]));
            //printf(" - %d\n", feedback[motorID][0]);
            feedback[motorID][1] = 0 | (recievedBytes[2]<<8) | recievedBytes[3];
            feedback[motorID][2] = 0 | (recievedBytes[4]<<8) | recievedBytes[5];
            feedback[motorID][3] = ((int16_t) recievedBytes[6]);

            //printf("Motor %d:\tAngle (0,8191):%d\tSpeed  ( RPM ):%d\tTorque ( CUR ):%d\tTemperature(C):%d \n",rxMsg.id,feedback[motorID][0],feedback[motorID][1],feedback[motorID][2],feedback[motorID][3]);
        }
        //CAN Recieving from feedback IDs
    }

    /**
     * @brief Returns angle of motor
     * 
     * @return int 
     */
    int getAngle(){
        return feedback[motorNumber][0];
    }

    int getMultiTurnAngle(){
        return multiTurnPositionAngle[motorNumber];
    }

    static int staticAngle(int motorID){
        return feedback[motorID][0];
    }

    static void multiTurnPositionControl() {
        int Threshold = 3000;

        static int lastMotorAngle[8] = {0,0,0,0,0,0,0,0};

        for (int i = 0; i < 7; i++) {
            if (abs(staticSpeed(i)) > 20) {
                int delta = staticAngle(i) - lastMotorAngle[i]; // 0 to 199 POS// 8000 to 128 NEG
                if(staticSpeed(i) < 0 && delta > 0){ //neg skip
                    multiTurnPositionAngle[i] += (delta - 8191);
                }else if(staticSpeed(i) > 0 && delta < 0){ //pos skip
                    multiTurnPositionAngle[i] += (delta + 8191);
                }else { //pos no skip or neg no skip same case
                    multiTurnPositionAngle[i] += delta;
                }

                lastMotorAngle[i] = staticAngle(i);
            }

        }
      
    }

    static void zeroPos(int motorID) {
        multiTurnPositionAngle[motorID] = 0;
    }

    /**
     * @brief Returns speed of motor
     * 
     * @return int 
     */
    int getSpeed(){
        return feedback[motorNumber][1];
    }

    static int staticSpeed(int motorID) {
        return feedback[motorID][1];
    }

    /**
     * @brief Returns torque of motor
     * 
     * @return int 
     */
    int getTorque(){
        return feedback[motorNumber][2];
    }

    /**
     * @brief Returns temperature of motor
     * 
     * @return int 
     */
    int getTemperature(){
        return feedback[motorNumber][3];
    }

    /**
     * @brief Returns specified data of specified motor
     * canBuss is a field between 1 and 8, specifing the can bus of the motor
     * dataNumber is the element of data you want
     * Angle: 0
     * Speed: 1
     * Torque: 2
     * Temperature: 3
     * 
     * @return int 
     */
    static int getData(int canBus, int dataNumber){
        return feedback[canBus -1][dataNumber];
    }

    /**
     * @brief send all motor values after setting them in setDesiredValues
     * 
     */
    static void sendValues(){
        //CAN Sending to the two sending IDs
        if(motorExists[0] || motorExists[1] || motorExists[2] || motorExists[3]){
            rawSend(sendIDs[0], motorOut1[0], motorOut1[1], motorOut1[2], motorOut1[3]);
        }
        if(motorExists[4] || motorExists[5] || motorExists[6] || motorExists[7]){
            int16_t outputArray[4] = {0, 0, 0, 0};
            for (int i = 0; i < 4; i++) {
                if (mode[i+4] == DISABLED)
                    outputArray[i] = 0;
                else if (mode[i+4] == POSITION)
                    outputArray[i] = -PIDPositionError(motorOut2[i], i+4);
                else if (mode[i+4] == CURRENT) {
                    outputArray[i] = motorOut2[i];
                }
            }

            rawSend(sendIDs[1], outputArray[0], outputArray[1], outputArray[2], outputArray[3]);
        }
    }

    /**
     * @brief Raw sending of CAN Messages
     * 
     * @param id the CAN ID you're sending to
     * @param data1 data to the first motor
     * @param data2 data to the second motor
     * @param data3 data to the third motor
     * @param data4 data to the fourth
     */
    static void rawSend(int id, int data1, int data2, int data3, int data4){
        txMsg.clear(); // clear Tx message storage
        //txMsg.format = CANStandard;
        //txMsg.type = CANData; 
        txMsg.id = id; 

        int motorSending[4] = {data1,data2,data3,data4};

        int8_t sentBytes1[8] = {0,0,0,0,0,0,0,0};
        for(int i = 0; i < 4;  i ++){
            sentBytes1[(2*i)+1] = motorSending[i] & (0xFF);
            sentBytes1[2*i] = (motorSending[i] >> 8) & (0xFF);
        }
        for(int i = 0;  i < 8; i ++){
            txMsg << sentBytes1[i]; //2 bytes per motor
        }
        if (can1.write(txMsg)) {
            // transmit message
            if(motorDebug){
                printf("-------------------------------------\r\n");
                printf("-------------------------------------\r\n");
                printf("CAN message sent\r\n");
                printMsg(txMsg);
            }
        }
        else{
            printf("Transmission error\r\n");
            //break; //TODO AT SOME POINT REMOVE THIs WHEN A TRANSMISSION ERROR ISNT CATASTROPHIC
        }
    }

    /**
     * @brief Function that should be called by the user every tick, runs necessary elements for CAN motors to work.
     * 
     */
    static void update(){
        getFeedback();
        multiTurnPositionControl();
        sendValues();
    }


};

#endif //motor_h