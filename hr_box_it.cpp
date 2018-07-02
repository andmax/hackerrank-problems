#include<bits/stdc++.h>

using namespace std;

//Implement the class Box  
//l,b,h are integers representing the dimensions of the box

class Box {
public:
    int l, b, h;
    Box() : l(0), b(0), h(0) { }
    Box(const int& _l, const int& _b, const int& _h) : l(_l), b(_b), h(_h) { }
    Box(const Box& _b) : l(_b.l), b(_b.b), h(_b.h) { }
    int getLength() const { return l; }
    int getBreadth() const { return b; }
    int getHeight() const { return h; }
    long long CalculateVolume() const {
        long long r = h; r *= b; r *= l;
        return r;
    }
    bool operator < (const Box& _b) const {
        if (l != _b.l)
            return l < _b.l;
        else {
            if (b != _b.b)
                return b < _b.b;
            else {
                return h < _b.h;
            }
        }
    }
    friend ostream& operator << (ostream& out, const Box& _b) {
        out << _b.l << ' ' << _b.b << ' ' << _b.h << flush;
        return out;
    }
};

// The class should have the following functions : 

// Constructors: 
// Box();
// Box(int,int,int);
// Box(Box);


// int getLength(); // Return box's length
// int getBreadth (); // Return box's breadth
// int getHeight ();  //Return box's height
// long long CalculateVolume(); // Return the volume of the box

//Overload operator < as specified
//bool operator<(Box& b)

//Overload operator << as specified
//ostream& operator<<(ostream& out, Box& B)

void check2()
{
    int n;
    cin>>n;
    Box temp;
    for(int i=0;i<n;i++)
    {
        int type;
        cin>>type;
        if(type ==1)
        {
            cout<<temp<<endl;
        }
        if(type == 2)
        {
            int l,b,h;
            cin>>l>>b>>h;
            Box NewBox(l,b,h);
            temp=NewBox;
            cout<<temp<<endl;
        }
        if(type==3)
        {
            int l,b,h;
            cin>>l>>b>>h;
            Box NewBox(l,b,h);
            if(NewBox<temp)
            {
                cout<<"Lesser\n";
            }
            else
            {
                cout<<"Greater\n";
            }
        }
        if(type==4)
        {
            cout<<temp.CalculateVolume()<<endl;
        }
        if(type==5)
        {
            Box NewBox(temp);
            cout<<NewBox<<endl;
        }

    }
}

int main()
{
    check2();
}
