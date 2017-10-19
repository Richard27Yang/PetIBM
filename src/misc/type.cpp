/***************************************************************************//**
 * \file type.cpp
 * \author Anush Krishnan (anush@bu.edu)
 * \author Olivier Mesnard (mesnardo@gwu.edu)
 * \author Pi-Yueh Chuang (pychuang@gwu.edu)
 * \brief Implementations of members inside namespace `types`.
 */

// here goes our headers
#include <petibm/type.h>


/** \copydoc operator<(const MatStencil &, const MatStencil &). */
bool operator<(const MatStencil &l, const MatStencil &r)
{
    if (l.k < r.k) return true;
    if (l.k > r.k) return false;

    if (l.j < r.j) return true;
    if (l.j > r.j) return false;

    if (l.i < r.i) return true;
    if (l.i > r.i) return false;

    if (l.c < r.c) return true;

    return false;
}


namespace petibm
{
/** \copydoc types */
namespace type
{
    /** \copydoc types::str2dir */
    std::map<std::string, Dir> str2dir {{"x", x}, {"y", y}, {"z", z}};
    /** \copydoc types::dir2str */
    std::map<Dir, std::string> dir2str {{x, "x"}, {y, "y"}, {z, "z"}};


    /** \copydoc types::str2fd */
    std::map<std::string, Field> str2fd {
        {"u", u}, {"v", v}, {"w", w}, {"p", p}, {"vertex", vertex}};
    /** \copydoc types::fd2str */
    std::map<Field, std::string> fd2str {
        {u, "u"}, {v, "v"}, {w, "w"}, {p, "p"}, {vertex, "vertex"}};


    /** \copydoc types::str2bt */
    std::map<std::string, BCType> str2bt {{"NOBC", NOBC},
        {"DIRICHLET", DIRICHLET}, {"NEUMANN", NEUMANN}, 
        {"CONVECTIVE", CONVECTIVE}, {"PERIODIC", PERIODIC}};
    /** \copydoc types::bt2str */
    std::map<BCType, std::string> bt2str {{NOBC, "NOBC"},
        {DIRICHLET, "DIRICHLET"}, {NEUMANN, "NEUMANN"}, 
        {CONVECTIVE, "CONVECTIVE"}, {PERIODIC, "PERIODIC"}};

    /** \copydoc types::str2bl */
    std::map<std::string, BCLoc> str2bl {
        {"left", XMINUS}, {"right", XPLUS}, {"bottom", YMINUS}, 
        {"top", YPLUS}, {"back", ZMINUS}, {"front", ZPLUS},
        {"xMinus", XMINUS}, {"xPlus", XPLUS}, {"yMinus", YMINUS}, 
        {"yPlus", YPLUS}, {"zMinus", ZMINUS}, {"zPlus", ZPLUS},
        {"XMINUS", XMINUS}, {"XPLUS", XPLUS}, {"YMINUS", YMINUS}, 
        {"YPLUS", YPLUS}, {"ZMINUS", ZMINUS}, {"ZPLUS", ZPLUS}};
    /** \copydoc types::bl2str */
    std::map<BCLoc, std::string> bl2str {
        {XMINUS, "xMinus"}, {XPLUS, "xPlus"}, {YMINUS, "yMinus"}, 
        {YPLUS, "yPlus"}, {ZMINUS, "zMinus"}, {ZPLUS, "zPlus"}};


    /** \copydoc types::str2ibm */
    std::map<std::string, IBMethod> str2ibm {
        {"NAVIER_STOKES", NAVIER_STOKES}, {"TAIRA_COLONIUS", TAIRA_COLONIUS}};
    /** \copydoc types::ibm2str */
    std::map<IBMethod, std::string> ibm2str {
        {NAVIER_STOKES, "NAVIER_STOKES"}, {TAIRA_COLONIUS, "TAIRA_COLONIUS"}};


    /** \copydoc types::str2sm */
    std::map<std::string, StaggeredMode> str2sm {
        {"CELL_CENTERED", CELL_CENTERED}, {"STAGGERED_MODE_X", STAGGERED_MODE_X}, 
        {"STAGGERED_MODE_Y", STAGGERED_MODE_Y}, {"STAGGERED_MODE_Z", STAGGERED_MODE_Z}};
    /** \copydoc types::sm2str */
    std::map<StaggeredMode, std::string> sm2str {
        {CELL_CENTERED, "CELL_CENTERED"}, {STAGGERED_MODE_X, "STAGGERED_MODE_X"}, 
        {STAGGERED_MODE_Y, "STAGGERED_MODE_Y"}, {STAGGERED_MODE_Z, "STAGGERED_MODE_Z"}};


    /** \copydoc types::str2et */
    std::map<std::string, ExecuteType> str2et {{"CPU", CPU}, {"GPU", GPU}};
    /** \copydoc types::et2str */
    std::map<ExecuteType, std::string> et2str {{CPU, "CPU"}, {GPU, "GPU"}};


    /** \copydoc types::str2out */
    std::map<std::string, OutputType> str2out {
        {"binary", Binary}, {"vtk", VTK}, {"hdf5", HDF5},
        {"Binary", Binary}, {"VTK", VTK}, {"HDF5", HDF5}};
    /** \copydoc types::out2str */
    std::map<OutputType, std::string> out2str {
        {Binary, "Binary"}, {VTK, "VTK"}, {HDF5, "HDF5"}};

} // end of namespace type
} // end of namespace petibm
