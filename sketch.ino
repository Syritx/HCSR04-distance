int TRIG_PIN = 14;
int ECHO_PIN = 12;

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
Adafruit_SSD1306 SSD_I2C = Adafruit_SSD1306(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

float duration, distance;
int MAX_DISTANCE_CM = 20;

bool sent = false;

void setup() {
    // put your setup code here, to run once:
    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);
    Serial.begin(9600);

    SSD_I2C.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    SSD_I2C.clearDisplay();
}

void loop() {
    // put your main code here, to run repeatedly:
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);

    duration = pulseIn(ECHO_PIN, HIGH);
    distance = (duration/2) * 0.0343;
    if (distance > 0 && distance <= MAX_DISTANCE_CM) {
        Serial.print("Distance: ");
        Serial.println(distance);

        SSD_I2C.clearDisplay();
        SSD_I2C.setTextSize(1);
        SSD_I2C.setTextColor(WHITE);
        SSD_I2C.setCursor(5, 5);
        SSD_I2C.println("Object within range:");
        SSD_I2C.setCursor(5, 15);
        SSD_I2C.println("0cm and "+String(MAX_DISTANCE_CM)+"cm");
        SSD_I2C.setCursor(5, 35);
        SSD_I2C.setTextSize(2);
        SSD_I2C.println(String(floor(distance))+"cm");
        SSD_I2C.display();
    }
    else {
        SSD_I2C.clearDisplay();
        SSD_I2C.setTextSize(1);
        SSD_I2C.setTextColor(WHITE);
        SSD_I2C.setCursor(5, 5);
        SSD_I2C.println("No object in range:");
        SSD_I2C.setCursor(5, 15);
        SSD_I2C.println("0cm and "+String(MAX_DISTANCE_CM)+"cm");
        SSD_I2C.display();
    }
    delay(100);
}
