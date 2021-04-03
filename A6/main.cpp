#include <iostream>
#include "node.h"
#include "operator.h"
#include "operand.h"
#include "utils.h"

int main()
{
	try{

		Tree t=make_tree();
		if (!check_tree(t))
		{	
			cerr<<"Problem with Tree."<<endl;
			return 0;
		}
		string line;
		int i=t.size()+1;
		while(getline(cin,line))
		{	
			i++;
			deal(t,line,i);
		}
		
	}catch(InaccessibleNodeException e){
		cout<<"Cannot Make Tree. Aborting..."<<endl;
		return 0;
	}
	catch(OperandChildException e){
		cerr<<"Cannot Add Child to Operand. Aborting"<<endl;
		return 0;
	}
	return 0;
}