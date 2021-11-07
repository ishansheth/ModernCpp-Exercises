// g++ compiler_output_poc.cpp -O2 -c -S -o - -masm=intel | c++filt | grep -vE '\s+\.'

int myglobal = 42;

int ml_global(int a,int b)
{
  myglobal += a;
  return b + myglobal;
}
