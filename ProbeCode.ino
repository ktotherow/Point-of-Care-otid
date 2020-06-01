const int xPin = 2;     // X output of the accelerometer
const int yPin = 3; 
const int idealPressure = 610;
const int errorMargin = 100;
const int tooLow = 10;
const int perfect = 8;
const int tooHigh = 6;


void setup() {
  // initialize serial communications:
  Serial.begin(9600);
  // initialize the pins connected to the accelerometer as inputs:
  pinMode(xPin, INPUT);
  pinMode(yPin, INPUT);
  pinMode(tooLow, OUTPUT);
  pinMode(tooHigh, OUTPUT);
  pinMode(perfect, OUTPUT);

}

void loop() {
   // variables to read the pulse widths:
  int pulseX, pulseY;
  // variables to contain the resulting accelerations
  int accelerationX, accelerationY;

  // read pulse from x- and y-axes:
  pulseX = pulseIn(xPin, HIGH);
  pulseY = pulseIn(yPin, HIGH);

  // convert the pulse width into acceleration
  // accelerationX and accelerationY are in milli-g's:
  // Earth's gravity is 1000 milli-g's, or 1 g.
  accelerationX = ((pulseX / 10) - 500) * 8;
  accelerationY = ((pulseY / 10) - 500) * 8;

  //pressure sensing
  int sum = 0;
  int count = 0;
  int sensorValue = 0;
  while (count < 30) {
    sensorValue = analogRead(A2);
    sum = sum + sensorValue;
    count = count + 1;
  }

  //light feedback
  if (sum/count > (idealPressure + errorMargin)) {
    digitalWrite(perfect, LOW);
    digitalWrite(tooLow, LOW);
    digitalWrite(tooHigh, HIGH);
  } else if (sum/count < (idealPressure - errorMargin)) {
    digitalWrite(perfect, LOW);
    digitalWrite(tooLow, HIGH);
    digitalWrite(tooHigh, LOW);
  } else {
    digitalWrite(perfect, HIGH);
    digitalWrite(tooLow, LOW);
    digitalWrite(tooHigh, LOW);
  }

  

  // print the acceleration
  Serial.print("x accel:");
  Serial.print(accelerationX);
  // print a tab character:
  Serial.print("\t");
  Serial.print("y accel:");
  Serial.print(accelerationY);
  Serial.println();
  Serial.print("pressure");
  Serial.print("\t");
  Serial.println(sum/count);


  delay(3000);

}
