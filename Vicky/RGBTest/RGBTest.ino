byte red, green, blue;
unsigned long rgb = 0x6f56a3;
string test;
void setup()
{
  Serial.begin(9600);

  test = GenerateRgba(rgb);
  Serial.println(test);
}



void loop(){


  }
  public string GenerateRgba(string backgroundColor, decimal backgroundOpacity)
{
 Color color = ColorTranslator.FromHtml(hexBackgroundColor);
 int r = Convert.ToInt16(color.R);
 int g = Convert.ToInt16(color.G);
 int b = Convert.ToInt16(color.B);
 return string.Format("rgba({0}, {1}, {2}, {3});", r, g, b, backgroundOpacity);
}