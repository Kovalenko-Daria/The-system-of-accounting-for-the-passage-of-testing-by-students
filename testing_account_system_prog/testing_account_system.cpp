#include <iostream>
#include <string>
#include <vector>
#include <Windows.h>
using namespace std;

class City; //преждевременное объявление класса "город", чтобы работали дружественные функции

class Test { //класс "тест"
protected:
	string subject; // название предмета, по которому писался тест
	int system; // максимальное количество баллов по тесту
public:
	Test(string subject, int system) : subject(subject), system(system) {}; //конструктор
	string get_subject() { // возвращает названия предмета
		return subject;
	};
	int get_system() { // возвращает максимального количества баллов
		return system;
	};
};

class Grade : public Test { // класс "оценка"
private:
	int ball; // набранное количество баллов
	float percentage; // процент правильных ответов
public:
	Grade(string subject, int ball, int system) : Test(subject, system) { // конструктор
		while ((ball < 0 || ball > system) && ball != -1) {
			cout << "Ошибка ввода данных" << endl << "Убедитесь, что количество баллов не превосходит " << system << endl << "Попробуйте снова: ";
			cin >> ball;
			cout << endl;
		};
		this->ball = ball;
		if (ball == -1) {
			percentage = -1;
		}
		else {
			percentage = (ball * 100) / system;
		};
	};

	float get_percentage() { // возвращает процент правильных ответов
		return percentage;
	};
	int get_ball() { // возвращает количество набранных баллов
		return ball;
	};
	void change_ball(int b) { // измененяет количество баллов по предмету
		ball = b;
		percentage = (ball * 100) / system;
	};
	void show_grade() { // выводит оценку по предмету
		if (percentage != -1) {
			cout << "По предмету " << subject << " набрано " << ball << " из " << system << ", что составляет " << percentage << "%" << endl;
		}
		else {
			cout << "Учащийся не проходил тест по предмету " << subject << endl;
		};
	};
};

class Student { // класс "ученик"
private:
	string name; // имя ученика
	vector <Grade> grades; // оценки ученика
public:
	Student(string name) : name(name) {}; // конструктор
	void add_grade(string subject, int ball, int system) { // добавляет новые оценки
		grades.push_back(Grade(subject, ball, system));
	};
	string get_name() { // возвращает имя ученика
		return name;
	};
	vector <Grade> get_grades() { //возвращает массив с информацией по тестам
		return grades;
	};
	float average_percentage() { // возвращает средний процент прохождение тестов учеником
		int s = 0, a = grades.size();
		for (auto c : grades) {
			if (c.get_percentage() == -1) {
				a -= 1;
			}
			else {
				s += c.get_percentage();
			};
		};
		s = s / a;
		return s;
	};
	bool check_subject(string subject) { //проверяет прохождение теста с таким названием
		for (int i = 0; i < grades.size(); i++) {
			if (subject == grades[i].get_subject()) {
				return 1;
			};
		};
		return 0;
	};
	void change_name(string n) { //изменяет имя
		name = n;
	};
	void all_info() { //выводит информацию обо всех тестах ученика
		cout << name << endl;
		for (int i = 0; i < grades.size(); i++) {
			grades[i].show_grade();
		};
		cout << endl;
	};
	friend void change_student(vector <City>&, int, int, int, int);
};

struct Name_Class { // структура для описания номера класса
	int floor;
	char letter;
};

