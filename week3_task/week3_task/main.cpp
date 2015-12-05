#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

class headquarters
{
public:
	headquarters(const int thelifeValue, const int theredOrblue, const int thewarriorvalue[], const string thewarriorName[], const int order[], const string theheadquarterName[]);
	~headquarters(){};
	int getLifeValue(){
		return lifeValue;
	}
	int getWarriosValues(int position){
		return warriorvalues[position];
	}
	void product(int time, int position);


private:
	int lifeValue;
	int redOrblue;//标记司令部，0是red,1是blue
	int count;//士兵数量
	int warriorCount[5];
	string headquarterName;
	string warriorName[5];
	int warriorvalues[5];
};
headquarters::headquarters(const int thelifeValue, const int theredOrblue, const int thewarriorvalue[], const string thewarriorName[], const int order[], const string theheadquarterName[]){
	count = 0;
	lifeValue = thelifeValue;
	redOrblue = theredOrblue;
	headquarterName = theheadquarterName[redOrblue];
	for (int i = 0; i < 5; ++i){
		warriorCount[i] = 0;
		warriorName[i] = thewarriorName[order[i]];
		warriorvalues[i] = thewarriorvalue[order[i]];
	}
}
void headquarters::product(int time, int position){
	count++;
	warriorCount[position]++;
	cout << setfill('0') << setw(3) << time << " " << headquarterName << " " << warriorName[position] << " " << count << " born with strength " << warriorvalues[position] << "," << warriorCount[position] << " " << warriorName[position] << " in " << headquarterName << " headquarter" << endl;
	lifeValue -= warriorvalues[position];
}

int main()
{
	const int redorder[5] = { 2, 3, 4, 1, 0 };
	const int bludeorder[5] = { 3, 0, 1, 2, 4 };
	const string headquarterNames[2] = { "red", "blue" };
	const string warriorNames[5] = { "dragon", "ninja", "iceman", "lion", "wolf" };
	int n = 0;
	cin >> n;
	for (int i = 0; i <= n; ++i){
		int priorValue[5], headquartersvalue, minvalue, redposition = 0, blueposition = 0;
		bool redHadStop = false, blueHadStop = false;

		cin >> headquartersvalue;
		for (int j = 0; j < 5; ++j){
			cin >> priorValue[j];
		}
		cout << "Case:" << i << endl;
		minvalue = priorValue[0];
		for (int j = 1; j < 5; ++j){
			if (priorValue[j] < minvalue) minvalue = priorValue[j];
		}

		//init headquarters
		headquarters redOne = headquarters(headquartersvalue, 0, priorValue, warriorNames, redorder, headquarterNames);
		headquarters blueOne = headquarters(headquartersvalue, 1, priorValue, warriorNames, bludeorder, headquarterNames);
		for (int time = 0; !redHadStop | !blueHadStop; time++){
			if (!redHadStop){
				if (redOne.getLifeValue() < minvalue){
					cout << setfill('0') << setw(3) << time << " red headquarter stops making warriors" << endl;
					redHadStop = true;
				}
				else {
					while (true){
						if (redOne.getLifeValue() >= redOne.getWarriosValues(redposition)){
							redOne.product(time, redposition);
							if (redposition == 4 ? redposition == 0 : redposition++);
							break;
						}
						else {
							if (redposition == 4 ? redposition == 0 : redposition++);
						}
					}
				}
			}
			if (!blueHadStop){
				if (blueOne.getLifeValue() < minvalue){
					cout << setfill('0') << setw(3) << time << " blue headquarter stops making warriors" << endl;
					blueHadStop = true;
				}
				else {
					while (true)
					{
						if (blueOne.getLifeValue() >= blueOne.getWarriosValues(blueposition)){
							blueOne.product(time, blueposition);
							if (blueposition == 4 ? blueposition = 0 : blueposition++);
							break;
						}
						else
						{
							if (blueposition == 4 ? blueposition = 0 : blueposition++);
						}
					}
				}
			}
		}

	}



	//system("pause");
	return 0;
}
