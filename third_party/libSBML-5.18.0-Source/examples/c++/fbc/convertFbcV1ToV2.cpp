/**
 * @file    convertFbcV1ToV2.cpp
 * @brief   Convert Fbc V1 models to Fbc V2
 * @author  Frank T. Bergmann
 *
 * <!--------------------------------------------------------------------------
 * This sample program is distributed under a different license than the rest
 * of libSBML.  This program uses the open-source MIT license, as follows:
 *
 * Copyright (c) 2013-2018 by the California Institute of Technology
 * (California, USA), the European Bioinformatics Institute (EMBL-EBI, UK)
 * and the University of Heidelberg (Germany), with support from the National
 * Institutes of Health (USA) under grant R01GM070923.  All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 * Neither the name of the California Institute of Technology (Caltech), nor
 * of the European Bioinformatics Institute (EMBL-EBI), nor of the University
 * of Heidelberg, nor the names of any contributors, may be used to endorse
 * or promote products derived from this software without specific prior
 * written permission.
 * ------------------------------------------------------------------------ -->
 */

#include <iostream>
#include <sbml/SBMLTypes.h>
#include <sbml/conversion/ConversionProperties.h>

#include <cstring>

using namespace std;
LIBSBML_CPP_NAMESPACE_USE

int
main (int argc, char* argv[])
{
  if (argc < 3 )
  {
    cout << endl << "Usage: convertFbcV1ToV2 input-filename output-filename [-strict]"
         << endl << endl;
    return 2;
  }

  bool strict = argc == 4 && strcmp(argv[3], "-strict") == 0;
  
  SBMLDocument *d = readSBML(argv[1]);
  if ( d->getNumErrors(LIBSBML_SEV_ERROR) > 0)
  {
    d->printErrors();
  }
  else
  {
    /* create a new conversion properties structure */
    ConversionProperties props;

    /* add an option that we want to strip a given package */
    props.addOption("convert fbc v1 to fbc v2", true,
                    "convert fbc v1 to fbc v2");
    props.addOption("strict", strict, 
      "should the model be a strict one (i.e.: all non-specified bounds will be filled)");
 
    /* perform the conversion */
    int result = d->convert(props);
    if (result != LIBSBML_OPERATION_SUCCESS)
    {
      cout<< "conversion failed ... " << endl;
      return 3;
    }

    writeSBML(d, argv[2]);
  }

  return 0;
}
