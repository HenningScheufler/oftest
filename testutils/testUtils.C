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
    Foam::syncSurfField

Description
    stores all geometric information for the phase boundary
    NOTES we assume that it is called after the advection step
Author
    Henning Scheufler, DLR, all rights reserved.


SourceFiles
    syncSurfField.C

\*---------------------------------------------------------------------------*/
#include "testUtils.H"
#include "processorPolyPatch.H"
#include "OFstream.H"


template<typename Type>
Foam::List<Foam::word> Foam::test::flatFieldNames
(
    const GeometricField<Type, fvsPatchField, surfaceMesh>& sf
)
{
    const fvMesh& mesh = sf.mesh();
    const fvBoundaryMesh& bMesh = mesh.boundary();

    // empty patches have a size of zero if the the are not empty the will
    //  overwrite the default value
    List<word> nameField(mesh.nFaces(),"empty");

    // internalFaces first
    label flatIdx = 0;
    forAll(sf,facei)
    {
        nameField[flatIdx] = "internal";
        flatIdx++;
    }

    forAll(bMesh,patchi)
    {
        // empty patch are skipped they have a size of zero
        forAll(bMesh[patchi],i)
        {
            nameField[flatIdx] = bMesh[patchi].name();
            flatIdx++;
        }
    }

    return nameField;

}

template<typename Type>
Foam::List<Foam::word> Foam::test::flatFieldNames
(
    const GeometricField<Type, fvPatchField, volMesh>& vf
)
{
    const fvMesh& mesh = vf.mesh();
    const fvBoundaryMesh& bMesh = mesh.boundary();
    // empty patches have a size of zero if the the are not empty the will
    //  overwrite the default value
    List<word> nameField(mesh.nCells()+mesh.nBoundaryFaces(),"empty");

    // internalFaces first
    label flatIdx = 0;
    forAll(vf,celli)
    {
        nameField[flatIdx] = "internal";
        flatIdx++;
    }

    forAll(bMesh,patchi)
    {
        // empty patch are skipped they have a size of zero
        forAll(bMesh[patchi],i)
        {
            nameField[flatIdx] = bMesh[patchi].name();
            flatIdx++;
        }
    }

    return nameField;
}

template<typename Type>
Foam::Field<Type> Foam::test::flatField
(
    const GeometricField<Type, fvsPatchField, surfaceMesh>& sf
)
{
    const fvMesh& mesh = sf.mesh();
    Field<Type> flatField(mesh.nFaces(),Zero);

    // internalFaces first
    label flatIdx = 0;
    forAll(sf,facei)
    {
        flatField[flatIdx] = sf[facei];
        flatIdx++;
    }

    forAll(sf.boundaryField(),patchi)
    {
        forAll(sf.boundaryField()[patchi],i)
        {
            flatField[flatIdx] = sf.boundaryField()[patchi][i];
            flatIdx++;
        }
    }

    return flatField;

}

template<typename Type>
Foam::Field<Type> Foam::test::flatField
(
    const GeometricField<Type, fvPatchField, volMesh>& vf
)
{
    const fvMesh& mesh = vf.mesh();
    Field<Type> flatField(mesh.nCells()+mesh.nBoundaryFaces(),Zero);

    // internalFaces first
    label flatIdx = 0;
    forAll(vf,celli)
    {
        flatField[flatIdx] = vf[celli];
        flatIdx++;
    }

    forAll(vf.boundaryField(),patchi)
    {
        forAll(vf.boundaryField()[patchi],i)
        {
            flatField[flatIdx] = vf.boundaryField()[patchi][i];
            flatIdx++;
        }
    }

    return flatField;
}

