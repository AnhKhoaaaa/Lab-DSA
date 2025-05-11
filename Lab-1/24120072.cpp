#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

//DECLARATION:

//Stack implement:
struct NODE{
    char key;
    NODE* p_next;
};
struct Stack{
    NODE* top;
};
Stack* initializeStack();
void push(Stack *&s, char key);
char pop(Stack *&s);
int size(Stack *s);
bool isEmpty(Stack *s);

void freeStack(Stack*& s);

//Big Integer math: using String to handle big int
//Basic opetators with string contain big integer.
string addStrings(string a,string b);
string subtractStrings(string a, string b);
string multiplyStrings(string a, string b);
string divideStrings(string a, string b);
bool isNegative(string s);


//Parsing syntax:
//change expressions from infix to postfix form.
//calculate with postfix form of the expressions.
vector<string> infixToPostfix(string expression);
string evaluatePostfix(vector<string> postfix);

//Main function
int main(int argc,char* argv[]){
    //Read command-line arguments:
    if(argc!=3){
        cout<<"Unidentify command!"<<endl;
        cout<<"Try again, with: 24120072 tests.txt output_24120072.txt"<<endl;
        cout<<"Or: ./24120072 tests.txt output_24120072.txt"<<endl;
        return 0;
    }
    string x,y;
    string arg1=argv[1];
    string arg2=argv[2];
    if(arg1=="tests.txt" && arg2=="output_24120072.txt"){
        x=argv[1];
        y=argv[2];
    }
    else{
        cout<<"Wrong input and output file name!"<<endl;
        cout<<"Try: 24120072 tests.txt output_24120072.txt"<<endl;
        return 0;
    }

    //Open input and output file:
    ifstream in(x);
    if(!in.is_open()){
        cout<<"Can not open file "<<x<<endl;
        return 0;
    }
    ofstream out(y);
    if(!out.is_open()){
        cout<<"Can not open file "<<y<<endl;
        return 0;
    }
    string expression;
    while(getline(in,expression)){
        vector<string> postFix=infixToPostfix(expression);
        cout<<evaluatePostfix(postFix)<<endl;
        out<<evaluatePostfix(postFix)<<endl;
    }
    //Close input and output file:
    in.close();
    out.close();
}

//DEFINITION:

//Stack implement:
Stack* initializeStack(){   
    Stack* s=new Stack();
    s->top=nullptr;
    return s;
}
bool isEmpty(Stack *s){
    return s->top==nullptr;
}
void push(Stack *&s, char key){
    NODE* newNode=new NODE();
    newNode->key=key;
    newNode->p_next=nullptr;
    if(isEmpty(s)){
        s->top=newNode;
        return;
    }
    newNode->p_next=s->top;
    s->top=newNode;
}
char pop(Stack *&s){
    if(isEmpty(s)){
        return -1;
    }
    NODE* temp=s->top;
    char val=temp->key;
    s->top=s->top->p_next;
    delete temp;
    return val;
}
int size(Stack *s){
    if(isEmpty(s)){
        return 0;
    }
    else{
        int count=0;
        NODE* cur=s->top;
        while(cur && ++count){
            cur=cur->p_next;
        }
        return count;
    }
}
void freeStack(Stack*& s){
    if(s==nullptr){
        return;
    }
    NODE* cur=s->top;
    while(cur){
        NODE* temp=cur;
        cur=cur->p_next;
        delete temp;
    }
    delete s;
}

