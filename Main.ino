#include <Servo.h>

#define IN1             3
#define IN2             4
#define IN3             5
#define IN4             6
#define TRIGGER         7
#define ECHO            8
#define SERVO           9
#define M_SPONGE        10

Servo servo;

bool forward[]  = {HIGH, LOW, HIGH, LOW};
bool reverse[]  = {LOW, HIGH, LOW, HIGH};
bool right[]    = {HIGH, LOW, LOW, HIGH};
bool left[]     = {LOW, HIGH, HIGH, LOW};
bool off[]      = {LOW, LOW, LOW, LOW};

void setup()
{
    pinMode (IN1, OUTPUT);
    pinMode (IN2, OUTPUT);
    pinMode (IN3, OUTPUT);
    pinMode (IN4, OUTPUT);
    pinMode (M_SPONGE, OUTPUT);

    pinMode (TRIGGER, OUTPUT);
    pinMode (ECHO, INPUT);

    servo.attach(SERVO);
    Serial.begin(9600);
}

float getDistance()
{
    float time, distance;

    // Lanzar señal
    digitalWrite(TRIGGER, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIGGER, HIGH);
    delayMicroseconds(15);
    digitalWrite(TRIGGER, LOW);

    // Calculo de tiempo
    time = pulseIn(ECHO, HIGH);

    // Convirtiendo a distancia en cm
    distance = time / 58.2;

    return distance;
}

void moveServo()
{
    for (int i = 0; i < 180; ++i)
    {
        servo.write(i);
        delay(5);
    }
    for (int i = 180; i >= 0; --i)
    {
        servo.write(i);
        delay(5);
    }
}

void changeStatus(bool data[])
{
    digitalWrite(IN4, data[0]);
    digitalWrite(IN3, data[1]);
    digitalWrite(IN2, data[2]);
    digitalWrite(IN1, data[3]);
}

void loop()
{
    float newDistance = getDistance();

    delay(500);
    Serial.print("Distancia: ");
    Serial.println(newDistance);
    digitalWrite(M_SPONGE, HIGH);
    changeStatus(forward);

    if (newDistance <= 10)
    {
        changeStatus(reverse);
        delay(1000);
        changeStatus(right);
        delay(2000);
        changeStatus(forward);
    }
    moveServo();
}
