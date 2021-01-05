#include <string>
#include <iostream>
#include <vector>

struct Definition {
    int number_owners{};
    std::vector<char> buf{};

    Definition() : number_owners(1) {}

    explicit Definition(const char * s) : number_owners(1) {
        while (*s) {
            buf.push_back(*s);
            ++s;
        }
    }

    Definition(const Definition *d) : number_owners(1), buf(d->buf) {}

    void push_back(const char * s) {
        while (*s) {
            buf.push_back(*s);
            ++s;
        }
    }

    void push_back(const Definition * d) {
        buf.insert(buf.end(), d->buf.begin(), d->buf.end());
    }
};

class String {
private:
    Definition *data;
public:
    String();

    String(const char *s);

    String(const String &a);

    String &operator=(const char *s);

    String &operator=(const String &a);

    String &operator+=(const char *s);

    String &operator+=(const String &a);

    char operator[](const size_t index) const;

    char &operator[](const size_t index);

    explicit operator std::string();

    ~String();
};

String::String() : data(new Definition{}) {}

String::String(const char *s) : data(new Definition{s}) {}

String::String(const String &a) : data(a.data) {
    data->number_owners++;
}

String &String::operator=(const char *s) {
    if (data->number_owners-- == 1) {
        delete data;
    }
    data = new Definition(s);
    return *this;
}

String &String::operator=(const String &a) {
    if (this == &a) {
        return *this;
    }
    if (data->number_owners-- == 1) {
        delete data;
    }
    data = a.data;
    data->number_owners++;
    return *this;
}

String &String::operator+=(const char *s) {
    if (data->number_owners != 1) {
        data->number_owners--;
        data = new Definition(data);
    }
    data->push_back(s);
    return *this;
}

String &String::operator+=(const String &a) {
    if (data->number_owners != 1) {
        data->number_owners--;
        data = new Definition(data);
    }
    data->push_back(a.data);
    return *this;
}

char String::operator[](const size_t index) const {
    return data->buf[index];
}

char &String::operator[](const size_t index) {
    if (data->number_owners != 1) {
        data->number_owners--;
        data = new Definition(data);
    }
    std::cout<<"lol";
    return data->buf[index];
}

String::~String() {
    if (data->number_owners-- == 1) {
        delete data;
    }
}

String::operator std::string() {
    return {data->buf.begin(), data->buf.end()};
}

int main() {
    String a = "abs";
    String b = a;
    String c = a;
    std::cout<<c[1];
    return 0;
}