class Class { //класс "класс"
protected:
	Name_Class name_class; // название класса
	vector <Student> students; // ученики в классе
public:
	Class() {};
	Class(int floor, char letter) { // коструктор
		name_class.floor = floor;
		name_class.letter = letter;
	};
	void add_student(Student student) { // добавить ученика
		students.push_back(student);
	};
	Name_Class get_nameclass() { // возвращает название класса
		return name_class;
	};
	vector <Student> get_students() { // возвращает перечень учеников в классе
		return students;
	};
	int check_student(string name) { // проверить существование ученика в классе
		for (int i = 0; i < students.size(); i++) {
			if (students[i].get_name() == name) {
				return i;
			};
		};
		return -1;
	};
	void delete_stud(int a) { // удалить ученика
		students.erase(students.begin() + a);
	};
	void average_each_subj() { // выводит средний процент прохождения в классе тестов по каждому предмету
		int tot = 0, k = 0;
		float per;
		for (int i = 0; i < students[0].get_grades().size(); i++) {
			for (int j = 0; j < students.size(); j++) {
				if (students[j].get_grades()[i].get_percentage() != -1) {
					k++;
					tot += students[j].get_grades()[i].get_ball();
				};
			};
			if (k != 0) {
				per = tot / k;
				cout << "По предмету " << students[0].get_grades()[i].get_subject()
					<< " средний процент прохождения составляет " << per << "%" << endl;
			};
			k = 0;
			tot = 0;
		};
	};
	void smart_stupid() { // выводит самого умного и самого глупого ученика в классе
		float ma = 0, mi = 100;
		int kma = 0, kmi = 0;
		bool f = 0;
		for (int i = 0; i < students.size(); i++) {
			if (i != 0 && students[i - 1].average_percentage() != students[i].average_percentage()) {
				f = 1;
			};
			if (students[i].average_percentage() == ma) {
				kma++;
			}
			else if (students[i].average_percentage() > ma) {
				ma = students[i].average_percentage();
				kma = 1;
			}
			else if (students[i].average_percentage() == mi) {
				kmi++;
			}
			else {
				mi = students[i].average_percentage();
				kmi = 1;
			};
		};
		if (f) {
			if (kma > 1) {
				cout << "Самые умные ученики класса: " << endl;
			}
			else {
				cout << "Самый умный ученик класса: " << endl;
			};
			for (int i = 0; i < students.size(); i++) {
				if (students[i].average_percentage() == ma) {
					cout << students[i].get_name() << endl;
				};
			};
			if (kmi > 1) {
				cout << "Самые глупые ученики класса: " << endl;
			}
			else {
				cout << "Самый глупый ученик класса: " << endl;
			};
			for (int i = 0; i < students.size(); i++) {
				if (students[i].average_percentage() == mi) {
					cout << students[i].get_name() << endl;
				};
			};
		}
		else {
			cout << "У всех учеников в этом классе одинаковая средняя успеваемость" << endl;
		};
	};
	friend void add_new_test(vector <City>&, int, int, int);
};

class Teacher : public Class { //класс "учитель"
private:
	string name_teacher; // имя классного руководителя
	float rating; // показатель качества обучения
public:
	Teacher(string name, int floor, char letter) : name_teacher(name), Class(floor, letter) {}; //конструктор
	string get_nameteacher() { // возвращает имя классного руководителя
		return name_teacher;
	};
	float get_rating() { // возвращает показатель качества обучения в классе
		int s = 0;
		for (auto c : students) {
			s += c.average_percentage();
		};
		s = s / students.size();
		rating = s;
		return rating;
	};
	void change_name(string n) { // меняет имя классного руководителя
		name_teacher = n;
	};
	void all_info() { // выводит информацию обо всех учениках в классе
		cout << "Класс " << name_class.floor << name_class.letter << endl;
		cout << "Классный руководитель " << name_teacher << endl;
		cout << "Ученики:" << endl;
		for (int i = 0; i < students.size(); i++) {
			students[i].all_info();
		};
		cout << endl;
	};
	friend void change_teacher(vector <City>&, int, int, int);
	friend void change_student(vector <City>&, int, int, int, int);
	friend void delete_student(vector <City>&, int, int, int, int);
};

