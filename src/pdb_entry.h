/*
 * Copyright (C) 2014 Tokyo Institute of Technology
 *
 *
 * This file is part of MEGADOCK.
 * MEGADOCK is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * MEGADOCK is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with MEGADOCK.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

//============================================================================//
//
//  Software Name : MEGADOCK
//
//  Class Name : PDBEntry
//
//  Contact address : Tokyo Institute of Technology, AKIYAMA Lab.
//
//============================================================================//

#ifndef PDBEntry_h
#define PDBEntry_h 1

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "parallel.h"

using namespace std;


class PDBEntry                      // ATOM element of pdb file class
{
private:
	friend class  FFTProcess;
    string        _Input_file;            // Input file    
    int           _Num_atoms;             // Number of atoms
    vector<string>    _Atom_type;         // Atom type of PDB file
    float         *_Coordinate;           // Atomic coordinate
protected:
    virtual void      pdb_read();         // Read pdb file
    virtual string    erase_space(const string &s);   // Head and tail space erase and double space to single
public:
    PDBEntry(string &rinput_file) : _Input_file(rinput_file) {
#ifdef DEBUG
        cout << "Constructing PDBEntry.\n";
#endif
    }
    virtual ~PDBEntry() {                 // Destructor
#ifdef DEBUG
        cout << "Destructing PDBEntry.\n";
#endif
        delete [] _Coordinate;
    }
    virtual string    input_file()            {
        return _Input_file;
    }
    virtual void      num_atoms(int &Num_atoms)   {
        _Num_atoms = Num_atoms;
        return;
    }
    virtual int       num_atoms()             {
        return _Num_atoms;
    }
    virtual void      coordinate(const int &i,float *Coordinate) {
        for( int j = 0 ; j < 3 ; j++ ) {
            _Coordinate[3*i+j]    = Coordinate[j];
        }
        return;
    }
    virtual void      coord_all(float *cod) {
        for( int i = 0 ; i < _Num_atoms*3 ; i++ ) {
            _Coordinate[i]    = cod[i];
        }
        return;
    }
    virtual float     coordinate(const int &i,int j)  {
        return _Coordinate[3*i+j];
    }
    virtual string    atom_type(const int &i)     {
        return _Atom_type[i];
    }
};

#endif
