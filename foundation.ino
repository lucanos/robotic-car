//
// Define Arduino Pins
//

// Pins for Ultrasonic Sensor
#define pinTrig 2
#define pinEcho 3

// Pins for L298N Motor Driver H-Bridge
#define pinMotor1 6
#define pinMotor2 7
#define pinMotor3 8
#define pinMotor4 9


//
// Initialise Variables
//

// Variables for Ultrasonic Sensor
long duration;
int distance;


//
// Main Arduino Functions
//

// Run once on boot
void setup(){
	// Start the Serial Output, do we can send Debug Messages
	Serial.begin(9600);
	
	// Initialise the Pins
	// Ultrasonic
	Serial.println("Ultrasonic Pins - Initialising");
	initUltrasonicPins();
	Serial.println("Ultrasonic Pins - Done");
	// Motor
	Serial.println("Motor Pins - Initialising");
	initMotorPins();
	Serial.println("Motor Pins - Done");
	
	// Quick Test
	Serial.println("Ultrasonic Test - Start");
	distance = getUltrasonicDistance();
	Serial.print("Object is ");
	Serial.print(distance);
	Serial.println("cm away");
	Serial.println("Ultrasonic Test - End");
	Serial.println("Motor Test - Start");
	commandMotor(HIGH, LOW, HIGH, LOW);
	delay(100);
	Serial.println("Motor Test - End");
}

// Run constantly
void loop(){

}


//
// Additional Arduino Functions
//

// Initialise the Ultrasonic Pins
void initUltrasonicPins(){
	// We set the Trigger Pin as an Output
	pinMode(pinTrig, OUTPUT);
	// and the Echo Pin as an Input
	pinMode(pinEcho, INPUT);
}

// Get the distance from the Ultrasonic Sensor to an object in front
int getUltrasonicDistance(){
	// Set the Trigger Pin to Low
	digitalWrite(pinTrig, LOW);
	// Wait 2 Microseconds
	delayMicroseconds(2);
	// Set the Trigger Pin to High - Send Ping
	digitalWrite(pinTrig, HIGH);
	// Wait 10 Microseconds
	delayMicroseconds(10);
	// Set the Trigger Pin to Low again
	digitalWrite(pinTrig, LOW);
	// Measure how long for the Ping to return
	duration = pulseIn(pinEcho, HIGH);
	// The time measures is out and back (eg 1m out, 1m back), we need half the time
	duration = duration / 2;
	// It takes sound 29.1 Microseconds to travel 1 centimeter, so divide the time by that
	return (duration / 29.1);
}

// Initialise the Motor Pins
void initMotorPins(){
	// Set all Motor Pins as Outputs
	pinMode(pinMotor1, OUTPUT);
	pinMode(pinMotor2, OUTPUT);
	pinMode(pinMotor3, OUTPUT);
	pinMode(pinMotor4, OUTPUT);
}

// Command the Motors
void commandMotor(int powerMotor1, int powerMotor2, int powerMotor3, int powerMotor4){
	// Send the Command to the Motor Pins
	digitalWrite(pinMotor1, powerMotor1);
	digitalWrite(pinMotor2, powerMotor2);
	digitalWrite(pinMotor3, powerMotor3);
	digitalWrite(pinMotor4, powerMotor4);
}
