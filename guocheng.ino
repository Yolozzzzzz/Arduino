void ledliushui(String num1, String num2, String num3, String num4, int r, int g, int b)
{

  for (int i = 0; i < NUMPIXELS; i++) {
    if (num1 == "1")pixels1.setPixelColor(i, pixels1.Color(r, g, b));
    if (num2 == "1")pixels2.setPixelColor(i, pixels1.Color(r, g, b));
    if (num3 == "1")pixels3.setPixelColor(i, pixels1.Color(r, g, b));
    if (num4 == "1")pixels4.setPixelColor(i, pixels1.Color(r, g, b));
    pixels1.show(); // This sends the updated pixel color to the hardware.
    pixels2.show();
    pixels3.show();
    pixels4.show();
    delay(20);
  }
  for (int i = 0; i < NUMPIXELS; i++) {
    pixels1.setPixelColor(i, pixels1.Color(0, 0, 0)); // Moderately bright green color.
    pixels2.setPixelColor(i, pixels1.Color(0, 0, 0));
    pixels3.setPixelColor(i, pixels1.Color(0, 0, 0));
    pixels4.setPixelColor(i, pixels1.Color(0, 0, 0));
    pixels1.show(); // This sends the updated pixel color to the hardware.
    pixels2.show();
    pixels3.show();
    pixels4.show();
    delay(20);
  }
}
void ledshan(String num1, String num2, String num3, String num4, int r, int g, int b)
{
    for (int i = 0; i < NUMPIXELS; i++) {
      if (num1 == "1")pixels1.setPixelColor(i, pixels1.Color(r, g, b));
      if (num2 == "1")pixels2.setPixelColor(i, pixels1.Color(r, g, b));
      if (num3 == "1")pixels3.setPixelColor(i, pixels1.Color(r, g, b));
      if (num4 == "1")pixels4.setPixelColor(i, pixels1.Color(r, g, b));
    }
    pixels1.show(); // This sends the updated pixel color to the hardware.
    pixels2.show();
    pixels3.show();
    pixels4.show();
    delay(100);
    for (int i = 0; i < NUMPIXELS; i++) {
      pixels1.setPixelColor(i, pixels1.Color(0, 0, 0)); // Moderately bright green color.
      pixels2.setPixelColor(i, pixels1.Color(0, 0, 0));
      pixels3.setPixelColor(i, pixels1.Color(0, 0, 0));
      pixels4.setPixelColor(i, pixels1.Color(0, 0, 0));
    }
    pixels1.show(); // This sends the updated pixel color to the hardware.
    pixels2.show();
    pixels3.show();
    pixels4.show();
    delay(100);
}
void xinjianwenjian(String wenjian)
{
  if (SD.exists(wenjian)) //检查文件是否存在
  {
    SD.remove(wenjian);
  }
  File myFile;
  myFile = SD.open(wenjian, FILE_WRITE);  //打开如果没有自动创建，写入状态
  myFile.close();  //关闭文件
}
