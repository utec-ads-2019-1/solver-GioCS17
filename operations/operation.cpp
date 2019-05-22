#include "operation.h"

class OperationChild: public Operation{
  public:

    OperationChild(){}
    //OperationChild(string eq,int left,int right,vector<int>&pos){ l=left,r=right,equation=eq,posBrackets=pos;}
    OperationChild(string eq,int left,int right,vector<int>&pos,unordered_map<char,float> &d){ l=left,r=right,equation=eq,posBrackets=pos,dict=d;}

    float operate(){
      int i;

      //Compresion de la expresion quitaron parentesis mas externos
    while(posBrackets[l]==r) l++,r--;
 //     cout<<"valor de l "<<l<<"- valor de r "<<r<<endl;

    for(i=r;i>=l;i--){

      if(equation[i]==')') i=posBrackets[i];
      else if(equation[i]=='+' || equation[i]=='-'){
        int posaux=i;
        int cont=0;
        while(equation[posaux]=='+' || equation[posaux]=='-'){
          if(equation[posaux]=='-')
            cont++;
          posaux--;
        }
        if(equation[posaux]=='*'){
          OperationChild ope1(equation,l,posaux-1,posBrackets,dict);
          OperationChild ope2(equation,i+1,r,posBrackets,dict);
          return ope1.operate()*pow(-1,cont)*ope2.operate();
        }
        else if(equation[posaux]=='/'){
          OperationChild ope1(equation,l,posaux-1,posBrackets,dict);
          OperationChild ope2(equation,i+1,r,posBrackets,dict);
          return ope1.operate()/(pow(-1,cont)*ope2.operate());
        }
        else if(equation[posaux]=='^'){
          OperationChild ope1(equation,l,posaux-1,posBrackets,dict);
          OperationChild ope2(equation,i+1,r,posBrackets,dict);
          return pow(ope1.operate(),pow(-1,cont)*ope2.operate());
        }
        else{
          OperationChild ope1(equation,l,posaux,posBrackets,dict);
          OperationChild ope2(equation,i+1,r,posBrackets,dict);
          return ope1.operate()+pow(-1,cont)*ope2.operate();
        }
      }
   }

    for(i=r;i>=l;i--){
      if(equation[i]==')') i=posBrackets[i];
      else if(equation[i]=='*'){
        OperationChild ope1(equation,l,i-1,posBrackets,dict);
        OperationChild ope2(equation,i+1,r,posBrackets,dict);
        return ope1.operate()*ope2.operate();
      }
    }

   for(i=r;i>=l;i--){
     if(equation[i]==')') i=posBrackets[i];
     else if(equation[i]=='/'){
       OperationChild ope1(equation,l,i-1,posBrackets,dict);
       OperationChild ope2(equation,i+1,r,posBrackets,dict);
       return ope1.operate()/ope2.operate();
     }
   }

   for(i=r;i>=l;i--){
     if(equation[i]==')') i=posBrackets[i];
     else if(equation[i]=='^'){
       OperationChild ope1(equation,l,i-1,posBrackets,dict);
       OperationChild ope2(equation,i+1,r,posBrackets,dict);
       return pow(ope1.operate(),ope2.operate());
     }
   }

   if(equation[l]>='a' && equation[l]<='z')
     return dict[equation[l]];

   float total=0;
   int cont=0;
   bool faro=false;
   for(i=l;i<=r;i++){
     if(equation[i]=='.') {faro=true;continue;}
     total*=10;
     total+=equation[i]-'0';
     if(faro)
       cont++;
   }
   total/=pow(10,cont);
   return total;
 }

};

Operation* Operation::buildFromEquation(string equation) {
	int size=equation.size();
  vector<int> posBrackets=positionsBrackets(size,equation);
  unordered_map<char,float> dict;

  OperationChild *opC=new OperationChild(equation,0,size-1,posBrackets,dict);
  return opC;
}

Operation* Operation::buildFromEquationWithVariables(string equation,unordered_map<char,float> &dict) {
	int size=equation.size();
  vector<int> posBrackets=positionsBrackets(size,equation);

  OperationChild *opC=new OperationChild(equation,0,size-1,posBrackets,dict);
  return opC;
}
vector<int> Operation::positionsBrackets(int size,string equation){

  vector<int> posBrackets(size,-1);
  stack<int> pos;

  //Get pos ()
  int i;
	for(i=0;i<size;i++){
		if(equation[i]=='(')
			pos.push(i);
		else if(equation[i]==')'){
			posBrackets[pos.top()]=i;
      posBrackets[i]=pos.top();
			pos.pop();
		}
	}
  return posBrackets;
}
