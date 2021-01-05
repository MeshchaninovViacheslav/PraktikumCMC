#include <iostream>
#include <string>
#include "boost/date_time/gregorian/gregorian_types.hpp"

using namespace boost::gregorian;

int main() {
    int year, mon, day;
    std::cin >> year >> mon >> day;
    date d(year, -mon, -day);
    long long ans = 0;
    while (std::cin >> year >> mon >> day) {
        date d1 = date(year, -mon, -day);
        date_duration dist = d1 - d;
        ans += abs(dist.days());
        d = d1;
    }
    std::cout << ans << std::endl;
    return 0;
}