class School { //класс "школа"
private:
	string name_school; // название школы
	vector <Teacher> teachers; // классы в школе
public:
	School(string name) : name_school(name) {}; //конструктор
	void add_teacher(Teacher teacher) { //добавляет новый класс в школу
		teachers.push_back(teacher);
	};
	string get_school_name() { //возращает название школы
		return name_school;
	};
	vector <Teacher> get_teachers() {  //возвращает перечень классов в школе
		return teachers;
	};
	float total_rating() { // возвращает показатель качества обучения школы
		float su = 0;
		for (int i = 0; i < teachers.size(); i++) {
			su += teachers[i].get_rating();
		};
		return su / teachers.size();
	};
	int check_class(Name_Class clas) { // проверяет существование класса
		for (int i = 0; i < teachers.size(); i++) {
			if (clas.floor == teachers[i].get_nameclass().floor && clas.letter == teachers[i].get_nameclass().letter) {
				return i;
			};
		};
		return -1;
	};
	void delete_clas(int a) { //удалить класс
		teachers.erase(teachers.begin() + a);
	};
	void all_info() { // вывести информацию обо всех классах школы
		cout << "Школа " << name_school << endl;
		for (int i = 0; i < teachers.size(); i++) {
			teachers[i].all_info();
		};
		cout << endl;
	};
	friend void add_new_student(vector <City>&, int, int, int);
	friend void add_new_test(vector <City>&, int, int, int);
	friend void change_teacher(vector <City>&, int, int, int);
	friend void add_new_class(vector <City>&, string, string, int, int);
	friend void change_student(vector <City>&, int, int, int, int);
	friend void delete_student(vector <City>&, int, int, int, int);
};

class City { //класс "город"
private:
	string name_city; // название города
	vector <School> schools; // перечень школ города
public:
	City(string name) : name_city(name) {}; //конструктор
	void add_school(School school) { //добавляет новую школу в город
		schools.push_back(school);
	};
	string get_name() { //возвращает название города
		return name_city;
	};
	vector <School> get_schools() { //возвращает перечень школ города
		return schools;
	};
	float total_rating() { // возвращает показатель качества обучения города
		float su = 0;
		for (int i = 0; i < schools.size(); i++) {
			su += schools[i].total_rating();
		};
		return su / schools.size();
	};
	int check_school(string school) { // проверяет существование школы в городе
		for (int i = 0; i < schools.size(); i++) {
			if (schools[i].get_school_name() == school) {
				return i;
			};
		};
		return -1;
	};
	void delete_school(int a) { //удаляет школу из города
		schools.erase(schools.begin() + a);
	};
	void all_info() { // выводит информацию обо всех школах города
		cout << "Город " << name_city << endl;
		for (int i = 0; i < schools.size(); i++) {
			schools[i].all_info();
		};
		cout << endl;
	};
	friend void add_new_student(vector <City>&, int, int, int);
	friend void add_new_test(vector <City>&, int, int, int);
	friend void change_teacher(vector <City>&, int, int, int);
	friend void add_new_class(vector <City>&, string, string, int, int);
	friend void change_student(vector <City>&, int, int, int, int);
	friend void delete_student(vector <City>&, int, int, int, int);
	friend void delete_class(vector <City>&, int, int, int);
};

int check_city(string city, vector <City>& cathalog) { //проверка существования такого города
	for (int i = 0; i < cathalog.size(); i++) {
		if (cathalog[i].get_name() == city) {
			return i;
		};
	};
	return -1;
};

string del_(string line) { // удаление '_'
	string s;
	for (auto c : line) {
		if (c == '_') {
			s += " ";
		}
		else {
			s += c;
		};
	};
	return s;
};

