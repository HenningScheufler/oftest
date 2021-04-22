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

Class
    Foam::functionObjects::writeCsvGeoField

Group

Description
    This function object...

    Example of function object specification:
    \verbatim
    writeCsvGeoField1
    {
        type           writeCsvGeoField;
        libs ("libwriteCsvGeoFieldFunctionObject.so");
        ...
        wordData       someWord;
        scalarData     1.0;
        labelData      1;
    }
    \endverbatim

Usage
    \table
        Property     | Description               | Required | Default value
        type         | type name: writeCsvGeoField | yes      |
        wordData     | some word option...       | no       | defaultWord
        scalarData   | some scalar value...      | yes      |
        labelData    | some label value...       | yes      |
    \endtable

SourceFiles
    writeCsvGeoField.C

\*---------------------------------------------------------------------------*/

#ifndef writeCsvGeoField_H
#define writeCsvGeoField_H

#include "fvMeshFunctionObject.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{
namespace functionObjects
{

/*---------------------------------------------------------------------------*\
                   Class writeCsvGeoField Declaration
\*---------------------------------------------------------------------------*/

class writeCsvGeoField
:
    public fvMeshFunctionObject
{
    // Private data

        //- word
        word wordData_;

        //- scalar
        scalar scalarData_;

        //- label
        label labelData_;


    // Private Member Functions


        //- No copy construct
        writeCsvGeoField(const writeCsvGeoField&);

        //- No copy assignment
        void operator=(const writeCsvGeoField&);


public:

    //- Runtime type information
    TypeName("writeCsvGeoField");


    // Constructors

        //- Construct from Time and dictionary
        writeCsvGeoField
        (
            const word& name,
            const Time& runTime,
            const dictionary& dict
        );


    //- Destructor
    virtual ~writeCsvGeoField();


    // Member Functions

        //- Read the writeCsvGeoField data
        virtual bool read(const dictionary& dict);

        //- Execute, currently does nothing
        virtual bool execute();

        //- Execute at the final time-loop, currently does nothing
        virtual bool end();

        //- Write the writeCsvGeoField
        virtual bool write();
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace functionObjects
} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
