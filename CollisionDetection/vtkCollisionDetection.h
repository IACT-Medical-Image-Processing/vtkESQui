/*==========================================================================
--------------------------------------------------
Program: ESQUI
Info and Bugs: {marf,jballesteros}@itccanarias.org
url: http://motivando.me 
--------------------------------------------------

Copyright (c) 2006-2007, Center for Technology in Medicine (CTM), 
University of Las Palmas de Gran Canaria (ULPGC), Canary Islands, Spain.
Copyright (c) 2007-2010, Institute of Technology at CanaryIslands (ITC),
Canary Islands, Spain.

This software is free software; you can redistribute it and/or modify it 
under the terms of the GNU Lesser General Public License (LGPL) as published
by the Free Software Foundation, either version 3 of the License, or (at 
your option) any later version.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1) Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.
2) Redistributions in binary form must reproduce the above copyright 
   notice, this list of conditions and the following disclaimer in the
   documentation and/or other materials provided with the distribution.

You should have received a copy of the GNU Lesser General Public License 
along with this program.  If not, see <http://www.gnu.org/licenses/>.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR 
PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHORS OR CONTRIBUTORS BE 
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
POSSIBILITY OF SUCH DAMAGE.
==========================================================================*/
#ifndef vtkCollisionDetectionLibrary_h
#define vtkCollisionDetectionLibrary_h

#include "vtkESQuiCollisionDetectionWin32Header.h"
#include "vtkObject.h"

class vtkCollisionCollection;
class vtkCollisionModel;
class vtkModelCollection;

class vtkPolyData;
class vtkIntArray;

//! Generic base class for collision detection library interfaces
/*!
 * This class serves as a base class for the collision detection libraries.
 * Scenario object models, vtkCollisionModel must be assigned before process
 * execution. The result of the procedure is collection of collisions,
 * vtkCollisionCollection, between scenario objects.
 * vtkBioEngInterface, an interface based on this class, has been implemented
 * to access the available deformation model, vtkbioeng.
 */

class VTK_ESQUI_COLLISIONDETECTION_EXPORT vtkCollisionDetection: public vtkObject
{
public:
  //! Type revision macro
  vtkTypeRevisionMacro(vtkCollisionDetection, vtkObject);
  vtkCollisionDetection();
  ~vtkCollisionDetection();

  //!Enumeration of detection types
  //BTX
  enum vtkCollisionDetectionMode
  {
    Simple = 0, //Only check between tools and organs
    Extended = 1, //Check between tools and organs, and between tools
    Full = 2 //Check between tools and organs, between tools and between organs
  };
  //ETX

  //! Specify the collision models to be checked in the collision detection process
  void SetModels(vtkModelCollection * models);

  //! Add a new collision model to the detector
  void AddModel(vtkCollisionModel * element);

  //! Return the collisions detected
  vtkCollisionCollection * GetCollisions();

  //! Get total number of collisions detected
  int GetNumberOfCollisions();

  //! Insert a new collision pair
  void InsertNextCollisionPair(int c0, int c1);

  //! Return the collided object id pairs
  vtkIntArray * GetCollisionPairs();

  //! Return a collision pair as a vector
  void GetCollisionPair(int id, int * pair);

  //! Get number of collision pairs
  int GetNumberOfCollisionPairs();

  //BTX
  //!Set detection type
  vtkSetMacro(Mode, vtkCollisionDetectionMode);

  //!Get detection type
  vtkGetMacro(Mode, vtkCollisionDetectionMode);
  //ETX

  //! Set type to simple
  void SetModeToSimple(){this->Mode = Simple;};

  //! Set type to extended
  void SetModeToExtended(){this->Mode = Extended;};

  //! Set type to full
  void SetModeToFull(){this->Mode = Full;};

  //! Method used to detect the collision between organs and tools from the scene must be implemented in the CollisionDetectionLibrary we want to use
  /*!
  * Abstract method to be defined on each implementation class
  */
  virtual void Update() = 0;

  //!Initializes the CollisionDetectionLibrary
  /*!
  * Abstract method to be defined on each implementation class
  */
  virtual void Initialize() = 0;

protected:

  //BTX
  //! Collision detection mode
  vtkCollisionDetectionMode Mode;
  //ETX

  //! Collection of models
  /*!
   * Every model contained in these collection will be processed in the collision detection process.
   */
  vtkModelCollection * Models;

  //! Collection of collisions
  /*!
   * After the collision detection process has been executed the collisions between models
   * are stored in this collection.
   */
  vtkCollisionCollection * Collisions;

  //! Collision Pairs
  /*!
   * Pair of collided objects ids 
   */
  vtkIntArray * CollisionPairs;

  //! Clear previous executions of the collision detection process
  /*!
  * Should be called every time collision detection is performed
  */
  void Reset();

private:
  vtkCollisionDetection(const vtkCollisionDetection &); //NotImplemented
  void operator =(const vtkCollisionDetection &); //Not Implemented

};

#endif

