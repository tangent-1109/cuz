#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

class Course {
protected:
    string courseID;
    string courseName;
    string tutoringTime;
   
public:
    Course(const string& id, const string& name, const string& time)
        : courseID(id), courseName(name), tutoringTime(time) {}

    virtual string getType() const = 0;
    virtual void showDetails() const = 0;
  
    string getCourseID() const {
        return courseID;
    }

    string getCourseName() const {
        return courseName;
    }

    string getTutoringTime() const {
        return tutoringTime;
    }

};

class BCourse : public Course {
private:
    string teacher;

public:
    BCourse(const string& id, const string& name, const string& time, const string& teacherName)
        : Course(id, name, time), teacher(teacherName) {}

    string getType() const override {
        return "����";
    }

    void showDetails() const override {
        cout << "�γ�����" << getCourseName() << endl;
        cout << "�γ����ͣ�" << getType() << endl;
        cout << "���ɸ���ʱ�䣺" << tutoringTime << endl;
        cout << "�ο���ʦ��" << teacher << endl;
    }

    string getTeacher() const {
        return teacher;
    }
};

class XCourse : public Course {
private:
    string teacher;

public:
    XCourse(const string& id, const string& name, const string& time, const string& teacherName)
        : Course(id, name, time), teacher(teacherName) {}

    string getType() const override {
        return "ѡ��";
    }

    void showDetails() const override {
        cout << "�γ�����" << getCourseName() << endl;
        cout << "�γ����ͣ�" << getType() << endl;
        cout << "���ɸ���ʱ�䣺" << tutoringTime << endl;
        cout << "�ο���ʦ��" << teacher << endl;
    }

    string getTeacher() const {
        return teacher;
    }
};

class Teacher {
private:
    string name;
    string password;
    vector<Course*> courses;
    
public:
    Teacher(const string& teacherName, const string& teacherPassword)
        : name(teacherName), password(teacherPassword) {}

    string getName() const {
        return name;
    }

    string getPassword() const {
        return password;
    }
    vector<Course*> getCourseList() const {
        return courses;
    }
    
    void addCourse(Course* course) {
        courses.push_back(course);
    }

    void deleteCourse(const string& courseID) {
        for (auto it = courses.begin(); it != courses.end(); ++it) {
            if ((*it)->getCourseID() == courseID) {
                delete* it;
                courses.erase(it);
                break;
            }
        }
    }

    void searchCourses() const {
        if (courses.empty()) {
            cout << "����û������κογ̣�" << endl;
            return;
        }

        cout << "���Ŀγ��б�" << endl;
        for (const auto& course : courses) {
            course->showDetails();
            cout << endl;
        }
    }
    
    void addTutoringInfo(const string& courseID, const string& info) {
        for (const auto& course : courses) {
            if (course->getCourseID() == courseID) {
                cout << "������������γ̣�" << course->getCourseName() << endl;
                // �ڴ˴�ִ��������ԵĲ���
                ofstream outputFile(courseID + ".txt", ios::app);
                if (outputFile.is_open()) {
                    outputFile << info << endl;
                    outputFile.close();
                }
                else {
                    cout << "�޷��������ļ���" << endl;
                }

                break;
            }
        }
    }

    friend istream& operator>>(istream& input, Teacher& teacher);
};

class Student {
private:
    string name;
    string password;
    vector<Course*> selectedCourses;

public:
    Student(const string& studentName, const string& studentPassword)
        : name(studentName), password(studentPassword) {}

    string getName() const {
        return name;
    }

    string getPassword() const {
        return password;
    }

    void selectCourse(Course* course) {
        selectedCourses.push_back(course);
    }

    void dropCourse(const string& courseID) {
        for (auto it = selectedCourses.begin(); it != selectedCourses.end(); ++it) {
            if ((*it)->getCourseID() == courseID) {
                selectedCourses.erase(it);
                break;
            }
        }
    }

    void showSelectedCourses() const {
        if (selectedCourses.empty()) {
            cout << "����û��ѡ���κογ̣�" << endl;
            return;
        }

        for (const auto& course : selectedCourses) {
            course->showDetails();
            cout << endl;
        }
    }
   
