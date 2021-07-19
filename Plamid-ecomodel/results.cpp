#include <iostream>
#include <fstream>
#include <cassert>
#include "results.h"

// CONSTRUCTOR

Results::Results()
    : m_time_vec{},
      m_plasmid_free_cell_density_time{},
      m_plasmid_bearing_cell_density_time{}
{

}

// MEMBER FUNCTIONS

void Results::collect(const double plasmid_free, const double plasmid_bearing, const double time)
{
    m_time_vec.push_back(time);
    m_plasmid_free_cell_density_time.push_back(plasmid_free);
    m_plasmid_bearing_cell_density_time.push_back(plasmid_bearing);
}

// Save results to file

void save(const Results& res, const unsigned long int& seed, const std::string& filename)
{
    std::ofstream of("seed_"+std::to_string(seed)+filename);
    of << "Simstep,time , plasmid_free_cell_density, plasmid_bearing_cell_density\n";
    if ( (res.plasmid_free_time().size()) == (res.plasmid_bearing_time().size()) )
    {
        const int size = res.plasmid_free_time().size();
        for (int i = 0; i != size; ++i)
        {
            of << i << ", " << res.time_time()[i] << ", " << res.plasmid_free_time()[i] << ", " << res.plasmid_bearing_time()[i] << "\n";
        }
    }
    else {assert(!"Should never get here");}
}
