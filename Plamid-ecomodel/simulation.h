#ifndef __simulation__
#define __simulation__

#include <iosfwd>
#include <random>
#include <unordered_map>
#include "parameters.h"
#include "results.h"

enum class events;

class Simulation
{
    public:
    Simulation(const Parameters& pars, const unsigned long int& seed);

    const Parameters& parameters() const noexcept {return m_parameters;}
    double simulation_time() const noexcept {return m_time;}

    void set_current_events_rates();
    std::unordered_map<events,double> compute_current_events_rates();
    double compute_total_events_rate();
    double compute_time_to_next_event(const double& rate_tot);

    events draw_event(const double& rate_tot);
    void realize_event(const events& event);

    Results run();

    private:
    Parameters m_parameters;
    double m_time;
    std::default_random_engine m_rng;
    double m_n_plasmid_free_cells;
    double m_n_plasmid_bearning_cells;
    std::unordered_map<events,double> m_current_events_rates;
};

#endif
