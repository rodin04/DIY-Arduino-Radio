#include <Wire.h>
#include <TEA5767.h>

TEA5767 radio;

// Pins für die Buttons
const int nextButtonPin = 2;
const int prevButtonPin = 3;

// Letzter Zustand für Entprellung
int lastNextButtonState = HIGH;
int lastPrevButtonState = HIGH;

int currentChannelIndex = 0;

// Liste der gewünschten Frequenzen
float channels[] = {
    87.9,
    89.5,
    90.1,
    90.8,
    92.2,
    94.7,
    99.2,
    101.3,
    102.3,
    103.9,
    104.9,
    105.7,
    107.7
};

const int numChannels = sizeof(channels) / sizeof(channels[0]);

void setup() {
  Serial.begin(9600);
  Wire.begin();
  pinMode(nextButtonPin, INPUT_PULLUP);
  pinMode(prevButtonPin, INPUT_PULLUP);

  radio.setFrequency(channels[currentChannelIndex]);
  Serial.print("Aktuelle Frequenz: ");
  Serial.println(channels[currentChannelIndex]);
}

void loop() {
  int nextButtonState = digitalRead(nextButtonPin);
  int prevButtonState = digitalRead(prevButtonPin);

  // Nächster Kanal
  if (nextButtonState == LOW && lastNextButtonState == HIGH) {
    currentChannelIndex++;
    if (currentChannelIndex >= numChannels) currentChannelIndex = 0;
    radio.setFrequency(channels[currentChannelIndex]);
    Serial.print("Wechsel zu Frequenz: ");
    Serial.println(channels[currentChannelIndex]);
    delay(200); // Entprellen
  }

  // Vorheriger Kanal
  if (prevButtonState == LOW && lastPrevButtonState == HIGH) {
    currentChannelIndex--;  
    if (currentChannelIndex < 0) currentChannelIndex = numChannels - 1;
    radio.setFrequency(channels[currentChannelIndex]);
    Serial.print("Wechsel zu Frequenz: ");
    Serial.println(channels[currentChannelIndex]);
    delay(200); // Entprellen
  }

  // Letzten Zustand merken
  lastNextButtonState = nextButtonState;
  lastPrevButtonState = prevButtonState;
}
