#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

//DECLARATION:
struct Company{
    string name;
    string profix_tax;
    string address;
};

struct HashNode{
    Company info;
    HashNode* next;
};

struct HashTable{
    int size;
    vector<HashNode*> Table;
};

vector<Company> readCompanyList(string filename);
long long hashString(string company_name);
HashTable* createHashTable(vector<Company> list_company);
void insert(HashTable* hash_table, Company company);
Company* search(HashTable* hash_table, string company_name);

int main(int argc, char* argv[]){
    //read argument and file name.
    if(argc!=4){
        cout<<"Unidentify command!"<<endl;
        cout<<"Correct format: main MST.txt input.txt output.txt"<<endl;
        return 0;
    }
    string infoFile=argv[1];
    string inputFile=argv[2];
    string outputFile=argv[3];
    if(infoFile!="MST.txt" || inputFile!="input.txt" || outputFile!="output.txt"){
        cout<<"Unidentify command!"<<endl;
        cout<<"Correct format: main MST.txt input.txt output.txt"<<endl;
        return 0;
    }
    //read and create company list from MST.txt.
    vector<Company> list_company=readCompanyList(infoFile);
    //create HashTable from company list.
    HashTable* companyTable=createHashTable(list_company);

    //Open input and output file.
    ifstream in(inputFile);
    if(!in.is_open()){
        cout<<"Can not open "<<inputFile<<endl;
        return 0;
    }
    ofstream out(outputFile);
    if(!out.is_open()){
        cout<<"Can not open "<<outputFile<<endl;
        return 0;
    }
    string company_name;
    while(getline(in,company_name)){
        if (company_name.empty()) {
            continue; //skip empty line
        }
        if(company_name.substr(0,2)=="//"){
            continue;
        }
        Company* info=search(companyTable,company_name);
        if(info!=nullptr){
        out<<info->name<<'|'<<info->profix_tax<<'|'<<info->address<<endl;
        }
    }
    in.close();
    out.close();
    return 0;
}

//DEFINITION
vector<Company> readCompanyList(string filename){
    ifstream in(filename);
    if(!in.is_open()){
        cout<<"Can not open "<<filename<<endl;
        return {};
    }
    vector<Company> list_company;
    string line;
    //skip the information fields.
    getline(in,line);
    while(getline(in,line)){
        Company info;
        stringstream ss(line);
        getline(ss,info.name,'|');
        getline(ss,info.profix_tax,'|');
        getline(ss,info.address,'\n');
        list_company.push_back(info);
    }
    in.close();
    return list_company;
}
long long hashString(string company_name){
    long long hash=0;
    int p=31;
    long long p_pow=1;
    if(company_name.size()<=20){
        for(int i=0;i<company_name.size();i++){
            hash=(hash+int(company_name[i]) * p_pow)%2000;
            p_pow=(p_pow*p)%2000;
        }
    }
    else{
        company_name=company_name.substr(company_name.size()-20);
        for(int i=0;i<20;i++){
            hash= (hash+int(company_name[i]) * p_pow)%2000;
            p_pow=(p_pow*p)%2000;
        }
    }
    return hash;
}
HashTable* createHashTable(vector<Company> list_company){
    HashTable* companyTable =new HashTable();
    companyTable->size=2000;
    companyTable->Table=vector<HashNode*> (companyTable->size,nullptr);
    for(int i=0;i<list_company.size();i++){
        HashNode* Node=new HashNode();
        Node->info=list_company[i];
        Node->next=nullptr;
        long long hash=hashString(list_company[i].name);
        if(companyTable->Table[hash]==nullptr){
            companyTable->Table[hash]=Node;
        }
        else{
            HashNode* cur=companyTable->Table[hash];
            while(cur->next!=nullptr){
                cur=cur->next;
            }
            cur->next=Node;
        }
    }
    return companyTable;
}
void insert(HashTable* hash_table, Company company){
    HashNode* Node=new HashNode();
    Node->info=company;
    Node->next=nullptr;
    long long hash=hashString(company.name);
    if(hash_table->Table[hash]==nullptr){
        hash_table->Table[hash]=Node;
    }
    else{
        HashNode* cur=hash_table->Table[hash];
            while(cur->next!=nullptr){
                cur=cur->next;
            }
            cur->next=Node;
    }
}
Company* search(HashTable* hash_table, string company_name){
    long long hash=hashString(company_name);
    HashNode* cur=hash_table->Table[hash];
    if(cur==nullptr){
        return nullptr;
    }
    else{
        while(cur!=nullptr){
            if(cur->info.name==company_name){
                return &(cur->info);
            }
            cur=cur->next;
        }
        return nullptr;
    }
}