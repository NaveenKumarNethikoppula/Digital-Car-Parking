#include<iostream>
using namespace std;
#include "Parking_System.h"
int main()
{
    display();
    int option;
    while(1)
    {
	cout << "\n--------------------------------" << endl;
	cout << "   MENU IS DISPLAYING  " << endl;
	cout << "--------------------------------" << endl;
	cout << "1.Park a Car" << endl;
	cout << "2.Exit a Car" << endl;
	cout << "3.Exit a Program" << endl;
	cout << "--------------------------------" << endl;
	cout << "Enter Your Choice : " << endl;
	cin >> option;
	cout << "\n--------------------------------" << endl;
	switch(option)
	{
	    case 1:
		cout << "You Choosed Park a Car" << endl;
		park_car();
		display();
		break;
	    case 2 :
		cout << "You Choosed Exit a Car" << endl;
		exit_car();
		display();
		break;
	    case 3 :
		return 0;
	}
    }
    return 0;
}

