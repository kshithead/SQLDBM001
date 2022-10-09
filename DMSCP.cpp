#include <bits/stdc++.h>
#include "dmscp.h"
using namespace std;

class Table{
public:
    string name;
    int attr_count;
    map <string, string> attr_type;
    map<string, vector<string> > attr_value;
    vector<int> selection;

    void showtable()
    {
        cout<<endl<<"Table name: "<<name<<endl<<"Attribute count: "<<attr_count<<endl;
        for(auto x: attr_type)
        {
            cout<<x.first<<" : "<<x.second<<"|  ";
        }
        cout<<endl;
        int s;
        for(auto x: attr_value)
        {
            cout<<x.first<<"\t";
            s = x.second.size();
        }
        for(int i=0;i<s;i++)
        {
            cout<<endl;
            for(auto x: attr_value)
            {
                cout<<x.second[i]<<"\t";
            }

        }
            cout<<endl;
    }

    bool checkcondition(int i, string attr, string operato, string value)
    {
        if(attr_type.find(attr)==attr_type.end())
        {
            cout<<"COMMAND NOT EXECUTED: NO ATTRIBUTE NAMED "<<attr<<" FOUND"<<endl;
            return false;
        }
        else{
                map<string, vector<string> >::iterator x;
                x = attr_value.find(attr);
            if(absolutecompare(attr_type.find(attr)->second,"int"))
            {
                stringstream val2(value),val1(x->second[i]);
                int num2 = 0, num1=0;
                val2 >> num2;
                val1 >> num1;
                if(operato == "=")
                {
                    if(num1 == num2)
                        return true;
                    else return false;
                }
                else if(operato == "!=")
                {
                     if(num1 != num2)
                        return true;
                    else return false;
                }
                else if(operato == ">")
                {
                     if(num1 > num2)
                        return true;
                    else return false;
                }
                else if(operato == "<")
                {
                     if(num1 < num2)
                        return true;
                    else return false;
                }
                else if(operato == ">=")
                {
                     if(num1 >= num2)
                        return true;
                    else return false;
                }
                else if(operato == "<=")
                {
                         if(num1 <= num2)
                        return true;
                    else return false;
                }
            }
            else if(absolutecompare(attr_type.find(attr)->second,"string"))
            {
                if(operato == "=")
                {
                    if(x->second[i] == value)
                        return true;
                    else return false;
                }
            }
            else{
                cout<<"ERROR: Incompatible DATATYPE"<<endl;
            }
        }
    }

    void showselection(vector<string> v)
    {
        if(v[0]=="*")
        {
            int s = selection.size();
        cout<<endl;
        for(map<string, vector<string> >::iterator j = attr_value.begin();j!=attr_value.end();j++)
            {
                cout<<j->first<<"\t";
            }
        for(int i=0;i<s;i++)
        {
            cout<<endl;
            for(map<string, vector<string> >::iterator j = attr_value.begin();j!=attr_value.end();j++)
            {
                cout<<j->second[selection[i]]<<"\t";
            }
        }
        cout<<endl;
        }
        else
        {
            int s = selection.size();
        cout<<endl;
        for(int j=0;j<v.size();j++)
            {
                cout<<v[j]<<"\t";
            }
        for(int i=0;i<s;i++)
        {
            cout<<endl;
            for(int j=0;j<v.size();j++)
            {
                cout<<attr_value.find(v[j])->second[selection[i]]<<"\t";
            }
        }
        cout<<endl;
        }
    }

    void deleterow(int i)
    {
        for(map<string, vector<string> >::iterator itr = attr_value.begin();itr != attr_value.end();itr++)
        {
            cout<<"here";
            itr->second.erase(itr->second.begin()+i);
        }

    }
};

class Database{
unordered_map<string, vector<string> > metadata;
//string meta = "instructions.txt";

string metafile = "meta.txt";
string datafile = "data.txt";

public:
    map<string , Table> database;
    Database(){
        loadData();
    }

