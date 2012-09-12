#include<iostream>
#include<string>

using namespace std;

int main()
{
	int QIUser(130);
	string nameUser("James Tombi");
	int& QIref(QIUser);
	bool aGagne;
	int ageUser(16);

 	cout<< "hello world!" << endl << "Vous avez quel age..?" << endl;
	cin >> ageUser;
	cout << "votre age est: " << ageUser << endl;
	cout << "quel est ton nom....?"<< endl;
	string joueur("rien vu");
	getline(cin, joueur);
	//cin >> joueur;
	cout << "tu t'appelles " << joueur << " et ton QI vaut " << QIUser << endl;
	cout << "Par réf " << QIref << endl; 
	return 0;
}
