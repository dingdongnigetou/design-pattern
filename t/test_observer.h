
#include <functional>
#include "gtest/gtest.h"

#include "../observer/observer.h"

int res_a;
int res_b;
int res_c;

void observerA(int a, int b) { res_a = a+b; }
void observerB(int a, int b) { res_b = a-b; }

void init()
{
	res_a = res_b = res_c = 0;
}

bool TestNotify(int a, int b)
{
	init();
	events<std::function<void(int,int)>> myevent;
	myevent.join(observerA);
	myevent.join(observerB);
	myevent.join([](int a, int b){ res_c = a*b;});

	myevent.notify(a,b); //广播所有观察者

	return true;
}

bool TestDepatch(int a, int b)
{
	init();
	events<std::function<void(int,int)>> myevent;
	myevent.join(observerA);
	auto key_b = myevent.join(observerB);
	myevent.join([](int a, int b){ res_c = a*b;});

	myevent.depatch(key_b);
	myevent.notify(a,b); //广播所有观察者

	return true;
}	

bool TestClear(int a, int b)
{
	init();
	events<std::function<void(int,int)>> myevent;
	myevent.join(observerA);
	myevent.join(observerB);
	myevent.join([](int a, int b){ res_c = a*b;});

	myevent.clear();
	myevent.notify(a,b); //广播所有观察者

	return true;
}

TEST(ObserverTest, Notify) {
	EXPECT_TRUE(TestNotify(1, 2));
	EXPECT_EQ(3, res_a);
	EXPECT_EQ(-1, res_b);
	EXPECT_EQ(2, res_c);
}

TEST(ObserverTest, Depatch) {
	EXPECT_TRUE(TestDepatch(1, 2));
	EXPECT_EQ(3, res_a);
	EXPECT_EQ(0, res_b); // depatch
	EXPECT_EQ(2, res_c);
}

TEST(ObserverTest, Clear) {
	EXPECT_TRUE(TestClear(1, 2));
	EXPECT_EQ(0, res_a);
	EXPECT_EQ(0, res_b); 
	EXPECT_EQ(0, res_c);
}

