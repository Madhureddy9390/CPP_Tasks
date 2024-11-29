#include<iostream>
#include<map>
using namespace std;
class Theme{
    public:
    string backgroundColor;
    string fontColor;
    int frontSize;
    string iconStyle;
    Theme(string backgroundColor,
    string fontColor,
    int frontSize,
    string iconStyle){
        this->backgroundColor=backgroundColor;
        this->fontColor=fontColor;
        this->frontSize=frontSize;
        this->iconStyle=iconStyle;
    }
    void display(){
        cout << "Background Color: " << backgroundColor << endl;
        cout << "Font Color: " << fontColor << endl;
        cout << "Font Size: " << frontSize << endl;
        cout << "Icon Style: " << iconStyle << endl;
    }
};
int main(){
    map<string,Theme*> s;
    s.emplace("Classic",new Theme("green background","white font",3,"Classic"));
    s.emplace("Sport",new Theme("yellow background","black font",5,"Sport"));
    s.emplace("Eco",new Theme("pink background","brown font",32,"Eco"));
    cout<<"choose which theme you want"<<endl;
    bool flag=true;
    while(flag){
    cout<<"1.Classic \n2.Sport \n3.Eco \n4.Exist"<<endl;
    int option;
    cin>>option;
    switch(option){
        case 1:{
        auto s1=s["Classic"];
        s1->display();
        break;
        }
        case 2:{
        auto s2=s["Sport"];
        s2->display();
        break;
        }
        case 3:{
        auto s3=s["Eco"];
        s3->display();
        break;
        }
        case 4:{
        flag=false;
        break;
        }
        default:{
        cout<<"please enter valid option"<<endl;
        }
    }
    }
}