/*---------------------------------------------------------------------------*\
            Copyright (c) 2017-2019, German Aerospace Center (DLR)
-------------------------------------------------------------------------------
License
    This file is part of the VoFLibrary source code library, which is an
	unofficial extension to OpenFOAM.

    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

Class
    Foam::testUtils

Description
    testing utilities to verify correctness of the solution

Author
    Henning Scheufler, DLR, all rights reserved.


SourceFiles
    testUtils.C

\*---------------------------------------------------------------------------*/

#ifndef testUtils_H
#define testUtils_H

#include "word.H"
#include "fvMesh.H"
#include "surfaceFields.H"
#include "volFields.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

namespace test
{
    template<typename Type>
    List<word> flatFieldNames
    (
        const GeometricField<Type, fvsPatchField, surfaceMesh>& sf
    );

    template<typename Type>
    List<word> flatFieldNames
    (
        const GeometricField<Type, fvPatchField, volMesh>& vf
    );

    template<typename Type>
    Field<Type> flatField
    (
        const GeometricField<Type, fvsPatchField, surfaceMesh>& sf
    );

    template<typename Type>
    Field<Type> flatField
    (
        const GeometricField<Type, fvPatchField, volMesh>& vf
    );

    template<typename Type>
    void writeCsv
    (
        word name,
        const volVectorField& C,
        const GeometricField<Type, fvPatchField, volMesh>& vf
    );

    template<typename Type>
    void writeCsv
    (
        word name,
        const surfaceVectorField& C,
        const GeometricField<Type, fvsPatchField, surfaceMesh>& sf
    );


} // End namespace test

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
