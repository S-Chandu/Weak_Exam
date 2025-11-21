#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {

   
    vector<int> numbers;

    numbers.push_back(10);
    numbers.push_back(20);
    numbers.push_back(30);
    numbers.push_back(40);
    numbers.insert(numbers.begin()+2, 25);
   
    auto it = numbers.end()-1;
    while (it != numbers.begin()-1) {
        cout << *it << " ";
        --it;
    }

    cout<<"\n"<<numbers.at(2)<<endl;
    auto F = find(numbers.begin(), numbers.end(), 25);
    numbers.erase(F);
    cout << "Elements after erasing 25: ";
    for (auto num : numbers) {
        cout << num << " ";
    }
    return 0;

}
