/***************************************************************************//**
 * \file SingleBoundary.h
 * \author Anush Krishnan (anus@bu.edu)
 * \author Olivier Mesnard (mesnardo@gwu.edu)
 * \author Pi-Yueh Chuang (pychuang@gwu.edu)
 * \brief Definition of the class `SingleBoundary`.
 */


# pragma once

// STL
# include <string>
# include <memory>
# include <functional>

// here goes PETSc headers
# include <petscsys.h>
# include <petscvec.h>

// here goes headers from our PetIBM
# include "CartesianMesh.h"
# include "Solutions.h"
# include "types.h"


class SingleBoundary
{
public:

    PetscInt            dim;

    types::BCLoc        loc;

    PetscBool           onThisProc;

    std::vector<types::BCType>  type;

    types::RealVec1D    value;

    PetscReal           normal;


    struct IdPairs {PetscInt bcPt; PetscInt ghId; 
        PetscReal area; PetscReal dL; PetscReal a0; PetscReal a1;};


    std::vector<std::vector<IdPairs>>   points;



    SingleBoundary();

    SingleBoundary(const CartesianMesh &mesh, const types::BCLoc &loc); 

    ~SingleBoundary();


    PetscErrorCode init(const CartesianMesh &mesh, const types::BCLoc &loc); 

    std::function<PetscErrorCode(Solutions &, const PetscReal &)> updateCoeffs;

    std::function<PetscErrorCode(Solutions &)> updateGhosts;

protected:

    std::shared_ptr<const MPI_Comm>     comm;

    PetscMPIInt                         mpiSize,
                                        mpiRank;


    std::shared_ptr<const CartesianMesh> mesh;


    std::vector<std::function<
        void(IdPairs &p, const PetscReal &bdValue, const PetscReal &ghValue, 
                const PetscReal &bc, const PetscReal &dt)>>  updateCoeffsKernel;


    PetscErrorCode setProc();

    PetscErrorCode setPoints(const PetscInt &field);

    PetscErrorCode setPointsX(
            const PetscInt &field, const PetscInt &self, const PetscInt &ghost);

    PetscErrorCode setPointsY(
            const PetscInt &field, const PetscInt &self, const PetscInt &ghost);

    PetscErrorCode setPointsZ(
            const PetscInt &field, const PetscInt &self, const PetscInt &ghost);

    PetscErrorCode setKernels(
            const PetscInt &field, const PetscInt &dir);

    PetscErrorCode updateCoeffsTrue(Solutions &soln, const PetscReal &dt);

    PetscErrorCode updateGhostsTrue(Solutions &soln);

private:

};