void add_new_class(vector <City>& cathalog, string city, string school, int a, int b) { // добавление нового класса
	string nameT, nameSt, nameSu;
	vector <string> subjects;
	vector <int> systems;
	char letCl;
	int ball, system, numCl, k;
	cout << endl << "Введите имя классного руководителя: ";
	cin >> nameT;
	nameT = del_(nameT);
	cout << endl << "Введите номер класса: ";
	cin >> numCl;
	cout << endl << "Введите букву класса: ";
	cin >> letCl;
	Teacher t(nameT, numCl, letCl);
	cout << endl << "Введите количество предметов, по которым писались тесты: ";
	cin >> k;
	while (k < 0) {
		cout << endl << "Количество тестов не может быть отрицательным. Попробуйте снова: ";
		cin >> k;
	};
	for (int i = 0; i < k; i++) {
		cout << endl << "#" << i + 1 << " предмет: ";
		cin >> nameSu;
		nameSu = del_(nameSu);
		subjects.push_back(nameSu);
		cout << endl << "Максимальное количество баллов по нему: ";
		cin >> system;
		systems.push_back(system);
	};
	cout << endl << "Введите количество учеников: ";
	cin >> k;
	while (k < 0) {
		cout << endl << "Количество учеников не может быть отрицательным. Попробуйте снова: ";
		cin >> k;
	};
	for (int i = 0; i < k; i++) {
		cout << endl << "Введите имя ученика: ";
		cin >> nameSt;
		nameSt = del_(nameSt);
		Student st(nameSt);
		for (int j = 0; j < subjects.size(); j++) {
			cout << endl << subjects[j];
			cout << endl << "Введите количество набранных баллов (если тест был пропущен, введите '-1'): ";
			cin >> ball;
			st.add_grade(subjects[j], ball, systems[j]);
		};
		t.add_student(st);
	};
	if (a == -1) {
		City c(city);
		School s(school);
		s.add_teacher(t);
		c.add_school(s);
		cathalog.push_back(c);
	}
	else if (a != -1 && b == -1) {
		School s(school);
		s.add_teacher(t);
		cathalog[a].add_school(s);
	}
	else {
		cathalog[a].schools[b].add_teacher(t);
	};
};

void add_new_student(vector <City>& cathalog, int a, int b, int c) { //добавление нового ученика
	string nameSt;
	int ball;
	cout << endl << "Введите имя ученика: ";
	cin >> nameSt;
	nameSt = del_(nameSt);
	while (cathalog[a].get_schools()[b].get_teachers()[c].check_student(nameSt) != -1) {
		cout << endl << "Такой ученик уже есть в классе. Введите другое имя: ";
		cin >> nameSt;
		nameSt = del_(nameSt);
	};
	Student st(nameSt);
	for (int j = 0; j < cathalog[a].get_schools()[b].get_teachers()[c].get_students()[0].get_grades().size(); j++) {
		cout << endl << cathalog[a].get_schools()[b].get_teachers()[c].get_students()[0].get_grades()[j].get_subject();
		cout << endl << "Введите количество набранных баллов (если тест был пропущен, введите '-1'): ";
		cin >> ball;
		st.add_grade(cathalog[a].get_schools()[b].get_teachers()[c].get_students()[0].get_grades()[j].get_subject(), ball,
			cathalog[a].get_schools()[b].get_teachers()[c].get_students()[0].get_grades()[j].get_system());
	};
	cathalog[a].schools[b].teachers[c].add_student(st);
};

void add_new_test(vector <City>& cathalog, int a, int b, int c) { //добавление нового теста
	string nameSub;
	int system, ball;
	cout << "Предмет, по которому проходился тест: ";
	cin >> nameSub;
	nameSub = del_(nameSub);
	while (cathalog[a].get_schools()[b].get_teachers()[c].get_students()[0].check_subject(nameSub)) {
		cout << endl << "Такой тест уже добавлен. Введите другой предмет: ";
		cin >> nameSub;
		nameSub = del_(nameSub);
	};
	cout << endl << "Максимальное количество баллов по нему: ";
	cin >> system;
	for (int i = 0; i < cathalog[a].get_schools()[b].get_teachers()[c].get_students().size(); i++) {
		cout << "Ученик " << cathalog[a].get_schools()[b].get_teachers()[c].get_students()[i].get_name() << " набрал(если тест был пропущен, введите '-1'): ";
		cin >> ball;
		cout << endl;
		cathalog[a].schools[b].teachers[c].students[i].add_grade(nameSub, ball, system);
	};
};

