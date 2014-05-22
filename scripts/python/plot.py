#!/usr/bin/env python
import matplotlib
matplotlib.use('Agg')
import sys
import numpy as np
import matplotlib.pyplot as plt
import array
import h5py
import argparse
import os
import errno
sys.path.append(os.path.join(os.environ['PETSC_DIR'],'bin','pythonscripts'))
import PetscBinaryIO

def isNumber(s):
    try:
        float(s)
        return True
    except ValueError:
        return False
        
def mkdir(path, overwrite=False):
	try:
		os.makedirs(path)
	except OSError as exception:
		if exception.errno == errno.EEXIST:
			if not overwrite:
				print "Path '%s' already exists" % path
				return
		else: raise
		
if __name__=="__main__":

	try:
		folder = sys.argv[1]
	except IndexError:
		folder = "cases/cavityRe100"
	
	print "Case folder: " + folder
	
	infoFile = folder + "/simulationInfo.txt"
	
	f = open(infoFile, "r")
	args_list = f.read().split()
	f.close()
	
	fileParser = argparse.ArgumentParser()
	fileParser.add_argument("-nx", type=int, dest="nx", help="number of cells in x-direction", default=32)
	fileParser.add_argument("-ny", type=int, dest="ny", help="number of cells in y-direction", default=32)
	fileParser.add_argument("-nt", type=int, dest="nt", help="number of time steps", default=200)
	fileParser.add_argument("-nsave", type=int, dest="nsave", help="data save stride", default=100)
	fileParser.add_argument("-xperiodic", dest="xperiodic", help="periodicity in x-direction", default="True")
	fileParser.add_argument("-yperiodic", dest="yperiodic", help="periodicity in y-direction", default="False")
	args = fileParser.parse_args(args_list)
	
	nx = args.nx
	ny = args.ny
	xperiodic = True if args.xperiodic.lower()=='true' else False
	yperiodic = True if args.yperiodic.lower()=='true' else False
	Unx, Uny = nx if xperiodic else nx-1, ny
	Vnx, Vny = nx, ny if yperiodic else ny-1
	
	print "Size of U-array: %d x %d" % (Unx, Uny)
	print "Size of V-array: %d x %d" % (Vnx, Vny)

	grid = np.loadtxt(folder+"/grid.txt")
	x = grid[:nx+1]
	y = grid[nx+1:]

	dx = np.zeros(nx)
	dy = np.zeros(ny)
	dx[0:nx] = x[1:nx+1]-x[0:nx]
	dy[0:ny] = y[1:ny+1]-y[0:ny]

	xu = np.zeros(Unx)
	yu = np.zeros(Uny)
	xu[0:Unx] = x[1:Unx+1]
	yu[0:Uny] = 0.5*(y[0:Uny]+y[1:Uny+1])

	xv = np.zeros(Vnx)
	yv = np.zeros(Vny)
	xv[0:Vnx] = 0.5*(x[0:Vnx]+x[1:Vnx+1])
	yv[0:Vny] = y[1:Vny+1]

	mkdir(folder+"/output")
	plt.ioff()
	
	for n in xrange(args.nsave, args.nt+args.nsave, args.nsave):
		
		# U
		
		petscObjs = PetscBinaryIO.PetscBinaryIO().readVec('%s/%07d/qx.dat' % (folder,n))[1:]
		U = petscObjs.reshape((Uny, Unx))
		for j in xrange(Uny):
			U[j,:] = U[j,:]/dy[j]
		
		X, Y = np.meshgrid(xu,yu)
		CS = plt.contour(X, Y, U, levels=np.linspace(-0.5, 1, 16))
		plt.colorbar(CS)
		plt.savefig('%s/output/U%07d.png' % (folder,n))
		plt.clf()

		# V
		
		petscObjs = PetscBinaryIO.PetscBinaryIO().readVec('%s/%07d/qy.dat' % (folder,n))[1:]
		V = petscObjs.reshape((Vny, Vnx))
		for i in xrange(Vnx):
			V[:,i] = V[:,i]/dx[i]
				
		X, Y = np.meshgrid(xv,yv)
		CS = plt.contour(X, Y, V, levels=np.linspace(-0.5, 0.5, 11))
		plt.colorbar(CS)
		plt.savefig('%s/output/V%07d.png' %(folder,n))
		plt.clf()
		
		print 'Plots generated for timestep %d.' % n
	