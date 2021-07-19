#include <iostream>
#include <cassert>
#include "parameters.h"
#include <string>
#include <iostream>
#include <random>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <chrono>
#include <string>
#include <iomanip>
#include <utility>

// CONSTRUCTOR
Parameters::Parameters(
     std::string parfilename
        )
    : m_parfilename{parfilename}

{
    std::ifstream ifs(m_parfilename);
    if (!ifs.is_open()) { std::cerr << "Unable to open parfile " <<m_parfilename  << '\n'; exit(EXIT_FAILURE); }
     for (;;) {
       std::string parId;
       ifs >> parId;
       if (ifs.good()) {
         if (parId == "init_n_plasmid_free_cells") { ifs >>  m_init_n_plasmid_free_cells; }

         else if (parId == "init_n_plasmid_bearing_cells") { ifs >> m_init_n_plasmid_bearing_cells; }
         else if (parId == "t_max") { ifs >> m_t_max; }
         else if (parId == "dilution_factor") { ifs >> m_dilution_factor; }
         else if (parId == "r_0") { ifs >> m_r_0; }
         else if (parId == "r_1") { ifs >> m_r_1; }
         else if (parId == "lambda") { ifs >> m_lambda; }
         else if (parId == "c") { ifs >> m_c; }
         else if (parId == "a_00") { ifs >> m_a_00; }
         else if (parId == "a_11") { ifs >> m_a_11; }
         else if (parId == "a_01") { ifs >> m_a_01; }
         else if (parId == "a_10") { ifs >> m_a_10; }

         else { std::cerr << "unknown parname in file"; exit(EXIT_FAILURE); }

       }
       else break;
     }

    assert( m_init_n_plasmid_free_cells >= 0.0 );
    assert( m_init_n_plasmid_bearing_cells >= 0.0 );
    assert( m_t_max > 0.0 );
    assert( (m_dilution_factor > 0.0) & (m_dilution_factor <= 1.0) );
    assert( (m_r_0 >= 0.0) & (m_r_0 <= 1.0) );
    assert( (m_r_1 >= 0.0 ) & (m_r_1 <= 1.0) );
    assert( (m_lambda >= 0.0) & (m_lambda <= 1.0) );
    assert( (m_c >= 0.0) & (m_c <= 1.0) );
    assert( (m_a_00 >= 0.0) & (m_a_00 <= 1.0) );
    assert( (m_a_11 >= 0.0) & (m_a_11 <= 1.0) );
    assert( (m_a_00 >= 0.0) & (m_a_00 <= 1.0) );
    assert( (m_a_01 >= 0.0) & (m_a_01 <= 1.0) );
    assert( (m_a_10 >= 0.0) & (m_a_10 <= 1.0) );
}
