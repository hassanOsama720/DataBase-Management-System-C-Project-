#include <iostream>
#include <string>
#include<vector>
#include<sstream>
#include <fstream>
#include <cstdlib>
#include <cctype>
#include <cstdio>
#include <filesystem>
#include<stdio.h>
#include <bits/stdc++.h>
#include<direct.h>
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif
using namespace std;

vector<string> split (string str,string seperator);
vector<int> DataRequiredsplit (string str,vector<string> header);
vector<vector<string>> conditionSplit (string str);
vector<string> splita (string user_input);
bool isNumber(const string& s);

class Select
{
private:
    /* data */
public:
    void query (string query,string dataBase){
        string line;
        vector<string> vecLine;
        vector<string> queryVec = split(query," ");
        vector<vector<string>> conditions;
        vector<string> header;
        vector<int> dataReq;
        /*---------------------------------------------------------------------------------------------------*/
        /*Open the file and get the header and data types*/
        // Open the File
        ifstream in((dataBase+"/"+queryVec[3]+".txt"));
        // Check if object is valid
        if(!in)
        {
            cout << "Cannot open the File : "<<queryVec[3]<<std::endl;
        }
        getline(in, line);
        header = split(line,",");
        /*---------------------------------------------------------------------------------------------------*/
        /*Get conditions if user enterd one*/
        if(queryVec.size() > 4){
            conditions = conditionSplit(queryVec[5]);
        }
        /*for (size_t i = 0; i < conditions.size(); i++){
            for (size_t t = 0; t < conditions[i].size(); t++)
                        cout << conditions[i][t] << endl;
        }*/
        /*--------------------------------------------------------------------------------------------------*/
        /*Get index of data needed if the user dont want all record data*/
        if(queryVec[1] != "all"){
            dataReq = DataRequiredsplit(queryVec[1],header);
        }
        /*for (size_t i = 0; i < dataReq.size(); i++)
                        cout << dataReq[i] << endl;*/
        /*-----------------------------------------------------------------------------------------------*/
        /*If Their is no conditions and need specific data */
        cout << "***************************************************************************************\n";
        if(conditions.size() == 0){
            if(dataReq.size() > 0){
                while (getline(in, line))
                {
                    if(line.size() > 0)
                        vecLine=split(line,",");
                        for (size_t i = 0; i < vecLine.size(); i++){
                            for (size_t t = 0; t < dataReq.size(); t++){
                                if(i == dataReq[t]){
                                    cout << vecLine[i] << " : ";
                                }
                            }
                        }
                        cout << "\n";
                }
            }
            //when no codition and need all data
            else{
                while (getline(in, line))
                {
                    if(line.size() > 0)
                        vecLine=split(line,",");
                        for (size_t i = 0; i < vecLine.size(); i++)
                            cout << vecLine[i] << " : ";
                        cout << "\n";
                }
            }
        }
        /*-----------------------------------------------------------------------------------------------------------*/
        /*If Their is conditions and spcific data nedded*/
        if(conditions.size() > 0){
            if(dataReq.size() > 0){
                while (getline(in, line))
                {
                    if(line.size() > 0)
                        vecLine=split(line,",");
                        int bigFlag = 1;
                        int flag = 0;
                        /*Check each condition on each field to find if any of theim meet the condition*/
                        for (size_t i = 0; i < conditions.size(); i++){
                            for (size_t t = 0; t < vecLine.size(); t++){
                                flag = 0;
                                if(header[t*2] == conditions[i][1]){
                                    if(header[(t*2)+1] == "int" || header[(t*2)+1] == "double" ){
                                        if(conditions[i][0] == ">"){
                                            if(stoi(vecLine[t]) > stoi(conditions[i][2])){
                                                flag = 1;
                                                break;
                                            }
                                        }
                                        if(conditions[i][0] == "<"){
                                            if(stoi(vecLine[t]) < stoi(conditions[i][2])){
                                                flag = 1;
                                                break;
                                            }
                                        }
                                        if(conditions[i][0] == "="){
                                            if(stoi(vecLine[t]) == stoi(conditions[i][2])){
                                                flag = 1;
                                                break;
                                            }
                                        }
                                    }
                                    else{
                                        if(conditions[i][0] == ">" || conditions[i][0] == "<"){
                                            if(vecLine[t] > conditions[i][2]){
                                                flag = 0;
                                                cout << "Cant compare between two strings";
                                                break;
                                            }
                                        }
                                        else if(conditions[i][0] == "="){
                                            if(vecLine[t] == conditions[i][2]){
                                                flag = 1;
                                                break;
                                            }
                                        }
                                    }
                                }
                            }
                            /*if one condition is not met at all will break the loop and go to next record in the table*/
                            if(flag == 0){
                                bigFlag = 0;
                                break;
                            }
                        }
                        if(bigFlag == 1){
                            for (size_t i = 0; i < vecLine.size(); i++){
                                for (size_t t = 0; t < dataReq.size(); t++){
                                    if(i == dataReq[t]){
                                        cout << vecLine[i] << " : ";
                                    }
                                }
                            }
                            cout << "\n";
                        }
                }
            }
            /*------------------------------------------------------------------------------------------------*/
            /*If their is conditions and all data needed for a record */
            else{
                while (getline(in, line))
                {
                    if(line.size() > 0)
                        vecLine=split(line,",");
                        int flag = 0;
                        int bigFlag = 1;
                        for (size_t i = 0; i < conditions.size(); i++){
                            
                            for (size_t t = 0; t < vecLine.size(); t++){
                                flag = 0;
                                if(header[t*2] == conditions[i][1]){
                                    if(header[(t*2)+1] == "int" || header[(t*2)+1] == "double" ){
                                        if(conditions[i][0] == ">"){
                                            if(stoi(vecLine[t]) > stoi(conditions[i][2])){
                                                flag = 1;
                                                break;
                                            }
                                        }
                                        if(conditions[i][0] == "<"){
                                            if(stoi(vecLine[t]) < stoi(conditions[i][2])){
                                                flag = 1;
                                                break;
                                            }
                                        }
                                        if(conditions[i][0] == "="){
                                            if(stoi(vecLine[t]) == stoi(conditions[i][2])){
                                                flag = 1;
                                                break;
                                            }
                                        }
                                    }
                                    else{
                                        if(conditions[i][0] == ">" || conditions[i][0] == "<"){
                                            if(vecLine[t] > conditions[i][2]){
                                                flag = 0;
                                                cout << "Cant compare between two strings";
                                                break;
                                            }
                                        }
                                        else if(conditions[i][0] == "="){
                                            if(vecLine[t] == conditions[i][2]){
                                                flag = 1;
                                                break;
                                            }
                                        }
                                    }
                                }
                            }
                            if(flag == 0){
                                bigFlag = 0;
                                break;
                            }
                        }
                        if(bigFlag == 1){
                            for (size_t i = 0; i < vecLine.size(); i++){
                                        cout << vecLine[i] << " : ";
                            }
                            cout << "\n";
                        }
                }
                            
            }
        }
        //Close The File
        in.close();
        cout << "Done!\n";
    }
    
};
class Update
{
private:
    /* data */
public:
    
