#pragma once

#include "TypeTraits.hpp"
#include "_Define.hpp"
#include "String.hpp"

#include <time.h>
#include <wchar.h>

namespace hsd
{
    class time
    {
    private:
        using time_val = tm;
        time_val _time{};
        static constexpr u8 _month_table[] = {
            31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
        };

    protected:
        inline void set_time_value(tm* new_val)
        {
            _time = *new_val;
        }

    public:
        constexpr time()
        {
            _time.tm_mday = 1;
        }

        constexpr u16 get_seconds() const
        {
            return static_cast<u16>(_time.tm_sec);
        }

        constexpr u16 get_minutes() const
        {
            return static_cast<u16>(_time.tm_min);
        }

        constexpr u16 get_hour() const
        {
            return static_cast<u16>(_time.tm_hour);
        }

        constexpr u16 get_month_day() const
        {
            return static_cast<u16>(_time.tm_mday);
        }

        constexpr u16 get_month() const
        {
            return static_cast<u16>(_time.tm_mon);
        }

        constexpr usize get_year() const
        {
            return static_cast<usize>(_time.tm_year) + 1900;
        }

        inline string to_text() const
        {
            return asctime(&_time);
        }

        constexpr void set_seconds(u16 seconds)
        {
            if (seconds < 60)
            {
                using CastToType = decltype(_time.tm_sec);
                _time.tm_sec = static_cast<CastToType>(seconds % 60);
            }
        }

        constexpr void set_minutes(u16 minutes)
        {
            if (minutes < 60)
            {
                using CastToType = decltype(_time.tm_min);
                _time.tm_min = static_cast<CastToType>(minutes % 60);
            }
        }

        constexpr void set_hour(u64 hour)
        {
            if (hour < 24)
            {
                using CastToType = decltype(_time.tm_hour);
                _time.tm_hour = static_cast<CastToType>(hour % 24);
            }
        }

        constexpr void set_month_day(u16 month_day)
        {
            if (month_day < _month_table[get_month()])
            {
                using CastToType = decltype(_time.tm_mday);
                _time.tm_mday = static_cast<CastToType>(month_day);
            }
        }

        constexpr void set_month(u16 month)
        {
            if (month < 12)
            {
                using CastToType = decltype(_time.tm_mon);
                _time.tm_mon = static_cast<CastToType>(month - 1);
            }
        }

        constexpr void set_year(usize year)
        {
            using CastToType = decltype(_time.tm_year);
            _time.tm_year = static_cast<CastToType>(year) - 1900;
        }

        constexpr bool operator==(const time& rhs) const
        {
            return (
                _time.tm_hour  == rhs._time.tm_hour  &&
                _time.tm_isdst == rhs._time.tm_isdst &&
                _time.tm_mday  == rhs._time.tm_mday  &&
                _time.tm_min   == rhs._time.tm_min   &&
                _time.tm_mon   == rhs._time.tm_mon   &&
                _time.tm_sec   == rhs._time.tm_sec   &&
                _time.tm_wday  == rhs._time.tm_wday  &&
                _time.tm_yday  == rhs._time.tm_yday  &&
                _time.tm_year  == rhs._time.tm_year
            );
        }

        constexpr bool operator!=(const time& rhs) const
        {
            return (
                _time.tm_hour  != rhs._time.tm_hour  ||
                _time.tm_isdst != rhs._time.tm_isdst ||
                _time.tm_mday  != rhs._time.tm_mday  ||
                _time.tm_min   != rhs._time.tm_min   ||
                _time.tm_mon   != rhs._time.tm_mon   ||
                _time.tm_sec   != rhs._time.tm_sec   ||
                _time.tm_wday  != rhs._time.tm_wday  ||
                _time.tm_yday  != rhs._time.tm_yday  ||
                _time.tm_year  != rhs._time.tm_year
            );
        }

