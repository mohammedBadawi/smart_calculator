#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <cctype>
#include <cstdlib>
#include <sstream>
#include<math.h>
#include<conio.h>
#include<iomanip>

using namespace std;
void get_operators_indexes (string ,vector<int>&);
void get_substrings(string,vector<int>&,vector <string>&);
int int_contains_letters (string);
bool bool_contains_letters (string);
void divide_equation_into_map(vector <string>&,map<std::string,float>&,vector<map<std::string,float> >&);
int get_equaloperator_index (string);
int num_vars(vector<map<std::string,float> >&);
void equation_i(vector<map<std::string,float> >&,int);
void coloumn_var(vector<map<std::string,float> >&,string);
void add_eqn (vector<map<std::string,float> >&,int,int);
void subtract_eqn (vector<map<std::string,float> >&,int,int);
void substitute(vector<map<std::string,float> >&,string ,int ,int );
vector<vector<float> > D(vector<map<std::string,float> >&vector_of_maps,float[][100]);
vector<vector<float> > D_variable(vector<map<std::string,float> >&,string,float[][100]);
double determ(float[100][100],int n);
void get_user_inputs(string&,vector<map<std::string,float> >&,float[][100],float[][100]);
void print_eqn(map<std::string,float>);
// main function********************************************
int main()
{
vector<map<std::string,float> >vector_of_maps;
string equation;
int n;
string num ;
getline(cin,num);
n=atoi(num.c_str());
for(int i=1;i<=n;i++){
vector <int> operators_indexes;
vector <string> sub_strings;
map<std::string,float>equation_map;
    getline(cin,equation);
    get_operators_indexes(equation,operators_indexes);
    get_substrings(equation,operators_indexes,sub_strings);
    divide_equation_into_map(sub_strings,equation_map,vector_of_maps);}
    float arr[100][100];float arr_variable[100][100];
    string input;
    getline(cin,input);
    while(input!="quit"){
    get_user_inputs(input,vector_of_maps,arr,arr_variable);
    getline(cin,input);}
    return 0;
}
// a fun to get operators indexes
    void get_operators_indexes (string user_equation,vector<int>&indexes){
        indexes.push_back(0);
    for(int i=1;i<user_equation.length();i++){
        if(user_equation[i]=='+'||user_equation[i]=='-'||user_equation[i]=='='){
            indexes.push_back(i);
            }}

            indexes.push_back(user_equation.length());
            }
    void get_substrings(string user_equation,vector<int>&indexes,vector <string>&sub_strings){
    for(int i=0;i<(indexes.size()-1);i++){
          if(indexes[i]>get_equaloperator_index(user_equation)){
                sub_strings.push_back('='+user_equation.substr(indexes[i],indexes[i+1]-indexes[i]));
                                                                    }
                else {
                sub_strings.push_back(user_equation.substr(indexes[i],indexes[i+1]-indexes[i]));}}

             for(int i=0;i<sub_strings.size();i++){
                if(sub_strings[i]=="="){sub_strings.erase(sub_strings.begin()+i);break;}
             }

            }
    void divide_equation_into_map(vector <string>&sub_strings,map<std::string,float>&equation_map,vector<map<std::string,float> >&vector_of_maps){
     string key; float value=1;
     for (int i=0;i<sub_strings.size();i++){
            string my_sub_string=sub_strings[i];
        if(bool_contains_letters(my_sub_string)){
                //the sub string contains letter
                if(my_sub_string[0]=='='){

                if(my_sub_string[1]=='+'&&isalpha(my_sub_string[2])){value=-1;key=my_sub_string.substr(2);}//======>EX:+X
                if(my_sub_string[1]=='+'&&!isalpha(my_sub_string[2])){value=-1*(atof((my_sub_string.substr(2,int_contains_letters(my_sub_string)-2)).c_str()));key=my_sub_string.substr(int_contains_letters(my_sub_string));}//====>EX:+25X
                if(my_sub_string[1]=='-'&&isalpha(my_sub_string[2])){value=1;key=my_sub_string.substr(2);}//==>EX:-X
                if(my_sub_string[1]=='-'&&!isalpha(my_sub_string[2])){value=(atof((my_sub_string.substr(2,int_contains_letters(my_sub_string)-2)).c_str()));key=my_sub_string.substr(int_contains_letters(my_sub_string));}//====>EX:-25X
                if(isalpha(my_sub_string[1])){value=-1;key=my_sub_string.substr(1);}
                if(isdigit(my_sub_string[1])){value=-1*(atof((my_sub_string.substr(1,int_contains_letters(my_sub_string)-1)).c_str()));key=my_sub_string.substr(int_contains_letters(my_sub_string));}


                }
                else{

                if(my_sub_string[0]=='+'&&isalpha(my_sub_string[1])){value=1;key=my_sub_string.substr(1);}
                if(my_sub_string[0]=='+'&&!isalpha(my_sub_string[1])){value=atof((my_sub_string.substr(1,int_contains_letters(my_sub_string)-1)).c_str());key=my_sub_string.substr(int_contains_letters(my_sub_string));}//====>EX:+25X
                if(my_sub_string[0]=='-'&&isalpha(my_sub_string[1])){value=-1;key=my_sub_string.substr(1);}//==>EX:-X
                if(my_sub_string[0]=='-'&&!isalpha(my_sub_string[1])){value=-1*(atof((my_sub_string.substr(1,int_contains_letters(my_sub_string)-1)).c_str()));key=my_sub_string.substr(int_contains_letters(my_sub_string));}//====>EX:-25X
                if(isalpha(my_sub_string[0])){value=1;key=my_sub_string;}
                if(isdigit(my_sub_string[0])){value=atof((my_sub_string.substr(0,int_contains_letters(my_sub_string))).c_str());key=my_sub_string.substr(int_contains_letters(my_sub_string));}
                }
                }


        else//the sub string does not contain any letter
        {

            if(my_sub_string[0]=='=')
                {
                if(my_sub_string[1]=='+'){value=1*(atof((my_sub_string.substr(2)).c_str()));key="";}
                if(my_sub_string[1]=='-'){value=-1*(atof((my_sub_string.substr(2)).c_str()));key="";}
                if(isdigit(my_sub_string[1])){value=1*(atof((my_sub_string.substr(1)).c_str()));key="";}
                }
            else
                {
                if(my_sub_string[0]=='+'){value=-1*(atof((my_sub_string.substr(1)).c_str()));key="";}
                if(my_sub_string[0]=='-'){value=atof((my_sub_string.substr(1)).c_str());key="";}
                if(isdigit(my_sub_string[0])){value=-1*(atof((my_sub_string.substr(0)).c_str()));key="";}
                }

        }

            if(equation_map.count(key)){
               equation_map[key]+=value;
            }

            else{equation_map.insert(std::pair<std::string,float>(key,value));}
            }
             vector_of_maps.push_back(equation_map);

    }
    int int_contains_letters (string mystring){
    for(int z=0;z<mystring.length();z++){
        if(isalpha(mystring[z])){return z;}
    }
    return 0;
    }
    bool bool_contains_letters (string mystring){
    for(int z=0;z<mystring.length();z++){
        if(isalpha(mystring[z])){return true;}
    }
    return false;
    }
    int get_equaloperator_index (string equation){
    for(int i=0;i<equation.length();i++){
        if(equation[i]=='='){
            return i;
        }
    }
    return 0;
     }
    int num_vars (vector<map<std::string,float> >&vector_of_maps){
    map<std::string,float>variables;int counter=0;
    for(int i=0;i<vector_of_maps.size();i++){
    for(std::map<std::string,float>::iterator it=vector_of_maps[i].begin();it!=vector_of_maps[i].end();it++){
           variables[it->first]=0;}}
    for(std::map<std::string,float>::iterator it=variables.begin();it!=variables.end();it++){
        if(it->first!="")counter++;
     }
     return counter;
    }
    void equation_i(vector<map<std::string,float> >&vector_of_maps,int i){
    print_eqn(vector_of_maps[i-1]);
    }
    void coloumn_var(vector<map<std::string,float> >&vector_of_maps,string var_name){
    vector<float>coloumn;
    for(int i=0;i<vector_of_maps.size();i++){
     std::map<std::string,float>::iterator it=vector_of_maps[i].find(var_name);
        if(it!=vector_of_maps[i].end()){coloumn.push_back(it->second);}
        else coloumn.push_back(0);
    }
    for(int i=0;i<coloumn.size();i++) cout<<coloumn[i]<<endl;
    }
    void add_eqn (vector<map<std::string,float> >&vector_of_maps,int eqn1_nom,int eqn2_nom){
    map<std::string,float>sum;
    for(std::map<std::string,float>::iterator it=vector_of_maps[eqn1_nom-1].begin();it!=vector_of_maps[eqn1_nom-1].end();it++){
     sum[it->first]=it->second + vector_of_maps[eqn2_nom-1][it->first];}
    for(std::map<std::string,float>::iterator it=vector_of_maps[eqn2_nom-1].begin();it!=vector_of_maps[eqn2_nom-1].end();it++){
     sum[it->first]=it->second + vector_of_maps[eqn1_nom-1][it->first];}
    print_eqn(sum);}
    void print_eqn(map<std::string,float>eqn){
    int counter=0;int flag=0;string equation="";
    for(std::map<std::string,float>::iterator it=eqn.begin();it!=eqn.end();it++){
    string str;ostringstream ss;ss<<it->second;str=ss.str();
    if(it->second==0){counter++;continue;}
    else if(counter==0&&it->first==""){flag=1;counter++;continue;}
    else if(counter==0){if(it->second==1){equation+=it->first;}
                        else if(it->second==-1){equation+='-'+it->first;}
                        else equation+=str+it->first;}
    else if(counter==1&&flag==1){
            if(it->second==1){equation+=it->first;}
            else if(it->second==-1){equation+='-'+it->first;}
            else equation+=str+it->first;}
    else{
        if(it->second==1){equation+='+'+it->first;}
        else if(it->second==-1){equation+='-'+it->first;}
        else if(it->second<0){equation+=str+it->first;}
        else if(it->second>0){equation+='+'+str+it->first;}}
        counter++;}
    if(equation[0]=='+')equation.erase(0,1);
    cout<<equation<<'='<<eqn[""]<<endl;
    }
    void subtract_eqn (vector<map<std::string,float> >&vector_of_maps,int eqn1_nom,int eqn2_nom){
    map<std::string,float>sum;
    for(std::map<std::string,float>::iterator it=vector_of_maps[eqn1_nom-1].begin();it!=vector_of_maps[eqn1_nom-1].end();it++){
     sum[it->first]=it->second - vector_of_maps[eqn2_nom-1][it->first];}
    for(std::map<std::string,float>::iterator it=vector_of_maps[eqn2_nom-1].begin();it!=vector_of_maps[eqn2_nom-1].end();it++){
     sum[it->first]=-1*(it->second - vector_of_maps[eqn1_nom-1][it->first]);}
    print_eqn(sum);}
    void substitute(vector<map<std::string,float> >&vector_of_maps,string variable,int eqn_1,int eqn_2){
  map<std::string,float>mytemp,eqn1_without_variable,sum;
  for(std::map<std::string,float>::iterator it=vector_of_maps[eqn_2-1].begin();it!=vector_of_maps[eqn_2-1].end();it++){
    if(it->first=="")mytemp[it->first]=vector_of_maps[eqn_2-1][it->first]/vector_of_maps[eqn_2-1][variable];
    if(it->first!=variable)mytemp[it->first]=-1*(vector_of_maps[eqn_2-1][it->first]/vector_of_maps[eqn_2-1][variable]);
    if(it->first==variable){}}
    for(std::map<std::string,float>::iterator it=vector_of_maps[eqn_1-1].begin();it!=vector_of_maps[eqn_1-1].end();it++){
        if(it->first!=variable)eqn1_without_variable[it->first]=vector_of_maps[eqn_1-1][it->first];
    }
    for(std::map<std::string,float>::iterator it=mytemp.begin();it!=mytemp.end();it++){
    sum[it->first]=(mytemp[it->first]*vector_of_maps[eqn_1-1][variable])+eqn1_without_variable[it->first];
    }

    print_eqn(sum);
        }
    vector<vector<float> > D(vector<map<std::string,float> >&vector_of_maps,float arr[][100]){
        map<std::string,float>variables;vector<vector<float> >Det;
    for(int i=0;i<vector_of_maps.size();i++){
    for(std::map<std::string,float>::iterator it=vector_of_maps[i].begin();it!=vector_of_maps[i].end();it++){
           variables[it->first]=0;}}
    for(int i=0;i<vector_of_maps.size();i++){
            vector<float>mytemp;
        for(std::map<std::string,float>::iterator it=variables.begin();it!=variables.end();it++){
           if(it->first==""){}
           else mytemp.push_back(vector_of_maps[i][it->first]);}
         Det.push_back(mytemp);}
         for(int i=0;i<Det.size();i++){
            for(int j=0;j<Det.size();j++){
                arr[i][j]=Det[i][j];}}
         return Det;}
    vector<vector<float> > D_variable(vector<map<std::string,float> >&vector_of_maps,string variable,float arr_variable[][100]){
        map<std::string,float>variables;vector<vector<float> >Det;
    for(int i=0;i<vector_of_maps.size();i++){
    for(std::map<std::string,float>::iterator it=vector_of_maps[i].begin();it!=vector_of_maps[i].end();it++){
           variables[it->first]=0;}}
    for(int i=0;i<vector_of_maps.size();i++){
            vector<float>mytemp;
        for(std::map<std::string,float>::iterator it=variables.begin();it!=variables.end();it++){
           if(it->first==""){}
           else if(it->first==variable)mytemp.push_back(vector_of_maps[i][""]);
           else mytemp.push_back(vector_of_maps[i][it->first]);}
         Det.push_back(mytemp);}
         for(int i=0;i<Det.size();i++){
            for(int j=0;j<Det.size();j++){
                arr_variable[i][j]=Det[i][j];}}
          return Det;}
    double determ(float a[100][100],int n) {
  double det=0;int p, h, k, i, j;float temp[100][100];
  if(n==1) {
    return a[0][0];
  } else if(n==2) {
    det=(a[0][0]*a[1][1]-a[0][1]*a[1][0]);
    return det;
  } else {
    for(p=0;p<n;p++) {
      h = 0;
      k = 0;
      for(i=1;i<n;i++) {
        for( j=0;j<n;j++) {
          if(j==p) {
            continue;
          }
          temp[h][k] = a[i][j];
          k++;
          if(k==n-1) {
            h++;
            k = 0;
          }
        }
      }
      det=det+a[0][p]*pow(-1,p)*determ(temp,n-1);
    }
    return det;}}

    void get_user_inputs(string& input,vector<map<std::string,float> >&vector_of_maps,float arr[][100],float arr_variable[][100]){
         //first requirement
     if(input=="num_vars"){cout<<num_vars(vector_of_maps)<<endl;}
        //second requirement
     else if(input[0]=='e'&&input[1]=='q'){
     string s_n=input.substr(9,input.length()-9);
     int n=atof(s_n.c_str());
     equation_i(vector_of_maps,n);
     }
       //third requirement
     else if(input[0]=='c'&&input[1]=='o'){
        string name=input.substr(7);
        coloumn_var(vector_of_maps,name);
     }
     //fourth requirement
     else if(input[0]=='a'&&input[1]=='d'){
        int length=1;string eqn1,eqn2;int n1,n2;
        while(isdigit(input[4+length])){length++;}
        eqn1=input.substr(4,length);
        eqn2=input.substr(4+eqn1.length());
        n1=atof(eqn1.c_str());n2=atof(eqn2.c_str());
        add_eqn(vector_of_maps,n1,n2);}
      //fifth requirement
    else if(input[0]=='s'&&input[1]=='u'&&input[3]=='t'){
        int length=1;string eqn1,eqn2;int n1,n2;
        while(isdigit(input[9+length])){length++;}
        eqn1=input.substr(9,length);
        eqn2=input.substr(9+eqn1.length());
        n1=atof(eqn1.c_str());n2=atof(eqn2.c_str());
        subtract_eqn(vector_of_maps,n1,n2);}
      //sixth requirement
     else if(input[0]=='s'&&input[1]=='u'&&input[3]=='s'){
        int length=1;string eqn1,eqn2;int n1,n2;string var_name;
        while(input[11+length]!=' '){length++;}
        var_name=input.substr(11,length);
        length=1;
        while(isdigit(input[11+var_name.length()+length])){length++;}
        eqn1=input.substr(11+var_name.length(),length);
        eqn2=input.substr(11+var_name.length()+eqn1.length());
        n1=atof(eqn1.c_str());n2=atof(eqn2.c_str());
        substitute(vector_of_maps,var_name,n1,n2);}
    //seventh requirement
    else if(input=="D"){
        vector<vector<float> >Det=D(vector_of_maps,arr);
        for(int i=0;i<Det.size();i++){
            for(int j=0;j<num_vars(vector_of_maps);j++){
        cout.width(6); cout <<left<<Det[i][j]<<"   ";}
         cout<<endl;}}
    //eighth requirement
    else if(input[0]=='D'&&input[1]==' '){
        vector<vector<float> >Det;string variable=input.substr(2);
        Det=D_variable(vector_of_maps,variable,arr_variable);
        for(int i=0;i<Det.size();i++){
            for(int j=0;j<num_vars(vector_of_maps);j++){
            cout.width(6); cout <<left<<Det[i][j]<<"   ";}
         cout<<endl;}}

     else if(input=="D_value"){
       vector<vector<float> >Det=D(vector_of_maps,arr);
       cout<<determ(arr,vector_of_maps.size())<<endl;
     }
     else if(input=="solve"){
    vector<vector<float> >Det=D(vector_of_maps,arr);
    map<std::string,float>variables;
    for(int i=0;i<vector_of_maps.size();i++){
    for(std::map<std::string,float>::iterator it=vector_of_maps[i].begin();it!=vector_of_maps[i].end();it++){
    variables[it->first]=0;}}

    for(std::map<std::string,float>::iterator it=variables.begin();it!=variables.end();it++){
        if(it->first!=""){
          D_variable(vector_of_maps,it->first,arr_variable);
         double Det_var=determ(arr_variable,vector_of_maps.size());
         double solution=Det_var/determ(arr,vector_of_maps.size());
         cout<<it->first<<'='<<solution<<endl;}}}
    else{cout<<"error,please try again or type \"quit\" to close\n";}

    }
