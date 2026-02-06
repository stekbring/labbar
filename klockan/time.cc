#define CATCH_CONFIG_RUNNER
#include "time.h"
#include <stdexcept>
#include <sstream>

using namespace std;

Time::Time(int hour, int minute, int second)
    : hour{hour}, minute{minute}, second{second}
{
    if (second < 0 || second >= 60) 
        throw std::invalid_argument("Du kan ej ha sekunder under 0 eller över 60");

    if (minute < 0 || minute >= 60) 
        throw std::invalid_argument("Du kan ej ha minuter under 0 eller över 60");

    if (hour < 0 || hour >= 24) 
        throw std::invalid_argument("Du kan ej ha timmar under 0 eller över 24");
}

Time::Time(string time_str)
    : hour{0}, minute{0}, second{0}
{
    std::istringstream iss{time_str};

    char trash;

    iss >> hour >> trash >> minute >> trash >> second;

    if (second < 0 || second >= 60) 
        throw std::invalid_argument("Du kan ej ha sekunder under 0 eller över 60");

    if (minute < 0 || minute >= 60) 
        throw std::invalid_argument("Du kan ej ha minuter under 0 eller över 60");

    if (hour < 0 || hour >= 24) 
        throw std::invalid_argument("Du kan ej ha timmar under 0 eller över 24");
}

Time& Time::operator++()
{
    second++;

    if (second >= 60)
    {
        second = 0;
        minute++;
        if (minute >= 60)
        {
            minute = 0;
            hour++;
            
            if (hour >= 24)
            {
                hour = 0;
            }
        }
    }

    return *this;
}

Time Time::operator++(int)
{
    Time temp = *this;
    ++(*this);
    return temp;
}


string Time::to_string(bool am_pm) const
{
    std::ostringstream oss{};

    int temp_hour = hour;
    string suffix = "";

    if (am_pm)
    {
        if (is_am())
        {
            suffix = " am";

            if (temp_hour == 0)
            {
                temp_hour = 12;
            }
        }
        else 
        {
            suffix = " pm";

            if (temp_hour > 12)
            {
                temp_hour = temp_hour - 12;
            }
        }
    }
    
    if (temp_hour < 10) 
    {
        oss << "0"; 
    }
    oss << temp_hour << ":";

    if (minute < 10) 
    {
        oss << "0";
    }
    oss << minute << ":";

    if (second < 10) 
    {
        oss << "0";
    }
    oss << second;

    oss << suffix;

    return oss.str();
}

int Time::get_hour() const
{
    return hour;
}

int Time::get_minute() const
{
    return minute;
}

int Time::get_second() const
{
    return second;
}

bool Time::is_am() const
{
    return hour < 12;
}

bool operator==(Time const& lhs, Time const& rhs)
{
    return (lhs.get_hour() == rhs.get_hour()) &&
           (lhs.get_minute() == rhs.get_minute()) &&
           (lhs.get_second() == rhs.get_second());
}

bool operator!=(Time const& lhs, Time const& rhs)
{
    return !(lhs == rhs);
}

bool operator<(Time const& lhs, Time const& rhs)
{
    if (lhs.get_hour() != rhs.get_hour())
    {
        return lhs.get_hour() < rhs.get_hour();
    }

    if (lhs.get_minute() != rhs.get_minute())
    {
        return lhs.get_minute() < rhs.get_minute();
    }

    return lhs.get_second() < rhs.get_second();
}

bool operator>(Time const& lhs, Time const& rhs)
{
    return rhs < lhs;
}

bool operator<=(Time const& lhs, Time const& rhs)
{
    return !(rhs < lhs);
}

bool operator>=(Time const& lhs, Time const& rhs)
{
    return !(lhs < rhs);
}


std::ostream& operator<<(std::ostream& os, Time const& t)
{
    os << t.to_string();
    
    return os;
}