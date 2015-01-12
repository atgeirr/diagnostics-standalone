function solution = opmEikonal(G, metric, startcells, varargin)
% Compute solution of eikonal equation using opm-core programs.
%
% SYNOPSIS:
%   solution = getOpmEikonal(G, metric, startcells)
%
% REQUIRED PARAMETERS:
%   G          - MRST grid
%   metric     - metric tensor for each cell, of size (n,(d*d)) where
%                n is the number of cells and d is the dimension
%   startcells - cells at which the solution is zero
%
% OPTIONAL PARAMETERS:
%
% RETURNS:
%   solution  - Column vector of values, one row for each cell in the grid.
%
% EXAMPLE:
%

%{
#COPYRIGHT#
%}

%% Write files for grid, flux etc.
curdir = pwd;
datadir = fullfile(curdir, 'data_for_opmEikonal');
[ok, msg] = mkdir(datadir);
if ~ok
   error(msg)
end
gridfilename = fullfile(datadir, 'grid_for_opmEikonal.txt');
writeMRSTGrid(G, gridfilename);
metricfilename = fullfile(datadir, 'metric_for_opmEikonal.txt');
save(metricfilename,'-ascii', '-double', 'metric');
startfilename = fullfile(datadir, 'start_for_opmEikonal.txt');
sf = fopen(startfilename, 'w');
fprintf(sf, '%d', startcells - 1);
fclose(sf);

%% Run the compute_eikonal_from_files program
binary_dir = [pwd,  '/../eikonal-build/'];
binary = [binary_dir, 'compute_eikonal_from_files'];
command = [binary, ' ', gridfilename, ' ', metricfilename, ' ', startfilename];

if mrstVerbose
   disp('Running the command');
   disp(command);

   t0 = tic;
   status = system(command);
   simtime = toc(t0);

   result = [];
else
   t0 = tic;
   [status, result] = system(command);
   simtime = toc(t0);
end

if status ~= 0,
   disp(result);
   error(['Command failed: ''', command, ''''])
end

%% Load the results
solution = load('eikonal_solution.txt');
