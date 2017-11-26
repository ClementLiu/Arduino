const int leftstart = 1;
const int increase = 4;
const int decrease = 3;
const int incline = 6;
const int decline = 7;
const int startButton = 2;


int testBegin = 0;
void setup()
{
  // no setup needed
}

void loop()
{
  if(testBegin == 0){
    for (int i = 0; i < 3; i++){
    analogWrite(startButton, 100);
    delay(1000);
    analogWrite(startButton, 0);
    }
    testBegin =1;
    }
  
      for (int i = 0; i < 80; i++){
         analogWrite(increase, 100);
         delay(10000);
         analogWrite(increase, 0);
        }
              for (int i = 0; i < 80; i++){
         analogWrite(decrease, 100);
         delay(400);
         analogWrite(decrease, 0);
        }
   
}