template<typename Type>
void Foam::test::writeCsv
(
    word name,
    const volVectorField& C,
    const GeometricField<Type, fvPatchField, volMesh>& vf
)
{

    fileName fName(name + ".csv");
    if(Pstream::parRun())
    {
        fName = fileName(name + "par.csv");
    }
    OFstream os(fName);

    List<Field<Type>> volField(Pstream::nProcs());
    List<vectorField> centre(Pstream::nProcs());
    List<List<word>> names(Pstream::nProcs());

    volField[Pstream::myProcNo()] = test::flatField(vf);
    centre[Pstream::myProcNo()] = test::flatField(C);
    names[Pstream::myProcNo()] = test::flatFieldNames(vf);

    Pstream::gatherList(volField);
    Pstream::gatherList(centre);
    Pstream::gatherList(names);

    if (Pstream::master())
    {

        Field<Type> combinedVolField;
        vectorField combinedCentre;
        List<word> combinedNames;

        forAll(volField,proci)
        {
            combinedVolField.append(volField[proci]);
            combinedCentre.append(centre[proci]);
            combinedNames.append(names[proci]);
        }


        // write as csv
        forAll(combinedVolField,i)
        {
            os  << combinedCentre[i].x() << "," << combinedCentre[i].y() << "," << combinedCentre[i].z() << ",";
            for (direction cmpt = 0; cmpt < pTraits<Type>::nComponents; cmpt++)
            {
                os << component(combinedVolField[i],cmpt) << ",";
            }
            os << combinedNames[i] <<  endl;
        }
    }

}

template<typename Type>
void Foam::test::writeCsv
(
    word name,
    const surfaceVectorField& Cf,
    const GeometricField<Type, fvsPatchField, surfaceMesh>& sf
)
{

    fileName fName(name + ".csv");
    if(Pstream::parRun())
    {
        fName = fileName(name + "par.csv");
    }
    OFstream os(fName);

    List<Field<Type>> surfaceField(Pstream::nProcs());
    List<vectorField> centre(Pstream::nProcs());
    List<List<word>> names(Pstream::nProcs());

    surfaceField[Pstream::myProcNo()] = test::flatField(sf);
    centre[Pstream::myProcNo()] = test::flatField(Cf);
    names[Pstream::myProcNo()] = test::flatFieldNames(sf);

    Pstream::gatherList(surfaceField);
    Pstream::gatherList(centre);
    Pstream::gatherList(names);

    if (Pstream::master())
    {

        Field<Type> combinedSurfaceField;
        vectorField combinedCentre;
        List<word> combinedNames;

        forAll(surfaceField,proci)
        {
            combinedSurfaceField.append(surfaceField[proci]);
            combinedCentre.append(centre[proci]);
            combinedNames.append(names[proci]);
        }

        // write as csv
        forAll(combinedSurfaceField,i)
        {
            os  << combinedCentre[i].x() << "," << combinedCentre[i].y() << "," << combinedCentre[i].z() << ",";
            for (direction cmpt = 0; cmpt < pTraits<Type>::nComponents; cmpt++)
            {
                os << component(combinedSurfaceField[i],cmpt) << ",";
            }
            os << combinedNames[i] <<  endl;
        }
    }

}

template Foam::List<Foam::word> Foam::test::flatFieldNames(const GeometricField<scalar, fvsPatchField, surfaceMesh>& sf);
template Foam::List<Foam::word> Foam::test::flatFieldNames(const GeometricField<vector, fvsPatchField, surfaceMesh>& sf);

template Foam::List<Foam::word> Foam::test::flatFieldNames(const GeometricField<scalar, fvPatchField, volMesh>& vf);
template Foam::List<Foam::word> Foam::test::flatFieldNames(const GeometricField<vector, fvPatchField, volMesh>& vf);

template Foam::Field<Foam::scalar> Foam::test::flatField(const GeometricField<scalar, fvsPatchField, surfaceMesh>& sf);
template Foam::Field<Foam::vector> Foam::test::flatField(const GeometricField<vector, fvsPatchField, surfaceMesh>& sf);

template Foam::Field<Foam::scalar> Foam::test::flatField(const GeometricField<scalar, fvPatchField, volMesh>& vf);
template Foam::Field<Foam::vector> Foam::test::flatField(const GeometricField<vector, fvPatchField, volMesh>& vf);

template void Foam::test::writeCsv(word name,const volVectorField& C,const GeometricField<scalar, fvPatchField, volMesh>& vf);
template void Foam::test::writeCsv(word name,const volVectorField& C,const GeometricField<vector, fvPatchField, volMesh>& vf);

template void Foam::test::writeCsv(word name,const surfaceVectorField& C,const GeometricField<scalar, fvsPatchField, surfaceMesh>& vf);
template void Foam::test::writeCsv(word name,const surfaceVectorField& C,const GeometricField<vector, fvsPatchField, surfaceMesh>& vf);
