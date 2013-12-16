
#include <string>
#include <vector>
using namespace std;

class Reference{
	public:
		string name;
		vector<int> locations;

		Reference(){
			name = "NULL";
		}

		Reference(string _name){
			name = _name;
		}

		//This is so we can sort things
		bool operator<(const Reference& other){
			if(name.compare(other.name) < 0){
				return true;
			}
			else{
				return false;
			}
		}
};