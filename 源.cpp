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
        return "必修";
    }

    void showDetails() const override {
        cout << "课程名：" << getCourseName() << endl;
        cout << "课程类型：" << getType() << endl;
        cout << "答疑辅导时间：" << tutoringTime << endl;
        cout << "任课老师：" << teacher << endl;
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
        return "选修";
    }

    void showDetails() const override {
        cout << "课程名：" << getCourseName() << endl;
        cout << "课程类型：" << getType() << endl;
        cout << "答疑辅导时间：" << tutoringTime << endl;
        cout << "任课老师：" << teacher << endl;
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
            cout << "您还没有添加任何课程！" << endl;
            return;
        }

        cout << "您的课程列表：" << endl;
        for (const auto& course : courses) {
            course->showDetails();
            cout << endl;
        }
    }
    
    void addTutoringInfo(const string& courseID, const string& info) {
        for (const auto& course : courses) {
            if (course->getCourseID() == courseID) {
                cout << "留言已添加至课程：" << course->getCourseName() << endl;
                // 在此处执行添加留言的操作
                ofstream outputFile(courseID + ".txt", ios::app);
                if (outputFile.is_open()) {
                    outputFile << info << endl;
                    outputFile.close();
                }
                else {
                    cout << "无法打开留言文件！" << endl;
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
            cout << "您还没有选择任何课程！" << endl;
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
                cout << "课程：" << course->getCourseName() << " 的留言信息：" << endl;
                // 在此处执行显示留言信息的操作
                ifstream inputFile(courseID + ".txt");
                if (inputFile.is_open()) {
                    string line;
                    while (getline(inputFile, line)) {
                        cout << line << endl;
                    }
                    inputFile.close();
                }
                else {
                    cout << "无法打开留言文件！" << endl;
                }
                break;
            }
        }
    }
    void addTutoringInfo(const string& courseID, const string& info) {
        for (const auto& course : selectedCourses) {
            if (course->getCourseID() == courseID) {
                cout << "留言已添加至课程：" << course->getCourseName() << endl;
                // 在此处执行添加留言的操作
                ofstream outputFile(courseID + ".txt", ios::app);
                if (outputFile.is_open()) {
                    outputFile << info << endl;
                    outputFile.close();
                }
                else {
                    cout << "无法打开留言文件！" << endl;
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
    cout << "请输入留言信息：";
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

    // 从文件加载教师信息
    ifstream teacherFile(teacherFilename);
    if (teacherFile.is_open()) {
        Teacher teacher("", "");
        while (teacherFile >> teacher) {
            teachers.push_back(teacher);
        }
        teacherFile.close();
    }

    // 从文件加载学生信息
    ifstream studentFile(studentFilename);
    if (studentFile.is_open()) {
        Student student("", "");
        while (studentFile >> student) {
            students.push_back(student);
        }
        studentFile.close();
    }

    // 从文件加载课程信息
    ifstream courseFile(courseFilename);
    if (courseFile.is_open()) {
        string courseID, courseName, courseType, tutoringTime, teacher;
        while (courseFile >> courseID >> courseName >> courseType >> tutoringTime >> teacher) {
            Course* course;
            if (courseType == "必修") {
                course = new BCourse(courseID, courseName, tutoringTime, teacher);
            }
            else if (courseType == "选修") {
                course = new XCourse(courseID, courseName, tutoringTime, teacher);
            }
            else {
                continue; // 忽略无效的课程类型
            }
            courses.push_back(course);
        }
        courseFile.close();
    }
    //调用函数将必修课添加到学生的选课列表中
    addRequiredCoursesToStudents(students, courses);
    // 主循环
    int option;
    string username, password;

    while (true) {
        system("cls");
        cout << "欢迎使用课程管理系统！" << endl;
        cout << "请选择操作类型：" << endl;
        cout << "1. 教师登录" << endl;
        cout << "2. 学生登录" << endl;
        cout << "3. 创建账号" << endl;
        cout << "0. 退出" << endl;
        cout << "请选择操作：";
        cin >> option;

        if (option == 0) {
            break;
        }

        if (option == 1) {
            cout << "请输入用户名：";
            cin >> username;
            cout << "请输入密码：";
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
                cout << "用户名或密码错误！" << endl;
                system("pause");
                continue;
            }

            while (true) {
                system("cls");
                cout << "欢迎，教师 " << currentTeacher->getName() << "！" << endl;
                cout << "请选择操作：" << endl;
                cout << "1. 查看我的课程" << endl;
                cout << "2. 添加课程" << endl;
                cout << "3. 删除课程" << endl;
                cout << "4. 添加留言" << endl;
                cout << "0. 返回" << endl;
                cout << "请选择操作：";
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
                    cout << "请输入课程ID：";
                    cin >> courseID;
                    // 检查课程ID是否已存在
                    bool isCourseIDExists = false;
                    for (const auto& course : courses) {
                        if (course->getCourseID() == courseID) {
                            isCourseIDExists = true;
                            break;
                        }
                    }

                    if (isCourseIDExists) {
                        cout << "课程ID已存在！" << endl;
                        break;
                    }
                    cout << "请输入课程名：";
                    cin >> courseName;
                    cout << "请输入答疑辅导时间：";
                    cin >> tutoringTime;
                    cout << "请输入课程类型（必修/选修）：";
                    cin >> courseType;
                    cout << "请输入任课老师：";
                    cin >> teacher;

                    Course* course;
                    if (courseType == "必修") {
                        course = new BCourse(courseID, courseName, tutoringTime, teacher);
                    }
                    else if (courseType == "选修") {
                        course = new XCourse(courseID, courseName, tutoringTime, teacher);
                    }
                    else {
                        cout << "无效的课程类型！" << endl;
                        break;
                    }

                    currentTeacher->addCourse(course);
                    courses.push_back(course);
                    saveCourses(courseFilename, courses);
                    break;
                }
                case 3: {
                    string courseID;
                    cout << "请输入要删除的课程ID：";
                    cin >> courseID;

                    currentTeacher->deleteCourse(courseID);
                    saveCourses(courseFilename, courses);
                    break;
                }
                case 4: {
                    string courseID, message;
                    cout << "请输入课程ID：";
                    cin >> courseID;
                    cout << "请输入留言信息：";
                    cin >> message;

                    currentTeacher->addTutoringInfo(courseID, message);
                    break;
                }
                default:
                    cout << "无效的操作！" << endl;
                    break;
                }
                system("pause");
            }
        }
        else if (option == 2) {
            cout << "请输入用户名：";
            cin >> username;
            cout << "请输入密码：";
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
                cout << "用户名或密码错误！" << endl;
                system("pause");
                continue;
            }
            
            while (true) {
                system("cls");
                cout << "欢迎，学生 " << currentStudent->getName() << "！" << endl;
                cout << "请选择操作：" << endl;
                cout << "1. 查看已选课程" << endl;
                cout << "2. 查看必修课程" << endl;
                cout << "3. 选择课程" << endl;
                cout << "4. 退选课程" << endl;
                cout << "5. 回答课程答疑" << endl;
                cout << "0. 返回" << endl;
                cout << "请选择操作：";
                cin >> option;

                if (option == 0) {
                    break;
                }

                switch (option) {
                case 1:
                    currentStudent->showSelectedCourses();
                    break;
                case 2: {
                    // 读取课程文件并显示必修课程列表
                    ifstream courseFile(courseFilename);
                    if (courseFile.is_open()) {
                        string courseID, courseName, courseType, tutoringTime, teacher;
                        while (courseFile >> courseID >> courseName >> courseType >> tutoringTime >> teacher) {
                            if (courseType == "必修") {
                                cout << "课程ID：" << courseID << endl;
                                cout << "课程名：" << courseName << endl;
                                cout << "答疑辅导时间：" << tutoringTime << endl;
                                cout << "任课老师：" << teacher << endl;
                                cout << "---------------------------" << endl;
                            }
                        }
                        courseFile.close();
                    }
                    else {
                        cout << "无法打开课程文件！" << endl;
                    }
                    
                }
                    break;
                case 3: {
                    ifstream courseFile(courseFilename);
                    if (courseFile.is_open()) {
                        string courseID, courseName, courseType, tutoringTime, teacher;
                        while (courseFile >> courseID >> courseName >> courseType >> tutoringTime >> teacher) {                           
                            cout << "可选修列表如下"<< endl;
                            if (courseType == "选修") {
                                
                                cout << "课程ID：" << courseID << endl;
                                cout << "课程名：" << courseName << endl;
                                cout << "答疑辅导时间：" << tutoringTime << endl;
                                cout << "任课老师：" << teacher << endl;
                                cout << "---------------------------" << endl;
                            }
                            else {
                                cout << endl;
                            }

                        }
                        courseFile.close();
                    }
                    else {
                        cout << "无法打开课程文件！" << endl;                       
                    }

                    string courseID;
                    cout << "请输入要选择的课程ID：";
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
                        cout << "未找到指定的课程！" << endl;
                    }
                    else {
                        cout << "选课成功！" << endl;
                        currentStudent->showSelectedCourses();  // 显示已选课程
                    }
                    break;
                }
                case 4: {
                    string courseID;
                    cout << "请输入要退选的课程ID：";
                    cin >> courseID;

                    currentStudent->dropCourse(courseID);
                    break;
                }
                case 5: {
                    string courseID;
                    cout << "请输入课程ID：";
                    cin >> courseID;
                    currentStudent->showTutoringInfo(courseID);
                    studentAddMessage(*currentStudent, courseID);
                    break;
                }
                default:
                    cout << "无效的操作！" << endl;
                    break;
                }
                system("pause");
            }
        }
        else if (option == 3) {
            string accountType;
            cout << "请输入账号类型（学生/教师）：" << endl;
            cin >> accountType;

            if (accountType == "学生") {
                string studentName, studentPassword;
                cout << "请输入学生姓名和密码：" << endl;
                cin >> studentName >> studentPassword;
                students.push_back(Student(studentName, studentPassword));
                saveStudents(studentFilename, students);
                cout << "创建学生账号成功" << endl;
            }
            else if (accountType == "教师") {
                string teacherName, teacherPassword;
                cout << "请输入教师姓名和密码：" << endl;
                cin >> teacherName >> teacherPassword;
                teachers.push_back(Teacher(teacherName, teacherPassword));
                saveTeachers(teacherFilename, teachers);
                cout << "创建教师账号成功" << endl;
            }
            else { cout << "无效的账号类型。" << endl;
            }
            system("pause");
        }
        else {
            cout << "无效的身份！" << endl;
        }
    }

    // 保存教师、学生和课程信息到文件
    saveTeachers(teacherFilename, teachers);
    saveStudents(studentFilename, students);
    saveCourses(courseFilename, courses);

    // 释放动态分配的内存
    for (auto& course : courses) {
        delete course;
    }

    return 0;
}
