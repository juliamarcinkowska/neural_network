#include "header.hpp"
#include <iostream>
#include "gnuplot_i.hpp"

using namespace std;

void getData(string name, vector<vector<double>> &x, vector<vector<double>> &y, int lines)
{
    ifstream data;
    data.open(name, ios::in);
    if (data.good())
    {
        for (int i = 0; i < lines; i++)
        {
            double a, b;
            data >> a >> b;
            x.push_back(vector < double > {a});
            y.push_back(vector < double > {b});
        }
    }

}

void showVectorValues(vector<double> &v)
{
    for(int i=0; i<v.size(); i++)
    {
        cout<<v[i]<<" ";
    }
    cout<<endl;
}

void plot(vector<double> Ox, vector<double> Ox1, vector<double> Oy, vector<double> Oy1)
{
    //system("pause");

    Gnuplot::set_GNUPlotPath(GNUPLOT_PATH);
    Gnuplot main_plot;

    main_plot.set_title( "wykres" );
    main_plot.set_xlabel( "Os x" );
    main_plot.set_ylabel( "Os y" );

    main_plot.set_xrange( -4, 4 ) ;

    main_plot.set_grid();

    main_plot.set_style( "points" );

    main_plot.plot_xy(Ox, Oy, "Punkty poprawne" );
    main_plot.plot_xy(Ox1, Oy1, "Punkty aproksymowane" );
    _sleep(1000000);
}

vector<int> train (vector<vector<double>> &input, vector<double> &result, vector<vector<double>> &desired, Network &net, double &err)
{
    result.clear();
    vector<int> indexes;
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    indexes.reserve(input.size());
    for (int i = 0; i < input.size(); ++i)
        indexes.push_back(i);
    shuffle(begin(indexes), end(indexes), default_random_engine(seed));
    int j=0;
    for (vector<int>::iterator i = indexes.begin(); i != indexes.end(); i++)
    {
        net.feed(input[*i]);
        net.getResults(result);
        net.backPropagation(desired[*i], true);
        err+=net.getError();
    }
    return indexes;
}

vector<int> test (vector<vector<double>> &input, vector<double> &result, vector<vector<double>> &desired, Network &net, double &err)
{
    result.clear();
    vector<int> indexes;
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    indexes.reserve(input.size());
    for (int i = 0; i < input.size(); ++i)
        indexes.push_back(i);
    shuffle(begin(indexes), end(indexes), default_random_engine(seed));
    int j=0;
    for (vector<int>::iterator i = indexes.begin(); i != indexes.end(); i++)
    {
        net.feed(input[*i]);
        net.getResults(result);
 //       net.backPropagation(desired[*i], true);
        err+=net.getError();
    }
    return indexes;
}
