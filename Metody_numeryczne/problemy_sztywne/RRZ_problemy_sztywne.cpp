// imn3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#pragma warning(disable:4996)
#include <iostream>
#include <cmath>
#include <vector>

double dt = 1.0;
double S = 0.75;
int p = 2;
double tmax = 40.0;
int alfa = 5;
double delta = pow(10, -10);
double x0 = 0.01;
double v0 = 0;
auto fun = [](double x, double v) {return alfa * (1 - x * x) * v - x; };

double max(double ex, double ev)
{
    return ex > ev ? ex : ev;
}

std::vector<double> RK2(double x, double v, double dt)
{
    double k1x = v;
    double k1v = alfa * (1 - x * x) * v - x;
    
    double k2x = v + dt * k1v;
    double k2v = fun(x + dt * k1x, v + dt * k1v);

    std::vector<double> res;
    double xnew = x + (dt * (k1x + k2x)) / 2;
    double vnew = v + (dt * (k1v + k2v)) / 2;
    res.push_back(xnew);
    res.push_back(vnew);
    return res;
}

std::vector<double> trapesoid(double x, double v, double dt)
{
    double x1 = x;
    double v1 = v;
    double F, G, a11, a12, a21, a22, dx, dv;

    while (true)
    {
        F = x1 - x - (dt * (v + v1)) / 2;
        G = v1 - v - (dt * (fun(x, v) + fun(x1, v1))) / 2;

        a11 = 1;
        a12 = -dt / 2;
        a21 = (-dt * (-2 * alfa * x1 * v1 - 1))/2;
        a22 = 1 - (dt * alfa * (1 - x1 * x1)) / 2;

        dx = (-F * a22 + G * a12) / (a11 * a22 - a12 * a21);
        dv = (-G * a11 + F * a21) / (a11 * a22 - a12 * a21);
        
        x1 += dx;
        v1 += dv;

        if (abs(dx) < delta && abs(dx) < delta)
            break;

    }
    std::vector<double> res = { x1,v1 };
    return res;
}

