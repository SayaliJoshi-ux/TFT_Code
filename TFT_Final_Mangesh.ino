#include <TimerOne.h>
#include <Adafruit_GFX.h>
#include <MCUFRIEND_kbv.h>
#include <TouchScreen.h>
MCUFRIEND_kbv tft;
#define MINPRESSURE 200
#define MAXPRESSURE 1000

// ALL Touch panels and wiring is DIFFERENT
// copy-paste results from TouchScreen_Calibr_native.ino
#define LCD_CS A3 // Chip Select goes to Analog 3
#define LCD_CD A2 // Command/Data goes to Analog 2
#define LCD_WR A1 // LCD Write goes to Analog 1
#define LCD_RD A0 // LCD Read goes to Analog 0
#define LCD_RESET A4 // Can alternately just connect to Arduino's reset pin
const int XP = 6, XM = A2, YP = A1, YM = 7; //ID=0x9341
Adafruit_GFX_Button btn_6, btn_5,btn_1,btn_2,btn_3,btn_4,btn[13],bt[15],btn_Stop;
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);
#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define YELLOW  0xFFE0
#define WHITE   0xFFFF
#define GREY    0x2108

#define RED2RED 0
#define GREEN2GREEN 1
#define BLUE2BLUE 2
#define BLUE2RED 3
#define GREEN2RED 4
#define RED2GREEN 5
bool MIN,on=true,set;
int pixel_x, pixel_y,num=0,x=20,y=20,Channel,Temperature;     //Touch_getXY() updates global vars
int sec_counter,min_counter;
bool Touch_getXY(void)
{
    TSPoint p = ts.getPoint();
    pinMode(YP, OUTPUT);      //restore shared pins
    pinMode(XM, OUTPUT);
    digitalWrite(YP, HIGH);   //because TFT control pins
    digitalWrite(XM, HIGH);
    bool pressed = (p.z > MINPRESSURE && p.z < MAXPRESSURE);
    if (pressed) {
        pixel_x = map(p.y,935 ,245 , 0, 320); //.kbv makes sense to me
        pixel_y = map(p.x,195 ,875 , 0, 240);
    }
    return pressed;
}
int Read_temp()
{
  // Tempreture_reading code 
}
int Read_pressure()
{
  //Pressure_reading code
}
void splash_screen()
{
  tft.fillScreen(WHITE);
  tft.setCursor(60,30);
  tft.setTextSize(5);
  tft.setTextColor(BLUE);
  tft.print("MACHINE");
  tft.setTextSize(2);
  tft.setCursor(130,120);
  tft.setTextColor(RED);
  tft.print("M6.8");
  tft.setTextSize(2);
  tft.setCursor(80,160);
  tft.setTextColor(BLACK);
  delay(1000);
  tft.print("Loading");
  for(int i=0;i<3;i++)
  {
    tft.fillCircle(170,170,3,BLACK);
    delay(500);
    tft.fillCircle(180,170,3,BLACK);
    delay(500);
    tft.fillCircle(190,170,3,BLACK);
    delay(500);
    tft.fillCircle(190,170,3,WHITE);
    tft.fillCircle(180,170,3,WHITE);
    tft.fillCircle(170,170,3,WHITE);
    delay(500);
  }
}
void Main_page()
{ 
    tft.setRotation(1);
    tft.fillScreen(BLACK);
    btn_1.initButton(&tft, 65, 30, 80, 30, GREEN,GREEN, BLACK, "ON", 2);
    btn_2.initButton(&tft, 225, 50, 160, 40, CYAN, BLACK, CYAN, "TIME", 2);
    btn_3.initButton(&tft, 225, 100, 160, 40, CYAN, BLACK, CYAN, "CHANNEL", 2);
    btn_4.initButton(&tft, 225, 150, 160, 40, CYAN, BLACK, CYAN, "TEMP", 2);
    btn_5.initButton(&tft, 179, 200, 65, 40, CYAN, BLACK, CYAN, "START", 2);
    btn_6.initButton(&tft, 270, 200, 66, 40, CYAN, BLACK, CYAN, "RESET", 2);
    btn_1.drawButton(false);
    btn_2.drawButton(false);
    btn_3.drawButton(false);
    btn_4.drawButton(false);
    btn_5.drawButton(false);
    btn_6.drawButton(false);
  tft.drawRect(0,0,320,240,WHITE);
  tft.setCursor(180,8);
  tft.setTextSize(2);
  tft.setTextColor(RED);
  tft.print("SETTINGS");
  tft.setCursor(5,70);
  tft.setTextSize(2);
  tft.setTextColor(RED);
  tft.print("Tempreture");
  tft.setCursor(10,160);
  tft.print("Pressure");
  tft.drawFastVLine(130,0,240,WHITE);
  tft.drawFastHLine(0,150,130,WHITE);
  tft.drawFastHLine(0,60,130,WHITE);
  while(1)
  {
    
    tft.setTextSize(2);
    tft.setTextColor(WHITE);
    tft.setCursor(5,95);
    tft.print(Read_temp());
    tft.print(" Celcius");
    tft.setCursor(10,185);
    tft.print(Read_pressure());
    tft.print(" Bars");
     bool down = Touch_getXY();
     btn_1.press(down && btn_1.contains(pixel_x, pixel_y));
     btn_2.press(down && btn_2.contains(pixel_x, pixel_y));
     btn_3.press(down && btn_3.contains(pixel_x, pixel_y));
     btn_4.press(down && btn_4.contains(pixel_x, pixel_y));
     btn_5.press(down && btn_5.contains(pixel_x, pixel_y));
     btn_6.press(down && btn_6.contains(pixel_x, pixel_y));
     
    if (btn_1.justReleased())
    {
      if(on==true)
       {
       btn_1.initButton(&tft, 65, 30, 80, 30, RED,BLACK,RED, "OFF", 2);
        btn_1.drawButton(true);
        on=false;

        //Add On button Code here//
       }
       else
       {
         btn_1.initButton(&tft, 65, 30, 80, 30, GREEN,BLACK, GREEN, "ON", 2);
        btn_1.drawButton(true);
        on=true;
        //Add Off code here//
       } 
     
    }
    if (btn_2.justReleased())
        btn_2.drawButton();
    if (btn_3.justReleased())
        btn_3.drawButton();
        
    if (btn_1.justPressed()) {
      
    }
    if (btn_2.justPressed()) {
        btn_2.drawButton(true);
        set_Time();
    }
    if (btn_3.justPressed()) {
        btn_3.drawButton(true);
       set_Channel();
    }     
    if (btn_5.justReleased())
        btn_5.drawButton();
    if (btn_6.justReleased())
        btn_6.drawButton();
        
    if (btn_4.justPressed()) {
        set_Temp();
    }
    if (btn_5.justPressed()) {
    
        Start_Timer();
    }
    if (btn_6.justPressed()) {
      
        Channel=0;
        Temperature=0;min_counter=0;sec_counter=0;
        Serial.println(Temperature);
        Serial.println(min_counter);
        Serial.println(sec_counter);
        Serial.println(Channel);
    }
  }
 
}
void calc_Values(int z)
{
  if(num==0)
  {
    num=z;
  }
  else if(z==0)
  {
    num=num*10;
  }
  else if(num>0)
  {
    num=(num*10)+z;
  }
  
}
  void Temp_Channel_Values(bool set)
{   
  num=0;
    while(1)
    {
     bool down = Touch_getXY();
     int count=0;
      
      btn[0].press(down&&btn[0].contains(pixel_x,pixel_y));
      btn[1].press(down&&btn[1].contains(pixel_x,pixel_y));
      btn[2].press(down&&btn[2].contains(pixel_x,pixel_y));
      btn[3].press(down&&btn[3].contains(pixel_x,pixel_y));
      btn[4].press(down&&btn[4].contains(pixel_x,pixel_y));
      btn[5].press(down&&btn[5].contains(pixel_x,pixel_y));
      btn[6].press(down&&btn[6].contains(pixel_x,pixel_y));
      btn[7].press(down&&btn[7].contains(pixel_x,pixel_y));
      btn[8].press(down&&btn[8].contains(pixel_x,pixel_y));
      btn[9].press(down&&btn[9].contains(pixel_x,pixel_y));
      btn[10].press(down&&btn[10].contains(pixel_x,pixel_y));
      btn[11].press(down&&btn[11].contains(pixel_x,pixel_y));
      btn[12].press(down&&btn[12].contains(pixel_x,pixel_y));
      btn[13].press(down&&btn[13].contains(pixel_x,pixel_y));

      if(btn[0].justReleased())
        btn[0].drawButton();
      if(btn[1].justReleased())
        btn[1].drawButton();
      if(btn[2].justReleased())
        btn[2].drawButton();
      if(btn[3].justReleased())
        btn[3].drawButton();
      if(btn[4].justReleased())
        btn[4].drawButton();
      if(btn[5].justReleased())
        btn[5].drawButton();
      if(btn[6].justReleased())
        btn[6].drawButton();
       if(btn[7].justReleased())
        btn[7].drawButton();
       if(btn[8].justReleased())
        btn[8].drawButton();
      if(btn[10].justReleased())
        btn[10].drawButton();   
    if (btn[0].justPressed()) {
        btn[0].drawButton(true);
        tft.setCursor(x,y);
        tft.setTextSize(3);
        tft.setTextColor(WHITE);
        tft.print("1");
        calc_Values(1);
          x=x+20;
    }
    if (btn[1].justPressed()) {
        btn[1].drawButton(true);
        tft.setCursor(x,y);
        tft.setTextSize(3);
        tft.setTextColor(WHITE);
        tft.print("2");
        calc_Values(2);
        x=x+20;
    }
    if (btn[2].justPressed()) {
        btn[2].drawButton(true);
        tft.setCursor(x,y);
        tft.setTextSize(3);
        tft.setTextColor(WHITE);
        tft.print("3");
        calc_Values(3);
        x=x+20;   
    }
    if (btn[3].justPressed()) {
        btn[3].drawButton(true);
        tft.setCursor(x,y);
        tft.setTextSize(3);
        tft.setTextColor(WHITE);
        tft.print("4");
        calc_Values(4);
        x=x+20;
    }
    if (btn[4].justPressed()) {
        btn[4].drawButton(true);
        tft.setCursor(x,y);
        tft.setTextSize(3);
        tft.setTextColor(WHITE);
        tft.print("5"); 
         calc_Values(5);
        x=x+20;
    }
    if (btn[5].justPressed()) {
        btn[5].drawButton(true);
        tft.setCursor(x,y);
        tft.setTextSize(3);
        tft.setTextColor(WHITE);
        tft.print("6");
         calc_Values(6);
          x=x+20;
        }
        
    if(btn[6].justPressed()) {
        btn[6].drawButton(true);
        tft.setCursor(x,y);
        tft.setTextSize(3);
        tft.setTextColor(WHITE);
        tft.print("7"); 
        calc_Values(7);
        x=x+20;
    }
    if (btn[7].justPressed()) {
        btn[7].drawButton(true);
        tft.setCursor(x,y);
        tft.setTextSize(3);
        tft.setTextColor(WHITE);
        tft.print("8");
        calc_Values(8); 
        x=x+20; 
    }
    if (btn[8].justPressed()) {
        btn[8].drawButton(true);
        tft.setCursor(x,y);
        tft.setTextSize(3);
        tft.setTextColor(WHITE);
        tft.print("9");
        calc_Values(9);
        x=x+20;
    }
    if (btn[11].justReleased())
        btn[11].drawButton();
  
    if (btn[9].justPressed()) {
        btn[9].drawButton(true);
        Serial.println(num);
        tft.setCursor(20,50);
        tft.setTextSize(2);
        tft.setTextColor(WHITE);
        tft.print("SET!!");
        if(set==true)
        {
          Channel=num;
          if(Channel>12)
          {
          tft.setCursor(20,50);
          tft.setTextSize(2);
          tft.setTextColor(WHITE);
          tft.print("Wrong!!");
          delay(3000);
          Channel=0;
          tft.fillRect(6, 6, 200,60, BLACK);
          num=0;
          }
        }
        else
        {
          Temperature=num;
          num=0;
        }
        x=20;
    }
    if (btn[11].justPressed()) {
        btn[11].drawButton(true);
        tft.fillRect(6, 6, 200,60, BLACK);
        x=20;
        num=0;
    }
    if (btn[10].justPressed()) {
        btn[10].drawButton(true);
        tft.setCursor(x,y);
        tft.setTextSize(3);
        tft.setTextColor(WHITE);
        tft.print("0");
        calc_Values(0);
        x=x+20;
    }
    if (btn[12].justPressed()) {
        Main_page();
        return num;
        x=20;
    }
  }
}
void Temp_Channel_Layout()
{
    tft.fillScreen(BLACK);
    tft.setRotation(1);    
    btn[0].initButton(&tft,  40, 110, 60, 40, WHITE, CYAN, BLACK, "1", 2);
    btn[1].initButton(&tft, 110,110 , 60, 40, WHITE, CYAN, BLACK, "2", 2);
    btn[2].initButton(&tft, 180, 110, 60, 40, WHITE, CYAN, BLACK, "3", 2); 
    btn[3].initButton(&tft,  40, 160, 60, 40, WHITE, CYAN, BLACK, "4", 2);
    btn[4].initButton(&tft, 110, 160, 60, 40, WHITE, CYAN, BLACK, "5", 2);
    btn[5].initButton(&tft, 180, 160, 60, 40, WHITE, CYAN, BLACK, "6", 2);
    btn[6].initButton(&tft,  40, 210, 60, 40, WHITE, CYAN, BLACK, "7", 2);
    btn[7].initButton(&tft, 110, 210, 60, 40, WHITE, CYAN, BLACK, "8", 2);
    btn[8].initButton(&tft, 180, 210, 60, 40, WHITE, CYAN, BLACK, "9", 2);
    btn[10].initButton(&tft, 260, 210, 70, 40, WHITE, CYAN, BLACK, "0", 2);
    btn[9].initButton(&tft, 260, 110, 70, 40, WHITE, CYAN, BLACK, "SET", 2);
    btn[11].initButton(&tft, 260, 160, 70, 40, RED, RED, BLACK, "CLR", 2);
    btn[12].initButton(&tft, 260, 60, 70, 40, BLUE, BLUE, BLACK, "BACK", 2);
    int count=0;
    while(count<13)
    {
      btn[count].drawButton(false);
      count=count+1;
    }
   
    tft.drawRect(5, 5, 210, 70, RED);
}
void Time_Layout()
{
   tft.setRotation(1);            //PORTRAIT
    tft.fillScreen(BLACK);
    bt[0].initButton(&tft,  40, 110, 60, 40, WHITE, CYAN, BLACK, "1", 2);
    bt[1].initButton(&tft, 110,110 , 60, 40, WHITE, CYAN, BLACK, "2", 2);
    bt[2].initButton(&tft, 180, 110, 60, 40, WHITE, CYAN, BLACK, "3", 2); 
    bt[3].initButton(&tft,  40, 160, 60, 40, WHITE, CYAN, BLACK, "4", 2);
    bt[4].initButton(&tft, 110, 160, 60, 40, WHITE, CYAN, BLACK, "5", 2);
    bt[5].initButton(&tft, 180, 160, 60, 40, WHITE, CYAN, BLACK, "6", 2);
    bt[6].initButton(&tft,  40, 210, 60, 40, WHITE, CYAN, BLACK, "7", 2);
    bt[7].initButton(&tft, 110, 210, 60, 40, WHITE, CYAN, BLACK, "8", 2);
    bt[8].initButton(&tft, 180, 210, 60, 40, WHITE, CYAN, BLACK, "9", 2);
    bt[9].initButton(&tft, 260, 110, 70, 40, WHITE, CYAN, BLACK, "SET", 2);
    bt[10].initButton(&tft, 260, 210, 70,40, WHITE, CYAN, BLACK, "0", 2);
    bt[11].initButton(&tft, 260, 160, 70, 40, RED, RED, BLACK, "CLR", 2);
    bt[12].initButton(&tft, 260, 60, 70, 40, BLUE, BLUE, BLACK, "BACK", 2);
    bt[13].initButton(&tft, 180, 20, 60, 40, WHITE, CYAN, BLACK, "MIN", 2);
    bt[14].initButton(&tft, 180, 65, 60, 40, WHITE, CYAN, BLACK, "SEC", 2);
    int count=0;
    while(count<15)
    {
      bt[count].drawButton(false);
      count=count+1;
    }
    tft.drawRect(5, 5, 140, 70, RED);
}
void Time_Values()
{
  
  while(1)
  {
     bool down = Touch_getXY();
     int count=0;
      
      bt[0].press(down&&bt[0].contains(pixel_x,pixel_y));
      bt[1].press(down&&bt[1].contains(pixel_x,pixel_y));
      bt[2].press(down&&bt[2].contains(pixel_x,pixel_y));
      bt[3].press(down&&bt[3].contains(pixel_x,pixel_y));
      bt[4].press(down&&bt[4].contains(pixel_x,pixel_y));
      bt[5].press(down&&bt[5].contains(pixel_x,pixel_y));
      bt[6].press(down&&bt[6].contains(pixel_x,pixel_y));
      bt[7].press(down&&bt[7].contains(pixel_x,pixel_y));
      bt[8].press(down&&bt[8].contains(pixel_x,pixel_y));
      bt[9].press(down&&bt[9].contains(pixel_x,pixel_y));
      bt[10].press(down&&bt[10].contains(pixel_x,pixel_y));
      bt[11].press(down&&bt[11].contains(pixel_x,pixel_y));
      bt[12].press(down&&bt[12].contains(pixel_x,pixel_y));
      bt[13].press(down&&bt[13].contains(pixel_x,pixel_y));
      bt[14].press(down&&bt[14].contains(pixel_x,pixel_y));

      if(bt[0].justReleased())
        bt[0].drawButton();
      if(bt[1].justReleased())
        bt[1].drawButton();
      if(bt[2].justReleased())
        bt[2].drawButton();
      if(bt[3].justReleased())
        bt[3].drawButton();
      if(bt[4].justReleased())
        bt[4].drawButton();
      if(bt[5].justReleased())
        bt[5].drawButton();
      if(bt[6].justReleased())
        bt[6].drawButton();
       if(bt[7].justReleased())
        bt[7].drawButton();
       if(bt[8].justReleased())
        bt[8].drawButton();
       if(bt[9].justReleased())
        bt[9].drawButton();
      if(bt[10].justReleased())
        bt[10].drawButton();   
      if (bt[11].justReleased())
        bt[11].drawButton();
    if (bt[12].justReleased())
        bt[12].drawButton();
    if (bt[13].justReleased())
        bt[13].drawButton();
    if (bt[14].justReleased())
        bt[14].drawButton();
    if (bt[0].justPressed()) {
        bt[0].drawButton(true);
        tft.setCursor(x,y);
        tft.setTextSize(3);
        tft.setTextColor(WHITE);
        tft.print("1");
        calc_Values(1);
          x=x+20;
    }
    if (bt[1].justPressed()) {
        bt[1].drawButton(true);
        tft.setCursor(x,y);
        tft.setTextSize(3);
        tft.setTextColor(WHITE);
        tft.print("2");
     calc_Values(2);
        x=x+20;
    }
    if (bt[2].justPressed()) {
        bt[2].drawButton(true);
        tft.setCursor(x,y);
        tft.setTextSize(3);
        tft.setTextColor(WHITE);
        tft.print("3");
        calc_Values(3);
        x=x+20;   
    }
    if (bt[3].justPressed()) {
        bt[3].drawButton(true);
        tft.setCursor(x,y);
        tft.setTextSize(3);
        tft.setTextColor(WHITE);
        tft.print("4");
        calc_Values(4);
        x=x+20;
    }
    if (bt[4].justPressed()) {
        bt[4].drawButton(true);
        tft.setCursor(x,y);
        tft.setTextSize(3);
        tft.setTextColor(WHITE);
        tft.print("5"); 
         calc_Values(5);
        x=x+20;
    }
    if (bt[5].justPressed()) {
        bt[5].drawButton(true);
        tft.setCursor(x,y);
        tft.setTextSize(3);
        tft.setTextColor(WHITE);
        tft.print("6");
         calc_Values(6);
          x=x+20;
        }
        
    if(bt[6].justPressed()) {
        bt[6].drawButton(true);
        tft.setCursor(x,y);
        tft.setTextSize(3);
        tft.setTextColor(WHITE);
        tft.print("7"); 
        calc_Values(7);
        x=x+20;
    }
    if (bt[7].justPressed()) {
        bt[7].drawButton(true);
        tft.setCursor(x,y);
        tft.setTextSize(3);
        tft.setTextColor(WHITE);
        tft.print("8");
        calc_Values(8); 
        x=x+20; 
    }
    if (bt[8].justPressed()) {
        bt[8].drawButton(true);
        tft.setCursor(x,y);
        tft.setTextSize(3);
        tft.setTextColor(WHITE);
        tft.print("9");
        calc_Values(9);
        x=x+20;
    }
   
    if (bt[9].justPressed()) {
        bt[9].drawButton(true);
      if(MIN==1)
        {
          min_counter=num;
          Serial.println(min_counter);
          tft.setCursor(20,50);
        tft.setTextSize(2);
        tft.setTextColor(WHITE);
        tft.print("MIN SET!");
        x=20;
        }
        else
        {
          sec_counter=num;
          Serial.println(sec_counter);
          tft.setCursor(20,50);
        tft.setTextSize(2);
        tft.setTextColor(WHITE);
        tft.print("SEC SET!");
        x=20;
        }
    }
      if (bt[10].justPressed()) {
        bt[10].drawButton(true);
        tft.setCursor(x,y);
        tft.setTextSize(3);
        tft.setTextColor(WHITE);
        tft.print("0");
        calc_Values(0);
        x=x+20;
    }   
    if (bt[11].justPressed()) {
        bt[11].drawButton(true);
        tft.fillRect(6, 6, 138,68, BLACK);
        x=20;
        num=0;
    }
     if (bt[12].justPressed()) {
        bt[12].drawButton(true);
        Main_page();
        x=20;
    }
    if (bt[13].justPressed()) {
        bt[13].drawButton(true);
        num=0;
        MIN=true;
        //Serial.println("Min");
        tft.fillRect(6, 6, 138,68, BLACK);
        x=15;
    }
    if (bt[14].justPressed()) {
        bt[14].drawButton(true);
        //Serial.println("Sec");
       tft.fillRect(6, 6, 138,68, BLACK);
       num=0;
       MIN=false;
       x=15;
    }
  }
}
int ringMeter(int value, int vmin, int vmax, int x, int y, int r, char *units, byte scheme)
{
  // Minimum value of r is about 52 before value text intrudes on ring
  // drawing the text first is an option
  
  x += r; y += r;   // Calculate coords of centre of ring
  int w = r / 3;    // Width of outer ring is 1/4 of radius 
  int angle = 150;  // Half the sweep angle of meter (300 degrees)
  int v = map(value, vmin, vmax, -angle, angle); // Map the value to an angle v
  byte seg = 3; // Segments are 3 degrees wide = 100 segments for 300 degrees
  byte inc = 6; // Draw segments every 3 degrees, increase to 6 for segmented ring
  // Variable to save "value" text colour from scheme and set default
  int colour = BLUE;
 
  // Draw colour blocks every inc degrees
  for (int i = -angle+inc/2; i < angle-inc/2; i += inc) {
    // Calculate pair of coordinates for segment start
    float sx = cos((i - 90) * 0.0174532925);
    float sy = sin((i - 90) * 0.0174532925);
    uint16_t x0 = sx * (r - w) + x;
    uint16_t y0 = sy * (r - w) + y;
    uint16_t x1 = sx * r + x;
    uint16_t y1 = sy * r + y;

    // Calculate pair of coordinates for segment end
    float sx2 = cos((i + seg - 90) * 0.0174532925);
    float sy2 = sin((i + seg - 90) * 0.0174532925);
    int x2 = sx2 * (r - w) + x;
    int y2 = sy2 * (r - w) + y;
    int x3 = sx2 * r + x;
    int y3 = sy2 * r + y;

    if (i < v) { // Fill in coloured segments with 2 triangles
      switch (scheme) {
        case 0: colour = RED; break; // Fixed colour
        case 1: colour = GREEN; break; // Fixed colour
        case 2: colour = BLUE; break; // Fixed colour
        case 3: colour = rainbow(map(i, -angle, angle, 0, 127)); break; // Full spectrum blue to red
        case 4: colour = rainbow(map(i, -angle, angle, 70, 127)); break; // Green to red (high temperature etc)
        case 5: colour = rainbow(map(i, -angle, angle, 127, 63)); break; // Red to green (low battery etc)
        default: colour = BLUE; break; // Fixed colour
      }
      tft.fillTriangle(x0, y0, x1, y1, x2, y2, colour);
      tft.fillTriangle(x1, y1, x2, y2, x3, y3, colour);
      //text_colour = colour; // Save the last colour drawn
    }
    else // Fill in blank segments
    {
      tft.fillTriangle(x0, y0, x1, y1, x2, y2, GREY);
      tft.fillTriangle(x1, y1, x2, y2, x3, y3, GREY);
    }
  }
  // Convert value to a string
  char buf[10];
  byte len = 2; if (value > 999) len = 4;
  dtostrf(value, len, 0, buf);
  buf[len] = ' '; buf[len] = 0; 
  // Set the text colour to default
  tft.setTextSize(1);

  if(value>9){
  tft.setTextColor(colour,BLACK);
  tft.setCursor(x-20,y-20);tft.setTextSize(4);
  tft.print(buf);}
  if(value<10){
  tft.setTextColor(colour,BLACK);
  tft.setCursor(x-20,y-15);tft.setTextSize(4);
  tft.print(buf);}
  tft.setTextColor(WHITE,BLACK);
  return x + r;
}

