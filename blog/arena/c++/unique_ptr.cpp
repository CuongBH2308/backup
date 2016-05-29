#include <memory>
#include <iostream>
using namespace std;

class Demo {
public:
	~Demo() {
		cout << "~Demo" << endl;
	}
	void print() {
		cout << "hello, world" << endl;
	}
};


#include <mutex>
#include <thread>
#include <chrono>

class DeadLock {
	static mutex mtx1;
	static mutex mtx2;

	static void task1() {
		lock_guard<mutex> lck1(mtx1);
		cout << "task1::lock mtx1" << endl;
		this_thread::sleep_for(chrono::seconds(2));
		unique_lock<mutex> lck2(mtx2);
		cout << "task1::lock mtx2" << endl;
		cout << "task1" << endl;
	}

	static void task2() {
		unique_lock<mutex> lck2(mtx2);
		cout << "task2::lock mtx2" << endl;
		this_thread::sleep_for(chrono::seconds(2));
		lock_guard<mutex> lck1(mtx1);
		cout << "task2::lock mtx1" << endl;
		cout << "task2" << endl;
	}

public:
	static void run()
	{
		thread t1(DeadLock::task1);
		thread t2(DeadLock::task2);

		t1.join();
		t2.join();
	}
};

// instanitate static vaiables
mutex DeadLock::mtx1;
mutex DeadLock::mtx2;

int main() {

	bool x;
	int y;
	float z;
	double z2;

	cout << x << y << z << z2 << endl;

	cout << bool() << int() << float() << double() << endl;

	while(true)
		DeadLock::run();

	return 1;

	{
		cout << "Out of scope:" << endl;
		unique_ptr<Demo> up1(new Demo());
	}

	cout << "reset:" << endl;
	unique_ptr<Demo> up2(new Demo());
	up2.reset();

	cout << "assign:" << endl;
	unique_ptr<Demo> up3(new Demo());
	unique_ptr<Demo> up4;
	up4 = std::move(up3);
	up3.reset();
	cout << "lose ownership" << endl;
	up4.reset();

	// You can easily break the unique_ptr by get one's native and assign it to the other
	unique_ptr<Demo> up5(new Demo());
	unique_ptr<Demo> up6(up5.get());

}