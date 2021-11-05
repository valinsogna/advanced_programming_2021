#include <iostream>
//Why shouldn't we use using namespace:
//OSS: trick for 1 starting enum
enum month { jan = 1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec };

using namespace std;

int main() {
  cout << nov << '\n';
  //If I decomment I get an error since dec is also present in std!
  //cout << dec << endl;

  //But if I change it into scope enum:
  //enum class month { jan = 1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec };
  //And I call it:
  //cout << month::nov << endl;
  //cout << month::dec << endl;
  
  //OR
  cout << static_cast<int>(month::nov) << '\n';
  cout << static_cast<int>(month::dec) << endl;
  return 0;
}
