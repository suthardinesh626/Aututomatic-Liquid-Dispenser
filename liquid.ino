#include <HCSR04.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>

#define trig 9
#define echo 10
#define tx 7
#define rx 8
#define relay 5

HCSR04 hc(trig, echo);
LiquidCrystal_I2C lcd(0x3F, 16, 2);
SoftwareSerial sim(tx, rx);

const int x;
String msg = "";
char pay[5];

void setup()
{
    // put your setup code here, to run once:
    sim.begin(9600);
    delay(100);
    sim.write("AT+CMGF=1");
    delay(500);
    sim.write("AT+CNMI=2,2,0,0,0");
    delay(500);

    pinMode(relay, OUTPUT);
    lcd.init();
    lcd.clear();
    lcd.backlight();
}

void loop()
{
    // put your main code here, to run repeatedly:
    while (hc.dist() < 10)
    {
        lcd.setCursor(1, 0);
        lcd.print("Proceed to Pay");

        // verification
        while ('"' != sim.read())
        {
            while (!sim.available())
                ;
        }

        while ('"' != sim.read())
        {
            while (!sim.available())
                ;
        }

        while ('"' != sim.read())
        {
            while (!sim.available())
                ;
        }

        while ('"' != sim.read())
        {
            while (!sim.available())
                ;
        }

        while (sim.available())
        {
            msg += sim.read();
        }

        for (int i = 2, j = 0;; i++, j++)
        {
            if (msg[i] == ' ')
            {
                break;
            }
            pay[j] = msg[i];
        }

        int payment = atoi(pay);

        if (payment > 0)
        {
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Payment verified");

            lcd.setCursor(0, 1);
            lcd.print("Filling...");
            digitalWrite(relay, HIGH);
            delay(payment * x);
            digitalWrite(relay, LOW);
            lcd.setCursor(0, 1);
            lcd.print("Done      ");
        }
        else
        {
            lcd.setCursor(0, 0);
            lcd.print("No Payment");
        }
    }

    digitalWrite(relay, LOW);
    lcd.clear();
}