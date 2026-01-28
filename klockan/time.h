#ifndef TIME_H
#define TIME_H
#include <string>

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

    private:
        int hour;
        int minute;
        int second;
};

#endif