void show_all(vector <City>& cathalog) { // вывод всей информации в системе
	for (int j = 0; j < cathalog.size(); j++) {
		cathalog[j].all_info();
	};
};

void change_teacher(vector <City>& cathalog, int a, int b, int c) { //смена имени учителя
	string n;
	cout << "Введите имя преподавателя: ";
	cin >> n;
	n = del_(n);
	cout << endl;
	cathalog[a].schools[b].teachers[c].change_name(n);
};

void change_student(vector <City>& cathalog, int a, int b, int c, int d) { //изменение имени/баллов ученика
	int n, ball;
	cout << "Введите цифру нужного варианта: " << endl;
	cout << "1. Изменить имя" << endl;
	cout << "2. Изменить баллы по тесту" << endl;
	cin >> n;
	while (n != 1 && n != 2) {
		cout << "Ошибочный номер. Попробуйте снова: ";
		cin >> n;
		cout << endl;
	};
	if (n == 1) {
		string name;
		cout << "Введите новое имя: ";
		cin >> name;
		name = del_(name);
		cout << endl;
		cathalog[a].schools[b].teachers[c].students[d].change_name(name);
	}
	else {
		if (cathalog[a].schools[b].teachers[c].students[d].grades.size() != 0) {
			for (int j = 0; j < cathalog[a].get_schools()[b].get_teachers()[c].get_students()[0].get_grades().size(); j++) {
				cout << "#" << j + 1 << " " << cathalog[a].get_schools()[b].get_teachers()[c].get_students()[0].get_grades()[j].get_subject() << endl;
			};
			cout << "Выберите номер предмета, по которому нужно изменить баллы: ";
			cin >> n;
			while (n < 1 || n > cathalog[a].schools[b].teachers[c].students[d].grades.size()) {
				cout << "Ошибочный номер. Попробуйте снова: ";
				cin >> n;
				cout << endl;
			};
			cout << "Максимальное количество баллов по этому тесту " << cathalog[a].schools[b].teachers[c].students[d].grades[n - 1].get_system() << endl;
			cout << "Введите новое количество баллов: ";
			cin >> ball;
			while (ball > cathalog[a].schools[b].teachers[c].students[d].grades[n - 1].get_system() || ball < -1) {
				if (ball < -1) {
					cout << "Количество баллов не может быть отрицательным. Попробуйте снова: ";
				}
				else {
					cout << "Количество баллов не может превосходить максимальное. Попробуйте снова: ";
				};
				cin >> ball;
			};
			cathalog[a].schools[b].teachers[c].students[d].grades[n - 1].change_ball(ball);
		}
		else {
			cout << "Нет информации о тестах этого ученика" << endl;
		};
	};
};

void delete_student(vector <City>& cathalog, int a, int b, int c, int d) { //удаление ученика
	cathalog[a].schools[b].teachers[c].delete_stud(d);
	if (cathalog[a].schools[b].teachers[c].get_students().size() == 0) {
		delete_class(cathalog, a, b, c);
	};
};

void delete_class(vector <City>& cathalog, int a, int b, int c) { //удаление класса
	cathalog[a].schools[b].delete_clas(c);
	if (cathalog[a].schools[b].get_teachers().size() == 0) {
		cathalog[a].delete_school(b);
		if (cathalog[a].get_schools().size() == 0) {
			cathalog.erase(cathalog.begin() + a);
		};
	};
};

