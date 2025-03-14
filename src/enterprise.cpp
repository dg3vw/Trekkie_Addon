#include <NonBlockingRtttl.h>
#include <Arduino.h>

// Define LED pins
#define LED_FRONT PC3
#define BUZZER PC0
#define LED_BLUE_MOTOR_LEFT PC4
#define LED_BLUE_MOTOR_RIGHT PC5
#define LED_RED_MOTOR_LEFT PC6
#define LED_RED_MOTOR_RIGHT PC7
#define LED_DISH_TOP_LEFT PD2
#define LED_DISH_TOP_RIGHT PD3
#define LED_DISH_BOTTOM_LEFT PD4
#define LED_DISH_BOTTOM_RIGHT PD5
#define LED_DEFLECTOR PD0
#define SWITCH_1 PD6
#define SWITCH_2 PD7 // <- work only if Pin D7 is reprogrammed to be an input (not NRST)

// Structure to hold LED timing parameters
struct LedTiming {
    unsigned long previousMillis;
    int ledState;
    const long (*intervalData)[3]; // Pointer to an array of arrays [on, off, repeat]
    const int numIntervals;        // Number of intervals in the array
    const int ledPin;
    int timingIndex;         // Index to switch between the timing sets
    int currentRepeat; // Counter for the current repeat of the interval
};

// Define interval arrays for each LED (example)
// Top Dish LEDs
const long topDishLeftData[][3] = {
    {2000, 15, 1},   // 100ms ON, 900ms OFF, repeat 3 times
    
};

const long topDishRightData[][3] = {
    {2100, 15, 1},   // 100ms ON, 900ms OFF, repeat 3 times
};

// Bottom Dish LEDs
const long bottomDishLeftData[][3] = {
    {50, 50, 4},    // 500ms ON, 100ms OFF, repeat 1 time
    {50, 200, 1},   // 200ms ON, 500ms OFF, repeat 2 time
    {2000, 350, 1},   // 200ms ON, 500ms OFF, repeat 2 time
};

const long bottomDishRightData[][3] = {
    {50, 50, 4},    // 500ms ON, 100ms OFF, repeat 1 time
    {50, 200, 1},   // 200ms ON, 500ms OFF, repeat 2 time
    {2000, 350, 1},   // 200ms ON, 500ms OFF, repeat 2 time
};

// Front LED
const long frontLedData[][3] = {
    {2500, 500, 1},   // 5000ms ON, 60ms OFF, repeat 1 time
};

// Blue Motor LEDs
const long blueMotorLeftData[][3] = {
    {100, 50, 1},
    {50, 200, 1},   
    {6000, 2000, 1},   
};

const long blueMotorRightData[][3] = {
    {100, 50, 1},
    {50, 200, 1},   
    {6000, 2000, 1},
};

// Red Motor LEDs
const long redMotorLeftData[][3] = {
    {5000, 500, 1},   // 5000ms ON, 60ms OFF, repeat 1 time
};

const long redMotorRightData[][3] = {
    {5000, 500, 1},   // 5000ms ON, 60ms OFF, repeat 1 time
};

// Deflector LED
const long deflectorLedData[][3] = {
    {3000, 700, 1},   // 5000ms ON, 60ms OFF, repeat 1 time
};

// Define LED timing parameters and instances
LedTiming topDishLeds[] = {
    {0, LOW, topDishLeftData, sizeof(topDishLeftData) / sizeof(topDishLeftData[0]), LED_DISH_TOP_LEFT, 0, 0},
    {0, LOW, topDishRightData, sizeof(topDishRightData) / sizeof(topDishRightData[0]), LED_DISH_TOP_RIGHT, 0, 0}};

LedTiming bottomDishLeds[] = {
    {0, LOW, bottomDishLeftData, sizeof(bottomDishLeftData) / sizeof(bottomDishLeftData[0]), LED_DISH_BOTTOM_LEFT, 0, 0},
    {0, LOW, bottomDishRightData, sizeof(bottomDishRightData) / sizeof(bottomDishRightData[0]), LED_DISH_BOTTOM_RIGHT, 0, 0}};

LedTiming frontLed = {0, LOW, frontLedData, sizeof(frontLedData) / sizeof(frontLedData[0]), LED_FRONT, 0, 0};

LedTiming blueMotorLeds[] = {
    {0, LOW, blueMotorLeftData, sizeof(blueMotorLeftData) / sizeof(blueMotorLeftData[0]), LED_BLUE_MOTOR_LEFT, 0, 0},
    {0, LOW, blueMotorRightData, sizeof(blueMotorRightData) / sizeof(blueMotorRightData[0]), LED_BLUE_MOTOR_RIGHT, 0, 0}};

LedTiming redMotorLeds[] = {
    {0, LOW, redMotorLeftData, sizeof(redMotorLeftData) / sizeof(redMotorLeftData[0]), LED_RED_MOTOR_LEFT, 0, 0},
    {0, LOW, redMotorRightData, sizeof(redMotorRightData) / sizeof(redMotorRightData[0]), LED_RED_MOTOR_RIGHT, 0, 0}};

