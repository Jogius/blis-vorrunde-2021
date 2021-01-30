#include <iostream>
#include <vector>

using namespace std;

int main()
{
  int breite, n;
  cin >> breite >> n;

  int maximaleDistanz = 0;
  for (int i = 0; i < n; i++)
  {
    int position, richtung;
    cin >> position >> richtung;

    int aktuellerAbstand = richtung ? position
                                    : breite - position;

    if (aktuellerAbstand > maximaleDistanz)
      maximaleDistanz = aktuellerAbstand;
  }

  int time = maximaleDistanz * 0.6;
  cout << time << endl;
}
