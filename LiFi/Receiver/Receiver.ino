#define LDR_PIN A0
#define SAMPLING_TIME 20

bool previous_state = true;
bool current_state = true;
char buff[64];

void print_binary(char byte) {
    for (int i = 7; i >= 0; i--) {
        Serial.print((byte >> i) & 1);
    }
}

void setup() {
    Serial.begin(9600);
}

void loop() {
    current_state = get_ldr();
    if (!current_state && previous_state) {
        char received_byte = get_byte();
        Serial.print(received_byte);
        Serial.print(" ");
        Serial.print("Decoded Byte (Binary): ");
        print_binary(received_byte);
        Serial.println();
    }
    previous_state = current_state;
}

bool get_ldr() {
    int val = analogRead(LDR_PIN);
    return val > 700 ? true : false;
}

char get_byte() {
    char data_byte = 0;
    delay(SAMPLING_TIME * 1.5);
    for (int i = 0; i < 8; i++) {
        data_byte = data_byte | ((char)(get_ldr()) << i);
        delay(SAMPLING_TIME);
    }
    return data_byte;
}
