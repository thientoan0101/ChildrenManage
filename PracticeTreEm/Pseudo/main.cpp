#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <queue>
#include <sstream>
#include <vector>
#include <algorithm>
#include <conio.h>
#include <windows.h>
#include <ctime>




using namespace std;

const string TREEM = "treem";
const string BAME = "bame";


struct Time
{
	int hour;
	int minute;

	friend bool operator==(const Time& t1, const Time& t2) {					// operator to show show sort function how to build minHeap priority queu
		return (t1.hour == t2.hour && t1.minute == t2.minute);
	}

	friend bool operator<(const Time& t1, const Time& t2) {					// operator to show show sort function how to build minHeap priority queu
		if (t1.hour < t2.hour) return true;
		else if (t1.hour == t2.hour) {
			return t1.minute < t2.minute;
		}
		return false;
	}

	friend bool operator>(const Time& t1, const Time& t2) {					// operator to show show sort function how to build minHeap priority queu
		if (t1.hour > t2.hour) return true;
		else if (t1.hour == t2.hour) {
			return t1.minute > t2.minute;
		}
		return false;
	}

	friend bool operator<=(const Time& t1, const Time& t2) {					// operator to show show sort function how to build minHeap priority queu
		return (t1 < t2 || t1 == t2);
	}

	friend bool operator>=(const Time& t1, const Time& t2) {					// operator to show show sort function how to build minHeap priority queu
		return (t1 > t2 || t1 == t2);
	}
};


struct RegulationTime
{
	Time from;
	Time to;
	int duration;
	int interrupt;
	int sumTime;	
};


	
class Children
{
private:
	Time startTime;
	int remainDurationTime;
	int remainSumTime;
	int interruptTime;
	Time nextTime;

public:
	// constructor:
	Children()
	{
		// sau nay phai lay getTime()
		startTime.hour = 0;
		startTime.minute = 0;
		remainDurationTime = 0;
		remainSumTime = 0;
		interruptTime = 0;
		nextTime.hour = 0;
		nextTime.minute = 0;
	}


	Children(int rd, int rs, RegulationTime reguTime, Time nt)
	{
		startTime.hour = 0;
		startTime.minute = 0;
		if (reguTime.duration == 0) {
			remainDurationTime = (reguTime.to.hour*60 + reguTime.to.minute) - (startTime.hour*60 + startTime.minute);
		}
		else {
			remainDurationTime = rd;
		}

		if (reguTime.sumTime == 0) {
			remainSumTime = (reguTime.to.hour * 60 + reguTime.to.minute) - (reguTime.from.hour * 60 + reguTime.from.minute);
		}
		else {
			remainSumTime = rs;
		}		
		nextTime = nt;
	}

public:
	int getRemainDuration() {
		return remainDurationTime;
	}

	int getRemainSum() {
		return remainSumTime;
	}

	int getInterrupt() {
		return interruptTime;
	}

	Time getNextTime() {
		return nextTime;
	}


	void countDown() {
		remainDurationTime--;
		remainSumTime--;
	}


};



Time currentTime;

RegulationTime reguTime;




int inputPassword()
{
	string pass;
	bool isParent = true;
	

	cout << "pass: ";

	while(true)
	{
		if(pass.length() == 17){
			system("cls");
			cout << "\nPassword too long. Please try again!\n";
			break;
		}
		char x = _getch();
		if(x == 13) break;
		cout << "*";
		pass.push_back(x);
	}
	cout << endl;

	//getline(cin, pass);
	int count = 1;
	if (pass == BAME) {
		return 1;
	}

	reguTime.from.hour = 9;
	reguTime.from.minute = 40;
	reguTime.to.hour = 11;
	reguTime.to.minute = 10;
	reguTime.duration = 15;
	reguTime.sumTime = 50;
	reguTime.interrupt = 10;
	
	
	currentTime.hour = 10;
	currentTime.minute = 30;

	// sau nay se thay bang ham inUseTime():
	if (currentTime < reguTime.from || currentTime > reguTime.to) {
		return 0;	// 0: khong trong khoang thoi gian duoc su dung
	}

	while (count < 3) {
		if (pass == TREEM) break;
		else {
			
			pass.clear();
			count++;
			cout << "pass: ";
			while(true)
			{
				if(pass.length() == 17){
					system("cls");
					cout << "\nPassword too long. Please try again!" << endl;
					break;
				}
			char x = _getch();
			if(x == 13) break;
			cout << "*";
			pass.push_back(x);
			}
			cout << endl;
			//getline(cin, pass);
		}
	}

	if (count < 3) return -1;	// dung pass tre em
	return -2; // sai pass tre em

}

Time getTime(){
	Time t;
	time_t now = time(0);
	tm *ltm = localtime(&now);
	t.hour = 1 + ltm->tm_hour;
	t.minute = 1 + ltm->tm_min;
	return t;
}





int main()
{
	
	int status;
	int lastCheck = 0;
	do {
		if (lastCheck % 60 == 0) {
			if (lastCheck == 60) {
				cout << "check again nhaa:" << endl << endl;
				lastCheck == 0;
			}
			
			status = inputPassword();
			

			Time nextTime;
			nextTime.hour = 12;
			nextTime.minute = 10;

			switch (status)
			{
			case 1:		// parent
				cout << "parent" << endl;
				lastCheck++;
				break;
			case 0:		// khong trong thoi gian su dung:
				cout << "ko duoc dung" << endl;
				break;
			case -1:		// nhap dung pass tre em:
			{
				Children tre = Children(20, 30, reguTime, nextTime);
				while (tre.getRemainDuration() > 0 && tre.getRemainSum() > 0) {
					cout << "tre dang dung may" << endl;
					cout << "thoi gian con lai: " << tre.getRemainDuration() << endl;
					cout << "tong thoi gian con lai: " << tre.getRemainSum() << endl;
					cout << endl;

					if (tre.getRemainDuration() == 1 || tre.getRemainSum() == 1)
					{
						cout << "1 phut nua tat may" << endl;
					}
					Sleep(2000);
					tre.countDown();
				}
			}
			break;
			default:
				break;
			}
		}
		Sleep(1000);
		lastCheck++;
	} while (status == 1);

	//==========================================Dong==========================================


	return 0;
}