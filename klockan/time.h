#ifndef TIME_H
#define TIME_H
#include <string>
#include <iostream>

class Time
{
    public:
        Time() = default;
        Time(int hour, int minute, int second);
        Time(std::string time_str);

        int get_hour() const;
        int get_minute() const;
        int get_second() const;
        
        bool is_am() const;
        std::string to_string(bool am_pm = false) const;

        Time& operator++();
        Time operator++(int);

    private:
        int hour{0};
        int minute{0};
        int second{0};
};

bool operator<(Time const& lhs, Time const& rhs);
bool operator>(Time const& lhs, Time const& rhs);
bool operator<=(Time const& lhs, Time const& rhs);
bool operator>=(Time const& lhs, Time const& rhs);
bool operator==(Time const& lhs, Time const& rhs);
bool operator!=(Time const& lhs, Time const& rhs);

std::ostream& operator<<(std::ostream& os, Time const& t);

#endif