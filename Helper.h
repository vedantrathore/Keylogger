#ifndef HELPER_H
#define HELPER_H

#include <ctime>
#include <string>
#include <sstream>

namespace Helper
{
    template <class T>

    std::string toString(const T &);

    struct DateTime
    {
        DateTime()
        {
            time_t ms;
            time(&ms);

            struct tm *info = localtime(&ms);

            D = info->tm_mday;
            m = info->tm_mon + 1; // Months start from 0
            y = info->tm_year + 1900; // Year from 1990
            M = info->tm_min;
            H = info->tm_hour;
            S = info->tm_sec;
        }

        DateTime(int D, int m, int y, int H, int M, int S) : D(D), m(m), y(y), H(H), M(M), S(S) {}
        DateTime(int D, int m, int y) : D(D), m(m), y(y), H(0), M(0), S(0) {}

        DateTime Now() const
        {
            return DateTime();
        }

        int D, m, y, H, M, S;

        std::string getDateString() const
        {
            return std::string( D < 10 ? "0" : "" ) + toString(D) +
                   std::string( m < 10 ? ".0" : ".") + toString(m) + "." +
                   toString(y);
        }

        std::string getTimeString(const std::string &sep = ":") const
        {
            return std::string(H < 10 ? "0" : "") + toString(H) + sep +
                   std::string(M < 10 ? "0" : "") + toString(M) + sep +
                   std::string(S < 10 ? "0" : "") + toString(S);
        }

        std::string getDateTimeString(const std::string &sep = ":") const
        {
            return getDateString() + " " + getTimeString(sep);
        }
    };

    template <class T>
    std::string toString(const T &e)
    {
        std::ostringstream s;
        s << e;
        return s.str();
    }

    void writeAppLog(const std::string &s)
    {
        std::ofstream file("AppLog.txt", std::ios::app);
        file << "[" << Helper::DateTime().getDateTimeString() << "]" <<
        "\n" << s << std::endl << "\n";
        file.close();
    }

}

#endif // HELPER_H
