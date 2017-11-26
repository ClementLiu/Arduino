const int leftstart = 1;
const int increase = 4;
const int decrease = 3;
const int incline = 6;
const int decline = 7;
const int startButton = 2;


int testBegin = 0;
int testSpeed = 0;


void setup()
{
  // no setup needed
  pinMode(leftstart, OUTPUT);
  pinMode(increase, OUTPUT);
  pinMode(decrease, OUTPUT);
  pinMode(incline, OUTPUT);
  // pinMode(increase, OUTPUT);
  pinMode(decline, OUTPUT);
  pinMode(startButton, OUTPUT);

  digitalWrite(leftstart, HIGH);
  digitalWrite(increase, HIGH);
  digitalWrite(decrease, HIGH);
  digitalWrite(incline, HIGH);
  // digitalWrite(increase, HIGH);
  digitalWrite(decline, HIGH);
  digitalWrite(startButton, HIGH);
  // pinMode(increase, OUTPUT);  
}

void loop()
{

  // left start begin 
  if(testBegin == 0){
    for (int i = 0; i < 3; i++){
    digitalWrite(leftstart, LOW);
    delay(1000);
    digitalWrite(leftstart, HIGH);
    delay(1000);
      }
    testBegin =1;
    }
    // left start  end
    // right part start begin 
    

    // right part start end
  if (testSpeed == 0)
  {
    /* code */
    // increase spped  from 0 to 60 M/h begin 
    digitalWrite(startButton, LOW);
    delay(1000);
    digitalWrite(startButton, HIGH);


      for (int i = 0; i < 60; i++){
         digitalWrite(increase, LOW);
         delay(500);
         digitalWrite(increase, HIGH);
         delay(400);
        }
      // increase spped from 0 to 60 M/h end
      testSpeed =1;
        delay(120000);
  }
      
      // wait 120 seconds 

        // decreae speed to 30 M/h begin 
       for (int i = 0; i < 30; i++){
         digitalWrite(decrease, LOW);
         delay(1000);
         digitalWrite(decrease, HIGH);
         delay(500);
        }
        // decreae speed to 30 M/h end
      // wait 120 seconds 
        delay(120000);
         // Incline angle to MAX(20 times ) begin 
    for (int i = 0; i < 20; i++){
         digitalWrite(incline, LOW);
         delay(1000);
         digitalWrite(incline, HIGH);
         delay(500);
        }
       // Incline angle to MAX(20 times ) end
      // wait 15 seconds 
        delay(15000);
       // Decline angle to middle(8 times ) begin 
        for (int i = 0; i < 8; i++){
         digitalWrite(decline, LOW);
         delay(1000);
         digitalWrite(decline, HIGH);
         delay(500);
        }
    // Decline angle to middle(8 times ) begin 
    // wait 60 seconds
        delay(60000);
        // flat again begin 
        for (int i = 0; i < 8; i++){
         digitalWrite(decline, LOW);
         delay(1000);
         digitalWrite(decline, HIGH);
         delay(500);
        }
        // flat again end 
        delay(30000);
        // increase spped to 45 M/h end
        for (int i = 0; i < 15; i++){
         digitalWrite(increase, LOW);
         delay(1000);
         digitalWrite(increase, HIGH);
         delay(500);
        }
        // increase spped to 45 M/h end
    // wait 45 second;
        delay(45000);

        // increse to speed 60 begin 
        for (int i = 0; i < 15; i++){
         digitalWrite(increase, LOW);
         delay(1000);
         digitalWrite(increase, HIGH);
         delay(500);
        }
        delay(120000);
        // increse to speed 60 end
   
}

