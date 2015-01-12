/*
  Copyright 2014 SINTEF ICT, Applied Mathematics.

  This file is part of the Open Porous Media project (OPM).

  OPM is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  OPM is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with OPM.  If not, see <http://www.gnu.org/licenses/>.
*/



#if HAVE_CONFIG_H
#include "config.h"
#endif // HAVE_CONFIG_H

#include <src/AnisotropicEikonal.hpp>
#include <src/grid.h>
#include <src/ErrorMacros.hpp>
#include <boost/filesystem.hpp>
#include <memory>
#include <algorithm>
#include <iostream>
#include <vector>
#include <numeric>
#include <iterator>
#include <fstream>



// ----------------- Main program -----------------
int
main(int argc, char** argv)
try
{
    if (argc != 4) {
        std::cout << "Usage: " << argv[0] << " grid metric startcells\n";
        return EXIT_FAILURE;
    }
    const std::string grid_filename = argv[1];
    const std::string metric_filename = argv[2];
    const std::string startcells_filename = argv[3];

    using namespace Opm;

    // Read grid.
    UnstructuredGrid* grid_ptr = read_grid(grid_filename.c_str());
    const UnstructuredGrid& grid = *grid_ptr;

    // Read metric tensor.
    std::vector<double> metric;
    {
        std::ifstream metric_stream(metric_filename.c_str());
        std::istream_iterator<double> beg(metric_stream);
        std::istream_iterator<double> end;
        metric.assign(beg, end);
        if (int(metric.size()) != grid.number_of_cells*grid.dimensions*grid.dimensions) {
            OPM_THROW(std::runtime_error, "Size of metric field differs from (dim^2 * number of cells).");
        }
    }

    // Read starting cells.
    std::vector<int> startcells;
    {
        std::ifstream start_stream(startcells_filename.c_str());
        std::istream_iterator<int> beg(start_stream);
        std::istream_iterator<int> end;
        startcells.assign(beg, end);
    }


    // Solve eikonal equation.
    std::vector<double> solution;
    AnisotropicEikonal2d ae(grid);
    ae.solve(metric.data(), startcells, solution);

    // Output.
    std::string filename = "eikonal_solution.txt";
    std::ofstream stream(filename.c_str());
    stream.precision(16);
    std::copy(solution.begin(), solution.end(), std::ostream_iterator<double>(stream, "\n"));
}
catch (const std::exception &e) {
    std::cerr << "Program threw an exception: " << e.what() << "\n";
    throw;
}
