#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<random>
using namespace std;

class Customer
{
protected:
	int age;
	string gender;
public:
	void setAge(const int& newAge) { age = newAge; }
	int getAge() { return age; }
	void setGender(string newGender) { gender = newGender; }
	string getGender() { return gender; }
};

int main()
{
	ofstream outfile("list.txt", ios_base::out);
	random_device engine1;
	uniform_int_distribution<unsigned> dist1(1, 99);
	random_device engine2;
	uniform_int_distribution<unsigned> dist2(1, 2);
	for (int i = 0; i < 100; ++i)
	{
		int age = dist1(engine1);
		int gender = dist2(engine2);
		if (gender == 1)
		{
			outfile << age << "f\n";
		}
		else if(gender == 2)
		{
			outfile << age << "m\n";
		}
	}

	outfile.close();

	int age;
	string gender;
	vector<Customer>vec;
	int x = 0;
	ifstream datafile("list.txt");
	while (datafile >> age >> gender)
	{
		vec.emplace_back();
		vec[x].setAge(age);
		vec[x].setGender(gender);
		x++;
	}
	datafile.close();

	size_t s = vec.size();
	for (int i = 0; i < s; ++i)
	{
		cout << vec[i].getAge() << "," << vec[i].getGender();
		cout << endl;
	}

	int ageDistribution[20];
	for (int k = 0; k < 20; k++)
	{
		ageDistribution[k] = 0;
	}

	for (int i = 0; i < s; i++)
	{
		int temp = vec[i].getAge() / 10;
		if (vec[i].getGender() == "m")
		{
			temp += 10;
		}
		ageDistribution[temp]++;
	}

	int max = 0;
	int maxId = -1;
	for (int k = 0; k < 20; k++)
	{
		if (max < ageDistribution[k])
		{
			max = ageDistribution[k];
			maxId = k;
		}
	}
	
	if(maxId<10)
	{
		cout << "最も多い層は" << maxId * 10 << "代女性で，その割合は" << 100.0 * max / s << "%です．";
	}
	else
	{
		cout << "最も多い層は" << ( maxId-10) * 10 << "代男性で，その割合は" << 100.0 * max / s << "%です．";
	}
}