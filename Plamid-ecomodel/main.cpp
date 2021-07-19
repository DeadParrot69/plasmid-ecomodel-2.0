// QT creator using c++ 14

#include <iostream>
#include "simulation.h"
#include "parameters.h"
#include "results.h"
#include <random>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <chrono>
#include <string>
#include <iomanip>
#include <utility>

int main()
{

    Parameters pars("pars.txt");       // for now here; then load from file.
    const unsigned long int seed = 80;
    Simulation simu(pars, seed);
    Results res = simu.run();
    save(res, seed, "_filename.csv");

    return 0;
}