    void showTutoringInfo(const string& courseID) const {
        for (const auto& course : selectedCourses) {
            if (course->getCourseID() == courseID) {
                cout << "�γ̣�" << course->getCourseName() << " ��������Ϣ��" << endl;
                // �ڴ˴�ִ����ʾ������Ϣ�Ĳ���
                ifstream inputFile(courseID + ".txt");
                if (inputFile.is_open()) {
                    string line;
                    while (getline(inputFile, line)) {
                        cout << line << endl;
                    }
                    inputFile.close();
                }
                else {
                    cout << "�޷��������ļ���" << endl;
                }
                break;
            }
        }
    }
    void addTutoringInfo(const string& courseID, const string& info) {
        for (const auto& course : selectedCourses) {
            if (course->getCourseID() == courseID) {
                cout << "������������γ̣�" << course->getCourseName() << endl;
                // �ڴ˴�ִ��������ԵĲ���
                ofstream outputFile(courseID + ".txt", ios::app);
                if (outputFile.is_open()) {
                    outputFile << info << endl;
                    outputFile.close();
                }
                else {
                    cout << "�޷��������ļ���" << endl;
                }

                break;
            }
        }
    }

    friend istream& operator>>(istream& input, Student& student);
};

istream& operator>>(istream& input, Teacher& teacher) {
    input >> teacher.name >> teacher.password;
    return input;
}

istream& operator>>(istream& input, Student& student) {
    input >> student.name >> student.password;
    return input;
}

void saveTeachers(const string& filename, const vector<Teacher>& teachers) {
    ofstream outputFile(filename);

    if (outputFile.is_open()) {
        for (const auto& teacher : teachers) {
            outputFile << teacher.getName() << " " << teacher.getPassword() << endl;
        }
        outputFile.close();
    }
}

void saveStudents(const string& filename, const vector<Student>& students) {
    ofstream outputFile(filename);

    if (outputFile.is_open()) {
        for (const auto& student : students) {
            outputFile << student.getName() << " " << student.getPassword() << endl;
        }
        outputFile.close();
    }
}

void saveCourses(const string& filename, const vector<Course*>& courses) {
    ofstream outputFile(filename);

    if (outputFile.is_open()) {
        for (const auto& course : courses) {
            if (BCourse* bCourse = dynamic_cast<BCourse*>(course)) {
                outputFile << bCourse->getCourseID() << " "
                    << bCourse->getCourseName() << " "
                    << bCourse->getType() << " "
                    << bCourse->getTutoringTime() << " "
                    << bCourse->getTeacher() << endl;
            }
            else if (XCourse* xCourse = dynamic_cast<XCourse*>(course)) {
                outputFile << xCourse->getCourseID() << " "
                    << xCourse->getCourseName() << " "
                    << xCourse->getType() << " "
                    << xCourse->getTutoringTime() << " "
                    << xCourse->getTeacher() << endl;
            }
        }
        outputFile.close();
    }
}
void studentAddMessage(Student& student, string courseID) {
    string message;
    cout << "������������Ϣ��";
    cin >> message;

    student.addTutoringInfo(courseID, message);
}
void addRequiredCoursesToStudents(vector<Student>& students, const vector<Course*>& courses) {
    for (auto& student : students) {
        for (const auto& course : courses) {
            if (BCourse* bCourse = dynamic_cast<BCourse*>(course)) {
                student.selectCourse(bCourse);
            }
        }
    }
}

