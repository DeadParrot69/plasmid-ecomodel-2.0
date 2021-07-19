#include <iostream>
#include <cassert>
#include "simulation.h"


// FREE CLASSES AND FUNCTIONS
enum class events
{
    plasmid_free_birth,
    plasmid_bearing_birth,
    plasmid_free_death,
    plasmid_bearing_death,
    plasmid_loss,
    conjugation
};

// CONSTRUCTOR
Simulation::Simulation(const Parameters& pars, const unsigned long int& seed)
    : m_parameters{pars},
      m_time{0.0},
      m_rng{seed},
      m_n_plasmid_free_cells{m_parameters.init_n_plasmid_free_cells()},
      m_n_plasmid_bearning_cells{m_parameters.init_n_plasmid_bearing_cells()},
      m_current_events_rates{compute_current_events_rates()}
{
}

// MEMBER FUNCTIONS

std::unordered_map<events,double> Simulation::compute_current_events_rates()
{
    std::unordered_map<events,double> rates;
    rates[events::plasmid_free_birth] = (m_parameters.r_0())*(m_n_plasmid_free_cells);

    rates[events::plasmid_bearing_birth] = (m_parameters.r_1())*(m_n_plasmid_bearning_cells);

    rates[events::plasmid_free_death] = ((m_parameters.a_00())*(m_n_plasmid_free_cells)*(m_n_plasmid_free_cells)) + ((m_parameters.a_01())*(m_n_plasmid_free_cells)*(m_n_plasmid_bearning_cells));

    rates[events::plasmid_bearing_death] =((m_parameters.a_11())*(m_n_plasmid_bearning_cells)*(m_n_plasmid_bearning_cells)) + (m_parameters.a_10())*(m_n_plasmid_bearning_cells)*(m_n_plasmid_free_cells);

    rates [events::plasmid_loss] = (m_parameters.lambda())* (m_n_plasmid_bearning_cells);

    rates [events::conjugation] = (m_parameters.c())*(m_n_plasmid_free_cells)*(m_n_plasmid_bearning_cells);

    return rates;
}

void Simulation::set_current_events_rates()
{
    m_current_events_rates = compute_current_events_rates();
}

double Simulation::compute_total_events_rate()
{
    const double rate_tot = (
                m_current_events_rates[events::plasmid_free_birth] +
                m_current_events_rates[events::plasmid_bearing_birth] +
                m_current_events_rates[events::plasmid_free_death]+
                m_current_events_rates[events::plasmid_bearing_death] +
                m_current_events_rates[events::plasmid_loss]+
                m_current_events_rates[events::conjugation]
                );
    return rate_tot;
}


double Simulation::compute_time_to_next_event(const double& rate_tot)
{
    std::exponential_distribution<double> exp(rate_tot);
    return exp(m_rng);
}

events Simulation::draw_event(const double& rate_tot)
{
    double random_number = std::uniform_real_distribution<double>(0.0,rate_tot)(m_rng);
    events this_event;

    //Plasmid free birth
    if ( (random_number) < (m_current_events_rates[events::plasmid_free_birth]) )
    {
        this_event = events::plasmid_free_birth;
        return this_event;
    }
    //plasmid bearing birth
    else if ( (random_number) < (m_current_events_rates[events::plasmid_free_birth] + m_current_events_rates[events::plasmid_bearing_birth]) )
    {
        this_event = events::plasmid_bearing_birth;
        return this_event;
    }


    //plasmid free intra death
    else if ( (random_number) < (m_current_events_rates[events::plasmid_free_birth] + m_current_events_rates[events::plasmid_bearing_birth] +
                                 m_current_events_rates[events::plasmid_free_death]) )
    {
        this_event = events::plasmid_free_death;
        return this_event;
    }



    //plasmid bearing intra death
    else if ( (random_number) < (m_current_events_rates[events::plasmid_free_birth] + m_current_events_rates[events::plasmid_bearing_birth] +
                                 m_current_events_rates[events::plasmid_free_death]+
                                 m_current_events_rates[events::plasmid_bearing_death]) )
    {
        this_event = events::plasmid_bearing_death;
        return this_event;
    }


    //plasmid loss
    else if ( (random_number) < (m_current_events_rates[events::plasmid_free_birth] + m_current_events_rates[events::plasmid_bearing_birth] +
                                 m_current_events_rates[events::plasmid_free_death]+
                                 m_current_events_rates[events::plasmid_bearing_death]+
                                 m_current_events_rates[events::plasmid_loss]

                                 ) )
    {
        this_event = events::plasmid_loss;
        return this_event;
    }


    //conjugation
    else if ( (random_number) < (m_current_events_rates[events::plasmid_free_birth] + m_current_events_rates[events::plasmid_bearing_birth] +
                                 m_current_events_rates[events::plasmid_free_death]+
                                 m_current_events_rates[events::plasmid_bearing_death]+
                                 m_current_events_rates[events::plasmid_loss]+ m_current_events_rates[events::conjugation]

                                 ) )
    {
        this_event = events::conjugation;
        return this_event;
    }

    else {assert(!"Should never get here");}
}

void Simulation::realize_event(const events &event)
{
    switch(event)
    {
    case events::plasmid_free_birth:
        m_n_plasmid_free_cells += m_parameters.dilution_factor();
        break;
    case events::plasmid_bearing_birth:
        m_n_plasmid_bearning_cells += m_parameters.dilution_factor();
        break;
    case events::plasmid_free_death:
        m_n_plasmid_free_cells -= m_parameters.dilution_factor();
        break; 
    case events::plasmid_bearing_death:
        m_n_plasmid_bearning_cells -= m_parameters.dilution_factor();
        break;
    case events::plasmid_loss:
        m_n_plasmid_bearning_cells -= m_parameters.dilution_factor();
        m_n_plasmid_free_cells += m_parameters.dilution_factor();
        break;
    case events::conjugation:
        m_n_plasmid_bearning_cells += m_parameters.dilution_factor();
        m_n_plasmid_free_cells -= m_parameters.dilution_factor();
        break;
    default: assert(!"Should never get here");
    }
}

Results Simulation::run()
{
    Results res;
    {
        res.collect(m_n_plasmid_free_cells, m_n_plasmid_bearning_cells, m_time);
    }

    while (m_time < m_parameters.t_max())
    {
       if ( (m_n_plasmid_free_cells > 0) & (m_n_plasmid_bearning_cells > 0) )
       {
           set_current_events_rates();
           const double rate_tot = compute_total_events_rate();
           const double time_step = compute_time_to_next_event(rate_tot);
           m_time += time_step;
           const events event = draw_event(rate_tot);
           realize_event(event);
           res.collect(m_n_plasmid_free_cells, m_n_plasmid_bearning_cells, m_time);

       }
       else {std::cout << "terminated at time " << m_time << " as one class went extinct" << std::endl; break;}
    }
    return res;
}
