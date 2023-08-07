double point[] = {0, 0};

class CapacitiveMatrix
{
  int capacitiveCells[64][3];
  double pinToCoord[21][3] = {{0, 0, 0}, {1, 0.988, 0.156}, {2, 0.891, 0.454}, {3, 0.707, 0.707}, {4, 0.454, 0.891}, {5, 0.156, 0.988}, {6, -0.156, 0.988}, {7, -0.454, 0.891}, {8, -0.707, 0.707}, {9, -0.891, 0.454}, {10, -0.988, 0.156}, {11, -0.988, -0.156}, {12, -0.891, -0.454}, {13, -0.707, -0.707}, {14, -0.454, -0.891}, {15, -0.156, -0.988}, {16, 0.156, -0.988}, {17, 0.454, -0.891}, {18, 0.707, -0.707}, {19, 0.891, -0.454}, {20, 0.988, -0.156}};
  int cells;
  int tx_pin;

  public:
  CapacitiveMatrix(int c, int tx)
  {
    cells = c;
    tx_pin = tx;
    for(int i = 1; i<=c; i++){
      capacitiveCells[i][0] = i;
    }
  }

  void Read()
  {
    int pin = -1;
    for(int i = 1; i<=cells; i++){
      if(i == 18){
        continue;
      }
      int read_high = 0;
      int read_low = 0;
      int diff = 0;
      long int sum = 0;
      digitalWrite(tx_pin,HIGH);           // Step the voltage high on conductor 1.
      read_high = analogRead(i);  // Measure response of conductor 2.
      delayMicroseconds(100);              // Delay to reach steady state.
      digitalWrite(tx_pin,LOW);            // Step the voltage to zero on conductor 1.

      read_low = analogRead(i);   // Measure response of conductor 2.
      diff = read_high - read_low;         // desired answer is the difference between high and low.
      if(diff < capacitiveCells[i][2]){
        pin = i;
        if(pin >= 0){
          point[0] = point[0] + pinToCoord[pin][1]/75.0;
          point[1] = point[1] + pinToCoord[pin][2]/75.0;
          myData.speed = 1;
        }
      } else if (diff < capacitiveCells[i][1]){
        pin = i;
        if(pin >= 0){
          point[0] = point[0] + pinToCoord[pin][1]/75.0;
          point[1] = point[1] + pinToCoord[pin][2]/75.0;
          myData.speed = 1;
        }
      } else {
      }
    }
  }

//More code not shown