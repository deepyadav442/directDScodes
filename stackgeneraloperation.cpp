#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
typedef long long ll;
using namespace std;

class stacking
    {
    public:
        ll listing[100001],top;
            stacking()
            {
                top=-1;
                int list={0};
            }
       void push(ll);
        void pop();
        void print();
};
void stacking::push(ll number)
{
    listing[++top]=number;
}
void stacking::pop()
{
    ll received=listing[top--];
}
void stacking ::print()
{
    ll maximum=0;
    for(int i=top;i>=0;i--)
    {
        if(maximum<=listing[i])
            maximum=listing[i];
    }
    cout<<maximum<<endl;

}
int main() {
    int n;
    cin>>n;
    stacking call;
    while(n--)
        {
        int type;
        long long number;
        cin>>type;
        if(type==1)
            {
            cin>>number;
            call.push(number);
        }
        else if(type==2)
            {
            call.pop();
        }
        else
        {
            call.print();
        }
    }

    return 0;
}