void show_student(vector <City>& cathalog, int a, int b, int c, int d) { //вывод статистических данных об ученике
	float ind = cathalog[a].get_schools()[b].get_teachers()[c].get_students()[d].average_percentage();
	float tot = cathalog[a].get_schools()[b].get_teachers()[c].get_rating();
	cathalog[a].get_schools()[b].get_teachers()[c].get_students()[d].all_info();
	cout << "Средняя успеваемость ученика по школьной программе составляет: ";
	cout << ind << "%" << endl;
	if (ind > tot) {
		cout << "Средняя успеваемость ученика по программе выше, чем в классе на " << ind - tot << "%" << endl;
	}
	else if (ind == tot) {
		cout << "Средняя успеваемость ученика по программе равна успеваемости класса" << endl;
	}
	else {
		cout << "Средняя успеваемость ученика по программе ниже, чем в классе на " << tot - ind << "%" << endl;
	};
};

void show_class(vector <City>& cathalog, int a, int b, int c) { //вывод статистических данных о классе
	cathalog[a].get_schools()[b].get_teachers()[c].average_each_subj();
	cout << "Средняя успеваемость класса по школьной программе составляет: ";
	cout << cathalog[a].get_schools()[b].get_teachers()[c].get_rating() << "%" << endl;
	if (cathalog[a].get_schools()[b].get_teachers()[c].get_students().size() > 1) {
		cathalog[a].get_schools()[b].get_teachers()[c].smart_stupid();
	};
};

void enter(vector <City>& cathalog, int n) {
	int b = -1, c = -1, numCl, d = -1, e = -1;
	char letCl;
	bool f = true;
	string city, school, nameS;
	Name_Class name;
	cout << "Введите название города: ";
	cin >> city;
	city = del_(city);
	cout << endl << "Введите название школы: ";
	cin >> school;
	school = del_(school);
	c = check_city(city, cathalog);
	if (n == 1 || n == 11) {
		if (n == 1) {
			if (c != -1) {
				b = cathalog[c].check_school(school);
			}
			add_new_class(cathalog, city, school, c, b);
		};
		if (n == 11) {
			if (c != -1) {
				b = cathalog[c].check_school(school);
			}
			if (c == -1 || b == -1) {
				cout << "Такой школы не существует" << endl;
			}
			else {
				cout << "Средняя успеваемость учеников этой школы: " << cathalog[c].get_schools()[b].total_rating() << "%" << endl;
			};
		};
	}
	else {
		cout << endl << "Введите номер класса: ";
		cin >> numCl;
		cout << endl << "Введите букву класса: ";
		cin >> letCl;
		name.floor = numCl;
		name.letter = letCl;
		if (c != -1) {
			b = cathalog[c].check_school(school);
			if (b != -1) {
				d = cathalog[c].get_schools()[b].check_class(name);
				if (d != -1) {
					f = false;
				}
			}
		};
		if (n == 2 || n == 3 || n == 4 || n == 7 || n == 10) {
			if (n == 2) {
				if (f) {
					cout << "Такого класса не существует. Чтобы добавить ученика, создайте сначала класс" << endl;
				}
				else {
					add_new_student(cathalog, c, b, d);
				};
			};
			if (n == 3) {
				if (f) {
					cout << "Такого класса не существует. Чтобы добавить тест, создайте сначала класс" << endl;
				}
				else {
					add_new_test(cathalog, c, b, d);
				};
			};
			if (n == 4) {
				if (f) {
					cout << "Такого класса не существует" << endl;
				}
				else {
					change_teacher(cathalog, c, b, d);
				};
			};
			if (n == 7) {
				if (f) {
					cout << "Такого класса не существует" << endl;
				}
				else {
					delete_class(cathalog, c, b, d);
				};
			};
			if (n == 10) {
				if (f) {
					cout << "Такого класса не существует" << endl;
				}
				else {
					show_class(cathalog, c, b, d);
				};
			};
		}
		else {
			cout << endl << "Введите имя ученика: ";
			cin >> nameS;
			nameS = del_(nameS);
			if (d != -1) {
				e = cathalog[c].get_schools()[b].get_teachers()[d].check_student(nameS);
				if (e != -1) {
					f = false;
				};
			};
			if (f) {
				cout << "Такого ученика не существует" << endl;
			}
			else if (n == 5) {
				change_student(cathalog, c, b, d, e);
			}
			else if (n == 6) {
				delete_student(cathalog, c, b, d, e);
			}
			else if (n == 9) {
				show_student(cathalog, c, b, d, e);
			};
		};
	};
};

