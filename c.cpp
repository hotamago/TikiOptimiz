#include <bits/stdc++.h>
using namespace std;

//-----------------------------------------------//
//                    Matrix                     //
//-----------------------------------------------//
#define ele_maxtrix float
struct Matrix
{
    int n, m;
    vector<vector<ele_maxtrix>> ma;
    Matrix() {}
    Matrix(int _n)
    {
        n = _n;
        m = _n;
        ma = vector<vector<ele_maxtrix>>(n, vector<ele_maxtrix>(m, 0));
    }
    Matrix(int _n, int _m)
    {
        n = _n;
        m = _m;
        ma = vector<vector<ele_maxtrix>>(n, vector<ele_maxtrix>(m, 0));
    }
};
Matrix operator*(Matrix ax, Matrix bx)
{
    if (ax.m != bx.n)
        return Matrix(0, 0);
    Matrix cx = Matrix(ax.n, bx.m);
    for (int i = 0; i < ax.n; i++)
    {
        for (int j = 0; j < bx.m; j++)
        {
            for (int c = 0; c < ax.m; c++)
            {
                cx.ma[i][j] = cx.ma[i][j] + (ax.ma[i][c] * bx.ma[c][j]);
            }
        }
    }
    return cx;
}
void print_matrix(Matrix ax)
{
    for (int i = 0; i < ax.n; i++)
    {
        for (int j = 0; j < ax.m; j++)
        {
            cout << ax.ma[i][j] << " ";
        }
        cout << "\n";
    }
}

//-----------------------------------------------//
//                  Fast random                  //
//-----------------------------------------------//
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// Random interger in [l, r]
int get_rand(int l, int r)
{
    uniform_int_distribution<int> uid(l, r);
    return uid(rng);
}
// Random float in [l, r]
float get_rand(float l, float r)
{
    uniform_real_distribution<float> urd(l, r);
    return urd(rng);
}

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
struct Truck
{
    int p, f, t;
    float c, vol, vel;
    Truck()
    {
        reset_cur();
    }
    Truck(int _p, int _f, int _t, int _c, int _vol, int _vel)
    {
        p = _p;
        f = _f;
        t = _t;
        c = _c;
        vol = _vol;
        vel = _vel;
        reset_cur();
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

    // dinamic value
    int cur_p;
    float cur_c, cur_vol;
    void reset_cur()
    {
        cur_p = p;
        cur_c = 0;
        cur_vol = 0;
    }
    // Function with checking
    bool checkTime(int curTime)
    {
        return (f <= curTime) && (curTime <= t);
    }
    bool checkOrder(Order &order)
    {
        return (cur_c + order.d <= c) && (cur_vol + order.v <= vol);
    }
    void addOrder(Order &order)
    {
        if (checkOrder(order))
        {
            cur_c += order.d;
            cur_vol += order.v;
        }
        else
        {
            throw "Order is too big!";
        }
    }
    int calTimeMove(int distance)
    {
        return ceil(1.0 * distance / vel);
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
    // Function checking
    bool checkTimeIn(int curTime)
    {
        curTime += sp;
        return (ep <= curTime) && (curTime <= lp);
    }
    bool checkTimeOut(int curTime)
    {
        curTime += sd;
        return (ed <= curTime) && (curTime <= ld);
    }
    bool checkHubIn(int curHub)
    {
        return (curHub == s);
    }
    bool checkHubOut(int curHub)
    {
        return (curHub == e);
    }
};

//-----------------------------------------------//
//                   Global data                 //
//-----------------------------------------------//
int m, d[1005][1005];
int k;
Truck truck[1005];
int n;
Order order[1005];

//-----------------------------------------------//
//                  In, out data                 //
//-----------------------------------------------//
void input()
{
    cin >> m;
    for (int i = 1; i <= m; i++)
    {
        for (int j = 1; j <= m; j++)
            cin >> d[i][j];
    }
    cin >> k;
    for (int i = 1; i <= k; i++)
        truck[i].input();
    cin >> n;
    for (int i = 1; i <= n; i++)
        order[i].input();
}

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    input();
    return 0;
}