//Define the analog inputs
const int x = A0;
const int y = A1;
const int z = A2;

int xVal;
int yVal;
int zVal;

void setup(){
    Serial.begin(9600);
    Serial.print("Test succsseful");
}

void loop(){
    xVal = analogRead(x);
    yVal = analogRead(y);
    zVal = analogRead(z);

    Serial.print("The x value is: ");
    Serial.println(xVal);
    Serial.print("The y value is: ");
    Serial.println(yVal);
    Serial.print("The z value is: ");
    Serial.println(zVal);
    delay(1000);
}
