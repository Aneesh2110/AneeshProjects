# Light Communication Project

This repository contains the **Arduino Transmitter and Receiver codes** for a simple light-based communication system.

---

## 📤 Transmitter Code

```cpp
#define TRANSMIT_LED 9
#define SAMPLING_TIME 20
const char* text = "WELCOME TO COEP";

bool led_state = false;
bool transmit_data = true;
int bytes_counter = 20;
int total_bytes;
int transmit_count = 0;

void transmit_byte(char data_byte);

void setup() {
    pinMode(TRANSMIT_LED, OUTPUT);
    total_bytes = strlen(text);
}

void loop() {
    if (transmit_count < 2) {
        transmit_data = true;
        while (transmit_data) {
            transmit_byte(text[total_bytes - bytes_counter]);
            bytes_counter--;
            if (bytes_counter == 0) {
                transmit_data = false;
            }
        }
        bytes_counter = total_bytes;
        transmit_data = true;
        transmit_count++;
        delay(1000);
    }
}

void transmit_byte(char data_byte) {
    digitalWrite(TRANSMIT_LED, LOW);
    delay(SAMPLING_TIME);
    for (int i = 0; i < 8; i++) {
        digitalWrite(TRANSMIT_LED, (data_byte >> i) & 0x01);
        delay(SAMPLING_TIME);
    }
    digitalWrite(TRANSMIT_LED, HIGH);
    delay(SAMPLING_TIME);
}
