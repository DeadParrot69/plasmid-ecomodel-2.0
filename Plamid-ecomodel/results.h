#ifndef __results__
#define __results__

#include <iosfwd>
#include <vector>

class Results
{
    public:
    Results();

    void collect(const double plasmid_free, const double plasmid_bearing, const double time);
    std::vector<double>time_time() const {return m_time_vec;}
    std::vector<double> plasmid_free_time() const noexcept {return m_plasmid_free_cell_density_time;}
    std::vector<double> plasmid_bearing_time() const noexcept {return m_plasmid_bearing_cell_density_time;}

    private:
    std::vector<double> m_time_vec;
    std::vector<double> m_plasmid_free_cell_density_time;
    std::vector<double> m_plasmid_bearing_cell_density_time;
};

void save(const Results& res, const unsigned long int& seed, const std::string& filename);

#endif
