#include <Arduino.h>

#include <MobaTools.h>

#define SERVO_PIN 4

#define BUTTON_PIN 5

MoToServo servo;

const byte tasterPinNr[] = { BUTTON_PIN };
const byte anzahlTaster = sizeof(tasterPinNr);

button_t getHW(void) {
	button_t tasterTemp = 0;
	for (byte i = 0; i < anzahlTaster; i++) {
		bitWrite(tasterTemp, i, !digitalRead(tasterPinNr[i]));     // Fragt den Taster ab und merkt sich den Status
	}
	return tasterTemp;
}

MoToButtons Taster1(getHW, 20, 500);  // 20ms Entprellzeit, 500ms für den Unterschied kurz/lang gedrückt.

void init_debug() {
	Serial.begin(115200);
}

void setup() {
	init_debug();
	servo.attach(SERVO_PIN);

	for (int i = 0; i < anzahlTaster; i++) {
		pinMode(tasterPinNr[i], INPUT_PULLUP);
	}
}

struct STEP {
	int pos;
	int speed;
	int delay;
};

STEP steps[] = { { 40, 40, 5 }, { 120, 10, 5 }, { 150, 20, 5 }, { 90, 30, 5 } };
size_t length = sizeof(steps) / sizeof(steps[0]);
enum STATE {
	START = 1, WAIT = 2, DELAY = 3, NEXT = 4, STOP = 5
};

STATE state = START;
int counter = 2;

long endtime = millis();

void loop() {

	Taster1.processButtons();

	STEP step = steps[counter];

	switch (state) {
	case START:
		Serial.print("START: (");
		Serial.print(counter);
		Serial.print(") Speed [");
		Serial.print(step.speed);
		Serial.print("] pos [");
		Serial.print(step.pos);
		Serial.print("] delay [");
		Serial.print(step.delay);
		Serial.println("]");

		servo.setSpeed(step.speed);
		servo.write(step.pos);
		state = WAIT;
		break;
	case WAIT:
		// Serial.println("START");
		if (servo.moving() == 0) {
			state = DELAY;
			endtime = millis() + (1000 * step.delay);
		}

		break;
	case DELAY:
		// Serial.println("DELAY");
		if (millis() > endtime) {
			state = NEXT;
		}
		break;
	case NEXT:
		// Serial.println("NEXT");
		counter++;


		if (counter >= length) {
			Serial.println(" == STOP");
			state = STOP;
			counter = 0;
		} else {
			state = START;
		}
		break;
	case STOP:
		if (Taster1.pressed(0)) {
			Serial.println("PRESSED");
			state = START;
			counter = 0;
		}
		break;
	}

	// counter 0 1 2 3 4
	//         x x x x
	// length 4

}