    void query(string query,string dataBase){
        string line;
        vector<string> vecLine;
        vector<string> allData;
        vector<string> queryVec = split(query," ");
        vector<vector<string>> conditions;
        vector<string> header;
        vector<string> newValues = split(queryVec[5],",");
        vector<int> updateFields;
        /*---------------------------------------------------------------------------------------------------*/
        /*Open the file and get the header and data types*/
        // Open the File
        ifstream in((dataBase+"/"+queryVec[1]+".txt"));
        // Check if object is valid
        if(!in)
        {
            cout << "Cannot open the File : "<<queryVec[3]<<std::endl;
        }
        getline(in, line);
        allData.push_back(line);
        header = split(line,",");
        /*---------------------------------------------------------------------------------------------------*/
        /*Get conditions if user enterd one*/
        conditions = conditionSplit(queryVec[3]);
        /*for (size_t i = 0; i < conditions.size(); i++){
            for (size_t t = 0; t < conditions[i].size(); t++)
                        cout << conditions[i][t] << endl;
        }*/
        /*--------------------------------------------------------------------------------------------------*/
        /*Get index of data needed if the user dont want all record data*/
        updateFields = DataRequiredsplit(queryVec[4],header);
        /*for (size_t i = 0; i < updateFields.size(); i++)
                        cout << updateFields[i]<<" : " << newValues[i] << endl;*/
        /*-----------------------------------------------------------------------------------------------*/
        while (getline(in, line))
        {
            if(line.size() > 0)
                vecLine=split(line,",");
                int bigFlag = 1;
                int flag = 0;
                /*Check each condition on each field to find if any of theim meet the condition*/
                for (size_t i = 0; i < conditions.size(); i++){
                    for (size_t t = 0; t < vecLine.size(); t++){
                        flag = 0;
                        if(header[t*2] == conditions[i][1]){
                            if(header[(t*2)+1] == "int" || header[(t*2)+1] == "double" ){
                                if(conditions[i][0] == ">"){
                                    if(stoi(vecLine[t]) > stoi(conditions[i][2])){
                                        flag = 1;
                                        break;
                                    }
                                }
                                if(conditions[i][0] == "<"){
                                    if(stoi(vecLine[t]) < stoi(conditions[i][2])){
                                        flag = 1;
                                        break;
                                    }
                                }
                                if(conditions[i][0] == "="){
                                    if(stoi(vecLine[t]) == stoi(conditions[i][2])){
                                        flag = 1;
                                        break;
                                    }
                                }
                            }
                            else{
                                if(conditions[i][0] == ">" || conditions[i][0] == "<"){
                                    if(vecLine[t] > conditions[i][2]){
                                        flag = 0;
                                        cout << "Cant compare between two strings";
                                        break;
                                    }
                                }
                                else if(conditions[i][0] == "="){
                                    if(vecLine[t] == conditions[i][2]){
                                        flag = 1;
                                        break;
                                    }
                                }
                            }
                        }
                    }
                    /*if one condition is not met at all will break the loop and go to next record in the table*/
                    if(flag == 0){
                        bigFlag = 0;
                        allData.push_back(line);
                        break;
                    }
                }
                /*if condition is is met split the record , change the values then make it string again and push to allData vector*/
                if(bigFlag == 1){
                    for (size_t i = 0; i < vecLine.size(); i++){
                        for (size_t t = 0; t < updateFields.size(); t++){
                            if(i == updateFields[t]){
                                vecLine[i] = newValues[t];
                            }
                        }
                        cout<<vecLine[i]<<" : ";
                    }
                    cout<<endl;
                    line = "";
                    line = line + vecLine[0];
                    for (size_t i = 1; i < vecLine.size(); i++){
                        line = line + "," +vecLine[i];
                    }
                    allData.push_back(line);                        
                }
        }

        ofstream writeToFile;
        writeToFile.open((dataBase+"/"+queryVec[1]+".txt"));
        for (size_t i = 0; i < allData.size(); i++){
            writeToFile << allData[i] <<endl;
        }
        writeToFile.close();
        cout<<"Done!"<<endl;
    }
};