    void loadData()
    {
        metadata.clear();
        database.clear();
     ifstream meta(metafile);
     ifstream data(datafile);
     string line;
     while (getline (meta, line)) {
              vector<string> v = tokenizefile(line);
              stringstream num(v[1]);
              int n =0;
              num>>n;
              Table t;
              t.name = v[0];
              t.attr_count = n;
              v.erase(v.begin(),v.begin()+2);
              for(int i=0;i<v.size();i+=2)
              {
                  t.attr_type.insert(pair<string,string>(v[i],v[i+1]));
              }
              for(int i=0;i<n;i++)
              {
                  string line2;
                  getline (data, line2);
                  vector<string> datavalues = tokenizefile(line2);
                  datavalues.erase(datavalues.begin());
                  t.attr_value.insert(pair<string, vector<string> >(v[i*2],datavalues));
                  ///tablecolumns
              }
            database.insert(pair<string, Table>(t.name,t));
            }
        meta.close();
        data.close();

    }

    void showall()
    {
        for(auto x: database)
        {
            x.second.showtable();
        }
    }

    void storeData()
    {
        ofstream meta2;
        meta2.open("meta.txt");
        ofstream data2("data.txt");
        for(auto x: database)
        {
            meta2<<x.first<<" "<<x.second.attr_count<<" ";
            for(auto y: x.second.attr_type)
            {
                meta2<<y.first<<" "<<y.second<<" ";
                data2<<y.first<<" ";
                for(auto z: x.second.attr_value.find(y.first)->second)
                {
                    data2<<z<<" ";
                }
                data2<<endl;
            }
            meta2<<endl;
        }
        meta2.close();
        data2.close();
    }

    void addnew(vector<string> v)
    {

        v.erase(v.begin(),v.begin()+2);
        string name = v[0];
        if(database.find(name) == database.end())
        {
            v.erase(v.begin());
        cout<<name<<endl;
        vector<vector< string > > attr = breakdowntokens(tokenizefile(v[0]));
        /*for(int i=0;i<attr.size();i++)
        {cout<<endl;
            for(int j=0;j<attr[i].size();j++)
                cout<<attr[i][j];
        cout<<"+++++++++++++++++++";
        }
*/
        Table t;
        t.name = name;
        t.attr_count = attr.size();
          for(int i=0;i<attr.size();i++)
          {
              if(attr[i].size()==2)
              {
                  t.attr_type.insert(pair<string,string>(attr[i][0],attr[i][1]));
                  vector<string> temp2;
                  t.attr_value.insert(pair<string,vector<string> >(attr[i][0],temp2));
              }
              else if(attr[i].size()==4)
              {
                  t.attr_type.insert(pair<string,string>(attr[i][0],attr[i][1]));
                  vector<string> temp2;
                  t.attr_value.insert(pair<string,vector<string> >(attr[i][0],temp2));
                  ///creat attributes and bound them with conditions;
              }
              else{
                cout<<"ERROR: INCORRECT INPUT";
                return;
              }
          }
          database.insert(pair<string,Table>(name,t));
        }
        else{
            cout<<"COMMAND NOT EXECUTED: TABLE NAME ALREADY EXIST"<<endl;
        }
        storeData();
        loadData();
    }

    void droptable(string tbl_name)
    {
        if(database.find(tbl_name) != database.end())
        {
            database.erase(tbl_name);
            storeData();
        }
        else{
            cout<<"COMMAND NOT EXECUTED: TABLE NOT FOUND"<<endl;
        }
    }

};