int main() {
    const string teacherFilename = "teachers.txt";
    const string studentFilename = "students.txt";
    const string courseFilename = "courses.txt";
    vector<Teacher> teachers;
    vector<Student> students;
    vector<Course*> courses;

    // ���ļ����ؽ�ʦ��Ϣ
    ifstream teacherFile(teacherFilename);
    if (teacherFile.is_open()) {
        Teacher teacher("", "");
        while (teacherFile >> teacher) {
            teachers.push_back(teacher);
        }
        teacherFile.close();
    }

    // ���ļ�����ѧ����Ϣ
    ifstream studentFile(studentFilename);
    if (studentFile.is_open()) {
        Student student("", "");
        while (studentFile >> student) {
            students.push_back(student);
        }
        studentFile.close();
    }

    // ���ļ����ؿγ���Ϣ
    ifstream courseFile(courseFilename);
    if (courseFile.is_open()) {
        string courseID, courseName, courseType, tutoringTime, teacher;
        while (courseFile >> courseID >> courseName >> courseType >> tutoringTime >> teacher) {
            Course* course;
            if (courseType == "����") {
                course = new BCourse(courseID, courseName, tutoringTime, teacher);
            }
            else if (courseType == "ѡ��") {
                course = new XCourse(courseID, courseName, tutoringTime, teacher);
            }
            else {
                continue; // ������Ч�Ŀγ�����
            }
            courses.push_back(course);
        }
        courseFile.close();
    }
    //���ú��������޿���ӵ�ѧ����ѡ���б���
    addRequiredCoursesToStudents(students, courses);
    // ��ѭ��
    int option;
    string username, password;

    while (true) {
        system("cls");
        cout << "��ӭʹ�ÿγ̹���ϵͳ��" << endl;
        cout << "��ѡ��������ͣ�" << endl;
        cout << "1. ��ʦ��¼" << endl;
        cout << "2. ѧ����¼" << endl;
        cout << "3. �����˺�" << endl;
        cout << "0. �˳�" << endl;
        cout << "��ѡ�������";
        cin >> option;

        if (option == 0) {
            break;
        }

        if (option == 1) {
            cout << "�������û�����";
            cin >> username;
            cout << "���������룺";
            cin >> password;
            bool isTeacherFound = false;
            Teacher* currentTeacher = nullptr;

            for (auto& teacher : teachers) {
                if (teacher.getName() == username && teacher.getPassword() == password) {
                    isTeacherFound = true;
                    currentTeacher = &teacher;
                    break;
                }
            }

            if (!isTeacherFound) {
                cout << "�û������������" << endl;
                system("pause");
                continue;
            }

            while (true) {
                system("cls");
                cout << "��ӭ����ʦ " << currentTeacher->getName() << "��" << endl;
                cout << "��ѡ�������" << endl;
                cout << "1. �鿴�ҵĿγ�" << endl;
                cout << "2. ��ӿγ�" << endl;
                cout << "3. ɾ���γ�" << endl;
                cout << "4. �������" << endl;
                cout << "0. ����" << endl;
                cout << "��ѡ�������";
                cin >> option;

                if (option == 0) {
                    break;
                }

                switch (option) {
                case 1:
                    currentTeacher->searchCourses();
                    break;
                case 2: {
                    string courseID, courseName, tutoringTime, courseType, teacher;
                    cout << "������γ�ID��";
                    cin >> courseID;
                    // ���γ�ID�Ƿ��Ѵ���
                    bool isCourseIDExists = false;
                    for (const auto& course : courses) {
                        if (course->getCourseID() == courseID) {
                            isCourseIDExists = true;
                            break;
                        }
                    }

                    if (isCourseIDExists) {
                        cout << "�γ�ID�Ѵ��ڣ�" << endl;
                        break;
                    }
                    cout << "������γ�����";
                    cin >> courseName;
                    cout << "��������ɸ���ʱ�䣺";
                    cin >> tutoringTime;
                    cout << "������γ����ͣ�����/ѡ�ޣ���";
                    cin >> courseType;
                    cout << "�������ο���ʦ��";
                    cin >> teacher;

                    Course* course;
                    if (courseType == "����") {
                        course = new BCourse(courseID, courseName, tutoringTime, teacher);
                    }
                    else if (courseType == "ѡ��") {
                        course = new XCourse(courseID, courseName, tutoringTime, teacher);
                    }
                    else {
                        cout << "��Ч�Ŀγ����ͣ�" << endl;
                        break;
                    }

                    currentTeacher->addCourse(course);
                    courses.push_back(course);
                    saveCourses(courseFilename, courses);
                    break;
                }
                case 3: {
                    string courseID;
                    cout << "������Ҫɾ���Ŀγ�ID��";
                    cin >> courseID;

                    currentTeacher->deleteCourse(courseID);
                    saveCourses(courseFilename, courses);
                    break;
                }
                case 4: {
                    string courseID, message;
                    cout << "������γ�ID��";
                    cin >> courseID;
                    cout << "������������Ϣ��";
                    cin >> message;

                    currentTeacher->addTutoringInfo(courseID, message);
                    break;
                }
                default:
                    cout << "��Ч�Ĳ�����" << endl;
                    break;
                }
                system("pause");
            }
        }
        else if (option == 2) {
            cout << "�������û�����";
            cin >> username;
            cout << "���������룺";
            cin >> password;
            bool isStudentFound = false;
            Student* currentStudent = nullptr;

            for (auto& student : students) {
                if (student.getName() == username && student.getPassword() == password) {
                    isStudentFound = true;
                    currentStudent = &student;
                    break;
                }
            }

            if (!isStudentFound) {
                cout << "�û������������" << endl;
                system("pause");
                continue;
            }
            
            while (true) {
                system("cls");
                cout << "��ӭ��ѧ�� " << currentStudent->getName() << "��" << endl;
                cout << "��ѡ�������" << endl;
                cout << "1. �鿴��ѡ�γ�" << endl;
                cout << "2. �鿴���޿γ�" << endl;
                cout << "3. ѡ��γ�" << endl;
                cout << "4. ��ѡ�γ�" << endl;
                cout << "5. �ش�γ̴���" << endl;
                cout << "0. ����" << endl;
                cout << "��ѡ�������";
                cin >> option;

                if (option == 0) {
                    break;
                }

                switch (option) {
                case 1:
                    currentStudent->showSelectedCourses();
                    break;
                case 2: {
                    // ��ȡ�γ��ļ�����ʾ���޿γ��б�
                    ifstream courseFile(courseFilename);
                    if (courseFile.is_open()) {
                        string courseID, courseName, courseType, tutoringTime, teacher;
                        while (courseFile >> courseID >> courseName >> courseType >> tutoringTime >> teacher) {
                            if (courseType == "����") {
                                cout << "�γ�ID��" << courseID << endl;
                                cout << "�γ�����" << courseName << endl;
                                cout << "���ɸ���ʱ�䣺" << tutoringTime << endl;
                                cout << "�ο���ʦ��" << teacher << endl;
                                cout << "---------------------------" << endl;
                            }
                        }
                        courseFile.close();
                    }
                    else {
                        cout << "�޷��򿪿γ��ļ���" << endl;
                    }
                    
                }
                    break;
                case 3: {
                    ifstream courseFile(courseFilename);
                    if (courseFile.is_open()) {
                        string courseID, courseName, courseType, tutoringTime, teacher;
                        while (courseFile >> courseID >> courseName >> courseType >> tutoringTime >> teacher) {                           
                            cout << "��ѡ���б�����"<< endl;
                            if (courseType == "ѡ��") {
                                
                                cout << "�γ�ID��" << courseID << endl;
                                cout << "�γ�����" << courseName << endl;
                                cout << "���ɸ���ʱ�䣺" << tutoringTime << endl;
                                cout << "�ο���ʦ��" << teacher << endl;
                                cout << "---------------------------" << endl;
                            }
                            else {
                                cout << endl;
                            }

                        }
                        courseFile.close();
                    }
                    else {
                        cout << "�޷��򿪿γ��ļ���" << endl;                       
                    }

                    string courseID;
                    cout << "������Ҫѡ��Ŀγ�ID��";
                    cin >> courseID;

                    bool isCourseFound = false;
                    for (auto& course : courses) {
                        if (course->getCourseID() == courseID) {
                            currentStudent->selectCourse(course);
                            isCourseFound = true;
                            break;
                        }
                    }

                    if (!isCourseFound) {
                        cout << "δ�ҵ�ָ���Ŀγ̣�" << endl;
                    }
                    else {
                        cout << "ѡ�γɹ���" << endl;
                        currentStudent->showSelectedCourses();  // ��ʾ��ѡ�γ�
                    }
                    break;
                }
                case 4: {
                    string courseID;
                    cout << "������Ҫ��ѡ�Ŀγ�ID��";
                    cin >> courseID;

                    currentStudent->dropCourse(courseID);
                    break;
                }
                case 5: {
                    string courseID;
                    cout << "������γ�ID��";
                    cin >> courseID;
                    currentStudent->showTutoringInfo(courseID);
                    studentAddMessage(*currentStudent, courseID);
                    break;
                }
                default:
                    cout << "��Ч�Ĳ�����" << endl;
                    break;
                }
                system("pause");
            }
        }
        else if (option == 3) {
            string accountType;
            cout << "�������˺����ͣ�ѧ��/��ʦ����" << endl;
            cin >> accountType;

            if (accountType == "ѧ��") {
                string studentName, studentPassword;
                cout << "������ѧ�����������룺" << endl;
                cin >> studentName >> studentPassword;
                students.push_back(Student(studentName, studentPassword));
                saveStudents(studentFilename, students);
                cout << "����ѧ���˺ųɹ�" << endl;
            }
            else if (accountType == "��ʦ") {
                string teacherName, teacherPassword;
                cout << "�������ʦ���������룺" << endl;
                cin >> teacherName >> teacherPassword;
                teachers.push_back(Teacher(teacherName, teacherPassword));
                saveTeachers(teacherFilename, teachers);
                cout << "������ʦ�˺ųɹ�" << endl;
            }
            else { cout << "��Ч���˺����͡�" << endl;
            }
            system("pause");
        }
        else {
            cout << "��Ч����ݣ�" << endl;
        }
    }

    // �����ʦ��ѧ���Ϳγ���Ϣ���ļ�
    saveTeachers(teacherFilename, teachers);
    saveStudents(studentFilename, students);
    saveCourses(courseFilename, courses);

    // �ͷŶ�̬������ڴ�
    for (auto& course : courses) {
        delete course;
    }

    return 0;
}
