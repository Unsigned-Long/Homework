#ifndef INTERPOLATION_OBSERVATION_H
#define INTERPOLATION_OBSERVATION_H

#include <ostream>
#include "cmath"
#include "vector"
#include "iomanip"
#include "fstream"

namespace ns_na {
    struct Observation;
    using Observations = std::vector<Observation>;

    struct Observation {
    public:
        double x{};
        double y{};

    public:
        Observation(double x, double y);

        Observation();

        friend std::ostream &operator<<(std::ostream &os, const Observation &observation);

        static void SaveObservationsToDisk(const std::string &filename, const Observations &observations);
    };

}

#endif //INTERPOLATION_OBSERVATION_H