//Big Integer math:
int compareStrings(string a,string b){
    if(a.length()<b.length()){
        return -1; //a<b
    }
    else if(a.length()>b.length()){
        return 1; //a>b
    }
    else{
        for(int i=0;i<a.length();i++){
            if(a[i]>b[i]){
                return 1; //a>b
            }
            if(a[i]<b[i]){
                return -1; //a<b
            }
        }
        return 0; //a=b
    }
}
string addStrings(string a,string b){
    if(a.length()<b.length()){
        swap(a,b);
    }
    bool over=0;
    string result="";
    int i = b.length()-1;
    int space=a.length()-b.length();
    for(i;i>=0;i--){
        int c=(a[i+space]-'0')+(b[i]-'0') + over;
        over=(c>=10);
        result=char(c%10+'0')+result;
    }
    for(i=space-1;i>=0;i--){
        int c=(a[i]-'0')+over;
        over=(c>=10);
        result=char(c%10  + '0')+result;
    }
    if(over){
        result='1'+result;
    }
    return result;
}
string subtractStrings(string a, string b){
    //If a<b we will add '-' in front of result and this boolen is to remember that.
    bool negative=0;

    //Make sure that a>b:
    if(compareStrings(a,b)==0){
        return "0";
    }
    if(compareStrings(a,b)==-1){
        swap(a,b);
        negative=1;
    }

    bool owe=0;
    string result="";
    int i=a.length()-1;

    //Add 0 in front of b to make sure two string have the same length, so that we can substract each char.
    while(a.length()>b.length()){
        b='0'+b;
    }

    //Assume that we owe 1 in every char, but if a[i]-b[i]>0, we will set owe to 0 else owe=1.
    for(i;i>=0;i--){
        int c=(a[i] - '0') + 10 - (b[i]-'0') - owe;
        owe=(c<10);
        result=char(c%10+'0') + result;
    }
    
    //Remove every '0' before result.
    int zeros=0;
    while(zeros<result.length()-1 && result[zeros]=='0'){
        zeros++;
    }
    //Just take the part which not include '0' in the first.
    result=result.substr(zeros);
    if(negative){
        result='-'+result;
    }
    return result;
}
string multiplyStrings(string a, string b){
    if(a=="0"||b=="0"){
        return "0";
    }
    if(a.length()<b.length()){
        swap(a,b);
    }
    string result="";
    int over=0;
    for(int i=b.length()-1;i>=0;i--){
        int pos=result.length()-(b.length()-1)+i;
        string subStr1="";
        for(int j=a.length()-1;j>=0;j--){
            int c=(b[i] - '0')*(a[j] - '0')+over;
            over=c/10;
            subStr1=char(c%10 + '0') + subStr1;
        }
        if(over!=0){
            subStr1=char(over+'0')+subStr1;
            over=0;
        }
        string subStr2=result.substr(0,pos); 
        result=addStrings(subStr2,subStr1)+result.substr(pos);
    }
    return result;
}
string divideStrings(string a, string b){
    if(b=="0") return "Error";
    //make sure a>b when divide
    if(compareStrings(a,b)==-1){
        return "0";
    }
    if(compareStrings(a,b)==0){
        return "1";
    }

    string res="";
    string cur="";
    int i=0;
    while(i<a.length()){
        cur=cur+a[i];
        i++;
        while (cur.length()>1 && cur[0]=='0') {
            cur=cur.substr(1);
        }
        if(compareStrings(cur,b)==-1){ //if cur<b and res already have value, add '0' after res.
            if(!res.empty()){
                res=res+'0';
            }
            continue;
        }
        int count=0;
        while(compareStrings(multiplyStrings(b,to_string(count+1)),cur)!=1){
            count++;
        }
        cur=subtractStrings(cur,multiplyStrings(b,to_string(count)));
        res=res+ to_string(count);
    }
    return res;
}
bool isNegative(string s){
    return s[0]=='-';
}

//Parsing syntax:
int prioritize(char a){
    if(a=='/'||a=='*') return 2;
    else if(a=='+'||a=='-') return 1;
    else return 0; //other charactor.
}

