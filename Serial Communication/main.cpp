/*
 * Copyright (c) 2020 Arm Limited and affiliates.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include <iostream>
#include "SerialCommunication.hpp"

SerialCommunication Serial(A0, A1, 9600);

char mycoolmessage[64];

int main() {

  while (1) {
        
        if (Serial.update(mycoolmessage))
            printf("your new messsage: %s\n", mycoolmessage);

    }

}