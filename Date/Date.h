
#include "../minghu6.h"

#include <map>

using std::map;
using std::pair;



namespace minghu6{
	//class Date;
	class Date {
	private:
		static map<int, int>months_t;
		static map<int, int> init_months();

		/** fix Feb days (28/29))
		 * leap year months[2]=months[2]-1
		 */
		static map<int, int> real_months(int year); // 

		//map<int, int>months; 

	protected:
		int day;
		int month;
		long year;

	public:

		Date();
		/* Month Day Year*/
		Date(int m, int d, int y);
		Date(Date& date);
		Date(string date);

		map<int, int> real_months();
		void setDate(int m, int d, int y);
		void setDate(Date date);

		/* Year-Month-Day */
		string getDate();

		void setYear(int y) {
			this->year = y;
		}

		void setMonth(int m) {
			this->month = m;
		}

		void setDay(int d) {
			this->day = d;
		}

		int getYear() {
			return this->year;
		}

		int getMonth() {
			return this->month;
		}

		int getDay() {
			return this->day;
		}


		bool isLeapyear() const { //闰年!!
			return isLeapyear(this->year);
		}

		static bool isLeapyear(const int y) {
			return y % 400 ? (y % 100 ? (y % 4 ? false : true) : false) : true;
		}

		//+AD  - BD  公元一年也即公元元年
		long toDays();

		Date operator+(int day);
		
		Date operator+(Date date2);

		Date& operator++(); //preposition
		Date& operator++(int); //postposition  

		Date operator-(int day);
	    Date operator-(Date date2);

		Date& operator--(); //preposition
		Date& operator--(int); //postposition  

		Date& operator+=(int day);
		Date& operator+=(Date &date);
		Date& operator-=(int day);
		Date& operator-=(Date &date);


		bool operator>( Date date);
		bool operator==( Date date);

		bool operator>=(Date date);
		bool operator<(Date date);
		bool operator<=(Date date);

		bool operator!=(Date date);
	};

}

namespace minghu6{
	Date getcurrentDate();
}