        constexpr bool operator<(const time& rhs) const
        {
            if (_time.tm_year > rhs._time.tm_year)
            {
                return false;
            }
            else if (_time.tm_year < rhs._time.tm_year)
            {
                return true;
            }
            else if (_time.tm_mon > rhs._time.tm_mon)
            {
                return true;
            }
            else if (_time.tm_mon < rhs._time.tm_mon)
            {
                return false;
            }
            else if (_time.tm_yday > rhs._time.tm_yday)
            {
                return false;
            }
            else if (_time.tm_yday < rhs._time.tm_yday)
            {
                return true;
            }
            else if (_time.tm_mday > rhs._time.tm_mday)
            {
                return false;
            }
            else if (_time.tm_mday < rhs._time.tm_mday)
            {
                return true;
            }
            else if (_time.tm_wday > rhs._time.tm_wday)
            {
                return false;
            }
            else if (_time.tm_wday < rhs._time.tm_wday)
            {
                return true;
            }
            else if (_time.tm_hour > rhs._time.tm_hour)
            {
                return false;
            }
            else if (_time.tm_hour < rhs._time.tm_hour)
            {
                return true;
            }
            else if (_time.tm_min > rhs._time.tm_min)
            {
                return false;
            }
            else if (_time.tm_min < rhs._time.tm_min)
            {
                return true;
            }
            else if (_time.tm_sec > rhs._time.tm_sec)
            {
                return false;
            }
            else if (_time.tm_sec < rhs._time.tm_sec)
            {
                return true;
            }
            else if (_time.tm_isdst > rhs._time.tm_isdst)
            {
                return false;
            }
            else if (_time.tm_isdst < rhs._time.tm_isdst)
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        constexpr bool operator>(const time& rhs) const
        {
            if (_time.tm_year < rhs._time.tm_year)
            {
                return false;
            }
            else if (_time.tm_year > rhs._time.tm_year)
            {
                return true;
            }
            else if (_time.tm_mon < rhs._time.tm_mon)
            {
                return true;
            }
            else if (_time.tm_mon > rhs._time.tm_mon)
            {
                return false;
            }
            else if (_time.tm_yday < rhs._time.tm_yday)
            {
                return false;
            }
            else if (_time.tm_yday > rhs._time.tm_yday)
            {
                return true;
            }
            else if (_time.tm_mday < rhs._time.tm_mday)
            {
                return false;
            }
            else if (_time.tm_mday > rhs._time.tm_mday)
            {
                return true;
            }
            else if (_time.tm_wday < rhs._time.tm_wday)
            {
                return false;
            }
            else if (_time.tm_wday > rhs._time.tm_wday)
            {
                return true;
            }
            else if (_time.tm_hour < rhs._time.tm_hour)
            {
                return false;
            }
            else if (_time.tm_hour > rhs._time.tm_hour)
            {
                return true;
            }
            else if (_time.tm_min < rhs._time.tm_min)
            {
                return false;
            }
            else if (_time.tm_min > rhs._time.tm_min)
            {
                return true;
            }
            else if (_time.tm_sec < rhs._time.tm_sec)
            {
                return false;
            }
            else if (_time.tm_sec > rhs._time.tm_sec)
            {
                return true;
            }
            else if (_time.tm_isdst < rhs._time.tm_isdst)
            {
                return false;
            }
            else if (_time.tm_isdst > rhs._time.tm_isdst)
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        constexpr bool operator<=(const time& rhs) const
        {
            if (_time.tm_year > rhs._time.tm_year)
            {
                return false;
            }
            else if (_time.tm_year < rhs._time.tm_year)
            {
                return true;
            }
            else if (_time.tm_mon > rhs._time.tm_mon)
            {
                return true;
            }
            else if (_time.tm_mon < rhs._time.tm_mon)
            {
                return false;
            }
            else if (_time.tm_yday > rhs._time.tm_yday)
            {
                return false;
            }
            else if (_time.tm_yday < rhs._time.tm_yday)
            {
                return true;
            }
            else if (_time.tm_mday > rhs._time.tm_mday)
            {
                return false;
            }
            else if (_time.tm_mday < rhs._time.tm_mday)
            {
                return true;
            }
            else if (_time.tm_wday > rhs._time.tm_wday)
            {
                return false;
            }
            else if (_time.tm_wday < rhs._time.tm_wday)
            {
                return true;
            }
            else if (_time.tm_hour > rhs._time.tm_hour)
            {
                return false;
            }
            else if (_time.tm_hour < rhs._time.tm_hour)
            {
                return true;
            }
            else if (_time.tm_min > rhs._time.tm_min)
            {
                return false;
            }
            else if (_time.tm_min < rhs._time.tm_min)
            {
                return true;
            }
            else if (_time.tm_sec > rhs._time.tm_sec)
            {
                return false;
            }
            else if (_time.tm_sec < rhs._time.tm_sec)
            {
                return true;
            }
            else if (_time.tm_isdst > rhs._time.tm_isdst)
            {
                return false;
            }
            else if (_time.tm_isdst < rhs._time.tm_isdst)
            {
                return true;
            }
            else
            {
                return true;
            }
        }

        constexpr bool operator>=(const time& rhs) const
        {
            if (_time.tm_year < rhs._time.tm_year)
            {
                return false;
            }
            else if (_time.tm_year > rhs._time.tm_year)
            {
                return true;
            }
            else if (_time.tm_mon < rhs._time.tm_mon)
            {
                return true;
            }
            else if (_time.tm_mon > rhs._time.tm_mon)
            {
                return false;
            }
            else if (_time.tm_yday < rhs._time.tm_yday)
            {
                return false;
            }
            else if (_time.tm_yday > rhs._time.tm_yday)
            {
                return true;
            }
            else if (_time.tm_mday < rhs._time.tm_mday)
            {
                return false;
            }
            else if (_time.tm_mday > rhs._time.tm_mday)
            {
                return true;
            }
            else if (_time.tm_wday < rhs._time.tm_wday)
            {
                return false;
            }
            else if (_time.tm_wday > rhs._time.tm_wday)
            {
                return true;
            }
            else if (_time.tm_hour < rhs._time.tm_hour)
            {
                return false;
            }
            else if (_time.tm_hour > rhs._time.tm_hour)
            {
                return true;
            }
            else if (_time.tm_min < rhs._time.tm_min)
            {
                return false;
            }
            else if (_time.tm_min > rhs._time.tm_min)
            {
                return true;
            }
            else if (_time.tm_sec < rhs._time.tm_sec)
            {
                return false;
            }
            else if (_time.tm_sec > rhs._time.tm_sec)
            {
                return true;
            }
            else if (_time.tm_isdst < rhs._time.tm_isdst)
            {
                return false;
            }
            else if (_time.tm_isdst > rhs._time.tm_isdst)
            {
                return true;
            }
            else
            {
                return true;
            }
        }
    };

    class date
        : private time
    {
    private:
        using time_ptr = tm*;
        time_t _epoch_date;

    public:
        inline date()
            : _epoch_date{::time(nullptr)}
        {
            auto* _date_val = localtime(&_epoch_date);
            set_time_value(_date_val);
        }

        inline date& update()
        {
            auto* _date_val = localtime(&_epoch_date);
            set_time_value(_date_val);

            return *this;
        }

        inline const time& get_time() const
        {
            return *this;
        }
    };

    class clock
    {
    private:
        i64 _clk;

    public:
        inline clock(clock_t clk = ::clock())
        {
            _clk = clk;
        }

        inline clock(const clock& rhs)
            : _clk(rhs._clk)
        {}

        inline clock& operator=(const clock& rhs)
        {
            _clk = rhs._clk;
            return *this;
        }

        inline friend clock operator-(const clock& lhs, const clock& rhs)
        {
            return clock{static_cast<clock_t>(lhs._clk - rhs._clk)};
        }

        inline friend clock operator+(const clock& lhs, const clock& rhs)
        {
            return clock{static_cast<clock_t>(lhs._clk + rhs._clk)};
        }

        inline bool operator==(const clock& rhs) const
        {
            return _clk == rhs._clk;
        }

        inline bool operator!=(const clock& rhs) const
        {
            return _clk != rhs._clk;
        }

        inline bool operator<(const clock& rhs) const
        {
            return _clk < rhs._clk;
        }

        inline bool operator>(const clock& rhs) const
        {
            return _clk > rhs._clk;
        }

        inline bool operator<=(const clock& rhs) const
        {
            return _clk <= rhs._clk;
        }

        inline bool operator>=(const clock& rhs) const
        {
            return _clk >= rhs._clk;
        }

        inline i64 to_microseconds() const
        {
            return static_cast<i64>(to_seconds() * 1000000);
        }

        inline i32 to_miliseconds() const
        {
            return static_cast<i32>(to_seconds() * 1000);
        }

        inline f32 to_seconds() const
        {
            return static_cast<f32>(_clk) / CLOCKS_PER_SEC;
        }

        inline clock restart()
        {
            clock _old_clk{static_cast<clock_t>(_clk)};
            _clk = ::clock();
            return *this - _old_clk;
        }

        inline clock elapsed_time() const
        {
            clock _new_clk;
            return _new_clk - *this;
        }
    };

    class precise_clock
    {
    private:
        timespec _clk;

    public:
        inline precise_clock()
        {
            clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &_clk);
        }

        inline precise_clock(const timespec& clk)
            : _clk{clk}
        {}

        inline precise_clock(const precise_clock& rhs)
            : _clk{rhs._clk}
        {}

        inline precise_clock& operator=(const precise_clock& rhs)
        {
            _clk = rhs._clk;
            return *this;
        }

        inline friend precise_clock operator-(
            const precise_clock& lhs, const precise_clock& rhs)
        {
            if (lhs._clk.tv_nsec - rhs._clk.tv_nsec < 0)
            {
                return timespec {
                    lhs._clk.tv_sec - rhs._clk.tv_sec - 1,
                    lhs._clk.tv_nsec - rhs._clk.tv_nsec + 1'000'000'000  
                };
            }
            else
            {
                return timespec {
                    lhs._clk.tv_sec - rhs._clk.tv_sec,
                    lhs._clk.tv_nsec - rhs._clk.tv_nsec  
                };
            }
        }

        inline friend precise_clock operator+(
            const precise_clock& lhs, const precise_clock& rhs)
        {
            if (lhs._clk.tv_nsec + rhs._clk.tv_nsec >= 1'000'000'000)
            {
                return timespec {
                    lhs._clk.tv_sec + rhs._clk.tv_sec + 1,
                    lhs._clk.tv_nsec + rhs._clk.tv_nsec - 1'000'000'000  
                };
            }
            else
            {
                return timespec {
                    lhs._clk.tv_sec + rhs._clk.tv_sec + 1,
                    lhs._clk.tv_nsec + rhs._clk.tv_nsec
                };
            }
        }

        inline bool operator==(const precise_clock& rhs) const
        {
            return (
                _clk.tv_sec == rhs._clk.tv_sec &&
                _clk.tv_nsec == rhs._clk.tv_nsec
            );
        }

        inline bool operator!=(const precise_clock& rhs) const
        {
            return (
                _clk.tv_sec != rhs._clk.tv_sec ||
                _clk.tv_nsec != rhs._clk.tv_nsec
            );
        }

        inline bool operator<(const precise_clock& rhs) const
        {
            if (_clk.tv_sec < rhs._clk.tv_sec)
            {
                return true;
            }
            else if (_clk.tv_sec > rhs._clk.tv_sec)
            {
                return false;
            }
            else
            {
                return _clk.tv_nsec < rhs._clk.tv_nsec;
            }
        }

        inline bool operator>(const precise_clock& rhs) const
        {
            if (_clk.tv_sec > rhs._clk.tv_sec)
            {
                return true;
            }
            else if (_clk.tv_sec < rhs._clk.tv_sec)
            {
                return false;
            }
            else
            {
                return _clk.tv_nsec > rhs._clk.tv_nsec;
            }
        }

        inline bool operator<=(const precise_clock& rhs) const
        {
            return *this < rhs || *this == rhs;
        }

        inline bool operator>=(const precise_clock& rhs) const
        {
            return *this > rhs || *this == rhs;
        }

        inline u64 to_nanoseconds() const
        {
            if (_clk.tv_sec != 0)
            {
                return static_cast<u64>(to_seconds() * 1'000'000'000);
            }
            else
            {
                return static_cast<u64>(_clk.tv_nsec);
            }
        }

        inline i64 to_microseconds() const
        {
            return static_cast<i64>(to_seconds() * 1'000'000);
        }

        inline i32 to_miliseconds() const
        {
            return static_cast<i32>(to_seconds() * 1000);
        }

        inline f64 to_seconds() const
        {
            return _clk.tv_nsec / 1'000'000'000.0 + 
                static_cast<f64>(_clk.tv_sec);
        }

        inline precise_clock restart()
        {
            precise_clock _old_clk{_clk};
            clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &_clk);
            return *this - _old_clk;
        }

        inline precise_clock elapsed_time() const
        {
            precise_clock _new_clk;
            return _new_clk - *this;
        }
    };

    namespace time_literals
    {
        static consteval time operator""_s(u64 seconds)
        {
            time _new_time{};
            _new_time.set_seconds(seconds);
            return _new_time;
        }

        static consteval time operator""_min(u64 minutes)
        {
            time _new_time{};
            _new_time.set_minutes(minutes);
            return _new_time;
        }

        static consteval time operator""_h(u64 hour)
        {
            time _new_time{};
            _new_time.set_hour(hour);
            return _new_time;
        }

        static consteval time operator""_md(u64 month_day)
        {
            time _new_time{};
            _new_time.set_month_day(month_day);
            return _new_time;
        }

        static consteval time operator""_m(u64 month)
        {
            time _new_time{};
            _new_time.set_month(month);
            return _new_time;
        }

        static consteval time operator""_yr(u64 year)
        {
            time _new_time{};
            _new_time.set_year(year);
            return _new_time;
        }

        static consteval time operator""_dmy(const char* date_format, usize)
        {
            time _new_time{};
            const char* _date_start = date_format;
            char _separator_letter = '.';
            usize _month_day = 0;

            // Day
            {
                // Dot format
                const auto* _day_border = cstring::find(
                    _date_start, _separator_letter
                );

                // Slash format
                if (_day_border == nullptr)
                {
                    // Make sure we are consistent
                    _separator_letter = '/';
                    _day_border = cstring::find(
                        _date_start, _separator_letter
                    );
                }

                // Because we do a month table check after
                _month_day = cstring::parse<usize>(_date_start);
                _date_start = _day_border + 1;
            }

            // Month
            {
                // Dot format
                const auto* _month_border = cstring::find(
                    _date_start, _separator_letter
                );

                _new_time.set_month(
                    cstring::parse<usize>(_date_start)
                );
                
                _new_time.set_month_day(_month_day);
                _date_start = _month_border + 1;
            }

            // Year
            {
                /// Gap for HMS @see line 952
                const auto* _year_border = 
                    cstring::find(_date_start, ' ');

                _new_time.set_year(
                    cstring::parse<usize>(_date_start)
                );
                
                if (_year_border != nullptr)
                    _date_start = _year_border + 1;
            }

            // If we have hours, nimutes and seconds
            if (*(_date_start - 1) == ' ')
            {
                // Hour
                {
                    // Colum format
                    const auto* _hour_border = 
                        cstring::find(_date_start, ':');

                    _new_time.set_hour(
                        cstring::parse<usize>(_date_start)
                    );

                    _date_start = _hour_border + 1;
                }

                // Minutes
                {
                    // Colum format
                    const auto* _min_border = 
                        cstring::find(_date_start, ':');

                    _new_time.set_minutes(
                        cstring::parse<usize>(_date_start)
                    );

                    _date_start = _min_border + 1;
                }

                // Seconds
                {
                    _new_time.set_seconds(
                        cstring::parse<usize>(_date_start)
                    );
                }
            }

            return _new_time;
        }

        static consteval time operator""_mdy(const char* date_format, usize)
        {
            time _new_time{};
            const char* _date_start = date_format;
            char _separator_letter = '.';

            // Month
            {
                // Dot format
                const auto* _month_border = cstring::find(
                    _date_start, _separator_letter
                );

                // Slash format
                if (_month_border == nullptr)
                {
                    // Make sure we are consistent
                    _separator_letter = '/';
                    _month_border = cstring::find(
                        _date_start, _separator_letter
                    );
                }

                _new_time.set_month(
                    cstring::parse<usize>(_date_start)
                );

                _date_start = _month_border + 1;
            }

            // Day
            {
                // Dot format
                const auto* _day_border = cstring::find(
                    _date_start, _separator_letter
                );

                _new_time.set_month_day(
                    cstring::parse<usize>(_date_start)
                );
                
                _date_start = _day_border + 1;
            }

            // Year
            {
                /// Gap for HMS @see line 952
                const auto* _year_border = 
                    cstring::find(_date_start, ' ');

                _new_time.set_year(
                    cstring::parse<usize>(_date_start)
                );
                
                if (_year_border != nullptr)
                    _date_start = _year_border + 1;
            }

            // If we have hours, nimutes and seconds
            if (*(_date_start - 1) == ' ')
            {
                // Hour
                {
                    // Colum format
                    const auto* _hour_border = 
                        cstring::find(_date_start, ':');

                    _new_time.set_hour(
                        cstring::parse<usize>(_date_start)
                    );

                    _date_start = _hour_border + 1;
                }

                // Minutes
                {
                    // Colum format
                    const auto* _min_border = 
                        cstring::find(_date_start, ':');

                    _new_time.set_minutes(
                        cstring::parse<usize>(_date_start)
                    );

                    _date_start = _min_border + 1;
                }

                // Seconds
                {
                    _new_time.set_seconds(
                        cstring::parse<usize>(_date_start)
                    );
                }
            }

            return _new_time;
        }
    } // namespace time_literals
} // namespace hsd