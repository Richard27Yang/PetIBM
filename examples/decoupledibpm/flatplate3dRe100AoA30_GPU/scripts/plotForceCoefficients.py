"""
Post-processes the force coefficients from a PetIBM simulation.
"""

import os
import numpy
from matplotlib import pyplot


script_dir = os.path.dirname(os.path.realpath(__file__))
root_dir = os.path.dirname(script_dir)

# Read the force coefficients.
filepath = os.path.join(root_dir, 'forces.txt')
with open(filepath, 'r') as infile:
  data = numpy.loadtxt(infile, dtype=numpy.float64, unpack=True)
times, cd, cl = data[:-1]

# Compute the time-averaged force coefficients.
time_limits = (15.0, 20.0)
mask = numpy.where(numpy.logical_and(time_limits[0] <= times,
                                     times <= time_limits[1]))[0]
if mask.size > 0:
  cd_mean, cl_mean = cd[mask].mean(), cl[mask].mean()
  cl_min, cl_max = cl[mask].min(), cl[mask].max()
  print('<Cd> = {:0.4f}'.format(cd_mean))
  print('<Cl> = {:0.4f} ([{:0.4f}, {:0.4f}])'.format(cl_mean, cl_min, cl_max))

# Plot the instantaneous force coefficients.
pyplot.style.use('seaborn-dark')
fig, ax = pyplot.subplots(2, figsize=(10.0, 6.0), sharex=True)
ax[0].grid(zorder=0)
ax[0].set_ylabel('$C_D$', fontname='DejaVu Serif', fontsize=16)
ax[0].plot(times, cd, linewidth=1, zorder=10)
ax[0].set_ylim(0.6, 1.2)
ax[1].grid(zorder=0)
ax[1].set_xlabel('non-dimensional time unit',
                 fontname='DejaVu Serif', fontsize=16)
ax[1].set_ylabel('$C_L$', fontname='DejaVu Serif', fontsize=16)
ax[1].plot(times, cl, linewidth=1, zorder=10)
ax[1].set_xlim(0.0, 20.0)
ax[1].set_ylim(0.6, 1.2)
for a in ax:
  for method in ['get_xticklabels', 'get_yticklabels']:
    for label in getattr(a, method)():
      label.set_fontname('DejaVu Serif')
      label.set_fontsize(14)
fig.tight_layout()

pyplot.show()

# Save the figure.
figures_dir = os.path.join(root_dir, 'figures')
if not os.path.isdir(figures_dir):
  os.makedirs(figures_dir)
filepath = os.path.join(figures_dir, 'forceCoefficients.png')
fig.savefig(filepath)
