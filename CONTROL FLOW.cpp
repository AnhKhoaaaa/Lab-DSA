#include <iostream>
using namespace std;

void ifElseState()
{
    int num;
    cout << "Enter a number: ";
    cin >> num;

    if (num % 2 == 0)
    {
        cout << num << " is even." << endl;
    }
    else
    {
        cout << num << " is odd." << endl;
    }
    return;
}

void switchState()
{
    int day;
    cout << "Enter day number (1-7): ";
    cin >> day;

    switch (day)
    {
    case 1:
        cout << "Monday" << endl;
        break;
    case 2:
        cout << "Tuesday" << endl;
        break;
    case 3:
        cout << "Wednesday" << endl;
        break;
    case 4:
        cout << "Thursday " << endl;
        break;
    case 5:
        cout << "Friday " << endl;
        break;
    case 6:
        cout << "Saturday " << endl;
        break;
    case 7:
        cout << "Sunday " << endl;
        break;
    default:
        cout << "Invalid day" << endl;
    }
    return;
}

void whileLoop()
{
    int num = 1;
    while (num <= 5)
    {
        cout << num << " ";
        num++;
    }
    return;
}

void doWhileLoop()
{
    int num = 1;
    do
    {
        cout << num << " ";
        num++;
    } while (num <= 5);
    return;
}

int main()
{
    whileLoop();
    cout << endl;
    doWhileLoop();
}
