#define seg7_a 2
int seg7_digit[10]={0xfc, 0x60, 0xda, 0xf2, 0x66, 0xb6, 0xbe, 0xe4, 0xfe, 0xf6};
int digits[4]={10,11,12,13};
unsigned long t0;

void setup()
{
  for (int i = 0; i <8 ; i++)
{
    pinMode(seg7_a + i, OUTPUT);
    digitalWrite(seg7_a + i, LOW);
  }
  for (int i = 0; i < 4; i++)
{
    pinMode(digits[i], OUTPUT);
    digitalWrite(digits[i], HIGH);
  }
 digitalWrite(digits[0], HIGH);
 digitalWrite(digits[1], HIGH);
 digitalWrite(digits[2], HIGH);
 digitalWrite(digits[3], HIGH);
}
void hide_seg7()
{
  for(int i=0; i<4; i++)
  {
     digitalWrite(digits[i], HIGH);
  }
}
void show(int val, bool decimal){
  int mask0 = 0x80;
  int mask;
  for(int i=0; i<8; i++){
    mask = mask0 >> i;
    if(val & mask) digitalWrite(seg7_a + i, HIGH);
    else digitalWrite(seg7_a + i, LOW);
  }
  if(decimal) {
    digitalWrite(seg7_a + 7, HIGH);  // 點亮DP (小數點)
  }
}


void loop() {
  //顯示0000~9999
  int x;
  int d;
  unsigned long t1;
  int toggle = 0;
  int cnt = 0;
  //每0.1秒共陰極4位數七段顯示器顯示0000~9999
     hide_seg7();
  for(int x1=0; x1<10000; x1++)
  {
    t0=millis();
    while(millis()-t0<100)
    {
      x = x1;
      //顯示千位數
      d = x/1000;
      show(seg7_digit[d], false);
      digitalWrite(digits[0], LOW);
      delay(5);
      digitalWrite(digits[0], HIGH);
      //顯示百位數
x = x % 1000;
d = x / 100;
show(seg7_digit[d], false);
digitalWrite(digits[1], LOW);
delay(5);
digitalWrite(digits[1], HIGH);

//顯示個位數
x = x % 100;
d = x % 10;
show(seg7_digit[d], false);  // 第二個參數為true，表示顯示小數點
digitalWrite(digits[2], LOW);
delay(5);
digitalWrite(digits[2], HIGH);

//顯示十位數
d = x / 10;
show(seg7_digit[d], true);
digitalWrite(digits[3], LOW);
delay(5);
digitalWrite(digits[3], HIGH);

    }
  }
}