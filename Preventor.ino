#define WATER_RELAY_PIN 5
#define PHOS_RELAY_PIN 18
#define BUTTON_PIN 4
#define RLED_PIN 16
#define YLED_PIN 0
#define GLED_PIN 2
bool sprinklerState = false;
void setup() {
    pinMode(WATER_RELAY_PIN, OUTPUT);
    pinMode(PHOS_RELAY_PIN, OUTPUT);
    pinMode(BUTTON_PIN, INPUT_PULLUP);
    pinMode(RLED_PIN, OUTPUT);
    pinMode(YLED_PIN, OUTPUT);
    pinMode(GLED_PIN, OUTPUT);
    digitalWrite(WATER_RELAY_PIN, LOW);
    digitalWrite(PHOS_RELAY_PIN, LOW);
    digitalWrite(GLED_PIN, LOW);
    digitalWrite(YLED_PIN, LOW);
    digitalWrite(RLED_PIN, LOW);
    Serial.begin(115200);
}
void loop() {
    int fireSignal = 2;
    int buttonState = digitalRead(BUTTON_PIN);
    Serial.print("Fire Signal: ");
    Serial.println(fireSignal);
    if (buttonState == LOW) {
        sprinklerState = !sprinklerState;
        digitalWrite(WATER_RELAY_PIN, sprinklerState ? HIGH : LOW);
        digitalWrite(PHOS_RELAY_PIN, LOW);
        digitalWrite(RLED_PIN, sprinklerState ? HIGH : LOW);
        digitalWrite(YLED_PIN, LOW);
        digitalWrite(GLED_PIN, LOW);
        Serial.println(sprinklerState ? "Sprinkler ON (Manual)" : "Sprinkler OFF (Manual)");
        delay(500);
    } else {
        if (fireSignal == 1) {
            digitalWrite(WATER_RELAY_PIN, HIGH);
            digitalWrite(PHOS_RELAY_PIN, LOW);
            digitalWrite(RLED_PIN, HIGH);
            digitalWrite(YLED_PIN, LOW);
            digitalWrite(GLED_PIN, LOW);
            Serial.println("🔥 Fire detected here! Deploying Water sprinkler...");
        } else if (fireSignal == 2) {
            digitalWrite(WATER_RELAY_PIN, LOW);
            digitalWrite(PHOS_RELAY_PIN, HIGH);
            digitalWrite(RLED_PIN, LOW);
            digitalWrite(YLED_PIN, HIGH);
            digitalWrite(GLED_PIN, LOW);
            Serial.println("🔥 Fire detected elsewhere! Deploying Phos-chek Sprinkler...");
        } else {
            digitalWrite(WATER_RELAY_PIN, LOW);
            digitalWrite(PHOS_RELAY_PIN, LOW);
            digitalWrite(RLED_PIN, LOW);
            digitalWrite(YLED_PIN, LOW);
            digitalWrite(GLED_PIN, HIGH);
        }
    }
    delay(100);
}
