//
//  globals.h
//  connexionUsineHydro
//
//  Created by Julien on 05/03/2015.
//
//

#pragma once

#define GLOBALS Globals::instance()

class Globals
{
	public:
		Globals					();


		static Globals*			instance();




	private:
		static Globals*			smp_instance;
};