class DeletQuery
{
private :
    /*string databaseName  ;
    vector<string> query_vector ;
    string query  ;*/
public :
    //class constractor
    /*DeletQuery(string _query, string _dbName = "")
    {
        databaseName  = _dbName ;
        query = _query ;
        query_vector = split(query," ") ;
    }*/
   //fun that delete from file
   int * attribute_names(vector<string>attributes,string condition_parameter)
   {
        int *arr=new int[2];
        int flag=0;
        for(int i=0;i<attributes.size();i++)
        {
            if(attributes[i]==condition_parameter)
            {
            arr[0]=i/2;
            flag=1;
            }
            int last_index=(attributes.size())/2;
            arr[1]=last_index-1;
        }
        if(flag==0)
            arr[0]=-1;
        return arr;
   }

    void evaluateDlete(string query,string databaseName)
    {
        vector<string> query_vector = split(query," ") ;
        if(query_vector[0]=="delete"&&query_vector[1]=="from")
        {
            string tableFileName =(query_vector.at(2)+".txt") ;
            const char *table = tableFileName.c_str();
            ifstream checkedFile;
            //get the current path of c++ project
            auto path = std::filesystem::current_path();
            //convet to database called base
            std::filesystem::current_path(databaseName);
            cout<<path<<endl;
            FILE *fptr;
            char c[1000];
            if ((fptr = fopen(table, "r")) == NULL) {
                printf("Error! File cannot be opened.");
            }
            fscanf(fptr, "%[^\n]", c);
            fclose(fptr);
            checkedFile.open(table);
            if (checkedFile)
            {
                cout<<"File is There "<<endl  ;
                //delete table it also the file
                if(query_vector.size() == 3)
                {
                    checkedFile.close() ;
                    remove(table);
                    cout << "Table deleted\n";
                    std::filesystem::current_path("../");
                    return;
                }
                //if there is a condition
                else
                {
                    if(query_vector[3]=="where")
                    {
                    char mychar;
                    string fline;
                    vector<string> condition;
                    vector<string>attributes;
                    ofstream temp;
                    vector<string> parameter_value;
                    const char * oldname = "temp.txt";
                    const char * newname = tableFileName.c_str();
                    temp.open("temp.txt");
                    condition=splita(query_vector.at(4).c_str());
                    attributes=split(c,",");
                    string condition_parameter=condition[0];
                    string condition_val=condition[1]; 
                    int* arr;
                    arr=attribute_names(attributes,condition_parameter);
                    int index1=arr[0];
                    int index2=arr[1];
                            while (getline(checkedFile,fline))
                                {
                                    //split data in each line with , seperator
                                        //cout<<fline<<endl;
                                         parameter_value=split(fline.c_str(),",");
                                         if(index1==-1)
                                         {
                                            cout<<"column not in the table"<<endl;
                                            std::filesystem::current_path("../");
                                            return;
                                         }
                                         string attribute_val=parameter_value[index1];
                                         string last_attribute_val=parameter_value[index2];
                                         //cout<<attribute_val<<"\t"<<last_attribute_val<<endl;
                                        //last index of age is space so i remove it
                                        last_attribute_val.erase(std::remove_if(last_attribute_val.begin(), last_attribute_val.end(), ::isspace),
                                        last_attribute_val.end());
                                                if (last_attribute_val==condition_val||attribute_val==condition_val)
                                                {
                                                    cout<<"record deleted"<<endl;
                                                }
                                                else
                                                {
                                                    temp << fline << endl;
                                                }
                                            }
                                            temp.close();
                                            checkedFile.close();
                                            remove(table);
                                            rename(oldname, newname);
                                       }
                }
            }
            else
            {
                cout<<"no such file"<<endl ;
                cout<<tableFileName ;
                return ;
            }
    }
    else
        cout<<"check your query ,please";
    std::filesystem::current_path("../");
    }
};

