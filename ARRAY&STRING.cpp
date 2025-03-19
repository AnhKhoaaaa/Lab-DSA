#include <iostream>
using namespace std;
void arrayTraversal()
{
    int arr[] = {10, 20, 30, 40, 50};
    int n = sizeof(arr) / sizeof(arr[0]);
    cout << "Array elements: ";
    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }
    return;
}

void stringMalnipulate()
{
    string name = "Alice";
    cout << "Original: " << name << endl;

    name.append(" In Wonderland");
    cout << "Updated: " << name << endl;
    cout << "Length: " << name.length() << endl;
    return;
}

int main()
{
    arrayTraversal();
    cout << endl;
    stringMalnipulate();
}