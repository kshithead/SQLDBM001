

std::string stripstring(std::string s)
{
    std::string ret="";
    bool quotation = false;
    for(int i=0;i<s.length();i++)
    {
        if(quotation)
        {
            if(s[i]=='"')
                quotation= !quotation;
            else ret+=s[i];
        }
        else{
            if(s[i]=='"')
                quotation = !quotation;
            else ret+=s[i];
        }

    }
    return ret;
}


std::string stripspace(std::string s)
{
    while(s[s.length()-1]==' ')
    {
        s.erase(s.length()-1,1);
    }
    while(s[0]==' ')
    {
        s.erase(0,1);
    }
    return s;
}

std::vector<std::string > cleantokens(std::vector<std::string > v)  ///removes extra space eating tokens like null tokens and ';' tokens
{
    for(int i=v.size()-1;i>=0;i--)
    {
        if(v[i]==" "||v[i]==""||v[i]==";"||v[i]==" ;")
            v.erase(v.begin()+i);
        else{
            v[i] = stripstring(stripspace(v[i]));
        }
    }
    return v;
}

std::vector<std::string > seperatetokens(std::vector<std::string > v)  ///removes extra space eating tokens like null tokens and ';' tokens
{
    for(int i=v.size()-1;i>=0;i--)
    {
        if(v[i]==" "||v[i]==""||v[i]==";"||v[i]==" ;"||v[i]==",")
            v.erase(v.begin()+i);
        else{
            v[i] = stripstring(stripspace(v[i]));
        }
    }
    return v;
}

std::string rearrangeline(std::string s)
{
    //#include<regex>
    //regex a("[0-9a-zA-Z()_]*[;(),;][0-9a-zA-Z()_]*")
    //regex_replace(back_inserter(s), s.begin(), s.end(),
	//			r, "geek");
	//std::regex a("[0-9a-zA-Z_(]");
	//std::regex b("[(),;a-zA-Z_]");
	std::set<char> a= {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s',
	't','u','v','w','x','y','z','A','B','C','D','E','F','G','H','I','J','K','L','M',
	'N','O','P','Q','R','S','T','U','V','W','X','Y','Z','0','1','2','3','4','5','6','7','8','9','_'};
	std::set<char> b= {',',';','(',')','=','!','>','<','"'};
	std::set<char> c= {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s',
	't','u','v','w','x','y','z','A','B','C','D','E','F','G','H','I','J','K','L','M',
	'N','O','P','Q','R','S','T','U','V','W','X','Y','Z','_',',',';',')','0','1','2','3','4','5','6','7','8','9','"'};


	for(int i=s.length()-2;i>=0;i--)
    {
        if((a.find(s[i])!=a.end() && b.find(s[i+1])!=b.end()) || (b.find(s[i])!=b.end() && c.find(s[i+1])!=c.end()))
        {
            s.insert(i+1," ");
        }
    }
    return s;

}

std::vector<std::string > tokenizefile(std::string line)  ///breaks line into tokens
{
    line = rearrangeline(line);
    std::string token ="";
    std::vector<std::string > ret;
    std::stack<char> parenthesis;

    ///std::cout<<line<<std::endl;

    for(int i=0;i<line.length();i++)
    {
        if(parenthesis.size()==0)
        {
            if(line[i]=='(')
            {
                parenthesis.push('(');
                ret.push_back(token);
                token.clear();
            }
            else if(line[i] == ' ')
            {
                ret.push_back(token);
                token.clear();
            }
            else{
                token+=line[i];
            }
        }
        else{
            if(line[i]==')')
            {
                if(parenthesis.size() == 1)
                {
                    parenthesis.pop();
                    ret.push_back(token);
                    token.clear();
                }
                else{
                    parenthesis.pop();
                    token+=')';
                }
            }
            else if(line[i] == ' ')
            {
                token+=line[i];
            }
            else if(line[i] == '(')
            {
                parenthesis.push('(');
                token+=line[i];
            }
            else{
                token+=line[i];
            }
        }
    }
    if(token.length()!=0)
        ret.push_back(token);

    return cleantokens(ret);

}

bool absolutecompare(std::string s1, std::string s2)
{
    std::transform(s1.begin(), s1.end(), s1.begin(), ::tolower);
    std::transform(s2.begin(), s2.end(), s2.begin(), ::tolower);
    return s1==s2;
}

std::vector<std::vector<std::string> > breakdowntokens(std::vector<std::string> v)
{
    std::vector<std::vector<std::string> > ret;
    std::vector<std::string> temp;
    for(int i=0;i<v.size();i++)
    {
        if(v[i] == ",")
        {
            ret.push_back(temp);
            temp.clear();
        }
        else temp.push_back(v[i]);
    }
    ret.push_back(temp);
    temp.clear();
    return ret;
}
