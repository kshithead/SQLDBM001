#include<bits/stdc++.h>
using namespace std;
vector<pair<string,string>> token(string data)
    {
        //(attribute attrubute_type,)
        vector<pair<string,string>>res;
        char *c ;
        c = strtok((char *)data.c_str()," ");
        
        int flag =0;
         pair<string,string>p;
          string a(c);
          p.first = a;
        while(c != NULL)
        {
            if(!flag)
            {
                c = strtok(NULL, ",");
                if(c== NULL)
                    break;
                string b(c);
                p.second = b;
                res.push_back(p);
                flag =1;
            }
            else{
                c = strtok(NULL, " ");
                if(c== NULL)
                    break;
                string b(c);
                p.first = b;
                
                flag =0;
            }
            
        }


    return res;

    }

int main()
{
    string str ="chbr frb,febf feubf,burbg urb";
    vector<pair<string,string>> res = token(str);
    for(auto p:res)
    {
        cout<<p.first<<" "<<p.second<<endl;
    }
    
}