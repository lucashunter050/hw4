#include <iostream>
#include <cstdlib>
#include "equal-paths.h"
using namespace std;


Node* a;
Node* b;
Node* c;
Node* d;
Node* e;
Node* f;

Node* t;
Node* v;
Node* w;
Node* x;
Node* y;
Node* z;

void setNode(Node* n, int key, Node* left=NULL, Node* right=NULL)
{
  n->key = key;
  n->left = left;
  n->right = right;
}

void test1(const char* msg)
{
  setNode(a,1,NULL, NULL);
  cout << msg << ": " <<   equalPaths(a) << endl;
}

void test2(const char* msg)
{
  setNode(a,1,b,NULL);
  setNode(b,2,NULL,NULL);
  cout << msg << ": " <<   equalPaths(a) << endl;
}

void test3(const char* msg)
{
  setNode(a,1,b,c);
  setNode(b,2,NULL,NULL);
  setNode(c,3,NULL,NULL);
  cout << msg << ": " <<   equalPaths(a) << endl;
}

void test4(const char* msg)
{
  setNode(a,1,NULL,c);
  setNode(c,3,NULL,NULL);
  cout << msg << ": " <<   equalPaths(a) << endl;
}

void test5(const char* msg)
{
  setNode(a,1,b,c);
  setNode(b,2,NULL,d);
  setNode(c,3,NULL,NULL);
  setNode(d,4,NULL,NULL);
  cout << msg << ": " <<   equalPaths(a) << endl;
}

void test6(const char* msg)
{
  setNode(a,1,b,c);
  setNode(b,2,d,t);
  setNode(c,3,v,w);
  setNode(d,4,x,NULL);
  setNode(t,5,NULL,NULL);
  setNode(v,6,NULL,NULL);
  setNode(w,7,NULL,NULL);
  setNode(x,8,NULL,NULL);
  //setNode(y,9,b,c);
  //setNode(z,10,NULL,d);

  cout << msg << ": " << static_cast<bool>(equalPaths(a)) << endl;
}

int main()
{
  a = new Node(1);
  b = new Node(2);
  c = new Node(3);
  d = new Node(4);

  t = new Node(5);
  v = new Node(6);
  w = new Node(7);
  x = new Node(8);
  y = new Node(9);
  z = new Node(10);

  test1("Test1");
  test2("Test2");
  test3("Test3");
  test4("Test4");
  test5("Test5");

  test6("Test6");
 
  delete a;
  delete b;
  delete c;
  delete d;
}

