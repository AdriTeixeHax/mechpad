#include <Keyboard.h>

#define MAX_ROW 2
#define MAX_COL 2

#define BASE_ROW_PIN 10
#define BASE_COL_PIN 12

int matrix_values[2][2] =
{
  {1,2},
  {3,4}
};

int i = 0, j = 0;

void setup()
{
  pinMode(13, INPUT);
  pinMode(12, INPUT);
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);

  digitalWrite(10, HIGH);
  digitalWrite(11, HIGH);

  Keyboard.begin();
}

void loop()
{
  keyboard_run();
}

void keyboard_run(void)
{
  for(i = 0; i < MAX_ROW; i++)
  {
    digitalWrite(BASE_ROW_PIN + i, LOW);
    for(j = 0; j < MAX_COL; j++)
    {
      if(digitalRead(BASE_COL_PIN + j) == LOW)
      {
        keyboard_press(i, j);
        delay(200);
      }
    }
    digitalWrite(BASE_ROW_PIN + i, HIGH);
  }
}

void keyboard_press(int i, int j)
{
  switch(matrix_values[i][j])
  {
    case 1:
      Keyboard.print("1");
      break;
    case 2:
      Keyboard.print("2");
      break;
    case 3:
      Keyboard.print("3");
      break;
    case 4:
      Keyboard.print("4");
      break;
  }
}