vector<string> infixToPostfix(string expression){
    bool justAddOp=true; //Check if two operators or operands next to each other.
    vector<string> postFix;
    Stack* s= initializeStack();
    int n=expression.length();
    int i=0;
    while(i<n){
        if(expression[i]==' '){
            i++;
            //skip space.
        }
        else if(isdigit(expression[i])){
            if(justAddOp==false){ //exist two operands next to each other.
                freeStack(s);
                return {};
            }
            justAddOp=false;
            string number="";
            while(i<n && isdigit(expression[i])){
                number=number+expression[i];
                i++;
            }
            while(number.size()>1 && number[0]=='0'){ //remove all unnecessary '0'
                number=number.substr(1);
            }
            //add big int to vector postFix.
            postFix.push_back(number);
        }
        else if(expression[i]=='('){
            while(expression[i+1]==' '){ //delete space.
                i++;
            }
            if(expression[i+1]=='-'){
                i++;
                string number="";
                number=number+expression[i];
                i++;
                while(expression[i]==' '){ //delete space.
                    i++;
                }
                while(i<n && isdigit(expression[i])){
                    number=number+expression[i];
                    i++;
                }
                while(expression[i]==' '){ //delete space.
                    i++;
                }
                if(number=="-"){ //Case: (-) with no number.
                    freeStack(s);
                    return {};
                }
                postFix.push_back(number);
                if(justAddOp==false){ //exist two operands next to each other: 3 (-3)
                    freeStack(s);
                    return {};
                }
                justAddOp=false;
                if(expression[i]==')'){
                    i++; //skip ')'
                }
                else{ //missing ')'
                    freeStack(s);
                    return {};
                }
            }
            else if(isdigit(expression[i+1])||expression[i+1]=='('){ //case: (24) or ((4+3)).
                push(s,'(');
                i++;
            }
            else{ //case: (+5)
                    freeStack(s);
                    return {};
            }
        }
        else if(expression[i]==')'){
            while(!isEmpty(s) && s->top->key!='('){
                //add all operator from stack s that after '(' to vector postFix.
                string op=string(1, pop(s));
                postFix.push_back(op);
            }
            if(isEmpty(s)){ //Missing '('.
                freeStack(s);
                return {};
            }
            if(justAddOp){ //Case: (5+)
                freeStack(s);
                return {};
            }
            //delete '(' in stack.
            pop(s);
            i++;
        }
        else{
            if(prioritize(expression[i])==0){ //Other characters like: abc&#@!$...
                freeStack(s);
                return {};
            }
            //operators with larger prioitize go to postfix first.
            while(!isEmpty(s) && (prioritize(s->top->key) >= prioritize(expression[i]))){
                string op=string(1, pop(s));
                postFix.push_back(op);
            }
            if(!justAddOp){ //An operator after an operand.
                push(s,expression[i]);
                justAddOp=true;
                i++;  
            }
            else{ //exist 2 operators next to each other.
                freeStack(s);
                return {};
            }  
        }
    }
    if(justAddOp){ //Case: 3 + 5 +
        freeStack(s);
        return {};
    }
    while(!isEmpty(s)){ //push all remaining operators to postfix.
        if(s->top->key=='('){ //Missing ')'
            freeStack(s);
            return {};
        }
        string op=string(1, pop(s));
        postFix.push_back(op);
    }
    freeStack(s);
    return postFix;
}
string evaluatePostfix(vector<string> postfix){
    if(postfix.empty()){ //Every syntax error in expression will return an empty vector.
        return "Error";
    }
    vector<string> nums;
    for(string value:postfix){
        if(value=="-"||value=="+"||value=="*"||value=="/"){
            if(nums.size()<2){ //Not enough operand before an operator to calculate.
                return "Error";
            }
            string a=nums.back();
            nums.pop_back();
            bool isNegativeA=isNegative(a);
            string b=nums.back();
            nums.pop_back();
            bool isNegativeB=isNegative(b);
            string res="";
            if(value=="-"){
                if(!isNegativeA&&!isNegativeB){
                    res=subtractStrings(b,a);
                }
                else if(isNegativeA&&!isNegativeB){
                    a=a.substr(1);
                    res=addStrings(b,a);
                }
                else if(!isNegativeA&&isNegativeB){
                    b=b.substr(1);
                    res="-"+addStrings(a,b);
                }
                else{
                    a=a.substr(1);
                    b=b.substr(1);
                    res=subtractStrings(a,b);
                }
            }
            else if(value=="+"){
                if(!isNegativeA&&!isNegativeB){
                    res=addStrings(a,b);
                }
                else if(isNegativeA&&!isNegativeB){
                    a=a.substr(1);
                    res=subtractStrings(b,a);
                }
                else if(!isNegativeA&&isNegativeB){
                    b=b.substr(1);
                    res=subtractStrings(a,b);
                }
                else{
                    a=a.substr(1);
                    b=b.substr(1);
                    res="-"+addStrings(a,b);
                }
            }
            else if(value=="*"){
                if(!isNegativeA&&!isNegativeB){
                    res=multiplyStrings(a,b);
                }
                else if(isNegativeA&&!isNegativeB){
                    a=a.substr(1);
                    res="-"+multiplyStrings(b,a);
                }
                else if(!isNegativeA&&isNegativeB){
                    b=b.substr(1);
                    res="-"+multiplyStrings(a,b);
                }
                else{
                    a=a.substr(1);
                    b=b.substr(1);
                    res=multiplyStrings(a,b);
                }
            }
            else{
                if(!isNegativeA&&!isNegativeB){
                    res=divideStrings(b,a);
                }
                else if(isNegativeA&&!isNegativeB){
                    a=a.substr(1);
                    res="-"+divideStrings(b,a);
                }
                else if(!isNegativeA&&isNegativeB){
                    b=b.substr(1);
                    res="-"+divideStrings(b,a);
                }
                else{
                    a=a.substr(1);
                    b=b.substr(1);
                    res=divideStrings(a,b);
                }
            }
            if(res=="Error"){
                return res;
            }
            while (res.length() > 1 && res[0] == '0') { //delete unnecessary '0'.
                res=res.substr(1);
            }
            nums.push_back(res);
        }
        else{
            nums.push_back(value);
        }
    }
    if(nums.size()!=1){ //Vector have not only the result but another operands.
        return "Error";
    }
    return nums.back(); //the only value in vector is the result.
}