class Insert
{
public:
    void insertInto (string qry , string dataBaseName)
    {
        string line;
        vector<string> header;
        vector<string> vecQury = split(qry , " ");
        vector<string> Values = split (vecQury[3], ",");
        ifstream in((dataBaseName+"/"+vecQury[2]+".txt"));
        // Check if object is valid
        if(!in)
        {
            cout << "Cannot open the File : "<<vecQury[2]<<std::endl;
        }
        else{

            getline(in, line);
            header = split(line,",");
            if(Values.size() == (header.size()/2)){
                if(vecQury[0] == "insert"){
                    for (size_t i = 0; i < Values.size(); i++)
                    {
                        if(!isNumber(Values[i]) && header[((i*2)+1)] == "int"){
                            cout<<"some values are not of required type\n";
                            return;
                        }

                    }
                    
                    ofstream insertInto;
                    insertInto.open((dataBaseName+"/"+vecQury[2]+".txt"), std::ios_base::app);
                    if(!insertInto)
                    {
                        cout << "Cannot open the File : "<<vecQury[2]<<endl;
                    }
                    else{
                        insertInto << vecQury[3] <<endl ;
                        cout<<"Done!\n";
                    }
                    insertInto.close();
                }
            }else{
                cout<<"values not matched\n";
            }
            in.close();
        }
    }
};
class Create
{
public:
    void createTable (string qry , string dataBaseName)
    {
        vector<string> vecQury = split(qry , " ");
//      vector<string> Values = split (vecQury[3], ",");
        if(vecQury[0] == "create"){

            ofstream createT;
            createT.open((dataBaseName+"/"+vecQury[2]+".txt"), std::ios_base::app);
            if(!createT)
            {
                cout << "Cannot open the File : "<<vecQury[2]<<endl;
            }
            else{
                createT << vecQury[3] << endl ;
                cout<<"Done!";
            }
        }
    }
    void createDataBase (string qry)
    {
        vector<string> vecQury = split(qry , " ");
//      vector<string> Values = split (vecQury[3], ",");
        if(vecQury[1] == "database"){
            auto path = std::filesystem::current_path();
            int check;
           const char *dir=vecQury[2].c_str();
           check=mkdir(dir);
            if(!check)
                cout<<"directory created"<<endl;
            else
            {
                cout<<"not created"<<endl;
                exit(1);
            }
                
        }
    }
};
/***************************************************************************************************************************/
/*Commen split function for any use*/
vector<string> split (string str,string seperator){
    vector<string> res;
 
    stringstream ss(str);
    if(seperator == " "){
        while (ss.good()) {
            string substr;
            getline(ss, substr,' ');
            if(substr.size() > 0)
                res.push_back(substr);
        }
    }
    else{
        while (ss.good()) {
            string substr;
            getline(ss, substr,',');
            if(substr.size() > 0)
                res.push_back(substr);
        }
    }
    
    return res;
}

