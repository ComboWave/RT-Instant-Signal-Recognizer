#define pi 3.14
#define F1 8
#define F2 6
#define F3 4
unsigned char temp;
int Fs = 20; // sample rate
int N = 5; // six samples
int j = 0;
double Mx[6] = {0};
void setup()
{
  Serial.begin(9600);
}


void loop()
{
  
  for (int i = 0; i < N; i++)
  {
    temp = 127 * (1 + sin(2.0 * pi * i * F1 / Fs));
    Mx[0] += temp;
    Serial.print(temp);
    Serial.print(',');
  }
  Mx[0] /= N;
  Serial.println("  //sin Frq = 8 Hz");
  
  Serial.print("243,78,12,178,243,");
  Mx[1] = 243+78+12+178+243;
  Mx[1] /= N;
  Serial.println("  //sin Frq = 5 Hz");
  
  for (int i = 0; i < N; i++)
  {
    temp = 127 * (1 + sin(2.0 * pi * i * F3 / Fs));
    Mx[2] += temp;
    Serial.print(temp);
    Serial.print(',');
  }
  Mx[2] /= N;
  Serial.println("  //sin Frq = 4 Hz");
  
  Serial.print("252,252,3,252,3");//sqr wave 8hz
  Mx[3] = 252 + 252 + 3 + 252 + 3  ;		
  Mx[3] /= N;
  Serial.println("  //sqr Frq = 8 Hz");

  Serial.print("252,252,252,3,3,"); //sqr wave 4hz using signal genartor
  
  Mx[4] = 252 + 252 + 252 + 3 + 3 ;
  Mx[4] /= 	N;
  Serial.println("  //sqr Frq = 4 Hz"); 
  
  Serial.print("127,1,125,69,30"); //trg wave hz
  Mx[5] = 127 + 1 + 125 + 69 + 30 ;
  Mx[5] /= N;
  Serial.println("  //trg Frq = 8 Hz");
  


  for (int i = 0; i < 6; i++)
  {
    Serial.print(Mx[i]);
    Serial.print(',');
  }
    Serial.println(' ');

  while (1);

}
