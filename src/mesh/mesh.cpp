/**
 * \file mesh.cpp
 * \brief Implementations of mesh::MeshBase and factory function.
 * \author Anush Krishnan (anus@bu.edu)
 * \author Olivier Mesnard (mesnardo@gwu.edu)
 * \author Pi-Yueh Chuang (pychuang@gwu.edu)
 * \copyright MIT.
 */

# include <petibm/mesh.h>
# include <petibm/cartesianmesh.h>
# include <petibm/io.h>


namespace petibm
{
namespace mesh
{
    
// implement MeshBase::~MeshBase
MeshBase::~MeshBase()
{
    PetscFunctionBeginUser;

    PetscErrorCode ierr;
    PetscBool finalized;

    ierr = PetscFinalized(&finalized); CHKERRV(ierr);
    if (finalized) return;

    for(int f=0; f<dim; ++f)
    {
        ierr = DMDestroy(&da[f]); CHKERRV(ierr);
    }
    ierr = DMDestroy(&da[3]); CHKERRV(ierr);
    ierr = DMDestroy(&da[4]); CHKERRV(ierr);
    ierr = DMDestroy(&UPack); CHKERRV(ierr);
    comm = MPI_COMM_NULL;
}

// implement MeshBase::destroy
PetscErrorCode MeshBase::destroy()
{
    PetscFunctionBeginUser;

    PetscErrorCode ierr;

    dim = -1;
    type::RealVec1D().swap(min);
    type::RealVec1D().swap(max);
    type::IntVec2D().swap(n);
    type::BoolVec2D().swap(periodic);
    type::GhostedVec3D().swap(coord);
    type::GhostedVec3D().swap(dL);
    UN = pN = 0;
    info = std::string();

    for(int f=0; f<dim; ++f)
    {
        ierr = DMDestroy(&da[f]); CHKERRQ(ierr);
    }
    ierr = DMDestroy(&da[3]); CHKERRQ(ierr);
    ierr = DMDestroy(&da[4]); CHKERRQ(ierr);

    type::IntVec1D().swap(nProc);
    type::IntVec2D().swap(bg);
    type::IntVec2D().swap(ed);
    type::IntVec2D().swap(m);
    UNLocal = pNLocal = 0;
    ierr = DMDestroy(&UPack); CHKERRQ(ierr);

    comm = MPI_COMM_NULL;
    mpiSize = mpiRank = 0;

    PetscFunctionReturn(0);
}

// implement MeshBase::printInfo
PetscErrorCode MeshBase::printInfo() const
{
    PetscFunctionBeginUser;

    PetscErrorCode ierr;
    ierr = io::print(info); CHKERRQ(ierr);

    PetscFunctionReturn(0);
}
    
// implement petibm::mesh::createMesh
PetscErrorCode createMesh(const MPI_Comm &comm,
        const YAML::Node &node, type::Mesh &mesh)
{
    PetscFunctionBeginUser;

    mesh = std::make_shared<CartesianMesh>(comm, node);

    PetscFunctionReturn(0);
}

} // end of mesh
} // end of petibm