// #########################################################################
// Return a 16 bit rainbow colour
// #########################################################################
unsigned int rainbow(byte value)
{
  // Value is expected to be in range 0-127
  // The value is converted to a spectrum colour from 0 = blue through to 127 = red

  byte red = 0; // Red is the top 5 bits of a 16 bit colour value
  byte green = 0;// Green is the middle 6 bits
  byte blue = 0; // Blue is the bottom 5 bits
  byte quadrant = value / 32;

  if (quadrant == 0) {
    blue = 31;
    green = 2 * (value % 32);
    red = 0;
  }
  if (quadrant == 1) {
    blue = 31 - (value % 32);
    green = 63;
    red = 0;
  }
  if (quadrant == 2) {
    blue = 0;
    green = 63;
    red = value % 32;
  }
  if (quadrant == 3) {
    blue = 0;
    green = 63 - 2 * (value % 32);
    red = 31;
  }
  return (red << 11) + (green << 5) + blue;
}

float sineWave(int phase) {
  return sin(phase * 0.0174532925);
}
void Timer_Layout()
{
  Timer1.initialize(1000000);
  Timer1.attachInterrupt(Time);
  tft.setRotation(1); // Set Rotation at 0 degress (default)
tft.fillScreen(BLACK); //Set Background Color with BLACK
 btn_Stop.initButton(&tft, 280, 160, 60, 50, RED, BLACK, RED, "STOP", 2);
    btn_Stop.drawButton(false);
    tft.setCursor (7,208);
    tft.setTextSize (3);
    tft.setTextColor (WHITE,BLACK);
    tft.print ("TIME:"); 
    tft.setCursor (65,108);
    tft.setTextSize (1);
    tft.setTextColor (WHITE,BLACK);
    tft.print ("TEMP");
    tft.setCursor (68,69);
    tft.setTextSize (1);
    tft.setTextColor (WHITE,BLACK);
     tft.setCursor (220,108);//heat index fahrenheit
    tft.setTextSize (1);
    tft.setTextColor (WHITE,BLACK);
    tft.print ("PRESSURE");
    tft.setCursor (55,128);//heat index fahrenheit
    tft.setTextSize (1);
     tft.print ("CELSIUS");
     tft.setCursor (230,128);//heat index fahrenheit
     tft.print ("BAR");
    
    tft.fillRect(0,158,230,4,BLUE);
    tft.fillRect(0,197,320,4,BLUE);
    tft.fillRect(0,236,320,4,BLUE);
     tft.setCursor (7,168);//heat index fahrenheit
    tft.setTextSize (3);
    tft.setTextColor (WHITE,BLACK);
    tft.print ("CHANNEL:");
    tft.print(Channel);
   
    tft.fillRect(98,203,80,30,BLACK);
    tft.setCursor(172,200);
    tft.setTextSize(5);
    tft.setTextColor(RED);
    tft.print(":");
    tft.fillRect(190,203,80,30,BLACK);
    Timer_Countdown();
}
void Timer_Countdown()
{
  while(1)
  {
   int xpos = 15, ypos = 5, gap = 100, radius = 60;
    ringMeter(30,0,100, xpos,ypos,radius,"Celsius",GREEN2RED); // Draw analogue meter
    xpos=180;ypos=5;
   ringMeter(80,0,100, xpos,ypos,radius,"Bar",GREEN2RED); // Draw analogue meter //
// Code that runs during the countdown//


   
   bool down=Touch_getXY();
 btn_Stop.press(down&&btn_Stop.contains(pixel_x,pixel_y));
if (btn_Stop.justReleased())
       btn_Stop.drawButton();
 else if (btn_Stop.justPressed())
    {
      Main_page();
      Channel=0;min_counter=0;sec_counter=0;
    }
  }
}
void Time() {
  // Interrupt Countdown//
if(sec_counter==0&&min_counter!=0)
{
  min_counter=min_counter-1;
  sec_counter=60;
}
sec_counter=sec_counter-1;
if(min_counter==0&&sec_counter==0)
{
  Timer1.stop();
  //Serial.println("Over");
  Main_page();
  Channel=0;min_counter=0;sec_counter=0;
}
  tft.setTextSize(3);
  tft.setTextColor(RED);
  if(min_counter<10)
  {tft.fillRect(98,203,80,30,BLACK);
    tft.setCursor(115,207);
    tft.print("00");
  tft.print(min_counter);
  }
  if(min_counter>=10&&min_counter<100)
  {
    tft.fillRect(98,203,80,30,BLACK);
    tft.setCursor(115,207);
    tft.print("0");
    tft.print(min_counter);
  }
  if(min_counter>=100)
  {
    tft.fillRect(98,203,80,30,BLACK);
    tft.setCursor(115,207);
    tft.print("0");
    tft.print(min_counter);
  }
  
  if(sec_counter<10)
  { 
    tft.fillRect(190,203,180,30,BLACK);
    tft.setCursor(195,207);
    tft.print("0");
    tft.setCursor(213,207);
    tft.print(sec_counter);
    
  }
  if(sec_counter>=10)
  {
    tft.fillRect(190,203,180,30,BLACK);
    tft.setCursor(195,207);
    tft.print(sec_counter);
  }
}
void set_Temp()
{
  set=false;
  Temp_Channel_Layout();
  Temp_Channel_Values(set);
  if(Channel>12)
  {
       tft.setCursor(20,50);
        tft.setTextSize(2);
        tft.setTextColor(WHITE);
        tft.print("WRONG VAL");
        delay(3000);
        Channel=0;
        tft.fillRect(6, 6, 200,60, BLACK);
        x=20;
       Temp_Channel_Values(set);
  }
}
void set_Channel()
{
  set=true;
 Temp_Channel_Layout();
 Temp_Channel_Values(set);
}
void set_Time()
{
  Time_Layout();
  Time_Values();
}
void Start_Timer()
{
  Timer_Layout();
  Timer_Countdown();
}
void setup() {
  // put your setup code here, to run once:
    Serial.begin(9600);
    uint16_t ID = tft.readID();
    Serial.print("TFT ID = 0x");
    Serial.println(ID, HEX);
    Serial.println("Calibrate for your Touch Panel");
    if (ID == 0xD3D3) ID = 0x9486; 
    tft.begin(ID);
    tft.setRotation(1);            //Landscape
    splash_screen();
    tft.fillScreen(BLACK);
    Main_page();
}

void loop() {
  // put your main code here, to run repeatedly:

}
