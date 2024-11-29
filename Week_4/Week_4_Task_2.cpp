#include<iostream>
#include<set>
#include<vector>
#include<algorithm>
using namespace std;
int main(){
    vector<string> s;
    s.push_back("Speedometer");
    s.push_back("Tachometer");
    set<string> s1;
    s1.insert("Logo");
    s1.insert("WarningLights");
    cout<<"Data from  dynamic widgets"<<endl;
    for(auto it=s.begin();it!=s.end();it++){
        cout<<*it<<endl;
    }
    auto it=find(s1.begin(),s1.end(),"WarningLights");
    if(it!=s1.end()){
        cout<<"Warning Lights present in set"<<endl;
    }
    else{
         cout<<"Warning Lights not present in set"<<endl;
    }
    vector<string> combined(size(s)+size(s1));
    copy(s.begin(),s.end(),combined.begin());
    copy(s1.begin(),s1.end(),combined.begin()+size(s));
    cout<<"Widgets after copying from s vector and s1 set"<<endl;
    for(auto d:combined){
        cout<<d<<endl;
    }
    auto it1=find(combined.begin(),combined.end(),"Touchscreen");
    if(it1!=combined.end()){
        cout<<"Touchscreen present in combined vector"<<endl;
    }
    else{
         cout<<"Touchscreen not present in combined vector"<<endl;
    }
}