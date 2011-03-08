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
#ifndef __vtkToolProbe_h
#define __vtkToolProbe_h

#include "vtkESQuiScenarioWin32Header.h"
#include "vtkToolLaparoscopy.h"

//! Implementation class of probe
/*!
	vtkToolProbe is the class that implements the probe tool, inside the scene.
	Contains methods for position control of the tool in the scene and collision detection.
	Probe are composed of 2 pieces: 1 stick and 1 tip (vtkPiece)
	Inherits vtkToolLaparascopy class
*/

class VTK_ESQUI_SCENARIO_EXPORT vtkToolProbe: public vtkToolLaparoscopy
{
public:

	//!Type revision macro
	vtkTypeRevisionMacro(vtkToolProbe,vtkToolLaparoscopy);

	//!Create new vtkToolProbe object
	static vtkToolProbe *New();

	//!Return class name
	const char *GetClassName() { return "vtkToolProbe"; }

	//!Print the attributes value
	void PrintSelf(ostream& os, vtkIndent indent);

	
	//!Tool type definition
	enum vtkPieceType{
		Stick = 0,
		Tip = 1,
	};
	

	//!Initialize the tool from VTK file
	/*!
		This function initializes the tool whose mesh is described on a VTK file
	*/
	virtual void Init();

	//!Update the tool
	/*!
	 * This function update the tool values
	 */
	virtual void Update();

	//!Set stick polydata filename
	/*!
	* Specify the path of the file that contains the stick piece polydata
	*/
	vtkSetStringMacro(StickFileName);

	//!Return the stick polydata file name
	/*!
	 * Path of the file that contains the probe piece polydata
	 */
	vtkGetStringMacro(StickFileName);

	//!Set probe polydata filename
	/*!
	 * Specify the path of the file that contains the probe piece polydata
	 */
	vtkSetStringMacro(TipFileName);

	//!Return the left probe polydata file name
	/*!
	* Path of the file that contains the probe piece polydata
	*/
	vtkGetStringMacro(TipFileName);

	//!Set stick texture filename
	/*!
	 * Specify the path of the file that contains the stick piece texture
	 */
	vtkSetStringMacro(StickTextureFileName);

	//!Return the stick texture file name
	/*!
	 * Path of the file that contains the stick piece texture
	 */
	vtkGetStringMacro(StickTextureFileName);

	//!Set tip texture filename
	/*!
	 * Specify the path of the file that contains the tip piece texture
	 */
	vtkSetStringMacro(TipTextureFileName);

	//!Return the tip texture file name
	/*!
	 * Path of the file that contains the tip piece texture
	 */
	vtkGetStringMacro(TipTextureFileName);

	//! Sets the probe yaw angle
	void Yaw(double angle);

	//! Sets the probe pitch angle
	void Pitch(double angle);

	//! Sets the probe roll angle
	void Roll(double angle);

protected:	

	vtkToolProbe();
	~vtkToolProbe();

private:

	vtkToolProbe (const vtkToolProbe &); //Not Implemented
	void operator =(const vtkToolProbe &); //Not Implemented

	char * StickFileName;
	char * TipFileName;

	char * StickTextureFileName;
	char * TipTextureFileName;

	//!Return the stick piece
	/*!
	 * Return the vtkPiece object of the stick
	 */
	vtkPiece * GetStick(){return this->GetPiece(vtkToolProbe::Stick);};

	//!Return the tip piece
	/*!
	 * Return the vtkPiece object of the tip
	 */
	vtkPiece * GetTip(){return this->GetPiece(vtkToolProbe::Tip);};

};
#endif
