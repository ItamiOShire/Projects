#pragma warning(disable:4996)
#include <iostream>
#include "mgmres.h"

double sq(double val)
{
    return val * val;
}

int j(int l, int nx)
{
    return l / (nx + 1);
}
int i(int l, int nx)
{
    return l - j(l, nx) * (nx + 1);
}
double rho(int x, int y, double delta, double xmax, double ymax, double sigma)
{
    double rho1 = exp(-sq((delta * x - 0.25 * xmax) / sigma) - sq((delta * y - 0.5 * ymax) / sigma));
    double rho2 = -exp(-sq((delta * x - 0.75 * xmax) / sigma) - sq((delta * y - 0.5 * ymax) / sigma));
    return rho1 + rho2;
}

double whatEps(double eps1, double eps2,int l,int nx)
{
    if (i(l, nx) <= nx / 2)
        return eps1;
    else
        return eps2;
}

void poisson(int nx, int ny, double delta, double eps1, double eps2, double v1, double v2, double v3, double v4, bool isRho, bool save, const char fname[])
{
    int N = (nx + 1) * (ny + 1);
    double xmax = delta * nx;
    double ymax = delta * ny;
    double sigma = xmax / 10.0;
    
    auto a = new double[5 * N];
    auto b = new double[N];
    auto v = new double[N];
    auto ia = new int[N + 1];
    auto ja = new int[5*N];
    for (int i = 0; i < 5 * N; i++)
    {
        a[i] = 0;
        ja[i] = 0;
        if (i < N + 1)
            ia[i] = -1;
        if (i < N)
        {
            b[i] = 0;
            v[i] = 0;
        }
    }

    int k = -1;
    int edge;
    double vb;

    for (int l = 0; l < N; l++)
    {
        edge = 0;
        vb = 0;
        if (i(l, nx) == 0)
        {
            edge = 1;
            vb = v1;
        }
        if (j(l, nx) == ny)
        {
            edge = 1;
            vb = v2;
        }
        if (i(l, nx) == nx)
        {
            edge = 1;
            vb = v3;
        }
        if (j(l, nx) == 0)
        {
            edge = 1;
            vb = v4;
        }

        if (edge == 1)
            b[l] = vb;
        else if (isRho)
            b[l] = -rho(i(l, nx), j(l, nx), delta, xmax, ymax, sigma);
        else
            b[l] = 0;

        ia[l] = -1;
        if (l - nx - 1 >= 0 && edge == 0)
        {
            k++;
            if (ia[l] < 0)
                ia[l] = k;
            a[k] = whatEps(eps1, eps2, l, nx) / (delta * delta);
            ja[k] = l - nx - 1;
        }
        if (l - 1 >= 0 && edge == 0)
        {
            k++;
            if (ia[l] < 0)
                ia[l] = k;
            a[k] = whatEps(eps1, eps2, l, nx) / (delta * delta);
            ja[k] = l - 1;
        }
        k++;
        if (ia[l] < 0)
            ia[l] = k;
        if (edge == 0)
            a[k] = -(2 * whatEps(eps1, eps2, l, nx) + whatEps(eps1, eps2, l + 1, nx)
                + whatEps(eps1, eps2, l + nx + 1, nx))/(delta * delta);
        else
            a[k] = 1;
        ja[k] = l;

        if (l < N && edge == 0)
        {
            k++;
            a[k] = whatEps(eps1, eps2, l + 1, nx) / (delta * delta);
            ja[k] = l + 1;
        }

        if (l < N - nx - 1 && edge == 0)
        {
            k++;
            a[k] = whatEps(eps1, eps2, l + nx + 1, nx)/(delta*delta);
            ja[k] = l + nx + 1;
        }
    }
    int nz_num = k + 1;
    ia[N] = nz_num;

    pmgmres_ilu_cr(N, nz_num, ia, ja, a, v, b, 500, 500, pow(10, -8), pow(10, -8));

    if (save)
    {
        FILE* fp1 = fopen("mA.txt", "w");
        for (int l = 0; l < 5 * N; l++)
            fprintf(fp1, "%d %d %d %g\n", l,i(l, nx),j(l, nx), a[l]);
        fclose(fp1);
        FILE* fp2 = fopen("vB.txt", "w");
        for (int l = 0; l < N; l++)
            fprintf(fp2, "%d %d %d %g\n", l, i(l, nx), j(l, nx), b[l]);
        fclose(fp2);
    }
    else
    {
        FILE* fp = fopen(fname, "w");
        double lim = 0;
        for (int l = 0; l < N; l++)
        {
            if (delta * j(l, nx) > lim)
                fprintf(fp, "\n");
            fprintf(fp, "%g %g %g\n", delta* j(l, nx), delta* i(l, nx), v[l]);
            lim = delta * j(l, nx);
        }
        fclose(fp);
    }

}

int main()
{

    poisson(4, 4, 0.1, 1, 1, 10, -10, 10, -10, false, true, "");
    poisson(50, 50, 0.1, 1, 1, 10, -10, 10, -10, false, false, "v_1.txt");
    poisson(100, 100, 0.1, 1, 1, 10, -10, 10, -10, false, false, "v_2.txt");
    poisson(200, 200, 0.1, 1, 1, 10, -10, 10, -10, false, false, "v_3.txt");
    poisson(100, 100, 0.1, 1, 1, 0, 0, 0, 0, true, false, "vRho_1.txt");
    poisson(100, 100, 0.1, 1, 2, 0, 0, 0, 0, true, false, "vRho_2.txt");
    poisson(100, 100, 0.1, 1, 10, 0, 0, 0, 0, true, false, "vRho_3.txt");
    return 0;

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