LedTiming deflectorLed = {0, LOW, deflectorLedData, sizeof(deflectorLedData) / sizeof(deflectorLedData[0]), LED_DEFLECTOR, 0, 0};

static bool switch1Pressed = false; // Flag to track switch 1 press state
static bool switch2Pressed = false; // Flag to track switch 2 press state
unsigned long currentMillis = millis();

int leds[] = {
    LED_FRONT, LED_BLUE_MOTOR_LEFT, LED_BLUE_MOTOR_RIGHT,
    LED_RED_MOTOR_LEFT, LED_RED_MOTOR_RIGHT, LED_DISH_TOP_LEFT,
    LED_DISH_TOP_RIGHT, LED_DISH_BOTTOM_LEFT, LED_DISH_BOTTOM_RIGHT,
    LED_DEFLECTOR};

const char *startrek = "StarTrekTNG:d=32,o=6,b=63:8f#.5,b.5,d#.,8c#.,a.5,g#.,4f#.,a.5,e.,f#.,g#.,e.,8d#,8c#,8b.5,d#.,b.5,2c#";
const char *rickroll = "RickRoll:d=4,o=5,b=200:8g,8a,8c6,8a,e6,8p,e6,8p,d6.,p,8p,8g,8a,8c6,8a,d6,8p,d6,8p,c6,8b,a.,8g,8a,8c6,8a,2c6,d6,b,a,g.,8p,g,2d6,2c6.,p,8g,8a,8c6,8a,e6,8p,e6,8p,d6.,p,8p,8g,8a,8c6,8a,2g6,b,c6.,8b,a,8g,8a,8c6,8a,2c6,d6,b,a,g.,8p,g,2d6,2c6.";


// Zapping sound parameters (for SWITCH_1)
const int zapFrequencies[] = {400, 600, 800, 1000, 800, 600, 400, 300, 200}; // Frequencies for the zap sound
const long zapDurations[] = {20, 20, 20, 20, 20, 20, 20, 30, 50};   // Durations for each frequency (milliseconds)
const int numZapTones = sizeof(zapFrequencies) / sizeof(zapFrequencies[0]);
unsigned long zapStartTime = 0; // Stores the start time of the zap sound
int zapToneIndex = 0;          // Index of the current tone
bool isZapping = false;        // Flag to indicate if the zapping sound is playing

// New sound parameters (for SWITCH_2)
const int beepFrequencies[] = {800, 1200, 1600, 2000}; // Frequencies for the beep sound
const long beepDurations[] = {50, 50, 50, 100};        // Durations for each frequency (milliseconds)
const int numBeepTones = sizeof(beepFrequencies) / sizeof(beepFrequencies[0]);
unsigned long beepStartTime = 0; // Stores the start time of the beep sound
int beepToneIndex = 0;          // Index of the current tone
bool isBeeping = false;        // Flag to indicate if the beep sound is playing

// New variables for rickroll functionality
int switch1PressCount = 0; // Counter for switch 1 presses
bool isRickrolling = false;  // Flag to indicate if Rickroll is playing
unsigned long rickrollBlinkMillis = 0;
int rickrollBlinkState = LOW;


// Function to play Rickroll
void playRickroll() {
    if (!isRickrolling) {
        isRickrolling = true;
        rtttl::begin(BUZZER, rickroll);
    }
    if (rtttl::done()) {
        isRickrolling = false;
        //reset leds
        for (int i = 0; i < sizeof(leds) / sizeof(leds[0]); i++) {
            digitalWrite(leds[i], HIGH); 
        }
    } else {
        rtttl::play();
    }
}

void setup() {
    pinMode(LED_FRONT, OUTPUT);
    pinMode(BUZZER, OUTPUT);
    pinMode(LED_BLUE_MOTOR_LEFT, OUTPUT);
    pinMode(LED_BLUE_MOTOR_RIGHT, OUTPUT);
    pinMode(LED_RED_MOTOR_LEFT, OUTPUT);
    pinMode(LED_RED_MOTOR_RIGHT, OUTPUT);
    pinMode(LED_DISH_TOP_LEFT, OUTPUT);
    pinMode(LED_DISH_TOP_RIGHT, OUTPUT);
    pinMode(LED_DISH_BOTTOM_LEFT, OUTPUT);
    pinMode(LED_DISH_BOTTOM_RIGHT, OUTPUT);
    pinMode(LED_DEFLECTOR, OUTPUT);
    pinMode(SWITCH_1, INPUT_PULLUP); // Use internal pull-up resistor
    pinMode(SWITCH_2, INPUT_PULLUP); // Use internal pull-up resistor

    for (int i = 0; i < sizeof(leds) / sizeof(leds[0]); i++) {
        digitalWrite(leds[i], HIGH); // Start all LEDs as off
    }

    rtttl::begin(BUZZER, startrek);
    while (!rtttl::done()) {
        rtttl::play();
    }
}