/*Split function to take name of fields needed and give vector with index of each field*/
vector<int> DataRequiredsplit (string str,vector<string> header){
    vector<int> res;
 
    stringstream ss(str);
    
        while (ss.good()) {
            string substr;
            getline(ss, substr,',');
            for (size_t i = 0; i < header.size(); i+=2)
            {
                if(header[i] == substr){
                    if(i == 0){
                        res.push_back(i);
                    }
                    else{
                        res.push_back((i/2));
                    }
                }
            }
        }
    
    return res;
}

/*Split function to take conditions and split theim and then split each condition into three parts 
(feiled , comparsion operator , data to comare with) , return 2d vector*/
vector<vector<string>> conditionSplit (string str){
    vector<string> comaSep;
    vector<string> logSep;
    vector<vector<string>> res;
 
    stringstream ss(str);


    while (ss.good()) {
        string substr;
        getline(ss, substr,',');
        comaSep.push_back(substr);
    }
    char sep = ' ';
    for (size_t i = 0; i < comaSep.size(); i++){
        stringstream ss(comaSep[i]);
        if (comaSep[i].find('>') != std::string::npos){
            sep = '>';
            logSep.push_back(">");
        }
        else if (comaSep[i].find('<') != std::string::npos){
            sep = '<';
            logSep.push_back("<");
        }
        else if (comaSep[i].find('=') != std::string::npos){
            sep = '=';
            logSep.push_back("=");
        }
        else{
            sep = 'n';
        }
        while (ss.good()) {
            string substr;
            getline(ss, substr,sep);
            if(substr.size() > 0)
                logSep.push_back(substr);
        }
        res.push_back(logSep);
        logSep.clear();
        
    }
    
    
    return res;
}

