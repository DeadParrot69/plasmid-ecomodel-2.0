#ifndef __parameters__
#define __parameters__

#include <iosfwd>
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

class Parameters
{
    public:
    explicit Parameters(
            const std::string parfilename
            );

    double init_n_plasmid_free_cells() const noexcept {return m_init_n_plasmid_free_cells;}
    double init_n_plasmid_bearing_cells() const noexcept {return m_init_n_plasmid_bearing_cells;}
    double t_max() const noexcept {return m_t_max;}
    double dilution_factor() const noexcept {return m_dilution_factor;}
    double r_0() const noexcept {return m_r_0;}
    double r_1() const noexcept {return  m_r_1;}
    double lambda() const noexcept {return m_lambda;}
    double c() const noexcept {return m_c;}
    double a_00() const noexcept {return m_a_00;}
    double a_11() const noexcept {return m_a_11;}
    double a_01() const noexcept {return m_a_01;}
    double a_10() const noexcept {return m_a_10;}

    private:
    std::string m_parfilename;
    double m_init_n_plasmid_free_cells;
    double m_init_n_plasmid_bearing_cells;
    double m_t_max;
    double m_dilution_factor;
    double m_r_0;
    double m_r_1;
    double m_lambda;
    double m_c;
    double m_a_00;
    double m_a_11;
    double m_a_01;
    double m_a_10;

};

#endif
