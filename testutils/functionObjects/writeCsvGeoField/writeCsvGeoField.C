/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright (C) 2021 AUTHOR,AFFILIATION
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

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

\*---------------------------------------------------------------------------*/

#include "writeCsvGeoField.H"
#include "Time.H"
#include "fvMesh.H"
#include "addToRunTimeSelectionTable.H"

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace Foam
{
namespace functionObjects
{
    defineTypeNameAndDebug(writeCsvGeoField, 0);
    addToRunTimeSelectionTable(functionObject, writeCsvGeoField, dictionary);
}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

Foam::functionObjects::writeCsvGeoField::writeCsvGeoField
(
    const word& name,
    const Time& runTime,
    const dictionary& dict
)
:
    fvMeshFunctionObject(name, runTime, dict),
    wordData_(dict.lookupOrDefault<word>("wordData", "defaultWord")),
    scalarData_(dict.get<scalar>("scalarData")),
    labelData_(dict.get<label>("labelData"))
{
    read(dict);
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

Foam::functionObjects::writeCsvGeoField::~writeCsvGeoField()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

bool Foam::functionObjects::writeCsvGeoField::read(const dictionary& dict)
{
    dict.readIfPresent("wordData", wordData_);

    dict.readEntry("scalarData", scalarData_);
    dict.readEntry("labelData", labelData_);

    return true;
}


bool Foam::functionObjects::writeCsvGeoField::execute()
{
    return true;
}


bool Foam::functionObjects::writeCsvGeoField::end()
{
    return true;
}


bool Foam::functionObjects::writeCsvGeoField::write()
{
    return true;
}


// ************************************************************************* //
