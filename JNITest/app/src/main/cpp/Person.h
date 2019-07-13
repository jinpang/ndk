#ifndef JNITEST_PERSON_H
#define JNITEST_PERSON_H

#include <jni.h>
#include <string>

class Person {
private:
    int age;
    std::string username;
    char *nickname;
    long income;
public:
    Person();
    int getAge();
    void setAge(int age);

    long getIncome() const;

    void setIncome(long income);

    std::string getUsername();

    void setUsername(std::string username);

    char *getNickname() const;

    void setNickname(char *nickname);
};


#endif //JNITEST_PERSON_H
