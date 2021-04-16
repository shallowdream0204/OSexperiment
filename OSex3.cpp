#include<iostream>
#include<vector>
using namespace std;
void OPTalgorithm(vector<int>&v1,int number)
{
    int pagefaults=0;
    vector< pair<int,int> >v2;
    vector<int>::iterator it1;
    vector< pair<int,int> >::iterator it2;
    while(!v1.empty())
    {
        it1=v1.begin();
        if(v2.size()<number)
        {
            for(it2=v2.begin();it2!=v2.end();it2++)
            {
                if(it2->first==*it1)
                break;
            }
            if(it2!=v2.end())
            {
                for(it2=v2.begin();it2!=v2.end();it2++)
                {
                    ++it2->second;
                    cout<<it2->first<<',';
                }
                for(int i=0;i<number-v2.size();++i)
                {
                    cout<<"-,";
                }
                if(v1.size()==1)
                cout<<'1'<<endl;
                else
                cout<<"1/";
                v1.erase(it1);
            }
            else
            {
                for(it2=v2.begin();it2!=v2.end();it2++)
                {
                    ++it2->second;
                    cout<<it2->first<<',';
                }
                v2.push_back(pair<int,int>(*it1,0));
                cout<<*it1<<',';
                for(int i=0;i<number-v2.size();++i)
                {
                    cout<<"-,";
                }
                if(v1.size()==1)
                cout<<'0'<<endl;
                else
                cout<<"0/";
                ++pagefaults;
                v1.erase(it1);
            }
        }
        else
        {
            for(it2=v2.begin();it2!=v2.end();it2++)
            {
                if(it2->first==*it1)
                break;
            }
            if(it2!=v2.end())
            {
                for(it2=v2.begin();it2!=v2.end();it2++)
                {
                    ++it2->second;
                    cout<<it2->first<<',';
                }
                if(v1.size()==1)
                cout<<'1'<<endl;
                else
                cout<<"1/";
                v1.erase(it1);
            }
            else
            {
                for(it2=v2.begin();it2!=v2.end();it2++)
                {
                    ++it2->second;
                }
                vector<int>v3(number,0);
                for(int i=0;i<number;++i)
                {
                    for(it1=v1.begin();it1!=v1.end();it1++)
                    {
                        if(*it1==v2[i].first)
                        break;
                        ++v3[i];
                    }   
                }
                int j=0;
                for(int i=0;i<number;++i)
                {
                    if(v3[i]>v3[j])
                    j=i;
                }
                vector<int>v4;
                for(int i=0;i<number;++i)
                {
                    if(v3[i]==v3[j])
                    v4.push_back(i);
                }
                int max=v4[0];
                for(int i=0;i<v4.size();++i)
                {
                    if(v2[v4[i]].second>v2[max].second)
                    max =i;
                }
                it1=v1.begin();
                v2[max].first=*it1;
                v2[max].second=0;
                for(it2=v2.begin();it2!=v2.end();it2++)
                {
                    cout<<it2->first<<',';
                }
                if(v1.size()==1)
                cout<<'0'<<endl;
                else
                cout<<"0/";
                ++pagefaults;
                v1.erase(it1);
            }
        }
    }
    cout<<pagefaults<<endl;
}
void FIFOalgorithm(vector<int>&v1,int number)
{
    int pagefaults=0;
    vector< pair<int,int> >v2;
    vector<int>::iterator it1;
    vector< pair<int,int> >::iterator it2;
    while(!v1.empty())
    {
        it1=v1.begin();
        if(v2.size()<number)
        {
            for(it2=v2.begin();it2!=v2.end();it2++)
            {
                if(it2->first==*it1)
                break;
            }
            if(it2!=v2.end())
            {
                for(it2=v2.begin();it2!=v2.end();it2++)
                {
                    ++it2->second;
                    cout<<it2->first<<',';
                }
                for(int i=0;i<number-v2.size();++i)
                {
                    cout<<"-,";
                }     
                if(v1.size()==1)
                cout<<'1'<<endl;
                else
                cout<<"1/";
                v1.erase(it1);
            }
            else
            {
                for(it2=v2.begin();it2!=v2.end();it2++)
                {
                    ++it2->second;
                    cout<<it2->first<<',';
                }
                v2.push_back(pair<int,int>(*it1,0));
                cout<<*it1<<',';
                for(int i=0;i<number-v2.size();++i)
                    cout<<"-,";
                if(v1.size()==1)
                cout<<'0'<<endl;
                else
                cout<<"0/";
                ++pagefaults;
                v1.erase(it1);
            }
        }
        else
        {
            for(it2=v2.begin();it2!=v2.end();it2++)
            {
                if(it2->first==*it1)
                break;
            }
            if(it2!=v2.end())
            {
                for(it2=v2.begin();it2!=v2.end();it2++)
                {
                    ++it2->second;
                    cout<<it2->first<<',';
                }
                if(v1.size()==1)
                cout<<'1'<<endl;
                else
                cout<<"1/";
                v1.erase(it1);
            }
            else
            {
                vector< pair<int,int> >::iterator it3=v2.begin();
                for(it2=v2.begin();it2!=v2.end();it2++)
                {
                    ++it2->second;
                }
                for(it2=v2.begin();it2!=v2.end();it2++)
                {
                    if(it2->second>it3->second)
                    it3=it2;
                }
                it3->first=*it1;
                it3->second=0;
                for(it2=v2.begin();it2!=v2.end();it2++)
                {
                    cout<<it2->first<<',';
                }
                if(v1.size()==1)
                cout<<'0'<<endl;
                else
                cout<<"0/";
                v1.erase(it1);
                ++pagefaults;
            }
        }
    }
    cout<<pagefaults<<endl;
}
void LRUalgorithm(vector<int>&v1,int number)
{
    int pagefaults=0;
    vector< pair<int,int> >v2;
    vector<int>::iterator it1;
    vector< pair<int,int> >::iterator it2,it3;
    while(!v1.empty())
    {
        it1=v1.begin();
        if(v2.size()<number)
        {
            for(it2=v2.begin();it2!=v2.end();it2++)
            {
                if(it2->first==*it1)
                break;
            }
            if(it2!=v2.end())
            {
                it3=it2;
                for(it2=v2.begin();it2!=v2.end();it2++)
                {
                    ++it2->second;
                    cout<<it2->first<<',';
                }
                it3->second=0;
                for(int i=0;i<number-v2.size();++i)
                {
                    cout<<"-,";
                }     
                if(v1.size()==1)
                cout<<'1'<<endl;
                else
                cout<<"1/";
                v1.erase(it1);
            }
            else
            {
                for(it2=v2.begin();it2!=v2.end();it2++)
                {
                    ++it2->second;
                    cout<<it2->first<<',';
                }
                v2.push_back(pair<int,int>(*it1,0));
                cout<<*it1<<',';
                for(int i=0;i<number-v2.size();++i)
                    cout<<"-,";
                if(v1.size()==1)
                cout<<'0'<<endl;
                else
                cout<<"0/";
                ++pagefaults;
                v1.erase(it1);
            }
        }
        else
        {
            for(it2=v2.begin();it2!=v2.end();it2++)
            {
                if(it2->first==*it1)
                break;
            }
            if(it2!=v2.end())
            {
                it3=it2;
                for(it2=v2.begin();it2!=v2.end();it2++)
                {
                    ++it2->second;
                    cout<<it2->first<<',';
                }
                it3->second=0;
                if(v1.size()==1)
                cout<<'1'<<endl;
                else
                cout<<"1/";
                v1.erase(it1);
            }
            else
            {
                it3=v2.begin();
                for(it2=v2.begin();it2!=v2.end();it2++)
                {
                    ++it2->second;
                }
                for(it2=v2.begin();it2!=v2.end();it2++)
                {
                    if(it2->second>it3->second)
                    it3=it2;
                }
                it3->first=*it1;
                it3->second=0;
                for(it2=v2.begin();it2!=v2.end();it2++)
                {
                    cout<<it2->first<<',';
                }
                if(v1.size()==1)
                cout<<'0'<<endl;
                else
                cout<<"0/";
                v1.erase(it1);
                ++pagefaults;
            }
        }
    }
    cout<<pagefaults<<endl;
}
int main()
{
    int algorithm;
    int number;
    cin>>algorithm>>number;
    vector<int> v1;
    char a;
    int b;
    while(1)
    {
        cin>>b;
        a=cin.get();
        v1.push_back(b);
        if(a=='\n')
        break;
    }
    switch(algorithm)
    {
        case(1):{
            OPTalgorithm(v1,number);
            break;
        }
        case(2):{
            FIFOalgorithm(v1,number);
            break;
        }
        case(3):
        {
            LRUalgorithm(v1,number);
            break;
        }
        default:{
            break;
        }
    }
    return 0;
}