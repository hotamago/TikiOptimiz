#include <bits/stdc++.h>
using namespace std;

//-----------------------------------------------//
//                   Struck data                 //
//-----------------------------------------------//
int s2i(string s)
{
    int res = 0;
    for (int i = 0; i < (int)s.size(); i++)
    {
        res = res * 10 + (s[i] - '0');
    }
    return res;
}
struct UnixTime
{
    int *time;
    UnixTime(int &_time)
    {
        time = &_time;
    }
    // Overload operator >> for input
    friend istream &operator>>(istream &is, UnixTime &t)
    {
        string stime;
        is >> stime;
        // cout << "st: " << stime << "\n";
        // s have format hh:mm:ss
        int h = s2i(stime.substr(0, 2));
        int m = s2i(stime.substr(3, 2));
        int s = s2i(stime.substr(6, 2));
        *(t.time) = h * 3600 + m * 60 + s;
        return is;
    }
};
struct OrderPay
{
    int id, pd;
    OrderPay() {}
    // Overload operator >> for input
    friend istream &operator>>(istream &is, OrderPay &o)
    {
        UnixTime ut(o.pd);
        is >> o.id >> ut;
        return is;
    }
    // Overload operator << for print
    friend ostream &operator<<(ostream &os, const OrderPay &o)
    {
        os << "Order: (" << o.id << " " << o.pd << ")";
        return os;
    }
};
struct HubOrders
{
    int h, x, ar, de;
    vector<OrderPay> orders;
    HubOrders() {}
    // Overload operator >> for input
    friend istream &operator>>(istream &is, HubOrders &ho)
    {
        UnixTime ut1(ho.ar), ut2(ho.de);
        is >> ho.h >> ho.x >> ut1 >> ut2;
        ho.orders = vector<OrderPay>(ho.x, OrderPay());
        for (int i = 0; i < ho.x; i++)
        {
            is >> ho.orders[i];
        }
        return is;
    }
    // Overload operator << for print
    friend ostream &operator<<(ostream &os, const HubOrders &ho)
    {
        os << "HubOrders: (" << ho.h << " " << ho.x << " " << ho.ar << " " << ho.de << ")";
        for (int i = 0; i < ho.x; i++)
        {
            cout << "   -> " << ho.orders[i] << "\n";
        }
        return os;
    }
};
struct PathGo
{
    int u;
    vector<HubOrders> hubOrders;
    PathGo() {}
    // Overload operator >> for input
    friend istream &operator>>(istream &is, PathGo &ho)
    {
        is >> ho.u;
        ho.hubOrders = vector<HubOrders>(ho.u, HubOrders());
        for (int i = 0; i < ho.u; i++)
        {
            is >> ho.hubOrders[i];
        }
        return is;
    }
    // Overload operator << for print
    friend ostream &operator<<(ostream &os, const PathGo &ho)
    {
        os << "PathGo: (" << ho.u << ")";
        for (int i = 0; i < ho.u; i++)
        {
            cout << "   -> " << ho.hubOrders[i] << "\n";
        }
        return os;
    }
};

struct Truck
{
    int p, f, t;
    float c, vol, vel;
    Truck() {}
    Truck(int _p, int _f, int _t, int _c, int _vol, int _vel)
    {
        p = _p;
        f = _f;
        t = _t;
        c = _c;
        vol = _vol;
        vel = _vel;
    }
    void input()
    {
        UnixTime ut(f), vt(t);
        cin >> p >> ut >> vt >> c >> vol >> vel;
    }
    // Overload operator << for print
    friend ostream &operator<<(ostream &os, const Truck &t)
    {
        os << "Truck: (" << t.p << " " << t.f << " " << t.t << " " << t.c << " " << t.vol << " " << t.vel << ")";
        return os;
    }
    // Function with checking

    void addOrder(Order)
    {
    }
};
struct Order
{
    int s, e;
    float d, v;
    int sp, sd, ep, lp, ed, ld;
    Order() {}
    Order(int _s, int _e, int _d, int _v, int _sp, int _sd, int _ep, int _lp, int _ed, int _ld)
    {
        s = _s;
        e = _e;
        d = _d;
        v = _v;
        sp = _sp;
        sd = _sd;
        ep = _ep;
        lp = _lp;
        ed = _ed;
        ld = _ld;
    }
    void input()
    {
        UnixTime uep(ep), ulp(lp), ued(ed), uld(ld);
        cin >> s >> e >> d >> v >> sp >> sd >> uep >> ulp >> ued >> uld;
    }
    // Overload operator << for print
    friend ostream &operator<<(ostream &os, const Order &o)
    {
        os << "Order: (" << o.s << " " << o.e << " " << o.d << " " << o.v << " " << o.sp << " " << o.sd << " " << o.ep << " " << o.lp << " " << o.ed << " " << o.ld << ")";
        return os;
    }
};

//-----------------------------------------------//
//                   Global data                 //
//-----------------------------------------------//
vector<PathGo> pathGos;

//-----------------------------------------------//
//                    Input data                 //
//-----------------------------------------------//
void input()
{
    pathGos.clear();
    PathGo pathGo;
    cin >> pathGo;
    while (cin >> pathGo)
    {
        pathGos.push_back(pathGo);
    }
}

//-----------------------------------------------//
//                   micro function              //
//-----------------------------------------------//

// Evaluate solution
int caculateScore(int o, int n, int uk, int k, int tt)
{
    return 1000000000 * o / n - 1000000 * uk / k - tt / 1000;
}

//

//-----------------------------------------------//

int main()
{
    freopen("output.txt", "r", stdin);

    input();
    return 0;
}