void driver(Database d)
{
    string inst = "Instructions.txt";
    ifstream myfile(inst);
     string line;
    // while (getline (myfile, line)) {
    cout<<"INSTR:: ";
            getline(cin,line);
    while(1){
            if(line=="")
            {
                break;
            }
              vector<string> v = tokenizefile(line);
              /*for(int i=0;i<v.size();i++)
              {
                  ///cout<<v[i]<<"|";
              }
              cout<<endl;*/
              if(absolutecompare(v[0],"CREATE"))
              {
                  /*for(int i=0;i<v.size();i++)
                  {

                      cout<<endl<<v[i]<<"++";
                  }*/
                  cout<<"FOUND CREATE-------------\n";
                  d.addnew(v);

              }
              else if(absolutecompare(v[0],"DROP"))
              {
                  cout<<"FOUND DROP-------------";
                  d.droptable(v[2]);
              }
              else if(absolutecompare(v[0],"SHOWALL"))
              {
                  cout<<"FOUND SHOWALL-------------";
                  d.showall();
              }
              else if(absolutecompare(v[0],"SELECT"))
              {
                  v = cleantokens(v);
                  cout<<"FOUND SELECT-------------";
                  v.erase(v.begin());
                  vector<string> toshow;
                  while(!absolutecompare(v[0],"FROM")){
                    if(v[0]!=",")
                        toshow.push_back(v[0]);
                    v.erase(v.begin());
                  }
                  /*cout<<"&&&&&&&&&&&&&&&&&&&&&&&"<<endl;
                  for(int i=0;i<toshow.size();i++)
                  {
                      cout<<toshow[i]<<"|";
                  }
                  cout<<endl<<"&&&&&&&&&&&&&&&&&&&&&&&";*/
                  v.erase(v.begin());
                  string name = v[0];
                  v.erase(v.begin());


                  if(absolutecompare(v[0],"WHERE"))
                  {
                    v.erase(v.begin());
                    if(d.database.find(name)==d.database.end())
                    {
                        cout<<"ERROR: NO TABLE NAMED "<<name<<" FOUND"<<endl;
                    }
                    else{
                        d.database.find(name)->second.selection.clear();
                    int len = d.database.find(name)->second.attr_value.find(v[0])->second.size();
                    for(int i=0;i<len;i++)
                    {
                        if(d.database.find(name)->second.checkcondition(i,v[0],v[1],v[2]))
                        {
                            d.database.find(name)->second.selection.push_back(i);
                        }
                    }
                    d.database.find(name)->second.showselection(toshow);
                    }

                  }
                  else{
                    if(d.database.find(name)==d.database.end())
                    {
                        cout<<"ERROR: NO TABLE NAMED "<<name<<" FOUND"<<endl;

                    }
                    else{
                        auto x = d.database.find(name)->second;
                        x.selection.clear();
                        int len = x.attr_value.begin()->second.size();

                        for(int i=0;i<len;i++)
                        {
                            x.selection.push_back(i);
                        }
                        x.showselection(toshow);

                    }

                  }
                }

              else if(absolutecompare(v[0],"INSERT"))
              {
                  cout<<"FOUND INSERT-------------\n";
                  ///Insert into Tbl1 values ("FORUPDATE", 29, "NOTYETUPDATED");

                v.erase(v.begin(),v.begin()+2);
                string name = v[0];
                v.erase(v.begin());
                vector<string> attr_names = seperatetokens(tokenizefile(v[0]));
                v.erase(v.begin());
                if(!absolutecompare(v[0],"values"))
                {
                        //cout<<"ERROR4: INCORRECT STATEMENT"<<endl;
                        vector<string> vals = seperatetokens(tokenizefile(v[0]));
                        if(d.database.find(name)==d.database.end())
                    {
                        cout<<"COMMAND NOT EXECUTED: no table named "<<name<<" found"<<endl;
                        return;
                    }
                    map<string, Table>::iterator x = d.database.find(name);
                    //--------
                    cout<< vals.size()<<"-----------------"<<x->second.attr_value.size()<<endl;
                    if(vals.size() == x->second.attr_value.size())
                    {
                        int j=0;
                        for(auto i = x->second.attr_value.begin(); i!=x->second.attr_value.end();i++)
                        {
                            i->second.push_back(vals[j]);
                            j+=1;
                        }
                    }
                    else{
                        cout<<"ERROR: Not Enough Entries"<<endl;
                        return;
                    }

                    //--------

                }
                else{
                    v.erase(v.begin());

                vector<string> vals = seperatetokens(tokenizefile(v[0]));
                if(d.database.find(name)==d.database.end())
                {
                    cout<<"COMMAND NOT EXECUTED: no table named "<<name<<" found"<<endl;
                    return;
                }
                map<string, Table>::iterator x = d.database.find(name);
                for(int i=0;i<attr_names.size();i++)
                {
                    if(x->second.attr_value.find(attr_names[i]) == x->second.attr_value.end())
                    {
                        cout<<"COMMAND NOT EXECUTED: No Attribute named "<<attr_names[i]<<" is present in table "<<name<<endl;
                        return;
                    }
                }
                if(attr_names.size() == x->second.attr_value.size())
                {
                    for(int i=0;i<attr_names.size();i++)
                    {
                        x->second.attr_value.find(attr_names[i])->second.push_back(vals[i]);
                    }
                }
                else{
                    cout<<"ERROR: NO NULL ENTRY PERMITTED"<<endl;
                    return;
                }
                }


               }
              else if(absolutecompare(v[0],"DELETE"))
              {
                  v = cleantokens(v);
                  cout<<"FOUND DELETE-------------";
                  ///DELETE FROM table_name WHERE condition;
                  if(!absolutecompare(v[1],"FROM") || !absolutecompare(v[3],"Where"))
                  {
                      cout<<"ERROR: Incorrect instruction format"<<endl;
                      return;
                  }
                  if(d.database.find(v[2])==d.database.end())
                  {
                      cout<<"No Table FOUND"<<endl;
                  }
                  string name = v[2];
                  v.erase(v.begin(),v.begin()+4);
                  int len = d.database.find(name)->second.attr_value.begin()->second.size();
                  for(int i=len-1;i>=0;i--)
                  {
                      cout<<"Here"<<endl;
                      cout<<v[0]<<"|"<<v[1]<<"|"<<v[2]<<endl;
                      if(d.database.find(name)->second.checkcondition(i,v[0],v[1],v[2]))
                        cout<<"TRUE"<<endl;
                      if(d.database.find(name)->second.checkcondition(i,v[0],v[1],v[2]))
                      {
                          /*for(map<string,vector<string> >::iterator x = d.database.find(name)->second.attr_value.begin(); x!=d.database.find(name)->second.attr_value.end();x++)
                          {
                              x->second.erase(x->second.begin()+i);
                          }*/
                          d.database.find(name)->second.deleterow(i);///-----------------------------------------------------------------------------------------------------
                      }
                  }

              }
              else if(absolutecompare(v[0],"UPDATE"))
              {
                  cout<<"FOUND UPDATE-------------";
                  v=seperatetokens(v);
                  string name = v[1];
                  if(absolutecompare(v[2],"SET"))
                  {
                      v.erase(v.begin(),v.begin()+3);
                      vector<string> col;
                      vector<string> val;
                      bool flag = true;
                      cout<<v[0]<<";;"<<endl;
                      while(!absolutecompare(v[0],"WHERE") && v.size()!=0)
                      {
                          if(v[1]!="=")
                          {
                              cout<<"Incorrect Format 2"<<endl;
                              flag = false;
                              break;
                          }
                          else{
                            if(d.database.find(name)->second.attr_value.find(v[0])!=d.database.find(name)->second.attr_value.end())
                            {
                                col.push_back(v[0]);
                                val.push_back(v[2]);
                                v.erase(v.begin(),v.begin()+3);
                            }
                            else{
                                cout<<"ERROR: No Attribute "<<v[0]<<" found"<<endl;
                                flag = false;
                                break;
                            }
                          }
                      }
                      if(flag)
                      {
                          v.erase(v.begin());
                          int len = d.database.find(name)->second.attr_value.begin()->second.size();
                            for(int i=0;i<len;i++)
                            {
                                if(d.database.find(name)->second.checkcondition(i,v[0],v[1],v[2]))
                                {
                                    for(int j=0;j<col.size();j++)
                                    {
                                        d.database.find(name)->second.attr_value.find(col[j])->second[i] = val[j];
                                    }
                                }
                            }
                    }

                  }
                  else{
                    cout<<"Incorrect Format"<<endl;
                  }
                  for(int i=0;i<v.size();i++)
                  {
                      cout<<endl<<v[i];
                  }

              }

              else if(absolutecompare(v[0],"COMMIT"))
              {
                  cout<<"Commiting data-------------";

                  d.storeData();
              }
              else if(absolutecompare(v[0],"QUIT"))
              {
                  cout<<"FOUND QUIT-------------";
                  d.storeData();
                  d.showall();
                  cout<<"\nDONE";
                  //myfile.close();
                  return;

              }
              cout<<endl;
              cout<<"INSTR:: ";
            getline(cin,line);

            }
           // myfile.close();
}


int main()
{
    Database d;
    cout<<endl<<"//////////////////////////////////////////////////////////// "<<endl;
    driver(d);
    cout<<endl<<"\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\ "<<endl;



    return 0;
}
