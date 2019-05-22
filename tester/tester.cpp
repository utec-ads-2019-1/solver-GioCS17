#include "tester.h"

void Tester::execute() {
    string equations[] = {
        "7/4*((3+1)*3)+3",
        "7/4*((2+-+--8)*2)+3",
        "2+(3)",
        "7/4*((1+2)^4*2)+3",
        "7*-1",
        "1-2*5/2+1-2^4+1",
        "19+-+++-++++++9",
        "((7*3)/4+6*(3^2)/2)*(-1)",
        "(5+-3)+(21/3*5)-(5^3-2)",
        "((19--45/16*100-(181^2-15*10)))","2+(3)"
    };

    float results[] = {
        24,
        -18,
        5,
        286.5,
        -7,
        -18,
        28,
        -32.25,
        -86,
        -32310.75,5
    };

    const unsigned int size = sizeof(equations) / sizeof(string);
    for (int i = 0; i < size; ++i) {
        Operation* root = Operation::buildFromEquation(equations[i]);
        float respuesta = root->operate();
        ASSERT(respuesta == results[i], "The solver is not working");
        cout << "Equation(" << i + 1 << ") solved" << endl;
    }
    //New option
    cout<<"Deseas ingresar otras expresiones con variables: 1(yes) o 0(no):"<<endl;
    bool answer=0;
    float var;
    cin>>answer;
    cin.ignore();
    string newequation;
    if(answer){
      int qs;
      cout<<"Cuantas nuevas preguntas desear realizar?:"<<endl;
      cin>>qs;
      cin.ignore();
      for(int m=1;m<=qs;m++){
        cout<<"Ingresa la ecuacion "<<m<<endl;
        unordered_map<char,float> dict;
        getline(cin,newequation);
        for(char c:newequation){
          if(c>='a' && c<='z'){
            if(!dict.count(c)){
              cout<<"valor para "<<c<<":";
              cin>>var;
              dict[c]=var;
            }
          }
        }
        cin.ignore();
        Operation* root = Operation::buildFromEquationWithVariables(newequation,dict);
        float respuesta = root->operate();
        cout<<"La respuesta es "<<respuesta<<endl;
      }
    }
}
