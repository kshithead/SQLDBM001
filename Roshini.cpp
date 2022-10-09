#include<bits/stdc++.h>
using namespace std;
class database{



};
class Table{
    string name;
    vector<string>name[20];
    unordered_map<string,string>attributes; // name of the feild and type of the feild
    unordered_map<string,vector<string>> table; // attribute name and the data
    //indx = table.find(attribute name) pair.second .push(data);
    public:
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
        while(c != NULL || c != ")")
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

    void createTable(string name_table, string data)
    {
        name = name_table;
        //run tokeniser on data
        data = data.substr(1);
        //attributes = token(data);
        

    }


};

int main()
{
    //create create table_name(attribute type attribute1)

}