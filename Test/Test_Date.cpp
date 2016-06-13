#include "Test.h"

#include "../utils.h"

using minghu6::Date;
//using namespace minghu6;

void test_getDate(){
	Date d(6, 5, 1993);
	cout << "d.getDate()    "<<d.getDate()<<endl;

}

void test_add (){
	Date d(6, 5, 1993);
	Date d2(6, 7, 1993);
	cout << "d1+d2:" << endl;
	cout << (d + d2).getDate() << endl;
	cout << d.getDate() << endl;
	cout << (d + 2).getDate() << endl;
	cout << (d + -1).getDate() << endl;
	cout << (d + d2 - d2).getDate() << endl;
	
}

void test_plusplus(){
	Date d(6, 13, 2016);
	cout << (++d).getDate() << endl;
	d++;
	cout << (d).getDate() << endl;
	cout << (--d).getDate() << endl;
	d--;
	cout << (d).getDate() << endl;
}

void test_pluseq(){
	Date d(6, 13, 2016);
	Date d2(8, 28, 2013);
	cout << (d +=20).getDate() << endl;
	cout << (d -= 20).getDate() << endl;

	cout << (d += d2).getDate() << endl;
	cout << (d -= d2).getDate() << endl;

	cout << (d -= d2).toDays() << endl;
}
void test_eq(){
	Date d(6, 13, 2016);
	Date d2(8, 28, 2013);
	cout << "d:" << d.getDate() << "  " << "d2:" << d2.getDate() << endl;
	cout << "d>d2"<<"  "<<(d > d2) << endl;
	cout << "d>=d2" << "  " << (d >= d2) << endl;
	cout << "d==d2" << "  " << (d == d2) << endl;
	cout << "d<d2" << "  " << (d < d2) << endl;
	cout << "d<=d2" << "  " << (d <= d2) << endl;
	cout << "d!=d2" << "  " << (d != d2) << endl;
}
void test_FWD(){
	Date d(6, 13, 2016);
	Date d3 = Date(d.getDate());
	cout << d3.getDate() << endl;
}
int test_date(){
    
	//test_getDate();
	//test_add();
	//test_plusplus();
	//test_pluseq();
	//test_eq();
	test_FWD();
	system("pause");
    return 0;
}