void handleLedBlinking(LedTiming &led) {
    unsigned long currentMillis = millis();
    long intervalOn = led.intervalData[led.timingIndex][0];
    long intervalOff = led.intervalData[led.timingIndex][1];
    int intervalRepeat = led.intervalData[led.timingIndex][2];

    if (led.ledState == LOW && currentMillis - led.previousMillis >= intervalOn) {
        led.previousMillis = currentMillis;
        led.ledState = HIGH;
        digitalWrite(led.ledPin, led.ledState);
    } else if (led.ledState == HIGH && currentMillis - led.previousMillis >= intervalOff) {
        led.previousMillis = currentMillis;
        led.ledState = LOW;
        digitalWrite(led.ledPin, led.ledState);
        led.currentRepeat++;

        if (led.currentRepeat >= intervalRepeat) {
            led.timingIndex = (led.timingIndex + 1) % led.numIntervals;
            led.currentRepeat = 0; // Reset the repeat counter
        }
    }
}


void handleLedGroupBlinking(LedTiming leds[], int count) {
    for (int i = 0; i < count; i++) {
        handleLedBlinking(leds[i]);
    }
}

// Function to play the zapping sound
void playZapSound() {
    if (isZapping) {
        unsigned long currentMillis = millis();
        if (currentMillis - zapStartTime >= zapDurations[zapToneIndex]) {
            zapToneIndex++;
            zapStartTime = currentMillis;
            if (zapToneIndex >= numZapTones) {
                isZapping = false;
                noTone(BUZZER);
            } else {
                tone(BUZZER, zapFrequencies[zapToneIndex]);
            }
        }
    }
}
// Function to play the new beep sound (for SWITCH_2)
void playBeepSound() {
    if (isBeeping) {
        unsigned long currentMillis = millis();
        if (currentMillis - beepStartTime >= beepDurations[beepToneIndex]) {
            beepToneIndex++;
            beepStartTime = currentMillis;
            if (beepToneIndex >= numBeepTones) {
                isBeeping = false;
                noTone(BUZZER);
            } else {
                tone(BUZZER, beepFrequencies[beepToneIndex]);
            }
        }
    }
}

void rickrollBlink() {
    unsigned long currentMillis = millis();
    if (currentMillis - rickrollBlinkMillis >= 50) {
        rickrollBlinkMillis = currentMillis;
        rickrollBlinkState = !rickrollBlinkState; // Toggle state
        if (rickrollBlinkState == HIGH) {
            int randomIndex = random(sizeof(leds) / sizeof(leds[0]));
            digitalWrite(leds[randomIndex], LOW);
        } else {
            for (int i = 0; i < sizeof(leds) / sizeof(leds[0]); i++) {
                digitalWrite(leds[i], HIGH);
            }
        }
    }
}

void loop() {
    unsigned long currentMillis = millis(); // Moved inside the loop!

    if (!isRickrolling) {
        // Handle top dish LEDs blinking
        handleLedGroupBlinking(topDishLeds, sizeof(topDishLeds) / sizeof(topDishLeds[0]));

        // Handle bottom dish LEDs blinking
        handleLedGroupBlinking(bottomDishLeds, sizeof(bottomDishLeds) / sizeof(bottomDishLeds[0]));

        // Handle Front LED blinking
        handleLedBlinking(frontLed);

        // Handle blue motor LEDs blinking
        handleLedGroupBlinking(blueMotorLeds, sizeof(blueMotorLeds) / sizeof(blueMotorLeds[0]));

        // Handle red motor LEDs blinking
        handleLedGroupBlinking(redMotorLeds, sizeof(redMotorLeds) / sizeof(redMotorLeds[0]));
    }

    // Handle deflector LED blinking when switch 1 is pressed and play sound
    if (digitalRead(SWITCH_1) == LOW) { // Switch is active LOW
        if (!switch1Pressed) {
            switch1PressCount++;
            switch1Pressed = true;
            if (!isZapping) {
                isZapping = true;
                zapToneIndex = 0;
                zapStartTime = currentMillis;
                tone(BUZZER, zapFrequencies[zapToneIndex]);
            }
        }
    } else {
        switch1Pressed = false;
        if (switch1PressCount >= 10 && !isRickrolling) {
            switch1PressCount = 0;
            playRickroll();
        }
    }

    if(isRickrolling){
        rickrollBlink();
        playRickroll();
    }

    // Handle new beep sound when switch 2 is pressed <- work only if Pin D7 is reprogrammed to be an input (not NRST)
    if (digitalRead(SWITCH_2) == LOW) { // Switch is active LOW
        switch2Pressed = true;
        if (!isBeeping) {
            isBeeping = true;
            beepToneIndex = 0;
            beepStartTime = currentMillis;
            tone(BUZZER, beepFrequencies[beepToneIndex]);
        }
    } else {
        switch2Pressed = false;
    }

    if (switch1Pressed && !isRickrolling) {
                handleLedBlinking(deflectorLed);
             } else if(!isRickrolling) {
                 digitalWrite(LED_DEFLECTOR, HIGH); // Keep deflector off when switch is not pressed
             }
             
             if (!isRickrolling) {
                 playZapSound(); // Play the zapping sound if it's active
             } 
             playBeepSound(); // Play the beep sound if it's active
        
        }
