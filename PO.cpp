class BaseFoo
{
  public:
  BaseFoo();
};

class Foo:public BaseFoo      
{                             
public:
  int x;
  static int bar;
  
  Foo:BaseFoo();

  Foo(int)
  {
    this->x = x;
    cout<<"konstruktor konwertujacy\n";
  }
  
  Foo(Foo &foo) 
  {
    this->x = foo.x;
    cout<<"konstruktor kopiujacy\n";
  }
  
  static void method();     
  void foo();
};

explicit - zabrania niejawnej konwersji

   int x = static_cast<int>(1.2)  zwykly cast
   dynamic_cast<typ *>(ptr);
   dynamic_cast<typ &>(a);    jesli nie jest tego typu przypisuje NULL
   reinterpret_cast (najgorszy)  rzadko daje to co chcielismy cos tam z biciorami miesza odcina to co sie nie miesci w pamieci
   const_cast jesli mamy stala to zrzutuje na niestala
 //*************
  
template <int N>
class Foo
{
  int a[N];  
};

class Foo
{
  Foo &operator ++() const    //"const"deklarujemy ze korzystajac z tej metody nie bedziemy mogli zmieniac pol "this"
  {
    // tutaj operacje operatora  
    return *this;
  }
};

//przeciazanie binarnego
class Foo
{
  Foo operator +(Foo const& prawy) const    
  {
    this->a;
    Foo result;
    return result;
  }
};
  

struct RangeNotValid
{
  string s;
};

float sqrt(float n)
{
  if(n<0)
  {
    throw RangeNotValid{"abc"};
  }
}

int main()
{
  try
  {
    sqrt(-3);
  }
  catch (RangeNotValid &rnv)
  {
    cout << rnv.s << endl;
  }
}
//****************

auto a = 1; //dedukcja typu

std::vector<int>::iterator it = v.begin();
auto it2 = v.begin(); //lepiej

std::vector<int> v[10];

int f(){return 0;} 
decltype(f()) b; // == int b;
it(i); //it staje się referncją na it

  template<class T, class T2>
  auto foo(int, float){
    return T + T2; //samo wykryje typ
  }
  
lambda:
[]()/*mutable*/->{}()
[lista przechwytywanch nazw]
(argumenty przyjmowane, prze lambdę - opcjonalnie)
mutable - żebyśmy mogli dokonywać zmain, na lokalnej kopii zmiennej przechwyconej przez wartość
-> T opcionalne, typ zwracany przez lambdę 
{ciało wyrażenia}
(czym wywołujemy)

[ & ] - wszystko przez referencję 
[ &, a ] - wszystko przez referencję, oprócz a
[ = ] - wszystko przez wartość
[ =, &a ] - wszystko przez wartość oprócz a
//*****
 int a = 6; //ok
 int &b = a; //ok
 
l-value wszystko co może być po lewej stronie =
  
int &&d = 6; //ok

const int& e = 5; // wyjątek

klasa::klasa(klasa &&); - konstruktor przenoszący


class A{
  private: 
  int size;
  int * data = nullptr;
  public:
  A(int n){
    data = new int[n];
    size = n;
  }
  A(A && a){              //przenoszenie
    this->data = a.data;
    a.data = nullptr;
    this->size = a.size;
  }
  A(const A & a){         //kopiowanie
    data = new int[a.size];
    size = a.size;
    for(int i = 0; i < size; i++)
      data[i] = a.data[i];
  }
};

//*******
//*********
#include <iostream>
#include <memory>
using namespace std;

template <class T>
struct Node
{
    T data;
    unique_ptr<Node> next;

    Node(T d, unique_ptr<Node> n) : data(d), next(nullptr){};

    void push_back(T &d)
    {
        if (next == nullptr)
        {
            next = make_unique<Node>(d, nullptr);
        }
        else
        {
            next->push_back(d);
        }
    }
};

template <class T>
class Stack
{
  private:
    unique_ptr<Node<T>> head;

  public:
    Stack() : head(nullptr){};

    void push_back(T value)
    {
        if (head == nullptr)
        {
            head = make_unique<Node<T>>(value, nullptr);
        }
        else
        {
            head->push_back(value);
        }
    }

    void pop()
    {
        while(head->next)
        {
            head = head->next;
        }
        head = nullptr;
    }

    void print()
    {
        shared_ptr<Node<T>> temp = move(head);
        while (temp)
        {
            cout << temp->data << endl;
            temp = move(temp->next);
        }
    }
};

int main()
{
    Stack<int> intStack;
    intStack.push_back(10);
    intStack.push_back(20);
    intStack.push_back(30);
    intStack.print();
    intStack.pop();
    intStack.print();
    system("pause");
}



void exec(void <function(auto elem)>);
lista.exec([](auto elem){cout << elem << " ";});

//*********
template <int N>
struct factorial;


template <int N>
struct factorial {
	enum { value = N * factorial<N - 1>::value };
};

template <>
struct factorial<0> {
	enum { value = 1 };
};

int main(){
  static_assert(factorial<4>::value == 24, "!");
  return 0;
}


constexpr int factorial(int n){
  int result = 1;
  for(int i = 1; i<=n; i++)
    result *=i;
  return result;
  
}

template<int n>
struct fib{
  enum{value = fib<n-1>::value + fib<n-2>::value};
};

template<>
struct fib<1>{
  enum{value = 1};
};

template<>
struct fib<0>{
  enum{value = 0};
};