//split fun using "=" seprator
vector<string> splita (string user_input)
{
    string temp ;
    stringstream line(user_input);
    vector<string> str;

    while(getline(line, temp, '='))
    {
        str.push_back(temp);
    }
    return str ;
}


bool isNumber(const string& s)
{
    for (char const &ch : s) {
        if (std::isdigit(ch) == 0)
            return false;
    }
    return true;
}

/******************************************************************************************************************************/



int main (){
    Select s;
    Update u;
    DeletQuery d;
    Insert i;
    Create c;
    string query;
    string dataBaseName;



    cout << "****************************************************************************************************************************" << endl;
    cout << "******                                                                                                                 *****" << endl;
    cout << "******                      Welcome To our DataBase management system (OS C++ Project)                                 *****" << endl;
    cout << "******                         Team Members (Hassan // Nabila // Mostafa // Mohamed)                                   *****" << endl;
    cout << "******                                                                                                                 *****" << endl;
    cout << "****************************************************************************************************************************" << endl;
    cout << "******                                                                                                                 *****" << endl;
    cout << "******                            At anytime to renter Database Name just type DataBase                                *****" << endl;
    cout << "******                                    At anytime to Exit just type Exit                                            *****" << endl;
    cout << "******                                                                                                                 *****" << endl;
    cout << "****************************************************************************************************************************" << endl;
    cout << "******                                                                                                                 *****" << endl;
    cout << "******           If query don't work that means you wrote the query wrong with more spaces or wrong formula            *****" << endl;
    cout << "******                                                                                                                 *****" << endl;
    cout << "****************************************************************************************************************************" << endl;
    Sleep(1000);
    cout << "Please Enter DataBase Name : "<<endl;
    getline(cin,dataBaseName);




    cout << "****************************************************************************************************************************" << endl;
    cout << "***                                                                                                                      ***" << endl;
    cout << "***  Query form :  select (field names or juste type all) from (table name) where (conditions coma seperated)            ***" << endl;
    cout << "***        Query form :  update (table name) where (conditions coma seperatede) (column names) (new values)              ***" << endl;
    cout << "***                    Query form :  create table (table name) columnn name followed by data type                        ***" << endl;
    cout << "***                    Query form :  insert into (table name) values coma seperated                                      ***" << endl;
    cout << "***                                     Query form :  craete database (batabase name)                                    ***" << endl;
    cout << "***                                Query form :  delete from (table name) where (conditions)                             ***" << endl;
    cout << "***                            !Very Very Very Important => Dont use any spaces except ones shown above                  ***" << endl;
    cout << "***                                                                                                                      ***" << endl;
    cout << "****************************************************************************************************************************" << endl;
    while(query.find("exit") == string::npos){
        cout << "Your Query : ";
        getline(cin,query);
        if (query == "DataBase")
        {
            cout << "Please Enter DataBase Name : "<<endl;
            getline(cin,dataBaseName);
        }
        else if (query.find("select") != string::npos)
        {
            s.query(query,dataBaseName);
        }
        else if (query.find("update") != string::npos)
        {
            u.query(query,dataBaseName);
        }
        else if (query.find("delete") != string::npos)
        {
            d.evaluateDlete(query,dataBaseName);
        }
        else if (query.find("insert") != string::npos)
        {
            i.insertInto(query,dataBaseName);
        }
        else if (query.find("create") != string::npos)
        {
            if(query.find("table") != string::npos){
                c.createTable(query,dataBaseName);
            }
            else if(query.find("database") != string::npos){
                c.createDataBase(query);
            }
        }
    cout << "******************************************************************************************" << endl;

    }
}