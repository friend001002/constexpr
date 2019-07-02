#include <iostream>

#include <stdio.h>

using namespace std;

constexpr double Add(double a, double b)
{
  return a + b; // In C++11 can't make variables.
}

constexpr double Div(double a, double b)
{
  // In C++14 constexpr functions can have if's and stuff.

  if (b == 0.0)
  {
    b = 0.00000000001;
  }

  int tmp = 2; // Need to initialize immediately.

  //static int st = 9; // Can't use statics.
  //thread_local int thr = 5; // Can't use thread-locals.

  return a / b;
}

class C
{
  private:

  /*virtual constexpr void Fun() // constexpr can't be virtual.
  {
  }*/

  public:

  int flag_;

  constexpr C() : flag_(0) // constexpr have to initialize fields in this fashon.
  {
    //cout << "Constexpr constructor\n"; // Can't have couts.

    int g = 9;
  }

  static constexpr void Fun_static()
  {
    //cout << "Static constexpr class function\n";

    //this->flag = 0; // Statics don't have this.
  }

  constexpr void Fun()
  {
    //cout << "Non-Static constexpr class function\n";

    this->flag_ = 1;

    //cout << "Flag is " << this->flag_ << " now\n";
  }
};

int main()
{
  constexpr int a = 7; // Need to initialize immediately.

  constexpr float b = a; // One constexpr can inintialize another.

  const /*double*/ int c = 3; // Cannot use const double as constant expression.

  constexpr double d = c;

  constexpr double e = b / d;

  //constexpr float f = 3.2F / 0.0F; // Dividing by zero is invalid.

  printf("a %d, b %f, c %d, d %f, e %f", a, b, c, d, e);

  cout << "Compile-time 2.1 + 3.2: " << Add(2.1, 3.2) << endl;

  double f {};
  double g {};

  cout << "Provide with f and g: ";
  cin >> f >> g;

  cout << "Run-time " << f << " + " << g << ": " << Add(f, g) << endl;

  cout << "Compile-time 12.1 / 4.0: " << Div(12.1, 4.0) << endl;

  cout << "Provide with f and g: ";
  cin >> f >> g;

  cout << "Run-time " << f << " / " << g << ": " << Div(f, g) << endl;

  C cls;

  cout << "After construction flag is " << cls.flag_ << endl;

  C::Fun_static();

  cout << "After Fun_static flag is " << cls.flag_ << endl;

  cls.Fun();

  cout << "After Fun flag is " << cls.flag_ << endl;

  extern int ext;

  //goto false_label; // Can't jump into if constexpr.

  // C++17
  if constexpr (true)
  {
    cout << "True\n";

    //goto false_label; // Can't jump from true to false.

    goto after_if_constexpr;
  }
  else
  {
    //false_label: // Can't have unused labels inside if constexpr.

    ext += 5; // In false part can use unreferenced externs.
  }

  after_if_constexpr:

  cout << "Can jump out of if constexpr\n";

  if constexpr (a > c)
  {
    cout << "a = " << a << " > c = " << c << endl;
  }
  else
  {
    cout << "a = " << a << " < c = " << c << endl;
  }

  /*if constexpr (f > g) // f and g aren't constant expressions.
  {
    cout << "f = " << f << " > g = " << g << endl;
  }
  else
  {
    cout << "f = " << f << " < g = " << g << endl;
  }*/

  cin.get();
  cin.get();
}
