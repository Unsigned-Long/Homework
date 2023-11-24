#include "observation.h"

namespace ns_na {

    ns_na::Observation::Observation(double x, double y) : x(x), y(y) {}

    std::ostream &operator<<(std::ostream &os, const Observation &observation) {
        os << "x: " << observation.x << " y: " << observation.y;
        return os;
    }

    void Observation::SaveObservationsToDisk(const std::string &filename, const Observations &observations) {
        std::ofstream file(filename);
        file << std::fixed << std::setprecision(10);
        for (const auto &obv: observations) { file << obv.x << ',' << obv.y << std::endl; }
        file.close();
    }

    Observation::Observation() = default;
}