int main()
{
    
    

    double Ex, Ev;

    double TOL1 = pow(10, -2);
    double TOL2 = pow(10, -5);
    std::vector<double> TOL = { TOL1,TOL2 };

    std::vector<double> x1;
    std::vector<double> v1;
    std::vector<double> tt;
    std::vector<double> resdt;
    FILE* fp1 = fopen("rk2xt.txt", "w+");
    FILE* fp2 = fopen("rk2vt.txt", "w+");
    FILE* fp3 = fopen("rk2dt.txt", "w+");
    FILE* fp4 = fopen("rk2v.txt", "w+");

    FILE* fp11 = fopen("rk2xt1.txt", "w+");
    FILE* fp22 = fopen("rk2vt2.txt", "w+");
    FILE* fp33 = fopen("rk2dt3.txt", "w+");
    FILE* fp44 = fopen("rk2v4.txt", "w+");

    FILE* fp5 = fopen("trapxt.txt", "w+");
    FILE* fp6 = fopen("trapvt.txt", "w+");
    FILE* fp7 = fopen("trapdt.txt", "w+");
    FILE* fp8 = fopen("trapv.txt", "w+");

    FILE* fp55 = fopen("trapxt1.txt", "w+");
    FILE* fp66 = fopen("trapvt2.txt", "w+");
    FILE* fp77 = fopen("trapdt3.txt", "w+");
    FILE* fp88 = fopen("trapv4.txt", "w+");


    for (double i : TOL)
    {
        std::vector<double> t = { 0 };
        std::vector<double> ddt = { dt,dt };
        std::vector<double> x = { x0 };
        std::vector<double> v = { v0 };

        std::vector<double> resn1;
        std::vector<double> resn2;
        std::vector<double> resn2x1;
        while (true)
        {
            resn1 = RK2(x.back(), v.back(), ddt.back());
            resn2 = RK2(resn1.at(0), resn1.at(1), ddt.back());

            //std::cout << resn1.at(0) << std::endl;

            resn2x1 = RK2(x.back(), v.back(), 2 * ddt.back());

            Ex = (resn2.at(0) - resn2x1.at(0)) / (pow(2, p) - 1);
            Ev = (resn2.at(1) - resn2x1.at(1)) / (pow(2, p) - 1);
            //std::cout << Ex << Ev << std::endl;
            if (max(abs(Ex), abs(Ev)) < i)
            {
                t.push_back(t.back() + 2.0 * ddt.back());
                x.push_back(resn2.at(0));
                v.push_back(resn2.at(1));
                ddt.push_back(ddt.back());
                //std::cout << "aa" << std::endl;
            }
            ddt.back()=(ddt.back() * pow((S * i) / max(abs(Ex), abs(Ev)), 1.0 / (p + 1)));
            //std::cout << ddt.back() << std::endl;
            //std::cout << t.back() << std::endl;
            if (t.back() >= tmax)
            {
                ddt.pop_back();
                break;
            } 
            //std::cout << x.back() << std::endl;
            
        }

        std::cout << "\n\n\n";
        if (i == TOL.at(0))
        {
            for (int i = 0; i < x.size(); i++)
            {
                fprintf(fp1, "%g %g\n", t.at(i), x.at(i));
                fprintf(fp2, "%g %g\n", t.at(i), v.at(i));
                fprintf(fp3, "%g %g\n", t.at(i), ddt.at(i));
                fprintf(fp4, "%g %g\n", x.at(i), v.at(i));
            }
        }
        else
        {
            for (int i = 0; i < x.size(); i++)
            {
            fprintf(fp11, "%g %g\n", t.at(i), x.at(i));
            fprintf(fp22, "%g %g\n", t.at(i), v.at(i));
            fprintf(fp33, "%g %g\n", t.at(i), ddt.at(i));
            fprintf(fp44, "%g %g\n", x.at(i), v.at(i));
            }
        }
        //std::cout << ddt.back() << std::endl;
    }
    





    for (double i : TOL)
    {
        std::vector<double> t = { 0 };
        std::vector<double> ddt = { dt,dt };
        std::vector<double> x = { x0 };
        std::vector<double> v = { v0 };

        std::vector<double> resn1;
        std::vector<double> resn2;
        std::vector<double> resn2x1;
        while (true)
        {
            resn1 = trapesoid(x.back(), v.back(), ddt.back());
            resn2 = trapesoid(resn1.at(0), resn1.at(1), ddt.back());

            //std::cout << resn1.at(0) << std::endl;

            resn2x1 = trapesoid(x.back(), v.back(), 2 * ddt.back());

            Ex = (resn2.at(0) - resn2x1.at(0)) / (pow(2, p) - 1);
            Ev = (resn2.at(1) - resn2x1.at(1)) / (pow(2, p) - 1);
            //std::cout << Ex << Ev << std::endl;
            if (max(abs(Ex), abs(Ev)) < i)
            {
                t.push_back(t.back() + 2.0 * ddt.back());
                x.push_back(resn2.at(0));
                v.push_back(resn2.at(1));
                ddt.push_back(ddt.back());
                //std::cout << "aa" << std::endl;
            }

            ddt.back() = (ddt.back() * pow((S * i) / max(abs(Ex), abs(Ev)), 1.0 / (p + 1)));
            std::cout << ddt.back() << std::endl;
             //std::cout << t.back() << std::endl;
            if (t.back() >= tmax)
            {
                ddt.pop_back();
                break;
            }
            //std::cout << x.back() << std::endl;

        }

        std::cout << "\n\n\n";
        if (i == TOL.at(0))
        {
            for (int i = 0; i < x.size(); i++)
            {
                fprintf(fp5, "%g %g\n", t.at(i), x.at(i));
                fprintf(fp6, "%g %g\n", t.at(i), v.at(i));
                fprintf(fp7, "%g %g\n", t.at(i), ddt.at(i));
                fprintf(fp8, "%g %g\n", x.at(i), v.at(i));
            }
        }
        else
        {
            for (int i = 0; i < x.size(); i++)
            {
                fprintf(fp55, "%g %g\n", t.at(i), x.at(i));
                fprintf(fp66, "%g %g\n", t.at(i), v.at(i));
                fprintf(fp77, "%g %g\n", t.at(i), ddt.at(i));
                fprintf(fp88, "%g %g\n", x.at(i), v.at(i));
            }
        }
        //std::cout << ddt.back() << std::endl;
    }

    
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
