/**
 * \file singleboundaryperiodic.h
 * \brief Definition of the class `SingleBoundaryPeriodic`.
 * \copyright Copyright (c) 2016-2018, Barba group. All rights reserved.
 * \license BSD 3-Clause License.
 */


# pragma once

// here goes headers from our PetIBM
# include <petibm/singleboundary.h>


namespace petibm
{
namespace boundary
{

/**
 * \brief An implementation of SingleBoundaryBase for periodic BC.
 * \see boundaryModule, petibm::type::SingleBoundary, petibm::boundary::createSingleBoundary
 * \ingroup boundaryModule
 * 
 * PETSc will handle periodic BCs for us, so this is just a trivial implementation 
 * to keep consistency.
 */
class SingleBoundaryPeriodic : public SingleBoundaryBase
{
public:

    /**
     * \brief Constructor.
     * \param mesh [in] a Mesh instance.
     * \param loc [in] the location of the target boundary.
     * \param field [in] the target field.
     * \param value [in] BC value.
     */
    SingleBoundaryPeriodic(const type::Mesh &mesh, const type::BCLoc &loc, 
            const type::Field &field, const PetscReal &value); 

    /** \copydoc SingleBoundaryBase::~SingleBoundaryBase */
    virtual ~SingleBoundaryPeriodic() = default;

protected:

    // implementation of SingleBoundaryBase::setGhostICsKernel
    virtual PetscErrorCode setGhostICsKernel(
            const PetscReal &targetValue, type::GhostPointInfo &p);

    // implementation of SingleBoundaryBase::updateEqsKernel
    virtual PetscErrorCode updateEqsKernel(const PetscReal &targetValue,
            const PetscReal &dt, type::GhostPointInfo &p);

}; // SingleBoundaryPeriodic

} // end of namespace boundary
} // end of namespace petibm