bool menu(vector <City>& cathalog) {
	int a, b = -1, c, numCl, d, e;
	char letCl;
	bool f = true;
	string city, school, nameS;
	Name_Class name;
	cout << "1. Добавить новый класс и оценки его учеников по тестам" << endl;
	cout << "2. Добавить нового ученика и его оценки по тестам" << endl;
	cout << "3. Добавить информацию по пройденному классом тесту" << endl;
	cout << "4. Изменить имя преподавателя" << endl;
	cout << "5. Изменить данные по ученику" << endl;
	cout << "6. Удалить ученика" << endl;
	cout << "7. Удалить класс" << endl;
	cout << "8. Вывести всю информацию" << endl;
	cout << "9. Получить информацию об ученике" << endl;
	cout << "10. Получить информацию о классе" << endl;
	cout << "11. Получить информацию о школе" << endl;
	cout << "12. Получить информацию о городе" << endl;
	cout << "13. Выход" << endl;
	cout << "Введите цифру нужного варианта: ";
	cin >> a;
	cout << endl;
	switch (a) {
	case 1: //1. Добавить новый класс и оценки его учеников по тестам
		enter(cathalog, 1);
		return true;
	case 2: //2. Добавить нового ученика и его оценки по тестам
		enter(cathalog, 2);
		return true;
	case 3: //3. Добавить информацию по пройденному классом тесту
		enter(cathalog, 3);
		return true;
	case 4: //4. Изменить имя преподавателя
		enter(cathalog, 4);
		return true;
	case 5: //5. Изменить данные по ученику
		enter(cathalog, 5);
		return true;
	case 6: //6. Удалить ученика
		enter(cathalog, 6);
		return true;
	case 7: //7. Удалить класс
		enter(cathalog, 7);
		return true;
	case 8: //8. Вывести всю информацию
		show_all(cathalog);
		return true;
	case 9: //9. Получить информацию об ученике
		enter(cathalog, 9);
		return true;
	case 10: //10. Получить информацию о классе
		enter(cathalog, 10);
		return true;
	case 11: //11. Получить информацию о школе
		enter(cathalog, 11);
		return true;
	case 12: //12. Получить информацию о городе
		cout << "Введите название города: ";
		cin >> city;
		city = del_(city);
		c = check_city(city, cathalog);
		if (c == -1) {
			cout << "Такого города не существует" << endl;
		}
		else {
			cout << "Средняя успеваемость учеников этого города: " << cathalog[c].total_rating() << "%" << endl;
		};
		return true;
	case 13: //13. Выход
		return false;
	default:
		cout << "Ошибочный номер. Попробуйте снова " << endl;
		return true;
	};
};

int main()
{
	vector <City> cathalog;
	bool f = 1;
	system("color F0");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "Russian");
	cout << "Добро пожаловать в систему учета прождения тестирования обучающихся!" << endl << endl;
	cout << "Перед началом работы с системой, ознакомьтесь с правилами:" << endl;
	cout << "1. Если в одной строке вводятся несколько слов через пробел, то необходимо вместо пробела ставить знак '_'" << endl;
	cout << "2. При создании нового класса нужно ввести минимум одного ученика" << endl;
	cout << "3. При начале работы с системой необходимо выбрать пункт 1 в меню" << endl;
	cout << endl << "Переход к работе с системой" << endl << endl;
	while (f) {
		f = menu(cathalog);
	};
	cout << "F I N I S H";
}