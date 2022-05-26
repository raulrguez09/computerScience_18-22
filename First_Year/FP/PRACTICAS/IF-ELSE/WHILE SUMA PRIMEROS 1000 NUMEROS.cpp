#include <iostream>

using namespace std;

int main (){
	
int i=1, s=0;

while (i <= 1000){
	s = s + i;
	i = i +1;
}
cout << "\n" << s;
return 0;
}
