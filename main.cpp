#include <iostream>
#include "header.hpp"

using namespace std;

int main()
{
    vector<int> topology;
    int nerNo;
    topology.push_back(1);
    vector<double> resultValues;
    vector<vector<double>>inputValuesTrain1, desiredValuesTrain1, inputValuesTrain2, desiredValuesTrain2, inputValuesTest, desiredValuesTest;
    cout << "Liczba neuronow na warstwie ukrytej (1-20):    ";
    cin >> nerNo;
    topology.push_back(nerNo);
    topology.push_back(1);
    int iteration=0;

    Network net(topology, true);

    double err;
    ofstream error;
    error.open("error15.txt", ios::out);

    getData("approximation_train_1.txt", inputValuesTrain1, desiredValuesTrain1, 81);
    getData("approximation_train_2.txt", inputValuesTrain2, desiredValuesTrain2, 15);
    getData("approximation_test.txt", inputValuesTest, desiredValuesTest, 1000);

    cout << "Trening na zbiorze \n1 - 81 punktow treningowych\n2 - 15 punktow treningowych\n3 - oba zbiory\n";
    int choice;
    cin >> choice;

    do
    {
        err=0.0;
        if (choice == 1)
            train(inputValuesTrain1, resultValues, desiredValuesTrain1, net, err);
        else if (choice == 2)
            train(inputValuesTrain2, resultValues, desiredValuesTrain2, net, err);
        else
        {
            train(inputValuesTrain1, resultValues, desiredValuesTrain1, net, err);
            train(inputValuesTrain2, resultValues, desiredValuesTrain2, net, err);
        }
        if(iteration%100==0)
        {
            if (choice == 1)
                error << iteration << " " << err/inputValuesTrain1.size() << endl;
            else if (choice == 2)
                error << iteration << " " << err/inputValuesTrain2.size() << endl;
            else
                error << iteration << " " << err/96.0 << endl;
            cout << iteration << endl;
        }
        if (choice == 1)
            err/=inputValuesTrain1.size();
        else if (choice == 2)
            err/=inputValuesTrain2.size();
        else
            err/=96.0;
        iteration++;
    }
    //while (iteration < 100000);
    while (err > 0.1);

    cout << "Liczba iteracji to " << iteration << " a blad to " << err << endl;
    vector<double> inputX, inputY;
    err=0.0;
    vector <int> indexes = test(inputValuesTest, resultValues, desiredValuesTest, net, err);

    error.close();

    for (vector<int>::iterator i = indexes.begin(); i != indexes.end(); i++)
    {
        for (int j=0; j<desiredValuesTest[*i].size(); j++)
        {
            inputX.push_back(inputValuesTest[*i][j]);
            inputY.push_back(desiredValuesTest[*i][j]);
        }
    }
    plot(inputX, inputX, inputY, resultValues);
    //system("pause");
    return 0;
}
